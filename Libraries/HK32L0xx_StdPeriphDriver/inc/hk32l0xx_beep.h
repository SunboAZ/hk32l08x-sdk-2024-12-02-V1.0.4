/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_beep.h
* @brief:     API file of beep module
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_BEEP_H
#define __HK32L0XX_BEEP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"


#define BEEPER_BUSY_FLAG                  ((uint32_t)0x80000000U)
#define BEEPER_CFGR_Value                 ((uint32_t)0x0000000AU)
#define BEEPER_CR_Value                   ((uint32_t)0x00000003U)
#define BEEPER_CFGR_BEEPER_Mask           ((uint32_t)0xFFFFFFF9U)
#define BEEPER_CFGR_TRGO_Mask             ((uint32_t)0xFFFFFFE7U)
/** @addtogroup BEEPER
  * @{
  */

/** @defgroup BEEPER_Exported_Types BEEPER_Exported_Types
  * @{
  */
/* Exported types ------------------------------------------------------------*/
typedef struct
{
    uint8_t BEEPER_Prescaler;
    uint8_t BEEPER_Clock;
} BEEPER_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** @defgroup BEEPER_Exported_Constants BEEPER_Exported_Constants
  * @{
  */

/** @defgroup BEEPER_Prescaler BEEPER_Prescaler
  * @{
  */
#define BEEPER_Prescaler_16               ((uint32_t)0x00000006U)
#define BEEPER_Prescaler_32               ((uint32_t)0x00000004U)
#define BEEPER_Prescaler_64               ((uint32_t)0x00000002U)
#define BEEPER_Prescaler_128              ((uint32_t)0x00000000U)
#define IS_BEEPER_PRESCALER(PRESCALER)    (((PRESCALER)==BEEPER_Prescaler_16) ||\
                                          ((PRESCALER)==BEEPER_Prescaler_32)  ||\
                                          ((PRESCALER)==BEEPER_Prescaler_64)  ||\
                                          ((PRESCALER)==BEEPER_Prescaler_128))
/**
  * @}
  */

/** @defgroup BEEPER_CLOCK BEEPER_CLOCK
  * @{
  */
#define BEEPER_CLOCK_PCLK                 ((uint32_t)0x00000010U)
#define BEEPER_CLOCK_HSE                  ((uint32_t)0x00000012U)
#define BEEPER_CLOCK_LSI                  ((uint32_t)0x00000000U)

#define IS_BEEPER_CLOCK(CLOCK)            ((CLOCK==(BEEPER_CLOCK_PCLK))||\
                                           (CLOCK==(BEEPER_CLOCK_HSE))|| \
                                           (CLOCK==(BEEPER_CLOCK_LSI)))
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/* Exported functions ------------------------------------------------------- */
void BEEPER_DeInit(void);
void BEEPER_Init(BEEPER_InitTypeDef * BEEPER_InitStruct);
void BEEPER_Cmd(FunctionalState NewState);
void BEEPER_ClockSelect(uint8_t BEEPER_CLOCK);
void BEEPER_SetPrescaler(uint8_t BEEPER_Prescaler);
FlagStatus BEEPER_ReadBeepStatus(void);


#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_BEEP_H */

