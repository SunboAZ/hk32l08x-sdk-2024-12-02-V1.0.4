/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_clu.h
* @brief:     This file contains all the functions prototypes for the CLU firmware
*             library.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_CLU_H
#define __HK32L0XX_CLU_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"

/** @addtogroup CLU
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup CLU_Exported_Constants CLU Exported Constants
  * @{
  */

/** @defgroup CLU_Selection CLU Selection
  * @{
  */
typedef enum
{
    CLU0      = 0x00, /*!< Selecte CLU0 */
    CLU1      = 0x01, /*!< Selecte CLU1 */
    CLU2      = 0x02, /*!< Selecte CLU2 */
    CLU3      = 0x03, /*!< Selecte CLU3 */
} CLUx_Selecte_TypeDef;

#define IS_CLU_ALL_CLUx(CLUx) (((CLUx) == CLU0) || \
                               ((CLUx) == CLU1) || \
                               ((CLUx) == CLU2) || \
                               ((CLUx) == CLU3) )
/**
  * @}
  */

/** @defgroup CLU0_Multiplexer_A_Input_Selection   CLU0_Multiplexer_A Input Selection
  * @{
  */
#define CLU0_MXA_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU0_MXA_CLU1_OUT_INTER               ((uint32_t)0x00000001)
#define CLU0_MXA_CLU2_OUT_INTER               ((uint32_t)0x00000002)
#define CLU0_MXA_CLU3_OUT_INTER               ((uint32_t)0x00000003)
#define CLU0_MXA_TIM1_BRK                     ((uint32_t)0x00000004)
#define CLU0_MXA_TIM1_CC1                     ((uint32_t)0x00000005)
#define CLU0_MXA_TIM1_COM                     ((uint32_t)0x00000006)
#define CLU0_MXA_TIM1_TRIG                    ((uint32_t)0x00000007)
#define CLU0_MXA_TIM1_UP                      ((uint32_t)0x00000008)
#define CLU0_MXA_COMP1_OUT                    ((uint32_t)0x00000009)
#define CLU0_MXA_COMP2_OUT                    ((uint32_t)0x0000000A)
#define CLU0_MXA_COMP3_OUT                    ((uint32_t)0x0000000B)
#define CLU0_MXA_PA0                          ((uint32_t)0x0000000C)
#define CLU0_MXA_PA1                          ((uint32_t)0x0000000D)
#define CLU0_MXA_PA2                          ((uint32_t)0x0000000E)
#define CLU0_MXA_PC10                         ((uint32_t)0x0000000F)

#define IS_CLU0_MXA_INPUT(MXA_INPUT)  (((MXA_INPUT) == CLU0_MXA_CLU0_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU0_MXA_CLU1_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU0_MXA_CLU2_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU0_MXA_CLU3_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU0_MXA_TIM1_BRK      ) || \
                                       ((MXA_INPUT) == CLU0_MXA_TIM1_CC1      ) || \
                                       ((MXA_INPUT) == CLU0_MXA_TIM1_COM      ) || \
                                       ((MXA_INPUT) == CLU0_MXA_TIM1_TRIG     ) || \
                                       ((MXA_INPUT) == CLU0_MXA_TIM1_UP       ) || \
                                       ((MXA_INPUT) == CLU0_MXA_COMP1_OUT     ) || \
                                       ((MXA_INPUT) == CLU0_MXA_COMP2_OUT     ) || \
                                       ((MXA_INPUT) == CLU0_MXA_COMP3_OUT     ) || \
                                       ((MXA_INPUT) == CLU0_MXA_PA0           ) || \
                                       ((MXA_INPUT) == CLU0_MXA_PA1           ) || \
                                       ((MXA_INPUT) == CLU0_MXA_PA2           ) || \
                                       ((MXA_INPUT) == CLU0_MXA_PC10          ))

/**
  * @}
  */

/** @defgroup CLU0_Multiplexer_B_Input_Selection   CLU0_Multiplexer_B Input Selection
  * @{
  */
#define CLU0_MXB_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU0_MXB_CLU1_OUT_INTER               ((uint32_t)0x00000010)
#define CLU0_MXB_CLU2_OUT_INTER               ((uint32_t)0x00000020)
#define CLU0_MXB_CLU3_OUT_INTER               ((uint32_t)0x00000030)
#define CLU0_MXB_ADC1_EOC                     ((uint32_t)0x00000040)
#define CLU0_MXB_ADC1_AWD                     ((uint32_t)0x00000050)
#define CLU0_MXB_ADC1_EOSEQ                   ((uint32_t)0x00000060)
#define CLU0_MXB_TIM6_UP                      ((uint32_t)0x00000070)
#define CLU0_MXB_TIM14_CC1                    ((uint32_t)0x00000080)
#define CLU0_MXB_COMP1_OUT                    ((uint32_t)0x00000090)
#define CLU0_MXB_COMP2_OUT                    ((uint32_t)0x000000A0)
#define CLU0_MXB_COMP3_OUT                    ((uint32_t)0x000000B0)
#define CLU0_MXB_PA3                          ((uint32_t)0x000000C0)
#define CLU0_MXB_PA4                          ((uint32_t)0x000000D0)
#define CLU0_MXB_PA5                          ((uint32_t)0x000000E0)
#define CLU0_MXB_PB1                          ((uint32_t)0x000000F0)

#define IS_CLU0_MXB_INPUT(MXB_INPUT)  (((MXB_INPUT) == CLU0_MXB_CLU0_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU0_MXB_CLU1_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU0_MXB_CLU2_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU0_MXB_CLU3_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU0_MXB_ADC1_EOC      ) || \
                                       ((MXB_INPUT) == CLU0_MXB_ADC1_AWD      ) || \
                                       ((MXB_INPUT) == CLU0_MXB_ADC1_EOSEQ    ) || \
                                       ((MXB_INPUT) == CLU0_MXB_TIM6_UP       ) || \
                                       ((MXB_INPUT) == CLU0_MXB_TIM14_CC1     ) || \
                                       ((MXB_INPUT) == CLU0_MXB_COMP1_OUT     ) || \
                                       ((MXB_INPUT) == CLU0_MXB_COMP2_OUT     ) || \
                                       ((MXB_INPUT) == CLU0_MXB_COMP3_OUT     ) || \
                                       ((MXB_INPUT) == CLU0_MXB_PA3           ) || \
                                       ((MXB_INPUT) == CLU0_MXB_PA4           ) || \
                                       ((MXB_INPUT) == CLU0_MXB_PA5           ) || \
                                       ((MXB_INPUT) == CLU0_MXB_PB1           ))

/**
  * @}
  */

/** @defgroup CLU0_Multiplexer_C_Input_Selection    CLU0_Multiplexer_C Input Selection
  * @{
  */
#define CLU0_MXC_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU0_MXC_CLU1_OUT_INTER               ((uint32_t)0x00000100)
#define CLU0_MXC_CLU2_OUT_INTER               ((uint32_t)0x00000200)
#define CLU0_MXC_CLU3_OUT_INTER               ((uint32_t)0x00000300)
#define CLU0_MXC_COMP1_OUT                    ((uint32_t)0x00000400)
#define CLU0_MXC_COMP2_OUT                    ((uint32_t)0x00000500)
#define CLU0_MXC_COMP3_OUT                    ((uint32_t)0x00000600)
#define CLU0_MXC_TIM14_UP                     ((uint32_t)0x00000700)
#define CLU0_MXC_TIM15_CC1                    ((uint32_t)0x00000800)
#define CLU0_MXC_TIM15_UP                     ((uint32_t)0x00000900)
#define CLU0_MXC_TIM2_TRIG                    ((uint32_t)0x00000A00)
#define CLU0_MXC_TIM16_UP                     ((uint32_t)0x00000B00)
#define CLU0_MXC_PA6                          ((uint32_t)0x00000C00)
#define CLU0_MXC_PA7                          ((uint32_t)0x00000D00)
#define CLU0_MXC_PA11                         ((uint32_t)0x00000E00)
#define CLU0_MXC_PC11                         ((uint32_t)0x00000F00)

#define IS_CLU0_MXC_INPUT(MXC_INPUT)  (((MXC_INPUT) == CLU0_MXC_CLU0_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU0_MXC_CLU1_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU0_MXC_CLU2_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU0_MXC_CLU3_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU0_MXC_COMP1_OUT     ) || \
                                       ((MXC_INPUT) == CLU0_MXC_COMP2_OUT     ) || \
                                       ((MXC_INPUT) == CLU0_MXC_COMP3_OUT     ) || \
                                       ((MXC_INPUT) == CLU0_MXC_TIM14_UP      ) || \
                                       ((MXC_INPUT) == CLU0_MXC_TIM15_CC1     ) || \
                                       ((MXC_INPUT) == CLU0_MXC_TIM15_UP      ) || \
                                       ((MXC_INPUT) == CLU0_MXC_TIM2_TRIG     ) || \
                                       ((MXC_INPUT) == CLU0_MXC_TIM16_UP      ) || \
                                       ((MXC_INPUT) == CLU0_MXC_PA6           ) || \
                                       ((MXC_INPUT) == CLU0_MXC_PA7           ) || \
                                       ((MXC_INPUT) == CLU0_MXC_PA11          ) || \
                                       ((MXC_INPUT) == CLU0_MXC_PC11          ))

/**
  * @}
  */

