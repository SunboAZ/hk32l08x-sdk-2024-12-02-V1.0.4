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

/** @addtogroup COMP_PWMSignalControl
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void COMP_Config(void);
static void TIM_Config(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Syscfg Peripheral clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    SYSCFG_SetAnalogEn(SYSCFG_F_A_EN_BUF_VREFINT_COMP1_2, ENABLE);
    SYSCFG_SetAnalogEn(SYSCFG_F_A_EN_VREFINT, ENABLE);

    /* COMP2 Configuration */
    COMP_Config();
    COMP_SetValidoutput(CMP2, COMP_OUTPUT_Valid_1);

    /* TIM1 Configuration in input capture mode */
    TIM_Config();

    while (1)
    {
    }
}

/**
  * @brief  Configure COMP2
  * @param  None
  * @retval None
  */
static void COMP_Config(void)
{
    COMP_InitTypeDef        COMP_InitStructure;
    GPIO_InitTypeDef        GPIO_InitStructure;

    /* GPIOA Peripheral clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* Configure PA3: PA3 is used as COMP2 non inveting input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    /* COMP Peripheral clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_COMP, ENABLE);

    /* COMP2 Init */
    COMP_InitStructure.InputMinus = COMP2_INPUT_MINUS_VREFINT;
    COMP_InitStructure.InputPlus = COMP2_INPUT_PLUS_PA3;
    COMP_InitStructure.WindowOut = COMP_WINDOWOUT_DISABLE;
    COMP_InitStructure.OutputPolarity = COMP_OUTPUTPOL_NONINVERTED;
    COMP_InitStructure.Hysteresis = COMP_HYSTERESIS_DISABLE;
    COMP_InitStructure.PowerMode = COMP_POWERMODE_LOWPOWER;
    COMP_Init(CMP2, &COMP_InitStructure);

    /* Enable COMP2 */
    COMP_Enable(CMP2);
}

/**
  * @brief  Configures TIM1: channels in PWM mode
  * @param  None
  * @retval None
  */
static void TIM_Config(void)
{

    TIM_BDTRInitTypeDef     TIM_BDTRInitStructure;
    TIM_OCInitTypeDef       TIM_OCInitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    GPIO_InitTypeDef        GPIO_InitStructure;

    /* GPIOA clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* TIM1 channels pin configuration:
         TIM1_CH1 -> PA8
    */
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Enable Alternate function on PA8 to be controlled by TIM1 */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);

    /* TIM1 clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    /* Time Base configuration */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 100;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    /* Channel 1 Configuration in PWM mode */
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 50;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    /* Automatic Output enable, Break, dead time and lock configuration*/
    TIM_BDTRStructInit(&TIM_BDTRInitStructure);
    TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
    TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
    TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
    TIM_BDTRInitStructure.TIM_DeadTime = 11;
    TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
    TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;
    TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
    TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

    /* Main Output Enable */
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    /* TIM1 counter enable */
    TIM_Cmd(TIM1, ENABLE);

    /* config COMP2 to Break */
    TIM_SourceofBreakConfig(TIM1, TIM1_COMP2_OUTPUT_TO_BREAK);
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

