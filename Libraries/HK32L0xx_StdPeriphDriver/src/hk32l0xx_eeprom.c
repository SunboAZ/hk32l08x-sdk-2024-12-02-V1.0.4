/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_eeprom.c
* @brief:     EEPROM init and functions configure
* @author:    AE Team
* @version:   V1.0.0/2024-01-10
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_eeprom.h"
#include "hk32l0xx_i2c.h"
#include <stdio.h>


/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup EEPROM EEPROM
  * @brief EEPROM driver modules
  * @{
  */

/** @defgroup EEPROM_Private_Functions EEPROM_Private_Functions
  * @{
  */

#define DEBUG_I2C  I2C2
#define I2C_CLK     RCC_APB1Periph_I2C2
#define EEPROM_I2C_TIMOUT   0XFFFF
/**
  * @brief  EEPROM init
  * @retval None
  */
void EEPROM_Init(void)
{
    I2C_InitTypeDef   I2C_InitStructure;
    RCC_APB1PeriphClockCmd(I2C_CLK, ENABLE);
    /*IIC config*/
    I2C_InitStructure.I2C_Timing = 0x00210507;
    I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
    I2C_InitStructure.I2C_DigitalFilter = 0;
    /*I2C mode*/
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    /*master self address ,only different slave address*/
    I2C_InitStructure.I2C_OwnAddress1 = 0;
    /*ACK*/
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
    /*Address mode*/
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(DEBUG_I2C, &I2C_InitStructure);
    /* Enable I2C */
    I2C_Cmd(DEBUG_I2C, ENABLE);
}


/**
  * @brief  form EEPROM read data
  * @param  startaddr: start address
  * @param  *buffer: read data from EEPROM to buffer
  * @param  Length: the length of read data
  * @retval ERROR or SUCCESS
  */
ErrorStatus EEPROM_Read(uint16_t startaddr, uint8_t *buffer, uint8_t Length)
{
    uint8_t i;
    uint32_t eeprom_cnt = 0;

    /*Check busy*/
    while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_BUSY))
    {
        eeprom_cnt++;

        if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
        {
            return ERROR;
        }
    }

#if (EE_TYPE > HK24C16)
    I2C_TransferHandling(DEBUG_I2C, EEPROM_ADDR, 2, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
    /*Whether TXDR is empty*/
    eeprom_cnt = 0;

    while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_TXIS) == RESET)
    {
        eeprom_cnt++;

        if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
        {
            return ERROR;
        }
    }

    /*Send slave address*/
    I2C_SendData(DEBUG_I2C, startaddr >> 8);
    /*Check send complete*/
    eeprom_cnt = 0;

    while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_TXIS) == RESET)
    {
        eeprom_cnt++;

        if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
        {
            return ERROR;
        }
    }

    I2C_SendData(DEBUG_I2C, startaddr);
    eeprom_cnt = 0;

    while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_TC) == RESET)
    {
        eeprom_cnt++;

        if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
        {
            return ERROR;
        }
    }

#else
    I2C_TransferHandling(DEBUG_I2C, EEPROM_ADDR, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
    /*Whether TXDR is empty*/
    eeprom_cnt = 0;

    while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_TXIS) == RESET)
    {
        eeprom_cnt++;

        if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
        {
            return ERROR;
        }
    }

    I2C_SendData(DEBUG_I2C, startaddr);
    eeprom_cnt = 0;

    while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_TC) == RESET)
    {
        eeprom_cnt++;

        if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
        {
            return ERROR;
        }
    }

#endif
    /*Generate start read sign*/
    I2C_TransferHandling(DEBUG_I2C, EEPROM_ADDR, Length, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);

    for (i = 0; i < Length; i++)
    {
        /*Wait receive complete*/
        eeprom_cnt = 0;

        while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_RXNE) == RESET)
        {
            eeprom_cnt++;

            if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
            {
                return ERROR;
            }
        }

        buffer[i] = I2C_ReceiveData(DEBUG_I2C);
    }

    /*Check stop sign*/
    eeprom_cnt = 0;

    while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_STOPF) == RESET)
    {
        eeprom_cnt++;

        if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
        {
            return ERROR;
        }
    }

    I2C_ClearFlag(DEBUG_I2C, I2C_FLAG_STOPF);
    return SUCCESS;
}