/** @defgroup CLU0_Multiplexer_D_Input_Selection    CLU0_Multiplexer_D Input Selection
  * @{
  */
#define CLU0_MXD_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU0_MXD_CLU1_OUT_INTER               ((uint32_t)0x00001000)
#define CLU0_MXD_CLU2_OUT_INTER               ((uint32_t)0x00002000)
#define CLU0_MXD_CLU3_OUT_INTER               ((uint32_t)0x00003000)
#define CLU0_MXD_COMP1_OUT                    ((uint32_t)0x00004000)
#define CLU0_MXD_COMP2_OUT                    ((uint32_t)0x00005000)
#define CLU0_MXD_RTC_OUT                      ((uint32_t)0x00006000)
#define CLU0_MXD_TIM16_COM                    ((uint32_t)0x00007000)
#define CLU0_MXD_TIM1_UP                      ((uint32_t)0x0000A000)
#define CLU0_MXD_TIM2_CC1                     ((uint32_t)0x0000B000)
#define CLU0_MXD_PA12                         ((uint32_t)0x0000C000)
#define CLU0_MXD_PA13                         ((uint32_t)0x0000D000)
#define CLU0_MXD_PA14                         ((uint32_t)0x0000E000)
#define CLU0_MXD_PC12                         ((uint32_t)0x0000F000)

#define IS_CLU0_MXD_INPUT(MXD_INPUT)  (((MXD_INPUT) == CLU0_MXD_CLU0_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU0_MXD_CLU1_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU0_MXD_CLU2_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU0_MXD_CLU3_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU0_MXD_COMP1_OUT     ) || \
                                       ((MXD_INPUT) == CLU0_MXD_COMP2_OUT     ) || \
                                       ((MXD_INPUT) == CLU0_MXD_RTC_OUT       ) || \
                                       ((MXD_INPUT) == CLU0_MXD_TIM16_COM     ) || \
                                       ((MXD_INPUT) == CLU0_MXD_TIM1_UP       ) || \
                                       ((MXD_INPUT) == CLU0_MXD_TIM2_CC1      ) || \
                                       ((MXD_INPUT) == CLU0_MXD_PA12          ) || \
                                       ((MXD_INPUT) == CLU0_MXD_PA13          ) || \
                                       ((MXD_INPUT) == CLU0_MXD_PA14          ) || \
                                       ((MXD_INPUT) == CLU0_MXD_PC12          ))

/**
  * @}
  */


/** @defgroup CLU1_Multiplexer_A_Input_Selection    CLU1_Multiplexer_A Input Selection
  * @{
  */
#define CLU1_MXA_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU1_MXA_CLU1_OUT_INTER               ((uint32_t)0x00000001)
#define CLU1_MXA_CLU2_OUT_INTER               ((uint32_t)0x00000002)
#define CLU1_MXA_CLU3_OUT_INTER               ((uint32_t)0x00000003)
#define CLU1_MXA_TIM1_BRK                     ((uint32_t)0x00000004)
#define CLU1_MXA_TIM1_CC1                     ((uint32_t)0x00000005)
#define CLU1_MXA_TIM1_COM                     ((uint32_t)0x00000006)
#define CLU1_MXA_TIM1_TRIG                    ((uint32_t)0x00000007)
#define CLU1_MXA_TIM1_UP                      ((uint32_t)0x00000008)
#define CLU1_MXA_COMP1_OUT                    ((uint32_t)0x00000009)
#define CLU1_MXA_COMP2_OUT                    ((uint32_t)0x0000000A)
#define CLU1_MXA_COMP3_OUT                    ((uint32_t)0x0000000B)
#define CLU1_MXA_PA3                          ((uint32_t)0x0000000C)
#define CLU1_MXA_PA4                          ((uint32_t)0x0000000D)
#define CLU1_MXA_PA5                          ((uint32_t)0x0000000E)
#define CLU1_MXA_PC10                         ((uint32_t)0x0000000F)

#define IS_CLU1_MXA_INPUT(MXA_INPUT)  (((MXA_INPUT) == CLU1_MXA_CLU0_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU1_MXA_CLU1_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU1_MXA_CLU2_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU1_MXA_CLU3_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU1_MXA_TIM1_BRK      ) || \
                                       ((MXA_INPUT) == CLU1_MXA_TIM1_CC1      ) || \
                                       ((MXA_INPUT) == CLU1_MXA_TIM1_COM      ) || \
                                       ((MXA_INPUT) == CLU1_MXA_TIM1_TRIG     ) || \
                                       ((MXA_INPUT) == CLU1_MXA_TIM1_UP       ) || \
                                       ((MXA_INPUT) == CLU1_MXA_COMP1_OUT     ) || \
                                       ((MXA_INPUT) == CLU1_MXA_COMP2_OUT     ) || \
                                       ((MXA_INPUT) == CLU1_MXA_COMP3_OUT     ) || \
                                       ((MXA_INPUT) == CLU1_MXA_PA3           ) || \
                                       ((MXA_INPUT) == CLU1_MXA_PA4           ) || \
                                       ((MXA_INPUT) == CLU1_MXA_PA5           ) || \
                                       ((MXA_INPUT) == CLU1_MXA_PC10          ))

/**
  * @}
  */

/** @defgroup CLU1_Multiplexer_B_Input_Selection    CLU1_Multiplexer_B Input Selection
  * @{
  */
#define CLU1_MXB_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU1_MXB_CLU1_OUT_INTER               ((uint32_t)0x00000010)
#define CLU1_MXB_CLU2_OUT_INTER               ((uint32_t)0x00000020)
#define CLU1_MXB_CLU3_OUT_INTER               ((uint32_t)0x00000030)
#define CLU1_MXB_ADC1_EOC                     ((uint32_t)0x00000040)
#define CLU1_MXB_ADC1_AWD                     ((uint32_t)0x00000050)
#define CLU1_MXB_ADC1_EOSEQ                   ((uint32_t)0x00000060)
#define CLU1_MXB_TIM6_UP                      ((uint32_t)0x00000070)
#define CLU1_MXB_TIM14_CC1                    ((uint32_t)0x00000080)
#define CLU1_MXB_COMP1_OUT                    ((uint32_t)0x00000090)
#define CLU1_MXB_COMP2_OUT                    ((uint32_t)0x000000A0)
#define CLU1_MXB_COMP3_OUT                    ((uint32_t)0x000000B0)
#define CLU1_MXB_PA0                          ((uint32_t)0x000000C0)
#define CLU1_MXB_PA1                          ((uint32_t)0x000000D0)
#define CLU1_MXB_PA2                          ((uint32_t)0x000000E0)
#define CLU1_MXB_PB1                          ((uint32_t)0x000000F0)

#define IS_CLU1_MXB_INPUT(MXB_INPUT)  (((MXB_INPUT) == CLU1_MXB_CLU0_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU1_MXB_CLU1_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU1_MXB_CLU2_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU1_MXB_CLU3_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU1_MXB_ADC1_EOC      ) || \
                                       ((MXB_INPUT) == CLU1_MXB_ADC1_AWD      ) || \
                                       ((MXB_INPUT) == CLU1_MXB_ADC1_EOSEQ    ) || \
                                       ((MXB_INPUT) == CLU1_MXB_TIM6_UP       ) || \
                                       ((MXB_INPUT) == CLU1_MXB_TIM14_CC1     ) || \
                                       ((MXB_INPUT) == CLU1_MXB_COMP1_OUT     ) || \
                                       ((MXB_INPUT) == CLU1_MXB_COMP2_OUT     ) || \
                                       ((MXB_INPUT) == CLU1_MXB_COMP3_OUT     ) || \
                                       ((MXB_INPUT) == CLU1_MXB_PA0           ) || \
                                       ((MXB_INPUT) == CLU1_MXB_PA1           ) || \
                                       ((MXB_INPUT) == CLU1_MXB_PA2           ) || \
                                       ((MXB_INPUT) == CLU1_MXB_PB1           ))

/**
  * @}
  */

/** @defgroup CLU1_Multiplexer_C_Input_Selection    CLU1_Multiplexer_C Input Selection
  * @{
  */
#define CLU1_MXC_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU1_MXC_CLU1_OUT_INTER               ((uint32_t)0x00000100)
#define CLU1_MXC_CLU2_OUT_INTER               ((uint32_t)0x00000200)
#define CLU1_MXC_CLU3_OUT_INTER               ((uint32_t)0x00000300)
#define CLU1_MXC_COMP1_OUT                    ((uint32_t)0x00000400)
#define CLU1_MXC_COMP2_OUT                    ((uint32_t)0x00000500)
#define CLU1_MXC_COMP3_OUT                    ((uint32_t)0x00000600)
#define CLU1_MXC_TIM14_UP                     ((uint32_t)0x00000700)
#define CLU1_MXC_TIM15_CC1                    ((uint32_t)0x00000800)
#define CLU1_MXC_TIM15_UP                     ((uint32_t)0x00000900)
#define CLU1_MXC_TIM2_TRIG                    ((uint32_t)0x00000A00)
#define CLU1_MXC_TIM16_UP                     ((uint32_t)0x00000B00)
#define CLU1_MXC_PA12                         ((uint32_t)0x00000C00)
#define CLU1_MXC_PA13                         ((uint32_t)0x00000D00)
#define CLU1_MXC_PA14                         ((uint32_t)0x00000E00)
#define CLU1_MXC_PC11                         ((uint32_t)0x00000F00)

