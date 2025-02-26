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

/* external functions ---------------------------------------------------------*/
extern void Display_CurDateTime(void);
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
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
}

/******************************************************************************/
/*                 hk32l0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (Keil_startup_hk32l0xx.s).                                               */
/******************************************************************************/


/**
  * @brief  This function handles RTC_IRQ Handler.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
    if (RTC_GetITStatus(RTC_IT_ALRA) == SET)
    {
        printf("\r\n Notice:Alarm A Occured... \r\n");
        RTC_ClearITPendingBit(RTC_IT_ALRA);
    }

    if (RTC_GetITStatus(RTC_IT_ALRB) == SET)
    {
        printf("\r\n Notice:Alarm B Occured... \r\n");
        RTC_ClearITPendingBit(RTC_IT_ALRB);
    }

    /* Clear the EXTIL line 17 */
    EXTI_ClearITPendingBit(EXTI_Line17);

}



/**
  * @brief  This function handles EXTI2_3_IRQn Handler.
  * @param  None
  * @retval None
  */
void EXTI2_3_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line2) == SET)
    {
        Display_CurDateTime();
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}


/**
  * @}
  */

/**
  * @}
  */

