/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_lp_modes.c
* @brief:     This file provides the low power function.
* @author:    AE Team
* @version:   V1.0.0/2024-01-19
*             1.Initial version
* @log:
*******************************************************************************/

#include "hk32l0xx.h"
#include "hk32l0xx_lp_modes.h"
#include "hk32l0xx_eval.h"

/** @addtogroup HK32L0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup PWR_CurrentConsumption
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function configures the system to enter LP RUN mode for
  *         current consumption measurement purpose.
  * @retval None
  */
void LPRunMode_Measure(void)
{
    __IO uint32_t index = 0;
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Configure all GPIO as analog to reduce current consumption on non used IOs */
    /* Enable GPIOs clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* Disable GPIOs clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, DISABLE);
    /* Configure Button KEY2 */
    HK_EVAL_PBInit(BUTTON_KEY2, BUTTON_MODE_EXTI);
    /* Switch to LSI CLK  */
    RCC_LSICmd(ENABLE);
    RCC_SYSCLKConfig(RCC_SYSCLKSource_LSI);
    /* Disable HSI  */
    RCC_HSICmd(DISABLE);
    /* Disable HSE  */
    RCC_HSEConfig(RCC_HSE_OFF);
    RCC_PLLCmd(DISABLE);
    /* Enter LPR RUN  */
    PWR_EnableUltraLowPower();
    PWR_EnableLowPowerRunMode();

    /* Infinite loop */
    while (1)
    {
    }
}
/**
  * @brief  This function configures the system to enter Sleep mode for
  *         current consumption measurement purpose.
  * @retval None
  */
void SleepMode_Measure(void)
{
    __IO uint32_t index = 0;
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Configure all GPIO as analog to reduce current consumption on non used IOs */
    /* Enable GPIOs clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* Disable GPIOs clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, DISABLE);
    /* Configure Button KEY2 */
    HK_EVAL_PBInit(BUTTON_KEY2, BUTTON_MODE_EXTI);
    /* Switch to LSI CLK  */
    RCC_LSICmd(ENABLE);
    RCC_SYSCLKConfig(RCC_SYSCLKSource_LSI);
    /* Disable HSI  */
    RCC_HSICmd(DISABLE);
    /* Disable HSE  */
    RCC_HSEConfig(RCC_HSE_OFF);
    RCC_PLLCmd(DISABLE);
    /* Request to enter SLEEP mode */
    __WFI();
    /* Initialize LED1 on EVAL board */
    HK_EVAL_LEDInit(LED1);

    /* Infinite loop */
    while (1)
    {
        /* Toggle The LED1 */
        HK_EVAL_LEDToggle(LED1);

        /* Inserted Delay */
        for (index = 0; index < 0x7FFFF; index++)
        {
        }
    }
}

/**
  * @brief  This function configures the system to enter  Low power Sleep mode for
  *         current consumption measurement purpose.
  * @retval None
  */
void LPSleepMode_Measure(void)
{
    __IO uint32_t index = 0;
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Configure all GPIO as analog to reduce current consumption on non used IOs */
    /* Enable GPIOs clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* Disable GPIOs clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, DISABLE);
    /* Configure Button KEY2 */
    HK_EVAL_PBInit(BUTTON_KEY2, BUTTON_MODE_EXTI);
    /* Switch to LSI CLK  */
    RCC_LSICmd(ENABLE);
    RCC_SYSCLKConfig(RCC_SYSCLKSource_LSI);
    /* Disable HSI  */
    RCC_HSICmd(DISABLE);
    /* Disable HSE  */
    RCC_HSEConfig(RCC_HSE_OFF);
    RCC_PLLCmd(DISABLE);
    /* Request to enter Low power SLEEP mode */
    PWR_EnableUltraLowPower();
    /* Enters Lower Power Sleep mode */
    PWR_EnterLowPowerSleepMode(PWR_SLEEPEntry_WFI);
    /* Initialize LED1 on EVAL board */
    HK_EVAL_LEDInit(LED1);

    /* Infinite loop */
    while (1)
    {
        /* Toggle The LED1 */
        HK_EVAL_LEDToggle(LED1);

        /* Inserted Delay */
        for (index = 0; index < 0x7FFFF; index++)
        {
        }
    }
}

/**
  * @brief  This function configures the system to enter stop mode for
  *         current consumption measurement purpose.
  * @retval None
  */
void StopMode_Measure(void)
{
    __IO uint32_t index = 0;
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Configure all GPIO as analog to reduce current consumption on non used IOs */
    /* Enable GPIOs clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* Disable GPIOs clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, DISABLE);
    /* Configure Button KEY2 */
    HK_EVAL_PBInit(BUTTON_KEY2, BUTTON_MODE_EXTI);
    /* Clear Power WakeUp (CWUF) pending flag */
    PWR_ClearFlag(PWR_FLAG_WU);
    /* Enter Stop Mode */
    PWR_EnableUltraLowPower();
    PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
    /* Initialize LED1 on EVAL board */
    HK_EVAL_LEDInit(LED1);

    /* Infinite loop */
    while (1)
    {
        /* Toggle The LED1 */
        HK_EVAL_LEDToggle(LED1);

        /* Inserted Delay */
        for (index = 0; index < 0x5FFFF; index++)
        {
        }
    }
}

/**
  * @brief  This function configures the system to enter low power stop mode for
  *         current consumption measurement purpose.
  * @retval None
  */
void LPStopMode_Measure(void)
{
    __IO uint32_t index = 0;
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Configure all GPIO as analog to reduce current consumption on non used IOs */
    /* Enable GPIOs clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* Disable GPIOs clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, DISABLE);
    /* Configure Button KEY2 */
    HK_EVAL_PBInit(BUTTON_KEY2, BUTTON_MODE_EXTI);
    /* Clear Power WakeUp (CWUF) pending flag */
    PWR_ClearFlag(PWR_FLAG_WU);
    /* Enter LP Stop Mode */
    PWR_EnableUltraLowPower();
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_SLEEPEntry_WFI);
    /* Initialize LED1 on EVAL board */
    HK_EVAL_LEDInit(LED1);

    /* Infinite loop */
    while (1)
    {
        /* Toggle The LED1 */
        HK_EVAL_LEDToggle(LED1);

        /* Inserted Delay */
        for (index = 0; index < 0x5FFFF; index++)
        {
        }
    }
}

/**
  * @}
  */

/**
  * @}
  */


