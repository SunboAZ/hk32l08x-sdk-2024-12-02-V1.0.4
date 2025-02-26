/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-08
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32l0xx_eval.h"

/** @addtogroup HK32L0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup ADC_LowPower
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define ADC1_DR_Address    0x40012440

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;

/* Private function prototypes -----------------------------------------------*/
static void Display(void);
static void ADC_Config(void);
static void TIM_Config(void);
static void USART_Config(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /*  Configures LED1 GPIO */
    HK_EVAL_LEDInit(LED1);

    /* Configure ADC1  */
    ADC_Config();

    /* Configure TIM3  */
    TIM_Config();

    /* USART configuration */
    USART_Config();

    /* Infinite loop */
    while (1)
    {
        while (!ADC_GetFlagStatus(ADC, ADC_FLAG_EOC))
        {
        }

        /* Get ADC1 converted data */
        ADC1ConvertedValue = ADC_GetConversionValue(ADC);
        /* Compute the voltage */
        ADC1ConvertedVoltage = (ADC1ConvertedValue * 3300) / 0xFFF;
        /* Display converted data on the LCD */
        Display();
    }
}


/**
  * @brief  Configure the USART Device
  * @param  None
  * @retval None
  */
static void USART_Config(void)
{
    USART_InitTypeDef USART_InitStructure;

    /* USARTx configured as follow:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1 Stop Bit
    - Parity = No Parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);
}


/**
  * @brief  ADC configuration
  * @param  None
  * @retval None
  */
static void ADC_Config(void)
{
    ADC_InitTypeDef          ADC_InitStructure;
    GPIO_InitTypeDef         GPIO_InitStructure;
    NVIC_InitTypeDef         NVIC_InitStructure;

    /* GPIOA Peripheral clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* ADC1 Peripheral clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);

    /* Configure ADC Chanenl0 as analog input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* ADCs DeInit */
    ADC_DeInit(ADC);

    /* Configure the ADC1 in continous mode withe a resolution equal to 12 bits*/
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(ADC, &ADC_InitStructure);
    ADC_ChannelConfig(ADC, ADC_Channel_0, ADC_SampleTime_28_5Cycles);

    /* ADC Calibration */
    ADC_GetCalibrationFactor(ADC);

    /* Enable OVR interupt */
    ADC_ITConfig(ADC, ADC_IT_OVR, ENABLE);

    /* Configure and enable ADC1 interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = ADC_COMP1_2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the ADC peripheral */
    ADC_Cmd(ADC, ENABLE);

    /* Wait the ADRDY flag */
    while (!ADC_GetFlagStatus(ADC, ADC_FLAG_ADRDY))
    {
    }

    /* Enable the wait conversion mode */
    ADC_WaitModeCmd(ADC, ENABLE);
    /* ADC1 regular Software Start Conv */
    ADC_StartOfConversion(ADC);
    /* Enable the Auto power off mode */
    ADC_AutoPowerOffCmd(ADC, ENABLE);
}

/**
  * @brief  TIM3 configuration
  * @param  None
  * @retval None
  */
static void TIM_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef        TIM_OCInitStructure;

    /* ADC1 Peripheral clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_DeInit(TIM3);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_OCStructInit(&TIM_OCInitStructure);

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 1000;
    TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 1000 - 1);
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* TIM3 TRGO selection */
    TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);

    /* TIM3 enable counter */
    TIM_Cmd(TIM3, ENABLE);
}
/**
  * @brief  Display ADC converted value on LCD
  * @param  None
  * @retval None
  */
static void Display(void)
{
    uint32_t v = 0, mv = 0;
    v = (ADC1ConvertedVoltage) / 1000;
    mv = (ADC1ConvertedVoltage % 1000) / 100;
    printf("   V(Pot) = %d.%d V\r\n", v, mv);
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