#define IS_CLU1_MXC_INPUT(MXC_INPUT)  (((MXC_INPUT) == CLU1_MXC_CLU0_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU1_MXC_CLU1_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU1_MXC_CLU2_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU1_MXC_CLU3_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU1_MXC_COMP1_OUT     ) || \
                                       ((MXC_INPUT) == CLU1_MXC_COMP2_OUT     ) || \
                                       ((MXC_INPUT) == CLU1_MXC_COMP3_OUT     ) || \
                                       ((MXC_INPUT) == CLU1_MXC_TIM14_UP      ) || \
                                       ((MXC_INPUT) == CLU1_MXC_TIM15_CC1     ) || \
                                       ((MXC_INPUT) == CLU1_MXC_TIM15_UP      ) || \
                                       ((MXC_INPUT) == CLU1_MXC_TIM2_TRIG     ) || \
                                       ((MXC_INPUT) == CLU1_MXC_TIM16_UP      ) || \
                                       ((MXC_INPUT) == CLU1_MXC_PA12          ) || \
                                       ((MXC_INPUT) == CLU1_MXC_PA13          ) || \
                                       ((MXC_INPUT) == CLU1_MXC_PA14          ) || \
                                       ((MXC_INPUT) == CLU1_MXC_PC11          ))

/**
  * @}
  */

/** @defgroup CLU1_Multiplexer_D_Input_Selection    CLU1_Multiplexer_D Input Selection
  * @{
  */
#define CLU1_MXD_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU1_MXD_CLU1_OUT_INTER               ((uint32_t)0x00001000)
#define CLU1_MXD_CLU2_OUT_INTER               ((uint32_t)0x00002000)
#define CLU1_MXD_CLU3_OUT_INTER               ((uint32_t)0x00003000)
#define CLU1_MXD_COMP1_OUT                    ((uint32_t)0x00004000)
#define CLU1_MXD_COMP2_OUT                    ((uint32_t)0x00005000)
#define CLU1_MXD_RTC_OUT                      ((uint32_t)0x00006000)
#define CLU1_MXD_TIM16_COM                    ((uint32_t)0x00007000)
#define CLU1_MXD_TIM1_UP                      ((uint32_t)0x0000A000)
#define CLU1_MXD_TIM2_CC1                     ((uint32_t)0x0000B000)
#define CLU1_MXD_PA6                          ((uint32_t)0x0000C000)
#define CLU1_MXD_PA7                          ((uint32_t)0x0000D000)
#define CLU1_MXD_PA11                         ((uint32_t)0x0000E000)
#define CLU1_MXD_PC12                         ((uint32_t)0x0000F000)

#define IS_CLU1_MXD_INPUT(MXD_INPUT)  (((MXD_INPUT) == CLU1_MXD_CLU0_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU1_MXD_CLU1_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU1_MXD_CLU2_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU1_MXD_CLU3_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU1_MXD_COMP1_OUT     ) || \
                                       ((MXD_INPUT) == CLU1_MXD_COMP2_OUT     ) || \
                                       ((MXD_INPUT) == CLU1_MXD_RTC_OUT       ) || \
                                       ((MXD_INPUT) == CLU1_MXD_TIM16_COM     ) || \
                                       ((MXD_INPUT) == CLU1_MXD_TIM1_UP       ) || \
                                       ((MXD_INPUT) == CLU1_MXD_TIM2_CC1      ) || \
                                       ((MXD_INPUT) == CLU1_MXD_PA6           ) || \
                                       ((MXD_INPUT) == CLU1_MXD_PA7           ) || \
                                       ((MXD_INPUT) == CLU1_MXD_PA11          ) || \
                                       ((MXD_INPUT) == CLU1_MXD_PC12          ))

/**
  * @}
  */


/** @defgroup CLU2_Multiplexer_A_Input_Selection    CLU2_Multiplexer_A Input Selection
  * @{
  */
#define CLU2_MXA_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU2_MXA_CLU1_OUT_INTER               ((uint32_t)0x00000001)
#define CLU2_MXA_CLU2_OUT_INTER               ((uint32_t)0x00000002)
#define CLU2_MXA_CLU3_OUT_INTER               ((uint32_t)0x00000003)
#define CLU2_MXA_TIM1_BRK                     ((uint32_t)0x00000004)
#define CLU2_MXA_TIM1_CC1                     ((uint32_t)0x00000005)
#define CLU2_MXA_TIM1_COM                     ((uint32_t)0x00000006)
#define CLU2_MXA_TIM1_TRIG                    ((uint32_t)0x00000007)
#define CLU2_MXA_TIM1_UP                      ((uint32_t)0x00000008)
#define CLU2_MXA_COMP1_OUT                    ((uint32_t)0x00000009)
#define CLU2_MXA_COMP2_OUT                    ((uint32_t)0x0000000A)
#define CLU2_MXA_COMP3_OUT                    ((uint32_t)0x0000000B)
#define CLU2_MXA_PA6                          ((uint32_t)0x0000000C)
#define CLU2_MXA_PA7                          ((uint32_t)0x0000000D)
#define CLU2_MXA_PA11                         ((uint32_t)0x0000000E)
#define CLU2_MXA_PC10                         ((uint32_t)0x0000000F)

#define IS_CLU2_MXA_INPUT(MXA_INPUT)  (((MXA_INPUT) == CLU2_MXA_CLU0_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU2_MXA_CLU1_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU2_MXA_CLU2_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU2_MXA_CLU3_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU2_MXA_TIM1_BRK      ) || \
                                       ((MXA_INPUT) == CLU2_MXA_TIM1_CC1      ) || \
                                       ((MXA_INPUT) == CLU2_MXA_TIM1_COM      ) || \
                                       ((MXA_INPUT) == CLU2_MXA_TIM1_TRIG     ) || \
                                       ((MXA_INPUT) == CLU2_MXA_TIM1_UP       ) || \
                                       ((MXA_INPUT) == CLU2_MXA_COMP1_OUT     ) || \
                                       ((MXA_INPUT) == CLU2_MXA_COMP2_OUT     ) || \
                                       ((MXA_INPUT) == CLU2_MXA_COMP3_OUT     ) || \
                                       ((MXA_INPUT) == CLU2_MXA_PA6           ) || \
                                       ((MXA_INPUT) == CLU2_MXA_PA7           ) || \
                                       ((MXA_INPUT) == CLU2_MXA_PA11          ) || \
                                       ((MXA_INPUT) == CLU2_MXA_PC10          ))

/**
  * @}
  */

/** @defgroup CLU2_Multiplexer_B_Input_Selection    CLU2_Multiplexer_B Input Selection
  * @{
  */
#define CLU2_MXB_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU2_MXB_CLU1_OUT_INTER               ((uint32_t)0x00000010)
#define CLU2_MXB_CLU2_OUT_INTER               ((uint32_t)0x00000020)
#define CLU2_MXB_CLU3_OUT_INTER               ((uint32_t)0x00000030)
#define CLU2_MXB_ADC1_EOC                     ((uint32_t)0x00000040)
#define CLU2_MXB_ADC1_AWD                     ((uint32_t)0x00000050)
#define CLU2_MXB_ADC1_EOSEQ                   ((uint32_t)0x00000060)
#define CLU2_MXB_TIM6_UP                      ((uint32_t)0x00000070)
#define CLU2_MXB_TIM14_CC1                    ((uint32_t)0x00000080)
#define CLU2_MXB_COMP1_OUT                    ((uint32_t)0x00000090)
#define CLU2_MXB_COMP2_OUT                    ((uint32_t)0x000000A0)
#define CLU2_MXB_COMP3_OUT                    ((uint32_t)0x000000B0)
#define CLU2_MXB_PA3                          ((uint32_t)0x000000C0)
#define CLU2_MXB_PA4                          ((uint32_t)0x000000D0)
#define CLU2_MXB_PA5                          ((uint32_t)0x000000E0)
#define CLU2_MXB_PB1                          ((uint32_t)0x000000F0)

#define IS_CLU2_MXB_INPUT(MXB_INPUT)  (((MXB_INPUT) == CLU2_MXB_CLU0_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU2_MXB_CLU1_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU2_MXB_CLU2_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU2_MXB_CLU3_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU2_MXB_ADC1_EOC      ) || \
                                       ((MXB_INPUT) == CLU2_MXB_ADC1_AWD      ) || \
                                       ((MXB_INPUT) == CLU2_MXB_ADC1_EOSEQ    ) || \
                                       ((MXB_INPUT) == CLU2_MXB_TIM6_UP       ) || \
                                       ((MXB_INPUT) == CLU2_MXB_TIM14_CC1     ) || \
                                       ((MXB_INPUT) == CLU2_MXB_COMP1_OUT     ) || \
                                       ((MXB_INPUT) == CLU2_MXB_COMP2_OUT     ) || \
                                       ((MXB_INPUT) == CLU2_MXB_COMP3_OUT     ) || \
                                       ((MXB_INPUT) == CLU2_MXB_PA3           ) || \
                                       ((MXB_INPUT) == CLU2_MXB_PA4           ) || \
                                       ((MXB_INPUT) == CLU2_MXB_PA5           ) || \
                                       ((MXB_INPUT) == CLU2_MXB_PB1           ))

/**
  * @}
  */