/**
  * @brief  write data to EEPROM
  * @param  startaddr: start address
  * @param  *buffer: write data from buffer to EEPROM
  * @param  Length: the length of write data
  * @retval ERROR or SUCCESS
  */
ErrorStatus I2C_EepromPageWrite(uint16_t startaddr, uint8_t *buffer, uint8_t Length)
{
    uint8_t i;
    uint32_t eeprom_cnt = 0;

    while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_BUSY))
    {
        eeprom_cnt++;

        if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
        {
            return ERROR;
        }
    }

#if (EE_TYPE > HK24C16)
    I2C_TransferHandling(DEBUG_I2C, EEPROM_ADDR, 2, I2C_Reload_Mode, I2C_Generate_Start_Write);
    /*Whether TXDR is empty*/
    eeprom_cnt = 0;

    while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_TXIS) == RESET)
    {
        eeprom_cnt++;

        if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
        {
            return ERROR;
        }
    }

    I2C_SendData(DEBUG_I2C, startaddr >> 8);
    eeprom_cnt = 0;

    while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_TXIS) == RESET)
    {
        eeprom_cnt++;

        if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
        {
            return ERROR;
        }
    }

    I2C_SendData(DEBUG_I2C, startaddr);
    eeprom_cnt = 0;

    while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_TCR) == RESET)
    {
        eeprom_cnt++;

        if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
        {
            return ERROR;
        }
    }

#else
    I2C_TransferHandling(DEBUG_I2C, EEPROM_ADDR, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);
    /*Whether TXDR is empty*/
    eeprom_cnt = 0;

    while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_TXIS) == RESET)
    {
        eeprom_cnt++;

        if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
        {
            return ERROR;
        }
    }

    I2C_SendData(DEBUG_I2C, startaddr);
    eeprom_cnt = 0;

    while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_TCR) == RESET)
    {
        eeprom_cnt++;

        if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
        {
            return ERROR;
        }
    }

#endif
    I2C_TransferHandling(DEBUG_I2C, EEPROM_ADDR, Length, I2C_AutoEnd_Mode, I2C_No_StartStop);

    for (i = 0; i < Length; i++)
    {
        /*Wait TXDR is empty*/
        eeprom_cnt = 0;

        while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_TXIS) == RESET)
        {
            eeprom_cnt++;

            if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
            {
                return ERROR;
            }
        }

        I2C_SendData(DEBUG_I2C, buffer[i]);
    }

    /*Check stop sign*/
    eeprom_cnt = 0;

    while (I2C_GetFlagStatus(DEBUG_I2C, I2C_FLAG_STOPF) == RESET)
    {
        eeprom_cnt++;

        if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
        {
            return ERROR;
        }
    }

    I2C_ClearFlag(DEBUG_I2C, I2C_FLAG_STOPF);
    return SUCCESS;
}

/**
  * @brief  Wait EEPROM standby state
  * @retval ERROR or SUCCESS
  */
ErrorStatus I2C_EepromWaitEepromStandbyState(void)
{
    uint32_t EETimeout = 0;
    uint32_t eeprom_cnt = 0;
    /* Keep looping till the slave acknowledge his address or maximum number
    of trials is reached  */
    /* Configure CR2 register : set Slave Address and end mode */
    I2C_TransferHandling(DEBUG_I2C, EEPROM_ADDR, 0, I2C_AutoEnd_Mode, I2C_No_StartStop);

    do
    {
        EETimeout = 0X1000;
        /* Clear NACKF */
        I2C_ClearFlag(DEBUG_I2C, I2C_ICR_NACKCF | I2C_ICR_STOPCF);
        /* Generate start */
        I2C_GenerateSTART(DEBUG_I2C, ENABLE);

        /* Wait until timeout elapsed */
        while (EETimeout-- != 0)
        {
        }

        eeprom_cnt++;

        if (eeprom_cnt >= EEPROM_I2C_TIMOUT)
        {
            return ERROR;
        }
    } while (I2C_GetFlagStatus(DEBUG_I2C, I2C_ISR_NACKF) != RESET);

    /* Clear STOPF */
    I2C_ClearFlag(DEBUG_I2C, I2C_ICR_STOPCF);
    return SUCCESS;
}

