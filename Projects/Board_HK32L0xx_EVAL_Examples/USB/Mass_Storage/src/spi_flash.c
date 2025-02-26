/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  spi_flash.c
* @brief:     Initialization SPI and configure external flash interface function.
* @author:    AE Team
* @version:   V1.0.0/2024-1-11
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "spi_flash.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Wait timeout callback function.
  * @param  error Code.
  * @retval None.
  */
static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
    /* Wait for processing after timeout and output error information */
    FLASH_ERROR("SPI Wait timeout!errorCode = %d\r\n", errorCode);
    return 0;
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length
  * @retval None
  */
void DELAY_ms(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--)
    {

    }
}

/**
  * @brief  Initialize SPI flash.
  * @param  None
  * @retval None
  */
uint8_t FLASH_SPI_disk_initialize(void)
{
    SPI_InitTypeDef  SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable SPI clock */
    FLASH_SPI_APBxClock_FUN (FLASH_SPI_CLK, ENABLE);
    FLASH_SPI_CS_GPIO_ClkCmd(FLASH_SPI_CS_CLK, ENABLE);
    FLASH_SPI_SCK_GPIO_ClkCmd(FLASH_SPI_SCK_CLK, ENABLE);
    FLASH_SPI_MISO_GPIO_ClkCmd(FLASH_SPI_MISO_CLK, ENABLE);
    FLASH_SPI_MOSI_GPIO_ClkCmd(FLASH_SPI_MOSI_CLK, ENABLE);

    /* selects the pin to used as Alternate function */
    GPIO_PinAFConfig(FLASH_SPI_SCK_PORT, FLASH_SPI_SCK_AF_SOURCE, GPIO_AF_0);
    GPIO_PinAFConfig(FLASH_SPI_MISO_PORT, FLASH_SPI_MISO_AF_SOURCE, GPIO_AF_0);
    GPIO_PinAFConfig(FLASH_SPI_MOSI_PORT, FLASH_SPI_MOSI_AF_SOURCE, GPIO_AF_0);

    /* NSS pin function configuration, NSS pin is configured as normal GPIO */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_CS_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(FLASH_SPI_CS_PORT, &GPIO_InitStructure);

    /* SCK pin function configuration */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_SCK_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(FLASH_SPI_SCK_PORT, &GPIO_InitStructure);

    /* MOSI pin function configuration */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MOSI_PIN;
    GPIO_Init(FLASH_SPI_MOSI_PORT, &GPIO_InitStructure);

    /* MISO pin function configuration */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO_PIN;
    GPIO_Init(FLASH_SPI_MISO_PORT, &GPIO_InitStructure);

    /* Disable Flash*/
    SPI_FLASH_CS_HIGH();

    /* SPI mode configuration */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(FLASH_SPIx, &SPI_InitStructure);

    SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);  //FIFO threshold must be configured

    /* Enable SPI */
    SPI_Cmd(FLASH_SPIx, ENABLE);

    /* Check whether flash works normally */
    if (sFLASH_ID == SPI_FLASH_ReadID())
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
  * @brief  Erase the specified address sector.
  * @param  SectorAddr:Sector address to erase.
  * @retval None
  */
void SPI_FLASH_SectorErase(uint32_t SectorAddr)
{
    /* Send flash write enable command */
    SPI_FLASH_WriteEnable();
    SPI_FLASH_WaitForWriteEnd();

    SPI_FLASH_CS_LOW();

    /* Send sector erase instruction*/
    SPI_FLASH_SendByte(W25X_SectorErase);

    /* Send erase sector address */
    SPI_FLASH_SendByte(SectorAddr >> 16);
    SPI_FLASH_SendByte(SectorAddr >> 8);
    SPI_FLASH_SendByte(SectorAddr);

    SPI_FLASH_CS_HIGH();

    /* Wait for the erase to complete */
    SPI_FLASH_WaitForWriteEnd();
}

/**
  * @brief  Erase flash sector
  * @param  None
  * @retval None
  */
void SPI_FLASH_BulkErase(void)
{
    /* Send flash write enable command */
    SPI_FLASH_WriteEnable();

    SPI_FLASH_CS_LOW();

    /* Send all block erase instruction*/
    SPI_FLASH_SendByte(W25X_ChipErase);

    SPI_FLASH_CS_HIGH();

    /* Wait for the erase to complete */
    SPI_FLASH_WaitForWriteEnd();
}