/** @defgroup CLU2_Multiplexer_C_Input_Selection    CLU2_Multiplexer_C Input Selection
  * @{
  */
#define CLU2_MXC_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU2_MXC_CLU1_OUT_INTER               ((uint32_t)0x00000100)
#define CLU2_MXC_CLU2_OUT_INTER               ((uint32_t)0x00000200)
#define CLU2_MXC_CLU3_OUT_INTER               ((uint32_t)0x00000300)
#define CLU2_MXC_COMP1_OUT                    ((uint32_t)0x00000400)
#define CLU2_MXC_COMP2_OUT                    ((uint32_t)0x00000500)
#define CLU2_MXC_COMP3_OUT                    ((uint32_t)0x00000600)
#define CLU2_MXC_TIM14_UP                     ((uint32_t)0x00000700)
#define CLU2_MXC_TIM15_CC1                    ((uint32_t)0x00000800)
#define CLU2_MXC_TIM15_UP                     ((uint32_t)0x00000900)
#define CLU2_MXC_TIM2_TRIG                    ((uint32_t)0x00000A00)
#define CLU2_MXC_TIM16_UP                     ((uint32_t)0x00000B00)
#define CLU2_MXC_PA0                          ((uint32_t)0x00000C00)
#define CLU2_MXC_PA1                          ((uint32_t)0x00000D00)
#define CLU2_MXC_PA2                          ((uint32_t)0x00000E00)
#define CLU2_MXC_PC11                         ((uint32_t)0x00000F00)

#define IS_CLU2_MXC_INPUT(MXC_INPUT)  (((MXC_INPUT) == CLU2_MXC_CLU0_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU2_MXC_CLU1_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU2_MXC_CLU2_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU2_MXC_CLU3_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU2_MXC_COMP1_OUT     ) || \
                                       ((MXC_INPUT) == CLU2_MXC_COMP2_OUT     ) || \
                                       ((MXC_INPUT) == CLU2_MXC_COMP3_OUT     ) || \
                                       ((MXC_INPUT) == CLU2_MXC_TIM14_UP      ) || \
                                       ((MXC_INPUT) == CLU2_MXC_TIM15_CC1     ) || \
                                       ((MXC_INPUT) == CLU2_MXC_TIM15_UP      ) || \
                                       ((MXC_INPUT) == CLU2_MXC_TIM2_TRIG     ) || \
                                       ((MXC_INPUT) == CLU2_MXC_TIM16_UP      ) || \
                                       ((MXC_INPUT) == CLU2_MXC_PA0           ) || \
                                       ((MXC_INPUT) == CLU2_MXC_PA1           ) || \
                                       ((MXC_INPUT) == CLU2_MXC_PA2           ) || \
                                       ((MXC_INPUT) == CLU2_MXC_PC11          ))

/**
  * @}
  */

/** @defgroup CLU2_Multiplexer_D_Input_Selection    CLU2_Multiplexer_D Input Selection
  * @{
  */
#define CLU2_MXD_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU2_MXD_CLU1_OUT_INTER               ((uint32_t)0x00001000)
#define CLU2_MXD_CLU2_OUT_INTER               ((uint32_t)0x00002000)
#define CLU2_MXD_CLU3_OUT_INTER               ((uint32_t)0x00003000)
#define CLU2_MXD_COMP1_OUT                    ((uint32_t)0x00004000)
#define CLU2_MXD_COMP2_OUT                    ((uint32_t)0x00005000)
#define CLU2_MXD_RTC_OUT                      ((uint32_t)0x00006000)
#define CLU2_MXD_TIM16_COM                    ((uint32_t)0x00007000)
#define CLU2_MXD_TIM1_UP                      ((uint32_t)0x0000A000)
#define CLU2_MXD_TIM2_CC1                     ((uint32_t)0x0000B000)
#define CLU2_MXD_PA12                         ((uint32_t)0x0000C000)
#define CLU2_MXD_PA13                         ((uint32_t)0x0000D000)
#define CLU2_MXD_PA14                         ((uint32_t)0x0000E000)
#define CLU2_MXD_PC12                         ((uint32_t)0x0000F000)

#define IS_CLU2_MXD_INPUT(MXD_INPUT)  (((MXD_INPUT) == CLU2_MXD_CLU0_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU2_MXD_CLU1_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU2_MXD_CLU2_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU2_MXD_CLU3_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU2_MXD_COMP1_OUT     ) || \
                                       ((MXD_INPUT) == CLU2_MXD_COMP2_OUT     ) || \
                                       ((MXD_INPUT) == CLU2_MXD_RTC_OUT       ) || \
                                       ((MXD_INPUT) == CLU2_MXD_TIM16_COM     ) || \
                                       ((MXD_INPUT) == CLU2_MXD_TIM1_UP       ) || \
                                       ((MXD_INPUT) == CLU2_MXD_TIM2_CC1      ) || \
                                       ((MXD_INPUT) == CLU2_MXD_PA12          ) || \
                                       ((MXD_INPUT) == CLU2_MXD_PA13          ) || \
                                       ((MXD_INPUT) == CLU2_MXD_PA14          ) || \
                                       ((MXD_INPUT) == CLU2_MXD_PC12          ))

/**
  * @}
  */


/** @defgroup CLU3_Multiplexer_A_Input_Selection    CLU3_Multiplexer_A Input Selection
  * @{
  */
#define CLU3_MXA_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU3_MXA_CLU1_OUT_INTER               ((uint32_t)0x00000001)
#define CLU3_MXA_CLU2_OUT_INTER               ((uint32_t)0x00000002)
#define CLU3_MXA_CLU3_OUT_INTER               ((uint32_t)0x00000003)
#define CLU3_MXA_TIM1_BRK                     ((uint32_t)0x00000004)
#define CLU3_MXA_TIM1_CC1                     ((uint32_t)0x00000005)
#define CLU3_MXA_TIM1_COM                     ((uint32_t)0x00000006)
#define CLU3_MXA_TIM1_TRIG                    ((uint32_t)0x00000007)
#define CLU3_MXA_TIM1_UP                      ((uint32_t)0x00000008)
#define CLU3_MXA_COMP1_OUT                    ((uint32_t)0x00000009)
#define CLU3_MXA_COMP2_OUT                    ((uint32_t)0x0000000A)
#define CLU3_MXA_COMP3_OUT                    ((uint32_t)0x0000000B)
#define CLU3_MXA_PA12                         ((uint32_t)0x0000000C)
#define CLU3_MXA_PA13                         ((uint32_t)0x0000000D)
#define CLU3_MXA_PA14                         ((uint32_t)0x0000000E)
#define CLU3_MXA_PC10                         ((uint32_t)0x0000000F)

#define IS_CLU3_MXA_INPUT(MXA_INPUT)  (((MXA_INPUT) == CLU3_MXA_CLU0_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU3_MXA_CLU1_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU3_MXA_CLU2_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU3_MXA_CLU3_OUT_INTER) || \
                                       ((MXA_INPUT) == CLU3_MXA_TIM1_BRK      ) || \
                                       ((MXA_INPUT) == CLU3_MXA_TIM1_CC1      ) || \
                                       ((MXA_INPUT) == CLU3_MXA_TIM1_COM      ) || \
                                       ((MXA_INPUT) == CLU3_MXA_TIM1_TRIG     ) || \
                                       ((MXA_INPUT) == CLU3_MXA_TIM1_UP       ) || \
                                       ((MXA_INPUT) == CLU3_MXA_COMP1_OUT     ) || \
                                       ((MXA_INPUT) == CLU3_MXA_COMP2_OUT     ) || \
                                       ((MXA_INPUT) == CLU3_MXA_COMP3_OUT     ) || \
                                       ((MXA_INPUT) == CLU3_MXA_PA12          ) || \
                                       ((MXA_INPUT) == CLU3_MXA_PA13          ) || \
                                       ((MXA_INPUT) == CLU3_MXA_PA14          ) || \
                                       ((MXA_INPUT) == CLU3_MXA_PC10          ))

/**
  * @}
  */

/** @defgroup CLU3_Multiplexer_B_Input_Selection    CLU3_Multiplexer_B Input Selection
  * @{
  */
#define CLU3_MXB_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU3_MXB_CLU1_OUT_INTER               ((uint32_t)0x00000010)
#define CLU3_MXB_CLU2_OUT_INTER               ((uint32_t)0x00000020)
#define CLU3_MXB_CLU3_OUT_INTER               ((uint32_t)0x00000030)
#define CLU3_MXB_ADC1_EOC                     ((uint32_t)0x00000040)
#define CLU3_MXB_ADC1_AWD                     ((uint32_t)0x00000050)
#define CLU3_MXB_ADC1_EOSEQ                   ((uint32_t)0x00000060)
#define CLU3_MXB_TIM6_UP                      ((uint32_t)0x00000070)
#define CLU3_MXB_TIM14_CC1                    ((uint32_t)0x00000080)
#define CLU3_MXB_COMP1_OUT                    ((uint32_t)0x00000090)
#define CLU3_MXB_COMP2_OUT                    ((uint32_t)0x000000A0)
#define CLU3_MXB_COMP3_OUT                    ((uint32_t)0x000000B0)
#define CLU3_MXB_PA6                          ((uint32_t)0x000000C0)
#define CLU3_MXB_PA7                          ((uint32_t)0x000000D0)
#define CLU3_MXB_PA11                         ((uint32_t)0x000000E0)
#define CLU3_MXB_PB1                          ((uint32_t)0x000000F0)

