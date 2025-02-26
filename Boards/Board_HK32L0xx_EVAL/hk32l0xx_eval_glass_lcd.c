/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_eval_glass_lcd.c
* @brief:     hk32l0xx lcd driver
* @author:    AE Team
* @version:   V1.0.0/2024-01-12
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_eval_glass_lcd.h"


/** @addtogroup Boards
  * @{
  */

/** @addtogroup HK32_EVAL
  * @{
  */


/** @defgroup HK32L0XX_EVAL_GLASS_LCD
  * @brief This file includes the LCD Glass driver for Pacific Display
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/** @defgroup HK32L0XX_EVAL_GLASS_LCD_Private_Types
  * @{
  */
typedef union
{
    struct
    {
        uint8_t segmentA;
        uint8_t segmentB;
        uint8_t segmentC;
        uint8_t segmentD;
        uint8_t segmentE;
        uint8_t segmentF;
        uint8_t segmentG;
    } seg;
    uint8_t segArray[DIGIT_NUMBER_SEG];
} DIGIT_Type;
/**
  * @}
  */

/* Private define ------------------------------------------------------------*/
/** @defgroup HK32L0XX_EVAL_GLASS_LCD_Private_Defines
  * @{
  */
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup HK32L0XX_EVAL_GLASS_LCD_Private_Macros
  * @{
  */
#define UPDATE_DELAY        1000
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup HK32L0XX_EVAL_GLASS_LCD_Private_Variables
  * @{
  */
/*LcdRamBuffer[0] Used for COM0*/
/*LcdRamBuffer[1] Used for COM1*/
/*LcdRamBuffer[2] Used for COM2*/
/*LcdRamBuffer[3] Used for COM3*/
static uint32_t LcdRamBuffer[4] = {0, 0, 0, 0};
static uint16_t LcdNumberMap[] =
{
    _LCD_1A,  _LCD_1B,  _LCD_1C,  _LCD_1D,  _LCD_1E,  _LCD_1F,  _LCD_1G,
    _LCD_2A,  _LCD_2B,  _LCD_2C,  _LCD_2D,  _LCD_2E,  _LCD_2F,  _LCD_2G,
    _LCD_3A,  _LCD_3B,  _LCD_3C,  _LCD_3D,  _LCD_3E,  _LCD_3F,  _LCD_3G,
    _LCD_4A,  _LCD_4B,  _LCD_4C,  _LCD_4D,  _LCD_4E,  _LCD_4F,  _LCD_4G,
    _LCD_5A,  _LCD_5B,  _LCD_5C,  _LCD_5D,  _LCD_5E,  _LCD_5F,  _LCD_5G,
    _LCD_6A,  _LCD_6B,  _LCD_6C,  _LCD_6D,  _LCD_6E,  _LCD_6F,  _LCD_6G,
    _LCD_7A,  _LCD_7B,  _LCD_7C,  _LCD_7D,  _LCD_7E,  _LCD_7F,  _LCD_7G,
    _LCD_8A,  _LCD_8B,  _LCD_8C,  _LCD_8D,  _LCD_8E,  _LCD_8F,  _LCD_8G,
    _LCD_9A,  _LCD_9B,  _LCD_9C,  _LCD_9D,  _LCD_9E,  _LCD_9F,  _LCD_9G,
    _LCD_10A, _LCD_10B, _LCD_10C, _LCD_10D, _LCD_10E, _LCD_10F, _LCD_10G,
};

DIGIT_Type  DigitSeg;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */


/** @defgroup HK32L0XX_EVAL_LCD_Private_Function_Prototypes
  * @{
  */
static void delay(__IO uint32_t nCount);
static void LCD_GPIOConfig(void);

/**
  * @}
  */

/** @defgroup HK32L0XX_EVAL_LCD_Private_Functions
  * @{
  */

/**
  * @brief  Configures the LCD GLASS relative GPIO port IOs and LCD peripheral.
  * @param  None
  * @retval None
  */
void LCD_GlassInit(void)
{
    LCD_InitTypeDef LCD_InitStructure;

    LCD_GPIOConfig(); /*!< Configure the LCD Glass GPIO pins */

    /*!< Configure the LCD interface -------------------------------------------*/
    /*!< Enable LCD APB1 Clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_LCD, ENABLE);

    LCD_InitStructure.LCD_Prescaler = LCD_PRESCALER_8;
    LCD_InitStructure.LCD_Divider = LCD_DIVIDER_16;
    LCD_InitStructure.LCD_Duty = LCD_DUTY_1_4;
    LCD_InitStructure.LCD_Bias = LCD_BIAS_1_3;
    LCD_InitStructure.LCD_Contrast = LCD_CONTRASTLEVEL_2;
    LCD_Init(&LCD_InitStructure);

    /*!< Configure the Pulse On Duration */
    LCD_PulseOnDuration(LCD_PULSEONDURATION_2);

    /*!< Configure the LCD Contrast (3.51V) */
    LCD_SetContrast(LCD_CONTRASTLEVEL_7);

    /*!< Wait Until the LCD FCR register is synchronized */
    LCD_WaitForSynchro();

    /*!< enable COM0~COM3 */
    LCD_ComEnable(0x0F, ENABLE);

    /*!< enable SEG0~SEG31 */
    LCD_SegEnable(0xFFFFFFFF, ENABLE);

    /*!< Enable LCD peripheral */
    LCD_Cmd(ENABLE);

    /*!< Wait Until the LCD is enabled */
    while (LCD_GetFlagStatus(LCD_FLAG_ENS) == RESET)
    {
    }

    /*!< Wait Until the LCD Booster is ready */
    while (LCD_GetFlagStatus(LCD_FLAG_RDY) == RESET)
    {
    }
}

/**
  * @brief  clear lcd.
  * @retval None
  */
void LCD_GlassClear(void)
{
    LCD_WrietNoMask(LCD_RAM_COM0, 0x0);
    LCD_WrietNoMask(LCD_RAM_COM1, 0x0);
    LCD_WrietNoMask(LCD_RAM_COM2, 0x0);
    LCD_WrietNoMask(LCD_RAM_COM3, 0x0);
    LCD_UpdateDisplayRequest();
    delay(UPDATE_DELAY);
}

/**
  * @brief  Displays a segment code.
  * @param  SegNum: the segment num.
  *         This parameter can be: 0~0xff, Specific meaning reference hk32l0xx_eval_glass_lcd.h.
  *         for example: _LCD_HK_LOGO is 31, use this parameter can show hk icon.
  * @retval None
  */
void LCD_GlassDisplaySeg(uint8_t SegNum)
{
    uint8_t SegBit;

    if (SegNum < 32)
    {
        SegBit = SegNum;
        LcdRamBuffer[0] |= (1 << SegBit);
    }
    else if (SegNum < 64)
    {
        SegBit = SegNum - 32;
        LcdRamBuffer[1] |= (1 << SegBit);
    }
    else if (SegNum < 96)
    {
        SegBit = SegNum - 64;
        LcdRamBuffer[2] |= (1 << SegBit);
    }
    else if (SegNum < 128)
    {
        SegBit = SegNum - 96;
        LcdRamBuffer[3] |= (1 << SegBit);
    }
}

/**
  * @brief  Clear a segment code.
  * @param  SegNum: the segment num.
  *         This parameter can be: 0~0xff, Specific meaning reference hk32l0xx_eval_Glasslcd.h.
  *         for example: _LCD_HK_LOGO is 31, use this parameter can clear hk icon.
  * @retval None
  */
void LCD_GlassClearSeg(uint8_t SegNum)
{
    uint8_t SegBit;

    if (SegNum < 32)
    {
        SegBit = SegNum;
        LcdRamBuffer[0] &= ~(1 << SegBit);
    }
    else if (SegNum < 64)
    {
        SegBit = SegNum - 32;
        LcdRamBuffer[1] &= ~(1 << SegBit);
    }
    else if (SegNum < 96)
    {
        SegBit = SegNum - 64;
        LcdRamBuffer[2] &= ~(1 << SegBit);
    }
    else if (SegNum < 128)
    {
        SegBit = SegNum - 96;
        LcdRamBuffer[3] &= ~(1 << SegBit);
    }
}

/**
  * @brief  Displays a number.
  * @param  Digit: the digit number.
  *         This parameter can be: 0~9, ohter value used for clear the shadow.
  * @param  Position: the digit num position.
  *         This parameter can be: 1~10, 1~6 mean big digit number, 7~10 mean small digit number.
  * @retval None
  */
void LCD_GlassDisplayDigit(unsigned char Digit, unsigned char Position)
{
    uint8_t cnt = 0;

    for (cnt = 0; cnt < DIGIT_NUMBER_SEG; cnt++)
    {
        LCD_GlassClearSeg(LcdNumberMap[(Position - 1) * DIGIT_NUMBER_SEG + cnt]);
        DigitSeg.segArray[cnt] =  LcdNumberMap[(Position - 1) * DIGIT_NUMBER_SEG + cnt];
    }

    switch (Digit)
    {
        case 0:
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentA);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentB);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentC);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentD);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentE);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentF);
            break;

        case 1:
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentB);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentC);
            break;

        case 2:
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentA);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentB);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentD);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentE);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentG);
            break;

        case 3:
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentA);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentB);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentC);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentD);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentG);
            break;

        case 4:
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentB);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentC);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentF);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentG);
            break;

        case 5:
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentA);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentC);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentD);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentF);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentG);
            break;

        case 6:
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentA);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentC);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentD);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentE);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentF);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentG);
            break;

        case 7:
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentA);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentB);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentC);
            break;

        case 8:
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentA);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentB);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentC);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentD);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentE);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentF);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentG);
            break;

        case 9:
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentA);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentB);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentC);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentD);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentF);
            LCD_GlassDisplaySeg(DigitSeg.seg.segmentG);
            break;

        default:
            break;
    }
}

