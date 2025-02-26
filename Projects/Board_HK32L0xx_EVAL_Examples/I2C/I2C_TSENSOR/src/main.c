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
#define TEMPERATURE_THYS     31
#define TEMPERATURE_TOS      32


/* Private variables ---------------------------------------------------------*/
__IO uint8_t SMbusAlertOccurred = 0;
static int32_t TempValue = 0, TempValueCelsius = 0, TempValueFahrenheit = 0;

uint8_t TempCelsiusSign = 0;   //Positive and negative temperature; 1: + , 0: -

/* Private function prototypes -----------------------------------------------*/
static void DEBUG_USARTx_Config(uint32_t Baud);

static void NVIC_Config(void);
static void Delay(uint32_t i);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* LED Init and close */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    HK_EVAL_LEDOff(LED1);
    HK_EVAL_LEDOff(LED2);

    /* USARTx Configured for printf */
    DEBUG_USARTx_Config(115200);

    /* NVIC Configuration */
    NVIC_Config();

    /* Initialize the Temperature Sensor */
    LM75_Init();

    debug("I2C_TSENSOR example is running!\n");

    if (LM75_GetStatus() == SUCCESS)
    {
        /* Configure the Temperature sensor device STLM75:
        - Thermostat mode Interrupt
        - Fault tolerance: 00
        */
        LM75_WriteConfReg(0x02);

        /* Configure the THYS and TOS in order to use the SMbus alert interrupt
           An SMBA interrupt occurs when the temperature exceeds the upper boundary
           and drops below the lower boundary */
        LM75_WriteReg(LM75_REG_THYS, TEMPERATURE_THYS << 8);   /* 31 C */
        LM75_WriteReg(LM75_REG_TOS, TEMPERATURE_TOS << 8);     /* 32 C */

        /* Enables the I2C SMBus Alert feature */
        I2C_SMBusAlertCmd(LM75_I2C, ENABLE);
        I2C_ClearFlag(LM75_I2C, I2C_FLAG_ALERT);

        SMbusAlertOccurred = 0;

        /* Enable SMBus Alert interrupt */
        I2C_ITConfig(LM75_I2C, I2C_IT_ERRI, ENABLE);

        printf("STLM75 Initialized successfully!");

        /* Infinite Loop */
        while (1)
        {
            /* Get double of Temperature value */
            TempValue = LM75_ReadTemp();

            /* get the Celsius degrees */
            if (TempValue <= 256)
            {
                /* Initialize the temperature sensor value*/
                TempValueCelsius = TempValue;
                TempCelsiusSign = 1;
            }
            else
            {
                /* Remove temperature value sign */
                TempValueCelsius = 0x200 - TempValue;
                TempCelsiusSign = 0;
            }

            /* Calculate temperature digits in Celsius and printf Celsius */
            if ((TempValueCelsius & 0x01) == 0x01)
            {
                if (TempCelsiusSign)
                {
                    printf("\n--centigrade??+%d.5\n", TempValueCelsius >> 1);
                }
                else
                {
                    printf("\n--centigrade??-%d.5\n", TempValueCelsius >> 1);
                }
            }
            else
            {
                if (TempCelsiusSign)
                {
                    printf("\n--centigrade??+%d.0\n", TempValueCelsius >> 1);
                }
                else
                {
                    printf("\n--centigrade??-%d.0\n", TempValueCelsius >> 1);
                }
            }

            /* Change to degrees Celsius */
            TempValueCelsius >>= 1;

            /* get the Fahrenheit degrees from it */
            if (TempValue > 256)
            {
                /* Conversion formula between Celsius and Fahrenheit degrees */
                if (((9 * TempValueCelsius) / 5) <= 32)
                {
                    /* Convert temperature centigrade to Fahrenheit */
                    TempValueFahrenheit = abs (32 - ((9 * TempValueCelsius) / 5));
                    printf("--Fahrenheit: +%d\n", TempValueFahrenheit);
                }
                else
                {
                    /* Convert temperature centigrade to Fahrenheit */
                    TempValueFahrenheit = abs(((9 * TempValueCelsius) / 5) - 32);

                    /* Calculate temperature digits in Fahrenheit */
                    printf("--Fahrenheit: -%d\n", TempValueFahrenheit);
                }

            }
            else
            {
                /* Convert temperature Celsius to Fahrenheit */
                TempValueFahrenheit = ((9 * TempValueCelsius) / 5) + 32;
                printf("--Fahrenheit: +%d\n", TempValueFahrenheit);
            }

            /* Alarm printf
               An SMBA interrupt occurs when the temperature exceeds the upper boundary
               and drops below the lower boundary */
            if (SMbusAlertOccurred == 1)
            {
                printf("Warning: Temp exceed");
                printf("      32 C      \n");
                HK_EVAL_LEDOn(LED1);
                HK_EVAL_LEDOn(LED2);
            }

            if (SMbusAlertOccurred == 2)
            {
                SMbusAlertOccurred = 0;
                HK_EVAL_LEDOff(LED1);
                HK_EVAL_LEDOff(LED2);
            }

            /* Delay cycle */
            Delay(0xFFFFFF);
        }
    }
    else
    {
        printf(" LM75 not correctly \n");
        printf(" Please restart the \n");
        printf(" example... \n");

        /* Infinite Loop */
        while (1)
        {
        }
    }

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
  * @brief  Configures the different interrupt.
  * @param  None
  * @retval None
  */
static void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Reconfigure and enable I2C1 error interrupt to have the higher priority */
    NVIC_InitStructure.NVIC_IRQChannel = I2C1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
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



