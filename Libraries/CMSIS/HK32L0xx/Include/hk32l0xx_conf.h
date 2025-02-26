/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_conf.h
* @brief:     conf program body
* @author:    AE Team
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0xx_CONF_H
#define __HK32L0xx_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/*system clock source*/
#define SYSCLK_SRC_PLL          0x1
#define SYSCLK_SRC_HSI8M        0x2
#define SYSCLK_SRC_HSI16M       0x3
#define SYSCLK_SRC_HSI48M       0x4
#define SYSCLK_SRC_HSE          0x5
#define SYSCLK_SRC_MSI          0x6
#define SYSCLK_SRC_EXTCLK_IO    0x7
#define SYSCLK_SRC_LSI          0x8
#define SYSCLK_SRC_LSE          0x9

/* select sysclk source here */
#define SYSCLK_SOURCE           SYSCLK_SRC_PLL

// #define VECT_TAB_SRAM
#define VECT_TAB_OFFSET  0x0           /*!< Vector Table base offset field. This value must be a multiple of 0x200. */

/* Uncomment the following line if you need to use sysclk freq*/
#if(SYSCLK_SOURCE==SYSCLK_SRC_PLL)
//#define SYSCLK_HSE8M_PLL_FREQ_4MHz           4000000
//#define SYSCLK_HSE8M_PLL_FREQ_8MHz           8000000
//#define SYSCLK_HSE8M_PLL_FREQ_12MHz          12000000
//#define SYSCLK_HSE8M_PLL_FREQ_24MHz          24000000
//#define SYSCLK_HSE8M_PLL_FREQ_32MHz          32000000
//#define SYSCLK_HSE8M_PLL_FREQ_36MHz          36000000
#define SYSCLK_HSE8M_PLL_FREQ_48MHz          48000000

//#define SYSCLK_HSI_PLL_FREQ_36MHz            36000000
//#define SYSCLK_HSI_PLL_FREQ_48MHz              48000000
#elif(SYSCLK_SOURCE == SYSCLK_SRC_HSE )
#define SYSCLK_FREQ_HSE                    HSE_VALUE
#elif(SYSCLK_SOURCE == SYSCLK_SRC_HSI8M)
#define SYSCLK_FREQ_HSI_8M                 8000000
#elif(SYSCLK_SOURCE == SYSCLK_SRC_HSI16M)
#define SYSCLK_FREQ_HSI_16M                16000000
#elif(SYSCLK_SOURCE == SYSCLK_SRC_HSI48M)
#define SYSCLK_FREQ_HSI_48M                48000000
#elif(SYSCLK_SOURCE == SYSCLK_SRC_EXTCLK_IO)
#define SYSCLK_FREQ_EXTCLK                 EXTCLK_GPIOINPUT_VALUE
#elif(SYSCLK_SOURCE == SYSCLK_SRC_LSI)
#define SYSCLK_FREQ_LSI                    LSI_VALUE
#elif(SYSCLK_SOURCE == SYSCLK_SRC_LSE)
#define SYSCLK_FREQ_LSE                    LSE_VALUE
#elif(SYSCLK_SOURCE == SYSCLK_SRC_MSI)
#define SYSCLK_FREQ_MSI                    MSI_VALUE
#endif


#if !defined  (HSE_VALUE)
#define HSE_VALUE                     ((uint32_t)8000000U) /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (LSE_VALUE)
#define LSE_VALUE                     ((uint32_t)32768U) /*!< Value of the External oscillator in Hz */
#endif /* LSE_VALUE */

#if !defined  (MSI_VALUE)
#define MSIRANGE_VALUE_65_5KHz        6500UL
#define MSIRANGE_VALUE_131KHz         131000UL
#define MSIRANGE_VALUE_262KHz         262000UL
#define MSIRANGE_VALUE_524KHz         524000UL
#define MSIRANGE_VALUE_1_05MHz        1050000UL
#define MSIRANGE_VALUE_2_1MHz         2100000UL
#define MSIRANGE_VALUE_4_2MHz         4200000UL

