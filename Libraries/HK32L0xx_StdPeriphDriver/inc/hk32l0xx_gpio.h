/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_gpio.h
* @brief:     API file of gpio module
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_GPIO_H
#define __HK32L0XX_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"

/** @addtogroup GPIO
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Types  GPIO_Exported_Types
  * @{
  */


#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                    ((PERIPH) == GPIOB) || \
                                    ((PERIPH) == GPIOC) || \
                                    ((PERIPH) == GPIOD) || \
                                    ((PERIPH) == GPIOF))

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** @defgroup Configuration_Mode_enumeration    Configuration_Mode
  * @{
  */
typedef enum
{
    GPIO_Mode_IN   = 0x00, /*!< GPIO Input Mode              */
    GPIO_Mode_OUT  = 0x01, /*!< GPIO Output Mode             */
    GPIO_Mode_AF   = 0x02, /*!< GPIO Alternate function Mode */
    GPIO_Mode_AN   = 0x03  /*!< GPIO Analog In/Out Mode      */
} GPIOMode_TypeDef;

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_IN)|| ((MODE) == GPIO_Mode_OUT) || \
                            ((MODE) == GPIO_Mode_AF)|| ((MODE) == GPIO_Mode_AN))
/**
  * @}
  */

/** @defgroup Output_type_enumeration   Output_type
  * @{
  */
typedef enum
{
    GPIO_OType_PP = 0x00,
    GPIO_OType_OD = 0x01
} GPIOOType_TypeDef;

#define IS_GPIO_OTYPE(OTYPE) (((OTYPE) == GPIO_OType_PP) || ((OTYPE) == GPIO_OType_OD))

/**
  * @}
  */

/** @defgroup Output_Maximum_frequency_enumeration   Output_Maximum_frequency
  * @{
  */
typedef enum
{
    GPIO_Speed_Level_1  = 0x00, /*!< I/O output speed: Low 2 MHz */
    GPIO_Speed_Level_2  = 0x01, /*!< I/O output speed: Medium 10 MHz */
    GPIO_Speed_Level_3  = 0x03  /*!< I/O output speed: High 50 MHz */
} GPIOSpeed_TypeDef;

#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Speed_Level_1) || ((SPEED) == GPIO_Speed_Level_2) || \
                              ((SPEED) == GPIO_Speed_Level_3))
/**
  * @}
  */

/** @defgroup Configuration_Pull-Up_Pull-Down_enumeration   Configuration_Pull-Up_Pull-Down
  * @{
  */
typedef enum
{
    GPIO_PuPd_NOPULL = 0x00,
    GPIO_PuPd_UP     = 0x01,
    GPIO_PuPd_DOWN   = 0x02
} GPIOPuPd_TypeDef;

#define IS_GPIO_PUPD(PUPD) (((PUPD) == GPIO_PuPd_NOPULL) || ((PUPD) == GPIO_PuPd_UP) || \
                            ((PUPD) == GPIO_PuPd_DOWN))
/**
  * @}
  */

/** @defgroup Bit_SET_and_Bit_RESET_enumeration     Bit_SET_and_Bit_RESET
  * @{
  */
typedef enum
{
    Bit_RESET = 0,
    Bit_SET
} BitAction;

#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))
/**
  * @}
  */

/** @defgroup Schmit_enable_or_disable_enumeration     Schmit_enable_or_disable
  * @{
  */
typedef enum
{
    GPIO_Schmit_Disable = 0x0,
    GPIO_Schmit_Enable  = 0x1,
} GPIOSchmit_TypeDef;
/**
  * @}
  */

/**
* @brief  TIM Time Base Init structure definition
*/
typedef struct
{
    uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
                                       This parameter can be any value of @ref GPIO_pins_define */

    GPIOMode_TypeDef GPIO_Mode;     /*!< Specifies the operating mode for the selected pins.
                                       This parameter can be a value of @ref GPIOMode_TypeDef   */

    GPIOSpeed_TypeDef GPIO_Speed;   /*!< Specifies the speed for the selected pins.
                                       This parameter can be a value of @ref GPIOSpeed_TypeDef  */

    GPIOOType_TypeDef GPIO_OType;   /*!< Specifies the operating output type for the selected pins.
                                       This parameter can be a value of @ref GPIOOType_TypeDef  */

    GPIOPuPd_TypeDef GPIO_PuPd;     /*!< Specifies the operating Pull-up/Pull down for the selected pins.
                                       This parameter can be a value of @ref GPIOPuPd_TypeDef   */

    GPIOSchmit_TypeDef  GPIO_Schmit; /*!<Specifies the operating Schmidt function switch.
                                       This parameter can be a value of @ref GPIOSchmit_TypeDef>*/

} GPIO_InitTypeDef;


