/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_rcc.h
* @brief:     RCC initialization and configuration
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_RCC_H
#define __HK32L0XX_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"

/** @addtogroup RCC RCC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RCC_Exported_Types RCC_Exported_Types
  * @{
  */
/**
  * @brief  RCC Init structure definition
  */
typedef struct
{
    uint32_t SYSCLK_Frequency;            /*!< returns SYSCLK clock frequency expressed in Hz */
    uint32_t HCLK_Frequency;              /*!< returns HCLK clock frequency expressed in Hz */
    uint32_t PCLK_Frequency;              /*!< returns PCLK clock frequency expressed in Hz */
    uint32_t I2C1CLK_Frequency;           /*!< returns I2C1 clock frequency expressed in Hz */
    uint32_t I2C2CLK_Frequency;           /*!< returns I2C2 clock frequency expressed in Hz */
    uint32_t USART1CLK_Frequency;         /*!< returns USART1 clock frequency expressed in Hz */
    uint32_t USART2CLK_Frequency;         /*!< returns USART2 clock frequency expressed in Hz */
    uint32_t UART3CLK_Frequency;          /*!< returns UART3 clock frequency expressed in Hz */
    uint32_t UART4CLK_Frequency;          /*!< returns UART4 clock frequency expressed in Hz */
    uint32_t LPUART1CLK_Frequency;        /*!< returns LPUART1 clock frequency expressed in Hz */
    uint32_t BEEPERCLK_Frequency;         /*!< returns BEEPER clock frequency expressed in Hz */
    uint32_t USBCLK_Frequency;            /*!< returns USB clock frequency expressed in Hz */
    uint32_t RTCCLK_Frequency;            /*!< returns RTC clock frequency expressed in Hz */
    uint32_t LCDPUMPDRV_Capability;       /*!< returns LCD PUMP driver capability */
} RCC_ClocksTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_Exported_Constants RCC_Exported_Constants
  * @{
  */

/** @defgroup RCC_HSE_configuration RCC_HSE_configuration
  * @{
  */
#define RCC_HSE_OFF                      ((uint8_t)0x00)
#define RCC_HSE_ON                       ((uint8_t)0x01)
#define RCC_HSE_Bypass                   ((uint8_t)0x05)
#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || ((HSE) == RCC_HSE_Bypass))
/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Source RCC_PLL_Clock_Source
  * @{
  */
#define RCC_PLLSource_HSI_Div2           ((uint8_t)0x00)
#define RCC_PLLSource_HSE                ((uint8_t)0x10)
#define RCC_PLLSource_HSI                ((uint8_t)0x11)
#define RCC_PLLSource_MSI                ((uint8_t)0x12)
#define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == RCC_PLLSource_HSI_Div2) ||\
                                   ((SOURCE) == RCC_PLLSource_HSI)      ||\
                                   ((SOURCE) == RCC_PLLSource_MSI)      ||\
                                   ((SOURCE) == RCC_PLLSource_HSE))
/**
  * @}
  */

/** @defgroup RCC_PLL_Multiplication_Factor RCC_PLL_Multiplication_Factor
  * @{
  */
#define RCC_PLLMul_2                     ((uint32_t)0x00 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_3                     ((uint32_t)0x01 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_4                     ((uint32_t)0x02 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_5                     ((uint32_t)0x03 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_6                     ((uint32_t)0x04 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_7                     ((uint32_t)0x05 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_8                     ((uint32_t)0x06 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_9                     ((uint32_t)0x07 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_10                    ((uint32_t)0x08 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_11                    ((uint32_t)0x09 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_12                    ((uint32_t)0x10 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_13                    ((uint32_t)0x11 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_14                    ((uint32_t)0x12 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_15                    ((uint32_t)0x13 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_16                    ((uint32_t)0x14 << RCC_CFGR_PLLMUL_Pos)
#define IS_RCC_PLL_MUL(MUL) (((MUL) == RCC_PLLMul_2)  || ((MUL) == RCC_PLLMul_3)  ||\
                             ((MUL) == RCC_PLLMul_4)  || ((MUL) == RCC_PLLMul_5)  ||\
                             ((MUL) == RCC_PLLMul_6)  || ((MUL) == RCC_PLLMul_7)  ||\
                             ((MUL) == RCC_PLLMul_8)  || ((MUL) == RCC_PLLMul_9)  ||\
                             ((MUL) == RCC_PLLMul_10) || ((MUL) == RCC_PLLMul_11) ||\
                             ((MUL) == RCC_PLLMul_12) || ((MUL) == RCC_PLLMul_13) ||\
                             ((MUL) == RCC_PLLMul_14) || ((MUL) == RCC_PLLMul_15) ||\
                             ((MUL) == RCC_PLLMul_16))
/**
  * @}
  */

/** @defgroup RCC_PREDIV_division_factor RCC_PREDIV_division_factor
  * @{
  */
