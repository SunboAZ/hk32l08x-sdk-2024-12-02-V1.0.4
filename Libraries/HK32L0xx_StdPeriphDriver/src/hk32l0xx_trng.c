/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_trng.c
* @brief:     TRNG module driver.
* @author:    AE Team
* @version:   V1.0.0/2024-01-08
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_trng.h"


/** @defgroup TRNG  TRNG
  * @brief TRNG driver modules
  * @{
  */

/** @defgroup TRNG_Private_Defines  TRNG_Private_Defines
  * @{
  */
#define TRNG_TIMEOUT_VALUE     ((uint32_t) 0x00010000)

#define TRNG_CR_CLEAR_MASK     ((uint32_t)0xFFFF01EF)
/**
  * @}
  */

/** @defgroup TRNG_Private_Functions    TRNG_Private_Functions
  * @{
  */

/** @defgroup TRNG_Group1  Initialize and enable the TRNG
 *  @brief    Initialize and enable the TRNG functions
  * @{
  */

/**
  * @brief  Initializes the TRNG peripheral and creates the associated handle.
  * @param  TRNG_InitStruct: pointer to a TRNG_InitTypeDef structure that contains
  *         the configuration information for TRNG.
  * @retval None
  */
void TRNG_Init(TRNG_InitTypeDef *TRNG_InitStruct)
{
    uint32_t tmpreg = 0;

    /* Get TRNG CR register value */
    tmpreg = TRNG->CR;

    /* Clear OP_CYCLE[15:9] bits and work mode MODE[0] */
    tmpreg &= (uint32_t)TRNG_CR_CLEAR_MASK;

    /* Set TRNG accumulation clock period and work mode */
    tmpreg |= ((TRNG_InitStruct->Option_Cycle << 9) | (TRNG_InitStruct->Mode << 4));

    TRNG->CR = (uint32_t)tmpreg;
}

/**
  * @brief  Deinitializes TRNG peripheral registers to their default reset values.
  * @retval None
  */
void TRNG_DeInit(void)
{
    /* Enable TRNG reset state */
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_TRNG, ENABLE);

    /* Release TRNG from reset state */
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_TRNG, DISABLE);
}



/**
  * @brief  Enable or disable the TRNG peripheral.
  * @param  NewState: new state of the TRNG peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TRNG_Cmd(FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the TRNG Peripheral */
        TRNG->CR |= (uint32_t)TRNG_CR_RNGEN;
    }
    else
    {
        /* Disable the TRNG peripheral */
        TRNG->CR &= (uint32_t)(~TRNG_CR_RNGEN);  /**< TRNG Disable */
    }
}
/**
  * @}
  */


/** @defgroup TRNG_Group2 Get random number
 *  @brief    Get random number functions
 *
 @verbatim
 ===============================================================================
                      ##### Get random number functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Get the 32 bit Random number
      (+) Get the 32 bit Random number with interrupt enabled

 @endverbatim
  * @{
  */

/**
  * @brief  Generates a 32-bit random number.
  * @note   Each time the random number data is read the TRNG_FLAG_DRDY flag
  *         is automatically cleared.
  * @param  random32bit pointer to generated random number variable if successful.
  * @retval Returns the state in which the random number was generated.
  */
ErrorStatus TRNG_GetRandomNumber(uint32_t *random32bit)
{
    uint32_t RandomNumber = 0;
    __IO uint32_t counter ;
    FlagStatus  ccstatus = RESET;
    ErrorStatus status = SUCCESS;

    /* Wait for DRDY flag to be set */
    counter = 0;

    do
    {
        ccstatus = TRNG_GetFlagStatus(TRNG_FLAG_DRDY);
        counter++;
    } while ((counter != TRNG_TIMEOUT_VALUE) && (ccstatus == RESET));

    if (ccstatus == RESET)
    {
        status = ERROR;
    }
    else
    {
        /* Get a 32bit Random number */
        RandomNumber = TRNG->DR;
        *random32bit = RandomNumber;
    }

    return status;
}

/**
  * @brief  Returns a 32-bit random number with interrupt enabled
  * @retval 32-bit random number
  */
