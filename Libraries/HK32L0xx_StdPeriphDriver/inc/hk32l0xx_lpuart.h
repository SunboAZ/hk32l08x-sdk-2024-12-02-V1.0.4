/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_lpuart.h
* @brief:     API file of lpuart module
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_LPUART_H
#define __HK32L0XX_LPUART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"

#define IS_LPUART_PERIPH(PERIPH) (((PERIPH) == LPUART))

/** @addtogroup LPUART
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup LPUART_Exported_Types  LPUART_Exported_Types
  * @{
  */

typedef struct
{
    uint32_t LPUART_BaudRate;            /*!< This member configures the LPUART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (LPUART_InitStruct->LPUART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((uint32_t) IntegerDivider)) * 16) + 0.5 */

    uint32_t LPUART_WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref LPUART_Word_Length */

    uint32_t LPUART_StopBits;            /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref LPUART_Stop_Bits */

    uint32_t LPUART_Parity;              /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref LPUART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */

    uint32_t LPUART_Mode;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref LPUART_Mode */

    uint32_t LPUART_HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref LPUART_Hardware_Flow_Control*/
} LPUART_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** @defgroup LPUART_Exported_Constants   LPUART_Exported_Constants
  * @{
  */


/** @defgroup LPUART_Word_Length     LPUART_Word_Length
  * @{
  */

#define LPUART_WordLength_8b                  ((uint32_t)0x00000000)
#define LPUART_WordLength_9b                  LPUART_CR1_M0 /* should be ((uint32_t)0x00001000) */
#define LPUART_WordLength_7b                  LPUART_CR1_M1
#define IS_LPUART_WORD_LENGTH(LENGTH)         (((LENGTH) == LPUART_WordLength_8b) || \
                                              ((LENGTH) == LPUART_WordLength_9b) || \
                                              ((LENGTH) == LPUART_WordLength_7b))
/**
  * @}
  */

/** @defgroup LPUART_Stop_Bits    LPUART_Stop_Bits
  * @{
  */

#define LPUART_StopBits_1                     ((uint32_t)0x00000000)
#define LPUART_StopBits_2                     LPUART_CR2_STOP_1
#define IS_LPUART_STOPBITS(STOPBITS)          (((STOPBITS) == LPUART_StopBits_1) || \
                                              ((STOPBITS) == LPUART_StopBits_2))
/**
  * @}
  */

/** @defgroup LPUART_Parity   LPUART_Parity
  * @{
  */

#define LPUART_Parity_No                      ((uint32_t)0x00000000)
#define LPUART_Parity_Even                    LPUART_CR1_PCE
#define LPUART_Parity_Odd                     (LPUART_CR1_PCE | LPUART_CR1_PS)
#define IS_LPUART_PARITY(PARITY)              (((PARITY) == LPUART_Parity_No) || \
                                               ((PARITY) == LPUART_Parity_Even) || \
                                               ((PARITY) == LPUART_Parity_Odd))
/**
  * @}
  */

/** @defgroup LPUART_Mode    LPUART_Mode
  * @{
  */

#define LPUART_Mode_Rx                        LPUART_CR1_RE
#define LPUART_Mode_Tx                        LPUART_CR1_TE
#define IS_LPUART_MODE(MODE)                  ((((MODE) & (uint32_t)0xFFFFFFF3) == 0x00) && \
                                               ((MODE) != (uint32_t)0x00))
/**
  * @}
  */

/** @defgroup LPUART_Hardware_Flow_Control   LPUART_Hardware_Flow_Control
  * @{
  */

#define LPUART_HardwareFlowControl_None       ((uint32_t)0x00000000)
#define LPUART_HardwareFlowControl_RTS        LPUART_CR3_RTSE
#define LPUART_HardwareFlowControl_CTS        LPUART_CR3_CTSE
#define LPUART_HardwareFlowControl_RTS_CTS    (LPUART_CR3_RTSE | LPUART_CR3_CTSE)
#define IS_LPUART_HARDWARE_FLOW_CONTROL(CONTROL)\
                                              (((CONTROL) == LPUART_HardwareFlowControl_None) || \
                                               ((CONTROL) == LPUART_HardwareFlowControl_RTS) || \
                                               ((CONTROL) == LPUART_HardwareFlowControl_CTS) || \
                                               ((CONTROL) == LPUART_HardwareFlowControl_RTS_CTS))

/**
  * @}
  */

/** @defgroup LPUART_DMA_Requests   LPUART_DMA_Requests
  * @{
  */

#define LPUART_DMAReq_Tx                      LPUART_CR3_DMAT
#define LPUART_DMAReq_Rx                      LPUART_CR3_DMAR
#define IS_LPUART_DMAREQ(DMAREQ)            ((((DMAREQ) & (uint32_t)0xFFFFFF3F) == 0x00) && \
                                             ((DMAREQ) != (uint32_t)0x00))

