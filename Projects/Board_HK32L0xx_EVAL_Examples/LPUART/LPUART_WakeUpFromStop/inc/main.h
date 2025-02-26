/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.h
* @brief:     Main program header.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "hk32l0xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define LPUARTx_TXIO_PORT                 GPIOA
#define LPUARTx_TX_PIN                    GPIO_Pin_9
#define LPUARTx_AF_TX_PIN                 GPIO_PinSource9
#define LPUARTx_TXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* TX IO clock Enable */
#define LPUARTx_TXIO_CLK                  RCC_AHBPeriph_GPIOA

#define LPUARTx_RXIO_PORT                 GPIOA
#define LPUARTx_RX_PIN                    GPIO_Pin_10
#define LPUARTx_AF_RX_PIN                 GPIO_PinSource10
#define LPUARTx_RXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* RX IO clock Enable */
#define LPUARTx_RXIO_CLK                  RCC_AHBPeriph_GPIOA

#define LPUARTx_AF_SELECT                 GPIO_AF_3               /* AFIO SELECT Reference datasheet 6.8 table*/

#define LPUARTx_IRQn                      LPUART_IRQn
#define LPUARTx_IRQHandler                LPUART_IRQHandler       /* LPUART1 interrupt handle */
#define LPUARTx_CLK_CMD                   RCC_APB1PeriphClockCmd  /* LPUART1 clock Enable */
#define LPUARTx_CLK                       RCC_APB1Periph_LPUART1

/* LPUART1 STOP mode config clock */
#define LPUARTx_STOPCLK_COFIG             RCC_LPUART1CLKConfig
#define LPUARTx_STOPCLK                   RCC_SELECTIONCLK_LSE
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif  /* End of __cplusplus */

#endif /*__MAIN_H */

