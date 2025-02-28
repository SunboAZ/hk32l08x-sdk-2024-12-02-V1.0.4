/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_adc.h
* @brief:     This file contains all the functions prototypes for the ADC firmware
*             library.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_ADC_H
#define __HK32L0XX_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup ADC_Exported_Types ADC Exported Types
  * @{
  */

/**
  * @brief  ADC Init structure definition
  */

typedef struct
{
    uint32_t ADC_Resolution;                  /*!< Selects the resolution of the conversion.
                                                 This parameter can be a value of @ref ADC_Resolution */
    FunctionalState ADC_ContinuousConvMode;   /*!< Specifies whether the conversion is performed in
                                                 Continuous or Single mode.
                                                 This parameter can be set to ENABLE or DISABLE. */

    uint32_t ADC_ExternalTrigConvEdge;        /*!< Selects the external trigger Edge and enables the
                                                 trigger of a regular group. This parameter can be a value
                                                 of @ref ADC_external_trigger_edge_conversion */

    uint32_t ADC_ExternalTrigConv;            /*!< Defines the external trigger used to start the analog
                                                 to digital conversion of regular channels. This parameter
                                                 can be a value of @ref ADC_external_trigger_sources_for_channels_conversion */

    uint32_t ADC_DataAlign;                   /*!< Specifies whether the ADC data alignment is left or right.
                                                 This parameter can be a value of @ref ADC_data_align */

    uint32_t  ADC_ScanDirection;              /*!< Specifies in which direction the channels will be scanned
                                                 in the sequence.
                                                 This parameter can be a value of @ref ADC_Scan_Direction */
} ADC_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants ADC Exported Constants
  * @{
  */

/** @defgroup ADC_Peripherals  ADC Peripherals
  * @{
  */
#define IS_ADC_ALL_PERIPH(PERIPH)                  ((PERIPH) == ADC)

/**
  * @}
  */

/** @defgroup ADC_Resolution ADC Resolution
  * @{
  */
#define ADC_Resolution_12b                         ((uint32_t)0x00000000)
#define ADC_Resolution_10b                         ADC_CFGR1_RES_0
#define ADC_Resolution_8b                          ADC_CFGR1_RES_1
#define ADC_Resolution_6b                          ADC_CFGR1_RES

#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_Resolution_12b) || \
                                       ((RESOLUTION) == ADC_Resolution_10b) || \
                                       ((RESOLUTION) == ADC_Resolution_8b) || \
                                       ((RESOLUTION) == ADC_Resolution_6b))

/**
  * @}
  */

/** @defgroup ADC_ClockMode  ADC ClockMode
  * @{
  */
#define ADC_ClockMode_AsynClk                  ((uint32_t)0x00000000)   /*!< ADC Asynchronous clock mode */
#define ADC_ClockMode_SynClkDiv1               (ADC_CFGR2_CKMODE_1 | ADC_CFGR2_CKMODE_0) /*!< Synchronous clock mode not divided  */
#define ADC_ClockMode_SynClkDiv2               ADC_CFGR2_CKMODE_0   /*!<  Synchronous clock mode divided by 2 */
#define ADC_ClockMode_SynClkDiv4               ADC_CFGR2_CKMODE_1   /*!<  Synchronous clock mode divided by 4 */
#define IS_ADC_CLOCKMODE(CLOCK) (((CLOCK) == ADC_ClockMode_AsynClk) ||\
                                      ((CLOCK) == ADC_ClockMode_SynClkDiv1) ||\
                                ((CLOCK) == ADC_ClockMode_SynClkDiv2) ||\
                                ((CLOCK) == ADC_ClockMode_SynClkDiv4))

/**
  * @}
  */

/** @defgroup ADC_Oversampler ADC Oversampler
  * @{
  */
#define ADC_OVS_DISABLE                  ((uint32_t)0x00000000)    /*!< ADC oversampling disabled. */
#define ADC_OVS_ENABLE                   ADC_CFGR2_OVSE           /*!< ADC oversampling enabled. */

#define ADC_OVS_CONT                     ((uint32_t)0x00000000)    /*!< ADC oversampling continuous mode */
#define ADC_OVS_DISCONT                  ADC_CFGR2_TOVS            /*!< ADC oversampling discontinuous mode */