/**
  * @brief  Displays a int number on big digit number area.
  * @param  Value: the digit int number.
  *         This parameter can be: -999999~999999.
  * @retval None
  */
void LCD_GlassDisplayIntOnBigNumArea(int Value)
{
    unsigned char i = 0;
    unsigned char DispBuff[6] = {0};

    /* Deal with negative numbers */
    if (Value < 0)
    {
        Value = -Value;
        LCD_GlassDisplaySeg(_LCD_NEG);
    }
    else
    {
        LCD_GlassClearSeg(_LCD_NEG);
    }


    for (i = 0; i < 6; i++)
    {
        DispBuff[i] = Value % 10;
        Value /= 10;
    }

    /* eliminate invalid "0" */
    for (i = 5; i > 0; i--)
    {
        if (DispBuff[i] == 0)
        {
            DispBuff[i] = 10;
        }
        else
        {
            break;
        }
    }

    for (i = 0; i < 6; i++)
    {
        LCD_GlassDisplayDigit(DispBuff[i], 6 - i);
    }
}

/**
  * @brief  Displays a int number on big digit number area.
  * @param  Value: the digit number.
  *         This parameter can be: -999999~999999.
  * @param  NumOfDecimal: the decimal bit location.
  *         This parameter can be: 1~6.
  * @retval None
  */
