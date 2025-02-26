/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_comp.h
* @brief:     Head file of comp module
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_COMP_H
#define __HK32L0XX_COMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"

/** @addtogroup COMP COMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup COMP_Exported_Types COMP_Exported_Types
  * @{
  */

/**
  * @brief  COMP Init structure definition
  */
typedef struct
{
    uint32_t PowerMode;               /*!< Specifies the COMP power mode. This parameter can be a value of
                                      @ref COMP_POWERMODE_Configuration */

    uint32_t InputPlus;               /*!< Specifies the COMP INPUT PLUS Configuration.
                                      This parameter can be a value of
                                      @ref COMP_INPUT_PLUS_and_MINUS_Configuration */

    uint32_t InputMinus;              /*!< Specifies the COMP MINUS Configuration.
                                      This parameter can be a value of
                                      @ref COMP_INPUT_PLUS_and_MINUS_Configuration */

    uint32_t OutputPolarity;          /*!< Specifies the COMP output polarity Configuration.
                                      This parameter can be a value of
                                      @ref COMP_OUTPUT_Polarity_Configuration */

    uint32_t WindowOut;               /*!< Specifies the COMP window output Configuration.
                                      This parameter can be a value of
                                      @ref COMP_WINDOWOUT_Configuration */

    uint32_t Hysteresis;             /*!< Specifies the COMP hysteresis Configuration.
                                      This parameter can be a value of
                                      @ref COMP_Hysteresis_Configuration */
} COMP_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup COMP_Define COMP_Define
  * @{
  */

/** @defgroup COMP_definition COMP_definition
  * @{
  */
/*********************************COMP definition****************************************************/
#define CMP1                                 1
#define CMP2                                 2
/*****************************************************************************************************/
/**
  * @}
  */

/** @defgroup COMP_POWERMODE_Configuration COMP_POWERMODE_Configuration
  * @{
  */
/*********************************COMP POWERMODE Configuration***************************************/
#define COMP_POWERMODE_LOWPOWER                 ((uint32_t)0x00000000U)
#define COMP_POWERMODE_NORMALPOWER              ((uint32_t)0x00040000U)
/*****************************************************************************************************/
/**
  * @}
  */

/** @defgroup COMP_WINDOWOUT_Configuration COMP_WINDOWOUT_Configuration
  * @{
  */
/*********************************COMP WINDOWOUT Configuration***************************************/
#define COMP_WINDOWOUT_DISABLE                  ((uint32_t)0x00000000U)
#define COMP_WINDOWOUT_ENABLE                   (COMP1_CSR_COMP1WINOUT)
/*****************************************************************************************************/
/**
  * @}
  */

/** @defgroup COMP_Hysteresis_Configuration COMP_Hysteresis_Configuration
  * @{
  */
/*********************************COMP Hysteresis Configuration***************************************/
#define COMP_HYSTERESIS_DISABLE                 ((uint32_t)0x00000000U)
#define COMP_HYSTERESIS_LEVEL1                  ((uint32_t)0x00010000U)
#define COMP_HYSTERESIS_LEVEL2                  ((uint32_t)0x00020000U)
#define COMP_HYSTERESIS_LEVEL3                  ((uint32_t)0x00030000U)
/*****************************************************************************************************/
/**
  * @}
  */

/** @defgroup COMP_INPUT_PLUS_and_MINUS_Configuration COMP_INPUT_PLUS_and_MINUS_Configuration
  * @{
  */
/*********************************COMP  INPUT PLUS and MINUS Configuration***************************************************/
#define COMP1_INPUT_PLUS_PA1            ((uint32_t)0x00000000U)
#define COMP1_INPUT_PLUS_COMP2          (COMP1_CSR_COMP1WM)

#define COMP1_INPUT_MINUS_VREFINT     ((uint32_t)0x00000000U)
#define COMP1_INPUT_MINUS_PA0         (COMP1_CSR_COMP1INNSEL_0)
#define COMP1_INPUT_MINUS_DAC_PA4     (COMP1_CSR_COMP1INNSEL_1)
#define COMP1_INPUT_MINUS_PA5         (COMP1_CSR_COMP1INNSEL_1|COMP1_CSR_COMP1INNSEL_0)
#define COMP1_INPUT_MINUS_1_4VREFINT  (COMP1_CSR_COMP1INNSEL_2)
#define COMP1_INPUT_MINUS_1_2VREFINT  (COMP1_CSR_COMP1INNSEL_2|COMP1_CSR_COMP1INNSEL_0)
#define COMP1_INPUT_MINUS_3_4VREFINT  (COMP1_CSR_COMP1INNSEL_2|COMP1_CSR_COMP1INNSEL_1)

#define COMP2_INPUT_PLUS_PA3          ((uint32_t)0x00000000U)
#define COMP2_INPUT_PLUS_PB4          (COMP2_CSR_COMP2INPSEL_0)
#define COMP2_INPUT_PLUS_PB5          (COMP2_CSR_COMP2INPSEL_1)
#define COMP2_INPUT_PLUS_PB6          (COMP2_CSR_COMP2INPSEL_1|COMP_CSR_COMP2INPSEL_0)
#define COMP2_INPUT_PLUS_PB7          (COMP2_CSR_COMP2INPSEL_2)

#define COMP2_INPUT_MINUS_VREFINT     ((uint32_t)0x00000000U)
#define COMP2_INPUT_MINUS_PA2         (COMP2_CSR_COMP2INNSEL_0)
#define COMP2_INPUT_MINUS_DAC_PA4     (COMP2_CSR_COMP2INNSEL_1)
#define COMP2_INPUT_MINUS_PA5         (COMP2_CSR_COMP2INNSEL_1|COMP2_CSR_COMP2INNSEL_0)
#define COMP2_INPUT_MINUS_1_4VREFINT  (COMP2_CSR_COMP2INNSEL_2)
#define COMP2_INPUT_MINUS_1_2VREFINT  (COMP2_CSR_COMP2INNSEL_2|COMP2_CSR_COMP2INNSEL_0)
#define COMP2_INPUT_MINUS_3_4VREFINT  (COMP2_CSR_COMP2INNSEL_2|COMP2_CSR_COMP2INNSEL_1)
#define COMP2_INPUT_MINUS_PB3         (COMP2_CSR_COMP2INNSEL_2|COMP2_CSR_COMP2INNSEL_1|COMP_CSR_COMP2INNSEL_0)
/*****************************************************************************************************************************/
/**
  * @}
  */

/** @defgroup COMP_OUTPUT_Polarity_Configuration COMP_OUTPUT_Polarity_Configuration
  * @{
  */
/*********************************COMP OUTPUT Polarity Configuration***********************************/
#define COMP_OUTPUTPOL_NONINVERTED   ((uint32_t)0x00000000U)
#define COMP_OUTPUTPOL_INVERTED      ((uint32_t)0x00008000U)
/******************************************************************************************************/
/**
  * @}
  */

/** @defgroup COMP_OUTPUT_Level_Configuration COMP_OUTPUT_Level_Configuration
  * @{
  */
/*********************************COMP OUTPUT Level Configuration**************************************/
#define COMP_OUTPUT_LEVEL_LOW        ((uint32_t)0x00000000U)
#define COMP_OUTPUT_LEVEL_HIGH       ((uint32_t)0x00000001U)
/******************************************************************************************************/
/**
  * @}
  */

/** @defgroup COMP_Valid_Output_Configuration COMP_Valid_Output_Configuration
  * @{
  */
/*********************************COMP OUTPUT Level Configuration**************************************/
#define COMP_OUTPUT_Valid_0       ((uint32_t)0x00000000U)
#define COMP_OUTPUT_Valid_1       ((uint32_t)0x00080000U)
/******************************************************************************************************/
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Comp Function used to set the COMP configuration to the default reset state *****/
void COMP_DeInit(void);
/* Comp Initialization functions *********************************/
ErrorStatus COMP_Init(uint8_t COMPx, COMP_InitTypeDef *COMP_InitStruct);
/* Comp Window mode set and get functions *********************************************************/
void COMP_SetCommonWindowMode(uint32_t WindowMode);
uint32_t COMP_GetCommonWindowMode(uint8_t COMPx);
/* Comp Power mode set and get functions *********************************************************/
void COMP_SetPowerMode(uint8_t COMPx, uint32_t PowerMode);
uint32_t COMP_GetPowerMode(uint8_t COMPx);
/* Comp Output Polarity set and get functions *********************************************************/
void COMP_SetOutputPolarity(uint8_t COMPx, uint32_t OutputPolarity);
uint32_t COMP_GetOutputPolarity(uint8_t COMPx);
/* Comp Enable/disable and enable state functions *************************************************/
void COMP_Enable(uint8_t COMPx);
void COMP_Disable(uint8_t COMPx);
uint32_t COMP_IsEnabled(uint8_t COMPx);
/* Comp Lock and Lock state functions *********************************************************/
void COMP_Lock(uint8_t COMPx);
uint32_t COMP_IsLocked(uint8_t COMPx);
/* Comp Read output state functions *********************************************************/
uint32_t COMP_ReadOutputLevel(uint8_t COMPx);
/* Comp set input NonInverting and invert state functions *****************************************/
void COMP_SetInputNonInverting(uint8_t COMPx, uint32_t InputNonInverting);
uint32_t COMP_GetInputNonInverting(uint8_t COMPx);
/* Comp set input Inverting and invert state functions *****************************************/
void COMP_SetInputInverting(uint8_t COMPx, uint32_t InputInverting);
uint32_t COMP_GetInputInverting(uint8_t COMPx);
/* Comp set and get hysteresis value functions *****************************************/
void COMP_SetHysteresis(uint8_t COMPx, uint32_t hysteresis);
uint32_t COMP_GetHysteresis(uint8_t COMPx);
/* Comp set and get valid output value functions *****************************************/
void COMP_SetValidoutput(uint8_t COMPx, uint32_t output);
uint32_t COMP_GetValidoutput(uint8_t COMPx);

#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_COMP_H */