#define ADC_OVS_RATIO_2                  ((uint32_t)0x00000000U)                                  /*!< ADC oversampling ratio of 2 (2 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data)*/
#define ADC_OVS_RATIO_4                  ADC_CFGR2_OVSR_0                                         /*!< ADC oversampling ratio of 4 (4 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data)*/
#define ADC_OVS_RATIO_8                  ADC_CFGR2_OVSR_1                                         /*!< ADC oversampling ratio of 8 (8 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data)*/
#define ADC_OVS_RATIO_16                 (ADC_CFGR2_OVSR_1 | ADC_CFGR2_OVSR_0)                      /*!< ADC oversampling ratio of 16 (16 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data)*/
#define ADC_OVS_RATIO_32                 ADC_CFGR2_OVSR_2                                         /*!< ADC oversampling ratio of 32 (32 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data)*/
#define ADC_OVS_RATIO_64                 (ADC_CFGR2_OVSR_2 | ADC_CFGR2_OVSR_0)                      /*!< ADC oversampling ratio of 64 (64 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data)*/
#define ADC_OVS_RATIO_128                (ADC_CFGR2_OVSR_2 | ADC_CFGR2_OVSR_1)                      /*!< ADC oversampling ratio of 128 (128 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data)*/
#define ADC_OVS_RATIO_256                (ADC_CFGR2_OVSR_2 | ADC_CFGR2_OVSR_1 | ADC_CFGR2_OVSR_0) /*!< ADC oversampling ratio of 256 (256 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data)*/
#define IS_ADC_OVS_RATIO(RATIO) (((RATIO) == ADC_OVS_RATIO_2) || \
                                 ((RATIO) == ADC_OVS_RATIO_4) || \
                                 ((RATIO) == ADC_OVS_RATIO_8) || \
                                 ((RATIO) == ADC_OVS_RATIO_16) || \
                                 ((RATIO) == ADC_OVS_RATIO_32) || \
                                 ((RATIO) == ADC_OVS_RATIO_64) || \
                                 ((RATIO) == ADC_OVS_RATIO_128) || \
                                 ((RATIO) == ADC_OVS_RATIO_256))


#define ADC_OVS_SHIFT_NONE              ((uint32_t)0x00000000U)                                     /*!< ADC oversampling no shift (sum of the ADC conversions data is not divided to result as the ADC oversampling conversion data) */
#define ADC_OVS_SHIFT_RIGHT_1           ADC_CFGR2_OVSS_0                                            /*!< ADC oversampling shift of 1 (sum of the ADC conversions data is divided by 2 to result as the ADC oversampling conversion data) */
#define ADC_OVS_SHIFT_RIGHT_2           ADC_CFGR2_OVSS_1                                            /*!< ADC oversampling shift of 2 (sum of the ADC conversions data is divided by 4 to result as the ADC oversampling conversion data) */
#define ADC_OVS_SHIFT_RIGHT_3           (ADC_CFGR2_OVSS_1 | ADC_CFGR2_OVSS_0)                       /*!< ADC oversampling shift of 3 (sum of the ADC conversions data is divided by 8 to result as the ADC oversampling conversion data) */
#define ADC_OVS_SHIFT_RIGHT_4           ADC_CFGR2_OVSS_2                                            /*!< ADC oversampling shift of 4 (sum of the ADC conversions data is divided by 16 to result as the ADC oversampling conversion data) */
#define ADC_OVS_SHIFT_RIGHT_5           (ADC_CFGR2_OVSS_2 | ADC_CFGR2_OVSS_0)                       /*!< ADC oversampling shift of 5 (sum of the ADC conversions data is divided by 32 to result as the ADC oversampling conversion data) */
#define ADC_OVS_SHIFT_RIGHT_6           (ADC_CFGR2_OVSS_2 | ADC_CFGR2_OVSS_1)                       /*!< ADC oversampling shift of 6 (sum of the ADC conversions data is divided by 64 to result as the ADC oversampling conversion data) */
#define ADC_OVS_SHIFT_RIGHT_7           (ADC_CFGR2_OVSS_2 | ADC_CFGR2_OVSS_1 | ADC_CFGR2_OVSS_0)    /*!< ADC oversampling shift of 7 (sum of the ADC conversions data is divided by 128 to result as the ADC oversampling conversion data) */
#define ADC_OVS_SHIFT_RIGHT_8           ADC_CFGR2_OVSS_3                                            /*!< ADC oversampling shift of 8 (sum of the ADC conversions data is divided by 256 to result as the ADC oversampling conversion data) */
#define IS_ADC_OVS_SHIFT(SHIFT) (((SHIFT) == ADC_OVS_SHIFT_NONE) || \
                                 ((SHIFT) == ADC_OVS_SHIFT_RIGHT_1) || \
                                 ((SHIFT) == ADC_OVS_SHIFT_RIGHT_2) || \
                                 ((SHIFT) == ADC_OVS_SHIFT_RIGHT_3) || \
                                 ((SHIFT) == ADC_OVS_SHIFT_RIGHT_4) || \
                                 ((SHIFT) == ADC_OVS_SHIFT_RIGHT_5) || \
                                 ((SHIFT) == ADC_OVS_SHIFT_RIGHT_6) || \
                                 ((SHIFT) == ADC_OVS_SHIFT_RIGHT_7) || \
                                 ((SHIFT) == ADC_OVS_SHIFT_RIGHT_8))

