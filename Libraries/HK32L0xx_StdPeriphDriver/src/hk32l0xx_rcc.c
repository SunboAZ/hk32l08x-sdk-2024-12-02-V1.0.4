/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_rcc.c
* @brief:     This file provides all the RCC firmware functions.
* @author:    AE Team
* @version:   V1.0.0/2024-01-09
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_rcc.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup RCC RCC
  * @brief: RCC driver modules
  * @{
  *
  @verbatim
  ===============================================================================
                        ##### RCC specific features #####
 ===============================================================================
  [..] After reset the device is running from HSI (8 MHz) with Flash 0 WS,
       all peripherals are off except internal SRAM, Flash and SWD.
         (#) There is no prescaler on High speed (AHB) and Low speed (APB) busses;
             all peripherals mapped on these busses are running at HSI speed.
         (#) The clock for all peripherals is switched off, except the SRAM and FLASH.
         (#) All GPIOs are in input floating state, except the SWD pins which
             are assigned to be used for debug purpose.
  [..] Once the device started from reset, the user application has to:
         (#) Configure the clock source to be used to drive the System clock
             (if the application needs higher frequency/performance)
         (#) Configure the System clock frequency and Flash settings
         (#) Configure the AHB and APB busses prescalers
         (#) Enable the clock for the peripheral(s) to be used
         (#) Configure the clock source(s) for peripherals which clocks are not
             derived from the System clock (ADC, I2C, USART, RTC and IWDG)
  @endverbatim
  *
  ******************************************************************************
  */

/** @defgroup RCC_Private_Macro_Define RCC_Private_Macro_Define
  * @brief   RCC Macro Define table
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* RCC Flag Mask */
#define FLAG_MASK                 ((uint8_t)0x1F)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint32_t LCDENReg = 0;
static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup RCC_Private_Functions RCC_Private_Functions
  * @{
  */

/** @defgroup RCC_Group1 Internal and external clocks, PLL, CSS and MCO configuration functions
 *  @brief    Internal and external clocks, PLL, CSS and MCO configuration functions
 *
@verbatim
    ===============================================================================
    ##### Internal-external clocks, PLL, CSS and MCO configuration functions #####
    ===============================================================================
    [..] This section provides functions allowing to configure the internal/external clocks,
         PLL, CSS and MCO.
         (#) HSI (high-speed internal), 8 MHz factory-trimmed RC used directly
             or through the PLL as System clock source.
             The HSI clock can be used also to clock the USART, I2C and CEC peripherals.
         (#) HSI16 (high-speed internal for ADC), 16 MHz factory-trimmed RC used to clock
             the ADC peripheral.
         (#) LSI (low-speed internal), 32 KHz low consumption RC used as IWDG and/or RTC
             clock source.
         (#) HSE (high-speed external), 4 to 32 MHz crystal oscillator used directly or
             through the PLL as System clock source. Can be used also as RTC clock source.
         (#) LSE (low-speed external), 32 KHz oscillator used as RTC clock source.
             LSE can be used also to clock the USART and CEC peripherals.
         (#) PLL (clocked by HSI or HSE), for System clock.
         (#) CSS (Clock security system), once enabled and if a HSE clock failure occurs
             (HSE used directly or through PLL as System clock source), the System clock
             is automatically switched to HSI and an interrupt is generated if enabled.
             The interrupt is linked to the Cortex-M0 NMI (Non-Maskable Interrupt)
             exception vector.
         (#) MCO (microcontroller clock output), used to output SYSCLK, HSI, HSI14, LSI,
             HSE, LSE or PLL (divided by 2) clock on PA8 pin.
@endverbatim
  * @{
  */

/**
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  * @note   HSI ON and used as system clock source
  * @note   HSI16, HSE and PLL OFF
  * @note   AHB, APB prescaler set to 0.
  * @note   CSS and MCO OFF
  * @note   All interrupts disabled
  * @note   However, this function doesn't modify the configuration of the Peripheral clocks ,LSI, LSE and RTC clocks
  * @retval None
  */
void RCC_DeInit(void)
{
    /* Set HSION bit */
    RCC->CR |= (uint32_t)0x00000001;

    /* Reset SW[1:0], SWS[1:0], HPRE[3:0], PPRE[2:0], STOPWUCK ,PLLSRC , PLLXTPRE , PLLMUL[3:0] , MCO[3:0] and  MCOPRE[2:0] bits */
    RCC->CFGR &= (uint32_t)0x80C0B80C;

    /* Reset HSEON, CSSON and PLLON bits */
    RCC->CR &= (uint32_t)0xFEF6FFFF;

    /* Reset PREDIV[3:0] bits */
    RCC->CFGR2 &= (uint32_t)0xFFFFFFF0;

    /* Reset USARTSW1[2:0], USART2SW[2:0] ,UART3SW[2:0], UART4SW[2:0] , USBSEL ,LPUART1SW[2:0]bits */
    RCC->CFGR3 &= (uint32_t)0xF0007000;

    /* Reset HSI16, HSI48 ,MSIRANGE[2:0] bit */
    RCC->CR2 &= (uint32_t)0xFFF8FFF6;

    /* Reset BEEPER_SW[1:0], I2C2CLK_SW[1:0] ,I2C1CLK_SW[1:0] bit */
    RCC->CFGR4 &= (uint32_t)0xFCF0FFFF;

    /*Reset MSION bit*/
    RCC->CSR &= (uint32_t)0xFFFFBFFF;

    /* Disable all interrupts */
    RCC->CIR &= 0x3F000000;
}

/**
  * @brief  Configures the External High Speed oscillator (HSE).
  * @note   After enabling the HSE (RCC_HSE_ON or RCC_HSE_Bypass), the application
  *         software should wait on HSERDY flag to be set indicating that HSE clock
  *         is stable and can be used to clock the PLL and/or system clock.
  * @note   HSE state can not be changed if it is used directly or through the
  *         PLL as system clock. In this case, you have to select another source
  *         of the system clock then change the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY modes.
  * @note   This function resets the CSSON bit, so if the Clock security system(CSS)
  *         was previously enabled you have to enable it again after calling this
  *         function.
  * @param  RCC_HSE: specifies the new state of the HSE.
  *            @arg RCC_HSE_OFF:    turn OFF the HSE oscillator, HSERDY flag goes low after
  *                 6 HSE oscillator clock cycles.
  *            @arg RCC_HSE_ON:     turn ON the HSE oscillator
  *            @arg RCC_HSE_Bypass: HSE oscillator bypassed with external clock
  * @retval None
  */
void RCC_HSEConfig(uint8_t RCC_HSE)
{
    /* Check the parameters */
    assert_param(IS_RCC_HSE(RCC_HSE));

    /* Reset HSEON and HSEBYP bits before configuring the HSE */
    RCC->CR &= ~RCC_CR_HSEON;
    RCC->CR &= ~RCC_CR_HSEBYP;

    /* Set the new HSE configuration */
    if (RCC_HSE == RCC_HSE_OFF)
    {
        RCC->CR &= ~RCC_CR_HSEON;
    }
    else if (RCC_HSE == RCC_HSE_ON)
    {
        RCC->CR |= RCC_CR_HSEON;
    }
    else
    {
        RCC->CR |= RCC_CR_HSEON | RCC_CR_HSEBYP;
    }

}

/**
  * @brief  Waits for HSE start-up.
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: HSE oscillator is stable and ready to use
  *         - ERROR: HSE oscillator not yet ready
  */
ErrorStatus RCC_WaitForHSEStartUp(void)
{
    __IO uint32_t StartUpCounter = 0;
    ErrorStatus status = ERROR;
    FlagStatus HSEStatus = RESET;

    /* Wait till HSE is ready and if timeout is reached exit */
    do
    {
        HSEStatus = RCC_GetFlagStatus(RCC_FLAG_HSERDY);
        StartUpCounter++;
    } while ((StartUpCounter != HSE_STARTUP_TIMEOUT) && (HSEStatus == RESET));

    if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }

    return (status);
}

/**
  * @brief  Fine adjusts the Internal High Speed oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  HSIFINETRIMValue: specifies the HSI fine trimming value.
  *         It is loaded automatically from flashoption when the MCU is power-on.
  *         This parameter must be a number between 0 and 0x3F.
  * @retval None
  */
void RCC_HSIFineTRIM(uint8_t HSIFINETRIMValue)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_HSI_FINETRIM_VALUE(HSIFINETRIMValue));

    tmpreg = RCC->CR;

    /* Clear HSIFTRIM[5:0] bits */
    tmpreg &= ~RCC_CR_HSIFTRIM;

    /* Set the HSIFTRIM[5:0] bits according to HSICalibrationValue value */
    tmpreg |= (uint32_t)HSIFINETRIMValue << 2;

    /* Store the new value */
    RCC->CR = tmpreg;
}

/**
  * @brief  Coarse adjusts the Internal High Speed oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  HSICOARSETRIMValue: specifies the HSI Coarse trimming value.
  *         It is loaded automatically from flashoption when the MCU is power-on.
  *         This parameter must be a number between 0 and 0x3F.
  * @retval None
  */
void RCC_HSICOARSETRIM(uint8_t HSICOARSETRIMValue)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_HSI_COARSETRIM_VALUE(HSICOARSETRIMValue));

    tmpreg = RCC->CR;

    /* Clear HSICTRIM[5:0] bits */
    tmpreg &= ~RCC_CR_HSICTRIM;

    /* Set the HSICTRIM[5:0] bits according to HSICalibrationValue value */
    tmpreg |= (uint32_t)HSICOARSETRIMValue << 8;

    /* Store the new value */
    RCC->CR = tmpreg;
}

/**
  * @brief  Coarse adjusts the Internal Low Speed oscillator (LSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal LSI RC.
  * @param  LSICOARSETRIMValue: specifies the LSI Coarse trimming value.
  *         It is loaded automatically from flashoption when the MCU is power-on.
  *         This parameter must be a number between 0 and 0x3F.
  * @retval None
  */
void RCC_LSICOARSETRIM(uint8_t LSICOARSETRIMValue)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_LSI_COARSETRIM_VALUE(LSICOARSETRIMValue));

    tmpreg = RCC->CSR;

    /* Clear LSICTRIM[5:0] bits */
    tmpreg &= ~RCC_CSR_LSICTRIM;

    /* Set the LSICTRIM[5:0] bits according to HSICalibrationValue value */
    tmpreg |= (uint32_t)LSICOARSETRIMValue << 6;

    /* Store the new value */
    RCC->CSR = tmpreg;
}

/**
  * @brief  Fine adjusts the Internal Low Speed oscillator (LSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal LSI RC.
  * @param  LSIFINETRIMValue: specifies the LSI Fine trimming value.
  *         It is loaded automatically from flashoption when the MCU is power-on.
  *         This parameter must be a number between 0 and 0x3F.
  * @retval None
  */
void RCC_LSIFINETRIM(uint8_t LSIFINETRIMValue)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_LSI_FINETRIM_VALUE(LSIFINETRIMValue));

    tmpreg = RCC->CSR;

    /* Clear LSIFTRIM[3:0] bits */
    tmpreg &= ~RCC_CSR_LSIFTRIM;

    /* Set the LSIFTRIM[3:0] bits according to LSICalibrationValue value */
    tmpreg |= (uint32_t)LSIFINETRIMValue << 2;

    /* Store the new value */
    RCC->CSR = tmpreg;
}
/**
  * @brief  Enables or disables the Internal High Speed oscillator (HSI).
  * @note   After enabling the HSI, the application software should wait on
  *         HSIRDY flag to be set indicating that HSI clock is stable and can
  *         be used to clock the PLL and/or system clock.
  * @note   HSI can not be stopped if it is used directly or through the PLL
  *         as system clock. In this case, you have to select another source
  *         of the system clock then stop the HSI.
  * @note   The HSI is stopped by hardware when entering STOP and STANDBY modes.
  * @param  NewState: new state of the HSI.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_HSICmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CR |= RCC_CR_HSION;
    }
    else
    {
        RCC->CR &= ~RCC_CR_HSION;
    }
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator  (HSI16).
  * @note   After enabling the HSI16, the application software should wait on
  *         HSIRDY flag to be set indicating that HSI clock is stable and can
  *         be used to clock the ADC.
  * @note   The HSI16 is stopped by hardware when entering STOP and STANDBY modes.
  * @param  NewState: new state of the HSI16.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When the HSI16 is stopped, HSI16RDY flag goes low after 6 HSI16 oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_HSI16Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CR2 |= RCC_CR2_HSI16ON;
    }
    else
    {
        RCC->CR2 &= ~RCC_CR2_HSI16ON;
    }
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator request from ADC.
  * @note   After enable the HSI16DIS , the HSI16 clock is enable and disable  with ADC enable
  *         and disable automatically.
  * @param  NewState: new state of the HSI16 ADC request.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_HSI16ADCRequestCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CR2 &= ~RCC_CR2_HSI16DIS;
    }
    else
    {
        RCC->CR2 |= RCC_CR2_HSI16DIS;
    }
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator for USB (HSI48).
  * @note   After enabling the HSI48, the application software should wait on
  *         HSI48RDY flag to be set indicating that HSI48 clock is stable and can
  *         be used to clock the USB.
  * @note   The HSI48 is stopped by hardware when entering STOP and STANDBY modes.
  * @param  NewState: new state of the HSI48.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_HSI48Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CR2 |= RCC_CR2_HSI48ON;
    }
    else
    {
        RCC->CR2 &= ~RCC_CR2_HSI48ON;
    }
}

/**
  * @brief  Configures the External Low Speed oscillator (LSE).
  * @note   As the LSE is in the Backup domain and write access is denied to this
  *         domain after reset, you have to enable write access using
  *         PWR_BackupAccessCmd(ENABLE) function before to configure the LSE
  *         (to be done once after reset).
  * @note   After enabling the LSE (RCC_LSE_ON or RCC_LSE_Bypass), the application
  *         software should wait on LSERDY flag to be set indicating that LSE clock
  *         is stable and can be used to clock the RTC.
  * @param  RCC_LSE: specifies the new state of the LSE.
  *         This parameter can be one of the following values:
  *            @arg RCC_LSE_OFF:    turn OFF the LSE oscillator, LSERDY flag goes low after
  *                 6 LSE oscillator clock cycles.
  *            @arg RCC_LSE_ON:     turn ON the LSE oscillator
  *            @arg RCC_LSE_Bypass: LSE oscillator bypassed with external clock
  * @retval None
  */
void RCC_LSEConfig(uint32_t RCC_LSE)
{
    /* Check the parameters */
    assert_param(IS_RCC_LSE(RCC_LSE));

    /* Reset LSEON and LSEBYP bits before configuring the LSE ------------------*/
    /* Reset LSEON bit*/
    RCC->BDCR &= ~(RCC_BDCR_LSEON );

    /* Reset LSEBYP bit */
    RCC->BDCR &= ~(RCC_BDCR_LSEBYP);

    /* Configure LSE */
    RCC->BDCR |= RCC_LSE;
}

/**
  * @brief  Configures the External Low Speed oscillator (LSE) drive capability.
  * @param  RCC_LSEDrive: specifies the new state of the LSE drive capability.
  *         This parameter can be one of the following values:
  *            @arg RCC_LSEDrive_Low: LSE oscillator low drive capability.
  *            @arg RCC_LSEDrive_MediumLow: LSE oscillator medium low drive capability.
  *            @arg RCC_LSEDrive_MediumHigh: LSE oscillator medium high drive capability.
  *            @arg RCC_LSEDrive_High: LSE oscillator high drive capability.
  * @retval None
  */
void RCC_LSEDriveConfig(uint32_t RCC_LSEDrive)
{
    /* Check the parameters */
    assert_param(IS_RCC_LSE_DRIVE(RCC_LSEDrive));

    /* Clear LSEDRV[1:0] bits */
    RCC->BDCR &= ~(RCC_BDCR_LSEDRV);

    /* Set the LSE Drive */
    RCC->BDCR |= RCC_LSEDrive;
}

/**
  * @brief  Enables or disables the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC and/or the LCD .
  * @note   LSI can not be disabled if the IWDG is running.
  * @param  NewState: new state of the LSI.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_LSICmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CSR |= RCC_CSR_LSION;
    }
    else
    {
        RCC->CSR &= ~RCC_CSR_LSION;
    }
}

/**
  * @brief  Enables or disables the RCC MSI.
  * @param  NewState: new state of the MSI.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_MSICmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CSR |= RCC_CSR_MSION;
    }
    else
    {
        RCC->CSR &= ~RCC_CSR_MSION;
    }
}

/**
  * @brief  Set range value of the RCC MSI .
  * @param  RCC_MSICLK: specifies the range value.
  *         This parameter can be one of the following values:
  *            @arg RCC_MSICLK_262K : MSI clock = 262KHz
  *            @arg RCC_MSICLK_524K : MSI clock = 524KHz
  *            @arg RCC_MSICLK_1_05M: MSI clock = 1.05MHz
  *            @arg RCC_MSICLK_2_1M : MSI clock = 2.1MHz
  *            @arg RCC_MSICLK_4_2M : MSI clock = 4.2MHz
  * @retval none.
  */
void RCC_MSIConfig(uint32_t RCC_MSICLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_MSICLK(RCC_MSICLK));

    /* Clear MSIRANGE[2:0] bits */
    RCC->CR2 &= ~(RCC_CR2_MSIRANGE);

    /* Set the MSIRANGE */
    RCC->CR2 |= RCC_MSICLK;
}

