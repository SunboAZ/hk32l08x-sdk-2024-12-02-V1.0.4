/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  system_hk32l0xx.h
* @brief:     CMSIS Cortex-M0 Device Peripheral Access Layer System Source File.
*             This file contains the system clock configuration for HK32L0XX devices,
* @author:    AE Team
*******************************************************************************/

#include "hk32l0xx.h"

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup hk32l0xx_system
  * @{
  */

/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_HK32L0xx_H
#define __SYSTEM_HK32L0xx_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup HK32L0xx_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup HK32L0xx_System_Exported_types
  * @{
  */

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

/**
  * @}
  */

/** @addtogroup HK32L0xx_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup HK32L0xx_System_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup HK32L0xx_System_Exported_Functions
  * @{
  */

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_HK32L0xx_H */

/**
  * @}
  */