void LCD_GlassDisplayFloatOnBigNumArea(float Value, uint8_t NumOfDecimal)
{
    uint32_t NumTmp;

    /* Clear the decimal point */
    LCD_GlassClearSeg(_LCD_DOT3);
    LCD_GlassClearSeg(_LCD_DOT4);
    LCD_GlassClearSeg(_LCD_DOT5);
    LCD_GlassClearSeg(_LCD_DOT6);

    if (NumOfDecimal < 6)
    {
        switch (NumOfDecimal)
        {
            case 0:
                NumTmp = (uint32_t)Value;
                LCD_GlassDisplayIntOnBigNumArea(NumTmp);
                break;

            case 1:
                NumTmp = (uint32_t)(Value * 10);
                LCD_GlassDisplayIntOnBigNumArea(NumTmp);
                LCD_GlassDisplaySeg(_LCD_DOT6);

                if (Value < 1)
                {
                    LCD_GlassDisplayDigit(0, 5);
                }

                break;

            case 2:
                NumTmp = (uint32_t)(Value * 100);
                LCD_GlassDisplayIntOnBigNumArea(NumTmp);
                LCD_GlassDisplaySeg(_LCD_DOT5);

                if (Value < 1)
                {
                    LCD_GlassDisplayDigit(0, 4);
                }

                if (Value < 0.1)
                {
                    LCD_GlassDisplayDigit(0, 5);
                }

                break;

            case 3:
                NumTmp = (uint32_t)(Value * 1000);
                LCD_GlassDisplayIntOnBigNumArea(NumTmp);
                LCD_GlassDisplaySeg(_LCD_DOT4);

                if (Value < 1)
                {
                    LCD_GlassDisplayDigit(0, 3);
                }

                if (Value < 0.1)
                {
                    LCD_GlassDisplayDigit(0, 4);
                }

                if (Value < 0.01)
                {
                    LCD_GlassDisplayDigit(0, 5);
                }

                break;

            case 4:
                NumTmp = (uint32_t)(Value * 10000);
                LCD_GlassDisplayIntOnBigNumArea(NumTmp);
                LCD_GlassDisplaySeg(_LCD_DOT3);

                if (Value < 1)
                {
                    LCD_GlassDisplayDigit(0, 2);
                }

                if (Value < 0.1)
                {
                    LCD_GlassDisplayDigit(0, 3);
                }

                if (Value < 0.01)
                {
                    LCD_GlassDisplayDigit(0, 4);
                }

                if (Value < 0.001)
                {
                    LCD_GlassDisplayDigit(0, 5);
                }

                break;

            case 5:
                NumTmp = (uint32_t)(Value * 100000);
                LCD_GlassDisplayIntOnBigNumArea(NumTmp);
                LCD_GlassDisplaySeg(_LCD_DOT2);

                if (Value < 1)
                {
                    LCD_GlassDisplayDigit(0, 1);
                }

                if (Value < 0.1)
                {
                    LCD_GlassDisplayDigit(0, 2);
                }

                if (Value < 0.01)
                {
                    LCD_GlassDisplayDigit(0, 3);
                }

                if (Value < 0.001)
                {
                    LCD_GlassDisplayDigit(0, 4);
                }

                if (Value < 0.0001)
                {
                    LCD_GlassDisplayDigit(0, 5);
                }

                break;
        }

        LCD_GlassUpdate();
    }
}