#define  RCC_PREDIV_Div1                 ((uint32_t)0x00 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV_Div2                 ((uint32_t)0x01 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV_Div3                 ((uint32_t)0x02 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV_Div4                 ((uint32_t)0x03 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV_Div5                 ((uint32_t)0x04 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV_Div6                 ((uint32_t)0x05 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV_Div7                 ((uint32_t)0x06 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV_Div8                 ((uint32_t)0x07 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV_Div9                 ((uint32_t)0x08 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV_Div10                ((uint32_t)0x09 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV_Div11                ((uint32_t)0x10 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV_Div12                ((uint32_t)0x11 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV_Div13                ((uint32_t)0x12 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV_Div14                ((uint32_t)0x13 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV_Div15                ((uint32_t)0x14 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV_Div16                ((uint32_t)0x15 << RCC_CFGR2_PREDIV_Pos)
#define IS_RCC_PREDIV(PREDIV)   (((PREDIV) == RCC_PREDIV_Div1)  || ((PREDIV) == RCC_PREDIV_Div2)  ||\
                                 ((PREDIV) == RCC_PREDIV_Div3)  || ((PREDIV) == RCC_PREDIV_Div4)  ||\
                                 ((PREDIV) == RCC_PREDIV_Div5)  || ((PREDIV) == RCC_PREDIV_Div6)  ||\
                                 ((PREDIV) == RCC_PREDIV_Div7)  || ((PREDIV) == RCC_PREDIV_Div8)  ||\
                                 ((PREDIV) == RCC_PREDIV_Div9)  || ((PREDIV) == RCC_PREDIV_Div10) ||\
                                 ((PREDIV) == RCC_PREDIV_Div11) || ((PREDIV) == RCC_PREDIV_Div12) ||\
                                 ((PREDIV) == RCC_PREDIV_Div13) || ((PREDIV) == RCC_PREDIV_Div14) ||\
                                 ((PREDIV) == RCC_PREDIV_Div15) || ((PREDIV) == RCC_PREDIV_Div16))
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source RCC_System_Clock_Source
  * @{
  */
#define RCC_SYSCLKSource_HSI             ((uint8_t)0x00)
#define RCC_SYSCLKSource_HSE             ((uint8_t)0x01)
#define RCC_SYSCLKSource_PLLCLK          ((uint8_t)0x02)
#define RCC_SYSCLKSource_LSE             ((uint8_t)0x10)
#define RCC_SYSCLKSource_LSI             ((uint8_t)0x11)
#define RCC_SYSCLKSource_HSI48           ((uint8_t)0x12)
#define RCC_SYSCLKSource_HSI16           ((uint8_t)0x13)
#define RCC_SYSCLKSource_GPIO            ((uint8_t)0x14)
#define RCC_SYSCLKSource_MSI             ((uint8_t)0x15)
#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI)    ||\
                                      ((SOURCE) == RCC_SYSCLKSource_HSE)    ||\
                                      ((SOURCE) == RCC_SYSCLKSource_PLLCLK) ||\
                                      ((SOURCE) == RCC_SYSCLKSource_LSE)    ||\
                                      ((SOURCE) == RCC_SYSCLKSource_LSI)    ||\
                                      ((SOURCE) == RCC_SYSCLKSource_HSI48)  ||\
                                      ((SOURCE) == RCC_SYSCLKSource_HSI16)  ||\
                                      ((SOURCE) == RCC_SYSCLKSource_GPIO)   ||\
                                      ((SOURCE) == RCC_SYSCLKSource_MSI))
/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Source RCC_AHB_Clock_Source
  * @{
  */
#define RCC_SYSCLK_Div1                  ((uint32_t)0x00 << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div2                  ((uint32_t)0x08 << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div4                  ((uint32_t)0x09 << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div8                  ((uint32_t)0x0A << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div16                 ((uint32_t)0x0B << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div64                 ((uint32_t)0x0C << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div128                ((uint32_t)0x0D << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div256                ((uint32_t)0x0E << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div512                ((uint32_t)0x0F << RCC_CFGR_HPRE_Pos)
#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_SYSCLK_Div1)   || ((HCLK) == RCC_SYSCLK_Div2)   ||\
                           ((HCLK) == RCC_SYSCLK_Div4)   || ((HCLK) == RCC_SYSCLK_Div8)   ||\
                           ((HCLK) == RCC_SYSCLK_Div16)  || ((HCLK) == RCC_SYSCLK_Div64)  ||\
                           ((HCLK) == RCC_SYSCLK_Div128) || ((HCLK) == RCC_SYSCLK_Div256) ||\
                           ((HCLK) == RCC_SYSCLK_Div512))
/**
  * @}
  */

/** @defgroup RCC_APB_Clock_Source RCC_APB_Clock_Source
  * @{
  */
#define RCC_HCLK_Div1                    ((uint32_t)0x00)
#define RCC_HCLK_Div2                    ((uint32_t)0x04)
#define RCC_HCLK_Div4                    ((uint32_t)0x05)
#define RCC_HCLK_Div8                    ((uint32_t)0x06)
#define RCC_HCLK_Div16                   ((uint32_t)0x07)
#define IS_RCC_PCLK(PCLK) (((PCLK) == RCC_HCLK_Div1) || ((PCLK) == RCC_HCLK_Div2) ||\
                           ((PCLK) == RCC_HCLK_Div4) || ((PCLK) == RCC_HCLK_Div8) ||\
                           ((PCLK) == RCC_HCLK_Div16))
