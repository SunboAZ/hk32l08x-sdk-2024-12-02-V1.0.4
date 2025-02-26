/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_it.c
* @brief:     Interrupt Service Routines
* @author:    AE Team
* @version:   V1.0.0/2024-01-04
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_it.h"
#include "hk32l0xx_eval.h"
#include "hk32l0xx_eval_glass_lcd.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t counter = 1;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 HK32L0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (KEIL_Startup_hk32l0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles EXTI Line 2 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_3_IRQHandler(void)
{
    if (EXTI_GetITStatus(KEY1_BUTTON_EXTI_LINE) != RESET)
    {
        /* Clear The LCD GLASS */
        LCD_GlassClear();

        switch (counter)
        {
            case 0:

                /* Configure all LCD segments and Coms to blink at frequency LCDCLK/16 */
                LCD_BlinkModeCmd(LCD_BLINKMODE_ALLSEG_ALLCOM, ENABLE);
                LCD_BlinkFrequencyConfig(LCD_BLINKFREQUENCY_DIV16);

                /* Display the "16" message on the LCD GLASS */
                LCD_GlassDisplayIntOnBigNumArea(16);

                /* Increment the Blink freqency */
                counter++;
                break;

            case  1:

                /* Configure all LCD segments and Coms to blink at frequency LCDCLK/32 */
                LCD_BlinkModeCmd(LCD_BLINKMODE_ALLSEG_ALLCOM, ENABLE);
                LCD_BlinkFrequencyConfig(LCD_BLINKFREQUENCY_DIV32);

                /* Display the "32" message on the LCD GLASS */
                LCD_GlassDisplayIntOnBigNumArea(32);

                /* Increment the Blink frequency */
                counter++;
                break ;

            case  2:

                /* Configure all LCD segments and Coms to blink at frequency LCDCLK/64 */
                LCD_BlinkModeCmd(LCD_BLINKMODE_ALLSEG_ALLCOM, ENABLE);
                LCD_BlinkFrequencyConfig(LCD_BLINKFREQUENCY_DIV64);

                /* Display the "64" message on the LCD GLASS */
                LCD_GlassDisplayIntOnBigNumArea(64);

                /* Increment the Blink frequency */
                counter++;
                break ;

            case  3:

                /* Configure all LCD segments and Coms to blink at frequency LCDCLK/128 */
                LCD_BlinkModeCmd(LCD_BLINKMODE_ALLSEG_ALLCOM, ENABLE);
                LCD_BlinkFrequencyConfig(LCD_BLINKFREQUENCY_DIV128);

                /* Display the "128" message on the LCD GLASS */
                LCD_GlassDisplayIntOnBigNumArea(128);

                /* Increment the blink frequency */
                counter++;
                break ;

            case  4:

                /* Configure all LCD segments and Coms to blink at frequency LCDCLK/256 */
                LCD_BlinkModeCmd(LCD_BLINKMODE_ALLSEG_ALLCOM, ENABLE);
                LCD_BlinkFrequencyConfig(LCD_BLINKFREQUENCY_DIV256);

                /* Display the "256" message on the LCD GLASS */

                LCD_GlassDisplayIntOnBigNumArea(256);

                /* Increment the Blink frequency */
                counter++;
                break ;

            case 5:

                /* Configure all LCD segments and Coms to blink at frequency LCDCLK/512 */
                LCD_BlinkModeCmd(LCD_BLINKMODE_ALLSEG_ALLCOM, ENABLE);
                LCD_BlinkFrequencyConfig(LCD_BLINKFREQUENCY_DIV512);

                /* Display the "512" message on the LCD GLASS */
                LCD_GlassDisplayIntOnBigNumArea(512);

                /* Increment the Blink frequency */
                counter++;
                break;

            default:

                /* Configure all LCD segments and Coms to blink at frequency LCDCLK/0 */
                LCD_BlinkModeCmd(LCD_BLINKMODE_ALLSEG_ALLCOM, ENABLE);
                LCD_BlinkFrequencyConfig(LCD_BLINKFREQUENCY_DIV1024);

                /* Display the "1024" message on the LCD GLASS */
                LCD_GlassDisplayIntOnBigNumArea(1024);
                break ;
        }

        LCD_GlassUpdate();
    }

    /* Clears the key Button EXTI line pending bits. */
    EXTI_ClearITPendingBit(KEY1_BUTTON_EXTI_LINE);
}

/**
  * @brief  This function handles PPP interrupt request.
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


