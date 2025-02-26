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
#include "main.h"
#include "hk32l0xx_eval.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t RxBuffer[];
extern uint8_t CmdBuffer[];
extern uint8_t AckBuffer[];
extern uint8_t RxIndex;
extern uint8_t TxIndex;

extern uint8_t UsartTransactionType;
extern uint8_t UsartMode;

__IO uint8_t Counter = 0x00;
extern  uint32_t TimeOut;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

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
  * @brief  This function handles LPUART interrupt request.
  * @retval None
  */
void LPUART_IRQHandler(void)
{
    /* LPUART in mode Transmitter -------------------------------------------------*/
    if (LPUART_GetITStatus(LPUART, LPUART_IT_TXE) == SET)
    {
        /* When Joystick Pressed send the command then send the data */
        if (UsartMode == USART_MODE_TRANSMITTER)
        {
            /* Send the command */
            if (UsartTransactionType == USART_TRANSACTIONTYPE_CMD)
            {
                LPUART_SendData(LPUART, CmdBuffer[TxIndex++]);

                if (TxIndex == 0x02)
                {
                    /* Disable the UARTx transmit data register empty interrupt */
                    LPUART_ITConfig(LPUART, LPUART_IT_TXE, DISABLE);
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
            LPUART_SendData(LPUART, AckBuffer[TxIndex++]);

            if (TxIndex == 0x02)
            {
                /* Disable the LPUART transmit data register empty interrupt */
                LPUART_ITConfig(LPUART, LPUART_IT_TXE, DISABLE);
            }
        }
    }

    /* LPUART in mode Receiver --------------------------------------------------*/
    if (LPUART_GetITStatus(LPUART, LPUART_IT_RXNE) == SET)
    {
        if (UsartMode == USART_MODE_TRANSMITTER)
        {
            AckBuffer[RxIndex++] = LPUART_ReceiveData(LPUART);
        }
        else
        {
            CmdBuffer[RxIndex] = LPUART_ReceiveData(LPUART);
            AckBuffer[RxIndex] = CmdBuffer[RxIndex];
            RxIndex++;
        }

        if ( (AckBuffer[0] == 0x55) && (AckBuffer[1] == 0x01))
        {
            HK_EVAL_LEDOn(LED1);
            HK_EVAL_LEDOn(LED2);
        }
    }
}