/**
  * @}
  */

/** @defgroup ADC_external_trigger_edge_conversion   ADC external trigger edge conversion
  * @{
  */
#define ADC_ExternalTrigConvEdge_None              ((uint32_t)0x00000000)
#define ADC_ExternalTrigConvEdge_Rising            ADC_CFGR1_EXTEN_0
#define ADC_ExternalTrigConvEdge_Falling           ADC_CFGR1_EXTEN_1
#define ADC_ExternalTrigConvEdge_RisingFalling     ADC_CFGR1_EXTEN

#define IS_ADC_EXT_TRIG_EDGE(EDGE) (((EDGE) == ADC_ExternalTrigConvEdge_None) || \
                                    ((EDGE) == ADC_ExternalTrigConvEdge_Rising) || \
                                    ((EDGE) == ADC_ExternalTrigConvEdge_Falling) || \
                                    ((EDGE) == ADC_ExternalTrigConvEdge_RisingFalling))
/**
  * @}
  */

/** @defgroup ADC_external_trigger_sources_for_channels_conversion  ADC external trigger sources for channels conversion
  * @{
  */

/* TIM1 */
#define ADC_ExternalTrigConv_T1_TRGO               ((uint32_t)0x00000000) /*0*/
#define ADC_ExternalTrigConv_T1_CC4                ADC_CFGR1_EXTSEL_0   /*1*/
#define ADC_ExternalTrigConv_T1_CC1                ADC_CFGR1_EXTSEL_3 /*8*/
#define ADC_ExternalTrigConv_T1_CC2                ((uint32_t)(ADC_CFGR1_EXTSEL_0 | ADC_CFGR1_EXTSEL_3))    /*9*/
#define ADC_ExternalTrigConv_T1_CC3                ((uint32_t)(ADC_CFGR1_EXTSEL_1 | ADC_CFGR1_EXTSEL_3))    /*10*/
/* TIM2 */
#define ADC_ExternalTrigConv_T2_TRGO               ADC_CFGR1_EXTSEL_1   /*2*/
#define ADC_ExternalTrigConv_T2_CC4                ((uint32_t)(ADC_CFGR1_EXTSEL_1 | ADC_CFGR1_EXTSEL_2))  /*6*/
#define ADC_ExternalTrigConv_T2_CC2                ((uint32_t)(ADC_CFGR1_EXTSEL_0 | ADC_CFGR1_EXTSEL_1 | ADC_CFGR1_EXTSEL_3)) /*11*/
#define ADC_ExternalTrigConv_T2_CC3                ((uint32_t)(ADC_CFGR1_EXTSEL_2 | ADC_CFGR1_EXTSEL_3))  /*12*/

/* TIM3 */
#define ADC_ExternalTrigConv_T3_TRGO               ((uint32_t)(ADC_CFGR1_EXTSEL_0 | ADC_CFGR1_EXTSEL_1))  /*3*/

/* TIM15 */
#define ADC_ExternalTrigConv_T15_TRGO               ADC_CFGR1_EXTSEL_2  /*4*/
/* CLU Trig */
#define ADC_ExternalTrigConv_CLU_TRGO               ((uint32_t)(ADC_CFGR1_EXTSEL_0 | ADC_CFGR1_EXTSEL_2)) /*5*/
/* IO Trig */
#define ADC_ExternalTrigConv_IO_TRGO               ((uint32_t)(ADC_CFGR1_EXTSEL_0 | ADC_CFGR1_EXTSEL_1 | ADC_CFGR1_EXTSEL_2))   /*7*/

