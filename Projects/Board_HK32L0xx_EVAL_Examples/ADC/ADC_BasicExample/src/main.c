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

/** @addtogroup ADC_BasicExample
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;

/* Private function prototypes -----------------------------------------------*/
static void Display(void);
static void ADC_Config(void);
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

    /* USART configuration */
    USART_Config();

    /* Configure ADC1  */
    ADC_Config();

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
        /* Display converted data on the UART */
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
    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_Init(ADC, &ADC_InitStructure);
    ADC_ChannelConfig(ADC, ADC_Channel_0, ADC_SampleTime_28_5Cycles);

    /* ADC Calibration */
    ADC_GetCalibrationFactor(ADC);

    /* Enable the ADC peripheral */
    ADC_Cmd(ADC, ENABLE);

    /* Wait the ADRDY flag */
    while (!ADC_GetFlagStatus(ADC, ADC_FLAG_ADRDY))
    {
    }

    /* ADC1 regular Software Start Conv */
    ADC_StartOfConversion(ADC);
}


/**
  * @brief  Display ADC converted value on UART
  * @param  None
  * @retval None
  */
static void Display(void)
{
    uint32_t v = 0, mv = 0;
    v = (ADC1ConvertedVoltage) / 1000;
    mv = (ADC1ConvertedVoltage % 1000) / 100;
    printf("   ADC = %d.%d V\r\n", v, mv);
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