/**
  * @brief  Configures the PLL clock source and multiplication factor.
  * @note   This function must be used only when the PLL is disabled.
  * @param  RCC_PLLSource: specifies the PLL entry clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_PLLSource_HSI_Div2: HSI divide-by-2 oscillator clock selected as PLL clock source
  *            @arg RCC_PLLSource_HSE: HSE oscillator clock selected as PLL clock source
  *            @arg RCC_PLLSource_MSI: MSI oscillator clock selected as PLL clock source
  *            @arg RCC_PLLSource_HSI: HSI 8M oscillator clock selected as PLL clock source
  * @param  RCC_PLLMul: specifies the PLL multiplication factor, which drive the PLLVCO clock
  *         This parameter can be RCC_PLLMUL_x where x:[2,16]
  * @retval None
  */
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul)
{
    uint32_t tmp = 0;
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_PLL_SOURCE(RCC_PLLSource));
    assert_param(IS_RCC_PLL_MUL(RCC_PLLMul));

    /* Clear PLL Source [16] and Multiplier [21:18] bits */
    RCC->CFGR &= ~(RCC_CFGR_PLLMUL | RCC_CFGR_PLLSRC);

    tmp = RCC_PLLSource >> 4;

    /* Set the PLL Source and Multiplier */
    /* The flag to check is in CFGR register */
    if (tmp == 0)
    {
        RCC->CFGR |= (uint32_t)(((uint32_t)RCC_PLLSource << RCC_CFGR_PLLSRC_Pos) | RCC_PLLMul);
    }
    else
    {
        /* The flag to check is in CFGR4 register */
        /* Clear PPSS bits */
        RCC->CFGR4 &= ~RCC_CFGR4_PPSS;

        /* The PLL clock source is determined by the PPSS bits in the CFGR4 register */
        tmpreg = (uint32_t)(RCC_PLLSource & 0x0F) << RCC_CFGR4_PPSS_Pos;
        RCC->CFGR4 |= tmpreg;

        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC | RCC_PLLMul);
    }
}

/**
  * @brief  Enables or disables the PLL.
  * @note   After enabling the PLL, the application software should wait on
  *         PLLRDY flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @note   The PLL can not be disabled if it is used as system clock source
  * @note   The PLL is disabled by hardware when entering STOP and STANDBY modes.
  * @param  NewState: new state of the PLL.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_PLLCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CR |= RCC_CR_PLLON;
    }
    else
    {
        RCC->CR &= ~RCC_CR_PLLON;
    }
}

/**
  * @brief  Configures the PREDIV division factor.
  * @note   This function must be used only when the PLL is disabled.
  * @param  RCC_PREDIV_Div: specifies the PREDIV clock division factor.
  *         This parameter can be RCC_PREDIV_Divx where x:[1,16]
  * @retval None
  */
void RCC_PREDIVConfig(uint32_t RCC_PREDIV_Div)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_PREDIV(RCC_PREDIV_Div));

    tmpreg = RCC->CFGR2;
    /* Clear PREDIV[3:0] bits */

    tmpreg &= ~(RCC_CFGR2_PREDIV);

    /* Set the PREDIV division factor */
    tmpreg |= RCC_PREDIV_Div;

    /* Store the new value */
    RCC->CFGR2 = tmpreg;
}

