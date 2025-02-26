/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_pwr.h
* @brief:     Head file of PWR module
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_PWR_H
#define __HK32L0XX_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"


/** @addtogroup PWR PWR
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup PWR_Exported_Types PWR_Exported_Types
  * @{
  */
typedef enum {RISING_EDGE = 0, FALLING_EDGE = 1} WakeupPinPolarity;
#define IS_WAKEUPPIN_STATE(STATE) (((STATE) == FALLING_EDGE) || ((STATE) == RISING_EDGE))

typedef enum {WAKE_UP_PIN1 = 0, WAKE_UP_PIN2 = 1} WakeupPinSel;
#define IS_WAKEUP_PIN(PIN) (((PIN) == 1) || ((PIN) == 0))

/* typedef --------------------------------------------------------------------*/
typedef enum
{
    PWR_OK       = 0x00U,
    PWR_ERROR    = 0x01U,
    PWR_BUSY     = 0x02U,
    PWR_TIMEOUT  = 0x03U
} PWR_StatusTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_Exported_Constants PWR_Exported_Constants
  * @{
  */
/** @defgroup PWR_PVDLevel PWR_PVDLevel
  * @{
  */
/* PVD level configuration */
#define  PWR_PVDLevel_0                     ((uint16_t)0x0000)     /*!< PVD level 0 */
#define  PWR_PVDLevel_1                     ((uint16_t)0x0020)     /*!< PVD level 1 */
#define  PWR_PVDLevel_2                     ((uint16_t)0x0040)     /*!< PVD level 2 */
#define  PWR_PVDLevel_3                     ((uint16_t)0x0060)     /*!< PVD level 3 */
#define  PWR_PVDLevel_4                     ((uint16_t)0x0080)     /*!< PVD level 4 */
#define  PWR_PVDLevel_5                     ((uint16_t)0x00A0)     /*!< PVD level 5 */
#define  PWR_PVDLevel_6                     ((uint16_t)0x00C0)     /*!< PVD level 6 */
#define  PWR_PVDLevel_7                     ((uint16_t)0x00E0)     /*!< PVD level 7 */

#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLevel_0) || ((LEVEL) == PWR_PVDLevel_1)|| \
                                 ((LEVEL) == PWR_PVDLevel_2) || ((LEVEL) == PWR_PVDLevel_3)|| \
                                 ((LEVEL) == PWR_PVDLevel_4) || ((LEVEL) == PWR_PVDLevel_5)|| \
                                 ((LEVEL) == PWR_PVDLevel_6) || ((LEVEL) == PWR_PVDLevel_7))
/**
  * @}
  */


/** @defgroup PWR_PVD_MODE PWR_PVD_MODE
  * @{
  */
#define PVD_MODE_IT               ((uint32_t)0x00010000U)
#define PVD_MODE_EVT              ((uint32_t)0x00020000U)
/**
  * @}
  */

/** @defgroup PWR_PVD_EDGE PWR_PVD_EDGE
  * @{
  */
#define PVD_RISING_EDGE           ((uint32_t)0x00000001U)
#define PVD_FALLING_EDGE          ((uint32_t)0x00000002U)
#define PVD_RISING_FALLING        ((uint32_t)0x00000003U)
/**
  * @}
  */

/** @defgroup PWR_Regulator_Voltage_Scale PWR_Regulator_Voltage_Scale
  * @{
  */
#define PWR_REGULATOR_VOLTAGE_SCALE1   PWR_CR_VOS_0
#define PWR_REGULATOR_VOLTAGE_SCALE2   PWR_CR_VOS_1
#define PWR_REGULATOR_VOLTAGE_SCALE3   PWR_CR_VOS

#define IS_PWR_VOLTAGE_SCALING_RANGE(RANGE) (((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE1) || \
                                             ((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE2) || \
                                             ((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE3))
/**
  * @}
  */

/** @defgroup PWR_WakeUpPin PWR_WakeUpPin
  * @{
  */
#define PWR_WakeUpPin_1                 PWR_CSR_EWUP1
#define PWR_WakeUpPin_2                 PWR_CSR_EWUP2
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WakeUpPin_1) || ((PIN) == PWR_WakeUpPin_2))
/**
  * @}
  */

/** @defgroup PWR_Regulator_state_is_Sleep_STOP_mode PWR_Regulator_state_is_Sleep_STOP_mode
  * @{
  */
#define PWR_Regulator_ON                ((uint32_t)0x00000000)
#define PWR_Regulator_LowPower          PWR_CR_LPSDSR
#define IS_PWR_REGULATOR(REGULATOR) (((REGULATOR) == PWR_Regulator_ON) || \
                                     ((REGULATOR) == PWR_Regulator_LowPower))
/**
  * @}
  */

/** @defgroup PWR_SLEEP_mode_entry PWR_SLEEP_mode_entry
  * @{
  */
