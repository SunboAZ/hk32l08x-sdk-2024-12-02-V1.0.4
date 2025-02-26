/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2024-01-19
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32l0xx_eval.h"

/** @addtogroup HK32L0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup ADC_AnalogWatchdog
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;

uint32_t TimeOut = 0xFFFFFF;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void Display(void);
static void ADC_Config(void);
static void USART_Config(void);
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Initialize LED1 */
    HK_EVAL_LEDInit(LED1);

    /* USART configuration */
    USART_Config();

    /* Configure ADC channel 0 */
    ADC_Config();

    /* Infinite loop */
    while (1)
    {
        /* Get ADC1 converted data */
        ADC1ConvertedValue = ADC_GetConversionValue(ADC);

        /* Compute the voltage */
        ADC1ConvertedVoltage = (ADC1ConvertedValue * 3300) / 0xFFF;

        /* Display converted data on the terminal */
        Display();
    }
}

/**
  * @brief  ADC1 channel configuration
  * @param  None
  * @retval None
  */
static void ADC_Config(void)
{
    ADC_InitTypeDef     ADC_InitStructure;
    GPIO_InitTypeDef    GPIO_InitStructure;
    NVIC_InitTypeDef    NVIC_InitStructure;

    /* GPIOA Periph clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* ADC Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);

    /* Configure ADC Channel0 as analog input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* ADC1 DeInit */
    ADC_DeInit(ADC);

    /* Initialize ADC structure */
    ADC_StructInit(&ADC_InitStructure);

    /* Configure the ADC1 in continuous mode withe a resolution equal to 12 bits  */
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(ADC, &ADC_InitStructure);
    ADC_ChannelConfig(ADC, ADC_Channel_0, ADC_SampleTime_239_5Cycles);

    /* Analog watchdog config ******************************************/

    /* Configure the ADC Thresholds between 1.5V and 2.5V (1861, 3102) */
    ADC_AnalogWatchdogThresholdsConfig(ADC, 3102, 1861);

    /* Enable the ADC1 single channel  */
    ADC_AnalogWatchdogSingleChannelCmd(ADC, ENABLE);
    ADC_OverrunModeCmd(ADC, ENABLE);

    /* Enable the ADC1 analog watchdog */
    ADC_AnalogWatchdogCmd(ADC, ENABLE);
    ADC_AnalogWatchdogSingleChannelConfig(ADC, ADC_AnalogWatchdog_Channel_0);

    /* Enable AWD interrupt */
    ADC_ITConfig(ADC, ADC_IT_AWD, ENABLE);

    /* Configure and enable ADC1 interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = ADC_COMP1_2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the ADC Calibration */
    ADC_GetCalibrationFactor(ADC);

    /* Enable the ADC peripheral */
    ADC_Cmd(ADC, ENABLE);

    /* Wait the ADRDY flag */
    while (!ADC_GetFlagStatus(ADC, ADC_FLAG_ADRDY))
    {
    }

    /* ADC regular Software Start Conv */
    ADC_StartOfConversion(ADC);
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
    printf("  V(PC0) = %d.%d V\r\n", v, mv);
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