/**
  * @}
  */

/** @defgroup RCC_UART_USART_LPUART_clock_source RCC_UART_USART_LPUART_clock_source
  * @{
  */
#define RCC_SELECTIONCLK_PCLK            ((uint32_t)0x00)
#define RCC_SELECTIONCLK_MSI             ((uint32_t)0x01)
#define RCC_SELECTIONCLK_LSE             ((uint32_t)0x02)
#define RCC_SELECTIONCLK_LSI             ((uint32_t)0x03)
#define RCC_SELECTIONCLK_HSI16           ((uint32_t)0x04)
#define IS_RCC_SELECTIONCLK(CLK) (((CLK) == RCC_SELECTIONCLK_PCLK) || ((CLK) == RCC_SELECTIONCLK_MSI) ||\
                                  ((CLK) == RCC_SELECTIONCLK_LSE)  || ((CLK) == RCC_SELECTIONCLK_LSI) ||\
                                  ((CLK) == RCC_SELECTIONCLK_HSI16))
/**
  * @}
  */

/** @defgroup RCC_USB_clock_source RCC_USB_clock_source
  * @{
  */
#define RCC_USBCLK_PLL                   ((uint32_t)0x00 << RCC_CFGR3_USBSEL_Pos)
#define RCC_USBCLK_HSI48                 ((uint32_t)0x01 << RCC_CFGR3_USBSEL_Pos)
#define IS_RCC_USBCLK(USBCLK) (((USBCLK) == RCC_USBCLK_PLL) || ((USBCLK) == RCC_USBCLK_HSI48))
/**
  * @}
  */

/** @defgroup RCC_I2C1_clock_source RCC_I2C1_clock_source
  * @{
  */
#define RCC_I2C1CLK_HSI8M                ((uint32_t)0x00 << RCC_CFGR4_I2C1CLK_SW_Pos)
#define RCC_I2C1CLK_MSI                  ((uint32_t)0x01 << RCC_CFGR4_I2C1CLK_SW_Pos)
#define RCC_I2C1CLK_SYSCLK               ((uint32_t)0x02 << RCC_CFGR4_I2C1CLK_SW_Pos)
#define RCC_I2C1CLK_PCLK1                ((uint32_t)0x03 << RCC_CFGR4_I2C1CLK_SW_Pos)
#define IS_RCC_I2C1CLK(I2CCLK) (((I2CCLK) == RCC_I2C1CLK_HSI8M) ||\
                                ((I2CCLK) == RCC_I2C1CLK_MSI)   ||\
                                ((I2CCLK) == RCC_I2C1CLK_SYSCLK)||\
                                ((I2CCLK) == RCC_I2C1CLK_PCLK1))
/**
  * @}
  */

/** @defgroup RCC_I2C2_clock_source RCC_I2C2_clock_source
  * @{
  */
#define RCC_I2C2CLK_HSI8M                ((uint32_t)0x00 << RCC_CFGR4_I2C2CLK_SW_Pos)
#define RCC_I2C2CLK_MSI                  ((uint32_t)0x01 << RCC_CFGR4_I2C2CLK_SW_Pos)
#define RCC_I2C2CLK_SYSCLK               ((uint32_t)0x02 << RCC_CFGR4_I2C2CLK_SW_Pos)
#define RCC_I2C2CLK_PCLK1                ((uint32_t)0x03 << RCC_CFGR4_I2C2CLK_SW_Pos)
#define IS_RCC_I2C2CLK(I2CCLK) (((I2CCLK) == RCC_I2C2CLK_HSI8M) ||\
                                ((I2CCLK) == RCC_I2C2CLK_MSI)   ||\
                                ((I2CCLK) == RCC_I2C2CLK_SYSCLK)||\
                                ((I2CCLK) == RCC_I2C2CLK_PCLK1))
/**
  * @}
  */

/** @defgroup RCC_BEEPER_clock_source RCC_BEEPER_clock_source
  * @{
  */
#define RCC_BEEPERCLK_PCLK2               ((uint32_t)0x00 << RCC_CFGR4_BEEPER_SW_Pos)
#define RCC_BEEPERCLK_LSI                 ((uint32_t)0x01 << RCC_CFGR4_BEEPER_SW_Pos)
#define RCC_BEEPERCLK_HSE                 ((uint32_t)0x02 << RCC_CFGR4_BEEPER_SW_Pos)
#define IS_RCC_BEEPERCLK(BEEPERCLK) (((BEEPERCLK) == RCC_BEEPERCLK_PCLK2) ||\
                                     ((BEEPERCLK) == RCC_BEEPERCLK_LSI)   ||\
                                     ((BEEPERCLK) == RCC_BEEPERCLK_HSE))
/**
  * @}
  */