#define PWR_SLEEPEntry_WFI              ((uint8_t)0x01)
#define PWR_SLEEPEntry_WFE              ((uint8_t)0x02)
#define PWR_SLEEPEntry_SLEEPONEXIT      ((uint8_t)0x03)
#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPEntry_WFI) || ((ENTRY) == PWR_SLEEPEntry_WFE) ||\
                                   ((ENTRY) == PWR_SLEEPEntry_SLEEPONEXIT))
/**
  * @}
  */

/** @defgroup PWR_STOP_mode_entry PWR_STOP_mode_entry
  * @{
  */
#define PWR_STOPEntry_WFI               ((uint8_t)0x01)
#define PWR_STOPEntry_WFE               ((uint8_t)0x02)
#define PWR_STOPEntry_SLEEPONEXIT       ((uint8_t)0x03)
#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPEntry_WFI) || ((ENTRY) == PWR_STOPEntry_WFE) ||\
                                  ((ENTRY) == PWR_STOPEntry_SLEEPONEXIT))
/**
  * @}
  */

/** @defgroup PWR_STANDBY_mode_entry PWR_STANDBY_mode_entry
  * @{
  */
#define PWR_STANDBYEntry_WFI               ((uint8_t)0x01)
#define PWR_STANDBYEntry_WFE               ((uint8_t)0x02)
#define PWR_STANDBYEntry_SLEEPONEXIT       ((uint8_t)0x03)
#define IS_PWR_STANDBY_ENTRY(ENTRY) (((ENTRY) == PWR_STANDBYEntry_WFI) || ((ENTRY) == PWR_STANDBYEntry_WFE) ||\
                                  ((ENTRY) == PWR_STANDBYEntry_SLEEPONEXIT))
/**
  * @}
  */

/** @defgroup PWR_Flag PWR_Flag
  * @{
  */
#define PWR_FLAG_WU                     PWR_CSR_WUF
#define PWR_FLAG_SB                     PWR_CSR_SBF
#define PWR_FLAG_PVDO                   PWR_CSR_PVDO
#define PWR_FLAG_VREFINTRDY             PWR_CSR_VREFINTRDYF

#define IS_PWR_GET_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB) || \
                               ((FLAG) == PWR_FLAG_PVDO) || ((FLAG) == PWR_FLAG_VREFINTRDY))

#define IS_PWR_CLEAR_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB))
/**
  * @}
  */

/** @defgroup PWR_DAC_config PWR_DAC_config
  * @{
  */
#define IS_PWR_DAC_DATA(DATA) (DATA &= 0x0f)
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
/* Function used to set the PWR configuration to the default reset state ******/
void PWR_DeInit(void);

/* Backup Domain Access function **********************************************/
void PWR_BackupAccessCmd(FunctionalState NewState);

/* PVD configuration functions ************************************************/
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel, uint32_t PWR_PVDMode, uint32_t PWR_PVDEdge);
void PWR_PVDCmd(FunctionalState NewState);

/* WakeUp pins configuration functions ****************************************/
void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState);

/* Low Power modes configuration functions ************************************/
void PWR_EnterSleepMode(uint32_t PWR_Regulator, uint8_t PWR_SLEEPEntry);
void PWR_EnterLowPowerSleepMode(uint8_t PWR_SLEEPEntry);
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
void PWR_EnterSTANDBYMode(uint8_t PWR_StandbyEntry);
void PWR_EnableSleepOnExit(void);
void PWR_DisableSleepOnExit(void);
void PWR_EnableSEVOnPend(void);
void PWR_DisableSEVOnPend(void);
void PWR_PVDIRQHandler(void);
void PWR_PVDCallback(void);

/* Flags management functions *************************************************/
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);

/* Peripheral extended features functions *************************************/
uint32_t PWR_GetVoltageRange(void);
void PWR_SetVoltageRange(uint32_t VoltageScaling);
void PWR_EnableFastWakeUp(void);
void PWR_DisableFastWakeUp(void);
void PWR_EnableUltraLowPower(void);
void PWR_DisableUltraLowPower(void);
void PWR_EnableLowPowerRunMode(void);
PWR_StatusTypeDef PWR_DisableLowPowerRunMode(void);
void PWR_DAC2InLowPowerModeControl(FunctionalState NewState);
void PWR_DAC1InLowPowerModeControl(FunctionalState NewState);
void PWR_DAC1InLowPowerModeConfig(uint32_t RELOADx, uint32_t DUTYx);
void PWR_DAC2InLowPowerModeConfig(uint32_t RELOADx, uint32_t DUTYx);
void PWR_WakeupPinPolarityConfig(uint32_t WakeUpPin, uint32_t Edge);
void PWR_PDRPDConfig(FunctionalState NewState);


#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_PWR_H */


