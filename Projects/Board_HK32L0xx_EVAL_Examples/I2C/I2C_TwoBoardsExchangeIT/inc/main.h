/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.h
* @brief:     Main program header.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "hk32l0xx.h"
#include "hk32l0xx_eval.h"
#include "hk32l0xx_eval_i2c_ee.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define I2C_COMx                          I2C1
#define I2C_COMx_CLK                      RCC_APB1Periph_I2C1

#define I2C_COMx_SCL_PIN                  GPIO_Pin_6                  /* PB.06 */
#define I2C_COMx_SCL_IO_PORT              GPIOB                       /* GPIOB */
#define I2C_COMx_SCL_SOURCE               GPIO_PinSource6
#define I2C_COMx_SCL_AF                   GPIO_AF_1
#define I2C_COMx_SCLIO_CLKCMD             RCC_AHBPeriphClockCmd
#define I2C_COMx_SCL_IO_CLK               RCC_AHBPeriph_GPIOB

#define I2C_COMx_SDA_PIN                  GPIO_Pin_7                  /* PB.07 */
#define I2C_COMx_SDA_IO_PORT              GPIOB                       /* GPIOB */
#define I2C_COMx_SDA_SOURCE               GPIO_PinSource7
#define I2C_COMx_SDA_AF                   GPIO_AF_1
#define I2C_COMx_SDAIO_CLKCMD             RCC_AHBPeriphClockCmd
#define I2C_COMx_SDA_IO_CLK               RCC_AHBPeriph_GPIOB

#define I2C_COMx_IRQHandler               I2C1_IRQHandler
#define I2C_COMx_IRQ                      I2C1_IRQn

/*I2C CLOCK*/
#define I2C_COMx_CLK_CMD                  RCC_APB1PeriphClockCmd
#define I2C_COMx_CLK                      RCC_APB1Periph_I2C1
/*I2C STOP MODE clock*/
#define I2C_COMx_STOPCLK                  RCC_I2C1CLK_HSI8M

/* I2C DMA Config need to remap config,Call the following function
   SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_I2C1_DMA_RMP,ENABLE); */
#define I2C_COMx_DMATX_Channel         DMA_Channel6
#define I2C_COMx_DMATX_IRQ             DMA_Channel4_7_IRQn
#define I2C_COMx_DMATX_IRQHandle       DMA_Channel4_7_IRQHandler

#define I2C_COMx_DMARX_Channel         DMA_Channel7
#define I2C_COMx_DMARX_IRQ             DMA_Channel4_7_IRQn
#define I2C_COMx_DMARX_IRQHandle       DMA_Channel4_7_IRQHandler

#define I2C_COMx_TX_DMA_FLAG_TC        DMA1_FLAG_TC6
#define I2C_COMx_TX_DMA_FLAG_GL        DMA1_FLAG_GL6
#define I2C_COMx_RX_DMA_FLAG_TC        DMA1_FLAG_TC7
#define I2C_COMx_RX_DMA_FLAG_GL        DMA1_FLAG_GL7


/*slect open or close debug info*/
#define DEBUG_ON 1

/*define to slect master or remove to slect slave
//#define I2C_MASTER*/

/* Configure the OA1 address of the slave device
   NOTE: The real address in 7-bit address mode is SLAVEADDRESS>>1*/
#define SLAVEADDRESS                      ((uint8_t)0x33)

#define SEND_LEN                          (2)

/* print with file name and number of lines you can close it by change DEBUG_ON is 0*/
#define debug(fmt,arg...)                if(DEBUG_ON)\
                                         printf("[%s:%d]\t"fmt"\r\n",__FILE__,__LINE__, ##arg)
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif  /* End of __cplusplus */

#endif /*__MAIN_H */