/**
  * @brief  Displays a unsigned int number on small digit number area.
  * @param  Value: the digit int number.
  *         This parameter can be: 0~99999.
  * @retval None
  */
void LCD_GlassDisplayUintOnSmallNumArea(uint16_t Value)
{
    unsigned char i = 0;
    unsigned char DispBuff[4] = {0};

    for (i = 0; i < 4; i++)
    {
        DispBuff[i] = Value % 10;
        Value /= 10;
    }

    /* eliminate invalid "0" */
    for (i = 3; i > 0; i--)
    {
        if (DispBuff[i] == 0)
            DispBuff[i] = 10;
        else
            break;
    }

    for (i = 0; i < 4; i++)
    {
        LCD_GlassDisplayDigit(DispBuff[i], i + 7);
    }
}

/**
  * @brief  Upadate the lcd display.
  * @param  None
  * @retval None
  */
void LCD_GlassUpdate(void)
{
    LCD_WrietNoMask(LCD_RAM_COM0, LcdRamBuffer[0]);
    LCD_WrietNoMask(LCD_RAM_COM1, LcdRamBuffer[1]);
    LCD_WrietNoMask(LCD_RAM_COM2, LcdRamBuffer[2]);
    LCD_WrietNoMask(LCD_RAM_COM3, LcdRamBuffer[3]);
    LCD_UpdateDisplayRequest();
    delay(UPDATE_DELAY);
}

/**
  * @brief  Display a string in scrolling mode
  * @note   The LCD should be cleared before to start the write operation.
  * @param  Value: The number to display on the LCD Glass.
  * @param  nScroll: Specifies how many time the message will be scrolled
  * @param  ScrollSpeed: Speciifes the speed of the scroll.
  *         Low value gives higher speed.
  * @retval None
  */
