/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_divsqrt.c
* @brief:     The file is the unique include file that the application programmer
*             is using in the C source code.it is a patch file
* @author:    AE Team
* @version:   V1.0.0/2024-01-08
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_divsqrt.h"
#include "hk32l0xx_rcc.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup DVSQ  DVSQ
  * @brief DVSQ driver modules
  * @{
  */

/** @defgroup DVSQ_Private_Functions   DVSQ_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the Divsqrt peripheral registers values.
  * @retval None
  */
void DVSQ_Init(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DVSQ, ENABLE);
    DVSQ_EnableDivFastStart();
}

/**
  * @brief  Deinitializes the Divsqrt peripheral registers to their default reset
  *         values.
  * @retval None
  */
void DVSQ_DeInit(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DVSQ, DISABLE);
}

/**
  * @brief  Unsigned division operation
  * @param  Dividend: 32bits Unsigned dividend
  * @param  Divisor: 32bits Unsigned divisor
  * @param  pRemainder: The data pointer used to store the remainder by dividing
  * @retval the quotient
  */
uint32_t DVSQ_UDivsion(uint32_t Dividend, uint32_t Divisor, uint32_t *pRemainder)
{
    DVSQ_Wait();
    DVSQ_ConfigDivUnsigned();
    DVSQ_EnableDivFastStart();
    DVSQ->DIVIDEND = Dividend;
    DVSQ->DIVISOR  = Divisor;
    DVSQ_Wait();

    if (pRemainder != NULL)
    {
        *pRemainder = DVSQ->REMAINDER;
    }

    return DVSQ->RES;
}


/**
  * @brief  Signed division operation
  * @param  Dividend: 32bits Signed dividend
  * @param  Divisor: 32bits Signed divisor
  * @param  pRemainder: The data pointer used to store the remainder by dividing
  * @retval the quotient
  */
int32_t DVSQ_Divsion(int32_t Dividend, int32_t Divisor, int32_t *pRemainder)
{
    DVSQ_Wait();
    // config for signed division operation
    DVSQ_ConfigDivSigned();
    DVSQ_EnableDivFastStart();
    DVSQ->DIVIDEND = Dividend;
    DVSQ->DIVISOR  = Divisor;
    DVSQ_Wait();

    if (pRemainder != NULL)
    {
        *pRemainder = DVSQ->REMAINDER;
    }

    return (int32_t)DVSQ->RES;
}


/**
  * @brief  Square root operation
  * @param  Radicand: the radicand
  * @retval Square root operation result
  */
uint32_t DVSQ_Sqrt(uint32_t Radicand)
{
    DVSQ_Wait();
    // config for normal square root operation
    DVSQ_ConfigSqrtPresNormal();
    DVSQ->RADICAND = Radicand;
    DVSQ_Wait();
    return DVSQ->RES;
}

/**
  * @brief  High precision square root operation
  * @param  Radicand: the radicand
  * @param  fraction: The data pointer used to storeDecimal part of the square root result
  * @retval The integer part of the square root result
  */
uint16_t DVSQ_SqrtH(uint32_t Radicand, uint16_t *fraction)
{
    uint16_t result;
    DVSQ_Wait();
    // config for high precision square root operation
    DVSQ_ConfigSqrtPresHigh();
    DVSQ->RADICAND = Radicand;
    DVSQ_Wait();
    result = (uint16_t)((DVSQ->RES >> 16) & 0xffff);
    *fraction = (uint16_t)(DVSQ->RES & 0xffff);
    return result;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