/**
  * @brief  Enables or disables the Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure (Clock Security System Interrupt, CSSI),
  *         allowing the MCU to perform rescue operations. The CSSI is linked to
  *         the Cortex-M0 NMI (Non-Maskable Interrupt) exception vector.
  * @param  NewState: new state of the Clock Security System.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ClockSecuritySystemCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CR |= RCC_CR_CSSON;
    }
    else
    {
        RCC->CR &= ~RCC_CR_CSSON;
    }
}

/**
  * @brief  Selects the clock source to output on MCO pin (PA8) and the corresponding
  *         prescsaler.
  * @note   PA8 should be configured in alternate function mode.
  * @param  RCC_MCOSource: specifies the clock source to output.
  *         This parameter can be one of the following values:
  *            @arg RCC_MCOSource_NoClock: No clock selected.
  *            @arg RCC_MCOSource_LSE: LSE oscillator clock selected.
  *            @arg RCC_MCOSource_LSI: LSI oscillator clock selected.
  *            @arg RCC_MCOSource_SYSCLK: System clock selected.
  *            @arg RCC_MCOSource_HSE: HSE oscillator clock selected.
  *            @arg RCC_MCOSource_MSI: MSI oscillator clock selected.
  *            @arg RCC_MCOSource_HSI: HSI oscillator clock selected.
  *            @arg RCC_MCOSource_PLLCLK: PLL clock selected.
  * @param  RCC_MCOPrescaler: specifies the prescaler on MCO pin.
  *         This parameter can be one of the following values:
  *            @arg RCC_MCOPrescaler_1: MCO clock is divided by 1.
  *            @arg RCC_MCOPrescaler_2: MCO clock is divided by 2.
  *            @arg RCC_MCOPrescaler_4: MCO clock is divided by 4.
  *            @arg RCC_MCOPrescaler_8: MCO clock is divided by 8.
  *            @arg RCC_MCOPrescaler_16: MCO clock is divided by 16.
  *            @arg RCC_MCOPrescaler_32: MCO clock is divided by 32.
  *            @arg RCC_MCOPrescaler_64: MCO clock is divided by 64.
  *            @arg RCC_MCOPrescaler_128: MCO clock is divided by 128.
  * @retval None
  */
void RCC_MCOConfig(uint8_t RCC_MCOSource, uint32_t RCC_MCOPrescaler)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_MCO_SOURCE(RCC_MCOSource));
    assert_param(IS_RCC_MCO_PRESCALER(RCC_MCOPrescaler));

    /* Get CFGR value */
    tmpreg = RCC->CFGR;

    /* Clear MCOPRE[2:0] and MCO[3:0] bits */
    tmpreg &= ~(RCC_CFGR_MCOPRE | RCC_CFGR_MCO);

    /* Set the RCC_MCOSource and RCC_MCOPrescaler */
    tmpreg |= (RCC_MCOPrescaler | ((uint32_t)RCC_MCOSource << RCC_CFGR_MCO_Pos));
    /* Store the new value */
    RCC->CFGR = tmpreg;
}

/**
  * @brief  Get clock after wake-up from stop mode.
  * @retval Clock after wake-up from stop mode.
  *         Returned value can be one of the following values:
  *            @arg RCC_STOP_WAKEUPCLOCK_HSI: HSI clock.
  *            @arg RCC_STOP_WAKEUPCLOCK_MSI: MSI clock.
  */
uint32_t RCC_GetClkAfterWakeFromStop(void)
{
    return RCC->CFGR & RCC_CFGR_STOPWUCK;
}

/**
  * @brief  Set clock after wake-up from stop mode.
  * @param  RCC_Stop_WakeupClock: new state of the Clock after wake-up from stop mode.
  *         This parameter can be one of the following values:
  *            @arg RCC_STOP_WAKEUPCLOCK_HSI: HSI clock.
  *            @arg RCC_STOP_WAKEUPCLOCK_MSI: MSI clock.
  * @retval None
  */
void RCC_SetClkAfterWakeFromStop(uint32_t RCC_Stop_WakeupClock)
{
    /* Check the parameters */
    assert_param(IS_RCC_STOP_WAKEUPCLOCK(RCC_Stop_WakeupClock));

    /* Clear STOPWUCK bit */
    RCC->CFGR &=  ~RCC_CFGR_STOPWUCK;

    /* Set the RCC_Stop_WakeupClock */
    RCC->CFGR |= RCC_Stop_WakeupClock;
}

/**
  * @}
  */

/** @defgroup RCC_Group2 System AHB and APB busses clocks configuration functions
 *  @brief    System, AHB and APB busses clocks configuration functions
 *
@verbatim
    ===============================================================================
        ##### System, AHB and APB busses clocks configuration functions #####
    ===============================================================================
    [..] This section provide functions allowing to configure the System, AHB and
         APB busses clocks.
         (#) Several clock sources can be used to drive the System clock (SYSCLK): HSI,
             HSE and PLL.
             The AHB clock (HCLK) is derived from System clock through configurable prescaler
             and used to clock the CPU, memory and peripherals mapped on AHB bus (DMA and GPIO).
             and APB (PCLK) clocks are derived from AHB clock through
             configurable prescalers and used to clock the peripherals mapped on these busses.
             You can use "RCC_GetClocksFreq()" function to retrieve the frequencies of these clocks.
         -@- All the peripheral clocks are derived from the System clock (SYSCLK) except:
             (+@) The I2C clock which is derived from HSI or system clock (SYSCLK).
             (+@) The USART clock which is derived from HSI, system clock (SYSCLK), APB or LSE.
             (+@) The RTC clock which is derived from the LSE, LSI or 2 MHz HSE_RTC (HSE
                  divided by a programmable prescaler).
                  The System clock (SYSCLK) frequency must be higher or equal to the RTC/LCD
                  clock frequency.
             (+@) IWDG clock which is always the LSI clock.
         (#) The maximum frequency of the SYSCLK, HCLK and PCLK is 48 MHz.
             Depending on the maximum frequency, the FLASH wait states (WS) should be
             adapted accordingly:
             +--------------------------------------------- +
             |  Wait states  |   HCLK clock frequency (MHz) |
             |---------------|------------------------------|
             |0WS(1CPU cycle)|       0 < HCLK <= 24         |
             |---------------|------------------------------|
             |1WS(2CPU cycle)|       24 < HCLK <= 48        |
             +---------------|------------------------------+
         (#) After reset, the System clock source is the HSI (8 MHz) with 0 WS and
             prefetch is disabled.

    [..] It is recommended to use the following software sequences to tune the number
         of wait states needed to access the Flash memory with the CPU frequency (HCLK).
         (+) Increasing the CPU frequency
         (++) Program the Flash Prefetch buffer, using "FLASH_PrefetchBufferCmd(ENABLE)"
              function
         (++) Check that Flash Prefetch buffer activation is taken into account by
              reading FLASH_ACR using the FLASH_GetPrefetchBufferStatus() function
         (++) Program Flash WS to 1, using "FLASH_SetLatency(FLASH_Latency_1)" function
         (++) Check that the new number of WS is taken into account by reading FLASH_ACR
         (++) Modify the CPU clock source, using "RCC_SYSCLKConfig()" function
         (++) If needed, modify the CPU clock prescaler by using "RCC_HCLKConfig()" function
         (++) Check that the new CPU clock source is taken into account by reading
              the clock source status, using "RCC_GetSYSCLKSource()" function
         (+) Decreasing the CPU frequency
         (++) Modify the CPU clock source, using "RCC_SYSCLKConfig()" function
         (++) If needed, modify the CPU clock prescaler by using "RCC_HCLKConfig()" function
         (++) Check that the new CPU clock source is taken into account by reading
              the clock source status, using "RCC_GetSYSCLKSource()" function
         (++) Program the new number of WS, using "FLASH_SetLatency()" function
         (++) Check that the new number of WS is taken into account by reading FLASH_ACR
         (++) Disable the Flash Prefetch buffer using "FLASH_PrefetchBufferCmd(DISABLE)"
              function
         (++) Check that Flash Prefetch buffer deactivation is taken into account by reading FLASH_ACR
              using the FLASH_GetPrefetchBufferStatus() function.
@endverbatim
  * @{
  */

/**
  * @brief  Configures the system clock (SYSCLK).
  * @note   The HSI is used (enabled by hardware) as system clock source after
  *         startup from Reset, wake-up from  STANDBY mode, or in case
  *         of failure of the HSE used directly or indirectly as system clock
  *         (if the Clock Security System CSS is enabled).
  * @note   User can choose system clock as HSI or MSI wake-up from STOP mode by RCC_CFGR_STOPWUCK.
  * @note   A switch from one clock source to another occurs only if the target
  *         clock source is ready (clock stable after startup delay or PLL locked).
  *         If a clock source which is not yet ready is selected, the switch will
  *         occur when the clock source will be ready.
  *         You can use RCC_GetSYSCLKSource() function to know which clock is
  *         currently used as system clock source.
  * @param  RCC_SYSCLKSource: specifies the clock source used as system clock source
  *         This parameter can be one of the following values:
  *            @arg RCC_SYSCLKSource_HSI   : HSI selected as system clock source
  *            @arg RCC_SYSCLKSource_HSE   : HSE selected as system clock source
  *            @arg RCC_SYSCLKSource_PLLCLK: PLL selected as system clock source
  *            @arg RCC_SYSCLKSource_LSE   : LSE selected as system clock source
  *            @arg RCC_SYSCLKSource_LSI   : LSI selected as system clock source
  *            @arg RCC_SYSCLKSource_HSI48 : HSI48 selected as system clock source
  *            @arg RCC_SYSCLKSource_HSI16 : HSI16 selected as system clock source
  *            @arg RCC_SYSCLKSource_GPIO  : GPIO selected as system clock source
  *            @arg RCC_SYSCLKSource_MSI   : MSI selected as system clock source
  * @retval None
  */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
    uint32_t tmp = 0;
    uint32_t tmpreg = 0;
    uint32_t StartUpCounter = 0;

    /* Check the parameters */
    assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));

    /* wait for CLK Ready*/
    do
    {
        switch (RCC_SYSCLKSource)
        {
            case RCC_SYSCLKSource_HSI:
                tmp = RCC->CR & RCC_CR_HSIRDY;
                break;

            case RCC_SYSCLKSource_HSE:
                tmp = RCC->CR & RCC_CR_HSERDY;
                break;

            case RCC_SYSCLKSource_PLLCLK:
                tmp = RCC->CR & RCC_CR_PLLRDY;
                break;

            case RCC_SYSCLKSource_LSE:
                tmp = RCC->BDCR & RCC_BDCR_LSERDY;
                break;

            case RCC_SYSCLKSource_LSI:
                tmp = RCC->CSR & RCC_CSR_LSIRDY;
                break;

            case RCC_SYSCLKSource_HSI48:
                tmp = RCC->CR2 & RCC_CR2_HSI48RDY;
                break;

            case RCC_SYSCLKSource_HSI16:
                tmp = RCC->CR2 & RCC_CR2_HSI16RDY;
                break;

            case RCC_SYSCLKSource_MSI:
                tmp = RCC->CR2 & RCC_CR2_MSIRDY;
                break;
        }

        StartUpCounter++;
    } while ((tmp == 0) && (StartUpCounter != 0xFFFF));

    /* Clear ESSS bits */
    RCC->CFGR4 &= ~RCC_CFGR4_ESSS;

    tmp = RCC_SYSCLKSource >> 4;

    if (tmp == 0)
    {
        tmpreg = RCC->CFGR;

        /* Clear SW[1:0] bits */
        tmpreg &= ~RCC_CFGR_SW;

        /* Set SW[1:0] bits according to RCC_SYSCLKSource value */
        tmpreg |= RCC_SYSCLKSource;

        /* Store the new value */
        RCC->CFGR = tmpreg;
    }
    else
    {
        tmpreg = RCC->CFGR4;

        /* Clear CFGR_ESW[2:0] bits */
        tmpreg &= ~RCC_CFGR4_ESW;

        /* Set CFGR_ESW[2:0] and ESSS bits  */
        tmpreg |= RCC_SYSCLKSource | RCC_CFGR4_ESSS;

        /* Store the new value */
        RCC->CFGR4 = tmpreg;
    }

}

