/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_dma.h
* @brief:     hk32l0xx_dma configuration file.
*             The file is the unique include file that the application programmer
*             is using in the C source code, it is a patch file.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_DMA_H
#define __HK32L0XX_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"


/** @addtogroup DMA DMA
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/** @defgroup DMA_Exported_Types DMA_Exported_Types
  * @{
  */

/**
  * @brief  DMA Init structures definition
  */
typedef struct
{
    uint32_t DMA_PeripheralBaseAddr; /*!< Specifies the peripheral base address for DMAy Channelx.              */

    uint32_t DMA_MemoryBaseAddr;     /*!< Specifies the memory base address for DMAy Channelx.                  */

    uint32_t DMA_DIR;                /*!< Specifies if the peripheral is the source or destination.
                                        This parameter can be a value of @ref DMA_data_transfer_direction     */

    uint32_t DMA_BufferSize;         /*!< Specifies the buffer size, in data unit, of the specified Channel.
                                        The data unit is equal to the configuration set in DMA_PeripheralDataSize
                                        or DMA_MemoryDataSize members depending in the transfer direction     */

    uint32_t DMA_PeripheralInc;      /*!< Specifies whether the Peripheral address register is incremented or not.
                                        This parameter can be a value of @ref DMA_peripheral_incremented_mode */

    uint32_t DMA_MemoryInc;          /*!< Specifies whether the memory address register is incremented or not.
                                        This parameter can be a value of @ref DMA_memory_incremented_mode     */

    uint32_t DMA_PeripheralDataSize; /*!< Specifies the Peripheral data width.
                                        This parameter can be a value of @ref DMA_peripheral_data_size        */

    uint32_t DMA_MemoryDataSize;     /*!< Specifies the Memory data width.
                                        This parameter can be a value of @ref DMA_memory_data_size            */

    uint32_t DMA_Mode;               /*!< Specifies the operation mode of the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_circular_normal_mode
                                        @note: The circular buffer mode cannot be used if the memory-to-memory
                                              data transfer is configured on the selected Channel */

    uint32_t DMA_Priority;           /*!< Specifies the software priority for the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_priority_level              */

    uint32_t DMA_M2M;                /*!< Specifies if the DMAy Channelx will be used in memory-to-memory transfer.
                                        This parameter can be a value of @ref DMA_memory_to_memory            */
} DMA_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA_Exported_Constants DMA_Exported_Constants
  * @{
  */
/**
  * @brief  DMA peripheral channel check
  */
#define IS_DMA_ALL_PERIPH(PERIPH) (((PERIPH) == DMA_Channel1) || \
                                   ((PERIPH) == DMA_Channel2) || \
                                   ((PERIPH) == DMA_Channel3) || \
                                   ((PERIPH) == DMA_Channel4) || \
                                   ((PERIPH) == DMA_Channel5) || \
                                   ((PERIPH) == DMA_Channel6) || \
                                   ((PERIPH) == DMA_Channel7))

/** @defgroup DMA_data_transfer_direction DMA_data_transfer_direction
  * @{
  */

#define DMA_DIR_PeripheralSRC              ((uint32_t)0x00000000)
#define DMA_DIR_PeripheralDST              DMA_Channel_CHCR_DIR

#define IS_DMA_DIR(DIR) (((DIR) == DMA_DIR_PeripheralSRC) || \
                         ((DIR) == DMA_DIR_PeripheralDST))
/**
  * @}
  */

/** @defgroup DMA_peripheral_incremented_mode DMA_peripheral_incremented_mode
  * @{
  */

#define DMA_PeripheralInc_Disable          ((uint32_t)0x00000000)
#define DMA_PeripheralInc_Enable           DMA_Channel_CHCR_PINC

#define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PeripheralInc_Disable) || \
                                            ((STATE) == DMA_PeripheralInc_Enable))
/**
  * @}
  */

/** @defgroup DMA_memory_incremented_mode DMA_memory_incremented_mode
  * @{
  */

#define DMA_MemoryInc_Disable              ((uint32_t)0x00000000)
#define DMA_MemoryInc_Enable               DMA_Channel_CHCR_MINC

#define IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MemoryInc_Disable) || \
                                        ((STATE) == DMA_MemoryInc_Enable))
/**
  * @}
  */

/** @defgroup DMA_peripheral_data_size DMA_peripheral_data_size
  * @{
  */

#define DMA_PeripheralDataSize_Byte        ((uint32_t)0x00000000)
#define DMA_PeripheralDataSize_HalfWord    DMA_Channel_CHCR_PSIZE_0
#define DMA_PeripheralDataSize_Word        DMA_Channel_CHCR_PSIZE_1

