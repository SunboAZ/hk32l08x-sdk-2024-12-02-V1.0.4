/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_eval_spi_flash.h
* @brief:     This file contains all the functions prototypes for the hk32l0xx_eval_spi_flash
*             firmware driver.
* @author:    AE Team
* @version:   V1.0.0/2024-01-15
*             1.Initial version
* @log:
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_EVAL_SPI_FLASH_H
#define __HK32L0XX_EVAL_SPI_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_eval.h"

/** @addtogroup Boards
  * @{
  */

/** @addtogroup HK32_EVAL
  * @{
  */

/** @addtogroup HK32FL0XX_EVAL
  * @{
  */

/** @addtogroup HK32FL0XX_EVAL_SPI_FLASH
  * @{
  */

/** @defgroup HK32FL0XX_EVAL_SPI_FLASH_Exported_Types HK32FL0XX_EVAL_SPI_FLASH_Exported_Types
  * @{
  */
/**
  * @}
  */

/** @defgroup HK32FL0XX_EVAL_SPI_FLASH_Exported_Constants HK32FL0XX_EVAL_SPI_FLASH_Exported_Constants
  * @{
  */
/**
  * @brief  M25P SPI Flash supported commands
  */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define sFLASH_CMD_WRITE          0x02  /*!< Write to Memory instruction */
#define sFLASH_CMD_WRSR           0x01  /*!< Write Status Register instruction */
#define sFLASH_CMD_WREN           0x06  /*!< Write enable instruction */
#define sFLASH_CMD_READ           0x03  /*!< Read from Memory instruction */
#define sFLASH_CMD_RDSR           0x05  /*!< Read Status Register instruction  */
#define sFLASH_CMD_RDID           0x9F  /*!< Read identification */
#define sFLASH_CMD_SE             0xD8  /*!< Sector Erase instruction */
#define sFLASH_CMD_BE             0xC7  /*!< Bulk Erase instruction */

#define sFLASH_WIP_FLAG           0x01  /*!< Write In Progress (WIP) flag */

#define sFLASH_DUMMY_BYTE         0xA5
#define sFLASH_SPI_PAGESIZE       0x100

/**
  * @}
  */

/** @defgroup HK32FL0XX_EVAL_SPI_FLASH_Exported_Macros
  * @{
  */
/**
  * @brief  Select sFLASH: Chip Select pin low
  */
#define sFLASH_CS_LOW()       GPIO_ResetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN)
/**
  * @brief  Deselect sFLASH: Chip Select pin high
  */
#define sFLASH_CS_HIGH()      GPIO_SetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN)
/**
  * @}
  */



/** @defgroup HK32FL0XX_EVAL_SPI_FLASH_Exported_Functions HK32FL0XX_EVAL_SPI_FLASH_Exported_Functions
  * @{
  */
/**
  * @brief  High layer functions
  */
/* Exported functions ------------------------------------------------------- */
void sFLASH_DeInit(void);
void sFLASH_Init(void);
void sFLASH_EraseSector(uint32_t SectorAddr);
void sFLASH_EraseBulk(void);
void sFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t sFLASH_ReadID(void);
void sFLASH_StartReadSequence(uint32_t ReadAddr);

/**
  * @brief  Low layer functions
  */
uint8_t sFLASH_ReadByte(void);
uint8_t sFLASH_SendByte(uint8_t byte);
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord);
void sFLASH_WriteEnable(void);
void sFLASH_WaitForWriteEnd(void);

#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_EVAL_SPI_FLASH_H */
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

/**
  * @}
  */

