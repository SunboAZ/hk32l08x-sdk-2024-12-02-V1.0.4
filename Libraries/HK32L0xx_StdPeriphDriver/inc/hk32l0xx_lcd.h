/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_lcd.h
* @brief:     hk32l0xx_lcd configuration file.
*             The file is the unique include file that the application programmer
*             is using in the C source code, it is a patch file.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_LCD_H
#define __HK32L0XX_LCD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"


/** @addtogroup LCD LCD
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup LCD_Exported_Types LCD_Exported_Types
  * @{
  */

/**
  * @brief  LCD Init Structure definition
  */

typedef struct
{
    uint32_t LCD_Prescaler;       /*!< Configures the LCD Prescaler.
                                 This parameter can be one value of @ref LCD_Prescaler */
    uint32_t LCD_Divider;         /*!< Configures the LCD Divider.
                                 This parameter can be one value of @ref LCD_Divider */
    uint32_t LCD_Duty;            /*!< Configures the LCD Duty.
                                 This parameter can be one value of @ref LCD_Duty */
    uint32_t LCD_Bias;            /*!< Configures the LCD Bias.
                                 This parameter can be one value of @ref LCD_Bias */
    uint32_t LCD_Contrast;        /*!< Configures the LCD Contrast.
                                 This parameter can be one value of @ref LCD_Contrast */

} LCD_InitTypeDef;

/**
  * @}
  */


/** @defgroup LCD_Exported_Constants LCD_Exported_Constants
  * @{
  */

/** @defgroup LCD_Prescaler LCD_Prescaler
  * @{
  */

#define LCD_PRESCALER_1        ((uint32_t)0x00000000U)  /*!< CLKPS = LCDCLK        */
#define LCD_PRESCALER_2        ((uint32_t)0x00400000U)  /*!< CLKPS = LCDCLK/2      */
#define LCD_PRESCALER_4        ((uint32_t)0x00800000U)  /*!< CLKPS = LCDCLK/4      */
#define LCD_PRESCALER_8        ((uint32_t)0x00C00000U)  /*!< CLKPS = LCDCLK/8      */
#define LCD_PRESCALER_16       ((uint32_t)0x01000000U)  /*!< CLKPS = LCDCLK/16     */
#define LCD_PRESCALER_32       ((uint32_t)0x01400000U)  /*!< CLKPS = LCDCLK/32     */
#define LCD_PRESCALER_64       ((uint32_t)0x01800000U)  /*!< CLKPS = LCDCLK/64     */
#define LCD_PRESCALER_128      ((uint32_t)0x01C00000U)  /*!< CLKPS = LCDCLK/128    */
#define LCD_PRESCALER_256      ((uint32_t)0x02000000U)  /*!< CLKPS = LCDCLK/256    */
#define LCD_PRESCALER_512      ((uint32_t)0x02400000U)  /*!< CLKPS = LCDCLK/512    */
#define LCD_PRESCALER_1024     ((uint32_t)0x02800000U)  /*!< CLKPS = LCDCLK/1024   */
#define LCD_PRESCALER_2048     ((uint32_t)0x02C00000U)  /*!< CLKPS = LCDCLK/2048   */
#define LCD_PRESCALER_4096     ((uint32_t)0x03000000U)  /*!< CLKPS = LCDCLK/4096   */
#define LCD_PRESCALER_8192     ((uint32_t)0x03400000U)  /*!< CLKPS = LCDCLK/8192   */
#define LCD_PRESCALER_16384    ((uint32_t)0x03800000U)  /*!< CLKPS = LCDCLK/16384  */
#define LCD_PRESCALER_32768    ((uint32_t)LCD_FCR_PS)  /*!< CLKPS = LCDCLK/32768  */

#define IS_LCD_PRESCALER(__PRESCALER__) (((__PRESCALER__) == LCD_PRESCALER_1)     || \
                                         ((__PRESCALER__) == LCD_PRESCALER_2)     || \
                                         ((__PRESCALER__) == LCD_PRESCALER_4)     || \
                                         ((__PRESCALER__) == LCD_PRESCALER_8)     || \
                                         ((__PRESCALER__) == LCD_PRESCALER_16)    || \
                                         ((__PRESCALER__) == LCD_PRESCALER_32)    || \
                                         ((__PRESCALER__) == LCD_PRESCALER_64)    || \
                                         ((__PRESCALER__) == LCD_PRESCALER_128)   || \
                                         ((__PRESCALER__) == LCD_PRESCALER_256)   || \
                                         ((__PRESCALER__) == LCD_PRESCALER_512)   || \
                                         ((__PRESCALER__) == LCD_PRESCALER_1024)  || \
                                         ((__PRESCALER__) == LCD_PRESCALER_2048)  || \
                                         ((__PRESCALER__) == LCD_PRESCALER_4096)  || \
                                         ((__PRESCALER__) == LCD_PRESCALER_8192)  || \
                                         ((__PRESCALER__) == LCD_PRESCALER_16384) || \
                                         ((__PRESCALER__) == LCD_PRESCALER_32768))

