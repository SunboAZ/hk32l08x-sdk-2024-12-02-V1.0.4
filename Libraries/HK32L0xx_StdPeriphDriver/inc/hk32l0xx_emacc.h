/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_emacc.h
* @brief:     This file contains all the functions prototypes for the AES firmware
*             library.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_EMACC_H
#define __HK32L0XX_EMACC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"


/** @addtogroup EMACC EMACC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup EMACC_Exported_Types EMACC_Exported_Types
  * @{
  */

/**
  * @brief Handle of a PI component
  */
typedef struct
{
    uint32_t  wKpiGain;              /**< gain used by PI component */
    uint32_t  wUpperIntegralLimit;  /**< Upper limit used to saturate the integral
                                       term given by integral of process variable error */
    uint32_t  wLowerIntegralLimit;  /**< Lower limit used to saturate the integral
                                       term given by Ki / Ki divisor * integral of
                                       process variable error */
    int16_t   hUpperOutputLimit;    /**< Upper limit used to saturate the PI output */
    int16_t   hLowerOutputLimit;    /**< Lower limit used to saturate the PI output */
    uint16_t  hKpDivisorPOW2;       /**< Kp gain divisor expressed as power of 2.
                                       E.g. if gain divisor is 512 the value
                                       must be 9 as 2^9 = 512 */
    uint16_t  hKiDivisorPOW2;       /**< Ki gain divisor expressed as power of 2.
                                       E.g. if gain divisor is 512 the value
                                       must be 9 as 2^9 = 512 */
} EMACC_PI_InitTypeDef;

/**
  * @brief Two components stator current type definition
  */
typedef struct
{
    int16_t qI_Component1;
    int16_t qI_Component2;
} Curr_Components;

/**
  * @brief  Two components stator voltage type definition
  */
typedef struct
{
    int16_t qV_Component1;
    int16_t qV_Component2;
} Volt_Components;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup EMACC_Exported_Constants EMACC_Exported_Constants
  * @{
  */

/** @defgroup EMACC_IE  EMACC_IE
  * @{
  */
#define EMACC_CORDIC_IE                     EMACC_IER_CORDIC_IE
#define EMACC_CLARK_IE                      EMACC_IER_CLARK_IE
#define EMACC_PARK_IE                       EMACC_IER_PARK_IE
#define EMACC_PID_IE                        EMACC_IER_PID_IE
#define EMACC_RPARK_IE                      EMACC_IER_RPARK_IE
#define IS_EMACC_IT(EMACC_IT)                           (((EMACC_IT) == EMACC_CORDIC_IE) || ((EMACC_IT) == EMACC_CLARK_IE) || \
                                                                                    ((EMACC_IT) == EMACC_PARK_IE) || ((EMACC_IT) == EMACC_PID_IE)|| \
                                                                                    ((EMACC_IT) == EMACC_RPARK_IE)  )

/**
  * @}
  */

/** @defgroup EMACC_STATUS EMACC_STATUS
  * @{
  */
#define EMACC_CORDIC_STATUS                             EMACC_SR_CORDIC_CF
#define EMACC_CLARK_STATUS                              EMACC_SR_CLARKE_CF
#define EMACC_PARK_STATUS                                   EMACC_SR_PARK_CF
#define EMACC_PID_STATUS                                    EMACC_SR_PID_CF
#define EMACC_RPARK_STATUS                              EMACC_SR_RPARK_CF

#define IS_EMACC_GET_FLAG(EMACC_STATUS)     (((EMACC_STATUS) == EMACC_CORDIC_STATUS) || ((EMACC_STATUS) == EMACC_CLARK_STATUS) || \
                                                                                    ((EMACC_STATUS) == EMACC_PARK_STATUS) || ((EMACC_STATUS) == EMACC_PID_STATUS)|| \
                                                                                    ((EMACC_STATUS) == EMACC_RPARK_STATUS) )

/**
  * @}
  */

