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
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif  /* End of __cplusplus */

#endif /*__MAIN_H */

