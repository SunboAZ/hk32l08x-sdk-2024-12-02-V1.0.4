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
#include "hk32l0xx_lp_modes.h"

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
  * @brief  This function handles EXTI Lines 4 to 15 interrupts requests.
  * @retval None
  */
void EXTI4_15_IRQHandler(void)
{
    if (EXTI_GetFlagStatus(EXTI_Line13) != RESET)
    {
        /* Disable the Low Power Run mode */
        PWR_DisableLowPowerRunMode();

        /* Enable HSE */
        RCC_HSEConfig(RCC_HSE_ON);

        while (RCC_WaitForHSEStartUp() != SUCCESS)
        {
        }

        /* Configures the PLL clock source to HSE */
        RCC_PLLConfig(RCC_PLLSource_HSE, RCC_PLLMul_6);

        /* Enable PLL */
        RCC_PLLCmd(ENABLE);

        /* Configures the System clock to PLL CLK */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        /* Clear EXTI line13 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line13);
    }
}


/**
  * @brief  This function handles PPP interrupt request.
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


