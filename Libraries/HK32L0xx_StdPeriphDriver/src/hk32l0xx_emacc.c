/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_emacc.c
* @brief:     This file provides firmware functions to manage the following
*             functionalities of the EMACC peripheral:
*             + Configuration
*             + Read/Write operations
*             + DMA transfers management
*             + Interrupts and flags management
* @author:    AE Team
* @version:   V1.0.0/2024-01-15
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_emacc.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup EMACC EMACC
  * @brief EMACC driver modules
  * @{
*/
/*Private typedef -----------------------------------------------------------*/
/*Private define ------------------------------------------------------------*/


/** @defgroup EMACC_Private_Variables EMACC_Private_Variables
  * @{
  */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint16_t MMItable[65] =
{
    32767, 32390, 32146, 31907, 31673, 31444, 31220, 31001, 30787, 30577, 30371,
    30169, 29971, 29777, 29587, 29400, 29217, 29037, 28861, 28687, 28517,
    28350, 28185, 28024, 27865, 27709, 27555, 27404, 27256, 27110, 26966,
    26824, 26685, 26548, 26413, 26280, 26149, 26019, 25892, 25767, 25643,
    25521, 25401, 25283, 25166, 25051, 24937, 24825, 24715, 24606, 24498,
    24392, 24287, 24183, 24081, 23980, 23880, 23782, 23684, 23588, 23493,
    23400, 23307, 23215, 23125
};
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup EMACC_Private_Functions EMACC_Private_Functions
  * @{
  */

/** @defgroup EMACC_Group1 Initialization and configuration
 *  @brief   Initialization and configuration.
 *
@verbatim
 ===============================================================================
                ##### Initialization and configuration #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  De-initializes the EMACC peripheral registers to their default reset values
  * @retval None
  */
void EMACC_DeInit(void)
{
    /* Enable EMACC reset state */
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_EMACC, ENABLE);
    /* Release EMACC from reset state */
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_EMACC, DISABLE);
}

/**
  * @brief  Initializes the EMACC peripheral according to the specified parameters
  *         in the EMACC_PI_InitTypeDef structure.
  * @param  EMACC_ID_InitStruct: pointer to a EMACC_PI_InitTypeDef structure that contains
  *         the configuration information for ID of the EMACC peripheral.
  * @param  EMACC_IQ_InitStruct : pointer to a EMACC_PI_InitTypeDef structure that contains
  *         the configuration information for IQ of  the EMACC peripheral.
  * @retval None
  */
void EMACC_Init(EMACC_PI_InitTypeDef* EMACC_ID_InitStruct, EMACC_PI_InitTypeDef* EMACC_IQ_InitStruct)
{
    int16_t i ;
    uint32_t* Pdata = PID_RAM_BASE;

    /*init PI Id*/
    EMACC->D_KPKI = EMACC_ID_InitStruct->wKpiGain;
    EMACC->D_INTUPPER = EMACC_ID_InitStruct->wUpperIntegralLimit;
    EMACC->D_INTLOWER = EMACC_ID_InitStruct->wLowerIntegralLimit;
    EMACC->D_INTOUT = (uint16_t)(EMACC_ID_InitStruct->hLowerOutputLimit) | ((uint16_t)(EMACC_ID_InitStruct->hUpperOutputLimit) << 16);
    EMACC->D_PI_DIV = (uint16_t)(EMACC_ID_InitStruct->hKiDivisorPOW2) | ((uint16_t)(EMACC_ID_InitStruct->hKpDivisorPOW2) << 16);
    /*init PI Iq*/
    EMACC->Q_KPKI = EMACC_IQ_InitStruct->wKpiGain;
    EMACC->Q_INTUPPER = EMACC_IQ_InitStruct->wUpperIntegralLimit;
    EMACC->Q_INTLOWER = EMACC_IQ_InitStruct->wLowerIntegralLimit;
    EMACC->Q_INTOUT = (uint16_t)(EMACC_IQ_InitStruct->hLowerOutputLimit) | ((uint16_t)(EMACC_IQ_InitStruct->hUpperOutputLimit) << 16);
    EMACC->Q_PI_DIV = (uint16_t)(EMACC_IQ_InitStruct->hKiDivisorPOW2) | ((uint16_t)(EMACC_IQ_InitStruct->hKpDivisorPOW2) << 16);

    /*RAM WR ENABLE*/
    EMACC->CR |= EMACC_CR_RAMWR_EN | EMACC_CR_RAMRD_EN;

    /*init MMITABLE*/
    for (i = 0; i < 65 ; )
    {
        *Pdata = MMItable[i] | (uint32_t)(MMItable[i + 1] << 16);
        Pdata ++;
        i = i + 2;
    }

    /*init the Circle limitation */
    EMACC->CIRCLELMT_CFG = (CIRCLELIM_TABLE_INDEX << 16) | CIRCLELIM_MAXMODULE;

    /*RAM WR DISABLE*/
    EMACC->CR &= ~(EMACC_CR_RAMWR_EN | EMACC_CR_RAMRD_EN);

}

