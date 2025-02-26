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
extern uint8_t ubButtonPress;
extern uint8_t ubIsNbGenerated;
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

/**
  * @brief  This function handles EXTI2_3_IRQHandler Handler.
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


/**
  * @brief  This function handles AES_TRNG_EMACC_IRQHandler Handler.
  * @retval None
  */
void AES_TRNG_EMACC_IRQHandler(void)
{
    /*!< Seed error current status  */
    if (TRNG_GetITStatus(TRNG_IT_SEI) != RESET)
    {
        if (TRNG_GetFlagStatus(TRNG_FLAG_SECS) != RESET)
        {
            // disable the interrupt
            TRNG_ClearITPendingBit(TRNG_IT_SEI);
            ubIsNbGenerated = 2;
        }
    }

    if (TRNG_GetITStatus(TRNG_IT_DRDY) != RESET)
    {
        TRNG_ITConfig(DISABLE);
        ubIsNbGenerated = 1;
    }
}


