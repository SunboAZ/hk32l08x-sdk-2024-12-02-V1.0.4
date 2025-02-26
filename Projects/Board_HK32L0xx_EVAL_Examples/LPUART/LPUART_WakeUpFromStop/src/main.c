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

/** @addtogroup LPUART_WakeUpFromStop
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint8_t InterruptCounter;
char StrStop[] = {"Enter STOP mode!\r\n"};
char StrWakeup[] = {"MCU STOP mode wake up!\r\n"};
/* Private function prototypes -----------------------------------------------*/
void LPUART_WakeStop_Config(uint32_t Baud);
static void SysTickConfig(void);
static void LPUART_SendByte(char Data);
static void LPUART_SendString(char *String, uint32_t Length);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint32_t i = 0xFFFF;

    /* Initialize LED */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    /* Configure LPUARTx use wakeup STOP mode */
    LPUART_WakeStop_Config(9600);
    LPUART_SendString(StrStop, 18);

    /* Waiting for data transfer to complete */
    while (LPUART_GetFlagStatus(LPUART, LPUART_FLAG_TC) != SET)
    {
    }

    /* delay a time to usart idle */
    while (i--)
    {
    }

    /* Enter LPUART in STOP mode with regulator in low power mode */
    PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);

    /* Waiting Wake Up interrupt */
    while (InterruptCounter == 0x00)
    {
    }

    LPUART_SendString(StrWakeup, 24);
    /* Configure and enable the systick timer to generate an interrupt each 1 ms */
    SysTickConfig();

    while (1)
    {
    }
}

/**
  * @brief  Send Data
  * @param  Data: The LPUARTx Send Data
  * @retval None
  */
static void LPUART_SendByte(char Data)
{
    LPUART_SendData(LPUART, Data);

    while (LPUART_GetFlagStatus(LPUART, LPUART_FLAG_TXE) == RESET)
    {
    }
}

/**
  * @brief  Send String
  * @param  String: The LPUARTx String
  * @param  Length: The LPUARTx Size
  * @retval None
  */
static void LPUART_SendString(char *String, uint32_t Length)
{
    uint32_t i = 0;

    while (Length--)
    {
        LPUART_SendByte(String[i]);
        i++;
    }
}

/**
  * @brief  Configure the LPUART Device
  * @param  Baud: The LPUARTx BaudRate
  * @retval None
  */
void LPUART_WakeStop_Config(uint32_t Baud)
{
    /* Enable PWR APB clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    LPUART_InitTypeDef LPUART_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    /* Enable GPIO clock and Enable LPUART Clock,LPUARTx,LPUARTy */
    LPUARTx_TXIO_CLK_CMD(LPUARTx_TXIO_CLK, ENABLE);
    LPUARTx_RXIO_CLK_CMD(LPUARTx_RXIO_CLK, ENABLE);
    LPUARTx_CLK_CMD(LPUARTx_CLK, ENABLE);

    /* Enable LSE clock */
    PWR_BackupAccessCmd(ENABLE);
    RCC_LSEConfig(RCC_LSE_ON);
    PWR_BackupAccessCmd(DISABLE);

    /* Configure the LSE as LPUART clock */
    LPUARTx_STOPCLK_COFIG(LPUARTx_STOPCLK);

    /* GPIO Configure RX TX */
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin     = LPUARTx_TX_PIN;
    GPIO_Init(LPUARTx_TXIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin     = LPUARTx_RX_PIN;
    GPIO_Init(LPUARTx_RXIO_PORT, &GPIO_InitStructure);

    /* Connect PXx to LPUART1 Tx Rx */
    GPIO_PinAFConfig(LPUARTx_TXIO_PORT, LPUARTx_AF_TX_PIN, LPUARTx_AF_SELECT);
    GPIO_PinAFConfig(LPUARTx_RXIO_PORT, LPUARTx_AF_RX_PIN, LPUARTx_AF_SELECT);

    /* LPUARTx configured */
    LPUART_InitStructure.LPUART_BaudRate = Baud;
    LPUART_InitStructure.LPUART_HardwareFlowControl = LPUART_HardwareFlowControl_None;    /* Hardware flow control disabled (RTS and CTS signals) */
    LPUART_InitStructure.LPUART_Mode = LPUART_Mode_Rx | LPUART_Mode_Tx;                    /* Receive and transmit enabled */

    /* When using Parity the word length must be configured to 9 bits */
    LPUART_InitStructure.LPUART_Parity = LPUART_Parity_No;                                /* No parity */
    LPUART_InitStructure.LPUART_StopBits = LPUART_StopBits_1;                             /* One Stop Bit */
    LPUART_InitStructure.LPUART_WordLength = LPUART_WordLength_8b;                        /*Word Length = 8 Bits */
    LPUART_Init(LPUART, &LPUART_InitStructure);

    /* NVIC configuration */

    /* Enable the LPUARTx Interrupt. The interrupt of LPUART is shared with EXTI28, so EXTI_Line28 is enabled */
    EXTI_InitStructure.EXTI_Line = EXTI_Line28;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = LPUARTx_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure the wake up Method = Start bit */
    LPUART_StopModeWakeUpSourceConfig(LPUART, LPUART_WakeUpSource_StartBit);

    /* Enable LPUART */
    LPUART_Cmd(LPUART, ENABLE);

    /* Before entering the LPUART in STOP mode the REACK flag must be checked to ensure the LPUART RX is ready */
    while (LPUART_GetFlagStatus(LPUART, LPUART_FLAG_REACK) == RESET)
    {
    }

    /* Enable LPUART STOP mode by setting the UESM bit in the CR1 register */
    LPUART_STOPModeCmd(LPUART, ENABLE);

    /* Enable the wake up from stop Interrupt WUF */
    LPUART_ITConfig(LPUART, LPUART_IT_WU, ENABLE);
}

/**
  * @brief  Configure a SysTick Base time to 1 ms.
  * @param  None
  * @retval None
  */
static void SysTickConfig(void)
{
    /* Set SysTick Timer for 10ms interrupts  */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        /* Capture error */
        while (1)
        {
        }
    }

    /* Configure the SysTick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x0);
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



