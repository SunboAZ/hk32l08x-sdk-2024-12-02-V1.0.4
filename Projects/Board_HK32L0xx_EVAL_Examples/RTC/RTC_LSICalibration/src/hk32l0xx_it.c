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
extern __IO uint32_t CaptureNumber, PeriodValue;
uint32_t IC1ReadValue1 = 0, IC1ReadValue2 = 0;

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
}

/******************************************************************************/
/*                 hk32l0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (Keil_startup_hk32l0xx.s).                                               */
/******************************************************************************/


/**
  * @brief  This function handles TIM14 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM14_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM14, TIM_IT_CC1) != RESET)
    {
        /* Clear TIM14 Capture Compare 1 interrupt pending bit */
        TIM_ClearITPendingBit(TIM14, TIM_IT_CC1);

        if (CaptureNumber == 0)
        {
            /* Get the Input Capture value */
            IC1ReadValue1 = TIM_GetCapture1(TIM14);
            CaptureNumber = 1;
        }
        else if (CaptureNumber == 1)
        {
            /* Get the Input Capture value */
            IC1ReadValue2 = TIM_GetCapture1(TIM14);
            TIM_ITConfig(TIM14, TIM_IT_CC1, DISABLE);

            /* Capture computation */
            if (IC1ReadValue2 > IC1ReadValue1)
            {
                PeriodValue = (IC1ReadValue2 - IC1ReadValue1);
            }
            else
            {
                PeriodValue = ((0xFFFF - IC1ReadValue1) + IC1ReadValue2);
            }

            /* capture of two values is done */
            CaptureNumber = 2;
        }
    }
}

/**
  * @brief  This function handles RTC Wakeup global interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
    if (RTC_GetITStatus(RTC_IT_ALRA) != RESET)
    {
        RTC_TimeTypeDef RTC_TimeStructure;

        /* Toggle on LED1 */
        HK_EVAL_LEDToggle(LED1);

        /* Set the time to 00h 00mn 00s AM */
        RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
        RTC_TimeStructure.RTC_Hours   = 0x00;
        RTC_TimeStructure.RTC_Minutes = 0x00;
        RTC_TimeStructure.RTC_Seconds = 0x00;
        RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);
        RTC_ClearITPendingBit(RTC_IT_ALRA);
        EXTI_ClearITPendingBit(EXTI_Line17);
    }
}


