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
extern uint8_t TxBuffer[];
extern  uint8_t RxBuffer[];
extern __IO uint8_t Rx_Idx;
extern __IO uint8_t Tx_Idx;
extern __IO uint8_t CmdTransmitted;
extern __IO uint8_t CmdReceived;
extern __IO uint8_t CmdStatus;

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
  * @brief  This function handles PPP interrupt request.
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  This function handles SPI2 Handler.
  * @param  None
  * @retval None
  */
void SPI1_IRQHandler(void)
{
#if (DEVICE == MASTER)

    if (SPIorI2S_GetITStatus(SPIy, SPI_I2S_IT_TXE) == SET)
    {
        if (CmdStatus == 0x00)
        {
            while (SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET)
            {
            }

            CmdTransmitted = 1;
            SPI_SendData8(SPIy, CmdTransmitted);
            CmdStatus = 0x01;
        }
        else
        {
            while (SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET)
            {
            }

            SPI_SendData8(SPIy, TxBuffer[Tx_Idx++]);

            if (Tx_Idx >= GetVar_NbrOfData())
            {
                /* Disable the Tx buffer empty interrupt */
                SPIorI2S_ITConfig(SPIy, SPI_I2S_IT_TXE, DISABLE);
            }
        }
    }

    /* SPI in Master Receiver mode--------------------------------------- */
    if (SPIorI2S_GetITStatus(SPIy, SPI_I2S_IT_RXNE) == SET)
    {
        if (CmdReceived == 0x00)
        {
            while (SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET)
            {
            }

            CmdReceived = SPI_ReceiveData8(SPIy);
            Rx_Idx = 0x00;
        }
        else
        {
            while (SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET)
            {
            }

            RxBuffer[Rx_Idx++] = SPI_ReceiveData8(SPIy);
        }
    }

    /* SPI Error interrupt--------------------------------------- */
    if (SPIorI2S_GetITStatus(SPIy, SPI_I2S_IT_OVR) == SET)
    {
        SPI_ReceiveData8(SPIy);
        SPIorI2S_GetITStatus(SPIy, SPI_I2S_IT_OVR);
    }

#elif (DEVICE == SLAVER)

    /* SPI in Slave Tramitter mode--------------------------------------- */
    if (SPIorI2S_GetITStatus(SPIz, SPI_I2S_IT_TXE) == SET)
    {
        while (SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET)
        {
        }

        SPI_SendData8(SPIz, TxBuffer[Tx_Idx++]);

        if (Tx_Idx >=  GetVar_NbrOfData())
        {
            /* Disable the Tx buffer empty interrupt */
            SPIorI2S_ITConfig(SPIz, SPI_I2S_IT_TXE, DISABLE);
        }
    }

    /* SPI in Slave Receiver mode--------------------------------------- */
    if (SPIorI2S_GetITStatus(SPIz, SPI_I2S_IT_RXNE) == SET)
    {
        if (CmdReceived == 0x00)
        {
            while (SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET)
            {
            }

            CmdReceived = SPI_ReceiveData8(SPIz);
            CmdStatus = 0x01;
        }
        else
        {
            while (SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET)
            {
            }

            RxBuffer[Rx_Idx++] = SPI_ReceiveData8(SPIz);
        }
    }

    /* SPI Error interrupt--------------------------------------- */
    if (SPIorI2S_GetITStatus(SPIz, SPI_I2S_IT_OVR) == SET)
    {
        SPI_ReceiveData8(SPIz);
        SPIorI2S_GetITStatus(SPIz, SPI_I2S_IT_OVR);
    }

#endif
}
