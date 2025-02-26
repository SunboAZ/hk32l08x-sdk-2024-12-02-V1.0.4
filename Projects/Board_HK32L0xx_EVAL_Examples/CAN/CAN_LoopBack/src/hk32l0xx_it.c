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
extern __IO uint32_t ret;
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
  * @param  None
  * @retval None
  */
void LCD_CAN_IRQHandler(void)
{
    if (CAN_GetITStatus(CAN_IT_FMP0) != RESET)
    {
        CanRxMsg RxMessage;

        RxMessage.StdId = 0x00;
        RxMessage.ExtId = 0x00;
        RxMessage.IDE = 0;
        RxMessage.DLC = 0;
        RxMessage.FMI = 0;
        RxMessage.Data[0] = 0x00;
        RxMessage.Data[1] = 0x00;

        CAN_Receive(CAN_FIFO0, &RxMessage);

        if ((RxMessage.ExtId == 0x1234) && (RxMessage.IDE == CAN_ID_EXT)
                && (RxMessage.DLC == 2) && ((RxMessage.Data[1] | (RxMessage.Data[0] << 8)) == 0xDECA))
        {
            ret = 1;
        }
        else
        {
            ret = 0;
        }
    }
}

/**
  * @brief  This function handles PPP interrupt request.
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


