/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_dbgmcu.c
* @brief:     This file provides all the DBGMCU firmware functions.
* @author:    AE Team
* @version:   V1.0.0/2024-01-09
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_dbgmcu.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup DBGMCU DBGMCU
  * @brief DBGMCU driver modules
  * @{
  */

/** @defgroup DBGMCU_Private_Macro_Define DBGMCU_Private_Macro_Define
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define IDCODE_DEVID_MASK    ((uint32_t)0x00000FFF)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup DBGMCU_Private_Functions DBGMCU_Private_Functions
  * @{
  */

/** @defgroup DBGMCU_Group1 Device and Revision ID management functions
 *  @brief   Device and Revision ID management functions
 *
@verbatim
    ==============================================================================
              ##### Device and Revision ID management functions #####
    ==============================================================================
        (#) Returns the device revision identifier
        (#) Returns the device identifier
@endverbatim
  * @{
  */

/**
  * @brief  Returns the device revision identifier.
  * @retval Device revision identifier
  */
uint32_t DBGMCU_GetREVID(void)
{
    return (DBGMCU->IDCODE >> 16);
}

/**
  * @brief  Returns the device identifier.
  * @retval Device identifier
  */
uint32_t DBGMCU_GetDEVID(void)
{
    return (DBGMCU->IDCODE & IDCODE_DEVID_MASK);
}
/**
  * @}
  */

/** @defgroup DBGMCU_Group2 Peripherals Configuration functions
 *  @brief   Peripherals Configuration functions
 *
@verbatim
    ==============================================================================
                ##### Peripherals Configuration functions #####
    ==============================================================================
        (#) Configures low power mode behavior when the MCU is in Debug mode
        (#) Configures APB1 peripheral behavior when the MCU is in Debug mode
        (#) Configures APB2 peripheral behavior when the MCU is in Debug mode
@endverbatim
  * @{
  */

/**
  * @brief  Configures low power mode behavior when the MCU is in Debug mode.
  * @param  DBGMCU_Periph: specifies the low power mode.
  *         This parameter can be any combination of the following values:
  *            @arg DBGMCU_SLEEP: Keep debugger connection during SLEEP mode
  *            @arg DBGMCU_STOP: Keep debugger connection during STOP mode
  *            @arg DBGMCU_STANDBY: Keep debugger connection during STANDBY mode
  * @param  NewState: new state of the specified low power mode in Debug mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_DBGMCU_PERIPH(DBGMCU_Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        DBGMCU->CR |= DBGMCU_Periph;
    }
    else
    {
        DBGMCU->CR &= ~DBGMCU_Periph;
    }
}

/**
  * @brief  Configures APB1 peripheral behavior when the MCU is in Debug mode.
  * @param  DBGMCU_Periph: specifies the APB1 peripheral.
  *         This parameter can be any combination of the following values:
  *            @arg DBGMCU_TIM2_STOP         : TIM2 counter stopped when Core is halted
  *            @arg DBGMCU_TIM3_STOP         : TIM3 counter stopped when Core is halted
  *            @arg DBGMCU_TIM14_STOP        : TIM14 coun ter stopped when Core is halted
  *            @arg DBGMCU_RTC_STOP          : RTC Calendar and Wakeup counter stopped when Core is halted.
  *            @arg DBGMCU_WWDG_STOP         : Debug WWDG stopped when Core is halted
  *            @arg DBGMCU_IWDG_STOP         : Debug IWDG stopped when Core is halted
  *            @arg DBGMCU_I2C1_SMBUS_TIMEOUT: I2C1 SMBUS timeout mode stopped when Core is halted
  *            @arg DBGMCU_I2C2_SMBUS_TIMEOUT: I2C2 SMBUS timeout mode stopped when Core is halted
  *            @arg DBGMCU_CAN_STOP          : Debug CAN1 stopped when Core is halted
  * @param  NewState: new state of the specified APB1 peripheral in Debug mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_APB1PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_DBGMCU_APB1PERIPH(DBGMCU_Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        DBGMCU->APB1_FZ |= DBGMCU_Periph;
    }
    else
    {
        DBGMCU->APB1_FZ &= ~DBGMCU_Periph;
    }
}

/**
  * @brief  Configures APB2 peripheral behavior when the MCU is in Debug mode.
  * @param  DBGMCU_Periph: specifies the APB2 peripheral.
  *         This parameter can be any combination of the following values:
  *            @arg DBGMCU_TIM1_STOP : TIM1 counter stopped when Core is halted
  *            @arg DBGMCU_TIM15_STOP: TIM15 counter stopped when Core is halted
  *            @arg DBGMCU_TIM16_STOP: TIM16 counter stopped when Core is halted
  *            @arg DBGMCU_TIM17_STOP: TIM17 counter stopped when Core is halted
  * @param  NewState: new state of the specified APB2 peripheral in Debug mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_APB2PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_DBGMCU_APB2PERIPH(DBGMCU_Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        DBGMCU->APB2_FZ |= DBGMCU_Periph;
    }
    else
    {
        DBGMCU->APB2_FZ &= ~DBGMCU_Periph;
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

/**
  * @}
  */

/************************ (C) COPYRIGHT HKMicrochip *****END OF FILE****/
