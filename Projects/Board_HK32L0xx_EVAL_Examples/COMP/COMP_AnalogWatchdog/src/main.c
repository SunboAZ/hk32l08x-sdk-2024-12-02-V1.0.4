/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2024-01-04
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32l0xx_eval.h"

/** @addtogroup HK32L0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup COMP_AnalogWatchdog
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t State = 0;
/* Private function prototypes -----------------------------------------------*/
static void COMP_Config(void);
static void STOPEntry(void);
static void RestoreConfiguration(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /******* Initialize LEDs available on HK32L08x-EVAL board ******************/
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    /* PWR Peripheral clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Syscfg Peripheral clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    SYSCFG_SetAnalogEn(SYSCFG_F_A_EN_BUF_VREFINT_COMP1_2, ENABLE);
    SYSCFG_SetAnalogEn(SYSCFG_F_A_EN_VREFINT, ENABLE);

    /* configure COMP1 and COMP2 with interrupts enabled */
    COMP_Config();
    COMP_SetValidoutput(CMP1, COMP_OUTPUT_Valid_1);
    COMP_SetValidoutput(CMP2, COMP_OUTPUT_Valid_1);

    /* Check input voltage level: within the thresholds, above the upper threshold
       or under the lower threshold */
    CheckState();

    while (1)
    {
        if (State == STATE_OVER_THRESHOLD)
        {
            /* Restore config: clock, GPIO... */
            RestoreConfiguration();

            /* Restore GPIO configuration */
            HK_EVAL_LEDInit(LED1);
            HK_EVAL_LEDInit(LED2);

            /* Turn on LED1 and turn off LED2 */
            HK_EVAL_LEDOn(LED1);
            HK_EVAL_LEDOff(LED2);

            while (State == STATE_OVER_THRESHOLD)
            {
                /* add your code here */
            }
        }
        else if (State == STATE_WITHIN_THRESHOLD)
        {
            /* Input voltage is within the thresholds: higher and lower thresholds */

            /* Enter STOP mode with regulator in low power */
            STOPEntry();
        }
        else /* (State == STATE_UNDER_THRESHOLD) */
        {
            /* Restore config: clock, GPIO... */
            RestoreConfiguration();

            /* Restore GPIO configuration */
            HK_EVAL_LEDInit(LED1);
            HK_EVAL_LEDInit(LED2);

            /* Turn on LED2 and turn off LED1 */
            HK_EVAL_LEDOff(LED1);
            HK_EVAL_LEDOn(LED2);

            while (State == STATE_UNDER_THRESHOLD)
            {
                /* add your code here */
            }
        }
    }
}

/**
  * @brief  Configure COMP1 and COMP2 with interrupt
  * @param  None
  * @retval None
  */