#define IS_ADC_EXTERNAL_TRIG_CONV(CONV) (((CONV) == ADC_ExternalTrigConv_T1_TRGO) || \
                                         ((CONV) == ADC_ExternalTrigConv_T1_CC4)   || \
                                         ((CONV) == ADC_ExternalTrigConv_T2_TRGO)   || \
                                         ((CONV) == ADC_ExternalTrigConv_T3_TRGO)   || \
                                         ((CONV) == ADC_ExternalTrigConv_T15_TRGO)   || \
                                         ((CONV) == ADC_ExternalTrigConv_CLU_TRGO)  || \
                                         ((CONV) == ADC_ExternalTrigConv_T2_CC4)  || \
                                         ((CONV) == ADC_ExternalTrigConv_IO_TRGO) || \
                                         ((CONV) == ADC_ExternalTrigConv_T1_CC1)   || \
                                         ((CONV) == ADC_ExternalTrigConv_T1_CC2)   || \
                                         ((CONV) == ADC_ExternalTrigConv_T1_CC3)  || \
                                         ((CONV) == ADC_ExternalTrigConv_T2_CC2)  || \
                                         ((CONV) == ADC_ExternalTrigConv_T2_CC3))
/**
  * @}
  */

/** @defgroup ADC_data_align  ADC data align
  * @{
  */

#define ADC_DataAlign_Right                        ((uint32_t)0x00000000)
#define ADC_DataAlign_Left                         ADC_CFGR1_ALIGN

#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DataAlign_Right) || \
                                  ((ALIGN) == ADC_DataAlign_Left))
/**
  * @}
  */

/** @defgroup ADC_Scan_Direction  ADC Scan Direction
  * @{
  */

#define ADC_ScanDirection_Upward                   ((uint32_t)0x00000000)
#define ADC_ScanDirection_Backward                 ADC_CFGR1_SCANDIR

#define IS_ADC_SCAN_DIRECTION(DIRECTION) (((DIRECTION) == ADC_ScanDirection_Upward) || \
                                          ((DIRECTION) == ADC_ScanDirection_Backward))
/**
 * @}
 */

/** @defgroup ADC_DMA_Mode  ADC_DMA Mode
  * @{
  */

#define ADC_DMAMode_OneShot                        ((uint32_t)0x00000000)
#define ADC_DMAMode_Circular                       ADC_CFGR1_DMACFG

#define IS_ADC_DMA_MODE(MODE) (((MODE) == ADC_DMAMode_OneShot) || \
                               ((MODE) == ADC_DMAMode_Circular))
/**
  * @}
  */

/** @defgroup ADC_analog_watchdog_selection   ADC analog watchdog selection
  * @{
  */

#define ADC_AnalogWatchdog_Channel_0                 ((uint32_t)0x00000000)
#define ADC_AnalogWatchdog_Channel_1                 ((uint32_t)0x04000000)
#define ADC_AnalogWatchdog_Channel_2                 ((uint32_t)0x08000000)
#define ADC_AnalogWatchdog_Channel_3                 ((uint32_t)0x0C000000)
#define ADC_AnalogWatchdog_Channel_4                 ((uint32_t)0x10000000)
#define ADC_AnalogWatchdog_Channel_5                 ((uint32_t)0x14000000)
#define ADC_AnalogWatchdog_Channel_6                 ((uint32_t)0x18000000)
#define ADC_AnalogWatchdog_Channel_7                 ((uint32_t)0x1C000000)
#define ADC_AnalogWatchdog_Channel_8                 ((uint32_t)0x20000000)
#define ADC_AnalogWatchdog_Channel_9                 ((uint32_t)0x24000000)
#define ADC_AnalogWatchdog_Channel_10                 ((uint32_t)0x28000000)
#define ADC_AnalogWatchdog_Channel_11                 ((uint32_t)0x2C000000)
#define ADC_AnalogWatchdog_Channel_12                 ((uint32_t)0x30000000)
#define ADC_AnalogWatchdog_Channel_13                 ((uint32_t)0x34000000)
#define ADC_AnalogWatchdog_Channel_14                 ((uint32_t)0x38000000)
#define ADC_AnalogWatchdog_Channel_15                 ((uint32_t)0x3C000000)
#define ADC_AnalogWatchdog_Channel_16                 ((uint32_t)0x40000000)
#define ADC_AnalogWatchdog_Channel_17                 ((uint32_t)0x44000000)
#define ADC_AnalogWatchdog_Channel_18                 ((uint32_t)0x48000000)
#define ADC_AnalogWatchdog_Channel_19                 ((uint32_t)0x4C000000)




