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
#define countof(a)   (sizeof(a) / sizeof(*(a)))
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define USER_TIMEOUT                    ((uint32_t)0x64) /* Waiting 1s */

#define SPIy                               SPI1   /* SPI pins are remapped by software */
#define SPIy_CLK                           RCC_APB2Periph_SPI1
#define SPIy_GPIO                          GPIOA
#define SPIy_GPIO_CLK                      RCC_AHBPeriph_GPIOA
#define SPIy_PIN_NSS                       GPIO_Pin_4
#define SPIy_PIN_SCK                       GPIO_Pin_5
#define SPIy_PIN_MISO                      GPIO_Pin_6
#define SPIy_PIN_MOSI                      GPIO_Pin_7
#define SPIy_RCC                           RCC_APB2PeriphClockCmd
#define SPIy_GPIO_RCC                      RCC_AHBPeriphClockCmd

#define SPIy_PIN_NSS_AF                    GPIO_AF_0
#define SPIy_PIN_SCK_AF                    GPIO_AF_0
#define SPIy_PIN_MISO_AF                   GPIO_AF_0
#define SPIy_PIN_MOSI_AF                   GPIO_AF_0

#define SPIy_PIN_NSS_PinSource             GPIO_PinSource4
#define SPIy_PIN_SCK_PinSource             GPIO_PinSource5
#define SPIy_PIN_MISO_PinSource            GPIO_PinSource6
#define SPIy_PIN_MOSI_PinSource            GPIO_PinSource7

#define SPIz                               SPI1
#define SPIz_CLK                           RCC_APB2Periph_SPI1
#define SPIz_GPIO                          GPIOA
#define SPIz_GPIO_CLK                      RCC_AHBPeriph_GPIOA
#define SPIz_PIN_NSS                       GPIO_Pin_4
#define SPIz_PIN_SCK                       GPIO_Pin_5
#define SPIz_PIN_MISO                      GPIO_Pin_6
#define SPIz_PIN_MOSI                      GPIO_Pin_7
#define SPIz_RCC                           RCC_APB2PeriphClockCmd
#define SPIz_GPIO_RCC                      RCC_AHBPeriphClockCmd

#define SPIz_PIN_NSS_AF                    GPIO_AF_0
#define SPIz_PIN_SCK_AF                    GPIO_AF_0
#define SPIz_PIN_MISO_AF                   GPIO_AF_0
#define SPIz_PIN_MOSI_AF                   GPIO_AF_0

#define SPIz_PIN_NSS_PinSource             GPIO_PinSource4
#define SPIz_PIN_SCK_PinSource             GPIO_PinSource5
#define SPIz_PIN_MISO_PinSource            GPIO_PinSource6
#define SPIz_PIN_MOSI_PinSource            GPIO_PinSource7

#define MASTER 1
#define SLAVER 0


#define TXBUFFERSIZE                     (countof(TxBuffer) - 1)
#define RXBUFFERSIZE                     TXBUFFERSIZE

/* Define numbers of bytes to transmit from TxBuffer */
#define DATA_SIZE                        TXBUFFERSIZE

#define CMD_ACK                          0x16


#define SPIx_DR_ADDRESS                  0x4001300C
#define SPIx_TX_DMA_CHANNEL              DMA_Channel3
#define SPIx_TX_DMA_FLAG_TC              DMA1_FLAG_TC3
#define SPIx_TX_DMA_FLAG_GL              DMA1_FLAG_GL3
#define SPIx_RX_DMA_CHANNEL              DMA_Channel2
#define SPIx_RX_DMA_FLAG_TC              DMA1_FLAG_TC2
#define SPIx_RX_DMA_FLAG_GL              DMA1_FLAG_GL2

#define DMAx_CLK                         RCC_AHBPeriph_DMA


#define TIMx                             TIM2
#define TIMx_CLK                         RCC_APB1Periph_TIM2
#define TIMx_DMA_CHANNEL                 TIM_DMA_CC2

#define TIMx_TRIGGER_PIN                 GPIO_Pin_1
#define TIMx_TRIGGER_GPIO_PORT           GPIOA
#define TIMx_TRIGGER_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define TIMx_TRIGGER_SOURCE              GPIO_PinSource1
#define TIMx_TRIGGER_AF                  GPIO_AF_2
#define TIMx_CHANNEL_INIT                TIM_OC2Init
#define TIMx_CHANNEL_DMA_CHANNEL         DMA_Channel3
#define TIMx_CHANNEL_DMA_FLAG_TC         DMA1_FLAG_TC3
#define TIMx_CHANNEL_DMA_FLAG_GL         DMA1_FLAG_GL3

/* TIM2 Autoreload and Capture Compare register values */
#define TIM_ARR                          ((uint16_t)600)
#define TIM_CCR                          ((uint16_t)300)


/* Joystick Commands */
#define CMD_ONE                          0x15
#define CMD_ACK                          0x16
/* Exported functions ------------------------------------------------------- */
uint8_t GetVar_NbrOfData(void);

#ifdef __cplusplus
}
#endif  /* End of __cplusplus */

#endif /*__MAIN_H */