/**
  * @}
  */

/** @defgroup LPUART_DMA_Recception_Error     LPUART_DMA_Recception_Error
  * @{
  */

#define LPUART_DMAOnError_Enable              ((uint32_t)0x00000000)
#define LPUART_DMAOnError_Disable             LPUART_CR3_DDRE
#define IS_LPUART_DMAONERROR(DMAERROR)      (((DMAERROR) == LPUART_DMAOnError_Disable)|| \
                                             ((DMAERROR) == LPUART_DMAOnError_Enable))
/**
  * @}
  */

/** @defgroup LPUART_MuteMode_WakeUp_methods   LPUART_MuteMode_WakeUp_methods
  * @{
  */

#define LPUART_WakeUp_IdleLine                ((uint32_t)0x00000000)
#define LPUART_WakeUp_AddressMark             LPUART_CR1_WAKE
#define IS_LPUART_MUTEMODE_WAKEUP(WAKEUP)     (((WAKEUP) == LPUART_WakeUp_IdleLine) || \
                                               ((WAKEUP) == LPUART_WakeUp_AddressMark))
/**
  * @}
  */

/** @defgroup LPUART_Address_Detection    LPUART_Address_Detection
  * @{
  */

#define LPUART_AddressLength_4b               ((uint32_t)0x00000000)
#define LPUART_AddressLength_7b               LPUART_CR2_ADDM7
#define IS_LPUART_ADDRESS_DETECTION(ADDRESS) (((ADDRESS) == LPUART_AddressLength_4b) || \
                                             ((ADDRESS) == LPUART_AddressLength_7b))
/**
  * @}
  */

/** @defgroup LPUART_StopMode_WakeUp_methods    LPUART_StopMode_WakeUp_methods
  * @{
  */

#define LPUART_WakeUpSource_AddressMatch      ((uint32_t)0x00000000)
#define LPUART_WakeUpSource_StartBit          LPUART_CR3_WUS_1
#define LPUART_WakeUpSource_RXNE              (LPUART_CR3_WUS_0 | LPUART_CR3_WUS_1)
#define IS_LPUART_STOPMODE_WAKEUPSOURCE(SOURCE) (((SOURCE) == LPUART_WakeUpSource_AddressMatch) || \
                                                ((SOURCE) == LPUART_WakeUpSource_StartBit) || \
                                                ((SOURCE) == LPUART_WakeUpSource_RXNE))

/**
  * @}
  */
/** @defgroup LPUART_DE_Polarity  LPUART_DE_Polarity
  * @{
  */

#define LPUART_DEPolarity_High                ((uint32_t)0x00000000)
#define LPUART_DEPolarity_Low                 LPUART_CR3_DEP
#define IS_LPUART_DE_POLARITY(POLARITY)       (((POLARITY) == LPUART_DEPolarity_Low) || \
                                               ((POLARITY) == LPUART_DEPolarity_High))
/**
  * @}
  */

/** @defgroup LPUART_Inversion_Pins   LPUART_Inversion_Pins
  * @{
  */

#define LPUART_InvPin_Tx                      LPUART_CR2_TXINV
#define LPUART_InvPin_Rx                      LPUART_CR2_RXINV
#define IS_LPUART_INVERSTION_PIN(PIN)       ((((PIN) & (uint32_t)0xFFFCFFFF) == 0x00) && \
                                             ((PIN) != (uint32_t)0x00))

/**
  * @}
  */

/** @defgroup LPUART_OVR_DETECTION   LPUART_OVR_DETECTION
  * @{
  */

#define LPUART_OVRDetection_Enable            ((uint32_t)0x00000000)
#define LPUART_OVRDetection_Disable           LPUART_CR3_OVRDIS
#define IS_LPUART_OVRDETECTION(OVR)         (((OVR) == LPUART_OVRDetection_Enable)|| \
                                             ((OVR) == LPUART_OVRDetection_Disable))
/**
  * @}
  */
/** @defgroup LPUART_Request     LPUART_Request
  * @{
  */

#define LPUART_Request_SBKRQ                  LPUART_RQR_SBKRQ
#define LPUART_Request_MMRQ                   LPUART_RQR_MMRQ
#define LPUART_Request_RXFRQ                  LPUART_RQR_RXFRQ

#define IS_LPUART_REQUEST(REQUEST)          (((REQUEST) == LPUART_Request_RXFRQ) || \
                                             ((REQUEST) == LPUART_Request_MMRQ) || \
                                             ((REQUEST) == LPUART_Request_SBKRQ))
/**
  * @}
  */

/** @defgroup LPUART_Flags    LPUART_Flags
  * @{
  */
