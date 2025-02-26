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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t TxBuffer[];
extern uint8_t RxBuffer[];
extern __IO uint8_t RxIndex;
extern __IO uint8_t TxIndex;
extern __IO ButtonMode_TypeDef PressedButton;

__IO uint8_t Counter = 0x00;
__IO uint32_t TimeOut = 0x00;
uint8_t  ComputedCRC = 0;
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
    if (Counter < 10)
    {
        Counter++;
    }
    else
    {
        Counter = 0x00;
        HK_EVAL_LEDToggle(LED2);
    }
}

/******************************************************************************/
/*                 HK32L0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (KEIL_Startup_hk32l0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles USRAT interrupt request.
  * @retval None
  */
void UART3_4_IRQHandler(void)
{
#ifdef MODE_TRANSMITTER

    /* ------------------ USART in mode Tramitter ------------------------------*/
    if (USART_GetITStatus(UART3, USART_IT_TXE) == SET)
    {
        if (TxIndex < 0x48)
        {
            /* Send TxBuffer data */
            USART_SendData(UART3, TxBuffer[TxIndex]);

            /* Compute 8-bit CRC */
            CRC_CalcCRC8bits(TxBuffer[TxIndex++]);

        }
        else if (TxIndex == 0x48)
        {
            /* Get computed computed value */
            TxBuffer[TxIndex] = (uint8_t)CRC_GetCRC();

            /* Reset CRC calculation unit */
            CRC_ResetDR();

            /* Send CRC computed value */
            USART_SendData(UART3, TxBuffer[TxIndex]);

            /* Disable the USARTx transmit data register empty interrupt */
            USART_ITConfig(UART3, USART_IT_TXE, DISABLE);

            /*Discard CRC sent value*/
            TxBuffer[TxIndex] = 0;

            /*reset TxBuffer index*/
            TxIndex = 0;
        }
    }

#else

    /* ------------------ USART in mode Receiver -------------------------------*/
    if (USART_GetITStatus(UART3, USART_IT_RXNE) == SET)
    {
        if (RxIndex < 0x48)
        {
            /* Receive the USART data */
            RxBuffer[RxIndex] = USART_ReceiveData(UART3);

            /* compute 8-bit CRC */
            CRC_CalcCRC8bits(RxBuffer[RxIndex++]);
        }
        else if (RxIndex == 0x48)
        {
            /* Get computed computed value */
            ComputedCRC = (uint8_t)CRC_GetCRC();

            /* Reset CRC calculation unit */
            CRC_ResetDR();

            /* Recive expected CRC value */
            RxBuffer[RxIndex] = USART_ReceiveData(UART3);

            /* Compare computed CRC and recived CRC values*/
            if (ComputedCRC == RxBuffer[RxIndex])
            {
                /* LED1 on */
                HK_EVAL_LEDOn(LED1);
            }
            else
            {
                /* LED1 off */
                HK_EVAL_LEDOff(LED1);
            }

            /* Reset RxBuffer index */
            RxIndex = 0;
        }
    }

#endif /* MODE_TRANSMITTER */
}

#ifdef MODE_TRANSMITTER
/**
  * @brief  This function handles External lines 0 to 1 interrupt request.
  * @retval None
  */
void EXTI2_3_IRQHandler(void)
{
    /* To detect user action on KEY1 button */
    if (EXTI_GetITStatus(EXTI_Line2) != RESET)
    {
        PressedButton = BUTTON_MODE_EXTI;

        /* Clear the KEY1 Button EXTI line pending bit */
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}
#endif /* MODE_TRANSMITTER */

/**
  * @brief  This function handles PPP interrupt request.
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