/** @defgroup RCC_EXTCLK_GPIO_source RCC_EXTCLK_GPIO_source
  * @{
  */
#define RCC_EXTCLK_GPIO_PA4              ((uint32_t)0x00 << RCC_CFGR4_EXTCLK_SEL_Pos)
#define RCC_EXTCLK_GPIO_PA13             ((uint32_t)0x01 << RCC_CFGR4_EXTCLK_SEL_Pos)
#define RCC_EXTCLK_GPIO_PA14             ((uint32_t)0x02 << RCC_CFGR4_EXTCLK_SEL_Pos)
#define IS_RCC_EXTCLK_GPIO(GPIOCLK) (((GPIOCLK) == RCC_EXTCLK_GPIO_PA4) || \
                                     ((GPIOCLK) == RCC_EXTCLK_GPIO_PA13)|| \
                                     ((GPIOCLK) == RCC_EXTCLK_GPIO_PA14))
/**
  * @}
  */

/** @defgroup RCC_FLITF_clock_source RCC_FLITF_clock_source
  * @{
  */
#define RCC_FLITFCLK_HSI8M              ((uint32_t)0x00 << RCC_CFGR4_FLITFCLK_SEL_Pos)
#define RCC_FLITFCLK_SYSCLK             ((uint32_t)0x01 << RCC_CFGR4_FLITFCLK_SEL_Pos)
#define RCC_FLITFCLK_EXTCLK             ((uint32_t)0x02 << RCC_CFGR4_FLITFCLK_SEL_Pos)
#define IS_RCC_FLITFCLK(FLITFCLK) (((FLITFCLK) == RCC_FLITFCLK_HSI8M) || \
                                   ((FLITFCLK) == RCC_FLITFCLK_SYSCLK)|| \
                                   ((FLITFCLK) == RCC_FLITFCLK_EXTCLK))
/**
  * @}
  */

/** @defgroup RCC_FLITFPrescaler RCC_FLITFPrescaler
  * @{
  */
#define RCC_FLITFPrescaler_1            ((uint32_t)0x00) << RCC_CFGR4_FLITFCLK_PRE_Pos
#define RCC_FLITFPrescaler_2            ((uint32_t)0x01) << RCC_CFGR4_FLITFCLK_PRE_Pos
#define RCC_FLITFPrescaler_4            ((uint32_t)0x02) << RCC_CFGR4_FLITFCLK_PRE_Pos
#define RCC_FLITFPrescaler_6            ((uint32_t)0x03) << RCC_CFGR4_FLITFCLK_PRE_Pos
#define IS_RCC_FLITF_PRESCALER(PRESCALER) (((PRESCALER) == RCC_FLITFPrescaler_1)  || \
                                           ((PRESCALER) == RCC_FLITFPrescaler_2)  || \
                                           ((PRESCALER) == RCC_FLITFPrescaler_4)  || \
                                           ((PRESCALER) == RCC_FLITFPrescaler_6))
/**
  * @}
  */

/** @defgroup RCC_Interrupt_Source RCC_Interrupt_Source
  * @{
  */
#define RCC_IT_LSIRDY                    ((uint32_t)0x01)
#define RCC_IT_LSERDY                    ((uint32_t)0x02)
#define RCC_IT_HSIRDY                    ((uint32_t)0x04)
#define RCC_IT_HSERDY                    ((uint32_t)0x08)
#define RCC_IT_PLLRDY                    ((uint32_t)0x10)
#define RCC_IT_HSI16RDY                  ((uint32_t)0x20)
#define RCC_IT_MSIRDY                    ((uint32_t)0x40)
#define RCC_IT_CSSHSE                    ((uint32_t)0x80)
#define RCC_IT_LSEFAIL                   ((uint32_t)0x80)
#define RCC_IT_CSSLSE                    ((uint32_t)0x40000000)
#define IS_RCC_IT(IT) ((((IT) & (uint8_t)0x80) == 0x00) && ((IT) != 0x00))
#define IS_RCC_GET_IT(IT) (((IT) == RCC_IT_LSIRDY) || ((IT) == RCC_IT_LSERDY)   || \
                           ((IT) == RCC_IT_HSIRDY) || ((IT) == RCC_IT_HSERDY)   || \
                           ((IT) == RCC_IT_PLLRDY) || ((IT) == RCC_IT_HSI16RDY) || \
                           ((IT) == RCC_IT_CSSHSE) || ((IT) == RCC_IT_CSSLSE)   || \
                           ((IT) == RCC_IT_MSIRDY) )
#define IS_RCC_CLEAR_IT(IT) (((IT) == RCC_IT_LSIRDY) || ((IT) == RCC_IT_LSERDY)   || \
                             ((IT) == RCC_IT_HSIRDY) || ((IT) == RCC_IT_HSERDY)   || \
                             ((IT) == RCC_IT_PLLRDY) || ((IT) == RCC_IT_HSI16RDY) || \
                             ((IT) == RCC_IT_CSSHSE) || ((IT) == RCC_IT_CSSLSE)   || \
                             ((IT) == RCC_IT_MSIRDY) )
