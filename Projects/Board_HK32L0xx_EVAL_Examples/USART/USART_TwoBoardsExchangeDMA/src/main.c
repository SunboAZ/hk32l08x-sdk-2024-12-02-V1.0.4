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

/** @addtogroup UART_TwoBoardsExchangeDMA
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
#define RXBUFFERSIZE1   (countof(TxBuffer1)-1)
#define RXBUFFERSIZE2   (countof(TxBuffer2)-1)
/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))
/* Private variables ---------------------------------------------------------*/
DMA_InitTypeDef DMA_InitStructure;
/* Buffer used for transmission */
uint8_t TxBuffer1[] = "USART DMA : USART1_BOARD1 -> USART1_BOARD2 using DMA Tx and Rx Flag";
uint8_t TxBuffer2[] = "USART DMA : USART1_BOARD2 -> USART1_BOARD1 using DMA Tx and Rx Flag";
uint8_t NbrOfDataToRead1 = RXBUFFERSIZE1;
uint8_t NbrOfDataToRead2 = RXBUFFERSIZE2;
uint8_t RxBuffer1[RXBUFFERSIZE2];
uint8_t RxBuffer2[RXBUFFERSIZE1];
__IO uint32_t TimeOut = 0x0;
/* Private function prototypes -----------------------------------------------*/
static void UART_Config(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
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
         system_hk32l0xx.c file
       */

    /* LED Init */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    /* BUTTON Init */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

    /* USART configuration */
    UART_Config();

    while (HK_EVAL_PBGetState(BUTTON_KEY1) != RESET)
    {
    }

#if (DEVICE == MASTER)
    DMA_DeInit(USARTx_TX_DMA_CHANNEL);
    DMA_InitStructure.DMA_PeripheralBaseAddr = USARTx_TDR_ADDRESS;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer1;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = NbrOfDataToRead1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(USARTx_TX_DMA_CHANNEL, &DMA_InitStructure);
    DMA_RemapConfig(DMA, USARTx_TX_DMA_Remap);

    /* Enable USART DMA TX request */
    USART_DMACmd(USARTx, USART_DMAReq_Tx, ENABLE);

    /* Enable USART DMA TX Channel */
    DMA_Cmd(USARTx_TX_DMA_CHANNEL, ENABLE);

    /* Wait until USART TX DMA Channel  Transfer Complete */
    while (DMA_GetFlagStatus(USARTx_TX_DMA_FLAG_TC) == RESET)
    {
    }

    DMA_DeInit(USARTx_RX_DMA_CHANNEL);
    DMA_InitStructure.DMA_PeripheralBaseAddr = USARTx_RDR_ADDRESS;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxBuffer1;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = NbrOfDataToRead2;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(USARTx_RX_DMA_CHANNEL, &DMA_InitStructure);
    DMA_RemapConfig(DMA, USARTx_RX_DMA_Remap);

    /* Enable USART DMA TX request */
    USART_DMACmd(USARTx, USART_DMAReq_Rx, ENABLE);

    /* Enable USART DMA TX Channel */
    DMA_Cmd(USARTx_RX_DMA_CHANNEL, ENABLE);

    /* Wait until USART TX DMA Channel  Transfer Complete */
    while (DMA_GetFlagStatus(USARTx_RX_DMA_FLAG_TC) == RESET)
    {
    }

#elif (DEVICE == SLAVER)
    DMA_DeInit(USARTx_RX_DMA_CHANNEL);
    DMA_InitStructure.DMA_PeripheralBaseAddr = USARTx_RDR_ADDRESS;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxBuffer2;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = NbrOfDataToRead1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(USARTx_RX_DMA_CHANNEL, &DMA_InitStructure);
    DMA_RemapConfig(DMA, USARTx_RX_DMA_Remap);

    /* Enable USART DMA TX request */
    USART_DMACmd(USARTx, USART_DMAReq_Rx, ENABLE);

    /* Enable USART DMA TX Channel */
    DMA_Cmd(USARTx_RX_DMA_CHANNEL, ENABLE);

    /* Wait until USART TX DMA Channel  Transfer Complete */
    while (DMA_GetFlagStatus(USARTx_RX_DMA_FLAG_TC) == RESET)
    {
    }

    DMA_DeInit(USARTx_TX_DMA_CHANNEL);
    DMA_InitStructure.DMA_PeripheralBaseAddr = USARTx_TDR_ADDRESS;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer2;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = NbrOfDataToRead2;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(USARTx_TX_DMA_CHANNEL, &DMA_InitStructure);
    DMA_RemapConfig(DMA, USARTx_TX_DMA_Remap);

    /* Enable USART DMA TX request */
    USART_DMACmd(USARTx, USART_DMAReq_Tx, ENABLE);

    /* Enable USART DMA TX Channel */
    DMA_Cmd(USARTx_TX_DMA_CHANNEL, ENABLE);

    /* Wait until USART TX DMA Channel  Transfer Complete */
    while (DMA_GetFlagStatus(USARTx_TX_DMA_FLAG_TC) == RESET)
    {
    }

#endif

    while (1)
    {
#if (DEVICE == MASTER)

        if (Buffercmp(TxBuffer2, RxBuffer1, NbrOfDataToRead1) == PASSED )
        {
            HK_EVAL_LEDOn(LED1);
            HK_EVAL_LEDOn(LED2);
        }

#elif (DEVICE == SLAVER)

        if (Buffercmp(TxBuffer1, RxBuffer2, NbrOfDataToRead2) == PASSED )
        {
            HK_EVAL_LEDOn(LED1);
            HK_EVAL_LEDOn(LED2);
        }

#endif
    }
}

/**
  * @brief  Configure the USART Device
  * @param  None
  * @retval None
  */
static void UART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef UART_InitStructure;

    /* DMA clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, ENABLE);

    /* GPIO clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* USART1 clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* USARTx configured as follow:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1 Stop Bit
    - Parity = No Parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    UART_InitStructure.USART_BaudRate = 115200;
    UART_InitStructure.USART_WordLength = USART_WordLength_8b;
    UART_InitStructure.USART_StopBits = USART_StopBits_1;
    UART_InitStructure.USART_Parity = USART_Parity_No;
    UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    UART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
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
    USART_Init(USART1, &UART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}


/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
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