/**
  * @brief  Enable or disable the EMACC peripheral.
  * @param  EMACC_Module
  *            @arg EMACC_EN: Electric Motor acceleration module
  *            @arg EMACC_CORDIC_EN:Cordic module enable
  *            @arg EMACC_CLARKE_EN:Clarke transformation enable
  *            @arg EMACC_PARK_EN:Park transformation enable
  *            @arg EMACC_PID_EN:PID module enable
  *            @arg EMACC_REVPARK_EN:Reverse park transformation enable
  * @param  NewState: new state of the EMACC peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EMACC_Cmd(uint32_t EMACC_Module, FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_EMACC_MODULE(EMACC_Module));


    if (NewState != DISABLE)
    {
        EMACC->CR &= (uint32_t)EMACC_MODULE_MASK;
        /* Enable the EMACC Peripheral */
        EMACC->CR |= (uint32_t) (EMACC_Module);
    }
    else
    {
        /* Disable the EMACC peripheral */
        EMACC->CR &= (uint32_t)(~EMACC_Module);
    }
}

/**
  * @brief  Set Clarke transimit input value
  * @param  Ia: the current of a axis
  * @param  Ib: the current of b axis
  * @retval None
  */
void EMACC_SetClarke(uint16_t Ia, uint16_t Ib)
{
    EMACC->CLARKE_LDR = (uint32_t) ((Ia << 16) | Ib);
}

/**
  * @brief  Set the Electric Angle input value
  * @param  ElAngle: Electric Angle
  * @retval None
  */
void EMACC_SetEleAngle(int16_t ElAngle)
{
    EMACC->ANG_LDR = ElAngle;
}

/**
  * @}
  */

/** @defgroup EMACC_Group2 EMACC Calculate
 *  @brief   EMACC calculate.
 *
@verbatim
 ===============================================================================
                ##### EMACC Calculate #####
 ===============================================================================

@endverbatim
  * @{
  */
/**
  * @brief  Execute the EMACC hardware module.
  * @param  hElAngle: electric degress
  * @param  Iab: current of the A axls and B axls
  * @param  Iqdref: Reference current of the d&q coordinate axis
  * @retval None
  */
Volt_Components EMACC_Cal(int16_t hElAngle, Curr_Components Iab, Curr_Components Iqdref)
{
    __IO uint32_t CaleStatus = 0;
    Volt_Components Valphabeta;

    /*input ref */
    EMACC->ID_REF = Iqdref.qI_Component2 << 16 | Iqdref.qI_Component1;
    EMACC->IQ_REF = Iqdref.qI_Component2 << 16 | Iqdref.qI_Component1;

    /*input hElAngle*/
    EMACC->ANG_LDR = hElAngle;

    /*input Iab */
    EMACC->CLARKE_LDR = (uint16_t)(Iab.qI_Component2) | ((uint16_t)(Iab.qI_Component1) << 16) ;

    /*wait result*/
    do
    {
        CaleStatus = EMACC->SR & EMACC_SR_RPARK_CF;
    } while (CaleStatus == 0);

    Valphabeta.qV_Component1 = (EMACC->REVPARK_OUT >> 16) & 0xFFFF;
    Valphabeta.qV_Component2 = EMACC->REVPARK_OUT & 0xFFFF;

    /*clear status*/
    EMACC->CLRSR |= EMACC_CLEAR_STATUS_MASK;

    return Valphabeta;
}
/**
  * @}
  */


/** @defgroup EMACC_Group3 EMACC Results
 *  @brief   Get results for each segment of EMACC.
 *
@verbatim
 ===============================================================================
                ##### EMACC Results #####
 ===============================================================================

@endverbatim
  * @{
  */
/**
  * @brief  This function returns cosine and sine functions of the electric angle fed in EMACC_ANG_LDR register
  * @retval Cos(angle) in Trig_Components format
  */
uint16_t EMACC_GetCordicOutCosx(void)
{
    return (uint16_t)((EMACC->CORDIC_OUT & 0xFFFF0000) >> 16);
}

/**
  * @brief  This function returns cosine and sine functions of the electric angle fed in EMACC_ANG_LDR register
  * @retval Sin(angle) in Trig_Components format
  */
