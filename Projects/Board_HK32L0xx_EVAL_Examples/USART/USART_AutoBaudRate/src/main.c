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

/** @addtogroup USART_AutoBaudRate
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void USART_Config(void);
static void AutoBauRate_StartBitMethod(void);
static void GPIO_Config(void);
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
    this is done through SystemInit() function which is called from startup
    file (startup_hk32l0xx.s) before to branch to application main.
    To reconfigure the default setting of SystemInit() function, refer to
    startup_hk32l0xx.c file
    */

    /* Initialize LEDs available***********************************************/
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    /* Configure and enable the systick timer to generate an interrupt each 1 ms */
    SysTick_Config((SystemCoreClock / 1000));

    /* GPIO configuration */
    GPIO_Config();

    /* USART configuration */
    USART_Config();

    /* AutoBaudRate for USART by Start bit Method */
    AutoBauRate_StartBitMethod();

    while (1)
    {
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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  Start Bit Method to USART AutoBaudRate.
  * @param  None
  * @retval None
  */
static void AutoBauRate_StartBitMethod(void)
{
    /* USART enable */
    USART_Cmd(USART1, ENABLE);

    /* Configure the AutoBaudRate method */
    USART_AutoBaudRateConfig(USART1, USART_AutoBaudRate_StartBit);

    /* Enable AutoBaudRate feature */
    USART_AutoBaudRateCmd(USART1, ENABLE);

    /* Wait until Receive enable acknowledge flag is set */
    while (USART_GetFlagStatus(USART1, USART_FLAG_REACK) == RESET)
    {
    }

    /* Wait until Transmit enable acknowledge flag is set */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TEACK) == RESET)
    {
    }

    /* Loop until the end of Autobaudrate phase */
    while (USART_GetFlagStatus(USART1, USART_FLAG_ABRF) == RESET)
    {
    }

    /* If AutoBaudBate error occurred */
    if (USART_GetFlagStatus(USART1, USART_FLAG_ABRE) != RESET)
    {
        /* Turn on LED2 */
        HK_EVAL_LEDOn(LED2);
    }
    else
    {
        /* Turn on LED1 */
        HK_EVAL_LEDOn(LED1);

        /* Wait until RXNE flag is set */
        while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        {
        }

        /* Wait until TXE flag is set */
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        {
        }

        /* Send received character */
        USART_SendData(USART1, USART_ReceiveData(USART1));

        while (USART_GetFlagStatus(USART1, USART_FLAG_BUSY) == RESET)
        {
        }

        /* clear the TE bit (if a transmission is on going or a data is in the TDR, it will be sent before
        efectivelly disabling the transmission) */
        USART_DirectionModeCmd(USART1, USART_Mode_Tx, DISABLE);

        /* Check the Transfer Complete Flag */
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
        {
        }
    }

    /* USART Disable */
    USART_Cmd(USART1, DISABLE);
}

/**
  * @brief  Deinitializes the GPIO peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
static void GPIO_Config(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    /*USART1:PA9(TX)---PA10(RX)*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
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


