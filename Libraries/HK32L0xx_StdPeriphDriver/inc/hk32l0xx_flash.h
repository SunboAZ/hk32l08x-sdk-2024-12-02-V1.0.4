/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_flash.h
* @brief:     FLASH initialization and configuration
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_FLASH_H
#define __HK32L0XX_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"

/** @addtogroup FLASH FLASH
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup FLASH_Exported_Types FLASH_Exported_Types
  * @{
  */
/**
  * @brief  FLASH Status
  */
typedef enum
{
    FLASH_BUSY = 1,
    FLASH_ERROR_WRP,
    FLASH_ERROR_PROGRAM,
    FLASH_COMPLETE,
    FLASH_TIMEOUT
} FLASH_Status;

/**
  * @brief Option Bytes Registers
  */
typedef struct
{
    __IO uint32_t USERRDP;       /*!< FLASH option byte user options and read protection,Address offset: 0x00 */
    __IO uint32_t DATA;          /*!< User data byte  (stored in FLASH_OBR[31:16]),      Address offset: 0x04 */
    __IO uint32_t WRP01;         /*!< FLASH option byte write protection 01,             Address offset: 0x08 */
    __IO uint32_t WRP23;         /*!< FLASH option byte write protection 23,             Address offset: 0x0C */
} OB_TypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Constants FLASH_Exported_Constants
  * @{
  */

/** @defgroup FLASH_Option_Bytes FLASH_Option_Bytes
  * @{
  */
#define OB_BASE                        ((uint32_t)0x1FFFF800U)
#define OB                             ((OB_TypeDef *) OB_BASE)
/**
  * @}
  */

/** @defgroup UID_base_address UID_base_address
  * @{
  */
#define UID_BASE                       ((uint32_t)0x1FFFF7AC)
/**
  * @}
  */

/** @defgroup FLASH_Keys FLASH_Keys
  * @{
  */
#define FLASH_KEY1                      ((uint32_t)(0x45670123U ))
#define FLASH_KEY2                      ((uint32_t)(0xCDEF89ABU ))
#define FLASH_OPTKEY1                   ((uint32_t)(0x45670123U ))
#define FLASH_OPTKEY2                   ((uint32_t)(0xCDEF89ABU ))
/**
  * @}
  */

/** @defgroup Flash_Latency Flash_Latency
  * @{
  */
#define FLASH_Latency_0                 ((uint32_t)0x00000000)
#define FLASH_Latency_1                 ((uint32_t)0x00000001)
#define FLASH_Latency_2                 ((uint32_t)0x00000002)
#define FLASH_Latency_3                 ((uint32_t)0x00000003)
#define FLASH_Latency_7                 ((uint32_t)0x00000004)
#define FLASH_Latency_9                 ((uint32_t)0x00000005)
#define FLASH_Latency_19                ((uint32_t)0x00000006)
#define FLASH_Latency_39                ((uint32_t)0x00000007)
#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_Latency_0) || \
                                   ((LATENCY) == FLASH_Latency_1) || \
                                   ((LATENCY) == FLASH_Latency_2) || \
                                   ((LATENCY) == FLASH_Latency_3) || \
                                   ((LATENCY) == FLASH_Latency_7) || \
                                   ((LATENCY) == FLASH_Latency_9) || \
                                   ((LATENCY) == FLASH_Latency_19)|| \
                                   ((LATENCY) == FLASH_Latency_39))
/**
  * @}
  */

/** @defgroup FLASH_Interrupts FLASH_Interrupts
  * @{
  */
#define FLASH_IT_EOP                    FLASH_CR_EOPIE          /*!< End of programming interrupt source */
#define FLASH_IT_ERR                    FLASH_CR_ERRIE          /*!< Error interrupt source */
#define FLASH_IT_ECC1BIT_ERR            FLASH_CR_ECC1BIT_ERRIE  /*!< ECC1bit error interrupt source */
#define FLASH_IT_ECC2BIT_ERR            FLASH_CR_ECC2BIT_ERRIE  /*!< ECC2bit error interrupt source */
#define IS_FLASH_IT(IT) ((((IT) & (uint32_t)0xFFFCEBFF) == 0x00000000) && (((IT) != 0x00000000)))
/**
  * @}
  */

/** @defgroup FLASH_Address FLASH_Address
  * @{
  */
#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0801FFFF)) /*!< 128K devices */
/**
  * @}
  */

