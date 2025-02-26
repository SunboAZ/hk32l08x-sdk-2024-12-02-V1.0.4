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
#include "hw_config.h"
#include "usb_istr.h"
#include "usb_lib.h"
#include "usb_pwr.h"

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

/**
  * @brief  This function handles USB interrupt request.
  * @param  None
  * @retval None
  */
void USB_DVSQ_IRQHandler(void)
{
    USB_Istr();

#ifdef USB_LOW_PWR_MGMT_SUPPORT
    EXTI_ClearITPendingBit(EXTI_Line18);
#endif  /* USB_LOW_PWR_MGMT_SUPPORT */
}

/**
  * @brief  This function handles USART interrupt request.
  * @param  None
  * @retval None
  */
void VCP_USARTx_IRQHandler(void)
{
    if (USART_GetITStatus(VCP_USARTx, USART_IT_RXNE) != RESET)
    {
        /* Send the received data to the PC Host*/
        USART_To_USB_Send_Data();
    }

    /* If overrun condition occurs, clear the ORE flag and recover communication */
    if (USART_GetFlagStatus(VCP_USARTx, USART_FLAG_ORE) != RESET)
    {
        (void)USART_ReceiveData(VCP_USARTx);
    }
}


/******************************************************************************/
/*                 hk32l0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (Keil_startup_hk32l0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


