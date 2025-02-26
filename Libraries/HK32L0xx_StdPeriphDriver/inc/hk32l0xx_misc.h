/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_misc.h
* @brief:     MISC initialization and configuration
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_MISC_H
#define __HK32L0XX_MISC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"

/** @addtogroup MISC MISC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup MISC_Exported_Types MISC_Exported_Types
  * @{
  */

/**
  * @brief  NVIC Init Structure definition
  */
typedef struct
{
    uint8_t NVIC_IRQChannel;             /*!< Specifies the IRQ channel to be enabled or disabled.
                                            This parameter can be a value of IRQn_Type */
    uint8_t NVIC_IRQChannelPriority;     /*!< Specifies the priority level for the IRQ channel specified
                                            in NVIC_IRQChannel. This parameter can be a value between 0 and 3 */
    FunctionalState NVIC_IRQChannelCmd;  /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                            will be enabled or disabled.This parameter can be set either to
                                            ENABLE or DISABLE */
} NVIC_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** @defgroup MISC_Exported_Constants MISC_Exported_Constants
  * @{
  */

/** @defgroup MISC_System_Low_Power MISC_System_Low_Power
  * @{
  */
#define NVIC_LP_SEVONPEND            ((uint8_t)0x10)
#define NVIC_LP_SLEEPDEEP            ((uint8_t)0x04)
#define NVIC_LP_SLEEPONEXIT          ((uint8_t)0x02)
#define IS_NVIC_LP(LP) (((LP) == NVIC_LP_SEVONPEND) || \
                        ((LP) == NVIC_LP_SLEEPDEEP) || \
                        ((LP) == NVIC_LP_SLEEPONEXIT))
/**
  * @}
  */

/** @defgroup MISC_Preemption_Priority_Group MISC_Preemption_Priority_Group
  * @{
  */
#define IS_NVIC_PRIORITY(PRIORITY)  ((PRIORITY) < 0x04)
/**
  * @}
  */

/** @defgroup MISC_SysTick_clock_source MISC_SysTick_clock_source
  * @{
  */
#define SysTick_CLKSource_HCLK_Div8    ((uint32_t)0xFFFFFFFB)
#define SysTick_CLKSource_HCLK         ((uint32_t)0x00000004)
#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SysTick_CLKSource_HCLK) || \
                                       ((SOURCE) == SysTick_CLKSource_HCLK_Div8))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/** @defgroup MISC_Exported_Functions MISC_Exported_Functions
  * @{
  */
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_MISC_H */



