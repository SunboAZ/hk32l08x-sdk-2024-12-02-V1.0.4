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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
CanRxMsg RxMessage, RxMessage1;
extern uint8_t KeyNumber;
extern CanTxMsg TxMessage, TxMessage1;
/* Private function prototypes -----------------------------------------------*/
extern void LED_Display(uint8_t Ledstatus);
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
}

/******************************************************************************/
/*                 HK32L0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (KEIL_Startup_hk32l0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles CAN request.
  * @retval None
  */
void LCD_CAN_IRQHandler(void)
{
    if (CAN_MessagePending(CAN_FIFO0) != 0)
    {
        CAN_Receive(CAN_FIFO0, &RxMessage);
        LED_Display(RxMessage.Data[0]);
        KeyNumber = RxMessage.Data[0];
    }

    if (CAN_MessagePending(CAN_FIFO1) != 0)
    {
        CAN_Receive(CAN_FIFO1, &RxMessage1);
        LED_Display(RxMessage1.Data[0]);
        KeyNumber = RxMessage1.Data[0];
    }
}
/**
  * @brief  This function handles EXTI 2 to 3 request.
  * @retval None
  */
void EXTI2_3_IRQHandler(void)
{
    if (KeyNumber < 0x2)

    {
        KeyNumber = 0x05;
    }

    LED_Display(--KeyNumber);

    TxMessage.Data[0] = KeyNumber;

    CAN_Transmit(&TxMessage);

    /* Clear the EXTI line 2 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line2);
}

/**
  * @brief  This function handles EXTI 4 to 15 request.
  * @retval None
  */
void EXTI4_15_IRQHandler(void)
{
    if (KeyNumber == 0x4)
    {
        KeyNumber = 0x00;
    }

    LED_Display(++KeyNumber);
    TxMessage1.Data[0] = KeyNumber;
    CAN_Transmit(&TxMessage1);

    /* Clear the EXTI line 13 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line13);
}

/**
  * @brief  This function handles PPP interrupt request.
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


