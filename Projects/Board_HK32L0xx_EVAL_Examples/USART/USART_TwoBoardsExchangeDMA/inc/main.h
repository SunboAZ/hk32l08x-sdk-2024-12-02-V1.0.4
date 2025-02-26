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
#define USARTx_TDR_ADDRESS                0x40013828
#define USARTx_RDR_ADDRESS                0x40013824

#define USARTx_TX_DMA_CHANNEL            DMA_Channel4
#define USARTx_TX_DMA_FLAG_TC            DMA1_FLAG_TC4
#define USARTx_TX_DMA_Remap              DMA_CSELR_CH4_USART1_TX
#define USARTx_RX_DMA_CHANNEL            DMA_Channel3
#define USARTx_RX_DMA_FLAG_TC            DMA1_FLAG_TC3
#define USARTx_RX_DMA_Remap              DMA_CSELR_CH3_USART1_RX
#define USARTx                           USART1
#define MASTER                           0
#define SLAVER                           1
/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* Exported functions ------------------------------------------------------- */
#ifdef __cplusplus
}
#endif  /* End of __cplusplus */

#endif /*__MAIN_H */