/**
  * @}
  */

/** @defgroup RCC_LSE_Configuration RCC_LSE_Configuration
  * @{
  */
#define RCC_LSE_OFF                      ((uint32_t)0x00000000)
#define RCC_LSE_ON                       RCC_BDCR_LSEON
#define RCC_LSE_Bypass                   ((uint32_t)(RCC_BDCR_LSEON | RCC_BDCR_LSEBYP))
#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_Bypass))
/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Source RCC_RTC_Clock_Source
  * @{
  */
#define RCC_RTCCLKSource_LSE             ((uint32_t)0x01 << RCC_BDCR_RTC_SEL_Pos)
#define RCC_RTCCLKSource_LSI             ((uint32_t)0x02 << RCC_BDCR_RTC_SEL_Pos)
#define RCC_RTCCLKSource_HSE_Div32       ((uint32_t)0x03 << RCC_BDCR_RTC_SEL_Pos)
#define RCC_RTCCLKSource_MSI             ((uint32_t)0x04 << RCC_BDCR_RTC_SEL_Pos)
#define IS_RCC_RTCCLK_SOURCE(SOURCE) (((SOURCE) == RCC_RTCCLKSource_MSI) || \
                                      ((SOURCE) == RCC_RTCCLKSource_LSE) || \
                                      ((SOURCE) == RCC_RTCCLKSource_LSI) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div32))
/**
  * @}
  */

/** @defgroup RCC_LCDPUMP_DRV RCC_LCDPUMP_DRV
  * @{
  */
#define RCC_LCDPUMP_DRV_LEVEL0            ((uint32_t)0x00)
#define RCC_LCDPUMP_DRV_LEVEL1            ((uint32_t)0x01)
#define RCC_LCDPUMP_DRV_LEVEL2            ((uint32_t)0x02)
#define RCC_LCDPUMP_DRV_LEVEL3            ((uint32_t)0x03)
#define RCC_LCDPUMP_DRV_LEVEL4            ((uint32_t)0x04)
#define RCC_LCDPUMP_DRV_LEVEL5            ((uint32_t)0x05)
#define RCC_LCDPUMP_DRV_LEVEL6            ((uint32_t)0x06)
#define RCC_LCDPUMP_DRV_LEVEL7            ((uint32_t)0x07)
#define IS_RCC_LCDPUMPDRV_SOURCE(SOURCE) (((SOURCE) == RCC_LCDPUMP_DRV_LEVEL0)   || \
                                          ((SOURCE) == RCC_LCDPUMP_DRV_LEVEL1)   || \
                                          ((SOURCE) == RCC_LCDPUMP_DRV_LEVEL2)   || \
                                          ((SOURCE) == RCC_LCDPUMP_DRV_LEVEL3)   || \
                                          ((SOURCE) == RCC_LCDPUMP_DRV_LEVEL4)   || \
                                          ((SOURCE) == RCC_LCDPUMP_DRV_LEVEL5)   || \
                                          ((SOURCE) == RCC_LCDPUMP_DRV_LEVEL6)   || \
                                          ((SOURCE) == RCC_LCDPUMP_DRV_LEVEL7))
/**
  * @}
  */

/** @defgroup RCC_LSE_Drive_Configuration RCC_LSE_Drive_Configuration
  * @{
  */
#define RCC_LSEDrive_Low                 ((uint32_t)0x00000000)
#define RCC_LSEDrive_MediumLow           RCC_BDCR_LSEDRV_0
#define RCC_LSEDrive_MediumHigh          RCC_BDCR_LSEDRV_1
#define RCC_LSEDrive_High                RCC_BDCR_LSEDRV
#define IS_RCC_LSE_DRIVE(DRIVE) (((DRIVE) == RCC_LSEDrive_Low) || ((DRIVE) == RCC_LSEDrive_MediumLow) || \
                                 ((DRIVE) == RCC_LSEDrive_MediumHigh) || ((DRIVE) == RCC_LSEDrive_High))
/**
  * @}
  */

/** @defgroup RCC_AHB_Peripherals RCC_AHB_Peripherals
  * @{
  */
#define RCC_AHBPeriph_TRNG                RCC_AHBENR_TRNGEN
#define RCC_AHBPeriph_CRYPT               RCC_AHBENR_CRYPTEN
#define RCC_AHBPeriph_GPIOA               RCC_AHBENR_IOPAEN
#define RCC_AHBPeriph_GPIOB               RCC_AHBENR_IOPBEN
#define RCC_AHBPeriph_GPIOC               RCC_AHBENR_IOPCEN
#define RCC_AHBPeriph_GPIOD               RCC_AHBENR_IOPDEN
#define RCC_AHBPeriph_GPIOF               RCC_AHBENR_IOPFEN
#define RCC_AHBPeriph_EMACC               RCC_AHBENR_EMACCEN
#define RCC_AHBPeriph_DVSQ                RCC_AHBENR_DVSQEN
#define RCC_AHBPeriph_CRC                 RCC_AHBENR_CRCEN
#define RCC_AHBPeriph_FLITF               RCC_AHBENR_FLITFEN
#define RCC_AHBPeriph_SRAM                RCC_AHBENR_SRAMEN
#define RCC_AHBPeriph_DMA                 RCC_AHBENR_DMAEN
#define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH) & 0xFCA1FCAA) == 0x00) && ((PERIPH) != 0x00))
#define IS_RCC_AHB_RST_PERIPH(PERIPH) ((((PERIPH) & 0xFCA1FCBE) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */

/** @defgroup RCC_APB2_Peripherals RCC_APB2_Peripherals
  * @{
  */
#define RCC_APB2Periph_SYSCFG            RCC_APB2ENR_SYSCFGEN
#define RCC_APB2Periph_ADC               RCC_APB2ENR_ADCEN
#define RCC_APB2Periph_TIM1              RCC_APB2ENR_TIM1EN
#define RCC_APB2Periph_SPI1              RCC_APB2ENR_SPI1EN
#define RCC_APB2Periph_USART1            RCC_APB2ENR_USART1EN
#define RCC_APB2Periph_TIM15             RCC_APB2ENR_TIM15EN
#define RCC_APB2Periph_TIM16             RCC_APB2ENR_TIM16EN
#define RCC_APB2Periph_TIM17             RCC_APB2ENR_TIM17EN
#define RCC_APB2Periph_DBGMCU            RCC_APB2ENR_DBGEN
#define RCC_APB2Periph_BEEPER            RCC_APB2ENR_BEEPEREN
#define RCC_APB2Periph_OPAMP             RCC_APB2ENR_OPAMPEN
#define RCC_APB2Periph_COMP              RCC_APB2ENR_COMPEN
#define IS_RCC_APB2_PERIPH(PERIPH) ((((PERIPH) & 0xE4B8A5FE) == 0x00) && ((PERIPH) != 0x00))
#define IS_RCC_APB2_RST_PERIPH(PERIPH) ((((PERIPH) & 0xE4B8A5FE) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */

/** @defgroup RCC_APB1_Peripherals RCC_APB1_Peripherals
  * @{
  */
#define RCC_APB1Periph_TIM2              RCC_APB1ENR_TIM2EN
#define RCC_APB1Periph_TIM3              RCC_APB1ENR_TIM3EN
#define RCC_APB1Periph_TIM14             RCC_APB1ENR_TIM14EN
#define RCC_APB1Periph_LCD               RCC_APB1ENR_LCDEN
#define RCC_APB1Periph_WWDG              RCC_APB1ENR_WWDGEN
#define RCC_APB1Periph_SPI2              RCC_APB1ENR_SPI2EN
#define RCC_APB1Periph_USART2            RCC_APB1ENR_USART2EN
#define RCC_APB1Periph_UART3             RCC_APB1ENR_UART3EN
#define RCC_APB1Periph_UART4             RCC_APB1ENR_UART4EN
#define RCC_APB1Periph_I2C1              RCC_APB1ENR_I2C1EN
#define RCC_APB1Periph_I2C2              RCC_APB1ENR_I2C2EN
#define RCC_APB1Periph_USB               RCC_APB1ENR_USBEN
#define RCC_APB1Periph_LPUART1           RCC_APB1ENR_LPUART1EN
#define RCC_APB1Periph_CAN               RCC_APB1ENR_CANEN
#define RCC_APB1Periph_PWR               RCC_APB1ENR_PWREN
#define RCC_APB1Periph_DAC               RCC_APB1ENR_DACEN
#define IS_RCC_APB1_PERIPH(PERIPH) ((((PERIPH) & 0x4C11B0FC) == 0x00) && ((PERIPH) != 0x00))
#define IS_RCC_APB1_RST_PERIPH(PERIPH) ((((PERIPH) & 0x4C11B0FC) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */

/**
  * @brief  RCC_MCO_Clock_Source
 */
/** @defgroup RCC_MCO_Clock_Source RCC_MCO_Clock_Source
  * @{
  */
#define RCC_MCOSource_NoClock            ((uint8_t)0x00)
#define RCC_MCOSource_HSI16M             ((uint8_t)0x01)
#define RCC_MCOSource_LSI                ((uint8_t)0x02)
#define RCC_MCOSource_LSE                ((uint8_t)0x03)
#define RCC_MCOSource_SYSCLK             ((uint8_t)0x04)
#define RCC_MCOSource_HSI                ((uint8_t)0x05)
#define RCC_MCOSource_HSE                ((uint8_t)0x06)
#define RCC_MCOSource_PLLCLK             ((uint8_t)0x07)
#define RCC_MCOSource_MSI                ((uint8_t)0x08)
#define IS_RCC_MCO_SOURCE(SOURCE) (((SOURCE) == RCC_MCOSource_NoClock) || ((SOURCE) == RCC_MCOSource_LSE)     || \
                                   ((SOURCE) == RCC_MCOSource_LSI)     || ((SOURCE) == RCC_MCOSource_SYSCLK)  || \
                                   ((SOURCE) == RCC_MCOSource_HSE)     || ((SOURCE) == RCC_MCOSource_MSI)     || \
                                   ((SOURCE) == RCC_MCOSource_HSI)     || ((SOURCE) == RCC_MCOSource_PLLCLK)  || \
                                   ((SOURCE) == RCC_MCOSource_HSI16M))
