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

/** @addtogroup CRC_TwoBoardsExchange
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t TxBuffer[] = "USART Interrupt Example: Communication between two USART using Interrupt";
uint8_t RxBuffer [RXBUFFERSIZE];

__IO ButtonMode_TypeDef PressedButton  = BUTTON_MODE_GPIO;
__IO uint8_t RxIndex = 0x00;
__IO uint8_t TxIndex = 0x00;
/* Private function prototypes -----------------------------------------------*/
static void USART_Config(void);
static void SysTickConfig(void);
static void CRC_Config(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* USART configuration -----------------------------------------------------*/
    USART_Config();

    /* SysTick configuration ---------------------------------------------------*/
    SysTickConfig();

    /* Initialize LEDs mounted on HK32L08x-EVAL board */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    /* Configure the CRC */
    CRC_Config();

#ifdef MODE_TRANSMITTER

    /* ------------------ USART in mode Tramitter ------------------------------*/

    /* Configure the external interrupt KEY1 button */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_EXTI);

    /* Forever loop */
    while (1)
    {

        /*Wait "BUTTON_MODE_EXTI" to start data transfer */
        if ((PressedButton != BUTTON_MODE_GPIO))
        {
            /* Enable the UART3 transmit data register empty interrupt */
            USART_ITConfig(UART3, USART_IT_TXE, ENABLE);

            /* Set PressedButton to default value */
            PressedButton = BUTTON_MODE_GPIO;
        }
    }

#else
    /* ------------------ USART in mode Receiver -------------------------------*/
    /* Enable the UART3 receive data register not empty interrupt */
    USART_ITConfig(UART3, USART_IT_RXNE, ENABLE);

    /* Infinite loop */
    while (1)
    {
    }

#endif /* MODE_TRANSMITTER */
}

/**
  * @brief  Configures the USART Peripheral.
  * @param  None
  * @retval None
  */
static void USART_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* UART configuration ----------------------------------------------------*/

    /* UART configured as follow:
    - BaudRate = 230400 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 230400;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);

    /* NVIC configuration: Enable the UART3 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = UART3_4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable UART */
    USART_Cmd(UART3, ENABLE);

}

/**
  * @brief  Configure a SysTick Base time to 10 ms.
  * @param  None
  * @retval None
  */
static void SysTickConfig(void)
{
    /* Setup SysTick Timer for 10ms interrupts  */
    if (SysTick_Config(SystemCoreClock / 100))
    {
        /* Capture error */
        while (1)
        {
        }
    }

    /* Configure the SysTick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x0);
}

/**
  * @brief  Configure the CRC.
  * @param  None
  * @retval None
  */
static void CRC_Config(void)
{
    /* Enable CRC AHB clock interface */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

    /* DeInit CRC peripheral */
    CRC_DeInit();

    /* Init the INIT register */
    CRC_SetInitRegister(0);
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

