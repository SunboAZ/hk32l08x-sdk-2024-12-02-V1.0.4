/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_lcd.c
* @brief:     This file provides all the DMA firmware functions.
* @author:    AE Team
* @version:   V1.0.0/2023-10-18
*             1.Initial version
* @verbatim
  ===============================================================================
                       ##### How to use this driver #####
  ===============================================================================
    [..]
         (#) Enable peripheral clock using RCC_LCDCLKCmd(ENABLE) function for LCD.
                 (#)    Enable clock using RCC_LCDPUMPCLKConfig() function for LCD chargepump.
         (#) The LCD peripherals are initialized by the LCD Init() function.
                         (##) Set LCD Bias and duty.
                         (##) Set the LCD Prescaler,Divider and Contrast.
                 (#) Use the LCD_VoltageSource function to select the LCD VoltageSource.
                 (#) Use the flicker mode using the LCD_BlinkModeCmd() function and the
                         LCD_BlinkFrequencyConfig () function to configure the flicker frequency.
                 (#) To use interrupts, enable the LCD ITConfig() function.
    [..] LCD and low power modes: The LCD remain active during STOP mode.
    @endverbatim
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_lcd.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup LCD  LCD
  * @brief LCD driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup LCD_Private_Defines  LCD_Private_Defines
  * @{
  */
#define SYNCHRO_TIMEOUT          ((uint32_t) 0x00008000)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup LCD_Private_Functions LCD_Private_Functions
  * @{
  */

/** @defgroup LCD_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
          ##### Initialization and Configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */


/**
  * @brief  Initializes the LCD peripheral according to the specified
  *         parameters in the LCD_InitStruct .
  * @param  LCD_InitStruct: pointer to a LCD_InitTypeDef structure that contains
  *         the configuration information for the specified LCD peripheral.
  * @retval None
  */
void LCD_Init(LCD_InitTypeDef *LCD_InitStruct)
{
    /* Check the parameters */
    assert_param(IS_LCD_PRESCALER(LCD_InitStruct->LCD_Prescaler));
    assert_param(IS_LCD_DIVIDER(LCD_InitStruct->LCD_Divider));
    assert_param(IS_LCD_DUTY(LCD_InitStruct->LCD_Duty));//
    assert_param(IS_LCD_BIAS(LCD_InitStruct->LCD_Bias)); //
    assert_param(IS_LCD_CONTRAST(LCD_InitStruct->LCD_Contrast));

    /*Disable LCD*/
    LCD->CR &= ~(LCD_CR_LCDEN);

    LCD->CR = LCD_InitStruct->LCD_Duty | LCD_InitStruct->LCD_Bias;

    LCD->FCR = LCD_InitStruct->LCD_Prescaler | LCD_InitStruct->LCD_Divider | LCD_InitStruct->LCD_Contrast;
}



/**
  * @brief  Mux segment enable.
  * @param  NewState: new state of the specified mux segment.
  *         This parameter can be:ENABLE or DISABLE.
  * @retval None
  */
void LCD_MuxSegentCmd(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        LCD->CR |= LCD_CR_MUX_SEG;
    }
    else
    {
        LCD->CR &= ~(LCD_CR_MUX_SEG);
    }
}


/**
  * @brief  Select the specified LCD voltage source.
  * @param  Voltage_Source: specifies voltage source.
  *         This parameter can be one of the following values:
  *            @arg LCD_VOLTAGESOURCE_INTERNAL:internal lcd voltage source.
  * @retval None
  */
void LCD_VoltageSource(uint8_t Voltage_Source)
{
    assert_param(IS_LCD_VOLTAGE_SOURCE(Voltage_Source));

    LCD->CR &= ~(LCD_CR_VSEL);

    LCD->CR |= Voltage_Source;
}

/**
  * @brief  Configures the specified bias voltage.
  * @param  Bias: Specifies the bias voltage.
  *         This parameter can be one of the following values:
  *            @arg LCD_BIAS_1_4
  *            @arg LCD_BIAS_1_3
  *            @arg LCD_BIAS_1_2
  * @retval None
  */
void LCD_BiasConfg(uint8_t Bias)
{
    assert_param(IS_LCD_BIAS(Bias));

    LCD->CR &= ~LCD_CR_BIAS;

    LCD->CR |= Bias;
}

/**
  * @brief  Configures the specified duty.
  * @param  Duty: Specifies the bias voltage.
  *         This parameter can be one of the following values:
  *            @arg LCD_DUTY_STATIC
  *            @arg LCD_DUTY_1_2
  *            @arg LCD_DUTY_1_3
  *            @arg LCD_DUTY_1_4
  *            @arg LCD_DUTY_1_8
  * @retval None
  */
void LCD_DutyConfig(uint8_t Duty)
{
    assert_param(IS_LCD_DUTY(Duty));

    LCD->CR &= ~(LCD_CR_DUTY);

    LCD->CR |= Duty;
}

/**
  * @brief  Enables or disables the specified LCD peripheral.
  * @param  NewState: new state of the LCD peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LCD_Cmd(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        LCD->CR |= LCD_CR_LCDEN;
    }
    else
    {
        LCD->CR &= ~(LCD_CR_LCDEN);
    }
}


/**
  * @brief  Set the LCD predivision frequency.
  * @param  Prescaler: Frequency division
  *         This parameter can be one of the following values:
  *            @arg LCD_PRESCALER_1
  *            @arg LCD_PRESCALER_2
  *            @arg LCD_PRESCALER_4
  *            @arg LCD_PRESCALER_8
  *            @arg LCD_PRESCALER_16
  *            @arg LCD_PRESCALER_32
  *            @arg LCD_PRESCALER_64
  *            @arg LCD_PRESCALER_128
  *            @arg LCD_PRESCALER_256
  *            @arg LCD_PRESCALER_512
  *            @arg LCD_PRESCALER_1024
  *            @arg LCD_PRESCALER_2048
  *            @arg LCD_PRESCALER_4096
  *            @arg LCD_PRESCALER_8192
  *            @arg LCD_PRESCALER_16384
  *            @arg LCD_PRESCALER_32768
  * @retval None
  */
void LCD_SetPrescaler(uint32_t Prescaler)
{
    assert_param(IS_LCD_PRESCALER(Prescaler));

    LCD->FCR &= ~(LCD_FCR_PS);

    LCD->FCR |= Prescaler;
}


/**
  * @brief  Set the LCD Divider.
  * @param  Divider_value: The value of divider.
  *         This parameter can be one of the following values:
  *            @arg LCD_DIVIDER_16
  *            @arg LCD_DIVIDER_17
  *            @arg LCD_DIVIDER_18
  *            @arg LCD_DIVIDER_19
  *            @arg LCD_DIVIDER_20
  *            @arg LCD_DIVIDER_21
  *            @arg LCD_DIVIDER_22
  *            @arg LCD_DIVIDER_23
  *            @arg LCD_DIVIDER_24
  *            @arg LCD_DIVIDER_25
  *            @arg LCD_DIVIDER_26
  *            @arg LCD_DIVIDER_27
  *            @arg LCD_DIVIDER_28
  *            @arg LCD_DIVIDER_29
  *            @arg LCD_DIVIDER_30
  *            @arg LCD_DIVIDER_31
  * @retval None
  */
void LCD_SetDivider(uint32_t Divider_value)
{
    assert_param(IS_LCD_DIVIDER(Divider_value));

    LCD->FCR &= ~(LCD_FCR_DIV);

    LCD->FCR |= Divider_value;

}

/**
  * @brief  Select pulse duration.
  * @param  DURATION: Pulse ON duration.
  *         This parameter can be one of the following values:
  *            @arg LCD_PULSEONDURATION_0
  *            @arg LCD_PULSEONDURATION_1
  *            @arg LCD_PULSEONDURATION_2
  *            @arg LCD_PULSEONDURATION_3
  *            @arg LCD_PULSEONDURATION_4
  *            @arg LCD_PULSEONDURATION_5
  *            @arg LCD_PULSEONDURATION_6
  *            @arg LCD_PULSEONDURATION_7
  * @retval None
  */
void LCD_PulseOnDuration(uint32_t DURATION)
{
    assert_param(IS_LCD_PULSE_ON_DURATION(DURATION));

    LCD->FCR |= DURATION;
}

/**
  * @}
  */

/** @defgroup LCD_Group2 Blink mode
 *  @brief   blink functions
 *
@verbatim
 ===============================================================================
                       ##### Blink mode #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Enable the blink mode of the LCD peripheral.
  * @param  Num: Select the number of blink pins.
  *         This parameter can be one of the following values:
  *            @arg LCD_BLINKMODE_OFF
  *            @arg LCD_BLINKMODE_SEG0_COM0
  *            @arg LCD_BLINKMODE_SEG0_ALLCOM
  * @param  NewState: new state of the selected LCD blink mode.
  *         This parameter can be:ENABLE or DISABLE.
  * @retval None
  */
void LCD_BlinkModeCmd(uint32_t Num, FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_LCD_BLINK_MODE(Num));


    if (NewState == ENABLE)
    {
        LCD->FCR |= Num;
    }
    else
    {
        LCD->FCR &= ~(LCD_FCR_BLINK);
    }
}


/**
  * @brief  Set the frequency of the LCD blinking mode.
  * @param  BlinkFrequency: Select the blinking frequency of the LCD.
  *         This parameter can be one of the following values:
  *            @arg LCD_BLINKFREQUENCY_DIV8
  *            @arg LCD_BLINKFREQUENCY_DIV16
  *            @arg LCD_BLINKFREQUENCY_DIV32
  *            @arg LCD_BLINKFREQUENCY_DIV64
  *            @arg LCD_BLINKFREQUENCY_DIV128
  *            @arg LCD_BLINKFREQUENCY_DIV256
  *            @arg LCD_BLINKFREQUENCY_DIV512
  *            @arg LCD_BLINKFREQUENCY_DIV1024
  * @retval None
  */
void LCD_BlinkFrequencyConfig(uint32_t BlinkFrequency)
{
    assert_param(IS_LCD_BLINK_FREQUENCY(BlinkFrequency));

    LCD->FCR &= ~(LCD_FCR_BLINKF);

    LCD->FCR |= BlinkFrequency;
}

/**
  * @}
  */


/** @defgroup LCD_Group3 contrast control
 *  @brief   contrast control
 *
@verbatim
 ===============================================================================
                       ##### contrast control #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Set the dead time of the LCD.
  * @param  DeadTime: Select the blinking frequency of the LCD.
  *         This parameter can be one of the following values:
  *            @arg LCD_DEADTIME_0
  *            @arg LCD_DEADTIME_1
  *            @arg LCD_DEADTIME_2
  *            @arg LCD_DEADTIME_3
  *            @arg LCD_DEADTIME_4
  *            @arg LCD_DEADTIME_5
  *            @arg LCD_DEADTIME_6
  *            @arg LCD_DEADTIME_7
  * @retval None
  */
void LCD_SetDeadTime(uint32_t DeadTime)
{
    assert_param(IS_LCD_DEAD_TIME(DeadTime));

    LCD->FCR &= ~(LCD_FCR_DEAD);

    LCD->FCR |= DeadTime;
}

/**
  * @brief  Set the Contrast of the LCD blinking mode.
  * @param  Contrast: Select the LCD contrast voltage.
  *         This parameter can be one of the following values:
  *            @arg LCD_CONTRASTLEVEL_0
  *            @arg LCD_CONTRASTLEVEL_1
  *            @arg LCD_CONTRASTLEVEL_2
  *            @arg LCD_CONTRASTLEVEL_3
  *            @arg LCD_CONTRASTLEVEL_4
  *            @arg LCD_CONTRASTLEVEL_5
  *            @arg LCD_CONTRASTLEVEL_6
  *            @arg LCD_CONTRASTLEVEL_7
  * @retval None
  */
void LCD_SetContrast(uint32_t Contrast)
{
    assert_param(IS_LCD_CONTRAST(Contrast));


    //clear CC[2:0]
    LCD->FCR &= ~(LCD_FCR_CC);


    LCD->FCR |= Contrast;
}

/**
  * @}
  */



/** @defgroup LCD_Group4 high drive
 *  @brief   high drive
 *
@verbatim
 ===============================================================================
                       ##### high drive #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified LCD middle drive.
  * @param  NewState: new state of the specified LCD drive.
  *         This parameter can be:ENABLE or DISABLE.
  * @retval None
  */
void LCD_MiddleDriveCmd(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if ( NewState == ENABLE )
    {
        LCD->FCR |= LCD_FCR_MD;
    }
    else
    {
        LCD->FCR &= ~LCD_FCR_MD;
    }
}


/**
  * @brief  Enables or disables the specified LCD high drive.
  * @param  NewState: new state of the specified LCD drive.
  *         This parameter can be:ENABLE or DISABLE.
  * @retval None
  */
void LCD_HighDriveCmd(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if ( NewState == ENABLE )
    {
        LCD->FCR |= (LCD_FCR_HD | LCD_FCR_MD);
    }
    else
    {
        LCD->FCR &= ~(LCD_FCR_HD | LCD_FCR_MD);
    }
}

/**
  * @}
  */


/** @defgroup LCD_Group5 LCD interrupt
 *  @brief   LCD interrupt
 *
@verbatim
 ===============================================================================
                       ##### LCD interrupt #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified LCD interrupts.
  * @param  LCD_IT: specifies the LCD interrupt sources to be enabled or disabled.
  *         This parameter can be one of the following values:
  *            @arg LCD_IT_SOF:Start of frame interrupt.
  *            @arg LCD_IT_UDD:Update Display Done interrupt
  * @param  NewState: new state of the specified LCD interrupts.
  *         This parameter can be:ENABLE or DISABLE.
  * @retval None
  */
void LCD_ITConfig(uint32_t LCD_IT, FunctionalState NewState)
{
    assert_param(IS_LCD_CONFIG_IT(LCD_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if ( NewState == ENABLE )
    {
        LCD->FCR |= LCD_IT;
    }
    else
    {
        LCD->FCR &= ~(LCD_IT);
    }
}

/**
  * @}
  */


/** @defgroup LCD_Group6 Write RAM
 *  @brief   Write RAM
 *
@verbatim
 ===============================================================================
                       ##### Write RAM #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Write data to LCD RAM.
  * @param  COM: LCD display memory.
  *         This parameter can be one of the following values:
  *            @arg LCD_RAM_COM0
  *            @arg LCD_RAM_COM1
  *            @arg LCD_RAM_COM2
  *            @arg LCD_RAM_COM3
  *            @arg LCD_RAM_COM4
  *            @arg LCD_RAM_COM5
  *            @arg LCD_RAM_COM6
  *            @arg LCD_RAM_COM7
  * @param  DATA:  Data to be written to RAM.
  * @retval None
  */
void LCD_WrietNoMask(uint32_t COM, uint32_t DATA)
{
    assert_param(IS_LCD_RAM_COM(COM));

    switch (COM)
    {
        case 0:
            LCD->RAM0 = DATA;
            break;

        case 1:
            LCD->RAM2 = DATA;
            break;

        case 2:
            LCD->RAM4 = DATA;
            break;

        case 3:
            LCD->RAM6 = DATA;
            break;

        case 4:
            LCD->RAM8 = DATA;
            break;

        case 5:
            LCD->RAM10 = DATA;
            break;

        case 6:
            LCD->RAM12 = DATA;
            break;

        case 7:
            LCD->RAM14 = DATA;
            break;

        default:
            break;

    }
}

/**
  * @brief  Write data to LCD RAM with mask.
  * @param  COM: LCD display memory.
  *         This parameter can be one of the following values:
  *            @arg LCD_RAM_COM0
  *            @arg LCD_RAM_COM1
  *            @arg LCD_RAM_COM2
  *            @arg LCD_RAM_COM3
  *            @arg LCD_RAM_COM4
  *            @arg LCD_RAM_COM5
  *            @arg LCD_RAM_COM6
  *            @arg LCD_RAM_COM7
  * @param  DATA: Data to be written to RAM.
  * @retval None
  */
void LCD_WriteMask(uint32_t COM, uint32_t DATA)
{
    uint32_t temp[8] = {0};

    temp[0] = LCD->RAM0;
    temp[1] = LCD->RAM2;
    temp[2] = LCD->RAM4;
    temp[3] = LCD->RAM6;
    temp[4] = LCD->RAM8;
    temp[5] = LCD->RAM10;
    temp[6] = LCD->RAM12;
    temp[7] = LCD->RAM14;

    switch (COM)
    {
        case 0:
            LCD->RAM0 = DATA | temp[0];
            break;

        case 1:
            LCD->RAM2 = DATA | temp[1];
            break;

        case 2:
            LCD->RAM4 = DATA | temp[2];
            break;

        case 3:
            LCD->RAM6 = DATA | temp[3];
            break;

        case 4:
            LCD->RAM8 = DATA | temp[4];
            break;

        case 5:
            LCD->RAM10 = DATA | temp[5];
            break;

        case 6:
            LCD->RAM12 = DATA | temp[6];
            break;

        case 7:
            LCD->RAM14 = DATA | temp[7];
            break;

        default:
            break;

    }
}

/**
  * @}
  */


/** @defgroup LCD_Group7 Update display
 *  @brief   Update display
 *
@verbatim
 ===============================================================================
                       ##### Update display #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  LCD updates the display request.
  * @retval None
  */
void LCD_UpdateDisplayRequest(void)
{
    LCD->SR |= LCD_SR_UDR;

    while ((LCD->SR & LCD_FLAG_UDD) == RESET)
    {
    }
}

/**
  * @}
  */



/** @defgroup LCD_Group8 Flag management
 *  @brief   Flag management
 *
@verbatim
 ===============================================================================
                       ##### Flag management #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Checks whether the specified LCD flag is set or not.
  * @param  LCD_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg LCD_FLAG_ENS:LCD enabled status.
  *            @arg LCD_FLAG_SOF:Start of frame interrupt.
  *            @arg LCD_FLAG_UDR:Update display request.
  *            @arg LCD_FLAG_UDD:Update display Done .
  *            @arg LCD_FLAG_RDY:Rdedy flag.
  *            @arg LCD_FLAG_FCRSF:LCD frame control register synchronization flag.
  * @retval None
  */
FlagStatus LCD_GetFlagStatus(uint32_t LCD_FLAG)
{
    FlagStatus bitstatus = RESET;

    assert_param(IS_LCD_FLAG(LCD_FLAG));

    if ((LCD->SR & LCD_FLAG) != 0)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * @brief  Clears the LCD's pending flags.
  * @param  LCD_FLAG: specifies the LCD interrupt sources to be enabled or disabled.
  *         This parameter can be one of the following values:
  *            @arg LCD_FLAG_SOF:Start of frame interrupt.
  *            @arg LCD_FLAG_UDD:Update Display Done interrupt
  * @retval None
  */
void LCD_ClearFlag( uint32_t LCD_FLAG)
{
    /* Check the parameters */
    assert_param(IS_LCD_FLAG(LCD_FLAG));

    LCD->CLR = LCD_FLAG;
}


/**
  * @}
  */



/** @defgroup LCD_Group9 LCD COM/SEG Enable
 *  @brief   LCD_Group9 LCD COM/SEG Enable
 *
@verbatim
 ===============================================================================
                       ##### LCD COM/SEG Enable #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified LCD COM.
  * @param  ComNumber: specifies the LCD COM to be enabled or disabled.
  *         This parameter can be 0~0xff.
  * @param  NewState: new state of the specified LCD interrupts.
  *         This parameter can be:ENABLE or DISABLE.
  * @retval None
  */
void LCD_ComEnable(uint8_t ComNumber, FunctionalState NewState)
{
    if ( ENABLE == NewState )
    {
        LCD->COMENR |= ComNumber;
    }
    else
    {
        LCD->COMENR &= ~ComNumber;
    }
}



/**
  * @brief  Enables or disables the specified LCD Segment.
  * @param  SegNumber: specifies the LCD SEG  to be enabled or disabled.
  *         This parameter can be 0~0xffffffff.
  * @param  NewState: new state of the specified LCD interrupts.
  *         This parameter can be:ENABLE or DISABLE.
  * @retval None
  */
void LCD_SegEnable(uint32_t SegNumber, FunctionalState NewState)
{
    if ( ENABLE == NewState )
    {
        LCD->SEGENR0 |= SegNumber;
    }
    else
    {
        LCD->SEGENR0 &= ~SegNumber;
    }
}

/**
  * @brief  Waits until the LCD FCR register is synchronized in the LCDCLK domain.
  *         This function must be called after any write operation to LCD_FCR register.
  * @retval None
  */
void LCD_WaitForSynchro(void)
{
    uint32_t synchrocounter = 0;
    uint32_t synchrostatus = 0x00;

    /* Loop until FCRSF flag is set */
    do
    {
        synchrostatus = LCD->SR & LCD_FLAG_FCRSF;
        synchrocounter++;
    } while ((synchrocounter != SYNCHRO_TIMEOUT) && (synchrostatus == 0x00));
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