void LCD_GlassScrollNum(uint32_t Value, uint16_t nScroll, uint32_t ScrollSpeed)
{
    uint8_t Repetition = 0;
    uint32_t Value1;
    uint32_t TmpValue1[6] = {0};
    uint32_t TmpValue2[6] = {0};
    Value1 = Value;

    LCD_GlassDisplayIntOnBigNumArea(Value1);

    LCD_GlassUpdate();
    delay(ScrollSpeed);

    TmpValue1[0] = Value / 100000 % 10;
    TmpValue1[1] = Value / 10000 % 10;
    TmpValue1[2] = Value / 1000 % 10;
    TmpValue1[3] = Value / 100 % 10;
    TmpValue1[4] = Value / 10 % 10;
    TmpValue1[5] = Value % 10;

    for (Repetition = 0; Repetition < nScroll; Repetition++)
    {
        TmpValue2[1] = TmpValue1[0] ;
        TmpValue2[2] = TmpValue1[1] ;
        TmpValue2[3] = TmpValue1[2];
        TmpValue2[4] = TmpValue1[3];
        TmpValue2[5] = TmpValue1[4];
        TmpValue2[0] = TmpValue1[5];
        Value1 = TmpValue2[0] * 100000 +  TmpValue2[1] * 10000 +  TmpValue2[2] * 1000 +  \
                 TmpValue2[3] * 100 + TmpValue2[4] * 10 +  TmpValue2[5];
        LCD_GlassClear();
        LCD_GlassDisplayIntOnBigNumArea(Value1);
        LCD_GlassUpdate();
        delay(ScrollSpeed);

        TmpValue2[1] = TmpValue1[5] ;
        TmpValue2[2] = TmpValue1[0] ;
        TmpValue2[3] = TmpValue1[1];
        TmpValue2[4] = TmpValue1[2];
        TmpValue2[5] = TmpValue1[3];
        TmpValue2[0] = TmpValue1[4];
        Value1 = TmpValue2[0] * 100000 +  TmpValue2[1] * 10000 +  TmpValue2[2] * 1000 +  \
                 TmpValue2[3] * 100 + TmpValue2[4] * 10 +  TmpValue2[5];
        LCD_GlassClear();
        LCD_GlassDisplayIntOnBigNumArea(Value1);
        LCD_GlassUpdate();
        delay(ScrollSpeed);

        TmpValue2[1] = TmpValue1[4] ;
        TmpValue2[2] = TmpValue1[5] ;
        TmpValue2[3] = TmpValue1[0];
        TmpValue2[4] = TmpValue1[1];
        TmpValue2[5] = TmpValue1[2];
        TmpValue2[0] = TmpValue1[3];
        Value1 = TmpValue2[0] * 100000 +  TmpValue2[1] * 10000 +  TmpValue2[2] * 1000 +  \
                 TmpValue2[3] * 100 + TmpValue2[4] * 10 +  TmpValue2[5];
        LCD_GlassClear();
        LCD_GlassDisplayIntOnBigNumArea(Value1);
        LCD_GlassUpdate();
        delay(ScrollSpeed);

        TmpValue2[1] = TmpValue1[3] ;
        TmpValue2[2] = TmpValue1[4] ;
        TmpValue2[3] = TmpValue1[5];
        TmpValue2[4] = TmpValue1[0];
        TmpValue2[5] = TmpValue1[1];
        TmpValue2[0] = TmpValue1[2];
        Value1 = TmpValue2[0] * 100000 +  TmpValue2[1] * 10000 +  TmpValue2[2] * 1000 +  \
                 TmpValue2[3] * 100 + TmpValue2[4] * 10 +  TmpValue2[5];
        LCD_GlassClear();
        LCD_GlassDisplayIntOnBigNumArea(Value1);
        LCD_GlassUpdate();
        delay(ScrollSpeed);

        TmpValue2[1] = TmpValue1[2] ;
        TmpValue2[2] = TmpValue1[3] ;
        TmpValue2[3] = TmpValue1[4];
        TmpValue2[4] = TmpValue1[5];
        TmpValue2[5] = TmpValue1[0];
        TmpValue2[0] = TmpValue1[1];
        Value1 = TmpValue2[0] * 100000 +  TmpValue2[1] * 10000 +  TmpValue2[2] * 1000 +  \
                 TmpValue2[3] * 100 + TmpValue2[4] * 10 +  TmpValue2[5];
        LCD_GlassClear();
        LCD_GlassDisplayIntOnBigNumArea(Value1);
        LCD_GlassUpdate();
        delay(ScrollSpeed);


        TmpValue2[1] = TmpValue1[1] ;
        TmpValue2[2] = TmpValue1[2] ;
        TmpValue2[3] = TmpValue1[3];
        TmpValue2[4] = TmpValue1[4];
        TmpValue2[5] = TmpValue1[5];
        TmpValue2[0] = TmpValue1[0];
        Value1 = TmpValue2[0] * 100000 +  TmpValue2[1] * 10000 +  TmpValue2[2] * 1000 +  \
                 TmpValue2[3] * 100 + TmpValue2[4] * 10 +  TmpValue2[5];
        LCD_GlassClear();
        LCD_GlassDisplayIntOnBigNumArea(Value1);
        LCD_GlassUpdate();
        delay(ScrollSpeed);

    }
}

