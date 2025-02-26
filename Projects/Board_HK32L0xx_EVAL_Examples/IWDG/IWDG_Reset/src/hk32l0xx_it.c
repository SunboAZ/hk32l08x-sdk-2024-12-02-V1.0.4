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
uint16_t IC1ReadValue1 = 0, IC1ReadValue2 = 0;
__IO uint16_t CaptureNumber = 0;
__IO uint32_t Capture = 0;

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
    TimingDelay_Decrement();
}

/******************************************************************************/
/*                 HK32L0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (KEIL_Startup_hk32l0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  This function handles External lines 2 to 3 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_3_IRQHandler(void)
{
    if (EXTI_GetITStatus(KEY1_BUTTON_EXTI_LINE) != RESET)
    {
        /* Clear the  EXTI line 2 pending bit */
        EXTI_ClearITPendingBit(KEY1_BUTTON_EXTI_LINE);

        /* As the following address is invalid (not mapped), a Hardfault exception
        will be generated with an infinite loop and when the IWDG counter reaches 0
        the IWDG reset occurs */
        *(__IO uint32_t *) 0x00040001 = 0xFF;
    }
}

#ifdef LSI_TIM_MEASURE
/**
  * @brief  This function handles TIM14 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM14_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM14, TIM_IT_CC1) != RESET)
    {
        if (CaptureNumber == 0)
        {
            /* Get the Input Capture value */
            IC1ReadValue1 = TIM_GetCapture1(TIM14);
        }
        else if (CaptureNumber == 1)
        {
            /* Get the Input Capture value */
            IC1ReadValue2 = TIM_GetCapture1(TIM14);

            /* Capture computation */
            if (IC1ReadValue2 > IC1ReadValue1)
            {
                Capture = (IC1ReadValue2 - IC1ReadValue1);
            }
            else
            {
                Capture = ((0xFFFF - IC1ReadValue1) + IC1ReadValue2);
            }

            /* Frequency computation */
            LsiFreq = (uint32_t) SystemCoreClock / Capture;
            LsiFreq *= 8;
        }

        CaptureNumber++;

        /* Clear TIM14 Capture compare interrupt pending bit */
        TIM_ClearITPendingBit(TIM14, TIM_IT_CC1);
    }
}
#endif /* LSI_TIM_MEASURE */