#define LPUART_FLAG_REACK                     LPUART_ISR_REACK
#define LPUART_FLAG_TEACK                     LPUART_ISR_TEACK
#define LPUART_FLAG_WU                        LPUART_ISR_WUF
#define LPUART_FLAG_RWU                       LPUART_ISR_RWU
#define LPUART_FLAG_SBK                       LPUART_ISR_SBKF
#define LPUART_FLAG_CM                        LPUART_ISR_CMF
#define LPUART_FLAG_BUSY                      LPUART_ISR_BUSY
#define LPUART_FLAG_nCTSS                     LPUART_ISR_CTS
#define LPUART_FLAG_CTS                       LPUART_ISR_CTSIF
#define LPUART_FLAG_TXE                       LPUART_ISR_TXE
#define LPUART_FLAG_TC                        LPUART_ISR_TC
#define LPUART_FLAG_RXNE                      LPUART_ISR_RXNE
#define LPUART_FLAG_IDLE                      LPUART_ISR_IDLE
#define LPUART_FLAG_ORE                       LPUART_ISR_ORE
#define LPUART_FLAG_NF                        LPUART_ISR_NF
#define LPUART_FLAG_FE                        LPUART_ISR_FE
#define LPUART_FLAG_PE                        LPUART_ISR_PE
#define IS_LPUART_FLAG(FLAG)                  (((FLAG) == LPUART_FLAG_PE) || ((FLAG) == LPUART_FLAG_TXE) || \
                                               ((FLAG) == LPUART_FLAG_TC) || ((FLAG) == LPUART_FLAG_RXNE) || \
                                               ((FLAG) == LPUART_FLAG_IDLE) || ((FLAG) == LPUART_FLAG_CTS)|| \
                                               ((FLAG) == LPUART_FLAG_ORE) || ((FLAG) == LPUART_FLAG_SBK)|| \
                                               ((FLAG) == LPUART_FLAG_NF) || ((FLAG) == LPUART_FLAG_FE) || \
                                               ((FLAG) == LPUART_FLAG_nCTSS)|| ((FLAG) == LPUART_FLAG_WU)|| \
                                               ((FLAG) == LPUART_FLAG_BUSY) || ((FLAG) == LPUART_FLAG_REACK)|| \
                                               ((FLAG) == LPUART_FLAG_CM) ||  ((FLAG) == LPUART_FLAG_RWU) || \
                                               ((FLAG) == LPUART_FLAG_TEACK))

#define IS_LPUART_CLEAR_FLAG(FLAG)            (((FLAG) == LPUART_FLAG_WU) || ((FLAG) == LPUART_FLAG_TC) || \
                                               ((FLAG) == LPUART_FLAG_IDLE) || ((FLAG) == LPUART_FLAG_ORE) || \
                                               ((FLAG) == LPUART_FLAG_NF) || ((FLAG) == LPUART_FLAG_FE) || \
                                               ((FLAG) == LPUART_FLAG_CM)|| ((FLAG) == LPUART_FLAG_CTS) || \
                                               ((FLAG) == LPUART_FLAG_PE))
/**
  * @}
  */

/** @defgroup LPUART_Interrupt_definition   LPUART_Interrupt
  * @brief LPUART Interrupt definition
  * LPUART_IT possible values
  * Elements values convention: 0xZZZZYYXX
  *   XX: Position of the corresponding Interrupt
  *   YY: Register index
  *   ZZZZ: Flag position
  * @{
  */

#define LPUART_IT_WU                          ((uint32_t)0x00140316)
#define LPUART_IT_CM                          ((uint32_t)0x0011010E)
#define LPUART_IT_PE                          ((uint32_t)0x00000108)
#define LPUART_IT_TXE                         ((uint32_t)0x00070107)
#define LPUART_IT_TC                          ((uint32_t)0x00060106)
#define LPUART_IT_RXNE                        ((uint32_t)0x00050105)
#define LPUART_IT_IDLE                        ((uint32_t)0x00040104)
#define LPUART_IT_CTS                         ((uint32_t)0x0009030A)
#define LPUART_IT_ERR                         ((uint32_t)0x00000300)
#define LPUART_IT_ORE                         ((uint32_t)0x00030300)
#define LPUART_IT_NE                          ((uint32_t)0x00020300)
#define LPUART_IT_FE                          ((uint32_t)0x00010300)

#define IS_LPUART_CONFIG_IT(IT)               (((IT) == LPUART_IT_PE) || ((IT) == LPUART_IT_TXE) || \
                                               ((IT) == LPUART_IT_TC) || ((IT) == LPUART_IT_RXNE) || \
                                               ((IT) == LPUART_IT_IDLE) ||  ((IT) == LPUART_IT_WU) ||\
                                               ((IT) == LPUART_IT_CTS) || ((IT) == LPUART_IT_ERR) || \
                                               ((IT) == LPUART_IT_CM))

