/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.h
* @brief:     Header for main.c file.
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
#include "string.h"
#include "hk32l0xx.h"
#include "hk32l0xx_adc.h"

#ifdef USE_HK32L0XX_EVAL
#include "hk32l0xx_eval.h"
#endif /* USE_HK32L0XX_EVAL */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void WaitForUserButtonPress(void);
void Delay(__IO uint32_t nCount);
#ifdef __cplusplus
}
#endif
#endif /*__MAIN_H */