#define IS_CLU3_MXB_INPUT(MXB_INPUT)  (((MXB_INPUT) == CLU3_MXB_CLU0_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU3_MXB_CLU1_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU3_MXB_CLU2_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU3_MXB_CLU3_OUT_INTER) || \
                                       ((MXB_INPUT) == CLU3_MXB_ADC1_EOC      ) || \
                                       ((MXB_INPUT) == CLU3_MXB_ADC1_AWD      ) || \
                                       ((MXB_INPUT) == CLU3_MXB_ADC1_EOSEQ    ) || \
                                       ((MXB_INPUT) == CLU3_MXB_TIM6_UP       ) || \
                                       ((MXB_INPUT) == CLU3_MXB_TIM14_CC1     ) || \
                                       ((MXB_INPUT) == CLU3_MXB_COMP1_OUT     ) || \
                                       ((MXB_INPUT) == CLU3_MXB_COMP2_OUT     ) || \
                                       ((MXB_INPUT) == CLU3_MXB_COMP3_OUT     ) || \
                                       ((MXB_INPUT) == CLU3_MXB_PA6           ) || \
                                       ((MXB_INPUT) == CLU3_MXB_PA7           ) || \
                                       ((MXB_INPUT) == CLU3_MXB_PA11          ) || \
                                       ((MXB_INPUT) == CLU3_MXB_PB1           ))

/**
  * @}
  */

/** @defgroup CLU3_Multiplexer_C_Input_Selection    CLU3_Multiplexer_C Input Selection
  * @{
  */
#define CLU3_MXC_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU3_MXC_CLU1_OUT_INTER               ((uint32_t)0x00000100)
#define CLU3_MXC_CLU2_OUT_INTER               ((uint32_t)0x00000200)
#define CLU3_MXC_CLU3_OUT_INTER               ((uint32_t)0x00000300)
#define CLU3_MXC_COMP1_OUT                    ((uint32_t)0x00000400)
#define CLU3_MXC_COMP2_OUT                    ((uint32_t)0x00000500)
#define CLU3_MXC_COMP3_OUT                    ((uint32_t)0x00000600)
#define CLU3_MXC_TIM14_UP                     ((uint32_t)0x00000700)
#define CLU3_MXC_TIM15_CC1                    ((uint32_t)0x00000800)
#define CLU3_MXC_TIM15_UP                     ((uint32_t)0x00000900)
#define CLU3_MXC_TIM2_TRIG                    ((uint32_t)0x00000A00)
#define CLU3_MXC_TIM16_UP                     ((uint32_t)0x00000B00)
#define CLU3_MXC_PA3                          ((uint32_t)0x00000C00)
#define CLU3_MXC_PA4                          ((uint32_t)0x00000D00)
#define CLU3_MXC_PA5                          ((uint32_t)0x00000E00)
#define CLU3_MXC_PC11                         ((uint32_t)0x00000F00)

#define IS_CLU3_MXC_INPUT(MXC_INPUT)  (((MXC_INPUT) == CLU3_MXC_CLU0_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU3_MXC_CLU1_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU3_MXC_CLU2_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU3_MXC_CLU3_OUT_INTER) || \
                                       ((MXC_INPUT) == CLU3_MXC_COMP1_OUT     ) || \
                                       ((MXC_INPUT) == CLU3_MXC_COMP2_OUT     ) || \
                                       ((MXC_INPUT) == CLU3_MXC_COMP3_OUT     ) || \
                                       ((MXC_INPUT) == CLU3_MXC_TIM14_UP      ) || \
                                       ((MXC_INPUT) == CLU3_MXC_TIM15_CC1     ) || \
                                       ((MXC_INPUT) == CLU3_MXC_TIM15_UP      ) || \
                                       ((MXC_INPUT) == CLU3_MXC_TIM2_TRIG     ) || \
                                       ((MXC_INPUT) == CLU3_MXC_TIM16_UP      ) || \
                                       ((MXC_INPUT) == CLU3_MXC_PA3           ) || \
                                       ((MXC_INPUT) == CLU3_MXC_PA4           ) || \
                                       ((MXC_INPUT) == CLU3_MXC_PA5           ) || \
                                       ((MXC_INPUT) == CLU3_MXC_PC11          ))

/**
  * @}
  */

/** @defgroup CLU3_Multiplexer_D_Input_Selection    CLU3_Multiplexer_D Input Selection
  * @{
  */
#define CLU3_MXD_CLU0_OUT_INTER               ((uint32_t)0x00000000)
#define CLU3_MXD_CLU1_OUT_INTER               ((uint32_t)0x00001000)
#define CLU3_MXD_CLU2_OUT_INTER               ((uint32_t)0x00002000)
#define CLU3_MXD_CLU3_OUT_INTER               ((uint32_t)0x00003000)
#define CLU3_MXD_COMP1_OUT                    ((uint32_t)0x00004000)
#define CLU3_MXD_COMP2_OUT                    ((uint32_t)0x00005000)
#define CLU3_MXD_RTC_OUT                      ((uint32_t)0x00006000)
#define CLU3_MXD_TIM16_COM                    ((uint32_t)0x00007000)
#define CLU3_MXD_TIM1_UP                      ((uint32_t)0x0000A000)
#define CLU3_MXD_TIM2_CC1                     ((uint32_t)0x0000B000)
#define CLU3_MXD_PA0                          ((uint32_t)0x0000C000)
#define CLU3_MXD_PA1                          ((uint32_t)0x0000D000)
#define CLU3_MXD_PA2                          ((uint32_t)0x0000E000)
#define CLU3_MXD_PC12                         ((uint32_t)0x0000F000)

#define IS_CLU3_MXD_INPUT(MXD_INPUT)  (((MXD_INPUT) == CLU3_MXD_CLU0_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU3_MXD_CLU1_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU3_MXD_CLU2_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU3_MXD_CLU3_OUT_INTER) || \
                                       ((MXD_INPUT) == CLU3_MXD_COMP1_OUT     ) || \
                                       ((MXD_INPUT) == CLU3_MXD_COMP2_OUT     ) || \
                                       ((MXD_INPUT) == CLU3_MXD_RTC_OUT       ) || \
                                       ((MXD_INPUT) == CLU3_MXD_TIM16_COM     ) || \
                                       ((MXD_INPUT) == CLU3_MXD_TIM1_UP       ) || \
                                       ((MXD_INPUT) == CLU3_MXD_TIM2_CC1      ) || \
                                       ((MXD_INPUT) == CLU3_MXD_PA0           ) || \
                                       ((MXD_INPUT) == CLU3_MXD_PA1           ) || \
                                       ((MXD_INPUT) == CLU3_MXD_PA2           ) || \
                                       ((MXD_INPUT) == CLU3_MXD_PC12          ))

/**
  * @}
  */

/** @defgroup Configurable_Logic_Enable  Configurable Logic Enable
  * @{
  */
typedef enum
{
    CLEN0_CxEN__ALLDISABLE   = 0x00, /*!< CLUx (x = 0&1&2&3) is disabled. The output of the block will be logic low */
    CLEN0_C0EN__ENABLE       = 0x01, /*!< CLU0 is enabled */
    CLEN0_C1EN__ENABLE       = 0x02, /*!< CLU1 is enabled */
    CLEN0_C2EN__ENABLE       = 0x04, /*!< CLU2 is enabled */
    CLEN0_C3EN__ENABLE       = 0x08, /*!< CLU3 is enabled */
} CLEN0_CEN_TypeDef;

#define IS_CLEN0_CEN(CEN) (((CEN) == CLEN0_CxEN__ALLDISABLE) || ((CEN) & 0x0F))
/**
  * @}
  */
/** @defgroup Configurable_Logic_Unit_Channel_Select   Configurable Logic Unit Channel Select
  * @{
  */
typedef enum
{
    CLUxMX_InputChannel__MXA          = 0x00,
    CLUxMX_InputChannel__MXB          = 0x01,
    CLUxMX_InputChannel__MXC          = 0x02,
    CLUxMX_InputChannel__MXD          = 0x03,
    CLUxMX_InputChannel__CARRY_IN     = 0x04,
} CLUxMX_InputChannel_Typedef;

#define IS_CLUxMX_InputChannel(ChannelSelect) (((ChannelSelect) == CLUxMX_InputChannel__MXA) || \
                                              ((ChannelSelect) == CLUxMX_InputChannel__MXB)  || \
                                              ((ChannelSelect) == CLUxMX_InputChannel__MXC)  || \
                                              ((ChannelSelect) == CLUxMX_InputChannel__MXD)  || \
                                              ((ChannelSelect) == CLUxMX_InputChannel__CARRY_IN))
/**
  * @}
  */

/** @defgroup CLU_Clock_Select   CLU Clock Select
  * @{
  */
typedef enum
{
    CLUxCF_CLKSEL__CARRY_IN           = 0x00, /*!< The carry-in signal */
    CLUxCF_CLKSEL__MXA_INPUT          = 0x01, /*!< The MXA input */
    CLUxCF_CLKSEL__SYSCLK             = 0x02, /*!< SYSCLK */
    CLUxCF_CLKSEL__TIMER_REQUESTS     = 0x03  /*!< The alternate clock signal TIMER REQUESTS */
} CLUxCF_CLKSEL_TypeDef;

