/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_opamp.h
* @brief:     This file contains all the functions prototypes for the AES firmware
*             library.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_OPAMP_H
#define __HK32L0XX_OPAMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"

/** @addtogroup OPAMP OPAMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup OPAMP_Exported_Types OPAMP_Exported_Types
  * @{
  */

/**
  * @brief OPAMP Init structure definition
  */
typedef struct
{
    uint32_t FunctionalMode;

    uint32_t InputNonInverting;

    uint32_t InputInverting;
} OPAMP_InitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup OPAMP_Exported_Constants OPAMP_Exported_Constants
  * @{
  */

/** @defgroup OPAMP_GA_Gain OPAMP_GA_Gain
  * @{
  */
#define OPAMP_PGA_GAIN_2                    ((uint32_t)0x00000000<<OPAMP_CSR_PGA_GAIN_Pos)
#define OPAMP_PGA_GAIN_4                    ((uint32_t)0x00000001<<OPAMP_CSR_PGA_GAIN_Pos)
#define OPAMP_PGA_GAIN_8                    ((uint32_t)0x00000002<<OPAMP_CSR_PGA_GAIN_Pos)
#define OPAMP_PGA_GAIN_16                   ((uint32_t)0x00000003<<OPAMP_CSR_PGA_GAIN_Pos)
#define OPAMP_PGA_GAIN_2_VM0                ((uint32_t)0x00000008<<OPAMP_CSR_PGA_GAIN_Pos)
#define OPAMP_PGA_GAIN_4_VM0                ((uint32_t)0x00000009<<OPAMP_CSR_PGA_GAIN_Pos)
#define OPAMP_PGA_GAIN_8_VM0                ((uint32_t)0x0000000A<<OPAMP_CSR_PGA_GAIN_Pos)
#define OPAMP_PGA_GAIN_16_VM0               ((uint32_t)0x0000000B<<OPAMP_CSR_PGA_GAIN_Pos)
#define OPAMP_PGA_GAIN_2_VM1                ((uint32_t)0x0000000C<<OPAMP_CSR_PGA_GAIN_Pos)
#define OPAMP_PGA_GAIN_4_VM1                ((uint32_t)0x0000000D<<OPAMP_CSR_PGA_GAIN_Pos)
#define OPAMP_PGA_GAIN_8_VM1                ((uint32_t)0x0000000E<<OPAMP_CSR_PGA_GAIN_Pos)
#define OPAMP_PGA_GAIN_16_VM1               ((uint32_t)0x0000000F<<OPAMP_CSR_PGA_GAIN_Pos)
/**
  * @}
  */

/** @defgroup OPAMP_Non-inverting_Input OPAMP_Non-inverting_Input
  * @{
  */
#define OPAMP_INPUT_NONINVERT_VP0      ((uint32_t)0x00000000)
#define OPAMP_INPUT_NONINVERT_VP1      (OPAMP_CSR_VP_SEL_0)
#define OPAMP_INPUT_NONINVERT_VP2      (OPAMP_CSR_VP_SEL_1)
#define OPAMP_INPUT_NONINVERT_VP3      (OPAMP_CSR_VP_SEL)
/**
  * @}
  */

/** @defgroup OPAMP_Inverting_Input OPAMP_inverting_Input
  * @{
  */
#define OPAMP_INPUT_INVERT_VM0        ((uint32_t)0x00000000<<OPAMP_CSR_VM_SEL_Pos)
#define OPAMP_INPUT_INVERT_VM1        ((uint32_t)0x00000001<<OPAMP_CSR_VM_SEL_Pos)
#define OPAMP_MODE_PGA                ((uint32_t)0x00000002<<OPAMP_CSR_VM_SEL_Pos)
#define OPAMP_MODE_FOLLOWER           ((uint32_t)0x00000003<<OPAMP_CSR_VM_SEL_Pos)
/**
  * @}
  */

/** @defgroup OPAMP_Secondary_Non-inverting_Input OPAMP_Secondary_Non-inverting_Input
  * @{
  */
#define OPAMP_INPUT_NONINVERT_VP0_SEC   ((uint32_t)0x00000000)
#define OPAMP_INPUT_NONINVERT_VP1_SEC   (OPAMP_CSR_VPS_SEL_0)
#define OPAMP_INPUT_NONINVERT_VP2_SEC   (OPAMP_CSR_VPS_SEL_1)
#define OPAMP_INPUT_NONINVERT_VP3_SEC   (OPAMP_CSR_VPS_SEL)
/**
  * @}
  */

/** @defgroup OPAMP_Secondary_Inverting_Input OPAMP_Secondary_Inverting_Input
 * @{
 */
#define OPAMP_INPUT_INVERT_VM0_SEC    ((uint32_t)0x00000000U)
#define OPAMP_INPUT_INVERT_VM1_SEC    (OPAMP_CSR_VMS_SEL)
/**
  * @}
  */

/** @defgroup OPAMP_MUX_Mode OPAMP_MUX_Mode
  * @{
  */
#define OPAMP_INPUT_MUX_DISABLE             ((uint32_t)0x00000000U)
#define OPAMP_INPUT_MUX_SECOND_ENABLE       (OPAMP_CSR_TCM_EN)
/**
  * @}
  */

/** @defgroup OPAMP_Operating_Mode OPAMP_Operating_Mode
  * @{
  */
#define OPAMP_MODE_FUNCTIONAL        ((uint32_t)0x00000000U)
#define OPAMP_MODE_CALIBRATION       (OPAMP_CSR_CALON)
/**
  * @}
  */

/** @defgroup OPAMP_VREF_Output OPAMP_VREF_Output
  * @{
  */
#define OPAMP_VREF_OUTPUT_DISABLE    ((uint32_t)0x00000000U)
#define OPAMP_VREF_OUTPUT_ENABLE     (OPAMP_CSR_TSTREF)
/**
  * @}
  */

/** @defgroup OPAMP_Trimming_Mode OPAMP_Trimming_Mode
  * @{
  */
#define OPAMP_TRIMMING_SELECT_MASK                  (OPAMP_CSR_CALSEL)
#define OPAMP_TRIMMING_VALUE_MASK                   (OPAMP_CSR_TRIMOFFSETN | OPAMP_CSR_TRIMOFFSETP)
#define OPAMP_TRIMMING_FACTORY                      ((uint32_t)0x00000000U)
#define OPAMP_TRIMMING_USER                         (OPAMP_CSR_USER_TRIM)
#define OPAMP_TRIMMING_NMOS_VREF_90PC_VDDA          (0x3 << OPAMP_CSR_CALSEL_Pos)
#define OPAMP_TRIMMING_NMOS_VREF_50PC_VDDA          (0x2 << OPAMP_CSR_CALSEL_Pos)
#define OPAMP_TRIMMING_PMOS_VREF_10PC_VDDA          (0x1 << OPAMP_CSR_CALSEL_Pos)
#define OPAMP_TRIMMING_PMOS_VREF_3_3PC_VDDA         (0x0 << OPAMP_CSR_CALSEL_Pos)
#define OPAMP_TRIMMING_NMOS                         (OPAMP_TRIMMING_NMOS_VREF_90PC_VDDA)
#define OPAMP_TRIMMING_PMOS                         (OPAMP_TRIMMING_PMOS_VREF_10PC_VDDA)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup OPAMP_Exported_Functions OPAMP_Exported_Functions
  * @{
  */
/*** Initialization and configuration functions*********************************/
void OPAMP_DeInit(void);
ErrorStatus OPAMP_Init(OPAMP_TypeDef *OPAMPx, OPAMP_InitTypeDef *OPAMP_InitStruct);
void OPAMP_Cmd(OPAMP_TypeDef *OPAMPx, FunctionalState NewState);
uint32_t OPAMP_IsEnabled(OPAMP_TypeDef *OPAMPx);
void OPAMP_Lock(OPAMP_TypeDef *OPAMPx);
uint32_t OPAMP_IsLocked(OPAMP_TypeDef *OPAMPx);

/*** setting and getting*********************************/
void OPAMP_SetMode(OPAMP_TypeDef *OPAMPx, uint32_t Mode);
uint32_t OPAMP_GetMode(OPAMP_TypeDef *OPAMPx);
void OPAMP_SetPGAGain(OPAMP_TypeDef *OPAMPx, uint32_t PGAGain);
uint32_t OPAMP_GetPGAGain(OPAMP_TypeDef *OPAMPx);
void OPAMP_SetInputNonInverting(OPAMP_TypeDef *OPAMPx, uint32_t InputNonInverting);
uint32_t OPAMP_GetInputNonInverting(OPAMP_TypeDef *OPAMPx);
void OPAMP_SetInputInverting(OPAMP_TypeDef *OPAMPx, uint32_t InputInverting);
uint32_t OPAMP_GetInputInverting(OPAMP_TypeDef *OPAMPx);
void OPAMP_SetInputNonInvertingSecondary(OPAMP_TypeDef *OPAMPx, uint32_t InputNonInverting);
uint32_t OPAMP_GetInputNonInvertingSecondary(OPAMP_TypeDef *OPAMPx);
void OPAMP_SetInputInvertingSecondary(OPAMP_TypeDef *OPAMPx, uint32_t InputInverting);
uint32_t OPAMP_GetInputInvertingSecondary(OPAMP_TypeDef *OPAMPx);
void OPAMP_SetInputsMuxMode(OPAMP_TypeDef *OPAMPx, uint32_t InputsMuxMode);
uint32_t OPAMP_GetInputsMuxMode(OPAMP_TypeDef *OPAMPx);
void OPAMP_SetTrimmingMode(OPAMP_TypeDef *OPAMPx, uint32_t TrimmingMode);
uint32_t OPAMP_GetTrimmingMode(OPAMP_TypeDef *OPAMPx);
void OPAMP_SetCalibrationSelection(OPAMP_TypeDef *OPAMPx, uint32_t TransistorsDiffPair);
uint32_t OPAMP_GetCalibrationSelection(OPAMP_TypeDef *OPAMPx);
void OPAMP_SetCalibrationVrefOutput(OPAMP_TypeDef *OPAMPx, uint32_t CalibrationVrefOutput);
uint32_t OPAMP_GetCalibrationVrefOutput(OPAMP_TypeDef *OPAMPx);
uint32_t OPAMP_IsCalibrationOutputSet(OPAMP_TypeDef *OPAMPx);
void OPAMP_SetTrimmingValue(OPAMP_TypeDef* OPAMPx, uint32_t TransistorsDiffPair, uint32_t TrimmingValue);
uint32_t OPAMP_GetTrimmingValue(OPAMP_TypeDef* OPAMPx, uint32_t TransistorsDiffPair);

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif



#endif /*__HK32L0XX_OPAMP_H */
/***************************** (C) COPYRIGHT HKMicroChip  *******************************/
