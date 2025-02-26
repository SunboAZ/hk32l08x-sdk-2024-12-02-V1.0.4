/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2024-01-14
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32l0xx_eval.h"

/** @addtogroup HK32L0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup RTC_Alarm
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define INIT_YEAR       2024
#define INIT_MONTH      1
#define INIT_DATE       1
#define INIT_WEEKDAY    RTC_Weekday_Monday
#define INIT_HOURS      0
#define INIT_MINUTES    0
#define INIT_SECONDS    0
#define INIT_AMPM       RTC_H12_AM
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
enum RTC_CLK_Source {RTC_NONE, RTC_MSI, RTC_LSI, RTC_LSE, RTC_HSE_DIV32};
const char* WeekDay[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
/* Private function prototypes -----------------------------------------------*/
static void USART_Config(void);
static void RTC_Config(enum RTC_CLK_Source RTC_CLK);
void Display_CurDateTime(void);
static uint8_t SetInitialTime(RTC_DateTypeDef *RTC_DateStruct, RTC_TimeTypeDef *RTC_TimeStruct);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_hk32l0xx.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_hk32l0xx.c file
       */
    USART_Config();
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);
    printf("\r\n ============== Real Time Clock Alarm ================");
    RTC_Config(RTC_LSE);

    /* Infinite loop */
    while (1)
    {
    }
}

/**
  * @brief  Configure RTC peripheral.
  * @param  RTC_CLK: Select the RTC clock from the following value.
  *            @arg : RTC_NONE
  *            @arg : RTC_MSI
  *            @arg : RTC_LSI
  *            @arg : RTC_LSE
  *            @arg : RTC_HSE_DIV32
  * @retval None
  */
static void RTC_Config(enum RTC_CLK_Source RTC_CLK)
{
    RTC_InitTypeDef  RTC_InitStruct;
    RTC_TimeTypeDef  RTC_TimeStruct;
    RTC_DateTypeDef  RTC_DateStruct;
    RTC_AlarmTypeDef RTC_AlarmStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    PWR_BackupAccessCmd(ENABLE);

    if (RTC_CLK == RTC_MSI)
    {
        RCC_MSIConfig(RCC_MSICLK_262K);
        RCC_MSICmd(ENABLE);

        while (RCC_GetFlagStatus(RCC_FLAG_MSIRDY) == RESET)
        {
        }

        RCC_RTCCLKConfig(RCC_RTCCLKSource_MSI);
    }
    else if (RTC_CLK == RTC_LSI)
    {
        RCC_LSICmd(ENABLE);

        while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
        {
        }

        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
    }
    else if (RTC_CLK == RTC_LSE)
    {
        RCC_LSEConfig(RCC_LSE_ON);

        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
        {
        }

        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    }
    else if (RTC_CLK == RTC_HSE_DIV32)
    {
        RCC_HSEConfig(RCC_HSE_ON);

        while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET)
        {
        }

        RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div32);
    }
    else
    {
        RCC->BDCR &= ~RCC_BDCR_RTC_SEL;
    }

    RCC_RTCCLKCmd(ENABLE);


    /*===================== Initialize Asyn & Syn Prescaler ======================*/
    /* Check if POR occured */
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
    {
        printf("\r\n\r\n Power On Reset occurred....");
        printf("\r\n RTC is configuring ...\r\n");
        RTC_InitStruct.RTC_AsynchPrediv = 127;
        RTC_InitStruct.RTC_HourFormat = RTC_HourFormat_24;
        RTC_InitStruct.RTC_SynchPrediv = 255;
        RTC_Init(&RTC_InitStruct);

        RTC_TimeStruct.RTC_H12 = RTC_H12_AM;
        RTC_TimeStruct.RTC_Hours = INIT_HOURS;
        RTC_TimeStruct.RTC_Minutes = INIT_MINUTES;
        RTC_TimeStruct.RTC_Seconds = INIT_SECONDS;

        RTC_DateStruct.RTC_Date = INIT_DATE;
        RTC_DateStruct.RTC_Month = INIT_MONTH;
        RTC_DateStruct.RTC_WeekDay = INIT_WEEKDAY;
        RTC_DateStruct.RTC_Year = 00;

        if (SetInitialTime(&RTC_DateStruct, &RTC_TimeStruct))
        {
            printf("\r\n RTC Set Initial DateTime Failed....");

            while (1)
            {
            }
        };

        printf("\r\n RTC configure Done....");
    }

    /* Check if PIN-Reset occured*/
    else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
    {
        printf("\r\n\r\n External Reset occurred....");
        printf("\r\n No need to configure RTC....");
    }

    /* Clear the MCU Reset Flags */
    RCC_ClearFlag();

    /* Display the Current Date/Time At the beginning of the process */
    Display_CurDateTime();

    /* Reflush the Date/Time Structure */
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);

    /* Set AlarmA 20s later ,Set AlarmB 30s later */
    RTC_AlarmCmd(RTC_Alarm_A | RTC_Alarm_B, DISABLE);
    RTC_AlarmStruct.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
    RTC_AlarmStruct.RTC_AlarmDateWeekDay = RTC_DateStruct.RTC_Date;
    RTC_AlarmStruct.RTC_AlarmMask = RTC_AlarmMask_None;
    RTC_AlarmStruct.RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
    RTC_AlarmStruct.RTC_AlarmTime.RTC_Hours = RTC_TimeStruct.RTC_Hours;
    RTC_AlarmStruct.RTC_AlarmTime.RTC_Minutes = RTC_TimeStruct.RTC_Minutes;
    RTC_AlarmStruct.RTC_AlarmTime.RTC_Seconds = RTC_TimeStruct.RTC_Seconds + 20;
    RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStruct);

    RTC_AlarmStruct.RTC_AlarmTime.RTC_Seconds = RTC_TimeStruct.RTC_Seconds + 30;
    RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_B, &RTC_AlarmStruct);

    /* Enable AlarmA and AlarmB*/
    RTC_AlarmCmd(RTC_Alarm_A | RTC_Alarm_B, ENABLE);

    /* Set IT for AlarmA and AlarmB*/
    RTC_ITConfig(RTC_IT_ALRA | RTC_IT_ALRB, ENABLE);

    /* RTC Alarm Interrupt Line is Combined with EXTI Line17*/
    EXTI_InitStruct.EXTI_Line = EXTI_Line17;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStruct);

    /* NVIC configuration */
    NVIC_InitStruct.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPriority = 0x0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}


