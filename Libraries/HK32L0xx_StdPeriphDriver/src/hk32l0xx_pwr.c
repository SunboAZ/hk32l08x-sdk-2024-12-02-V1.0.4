/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_pwr.c
* @brief:     API file of PWR module
* @author:    AE Team
* @version:   V1.0.0/2024-01-08
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_pwr.h"
#include "hk32l0xx_rcc.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup PWR PWR
  * @brief PWR driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup PWR_Private_Defines PWR_Private_Defines
  * @{
  */
/* CR register bit mask */
#define CR_DS_MASK               ((uint32_t)0xFFFFFFFC)
#define CR_PLS_MASK              ((uint32_t)0xFFFFFF1F)

#define PWR_FLAG_SETTING_DELAY_US   50U
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PWR_Private_Functions PWR_Private_Functions
  * @{
  */

/******************************************************************************
  ==============================================================================
                   ##### Backup Domain Access function #####
  ==============================================================================

    [..] After reset, the Backup Domain Registers (RCC BDCR Register, RTC registers
         and RTC backup registers) are protected against possible stray write accesses.
    [..] To enable access to Backup domain use the PWR_BackupAccessCmd(ENABLE) function.

*******************************************************************************/

/**
  * @brief  Deinitializes the PWR peripheral registers to their default reset values.
  * @retval None
  */
void PWR_DeInit(void)
{
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, DISABLE);
}

/**
  * @brief  Enables or disables access to the Backup domain registers.
  * @note   If the HSE divided by 32 is used as the RTC clock, the
  *         Backup Domain Access should be kept enabled.
  * @param  NewState: new state of the access to the Backup domain registers.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_BackupAccessCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Backup Domain Access */
        PWR->CR |= PWR_CR_DBP;
    }
    else
    {
        /* Disable the Backup Domain Access */
        PWR->CR &= (uint32_t)~((uint32_t)PWR_CR_DBP);
    }
}


/*******************************************************************************

  ==============================================================================
                    ##### PVD configuration functions #####
  ==============================================================================
  [..]
  (+) The PVD is used to monitor the VDD power supply by comparing it to a threshold
      selected by the PVD Level (PLS[2:0] bits in the PWR_CR).
  (+) A PVDO flag is available to indicate if VDD/VDDA is higher or lower than the
      PVD threshold. This event is internally connected to the EXTI line16
      and can generate an interrupt if enabled through the EXTI registers.
  (+) The PVD is stopped in Standby mode.

********************************************************************************/

/**
  * @brief  Configures the voltage threshold detected by the Power Voltage Detector(PVD).
  * @param  PWR_PVDLevel: specifies the PVD detection level
  *         This parameter can be one of the following values:
  *            @arg PWR_PVDLevel_0
  *            @arg PWR_PVDLevel_1
  *            @arg PWR_PVDLevel_2
  *            @arg PWR_PVDLevel_3
  *            @arg PWR_PVDLevel_4
  *            @arg PWR_PVDLevel_5
  *            @arg PWR_PVDLevel_6
  *            @arg PWR_PVDLevel_7
  * @param  PWR_PVDMode:
  *            @arg PVD_MODE_IT
  *            @arg PVD_MODE_EVT
  * @param  PWR_PVDEdge:
  *            @arg PVD_RISING_EDGE
  *            @arg PVD_FALLING_EDGE
  *            @arg PVD_RISING_FALLING
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each
  *         detection level.
  * @retval None
  */
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel, uint32_t PWR_PVDMode, uint32_t PWR_PVDEdge)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));

    EXTI->EMR &= (uint32_t)~((uint32_t)EXTI_EMR_EM16);
    EXTI->IMR &= (uint32_t)~((uint32_t)EXTI_IMR_IM16);

    EXTI->FTSR &= (uint32_t)~((uint32_t)EXTI_FTSR_FT16);
    EXTI->RTSR &= (uint32_t)~((uint32_t)EXTI_RTSR_RT16);

    tmpreg = PWR->CR;
    /* Clear PLS[7:5] bits */
    tmpreg &= CR_PLS_MASK;

    /* Set PLS[7:5] bits according to PWR_PVDLevel value */
    tmpreg |= PWR_PVDLevel;

    /* Store the new value */
    PWR->CR = tmpreg;

    /* Configure interrupt mode */
    if ((PWR_PVDMode & PVD_MODE_IT) == PVD_MODE_IT)
    {
        EXTI->IMR |= EXTI_IMR_IM16;
    }

    /* Configure event mode */
    if ((PWR_PVDMode & PVD_MODE_EVT) == PVD_MODE_EVT)
    {
        EXTI->EMR |= EXTI_EMR_EM16;
    }

    /* Configure the edge */
    if ((PWR_PVDEdge & PVD_RISING_EDGE) == PVD_RISING_EDGE)
    {
        EXTI->RTSR |= EXTI_RTSR_RT16;
    }

    if ((PWR_PVDEdge & PVD_FALLING_EDGE) == PVD_FALLING_EDGE)
    {
        EXTI->FTSR |= EXTI_FTSR_FT16;
    }
}