#define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE) (((SIZE) == DMA_PeripheralDataSize_Byte) || \
                                           ((SIZE) == DMA_PeripheralDataSize_HalfWord) || \
                                           ((SIZE) == DMA_PeripheralDataSize_Word))
/**
  * @}
  */

/** @defgroup DMA_memory_data_size DMA_memory_data_size
  * @{
  */

#define DMA_MemoryDataSize_Byte            ((uint32_t)0x00000000)
#define DMA_MemoryDataSize_HalfWord        DMA_Channel_CHCR_MSIZE_0
#define DMA_MemoryDataSize_Word            DMA_Channel_CHCR_MSIZE_1

#define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MemoryDataSize_Byte) || \
                                       ((SIZE) == DMA_MemoryDataSize_HalfWord) || \
                                       ((SIZE) == DMA_MemoryDataSize_Word))
/**
  * @}
  */

/** @defgroup DMA_circular_normal_mode DMA_circular_normal_mode
  * @{
  */

#define DMA_Mode_Normal                    ((uint32_t)0x00000000)
#define DMA_Mode_Circular                  DMA_Channel_CHCR_CIRC

#define IS_DMA_MODE(MODE) (((MODE) == DMA_Mode_Normal) || ((MODE) == DMA_Mode_Circular))
/**
  * @}
  */

/** @defgroup DMA_priority_level DMA_priority_level
  * @{
  */

#define DMA_Priority_VeryHigh              DMA_Channel_CHCR_PL
#define DMA_Priority_High                  DMA_Channel_CHCR_PL_1
#define DMA_Priority_Medium                DMA_Channel_CHCR_PL_0
#define DMA_Priority_Low                   ((uint32_t)0x00000000)

#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_Priority_VeryHigh) || \
                                   ((PRIORITY) == DMA_Priority_High) || \
                                   ((PRIORITY) == DMA_Priority_Medium) || \
                                   ((PRIORITY) == DMA_Priority_Low))
/**
  * @}
  */

/** @defgroup DMA_memory_to_memory DMA_memory_to_memory
  * @{
  */

#define DMA_M2M_Disable                    ((uint32_t)0x00000000)
#define DMA_M2M_Enable                     DMA_Channel_CHCR_MEM2MEM

#define IS_DMA_M2M_STATE(STATE) (((STATE) == DMA_M2M_Disable) || ((STATE) == DMA_M2M_Enable))

/**
  * @}
  */

/** @defgroup DMA_Remap_Config DMA_Remap_Config
  * @{
  */
#define DMAx_CHANNEL1_RMP                                     0x00000000
#define DMAx_CHANNEL2_RMP                                     0x10000000
#define DMAx_CHANNEL3_RMP                                     0x20000000
#define DMAx_CHANNEL4_RMP                                     0x30000000
#define DMAx_CHANNEL5_RMP                                     0x40000000
#define DMAx_CHANNEL6_RMP                                     0x50000000
#define DMAx_CHANNEL7_RMP                                     0x60000000

/******************  Bit definition for DMA_CSELR register  ********************/
#define DMA_CSELR_CH1_ADC                  ((uint32_t)(DMAx_CHANNEL1_RMP | 0x00000000))        /*!< Remap ADC on DMA1 channel 1 */
#define DMA_CSELR_CH1_TIM2_CH3             ((uint32_t)(DMAx_CHANNEL1_RMP | 0x00000007))        /*!< Remap TIM2 CH3 on DMA1 channel 1 */
#define DMA_CSELR_CH1_AES_IN               ((uint32_t)(DMAx_CHANNEL1_RMP | 0x0000000A))        /*!< Remap AES IN on DMA1 channel 1 */
#define DMA_CSELR_CH1_TIM1_CH1             ((uint32_t)(DMAx_CHANNEL1_RMP | 0x0000000D))        /*!< Remap TIM1 CH1 on DMA1 channel 1 */
#define DMA_CSELR_CH1_TIM17_CH1            ((uint32_t)(DMAx_CHANNEL1_RMP | 0x0000000F))        /*!< Remap TIM17 CH1 on DMA1 channel 1 */

