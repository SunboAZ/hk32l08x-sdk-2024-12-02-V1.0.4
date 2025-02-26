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
extern CAN_FilterInitTypeDef  CAN_FilterInitStructure;
__IO uint8_t MsgReceived = 0;
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
  * @brief  This function handles CAN request.
  * @retval None
  */
void LCD_CAN_IRQHandler(void)
{
    if (CAN_GetFlagStatus(CAN_FLAG_FF0) != RESET)
    {
        /* Clears the CAN interrupt pending bit */
        CAN_ClearITPendingBit(CAN_IT_FF0);

        /* CAN filter init "FIFO1 " */
        CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 1;
        CAN_FilterInit(&CAN_FilterInitStructure);
    }

    if (CAN_GetFlagStatus(CAN_FLAG_FF1) != RESET)
    {
        /* Clears the CAN interrupt pending bit */
        CAN_ClearITPendingBit(CAN_IT_FF1);

        /* CAN filter init "FIFO0" */
        CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
        CAN_FilterInit(&CAN_FilterInitStructure);

        MsgReceived = 1;
    }
}

/**
  * @brief  This function handles PPP interrupt request.
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