/**
  * @}
  */

/** @defgroup RCC_Stop_WakeupClock RCC_Stop_WakeupClock
  * @{
  */
#define RCC_STOP_WAKEUPCLOCK_HSI         ((uint32_t)0x00 << RCC_CFGR_STOPWUCK_Pos)
#define RCC_STOP_WAKEUPCLOCK_MSI         ((uint32_t)0x01 << RCC_CFGR_STOPWUCK_Pos)
#define IS_RCC_STOP_WAKEUPCLOCK(CLK) (((CLK) == RCC_STOP_WAKEUPCLOCK_HSI) || ((CLK) == RCC_STOP_WAKEUPCLOCK_MSI))
/**
  * @}
  */

/** @defgroup RCC_MCOPrescaler RCC_MCOPrescaler
  * @{
  */
#define RCC_MCOPrescaler_1               ((uint32_t)0x00 << RCC_CFGR_MCOPRE_Pos)
#define RCC_MCOPrescaler_2               ((uint32_t)0x01 << RCC_CFGR_MCOPRE_Pos)
#define RCC_MCOPrescaler_4               ((uint32_t)0x02 << RCC_CFGR_MCOPRE_Pos)
#define RCC_MCOPrescaler_8               ((uint32_t)0x03 << RCC_CFGR_MCOPRE_Pos)
#define RCC_MCOPrescaler_16              ((uint32_t)0x04 << RCC_CFGR_MCOPRE_Pos)
#define RCC_MCOPrescaler_32              ((uint32_t)0x05 << RCC_CFGR_MCOPRE_Pos)
#define RCC_MCOPrescaler_64              ((uint32_t)0x06 << RCC_CFGR_MCOPRE_Pos)
#define RCC_MCOPrescaler_128             ((uint32_t)0x07 << RCC_CFGR_MCOPRE_Pos)
#define IS_RCC_MCO_PRESCALER(PRESCALER) (((PRESCALER) == RCC_MCOPrescaler_1)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_2)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_4)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_8)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_16) || \
                                         ((PRESCALER) == RCC_MCOPrescaler_32) || \
                                         ((PRESCALER) == RCC_MCOPrescaler_64) || \
                                         ((PRESCALER) == RCC_MCOPrescaler_128))
/**
  * @}
  */

/** @defgroup RCC_Flag RCC_Flag
  * @{
  */
#define RCC_FLAG_HSIRDY                  ((uint8_t)0x01)
#define RCC_FLAG_HSERDY                  ((uint8_t)0x11)
#define RCC_FLAG_PLLRDY                  ((uint8_t)0x19)
#define RCC_FLAG_LSERDY                  ((uint8_t)0x21)
#define RCC_FLAG_LSIRDY                  ((uint8_t)0x41)
#define RCC_FLAG_VCPURSTF                ((uint8_t)0x57)
#define RCC_FLAG_OBLRST                  ((uint8_t)0x59)
#define RCC_FLAG_PINRST                  ((uint8_t)0x5A)
#define RCC_FLAG_PORRST                  ((uint8_t)0x5B)
#define RCC_FLAG_SFTRST                  ((uint8_t)0x5C)
#define RCC_FLAG_IWDGRST                 ((uint8_t)0x5D)
#define RCC_FLAG_WWDGRST                 ((uint8_t)0x5E)
#define RCC_FLAG_LPWRRST                 ((uint8_t)0x5F)
#define RCC_FLAG_HSI16RDY                ((uint8_t)0x61)
#define RCC_FLAG_HSI48RDY                ((uint8_t)0x64)
#define RCC_FLAG_MSIRDY                  ((uint8_t)0x69)
#define IS_RCC_FLAG(FLAG) (((FLAG) == RCC_FLAG_HSIRDY)  || ((FLAG) == RCC_FLAG_HSERDY)   || \
                           ((FLAG) == RCC_FLAG_PLLRDY)  || ((FLAG) == RCC_FLAG_LSERDY)   || \
                           ((FLAG) == RCC_FLAG_LSIRDY)  || ((FLAG) == RCC_FLAG_OBLRST)   || \
                           ((FLAG) == RCC_FLAG_PINRST)  || ((FLAG) == RCC_FLAG_PORRST)   || \
                           ((FLAG) == RCC_FLAG_SFTRST)  || ((FLAG) == RCC_FLAG_IWDGRST)  || \
                           ((FLAG) == RCC_FLAG_WWDGRST) || ((FLAG) == RCC_FLAG_LPWRRST)  || \
                           ((FLAG) == RCC_FLAG_HSI16RDY)|| ((FLAG) == RCC_FLAG_VCPURSTF) || \
                           ((FLAG) == RCC_FLAG_HSI48RDY))
/**
  * @}
  */

/** @defgroup RCC_MSI_clock_range RCC_MSI_clock_range
  * @{
  */
