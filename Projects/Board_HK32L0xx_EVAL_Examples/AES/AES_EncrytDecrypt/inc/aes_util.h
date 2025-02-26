/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  aes_util.h
* @brief:     This file contains all the functions prototypes for the AES firmware
*             library.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AES_UTIL_H
#define __AES_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

ErrorStatus AES_ECB_Encrypt(uint8_t* Key, uint16_t Keysize, uint8_t* Input, uint32_t Ilength, uint8_t* Output);
ErrorStatus AES_ECB_Decrypt(uint8_t* Key, uint16_t Keysize, uint8_t* Input, uint32_t Ilength, uint8_t* Output);
ErrorStatus AES_CBC_Encrypt(uint8_t* Key,  uint16_t Keysize, uint8_t InitVectors[16], uint8_t* Input, uint32_t Ilength, uint8_t* Output);
ErrorStatus AES_CBC_Decrypt(uint8_t* Key, uint16_t Keysize, uint8_t InitVectors[16], uint8_t* Input, uint32_t Ilength, uint8_t* Output);
ErrorStatus AES_CTR_Encrypt(uint8_t* Key, uint16_t Keysize, uint8_t InitVectors[16], uint8_t* Input, uint32_t Ilength, uint8_t* Output);
ErrorStatus AES_CTR_Decrypt(uint8_t* Key, uint16_t Keysize, uint8_t InitVectors[16], uint8_t* Input, uint32_t Ilength, uint8_t* Output);

#ifdef __cplusplus
}
#endif

#endif /*__AES_UTIL_H */
