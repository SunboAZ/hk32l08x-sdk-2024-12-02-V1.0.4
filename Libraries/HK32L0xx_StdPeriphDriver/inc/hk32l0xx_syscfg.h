/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_syscfg.h
* @brief:     This file contains all the functions prototypes for the SYSCFG firmware
*             library.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_SYSCFG_H
#define __HK32L0XX_SYSCFG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"

/** @addtogroup SYSCFG
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup SYSCFG_Exported_Constants  SYSCFG Exported Constants
  * @{
  */

/** @defgroup SYSCFG_EXTI_Port_Sources   SYSCFG EXTI Port Sources
  * @{
  */
#define EXTI_PortSourceGPIOA       ((uint8_t)0x00)
#define EXTI_PortSourceGPIOB       ((uint8_t)0x01)
#define EXTI_PortSourceGPIOC       ((uint8_t)0x02)
#define EXTI_PortSourceGPIOD       ((uint8_t)0x03)
#define EXTI_PortSourceGPIOE       ((uint8_t)0x04)
#define EXTI_PortSourceGPIOF       ((uint8_t)0x05)

#define IS_EXTI_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == EXTI_PortSourceGPIOA) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOB) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOC) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOD) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOE) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOF))
/**
  * @}
  */

/** @defgroup SYSCFG_EXTI_Pin_sources   SYSCFG EXTI Pin sources
  * @{
  */
#define EXTI_PinSource0            ((uint8_t)0x00)
#define EXTI_PinSource1            ((uint8_t)0x01)
#define EXTI_PinSource2            ((uint8_t)0x02)
#define EXTI_PinSource3            ((uint8_t)0x03)
#define EXTI_PinSource4            ((uint8_t)0x04)
#define EXTI_PinSource5            ((uint8_t)0x05)
#define EXTI_PinSource6            ((uint8_t)0x06)
#define EXTI_PinSource7            ((uint8_t)0x07)
#define EXTI_PinSource8            ((uint8_t)0x08)
#define EXTI_PinSource9            ((uint8_t)0x09)
#define EXTI_PinSource10           ((uint8_t)0x0A)
#define EXTI_PinSource11           ((uint8_t)0x0B)
#define EXTI_PinSource12           ((uint8_t)0x0C)
#define EXTI_PinSource13           ((uint8_t)0x0D)
#define EXTI_PinSource14           ((uint8_t)0x0E)
#define EXTI_PinSource15           ((uint8_t)0x0F)

#define IS_EXTI_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == EXTI_PinSource0) || \
                                       ((PINSOURCE) == EXTI_PinSource1) || \
                                       ((PINSOURCE) == EXTI_PinSource2) || \
                                       ((PINSOURCE) == EXTI_PinSource3) || \
                                       ((PINSOURCE) == EXTI_PinSource4) || \
                                       ((PINSOURCE) == EXTI_PinSource5) || \
                                       ((PINSOURCE) == EXTI_PinSource6) || \
                                       ((PINSOURCE) == EXTI_PinSource7) || \
                                       ((PINSOURCE) == EXTI_PinSource8) || \
                                       ((PINSOURCE) == EXTI_PinSource9) || \
                                       ((PINSOURCE) == EXTI_PinSource10) || \
                                       ((PINSOURCE) == EXTI_PinSource11) || \
                                       ((PINSOURCE) == EXTI_PinSource12) || \
                                       ((PINSOURCE) == EXTI_PinSource13) || \
                                       ((PINSOURCE) == EXTI_PinSource14) || \
                                       ((PINSOURCE) == EXTI_PinSource15))
/**
  * @}
  */

/** @defgroup SYSCFG_Memory_Remap_Config    SYSCFG Memory Remap Config
  * @{
  */
#define SYSCFG_MemoryRemap_Flash                ((uint8_t)0x00)
#define SYSCFG_MemoryRemap_SystemMemory         ((uint8_t)0x01)
#define SYSCFG_MemoryRemap_SRAM                 ((uint8_t)0x03)


#define IS_SYSCFG_MEMORY_REMAP(REMAP) (((REMAP) == SYSCFG_MemoryRemap_Flash) || \
                                       ((REMAP) == SYSCFG_MemoryRemap_SystemMemory) || \
                                       ((REMAP) == SYSCFG_MemoryRemap_SRAM))

/**
  * @}
  */

/** @defgroup SYSCFG_DMA_Remap_Config  SYSCFG DMA Remap Config
  * @{
  */
