/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_irtim.h
* @brief:     This file contains all the functions prototypes for the IRTIM firmware
*             library.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_IRTIM_H
#define __HK32L0XX_IRTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"
#include "hk32l0xx_rcc.h"

/** @addtogroup IRTIM
  * @{
  */

/** @defgroup IRTIM_Exported_Functions IRTIM_Exported_Functions
  * @{
  */
void IR_OutGpioConfig(void);
void IRTIM_CarrierConfig(void);
void IRTIM_EnvelopeNvicConfig(void);
void IRTIM_EnvelopeConfig(void);
void Send_IRdata(unsigned char x_irdata);
void Write_IRdata(unsigned char p_irdata);
void IRTIM_Config(void);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_IRTIM_H */


