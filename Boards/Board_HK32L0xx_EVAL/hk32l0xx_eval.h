/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_eval.h
* @brief:     This file contains definitions for HK32FL0XX_EVAL's Leds, push-buttons
*             and COM ports hardware resources.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_EVAL_H
#define __HK32L0XX_EVAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"

/** @addtogroup Boards
  * @{
  */

/** @addtogroup HK32_EVAL
  * @{
  */

/** @addtogroup HK32FL0XX_EVAL
  * @{
  */

/** @addtogroup HK32FL0XX_EVAL_LOW_LEVEL
  * @{
  */

/* Exported types ------------------------------------------------------------*/
typedef enum
{
    LED1 = 0,
    LED2 = 1,
} Led_TypeDef;

typedef enum
{
    BUTTON_KEY1 = 0,
    BUTTON_KEY2 = 1,
} Button_TypeDef;

typedef enum
{
    BUTTON_MODE_GPIO = 0,
    BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

typedef enum
{
    JOY_NONE = 0,
    JOY_SEL = 1,
    JOY_DOWN = 2,
    JOY_LEFT = 3,
    JOY_RIGHT = 4,
    JOY_UP = 5
} JOYState_TypeDef
;

typedef enum
{
    COM1 = 0,
} COM_TypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** @defgroup HK32FL0XX_EVAL_LOW_LEVEL_Exported_Constants
  * @{
  */

/**
  * @brief  Define for HK32FL0XX_EVAL board
  */
#if !defined (USE_HK32FL0XX_EVAL)
#define USE_HK32FL0XX_EVAL
#endif




/** @addtogroup HK32FL0XX_EVAL_LOW_LEVEL_LED
  * @{
  */
#define LEDn                             2

#define LED1_PIN                         GPIO_Pin_4
#define LED1_GPIO_PORT                   GPIOF
#define LED1_GPIO_CLK                    RCC_AHBPeriph_GPIOF

#define LED2_PIN                         GPIO_Pin_5
#define LED2_GPIO_PORT                   GPIOF
#define LED2_GPIO_CLK                    RCC_AHBPeriph_GPIOF


/**
  * @}
  */

/** @addtogroup HK32FL0XX_EVAL_LOW_LEVEL_BUTTON
  * @{
  */
#define BUTTONn                          2

/**
 * @brief KEY1 push-button
 */
#define KEY1_BUTTON_PIN                  GPIO_Pin_2
#define KEY1_BUTTON_GPIO_PORT            GPIOB
#define KEY1_BUTTON_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define KEY1_BUTTON_EXTI_LINE            EXTI_Line2
#define KEY1_BUTTON_EXTI_PORT_SOURCE     EXTI_PortSourceGPIOB
#define KEY1_BUTTON_EXTI_PIN_SOURCE      EXTI_PinSource2
#define KEY1_BUTTON_EXTI_IRQn            EXTI2_3_IRQn

/**
 * @brief KEY2 push-button
 */
#define KEY2_BUTTON_PIN                    GPIO_Pin_13
#define KEY2_BUTTON_GPIO_PORT              GPIOC
#define KEY2_BUTTON_GPIO_CLK               RCC_AHBPeriph_GPIOC
#define KEY2_BUTTON_EXTI_LINE              EXTI_Line13
#define KEY2_BUTTON_EXTI_PORT_SOURCE       EXTI_PortSourceGPIOC
#define KEY2_BUTTON_EXTI_PIN_SOURCE        EXTI_PinSource13
#define KEY2_BUTTON_EXTI_IRQn              EXTI4_15_IRQn
/**
  * @}
  */


/** @addtogroup HK32FL0XX_EVAL_LOW_LEVEL_COM
  * @{
  */
#define COMn                             1

/**
 * @brief Definition for COM port1, connected to UART3
 */
#define EVAL_COM1                        UART3
#define EVAL_COM1_CLK                    RCC_APB1Periph_UART3

#define EVAL_COM1_TX_PIN                 GPIO_Pin_4
#define EVAL_COM1_TX_GPIO_PORT           GPIOA
#define EVAL_COM1_TX_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define EVAL_COM1_TX_SOURCE              GPIO_PinSource4
#define EVAL_COM1_TX_AF                  GPIO_AF_5

#define EVAL_COM1_RX_PIN                 GPIO_Pin_5
#define EVAL_COM1_RX_GPIO_PORT           GPIOA
#define EVAL_COM1_RX_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define EVAL_COM1_RX_SOURCE              GPIO_PinSource5
#define EVAL_COM1_RX_AF                  GPIO_AF_5

#define EVAL_COM1_IRQn                   UART3_4_IRQn

/**
  * @}
  */

/** @addtogroup HK32FL0XX_EVAL_LOW_LEVEL_W25Q_FLASH_SPI
  * @{
  */
/**
  * @brief  W25Q FLASH SPI Interface pins
  */
#define sFLASH_SPI                       SPI1
#define sFLASH_SPI_CLK                   RCC_APB2Periph_SPI1

#define sFLASH_SPI_SCK_PIN               GPIO_Pin_5                 /* PA.05 */
#define sFLASH_SPI_SCK_GPIO_PORT         GPIOA                       /* GPIOA */
#define sFLASH_SPI_SCK_GPIO_CLK          RCC_AHBPeriph_GPIOA
#define sFLASH_SPI_SCK_AF                GPIO_AF_0
#define sFLASH_SPI_SCK_SOURCE            GPIO_PinSource5

#define sFLASH_SPI_MISO_PIN              GPIO_Pin_6                 /* PA.06 */
#define sFLASH_SPI_MISO_GPIO_PORT        GPIOA                       /* GPIOA */
#define sFLASH_SPI_MISO_GPIO_CLK         RCC_AHBPeriph_GPIOA
#define sFLASH_SPI_MISO_AF               GPIO_AF_0
#define sFLASH_SPI_MISO_SOURCE           GPIO_PinSource6

#define sFLASH_SPI_MOSI_PIN              GPIO_Pin_7                 /* PA.07 */
#define sFLASH_SPI_MOSI_GPIO_PORT        GPIOA                       /* GPIOB */
#define sFLASH_SPI_MOSI_GPIO_CLK         RCC_AHBPeriph_GPIOA
#define sFLASH_SPI_MOSI_AF               GPIO_AF_0
#define sFLASH_SPI_MOSI_SOURCE           GPIO_PinSource7

#define sFLASH_CS_PIN                    GPIO_Pin_4                 /* PA.04 */
#define sFLASH_CS_GPIO_PORT              GPIOA                       /* GPIOA */
#define sFLASH_CS_GPIO_CLK               RCC_AHBPeriph_GPIOA
#define sFLASH_CS_AF                     GPIO_AF_0
#define sFLASH_CS_SOURCE                 GPIO_PinSource4

/**
  * @}
  */


/** @addtogroup HK32FL0XX_EVAL_LOW_LEVEL_I2C_EE
  * @{
  */
/**
  * @brief  I2C EEPROM Interface pins
  */
#define sEE_I2C                          I2C1
#define sEE_I2C_CLK                      RCC_APB1Periph_I2C1

#define sEE_I2C_SCL_PIN                  GPIO_Pin_6                  /* PB.06 */
#define sEE_I2C_SCL_GPIO_PORT            GPIOB                       /* GPIOB */
#define sEE_I2C_SCL_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define sEE_I2C_SCL_SOURCE               GPIO_PinSource6
#define sEE_I2C_SCL_AF                   GPIO_AF_1

#define sEE_I2C_SDA_PIN                  GPIO_Pin_7                  /* PB.07 */
#define sEE_I2C_SDA_GPIO_PORT            GPIOB                       /* GPIOB */
#define sEE_I2C_SDA_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define sEE_I2C_SDA_SOURCE               GPIO_PinSource7
#define sEE_I2C_SDA_AF                   GPIO_AF_1

/**
  * @}
  */
/** @addtogroup HK32FL0XX_EVAL_LOW_LEVEL_SD_SPI
  * @{
  */
/**
  * @brief  SD SPI Interface pins
  */
#define SD_SPI                           SPI1
#define SD_SPI_CLK                       RCC_APB2Periph_SPI1

#define SD_SPI_SCK_PIN                   GPIO_Pin_5                 /* PA.05 */
#define SD_SPI_SCK_GPIO_PORT             GPIOA                       /* GPIOA */
#define SD_SPI_SCK_GPIO_CLK              RCC_AHBPeriph_GPIOA
#define SD_SPI_SCK_SOURCE                GPIO_PinSource5
#define SD_SPI_SCK_AF                    GPIO_AF_0

#define SD_SPI_MISO_PIN                 GPIO_Pin_6                 /* PA.6 */
#define SD_SPI_MISO_GPIO_PORT           GPIOA                       /* GPIOA*/
#define SD_SPI_MISO_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define SD_SPI_MISO_SOURCE              GPIO_PinSource6
#define SD_SPI_MISO_AF                  GPIO_AF_0

#define SD_SPI_MOSI_PIN                  GPIO_Pin_7                  /* PA.7 */
#define SD_SPI_MOSI_GPIO_PORT            GPIOA                       /* GPIOA*/
#define SD_SPI_MOSI_GPIO_CLK             RCC_AHBPeriph_GPIOA
#define SD_SPI_MOSI_SOURCE               GPIO_PinSource7
#define SD_SPI_MOSI_AF                   GPIO_AF_0

#define SD_CS_PIN                        GPIO_Pin_4                  /* PA.4 */
#define SD_CS_GPIO_PORT                  GPIOA                       /* GPIOA */
#define SD_CS_GPIO_CLK                   RCC_AHBPeriph_GPIOA

#define SD_DETECT_PIN                    GPIO_Pin_15                 /* PA.15 */
#define SD_DETECT_EXTI_LINE              EXTI_Line15
#define SD_DETECT_EXTI_PIN_SOURCE        EXTI_PinSource15
#define SD_DETECT_GPIO_PORT              GPIOB                       /* GPIOB */
#define SD_DETECT_GPIO_CLK               RCC_AHBPeriph_GPIOB
#define SD_DETECT_EXTI_PORT_SOURCE       EXTI_PortSourceGPIOB
#define SD_DETECT_EXTI_IRQn              EXTI4_15_IRQn

/* Exported functions ------------------------------------------------------- */
/** @defgroup HK32FL0XX_EVAL_LOW_LEVEL_Exported_Functions
  * @{
  */
void HK_EVAL_LEDInit(Led_TypeDef Led);
void HK_EVAL_LEDOn(Led_TypeDef Led);
void HK_EVAL_LEDOff(Led_TypeDef Led);
void HK_EVAL_LEDToggle(Led_TypeDef Led);
void HK_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t HK_EVAL_PBGetState(Button_TypeDef Button);
void HK_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);
void sFLASH_LowLevel_DeInit(void);
void sFLASH_LowLevel_Init(void);
void sEE_LowLevel_DeInit(void);
void sEE_LowLevel_Init(void);
void SD_LowLevel_DeInit(void);
void SD_LowLevel_Init(void);
uint8_t HK_SPI_WriteRead(uint8_t Data);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_EVAL_H */
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