#define DMA_CSELR_CH2_ADC                  ((uint32_t)(DMAx_CHANNEL2_RMP | 0x00000000))        /*!< Remap ADC on DMA1 channel 2 */
#define DMA_CSELR_CH2_SPI1_RX              ((uint32_t)(DMAx_CHANNEL2_RMP | 0x00000010))        /*!< Remap SPI1 RX on DMA1 channel 2 */
#define DMA_CSELR_CH2_USART1_TX            ((uint32_t)(DMAx_CHANNEL2_RMP | 0x00000020))        /*!< Remap USART1 TX on DMA1 channel 2 */
#define DMA_CSELR_CH2_LPUART1_TX           ((uint32_t)(DMAx_CHANNEL2_RMP | 0x00000040))        /*!< Remap LPUART1 TX on DMA1 channel 2 */
#define DMA_CSELR_CH2_I2C1_TX              ((uint32_t)(DMAx_CHANNEL2_RMP | 0x00000050))        /*!< Remap I2C1 TX on DMA1 channel 2 */
#define DMA_CSELR_CH2_TIM2_UP              ((uint32_t)(DMAx_CHANNEL2_RMP | 0x00000070))        /*!< Remap TIM2 UP on DMA1 channel 2 */
#define DMA_CSELR_CH2_DAC_CH1              ((uint32_t)(DMAx_CHANNEL2_RMP | 0x00000080))        /*!< Remap DAC CH1 on DMA1 channel 2 */
#define DMA_CSELR_CH2_TIM3_CH3             ((uint32_t)(DMAx_CHANNEL2_RMP | 0x00000090))        /*!< Remap TIM3 CH3 on DMA1 channel 2 */
#define DMA_CSELR_CH2_AES_OUT              ((uint32_t)(DMAx_CHANNEL2_RMP | 0x000000A0))        /*!< Remap AES OUT on DMA1 channel 2 */
#define DMA_CSELR_CH2_UART3_RX             ((uint32_t)(DMAx_CHANNEL2_RMP | 0x000000B0))        /*!< Remap UART3_RX on DMA1 channel 2 */
#define DMA_CSELR_CH2_UART4_RX             ((uint32_t)(DMAx_CHANNEL2_RMP | 0x000000C0))        /*!< Remap UART4 RX on DMA1 channel 2 */
#define DMA_CSELR_CH2_TIM1_CH2             ((uint32_t)(DMAx_CHANNEL2_RMP | 0x000000D0))        /*!< Remap TIM1 CH2 on DMA1 channel 2 */
#define DMA_CSELR_CH2_TIM17_UP             ((uint32_t)(DMAx_CHANNEL2_RMP | 0x000000F0))        /*!< Remap TIM17 UP on DMA1 channel 2 */

#define DMA_CSELR_CH3_SPI1_TX              ((uint32_t)(DMAx_CHANNEL3_RMP | 0x00000100))        /*!< Remap SPI1 TX on DMA1 channel 3 */
#define DMA_CSELR_CH3_USART1_RX            ((uint32_t)(DMAx_CHANNEL3_RMP | 0x00000200))        /*!< Remap USART1_RX on DMA1 channel 3 */
#define DMA_CSELR_CH3_LPUART1_RX           ((uint32_t)(DMAx_CHANNEL3_RMP | 0x00000400))        /*!< Remap LPUART1_RX on DMA1 channel 3 */
#define DMA_CSELR_CH3_I2C1_RX              ((uint32_t)(DMAx_CHANNEL3_RMP | 0x00000500))        /*!< Remap I2C1 RX on DMA1 channel 3 */
#define DMA_CSELR_CH3_TIM2_CH2             ((uint32_t)(DMAx_CHANNEL3_RMP | 0x00000700))        /*!< Remap TIM2 CH2 on DMA1 channel 3 */
#define DMA_CSELR_CH3_TIM3_CH4_TIM3_UP     ((uint32_t)(DMAx_CHANNEL3_RMP | 0x00000900))        /*!< Remap TIM3 CH4 or TIM3_UP on DMA1 channel 3 */
#define DMA_CSELR_CH3_AES_OUT              ((uint32_t)(DMAx_CHANNEL3_RMP | 0x00000A00))        /*!< Remap AES OUT on DMA1 channel 3 */
#define DMA_CSELR_CH3_UART3_TX             ((uint32_t)(DMAx_CHANNEL3_RMP | 0x00000B00))        /*!< Remap UART3 TX on DMA1 channel 3 */
#define DMA_CSELR_CH3_UART4_TX             ((uint32_t)(DMAx_CHANNEL3_RMP | 0x00000C00))        /*!< Remap UART4 TX on DMA1 channel 3 */
#define DMA_CSELR_CH3_TIM1_CH3             ((uint32_t)(DMAx_CHANNEL3_RMP | 0x00000D00))        /*!< Remap TIM1 CH3 on DMA1 channel 3 */
#define DMA_CSELR_CH3_TIM17_CH1            ((uint32_t)(DMAx_CHANNEL3_RMP | 0x00000F00))        /*!< Remap TIM17 CH1 on DMA1 channel 3 */

#define DMA_CSELR_CH4_SPI2_RX              ((uint32_t)(DMAx_CHANNEL4_RMP | 0x00001000))        /*!< Remap SPI2 RX on DMA1 channel 4 */
#define DMA_CSELR_CH4_USART1_TX            ((uint32_t)(DMAx_CHANNEL4_RMP | 0x00002000))        /*!< Remap USART1 TX on DMA1 channel 4 */
#define DMA_CSELR_CH4_USART2_TX            ((uint32_t)(DMAx_CHANNEL4_RMP | 0x00003000))        /*!< Remap USART2 TX on DMA1 channel 4 */
#define DMA_CSELR_CH4_I2C2_TX              ((uint32_t)(DMAx_CHANNEL4_RMP | 0x00006000))        /*!< Remap I2C2 TX on DMA1 channel 4 */
#define DMA_CSELR_CH4_TIM2_CH4             ((uint32_t)(DMAx_CHANNEL4_RMP | 0x00007000))        /*!< Remap TIM2 CH4 on DMA1 channel 4 */
#define DMA_CSELR_CH4_TIM1_CH4             ((uint32_t)(DMAx_CHANNEL4_RMP | 0x0000D000))        /*!< Remap TIM1 CH4 on DMA1 channel 4 */
#define DMA_CSELR_CH4_TIM16_CH1            ((uint32_t)(DMAx_CHANNEL4_RMP | 0x0000E000))        /*!< Remap TIM16 CH1 on DMA1 channel 4 */
#define DMA_CSELR_CH4_TIM17_UP             ((uint32_t)(DMAx_CHANNEL4_RMP | 0x0000F000))        /*!< Remap TIM17 UP on DMA1 channel 4 */

#define DMA_CSELR_CH5_SPI2_TX              ((uint32_t)(DMAx_CHANNEL5_RMP | 0x00010000))        /*!< Remap SPI2 TX on DMA1 channel 5 */
#define DMA_CSELR_CH5_USART1_RX            ((uint32_t)(DMAx_CHANNEL5_RMP | 0x00020000))        /*!< Remap USART1 RX on DMA1 channel 5 */
#define DMA_CSELR_CH5_USART2_RX            ((uint32_t)(DMAx_CHANNEL5_RMP | 0x00030000))        /*!< Remap USART2 RX on DMA1 channel 5 */
#define DMA_CSELR_CH5_I2C2_RX              ((uint32_t)(DMAx_CHANNEL5_RMP | 0x00060000))        /*!< Remap I2C2 RX on DMA1 channel 5 */
#define DMA_CSELR_CH5_TIM2_CH1             ((uint32_t)(DMAx_CHANNEL5_RMP | 0x00070000))        /*!< Remap TIM2 CH1 on DMA1 channel 5 */
#define DMA_CSELR_CH5_TIM3_CH1             ((uint32_t)(DMAx_CHANNEL5_RMP | 0x00090000))        /*!< Remap TIM3 CH1 on DMA1 channel 5 */
#define DMA_CSELR_CH5_AES_IN               ((uint32_t)(DMAx_CHANNEL5_RMP | 0x000A0000))        /*!< Remap AES IN on DMA1 channel 5 */
#define DMA_CSELR_CH5_TIM1_UP              ((uint32_t)(DMAx_CHANNEL5_RMP | 0x000D0000))        /*!< Remap TIM1 UP on DMA1 channel 5 */
#define DMA_CSELR_CH5_TIM16_UP             ((uint32_t)(DMAx_CHANNEL5_RMP | 0x000E0000))        /*!< Remap TIM16 UP on DMA1 channel 5 */

#define DMA_CSELR_CH6_SPI2_RX              ((uint32_t)(DMAx_CHANNEL6_RMP | 0x00100000))        /*!< Remap SPI2 RX on DMA1 channel 6 */
#define DMA_CSELR_CH6_USART2_RX            ((uint32_t)(DMAx_CHANNEL6_RMP | 0x00300000))        /*!< Remap USART2 RX on DMA1 channel 6 */
#define DMA_CSELR_CH6_LPUART1_RX           ((uint32_t)(DMAx_CHANNEL6_RMP | 0x00400000))        /*!< Remap LPUART1_RX on DMA1 channel 6 */
#define DMA_CSELR_CH6_I2C1_TX              ((uint32_t)(DMAx_CHANNEL6_RMP | 0x00500000))        /*!< Remap I2C1 TX on DMA1 channel 6 */
#define DMA_CSELR_CH6_TIM3_TRIG            ((uint32_t)(DMAx_CHANNEL6_RMP | 0x00900000))        /*!< Remap TIM3 TRIG on DMA1 channel 6 */
#define DMA_CSELR_CH6_UART3_RX             ((uint32_t)(DMAx_CHANNEL6_RMP | 0x00B00000))        /*!< Remap UART3 RX on DMA1 channel 6 */
#define DMA_CSELR_CH6_UART4_RX             ((uint32_t)(DMAx_CHANNEL6_RMP | 0x00C00000))        /*!< Remap UART4_RX on DMA1 channel 6 */
#define DMA_CSELR_CH6_TIM1_COM             ((uint32_t)(DMAx_CHANNEL6_RMP | 0x00D00000))        /*!< Remap UART4_RX on DMA1 channel 6 */
#define DMA_CSELR_CH6_TIM16_CH1            ((uint32_t)(DMAx_CHANNEL6_RMP | 0x00E00000))        /*!< Remap TIM16 CH1 on DMA1 channel 6 */

#define DMA_CSELR_CH7_SPI2_TX              ((uint32_t)(DMAx_CHANNEL7_RMP | 0x01000000))        /*!< Remap SPI2 TX on DMA1 channel 7 */
#define DMA_CSELR_CH7_USART2_TX            ((uint32_t)(DMAx_CHANNEL7_RMP | 0x03000000))        /*!< Remap USART2 TX on DMA1 channel 7 */
#define DMA_CSELR_CH7_LPUART1_TX           ((uint32_t)(DMAx_CHANNEL7_RMP | 0x04000000))        /*!< Remap LPUART1 TX on DMA1 channel 7 */
#define DMA_CSELR_CH7_I2C1_RX              ((uint32_t)(DMAx_CHANNEL7_RMP | 0x05000000))        /*!< Remap I2C1 RX on DMA1 channel 7 */
#define DMA_CSELR_CH7_TIM2_CH2_TIM2_CH4    ((uint32_t)(DMAx_CHANNEL7_RMP | 0x07000000))        /*!< Remap TIM2_CH2 TIM2_CH4 on DMA1 channel 7 */
#define DMA_CSELR_CH7_UART3_TX             ((uint32_t)(DMAx_CHANNEL7_RMP | 0x0B000000))        /*!< Remap UART3 TX on DMA1 channel 7 */
#define DMA_CSELR_CH7_UART4_TX             ((uint32_t)(DMAx_CHANNEL7_RMP | 0x0C000000))        /*!< Remap UART4 TX on DMA1 channel 7 */
#define DMA_CSELR_CH7_TIM1_TRIG            ((uint32_t)(DMAx_CHANNEL7_RMP | 0x0D000000))        /*!< Remap TIM1 TRIG on DMA1 channel 7 */
#define DMA_CSELR_CH7_TIM16_UP             ((uint32_t)(DMAx_CHANNEL7_RMP | 0x0E000000))        /*!< Remap TIM16 UP on DMA1 channel 7 */


#define IS_DMA_ALL_LIST(LIST) ((LIST) == DMA)

