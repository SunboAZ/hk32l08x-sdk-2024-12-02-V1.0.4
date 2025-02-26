/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_dbgmcu.h
* @brief:     DBGMCU initialization and configuration
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_DBGMCU_H
#define __HK32L0XX_DBGMCU_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"

/** @addtogroup DBGMCU DBGMCU
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup DBGMCU_Exported_Constants DBGMCU_Exported_Constants
  * @{
  */

/** @defgroup DBGMCU_LowPowerMode DBGMCU_LowPowerMode
  * @{
  */
#define DBGMCU_SLEEP                 ((uint32_t)0x00000001)
#define DBGMCU_STOP                  ((uint32_t)0x00000002)
#define DBGMCU_STANDBY               ((uint32_t)0x00000004)
#define IS_DBGMCU_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFFF8) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */

/** @defgroup DBGMCU_StopDebug DBGMCU_StopDebug
  * @{
  */
#define DBGMCU_TIM2_STOP             ((uint32_t)0x00000001)
#define DBGMCU_TIM3_STOP             ((uint32_t)0x00000002)
#define DBGMCU_TIM14_STOP            ((uint32_t)0x00000100)
#define DBGMCU_RTC_STOP              ((uint32_t)0x00000400)
#define DBGMCU_WWDG_STOP             ((uint32_t)0x00000800)
#define DBGMCU_IWDG_STOP             ((uint32_t)0x00001000)
#define DBGMCU_I2C1_SMBUS_TIMEOUT    ((uint32_t)0x00200000)
#define DBGMCU_I2C2_SMBUS_TIMEOUT    ((uint32_t)0x00400000)
#define DBGMCU_CAN_STOP              ((uint32_t)0x02000000)
#define IS_DBGMCU_APB1PERIPH(PERIPH) ((((PERIPH) & 0x1D9FE2FC) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */

/** @defgroup DBGMCU_TIM_StopDebug DBGMCU_TIM_StopDebug
  * @{
  */
#define DBGMCU_TIM1_STOP             ((uint32_t)0x00000800)
#define DBGMCU_TIM15_STOP            ((uint32_t)0x00010000)
#define DBGMCU_TIM16_STOP            ((uint32_t)0x00020000)
#define DBGMCU_TIM17_STOP            ((uint32_t)0x00040000)
#define IS_DBGMCU_APB2PERIPH(PERIPH) ((((PERIPH) & 0xFFF8F7FF) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @defgroup DBGMCU_Exported_Functions DBGMCU_Exported_Functions
  * @{
  */
uint32_t DBGMCU_GetREVID(void);
uint32_t DBGMCU_GetDEVID(void);
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);
void DBGMCU_APB1PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);
void DBGMCU_APB2PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_DBGMCU_H */

/************************ (C) COPYRIGHT HKMicrochip *****END OF FILE****/
