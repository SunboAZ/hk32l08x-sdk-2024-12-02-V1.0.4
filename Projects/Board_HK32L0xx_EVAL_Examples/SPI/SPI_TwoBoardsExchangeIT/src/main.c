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

/** @addtogroup SPI_TwoBoardsExchangeIT
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SPI_InitTypeDef   SPI_InitStructure;
uint8_t TxBuffer[] = "SPI Interrupt Example";
uint8_t RxBuffer [RXBUFFERSIZE];
__IO uint8_t Rx_Idx = 0x00;
__IO uint8_t Tx_Idx = 0x00;
__IO uint8_t CmdTransmitted = 0x00;
__IO uint8_t CmdReceived = 0x00;
__IO uint8_t CmdStatus = 0x00;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;

/* Private function prototypes -----------------------------------------------*/
static void GPIO_Config(void);
static void SPI_Config(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
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
    HK_EVAL_LEDInit(LED2);
    HK_EVAL_LEDOff(LED2);
#if (DEVICE == MASTER)
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

    while (HK_EVAL_PBGetState(BUTTON_KEY1) != RESET)
    {
    }

    /* Initialize the FIFO threshold */
    SPI_RxFIFOThresholdConfig(SPIy, SPI_RxFIFOThreshold_QF);

    /* Enable the Tx buffer empty interrupt */
    SPIorI2S_ITConfig(SPIy, SPI_I2S_IT_TXE, ENABLE);

    /* Enable the Rx buffer not empty interrupt */
    SPIorI2S_ITConfig(SPIy, SPI_I2S_IT_RXNE, ENABLE);

    /* Enable the SPI Error interrupt */
    SPIorI2S_ITConfig(SPIy, SPI_I2S_IT_ERR, ENABLE);

    /* SPIy enable */
    SPI_Cmd(SPIy, ENABLE);
#elif (DEVICE == SLAVER)

    /* Initialize the FIFO threshold */
    SPI_RxFIFOThresholdConfig(SPIz, SPI_RxFIFOThreshold_QF);

    /* Enable the Rx buffer not empty interrupt */
    SPIorI2S_ITConfig(SPIz, SPI_I2S_IT_RXNE, ENABLE);

    /* Enable the SPI Error interrupt */
    SPIorI2S_ITConfig(SPIz, SPI_I2S_IT_ERR, ENABLE);

    /* Enable the SPI peripheral */
    SPI_Cmd(SPIz, ENABLE);
#endif

    while (1)
    {
#if (DEVICE == MASTER)

        /* Waiting until TX FIFO is empty */
        while (SPI_GetTransmissionFIFOStatus(SPIy) != SPI_TransmissionFIFOStatus_Empty)
        {
        }

        /* Wait busy flag */
        while (SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_BSY) == SET)
        {
        }

        /* Waiting until RX FIFO is empty */
        while (SPI_GetReceptionFIFOStatus(SPIy) != SPI_ReceptionFIFOStatus_Empty)
        {
        }

        if ((Buffercmp(TxBuffer, RxBuffer, DATA_SIZE) == PASSED) && (CmdReceived == CMD_ACK))
        {
            /* Turn ON LED2 and LED1 */
            HK_EVAL_LEDOn(LED1);

            /* Turn ON LED2 and LED2 */
            HK_EVAL_LEDOn(LED2);
        }
        else
        {
            /* Turn ON LED2 and LED2 */
            HK_EVAL_LEDOn(LED2);
        }

#elif (DEVICE == SLAVER)
        SPI_SendData8(SPIz, CMD_ACK);
        SPIorI2S_ITConfig(SPIz, SPI_I2S_IT_TXE, ENABLE);

        /* Waiting Transaction code Byte */
        while (CmdStatus == 0x00)
        {
        }

        /* Waiting until TX FIFO is empty */
        while (SPI_GetTransmissionFIFOStatus(SPIz) != SPI_TransmissionFIFOStatus_Empty)
        {
        }

        /* Wait busy flag */
        while (SPIorI2S_GetFlagStatus(SPIz, SPI_I2S_FLAG_BSY) == SET)
        {
        }

        /* Disable the Tx buffer empty interrupt */
        SPIorI2S_ITConfig(SPIz, SPI_I2S_IT_TXE, DISABLE);

        /* Waiting until RX FIFO is empty */
        while (SPI_GetReceptionFIFOStatus(SPIz) != SPI_ReceptionFIFOStatus_Empty)
        {
        }

        if (Buffercmp(TxBuffer, RxBuffer, DATA_SIZE) == PASSED)
        {
            /* Turn ON LED2 and LED1 */
            HK_EVAL_LEDOn(LED1);
            /* Turn ON LED2 and LED2 */
            HK_EVAL_LEDOn(LED2);
        }
        else
        {
            /* Turn ON LED2 and LED1 */
            HK_EVAL_LEDOn(LED1);
        }

#endif
    }
}

/**
  * @brief  Deinitializes the GPIO peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
static void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
#if (DEVICE == SLAVER)
    SPIz_GPIO_RCC(SPIz_GPIO_CLK, ENABLE);
    /*SPI1:PA4(NSS)---PA5(SCK)---PA6(MISO)---PA7(MOSI)*/
    GPIO_InitStruct.GPIO_Pin = SPIz_PIN_SCK | SPIz_PIN_MISO | SPIz_PIN_MOSI;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_Init(SPIz_GPIO, &GPIO_InitStruct);
    GPIO_PinAFConfig(SPIz_GPIO, SPIz_PIN_SCK_PinSource, SPIz_PIN_SCK_AF);
    GPIO_PinAFConfig(SPIz_GPIO, SPIz_PIN_MISO_PinSource, SPIz_PIN_MISO_AF);
    GPIO_PinAFConfig(SPIz_GPIO, SPIz_PIN_MOSI_PinSource, SPIz_PIN_MOSI_AF);
    GPIO_InitStruct.GPIO_Pin = SPIy_PIN_NSS;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_Init(SPIy_GPIO, &GPIO_InitStruct);
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
static void SPI_Config(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
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

    /* Configure and enable SPI_SLAVE interrupt --------------------------------*/
    NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#if (DEVICE == MASTER)
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;

    /* Configure SPIy */
    SPI_Init(SPIy, &SPI_InitStructure);
#elif (DEVICE == SLAVER)
    SPIorI2S_DeInit(SPIz);
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;

    /* Configure SPIz */
    SPI_Init(SPIz, &SPI_InitStructure);
#endif
}

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
/**
  * @brief  Returns NbrOfDataToTransfer value.
  * @param  None
  * @retval Tx Buffer Size (NbrOfDataToTransfer1).
  */
uint8_t GetVar_NbrOfData(void)
{
    return DATA_SIZE;
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