#define IS_CLUxCF_CLKSEL(CLKSEL) (((CLKSEL) == CLUxCF_CLKSEL__CARRY_IN) || ((CLKSEL) == CLUxCF_CLKSEL__MXA_INPUT) || \
                                 ((CLKSEL) == CLUxCF_CLKSEL__SYSCLK) || ((CLKSEL) == CLUxCF_CLKSEL__TIMER_REQUESTS))
/**
  * @}
  */

/** @defgroup CLU_Clock_Invert  CLU Clock Invert
  * @{
  */
typedef enum
{
    CLUxCF_CLKINV__NORMAL   = 0x00, /*!< Clock signal is not inverted */
    CLUxCF_CLKINV__INVERT   = 0x01, /*!< Clock signal will be inverted */
} CLUxCF_CLKINV_TypeDef;

#define IS_CLUxCF_CLKINV(CLKINV) (((CLKINV) == CLUxCF_CLKINV__NORMAL)|| ((CLKINV) == CLUxCF_CLKINV__INVERT))
/**
  * @}
  */


/** @defgroup CLU_Asynchronous_Output  CLU Asynchronous Output
  * @{
  */
typedef enum
{
    CLUxCF_OEN__DISABLE   = 0x00, /*!< Disables asynchronous output to the selected GPIO pin */
    CLUxCF_OEN__ENABLE    = 0x01, /*!< Enables asynchronous output to the selected GPIO pin */
} CLUxCF_OEN_TypeDef;

#define IS_CLUxCF_OEN(OEN) (((OEN) == CLUxCF_OEN__DISABLE)|| ((OEN) == CLUxCF_OEN__ENABLE))
/**
  * @}
  */

/** @defgroup CLU_DFlipFlop_Output   CLU DFlipFlop Output
  * @{
  */
typedef enum
{
    CLUxCF_OUTSEL__D_FF   = 0x00, /*!< Select D flip-flop output of CLU */
    CLUxCF_OUTSEL__LUT    = 0x01, /*!< Select LUT output */
} CLUxCF_OUTSEL_TypeDef;

#define IS_CLUxCF_OUTSEL(OUTSEL) (((OUTSEL) == CLUxCF_OUTSEL__D_FF)|| ((OUTSEL) == CLUxCF_OUTSEL__LUT))
/**
  * @}
  */

/** @defgroup CLU_Function_Select   CLU Function Select
  * @{
  */
typedef uint32_t CLUxFN_Function_TypeDef;

#define IS_CLUxFN_FUNCTION(FUNC) ((uint32_t)(FUNC) != 0x0)
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup CLU_Multiplexer   CLU Multiplexer
  * @{
  */
#define CLUxMX_MXD__CLUxD0             ((uint32_t)0x00 << 12)
#define CLUxMX_MXD__CLUxD1             ((uint32_t)0x01 << 12)
#define CLUxMX_MXD__CLUxD2             ((uint32_t)0x02 << 12)
#define CLUxMX_MXD__CLUxD3             ((uint32_t)0x03 << 12)
#define CLUxMX_MXD__CLUxD4             ((uint32_t)0x04 << 12)
#define CLUxMX_MXD__CLUxD5             ((uint32_t)0x05 << 12)
#define CLUxMX_MXD__CLUxD6             ((uint32_t)0x06 << 12)
#define CLUxMX_MXD__CLUxD7             ((uint32_t)0x07 << 12)
#define CLUxMX_MXD__CLUxD8             ((uint32_t)0x08 << 12)
#define CLUxMX_MXD__CLUxD9             ((uint32_t)0x09 << 12)
#define CLUxMX_MXD__CLUxD10            ((uint32_t)0x0A << 12)
#define CLUxMX_MXD__CLUxD11            ((uint32_t)0x0B << 12)
#define CLUxMX_MXD__CLUxD12            ((uint32_t)0x0C << 12)
#define CLUxMX_MXD__CLUxD13            ((uint32_t)0x0D << 12)
#define CLUxMX_MXD__CLUxD14            ((uint32_t)0x0E << 12)
#define CLUxMX_MXD__CLUxD15            ((uint32_t)0x0F << 12)

#define CLUxMX_MXC__CLUxC0             ((uint32_t)0x00 << 8)
#define CLUxMX_MXC__CLUxC1             ((uint32_t)0x01 << 8)
#define CLUxMX_MXC__CLUxC2             ((uint32_t)0x02 << 8)
#define CLUxMX_MXC__CLUxC3             ((uint32_t)0x03 << 8)
#define CLUxMX_MXC__CLUxC4             ((uint32_t)0x04 << 8)
#define CLUxMX_MXC__CLUxC5             ((uint32_t)0x05 << 8)
#define CLUxMX_MXC__CLUxC6             ((uint32_t)0x06 << 8)
#define CLUxMX_MXC__CLUxC7             ((uint32_t)0x07 << 8)
#define CLUxMX_MXC__CLUxC8             ((uint32_t)0x08 << 8)
#define CLUxMX_MXC__CLUxC9             ((uint32_t)0x09 << 8)
#define CLUxMX_MXC__CLUxC10            ((uint32_t)0x0A << 8)
#define CLUxMX_MXC__CLUxC11            ((uint32_t)0x0B << 8)
#define CLUxMX_MXC__CLUxC12            ((uint32_t)0x0C << 8)
#define CLUxMX_MXC__CLUxC13            ((uint32_t)0x0D << 8)
#define CLUxMX_MXC__CLUxC14            ((uint32_t)0x0E << 8)
#define CLUxMX_MXC__CLUxC15            ((uint32_t)0x0F << 8)

#define CLUxMX_MXB__CLUxB0             ((uint32_t)0x00 << 4)
#define CLUxMX_MXB__CLUxB1             ((uint32_t)0x01 << 4)
#define CLUxMX_MXB__CLUxB2             ((uint32_t)0x02 << 4)
#define CLUxMX_MXB__CLUxB3             ((uint32_t)0x03 << 4)
#define CLUxMX_MXB__CLUxB4             ((uint32_t)0x04 << 4)
#define CLUxMX_MXB__CLUxB5             ((uint32_t)0x05 << 4)
#define CLUxMX_MXB__CLUxB6             ((uint32_t)0x06 << 4)
#define CLUxMX_MXB__CLUxB7             ((uint32_t)0x07 << 4)
#define CLUxMX_MXB__CLUxB8             ((uint32_t)0x08 << 4)
#define CLUxMX_MXB__CLUxB9             ((uint32_t)0x09 << 4)
#define CLUxMX_MXB__CLUxB10            ((uint32_t)0x0A << 4)
#define CLUxMX_MXB__CLUxB11            ((uint32_t)0x0B << 4)
#define CLUxMX_MXB__CLUxB12            ((uint32_t)0x0C << 4)
#define CLUxMX_MXB__CLUxB13            ((uint32_t)0x0D << 4)
#define CLUxMX_MXB__CLUxB14            ((uint32_t)0x0E << 4)
#define CLUxMX_MXB__CLUxB15            ((uint32_t)0x0F << 4)

#define CLUxMX_MXA__CLUxA0             ((uint32_t)0x00)
#define CLUxMX_MXA__CLUxA1             ((uint32_t)0x01)
#define CLUxMX_MXA__CLUxA2             ((uint32_t)0x02)
#define CLUxMX_MXA__CLUxA3             ((uint32_t)0x03)
#define CLUxMX_MXA__CLUxA4             ((uint32_t)0x04)
#define CLUxMX_MXA__CLUxA5             ((uint32_t)0x05)
#define CLUxMX_MXA__CLUxA6             ((uint32_t)0x06)
#define CLUxMX_MXA__CLUxA7             ((uint32_t)0x07)
#define CLUxMX_MXA__CLUxA8             ((uint32_t)0x08)
#define CLUxMX_MXA__CLUxA9             ((uint32_t)0x09)
#define CLUxMX_MXA__CLUxA10            ((uint32_t)0x0A)
#define CLUxMX_MXA__CLUxA11            ((uint32_t)0x0B)
#define CLUxMX_MXA__CLUxA12            ((uint32_t)0x0C)
#define CLUxMX_MXA__CLUxA13            ((uint32_t)0x0D)
#define CLUxMX_MXA__CLUxA14            ((uint32_t)0x0E)
#define CLUxMX_MXA__CLUxA15            ((uint32_t)0x0F)

typedef enum
{
    CLUx_INPUT_MXA_00 = CLUxMX_MXA__CLUxA0,
    CLUx_INPUT_MXA_01 = CLUxMX_MXA__CLUxA1,
    CLUx_INPUT_MXA_02 = CLUxMX_MXA__CLUxA2,
    CLUx_INPUT_MXA_03 = CLUxMX_MXA__CLUxA3,
    CLUx_INPUT_MXA_04 = CLUxMX_MXA__CLUxA4,
    CLUx_INPUT_MXA_05 = CLUxMX_MXA__CLUxA5,
    CLUx_INPUT_MXA_06 = CLUxMX_MXA__CLUxA6,
    CLUx_INPUT_MXA_07 = CLUxMX_MXA__CLUxA7,
    CLUx_INPUT_MXA_08 = CLUxMX_MXA__CLUxA8,
    CLUx_INPUT_MXA_09 = CLUxMX_MXA__CLUxA9,
    CLUx_INPUT_MXA_10 = CLUxMX_MXA__CLUxA10,
    CLUx_INPUT_MXA_11 = CLUxMX_MXA__CLUxA11,
    CLUx_INPUT_MXA_12 = CLUxMX_MXA__CLUxA12,
    CLUx_INPUT_MXA_13 = CLUxMX_MXA__CLUxA13,
    CLUx_INPUT_MXA_14 = CLUxMX_MXA__CLUxA14,
    CLUx_INPUT_MXA_15 = CLUxMX_MXA__CLUxA15,
} CLUxMX_MXA_TypeDef;

typedef enum
{
    CLUx_INPUT_MXB_00 = CLUxMX_MXB__CLUxB0,
    CLUx_INPUT_MXB_01 = CLUxMX_MXB__CLUxB1,
    CLUx_INPUT_MXB_02 = CLUxMX_MXB__CLUxB2,
    CLUx_INPUT_MXB_03 = CLUxMX_MXB__CLUxB3,
    CLUx_INPUT_MXB_04 = CLUxMX_MXB__CLUxB4,
    CLUx_INPUT_MXB_05 = CLUxMX_MXB__CLUxB5,
    CLUx_INPUT_MXB_06 = CLUxMX_MXB__CLUxB6,
    CLUx_INPUT_MXB_07 = CLUxMX_MXB__CLUxB7,
    CLUx_INPUT_MXB_08 = CLUxMX_MXB__CLUxB8,
    CLUx_INPUT_MXB_09 = CLUxMX_MXB__CLUxB9,
    CLUx_INPUT_MXB_10 = CLUxMX_MXB__CLUxB10,
    CLUx_INPUT_MXB_11 = CLUxMX_MXB__CLUxB11,
    CLUx_INPUT_MXB_12 = CLUxMX_MXB__CLUxB12,
    CLUx_INPUT_MXB_13 = CLUxMX_MXB__CLUxB13,
    CLUx_INPUT_MXB_14 = CLUxMX_MXB__CLUxB14,
    CLUx_INPUT_MXB_15 = CLUxMX_MXB__CLUxB15,
} CLUxMX_MXB_TypeDef;

typedef enum
{
    CLUx_INPUT_MXC_00 = CLUxMX_MXC__CLUxC0,
    CLUx_INPUT_MXC_01 = CLUxMX_MXC__CLUxC1,
    CLUx_INPUT_MXC_02 = CLUxMX_MXC__CLUxC2,
    CLUx_INPUT_MXC_03 = CLUxMX_MXC__CLUxC3,
    CLUx_INPUT_MXC_04 = CLUxMX_MXC__CLUxC4,
    CLUx_INPUT_MXC_05 = CLUxMX_MXC__CLUxC5,
    CLUx_INPUT_MXC_06 = CLUxMX_MXC__CLUxC6,
    CLUx_INPUT_MXC_07 = CLUxMX_MXC__CLUxC7,
    CLUx_INPUT_MXC_08 = CLUxMX_MXC__CLUxC8,
    CLUx_INPUT_MXC_09 = CLUxMX_MXC__CLUxC9,
    CLUx_INPUT_MXC_10 = CLUxMX_MXC__CLUxC10,
    CLUx_INPUT_MXC_11 = CLUxMX_MXC__CLUxC11,
    CLUx_INPUT_MXC_12 = CLUxMX_MXC__CLUxC12,
    CLUx_INPUT_MXC_13 = CLUxMX_MXC__CLUxC13,
    CLUx_INPUT_MXC_14 = CLUxMX_MXC__CLUxC14,
    CLUx_INPUT_MXC_15 = CLUxMX_MXC__CLUxC15,
} CLUxMX_MXC_TypeDef;

typedef enum
{
    CLUx_INPUT_MXD_00 = CLUxMX_MXD__CLUxD0,
    CLUx_INPUT_MXD_01 = CLUxMX_MXD__CLUxD1,
    CLUx_INPUT_MXD_02 = CLUxMX_MXD__CLUxD2,
    CLUx_INPUT_MXD_03 = CLUxMX_MXD__CLUxD3,
    CLUx_INPUT_MXD_04 = CLUxMX_MXD__CLUxD4,
    CLUx_INPUT_MXD_05 = CLUxMX_MXD__CLUxD5,
    CLUx_INPUT_MXD_06 = CLUxMX_MXD__CLUxD6,
    CLUx_INPUT_MXD_07 = CLUxMX_MXD__CLUxD7,
    CLUx_INPUT_MXD_08 = CLUxMX_MXD__CLUxD8,
    CLUx_INPUT_MXD_09 = CLUxMX_MXD__CLUxD9,
    CLUx_INPUT_MXD_10 = CLUxMX_MXD__CLUxD10,
    CLUx_INPUT_MXD_11 = CLUxMX_MXD__CLUxD11,
    CLUx_INPUT_MXD_12 = CLUxMX_MXD__CLUxD12,
    CLUx_INPUT_MXD_13 = CLUxMX_MXD__CLUxD13,
    CLUx_INPUT_MXD_14 = CLUxMX_MXD__CLUxD14,
    CLUx_INPUT_MXD_15 = CLUxMX_MXD__CLUxD15,
} CLUxMX_MXD_TypeDef;

#define IS_CLUxMX_MXA_SELECTION(MXASELECTION) (((MXASELECTION) == CLUxMX_MXA__CLUxA0 ) || \
                                               ((MXASELECTION) == CLUxMX_MXA__CLUxA1 ) || \
                                               ((MXASELECTION) == CLUxMX_MXA__CLUxA2 ) || \
                                               ((MXASELECTION) == CLUxMX_MXA__CLUxA3 ) || \
                                               ((MXASELECTION) == CLUxMX_MXA__CLUxA4 ) || \
                                               ((MXASELECTION) == CLUxMX_MXA__CLUxA5 ) || \
                                               ((MXASELECTION) == CLUxMX_MXA__CLUxA6 ) || \
                                               ((MXASELECTION) == CLUxMX_MXA__CLUxA7 ) || \
                                               ((MXASELECTION) == CLUxMX_MXA__CLUxA8 ) || \
                                               ((MXASELECTION) == CLUxMX_MXA__CLUxA9 ) || \
                                               ((MXASELECTION) == CLUxMX_MXA__CLUxA10) || \
                                               ((MXASELECTION) == CLUxMX_MXA__CLUxA11) || \
                                               ((MXASELECTION) == CLUxMX_MXA__CLUxA12) || \
                                               ((MXASELECTION) == CLUxMX_MXA__CLUxA13) || \
                                               ((MXASELECTION) == CLUxMX_MXA__CLUxA14) || \
                                               ((MXASELECTION) == CLUxMX_MXA__CLUxA15) )