#define IS_ADC_ANALOG_WATCHDOG_CHANNEL(CHANNEL) (((CHANNEL) == ADC_AnalogWatchdog_Channel_0)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_1)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_2)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_3)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_4)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_5)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_6)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_7)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_8)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_9)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_10)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_11)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_12)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_13)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_14)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_15)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_16)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_17)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_18)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_19))
/**
  * @}
  */

/** @defgroup ADC_sampling_times  ADC sampling times
  * @{
  */

#define ADC_SampleTime_1_5Cycles                     ((uint32_t)0x00000000)
#define ADC_SampleTime_7_5Cycles                     ((uint32_t)0x00000001)
#define ADC_SampleTime_13_5Cycles                    ((uint32_t)0x00000002)
#define ADC_SampleTime_28_5Cycles                    ((uint32_t)0x00000003)
#define ADC_SampleTime_41_5Cycles                    ((uint32_t)0x00000004)
#define ADC_SampleTime_55_5Cycles                    ((uint32_t)0x00000005)
#define ADC_SampleTime_71_5Cycles                    ((uint32_t)0x00000006)
#define ADC_SampleTime_239_5Cycles                   ((uint32_t)0x00000007)

#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SampleTime_1_5Cycles)   || \
                                  ((TIME) == ADC_SampleTime_7_5Cycles)   || \
                                  ((TIME) == ADC_SampleTime_13_5Cycles)  || \
                                  ((TIME) == ADC_SampleTime_28_5Cycles)  || \
                                  ((TIME) == ADC_SampleTime_41_5Cycles)  || \
                                  ((TIME) == ADC_SampleTime_55_5Cycles)  || \
                                  ((TIME) == ADC_SampleTime_71_5Cycles)  || \
                                  ((TIME) == ADC_SampleTime_239_5Cycles))
/**
  * @}
  */

/** @defgroup ADC_thresholds   ADC thresholds
  * @{
  */

#define IS_ADC_THRESHOLD(THRESHOLD) ((THRESHOLD) <= 0xFFF)

/**
  * @}
  */

/** @defgroup ADC_channels   ADC channels
  * @{
  */

#define ADC_Channel_0                              ADC_CHSELR_CHSEL0
#define ADC_Channel_1                              ADC_CHSELR_CHSEL1
#define ADC_Channel_2                              ADC_CHSELR_CHSEL2
#define ADC_Channel_3                              ADC_CHSELR_CHSEL3
#define ADC_Channel_4                              ADC_CHSELR_CHSEL4
#define ADC_Channel_5                              ADC_CHSELR_CHSEL5
#define ADC_Channel_6                              ADC_CHSELR_CHSEL6
#define ADC_Channel_7                              ADC_CHSELR_CHSEL7
#define ADC_Channel_8                              ADC_CHSELR_CHSEL8
#define ADC_Channel_9                              ADC_CHSELR_CHSEL9
#define ADC_Channel_10                             ADC_CHSELR_CHSEL10
#define ADC_Channel_11                             ADC_CHSELR_CHSEL11
#define ADC_Channel_12                             ADC_CHSELR_CHSEL12
#define ADC_Channel_13                             ADC_CHSELR_CHSEL13
#define ADC_Channel_14                             ADC_CHSELR_CHSEL14
#define ADC_Channel_15                             ADC_CHSELR_CHSEL15
#define ADC_Channel_16                             ADC_CHSELR_CHSEL16
#define ADC_Channel_17                             ADC_CHSELR_CHSEL17
#define ADC_Channel_18                             ADC_CHSELR_CHSEL18
#define ADC_Channel_19                             ADC_CHSELR_CHSEL19


#define ADC_Channel_VLCD                         ((uint32_t)ADC_Channel_16)
#define ADC_Channel_Vrefint                        ((uint32_t)ADC_Channel_17)
#define ADC_Channel_TempSensor                     ((uint32_t)ADC_Channel_18)
#define ADC_Channel_OPAOut                         ((uint32_t)ADC_Channel_19)


