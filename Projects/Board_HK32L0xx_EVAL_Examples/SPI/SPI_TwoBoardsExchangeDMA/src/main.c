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

/** @addtogroup SPI_TwoBoardsExchangeDMA
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SPI_InitTypeDef  SPI_InitStructure;
DMA_InitTypeDef  DMA_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint8_t TxBuffer[] = "SPI DMA Example";
uint8_t RxBuffer [RXBUFFERSIZE];
__IO uint32_t CommandTransmitted = 0x00;
__IO uint32_t CommandReceived = 0x00;
__IO uint16_t NumberOfByte = 0x00;
__IO uint16_t PrescalerValue = 0;
__IO uint32_t TimeOut = 0x0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
/* Private function prototypes -----------------------------------------------*/
static void GPIO_Config(void);
static void SPI_Config(void);
static void SysTickConfig(void);
static void TimeOut_UserCallback(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

#if (DEVICE == MASTER)
    static void TIM_Config(void);
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

    /* SysTick configuration ---------------------------------------------------*/
    SysTickConfig();
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDOff(LED1);
    HK_EVAL_LEDInit(LED2);
    HK_EVAL_LEDOff(LED2);
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);
#if (DEVICE == MASTER)

    /* Initialize the FIFO threshold */
    SPI_RxFIFOThresholdConfig(SPIy, SPI_RxFIFOThreshold_QF);

    /* TIM configuration ------------------------------------------------------*/
    TIM_Config();

    /* Enable the SPI peripheral */
    SPI_Cmd(SPIy, ENABLE);

    /* Enable NSS output for master mode */
    SPI_SSOutputCmd(SPIy, ENABLE);

    /* TIM Capture Compare DMA Request enable */
    TIM_DMACmd(TIMx, TIMx_DMA_CHANNEL, ENABLE);

    /* DMA channel Rx of SPI Configuration */
    DMA_InitStructure.DMA_BufferSize = (uint16_t)1;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPIx_DR_ADDRESS;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) &CommandReceived;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_Init(SPIx_RX_DMA_CHANNEL, &DMA_InitStructure);
    DMA_RemapConfig(DMA, DMA_CSELR_CH2_SPI1_RX);

    /* DMA TIM trigger channel Configuration */
    DMA_InitStructure.DMA_BufferSize = (uint16_t)1;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPIx_DR_ADDRESS;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) &CommandTransmitted;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
    DMA_Init(TIMx_CHANNEL_DMA_CHANNEL, &DMA_InitStructure);
    DMA_RemapConfig(DMA, DMA_CSELR_CH3_TIM2_CH2);

    /* Enable the SPI Rx DMA request */
    SPIorI2S_DMACmd(SPIy, SPI_I2S_DMAReq_Rx, ENABLE);
#elif (DEVICE == SLAVER)

    /* Initialize the FIFO threshold */
    SPI_RxFIFOThresholdConfig(SPIz, SPI_RxFIFOThreshold_QF);
    CommandTransmitted = CMD_ACK;