/**
  * @brief  Returns the clock source used as system clock.
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following values:
  *         - 0x00: HSI used as system clock
  *         - 0x01: HSE used as system clock
  *         - 0x02: PLL used as system clock
  *         - 0x10: LSE used as system clock
  *         - 0x11: LSI used as system clock
  *         - 0x12: HSI48 used as system clock
  *         - 0x13: HSI16 used as system clock
  *         - 0x14: GPIO INPUT used as system clock
  *         - 0x15: MSI used as system clock
  */
uint8_t RCC_GetSYSCLKSource(void)
{
    uint32_t tmp = 0;

    tmp = (RCC->CFGR4 & RCC_CFGR4_ESSS) >> 7;

    if (tmp != 0)
    {
        /*RCC_CFGR4.ESWS set as SYSCLK*/
        return ((uint8_t)(((RCC->CFGR4 & RCC_CFGR4_ESWS) >> RCC_CFGR4_ESWS_Pos) | 0x10));
    }
    else
    {
        /*RCC_CFGR.SWS set as SYSCLK*/
        return ((uint8_t)((RCC->CFGR & RCC_CFGR_SWS) >> RCC_CFGR_SWS_Pos));
    }
}

/**
  * @brief  Configures the AHB clock (HCLK).
  * @param  RCC_SYSCLK: defines the AHB clock divider. This clock is derived from
  *         the system clock (SYSCLK).
  *         This parameter can be one of the following values:
  *            @arg RCC_SYSCLK_Div1:   AHB clock = SYSCLK
  *            @arg RCC_SYSCLK_Div2:   AHB clock = SYSCLK/2
  *            @arg RCC_SYSCLK_Div4:   AHB clock = SYSCLK/4
  *            @arg RCC_SYSCLK_Div8:   AHB clock = SYSCLK/8
  *            @arg RCC_SYSCLK_Div16:  AHB clock = SYSCLK/16
  *            @arg RCC_SYSCLK_Div64:  AHB clock = SYSCLK/64
  *            @arg RCC_SYSCLK_Div128: AHB clock = SYSCLK/128
  *            @arg RCC_SYSCLK_Div256: AHB clock = SYSCLK/256
  *            @arg RCC_SYSCLK_Div512: AHB clock = SYSCLK/512
  * @retval None
  */
void RCC_HCLKConfig(uint32_t RCC_SYSCLK)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_HCLK(RCC_SYSCLK));

    tmpreg = RCC->CFGR;

    /* Clear HPRE[3:0] bits */
    tmpreg &= ~RCC_CFGR_HPRE;

    /* Set HPRE[3:0] bits according to RCC_SYSCLK value */
    tmpreg |= RCC_SYSCLK;

    /* Store the new value */
    RCC->CFGR = tmpreg;
}

/**
  * @brief  Configures the APB clock (PCLK).
  * @param  RCC_PCLK: defines the APB clock divider. This clock is derived from
  *         the AHB clock (HCLK).
  *         This parameter can be one of the following values:
  *            @arg RCC_HCLK_Div1: APB clock = HCLK
  *            @arg RCC_HCLK_Div2: APB clock = HCLK/2
  *            @arg RCC_HCLK_Div4: APB clock = HCLK/4
  *            @arg RCC_HCLK_Div8: APB clock = HCLK/8
  *            @arg RCC_HCLK_Div16: APB clock = HCLK/16
  * @retval None
  */
void RCC_PCLKConfig(uint32_t RCC_PCLK)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_PCLK(RCC_PCLK));

    tmpreg = RCC->CFGR;

    /* Clear PPRE[2:0] bits */
    tmpreg &= ~RCC_CFGR_PPRE;

    /* Set PPRE[2:0] bits according to RCC_PCLK value */
    tmpreg |= (uint32_t)RCC_PCLK << RCC_CFGR_PPRE_Pos;

    /* Store the new value */
    RCC->CFGR = tmpreg;
}

/**
  * @brief  Configures the LPUART1 clock (LPUART1CLK).
  * @param  RCC_LPUART1CLK: defines the LPUART1 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_SELECTIONCLK_PCLK: LPUART1 clock = PCLK
  *            @arg RCC_SELECTIONCLK_MSI:  LPUART1 clock = MSI
  *            @arg RCC_SELECTIONCLK_LSE:  LPUART1 clock = LSE
  *            @arg RCC_SELECTIONCLK_LSI:  LPUART1 clock = LSI
  *            @arg RCC_SELECTIONCLK_HSI16:LPUART1 clock = LSI16
  * @retval None
  */
void RCC_LPUART1CLKConfig(uint32_t RCC_LPUART1CLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_SELECTIONCLK(RCC_LPUART1CLK));

    /* Clear LPUART1SW[2:0] bit */
    RCC->CFGR3 &= ~RCC_CFGR3_LPUART1SW;

    /* Set LPUART1SW[2:0] bits according to RCC_LPUART1CLK value */
    RCC->CFGR3 |= RCC_LPUART1CLK << RCC_CFGR3_LPUART1SW_Pos;
}

/**
  * @brief  Configures the USB clock (USBCLK).
  * @param  RCC_USBCLK: defines the USB clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_USBCLK_PLL: USB clock = PLLCLK
  *            @arg RCC_USBCLK_HSI48: USB clock = HSI48
  * @retval None
  */
void RCC_USBCLKConfig(uint32_t RCC_USBCLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_USBCLK(RCC_USBCLK));

    /* Clear USBSEL bit */
    RCC->CFGR3 &= ~RCC_CFGR3_USBSEL;

    /* Set USBSEL bits according to RCC_USBCLK value */
    RCC->CFGR3 |= RCC_USBCLK ;
}

/**
  * @brief  Configures the UART4 clock (UART4CLK).
  * @param  RCC_UART4CLK: defines the UART4 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_SELECTIONCLK_PCLK: UART4 clock = PCLK
  *            @arg RCC_SELECTIONCLK_MSI:  UART4 clock = MSI
  *            @arg RCC_SELECTIONCLK_LSE:  UART4 clock = LSE
  *            @arg RCC_SELECTIONCLK_LSI:  UART4 clock = LSI
  *            @arg RCC_SELECTIONCLK_HSI16:UART4 clock = LSI16
  * @retval None
  */
void RCC_UART4CLKConfig(uint32_t RCC_UART4CLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_SELECTIONCLK(RCC_UART4CLK));

    /* Clear UART4SW[2:0] bit */
    RCC->CFGR3 &= ~RCC_CFGR3_UART4SW;

    /* Set UART4SW bits according to RCC_UART4CLK value */
    RCC->CFGR3 |= RCC_UART4CLK << RCC_CFGR3_UART4SW_Pos;
}

/**
  * @brief  Configures the UART3 clock (UART3CLK).
  * @param  RCC_UART3CLK: defines the UART3 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_SELECTIONCLK_PCLK:  UART3 clock = PCLK
  *            @arg RCC_SELECTIONCLK_MSI:   UART3 clock = MSI
  *            @arg RCC_SELECTIONCLK_LSE:   UART3 clock = LSE
  *            @arg RCC_SELECTIONCLK_LSI:   UART3 clock = LSI
  *            @arg RCC_SELECTIONCLK_HSI16: UART3 clock = LSI16
  * @retval None
  */
void RCC_UART3CLKConfig(uint32_t RCC_UART3CLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_SELECTIONCLK(RCC_UART3CLK));

    /* Clear UART3SW[2:0] bit */
    RCC->CFGR3 &= ~RCC_CFGR3_UART3SW;

    /* Set UART3SW[2:0] bits according to RCC_UART3CLK value */
    RCC->CFGR3 |= RCC_UART3CLK << RCC_CFGR3_UART3SW_Pos;
}

/**
  * @brief  Configures the USART2 clock (USART2CLK).
  * @param  RCC_USART2CLK: defines the USART2 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_SELECTIONCLK_PCLK: USART2 clock = PCLK
  *            @arg RCC_SELECTIONCLK_MSI:  USART2 clock = MSI
  *            @arg RCC_SELECTIONCLK_LSE:  USART2 clock = LSE
  *            @arg RCC_SELECTIONCLK_LSI:  USART2 clock = LSI
  *            @arg RCC_SELECTIONCLK_HSI16:USART2 clock = LSI16
  * @retval None
  */
void RCC_USART2CLKConfig(uint32_t RCC_USART2CLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_SELECTIONCLK(RCC_USART2CLK));

    /* Clear USART2SW[2:0] bit */
    RCC->CFGR3 &= ~RCC_CFGR3_USART2SW;

    /* Set USART2SW[2:0] bits according to RCC_USART2CLK value */
    RCC->CFGR3 |= RCC_USART2CLK << RCC_CFGR3_USART2SW_Pos;
}

/**
  * @brief  Configures the USART1 clock (USART1CLK).
  * @param  RCC_USART1CLK: defines the USART1 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_SELECTIONCLK_PCLK: USART1 clock = PCLK
  *            @arg RCC_SELECTIONCLK_MSI:  USART1 clock = MSI
  *            @arg RCC_SELECTIONCLK_LSE:  USART1 clock = LSE
  *            @arg RCC_SELECTIONCLK_LSI:  USART1 clock = LSI
  *            @arg RCC_SELECTIONCLK_HSI16:USART1 clock = LSI16
  * @retval None
  */
void RCC_USART1CLKConfig(uint32_t RCC_USART1CLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_SELECTIONCLK(RCC_USART1CLK));

    /* Clear USART1SW[2:0] bit */
    RCC->CFGR3 &= ~RCC_CFGR3_USART1SW;

    /* Set USART1SW[2:0] bits according to RCC_USART1CLK value */
    RCC->CFGR3 |= RCC_USART1CLK << RCC_CFGR3_USART1SW_Pos;
}

/**
  * @brief  Configures the BEEPER clock (BEEPERCLK).
  * @param  RCC_BEEPERCLK: defines the BEEPER clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_BEEPERCLK_PCLK2: BEEPER clock = PCLK
  *            @arg RCC_BEEPERCLK_LSI  : BEEPER clock = LSI
  *            @arg RCC_BEEPERCLK_HSE  : BEEPER clock = HSE
  * @retval None
  */