/** @defgroup EMACC_FLAG EMACC_FLAG
* @{
*/
#define EMACC_ALL_STATUS_FLAG                       (0x0000003F)
#define EMACC_CORDIC_FLAG                               EMACC_CLRSR_CLR_CORDIC
#define EMACC_CLARK_FLAG                                EMACC_CLRSR_CLR_CLARKE
#define EMACC_PARK_FLAG                                 EMACC_CLRSR_CLR_PARK
#define EMACC_PID_FLAG                                  EMACC_CLRSR_CLR_PID
#define EMACC_RPARK_FLAG                                EMACC_CLRSR_CLR_RPARK
#define IS_EMACC_CLEAR_FLAG(EMACC_FLAG)     (((EMACC_FLAG) == EMACC_CORDIC_FLAG) || ((EMACC_FLAG) == EMACC_CLARK_FLAG) || \
                                                                                    ((EMACC_FLAG) == EMACC_PARK_FLAG) || ((EMACC_FLAG) == EMACC_PID_FLAG)|| \
                                                                                    ((EMACC_FLAG) == EMACC_RPARK_FLAG) || ((EMACC_FLAG) == EMACC_ALL_STATUS_FLAG))

/**
  * @}
  */


/** @defgroup EMACC_Circlelimit_Selection EMACC_Circlelimit_Selection
  * @{
  */
#define EMACC_MODULE_MASK                   (0xFFFFFFC0)
#define EMACC_EN                            (EMACC_CR_EMACC_EN)
#define EMACC_CORDIC_EN                     (EMACC_CR_CORDIC_EN|EMACC_CR_EMACC_EN)
#define EMACC_CLARKE_EN                     (EMACC_CR_CORDIC_EN | EMACC_CR_CLARKE_EN|EMACC_CR_EMACC_EN)
#define EMACC_PARK_EN                       (EMACC_CR_CORDIC_EN | EMACC_CR_CLARKE_EN | EMACC_CR_PARK_EN|EMACC_CR_EMACC_EN)
#define EMACC_PID_EN                        (EMACC_CR_CORDIC_EN | EMACC_CR_CLARKE_EN | EMACC_CR_PID_EN|EMACC_CR_EMACC_EN)
#define EMACC_REVPARK_EN                    (EMACC_CR_CORDIC_EN | EMACC_CR_CLARKE_EN | EMACC_CR_PID_EN| EMACC_CR_RPARK_EN|EMACC_CR_EMACC_EN)

#define IS_EMACC_MODULE(EMACC_Module)       (((EMACC_Module) == EMACC_CORDIC_EN) || ((EMACC_Module) == EMACC_CLARKE_EN) || \
                                                ((EMACC_Module) == EMACC_PARK_EN) || ((EMACC_Module) == EMACC_PID_EN)|| \
                                                ((EMACC_Module) == EMACC_REVPARK_EN)|| ((EMACC_Module) == EMACC_EN) )


#define CIRCLELIM_MAXMODULE       (0x7FFF)
#define CIRCLELIM_TABLE_INDEX     (0x3F)
#define EMACC_CLEAR_STATUS_MASK   (0x1F)


#define PID_RAM_BASE              ((uint32_t *) 0x40028100)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup EMACC_Exported_Functions EMACC_Exported_Functions
  * @{
  */
/*** Initialization and configuration functions*********************************/
void EMACC_DeInit(void);
void EMACC_Init(EMACC_PI_InitTypeDef* EMACC_ID_InitStruct, EMACC_PI_InitTypeDef* EMACC_IQ_InitStruct);
void EMACC_Cmd(uint32_t EMACC_Module, FunctionalState NewState);

/*** EMACC Calculate functions*********************************/
Volt_Components EMACC_Cal(int16_t hElAngle, Curr_Components Iab, Curr_Components Iqdref);

/*** EMACC Results functions*********************************/
void EMACC_SetClarke(uint16_t Ia, uint16_t Ib);
void EMACC_SetEleAngle(int16_t ElAngle);
uint16_t EMACC_GetCordicOutCosx(void);
uint16_t EMACC_GetCordicOutSinx(void);
uint16_t EMACC_GetClarkeOutIalpha(void);
uint16_t EMACC_GetClarkeOutIbeta(void);
uint16_t EMACC_GetParkOutId(void);
uint16_t EMACC_GetParkOutIq(void);
uint16_t EMACC_GetPIDOutVd(void);
uint16_t EMACC_GetPIDOutVq(void);
uint16_t EMACC_GetRevParkOutValpha(void);
uint16_t EMACC_GetRevParkOutVbeta(void);

/*** EMACC Flags functions*********************************/
FlagStatus EMACC_GetFlag( uint32_t EMACC_STATUS);
void EMACC_ClearFlag(uint16_t EMACC_FLAG);




/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif





#endif /*__HK32L0XX_EMACC_H */
/***************************** (C) COPYRIGHT HKMicroChip  *******************************/