/** @defgroup GPIO_Exported_Constants    GPIO_Exported_Constants
  * @{
  */

/** @defgroup GPIO_pins_define          GPIO_pins_define
  * @{
  */
#define GPIO_Pin_0                 ((uint16_t)0x0001)  /*!< Pin 0 selected    */
#define GPIO_Pin_1                 ((uint16_t)0x0002)  /*!< Pin 1 selected    */
#define GPIO_Pin_2                 ((uint16_t)0x0004)  /*!< Pin 2 selected    */
#define GPIO_Pin_3                 ((uint16_t)0x0008)  /*!< Pin 3 selected    */
#define GPIO_Pin_4                 ((uint16_t)0x0010)  /*!< Pin 4 selected    */
#define GPIO_Pin_5                 ((uint16_t)0x0020)  /*!< Pin 5 selected    */
#define GPIO_Pin_6                 ((uint16_t)0x0040)  /*!< Pin 6 selected    */
#define GPIO_Pin_7                 ((uint16_t)0x0080)  /*!< Pin 7 selected    */
#define GPIO_Pin_8                 ((uint16_t)0x0100)  /*!< Pin 8 selected    */
#define GPIO_Pin_9                 ((uint16_t)0x0200)  /*!< Pin 9 selected    */
#define GPIO_Pin_10                ((uint16_t)0x0400)  /*!< Pin 10 selected   */
#define GPIO_Pin_11                ((uint16_t)0x0800)  /*!< Pin 11 selected   */
#define GPIO_Pin_12                ((uint16_t)0x1000)  /*!< Pin 12 selected   */
#define GPIO_Pin_13                ((uint16_t)0x2000)  /*!< Pin 13 selected   */
#define GPIO_Pin_14                ((uint16_t)0x4000)  /*!< Pin 14 selected   */
#define GPIO_Pin_15                ((uint16_t)0x8000)  /*!< Pin 15 selected   */
#define GPIO_Pin_All               ((uint16_t)0xFFFF)  /*!< All pins selected */

#define IS_GPIO_PIN(PIN) ((PIN) != (uint16_t)0x00)

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
                              ((PIN) == GPIO_Pin_1) || \
                              ((PIN) == GPIO_Pin_2) || \
                              ((PIN) == GPIO_Pin_3) || \
                              ((PIN) == GPIO_Pin_4) || \
                              ((PIN) == GPIO_Pin_5) || \
                              ((PIN) == GPIO_Pin_6) || \
                              ((PIN) == GPIO_Pin_7) || \
                              ((PIN) == GPIO_Pin_8) || \
                              ((PIN) == GPIO_Pin_9) || \
                              ((PIN) == GPIO_Pin_10) || \
                              ((PIN) == GPIO_Pin_11) || \
                              ((PIN) == GPIO_Pin_12) || \
                              ((PIN) == GPIO_Pin_13) || \
                              ((PIN) == GPIO_Pin_14) || \
                              ((PIN) == GPIO_Pin_15))

/**
  * @}
  */

/** @defgroup GPIO_Pin_sources  GPIO_Pin_sources
  * @{
  */