#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) != (uint32_t)RESET) && (((CHANNEL) & 0xFFF00000) == (uint32_t)RESET))

/**
  * @}
  */

/** @defgroup ADC_interrupts_definition   ADC interrupts definition
  * @{
  */

#define ADC_IT_ADRDY                               ADC_IER_ADRDYIE
#define ADC_IT_EOSMP                               ADC_IER_EOSMPIE
#define ADC_IT_EOC                                 ADC_IER_EOCIE
#define ADC_IT_EOSEQ                               ADC_IER_EOSEQIE
#define ADC_IT_OVR                                 ADC_IER_OVRIE
#define ADC_IT_AWD                                 ADC_IER_AWDIE
#define ADC_IT_EOCAL                               ADC_IER_EOCALIE

#define IS_ADC_CONFIG_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFFF760) == (uint32_t)RESET))

#define IS_ADC_GET_IT(IT) (((IT) == ADC_IT_ADRDY) || ((IT) == ADC_IT_EOSMP) || \
                           ((IT) == ADC_IT_EOC)   || ((IT) == ADC_IT_EOSEQ) || \
                           ((IT) == ADC_IT_OVR)   || ((IT) == ADC_IT_AWD) || ((IT) == ADC_IT_EOCAL))

#define IS_ADC_CLEAR_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFFF760) == (uint32_t)RESET))

/**
  * @}
  */

/** @defgroup ADC_flags_definition   ADC flags definition
  * @{
  */

#define ADC_FLAG_ADRDY                             ADC_ISR_ADRDY
#define ADC_FLAG_EOSMP                             ADC_ISR_EOSMP
#define ADC_FLAG_EOC                               ADC_ISR_EOC
#define ADC_FLAG_EOSEQ                             ADC_ISR_EOSEQ
#define ADC_FLAG_OVR                               ADC_ISR_OVR
#define ADC_FLAG_AWD                               ADC_ISR_AWD
#define ADC_FLAG_EOCAL                             ADC_ISR_EOCAL

#define ADC_FLAG_ADEN                              ((uint32_t)0x00000001)
#define ADC_FLAG_ADDIS                             ((uint32_t)0x00000002)
#define ADC_FLAG_ADSTART                           ((uint32_t)0x00000004)
#define ADC_FLAG_ADSTP                             ((uint32_t)0x00000010)
#define ADC_FLAG_ADCAL                             ((uint32_t)0x80000000)

#define IS_ADC_CLEAR_FLAG(FLAG) (((FLAG) != (uint32_t)RESET) && (((FLAG) & 0xFFFFF760) == (uint32_t)RESET))

#define IS_ADC_GET_FLAG(FLAG) (((FLAG) == ADC_FLAG_ADRDY)   || ((FLAG) == ADC_FLAG_EOSMP) || \
                               ((FLAG) == ADC_FLAG_EOC)     || ((FLAG) == ADC_FLAG_EOSEQ) || \
                               ((FLAG) == ADC_FLAG_AWD)     || ((FLAG) == ADC_FLAG_OVR)   || \
                               ((FLAG) == ADC_FLAG_ADEN)    || ((FLAG) == ADC_FLAG_ADDIS) || \
                               ((FLAG) == ADC_FLAG_ADSTART) || ((FLAG) == ADC_FLAG_ADSTP) || \
                               ((FLAG) == ADC_FLAG_ADCAL))

#define ADC_AWDWkup_En                             ((uint32_t)0x80000000)
#define ADC_OVSEN                                  ((uint32_t)0x00000004)
#define ADC_SDIFDiffIn_En                          ((uint32_t)0x00000002)

#define TEMP85_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7C2))
#define TEMP25_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7B8))
#define VREFINT_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7C0))   
#define TEMPS_CAL_ADDR   ((uint32_t)0x1FFFF7BC)

