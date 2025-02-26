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

/* external variables ---------------------------------------------------------*/
extern __IO uint8_t Button_State;
extern __IO uint8_t Button_RTC;
extern __IO uint8_t StartEvent;
extern uint32_t BackupIndex;
uint32_t TimeIncrase;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define RTC_TAMP         1
#define KEY1_HOLD_2S     2
#define KEY1_PRESS       3
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/


/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
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
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    TimeIncrase++;
}

/******************************************************************************/
/*                 hk32l0xx Peripherals Interrupt Handlers                    */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (Keil_startup_hk32l0xx.s).                                           */
/******************************************************************************/

/**
  * @brief  This function handles Tamper pin interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
    if (RTC_GetITStatus(RTC_IT_TAMP1) != RESET)
    {
        Button_RTC = RTC_TAMP;
    }

    /* Clear the EXTIL line 19 */
    EXTI_ClearITPendingBit(EXTI_Line19);

    /* Clear Tamper pin interrupt pending bit */
    RTC_ClearITPendingBit(RTC_IT_TAMP1);
}

/**
  * @brief  This function handles External lines 2 to 3 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_3_IRQHandler(void)
{
    if ((EXTI_GetITStatus(KEY1_BUTTON_EXTI_LINE) != RESET) && (StartEvent != 0x0) && (BackupIndex < 10))
    {
        Button_State = KEY1_PRESS;
    }

    /* Clear the KEY1 EXTI  pending bit */
    EXTI_ClearITPendingBit(KEY1_BUTTON_EXTI_LINE);
}