#endif

    while (1)
    {
#if (DEVICE == MASTER)

        while (HK_EVAL_PBGetState(BUTTON_KEY1) != RESET)
        {
        }

        CommandTransmitted = CMD_ONE;

        /* Enable the DMA channel */
        DMA_Cmd(SPIx_RX_DMA_CHANNEL, ENABLE);

        /* Enable DMA1 TIM Trigger Channel */
        DMA_Cmd(TIMx_CHANNEL_DMA_CHANNEL, ENABLE);

        /* TIM enable counter */
        TIM_Cmd(TIMx, ENABLE);

        /* Wait the SPI DMA Rx transfer complete or time out*/
        TimeOut = USER_TIMEOUT;

        while ((DMA_GetFlagStatus(SPIx_RX_DMA_FLAG_TC) == RESET) && (TimeOut != 0x00))
        {
        }

        if (TimeOut == 0)
        {
            TimeOut_UserCallback();
        }

        TimeOut = USER_TIMEOUT;

        while ((SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET) && (TimeOut != 0x00))
        {
        }

        if (TimeOut == 0)
        {
            TimeOut_UserCallback();
        }

        TimeOut = USER_TIMEOUT;

        while ((SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_BSY) == SET) && (TimeOut != 0x00))
        {
        }

        if (TimeOut == 0)
        {
            TimeOut_UserCallback();
        }

        DMA_ClearFlag(TIMx_CHANNEL_DMA_FLAG_GL);
        DMA_ClearFlag(SPIx_RX_DMA_FLAG_GL);

        /* disable the DMA channels */
        DMA_Cmd(SPIx_RX_DMA_CHANNEL, DISABLE);
        DMA_Cmd(TIMx_CHANNEL_DMA_CHANNEL, DISABLE);

        /* disable the SPI Rx DMA request */
        SPIorI2S_DMACmd(SPIy, SPI_I2S_DMAReq_Rx, DISABLE);

        /* TIM Capture Compare DMA Request DISABLE */
        TIM_DMACmd(TIMx, TIMx_DMA_CHANNEL, DISABLE);

        /* TIM disable counter */
        TIM_Cmd(TIMx, DISABLE);

        if (CommandReceived == CMD_ACK)
        {
            /* DMA channel Rx of SPI Configuration */
            DMA_InitStructure.DMA_BufferSize = (uint16_t)DATA_SIZE;
            DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPIx_DR_ADDRESS;
            DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) RxBuffer;
            DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
            DMA_InitStructure.DMA_Priority = DMA_Priority_High;
            DMA_Init(SPIx_RX_DMA_CHANNEL, &DMA_InitStructure);
            DMA_RemapConfig(DMA, DMA_CSELR_CH2_SPI1_RX);

            /* DMA channel Tx of SPI Configuration */
            DMA_InitStructure.DMA_BufferSize = (uint16_t)DATA_SIZE;
            DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPIx_DR_ADDRESS;
            DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) TxBuffer;
            DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
            DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
            DMA_Init(SPIx_TX_DMA_CHANNEL, &DMA_InitStructure);
            DMA_RemapConfig(DMA, DMA_CSELR_CH3_SPI1_TX);

            /* Enable the SPI Rx DMA request */
            SPIorI2S_DMACmd(SPIy, SPI_I2S_DMAReq_Rx, ENABLE);

            /* Enable the SPI Tx DMA request */
            SPIorI2S_DMACmd(SPIy, SPI_I2S_DMAReq_Tx, ENABLE);

            /* Enable the DMA channel */
            DMA_Cmd(SPIx_RX_DMA_CHANNEL, ENABLE);

            /* Enable DMA1 SPI Trigger Channel */
            DMA_Cmd(SPIx_TX_DMA_CHANNEL, ENABLE);
            HK_EVAL_LEDOff(LED2);

            /* Wait the SPI Rx DMA transfer complete or time out */
            TimeOut = USER_TIMEOUT;

            while ((DMA_GetFlagStatus(SPIx_RX_DMA_FLAG_TC) == RESET) && (TimeOut != 0x00))
            {
            }

            if (TimeOut == 0)
            {
                TimeOut_UserCallback();
            }

            TimeOut = USER_TIMEOUT;

            while ((DMA_GetFlagStatus(SPIx_TX_DMA_FLAG_TC) == RESET) && (TimeOut != 0x00))
            {
            }

            while ((SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET) && (TimeOut != 0x00))
            {
            }

            if (TimeOut == 0)
            {
                TimeOut_UserCallback();
            }

            TimeOut = USER_TIMEOUT;

            while ((SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_BSY) == SET) && (TimeOut != 0x00))
            {
            }

            if (TimeOut == 0)
            {
                TimeOut_UserCallback();
            }

            TimeOut = USER_TIMEOUT;

            /* Clear DMA1 global flags */
            DMA_ClearFlag(SPIx_TX_DMA_FLAG_GL);
            DMA_ClearFlag(SPIx_RX_DMA_FLAG_GL);

            /* Disable the DMA channels */
            DMA_Cmd(SPIx_RX_DMA_CHANNEL, DISABLE);
            DMA_Cmd(SPIx_TX_DMA_CHANNEL, DISABLE);

            /* Disable the SPI Rx and Rx DMA requests */
            SPIorI2S_DMACmd(SPIy, SPI_I2S_DMAReq_Rx, DISABLE);

            /* Disable the SPI Rx and Tx DMA requests */
            SPIorI2S_DMACmd(SPIy, SPI_I2S_DMAReq_Tx, DISABLE);

            /* Disable the SPI peripheral */
            SPI_Cmd(SPIy, DISABLE);
        }

        TimeOut = USER_TIMEOUT;

        if ((Buffercmp(TxBuffer, RxBuffer, DATA_SIZE) == PASSED) )
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

        while (HK_EVAL_PBGetState(BUTTON_KEY1) == RESET)
        {
        }