void RCC_BEEPERCLKConfig(uint32_t RCC_BEEPERCLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_BEEPERCLK(RCC_BEEPERCLK));

    /* Clear BEEPERSW[1:0] bit */
    RCC->CFGR4 &= ~RCC_CFGR4_BEEPER_SW;

    /* Set BEEPERSW[1:0] bits according to RCC_BEEPERCLK value */
    RCC->CFGR4 |= RCC_BEEPERCLK;
}

/**
  * @brief  Configures the I2C1 clock (I2C1CLK).
  * @param  RCC_I2C1CLK: defines the I2C1 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_I2C1CLK_HSI8M : I2C1 clock = HSI8M
  *            @arg RCC_I2C1CLK_MSI   : I2C1 clock = MSI
  *            @arg RCC_I2C1CLK_SYSCLK: I2C1 clock = SYSCLK
  *            @arg RCC_I2C1CLK_PCLK :  I2C1 clock = PCLK
  * @retval None
  */
void RCC_I2C1CLKConfig(uint32_t RCC_I2C1CLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_I2C1CLK(RCC_I2C1CLK));

    /* Clear I2C1CLKSW[1:0] bit */
    RCC->CFGR4 &= ~RCC_CFGR4_I2C1CLK_SW;

    /* Set I2C1CLKSW[1:0] bits according to RCC_USBCLK value */
    RCC->CFGR4 |= RCC_I2C1CLK;
}

/**
  * @brief  Configures the I2C2 clock (I2C2CLK).
  * @param  RCC_I2C2CLK: defines the I2C2 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_I2C2CLK_HSI8M : I2C2 clock = HSI8M
  *            @arg RCC_I2C2CLK_MSI   : I2C2 clock = MSI
  *            @arg RCC_I2C2CLK_SYSCLK: I2C2 clock = SYSCLK
  *            @arg RCC_I2C2CLK_PCLK1 : I2C2 clock = PCLK1
  * @retval None
  */
void RCC_I2C2CLKConfig(uint32_t RCC_I2C2CLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_I2C2CLK(RCC_I2C2CLK));

    /* Clear I2C2CLKSW[1:0] bits */
    RCC->CFGR4 &= ~RCC_CFGR4_I2C2CLK_SW;

    /* Set I2C2CLKSW[1:0] bits according to RCC_I2C2CLK value */
    RCC->CFGR4 |= RCC_I2C2CLK;
}

/**
  * @brief  Configures the external clock source(GPIOCLK).
  * @param  RCC_EXTCLK_GPIO: defines the external clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_EXTCLK_GPIO_PA4  : external clock = GPIOA_4
  *            @arg RCC_EXTCLK_GPIO_PA13 : external clock = GPIOA_13
  *            @arg RCC_EXTCLK_GPIO_PA14 : external clock = GPIOA_14
  * @retval None
  */
void RCC_ExternalClkConfig(uint32_t RCC_EXTCLK_GPIO)
{
    /* Check the parameters */
    assert_param(IS_RCC_EXTCLK_GPIO(RCC_EXTCLK_GPIO));

    /* Clear EXTCLK_SEL[1:0] bits */
    RCC->CFGR4 &= ~RCC_CFGR4_EXTCLK_SEL;

    /* Set EXTCLK_SEL[1:0] bits according to RCC_BEEPERCLK value */
    RCC->CFGR4 |= RCC_EXTCLK_GPIO;
}

/**
  * @brief  Configures the FLITF clock(FLITFCLK).
  * @param  RCC_FLITFCLK: defines the FLITF clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_FLITFCLK_HSI8M   : FLITF clock = HSI
  *            @arg RCC_FLITFCLK_SYSCLK  : FLITF clock = SYSCLK
  *            @arg RCC_FLITFCLK_EXTCLK  : FLITF clock = EXTCLK
  * @param  RCC_FLITFCLKPrescaler: defines the FLITF clock prescaler.
  *         This parameter can be one of the following values:
  *            @arg RCC_FLITFPrescaler_1 : FLITF clock prescaler = Prescaler_1
  *            @arg RCC_FLITFPrescaler_2 : FLITF clock prescaler = Prescaler_2
  *            @arg RCC_FLITFPrescaler_4 : FLITF clock prescaler = Prescaler_4
  *            @arg RCC_FLITFPrescaler_6 : FLITF clock prescaler = Prescaler_6
  * @retval None
  */
void RCC_FLITFCLKConfig(uint32_t RCC_FLITFCLK, uint32_t RCC_FLITFCLKPrescaler)
{
    /* Check the parameters */
    assert_param(IS_RCC_FLITFCLK(RCC_FLITFCLK));
    assert_param(IS_RCC_FLITF_PRESCALER(RCC_FLITFCLKPrescaler));

    /* Clear FLITFCLK_SEL[1:0] and FLITFCLK_PRE[1:0] bits */
    RCC->CFGR4 &= ~(RCC_CFGR4_FLITFCLK_SEL | RCC_CFGR4_FLITFCLK_PRE);

    /* Set FLITFCLK_SEL and FLITFCLK_PRE bits according to RCC_FLITFCLK value */
    RCC->CFGR4 |= RCC_FLITFCLK | RCC_FLITFCLKPrescaler;
}