/**
  * @brief  Write data to flash by page.
  * @param  pBuffer: Pointer to write data.
  * @param  WriteAddr: Address written.
  * @param  NumByteToWrite: The length of written data must be less than SPI_FLASH_PerWritePageSize.
  * @retval None
  */
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    /* Send flash write enable command */
    SPI_FLASH_WriteEnable();

    SPI_FLASH_CS_LOW();

    /* Page write instruction*/
    SPI_FLASH_SendByte(W25X_PageProgram);

    SPI_FLASH_SendByte(WriteAddr >> 16);
    SPI_FLASH_SendByte(WriteAddr >> 8);
    SPI_FLASH_SendByte(WriteAddr);

    if (NumByteToWrite > SPI_FLASH_PerWritePageSize)
    {
        NumByteToWrite = SPI_FLASH_PerWritePageSize;
        FLASH_ERROR("SPI_FLASH_PageWrite too large!");
    }

    /* Write data */
    while (NumByteToWrite--)
    {
        SPI_FLASH_SendByte(*pBuffer);
        pBuffer++;
    }

    SPI_FLASH_CS_HIGH();

    /* Wait for writing to complete */
    SPI_FLASH_WaitForWriteEnd();
}

/**
  * @brief  Write data to flash.
  * @param  pBuffer: Pointer to write data.
  * @param  WriteAddr: Address written.
  * @param  NumByteToWrite: Length of data written.
  * @retval None
  */
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    /* operation for remainder, if writeAddr is SPI_ FLASH_ PageSize is an integer multiple,
       and the result of the operation is an Addr value of 0 */
    Addr = WriteAddr % SPI_FLASH_PageSize;

    /*How much difference can be calculated to align page addresses*/
    count = SPI_FLASH_PageSize - Addr;
    /*Calculate how many integer pages to write*/
    NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
    /*Calculate the remainder by calculating the number of bytes remaining on less than one page*/
    NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

    /* Addr=0,Then WriteAddr aligns exactly on the page */
    if (Addr == 0)
    {
        /* NumByteToWrite < SPI_FLASH_PageSize */
        if (NumOfPage == 0)
        {
            SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
        }
        else /* NumByteToWrite > SPI_FLASH_PageSize */
        {
            /*First, write down all the integer pages*/
            while (NumOfPage--)
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr +=  SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }

            /*If there is any extra data that is less than one page, write it down*/
            SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    /* If the address is not aligned with SPI_FLASH_PageSize */
    else
    {
        /* NumByteToWrite < SPI_FLASH_PageSize */
        if (NumOfPage == 0)
        {
            /* The remaining position on the current page is smaller than NumOfSingle
               and cannot be completed on a single page */
            if (NumOfSingle > count)
            {
                temp = NumOfSingle - count;
                /*Fill the current page first*/
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);

                WriteAddr +=  count;
                pBuffer += count;
                /*Write the remaining data again*/
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
            }
            else /*NumOfSingle data can be written in the remaining positions on the current page*/
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else /* NumByteToWrite > SPI_FLASH_PageSize */
        {
            /*Any additional data with incorrect addresses will be processed separately
              and will not be included in this operation*/
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
            NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

            /* Write the count of data first, in order to align the addresses for the next write */
            SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);

            /* Next, let's discuss the situation of repeated address alignment */
            WriteAddr +=  count;
            pBuffer += count;

            /*Write down all the integer pages*/
            while (NumOfPage--)
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr +=  SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }

            /*If there is any extra data that is less than one page, write it down*/
            if (NumOfSingle != 0)
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/**
  * @brief  Read flash data
  * @param  pBuffer: Pointer for storing read data.
  * @param  ReadAddr: Address read.
  * @param  NumByteToRead: Length of data read.
  * @retval None
  */
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    SPI_FLASH_CS_LOW();

    /* Send read instruction */
    SPI_FLASH_SendByte(W25X_ReadData);

    SPI_FLASH_SendByte(ReadAddr >> 16);
    SPI_FLASH_SendByte(ReadAddr >> 8);
    SPI_FLASH_SendByte(ReadAddr);

    /* Read data */
    while (NumByteToRead--)
    {
        *pBuffer = SPI_FLASH_SendByte(Dummy_Byte);
        pBuffer++;
    }

    SPI_FLASH_CS_HIGH();
}

/**
  * @brief  Read FLASH ID
  * @param  None
  * @retval FLASH ID
  */
uint32_t SPI_FLASH_ReadID(void)
{
    uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

    SPI_FLASH_CS_LOW();

    /* Send JEDEC instructions, read ID */
    SPI_FLASH_SendByte(W25X_JedecDeviceID);

    Temp0 = SPI_FLASH_SendByte(Dummy_Byte);
    Temp1 = SPI_FLASH_SendByte(Dummy_Byte);
    Temp2 = SPI_FLASH_SendByte(Dummy_Byte);

    SPI_FLASH_CS_HIGH();

    Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
    return Temp;
}

/**
  * @brief  Read FLASH Device ID
  * @param  None
  * @retval FLASH Device ID
  */
uint32_t SPI_FLASH_ReadDeviceID(void)
{
    uint32_t Temp = 0;

    SPI_FLASH_CS_LOW();

    /* Send "RDID " instruction */
    SPI_FLASH_SendByte(W25X_DeviceID);
    SPI_FLASH_SendByte(Dummy_Byte);
    SPI_FLASH_SendByte(Dummy_Byte);
    SPI_FLASH_SendByte(Dummy_Byte);

    /* Read a byte from the FLASH */
    Temp = SPI_FLASH_SendByte(Dummy_Byte);

    SPI_FLASH_CS_HIGH();

    return Temp;
}