#define SYSCFG_DMARemap_USART1Rx    SYSCFG_CFGR1_USART1RX_DMA_RMP /* Remap USART1 Rx DMA requests from channel3 to channel5 */
#define SYSCFG_DMARemap_USART1Tx    SYSCFG_CFGR1_USART1TX_DMA_RMP /* Remap USART1 Tx DMA requests from channel2 to channel4 */
#define SYSCFG_DMARemap_ADC1        SYSCFG_CFGR1_ADC_DMA_RMP      /* Remap ADC1 DMA requests from channel1 to channel2 */

#define IS_SYSCFG_DMA_REMAP(REMAP) (((REMAP) == SYSCFG_DMARemap_USART1Rx) || \
                                    ((REMAP) == SYSCFG_DMARemap_USART1Tx) || \
                                    ((REMAP) == SYSCFG_DMARemap_ADC1))

/**
  * @}
  */

/** @defgroup SYSCFG_I2C_FastModePlus_Config    SYSCFG I2C FastModePlus Config
  * @{
  */
#define SYSCFG_I2CFastModePlus_PB6       SYSCFG_CFGR1_I2C1_PB6_FMP /* Enable Fast Mode Plus on PB6 */
#define SYSCFG_I2CFastModePlus_PB7       SYSCFG_CFGR1_I2C1_PB7_FMP /* Enable Fast Mode Plus on PB7 */
#define SYSCFG_I2CFastModePlus_PB8       SYSCFG_CFGR1_I2C1_PB8_FMP /* Enable Fast Mode Plus on PB8 */
#define SYSCFG_I2CFastModePlus_PB9       SYSCFG_CFGR1_I2C1_PB9_FMP /* Enable Fast Mode Plus on PB9 */
#define SYSCFG_I2CFastModePlus_I2C1      SYSCFG_CFGR1_I2C1_FMP    /* Enable Fast Mode Plus on PB10, PB11, PF6 and PF7*/
#define SYSCFG_I2CFastModePlus_PA9       SYSCFG_CFGR1_I2C1_PA9_FMP/* Enable Fast Mode Plus on PA9  */
#define SYSCFG_I2CFastModePlus_PA10      SYSCFG_CFGR1_I2C1_PA10_FMP/* Enable Fast Mode Plus on PA10*/

#define IS_SYSCFG_I2C_FMP(PIN) (((PIN) == SYSCFG_I2CFastModePlus_PB6)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB7)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB8)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB9)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C1) || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PA9)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PA10))


/**
  * @}
  */

/** @defgroup SYSCFG_Lock_Config   SYSCFG Lock Config
  * @{
  */
#define SYSCFG_Break_PVD                     SYSCFG_CFGR2_PVD_LOCK          /*!< Connects the PVD event to the Break Input of TIM1 */
#define SYSCFG_Break_Lockup                  SYSCFG_CFGR2_LOCKUP_LOCK       /*!< Connects Lockup output of CortexM0 to the break input of TIM1 */

#define IS_SYSCFG_LOCK_CONFIG(CONFIG) (((CONFIG) == SYSCFG_Break_Lockup)     || \
                                       ((CONFIG) == SYSCFG_CFGR2_PVD_LOCK))

/**
  * @}
  */

/** @defgroup SYSCFG_TIM3_CH4_REMAP   SYSCFG TIM3 CH4 REMAP
  * @{
  */

#define SYSCFG_TIM3_CH4_REMAP_GPIO                           ((uint32_t) 0x00000000)
#define SYSCFG_TIM3_CH4_REMAP_LSI                            ((uint32_t) 0x00010000)
#define SYSCFG_TIM3_CH4_REMAP_HSI                            ((uint32_t) 0x00020000)
#define SYSCFG_TIM3_CH4_REMAP_LSE                            ((uint32_t) 0x00030000)
#define SYSCFG_TIM3_CH4_REMAP_USB_SOF                        ((uint32_t) 0x00040000)
#define SYSCFG_TIM3_CH4_REMAP_MSI_DIV_8                      ((uint32_t) 0x00050000)
#define SYSCFG_TIM3_CH4_REMAP_MSI_DIV_64                     ((uint32_t) 0x00060000)
#define SYSCFG_TIM3_CH4_REMAP_MSI_DIV_512                    ((uint32_t) 0x00070000)

#define SYSCFG_TIM3_CH4_REMAP_MASK                            SYSCFG_CFGR2_TIM3_CH4_REMAP

#define IS_SYSCFG_TIM3_CH4_REMAP(FLAG) (((FLAG) <= SYSCFG_TIM3_CH4_REMAP_MSI_DIV_512))

/**
  * @}
  */

/** @defgroup SYSCFG_LCD_CAPA    SYSCFG LCD CAPA
  * @{
  */