/**
  * @brief  Returns the frequencies of the System, AHB and APB busses clocks.
  * @note   The frequency returned by this function is not the real frequency
  *         in the chip. It is calculated based on the predefined constant and
  *         the source selected by RCC_SYSCLKConfig():
  * @note   If SYSCLK source is HSE, function returns constant HSE_VALUE
  * @note   If SYSCLK source is PLL, function returns constant HSE_VALUE
  *         or HSI_VALUE(*) multiplied by the PLL factors.
  * @note   HSI_VALUE is a constant defined in HK32f0xx.h file (default value
  *         8 MHz) but the real value may vary depending on the variations
  *         in voltage and temperature, refer to RCC_AdjustHSICalibrationValue().
  * @note   HSE_VALUE is a constant defined in HK32f0xx.h file (default value
  *         8 MHz), user has to ensure that HSE_VALUE is same as the real
  *         frequency of the crystal used. Otherwise, this function may
  *         return wrong result.
  * @note   The result of this function could be not correct when using fractional
  *         value for HSE crystal.
  * @param  RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold
  *         the clocks frequencies.
  * @note   This function can be used by the user application to compute the
  *         baudrate for the communication peripherals or configure other parameters.
  * @note   Each time SYSCLK, HCLK and/or PCLK clock changes, this function
  *         must be called to update the structure's field. Otherwise, any
  *         configuration based on this function will be incorrect.
  * @retval None
  */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
    uint32_t tmp = 0, pllmull = 0, pllsource = 0, prediv1factor = 0, presc = 0, pllclk = 0;

    /* Get PLL clock source and multiplication factor */
    pllmull = RCC->CFGR & RCC_CFGR_PLLMUL;
    pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
    pllmull = ( pllmull >> 18) + 2;

    if (pllsource == 0x00)
    {
        /* HSI oscillator clock divided by 2 selected as PLL clock entry */
        pllclk = (HSI_VALUE >> 1) * pllmull;
    }
    else
    {
        prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV) + 1;

        pllsource = (RCC->CFGR4 & RCC_CFGR4_PPSS) >> RCC_CFGR4_PPSS_Pos;

        if (pllsource == 0x00)
        {
            /* HSE oscillator clock selected as PREDIV1 clock entry */
            pllclk = (HSE_VALUE / prediv1factor) * pllmull;
        }
        else if (pllsource == 0x01)
        {
            /* HSI oscillator clock selected as PREDIV1 clock entry */
            pllclk = (HSI_VALUE / prediv1factor) * pllmull;
        }
        else
        {
            if (pllsource == 0x02)
            {
                /* MSI oscillator clock selected as PREDIV1 clock entry */
                pllclk = (MSI_VALUE / prediv1factor) * pllmull;
            }
        }
    }

    /* Get SYSCLK source */
    if ((RCC->CFGR4 & RCC_CFGR4_ESSS) != 0)
    {
        tmp = (RCC->CFGR4 & RCC_CFGR4_ESWS) >> RCC_CFGR4_ESWS_Pos;
        tmp = tmp | 0x10;
    }
    else
    {
        tmp = (RCC->CFGR & RCC_CFGR_SWS) >> RCC_CFGR_SWS_Pos;
    }

    switch (tmp)
    {
        /* HSI used as system clock */
        case 0x00:
            RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
            break;

        /* HSE used as system clock */
        case 0x01:
            RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
            break;

        /* PLL used as system clock */
        case 0x02:
            RCC_Clocks->SYSCLK_Frequency = pllclk;
            break;

        /* LSE used as system clock */
        case 0x10:
            RCC_Clocks->SYSCLK_Frequency = LSE_VALUE;
            break;

        /* LSI used as system clock */
        case 0x11:
            RCC_Clocks->SYSCLK_Frequency = LSI_VALUE;
            break;

        /* HSI48 used as system clock */
        case 0x12:
            RCC_Clocks->SYSCLK_Frequency = HSI48_VALUE;
            break;

        /* HSI16 used as system clock */
        case 0x13:
            RCC_Clocks->SYSCLK_Frequency = HSI16_VALUE;
            break;

        /* EXTCLK_GPIOINPUT used as system clock */
        case 0x14:
            RCC_Clocks->SYSCLK_Frequency = EXTCLK_GPIOINPUT_VALUE;
            break;

        /* MSI used as system clock */
        case 0x15:
            RCC_Clocks->SYSCLK_Frequency = MSI_VALUE;
            break;

        /* HSI used as system clock */
        default:
            RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
            break;
    }

    /* Compute HCLK, PCLK clocks frequencies -----------------------------------*/
    /* Get HCLK prescaler */
    tmp = RCC->CFGR & RCC_CFGR_HPRE;
    tmp = tmp >> RCC_CFGR_HPRE_Pos;
    presc = APBAHBPrescTable[tmp];
    /* HCLK clock frequency */
    RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;

    /* Get PCLK(APB) prescaler */
    tmp = RCC->CFGR & RCC_CFGR_PPRE;
    tmp = tmp >> RCC_CFGR_PPRE_Pos;
    presc = APBAHBPrescTable[tmp];
    /* PCLK clock frequency */
    RCC_Clocks->PCLK_Frequency = RCC_Clocks->HCLK_Frequency >> presc;

    /* I2C1CLK clock frequency */
    tmp = (RCC->CFGR4 & RCC_CFGR4_I2C1CLK_SW) >> RCC_CFGR4_I2C1CLK_SW_Pos;

    switch (tmp)
    {
        /* I2C1 Clock is HSI Osc. */
        case 0x00:
            RCC_Clocks->I2C1CLK_Frequency = HSI_VALUE;
            break;

        /* I2C1 Clock is MSI Osc. */
        case 0x01:
            RCC_Clocks->I2C1CLK_Frequency = MSI_VALUE;
            break;

        /* I2C1 Clock is System Clock */
        case 0x02:
            RCC_Clocks->I2C1CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
            break;

        /* I2C1 Clock is PCLK Clock */
        case 0x03:
            RCC_Clocks->I2C1CLK_Frequency = RCC_Clocks->PCLK_Frequency;
            break;

        default:
            RCC_Clocks->I2C1CLK_Frequency = HSI_VALUE;
            break;
    }

    /* I2C2CLK clock frequency */
    tmp = (RCC->CFGR4 & RCC_CFGR4_I2C2CLK_SW) >> RCC_CFGR4_I2C2CLK_SW_Pos;

    switch (tmp)
    {
        /* I2C2 Clock is HSI Osc. */
        case 0x00:
            RCC_Clocks->I2C2CLK_Frequency = HSI_VALUE;
            break;

        /* I2C2 Clock is MSI Osc. */
        case 0x01:
            RCC_Clocks->I2C2CLK_Frequency = MSI_VALUE;
            break;

        /* I2C2 Clock is System Clock */
        case 0x02:
            RCC_Clocks->I2C2CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
            break;

        /* I2C2 Clock is PCLK Clock */
        case 0x03:
            RCC_Clocks->I2C2CLK_Frequency = RCC_Clocks->PCLK_Frequency;
            break;

        default:
            RCC_Clocks->I2C2CLK_Frequency = HSI_VALUE;
            break;
    }

    /* BEEPER clock frequency */
    tmp = (RCC->CFGR4 & RCC_CFGR4_BEEPER_SW) >> RCC_CFGR4_BEEPER_SW_Pos;

    switch (tmp)
    {
        /* BEEPER Clock is PCLK2 Clock */
        case 0x00:
            RCC_Clocks->BEEPERCLK_Frequency = RCC_Clocks->PCLK_Frequency;
            break;

        /* BEEPER Clock is LSI Osc. */
        case 0x01:
            RCC_Clocks->BEEPERCLK_Frequency = LSI_VALUE;
            break;

        /* BEEPER Clock is HSE Osc. */
        case 0x02:
            RCC_Clocks->BEEPERCLK_Frequency = HSE_VALUE;
            break;

        default:
            RCC_Clocks->BEEPERCLK_Frequency = RCC_Clocks->PCLK_Frequency;
            break;
    }

    /* USART1CLK clock frequency */
    tmp = (RCC->CFGR3 & RCC_CFGR3_USART1SW) >> RCC_CFGR3_USART1SW_Pos;

    switch (tmp)
    {
        /* USART1 Clock is PCLK Clock */
        case 0x00:
            RCC_Clocks->USART1CLK_Frequency = RCC_Clocks->PCLK_Frequency;
            break;

        /* USART1 Clock is MSI Osc. */
        case 0x01:
            RCC_Clocks->USART1CLK_Frequency = MSI_VALUE;
            break;

        /* USART1 Clock is LSE Osc. */
        case 0x02:
            RCC_Clocks->USART1CLK_Frequency = LSE_VALUE;
            break;

        /* USART1 Clock is LSI Osc. */
        case 0x03:
            RCC_Clocks->USART1CLK_Frequency = LSI_VALUE;
            break;

        /* USART1 Clock is HSI16 Osc. */
        case 0x04:
            RCC_Clocks->USART1CLK_Frequency = HSI16_VALUE;
            break;

        default:
            RCC_Clocks->USART1CLK_Frequency = RCC_Clocks->PCLK_Frequency;
            break;
    }

    /* USART2CLK clock frequency */
    tmp = (RCC->CFGR3 & RCC_CFGR3_USART2SW) >> RCC_CFGR3_USART2SW_Pos;

    switch (tmp)
    {
        /* USART2 Clock is PCLK Clock */
        case 0x00:
            RCC_Clocks->USART2CLK_Frequency = RCC_Clocks->PCLK_Frequency;
            break;

        /* USART2 Clock is MSI Osc. */
        case 0x01:
            RCC_Clocks->USART2CLK_Frequency = MSI_VALUE;
            break;

        /* USART2 Clock is LSE Osc. */
        case 0x02:
            RCC_Clocks->USART2CLK_Frequency = LSE_VALUE;
            break;

        /* USART2 Clock is LSI Osc. */
        case 0x03:
            RCC_Clocks->USART2CLK_Frequency = LSI_VALUE;
            break;

        /* USART2 Clock is HSI16 Osc. */
        case 0x04:
            RCC_Clocks->USART2CLK_Frequency = HSI16_VALUE;
            break;

        default:
            RCC_Clocks->USART2CLK_Frequency = RCC_Clocks->PCLK_Frequency;
            break;
    }

    /* UART3CLK clock frequency */
    tmp = (RCC->CFGR3 & RCC_CFGR3_UART3SW) >> RCC_CFGR3_UART3SW_Pos;

    switch (tmp)
    {
        /* UART3 Clock is PCLK Clock */
        case 0x00:
            RCC_Clocks->UART3CLK_Frequency = RCC_Clocks->PCLK_Frequency;
            break;

        /* UART3 Clock is MSI Osc. */
        case 0x01:
            RCC_Clocks->UART3CLK_Frequency = MSI_VALUE;
            break;

        /* UART3 Clock is LSE Osc. */
        case 0x02:
            RCC_Clocks->UART3CLK_Frequency = LSE_VALUE;
            break;

        /* UART3 Clock is LSI Osc. */
        case 0x03:
            RCC_Clocks->UART3CLK_Frequency = LSI_VALUE;
            break;

        /* UART3 Clock is HSI16 Osc. */
        case 0x04:
            RCC_Clocks->UART3CLK_Frequency = HSI16_VALUE;
            break;

        default:
            RCC_Clocks->UART3CLK_Frequency = RCC_Clocks->PCLK_Frequency;
            break;
    }

    /* UART4CLK clock frequency */
    tmp = (RCC->CFGR3 & RCC_CFGR3_UART4SW) >> RCC_CFGR3_UART4SW_Pos;

    switch (tmp)
    {
        /* UART4 Clock is PCLK Clock */
        case 0x00:
            RCC_Clocks->UART4CLK_Frequency = RCC_Clocks->PCLK_Frequency;
            break;

        /* UART4 Clock is MSI Osc. */
        case 0x01:
            RCC_Clocks->UART4CLK_Frequency = MSI_VALUE;
            break;

        /* UART4 Clock is LSE Osc. */
        case 0x02:
            RCC_Clocks->UART4CLK_Frequency = LSE_VALUE;
            break;

        /* UART4 Clock is LSI Osc. */
        case 0x03:
            RCC_Clocks->UART4CLK_Frequency = LSI_VALUE;
            break;

        /* UART4 Clock is HSI16 Osc. */
        case 0x04:
            RCC_Clocks->UART4CLK_Frequency = HSI16_VALUE;
            break;

        default:
            RCC_Clocks->UART4CLK_Frequency = RCC_Clocks->PCLK_Frequency;
            break;
    }

    /* USBCLK clock frequency */
    tmp = (RCC->CFGR3 & RCC_CFGR3_USBSEL) >> RCC_CFGR3_USBSEL_Pos;

    switch (tmp)
    {
        /* USB Clock is PLL clock */
        case 0x0:
            RCC_Clocks->USBCLK_Frequency = pllclk;
            break;

        /* USB Clock is HSI48 Osc. */
        case 0x1:
            RCC_Clocks->USBCLK_Frequency = HSI48_VALUE;
            break;

        default:
            RCC_Clocks->USBCLK_Frequency = pllclk;
            break;
    }

    /* LPUART1CLK clock frequency */
    tmp = (RCC->CFGR3 & RCC_CFGR3_LPUART1SW) >> RCC_CFGR3_LPUART1SW_Pos;

    switch (tmp)
    {
        /* LPUART1 Clock is PCLK Clock */
        case 0x00:
            RCC_Clocks->LPUART1CLK_Frequency = RCC_Clocks->PCLK_Frequency;
            break;

        /* LPUART1 Clock is MSI Osc. */
        case 0x01:
            RCC_Clocks->LPUART1CLK_Frequency = MSI_VALUE;
            break;

        /* LPUART1 Clock is LSE Osc. */
        case 0x02:
            RCC_Clocks->LPUART1CLK_Frequency = LSE_VALUE;
            break;

        /* LPUART1 Clock is LSI Osc. */
        case 0x03:
            RCC_Clocks->LPUART1CLK_Frequency = LSI_VALUE;
            break;

        /* LPUART1 Clock is HSI16 Osc. */
        case 0x04:
            RCC_Clocks->LPUART1CLK_Frequency = HSI16_VALUE;
            break;

        default:
            RCC_Clocks->LPUART1CLK_Frequency = RCC_Clocks->PCLK_Frequency;
            break;
    }

    /* RTCCLK clock frequency */
    tmp = (RCC->BDCR & RCC_BDCR_RTC_SEL) >> RCC_BDCR_RTC_SEL_Pos;

    switch (tmp)
    {
        /* RTC Clock is LSE Osc. */
        case 0x01:
            RCC_Clocks->RTCCLK_Frequency = LSE_VALUE;
            break;

        /* RTC Clock is LSI Osc. */
        case 0x02:
            RCC_Clocks->RTCCLK_Frequency = LSI_VALUE;
            break;

        /* RTC Clock is HSE/32 Osc. */
        case 0x03:
            RCC_Clocks->RTCCLK_Frequency = HSE_VALUE / 32;
            break;

        /* RTC Clock is MSI Osc. */
        case 0x04:
            RCC_Clocks->RTCCLK_Frequency = MSI_VALUE;
            break;

        default:
            RCC_Clocks->RTCCLK_Frequency = MSI_VALUE;
            break;
    }

    /* LCD PUMP driver capability */
    tmp = (RCC->BDCR & RCC_BDCR_LCDPUMPDRV) >> RCC_BDCR_LCDPUMPDRV_Pos;

    switch (tmp)
    {
        /* LCD PUMP driver capability Level 0 */
        case 0x00:
            RCC_Clocks->LCDPUMPDRV_Capability = RCC_LCDPUMP_DRV_LEVEL0;
            break;

        /* LCD PUMP driver capability Level 1 */
        case 0x01:
            RCC_Clocks->LCDPUMPDRV_Capability = RCC_LCDPUMP_DRV_LEVEL1;
            break;

        /* LCD PUMP driver capability Level 2 */
        case 0x02:
            RCC_Clocks->LCDPUMPDRV_Capability = RCC_LCDPUMP_DRV_LEVEL2;
            break;

        /* LCD PUMP driver capability Level 3 */
        case 0x03:
            RCC_Clocks->LCDPUMPDRV_Capability = RCC_LCDPUMP_DRV_LEVEL3;
            break;

        /* LCD PUMP driver capability Level 4 */
        case 0x04:
            RCC_Clocks->LCDPUMPDRV_Capability = RCC_LCDPUMP_DRV_LEVEL4;
            break;

        /* LCD PUMP driver capability Level 5 */
        case 0x05:
            RCC_Clocks->LCDPUMPDRV_Capability = RCC_LCDPUMP_DRV_LEVEL5;
            break;

        /* LCD PUMP driver capability Level 6 */
        case 0x06:
            RCC_Clocks->LCDPUMPDRV_Capability = RCC_LCDPUMP_DRV_LEVEL6;
            break;

        /* LCD PUMP driver capability Level 7 */
        case 0x07:
            RCC_Clocks->LCDPUMPDRV_Capability = RCC_LCDPUMP_DRV_LEVEL7;
            break;

        default:
            RCC_Clocks->LCDPUMPDRV_Capability = RCC_LCDPUMP_DRV_LEVEL3;
            break;
    }
}