/** @defgroup FLASH_OB_DATA_ADDRESS FLASH_OB_DATA_ADDRESS
  * @{
  */
#define IS_OB_DATA_ADDRESS(ADDRESS) (((ADDRESS) >= 0x1FFFF800) && ((ADDRESS) <= 0x1FFFF840))
/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_Write_Protection FLASH_Option_Bytes_Write_Protection
  * @{
  */
#define OB_WRP_Pages0to3               ((uint32_t)0x00000001) /* Write protection of page 0 to 3 */
#define OB_WRP_Pages4to7               ((uint32_t)0x00000002) /* Write protection of page 4 to 7 */
#define OB_WRP_Pages8to11              ((uint32_t)0x00000004) /* Write protection of page 8 to 11 */
#define OB_WRP_Pages12to15             ((uint32_t)0x00000008) /* Write protection of page 12 to 15 */
#define OB_WRP_Pages16to19             ((uint32_t)0x00000010) /* Write protection of page 16 to 19 */
#define OB_WRP_Pages20to23             ((uint32_t)0x00000020) /* Write protection of page 20 to 23 */
#define OB_WRP_Pages24to27             ((uint32_t)0x00000040) /* Write protection of page 24 to 27 */
#define OB_WRP_Pages28to31             ((uint32_t)0x00000080) /* Write protection of page 28 to 31 */
#define OB_WRP_Pages32to35             ((uint32_t)0x00000100) /* Write protection of page 32 to 35 */
#define OB_WRP_Pages36to39             ((uint32_t)0x00000200) /* Write protection of page 36 to 39 */
#define OB_WRP_Pages40to43             ((uint32_t)0x00000400) /* Write protection of page 40 to 43 */
#define OB_WRP_Pages44to47             ((uint32_t)0x00000800) /* Write protection of page 44 to 47 */
#define OB_WRP_Pages48to51             ((uint32_t)0x00001000) /* Write protection of page 48 to 51 */
#define OB_WRP_Pages52to55             ((uint32_t)0x00002000) /* Write protection of page 52 to 55 */
#define OB_WRP_Pages56to59             ((uint32_t)0x00004000) /* Write protection of page 56 to 59 */
#define OB_WRP_Pages60to63             ((uint32_t)0x00008000) /* Write protection of page 60 to 63 */
#define OB_WRP_Pages64to67             ((uint32_t)0x00010000) /* Write protection of page 64 to 67 */
#define OB_WRP_Pages68to71             ((uint32_t)0x00020000) /* Write protection of page 68 to 71 */
#define OB_WRP_Pages72to75             ((uint32_t)0x00040000) /* Write protection of page 72 to 75 */
#define OB_WRP_Pages76to79             ((uint32_t)0x00080000) /* Write protection of page 76 to 79 */
#define OB_WRP_Pages80to83             ((uint32_t)0x00100000) /* Write protection of page 80 to 83 */
#define OB_WRP_Pages84to87             ((uint32_t)0x00200000) /* Write protection of page 84 to 87 */
#define OB_WRP_Pages88to91             ((uint32_t)0x00400000) /* Write protection of page 88 to 91 */
#define OB_WRP_Pages92to95             ((uint32_t)0x00800000) /* Write protection of page 92 to 95 */
#define OB_WRP_Pages96to99             ((uint32_t)0x01000000) /* Write protection of page 96 to 99 */
#define OB_WRP_Pages100to103           ((uint32_t)0x02000000) /* Write protection of page 100 to 103 */
#define OB_WRP_Pages104to107           ((uint32_t)0x04000000) /* Write protection of page 104 to 107 */
#define OB_WRP_Pages108to111           ((uint32_t)0x08000000) /* Write protection of page 108 to 111 */
#define OB_WRP_Pages112to115           ((uint32_t)0x10000000) /* Write protection of page 112 to 115 */
#define OB_WRP_Pages116to119           ((uint32_t)0x20000000) /* Write protection of page 116 to 119 */
#define OB_WRP_Pages120to123           ((uint32_t)0x40000000) /* Write protection of page 120 to 123 */
#define OB_WRP_Pages124to127           ((uint32_t)0x80000000) /* Write protection of page 124 to 127 */
#define OB_WRP_AllPages                ((uint32_t)0xFFFFFFFF) /*!< Write protection of all Sectors */
#define IS_OB_WRP(PAGE) (((PAGE) != 0x0000000))
/**
  * @}
  */

/** @defgroup FLASH_Read_Protection_Level FLASH_Read_Protection_Level
  * @{
  */
#define OB_RDP_Level_0   ((uint8_t)0xAA)
#define OB_RDP_Level_1   ((uint8_t)0xBB)
/*#define OB_RDP_Level_2   ((uint8_t)0xCC)*/ /* Warning: When enabling read protection level 2
                                                it's no more possible to go back to level 1 or 0 */
#define IS_OB_RDP(LEVEL) (((LEVEL) == OB_RDP_Level_0)||\
                          ((LEVEL) == OB_RDP_Level_1))/*||\
                          ((LEVEL) == OB_RDP_Level_2))*/