/**
  * @brief  Enables or disables the Power Voltage Detector(PVD).
  * @note   This function is not applicable for HK32L0xx devices.
  * @param  NewState: new state of the PVD.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_PVDCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the PVD */
        PWR->CR |= PWR_CR_PVDE;
    }
    else
    {
        /* Disable the PVD */
        PWR->CR &= (uint32_t)~((uint32_t)PWR_CR_PVDE);
    }
}

/*******************************************************************************

  ==============================================================================
               ##### WakeUp pin configuration functions #####
  ==============================================================================

  (+) WakeUp pins are used to wakeup the system from Standby mode. These pins are
      forced in input pull down configuration and are active on rising edges.
  (+) There are eight WakeUp pins: WakeUp Pin 1 on PA.00 and WakeUp Pin 2 on PC.13.

*******************************************************************************/

/**
  * @brief  Enables or disables the WakeUp Pin functionality.
  * @param  PWR_WakeUpPin: specifies the WakeUpPin.
  *         This parameter can be one of the following values
  *            @arg PWR_WakeUpPin_1
  *            @arg PWR_WakeUpPin_2
  * @param  NewState: new state of the WakeUp Pin functionality.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_PWR_WAKEUP_PIN(PWR_WakeUpPin));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the EWUPx pin */
        PWR->CSR |= PWR_WakeUpPin;
    }
    else
    {
        /* Disable the EWUPx pin */
        PWR->CSR &= ~PWR_WakeUpPin;
    }
}