/**
  * @}
  */

/** @defgroup RCC_Group3 Peripheral clocks configuration functions
 *  @brief    Peripheral clocks configuration functions
 *
@verbatim
    ===============================================================================
                #####Peripheral clocks configuration functions #####
    ===============================================================================
    [..] This section provide functions allowing to configure the Peripheral clocks.
         (#) The RTC clock which is derived from the LSE, LSI or  HSE_Div32 (HSE
             divided by 32).
         (#) After restart from Reset or wakeup from STANDBY, all peripherals are off
             except internal SRAM, Flash and SWD. Before to start using a peripheral you
             have to enable its interface clock. You can do this using RCC_AHBPeriphClockCmd(),
             RCC_APB2PeriphClockCmd() and RCC_APB1PeriphClockCmd() functions.
         (#) To reset the peripherals configuration (to the default state after device reset)
             you can use RCC_AHBPeriphResetCmd(), RCC_APB2PeriphResetCmd() and
             RCC_APB1PeriphResetCmd() functions.
@endverbatim
  * @{
  */

/**
  * @brief  Configures the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using PWR_BackupAccessCmd(ENABLE) function before to configure
  *         the RTC clock source (to be done once after reset).
  * @note   Once the RTC clock is configured it can't be changed unless the RTC
  *         is reset using RCC_BackupResetCmd function, or by a Power On Reset.
  * @param  RCC_RTCCLKSource: specifies the RTC clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_RTCCLKSource_MSI: MSI selected as RTC clock
  *            @arg RCC_RTCCLKSource_LSE: LSE selected as RTC clock
  *            @arg RCC_RTCCLKSource_LSI: LSI selected as RTC clock
  *            @arg RCC_RTCCLKSource_HSE_Div32: HSE divided by 32 selected as RTC clock
  * @note   If the LSE or LSI is used as RTC clock source, the RTC continues to
  *         work in STOP and STANDBY modes, and can be used as wakeup source.
  *         However, when the HSE clock is used as RTC clock source, the RTC
  *         cannot be used in STOP and STANDBY modes.
  * @note   The maximum input clock frequency for RTC is 2MHz (when using HSE as
  *         RTC clock source).
  * @retval None
  */
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_RTCCLK_SOURCE(RCC_RTCCLKSource));

    /* Reset RTCSEL[2:0] bits */
    RCC->BDCR &= ~RCC_BDCR_RTC_SEL;

    /* Select the RTC clock source */
    RCC->BDCR |= RCC_RTCCLKSource;
}

/**
  * @brief  Enables or disables the RTC clock.
  * @note   This function must be used only after the RTC clock source was selected
  *         using the RCC_RTCCLKConfig function.
  * @param  NewState: new state of the RTC clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_RTCCLKCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->BDCR |= RCC_BDCR_RTCEN;
    }
    else
    {
        RCC->BDCR &= ~RCC_BDCR_RTCEN;
    }
}

/**
  * @brief  Configures the LCDPUMP Drive capability.
  * @param  RCC_LCDPUMPDRV: specifies the LCDPUMP Drive capability.
  *         This parameter can be one of the following values:
  *            @arg RCC_LCDPUMP_DRV_LEVEL0:  LCDPUMP Drive capability level0
  *            @arg RCC_LCDPUMP_DRV_LEVEL1:  LCDPUMP Drive capability level1
  *            @arg RCC_LCDPUMP_DRV_LEVEL2:  LCDPUMP Drive capability level2
  *            @arg RCC_LCDPUMP_DRV_LEVEL3:  LCDPUMP Drive capability level3 (default)
  *            @arg RCC_LCDPUMP_DRV_LEVEL4:  LCDPUMP Drive capability level4
  *            @arg RCC_LCDPUMP_DRV_LEVEL5:  LCDPUMP Drive capability level5
  *            @arg RCC_LCDPUMP_DRV_LEVEL6:  LCDPUMP Drive capability level6
  *            @arg RCC_LCDPUMP_DRV_LEVEL7:  LCDPUMP Drive capability level7
  * @retval None
  */
void RCC_LCDPUMPDRVConfig(uint32_t RCC_LCDPUMPDRV)
{
    /* Check the parameters */
    assert_param(IS_RCC_LCDPUMPDRV_SOURCE(RCC_LCDPUMPDRV));

    /* Reset LCDPUMPCLK[2:0] bits */
    RCC->BDCR &= ~RCC_BDCR_LCDPUMPDRV;

    /* Select the LCDPUMP clock source */
    RCC->BDCR |= RCC_LCDPUMPDRV;
}

/**
  * @brief  Forces or releases the Backup domain reset.
  *         and the RTC clock source selection in RCC_BDCR register.
  * @param  NewState: new state of the Backup domain reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_BackupResetCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->BDCR |= RCC_BDCR_BDRST;
    }
    else
    {
        RCC->BDCR &= ~RCC_BDCR_BDRST;
    }
}

/**
  * @brief  Enables or disables the AHB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to gates its clock.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_AHBPeriph_TRNG : TRNG clock
  *            @arg RCC_AHBPeriph_CRYPT: CRYPT(AES) clock
  *            @arg RCC_AHBPeriph_GPIOA: GPIOA clock
  *            @arg RCC_AHBPeriph_GPIOB: GPIOB clock
  *            @arg RCC_AHBPeriph_GPIOC: GPIOC clock
  *            @arg RCC_AHBPeriph_GPIOD: GPIOD clock
  *            @arg RCC_AHBPeriph_GPIOF: GPIOF clock
  *            @arg RCC_AHBPeriph_EMACC: EMACC clock
  *            @arg RCC_AHBPeriph_DVSQ:  DVSQ  clock
  *            @arg RCC_AHBPeriph_CRC:   CRC   clock
  *            @arg RCC_AHBPeriph_FLITF: (has effect only when the Flash memory is in power down mode)
  *            @arg RCC_AHBPeriph_SRAM:  SRAM clock
  *            @arg RCC_AHBPeriph_DMA:   DMA clock
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->AHBENR |= RCC_AHBPeriph;
    }
    else
    {
        RCC->AHBENR &= ~RCC_AHBPeriph;
    }
}

/**
  * @brief  Enables or disables the High Speed APB (APB2) peripheral clock.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
  *         However, both APB1 and APB2 clock is APB clok
  *         This parameter can be any combination of the following values:
  *            @arg RCC_APB2Periph_SYSCFG: SYSCFG clock
  *            @arg RCC_APB2Periph_ADC:    ADC clock
  *            @arg RCC_APB2Periph_TIM1:   TIM1 clock
  *            @arg RCC_APB2Periph_SPI1:   SPI1 clock
  *            @arg RCC_APB2Periph_USART1: USART1 clock
  *            @arg RCC_APB2Periph_TIM15:  TIM15 clock
  *            @arg RCC_APB2Periph_TIM16:  TIM16 clock
  *            @arg RCC_APB2Periph_TIM17:  TIM17 clock
  *            @arg RCC_APB2Periph_DBGMCU: DBGMCU clock
  *            @arg RCC_APB2Periph_BEEPER: BEEPER clock
  *            @arg RCC_APB2Periph_OPAMP:  OPAMP clock
  *            @arg RCC_APB2Periph_COMP:   COMP clock
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->APB2ENR |= RCC_APB2Periph;
    }
    else
    {
        RCC->APB2ENR &= ~RCC_APB2Periph;
    }
}

/**
  * @brief  Enables or disables the Low Speed APB (APB1) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to gates its clock.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_APB1Periph_TIM2   : TIM2 clock
  *            @arg RCC_APB1Periph_TIM3   : TIM3 clock
  *            @arg RCC_APB1Periph_TIM14  : TIM14 clock
  *            @arg RCC_APB1Periph_LCD    : LCD clock
  *            @arg RCC_APB1Periph_WWDG   : WWDG clock
  *            @arg RCC_APB1Periph_SPI2   : SPI2 clock
  *            @arg RCC_APB1Periph_USART2 : USART2 clock
  *            @arg RCC_APB1Periph_UART3  : UART3 clock
  *            @arg RCC_APB1Periph_UART4  : UART4 clock
  *            @arg RCC_APB1Periph_I2C1   : I2C1 clock
  *            @arg RCC_APB1Periph_I2C2   : I2C2 clock
  *            @arg RCC_APB1Periph_USB    : USB clock
  *            @arg RCC_APB1Periph_LPUART1: LPUART1 clock
  *            @arg RCC_APB1Periph_CAN    : CAN clock
  *            @arg RCC_APB1Periph_PWR    : PWR clock
  *            @arg RCC_APB1Periph_DAC    : DAC clock
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        LCDENReg |= (RCC_APB1Periph & RCC_APB1Periph_LCD) ;
        RCC->APB1ENR = (RCC->APB1ENR | LCDENReg) | RCC_APB1Periph ;
    }
    else
    {
        LCDENReg &= ~(RCC_APB1Periph & RCC_APB1Periph_LCD) ;
        RCC->APB1ENR = (RCC->APB1ENR | LCDENReg) & ~RCC_APB1Periph ;
    }
}

/**
  * @brief  Forces or releases AHB peripheral reset.
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to reset.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_AHBPeriph_TRNG: TRNG clock
  *            @arg RCC_AHBPeriph_CRYPT: CRYPT clock
  *            @arg RCC_AHBPeriph_GPIOA: GPIOA clock
  *            @arg RCC_AHBPeriph_GPIOB: GPIOB clock
  *            @arg RCC_AHBPeriph_GPIOC: GPIOC clock
  *            @arg RCC_AHBPeriph_GPIOD: GPIOD clock
  *            @arg RCC_AHBPeriph_GPIOF: GPIOF clock
  *            @arg RCC_AHBPeriph_EMACC: EMACC clock
  *            @arg RCC_AHBPeriph_DVSQ:  DVSQ clock
  *            @arg RCC_AHBPeriph_CRC:   CRC clock
  *            @arg RCC_AHBPeriph_DMA:  DMA clock
  * @param  NewState: new state of the specified peripheral reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB_RST_PERIPH(RCC_AHBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->AHBRSTR |= RCC_AHBPeriph;
    }
    else
    {
        RCC->AHBRSTR &= ~RCC_AHBPeriph;
    }
}

/**
  * @brief  Forces or releases High Speed APB (APB2) peripheral reset.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to reset.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_APB2Periph_SYSCFG: SYSCFG clock
  *            @arg RCC_APB2Periph_ADC:    ADC clock
  *            @arg RCC_APB2Periph_TIM1:   TIM1 clock
  *            @arg RCC_APB2Periph_SPI1:   SPI1 clock
  *            @arg RCC_APB2Periph_USART1: USART1 clock
  *            @arg RCC_APB2Periph_TIM15:  TIM15 clock
  *            @arg RCC_APB2Periph_TIM16:  TIM16 clock
  *            @arg RCC_APB2Periph_TIM17:  TIM17 clock
  *            @arg RCC_APB2Periph_DBG:    DBG clock
  *            @arg RCC_APB2Periph_BEEPER: BEEPER clock
  *            @arg RCC_APB2Periph_OPAMP:  OPAMP clock
  *            @arg RCC_APB2Periph_COMP:   COMP clock
  * @param  NewState: new state of the specified peripheral reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB2_RST_PERIPH(RCC_APB2Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->APB2RSTR |= RCC_APB2Periph;
    }
    else
    {
        RCC->APB2RSTR &= ~RCC_APB2Periph;
    }
}

/**
  * @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to reset.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_APB1Periph_TIM2   : TIM2 clock
  *            @arg RCC_APB1Periph_TIM3   : TIM3 clock
  *            @arg RCC_APB1Periph_TIM14  : TIM14 clock
  *            @arg RCC_APB1Periph_LCD    : LCD clock
  *            @arg RCC_APB1Periph_WWDG   : WWDG clock
  *            @arg RCC_APB1Periph_SPI2   : SPI2 clock
  *            @arg RCC_APB1Periph_USART2 : USART2 clock
  *            @arg RCC_APB1Periph_UART3  : UART3 clock
  *            @arg RCC_APB1Periph_UART4  : UART4 clock
  *            @arg RCC_APB1Periph_I2C1   : I2C1 clock
  *            @arg RCC_APB1Periph_I2C2   : I2C2 clock
  *            @arg RCC_APB1Periph_USB    : USB clock
  *            @arg RCC_APB1Periph_LPUART1: LPUART1 clock
  *            @arg RCC_APB1Periph_CAN    : CAN clock
  *            @arg RCC_APB1Periph_PWR    : PWR clock
  *            @arg RCC_APB1Periph_DAC    : DAC clock
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB1_RST_PERIPH(RCC_APB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->APB1RSTR |= RCC_APB1Periph;
    }
    else
    {
        RCC->APB1RSTR &= ~RCC_APB1Periph;
    }
}

/**
  * @}
  */

