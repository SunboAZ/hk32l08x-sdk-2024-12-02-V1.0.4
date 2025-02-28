/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_exti.h
* @brief:     EXTI initialization and configuration
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_EXTI_H
#define __HK32L0XX_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"

/** @addtogroup EXTI EXTI
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Types EXTI_Exported_Types
  * @{
  */

/**
  * @brief EXTI mode enumeration
  */
typedef enum
{
    EXTI_Mode_Interrupt = 0x00,
    EXTI_Mode_Event = 0x04
} EXTIMode_TypeDef;

/**
  * @brief  EXTI Trigger enumeration
  */
typedef enum
{
    EXTI_Trigger_Rising = 0x08,
    EXTI_Trigger_Falling = 0x0C,
    EXTI_Trigger_Rising_Falling = 0x10
} EXTITrigger_TypeDef;

/**
  * @brief  EXTI Init Structure definition
  */
typedef struct
{
    uint32_t EXTI_Line;               /*!< Specifies the EXTI lines to be enabled or disabled.
                                           This parameter can be any combination of @ref EXTI_Lines */
    EXTIMode_TypeDef EXTI_Mode;       /*!< Specifies the mode for the EXTI lines.
                                           This parameter can be a value of @ref EXTIMode_TypeDef */
    EXTITrigger_TypeDef EXTI_Trigger; /*!< Specifies the trigger signal active edge for the EXTI lines.
                                           This parameter can be a value of @ref EXTITrigger_TypeDef */
    FunctionalState EXTI_LineCmd;     /*!< Specifies the new state of the selected EXTI lines.
                                           This parameter can be set either to ENABLE or DISABLE */
} EXTI_InitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup EXTI_Exported_Constants EXTI_Exported_Constants
  * @{
  */

/** @defgroup EXTI_Lines EXTI_Lines
  * @{
  */
#define EXTI_Line0       ((uint32_t)0x00000001)  /*!< External interrupt line 0  */
#define EXTI_Line1       ((uint32_t)0x00000002)  /*!< External interrupt line 1  */
#define EXTI_Line2       ((uint32_t)0x00000004)  /*!< External interrupt line 2  */
#define EXTI_Line3       ((uint32_t)0x00000008)  /*!< External interrupt line 3  */
#define EXTI_Line4       ((uint32_t)0x00000010)  /*!< External interrupt line 4  */
#define EXTI_Line5       ((uint32_t)0x00000020)  /*!< External interrupt line 5  */
#define EXTI_Line6       ((uint32_t)0x00000040)  /*!< External interrupt line 6  */
#define EXTI_Line7       ((uint32_t)0x00000080)  /*!< External interrupt line 7  */
#define EXTI_Line8       ((uint32_t)0x00000100)  /*!< External interrupt line 8  */
#define EXTI_Line9       ((uint32_t)0x00000200)  /*!< External interrupt line 9  */
#define EXTI_Line10      ((uint32_t)0x00000400)  /*!< External interrupt line 10 */
#define EXTI_Line11      ((uint32_t)0x00000800)  /*!< External interrupt line 11 */
#define EXTI_Line12      ((uint32_t)0x00001000)  /*!< External interrupt line 12 */
#define EXTI_Line13      ((uint32_t)0x00002000)  /*!< External interrupt line 13 */
#define EXTI_Line14      ((uint32_t)0x00004000)  /*!< External interrupt line 14 */
#define EXTI_Line15      ((uint32_t)0x00008000)  /*!< External interrupt line 15 */
#define EXTI_Line16      ((uint32_t)0x00010000)  /*!< External interrupt line 16 Connected to the PVD Output*/
#define EXTI_Line17      ((uint32_t)0x00020000)  /*!< Internal interrupt line 17 Connected to the RTC Alarm event */
#define EXTI_Line18      ((uint32_t)0x00040000)  /*!< Internal interrupt line 18 Connected to the USB event */
#define EXTI_Line19      ((uint32_t)0x00080000)  /*!< Internal interrupt line 19 Connected to the RTC Tamper and Time Stamp events */
#define EXTI_Line20      ((uint32_t)0x00100000)  /*!< Internal interrupt line 20 Connected to the RTC wakeup event */
#define EXTI_Line21      ((uint32_t)0x00200000)  /*!< Internal interrupt line 21 Connected to the Comparator 1 event*/
#define EXTI_Line22      ((uint32_t)0x00400000)  /*!< Internal interrupt line 22 Connected to the Comparator 2 event*/
#define EXTI_Line23      ((uint32_t)0x00800000)  /*!< Internal interrupt line 23 Connected to the I2C1 wakeup event*/
#define EXTI_Line24      ((uint32_t)0x01000000)  /*!< Internal interrupt line 24 Connected to the I2C2 wakeup event*/
#define EXTI_Line25      ((uint32_t)0x02000000)  /*!< Internal interrupt line 25 Connected to the USART1 wakeup event*/
#define EXTI_Line26      ((uint32_t)0x04000000)  /*!< Internal interrupt line 26 Connected to the USART2 wakeup event*/
#define EXTI_Line28      ((uint32_t)0x10000000)  /*!< Internal interrupt line 28 Connected to the Low Power Uart 1 event*/
#define EXTI_Line31      ((uint32_t)0x80000000)  /*!< Internal interrupt line 31 Connected to the ADC AWD event*/
/**
  * @}
  */

/** @defgroup EXTI_Lines_check EXTI_Lines_check
  * @{
  */
#define IS_EXTI_MODE(MODE) (((MODE) == EXTI_Mode_Interrupt) || ((MODE) == EXTI_Mode_Event))
#define IS_EXTI_TRIGGER(TRIGGER) (((TRIGGER) == EXTI_Trigger_Rising)  || \
                                  ((TRIGGER) == EXTI_Trigger_Falling) || \
                                  ((TRIGGER) == EXTI_Trigger_Rising_Falling))
