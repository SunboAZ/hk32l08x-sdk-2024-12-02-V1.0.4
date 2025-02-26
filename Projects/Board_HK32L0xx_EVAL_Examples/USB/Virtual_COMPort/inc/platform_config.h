/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  platform_config.h
* @brief:     Evaluation board specific configuration file.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_conf.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Define if Low power mode is enabled; it allows entering the device into
   STOP mode following USB Suspend event, and wakes up after the USB wakeup
   event is received. */
//#define USB_LOW_PWR_MGMT_SUPPORT

/*Unique Devices IDs register set*/
#define         ID1          (0x1FFFF7AC)
#define         ID2          (0x1FFFF7B0)
#define         ID3          (0x1FFFF7B4)

#define USB_DISCONNECT                      GPIOD
#define USB_DISCONNECT_PIN                  GPIO_Pin_6
#define RCC_AHBPeriph_GPIO_DISCONNECT       RCC_AHBPeriph_GPIOD
//#define ADC1_DR_Address                     ((uint32_t)0x4001244C)

#define RCC_AHBPeriph_ALLGPIO               (RCC_AHBPeriph_GPIOA | \
                                             RCC_AHBPeriph_GPIOB | \
                                             RCC_AHBPeriph_GPIOC | \
                                             RCC_AHBPeriph_GPIOD | \
                                             RCC_AHBPeriph_GPIOF )

/* UART defines (can be ported to any other devices) */
#define VCP_USARTx                        UART3
#define VCP_USARTx_CLK                    RCC_APB1Periph_UART3

#define VCP_USARTx_TX_PIN                 GPIO_Pin_4
#define VCP_USARTx_TX_GPIO_PORT           GPIOA
#define VCP_USARTx_TX_SOURCE              GPIO_PinSource4
#define VCP_USARTx_TX_AF                  GPIO_AF_5
#define VCP_USARTx_TX_GPIO_CLK            RCC_AHBPeriph_GPIOA

#define VCP_USARTx_RX_PIN                 GPIO_Pin_5
#define VCP_USARTx_RX_GPIO_PORT           GPIOA
#define VCP_USARTx_RX_SOURCE              GPIO_PinSource5
#define VCP_USARTx_RX_AF                  GPIO_AF_5
#define VCP_USARTx_RX_GPIO_CLK            RCC_AHBPeriph_GPIOA

#define VCP_USARTx_IRQn                   UART3_4_IRQn
#define VCP_USARTx_IRQHandler             UART3_4_IRQHandler

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /*__PLATFORM_CONFIG_H */

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/