/** @defgroup RCC_Group4 Interrupts and flags management functions
 *  @brief    Interrupts and flags management functions
 *
@verbatim
 ===============================================================================
             ##### Interrupts and flags management functions #####
 ===============================================================================
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified RCC interrupts.
  * @param  RCC_IT: specifies the RCC interrupt sources to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDY   : LSI ready interrupt
  *            @arg RCC_IT_LSERDY   : LSE ready interrupt
  *            @arg RCC_IT_HSIRDY   : HSI ready interrupt
  *            @arg RCC_IT_HSERDY   : HSE ready interrupt
  *            @arg RCC_IT_PLLRDY   : PLL ready interrupt
  *            @arg RCC_IT_HSI16RDY : HSI16 ready interrupt
  *            @arg RCC_IT_MSIRDY   : MSI ready interrupt
  *            @arg RCC_IT_LSEFAIL  : LSE fail interrupt(need to set CSSON bit can generate interrupt)
  * @param  NewState: new state of the specified RCC interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_IT(RCC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /*Enable the selected interrupts */
        RCC->CIR |= (uint32_t)RCC_IT << 8;
    }
    else
    {
        /*Disable the selected interrupts */
        RCC->CIR &= ~((uint32_t)RCC_IT) << 8;
    }
}

/**
  * @brief  Checks whether the specified RCC flag is set or not.
  * @param  RCC_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg RCC_FLAG_HSIRDY:   HSI oscillator clock ready
  *            @arg RCC_FLAG_HSERDY:   HSE oscillator clock ready
  *            @arg RCC_FLAG_PLLRDY:   PLL clock ready
  *            @arg RCC_FLAG_LSERDY:   LSE oscillator clock ready
  *            @arg RCC_FLAG_LSIRDY:   LSI oscillator clock ready
  *            @arg RCC_FLAG_VCPURSTF: V1.2 power domain reset
  *            @arg RCC_FLAG_OBLRST:   Option Byte Loader (OBL) reset
  *            @arg RCC_FLAG_PINRST:   Pin reset
  *            @arg RCC_FLAG_PORRST:   POR/PDR reset
  *            @arg RCC_FLAG_SFTRST:   Software reset
  *            @arg RCC_FLAG_IWDGRST:  Independent Watchdog reset
  *            @arg RCC_FLAG_WWDGRST:  Window Watchdog reset
  *            @arg RCC_FLAG_LPWRRST:  Low Power reset
  *            @arg RCC_FLAG_HSI16RDY: HSI16 oscillator clock ready
  *            @arg RCC_FLAG_HSI48RDY: HSI48 oscillator clock ready
  *            @arg RCC_FLAG_MSIRDY:   MSI oscillator clock ready
  * @retval The new state of RCC_FLAG (SET or RESET).
  */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG)
{
    uint32_t tmp = 0;
    uint32_t statusreg = 0;
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_RCC_FLAG(RCC_FLAG));

    /* Get the RCC register index */
    tmp = RCC_FLAG >> 5;

    /* The flag to check is in CR register */
    if (tmp == 0)
    {
        statusreg = RCC->CR;
    }
    /* The flag to check is in BDCR register */
    else if (tmp == 1)
    {
        statusreg = RCC->BDCR;
    }
    /* The flag to check is in CSR register */
    else if (tmp == 2)
    {
        statusreg = RCC->CSR;
    }
    /* The flag to check is in CR2 register */
    else
    {
        statusreg = RCC->CR2;
    }

    /* Get the flag position */
    tmp = RCC_FLAG & FLAG_MASK;

    if ((statusreg & ((uint32_t)1 << tmp)) != (uint32_t)RESET)
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
  * @brief  Clears the RCC reset flags.
  *         The reset flags are: RCC_FLAG_OBLRST, RCC_FLAG_PINRST, RCC_FLAG_V18PWRRSTF,
  *         RCC_FLAG_PORRST, RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST,
  *         RCC_FLAG_LPWRRST.
  * @retval None
  */
void RCC_ClearFlag(void)
{
    /* Set RMVF bit to clear the reset flags */
    RCC->CSR |= RCC_CSR_RMVF;
}

/**
  * @brief  Checks whether the specified RCC interrupt has occurred or not.
  * @param  RCC_IT: specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg RCC_IT_LSIRDY  : LSI ready interrupt
  *            @arg RCC_IT_LSERDY  : LSE ready interrupt
  *            @arg RCC_IT_HSIRDY  : HSI ready interrupt
  *            @arg RCC_IT_HSERDY  : HSE ready interrupt
  *            @arg RCC_IT_PLLRDY  : PLL ready interrupt
  *            @arg RCC_IT_HSI16RDY: HSI16 ready interrupt
  *            @arg RCC_IT_MSIRDY  : MSI ready interrupt
  *            @arg RCC_IT_CSSHSE  : HSE Clock Security System
  *            @arg RCC_IT_CSSLSE  : LSE Clock Security System
  * @retval The new state of RCC_IT (SET or RESET).
  */
ITStatus RCC_GetITStatus(uint32_t RCC_IT)
{
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_RCC_GET_IT(RCC_IT));

    /* Check the status of the specified RCC interrupt */
    if ((RCC->CIR & RCC_IT) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the RCC_IT status */
    return  bitstatus;
}

/**
  * @brief  Clears the RCC's interrupt pending bits.
  * @param  RCC_IT: specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDY  : LSI ready interrupt
  *            @arg RCC_IT_LSERDY  : LSE ready interrupt
  *            @arg RCC_IT_HSIRDY  : HSI ready interrupt
  *            @arg RCC_IT_HSERDY  : HSE ready interrupt
  *            @arg RCC_IT_PLLRDY  : PLL ready interrupt
  *            @arg RCC_IT_HSI16RDY: HSI16 ready interrupt
  *            @arg RCC_IT_MSIRDY  : MSI ready interrupt
  *            @arg RCC_IT_CSSHSE  : HSE Clock Security System
  *            @arg RCC_IT_CSSLSE  : LSE Clock Security System
  * @retval None
  */
void RCC_ClearITPendingBit(uint32_t RCC_IT)
{
    /* Check the parameters */
    assert_param(IS_RCC_CLEAR_IT(RCC_IT));

    if (RCC_IT == RCC_IT_CSSLSE)
    {
        /* Clear CSSLSE pending bits */
        RCC->CIR |= (uint32_t)RCC_IT << 1;

    }

    /* Clear the selected interrupt pending bits */
    RCC->CIR |= (uint32_t)RCC_IT << 16;
}

/**
  * @brief  Adjusts the CSS counter threshold control.
  * @note   After the CSS function is enabled, RCC uses the HSI clock to sample the HSE frequency division waveform.
  *         If the FREQUENCY of HSE input is very low, CSS outages can be triggered even when the HSE is still working.
  *         You can adjust the value through CSS_THRESHOLD[6:0] to avoid. When different thresholds are configured,
  *         the lowest HSE frequency determined by the CSS is about 4M/ CSS_THRESHOLD[6:0].
  * @param  CSS_THRESHOLD_Value: specifies the CSS counter threshold control value.
  *         This parameter must be a number between 0 and 0x3F.
  * @retval None
  */
void RCC_CSSThresholdConfig(uint8_t CSS_THRESHOLD_Value)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_CSS_THRESHOLD_Value(CSS_THRESHOLD_Value));

    tmpreg = RCC->HSECTL ;

    /* Clear CSS_THRESHOLD[6:0] bits */
    tmpreg &= ~RCC_HSECTL_CSS_THRESHOLD;

    /* Set CSS_THRESHOLD[6:0] bits */
    tmpreg |= (uint32_t)CSS_THRESHOLD_Value << 25 ;

    /* Store the new value */
    RCC->HSECTL = tmpreg;
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

