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

/** @addtogroup RTC_StopWatch
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define RTC_TAMP         1
#define KEY1_HOLD_2S     2
#define KEY1_PRESS       3
#define RTC_BKP_DR_NUMBER              5  /* RTC Backup Data Register Number */

/* Uncomment the corresponding line to select the RTC Clock source */
#define RTC_CLOCK_SOURCE_LSE   /* LSE used as RTC source clock */
/* #define RTC_CLOCK_SOURCE_LSI */ /* LSI used as RTC source clock. The RTC Clock
                                      may varies due to LSI frequency dispersion. */


/* Private macro -------------------------------------------------------------*/
#define WATCH_DOG_LOG_CNT               ((uint32_t)2)
/* Private variables ---------------------------------------------------------*/
uint32_t BackupIndex = 0;
__IO uint32_t SubSecFrac = 0;
__IO uint8_t StartEvent = 0;
__IO uint8_t Button_State = 0;
__IO uint8_t Button_RTC = 0;
extern uint32_t TimeIncrase;
/* Define the backup register */
uint32_t BKPDataReg[5] = { RTC_BKP_DR0, RTC_BKP_DR1, RTC_BKP_DR2, RTC_BKP_DR3, RTC_BKP_DR4
                         };
/* Private function prototypes -----------------------------------------------*/
static void RTC_Config(void);
static void RTC_TamperConfig(void);
static void Key_Scan(void);
static void delay_ms(uint16_t seconds);

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
    RTC_TimeTypeDef  RTC_TimeStruct;
    USART_InitTypeDef USART_InitStructure;

    /* USARTx configured as follow:
          - BaudRate = 115200 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - No parity
          - Hardware flow control disabled (RTS and CTS signals)
          - Receive and transmit enabled
    */
    SysTick_Config(SystemCoreClock / 1000 - 1);
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);

    /* Output a message on Hyperterminal using printf function */
    printf("%s", "\r\n  *********************** RTC StopWatch Example ***********************\r\n");
    printf("%s", "\r\n  **   Press and hold KEY1 button(2s) to start the stopwatch         **\r\n");
    printf("%s", "\r\n  **   Press KEY1 button to log the stopwatch                        **\r\n");
    printf("%s", "\r\n  **   Press and hold TAMPER(KEY2) to stop the stopwatch             **\r\n");

    /* Configure the GPIO "Key1" buttons */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

    /* Configure the RTC peripheral by selecting the clock source */
    RTC_Config();

    /* Configure the RTC tamper register : To Clear all the Backup data register */
    RTC_TamperConfig();

    /* Initialize time Stucture */
    RTC_TimeStructInit(&RTC_TimeStruct);

    /* Infinite loop */
    while (1)
    {

        /* Check on the event 'start' */
        if (StartEvent == 0x0)
        {
            Key_Scan();
        }

        /* KEY1 button is pressed and hold over 2s*/
        if (Button_State == KEY1_HOLD_2S)
        {
            /* Configure the external interrupt "KEY1" buttons */
            HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_EXTI);

            /* Enable Tamper interrupt */
            RTC_ITConfig(RTC_IT_TAMP, ENABLE);

            /* Enabale the tamper 1 */
            RTC_TamperCmd(RTC_Tamper_1, ENABLE);

            /* start count */
            StartEvent = 0x1;

            /* Reinitialize Button_State variable */
            Button_State = 0;
            printf("\r\n Stopwatch is started! \r\n");
        }

        /* Right button is pressed */
        else if (Button_State == KEY1_PRESS)
        {
            if (BackupIndex < WATCH_DOG_LOG_CNT)
            {
                SubSecFrac = 0;

                /* Get the Current sub second and time */
                SubSecFrac = (((256 - (uint32_t)RTC_GetSubSecond()) * 1000) / 256);
                RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);

                /* Display result on the COM1 */
                printf("\r\n %2d:%2d:%2d:%3d", RTC_TimeStruct.RTC_Hours, RTC_TimeStruct.RTC_Minutes,
                       RTC_TimeStruct.RTC_Seconds, SubSecFrac);
                //if (BackupIndex < 2)
                {
                    /* Save time register  to Backup register ( the first 5 register is reserved for time) */
                    RTC_WriteBackupRegister(BKPDataReg[BackupIndex], (uint32_t)RTC->TR);

                    /* Save sub second time stamp register ( the latest 6 register is reserved for time) */
                    RTC_WriteBackupRegister(BKPDataReg[BackupIndex + 2], SubSecFrac);
                }
            }
            else
            {
                /* the backup register is full with 2trials */
                printf("%s", "\r\n  **   Press and hold TAMPER to stop the stopwatch                   **\r\n");
            }

            BackupIndex++;
            /* Reinitialize Button_State variable */
            Button_State = 0;
        }
        /* TAMPER button is pressed */
        else if (Button_RTC == RTC_TAMP)
        {
            /* reset Counter */
            BackupIndex = 0 ;
            /* Enetr to idle */
            StartEvent = 0x0;
            /* Enable Tamper interrupt */
            RTC_ITConfig(RTC_IT_TAMP, DISABLE);
            /* Enabale the tamper 1 */
            RTC_TamperCmd(RTC_Tamper_1, DISABLE);
            /* Reinitialize Button_RTC variable */
            Button_RTC = 0;
            printf("%s", "\r\n  **   Stopwatch Stoped and bkp register cleared                     **\r\n");
        }
    }
}

