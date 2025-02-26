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
__IO uint32_t step = 1;
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
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    /* Generate TIM1 COM event by software */
    TIM_GenerateEvent(TIM1, TIM_EventSource_COM);
}

/**
  * @brief  This function handles TIM1 Trigger and commutation interrupts requests.
  * @param  None
  * @retval None
  */
void TIM1_IRQHandler(void)
{
    /* Clear TIM1 COM pending bit */
    TIM_ClearITPendingBit(TIM1, TIM_IT_COM);

    if (step == 1)
    {
        /* Next step: Step 2 Configuration ---------------------------- */

        /*  Channel3 configuration */
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);

        /*  Channel1 configuration */
        TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);

        /*  Channel2 configuration */
        TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1 );
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable);
        step++;
    }
    else if (step == 2)
    {
        /* Next step: Step 3 Configuration ---------------------------- */

        /*  Channel2 configuration */
        TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable);

        /*  Channel3 configuration */
        TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);

        /*  Channel1 configuration */
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);
        step++;
    }
    else if (step == 3)
    {
        /* Next step: Step 4 Configuration ---------------------------- */

        /*  Channel3 configuration */
        TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);

        /*  Channel2 configuration */
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);

        /*  Channel1 configuration */
        TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable);
        step++;
    }
    else if (step == 4)
    {
        /* Next step: Step 5 Configuration ---------------------------- */

        /*  Channel3 configuration */
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);

        /*  Channel1 configuration */
        TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable);

        /*  Channel2 configuration */
        TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);
        step++;
    }
    else if (step == 5)
    {
        /* Next step: Step 6 Configuration ---------------------------- */

        /*  Channel3 configuration */
        TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable);

        /*  Channel1 configuration */
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);

        /*  Channel2 configuration */
        TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);
        step++;
    }
    else
    {
        /* Next step: Step 1 Configuration ---------------------------- */

        /*  Channel1 configuration */
        TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);

        /*  Channel3 configuration */
        TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable);

        /*  Channel2 configuration */
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);
        step = 1;
    }
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