/*******************************************************************************

  ==============================================================================
              ##### Low Power modes configuration functions #####
  ==============================================================================

    [..] The devices feature three low-power modes:
    (+) Sleep mode: Cortex-M0 core stopped, peripherals kept running.
    (+) Stop mode: all clocks are stopped, regulator running, regulator in low power mode
    (+) Standby mode: VCORE domain powered off

  *** Sleep mode ***
  ==================
  [..]
    (+) Entry:
        (++) The Sleep mode is entered by executing the WFE() or WFI() instructions.
    (+) Exit:
        (++) Any peripheral interrupt acknowledged by the nested vectored interrupt
             controller (NVIC) can wake up the device from Sleep mode.

  *** Stop mode ***
  =================
  [..] In Stop mode, all clocks in the VCORE domain are stopped, the PLL, the HSI,
       the HSI14 and the HSE RC oscillators are disabled. Internal SRAM and register
       contents are preserved.
       The voltage regulator can be configured either in normal or low-power mode.

    (+) Entry:
        (++) The Stop mode is entered using the PWR_EnterSTOPMode(PWR_Regulator_LowPower,)
             function with regulator in LowPower or with Regulator ON.
    (+) Exit:
        (++) Any EXTI Line (Internal or External) configured in Interrupt/Event mode
             or any internal IPs (I2C, UASRT or CEC) wakeup event.

  *** Standby mode ***
  ====================
  [..] The Standby mode allows to achieve the lowest power consumption. It is based
       on the Cortex-M0 deepsleep mode, with the voltage regulator disabled.
       The VCORE domain is consequently powered off. The PLL, the HSI, the HSI14
       oscillator and the HSE oscillator are also switched off. SRAM and register
       contents are lost except for the Backup domain (RTC registers, RTC backup
       registers and Standby circuitry).

  [..] The voltage regulator is OFF.

    (+) Entry:
        (++) The Standby mode is entered using the PWR_EnterSTANDBYMode() function.
    (+) Exit:
        (++) WKUP pin rising edge, RTC alarm (Alarm A and Alarm B), RTC wakeup,
             tamper event, time-stamp event, external reset in NRST pin, IWDG reset.

  *** Auto-wakeup (AWU) from low-power mode ***
  =============================================
  [..] The MCU can be woken up from low-power mode by an RTC Alarm event, a tamper
       event, a time-stamp event, or a comparator event, without depending on an
       external interrupt (Auto-wakeup mode).

    (+) RTC auto-wakeup (AWU) from the Stop mode
        (++) To wake up from the Stop mode with an RTC alarm event, it is necessary to:
             (+++) Configure the EXTI Line 17 to be sensitive to rising edges (Interrupt
                   or Event modes) using the EXTI_Init() function.
             (+++) Enable the RTC Alarm Interrupt using the RTC_ITConfig() function
             (+++) Configure the RTC to generate the RTC alarm using the RTC_SetAlarm()
                   and RTC_AlarmCmd() functions.
        (++) To wake up from the Stop mode with an RTC Tamper or time stamp event, it
             is necessary to:
             (+++) Configure the EXTI Line 19 to be sensitive to rising edges (Interrupt
                   or Event modes) using the EXTI_Init() function.
             (+++) Enable the RTC Tamper or time stamp Interrupt using the RTC_ITConfig()
                   function.
             (+++) Configure the RTC to detect the tamper or time stamp event using the
                   RTC_TimeStampConfig(), RTC_TamperTriggerConfig() and RTC_TamperCmd()
                   functions.

    (+) RTC auto-wakeup (AWU) from the Standby mode
        (++) To wake up from the Standby mode with an RTC alarm event, it is necessary to:
             (+++) Enable the RTC Alarm Interrupt using the RTC_ITConfig() function.
             (+++) Configure the RTC to generate the RTC alarm using the RTC_SetAlarm()
                   and RTC_AlarmCmd() functions.
        (++) To wake up from the Standby mode with an RTC Tamper or time stamp event, it
             is necessary to:
             (+++) Enable the RTC Tamper or time stamp Interrupt using the RTC_ITConfig()
                   function.
             (+++) Configure the RTC to detect the tamper or time stamp event using the
                   RTC_TimeStampConfig(), RTC_TamperTriggerConfig() and RTC_TamperCmd()
                   functions.

    (+) Comparator auto-wakeup (AWU) from the Stop mode
        (++) To wake up from the Stop mode with an comparator 1 or comparator 2 wakeup
             event, it is necessary to:
             (+++) Configure the EXTI Line 21 for comparator 1 or EXTI Line 22 for comparator 2
                   to be sensitive to to the selected edges (falling, rising or falling
                   and rising) (Interrupt or Event modes) using the EXTI_Init() function.
             (+++) Configure the comparator to generate the event.

*************************************************************************************/

/**
  * @brief  Enters Sleep mode.
  * @note   In Sleep mode, all I/O pins keep the same state as in Run mode.
  * @param  PWR_Regulator: Specifies the regulator state in SLEEP mode.
  *         This parameter can be one of the following values:
  *            @arg PWR_Regulator_ON: SLEEP mode with regulator ON
  *            @arg PWR_Regulator_LowPower: SLEEP mode with low power regulator ON
  * @param  PWR_SLEEPEntry: specifies if SLEEP mode in entered with WFI or WFE instruction.
  *         This parameter can be one of the following values:
  *            @arg PWR_SLEEPEntry_WFI: enter SLEEP mode with WFI instruction
  *            @arg PWR_SLEEPEntry_WFE: enter SLEEP mode with WFE instruction
  *            @arg PWR_SLEEPEntry_SLEEPONEXIT: enter SLEEP mode with SLEEPONEXIT instruction
  * @retval None
  */
void PWR_EnterSleepMode(uint32_t PWR_Regulator, uint8_t PWR_SLEEPEntry)
{
    uint32_t tmpreg = 0U;
    /* Check the parameters */
    assert_param(IS_PWR_REGULATOR(PWR_Regulator));
    assert_param(IS_PWR_SLEEP_ENTRY(PWR_SLEEPEntry));

    /* Select the regulator state in Sleep mode ---------------------------------*/
    tmpreg = PWR->CR;
    /* Clear PDDS and LPSDSR bits */
    tmpreg &= CR_DS_MASK;
    /* Set LPSDSR bit according to PWR_Regulator value */
    tmpreg |= PWR_Regulator;

    /* Store the new value */
    PWR->CR = tmpreg;

    /* Clear SLEEPDEEP bit of Cortex-M0 System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

    /* Select SLEEP mode entry -------------------------------------------------*/
    if (PWR_SLEEPEntry == PWR_SLEEPEntry_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else if (PWR_SLEEPEntry == PWR_SLEEPEntry_WFE)
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }
    else
    {
        /* Set SLEEP on exit bit of Cortex-M0 System Control Register */
        SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    }

    __NOP();
}

