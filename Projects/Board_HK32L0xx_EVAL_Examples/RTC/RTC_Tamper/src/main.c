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

/** @addtogroup RTC_Tamper
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define RTC_BKP_DR_NUMBER              5  /* RTC Backup Data Register Number */

/* Uncomment the corresponding line to select the RTC Clock source */
#define RTC_CLOCK_SOURCE_LSE   /* LSE used as RTC source clock */
/* #define RTC_CLOCK_SOURCE_LSI */ /* LSI used as RTC source clock. The RTC Clock
                                      may varies due to LSI frequency dispersion. */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t RTC_BKP_DR[RTC_BKP_DR_NUMBER] =
{
    RTC_BKP_DR0, RTC_BKP_DR1, RTC_BKP_DR2, RTC_BKP_DR3, RTC_BKP_DR4
};

/* Private function prototypes -----------------------------------------------*/
static void RTC_Config(void);
static void WriteToRTC_BKP_DR(uint32_t FirstRTCBackupData);
static uint32_t CheckRTC_BKP_DR(uint32_t FirstRTCBackupData);

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
    printf("%s", "\r\n  *********************** RTC Tamper Example ***********************\r\n");

    /* RTC configuration */
    RTC_Config();

    /* Write To RTC Backup Data registers */
    WriteToRTC_BKP_DR(0xA53C);

    /* Check if the written data are correct */
    if (CheckRTC_BKP_DR(0xA53C) == 0x00)
    {
        printf("%s", "\r\n  **   BKP_DR written data are correct!                           **\r\n");
    }
    else
    {
        printf("%s", "\r\n  **   BKP_DR written data are not correct!                       **\r\n");
    }

    /* Infinite loop */
    while (1)
    {
        ;
    }
}

/**
  * @brief  Configure the RTC peripheral by selecting the clock source.
  * @param  None
  * @retval None
  */
static void RTC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef  EXTI_InitStructure;

    /* Enable the PWR clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Allow access to RTC */
    PWR_BackupAccessCmd(ENABLE);

#if defined (RTC_CLOCK_SOURCE_LSI)  /* LSI used as RTC source clock*/

    /* The RTC Clock may varies due to LSI frequency dispersion. */

    /* Enable the LSI OSC */
    RCC_LSICmd(ENABLE);

    /* Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {
        ;
    }

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
#elif defined (RTC_CLOCK_SOURCE_LSE) /* LSE used as RTC source clock */

    /* Enable the LSE OSC */
    RCC_LSEConfig(RCC_LSE_ON);

    /* Wait till LSE is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
    {
        ;
    }

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
#else
#error Please select the RTC Clock source inside the main.c file
#endif /* RTC_CLOCK_SOURCE_LSI */

    /* Enable The external line19 interrupt */
    EXTI_ClearITPendingBit(EXTI_Line19);
    EXTI_InitStructure.EXTI_Line = EXTI_Line19;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable RTC IRQChannel */
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Disable the Tamper 1 detection */
    RTC_TamperCmd(RTC_Tamper_1, DISABLE);

    /* Clear Tamper 1 pin Event(TAMP1F) pending flag */
    RTC_ClearFlag(RTC_FLAG_TAMP1F);

    /* Configure the Tamper 1 Trigger */
    RTC_TamperTriggerConfig(RTC_Tamper_1,  RTC_TamperTrigger_RisingEdge);

    /* Enable the Tamper interrupt */
    RTC_ITConfig(RTC_IT_TAMP, ENABLE);

    /* Clear Tamper 1 pin interrupt pending bit */
    RTC_ClearITPendingBit(RTC_IT_TAMP1);

    /* Enable the Tamper 1 detection */
    RTC_TamperCmd(RTC_Tamper_1, ENABLE);
}

/**
  * @brief  Writes data RTC Backup DRx registers.
  * @param  FirstRTCBackupData: data to be written to RTC Backup data registers.
  * @retval None
  */
static void WriteToRTC_BKP_DR(uint32_t FirstRTCBackupData)
{
    uint32_t index = 0;

    for (index = 0; index < RTC_BKP_DR_NUMBER; index++)
    {
        /* write To bkp data register */
        RTC_WriteBackupRegister(RTC_BKP_DR[index], FirstRTCBackupData + (index * 0x5A));
    }
}

/**
  * @brief  Checks if the RTC Backup DRx registers values are correct or not.
  * @param  FirstRTCBackupData: data to be compared with RTC Backup data registers.
  * @retval - 0: All RTC Backup DRx registers values are correct
  *         - Value different from 0: Number of the first Backup register
  *         which value is not correct
  */
static uint32_t CheckRTC_BKP_DR(uint32_t FirstRTCBackupData)
{
    uint32_t index = 0;

    for (index = 0; index < RTC_BKP_DR_NUMBER; index++)
    {
        /* Read from data register */
        if (RTC_ReadBackupRegister(RTC_BKP_DR[index]) != (FirstRTCBackupData + (index * 0x5A)))
        {
            return (index + 1);
        }
    }

    return 0;
}

/**
  * @brief  Checks if the RTC Backup DRx registers are reset or not.
  * @param  None
  * @retval - 0: All RTC Backup DRx registers are reset
  *         - Value different from 0: Number of the first Backup register
  *         not reset
  */
uint32_t IsBackupRegReset(void)
{
    uint32_t index = 0;

    for (index = 0; index < RTC_BKP_DR_NUMBER; index++)
    {
        /* Read from bkp Data Register */
        if (RTC_ReadBackupRegister(RTC_BKP_DR[index]) != 0x0)
        {
            return (index + 1);
        }
    }

    return 0;
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