#define IS_CLUxMX_MXB_SELECTION(MXBSELECTION) (((MXBSELECTION) == CLUxMX_MXB__CLUxB0 ) || \
                                               ((MXBSELECTION) == CLUxMX_MXB__CLUxB1 ) || \
                                               ((MXBSELECTION) == CLUxMX_MXB__CLUxB2 ) || \
                                               ((MXBSELECTION) == CLUxMX_MXB__CLUxB3 ) || \
                                               ((MXBSELECTION) == CLUxMX_MXB__CLUxB4 ) || \
                                               ((MXBSELECTION) == CLUxMX_MXB__CLUxB5 ) || \
                                               ((MXBSELECTION) == CLUxMX_MXB__CLUxB6 ) || \
                                               ((MXBSELECTION) == CLUxMX_MXB__CLUxB7 ) || \
                                               ((MXBSELECTION) == CLUxMX_MXB__CLUxB8 ) || \
                                               ((MXBSELECTION) == CLUxMX_MXB__CLUxB9 ) || \
                                               ((MXBSELECTION) == CLUxMX_MXB__CLUxB10) || \
                                               ((MXBSELECTION) == CLUxMX_MXB__CLUxB11) || \
                                               ((MXBSELECTION) == CLUxMX_MXB__CLUxB12) || \
                                               ((MXBSELECTION) == CLUxMX_MXB__CLUxB13) || \
                                               ((MXBSELECTION) == CLUxMX_MXB__CLUxB14) || \
                                               ((MXBSELECTION) == CLUxMX_MXB__CLUxB15) )

#define IS_CLUxMX_MXC_SELECTION(MXCSELECTION) (((MXCSELECTION) == CLUxMX_MXC__CLUxC0 ) || \
                                               ((MXCSELECTION) == CLUxMX_MXC__CLUxC1 ) || \
                                               ((MXCSELECTION) == CLUxMX_MXC__CLUxC2 ) || \
                                               ((MXCSELECTION) == CLUxMX_MXC__CLUxC3 ) || \
                                               ((MXCSELECTION) == CLUxMX_MXC__CLUxC4 ) || \
                                               ((MXCSELECTION) == CLUxMX_MXC__CLUxC5 ) || \
                                               ((MXCSELECTION) == CLUxMX_MXC__CLUxC6 ) || \
                                               ((MXCSELECTION) == CLUxMX_MXC__CLUxC7 ) || \
                                               ((MXCSELECTION) == CLUxMX_MXC__CLUxC8 ) || \
                                               ((MXCSELECTION) == CLUxMX_MXC__CLUxC9 ) || \
                                               ((MXCSELECTION) == CLUxMX_MXC__CLUxC10) || \
                                               ((MXCSELECTION) == CLUxMX_MXC__CLUxC11) || \
                                               ((MXCSELECTION) == CLUxMX_MXC__CLUxC12) || \
                                               ((MXCSELECTION) == CLUxMX_MXC__CLUxC13) || \
                                               ((MXCSELECTION) == CLUxMX_MXC__CLUxC14) || \
                                               ((MXCSELECTION) == CLUxMX_MXC__CLUxC15) )

