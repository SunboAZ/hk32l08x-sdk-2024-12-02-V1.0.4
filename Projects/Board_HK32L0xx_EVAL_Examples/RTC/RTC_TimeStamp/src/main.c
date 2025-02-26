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

/** @addtogroup RTC_TimerStamp
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TAMPER_ON   1
#define SEL_ON      2
/* Uncomment the corresponding line to select the RTC Clock source */
#define RTC_CLOCK_SOURCE_LSE   /* LSE used as RTC source clock */
//#define RTC_CLOCK_SOURCE_LSI  // LSI used as RTC source clock. The RTC Clock
// may varies due to LSI frequency dispersion

#define BKP_VALUE    0x32F2
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t AsynchPrediv = 0, SynchPrediv = 0;
__IO uint8_t Button_State = 0;
/* Private function prototypes -----------------------------------------------*/
static void RTC_Config(void);
static void RTC_TimeRegulate(void);
static void RTC_TimeShow(void);
static void RTC_DateShow(void);
static void RTC_TimeStampShow(void);

static void RTC_IntrInit(void);
static void RTC_Wait(void);


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

    /* Configure LEDs */
    HK_EVAL_LEDOn(LED1);

    /* Output a message on Hyperterminal using printf function */
    printf("\r\n  *********************** RTC TimeStamp Example ***********************\r\n");

    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
    {
        printf("\r\n\r\n Power On Reset occurred....");
        printf("\r\n RTC is configuring ...\r\n");

        /* RTC configuration  */
        RTC_Config();

        /* Configure the time register */
        RTC_TimeRegulate();
    }
    else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
    {
        printf("\r\n External Reset occurred....\r\n");
        printf("\r\n No need to configure RTC....\r\n");

        /* Enable the PWR clock */
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

        /* Allow access to RTC */
        PWR_BackupAccessCmd(ENABLE);
#ifdef RTC_CLOCK_SOURCE_LSI

        /* Enable the LSI OSC */
        RCC_LSICmd(ENABLE);
#endif /* RTC_CLOCK_SOURCE_LSI */

        /* Wait for RTC APB registers synchronisation */
        RTC_WaitForSynchro();

        /* Display the RTC Time/Date and TimeStamp Time/Date */
        RTC_DateShow();
        RTC_TimeShow();
    }

    /* Clear the MCU Reset Flags */
    RCC_ClearFlag();

    RTC_IntrInit();

    printf("\r\n RTC Configuration Done! Press RTC_TS pin to Trigger a TS event....\r\n");

    /* Infinite loop */
    while (1)
    {
        if (Button_State == TAMPER_ON)
        {
            /* Turn LED1 ON */
            HK_EVAL_LEDToggle(LED1);

            printf("\n\r TimeStamp Event Occurred" );

            Button_State = 0;
            RTC_Wait();
            RTC_TimeStampShow();
            RTC_ClearFlag((RTC_FLAG_TSF | RTC_FLAG_TSOVF));
        }
    }
}

/**
  * @brief  Configure the RTC peripheral by selecting the clock source.
  * @param  None
  * @retval None
  */
static void RTC_Config(void)
{
    RTC_InitTypeDef RTC_InitStructure;

    /* Enable the PWR clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Allow access to RTC */
    PWR_BackupAccessCmd(ENABLE);
    RCC_BackupResetCmd(ENABLE);
    RCC_BackupResetCmd(DISABLE);
#if defined (RTC_CLOCK_SOURCE_LSE) /* LSE used as RTC source clock */

    /* Enable the LSE OSC */
    RCC_LSEConfig(RCC_LSE_ON);

    /* Wait till LSE is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
    {
    }

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

    /* Enable the RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* ck_spre(1Hz) = RTCCLK(LSE) /(AsynchPrediv + 1)*(SynchPrediv + 1)*/
    SynchPrediv = 0xFF;
    AsynchPrediv = 0x7F;
#elif defined (RTC_CLOCK_SOURCE_LSI)  /* LSI used as RTC source clock*/

    /* The RTC Clock may varies due to LSI frequency dispersion. */

    /* Enable the LSI OSC */
    RCC_LSICmd(ENABLE);

    /* Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {
    }

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

    /* ck_spre(1Hz) = RTCCLK(LSI) /(AsynchPrediv + 1)*(SynchPrediv + 1)*/
    SynchPrediv = 0xFF;
    AsynchPrediv = 0x7F;
#else
#error Please select the RTC Clock source inside the main.c file
#endif /* RTC_CLOCK_SOURCE_LSE */

    /* Configure the RTC data register and RTC prescaler */
    RTC_InitStructure.RTC_AsynchPrediv = AsynchPrediv;
    RTC_InitStructure.RTC_SynchPrediv = SynchPrediv;
    RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;

    /* Check on RTC init */
    if (RTC_Init(&RTC_InitStructure) == ERROR)
    {
        printf("\n\r RTC Prescaler Conf failed" );
    }

    /* Wait for RTC APB registers synchronisation */
    RTC_WaitForSynchro();
}