/**
  * @}
  */

/** @defgroup LCD_Divider LCD_Divider
  * @{
  */

#define LCD_DIVIDER_16    ((uint32_t)0x00000000U)  /*!< LCD frequency = CLKPS/16 */
#define LCD_DIVIDER_17    ((uint32_t)0x00040000U)  /*!< LCD frequency = CLKPS/17 */
#define LCD_DIVIDER_18    ((uint32_t)0x00080000U)  /*!< LCD frequency = CLKPS/18 */
#define LCD_DIVIDER_19    ((uint32_t)0x000C0000U)  /*!< LCD frequency = CLKPS/19 */
#define LCD_DIVIDER_20    ((uint32_t)0x00100000U)  /*!< LCD frequency = CLKPS/20 */
#define LCD_DIVIDER_21    ((uint32_t)0x00140000U)  /*!< LCD frequency = CLKPS/21 */
#define LCD_DIVIDER_22    ((uint32_t)0x00180000U)  /*!< LCD frequency = CLKPS/22 */
#define LCD_DIVIDER_23    ((uint32_t)0x001C0000U)  /*!< LCD frequency = CLKPS/23 */
#define LCD_DIVIDER_24    ((uint32_t)0x00200000U)  /*!< LCD frequency = CLKPS/24 */
#define LCD_DIVIDER_25    ((uint32_t)0x00240000U)  /*!< LCD frequency = CLKPS/25 */
#define LCD_DIVIDER_26    ((uint32_t)0x00280000U)  /*!< LCD frequency = CLKPS/26 */
#define LCD_DIVIDER_27    ((uint32_t)0x002C0000U)  /*!< LCD frequency = CLKPS/27 */
#define LCD_DIVIDER_28    ((uint32_t)0x00300000U)  /*!< LCD frequency = CLKPS/28 */
#define LCD_DIVIDER_29    ((uint32_t)0x00340000U)  /*!< LCD frequency = CLKPS/29 */
#define LCD_DIVIDER_30    ((uint32_t)0x00380000U)  /*!< LCD frequency = CLKPS/30 */
#define LCD_DIVIDER_31    ((uint32_t)LCD_FCR_DIV) /*!< LCD frequency = CLKPS/31 */

#define IS_LCD_DIVIDER(__DIVIDER__) (((__DIVIDER__) == LCD_DIVIDER_16) || \
                                     ((__DIVIDER__) == LCD_DIVIDER_17) || \
                                     ((__DIVIDER__) == LCD_DIVIDER_18) || \
                                     ((__DIVIDER__) == LCD_DIVIDER_19) || \
                                     ((__DIVIDER__) == LCD_DIVIDER_20) || \
                                     ((__DIVIDER__) == LCD_DIVIDER_21) || \
                                     ((__DIVIDER__) == LCD_DIVIDER_22) || \
                                     ((__DIVIDER__) == LCD_DIVIDER_23) || \
                                     ((__DIVIDER__) == LCD_DIVIDER_24) || \
                                     ((__DIVIDER__) == LCD_DIVIDER_25) || \
                                     ((__DIVIDER__) == LCD_DIVIDER_26) || \
                                     ((__DIVIDER__) == LCD_DIVIDER_27) || \
                                     ((__DIVIDER__) == LCD_DIVIDER_28) || \
                                     ((__DIVIDER__) == LCD_DIVIDER_29) || \
                                     ((__DIVIDER__) == LCD_DIVIDER_30) || \
                                     ((__DIVIDER__) == LCD_DIVIDER_31))

/**
  * @}
  */


/** @defgroup LCD_Duty LCD_Duty
  * @{
  */

