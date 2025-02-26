/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_it.c
* @brief:     Interrupt Service Routines
* @author:    AE Team
* @version:   V1.0.0/2024-01-04
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_it.h"
#include "hk32l0xx_eval.h"
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

extern uint8_t RxBuffer[];
extern uint8_t CmdBuffer[];
extern uint8_t AckBuffer[];
extern __IO uint8_t RxIndex;
extern __IO uint8_t TxIndex;

extern __IO uint8_t UsartTransactionType;
extern __IO uint8_t UsartMode;

__IO uint8_t Counter = 0x00;
extern __IO uint32_t TimeOut;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern uint8_t GetVar_NbrOfData(void);
/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @retval None
  */
void SysTick_Handler(void)
{
    /* Decrement the timeout value */
    if (TimeOut != 0x0)
    {
        TimeOut--;
    }

    if (Counter < 10)
    {
        Counter++;
    }
    else
    {
        Counter = 0x00;
    }
}

/******************************************************************************/
/*                 HK32L0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (KEIL_Startup_hk32l0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles USART interrupt request.
  * @retval None
  */
void USART1_IRQHandler(void)
{
    /* USART in mode Transmitter -------------------------------------------------*/
    if (USART_GetITStatus(USART1, USART_IT_TXE) == SET)
    {
        /* When Joystick Pressed send the command then send the data */
        if (UsartMode == USART_MODE_TRANSMITTER)
        {
            /* Send the command */
            if (UsartTransactionType == USART_TRANSACTIONTYPE_CMD)
            {
                USART_SendData(USART1, CmdBuffer[TxIndex++]);

                if (TxIndex == 0x02)
                {
                    /* Disable the USARTx transmit data register empty interrupt */
                    USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
                }
            }

            /* Send the data */
            else
            {
            }
        }
        /*If Data Received send the ACK*/
        else
        {
            USART_SendData(USART1, AckBuffer[TxIndex++]);

            if (TxIndex == 0x02)
            {
                /* Disable the USARTx transmit data register empty interrupt */
                USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
            }
        }
    }

    /* USART in mode Receiver --------------------------------------------------*/
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        if (UsartMode == USART_MODE_TRANSMITTER)
        {
            AckBuffer[RxIndex++] = USART_ReceiveData(USART1);
        }
        else
        {
            CmdBuffer[RxIndex] = USART_ReceiveData(USART1);
            AckBuffer[RxIndex++] = USART_ReceiveData(USART1);
        }

        if ( (AckBuffer[0] == 0x55) && (AckBuffer[1] == 0x01))
        {
            HK_EVAL_LEDOn(LED1);
            HK_EVAL_LEDOn(LED2);
        }
    }
}