#define SYSCFG_LCD_CAPA_PB2                      SYSCFG_CFGR1_LCD_CAPA_0
#define SYSCFG_LCD_CAPA_PB12                     SYSCFG_CFGR1_LCD_CAPA_1
#define SYSCFG_LCD_CAPA_PB0                      SYSCFG_CFGR1_LCD_CAPA_2

#define IS_SYSCFG_LCD_CAPA(CONFIG)    (((CONFIG) == SYSCFG_LCD_CAPA_PB2)     || \
                                       ((CONFIG) == SYSCFG_LCD_CAPA_PB12)    || \
                                       ((CONFIG) == SYSCFG_LCD_CAPA_PB0))

/**
  * @}
  */

/** @defgroup SYSCFG_ISR_WRAPPER   SYSCFG ISR WRAPPER
  * @{
  */
#define SYSCFG_ITLINE0                           ((uint32_t) 0x00000000)
#define SYSCFG_ITLINE1                           ((uint32_t) 0x00000001)
#define SYSCFG_ITLINE2                           ((uint32_t) 0x00000002)
#define SYSCFG_ITLINE3                           ((uint32_t) 0x00000003)
#define SYSCFG_ITLINE4                           ((uint32_t) 0x00000004)
#define SYSCFG_ITLINE5                           ((uint32_t) 0x00000005)
#define SYSCFG_ITLINE6                           ((uint32_t) 0x00000006)
#define SYSCFG_ITLINE7                           ((uint32_t) 0x00000007)
#define SYSCFG_ITLINE8                           ((uint32_t) 0x00000008)
#define SYSCFG_ITLINE9                           ((uint32_t) 0x00000009)
#define SYSCFG_ITLINE10                          ((uint32_t) 0x0000000A)
#define SYSCFG_ITLINE11                          ((uint32_t) 0x0000000B)
#define SYSCFG_ITLINE12                          ((uint32_t) 0x0000000C)
#define SYSCFG_ITLINE13                          ((uint32_t) 0x0000000D)
#define SYSCFG_ITLINE14                          ((uint32_t) 0x0000000E)
#define SYSCFG_ITLINE15                          ((uint32_t) 0x0000000F)
#define SYSCFG_ITLINE16                          ((uint32_t) 0x00000010)
#define SYSCFG_ITLINE17                          ((uint32_t) 0x00000011)
#define SYSCFG_ITLINE18                          ((uint32_t) 0x00000012)
#define SYSCFG_ITLINE19                          ((uint32_t) 0x00000013)
#define SYSCFG_ITLINE20                          ((uint32_t) 0x00000014)
#define SYSCFG_ITLINE21                          ((uint32_t) 0x00000015)
#define SYSCFG_ITLINE22                          ((uint32_t) 0x00000016)
#define SYSCFG_ITLINE23                          ((uint32_t) 0x00000017)
#define SYSCFG_ITLINE24                          ((uint32_t) 0x00000018)
#define SYSCFG_ITLINE25                          ((uint32_t) 0x00000019)
#define SYSCFG_ITLINE26                          ((uint32_t) 0x0000001A)
#define SYSCFG_ITLINE27                          ((uint32_t) 0x0000001B)
#define SYSCFG_ITLINE28                          ((uint32_t) 0x0000001C)
#define SYSCFG_ITLINE29                          ((uint32_t) 0x0000001D)
#define SYSCFG_ITLINE30                          ((uint32_t) 0x0000001E)
#define SYSCFG_ITLINE31                          ((uint32_t) 0x0000001F)
/**
  * @}
  */

/** @defgroup SYSCFG_FLAG_ANALOG_EN_definition   SYSCFG FLAG ANALOG EN definition
  * @{
  */

#define SYSCFG_F_A_EN_BUF_AIN19               SYSCFG_CFGR3_EN_BUF_AIN19
#define SYSCFG_F_A_EN_SW_AIN19                SYSCFG_CFGR3_EN_SW_AIN19
#define SYSCFG_F_A_EN_BUF_VREFINT_COMP1_2     SYSCFG_CFGR3_ENBUF_VREFINT_COMP1_2
#define SYSCFG_F_A_EN_BUF_SENSOR_OUT          SYSCFG_CFGR3_ENBUF_SENSOR_OUT
#define SYSCFG_F_A_EN_BUF_VREFINT_ADC         SYSCFG_CFGR3_ENBUF_VREFINT_ADC
#define SYSCFG_F_A_EN_VREFINT                 SYSCFG_CFGR3_EN_VREFINT