uint32_t TRNG_GetRandomNumberIT(void)
{
    uint32_t random32bit = 0U;

    /* Get a 32bit Random number */
    random32bit = TRNG->DR;

    /* Enable the TRNG Interrupts: Data Ready, Seed error */
    TRNG_ITConfig(ENABLE);

    /* Return the 32 bit random number */
    return random32bit;
}
/**
  * @}
  */

/** @defgroup TRNG_Group3 Interrupts and flags management
 *  @brief    Interrupts and flags management functions
 @verbatim
 ===============================================================================
                      ##### Interrupts and flags management functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Enable the TRNG interrupts
      (+) Flags management functions
      (+) Interrupts flags management functions
      (+) Get the status and clear flags
    [..] The HASH provides 1 Interrupts sources and 2 Flags:
 *** Flags : ***
 ===============
        [..]
            (#) TRNG_FLAG_DRDY: set when the random number has ready.
            (#) TRNG_FLAG_SECS: Seed error current status.

@endverbatim
 * @{
 */

/**
  * @brief  Enables or disables the specified TRNG interrupt.
  * @param  NewState: The new state of the TRNG interrupt source.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TRNG_ITConfig( FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        TRNG->CR |= (uint32_t) TRNG_IT_IE;    /**< TRNG_IT Enable */
    }
    else
    {
        TRNG->CR &= (uint32_t)(~TRNG_IT_IE);  /**< TRNG_IT Disable */
    }
}

/**
  * @brief  Checks whether the specified TRNG flag is set or not.
  * @param  TRNG_FLAG specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg TRNG_FLAG_DRDY: Data ready
  *            @arg TRNG_FLAG_SECS: Seed error current status
  * @retval FlagStatus (SET or RESET)
  */
FlagStatus TRNG_GetFlagStatus(uint32_t TRNG_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check parameters */
    assert_param(IS_TRNG_FLAG(TRNG_FLAG));

    if ((TRNG->SR & TRNG_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the TRNG_FLAG status */
    return  bitstatus;
}


/**
  * @brief  Checks whether the specified TRNG interrupt has occurred or not.
  * @param  TRNG_IT: Specifies the TRNG interrupt pending bit to check.
  *         This parameter can be:
  *            @arg TRNG_IT_DRDY: Data ready interrupt
  *            @arg TRNG_IT_SEI: Seed error interrupt
  * @retval ITStatus The new state of TRNG_IT (SET or RESET).
  */
ITStatus TRNG_GetITStatus(uint32_t TRNG_IT)
{
    ITStatus itstatus = RESET;
    uint32_t cciebitstatus = RESET;

    /* Check parameters */
    assert_param(IS_TRNG_GET_IT(TRNG_IT));

    cciebitstatus = TRNG->CR & TRNG_CR_IE;

    if (cciebitstatus != (uint16_t)RESET)
    {
        /* Check the status of the specified TRNG interrupt */
        if ((TRNG->SR & TRNG_IT) != RESET)
        {
            /* Check if WRERR or RDERR flags are set */
            if ((TRNG->SR & (uint32_t)(TRNG_IT_DRDY | TRNG_IT_SEI)) != (uint16_t)RESET)
            {
                /* Interrupt occurred */
                itstatus = SET;
            }
            else
            {
                /* Interrupt didn't occur */
                itstatus = RESET;
            }
        }
        else
        {
            /* Interrupt didn't occur */
            itstatus = (ITStatus) RESET;

        }
    }

    /* Return the TRNG_IT status */
    return itstatus;

}

/**
  * @brief  Clears the TRNG's interrupt pending bits.
  * @param  TRNG_IT: specifies the interrupt pending bit to clear.
  *         This parameter can be any combinations of the following values:
  *            @arg TRNG_IT_SEI: Seed error interrupt
  * @retval None
  */
void TRNG_ClearITPendingBit(uint32_t TRNG_IT)
{
    /* Check the parameters */
    assert_param(IS_TRNG_IT(TRNG_IT));

    /* Clear the interrupt pending bit */
    TRNG->SR &= (uint32_t) (~TRNG_IT);
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

