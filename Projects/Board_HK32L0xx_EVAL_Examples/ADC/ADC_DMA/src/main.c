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

/** @addtogroup ADC_DMA
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define ADC1_DR_Address    0x40012440

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;
__IO uint16_t RegularConvData_Tab[3];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void ADC_Config(void);
static void DMA_Config(void);
static void Display(void);
static void USART_Config(void);

/**
  * @brief  Main program.
  * @retval None
  */
int main(void)
{
    /* USART configuration */
    USART_Config();

    /* DMA configuration */
    DMA_Config();

    /* ADC configuration */
    ADC_Config();


    /* Infinite loop */
    while (1)
    {
        /* Test DMA1 TC flag */
        while ((DMA_GetFlagStatus(DMA1_FLAG_TC1)) == RESET )
        {
        }

        /* Clear DMA TC flag */
        DMA_ClearFlag(DMA1_FLAG_TC1);
        Display();
    }
}

/**
  * @brief  Configure the USART Device
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
  * @brief  ADC channel configuration
  * @retval None
  */
static void ADC_Config(void)
{
    ADC_InitTypeDef     ADC_InitStructure;
    GPIO_InitTypeDef    GPIO_InitStructure;

    /* ADC DeInit */
    ADC_DeInit(ADC);

    /* GPIOA and SYSCFG Periph clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* Enable Vrefint ADC  */
    SYSCFG_ADCVrefEnableCmd(ENABLE);

    /* ADC Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);

    /* Configure ADC channel0 as analog input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Initialize ADC structure */
    ADC_StructInit(&ADC_InitStructure);

    /* Configure the ADC in continuous mode withe a resolution equal to 12 bits  */
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Backward;
    ADC_Init(ADC, &ADC_InitStructure);

    /* Convert the ADC Channel0 with 55.5 Cycles as sampling time */
    ADC_ChannelConfig(ADC, ADC_Channel_0, ADC_SampleTime_55_5Cycles);

    /* Convert the ADC temperature sensor  with 55.5 Cycles as sampling time */
    ADC_ChannelConfig(ADC, ADC_Channel_TempSensor, ADC_SampleTime_55_5Cycles);
    ADC_TempSensorCmd(ADC, ENABLE);

    /* Convert the ADC Vref  with 55.5 Cycles as sampling time */
    ADC_ChannelConfig(ADC, ADC_Channel_Vrefint, ADC_SampleTime_55_5Cycles);
    ADC_VrefintCmd(ADC, ENABLE);
    ADC_SetClock(ADC, ADC_ClockMode_SynClkDiv4);

    /* ADC Calibration */
    ADC_GetCalibrationFactor(ADC);

    /* ADC DMA request in circular mode */
    ADC_DMARequestModeConfig(ADC, ADC_DMAMode_Circular);

    /* Enable ADC_DMA */
    ADC_DMACmd(ADC, ENABLE);

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
  * @brief  DMA channel1 configuration
  * @retval None
  */
static void DMA_Config(void)
{
    DMA_InitTypeDef   DMA_InitStructure;

    /* DMA clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, ENABLE);

    /* DMA Channel1 Config */
    DMA_DeInit(DMA_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RegularConvData_Tab;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 3;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA_Channel1, &DMA_InitStructure);

    /* DMA Channel1 enable */
    DMA_Cmd(DMA_Channel1, ENABLE);
}



/**
  * @brief  Display ADC channels Sample Value buffer by UART.
  * @retval None
  */
static void Display(void)
{
    uint32_t v = 0, mv = 0, sensor = 0;
    uint8_t  index = 0;
    uint16_t TmpVal = 0;

    for (index = 0; index < 3; index++)
    {
        TmpVal = RegularConvData_Tab[index];

        if (index == 0)
        {
            sensor = ADC_GetTemperature(TmpVal, 3300);
        }
        else
        {
            v = ((TmpVal * 3300) / 0xFFF) / 1000;
            mv = (((TmpVal * 3300) / 0xFFF) % 1000) / 100;
        }

        if (index == 2)
        {
            printf(" V(PA0)  = %d.%d V\r\n\r\n", v, mv);
        }
        else if (index == 0)
        {
            printf(" Sensor  = %d degree celsius\r\n", sensor);
        }
        else
        {
            printf(" V(ref)  = %d.%d V\r\n", v, mv);
        }
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