/**
  * @brief  Write EEPROM Buffer
  * @param  WriteAddr: Write address
  * @param  pBuffer: buffer point
  * @param  NumByteToWrite: number bytes to write
  * @retval ERROR or SUCCESS
  */
ErrorStatus I2C_EepromBufferWrite(uint16_t WriteAddr, uint8_t* pBuffer, uint16_t NumByteToWrite)
{
    uint16_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;
    Addr = WriteAddr % I2C_PageSize;
    count = I2C_PageSize - Addr;
    NumOfPage =  NumByteToWrite / I2C_PageSize;
    NumOfSingle = NumByteToWrite % I2C_PageSize;

    /* If WriteAddr is I2C_PageSize aligned  */
    if (Addr == 0)
    {
        /* If NumByteToWrite < I2C_PageSize */
        if (NumOfPage == 0)
        {
            if ((I2C_EepromPageWrite(WriteAddr, pBuffer,  NumOfSingle)) != SUCCESS)
            {
                return ERROR;
            }

            if ((I2C_EepromWaitEepromStandbyState()) != SUCCESS)
            {
                return ERROR;
            }
        }
        /* If NumByteToWrite > I2C_PageSize */
        else
        {
            while (NumOfPage--)
            {
                if ((I2C_EepromPageWrite(WriteAddr, pBuffer,  I2C_PageSize)) != SUCCESS)
                {
                    return ERROR;
                }

                if ((I2C_EepromWaitEepromStandbyState()) != SUCCESS)
                {
                    return ERROR;
                }

                WriteAddr +=  I2C_PageSize;
                pBuffer += I2C_PageSize;
            }

            if (NumOfSingle != 0)
            {
                if ((I2C_EepromPageWrite(WriteAddr, pBuffer,  NumOfSingle)) != SUCCESS)
                {
                    return ERROR;
                }

                if ((I2C_EepromWaitEepromStandbyState()) != SUCCESS)
                {
                    return ERROR;
                }
            }
        }
    }
    /* If WriteAddr is not I2C_PageSize aligned  */
    else
    {
        /* If NumByteToWrite < I2C_PageSize */
        if (NumOfPage == 0)
        {
            if ((I2C_EepromPageWrite(WriteAddr, pBuffer,  NumOfSingle)) != SUCCESS)
            {
                return ERROR;
            }

            if ((I2C_EepromWaitEepromStandbyState()) != SUCCESS)
            {
                return ERROR;
            }
        }
        /* If NumByteToWrite > I2C_PageSize */
        else
        {
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / I2C_PageSize;
            NumOfSingle = NumByteToWrite % I2C_PageSize;

            if (count != 0)
            {
                if ((I2C_EepromPageWrite(WriteAddr, pBuffer, count)) != SUCCESS)
                {
                    return ERROR;
                }

                if ((I2C_EepromWaitEepromStandbyState()) != SUCCESS)
                {
                    return ERROR;
                }

                WriteAddr += count;
                pBuffer += count;
            }

            while (NumOfPage--)
            {
                if ((I2C_EepromPageWrite(WriteAddr, pBuffer, I2C_PageSize)) != SUCCESS)
                {
                    return ERROR;
                }

                if ((I2C_EepromWaitEepromStandbyState()) != SUCCESS)
                {
                    return ERROR;
                }

                WriteAddr +=  I2C_PageSize;
                pBuffer += I2C_PageSize;
            }

            if (NumOfSingle != 0)
            {
                if ((I2C_EepromPageWrite(WriteAddr, pBuffer, NumOfSingle)) != SUCCESS)
                {
                    return ERROR;
                }

                if ((I2C_EepromWaitEepromStandbyState()) != SUCCESS)
                {
                    return ERROR;
                }
            }
        }
    }

    return SUCCESS;
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */



