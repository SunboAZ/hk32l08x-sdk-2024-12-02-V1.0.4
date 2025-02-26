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
/* Private macro -------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define SEND_LEN       1
#define BUTTON_SEL   BUTTON_KEY1
/* Private variables ---------------------------------------------------------*/
uint8_t WriteBuf[10] = {0x01, 0x02, 0x03, 0x04, 0x05};
uint8_t ReadBuf[10] = {0};
uint8_t RecvFlag = 0;

/* Private function prototypes -----------------------------------------------*/
static void DEBUG_USARTx_Config(uint32_t Baud);

void I2C_COMx_Config(void);
void I2C_COMx_Read(uint16_t SalveAddr, uint8_t* buffer, uint8_t Length);
void I2C_COMx_Write(uint16_t SalveAddr, uint8_t* buffer, uint8_t Length);
static void Delay(uint32_t i);
#ifndef I2C_MASTER
    static void Restore_Configuration(void);
#endif
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

    /* Initialize the I2C wakeup stop mode */
    I2C_COMx_Config();

    debug("I2C_WakeUpFromStop example is running!");

#ifdef I2C_MASTER /* I2C_MASTER */

    /* open LED1 and LED2 */
    HK_EVAL_LEDOn(LED1);
    HK_EVAL_LEDOn(LED2);

    while (1)
    {
        /* wait until Key button is pushed */
        while (HK_EVAL_PBGetState(BUTTON_SEL))
        {
        }

        /* send to slave device to wakeup slave */
        I2C_COMx_Write(SLAVEADDRESS, WriteBuf, SEND_LEN);
        printf("send msg to wakeup slave dvice!\n");

        /* Read the data returned by the slave */
        I2C_COMx_Read(SLAVEADDRESS, ReadBuf, SEND_LEN);

        /* Verify if the data is correct */
        if (ReadBuf[0] == WriteBuf[0])
        {
            printf("slave has already woken up and return data correct!\n");
            Delay(0xfffff);
        }
        else
        {
            printf("slave has already woken up but return data err!\n");
            Delay(0xfffff);
        }
    }

#else /* if HK32 device is set as Slave */
    /* enable I2C wakeup EXTI */
    EXTI_InitTypeDef  EXTI_InitStructure;
    EXTI_ClearITPendingBit(EXTI_Line23);
    EXTI_InitStructure.EXTI_Line = EXTI_Line23;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable I2C wakeup from stop mode. */
    I2C_StopModeCmd(I2C_COMx, ENABLE);

    /* close LED1 and LED2 */
    HK_EVAL_LEDOff(LED1);
    HK_EVAL_LEDOff(LED2);
    printf("system enter Stop mode!");

    /* enter STOP mode */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFE);

    /* Configure SystemClock to HSE48MHZ*/
    Restore_Configuration();

    /* wait SystemClock until stabilize */
    Delay(0xffff);

    /* wakeup will open LED1 and LED2 */
    HK_EVAL_LEDOn(LED1);
    HK_EVAL_LEDOn(LED2);

    printf("system Stop mode wakeup!\n");
    uint16_t direction = 0;

    while (1)
    {
        /* Address matching,clears ADDR flag
           note: we must clear the flag */
        if (I2C_GetFlagStatus(I2C_COMx, I2C_FLAG_ADDR))
        {
            I2C_ClearFlag(I2C_COMx, I2C_FLAG_ADDR);

            /* get transfer direction */
            direction = I2C_GetTransferDirection(I2C_COMx);
        }

        /* recv master data,just one data in this example */
        if (I2C_GetFlagStatus(I2C_COMx, I2C_FLAG_RXNE))
        {
            ReadBuf[0] = I2C_ReceiveData(I2C_COMx);
            RecvFlag = 1;
        }

        /* Send received data from master When reading from the master */
        if (RecvFlag &&  direction == I2C_Direction_Receiver)
        {
            RecvFlag = 0;

            /* just send one data in this example */
            while (I2C_GetFlagStatus(I2C_COMx, I2C_FLAG_TXIS) != SET)
            {

            }

            I2C_SendData(I2C_COMx, ReadBuf[0]);
            printf("send received data!");
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

    /* I2C CLOCK Enable */
    I2C_COMx_CLK_CMD(I2C_COMx_CLK, ENABLE);
    I2C_COMx_SCLIO_CLKCMD(I2C_COMx_SCL_IO_CLK, ENABLE);
    I2C_COMx_SDAIO_CLKCMD(I2C_COMx_SDA_IO_CLK, ENABLE);
    /*slect I2C hsi clock, I2C clock confirm here*/
    RCC_I2C1CLKConfig(I2C_COMx_STOPCLK);

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
    GPIO_PinAFConfig(I2C_COMx_SDA_IO_PORT, I2C_COMx_SDA_SOURCE, I2C_COMx_SDA_AF);
    GPIO_PinAFConfig(I2C_COMx_SCL_IO_PORT, I2C_COMx_SCL_SOURCE, I2C_COMx_SCL_AF);

    /* I2C Configuration */

    /* I2C speed 100KHz, I2C clock 8MHz, Rise time 100ns, Fall time 10ns, gain timing=0x00201D2B */
    I2C_InitStructure.I2C_Timing = 0x00201D2B;
    I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Disable;

    /* The digital filter function is not compatible with waking from stop mode function and needs to be set to 0 */
    I2C_InitStructure.I2C_DigitalFilter = 0;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
#ifdef I2C_MASTER
    I2C_InitStructure.I2C_OwnAddress1 = 0;                          /*master addres*/
#else
    I2C_InitStructure.I2C_OwnAddress1 = SLAVEADDRESS;               /*slave addres*/
#endif
    I2C_Init(I2C_COMx, &I2C_InitStructure);

    /* Clock extension must be enabled to ensure normal wake-up function from stop mode */
    I2C_StretchClockCmd(I2C_COMx, ENABLE);

    /* Enable I2C */
    I2C_Cmd(I2C_COMx, ENABLE);
}

/**
  * @brief  Reads a block of data from the I2C.
  * @param  SalveAddr:I2C slave addr
  * @param  buffer: pointer to the buffer that receives the data read from
  *         the I2C.
  * @param  Length: pointer to the variable holding number of bytes to
  *         be read from the I2C
  * @retval None
  */
void I2C_COMx_Read(uint16_t SalveAddr, uint8_t* buffer, uint8_t Length)
{
    uint8_t i;

    /* Check if the bus is busy */
    while (I2C_GetFlagStatus(I2C_COMx, I2C_FLAG_BUSY))
    {

    }

    /* Generate a start reading signal */
    I2C_TransferHandling(I2C_COMx, SalveAddr, Length, I2C_SoftEnd_Mode, I2C_Generate_Start_Read);

    /* Loop receive data */
    for (i = 0; i < Length; i++)
    {
        while (I2C_GetFlagStatus(I2C_COMx, I2C_FLAG_RXNE) == RESET)
        {
        }

        buffer[i] = I2C_ReceiveData(I2C_COMx);
    }

    /* generat stop signals */
    I2C_GenerateSTOP(I2C_COMx, ENABLE);

    /* As the host detects stop signals generated by peripherals */
    while (I2C_GetFlagStatus(I2C_COMx, I2C_FLAG_STOPF) == RESET)
    {

    }

    I2C_ClearFlag(I2C_COMx, I2C_FLAG_STOPF);
}

/**
  * @brief  Writes buffer of data to the I2C.
  * @param  SalveAddr:I2C slave addr
  * @param  buffer: pointer to the buffer containing the data to be written
  * @param  Length: number of bytes to write
  * @retval None
  */
void I2C_COMx_Write(uint16_t SalveAddr, uint8_t* buffer, uint8_t Length)
{
    uint8_t i;

    /* Check if the bus is busy */
    while (I2C_GetFlagStatus(I2C_COMx, I2C_FLAG_BUSY))
    {

    }

    /* Next, control the number of data written */
    I2C_TransferHandling(I2C_COMx, SalveAddr, Length, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);//I2C_No_StartStop);

    /* Loop sending data */
    for (i = 0; i < Length; i++)
    {
        while (I2C_GetFlagStatus(I2C_COMx, I2C_FLAG_TXIS) == RESET)
        {
        }

        I2C_SendData(I2C_COMx, buffer[i]);
    }

    /* generat stop signals */
    I2C_GenerateSTOP(I2C_COMx, ENABLE);

    /* As the host detects stop signals generated by peripherals */
    while (I2C_GetFlagStatus(I2C_COMx, I2C_FLAG_STOPF) == RESET)
    {

    }

    I2C_ClearFlag(I2C_COMx, I2C_FLAG_STOPF);
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

#ifndef I2C_MASTER
/**
  * @brief  Reconfiguration SystemClock
  * @param  None
  * @retval None
  */
static void Restore_Configuration(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */

    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= ((uint32_t)0x2) << FLASH_ACR_LATENCY_Pos;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

        /* PLL configuration: = HSE  * pllmul6 = 48 MHz */
        RCC->CFGR2 &= ~(RCC_CFGR2_PREDIV);
        RCC->CFGR2 |= (uint32_t)0x0 << RCC_CFGR2_PREDIV_Pos;

        RCC->CFGR4 &= ~RCC_CFGR4_PPSS;
        RCC->CFGR4 |= (uint32_t)0x0 << RCC_CFGR4_PPSS_Pos;

        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL));
        RCC->CFGR |= (uint32_t)((0x1 << RCC_CFGR_PLLSRC_Pos) | ((uint32_t)0x0 << RCC_CFGR_PLLXTPRE_Pos) | ((uint32_t)0x4 << RCC_CFGR_PLLMUL_Pos));

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= ~(RCC_CFGR_SW);
        RCC->CFGR |= (uint32_t)0x2 << RCC_CFGR_SW_Pos;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != ((uint32_t)0x2 << RCC_CFGR_SWS_Pos))
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}
#endif

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