#define LCD_DUTY_STATIC                 ((uint32_t)0x00000000U)           /*!< Static duty */
#define LCD_DUTY_1_2                    (LCD_CR_DUTY_0)                   /*!< 1/2 duty    */
#define LCD_DUTY_1_3                    (LCD_CR_DUTY_1)                   /*!< 1/3 duty    */
#define LCD_DUTY_1_4                    ((LCD_CR_DUTY_1 | LCD_CR_DUTY_0)) /*!< 1/4 duty    */
#define LCD_DUTY_1_8                    (LCD_CR_DUTY_2)                   /*!< 1/8 duty    */

#define IS_LCD_DUTY(__DUTY__) (((__DUTY__) == LCD_DUTY_STATIC)  || \
                               ((__DUTY__) == LCD_DUTY_1_2)     || \
                               ((__DUTY__) == LCD_DUTY_1_3)     || \
                               ((__DUTY__) == LCD_DUTY_1_4)     || \
                               ((__DUTY__) == LCD_DUTY_1_8))

/**
  * @}
  */


/** @defgroup LCD_Bias LCD Bias
  * @{
  */

#define LCD_BIAS_1_4                    ((uint32_t)0x00000000U) /*!< 1/4 Bias */
#define LCD_BIAS_1_2                    LCD_CR_BIAS_0           /*!< 1/2 Bias */
#define LCD_BIAS_1_3                    LCD_CR_BIAS_1           /*!< 1/3 Bias */

#define IS_LCD_BIAS(__BIAS__) (((__BIAS__) == LCD_BIAS_1_4) || \
                               ((__BIAS__) == LCD_BIAS_1_2) || \
                               ((__BIAS__) == LCD_BIAS_1_3))
/**
  * @}
  */

/** @defgroup LCD_Voltage_Source LCD_Voltage_Source
  * @{
  */

#define LCD_VOLTAGESOURCE_INTERNAL      ((uint32_t)0x00000000U) /*!< Internal voltage source for the LCD */

#define IS_LCD_VOLTAGE_SOURCE(SOURCE)   ((SOURCE) == LCD_VOLTAGESOURCE_INTERNAL)

/**
  * @}
  */

/** @defgroup LCD_Interrupts LCD_Interrupts
  * @{
  */
#define LCD_IT_SOF                      LCD_FCR_SOFIE
#define LCD_IT_UDD                      LCD_FCR_UDDIE

#define IS_LCD_CONFIG_IT(LCD_IT)    (((LCD_IT) == LCD_IT_SOF) || \
                                                                     ((LCD_IT) == LCD_IT_UDD)  )
/**
  * @}
  */

/** @defgroup LCD_PulseOnDuration LCD_PulseOnDuration
  * @{
  */

#define LCD_PULSEONDURATION_0           ((uint32_t)0x00000000U)         /*!< Pulse ON duration = 0 pulse   */
#define LCD_PULSEONDURATION_1           (LCD_FCR_PON_0)                 /*!< Pulse ON duration = 1/CK_PS  */
#define LCD_PULSEONDURATION_2           (LCD_FCR_PON_1)                 /*!< Pulse ON duration = 2/CK_PS  */
#define LCD_PULSEONDURATION_3           (LCD_FCR_PON_1 | LCD_FCR_PON_0) /*!< Pulse ON duration = 3/CK_PS  */
#define LCD_PULSEONDURATION_4           (LCD_FCR_PON_2)                 /*!< Pulse ON duration = 4/CK_PS  */
#define LCD_PULSEONDURATION_5           (LCD_FCR_PON_2 | LCD_FCR_PON_0) /*!< Pulse ON duration = 5/CK_PS  */
#define LCD_PULSEONDURATION_6           (LCD_FCR_PON_2 | LCD_FCR_PON_1) /*!< Pulse ON duration = 6/CK_PS  */
#define LCD_PULSEONDURATION_7           (LCD_FCR_PON)                   /*!< Pulse ON duration = 7/CK_PS  */

#define IS_LCD_PULSE_ON_DURATION(__DURATION__) (((__DURATION__) == LCD_PULSEONDURATION_0) || \
                                                ((__DURATION__) == LCD_PULSEONDURATION_1) || \
                                                ((__DURATION__) == LCD_PULSEONDURATION_2) || \
                                                ((__DURATION__) == LCD_PULSEONDURATION_3) || \
                                                ((__DURATION__) == LCD_PULSEONDURATION_4) || \
                                                ((__DURATION__) == LCD_PULSEONDURATION_5) || \
                                                ((__DURATION__) == LCD_PULSEONDURATION_6) || \
                                                ((__DURATION__) == LCD_PULSEONDURATION_7))