/**
  * @brief  Initiates a read data byte (READ) sequence from the Flash.
  *         This is done by driving the /CS line low to select the device,
  *         then the READ instruction is transmitted followed by 3 bytes
  *         address. This function exit and keep the /CS line low, so the
  *         Flash still being selected. With this technique the whole
  *         content of the Flash is read with a single READ instruction.
  * @param  FLASH's internal address to read from.
  * @retval None
  */
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr)
{
    /* Select the FLASH: Chip Select low */
    SPI_FLASH_CS_LOW();

    /* Send "Read from Memory " instruction */
    SPI_FLASH_SendByte(W25X_ReadData);

    /* Send the 24-bit address of the address to read from -----------------------*/

    /* Send ReadAddr high nibble address byte */
    SPI_FLASH_SendByte(ReadAddr >> 16);

    /* Send ReadAddr medium nibble address byte */
    SPI_FLASH_SendByte(ReadAddr >> 8);

    /* Send ReadAddr low nibble address byte */
    SPI_FLASH_SendByte(ReadAddr);
}

/**
  * @brief  Read one byte of data.
  * @param  None
  * @retval Return received data.
  */
uint8_t SPI_FLASH_ReadByte(void)
{
    return (SPI_FLASH_SendByte(Dummy_Byte));
}

/**
  * @brief  Send one byte of data.
  * @param  Data to send.
  * @retval Return received data.
  */
uint8_t SPI_FLASH_SendByte(uint8_t byte)
{
    uint32_t SPITimeout = SPIT_FLAG_TIMEOUT;

    while (SPIorI2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_TXE) == RESET)
    {
        if ((SPITimeout--) == 0)
        {
            return SPI_TIMEOUT_UserCallback(0);
        }
    }

    SPI_SendData8(FLASH_SPIx, byte);

    SPITimeout = SPIT_FLAG_TIMEOUT;

    while (SPIorI2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_RXNE) == RESET)
    {
        if ((SPITimeout--) == 0)
        {
            return SPI_TIMEOUT_UserCallback(1);
        }
    }

    return SPI_ReceiveData8(FLASH_SPIx );
}

/**
  * @brief  Send two byte of data.
  * @param  Data to send.
  * @retval Return received data.
  */
uint16_t SPI_FLASH_SendHalfWord(uint16_t HalfWord)
{
    uint32_t SPITimeout = SPIT_FLAG_TIMEOUT;

    while (SPIorI2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_TXE) == RESET)
    {
        if ((SPITimeout--) == 0)
        {
            return SPI_TIMEOUT_UserCallback(2);
        }
    }

    SPIorI2S_SendData16(FLASH_SPIx, HalfWord);

    SPITimeout = SPIT_FLAG_TIMEOUT;

    while (SPIorI2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_RXNE) == RESET)
    {
        if ((SPITimeout--) == 0)
        {
            return SPI_TIMEOUT_UserCallback(3);
        }
    }

    return SPIorI2S_ReceiveData16(FLASH_SPIx );
}

/**
  * @brief  Send write enable command to flash
  * @param  none
  * @retval none
  */
void SPI_FLASH_WriteEnable(void)
{
    SPI_FLASH_CS_LOW();

    /* Send write enable command */
    SPI_FLASH_SendByte(W25X_WriteEnable);

    SPI_FLASH_CS_HIGH();
}

/**
  * @brief  Wait until the flash internal data is written.
  * @param  none
  * @retval none
  */
void SPI_FLASH_WaitForWriteEnd(void)
{
    uint8_t FLASH_Status = 0;

    /* Enable Flash */
    SPI_FLASH_CS_LOW();

    /* Send read status register command */
    SPI_FLASH_SendByte(W25X_ReadStatusReg);

    do
    {
        /* Read the status register of flash chip */
        FLASH_Status = SPI_FLASH_SendByte(Dummy_Byte);
    } while ((FLASH_Status & WIP_Flag) == SET);

    /* Disable Flash */
    SPI_FLASH_CS_HIGH();
}

/**
  * @brief  Enter power down mode.
  * @param  none
  * @retval none
  */
void SPI_Flash_PowerDown(void)
{
    /* Enable Flash */
    SPI_FLASH_CS_LOW();

    /* Send power down command */
    SPI_FLASH_SendByte(W25X_PowerDown);

    /* Disable Flash */
    SPI_FLASH_CS_HIGH();
}

/**
  * @brief  awaken.
  * @param  none
  * @retval none
  */
void SPI_Flash_WAKEUP(void)
{
    /* Enable Flash */
    SPI_FLASH_CS_LOW();

    /* Send awaken command */
    SPI_FLASH_SendByte(W25X_ReleasePowerDown);

    /* Disable Flash */
    SPI_FLASH_CS_HIGH();
}

