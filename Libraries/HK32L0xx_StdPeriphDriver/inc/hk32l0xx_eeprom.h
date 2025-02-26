/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_eeprom.h
* @brief:     This file contains all the functions prototypes for the EEPROM firmware
*             library.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_EEPROM_H
#define __HK32L0XX_EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include "hk32l0xx.h"

/** @addtogroup EEPROM
  * @{
  */

/** @defgroup EEPROM_Exported_Constants EEPROM_Exported_Constants
  * @{
  */

/** @defgroup EEPROM_Address EEPROM_Address
  * @{
  */
#define EEPROM_ADDR 0xA0

/**
  * @}
  */
/** @defgroup EEPROM_Type EEPROM_Type
  * @{
  */
#define HK24C01   0x01
#define HK24C02   0x02
#define HK24C04   0x03
#define HK24C08   0x04
#define HK24C16   0x05
#define HK24C32   0x06
#define HK24C64   0x07
#define HK24C128  0x08
#define HK24C256  0x09
#define HK24C512  0x0a
#define HK24C1024 0x0b

#define EE_TYPE HK24C64
/**
  * @}
  */

/** @defgroup EEPROM_Size EEPROM_Size
  * @{
  */
#define I2C_PageSize           32

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup EEPROM_Exported_Functions EEPROM_Exported_Functions
  * @{
  */

void EEPROM_Init(void);
ErrorStatus EEPROM_Read(uint16_t startaddr, uint8_t *buffer, uint8_t Length);
ErrorStatus I2C_EepromPageWrite(uint16_t startaddr, uint8_t *buffer, uint8_t Length);
ErrorStatus I2C_EepromBufferWrite(uint16_t WriteAddr, uint8_t* pBuffer, uint16_t NumByteToWrite);
ErrorStatus I2C_EepromWaitEepromStandbyState(void);
/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_EEPROM_H */