#define GPIO_PinSource0            ((uint8_t)0x00)
#define GPIO_PinSource1            ((uint8_t)0x01)
#define GPIO_PinSource2            ((uint8_t)0x02)
#define GPIO_PinSource3            ((uint8_t)0x03)
#define GPIO_PinSource4            ((uint8_t)0x04)
#define GPIO_PinSource5            ((uint8_t)0x05)
#define GPIO_PinSource6            ((uint8_t)0x06)
#define GPIO_PinSource7            ((uint8_t)0x07)
#define GPIO_PinSource8            ((uint8_t)0x08)
#define GPIO_PinSource9            ((uint8_t)0x09)
#define GPIO_PinSource10           ((uint8_t)0x0A)
#define GPIO_PinSource11           ((uint8_t)0x0B)
#define GPIO_PinSource12           ((uint8_t)0x0C)
#define GPIO_PinSource13           ((uint8_t)0x0D)
#define GPIO_PinSource14           ((uint8_t)0x0E)
#define GPIO_PinSource15           ((uint8_t)0x0F)

#define IS_GPIO_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == GPIO_PinSource0) || \
                                       ((PINSOURCE) == GPIO_PinSource1) || \
                                       ((PINSOURCE) == GPIO_PinSource2) || \
                                       ((PINSOURCE) == GPIO_PinSource3) || \
                                       ((PINSOURCE) == GPIO_PinSource4) || \
                                       ((PINSOURCE) == GPIO_PinSource5) || \
                                       ((PINSOURCE) == GPIO_PinSource6) || \
                                       ((PINSOURCE) == GPIO_PinSource7) || \
                                       ((PINSOURCE) == GPIO_PinSource8) || \
                                       ((PINSOURCE) == GPIO_PinSource9) || \
                                       ((PINSOURCE) == GPIO_PinSource10) || \
                                       ((PINSOURCE) == GPIO_PinSource11) || \
                                       ((PINSOURCE) == GPIO_PinSource12) || \
                                       ((PINSOURCE) == GPIO_PinSource13) || \
                                       ((PINSOURCE) == GPIO_PinSource14) || \
                                       ((PINSOURCE) == GPIO_PinSource15))
/**
  * @}
  */

/** @defgroup GPIO_Alternate_function_selection_define    GPIO_Alternate_function
  * @{
  */

/**
  * @brief  AF 0 selection
  * TIM15_CH1, TIM15_CH2, SPI1_NSS/I2S1_WS, SPI1_SCK/I2S1_CK, SPI1_MISO/I2S1_MCK, SPI1_MOSI/I2S1_SD, MCO, TIM15_BKIN, SWDIO, SWCLK,
  * TIM14_CH1, USART1_TX, USART1_RX, SPI2_NSS/I2S2_WS, SPI2_SCK/I2S2_CK, TIM3_CH1, TIM3_CH2, TIM3_CH3, TIM3_CH4, TIM3_CH1/TIM3_ETR, TIM17_BKIN
  */

#define GPIO_AF_0            ((uint8_t)0x00)
/**
  * @brief  AF 1 selection
  * USART1_CTS, USART1_RTS/USART1_DE, USART1_TX, USART1_RX, USART1_CK, TIM3_CH1, TIM3_CH2, IROUT, TIM3_CH3, TIM3_CH4,
  * I2C2_SMBA, I2C1_SCL, I2C1_SDA, I2C2_SCL, I2C2_SDA, SPI2_NSS/I2S2_WS, SPI2_SCK/I2S2_CK, SPI2_MISO/I2S2_MCK, SPI2_MOSI/I2S2_SD,
  */
#define GPIO_AF_1            ((uint8_t)0x01)
/**
  * @brief  AF 2 selection
  * TIM2_CH1/TIM2_ETR, TIM2_CH2, TIM2_CH3, TIM2_CH4, TIM1_BKIN, TIM1_CH1N, TIM1_CH1, TIM1_CH2, TIM1_CH3, TIM1_CH4, TIM1_ETR,
  * USB_NOE, TIM1_CH2N, TIM1_CH3N, TIM16_BKIN, TIM16_CH1N, TIM17_CH1N, TIM16_CH1, IROUT, LPUART1_TX, LPUART1_RX, LPUART1_RTS/LPUART1_DE
  */
#define GPIO_AF_2            ((uint8_t)0x02)
/**
  * @brief  AF 3 selection
  * LPUART1_CTS, MCO, LPUART1_TX, LPUART1_RX, I2C1_SCL, I2C1_SDA, LPUART1_RTS/LPUART1_DE, I2C1_SMBA, TIM17_CH1, TIM15_CH1N
  */
