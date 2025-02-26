/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2024-01-04
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32l0xx_eval.h"
/** @addtogroup HK32L0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup SPI_TwoBoardsExchangePoll
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BufferSize 5
#define MASTER     1
#define SLAVER     0
#define SPI_CS_HIGH           GPIO_SetBits(GPIOA,GPIO_Pin_4);
#define SPI_CS_LOW            GPIO_ResetBits(GPIOA,GPIO_Pin_4);

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SPI_InitTypeDef   SPI_InitStructure;
uint8_t SPIy_Buffer_Tx[BufferSize] = {0x51, 0x52, 0x53, 0x54, 0x55};
uint8_t SPIz_Buffer_Tx[BufferSize] = {0x51, 0x52, 0x53, 0x54, 0x55};
uint8_t SPIz_Buffer_Rx[BufferSize], SPIy_Buffer_Rx[BufferSize];
__IO uint8_t TxIdx = 0, RxIdx = 0, k = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
uint8_t AckFlag = 0;

/* Private function prototypes -----------------------------------------------*/
static void GPIO_Config(void);
static void SPI_Config(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

#if (DEVICE == MASTER)
    static uint8_t SPIy_ReadWriteBit_8(uint8_t data);
#endif

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    GPIO_Config();
    SPI_Config();
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDOff(LED1);
#if (DEVICE == MASTER)
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

    while (HK_EVAL_PBGetState(BUTTON_KEY1) != RESET)
    {
    }

    SPI_CS_LOW;

    /* Transfer procedure */
    while (TxIdx < BufferSize)
    {
        while (SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET)
        {
        }

        SPI_SendData8(SPIy, SPIy_Buffer_Tx[TxIdx++]);
    }

    while (RxIdx < BufferSize)
    {
        if (SPIy_Buffer_Rx[0] != 0)
        {
            SPIy_Buffer_Rx[++RxIdx] =  SPIy_ReadWriteBit_8(0);
        }
        else
        {
            SPIy_Buffer_Rx[0] = SPIy_ReadWriteBit_8(0);
        }
    }

    SPI_CS_HIGH;
#elif (DEVICE == SLAVER)

    while (RxIdx < BufferSize)
    {
        /* Read SPIy received data */
        while (SPIorI2S_GetFlagStatus(SPIz, SPI_I2S_FLAG_RXNE) == RESET)
        {
        }

        SPIz_Buffer_Rx[RxIdx++] =  SPI_ReceiveData8(SPIz);
    }

    /* Transfer procedure */
    while (TxIdx < BufferSize)
    {
        while (SPIorI2S_GetFlagStatus(SPIz, SPI_I2S_FLAG_TXE) == RESET)
        {
        }

        SPI_SendData8(SPIz, SPIz_Buffer_Tx[TxIdx++]);
    }

#endif
#if (DEVICE == MASTER)
    /* Check the correctness of written dada */
    TransferStatus1 = Buffercmp(SPIy_Buffer_Rx, SPIz_Buffer_Tx, BufferSize);

    if (TransferStatus1 == PASSED)
    {
        HK_EVAL_LEDOn(LED1);
    }

#elif (DEVICE == SLAVER)
    /* Check the correctness of written dada */
    TransferStatus2 = Buffercmp(SPIz_Buffer_Rx, SPIy_Buffer_Tx, BufferSize);

    if (TransferStatus2 == PASSED)
    {
        HK_EVAL_LEDOn(LED1);
    }

#endif

    while (1)
    {
    }
}

/**
  * @brief  Deinitializes the GPIO peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
#if (DEVICE == SLAVER)
    SPIz_GPIO_RCC(SPIz_GPIO_CLK, ENABLE);
    /*SPI1:PA4(NSS)---PA5(SCK)---PA6(MISO)---PA7(MOSI)*/
    GPIO_InitStruct.GPIO_Pin = SPIz_PIN_NSS | SPIz_PIN_SCK | SPIz_PIN_MISO | SPIz_PIN_MOSI;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_Init(SPIz_GPIO, &GPIO_InitStruct);
    GPIO_PinAFConfig(SPIz_GPIO, SPIz_PIN_NSS_PinSource, SPIz_PIN_NSS_AF);
    GPIO_PinAFConfig(SPIz_GPIO, SPIz_PIN_SCK_PinSource, SPIz_PIN_SCK_AF);
    GPIO_PinAFConfig(SPIz_GPIO, SPIz_PIN_MISO_PinSource, SPIz_PIN_MISO_AF);
    GPIO_PinAFConfig(SPIz_GPIO, SPIz_PIN_MOSI_PinSource, SPIz_PIN_MOSI_AF);
#elif (DEVICE == MASTER)
    SPIy_GPIO_RCC(SPIy_GPIO_CLK, ENABLE);
    /*SPI1:PA4(NSS)---PA5(SCK)---PA6(MISO)---PA7(MOSI)*/
    GPIO_InitStruct.GPIO_Pin = SPIy_PIN_SCK | SPIy_PIN_MISO | SPIy_PIN_MOSI;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_Init(SPIy_GPIO, &GPIO_InitStruct);
    GPIO_PinAFConfig(SPIy_GPIO, SPIy_PIN_SCK_PinSource, SPIy_PIN_SCK_AF);
    GPIO_PinAFConfig(SPIy_GPIO, SPIy_PIN_MISO_PinSource, SPIy_PIN_MISO_AF);
    GPIO_PinAFConfig(SPIy_GPIO, SPIy_PIN_MOSI_PinSource, SPIy_PIN_MOSI_AF);
    GPIO_InitStruct.GPIO_Pin = SPIy_PIN_NSS;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_Init(SPIy_GPIO, &GPIO_InitStruct);
#endif
}
/**
  * @brief  Deinitializes the SPI peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void SPI_Config(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    SPIy_RCC(SPIy_CLK, ENABLE);
    SPIz_RCC(SPIz_CLK, ENABLE);
    SPI_StructInit(&SPI_InitStructure);
    SPIorI2S_DeInit(SPIy);
    SPIorI2S_DeInit(SPIz);

    /* SPI1 Config */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
#if (DEVICE == MASTER)
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;

    /* Configure SPIy */
    SPI_Init(SPIy, &SPI_InitStructure);

    /* SPIy enable */
    SPI_Cmd(SPIy, ENABLE);
#elif (DEVICE == SLAVER)
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;

    /* Configure SPIz */
    SPI_Init(SPIz, &SPI_InitStructure);

    /* SPIz enable */
    SPI_Cmd(SPIz, ENABLE);
#endif
}

#if (DEVICE == MASTER)
/**
  * @brief  8 bit Read and write program for the SPI peripheral registers.
  * @param  data: Written data
  * @retval SPI_I2SReceiveData(SPIz): read data for the SPIz.
  */
uint8_t SPIy_ReadWriteBit_8(uint8_t data)
{
    while (SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET)
    {
    }

    SPI_SendData8(SPIy, data);

    while (SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET)
    {
    }

    return SPI_ReceiveData8(SPIy);
}
#endif

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
  * @}
  */