static void COMP_Config(void)
{
    COMP_InitTypeDef        COMP_InitStructure;
    EXTI_InitTypeDef        EXTI_InitStructure;
    NVIC_InitTypeDef        NVIC_InitStructure;
    GPIO_InitTypeDef        GPIO_InitStructure;

    /* GPIOA Peripheral clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* Configure PA3: PA3 is used as COMP1 and COMP2 non inveting input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* COMP Peripheral clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_COMP, ENABLE);

    /* COMP1 Init: the higher threshold is set to VREFINT ~ 1.20V
       but can be changed to other available possibilities */
    COMP_InitStructure.InputMinus = COMP1_INPUT_MINUS_VREFINT;
    COMP_InitStructure.WindowOut = COMP_WINDOWOUT_DISABLE;
    COMP_InitStructure.OutputPolarity = COMP_OUTPUTPOL_NONINVERTED;
    COMP_InitStructure.Hysteresis = COMP_HYSTERESIS_LEVEL3;
    COMP_InitStructure.PowerMode = COMP_POWERMODE_LOWPOWER;
    COMP_Init(CMP1, &COMP_InitStructure);

    /* COMP2 Init: the lower threshold is set to VREFINT/4 ~ 1.20 / 4 ~ 0.30 V
       but can be changed to other available possibilities */
    COMP_InitStructure.InputMinus = COMP2_INPUT_MINUS_1_4VREFINT;
    COMP_InitStructure.InputPlus = COMP2_INPUT_PLUS_PA3;
    COMP_InitStructure.WindowOut = COMP_WINDOWOUT_DISABLE;
    COMP_InitStructure.OutputPolarity = COMP_OUTPUTPOL_NONINVERTED;
    COMP_InitStructure.Hysteresis = COMP_HYSTERESIS_LEVEL3;
    COMP_InitStructure.PowerMode = COMP_POWERMODE_LOWPOWER;
    COMP_Init(CMP2, &COMP_InitStructure);

    /* Enable Window mode */
    COMP_SetCommonWindowMode(COMP1_INPUT_PLUS_COMP2);

    /* Enable COMP1: the higher threshold is set to VREFINT ~ 1.20 V */
    COMP_Enable(CMP1);

    /* Enable COMP2: the lower threshold is set to VREFINT/4 ~ 0.30 V */
    COMP_Enable(CMP2);

    /* Configure EXTI Line 21 in interrupt mode */
    EXTI_InitStructure.EXTI_Line = EXTI_Line21;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Configure EXTI Line 22 in interrupt mode */
    EXTI_InitStructure.EXTI_Line = EXTI_Line22;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Clear EXTI21 line */
    EXTI_ClearITPendingBit(EXTI_Line21);

    /* Clear EXTI22 line */
    EXTI_ClearITPendingBit(EXTI_Line22);

    /* Configure COMP IRQ */
    NVIC_InitStructure.NVIC_IRQChannel = ADC_COMP1_2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Prepare the system to enter STOP mode.
  * @param  None
  * @retval None
  */
static void STOPEntry(void)
{
    GPIO_InitTypeDef        GPIO_InitStructure;

    /* Enable GPIOs clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, ENABLE);

    /* Configure all GPIO port pins in Analog mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    /* Request to enter STOP mode with regulator in low power */
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
}

/**
  * @brief  check input voltage level: within the thresholds, above the upper
  *         threshold or under the lower threshold
  * @param  None
  * @retval None
  */
void CheckState(void)
{
    /* Check if COMP2 output level is high */
    if ((COMP_ReadOutputLevel(CMP1) == COMP_OUTPUT_LEVEL_HIGH)
            && (COMP_ReadOutputLevel(CMP2) == COMP_OUTPUT_LEVEL_HIGH))
    {
        /* A rising edge is detected so the input voltage is higher than VREFINT */
        State = STATE_OVER_THRESHOLD;
    }
    else if ((COMP_ReadOutputLevel(CMP1) == COMP_OUTPUT_LEVEL_LOW)
             && (COMP_ReadOutputLevel(CMP2) == COMP_OUTPUT_LEVEL_HIGH))
    {
        /* A falling edge is detected so the input voltage is lower than VREFINT */
        State = STATE_WITHIN_THRESHOLD;
    }
    else if ((COMP_ReadOutputLevel(CMP1) == COMP_OUTPUT_LEVEL_LOW)
             && (COMP_ReadOutputLevel(CMP2) == COMP_OUTPUT_LEVEL_LOW))
    {
        State = STATE_UNDER_THRESHOLD;
    }
}

/**
  * @brief  Restore peripheral config before entering STOP mode.
  * @param  None
  * @retval None
  */
static void RestoreConfiguration(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK configuration ----------------------------------------*/

    /* Enable HSE */
    RCC_HSEConfig(RCC_HSE_ON);

    /* Wait till HSE is ready and if Time out is reached exit */
    HSEStatus = RCC_WaitForHSEStartUp();

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH_SetLatency(FLASH_Latency_1);

        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        /* PCLK = HCLK */
        RCC_PCLKConfig(RCC_HCLK_Div1);

        /*  PLL configuration:  = HSE *  6 = 48 MHz */
        RCC_PREDIVConfig(RCC_PREDIV_Div1);
        RCC_PLLConfig(RCC_PLLSource_HSE, RCC_PLLMul_6);

        /* Enable PLL */
        RCC_PLLCmd(ENABLE);

        /* PLL as system clock source */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    }

}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