#define ADC_CLOCK_ASYNC_DIV1                             ((uint32_t)0x00000000U)
#define ADC_CLOCK_ASYNC_DIV2                             ADC_CCR_PRESC_0
#define ADC_CLOCK_ASYNC_DIV4                             ADC_CCR_PRESC_1
#define ADC_CLOCK_ASYNC_DIV6                             (ADC_CCR_PRESC_0 | ADC_CCR_PRESC_1)
#define ADC_CLOCK_ASYNC_DIV8                             ADC_CCR_PRESC_2
#define ADC_CLOCK_ASYNC_DIV10                            (ADC_CCR_PRESC_0 | ADC_CCR_PRESC_2)
#define ADC_CLOCK_ASYNC_DIV12                            (ADC_CCR_PRESC_1 | ADC_CCR_PRESC_2)
#define ADC_CLOCK_ASYNC_DIV16                            (ADC_CCR_PRESC_0 | ADC_CCR_PRESC_1 | ADC_CCR_PRESC_2)
#define ADC_CLOCK_ASYNC_DIV32                            ADC_CCR_PRESC_3
#define ADC_CLOCK_ASYNC_DIV64                             (ADC_CCR_PRESC_0 | ADC_CCR_PRESC_3)
#define ADC_CLOCK_ASYNC_DIV128                            (ADC_CCR_PRESC_1 | ADC_CCR_PRESC_3)
#define ADC_CLOCK_ASYNC_DIV256                            (ADC_CCR_PRESC_0 | ADC_CCR_PRESC_1 | ADC_CCR_PRESC_3)

#define IS_ADC_CLOCK_ASYNC_DIV(CommonClock)  (((CommonClock) == ADC_CLOCK_ASYNC_DIV1 )   || \
                                              ((CommonClock) == ADC_CLOCK_ASYNC_DIV2 )   || \
                                              ((CommonClock) == ADC_CLOCK_ASYNC_DIV4 )   || \
                                              ((CommonClock) == ADC_CLOCK_ASYNC_DIV6 )   || \
                                              ((CommonClock) == ADC_CLOCK_ASYNC_DIV8 )   || \
                                              ((CommonClock) == ADC_CLOCK_ASYNC_DIV10 )   || \
                                              ((CommonClock) == ADC_CLOCK_ASYNC_DIV12 )   || \
                                              ((CommonClock) == ADC_CLOCK_ASYNC_DIV16 )   || \
                                              ((CommonClock) == ADC_CLOCK_ASYNC_DIV32 )   || \
                                              ((CommonClock) == ADC_CLOCK_ASYNC_DIV64 )   || \
                                              ((CommonClock) == ADC_CLOCK_ASYNC_DIV128 )   || \
                                              ((CommonClock) == ADC_CLOCK_ASYNC_DIV256 ))


#define ADC_ADCGAIN_SEL1_0                             ((uint32_t)0x00000000U)
#define ADC_ADCGAIN_SEL1_1                             ADC_GAIN_GAIN_SEL1_0
#define ADC_ADCGAIN_SEL1_2                             ADC_GAIN_GAIN_SEL1_1
#define ADC_ADCGAIN_SEL1_3                             ADC_GAIN_GAIN_SEL1_0 | ADC_GAIN_GAIN_SEL1_1
#define ADC_ADCGAIN_SEL1_4                             ADC_GAIN_GAIN_SEL1_2
#define ADC_ADCGAIN_SEL1_5                             ADC_GAIN_GAIN_SEL1_2 | ADC_GAIN_GAIN_SEL1_0

#define IS_ADC_ADCGAIN_SEL1(GAIN_SEL)  (((GAIN_SEL) == ADC_ADCGAIN_SEL1_0)   || \
                                        ((GAIN_SEL) == ADC_ADCGAIN_SEL1_1 )  || \
                                        ((GAIN_SEL) == ADC_ADCGAIN_SEL1_2 )  || \
                                        ((GAIN_SEL) == ADC_ADCGAIN_SEL1_3 )  || \
                                        ((GAIN_SEL) == ADC_ADCGAIN_SEL1_4 )  || \
                                        ((GAIN_SEL) == ADC_ADCGAIN_SEL1_5 ))

#define ADC_ADCGAIN_SEL2_0                             ((uint32_t)0x00000000U)
#define ADC_ADCGAIN_SEL2_1                             ADC_GAIN_GAIN_SEL2_0
#define ADC_ADCGAIN_SEL2_2                             ADC_GAIN_GAIN_SEL2_1
#define ADC_ADCGAIN_SEL2_3                             ADC_GAIN_GAIN_SEL2_0 | ADC_GAIN_GAIN_SEL2_1
#define ADC_ADCGAIN_SEL2_4                             ADC_GAIN_GAIN_SEL2_2
#define ADC_ADCGAIN_SEL2_5                             ADC_GAIN_GAIN_SEL2_2 | ADC_GAIN_GAIN_SEL2_0