/**
  * @brief  Enters Lower Power Sleep mode.
  * @note   In Sleep mode, all I/O pins keep the same state as in Run mode.
  * @param  PWR_SLEEPEntry: specifies if SLEEP mode in entered with WFI or WFE instruction.
  *         This parameter can be one of the following values:
  *            @arg PWR_SLEEPEntry_WFI: enter Low Power SLEEP mode with WFI instruction
  *            @arg PWR_SLEEPEntry_WFE: enter Low Power SLEEP mode with WFE instruction
  *            @arg PWR_SLEEPEntry_SLEEPONEXIT: enter Low Power mode with SLEEPONEXIT instruction
  * @retval None
  */
void PWR_EnterLowPowerSleepMode(uint8_t PWR_SLEEPEntry)
{
    uint32_t tmpreg = 0U;
    /* Check the parameters */
    assert_param(IS_PWR_SLEEP_ENTRY(PWR_SLEEPEntry));

    /* Select the regulator state in Sleep mode ---------------------------------*/
    tmpreg = PWR->CR;
    /* Clear PDDS and LPSDSR bits */
    tmpreg &= CR_DS_MASK;
    /* Set LPSDSR  & LPRUN bit */
    tmpreg |= PWR_CR_LPSDSR;
    tmpreg |= PWR_CR_LPRUN;

    /* Store the new value */
    PWR->CR = tmpreg;

    /* Clear SLEEPDEEP bit of Cortex-M0 System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

    /* Select SLEEP mode entry -------------------------------------------------*/
    if (PWR_SLEEPEntry == PWR_SLEEPEntry_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else if (PWR_SLEEPEntry == PWR_SLEEPEntry_WFE)
    {
        /* Request Wait For Event */

        __SEV();
        __WFE();
        __WFE();

    }
    else
    {
        /* Set SLEEP on exit bit of Cortex-M0 System Control Register */
        SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    }

    __NOP();
}



/**
  * @brief  Enters STOP mode.
  * @note   In Stop mode, all I/O pins keep the same state as in Run mode.
  * @note   When exiting Stop mode by issuing an interrupt or a wakeup event,
  *         the HSI RC oscillator is selected as system clock.
  * @note   When the voltage regulator operates in low power mode, an additional
  *         startup delay is incurred when waking up from Stop mode.
  *         By keeping the internal regulator ON during Stop mode, the consumption
  *         is higher although the startup time is reduced.
  * @param  PWR_Regulator: specifies the regulator state in STOP mode.
  *         This parameter can be one of the following values:
  *            @arg PWR_Regulator_ON: STOP mode with regulator ON
  *            @arg PWR_Regulator_LowPower: STOP mode with regulator in low power mode
  * @param  PWR_STOPEntry: specifies if STOP mode in entered with WFI or WFE instruction.
  *         This parameter can be one of the following values:
  *            @arg PWR_STOPEntry_WFI: enter STOP mode with WFI instruction
  *            @arg PWR_STOPEntry_WFE: enter STOP mode with WFE instruction
  *            @arg PWR_STOPEntry_SLEEPONEXIT: enter STOP mode with SLEEPONEXIT instruction
  * @retval None
  */
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_PWR_REGULATOR(PWR_Regulator));
    assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));

    /* Select the regulator state in STOP mode ---------------------------------*/
    tmpreg = PWR->CR;
    /* Clear PDDS and LPDSR bits */
    tmpreg &= CR_DS_MASK;

    /* Set LPDSR bit according to PWR_Regulator value */
    tmpreg |= PWR_Regulator;

    /* Store the new value */
    PWR->CR = tmpreg;

    /* Set SLEEPDEEP bit of Cortex-M0 System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Select STOP mode entry --------------------------------------------------*/
    if (PWR_STOPEntry == PWR_STOPEntry_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
        /* Reset SLEEPDEEP bit of Cortex System Control Register */
        SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
    }
    else if (PWR_STOPEntry == PWR_STOPEntry_WFE)
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
        /* Reset SLEEPDEEP bit of Cortex System Control Register */
        SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
    }
    else
    {
        /* Set SLEEP on exit bit of Cortex-M0 System Control Register */
        SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    }
}