#define IS_DMA1_REMAP(REMAP)                 (  (REMAP == DMA_CSELR_CH1_ADC)               || \
  (REMAP == DMA_CSELR_CH1_TIM2_CH3)         ||  (REMAP == DMA_CSELR_CH1_AES_IN)            || \
  (REMAP == DMA_CSELR_CH1_TIM1_CH1)         ||  (REMAP == DMA_CSELR_CH2_ADC)               || \
  (REMAP == DMA_CSELR_CH2_SPI1_RX)          ||  (REMAP == DMA_CSELR_CH2_USART1_TX)         || \
  (REMAP == DMA_CSELR_CH2_LPUART1_TX)       ||  (REMAP == DMA_CSELR_CH2_I2C1_TX)           || \
  (REMAP == DMA_CSELR_CH2_TIM2_UP)          ||  (REMAP == DMA_CSELR_CH2_DAC_CH1)           || \
  (REMAP == DMA_CSELR_CH2_TIM3_CH3)         ||  (REMAP == DMA_CSELR_CH2_AES_OUT)           || \
  (REMAP == DMA_CSELR_CH2_UART3_RX)         ||  (REMAP == DMA_CSELR_CH2_UART4_RX)          || \
  (REMAP == DMA_CSELR_CH2_TIM1_CH2)         ||  (REMAP == DMA_CSELR_CH2_UART4_RX)          || \
  (REMAP == DMA_CSELR_CH3_SPI1_TX)          ||  (REMAP == DMA_CSELR_CH3_USART1_RX)         || \
  (REMAP == DMA_CSELR_CH3_LPUART1_RX)       ||  (REMAP == DMA_CSELR_CH3_I2C1_RX)           || \
  (REMAP == DMA_CSELR_CH3_TIM2_CH2)         ||  (REMAP == DMA_CSELR_CH3_TIM3_CH4_TIM3_UP)  || \
  (REMAP == DMA_CSELR_CH3_AES_OUT)          ||  (REMAP == DMA_CSELR_CH3_UART3_TX)          || \
  (REMAP == DMA_CSELR_CH3_UART4_TX)         ||  (REMAP == DMA_CSELR_CH3_TIM1_CH3)          || \
  (REMAP == DMA_CSELR_CH4_SPI2_RX)          ||  (REMAP == DMA_CSELR_CH4_USART1_TX)         || \
  (REMAP == DMA_CSELR_CH4_USART2_TX)        ||  (REMAP == DMA_CSELR_CH4_I2C2_TX)           || \
  (REMAP == DMA_CSELR_CH4_TIM2_CH4)         ||  (REMAP == DMA_CSELR_CH4_TIM1_CH4)          || \
  (REMAP == DMA_CSELR_CH5_SPI2_TX)          ||  (REMAP == DMA_CSELR_CH5_USART1_RX)         || \
  (REMAP == DMA_CSELR_CH5_USART2_RX)        ||  (REMAP == DMA_CSELR_CH5_I2C2_RX)           || \
  (REMAP == DMA_CSELR_CH5_TIM2_CH1)         ||  (REMAP == DMA_CSELR_CH5_TIM3_CH1)          || \
  (REMAP == DMA_CSELR_CH5_AES_IN)           ||  (REMAP == DMA_CSELR_CH5_TIM1_UP)           || \
  (REMAP == DMA_CSELR_CH6_SPI2_RX)          ||  (REMAP == DMA_CSELR_CH6_USART2_RX)         || \
  (REMAP == DMA_CSELR_CH6_LPUART1_RX)       ||  (REMAP == DMA_CSELR_CH6_I2C1_TX)           || \
  (REMAP == DMA_CSELR_CH6_TIM3_TRIG)        ||  (REMAP == DMA_CSELR_CH6_UART3_RX)          || \
  (REMAP == DMA_CSELR_CH6_UART4_RX)         ||  (REMAP == DMA_CSELR_CH6_TIM1_COM)          || \
  (REMAP == DMA_CSELR_CH7_SPI2_TX)          ||  (REMAP == DMA_CSELR_CH7_USART2_TX)         || \
  (REMAP == DMA_CSELR_CH7_LPUART1_TX)       ||  (REMAP == DMA_CSELR_CH7_I2C1_RX)           || \
  (REMAP == DMA_CSELR_CH7_TIM2_CH2_TIM2_CH4)||  (REMAP == DMA_CSELR_CH7_UART3_TX)          || \
  (REMAP == DMA_CSELR_CH7_UART4_TX)         ||  (REMAP == DMA_CSELR_CH7_TIM1_TRIG)         || \
  (REMAP == DMA_CSELR_CH1_TIM17_CH1)        ||  (REMAP == DMA_CSELR_CH2_TIM17_UP)          || \
  (REMAP == DMA_CSELR_CH3_TIM17_CH1)        ||  (REMAP == DMA_CSELR_CH4_TIM16_CH1)         || \
  (REMAP == DMA_CSELR_CH4_TIM17_UP)         ||  (REMAP == DMA_CSELR_CH5_TIM16_UP)          || \
  (REMAP == DMA_CSELR_CH6_TIM16_CH1)        ||  (REMAP == DMA_CSELR_CH7_TIM16_UP))
/**
  * @}
  */

/** @defgroup DMA_interrupts_definition DMA_interrupts_definition
  * @{
  */

#define DMA_IT_TC                          DMA_Channel_CHCR_TCIE
#define DMA_IT_HT                          DMA_Channel_CHCR_HTIE
#define DMA_IT_TE                          DMA_Channel_CHCR_TEIE

#define IS_DMA_CONFIG_IT(IT) ((((IT) & 0xFFFFFFF1) == 0x00) && ((IT) != 0x00))

