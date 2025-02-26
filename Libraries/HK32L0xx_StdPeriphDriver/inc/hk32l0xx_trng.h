/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_trng.h
* @brief:     API file of trng module
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_TRNG_H
#define __HK32L0XX_TRNG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup TRNG
  * @{
  */

/** @defgroup TRNG_Exported_Types  TRNG_Exported_Types
  * @{
  */
typedef struct
{
    uint32_t Option_Cycle;  //TRNG accumulation clock period
    uint32_t Mode;          // TRNG work mode
} TRNG_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup TRNG_Exported_Constants   TRNG_Exported_Constants
  * @{
  */

/** @defgroup TRNG_Exported_Constants_Group1  RNG Interrupt definition
  * @{
  */
#define TRNG_IT_DRDY  TRNG_SR_DRDY  /*!< Data Ready interrupt  */
#define TRNG_IT_SEI   TRNG_SR_SEIS  /*!< Seed error interrupt  */

#define IS_TRNG_GET_IT(IT) (((IT) == TRNG_IT_DRDY) || TRNG_IT_SEI)

#define IS_TRNG_IT(IT) ((IT) == TRNG_IT_SEI)

/**
  * @}
  */

/** @defgroup TRNG_Exported_Constants_Group2  RNG Flag definition
  * @{
  */
#define TRNG_FLAG_DRDY   TRNG_SR_DRDY  /*!< Data ready                 */
#define TRNG_FLAG_SECS   TRNG_SR_SECS  /*!< Seed error current status  */

#define TRNG_IT_IE       TRNG_CR_IE      /*!< TRNG Interrupt enable */

#define IS_TRNG_FLAG(FLAG) (((FLAG) == TRNG_FLAG_DRDY) || \
                            ((FLAG) == TRNG_FLAG_SECS))

#define TRNG_MODE_OPEN_ANOLOG       TRNG_CR_MODE
#define TRNG_MODE_CLOSED_ANOLOG     TRNG_CR_MODE_Pos
/**
  * @}
  */


/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

/* Initialization and Configuration functions *********************************/
void TRNG_Init(TRNG_InitTypeDef *TRNG_InitStruct);
void TRNG_DeInit(void);
void TRNG_Cmd(FunctionalState NewState);
ErrorStatus TRNG_GetRandomNumber(uint32_t *random32bit);
uint32_t TRNG_GetRandomNumberIT(void);
void TRNG_ITConfig( FunctionalState NewState);
FlagStatus TRNG_GetFlagStatus(uint32_t TRNG_FLAG);
void TRNG_ClearFlag(uint32_t TRNG_FLAG);
ITStatus TRNG_GetITStatus(uint32_t TRNG_IT);
void TRNG_ClearITPendingBit(uint32_t TRNG_IT);
void AES_TRNG_IRQHandler(void);


#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_TRNG_H */


