/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  spi_flash.h
* @brief:     Initialization SPI and configure external flash interface function.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"
#include <stdio.h>
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
/*等待超时时间*/
/* timeout -------------------------------------------------------------------*/
#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)

/* WIP(busy)flag, flash internal writing -------------------------------------*/
#define WIP_Flag                  0x01
#define Dummy_Byte                0xFF

/* Select flash chip type ----------------------------------------------------*/
//#define  sFLASH_ID                0xEF3015    //W25X16
//#define  sFLASH_ID                0xEF4015    //W25Q16
//#define  sFLASH_ID                0XEF4018    //W25Q128
//#define  sFLASH_ID                0XEF4017    //W25Q64
#define  sFLASH_ID                0X684017    //HK25Q128

/* flash chip page size ------------------------------------------------------*/
#define SPI_FLASH_PageSize              (256)
#define SPI_FLASH_PerWritePageSize      (256)

//memory size = FLASH_SectorSize*FLASH_SectorNum
#define FLASH_SectorSize                (4096)
#define FLASH_SectorNum                 (4096)

/* flash chip command --------------------------------------------------------*/
#define W25X_WriteEnable                0x06
#define W25X_WriteDisable               0x04
#define W25X_ReadStatusReg              0x05
#define W25X_WriteStatusReg             0x01
#define W25X_ReadData                   0x03
#define W25X_FastReadData               0x0B
#define W25X_FastReadDual               0x3B
#define W25X_PageProgram                0x02
#define W25X_BlockErase                 0xD8
#define W25X_SectorErase                0x20
#define W25X_ChipErase                  0xC7
#define W25X_PowerDown                  0xB9
#define W25X_ReleasePowerDown           0xAB
#define W25X_DeviceID                   0xAB
#define W25X_ManufactDeviceID           0x90
#define W25X_JedecDeviceID              0x9F

/* SPIx selection ------------------------------------------------------------*/
#define FLASH_SPIx                        SPI1

/* SPI clock definition ------------------------------------------------------*/
#define FLASH_SPI_APBxClock_FUN           RCC_APB2PeriphClockCmd
#define FLASH_SPI_CLK                     RCC_APB2Periph_SPI1

/* SPI NSS pin definition ----------------------------------------------------*/
#define FLASH_SPI_CS_GPIO_ClkCmd          RCC_AHBPeriphClockCmd
#define FLASH_SPI_CS_CLK                  RCC_AHBPeriph_GPIOA
#define FLASH_SPI_CS_PORT                 GPIOA
#define FLASH_SPI_CS_PIN                  GPIO_Pin_4
#define FLASH_SPI_CS_AF_SOURCE            GPIO_PinSource4

/* SPI SCK pin definition ----------------------------------------------------*/
#define FLASH_SPI_SCK_GPIO_ClkCmd         RCC_AHBPeriphClockCmd
#define FLASH_SPI_SCK_CLK                 RCC_AHBPeriph_GPIOA
#define FLASH_SPI_SCK_PORT                GPIOA
#define FLASH_SPI_SCK_PIN                 GPIO_Pin_5
#define FLASH_SPI_SCK_AF_SOURCE           GPIO_PinSource5

/* SPI MISO pin definition ---------------------------------------------------*/
#define FLASH_SPI_MISO_GPIO_ClkCmd        RCC_AHBPeriphClockCmd
#define FLASH_SPI_MISO_CLK                RCC_AHBPeriph_GPIOA
#define FLASH_SPI_MISO_PORT               GPIOA
#define FLASH_SPI_MISO_PIN                GPIO_Pin_6
#define FLASH_SPI_MISO_AF_SOURCE          GPIO_PinSource6

/* SPI MOSI pin definition ---------------------------------------------------*/
#define FLASH_SPI_MOSI_GPIO_ClkCmd        RCC_AHBPeriphClockCmd
#define FLASH_SPI_MOSI_CLK                RCC_AHBPeriph_GPIOA
#define FLASH_SPI_MOSI_PORT               GPIOA
#define FLASH_SPI_MOSI_PIN                GPIO_Pin_7
#define FLASH_SPI_MOSI_AF_SOURCE          GPIO_PinSource7

/* SPI flash CS enable and disable -------------------------------------------*/
#define SPI_FLASH_CS_LOW()                GPIO_ResetBits( FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN )
#define SPI_FLASH_CS_HIGH()               GPIO_SetBits( FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN )

/* Information output --------------------------------------------------------*/
#define FLASH_DEBUG_ON         1
#define FLASH_DEBUG_FUNC_ON    0
#define FLASH_INFO(fmt,arg...)           printf("<<-FLASH-INFO->> "fmt"\n",##arg)
#define FLASH_ERROR(fmt,arg...)          printf("<<-FLASH-ERROR->> "fmt"\n",##arg)

#define FLASH_DEBUG(fmt,arg...)          do{\
                                          if(FLASH_DEBUG_ON)\
                                          printf("<<-FLASH-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                           }while(0)
#define FLASH_DEBUG_FUNC()               do{\
                                          if(FLASH_DEBUG_FUNC_ON)\
                                          printf("<<-FLASH-FUNC->> Func:%s@Line:%d\n",__func__,__LINE__);\
                                           }while(0)

/* Exported functions ------------------------------------------------------- */
uint8_t FLASH_SPI_disk_initialize(void);
void SPI_FLASH_SectorErase(uint32_t SectorAddr);
void SPI_FLASH_BulkErase(void);
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t SPI_FLASH_ReadID(void);
uint32_t SPI_FLASH_ReadDeviceID(void);
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr);
void SPI_Flash_PowerDown(void);
void SPI_Flash_WAKEUP(void);
uint8_t SPI_FLASH_ReadByte(void);
uint8_t SPI_FLASH_SendByte(uint8_t byte);
uint16_t SPI_FLASH_SendHalfWord(uint16_t HalfWord);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);
/* External variables --------------------------------------------------------*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /*__SPI_FLASH_H */