#define DMA1_IT_GL1                        DMA_ISR_GIF1
#define DMA1_IT_TC1                        DMA_ISR_TCIF1
#define DMA1_IT_HT1                        DMA_ISR_HTIF1
#define DMA1_IT_TE1                        DMA_ISR_TEIF1
#define DMA1_IT_GL2                        DMA_ISR_GIF2
#define DMA1_IT_TC2                        DMA_ISR_TCIF2
#define DMA1_IT_HT2                        DMA_ISR_HTIF2
#define DMA1_IT_TE2                        DMA_ISR_TEIF2
#define DMA1_IT_GL3                        DMA_ISR_GIF3
#define DMA1_IT_TC3                        DMA_ISR_TCIF3
#define DMA1_IT_HT3                        DMA_ISR_HTIF3
#define DMA1_IT_TE3                        DMA_ISR_TEIF3
#define DMA1_IT_GL4                        DMA_ISR_GIF4
#define DMA1_IT_TC4                        DMA_ISR_TCIF4
#define DMA1_IT_HT4                        DMA_ISR_HTIF4
#define DMA1_IT_TE4                        DMA_ISR_TEIF4
#define DMA1_IT_GL5                        DMA_ISR_GIF5
#define DMA1_IT_TC5                        DMA_ISR_TCIF5
#define DMA1_IT_HT5                        DMA_ISR_HTIF5
#define DMA1_IT_TE5                        DMA_ISR_TEIF5
#define DMA1_IT_GL6                        DMA_ISR_GIF6
#define DMA1_IT_TC6                        DMA_ISR_TCIF6
#define DMA1_IT_HT6                        DMA_ISR_HTIF6
#define DMA1_IT_TE6                        DMA_ISR_TEIF6
#define DMA1_IT_GL7                        DMA_ISR_GIF7
#define DMA1_IT_TC7                        DMA_ISR_TCIF7
#define DMA1_IT_HT7                        DMA_ISR_HTIF7
#define DMA1_IT_TE7                        DMA_ISR_TEIF7

#define IS_DMA_CLEAR_IT(IT) (((((IT) & 0xF0000000) == 0x00) || (((IT) & 0xEFF00000) == 0x00)) && ((IT) != 0x00))

#define IS_DMA_GET_IT(IT) (((IT) == DMA1_IT_GL1) || ((IT) == DMA1_IT_TC1) || \
                           ((IT) == DMA1_IT_HT1) || ((IT) == DMA1_IT_TE1) || \
                           ((IT) == DMA1_IT_GL2) || ((IT) == DMA1_IT_TC2) || \
                           ((IT) == DMA1_IT_HT2) || ((IT) == DMA1_IT_TE2) || \
                           ((IT) == DMA1_IT_GL3) || ((IT) == DMA1_IT_TC3) || \
                           ((IT) == DMA1_IT_HT3) || ((IT) == DMA1_IT_TE3) || \
                           ((IT) == DMA1_IT_GL4) || ((IT) == DMA1_IT_TC4) || \
                           ((IT) == DMA1_IT_HT4) || ((IT) == DMA1_IT_TE4) || \
                           ((IT) == DMA1_IT_GL5) || ((IT) == DMA1_IT_TC5) || \
                           ((IT) == DMA1_IT_HT5) || ((IT) == DMA1_IT_TE5) || \
                           ((IT) == DMA1_IT_GL6) || ((IT) == DMA1_IT_TC6) || \
                           ((IT) == DMA1_IT_HT6) || ((IT) == DMA1_IT_TE6) || \
                           ((IT) == DMA1_IT_GL7) || ((IT) == DMA1_IT_TC7) || \
                           ((IT) == DMA1_IT_HT7) || ((IT) == DMA1_IT_TE7))

/**
  * @}
  */

/** @defgroup DMA_flags_definition DMA_flags_definition
  * @{
  */