/**
  * @brief  Enters STANDBY mode.
  * @note   In Standby mode, all I/O pins are high impedance except for:
  *         - Reset pad (still available)
  *         - RTC_AF1 pin (PC13) if configured for Wakeup pin 2 (WKUP2), tamper,
  *         time-stamp, RTC Alarm out, or RTC clock calibration out.
  *         - WKUP pin 1 (PA0) if enabled.
  * @note   The Wakeup flag (WUF) need to be cleared at application level before to call this function
  * @param  PWR_StandbyEntry: specifies if STOP mode in entered with WFI or WFE instruction.
  *         This parameter can be one of the following values:
  *            @arg PWR_STANDBYEntry_WFI: enter STOP mode with WFI instruction
  *            @arg PWR_STANDBYEntry_WFE: enter STOP mode with WFE instruction
  *            @arg PWR_STANDBYEntry_SLEEPONEXIT: enter STOP mode with SLEEPONEXIT instruction
  * @retval None
  */
void PWR_EnterSTANDBYMode(uint8_t PWR_StandbyEntry)
{
    /* Select STANDBY mode */
    PWR->CR |= PWR_CR_PDDS;

    /* Set SLEEPDEEP bit of Cortex-M0 System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Select STOP mode entry --------------------------------------------------*/
    if (PWR_StandbyEntry == PWR_STANDBYEntry_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else if (PWR_StandbyEntry == PWR_STANDBYEntry_WFE)
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }
    else
    {
        /* Set SLEEP on exit bit of Cortex-M0 System Control Register */
        SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    }
}


/**
  * @brief  Indicates Sleep-On-Exit when returning from Handler mode to Thread mode.
  * @note   Set SLEEPONEXIT bit of SCR register. When this bit is set, the processor
  *         re-enters SLEEP mode when an interruption handling is over.
  *         Setting this bit is useful when the processor is expected to run only on
  *         interruptions handling.
  * @retval None
  */