/**
  * @}
  */

/** @defgroup LCD_HighDrive LCD_HighDrive
  * @{
  */

#define LCD_HIGHDRIVE_0           ((uint32_t)0x00000000U)         /*!< Low resistance Drive   */
#define LCD_HIGHDRIVE_1           (LCD_FCR_HD)                    /*!< High resistance Drive  */

#define IS_LCD_HIGHDRIVE(__HIGHDRIVE__) (((__HIGHDRIVE__) == LCD_HIGHDRIVE_0) || \
                                         ((__HIGHDRIVE__) == LCD_HIGHDRIVE_1))
/**
  * @}
  */

/** @defgroup LCD_DeadTime LCD_DeadTime
  * @{
  */

#define LCD_DEADTIME_0                  ((uint32_t)0x00000000U)           /*!< No dead Time  */
#define LCD_DEADTIME_1                  (LCD_FCR_DEAD_0)                  /*!< One Phase between different couple of Frame   */
#define LCD_DEADTIME_2                  (LCD_FCR_DEAD_1)                  /*!< Two Phase between different couple of Frame   */
#define LCD_DEADTIME_3                  (LCD_FCR_DEAD_1 | LCD_FCR_DEAD_0) /*!< Three Phase between different couple of Frame */
#define LCD_DEADTIME_4                  (LCD_FCR_DEAD_2)                  /*!< Four Phase between different couple of Frame  */
#define LCD_DEADTIME_5                  (LCD_FCR_DEAD_2 | LCD_FCR_DEAD_0) /*!< Five Phase between different couple of Frame  */
#define LCD_DEADTIME_6                  (LCD_FCR_DEAD_2 | LCD_FCR_DEAD_1) /*!< Six Phase between different couple of Frame   */
#define LCD_DEADTIME_7                  (LCD_FCR_DEAD)                    /*!< Seven Phase between different couple of Frame */

#define IS_LCD_DEAD_TIME(__TIME__) (((__TIME__) == LCD_DEADTIME_0) || \
                                    ((__TIME__) == LCD_DEADTIME_1) || \
                                    ((__TIME__) == LCD_DEADTIME_2) || \
                                    ((__TIME__) == LCD_DEADTIME_3) || \
                                    ((__TIME__) == LCD_DEADTIME_4) || \
                                    ((__TIME__) == LCD_DEADTIME_5) || \
                                    ((__TIME__) == LCD_DEADTIME_6) || \
                                    ((__TIME__) == LCD_DEADTIME_7))
/**
  * @}
  */

/** @defgroup LCD_BlinkMode LCD_BlinkMode
  * @{
  */

#define LCD_BLINKMODE_OFF               ((uint32_t)0x00000000U) /*!< Blink disabled            */
#define LCD_BLINKMODE_SEG0_COM0         (LCD_FCR_BLINK_0)       /*!< Blink enabled on SEG[0], COM[0] (1 pixel)   */
#define LCD_BLINKMODE_SEG0_ALLCOM       (LCD_FCR_BLINK_1)       /*!< Blink enabled on SEG[0], all COM (up to 
                                                                    8 pixels according to the programmed duty)  */
#define LCD_BLINKMODE_ALLSEG_ALLCOM     (LCD_FCR_BLINK)         /*!< Blink enabled on all SEG and all COM (all pixels)  */

#define IS_LCD_BLINK_MODE(__MODE__) (((__MODE__) == LCD_BLINKMODE_OFF)            || \
                                     ((__MODE__) == LCD_BLINKMODE_SEG0_COM0)      || \
                                     ((__MODE__) == LCD_BLINKMODE_SEG0_ALLCOM)    || \
                                     ((__MODE__) == LCD_BLINKMODE_ALLSEG_ALLCOM))
/**
  * @}
  */

/** @defgroup LCD_BlinkFrequency LCD_BlinkFrequency
  * @{
  */