/**
  * @brief  Returns the time entered by user, using Hyperterminal.
  * @param  None
  * @retval None
  */
static void RTC_TimeRegulate(void)
{
    RTC_TimeTypeDef RTC_TimeStructure;
    RTC_DateTypeDef RTC_DateStructure;

    /* Set Time hh:mm:ss */
    RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
    RTC_TimeStructure.RTC_Hours   = 0x08;
    RTC_TimeStructure.RTC_Minutes = 0x10;
    RTC_TimeStructure.RTC_Seconds = 0x00;
    RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);

    /* Set Date Week/Date/Month/Year */
    RTC_DateStructure.RTC_WeekDay = 01;
    RTC_DateStructure.RTC_Date = 0x31;
    RTC_DateStructure.RTC_Month = 0x12;
    RTC_DateStructure.RTC_Year = 0x12;
    RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);

    /* Write BkUp DR0 */
    RTC_WriteBackupRegister(RTC_BKP_DR0, BKP_VALUE);
}

/**
  * @brief  Display the current time on the Hyperterminal.
  * @param  None
  * @retval None
  */
static void RTC_TimeShow(void)
{
    RTC_TimeTypeDef RTC_TimeStructure;

    /* Get the current Time */
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
    printf("\n\r  The current time is :  %0.2d:%0.2d:%0.2d \n\r", RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds);
}

/**
  * @brief  Display the current date on the Hyperterminal.
  * @param  None
  * @retval None
  */
static void RTC_DateShow(void)
{
    RTC_DateTypeDef RTC_DateStructure;
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
    printf("\n\r  Current Date:  %0.2d-%0.2d-%0.2d (YY-MM-DD)\n\r", RTC_DateStructure.RTC_Year, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date);
}

/**
  * @brief  Display the current TimeStamp (time and date) on the Hyperterminal.
  * @param  None
  * @retval None
  */
static void RTC_TimeStampShow(void)
{
    RTC_TimeTypeDef  RTC_TimeStampStructure;
    RTC_DateTypeDef  RTC_TimeStampDateStructure;
    RTC_GetTimeStamp(RTC_Format_BIN, &RTC_TimeStampStructure, &RTC_TimeStampDateStructure);
    printf("\n\r  The TimeStamp is: %0.2d-%0.2d %0.2d:%0.2d:%0.2d \n\r", RTC_TimeStampDateStructure.RTC_Month, RTC_TimeStampDateStructure.RTC_Date,
           RTC_TimeStampStructure.RTC_Hours, RTC_TimeStampStructure.RTC_Minutes, RTC_TimeStampStructure.RTC_Seconds);
    //printf("\r\n ISR: 0x%08X", RTC->ISR);
}

/**
  * @brief  Init RTC TS Interrupt
  * @param  None
  * @retval None
  */
static void RTC_IntrInit(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef  EXTI_InitStructure;

    /* Enable The TimeStamp */
    RTC_TimeStampCmd(RTC_TimeStampEdge_Falling, DISABLE);

    /* Enable The external line19 interrupt */
    EXTI_ClearITPendingBit(EXTI_Line19);

    EXTI_InitStructure.EXTI_Line = EXTI_Line19;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Clear TSF&TSOVF flag */
    RTC_ClearFlag((RTC_FLAG_TSF | RTC_FLAG_TSOVF));

    /* Enable RTC IRQChannel */
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    RTC_ITConfig(RTC_IT_TS, ENABLE);

    /* Enable The TimeStamp */
    RTC_TimeStampCmd(RTC_TimeStampEdge_Falling, ENABLE);
}


/**
  * @brief  Time Delay
  * @retval None
  */
static void RTC_Wait(void)
{
    uint32_t i;

    for (i = 0; i < 0xffff; i++)
    {
        ;
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
        ;
    }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

