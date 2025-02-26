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

/** @addtogroup USART_TwoBoardsExchangeIT
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
static void USART_Config(void);
static void GPIO_Config(void);
static JOYState_TypeDef Read_Joystick(void);
#if (DEVICE == MASTER)
    static void TimeOut_UserCallback(void);
#endif
uint8_t GetVar_NbrOfData(void);
static void SysTickConfig(void);
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

    /* USART configuration */
    USART_Config();

    /* GPIO configuration */
    GPIO_Config();
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

    /* SysTick configuration */
    SysTickConfig();

    /* Waiting Joystick pressed in case to transmit data or received Transaction command */
    while ((PressedButton == JOY_NONE) && (CmdBuffer[0x00] == 0x00))
    {
        PressedButton = Read_Joystick();
    }

#if (DEVICE == MASTER)

    /* USART in Mode Transmitter ---------------------------------------------*/
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
            /* Enable the USARTx transmit data register empty interrupt */
            USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
            /* Wait until USART sends the command or time out */
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

            while ((USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) && (TimeOut != 0x00))
            {
            }

            if (TimeOut == 0)
            {
                TimeOut_UserCallback();
            }

            /* Wait until USART receives the Ack command  or time out*/
            TimeOut = USER_TIMEOUT;
            /* Enable the USART1 Receive interrupt: this interrupt is generated when the
            USART1 receive data register is not empty */
            USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
        }
    }

#elif (DEVICE == SLAVER)
    /* Enable the USART1 Receive interrupt: this interrupt is generated when the
    USART1 receive data register is not empty */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    UsartMode = USART_MODE_RECEIVER;

    while (CmdBuffer[0x01] == 0x00)
    {
    }

    if (CmdBuffer[0x01] != 0x00)
    {
        /* Enable the USARTx transmit data register empty interrupt */
        USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
    }

#endif

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
    NVIC_InitTypeDef NVIC_InitStructure;

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

    /* NVIC configuration */

    /* Enable the USART1 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    USART_Cmd(USART1, ENABLE);
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
#if (DEVICE == MASTER)
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
/**
  * @brief  Returns NbrOfData value.
  * @param  None
  * @retval Tx Buffer Size (NbrOfDataToTransfer).
  */
uint8_t GetVar_NbrOfData(void)
{
    return CmdBuffer[0x01];
}
/**
  * @brief  Configure a SysTick Base time to 10 ms.
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


