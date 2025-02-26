/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  aes_util.c
* @brief:     This file provides high level functions to encrypt and decrypt an
*             input message using AES in ECB/CBC/CTR modes.
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*              1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_aes.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define AES_CC_TIMEOUT    ((uint32_t) 0x00010000)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Encrypt using AES in ECB Mode
  * @param  Key: Key used for AES algorithm.
    * @param  Keysize: length of the Key, must be a 128, 192 or 256.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilength: length of the Input buffer, must be a multiple of 16 bytes.
  * @param  Output: pointer to the returned buffer.
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: Operation done
  *         - ERROR: Operation failed
  */
ErrorStatus AES_ECB_Encrypt(uint8_t* Key, uint16_t Keysize, uint8_t* Input, uint32_t Ilength, uint8_t* Output)
{
    AES_InitTypeDef AES_InitStructure;
    AES_KeyInitTypeDef  AES_KeyInitStructure = {0};
    ErrorStatus status = SUCCESS;
    uint32_t inputaddr  = (uint32_t)Input;
    uint32_t outputaddr = (uint32_t)Output;
    __IO uint32_t counter = 0;
    uint32_t ccstatus = 0;
    uint32_t i = 0;

    /* AES Key config */
    switch (Keysize)
    {
        case 128:
            AES_KeyInitStructure.AES_KeySize = AES_KEYSIZE_128B;
            break;

        case 192:
            AES_KeyInitStructure.AES_KeySize = AES_KEYSIZE_192B;
            break;

        case 256:
            AES_KeyInitStructure.AES_KeySize = AES_KEYSIZE_256B;
            break;

        default:
            break;
    }

    /* AES Key initialisation */
    AES_KeyInit(&AES_KeyInitStructure, Key);
    /* AES configuration */
    AES_InitStructure.AES_Operation = AES_Operation_Encryp;
    AES_Init(&AES_InitStructure);
    /* Enable AES */
    AES_Cmd(ENABLE);

    for (i = 0; ((i < Ilength) && (status != ERROR)); i += 16)
    {
        /* Write the Input block in the IN FIFO with bit reverse */
        AES_WriteSubData((*(uint32_t*)(inputaddr)));
        inputaddr += 4;
        AES_WriteSubData((*(uint32_t*)(inputaddr)));
        inputaddr += 4;
        AES_WriteSubData((*(uint32_t*)(inputaddr)));
        inputaddr += 4;
        AES_WriteSubData((*(uint32_t*)(inputaddr)));
        inputaddr += 4;

        /* Wait for CCF flag to be set (Wait until the complete message has been processed) */
        counter = 0;

        do
        {
            ccstatus = AES_GetFlagStatus(AES_FLAG_CCF);
            counter++;
        } while ((counter != AES_CC_TIMEOUT) && (ccstatus == RESET));

        if (ccstatus == RESET)
        {
            status = ERROR;
        }
        else
        {
            /* Clear CCF flag */
            AES_ClearFlag(AES_FLAG_CCF);

            /* Read cipher text */
            *(uint32_t*)(outputaddr) = AES_ReadSubData();
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = AES_ReadSubData();
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = AES_ReadSubData();
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = AES_ReadSubData();
            outputaddr += 4;
        }
    }

    /* Disable AES before starting new processing */
    AES_Cmd(DISABLE);
    return status;
}

/**
  * @brief  Decrypt using AES in ECB Mode
  * @param  Key: Key used for AES algorithm.
  * @param  Keysize: length of the Key, must be a 128, 192 or 256.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilength: length of the Input buffer, must be a multiple of 16 bytes.
  * @param  Output: pointer to the returned buffer.
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: Operation done
  *         - ERROR: Operation failed
  */
ErrorStatus AES_ECB_Decrypt(uint8_t* Key, uint16_t Keysize, uint8_t* Input, uint32_t Ilength, uint8_t* Output)
{
    AES_InitTypeDef AES_InitStructure;
    AES_KeyInitTypeDef  AES_KeyInitStructure = {0};
    ErrorStatus status = SUCCESS;
    uint32_t inputaddr  = (uint32_t)Input;
    uint32_t outputaddr = (uint32_t)Output;
    __IO uint32_t counter = 0;
    uint32_t ccstatus = 0;
    uint32_t i = 0;


    /* AES Key config */
    switch (Keysize)
    {
        case 128:
            AES_KeyInitStructure.AES_KeySize = AES_KEYSIZE_128B;
            break;

        case 192:
            AES_KeyInitStructure.AES_KeySize = AES_KEYSIZE_192B;
            break;

        case 256:
            AES_KeyInitStructure.AES_KeySize = AES_KEYSIZE_256B;
            break;

        default:
            break;
    }

    /* AES Key initialisation */
    AES_KeyInit(&AES_KeyInitStructure, Key);
    /* AES configuration */
    AES_InitStructure.AES_Operation = AES_Operation_KeyDerivAndDecryp;
    AES_Init(&AES_InitStructure);

    /* Enable AES */
    AES_Cmd(ENABLE);

    for (i = 0; ((i < Ilength) && (status != ERROR)); i += 16)
    {
        AES_WriteSubData((*(uint32_t*)(inputaddr)));
        inputaddr += 4;
        AES_WriteSubData((*(uint32_t*)(inputaddr)));
        inputaddr += 4;
        AES_WriteSubData((*(uint32_t*)(inputaddr)));
        inputaddr += 4;
        AES_WriteSubData((*(uint32_t*)(inputaddr)));
        inputaddr += 4;

        /* Wait for CCF flag to be set */
        counter = 0;

        do
        {
            ccstatus = AES_GetFlagStatus(AES_FLAG_CCF);
            counter++;
        } while ((counter != AES_CC_TIMEOUT) && (ccstatus == RESET));

        if (ccstatus == RESET)
        {
            status = ERROR;
        }
        else
        {
            /* Clear CCF flag */
            AES_ClearFlag(AES_FLAG_CCF);

            /* Read cipher text */
            *(uint32_t*)(outputaddr) = AES_ReadSubData();
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = AES_ReadSubData();
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = AES_ReadSubData();
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = AES_ReadSubData();
            outputaddr += 4;
        }
    }

    /* Disable AES before starting new processing */
    AES_Cmd(DISABLE);
    return status;
}

