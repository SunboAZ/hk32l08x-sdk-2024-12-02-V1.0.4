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
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BUTTON_SEL BUTTON_KEY1
DMA_InitTypeDef  DMA_InitStructure;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t RecvFlag = 0;
uint8_t SendFlag = 0;
uint16_t direction = 0;

uint8_t I2C_SENDBUF[64] = {0x01, 0x02, 0x03, 0x04, 0x05};
uint8_t I2C_RECVBUF[64] = {0};

/* Private function prototypes -----------------------------------------------*/
static void DEBUG_USARTx_Config(uint32_t Baud);

void I2C_COMx_Config(void);
void I2C_COMx_StartRead(uint16_t SalveAddr, uint8_t Length);
void I2C_COMx_StartWrite(uint16_t SalveAddr, uint8_t Length);
void I2C_COMx_DMA_Send(uint8_t *sendbuf, uint16_t sendlen);
void I2C_COMx_DMA_Recv(uint8_t *recvbuf, uint16_t recvlen);

static uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
static void Delay(uint32_t i);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* LED Init */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    /* Configure the Push buttons in Polling mode */
    HK_EVAL_PBInit(BUTTON_SEL, BUTTON_MODE_GPIO);

    /* USARTx Configured for printf */
    DEBUG_USARTx_Config(115200);

    /* Initialize the I2C and its interrupt */
    I2C_COMx_Config();
    Delay(0xfff);

    /* close LED1 and LED2 */
    HK_EVAL_LEDOff(LED1);
    HK_EVAL_LEDOff(LED2);

    debug("I2C_TwoBoardsExchangeDMA example is running!");

#ifdef I2C_MASTER /* I2C_MASTER */

    while (1)
    {
        /* Waiting transaction code in case of I2C receiver */

        /* DMA channel Rx of I2C Configuration and ready to recv */
        I2C_COMx_DMA_Recv(I2C_RECVBUF, SEND_LEN);

        /* wait until Key button is pushed */
        while (HK_EVAL_PBGetState(BUTTON_SEL))
        {
        }

        /* Preparing to send data to slave */
        I2C_COMx_StartWrite(SLAVEADDRESS, SEND_LEN);
        I2C_COMx_DMA_Send(I2C_SENDBUF, SEND_LEN);

        /* Waiting for sending to complete */
        while (I2C_GetFlagStatus(I2C_COMx, I2C_FLAG_TC) != SET)
        {

        }

        /* Generate stop signal */
        I2C_GenerateSTOP(I2C_COMx, ENABLE);

        printf("send msg to slave dvice finsh!\n");

        /* Preparing to Read the data returned by the slave */
        I2C_COMx_StartRead(SLAVEADDRESS, SEND_LEN);

        /* wati until data recv finsh */
        while (RecvFlag != 1)
        {
        }

        /* Verify if the data is correct */
        if (Buffercmp(I2C_SENDBUF, I2C_RECVBUF, SEND_LEN))
        {
            printf("slave return data correct!\n");
            HK_EVAL_LEDOn(LED1);
            HK_EVAL_LEDOn(LED2);
            Delay(0xfffff);
        }
        else
        {
            printf("slave return data err!\n");
            HK_EVAL_LEDOff(LED1);
            HK_EVAL_LEDOff(LED2);
            Delay(0xfffff);
        }

        /* clear recv flag */
        RecvFlag = 0;
        memset(I2C_RECVBUF, 0, SEND_LEN);
    }

#else /* if HK32 device is set as Slave */

    while (1)
    {
        /* Waiting transaction code in case of I2C receiver */

        /* DMA channel Rx of I2C Configuration and ready to recv */
        I2C_COMx_DMA_Recv(I2C_RECVBUF, SEND_LEN);

        /* wati until data recv finsh */
        while (RecvFlag != 1)
        {

        }

        while (1)
        {

            /* handle data from master with master read data */
            if (RecvFlag && direction == I2C_Direction_Receiver)
            {
                RecvFlag = 0;

                /* return received data to master */
                I2C_COMx_DMA_Send(I2C_RECVBUF, SEND_LEN);

                /* wati until data send finsh */
                while (SendFlag != 1)
                {
                }

                SendFlag = 0;
                printf("slave return received data finsh!");

                /* Verify if the data is correct */
                if (Buffercmp(I2C_SENDBUF, I2C_RECVBUF, SEND_LEN))
                {
                    printf("slave recv data correct!\n");
                    HK_EVAL_LEDOn(LED1);
                    HK_EVAL_LEDOn(LED2);
                }
                else
                {
                    printf("slave recv data err!\n");
                    HK_EVAL_LEDOff(LED1);
                    HK_EVAL_LEDOff(LED2);
                }

                memset(I2C_RECVBUF, 0, SEND_LEN);
                break;
            }
        }
    }

#endif
}

/**
  * @brief  Configure the USARTx Device for printf
  * @param  Baud: The USARTx BaudRate
  * @retval None
  */
static void DEBUG_USARTx_Config(uint32_t Baud)
{
    USART_InitTypeDef USART_InitStructure;

    /* USARTx configured as follow:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1 Stop Bit
    - Parity = No Parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = Baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);
}


/**
  * @brief  Initializes peripherals used by the I2C EEPROM driver.
  * @param  None
  * @retval None
  */
void I2C_COMx_Config(void)
{
    I2C_InitTypeDef   I2C_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;

    /* I2C CLOCK Enable */
    I2C_COMx_CLK_CMD(I2C_COMx_CLK, ENABLE);
    I2C_COMx_SCLIO_CLKCMD(I2C_COMx_SCL_IO_CLK, ENABLE);
    I2C_COMx_SDAIO_CLKCMD(I2C_COMx_SDA_IO_CLK, ENABLE);

    RCC_I2C1CLKConfig(RCC_I2C1CLK_SYSCLK);

    /* I2C GPIO Configuration */
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_PuPd    =  GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Pin     = I2C_COMx_SCL_PIN;
    GPIO_Init(I2C_COMx_SCL_IO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin     = I2C_COMx_SDA_PIN;
    GPIO_Init(I2C_COMx_SDA_IO_PORT, &GPIO_InitStructure);

    /* I2C Pxx connect to SDA and SCL */
    GPIO_PinAFConfig(I2C_COMx_SDA_IO_PORT, I2C_COMx_SDA_SOURCE, I2C_COMx_SDA_AF); /*SDA*/
    GPIO_PinAFConfig(I2C_COMx_SCL_IO_PORT, I2C_COMx_SCL_SOURCE, I2C_COMx_SCL_AF); /*SCL*/

    /*SYSCFG_I2CFastModePlusConfig(SYSCFG_I2CFastModePlus_I2C1, ENABLE); // config I2C FastMode(1MHz)*/

    /* I2C Configuration */

    /* I2C speed 100KHz, I2C clock 48MHz, Rise time 100ns, Fall time 10ns, gain timing=0x10805E89 */
    I2C_InitStructure.I2C_Timing = 0x10805E89;
    I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;

    /* The digital filter function is not compatible with waking from stop mode function
       and needs to be set to 0 */
    I2C_InitStructure.I2C_DigitalFilter = 0;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
#ifdef I2C_MASTER
    I2C_InitStructure.I2C_OwnAddress1 = 0;                          /*master addres*/
#else
    I2C_InitStructure.I2C_OwnAddress1 = SLAVEADDRESS;               /*slave addres*/
#endif
    I2C_Init(I2C_COMx, &I2C_InitStructure);

#if I2C_COMx_DMAENABLE /*I2C DMA use or not*/
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, ENABLE);

    /* DMA basic configuration */
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralInc =  DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

    /* To use I2C1 DMA, remapping needs to be enabled */
    DMA_RemapConfig(DMA, DMA_CSELR_CH6_I2C1_TX);
    DMA_RemapConfig(DMA, DMA_CSELR_CH7_I2C1_RX);

    NVIC_InitStructure.NVIC_IRQChannel = I2C_COMx_DMATX_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* I2C DMA interrupt config */
    DMA_ITConfig(I2C_COMx_DMATX_Channel, DMA_IT_TC, ENABLE);
    DMA_ITConfig(I2C_COMx_DMARX_Channel, DMA_IT_TC, ENABLE);
    DMA_ClearFlag(I2C_COMx_TX_DMA_FLAG_TC);
    DMA_ClearFlag(I2C_COMx_RX_DMA_FLAG_TC);

#endif


#ifndef I2C_MASTER

    NVIC_InitStructure.NVIC_IRQChannel = I2C_COMx_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* I2C interrupt config */
    I2C_ITConfig(I2C_COMx, I2C_IT_ADDRI, ENABLE);
#endif

    /* Enable I2C */
    I2C_Cmd(I2C_COMx, ENABLE);
}

/**
  * @brief  The I2C_COMx dma send msg handle
  * @param  sendbuf:The buffer ready to send
  * @param  sendlen:The buffer length
  * @retval None.
  */
void I2C_COMx_DMA_Send(uint8_t *sendbuf, uint16_t sendlen)
{
    /* Clear DMA1 global flags */
    DMA_ClearFlag(I2C_COMx_TX_DMA_FLAG_GL);

    /* Disable the DMA channels */
    DMA_Cmd(I2C_COMx_DMATX_Channel, DISABLE);

    /* Disable the I2C Tx DMA request */
    I2C_DMACmd(I2C_COMx, I2C_DMAReq_Tx, DISABLE);

    /* DMA channel Tx of USART Configuration */
    /*DMA_DeInit(I2C_COMx_DMATX_Channel);   //it will close all interrupt*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = I2C_COMx_TDR_ADDRESS;
    DMA_InitStructure.DMA_BufferSize = sendlen;
    DMA_InitStructure.DMA_MemoryBaseAddr =  (uint32_t)sendbuf;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_Init(I2C_COMx_DMATX_Channel, &DMA_InitStructure);
    I2C_DMACmd(I2C_COMx, I2C_DMAReq_Tx, ENABLE);
    DMA_ITConfig(I2C_COMx_DMATX_Channel, DMA_IT_TC, ENABLE);

    /* Enable DMA1 USART Tx Channel */
    DMA_Cmd(I2C_COMx_DMATX_Channel, ENABLE);
}


/**
  * @brief  The I2C_COMx dma ready to recv msg
  * @param  recvbuf:Set buffer ready to reception
  * @param  recvlen:The buffer length
  * @retval None.
  */
void I2C_COMx_DMA_Recv(uint8_t *recvbuf, uint16_t recvlen)
{
    /* Clear DMA1 global flags */
    DMA_ClearFlag(I2C_COMx_RX_DMA_FLAG_GL);

    /* Disable the DMA channels */
    DMA_Cmd(I2C_COMx_DMARX_Channel, DISABLE);

    /* Disable the I2C Tx DMA request */
    I2C_DMACmd(I2C_COMx, I2C_DMAReq_Rx, DISABLE);

    /* DMA channel Tx of USART Configuration */
    /*DMA_DeInit(I2C_COMx_DMARX_Channel);   //it will close all interrupt*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = I2C_COMx_RDR_ADDRESS;
    DMA_InitStructure.DMA_BufferSize = recvlen;
    DMA_InitStructure.DMA_MemoryBaseAddr =  (uint32_t)recvbuf;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_Init(I2C_COMx_DMARX_Channel, &DMA_InitStructure);
    I2C_DMACmd(I2C_COMx, I2C_DMAReq_Rx, ENABLE);
    DMA_ITConfig(I2C_COMx_DMARX_Channel, DMA_IT_TC, ENABLE);

    /* Enable DMA1 USART Tx Channel */
    DMA_Cmd(I2C_COMx_DMARX_Channel, ENABLE);
}
/**
  * @brief  Reads a block of data from the I2C.
  * @param  SalveAddr:I2C slave addr
  * @param  Length: pointer to the variable holding number of bytes to
  *         be read from the I2C
  * @retval None.
  */
void I2C_COMx_StartRead(uint16_t SalveAddr, uint8_t Length)
{
    /* Check if the bus is busy */
    while (I2C_GetFlagStatus(I2C_COMx, I2C_FLAG_BUSY))
    {

    }

    /* Generate a start reading signal */
    I2C_TransferHandling(I2C_COMx, SalveAddr, Length, I2C_SoftEnd_Mode, I2C_Generate_Start_Read);
}

/**
  * @brief  Writes buffer of data to the I2C.
  * @param  SalveAddr:I2C slave addr
  * @param  Length: number of bytes to write
  * @retval None
  */
void I2C_COMx_StartWrite(uint16_t SalveAddr, uint8_t Length)
{
    /* Check if the bus is busy */
    while (I2C_GetFlagStatus(I2C_COMx, I2C_FLAG_BUSY))
    {

    }

    /* Next, control the number of data written */
    I2C_TransferHandling(I2C_COMx, SalveAddr, Length, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval 1: pBuffer1 identical to pBuffer2
  *         0: pBuffer1 differs from pBuffer2
  */
static uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return 0;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return 1;
}

/**
  * @brief  Simple Delay
  * @param  None
  * @retval None
  */
static void Delay(uint32_t i)
{
    while (i--)
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



