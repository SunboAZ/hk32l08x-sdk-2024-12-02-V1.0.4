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
/*  A plate processing flow  */
#ifdef AES_TWO_BOARD_A
    extern uint8_t ubButtonPress;
#endif
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
}

/******************************************************************************/
/*                 HK32L0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (KEIL_Startup_hk32l0xx.s).                                               */
/******************************************************************************/

#ifdef AES_TWO_BOARD_A
/**
  * @brief  This function handles external lines 2 to 3 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_3_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line2) != RESET)
    {
        ubButtonPress = 1;

        /* Clear the EXTI line 2 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}
/* Data received on board A */
extern  uint8_t BoardA_RxBuffer[AES_TEXT_SIZE];

/* received data length */
extern  uint8_t RxIndex;

/* reception completion flag */
extern  uint8_t RxDone;


/**
  * @brief  This function handles USART2 interrupt request.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
    /* Receive cached temporary variables */
    static uint8_t Rxindextemp = 0;

    if (USART_GetFlagStatus(USART2, USART_FLAG_ORE))
    {
        USART_ClearFlag(USART2, USART_FLAG_ORE);
    }

    if (USART_GetITStatus(USART2, USART_IT_RXNE))
    {
        /* Clear receive interrupt flag */
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        BoardA_RxBuffer[RxIndex++] = USART_ReceiveData(USART2);

        /* Ensure that AES_TEXT_SIZE bytes are received at once before processing */
        if (RxIndex == AES_TEXT_SIZE)
        {
            Rxindextemp = 1;
        }
        else
        {
            Rxindextemp = 0;
        }

        /* AES_TEXT_SIZE bytes received at most once */
        RxIndex %= AES_TEXT_SIZE;
    }

    if (USART_GetITStatus(USART2, USART_IT_IDLE))
    {
        /* finish clearing IDLE interrupt flag */
        USART_ClearITPendingBit(USART2, USART_IT_IDLE);

        if (Rxindextemp)
        {
            RxDone = 1;
        }
    }
}
#endif


/* B plate processing flow */
#ifdef AES_TWO_BOARD_B

/**
  * @brief  This function handles usart2 Handler.
  * @param  None
  * @retval None
  */
/* Data received on board B */
extern  uint8_t BoardB_RxBuffer[AES_TEXT_SIZE];
/* received data length */
extern  uint8_t RxIndex  ;
/* reception completion flag */
extern  uint8_t RxDone  ;
/**
  * @brief  This function handles USART2 interrupt request.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
    /* Receive cached temporary variables */
    static uint8_t Rxindextemp = 0;

    if (USART_GetFlagStatus(USART2, USART_FLAG_ORE))
    {
        USART_ClearFlag(USART2, USART_FLAG_ORE);
    }

    if (USART_GetITStatus(USART2, USART_IT_RXNE))
    {
        /*Clear receive interrupt flag*/
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        BoardB_RxBuffer[RxIndex++] = USART_ReceiveData(USART2);

        /* Ensure that AES_TEXT_SIZE bytes are received at once before processing */
        if (RxIndex == AES_TEXT_SIZE)
        {
            Rxindextemp = 1;
        }
        else
        {
            Rxindextemp = 0;
        }

        /*AES_TEXT_SIZE bytes received at most once*/
        RxIndex %= AES_TEXT_SIZE;
    }

    if (USART_GetITStatus(USART2, USART_IT_IDLE))
    {

        /* finish clearing IDLE interrupt flag */
        USART_ClearITPendingBit(USART2, USART_IT_IDLE);

        /* Make sure to receive 16 bytes at a time before processing */
        if (Rxindextemp)
        {
            RxDone = 1;
        }
    }
}
#endif

/**
  * @brief  This function handles PPP interrupt request.
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
