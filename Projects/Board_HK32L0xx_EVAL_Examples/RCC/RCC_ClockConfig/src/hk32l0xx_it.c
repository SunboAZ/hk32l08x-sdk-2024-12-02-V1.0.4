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
    /* This interrupt is generated when HSE clock fails */
    if (RCC_GetITStatus(RCC_IT_CSSHSE) != RESET)
    {
        /* At this stage: HSE, PLL are disabled (but no change on PLL config) and HSI
           is selected as system clock source */

        /* Enable HSE */
        RCC_HSEConfig(RCC_HSE_ON);

        /* Enable HSE Ready and PLL Ready interrupts */
        RCC_ITConfig(RCC_IT_HSERDY | RCC_IT_PLLRDY, ENABLE);

        /* Clear Clock Security System interrupt pending bit */
        RCC_ClearITPendingBit(RCC_IT_CSSHSE);

        /* Once HSE clock recover, the HSERDY interrupt is generated and in the RCC ISR
           routine the system clock will be reconfigured to its previous state (before
           HSE clock failure) */
    }
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
  * @brief  This function handles PPP interrupt request.
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  This function handles RCC interrupt request.
  * @param  None
  * @retval None
  */
void RCC_IRQHandler(void)
{
    if (RCC_GetITStatus(RCC_IT_HSERDY) != RESET)
    {
        /* Clear HSERDY interrupt pending bit */
        RCC_ClearITPendingBit(RCC_IT_HSERDY);

        /* Check if the HSE clock is still available */
        if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET)
        {
            /* Enable PLL: once the PLL is ready the PLLRDY interrupt is generated */
            RCC_PLLCmd(ENABLE);
        }
    }

    if (RCC_GetITStatus(RCC_IT_PLLRDY) != RESET)
    {
        /* Clear PLLRDY interrupt pending bit */
        RCC_ClearITPendingBit(RCC_IT_PLLRDY);

        /* Check if the PLL is still locked */
        if (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != RESET)
        {
            /* Select PLL as system clock source */
            RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        }
    }
}

