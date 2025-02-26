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
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t RecvFlag;
extern uint8_t SendFlag;
extern uint16_t direction;
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
  * @brief  This function handles I2Cx DMA interrupt request,
  *         its TX DMA channel interrupt is same with RX DMA channel interrupt.
  * @retval None
  */
void I2C_COMx_DMATX_IRQHandle(void)
{
    /* send channel finsh */
    if (DMA_GetITStatus(I2C_COMx_TXIT_TC))
    {
#ifdef I2C_MASTER

#else
        SendFlag = 1;
#endif

        DMA_ClearITPendingBit(I2C_COMx_TXIT_TC);
    }

    if (DMA_GetITStatus(I2C_COMx_RXIT_TC))
    {
#ifdef I2C_MASTER /*Generate stop signal in host mode after recv data finsh*/
        I2C_GenerateSTOP(I2C_COMx, ENABLE);
#endif
        RecvFlag = 1;
        DMA_ClearITPendingBit(I2C_COMx_RXIT_TC);
    }
}


/**
  * @brief  This function handles I2Cx interrupt request.
  * @retval None
  */
void I2C_COMx_IRQHandler(void)
{
    /* Address matching interrupt */
    if (I2C_GetITStatus(I2C_COMx, I2C_IT_ADDR))
    {
        I2C_ClearITPendingBit(I2C_COMx, I2C_IT_ADDR);
        direction = I2C_GetTransferDirection(I2C_COMx);

    }
}

/**
  * @brief  This function handles PPP interrupt request.
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