#define MSI_VALUE                     MSIRANGE_VALUE_2_1MHz /*!< Value of the Internal oscillator in Hz*/

#if ((MSI_VALUE != MSIRANGE_VALUE_65_5KHz) && (MSI_VALUE != MSIRANGE_VALUE_131KHz) && (MSI_VALUE != MSIRANGE_VALUE_262KHz) && \
      (MSI_VALUE != MSIRANGE_VALUE_524KHz) && (MSI_VALUE != MSIRANGE_VALUE_1_05MHz) && (MSI_VALUE != MSIRANGE_VALUE_2_1MHz) && \
      (MSI_VALUE != MSIRANGE_VALUE_4_2MHz))
#error "The set value of MSI_VALUE is wrong"
#endif
#endif /* MSI_VALUE */

#if !defined  (HSI_VALUE)
#define HSI_VALUE                     ((uint32_t)8000000U) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

#if !defined  (LSI_VALUE)
#define LSI_VALUE                     ((uint32_t)32768U) /*!< Value of the Internal oscillator in Hz*/
#endif /* LSI_VALUE */

#if !defined  (HSI48_VALUE)
#define HSI48_VALUE                   ((uint32_t)48000000U) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI48_VALUE */

#if !defined  (HSI16_VALUE)
#define HSI16_VALUE                   ((uint32_t)16000000U) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI16_VALUE */

#if !defined  (EXTCLK_GPIOINPUT_VALUE)
#define EXTCLK_GPIOINPUT_VALUE        ((uint32_t)8000000U) /*!< Value of the Internal oscillator in Hz*/
#endif /* EXTCLK_GPIOINPUT_VALUE */

#if !defined  (HSE_STARTUP_TIMEOUT)
#define HSE_STARTUP_TIMEOUT           ((uint16_t)0xFFFF) /*!< Time out for HSE start up */
#endif

#if !defined  (HSI_STARTUP_TIMEOUT)
#define HSI_STARTUP_TIMEOUT           ((uint16_t)0xFFFF) /*!< Time out for HSI start up */
#endif

/* Includes ------------------------------------------------------------------*/
/**
  * @brief Include module's header file
  */

#include "hk32l0xx_rcc.h"

#include "hk32l0xx_crc.h"

#include "hk32l0xx_exti.h"

#include "hk32l0xx_flash.h"

#include "hk32l0xx_gpio.h"

#include "hk32l0xx_misc.h"

#include "hk32l0xx_adc.h"

#include "hk32l0xx_emacc.h"

#include "hk32l0xx_syscfg.h"

#include "hk32l0xx_def.h"

#include "hk32l0xx_i2c.h"

#include "hk32l0xx_iwdg.h"

#include "hk32l0xx_pwr.h"

#include "hk32l0xx_spi.h"

#include "hk32l0xx_tim.h"

#include "hk32l0xx_usart.h"

#include "hk32l0xx_iwdg.h"

#include "hk32l0xx_wwdg.h"

#include "hk32l0xx_beep.h"

#include "hk32l0xx_lpuart.h"

#include "hk32l0xx_lcd.h"

#include "hk32l0xx_rtc.h"

#include "hk32l0xx_dac.h"

#include "hk32l0xx_aes.h"

#include "hk32l0xx_trng.h"

#include "hk32l0xx_clu.h"

#include "hk32l0xx_dma.h"

#include "hk32l0xx_divsqrt.h"

#include "hk32l0xx_comp.h"

#include "hk32l0xx_opamp.h"

#include "hk32l0xx_dbgmcu.h"

#include "hk32l0xx_can.h"

#include "hk32l0xx_eeprom.h"

/* Exported macro ------------------------------------------------------------*/
/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the
  *         drivers code
  */

#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports
  *         the name of the source file and the source line number of the call
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* __HK32L0xx_CONF_H */

/************************ (C) COPYRIGHT MKMcircoChuip *****END OF FILE****/