#endif
#if (DEVICE == SLAVER)
        /* DMA channel Rx of SPI Configuration */
        DMA_InitStructure.DMA_BufferSize = 1;
        DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPIx_DR_ADDRESS;
        DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) &CommandReceived;
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
        DMA_InitStructure.DMA_Priority = DMA_Priority_High;
        DMA_Init(SPIx_RX_DMA_CHANNEL, &DMA_InitStructure);
        DMA_RemapConfig(DMA, DMA_CSELR_CH2_SPI1_RX);
        /* DMA channel Tx of SPI Configuration */
        DMA_InitStructure.DMA_BufferSize = 1;
        DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPIx_DR_ADDRESS;
        DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) &CommandTransmitted;
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
        DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
        DMA_Init(SPIx_TX_DMA_CHANNEL, &DMA_InitStructure);
        DMA_RemapConfig(DMA, DMA_CSELR_CH3_SPI1_TX);
        /* Enable the SPI Rx and Tx DMA requests */
        SPIorI2S_DMACmd(SPIy, SPI_I2S_DMAReq_Rx, ENABLE);
        SPIorI2S_DMACmd(SPIy, SPI_I2S_DMAReq_Tx, ENABLE);
        /* Enable the SPI peripheral */
        SPI_Cmd(SPIy, ENABLE);
        /* Enable the DMA channels */
        DMA_Cmd(SPIx_RX_DMA_CHANNEL, ENABLE);
        DMA_Cmd(SPIx_TX_DMA_CHANNEL, ENABLE);

        /* Wait the SPI DMA transfers complete or time out */
        while (DMA_GetFlagStatus(SPIx_RX_DMA_FLAG_TC) == RESET)
        {
        }

        TimeOut = USER_TIMEOUT;

        while ((DMA_GetFlagStatus(SPIx_TX_DMA_FLAG_TC) == RESET) && (TimeOut != 0x00))
        {
        }

        if (TimeOut == 0)
        {
            TimeOut_UserCallback();
        }

        TimeOut = USER_TIMEOUT;

        while ((SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET) && (TimeOut != 0x00))
        {
        }

        if (TimeOut == 0)
        {
            TimeOut_UserCallback();
        }

        TimeOut = USER_TIMEOUT;

        while ((SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_BSY) == SET) && (TimeOut != 0x00))
        {
        }

        if (TimeOut == 0)
        {
            TimeOut_UserCallback();
        }

        /* Clear DMA1 global flags */
        DMA_ClearFlag(SPIx_TX_DMA_FLAG_GL);
        DMA_ClearFlag(SPIx_RX_DMA_FLAG_GL);
        /* Disable the DMA channels */
        DMA_Cmd(SPIx_RX_DMA_CHANNEL, DISABLE);
        DMA_Cmd(SPIx_TX_DMA_CHANNEL, DISABLE);
        /* Disable the SPI peripheral */
        SPI_Cmd(SPIy, DISABLE);
        /* Disable the SPI Rx and Tx DMA requests */
        SPIorI2S_DMACmd(SPIy, SPI_I2S_DMAReq_Rx, DISABLE);
        SPIorI2S_DMACmd(SPIy, SPI_I2S_DMAReq_Tx, DISABLE);
        /* DMA channel Rx of SPI Configuration */
        DMA_InitStructure.DMA_BufferSize = DATA_SIZE;
        DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPIx_DR_ADDRESS;
        DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxBuffer;
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
        DMA_InitStructure.DMA_Priority = DMA_Priority_High;
        DMA_Init(SPIx_RX_DMA_CHANNEL, &DMA_InitStructure);
        /* DMA channel Tx of SPI Configuration */
        DMA_InitStructure.DMA_BufferSize = DATA_SIZE;
        DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPIx_DR_ADDRESS;
        DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer;
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
        DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
        DMA_Init(SPIx_TX_DMA_CHANNEL, &DMA_InitStructure);
        /* Enable the SPI Rx and Rx DMA requests */
        SPIorI2S_DMACmd(SPIy, SPI_I2S_DMAReq_Rx, ENABLE);
        /* Enable the SPI Rx and Tx DMA requests */
        SPIorI2S_DMACmd(SPIy, SPI_I2S_DMAReq_Tx, ENABLE);
        /* Enable the SPI peripheral */
        SPI_Cmd(SPIy, ENABLE);
        /* Enable the DMA channels */
        DMA_Cmd(SPIx_RX_DMA_CHANNEL, ENABLE);
        DMA_Cmd(SPIx_TX_DMA_CHANNEL, ENABLE);
        TimeOut = USER_TIMEOUT;

        /* Wait the SPI DMA transfers complete or time out */
        while (DMA_GetFlagStatus(SPIx_RX_DMA_FLAG_TC) == RESET)
        {
        }

        if (TimeOut == 0)
        {
            TimeOut_UserCallback();
        }

        TimeOut = USER_TIMEOUT;

        while ((DMA_GetFlagStatus(SPIx_TX_DMA_FLAG_TC) == RESET) && (TimeOut != 0x00))
        {
        }

        if (TimeOut == 0)
        {
            TimeOut_UserCallback();
        }

        TimeOut = USER_TIMEOUT;

        while ((SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET) && (TimeOut != 0x00))
        {
        }

        if (TimeOut == 0)
        {
            TimeOut_UserCallback();
        }

        TimeOut = USER_TIMEOUT;

        while ((SPIorI2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_BSY) == SET) && (TimeOut != 0x00))
        {
        }

        if (TimeOut == 0)
        {
            TimeOut_UserCallback();
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
void GPIO_Config(void)
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
void SPI_Config(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    SPIy_RCC(SPIy_CLK, ENABLE);
    SPIz_RCC(SPIz_CLK, ENABLE);

    /* Enable the DMA peripheral */
    RCC_AHBPeriphClockCmd(DMAx_CLK, ENABLE);
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

    /* DMA Configuration -------------------------------------------------------*/
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize =  DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
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
#if (DEVICE == MASTER)

/**
  * @brief  Configures the TIM Peripheral.
  * @param  None
  * @retval None
  */
static void TIM_Config(void)
{
    /* TIM2 and TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* ---------------------------------------------------------------------------
      TIM2 Configuration: generate 1 PWM signals with 50% duty cycle.
      The TIM2CLK frequency is set to SystemCoreClock (Hz), to get TIM2 counter
      clock at 32 MHz the Prescaler is computed as following:
       - Prescaler = (TIM2CLK / TIM2 counter clock) - 1
      SystemCoreClock is set to 48 MHz for Ultra Low Power Medium-density devices.

      The TIM2 is running at 4 KHz: TIM2 Frequency = TIM2 counter clock/(TIM2_ARR + 1)
                                                   = 28 MHz / (TIM2_ARR +1) = 1 KHz
                                                   ==> TIM2_ARR + 1 = 28000
      TIM2 Channel2 duty cycle = (TIM2_CCR4/ TIM2_ARR)* 100 = 50%
      ==> TIM2_CCR4 = TIM2_ARR/2 = 14000
    ----------------------------------------------------------------------------*/
    PrescalerValue = (uint16_t) (SystemCoreClock / 1000) - 1;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = TIM_ARR;
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* TIM PWM1 Mode configuration: Channel */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = TIM_CCR;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIMx_CHANNEL_INIT(TIM2, &TIM_OCInitStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
#endif
/**
  * @brief  Configure a SysTick Base time to 10 ms.
  * @param  None
  * @retval None
  */
static void SysTickConfig(void)
{
    /* Setup SysTick Timer for 10ms interrupts  */
    if (SysTick_Config(SystemCoreClock / 100))
    {
        /* Capture error */
        while (1)
        {
        }
    }

    /* Configure the SysTick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x0);
}

/**
  * @brief  Basic management of the timeout situation.
  * @param  None
  * @retval None
  */
static void TimeOut_UserCallback(void)
{
    /* User can add his own implementation to manage TimeOut Communication failure */

    /* Block communication and all processes */
    while (1)
    {
    }
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