/**
  * @brief  Print the current time at Debug_Com.
  * @param  None
  * @retval None
  */
void Display_CurDateTime(void)
{
    __IO uint32_t timeout = 0x00;
    RTC_DateTypeDef RTC_DateStruct;
    RTC_TimeTypeDef RTC_TimeStruct;

    while (!RTC_WaitForSynchro())
    {
        timeout++;

        if (timeout == 0xffff)
        {
            return;
        }
    }

    RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
    printf("\r\n\r\n TIME NOW: %04d/%02d/%02d   %s    ", (RTC_DateStruct.RTC_Year + INIT_YEAR), RTC_DateStruct.RTC_Month, RTC_DateStruct.RTC_Date, WeekDay[RTC_DateStruct.RTC_WeekDay - 1]);
    printf("%02d:%02d:%02d\r\n\r\n", RTC_TimeStruct.RTC_Hours, RTC_TimeStruct.RTC_Minutes, RTC_TimeStruct.RTC_Seconds);
}




/**
  * @brief  Set time and date during RTC initialization.
  * @param  *RTC_DateStruct: The pointer to RTC Date structure
  *         including Year,month,date,weekday.
  * @param  *RTC_TimeStruct: The pointer to RTC Time structure
  *         including Hour,minutes,Seconds,AM/PM.
  * @retval An ErrorStatus enumeration value:
  *         - 0: RTC Date register is configured
  *         - 1: RTC Date register is not configured
  */
static uint8_t SetInitialTime(RTC_DateTypeDef *RTC_DateStruct, RTC_TimeTypeDef *RTC_TimeStruct)
{
    __IO uint32_t timeout = 0x00;

    while (!RTC_SetDate(RTC_Format_BIN, RTC_DateStruct))
    {
        timeout++;

        if (timeout == 0xffff)
        {
            return 1;
        }
    }

    timeout = 0;

    while (!RTC_SetTime(RTC_Format_BIN, RTC_TimeStruct))
    {
        timeout++;

        if (timeout == 0xffff)
        {
            return 1;
        }
    }

    return 0;
}


/**
  * @brief  Configure USART peripheral, used to print.
  * @param  None
  * @retval None
  */
static void USART_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    //ErrorStatus ErrLog;

    /* USARTx configured as follow:
          - BaudRate = 115200 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - No parity
          - Hardware flow control disabled (RTS and CTS signals)
          - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);
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
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    while (1)
    {
    }
}
#endif /* USE_FULL_ASSERT */


/**
  * @}
  */

/**
  * @}
  */