#define GPIO_AF_3            ((uint8_t)0x03)

/**
  * @brief  AF 4 selection
  * USART2_CTS, USART2_RTS/USART2_DE, USART2_TX, USART2_RX, USART2_CK, CAN_RX, CAN_TX, I2C1_SCL, I2C1_SDA, I2C1_SMBA,
  * TIM15_BKIN, TIM15_CH1, TIM15_CH2
  */
#define GPIO_AF_4            ((uint8_t)0x04)

/**
  * @brief  AF 5 selection
  * TIM15_CH1N, UART3_TX, UART3_RX, UART3_CTS, UART3_RTS/UART3_DE, I2C2_SCL, I2C2_SDA, TIM17_BKIN, I2C2_SMBA
  */
#define GPIO_AF_5            ((uint8_t)0x05)

/**
  * @brief  AF 6 selection
  * I2C1_SMBA, I2C1_SCL, I2C1_SDA
  */
#define GPIO_AF_6            ((uint8_t)0x06)
/**
  * @brief  AF 7 selection
  * COMP1_OUT, COMP2_OUT
  */
#define GPIO_AF_7            ((uint8_t)0x07)
/**
  * @brief  AF 8 selection
  * EVENTOUT, CAN_RX, CAN_TX, RTC_OUT
  */
#define GPIO_AF_8            ((uint8_t)0x08)
/**
  * @brief  AF 9 selection
  * UART4_TX, UART4_RX, TIM14_CH1, UART4_CTS, USART2_TX, USART2_RX, UART4_RTS/UART4_DE
  */
#define GPIO_AF_9            ((uint8_t)0x09)
/**
  * @brief  AF 10 selection
  * TIM16_CH1, TIM17_CH1, MCO, CLU0_O
  */
#define GPIO_AF_10           ((uint8_t)0x0a)
/**
  * @brief  AF 11 selection
  * CLU1_O
  */
#define GPIO_AF_11           ((uint8_t)0x0b)
/**
  * @brief  AF 12 selection
  * CLU2_O
  */
#define GPIO_AF_12           ((uint8_t)0x0c)
/**
  * @brief  AF 13 selection
  * CLU3_O
  */
#define GPIO_AF_13           ((uint8_t)0x0d)
/**
  * @brief  AF 14 selection
  * BEEPER
  */
#define GPIO_AF_14           ((uint8_t)0x0e)


#define IS_GPIO_AF(AF)     (((AF) == GPIO_AF_0) || ((AF) == GPIO_AF_1)  || \
                           ((AF) == GPIO_AF_2)  || ((AF) == GPIO_AF_3)  || \
                           ((AF) == GPIO_AF_4)  || ((AF) == GPIO_AF_5)  || \
                           ((AF) == GPIO_AF_6)  || ((AF) == GPIO_AF_7)  || \
                           ((AF) == GPIO_AF_8)  || ((AF) == GPIO_AF_9)  || \
                           ((AF) == GPIO_AF_10) || ((AF) == GPIO_AF_11) || \
                           ((AF) == GPIO_AF_12) || ((AF) == GPIO_AF_13) || \
                           ((AF) == GPIO_AF_14))
/**
  * @}
  */

/** @defgroup GPIO_Speed_Legacy    GPIO_Speed
  * @{
  */
#define GPIO_Speed_2MHz  GPIO_Speed_Level_1   /*!< I/O output speed: Low 2 MHz  */
#define GPIO_Speed_10MHz GPIO_Speed_Level_2   /*!< I/O output speed: Medium 10 MHz */
#define GPIO_Speed_50MHz GPIO_Speed_Level_3   /*!< I/O output speed: High 50 MHz */
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
/* Exported functions ------------------------------------------------------- */
/* Function used to set the GPIO configuration to the default reset state *****/
void GPIO_DeInit(GPIO_TypeDef* GPIOx);

/* Initialization and Configuration functions *********************************/
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/* GPIO Read and Write functions **********************************************/
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);
void GPIO_Toggle(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/* GPIO Alternate functions configuration functions ***************************/
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF);

#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_GPIO_H */

/***************************** (C) COPYRIGHT HKMicroChip  *******************************/

