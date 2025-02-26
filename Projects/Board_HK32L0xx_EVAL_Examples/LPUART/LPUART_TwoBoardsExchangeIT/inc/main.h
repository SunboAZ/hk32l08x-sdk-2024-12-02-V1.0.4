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
#define MASTER  1
#define SLAVER  0
#define DEVICE  SLAVER

#define USER_TIMEOUT                    ((uint32_t)0x64) /* Waiting 1s */

/* USART Mode Selected */
#define USART_MODE_TRANSMITTER           0x00
#define USART_MODE_RECEIVER              0x01

/* USART Transaction Type use in slave to slect phase */
#define USART_TRANSACTIONTYPE_CMD        0x00
#define USART_TRANSACTIONTYPE_DATA       0x01

/* Joystick Commands */
#define CMD_RIGHT                        0x55
#define CMD_LEFT                         0xAA
#define CMD_UP                           0x33
#define CMD_DOWN                         0xCC
#define CMD_SEL                          0xFF

#define CMD_ACK                          0x66

/* Define numbers of bytes to transmit from TxBuffer */
#define CMD_RIGHT_SIZE                   0x01
#define CMD_LEFT_SIZE                    0x05
#define CMD_UP_SIZE                      0x14
#define CMD_DOWN_SIZE                    0x1E



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
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif  /* End of __cplusplus */

#endif /*__MAIN_H */