#define RCC_MSICLK_262K                  ((uint32_t)0x02 << RCC_CR2_MSIRANGE_Pos)
#define RCC_MSICLK_524K                  ((uint32_t)0x03 << RCC_CR2_MSIRANGE_Pos)
#define RCC_MSICLK_1_05M                 ((uint32_t)0x04 << RCC_CR2_MSIRANGE_Pos)
#define RCC_MSICLK_2_1M                  ((uint32_t)0x05 << RCC_CR2_MSIRANGE_Pos)
#define RCC_MSICLK_4_2M                  ((uint32_t)0x06 << RCC_CR2_MSIRANGE_Pos)
#define IS_RCC_MSICLK(MSICLK) (((MSICLK) == RCC_MSICLK_262K)  || \
                               ((MSICLK) == RCC_MSICLK_524K)  || \
                               ((MSICLK) == RCC_MSICLK_1_05M) || \
                               ((MSICLK) == RCC_MSICLK_2_1M)  || \
                               ((MSICLK) == RCC_MSICLK_4_2M))
/**
  * @}
  */

/** @defgroup CSS_THRESHOLD_Value CSS_THRESHOLD_Value
  * @{
  */
#define IS_CSS_THRESHOLD_Value(VALUE) ((VALUE) <= 0x7F)
/**
  * @}
  */

/** @defgroup HSI_LSI_TRIM_Value HSI_LSI_TRIM_Value
  * @{
  */
#define IS_RCC_HSI_FINETRIM_VALUE(VALUE)   ((VALUE) <= 0x3F)
#define IS_RCC_HSI_COARSETRIM_VALUE(VALUE) ((VALUE) <= 0x3F)
#define IS_RCC_LSI_COARSETRIM_VALUE(VALUE) ((VALUE) <= 0x3F)
#define IS_RCC_LSI_FINETRIM_VALUE(VALUE)   ((VALUE) <= 0xF)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/** @defgroup RCC_Exported_Functions RCC_Exported_Functions
  * @{
  */
/* Internal-external clocks, PLL, CSS and MCO configuration functions */
void RCC_DeInit(void);
void RCC_HSEConfig(uint8_t RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp(void);
void RCC_HSIFineTRIM(uint8_t HSIFINETRIMValue);
void RCC_HSICOARSETRIM(uint8_t HSICOARSETRIMValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_HSI16Cmd(FunctionalState NewState);
void RCC_HSI16ADCRequestCmd(FunctionalState NewState);
void RCC_HSI48Cmd(FunctionalState NewState);
void RCC_LSIFINETRIM(uint8_t LSIFINETRIMValue);
void RCC_LSICOARSETRIM(uint8_t LSICOARSETRIMValue);
void RCC_LSEConfig(uint32_t RCC_LSE);
void RCC_LSEDriveConfig(uint32_t RCC_LSEDrive);
void RCC_LSICmd(FunctionalState NewState);
void RCC_MSICmd(FunctionalState NewState);
void RCC_MSIConfig(uint32_t RCC_MSICLK);
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul);
void RCC_PLLCmd(FunctionalState NewState);
void RCC_PREDIVConfig(uint32_t RCC_PREDIV_Div);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void RCC_MCOConfig(uint8_t RCC_MCOSource, uint32_t RCC_MCOPrescaler);
uint32_t RCC_GetClkAfterWakeFromStop(void);
void RCC_SetClkAfterWakeFromStop(uint32_t RCC_Stop_WakeupClock);

/* System, AHB and APB busses clocks configuration functions ******************/
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);
void RCC_PCLKConfig(uint32_t RCC_PCLK);
void RCC_LPUART1CLKConfig(uint32_t RCC_LPUART1CLK);
void RCC_UART4CLKConfig(uint32_t RCC_UART4CLK);
void RCC_UART3CLKConfig(uint32_t RCC_UART3CLK);
void RCC_USART2CLKConfig(uint32_t RCC_USART2CLK);
void RCC_USART1CLKConfig(uint32_t RCC_USART1CLK);
void RCC_USBCLKConfig(uint32_t RCC_USBCLK);
void RCC_I2C1CLKConfig(uint32_t RCC_I2C1CLK);
void RCC_I2C2CLKConfig(uint32_t RCC_I2C2CLK);
void RCC_BEEPERCLKConfig(uint32_t RCC_BEEPERCLK);
void RCC_FLITFCLKConfig(uint32_t RCC_FLITFCLK, uint32_t RCC_FLITFCLKPrescaler);
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);
void RCC_ExternalClkConfig(uint32_t RCC_EXTCLK_GPIO);

/* Peripheral clocks configuration functions **********************************/
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_LCDPUMPDRVConfig(uint32_t RCC_LCDPUMPDRV);
void RCC_BackupResetCmd(FunctionalState NewState);
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(uint32_t RCC_IT);
void RCC_ClearITPendingBit(uint32_t RCC_IT);
void RCC_CSSThresholdConfig(uint8_t CSS_THRESHOLD_Value);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_RCC_H */