#define IS_EXTI_LINE(LINE) ((((LINE) & (uint32_t)0x00000000) == 0x00) && ((LINE) != (uint16_t)0x00))
#define IS_GET_EXTI_LINE(LINE) (((LINE) == EXTI_Line0)  || ((LINE) == EXTI_Line1)  || \
                                ((LINE) == EXTI_Line2)  || ((LINE) == EXTI_Line3)  || \
                                ((LINE) == EXTI_Line4)  || ((LINE) == EXTI_Line5)  || \
                                ((LINE) == EXTI_Line6)  || ((LINE) == EXTI_Line7)  || \
                                ((LINE) == EXTI_Line8)  || ((LINE) == EXTI_Line9)  || \
                                ((LINE) == EXTI_Line10) || ((LINE) == EXTI_Line11) || \
                                ((LINE) == EXTI_Line12) || ((LINE) == EXTI_Line13) || \
                                ((LINE) == EXTI_Line14) || ((LINE) == EXTI_Line15) || \
                                ((LINE) == EXTI_Line16) || ((LINE) == EXTI_Line17) || \
                                ((LINE) == EXTI_Line18) || ((LINE) == EXTI_Line19) || \
                                ((LINE) == EXTI_Line20) || ((LINE) == EXTI_Line21) || \
                                ((LINE) == EXTI_Line22) || ((LINE) == EXTI_Line23) || \
                                ((LINE) == EXTI_Line24) || ((LINE) == EXTI_Line25) || \
                                ((LINE) == EXTI_Line26) || ((LINE) == EXTI_Line28) || \
                                ((LINE) == EXTI_Line31))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/** @defgroup EXTI_Exported_Functions EXTI_Exported_Functions
  * @{
  */
/* Function used to set the EXTI configuration to the default reset state *****/
void EXTI_DeInit(void);
/* Initialization and Configuration functions *********************************/
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line);
/* Interrupts and flags management functions **********************************/
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);
void EXTI_ClearFlag(uint32_t EXTI_Line);
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
void EXTI_ClearITPendingBit(uint32_t EXTI_Line);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_EXTI_H */


