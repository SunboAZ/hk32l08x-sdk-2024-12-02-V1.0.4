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
extern __IO uint8_t SMbusAlertOccurred;
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
  * @brief  This function handles I2C1 Error interrupt request.
  * @param  None
  * @retval None
  */
void I2C1_IRQHandler(void)
{
    /* Check on I2C1 SMBALERT flag and clear it */
    if (I2C_GetITStatus(I2C1, I2C_IT_ALERT))
    {
        I2C_ClearITPendingBit(I2C1, I2C_IT_ALERT);
        SMbusAlertOccurred++;
    }

    /* Check on I2C1 Time out flag and clear it */
    if (I2C_GetITStatus(I2C1, I2C_IT_TIMEOUT))
    {
        I2C_ClearITPendingBit(I2C1, I2C_IT_TIMEOUT);
    }

    /* Check on I2C1 Arbitration Lost flag and clear it */
    if (I2C_GetITStatus(I2C1, I2C_IT_ARLO))
    {
        I2C_ClearITPendingBit(I2C1, I2C_IT_ARLO);
    }

    /* Check on I2C1 PEC error flag and clear it */
    if (I2C_GetITStatus(I2C1, I2C_IT_PECERR))
    {
        I2C_ClearITPendingBit(I2C1, I2C_IT_PECERR);
    }

    /* Check on I2C1 Overrun/Underrun error flag and clear it */
    if (I2C_GetITStatus(I2C1, I2C_IT_OVR))
    {
        I2C_ClearITPendingBit(I2C1, I2C_IT_OVR);
    }

    /* Check on I2C1 Acknowledge failure error flag and clear it */
    if (I2C_GetITStatus(I2C1, I2C_IT_NACKF))
    {
        I2C_ClearITPendingBit(I2C1, I2C_IT_NACKF);
    }

    /* Check on I2C1 Bus error flag and clear it */
    if (I2C_GetITStatus(I2C1, I2C_IT_BERR))
    {
        I2C_ClearITPendingBit(I2C1, I2C_IT_BERR);
    }
}
/**
  * @brief  This function handles PPP interrupt request.
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


