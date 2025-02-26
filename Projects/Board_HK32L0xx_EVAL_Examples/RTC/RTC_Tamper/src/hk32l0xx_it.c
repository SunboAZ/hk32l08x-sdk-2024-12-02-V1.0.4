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
extern uint32_t IsBackupRegReset(void);
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
/*                 hk32l0xx Peripherals Interrupt Handlers                    */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (Keil_startup_hk32l0xx.s).                                           */
/******************************************************************************/

/**
  * @brief  This function handles RTC interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
    if (RTC_GetFlagStatus(RTC_FLAG_TAMP1F) != RESET)
    {
        /* Tamper 1 detection event occurred */

        /* Check if RTC Backup Data registers are cleared */
        if (IsBackupRegReset() == 0)
        {
            /* OK, RTC Backup Data registers are reset as expected */
            printf("%s", "\r\n  **   RTC Backup Data registers are reset as expected            **\r\n");
        }
        else
        {
            /* RTC Backup Data registers are not reset */
            printf("%s", "\r\n  **   RTC Backup Data registers are not reset                    **\r\n");
        }

        /* Clear Tamper 1 pin Event(TAMP1F) pending flag */
        RTC_ClearFlag(RTC_FLAG_TAMP1F);
        /* Disable Tamper pin 1 */
        RTC_TamperCmd(RTC_Tamper_1, DISABLE);
        /* Enable Tamper pin */
        RTC_TamperCmd(RTC_Tamper_1, ENABLE);
    }

    /* Clear the EXTIL line 19 */
    EXTI_ClearITPendingBit(EXTI_Line19);
}