/**
  * @brief  RTC Tamper Configuration..
  * @param  None
  * @retval None
  */
static void RTC_TamperConfig(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* EXTI configuration *********************************************************/
    EXTI_ClearITPendingBit(EXTI_Line19);
    EXTI_InitStructure.EXTI_Line = EXTI_Line19;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable RTC_IRQn */
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* determines the number of active pulse for the specific level */
    RTC_TamperFilterConfig(RTC_TamperFilter_2Sample);

    /* Determines the frequency at which each of the tamper inputs are sampled */
    RTC_TamperSamplingFreqConfig(RTC_TamperSamplingFreq_RTCCLK_Div32768);
    RTC_TamperPullUpCmd(DISABLE);

    /* Select the tamper 1 with High level */
    RTC_TamperTriggerConfig(RTC_Tamper_1, RTC_TamperTrigger_LowLevel );

    /* Clear tamper 1 flag */
    RTC_ClearFlag(RTC_FLAG_TAMP1F);
}

/**
  * @brief  Configure the RTC peripheral by selecting the clock source.
  * @param  None
  * @retval None
  */
static void RTC_Config(void)
{
    RTC_InitTypeDef RTC_InitStructure;
    RTC_TimeTypeDef  RTC_TimeStruct;

    /* Enable the PWR clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Allow access to RTC */
    PWR_BackupAccessCmd(ENABLE);

    /* Enable the LSE OSC */
    RCC_LSEConfig(RCC_LSE_ON);

    /* Wait till LSE is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
    {
        ;
    }

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    RTC_DeInit();

    /* Configure the RTC data register and RTC prescaler */
    RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
    RTC_InitStructure.RTC_SynchPrediv  = 0xFF;
    RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;
    RTC_Init(&RTC_InitStructure);

    /* Set the time to 00h 00mn 00s AM */
    RTC_TimeStruct.RTC_H12     = RTC_H12_AM;
    RTC_TimeStruct.RTC_Hours   = 0x00;
    RTC_TimeStruct.RTC_Minutes = 0x00;
    RTC_TimeStruct.RTC_Seconds = 0x00;
    RTC_SetTime(RTC_Format_BCD, &RTC_TimeStruct);

    /* Enable the RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC APB registers synchronisation */
    RTC_WaitForSynchro();
}

/**
  * @brief  Get the KEY1 status.
  * @param  None
  * @retval None
  */
static void Key_Scan(void)
{
    if (GPIO_ReadInputDataBit(KEY1_BUTTON_GPIO_PORT, KEY1_BUTTON_PIN) == RESET)
    {
        delay_ms(2000);

        if ((GPIO_ReadInputDataBit(KEY1_BUTTON_GPIO_PORT, KEY1_BUTTON_PIN) == RESET) && (StartEvent == 0x0))
        {
            Button_State = KEY1_HOLD_2S ;
        }
        else
        {
            Button_State = 0;
        }
    }
}

/**
  * @brief  Systick delay .
  * @param  milliseconds: millisecond to delay.
  * @retval None
  */
static void delay_ms(uint16_t milliseconds)
{
    TimeIncrase = 0;
    SysTick->VAL = 0;

    while (TimeIncrase < milliseconds)
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

