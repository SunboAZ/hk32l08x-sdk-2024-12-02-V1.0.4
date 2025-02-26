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

/** @addtogroup COMP_PulseWidthMeasurement
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t Capture = 0;
__IO uint32_t MeasuredPulse = 0;
__IO uint32_t DisplayActive = 0;
/* Private function prototypes -----------------------------------------------*/
static void DAC_Config(void);
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
    /* USART configuration */
    USART_InitTypeDef USART_InitStruct;

    USART_StructInit(&USART_InitStruct);
    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    HK_EVAL_COMInit(COM1, &USART_InitStruct);

    /* DAC Channel1 configuration */
    DAC_Config();

    /* COMP1 Configuration */
    COMP_Config();
    COMP_SetValidoutput(CMP1, COMP_OUTPUT_Valid_1);

    /* TIM2 Configuration in input capture mode */
    TIM_Config();

    while (1)
    {
        if (DisplayActive != 0)
        {
            /* Compute the pulse width in us */
            MeasuredPulse = (uint32_t)(((uint64_t) Capture * 1000000) / ((uint32_t)SystemCoreClock));

            /* printf measured pulse width */
            printf("PulseWidth = %d us \r\n", MeasuredPulse);
            DisplayActive = 0;
        }
    }
}

/**
  * @brief  Configures the DAC channel 1 with output buffer enabled.
  * @param  None
  * @retval None
  */
static void DAC_Config(void)
{

    /* Init Structure definition */
    DAC_InitTypeDef  DAC_InitStructure;

    /* DAC clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

    /* Fill DAC InitStructure */
    DAC_StructInit(&DAC_InitStructure);
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;

    /* DAC Init */
    DAC_Init(&DAC_InitStructure);

    /* Enable DAC */
    DAC_Cmd(ENABLE);

    /* Set DAC Channel1 DHR register: DAC_OUT1 = (3.3 * 2000) / 4095 ~ 1.61 V */
    DAC_SetChannelData(DAC_Align_12b_R, 2000);
}

/**
  * @brief  Configure COMP1
  * @param  None
  * @retval None
  */
static void COMP_Config(void)
{
    COMP_InitTypeDef        COMP_InitStructure;
    GPIO_InitTypeDef        GPIO_InitStructure;

    /* GPIOA Peripheral clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* Configure PA1: PA1 is used as COMP1 non inveting input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* COMP Peripheral clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_COMP, ENABLE);

    /* COMP1 Init: DAC1 output is used COMP1 inverting input */
    COMP_InitStructure.InputMinus = COMP1_INPUT_MINUS_DAC_PA4;
    COMP_InitStructure.WindowOut = COMP_WINDOWOUT_DISABLE;
    COMP_InitStructure.OutputPolarity = COMP_OUTPUTPOL_NONINVERTED;
    COMP_InitStructure.Hysteresis = COMP_HYSTERESIS_DISABLE;
    COMP_InitStructure.PowerMode = COMP_POWERMODE_NORMALPOWER;
    COMP_Init(CMP1, &COMP_InitStructure);

    /* Enable COMP1 */
    COMP_Enable(CMP1);
}

/**
  * @brief  Configures TIM2 channel 4 in input capture mode
  * @param  None
  * @retval None
  */
static void TIM_Config(void)
{

    /* Init Structure definition */
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* TIM2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* TIM2 Time base configuration */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);

    /* TIM2 Channel4 Input capture Mode configuration */
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;

    /* TIM2 counter is captured at each transition detection: rising or falling edges (both edges) */
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);

    /* TIM2 IRQChannel enable */
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable capture interrupt */
    TIM_ITConfig(TIM2, TIM_IT_CC4, ENABLE);

    /* Enable the TIM2 counter */
    TIM_Cmd(TIM2, ENABLE);
    TIM2_TI4RemapConfig(TIM2_TI4_INPUT_SOURCE_COMP1);

    /* Reset the flags */
    TIM2->SR = 0;
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