/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_IWatchdog FLASH_Option_Bytes_IWatchdog
  * @{
  */
#define OB_IWDG_SW                     ((uint8_t)0x01)  /*!< Software IWDG selected */
#define OB_IWDG_HW                     ((uint8_t)0x00)  /*!< Hardware IWDG selected */
#define IS_OB_IWDG_SOURCE(SOURCE) (((SOURCE) == OB_IWDG_SW) || ((SOURCE) == OB_IWDG_HW))
/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_nRST_STOP FLASH_Option_Bytes_nRST_STOP
  * @{
  */
#define OB_STOP_NoRST                  ((uint8_t)0x02) /*!< No reset generated when entering in STOP */
#define OB_STOP_RST                    ((uint8_t)0x00) /*!< Reset generated when entering in STOP */
#define IS_OB_STOP_SOURCE(SOURCE) (((SOURCE) == OB_STOP_NoRST) || ((SOURCE) == OB_STOP_RST))
/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_nRST_STDBY FLASH_Option_Bytes_nRST_STDBY
  * @{
  */
#define OB_STDBY_NoRST                 ((uint8_t)0x04) /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST                   ((uint8_t)0x00) /*!< Reset generated when entering in STANDBY */
#define IS_OB_STDBY_SOURCE(SOURCE) (((SOURCE) == OB_STDBY_NoRST) || ((SOURCE) == OB_STDBY_RST))
/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_BOOT1 FLASH_Option_Bytes_BOOT1
  * @{
  */
#define OB_BOOT1_RESET                 ((uint8_t)0x00) /*!< BOOT1 Reset */
#define OB_BOOT1_SET                   ((uint8_t)0x10) /*!< BOOT1 Set */
#define IS_OB_BOOT1(BOOT1) (((BOOT1) == OB_BOOT1_RESET) || ((BOOT1) == OB_BOOT1_SET))
/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_BOOT0 FLASH_Option_Bytes_BOOT0
  * @{
  */
#define OB_BOOT0_RESET                 ((uint8_t)0x00) /*!< BOOT0 Reset */
#define OB_BOOT0_SET                   ((uint8_t)0x08) /*!< BOOT0 Set */
#define IS_OB_BOOT0(BOOT0) (((BOOT0) == OB_BOOT0_RESET) || ((BOOT0) == OB_BOOT0_SET))
/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_BOOT0SW FLASH_Option_Bytes_BOOT0SW
  * @{
  */
#define OB_BOOT0_SW                   ((uint8_t)0x80) /*!< BOOT0 pin disabled */
#define OB_BOOT0_HW                   ((uint8_t)0x00) /*!< BOOT0 pin bonded with GPIO */
#define IS_OB_BOOT0SW(BOOT0) (((BOOT0) == OB_BOOT0_SW) || ((BOOT0) == OB_BOOT0_HW))
/**
  * @}
  */

/** @defgroup FLASH_Flags FLASH_Flags
  * @{
  */
#define FLASH_FLAG_BSY                 FLASH_SR_BSY             /*!< FLASH Busy flag */
#define FLASH_FLAG_PGERR               FLASH_SR_PGERR           /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPERR              FLASH_SR_WRPRTERR        /*!< FLASH Write protected error flag */
#define FLASH_FLAG_EOP                 FLASH_SR_EOP             /*!< FLASH End of Programming flag */
#define FLASH_FLAG_SIZE_ERR            FLASH_SR_SIZEERR         /*!< FLASH SIZE ERR flag */
#define FLASH_FLAG_ECC1BIT_ERR         FLASH_SR_ECC1BIT_ERR     /*!< FLASH ECC1BIT ERR flag */
#define FLASH_FLAG_ECC2BIT_ERR         FLASH_SR_ECC2BIT_ERR     /*!< FLASH ECC2BIT ERR flag */
#define IS_FLASH_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFF3BCB) == 0x00000000) && ((FLAG) != 0x00000000))
#define IS_FLASH_GET_FLAG(FLAG)   (((FLAG) == FLASH_FLAG_BSY) || ((FLAG) == FLASH_FLAG_PGERR)           || \
                                  ((FLAG) == FLASH_FLAG_WRPERR) || ((FLAG) == FLASH_FLAG_EOP)           || \
                                  ((FLAG) == FLASH_FLAG_SIZE_ERR) || ((FLAG) == FLASH_FLAG_ECC1BIT_ERR) || \
                                  ((FLAG) == FLASH_FLAG_ECC2BIT_ERR))
/**
  * @}
  */

/** @defgroup FLASH_Timeout_definition FLASH_Timeout_definition
  * @{
  */
#define FLASH_ER_PRG_TIMEOUT         ((uint32_t)0x000B0000)
/**
  * @}
  */

/** @defgroup Bit_definition_for_OptionByte_register Bit_definition_for_OptionByte_register
  * @{
  */
/******************  Bit definition for OB_RDP register  **********************/
#define OB_RDP_RDP_Pos       (0U)
#define OB_RDP_RDP_Msk       (0xFFU << OB_RDP_RDP_Pos)                         /*!< 0x000000FF */
#define OB_RDP_RDP           OB_RDP_RDP_Msk                                    /*!< Read protection option byte */
#define OB_RDP_nRDP_Pos      (8U)
#define OB_RDP_nRDP_Msk      (0xFFU << OB_RDP_nRDP_Pos)                        /*!< 0x0000FF00 */
#define OB_RDP_nRDP          OB_RDP_nRDP_Msk                                   /*!< Read protection complemented option byte */

/******************  Bit definition for OB_USER register  *********************/
#define OB_USER_USER_Pos     (16U)
#define OB_USER_USER_Msk     (0xFFU << OB_USER_USER_Pos)                       /*!< 0x00FF0000 */
#define OB_USER_USER         OB_USER_USER_Msk                                  /*!< User option byte */
#define OB_USER_nUSER_Pos    (24U)
#define OB_USER_nUSER_Msk    (0xFFU << OB_USER_nUSER_Pos)                      /*!< 0xFF000000 */
#define OB_USER_nUSER        OB_USER_nUSER_Msk                                 /*!< User complemented option byte */

/******************  Bit definition for OB_WRP0 register  *********************/
#define OB_WRP0_WRP0_Pos     (0U)
#define OB_WRP0_WRP0_Msk     (0xFFU << OB_WRP0_WRP0_Pos)                       /*!< 0x000000FF */
#define OB_WRP0_WRP0         OB_WRP0_WRP0_Msk                                  /*!< Flash memory write protection option bytes */
#define OB_WRP0_nWRP0_Pos    (8U)
#define OB_WRP0_nWRP0_Msk    (0xFFU << OB_WRP0_nWRP0_Pos)                      /*!< 0x0000FF00 */
#define OB_WRP0_nWRP0        OB_WRP0_nWRP0_Msk                                 /*!< Flash memory write protection complemented option bytes */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/** @defgroup FLASH_Exported_Functions FLASH_Exported_Functions
  * @{
  */
/* FLASH Interface configuration functions ************************************/
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_PrefetchBufferCmd(FunctionalState NewState);
FlagStatus FLASH_GetPrefetchBufferStatus(void);
void FLASH_EccConfig(FunctionalState NewState);
/* FLASH Memory Programming functions *****************************************/
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_HalfErasePage(uint32_t Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
/* FLASH Option Bytes Programming functions *****************************************/
void FLASH_OptionByteUnlock(void);
void FLASH_OptionByteLock(void);
void FLASH_OptionByteLaunch(void);
FLASH_Status FLASH_OptionByteErase(void);
FLASH_Status FLASH_OptionByteEnableWRP(uint32_t OB_WRP);
FLASH_Status FLASH_OptionByteConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY, uint8_t OB_RDP, uint8_t OB_BOOT_SEL, uint8_t OB_BOOT01);
FLASH_Status FLASH_OptionByteProgramData(uint32_t Address, uint32_t Data);
uint8_t FLASH_OptionByteGetUser(void);
uint32_t FLASH_OptionByteGetWRP(void);
FlagStatus FLASH_OptionByteGetRDP(void);
/* FLASH Interrupts and flags management functions **********************************/
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);
void Sys_GetDevice96BitUID(uint32_t *UID);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_FLASH_H */