/**
  * @brief  Displays a segment code.
  * @param  None
  * @retval None
  */
void LCD_GlassDisplayHKLog(void)
{
    LCD_GlassDisplaySeg(_LCD_HK_LOGO);
}

/**
  * @brief  Configures the LCD Segments and Coms GPIOs.
  * @param  None
  * @retval None\\HK32L0xx_Demo\../../../../../Boards/Board_HK32L0xx_EVAL/hk32l0xx_eval_glass_lcd.c\LCD_GlassScrollNum\TmpValue
  */
static void LCD_GPIOConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*!< Enable GPIOA, GPIOB, GPIOC, GPIOD and GPIOE AHB Clocks */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC
                          | RCC_AHBPeriph_GPIOD, ENABLE);

    /*!< Connect PA.08 to LCD COM0 */
    /*!< Connect PA.09 to LCD COM1 */
    /*!< Connect PA.10 to LCD COM2 */
    /*!< Connect PB.09 to LCD COM3 */
    /*!< Connect PA.01 to LCD SEG0 */
    /*!< Connect PA.02 to LCD SEG1 */
    /*!< Connect PA.03 to LCD SEG2 */
    /*!< Connect PA.06 to LCD SEG3 */
    /*!< Connect PA.07 to LCD SEG4 */
    /*!< Connect PB.00 to LCD SEG5 */
    /*!< Connect PB.01 to LCD SEG6 */
    /*!< Connect PB.03 to LCD SEG7 */
    /*!< Connect PB.04 to LCD SEG8 */
    /*!< Connect PB.05 to LCD SEG9 */
    /*!< Connect PB.10 to LCD SEG10 */
    /*!< Connect PB.11 to LCD SEG11 */
    /*!< Connect PB.12 to LCD SEG12 */
    /*!< Connect PB.13 to LCD SEG13 */
    /*!< Connect PB.14 to LCD SEG14 */
    /*!< Connect PB.15 to LCD SEG15 */
    /*!< Connect PB.08 to LCD SEG16 */
    /*!< Connect PA.15 to LCD SEG17 */
    /*!< Connect PC.00 to LCD SEG18 */
    /*!< Connect PC.01 to LCD SEG19 */
    /*!< Connect PC.02 to LCD SEG20 */
    /*!< Connect PC.03 to LCD SEG21 */
    /*!< Connect PC.04 to LCD SEG22 */
    /*!< Connect PC.05 to LCD SEG23 */
    /*!< Connect PC.06 to LCD SEG24 */
    /*!< Connect PC.07 to LCD SEG25 */
    /*!< Connect PC.08 to LCD SEG26 */
    /*!< Connect PC.09 to LCD SEG27 */
    /*!< Connect PC.10 to LCD SEG28 */
    /*!< Connect PC.11 to LCD SEG29 */
    /*!< Connect PC.12 to LCD SEG30 */
    /*!< Connect PD.02 to LCD SEG31 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_1 | GPIO_Pin_2 | \
                                  GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | \
                                  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | \
                                  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_8;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | \
                                  GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | \
                                  GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
static void delay(__IO uint32_t nCount)
{
    __IO uint32_t index = 0;

    for (index = (0xFF * nCount); index != 0; index--)
    {
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