#define IS_CLUxMX_MXD_SELECTION(MXDSELECTION) (((MXDSELECTION) == CLUxMX_MXD__CLUxD0 ) || \
                                               ((MXDSELECTION) == CLUxMX_MXD__CLUxD1 ) || \
                                               ((MXDSELECTION) == CLUxMX_MXD__CLUxD2 ) || \
                                               ((MXDSELECTION) == CLUxMX_MXD__CLUxD3 ) || \
                                               ((MXDSELECTION) == CLUxMX_MXD__CLUxD4 ) || \
                                               ((MXDSELECTION) == CLUxMX_MXD__CLUxD5 ) || \
                                               ((MXDSELECTION) == CLUxMX_MXD__CLUxD6 ) || \
                                               ((MXDSELECTION) == CLUxMX_MXD__CLUxD7 ) || \
                                               ((MXDSELECTION) == CLUxMX_MXD__CLUxD8 ) || \
                                               ((MXDSELECTION) == CLUxMX_MXD__CLUxD9 ) || \
                                               ((MXDSELECTION) == CLUxMX_MXD__CLUxD10) || \
                                               ((MXDSELECTION) == CLUxMX_MXD__CLUxD11) || \
                                               ((MXDSELECTION) == CLUxMX_MXD__CLUxD12) || \
                                               ((MXDSELECTION) == CLUxMX_MXD__CLUxD13) || \
                                               ((MXDSELECTION) == CLUxMX_MXD__CLUxD14) || \
                                               ((MXDSELECTION) == CLUxMX_MXD__CLUxD15) )

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup CLU_Exported_Types  CLU Exported Types
  * @{
  */
/**
  * @brief  CLU Init structure definition
  */
typedef struct
{
    CLEN0_CEN_TypeDef CLU_Enable;

    /* Config CLU0 */
    CLUxMX_MXA_TypeDef CLU0_MXA;

    CLUxMX_MXB_TypeDef CLU0_MXB;

    CLUxMX_MXC_TypeDef CLU0_MXC;

    CLUxMX_MXD_TypeDef CLU0_MXD;

    CLUxFN_Function_TypeDef  CLU0_FN;

    CLUxCF_CLKSEL_TypeDef CLU0_ClkSel;

    CLUxCF_CLKINV_TypeDef CLU0_ClkInv;

    CLUxCF_OEN_TypeDef CLU0_PinOut;

    CLUxCF_OUTSEL_TypeDef CLU0_OutSel;

    /* Config CLU1 */
    CLUxMX_MXA_TypeDef CLU1_MXA;

    CLUxMX_MXB_TypeDef CLU1_MXB;

    CLUxMX_MXC_TypeDef CLU1_MXC;

    CLUxMX_MXD_TypeDef CLU1_MXD;

    CLUxFN_Function_TypeDef  CLU1_FN;

    CLUxCF_CLKSEL_TypeDef CLU1_ClkSel;

    CLUxCF_CLKINV_TypeDef CLU1_ClkInv;

    CLUxCF_OEN_TypeDef CLU1_PinOut;

    CLUxCF_OUTSEL_TypeDef CLU1_OutSel;

    /* Config CLU2 */
    CLUxMX_MXA_TypeDef CLU2_MXA;

    CLUxMX_MXB_TypeDef CLU2_MXB;

    CLUxMX_MXC_TypeDef CLU2_MXC;

    CLUxMX_MXD_TypeDef CLU2_MXD;

    CLUxFN_Function_TypeDef  CLU2_FN;

    CLUxCF_CLKSEL_TypeDef CLU2_ClkSel;

    CLUxCF_CLKINV_TypeDef CLU2_ClkInv;

    CLUxCF_OEN_TypeDef CLU2_PinOut;

    CLUxCF_OUTSEL_TypeDef CLU2_OutSel;

    /* Config CLU3 */
    CLUxMX_MXA_TypeDef CLU3_MXA;

    CLUxMX_MXB_TypeDef CLU3_MXB;

    CLUxMX_MXC_TypeDef CLU3_MXC;

    CLUxMX_MXD_TypeDef CLU3_MXD;

    CLUxFN_Function_TypeDef  CLU3_FN;

    CLUxCF_CLKSEL_TypeDef CLU3_ClkSel;

    CLUxCF_CLKINV_TypeDef CLU3_ClkInv;

    CLUxCF_OEN_TypeDef CLU3_PinOut;

    CLUxCF_OUTSEL_TypeDef CLU3_OutSel;

} CLU_InitTypeDef;
/**
  * @}
  */

/** @defgroup CLU_Exported_Special_Functions  CLU Exported Special Functions
  * @{
  */
#define CLU_FUNCTION_A_INPUT_TRUE       0xFFFF0000            // MXA channel
#define CLU_FUNCTION_B_INPUT_TRUE       0xFF00FF00            // MXB channel
#define CLU_FUNCTION_C_INPUT_TRUE       0xF0F0F0F0            // MXC channel
#define CLU_FUNCTION_D_INPUT_TRUE       0xCCCCCCCC            // MXD channel
#define CLU_FUNCTION_E_INPUT_TRUE       0xAAAAAAAA            // Carry-in channel

#define CLU_FUNCTION_NOT(CLU_Input_x)                 ~(CLU_Input_x)
#define CLU_FUNCTION_AND(CLU_Input_x, CLU_Input_y)    ((CLU_Input_x)&(CLU_Input_y))
#define CLU_FUNCTION_OR(CLU_Input_x, CLU_Input_y)     ((CLU_Input_x)|(CLU_Input_y))
#define CLU_FUNCTION_NOR(CLU_Input_x, CLU_Input_y)    ~(CLU_FUNCTION_OR(CLU_Input_x,CLU_Input_y))
#define CLU_FUNCTION_NAND(CLU_Input_x, CLU_Input_y)   ~(CLU_FUNCTION_AND(CLU_Input_x,CLU_Input_y))
#define CLU_FUNCTION_XOR(CLU_Input_x, CLU_Input_y)    (CLU_FUNCTION_AND(CLU_FUNCTION_OR(CLU_Input_x,CLU_Input_y),~CLU_FUNCTION_AND(CLU_Input_x,CLU_Input_y)))
#define CLU_FUNCTION_XNOR(CLU_Input_x, CLU_Input_y)   ~(CLU_FUNCTION_XOR(CLU_Input_x,CLU_Input_y))
#define CLU_FUNCTION_SELECT(CLU_Input_x, CLU_Input_y, CLU_Input_sel)     (CLU_FUNCTION_OR(CLU_FUNCTION_AND(CLU_Input_x,CLU_Input_sel),CLU_FUNCTION_AND(CLU_Input_y,~(CLU_Input_sel))))

/**
  * @}
  */

/** @defgroup CLU_Exported_Functions  CLU Exported Functions
  * @{
  */
void CLU_Init(CLU_InitTypeDef* CLU_InitStruct);
void CLU0_MultiplexerInputConfig(uint32_t MultiplexerInputA, uint32_t MultiplexerInputB, uint32_t MultiplexerInputC, uint32_t MultiplexerInputD);
void CLU1_MultiplexerInputConfig(uint32_t MultiplexerInputA, uint32_t MultiplexerInputB, uint32_t MultiplexerInputC, uint32_t MultiplexerInputD);
void CLU2_MultiplexerInputConfig(uint32_t MultiplexerInputA, uint32_t MultiplexerInputB, uint32_t MultiplexerInputC, uint32_t MultiplexerInputD);
void CLU3_MultiplexerInputConfig(uint32_t MultiplexerInputA, uint32_t MultiplexerInputB, uint32_t MultiplexerInputC, uint32_t MultiplexerInputD);
void CLU_InputChannelEN(CLUx_Selecte_TypeDef CLUx, CLUxMX_InputChannel_Typedef inputchan, FunctionalState NewState);
void CLU_InitDFlipflop(CLUx_Selecte_TypeDef CLUx, CLUxCF_CLKSEL_TypeDef clock, CLUxCF_CLKINV_TypeDef clockInvert);
void CLU_ResetDFlipflop(CLUx_Selecte_TypeDef CLUx);
void CLU_SetDFlipflop(CLUx_Selecte_TypeDef CLUx);
void CLU_SetOutputFunction(CLUx_Selecte_TypeDef CLUx, CLUxFN_Function_TypeDef function);
void CLU_Cmd(CLUx_Selecte_TypeDef CLUx, FunctionalState NewState);
void CLU_OutputSelection(CLUx_Selecte_TypeDef CLUx, CLUxCF_OUTSEL_TypeDef OutSel);
void CLU_EnablePinOutput(CLUx_Selecte_TypeDef CLUx, CLUxCF_OEN_TypeDef PinOut);
void CLU_TriggADCToWork(CLUx_Selecte_TypeDef CLUx);
void CLU_TriggDACToWork(CLUx_Selecte_TypeDef CLUx);
FlagStatus CLU_GetOutput(CLUx_Selecte_TypeDef CLUx);
/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_CLU_H */


