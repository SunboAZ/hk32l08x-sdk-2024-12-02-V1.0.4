/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_beep.c
* @brief:     This file provides firmware functions to manage the beeper peripherals
* @author:    AE Team
* @version:   V1.0.0/2024-01-08
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_beep.h"
#include "hk32l0xx.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup BEEPER  BEEPER
  * @brief BEEPER driver modules
  * @{
  */

/** @defgroup BEEPER_Private_Functions BEEPER_Private_Functions
  * @{
  */

/**
  * @brief  Initialize the beeper peripheral register to the default
  *         value reset value
  * @retval None
  */
void BEEPER_DeInit(void)
{
    /*BEEPER clock:LSI,BEEPER_Prescaler:64,BEEPER_TRGO_Prescaler:64*/
    BEEPER->CFGR = BEEPER_CFGR_Value;

    /*BEEPER:ENABLE,TRGO:ENABLE*/
    while (BEEPER->CR & BEEPER_BUSY_FLAG)
    {
    }

    BEEPER->CR |= BEEPER_CR_Value;
}

/**
  * @brief  Initialize the BEEPER peripheral register
  * @param  BEEPER_InitStruct: pointer to a BEEPER_InitTypeDef structure which will be initialized.
  * @retval None
  */
void BEEPER_Init(BEEPER_InitTypeDef *BEEPER_InitStruct)
{
    assert_param(IS_BEEPER_CLOCK(BEEPER_InitStruct->BEEPER_Clock));
    assert_param(IS_BEEPER_PRESCALER(BEEPER_InitStruct->BEEPER_Prescaler));


    uint32_t temp = 0;

    /*Set the BEEPER clock*/
    if (BEEPER_InitStruct->BEEPER_Clock == BEEPER_CLOCK_LSI)
    {
        BEEPER->CFGR &= ~(BEEPER_CFGR_BEEP_CKSEL);
    }
    else
    {
        BEEPER->CFGR |= BEEPER_CFGR_BEEP_CKSEL;
        RCC->CFGR4 &= ~RCC_CFGR4_BEEPER_SW;
        RCC->CFGR4 |= ((BEEPER_InitStruct->BEEPER_Clock & ~0x10) << RCC_CFGR4_BEEPER_SW_Pos);
    }


    /*Clear [2:1]bits*/
    temp = BEEPER->CFGR;

    temp &= BEEPER_CFGR_BEEPER_Mask;
    /*Set the frequency division coefficient*/
    temp |= BEEPER_InitStruct->BEEPER_Prescaler;
    /*To transfer a value into a register*/
    BEEPER->CFGR = temp;
}

/**
  * @brief  Enables or disables the specified BEEPER peripheral.
  * @param  NewState: new state of the BEEPER peripheral.
  * @retval None
  */
void BEEPER_Cmd(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /*Enable BEEPER*/
        while (BEEPER->CR & BEEPER_BUSY_FLAG)
        {
        }

        BEEPER->CR |= BEEPER_CR_BEEPER_EN;
    }
    else
    {
        /*Disable BEEPER*/
        while (BEEPER->CR & BEEPER_BUSY_FLAG)
        {
        }

        BEEPER->CR &= (uint32_t)~((uint32_t)BEEPER_CR_BEEPER_EN);
    }
}


/**
  * @brief  Select the BEEPER clock.
  * @param  BEEPER_CLOCK: Clock source selection.
  *         This parameter can be one of the following values:
  *            @arg BEEPER_CLOCK_HSE
  *            @arg BEEPER_CLOCK_LSI
  * @retval None
  */
void BEEPER_ClockSelect(uint8_t BEEPER_CLOCK)
{
    assert_param(IS_BEEPER_CLOCK(BEEPER_CLOCK));

    if (BEEPER_CLOCK_HSE == BEEPER_CLOCK)
    {
        /*Set HSE as the clock source*/
        BEEPER->CFGR |= BEEPER_CLOCK_HSE;
    }
    else
    {
        /*Set LSI as the clock source*/
        BEEPER->CFGR &= ~(BEEPER_CLOCK_HSE);
    }
}


/**
  * @brief  Set the BEEPER frequency division coefficient.
  * @param  BEEPER_Prescaler: frequency division coefficient selection.
  *         This parameter can be one of the following values:
  *            @arg BEEPER_Prescaler_16
  *            @arg BEEPER_Prescaler_32
  *            @arg BEEPER_Prescaler_64
  *            @arg BEEPER_Prescaler_128
  * @retval None
  */
void BEEPER_SetPrescaler(uint8_t BEEPER_Prescaler)
{
    uint32_t temp = 0;
    assert_param(IS_BEEPER_PRESCALER(BEEPER_Prescaler));

    /*Clear [2:1]bits*/
    temp = BEEPER->CFGR;
    temp &= BEEPER_CFGR_BEEPER_Mask;
    /*Set the frequency division coefficient*/
    temp |= BEEPER_Prescaler;
    /*To transfer a value into a register*/
    BEEPER->CFGR = temp;
}



/**
  * @brief  Read BEEPER register status.
  * @retval register status
  */
FlagStatus BEEPER_ReadBeepStatus(void)
{
    if ((BEEPER->CR & (BEEPER_BUSY_FLAG)) == BEEPER_BUSY_FLAG)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
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
