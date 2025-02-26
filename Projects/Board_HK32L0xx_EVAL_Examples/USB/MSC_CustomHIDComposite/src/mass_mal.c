/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  mass_mal.c
* @brief:     Medium Access Layer interface.
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
#include "mass_mal.h"
#include "spi_flash.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t Mass_Memory_Size[2];
uint32_t Mass_Block_Size[2];
uint32_t Mass_Block_Count[2];
__IO uint32_t Status = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the Media on the HK32
  * @retval None
  */
uint16_t MAL_Init(uint8_t lun)
{
    uint16_t status = MAL_OK;

    switch (lun)
    {
        case 0:
            FLASH_SPI_disk_initialize();

            if (SPI_FLASH_ReadID() == sFLASH_ID)
            {
                //printf("flash init succsee\n");
                Status = MAL_OK;
            }
            else
            {
                Status = MAL_FAIL;
            }

            break;

        default:
            return MAL_FAIL;
    }

    return status;
}

/**
  * @brief  Write sectors
  * @retval None
  */
uint16_t MAL_Write(uint8_t lun, uint32_t Memory_Offset, uint32_t *Writebuff, uint16_t Transfer_Length)
{

    switch (lun)
    {
        case 0:
            //printf("write add =%d.length=%d\n",Memory_Offset,Transfer_Length);
            SPI_FLASH_SectorErase(Memory_Offset);
            SPI_FLASH_BufferWrite((uint8_t *)Writebuff, Memory_Offset, Transfer_Length);
            break;

        default:
            return MAL_FAIL;
    }

    return MAL_OK;
}

/**
  * @brief  Read sectors
  * @retval Buffer pointer
  */
uint16_t MAL_Read(uint8_t lun, uint32_t Memory_Offset, uint32_t *Readbuff, uint16_t Transfer_Length)
{

    switch (lun)
    {
        case 0:
            //printf("read add =%d.length=%d\n",Memory_Offset,Transfer_Length);
            SPI_FLASH_BufferRead((uint8_t *)Readbuff, Memory_Offset, Transfer_Length);
            break;

        default:
            return MAL_FAIL;
    }

    return MAL_OK;
}

/**
  * @brief  Get status
  * @retval None
  */
uint16_t MAL_GetStatus(uint8_t lun)
{
    if (lun == 0)
    {
        FLASH_SPI_disk_initialize();

        if (SPI_FLASH_ReadID() == sFLASH_ID)
        {
            //Flash Sector size
            Mass_Block_Size[0]  = FLASH_SectorSize;

            //Flash Sector number
            Mass_Block_Count[0] = FLASH_SectorNum;

            //Flash memory size
            Mass_Memory_Size[0] = Mass_Block_Size[0] * Mass_Block_Count[0];

            return MAL_OK;
        }
    }

    return MAL_FAIL;
}

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/