#define LCD_BLINKFREQUENCY_DIV8         ((uint32_t)0x00000000U)               /*!< The Blink frequency = fLCD/8    */
#define LCD_BLINKFREQUENCY_DIV16        (LCD_FCR_BLINKF_0)                    /*!< The Blink frequency = fLCD/16   */
#define LCD_BLINKFREQUENCY_DIV32        (LCD_FCR_BLINKF_1)                    /*!< The Blink frequency = fLCD/32   */
#define LCD_BLINKFREQUENCY_DIV64        (LCD_FCR_BLINKF_1 | LCD_FCR_BLINKF_0) /*!< The Blink frequency = fLCD/64   */
#define LCD_BLINKFREQUENCY_DIV128       (LCD_FCR_BLINKF_2)                    /*!< The Blink frequency = fLCD/128  */
#define LCD_BLINKFREQUENCY_DIV256       (LCD_FCR_BLINKF_2 |LCD_FCR_BLINKF_0)  /*!< The Blink frequency = fLCD/256  */
#define LCD_BLINKFREQUENCY_DIV512       (LCD_FCR_BLINKF_2 |LCD_FCR_BLINKF_1)  /*!< The Blink frequency = fLCD/512  */
#define LCD_BLINKFREQUENCY_DIV1024      (LCD_FCR_BLINKF)                      /*!< The Blink frequency = fLCD/1024 */

#define IS_LCD_BLINK_FREQUENCY(__FREQUENCY__) (((__FREQUENCY__) == LCD_BLINKFREQUENCY_DIV8)   || \
                                               ((__FREQUENCY__) == LCD_BLINKFREQUENCY_DIV16)  || \
                                               ((__FREQUENCY__) == LCD_BLINKFREQUENCY_DIV32)  || \
                                               ((__FREQUENCY__) == LCD_BLINKFREQUENCY_DIV64)  || \
                                               ((__FREQUENCY__) == LCD_BLINKFREQUENCY_DIV128) || \
                                               ((__FREQUENCY__) == LCD_BLINKFREQUENCY_DIV256) || \
                                               ((__FREQUENCY__) == LCD_BLINKFREQUENCY_DIV512) || \
                                               ((__FREQUENCY__) == LCD_BLINKFREQUENCY_DIV1024))
/**
  * @}
  */

/** @defgroup LCD_Contrast LCD_Contrast
  * @{
  */

#define LCD_CONTRASTLEVEL_0               ((uint32_t)0x00000000U)       /*!< Maximum Voltage = 2.60V    */
#define LCD_CONTRASTLEVEL_1               (LCD_FCR_CC_0)                /*!< Maximum Voltage = 2.73V    */
#define LCD_CONTRASTLEVEL_2               (LCD_FCR_CC_1)                /*!< Maximum Voltage = 2.86V    */
#define LCD_CONTRASTLEVEL_3               (LCD_FCR_CC_1 | LCD_FCR_CC_0) /*!< Maximum Voltage = 2.99V    */
#define LCD_CONTRASTLEVEL_4               (LCD_FCR_CC_2)                /*!< Maximum Voltage = 3.12V    */
#define LCD_CONTRASTLEVEL_5               (LCD_FCR_CC_2 | LCD_FCR_CC_0) /*!< Maximum Voltage = 3.25V    */
#define LCD_CONTRASTLEVEL_6               (LCD_FCR_CC_2 | LCD_FCR_CC_1) /*!< Maximum Voltage = 3.38V    */
#define LCD_CONTRASTLEVEL_7               (LCD_FCR_CC)                  /*!< Maximum Voltage = 3.51V    */

#define IS_LCD_CONTRAST(__CONTRAST__) (((__CONTRAST__) == LCD_CONTRASTLEVEL_0) || \
                                       ((__CONTRAST__) == LCD_CONTRASTLEVEL_1) || \
                                       ((__CONTRAST__) == LCD_CONTRASTLEVEL_2) || \
                                       ((__CONTRAST__) == LCD_CONTRASTLEVEL_3) || \
                                       ((__CONTRAST__) == LCD_CONTRASTLEVEL_4) || \
                                       ((__CONTRAST__) == LCD_CONTRASTLEVEL_5) || \
                                       ((__CONTRAST__) == LCD_CONTRASTLEVEL_6) || \
                                       ((__CONTRAST__) == LCD_CONTRASTLEVEL_7))
/**
  * @}
  */

/** @defgroup LCD_MuxSegment LCD Mux Segment
  * @{
  */

#define LCD_MUXSEGMENT_DISABLE            ((uint32_t)0x00000000U)       /*!< SEG pin multiplexing disabled */
#define LCD_MUXSEGMENT_ENABLE             (LCD_CR_MUX_SEG)              /*!< SEG[31:28] are multiplexed with SEG[43:40]    */

#define IS_LCD_MUXSEGMENT(__VALUE__) (((__VALUE__) == LCD_MUXSEGMENT_ENABLE) || \
                                      ((__VALUE__) == LCD_MUXSEGMENT_DISABLE))
/**
  * @}
  */

/** @defgroup LCD_Flag LCD_Flag
  * @{
  */

#define LCD_FLAG_ENS                    LCD_SR_ENS
#define LCD_FLAG_SOF                    LCD_SR_SOF
#define LCD_FLAG_UDR                    LCD_SR_UDR
#define LCD_FLAG_UDD                    LCD_SR_UDD
#define LCD_FLAG_RDY                    LCD_SR_RDY
#define LCD_FLAG_FCRSF                  LCD_SR_FCRSF

#define IS_LCD_FLAG(__FLAG__)  (((__FLAG__) == LCD_FLAG_ENS) || \
                                                                ((__FLAG__) == LCD_FLAG_SOF) || \
                                                                ((__FLAG__) == LCD_FLAG_UDR) || \
                                                                ((__FLAG__) == LCD_FLAG_UDD) || \
                                                                ((__FLAG__) == LCD_FLAG_RDY) || \
                                                                ((__FLAG__) == LCD_FLAG_FCRSF))

/**
  * @}
  */

/** @defgroup LCD_RAMRegister LCD_RAMRegister
  * @{
  */

#define LCD_RAM_COM0               ((uint8_t)0x00U) /*!< LCD RAM Register 0  */
#define LCD_RAM_COM1               ((uint8_t)0x01U) /*!< LCD RAM Register 2  */
#define LCD_RAM_COM2               ((uint8_t)0x02U) /*!< LCD RAM Register 4  */
#define LCD_RAM_COM3               ((uint8_t)0x03U) /*!< LCD RAM Register 6  */
#define LCD_RAM_COM4               ((uint8_t)0x04U) /*!< LCD RAM Register 8  */
#define LCD_RAM_COM5               ((uint8_t)0x05U) /*!< LCD RAM Register 10 */
#define LCD_RAM_COM6               ((uint8_t)0x06U) /*!< LCD RAM Register 12 */
#define LCD_RAM_COM7               ((uint8_t)0x07U) /*!< LCD RAM Register 14 */

#define IS_LCD_RAM_COM(__COM__)                     (((__COM__) == LCD_RAM_COM0)  || \
                                           ((__COM__) == LCD_RAM_COM1)  || \
                                           ((__COM__) == LCD_RAM_COM2)  || \
                                           ((__COM__) == LCD_RAM_COM3)  || \
                                           ((__COM__) == LCD_RAM_COM4)  || \
                                           ((__COM__) == LCD_RAM_COM5)  || \
                                           ((__COM__) == LCD_RAM_COM6)  || \
                                           ((__COM__) == LCD_RAM_COM7))

/**
  * @}
  */

/**
  * @}
  */


/** @defgroup LCD_Exported_Functions LCD_Exported_Functions
  * @{
  */
void LCD_Init(LCD_InitTypeDef *LCD_InitStruct);
void LCD_MuxSegentCmd(FunctionalState NewState);
void LCD_VoltageSource(uint8_t Voltage_Source);
void LCD_BiasConfg(uint8_t Bias);
void LCD_DutyConfig(uint8_t Duty);
void LCD_Cmd(FunctionalState NewState);
void LCD_SetPrescaler(uint32_t Prescaler);
void LCD_SetDivider(uint32_t Divider_value);
void LCD_BlinkModeCmd(uint32_t Num, FunctionalState NewState);
void LCD_BlinkFrequencyConfig(uint32_t BlinkFrequency);
void LCD_SetContrast(uint32_t Contrast);
void LCD_SetDeadTime(uint32_t DeadTime);
void LCD_PulseOnDuration(uint32_t DURATION);
void LCD_ITConfig(uint32_t LCD_IT, FunctionalState NewState);
void LCD_MiddleDriveCmd(FunctionalState NewState);
void LCD_HighDriveCmd(FunctionalState NewState);
void LCD_ClearFlag( uint32_t LCD_FLAG);
void LCD_WrietNoMask(uint32_t COM, uint32_t DATA);
void LCD_WriteMask(uint32_t COM, uint32_t DATA);
void LCD_UpdateDisplayRequest(void);
FlagStatus LCD_GetFlagStatus(uint32_t LCD_FLAG);
void LCD_ComEnable(uint8_t ComNumber, FunctionalState NewState);
void LCD_SegEnable(uint32_t SegNumber, FunctionalState NewState);
void LCD_WaitForSynchro(void);
/**
  * @}
  */


/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_LCD_H */