#define DMA1_FLAG_GL1                      DMA_ISR_GIF1
#define DMA1_FLAG_TC1                      DMA_ISR_TCIF1
#define DMA1_FLAG_HT1                      DMA_ISR_HTIF1
#define DMA1_FLAG_TE1                      DMA_ISR_TEIF1
#define DMA1_FLAG_GL2                      DMA_ISR_GIF2
#define DMA1_FLAG_TC2                      DMA_ISR_TCIF2
#define DMA1_FLAG_HT2                      DMA_ISR_HTIF2
#define DMA1_FLAG_TE2                      DMA_ISR_TEIF2
#define DMA1_FLAG_GL3                      DMA_ISR_GIF3
#define DMA1_FLAG_TC3                      DMA_ISR_TCIF3
#define DMA1_FLAG_HT3                      DMA_ISR_HTIF3
#define DMA1_FLAG_TE3                      DMA_ISR_TEIF3
#define DMA1_FLAG_GL4                      DMA_ISR_GIF4
#define DMA1_FLAG_TC4                      DMA_ISR_TCIF4
#define DMA1_FLAG_HT4                      DMA_ISR_HTIF4
#define DMA1_FLAG_TE4                      DMA_ISR_TEIF4
#define DMA1_FLAG_GL5                      DMA_ISR_GIF5
#define DMA1_FLAG_TC5                      DMA_ISR_TCIF5
#define DMA1_FLAG_HT5                      DMA_ISR_HTIF5
#define DMA1_FLAG_TE5                      DMA_ISR_TEIF5
#define DMA1_FLAG_GL6                      DMA_ISR_GIF6
#define DMA1_FLAG_TC6                      DMA_ISR_TCIF6
#define DMA1_FLAG_HT6                      DMA_ISR_HTIF6
#define DMA1_FLAG_TE6                      DMA_ISR_TEIF6
#define DMA1_FLAG_GL7                      DMA_ISR_GIF7
#define DMA1_FLAG_TC7                      DMA_ISR_TCIF7
#define DMA1_FLAG_HT7                      DMA_ISR_HTIF7
#define DMA1_FLAG_TE7                      DMA_ISR_TEIF7

#define IS_DMA_CLEAR_FLAG(FLAG) (((((FLAG) & 0xF0000000) == 0x00) || (((FLAG) & 0xEFF00000) == 0x00)) && ((FLAG) != 0x00))

#define IS_DMA_GET_FLAG(FLAG) (((FLAG) == DMA1_FLAG_GL1) || ((FLAG) == DMA1_FLAG_TC1) || \
                               ((FLAG) == DMA1_FLAG_HT1) || ((FLAG) == DMA1_FLAG_TE1) || \
                               ((FLAG) == DMA1_FLAG_GL2) || ((FLAG) == DMA1_FLAG_TC2) || \
                               ((FLAG) == DMA1_FLAG_HT2) || ((FLAG) == DMA1_FLAG_TE2) || \
                               ((FLAG) == DMA1_FLAG_GL3) || ((FLAG) == DMA1_FLAG_TC3) || \
                               ((FLAG) == DMA1_FLAG_HT3) || ((FLAG) == DMA1_FLAG_TE3) || \
                               ((FLAG) == DMA1_FLAG_GL4) || ((FLAG) == DMA1_FLAG_TC4) || \
                               ((FLAG) == DMA1_FLAG_HT4) || ((FLAG) == DMA1_FLAG_TE4) || \
                               ((FLAG) == DMA1_FLAG_GL5) || ((FLAG) == DMA1_FLAG_TC5) || \
                               ((FLAG) == DMA1_FLAG_HT5) || ((FLAG) == DMA1_FLAG_TE5) || \
                               ((FLAG) == DMA1_FLAG_GL6) || ((FLAG) == DMA1_FLAG_TC6) || \
                               ((FLAG) == DMA1_FLAG_HT6) || ((FLAG) == DMA1_FLAG_TE6) || \
                               ((FLAG) == DMA1_FLAG_GL7) || ((FLAG) == DMA1_FLAG_TC7) || \
                               ((FLAG) == DMA1_FLAG_HT7) || ((FLAG) == DMA1_FLAG_TE7))
/**
  * @}
  */

/** @defgroup DMA_Buffer_Size DMA_Buffer_Size
  * @{
  */

#define IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x1) && ((SIZE) < 0x10000))

/**
  * @}
  */

/**
  * @}
  */



/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/** @defgroup DMA_Exported_Functions DMA_Exported_Functions
  * @{
  */

/* Function used to set the DMA configuration to the default reset state ******/
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);

/* Initialization and Configuration functions *********************************/
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);
void DMA_RemapConfig(DMA_TypeDef* DMAy, uint32_t DMAy_CHx_RemapRequest);

/* Data Counter functions******************************************************/
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t DataNumber);
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx);

/* Interrupts and flags management functions **********************************/
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState);
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG);
void DMA_ClearFlag(uint32_t DMAy_FLAG);
ITStatus DMA_GetITStatus(uint32_t DMAy_IT);
void DMA_ClearITPendingBit(uint32_t DMAy_IT);
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_DMA_H */

/***************************** (C) COPYRIGHT HKMicroChip  *******************************/