#define IS_LPUART_GET_IT(IT)                  (((IT) == LPUART_IT_PE) || ((IT) == LPUART_IT_TXE) || \
                                               ((IT) == LPUART_IT_TC) || ((IT) == LPUART_IT_RXNE) || \
                                               ((IT) == LPUART_IT_IDLE) || ((IT) == LPUART_IT_WU) ||\
                                               ((IT) == LPUART_IT_CTS) || ((IT) == LPUART_IT_ORE) || \
                                               ((IT) == LPUART_IT_NE) || ((IT) == LPUART_IT_FE) || \
                                               ((IT) == LPUART_IT_CM))

#define IS_LPUART_CLEAR_IT(IT)                (((IT) == LPUART_IT_TC) || ((IT) == LPUART_IT_PE) || \
                                               ((IT) == LPUART_IT_FE) || ((IT) == LPUART_IT_NE) || \
                                               ((IT) == LPUART_IT_ORE) || ((IT) == LPUART_IT_IDLE) || \
                                               ((IT) == LPUART_IT_WU)|| ((IT) == LPUART_IT_CTS) || \
                                               ((IT) == LPUART_IT_CM) )
/**
  * @}
  */

/** @defgroup LPUART_Global_definition  LPUART_Global_definition
  * @{
  */

#define IS_LPUART_BAUDRATE(BAUDRATE)        (((BAUDRATE) > 0) && ((BAUDRATE) < 0x005B8D81))
#define IS_LPUART_DE_ASSERTION_DEASSERTION_TIME(TIME) ((TIME) <= 0x1F)
#define IS_LPUART_DATA(DATA)                ((DATA) <= 0x1FF)

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
/* Initialization and Configuration functions *********************************/
void LPUART_DeInit(LPUART_TypeDef* LPUARTx);
uint32_t LPUART_Init(LPUART_TypeDef* LPUARTx, LPUART_InitTypeDef* LPUART_InitStruct);
void LPUART_StructInit(LPUART_InitTypeDef* LPUART_InitStruct);
void LPUART_Cmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState);
void LPUART_DirectionModeCmd(LPUART_TypeDef* LPUARTx, uint32_t LPUART_DirectionMode, FunctionalState NewState);
void LPUART_MSBFirstCmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState);
void LPUART_DataInvCmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState);
void LPUART_InvPinCmd(LPUART_TypeDef* LPUARTx, uint32_t LPUART_InvPin, FunctionalState NewState);
void LPUART_SWAPPinCmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState);

/* STOP Mode functions ********************************************************/
void LPUART_STOPModeCmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState);
void LPUART_StopModeWakeUpSourceConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_WakeUpSource);

/* Data transfers functions ***************************************************/
void LPUART_SendData(LPUART_TypeDef* LPUARTx, uint16_t Data);
uint16_t LPUART_ReceiveData(LPUART_TypeDef* LPUARTx);

/* Multi-Processor Communication functions ************************************/
void LPUART_SetAddress(LPUART_TypeDef* LPUARTx, uint8_t LPUART_Address);
void LPUART_MuteModeWakeUpConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_WakeUp);
void LPUART_MuteModeCmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState);
void LPUART_AddressDetectionConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_AddressLength);

/* Half-duplex mode function **************************************************/
void LPUART_HalfDuplexCmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState);

/* RS485 mode functions *******************************************************/
void LPUART_DECmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState);
void LPUART_DEPolarityConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_DEPolarity);
void LPUART_SetDEAssertionTime(LPUART_TypeDef* LPUARTx, uint32_t LPUART_DEAssertionTime);
void LPUART_SetDEDeassertionTime(LPUART_TypeDef* LPUARTx, uint32_t LPUART_DEDeassertionTime);

/* DMA transfers management functions *****************************************/
void LPUART_DMACmd(LPUART_TypeDef* LPUARTx, uint32_t LPUART_DMAReq, FunctionalState NewState);
void LPUART_DMAReceptionErrorConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_DMAOnError);

/* Interrupts and flags management functions **********************************/
void LPUART_ITConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_IT, FunctionalState NewState);
void LPUART_RequestCmd(LPUART_TypeDef* LPUARTx, uint32_t LPUART_Request, FunctionalState NewState);
void LPUART_OverrunDetectionConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_OVRDetection);
FlagStatus LPUART_GetFlagStatus(LPUART_TypeDef* LPUARTx, uint32_t LPUART_FLAG);
void LPUART_ClearFlag(LPUART_TypeDef* LPUARTx, uint32_t LPUART_FLAG);
ITStatus LPUART_GetITStatus(LPUART_TypeDef* LPUARTx, uint32_t LPUART_IT);
void LPUART_ClearITPendingBit(LPUART_TypeDef* LPUARTx, uint32_t LPUART_IT);

#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_LPUART_H */



/***************************** (C) COPYRIGHT HKMicroChip  *****************************/