#define IS_SYSCFG_FLAG_ANALOG_EN(FLAG) (((FLAG) == SYSCFG_F_A_EN_BUF_AIN19)       || \
                                        ((FLAG) == SYSCFG_F_A_EN_SW_AIN19)        || \
                                        ((FLAG) == SYSCFG_F_A_EN_BUF_VREFINT_COMP1_2)       || \
                                        ((FLAG) == SYSCFG_F_A_EN_BUF_SENSOR_OUT)        || \
                                        ((FLAG) == SYSCFG_F_A_EN_BUF_VREFINT_ADC)       || \
                                        ((FLAG) == SYSCFG_F_A_EN_VREFINT))

#define IS_VALID_SYSCFG_FLAG_ANALOG_EN(FLAG)  (((FLAG) == SYSCFG_F_A_EN_BUF_AIN19)             || \
                                               ((FLAG) == SYSCFG_F_A_EN_SW_AIN19)              || \
                                               ((FLAG) == SYSCFG_F_A_EN_BUF_VREFINT_COMP1_2)   || \
                                               ((FLAG) == SYSCFG_F_A_EN_BUF_SENSOR_OUT)        || \
                                               ((FLAG) == SYSCFG_F_A_EN_BUF_VREFINT_ADC)       || \
                                               ((FLAG) == SYSCFG_F_A_EN_VREFINT))


/**
  * @}
  */

/** @defgroup SYSCFG_FLAG_SEL_VREF_OUT   SYSCFG FLAG SEL VREF OUT
  * @{
  */
#define SYSCFG_FLAG_SEL_VREF_NO                ((uint32_t)0)
#define SYSCFG_FLAG_SEL_VREF_PA0               SYSCFG_CFGR3_SEL_VREF_OUT_2
#define SYSCFG_FLAG_SEL_VREF_PB0               SYSCFG_CFGR3_SEL_VREF_OUT_0

#define SYSCFG_FLAG_SEL_VREF_MASK           SYSCFG_CFGR3_SEL_VREF_OUT_Mask
#define IS_SYSCFG_FLAG_SEL_VREF_OUT(FLAG) (((FLAG) == SYSCFG_FLAG_SEL_VREF_PA0)       || \
                                        ((FLAG) == SYSCFG_FLAG_SEL_VREF_PB0))

#define IS_VALID_SYSCFG_FLAG_SEL_VREF_OUT(FLAG) (!((FLAG) & \
                                                (~SYSCFG_CFGR3_SEL_VREF_OUT_Mask)))

/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @defgroup SYSCFG_Exported_Functions   SYSCFG Exported Functions
  * @{
  */

/*  Function used to set the SYSCFG configuration to the default reset state **/
void SYSCFG_DeInit(void);

/* SYSCFG configuration functions *********************************************/
void SYSCFG_MemoryRemapConfig(uint32_t SYSCFG_MemoryRemap);
void SYSCFG_DMAChannelRemapConfig(uint32_t SYSCFG_DMARemap, FunctionalState NewState);
void SYSCFG_I2CFastModePlusConfig(uint32_t SYSCFG_I2CFastModePlus, FunctionalState NewState);
void SYSCFG_IRDAEnvSelection(uint32_t SYSCFG_IRDAEnv);
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex);
void SYSCFG_BreakConfig(uint32_t SYSCFG_Break, FunctionalState NewStaus);
FlagStatus SYSCFG_GetFlagStatus(uint32_t SYSCFG_Flag);
void SYSCFG_ClearFlag(uint32_t SYSCFG_Flag);
void SYSCFG_SetTimer3Ch4Remap(uint32_t remap_source);
uint32_t SYSCFG_GetTimer3Ch4Remap(void);
void SYSCFG_SetModifyLock(void);
FlagStatus SYSCFG_GetModifyLock(void);
FlagStatus SYSCFG_GetVrefIntReady(void);
void SYSCFG_SetAnalogEn(uint32_t AFlag, FunctionalState NewStaus);
FunctionalState SYSCFG_GetAnalogEn(uint32_t AFlag);
void SYSCFG_SetSelVrefOut(uint32_t AFlag, FunctionalState NewStaus);
uint32_t SYSCFG_GetSelVrefOut(void);
void SYSCFG_SetTimer3Ch4Remap(uint32_t remap_source);
uint32_t SYSCFG_GetTimer3Ch4Remap(void);
uint32_t SYSCFG_GetMemoryRemapConfig(void);
void SYSCFG_PA9PA10RemapConfig(FunctionalState NewState);
void SYSCFG_LCDCAPAConfig(uint32_t SYSCFG_LCD_CAPA, FunctionalState NewState);
void SYSCFG_ADCVrefEnableCmd(FunctionalState NewStaus);
FlagStatus SYSCFG_GetADCVrefEnableStatus(void);

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_SYSCFG_H */