#define IS_ADC_ADCGAIN_SEL2(GAIN_SEL)  (((GAIN_SEL) == ADC_ADCGAIN_SEL2_0)   || \
                                        ((GAIN_SEL) == ADC_ADCGAIN_SEL2_1 )  || \
                                        ((GAIN_SEL) == ADC_ADCGAIN_SEL2_2 )  || \
                                        ((GAIN_SEL) == ADC_ADCGAIN_SEL2_3 )  || \
                                        ((GAIN_SEL) == ADC_ADCGAIN_SEL2_4 )  || \
                                        ((GAIN_SEL) == ADC_ADCGAIN_SEL2_5 ))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @defgroup ADC_Exported_Functions  ADC Exported Functions
  * @{
  */
/*  Function used to set the ADC configuration to the default reset state *****/
void ADC_DeInit(ADC_TypeDef* ADCx);

/* Initialization and Configuration functions *********************************/
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_SetClock(ADC_TypeDef* ADCx, uint32_t ADC_ClockMode);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
uint32_t ADC_IsEnabled(ADC_TypeDef *ADCx);

/* Power saving functions *****************************************************/
void ADC_AutoPowerOffCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_WaitModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);

/* Analog Watchdog configuration functions ************************************/
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold, uint16_t LowThreshold);
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog_Channel);
void ADC_AnalogWatchdogSingleChannelCmd(ADC_TypeDef* ADCx, FunctionalState NewState);

/* Temperature Sensor , Vrefint and Vbat management function ******************/
void ADC_VrefintCmd(ADC_TypeDef *ADCx, FunctionalState NewState);
void ADC_TempSensorCmd(ADC_TypeDef *ADCx, FunctionalState NewState);
void ADC_VLCDCmd(ADC_TypeDef *ADCx, FunctionalState NewState);

/* Channels Configuration functions *******************************************/
void ADC_ChannelConfig(ADC_TypeDef* ADCx, uint32_t ADC_Channel, uint32_t ADC_SampleTime);
void ADC_ChannelReset(ADC_TypeDef* ADCx);
void ADC_ContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_OverrunModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
uint32_t ADC_GetCalibrationFactor(ADC_TypeDef* ADCx);
void ADC_StopOfConversion(ADC_TypeDef* ADCx);
void ADC_StartOfConversion(ADC_TypeDef* ADCx);
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx);

/* Interrupts and flags management functions **********************************/
void ADC_ITConfig(ADC_TypeDef* ADCx, uint32_t ADC_IT, FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint32_t ADC_IT);
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint32_t ADC_IT);

/*ADC Clock prescaler functions***************************************************/
void ADC_SetCommonClock(ADC_TypeDef *ADCx, uint32_t CommonClock);
uint32_t ADC_GetCommonClock(ADC_TypeDef *ADCx);

/*ADC oversampling functions***************************************************/
void ADC_OverSamplingCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_OverSamplingDiscontCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ConfigOverSamplingRatioShift(ADC_TypeDef *ADCx, uint32_t Ratio, uint32_t Shift);

/*ADC AWD wake up and Differential input mode functions****************************/
void ADC_AWDWKupCmd(ADC_TypeDef *ADCx,  FunctionalState NewState);
void ADC_OversamplingFunctionCmd(ADC_TypeDef *ADCx,  FunctionalState NewState);
void ADC_DiffModeCmd(ADC_TypeDef *ADCx,  FunctionalState NewState);

/*Get real VDDA when the power supply voltage changes*****************************/
uint32_t ADC_GETVDDA(uint32_t VrefADbuff);
/*Get Temperature (in degrees Celsius)********************************************/
int ADC_GetTemperatureATFT(void);
int ADC_GetTemperature(uint32_t tempADbuff, uint32_t VDDA_mV);

/*DMA Enable*********************************************************************/
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DMARequestModeConfig(ADC_TypeDef* ADCx, uint32_t ADC_DMARequestMode);

/*SET Resolution*********************************************************************/
void ADC_SETResolution(ADC_TypeDef* ADCx, uint32_t ADC_Resolution);

/*set the ADC GAIN_SEL configuration***************************************************/
void ADC_ConfigADCGainSel(ADC_TypeDef *ADCx, uint32_t GAIN_SEL1, uint32_t GAIN_SEL2);
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

#endif /*__HK32L0XX_ADC_H */

/**
  * @}
  */
