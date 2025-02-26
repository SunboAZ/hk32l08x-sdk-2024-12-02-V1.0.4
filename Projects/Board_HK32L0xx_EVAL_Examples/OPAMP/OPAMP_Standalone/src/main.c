/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body, This example provides AES encryption decryption  fuctions
* @author:    AE Team
* @version:   V1.0.0/2024-1-20
*              1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t ubButtonPress = 0;
uint8_t uADC_EOCFlag = 0;
/*Add "ADCVal" to live watch to display the measured voltage */
float ADCVal = 0.0;

/* Private function prototypes -----------------------------------------------*/
static void OPAMP_Function_Handle(void);
static void OPAMP_Config(void);
static void ADC_Config(void);
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Initialize LED1 */
    HK_EVAL_LEDInit(LED1);

    /* Initialize LED2 */
    HK_EVAL_LEDInit(LED2);

    /* ------------------------------- USART-------------------------------------*/

    /* USARTx configured as follow:
    - BaudRate = 115200
    - Word Length = USART_WordLength_8b
    - Stop Bit = USART_StopBits_1
    - Parity = USART_Parity_No
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;

    /* Initialize USART1 */
    HK_EVAL_COMInit(COM1, &USART_InitStructure);

    /* Initialize User push-button in EXTI mode */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_EXTI);

    /* Start to  continue */
    printf("Wait for User push-button press to start OPAMP Standalone mode ...\r\n");

    /* Wait for User push-button press to continue */
    WaitForUserButtonPress();

    /* OPAMP internal Follower  */
    OPAMP_Function_Handle();

    /* Infinite loop */
    while (1)
    {
        if (uADC_EOCFlag)
        {
            uADC_EOCFlag = 0;
            HK_EVAL_LEDToggle(LED1);
            Delay(0x3FFFF);
            printf(" After OPAMP1 Standalone mode,The measured voltage:%f\r\n", ADCVal);
        }
    }
}

/**
  * @brief  Config OPAMP.
  * @retval None
  */
static void OPAMP_Function_Handle(void)
{
    /* OPAMP1 configuration: OPAMP1 in internal follower mode, OPAMP1 output is
     internally connected to ADC Channel 5 */
    OPAMP_Config();

    /* ADC configuration: Channel 5 (PA5) is internally connected to OPAMP1 output,
     End Of Conversion (EOC) interrupt is enabled */
    ADC_Config();
}

/**
  * @brief  ADC configuration.
  * @param  None
  * @retval None
  */
static void ADC_Config(void)
{
    ADC_InitTypeDef   ADC_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;

    /* Enable the HSI */
    RCC_HSICmd(ENABLE);

    /* Wait until HSI oscillator is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)
    {
    }

    /* ADC1  clock 2 prescaler */
    ADC_SetCommonClock(ADC, ADC_CLOCK_ASYNC_DIV2);

    /* ADC1 Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);

    /* ADC1 Configuration */
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = 0;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(ADC, &ADC_InitStructure);

    /* ADC1 regular channel 5 configuration */
    ADC_ChannelConfig(ADC, ADC_Channel_5, ADC_SampleTime_239_5Cycles);

    /* Enable EOC interupt */
    ADC_ITConfig(ADC, ADC_IT_EOC, ENABLE);

    /* Enable ADC1 IRQ */
    NVIC_InitStructure.NVIC_IRQChannel = ADC_COMP1_2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable ADC */
    ADC_Cmd(ADC, ENABLE);

    /* Wait for ADC to be ready */
    while (!ADC_GetFlagStatus(ADC, ADC_FLAG_ADRDY))
    {
    }

    /* Start ADC Software Conversion */
    ADC_StartOfConversion(ADC);
}


/**
  * @brief  OPAMP configuration.
  * @param  None
  * @retval None
  */
static void OPAMP_Config(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure;
    OPAMP_InitTypeDef  OPAMP_InitStructure;

    /* GPIOA Peripheral clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* Configure PA5 (OPAMP1 output) in analog mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure PA7 (OPAMP1 positive input) in analog mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* OPAMP Peripheral clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_OPAMP, ENABLE);

    /* OPAMP1 config :The board needs to be physically connected to PA5 and PC5. */
    OPAMP_InitStructure.FunctionalMode = OPAMP_MODE_FUNCTIONAL;
    OPAMP_InitStructure.InputInverting = OPAMP_INPUT_INVERT_VM0;
    OPAMP_InitStructure.InputNonInverting = OPAMP_INPUT_NONINVERT_VP0;
    OPAMP_Init(OPA1, &OPAMP_InitStructure);

    /* Enable OPAMP1 */
    OPAMP_Cmd(OPA1, ENABLE);
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }
}

/**
  * @brief  Wait for User push-button press to start transfer.
  * @param  None
  * @retval None
  */
void WaitForUserButtonPress(void)
{
    while (ubButtonPress == 0)
    {
        HK_EVAL_LEDToggle(LED2);
        Delay(0x3FFFF);
    }

    /* Turn LED2 on */
    HK_EVAL_LEDOn(LED2);
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
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */
