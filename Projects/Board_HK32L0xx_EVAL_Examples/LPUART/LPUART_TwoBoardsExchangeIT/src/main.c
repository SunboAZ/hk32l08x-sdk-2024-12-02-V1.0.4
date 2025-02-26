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

/** @addtogroup LPUART_twoBoardsExchangeIT
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t CmdBuffer [0x02] = {0x00, 0x00}; /* {Command, Number of byte to receive or to transmit} */
uint8_t AckBuffer [0x02] = {0x00, 0x00}; /* {Command, ACK} */

__IO uint32_t TimeOut = 0x0;
__IO JOYState_TypeDef PressedButton = JOY_NONE;
__IO uint8_t UsartTransactionType = USART_TRANSACTIONTYPE_CMD;
__IO uint8_t UsartMode = USART_MODE_TRANSMITTER;
__IO uint8_t RxIndex = 0x00;
__IO uint8_t TxIndex = 0x00;
/* Private function prototypes -----------------------------------------------*/
static void LPUART_Config(void);
static void SysTickConfig(void);
static JOYState_TypeDef Read_Joystick(void);
#if (DEVICE)
    #define  MASTER_FUNCTION
    static void TimeOut_UserCallback(void);
#endif
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

    LPUART_Config();
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);
    SysTickConfig();


    /* Waiting Joystick pressed in case to transmit data or received Transaction command */
    while ((PressedButton == JOY_NONE) && (CmdBuffer[0x00] == 0x00))
    {
        PressedButton = Read_Joystick();
    }

#if (DEVICE)

    /* LPUART in Mode Transmitter ---------------------------------------------*/
    if ((PressedButton != JOY_NONE) && (CmdBuffer[0x00] == 0x00))
    {
        UsartMode = USART_MODE_TRANSMITTER;

        switch (PressedButton)
        {
            /* JOY_RIGHT button pressed */
            case JOY_RIGHT:
                CmdBuffer[0x00] = CMD_RIGHT;
                CmdBuffer[0x01] = CMD_RIGHT_SIZE;
                break;

            default:
                break;
        }

        if (CmdBuffer[0x00] != 0x00)
        {
            /* Enable the LPUART transmit data register empty interrupt */
            LPUART_ITConfig(LPUART, LPUART_IT_TXE, ENABLE);

            /* Wait until LPUART sends the command or time out */
            TimeOut = USER_TIMEOUT;

            while ((TxIndex < 0x02) && (TimeOut != 0x00))
            {
            }

            if (TimeOut == 0)
            {
                TimeOut_UserCallback();
            }

            /* The software must wait until TC=1. The TC flag remains cleared during all data
               transfers and it is set by hardware at the last frame end of transmission*/
            TimeOut = USER_TIMEOUT;

            while ((LPUART_GetFlagStatus(LPUART, LPUART_FLAG_TC) == RESET) && (TimeOut != 0x00))
            {
            }

            if (TimeOut == 0)
            {
                TimeOut_UserCallback();
            }

            /* Wait until LPUART receives the Ack command  or time out*/
            TimeOut = USER_TIMEOUT;
            /* Enable the LPUART Receive interrupt: this interrupt is generated when the
            LPUART receive data register is not empty */
            LPUART_ITConfig(LPUART, LPUART_IT_RXNE, ENABLE);

        }

    }

#else
    /* Enable the LPUART Receive interrupt: this interrupt is generated when the
    LPUART receive data register is not empty */
    LPUART_ITConfig(LPUART, LPUART_IT_RXNE, ENABLE);




    UsartMode = USART_MODE_RECEIVER;

    while (CmdBuffer[0x01] == 0x00)
    {
    }

    if (CmdBuffer[0x01] != 0x00)
    {

        /* Enable the LPUART transmit data register empty interrupt */
        LPUART_ITConfig(LPUART, LPUART_IT_TXE, ENABLE);
    }

#endif

    while (1)
    {
    }
}

/**
  * @brief  LPUART Config.
  * @param  None
  * @retval None
  */
static void LPUART_Config(void)
{
    LPUART_InitTypeDef LPUART_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    /* Enable GPIO clock and Enable LPUART Clock,LPUARTx,LPUARTy */
    LPUARTx_TXIO_CLK_CMD(LPUARTx_TXIO_CLK, ENABLE);
    LPUARTx_RXIO_CLK_CMD(LPUARTx_RXIO_CLK, ENABLE);
    LPUARTx_CLK_CMD(LPUARTx_CLK, ENABLE);
    RCC_HSI16Cmd(ENABLE);

    /* Configure the LSE as LPUART clock */
    RCC_LPUART1CLKConfig(RCC_SELECTIONCLK_HSI16);

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
    LPUART_InitStructure.LPUART_BaudRate = 9600;
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
    NVIC_InitStructure.NVIC_IRQChannel = LPUART_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    LPUART_Cmd(LPUART, ENABLE);
}

/**
  * @brief  SysTick Config.
  * @param  None
  * @retval None
  */
static void SysTickConfig(void)
{
    /* Set SysTick Timer for 10ms interrupts  */
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
  * @brief  Reads key from evaluationboard.
  * @param  None
  * @retval Return JOY_RIGHT or JOY_NONE
  */
static JOYState_TypeDef Read_Joystick(void)
{
    /* "JOY_RIGHT" key is pressed */
    if (HK_EVAL_PBGetState(BUTTON_KEY1))
    {
        while (HK_EVAL_PBGetState(BUTTON_KEY1) == SET)
        {

        }

        return JOY_RIGHT;
    }
    else
    {
        return JOY_NONE;
    }
}
#ifdef MASTER_FUNCTION
/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
  */
static void TimeOut_UserCallback(void)
{
    /* User can add his own implementation to manage TimeOut Communication failure */

    /* Block communication and all processes */
    while (1)
    {

    }
}
#endif

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