uint16_t EMACC_GetCordicOutSinx(void)
{
    return (uint16_t)(EMACC->CORDIC_OUT & 0x0000FFFF);
}

/**
  * @brief  Get the current of alpha axis in clarke module
  * @retval the current of alpha axis in clarke module
  */
uint16_t EMACC_GetClarkeOutIalpha(void)
{
    return (uint16_t)((EMACC->CLARKE_OUT & 0xFFFF0000) >> 16);
}

/**
  * @brief  Get the current of Beta axis in clarke module
  * @retval the current of Beta axis in clarke module
  */
uint16_t EMACC_GetClarkeOutIbeta(void)
{
    return (uint16_t)(EMACC->CLARKE_OUT & 0x0000FFFF);
}

/**
  * @brief  Get the current of D axis in park module
  * @retval the current of D axis in clarke module
  */
uint16_t EMACC_GetParkOutId(void)
{
    return (uint16_t)((EMACC->PARK_OUT & 0xFFFF0000) >> 16);
}

/**
  * @brief  Get the current of Q axis in park module
  * @retval the current of Q axis in park module
  */
uint16_t EMACC_GetParkOutIq(void)
{
    return (uint16_t)(EMACC->PARK_OUT & 0x0000FFFF);
}


/**
  * @brief  Get the Voltage of D axis in PID module for foc system
  * @retval the Voltage of D axis in PID module
  */
uint16_t EMACC_GetPIDOutVd(void)
{
    return (uint16_t)((EMACC->PID_OUT & 0xFFFF0000) >> 16);
}

/**
  * @brief  Get the Voltage of Q axis in PID module for foc system
  * @retval the Voltage of Q axis in PID module
  */
uint16_t EMACC_GetPIDOutVq(void)
{
    return (uint16_t)(EMACC->PID_OUT & 0x0000FFFF);
}

/**
  * @brief  Get the Voltage of alpha axis in RevPark module
  * @retval the Voltage of alpha axis in RevPark module
  */
uint16_t EMACC_GetRevParkOutValpha(void)
{
    return (uint16_t)((EMACC->REVPARK_OUT & 0xFFFF0000) >> 16);
}

/**
  * @brief  Get the Voltage of beta axis in RevPark module
  * @retval the Voltage of beta axis in RevPark module
  */
uint16_t EMACC_GetRevParkOutVbeta(void)
{
    return (uint16_t)(EMACC->REVPARK_OUT & 0x0000FFFF);
}
/**
  * @}
  */

/** @defgroup EMACC_Group4 EMACC Flags
 *  @brief   get or clear emacc flags.
 *
@verbatim
 ===============================================================================
                ##### EMACC Flags #####
 ===============================================================================

@endverbatim
  * @{
  */
/**
  * @brief  Checks whether the specified EMACC status is set or not.
  * @param  EMACC_STATUS: specifies the EMACC interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg EMACC_CORDIC_STATUS
  *            @arg EMACC_CLARK_STATUS
  *            @arg EMACC_PARK_STATUS
  *            @arg EMACC_PID_STATUS
  *            @arg EMACC_RPARK_STATUS
    *            @arg EMACC_TRACE_BUSY_STATUS
  * @retval The new state of EMACC_FLAG (SET or RESET).
  */
FlagStatus EMACC_GetFlag(uint32_t EMACC_STATUS)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_EMACC_GET_FLAG(EMACC_STATUS));

    /* Check the status of the specified EMACC interrupt */
    if ((uint32_t)(EMACC->SR & EMACC_STATUS) != (uint32_t)RESET)
    {
        /* EMACC FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* EMACC FLAG is reset */
        bitstatus = RESET;
    }

    /* Return the EMACC FLAG status */
    return  bitstatus;
}

/**
  * @brief  Clears the EMACC's pending flags.
  * @param  EMACC_FLAG: specifies the flag bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg EMACC_CORDIC_FLAG: cordic Flag
  *            @arg EMACC_CLARK_FLAG: clark tansmit Flag
  *            @arg EMACC_PARK_FLAG: park tansmit Flag
  *            @arg EMACC_PID_FLAG:  pid tansmit Flag
  *            @arg EMACC_RPARK_FLAG: revser park tansmit Flag
  *            @arg EMACC_ALL_STATUS_FLAG: all status flag
  * @retval None
  */
void EMACC_ClearFlag( uint16_t EMACC_FLAG)
{
    /* Check the parameters */
    assert_param(IS_EMACC_CLEAR_FLAG(EMACC_FLAG));

    /* Clear the flags */
    EMACC->CLRSR |= (uint16_t)EMACC_FLAG;
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

/**
  * @}
  */



