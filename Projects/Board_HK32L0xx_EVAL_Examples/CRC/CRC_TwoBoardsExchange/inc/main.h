/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.h
* @brief:     Header for main.c module
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
/* Uncomment the line below if you will use the TRANSMITTER mode */
//#define MODE_TRANSMITTER
/* Uncomment the line below if you will use the RECIVER mode */
#define MODE_RECEIVER

#define TXBUFFERSIZE                     (countof(TxBuffer) - 1)
#define RXBUFFERSIZE                     TXBUFFERSIZE + 1
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif  /* End of __cplusplus */

#endif /*__MAIN_H */