void PWR_EnableSleepOnExit(void)
{
    /* Set SLEEPONEXIT bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
}


/**
  * @brief  Disables Sleep-On-Exit feature when returning from Handler mode to Thread mode.
  * @note   Clears SLEEPONEXIT bit of SCR register. When this bit is set, the processor
  *         re-enters SLEEP mode when an interruption handling is over.
  * @retval None
  */
void PWR_DisableSleepOnExit(void)
{
    /* Clear SLEEPONEXIT bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPONEXIT_Msk);
}


/**
  * @brief  Enables CORTEX M0+ SEVONPEND bit.
  * @note   Sets SEVONPEND bit of SCR register. When this bit is set, this causes
  *         WFE to wake up when an interrupt moves from inactive to pended.
  * @retval None
  */
void PWR_EnableSEVOnPend(void)
{
    /* Set SEVONPEND bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SEVONPEND_Msk;
}


/**
  * @brief  Disables CORTEX M0+ SEVONPEND bit.
  * @note   Clears SEVONPEND bit of SCR register. When this bit is set, this causes
  *         WFE to wake up when an interrupt moves from inactive to pended.
  * @retval None
  */
void PWR_DisableSEVOnPend(void)
{
    /* Clear SEVONPEND bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SEVONPEND_Msk);
}

#if defined(PWR_PVD_SUPPORT)
/**
  * @brief  This function handles the PWR PVD interrupt request.
  * @note   This API should be called under the PVD_IRQHandler().
  * @retval None
  */
void PWR_PVDIRQHandler(void)
{
    /* Check PWR exti flag */
    if ((EXTI->PR & (EXTI_FTSR_TR16)) != RESET)
    {
        /* PWR PVD interrupt user callback */
        PWR_PVDCallback();

        /* Clear PWR Exti pending bit */
        EXTI->PR = EXTI_FTSR_TR16;
    }
}

/**
  * @brief  PWR PVD interrupt callback
  * @retval None
  */
__weak void PWR_PVDCallback(void)
{
    /* NOTE : This function Should not be modified, when the callback is needed,
              the PWR_PVDCallback could be implemented in the user file
     */
}
#endif /* PWR_MODULE_ENABLED */


/******************************************************************************

  ==============================================================================
                       ##### Flags management functions #####
  ==============================================================================

*******************************************************************************/

/**
  * @brief  Checks whether the specified PWR flag is set or not.
  * @param  PWR_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg PWR_FLAG_WU: Wake Up flag. This flag indicates that a wakeup
  *                 event was received from the WKUP pin or from the RTC alarm
  *                 (Alarm A or Alarm B), RTC Tamper event or RTC TimeStamp event.
  *            @arg PWR_FLAG_SB: StandBy flag. This flag indicates that the
  *                 system was resumed from StandBy mode.
  *            @arg PWR_FLAG_PVDO: PVD Output. This flag is valid only if PVD
  *                 is enabled by the PWR_PVDCmd() function.
  *            @arg PWR_FLAG_VREFINTRDY: Internal Voltage Reference Ready flag.
  *                 This flag indicates the state of the internal voltage
  *                 reference, VREFINT.
  * @retval The new state of PWR_FLAG (SET or RESET).
  */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_PWR_GET_FLAG(PWR_FLAG));

    if ((PWR->CSR & PWR_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the flag status */
    return bitstatus;
}

/**
  * @brief  Clears the PWR's pending flags.
  * @param  PWR_FLAG: specifies the flag to clear.
  *         This parameter can be one of the following values:
  *            @arg PWR_FLAG_WU: Wake Up flag
  *            @arg PWR_FLAG_SB: StandBy flag
  * @retval None
  */
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
    /* Check the parameters */
    assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));

    PWR->CR |=  PWR_FLAG << 2;
}
/*******************************************************************************

 ===============================================================================
                 ##### Peripheral extended features functions #####
 ===============================================================================

*******************************************************************************/

/**
  * @brief  Return Voltage Scaling Range.
  * @retval VOS bit field (PWR_REGULATOR_VOLTAGE_SCALE1, PWR_REGULATOR_VOLTAGE_SCALE2 or PWR_REGULATOR_VOLTAGE_SCALE3)
  */
uint32_t PWR_GetVoltageRange(void)
{
    return  (PWR->CR & PWR_CR_VOS_Mask);
}

/**
  * @brief  Set the main internal regulator output voltage
  * @param  VoltageScaling: This parameter can be one of the following values:
  *            @arg @ref PWR_REGULATOR_VOLTAGE_SCALE1
  *            @arg @ref PWR_REGULATOR_VOLTAGE_SCALE2
  *            @arg @ref PWR_REGULATOR_VOLTAGE_SCALE3
  * @retval None
  */
void PWR_SetVoltageRange(uint32_t VoltageScaling)
{
    assert_param(IS_PWR_VOLTAGE_SCALING_RANGE(VoltageScaling));

    PWR->CR &= (uint32_t)~((uint32_t)PWR_CR_VOS);
    PWR->CR |= VoltageScaling;
}

/**
  * @brief  Enables the Fast WakeUp from Ultra Low Power mode.
  * @note   This bit works in conjunction with ULP bit.
  *         Means, when ULP = 1 and FWU = 1 :VREFINT startup time is ignored when
  *         exiting from low power mode.
  * @retval None
  */
void PWR_EnableFastWakeUp(void)
{
    /* Enable the fast wake up */
    PWR->CR |= PWR_CR_FWU;
}
/**
  * @brief  Disables the Fast WakeUp from Ultra Low Power mode.
  * @retval None
  */
void PWR_DisableFastWakeUp(void)
{
    /* Disable the fast wake up */
    PWR->CR &= (uint32_t)~((uint32_t)PWR_CR_FWU);
}

/**
  * @brief  Enables the Ultra Low Power mode
  * @retval None
  */
void PWR_EnableUltraLowPower(void)
{
    /* Enable the Ultra Low Power mode */
    PWR->CR |= PWR_CR_ULP;
}
/**
  * @brief  Disables the Ultra Low Power mode
  * @retval None
  */
void PWR_DisableUltraLowPower(void)
{
    /* Disable the Ultra Low Power mode */
    PWR->CR &= (uint32_t)~((uint32_t)PWR_CR_ULP);
}
/**
  * @brief  Enable the Low Power Run mode.
  * @note   Low power run mode can only be entered when VCORE is in range 2.
  *         In addition, the dynamic voltage scaling must not be used when Low
  *         power run mode is selected. Only Stop and Sleep modes with regulator
  *         configured in Low power mode is allowed when Low power run mode is
  *         selected.
  * @note   The frequency of the system clock must be decreased to not exceed the
  *         frequency of RCC_MSIRANGE_1.
  * @note   In Low power run mode, all I/O pins keep the same state as in Run mode.
  * @retval None
  */
void PWR_EnableLowPowerRunMode(void)
{
    /* Enters the Low Power Run mode */
    PWR->CR |= PWR_CR_LPSDSR;
    PWR->CR |= PWR_CR_LPRUN;
}

/**
  * @brief  Disable the Low Power Run mode.
  * @note   Before PWREx_DisableLowPowerRunMode() completion, the function checks that
  *         REGLPF has been properly reset (otherwise, PWREx_DisableLowPowerRunMode
  *         returns TIMEOUT status). The system clock frequency can then be
  *         increased above 2 MHz.
  * @retval StatusTypeDef
  */
PWR_StatusTypeDef PWR_DisableLowPowerRunMode(void)
{
    uint32_t wait_loop_index = 0U;

    /* Exit the Low Power Run mode */
    PWR->CR &= (uint32_t)~((uint32_t)PWR_CR_LPRUN);
    PWR->CR &= (uint32_t)~((uint32_t)PWR_CR_LPSDSR);

    /* Wait until REGLPF is reset */
    wait_loop_index = (PWR_FLAG_SETTING_DELAY_US * (SystemCoreClock / 1000000U));

    while ((wait_loop_index != 0U) && ((PWR->CSR & PWR_CSR_REGLPF) == PWR_CSR_REGLPF))
    {
        wait_loop_index--;
    }

    if ((PWR->CSR & PWR_CSR_REGLPF) == PWR_CSR_REGLPF)
    {
        return PWR_TIMEOUT;
    }

    return PWR_OK;
}


/**
  * @brief  wakeup pin polarity config.
  * @note   the wakeup pin can set rising edge  wakeup or falling edge
  * @param  WakeUpPin:
  *            @arg WAKE_UP_PIN1
  *            @arg WAKE_UP_PIN2
  * @param  Edge:
  *            @arg FALLING_EDGE
  *            @arg RISING_EDGE
  * @retval None
  */
void PWR_WakeupPinPolarityConfig(uint32_t WakeUpPin, uint32_t Edge)
{
    /* Check the parameters */
    assert_param(IS_WAKEUPPIN_STATE(Edge));
    assert_param(IS_WAKEUP_PIN(WakeUpPin));

    if (WakeUpPin == WAKE_UP_PIN1)
    {
        /* clear WUPOL1 */
        PWR->WUP_POL &= (uint32_t)~((uint32_t)PWR_WUP_POL_WUPOL1);
        /* set WUPOL1*/
        PWR->WUP_POL |= (Edge << PWR_WUP_POL_WUPOL1_Pos);
    }
    else
    {
        /* clear WUPOL2 */
        PWR->WUP_POL &= (uint32_t)~((uint32_t)PWR_WUP_POL_WUPOL2);
        /* set WUPOL2*/
        PWR->WUP_POL |= (Edge << PWR_WUP_POL_WUPOL2_Pos);
    }
}

/**
  * @brief  pdr config in standby mode.
  * @note   the pdr can be powered down or open in stanby mode.
  * @param  NewState: new state of the pdr status in standby mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_PDRPDConfig(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* pdr is powered down in standby mode */
        PWR->PORPDR_CFG  = 0x0000;
        PWR->PORPDR_CFG  = 0x5500;
        PWR->PORPDR_CFG  = 0xAA00;
        PWR->PORPDR_CFG  = 0x5A00;
        PWR->PORPDR_CFG  = 0xA500;
        PWR->PORPDR_CFG  = 0xC800;
        PWR->PORPDR_CFG  = 0x8C00;
        PWR->PORPDR_CFG  = 0x6900;
        PWR->PORPDR_CFG  = 0x9600;
    }
    else
    {
        /* pdr is opened in standby mode */
        PWR->PORPDR_CFG  = 0x0000;
        PWR->PORPDR_CFG  = 0x5500;
        PWR->PORPDR_CFG  = 0xAA00;
        PWR->PORPDR_CFG  = 0x5A00;
        PWR->PORPDR_CFG  = 0xA500;
        PWR->PORPDR_CFG  = 0xC800;
        PWR->PORPDR_CFG  = 0x8C00;
        PWR->PORPDR_CFG  = 0x6900;
        PWR->PORPDR_CFG  = 0x9601;
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
