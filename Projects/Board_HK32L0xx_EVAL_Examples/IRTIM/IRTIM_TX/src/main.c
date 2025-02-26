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
#include "hk32l0xx_irtim.h"
#include "hk32l0xx_eval.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define  u32 uint32_t
#define  u8  uint8_t
/* Private variables ---------------------------------------------------------*/
/*RX-------------*/
uint32_t frame_data = 0;
uint8_t  frame_cnt = 0;
uint8_t  frame_flag = 0;
static __IO u32 TimingDelay;
/*TX-------------*/
/*Key flag*/
unsigned int ZLG_flag;
/* Private function prototypes -----------------------------------------------*/
void USART_Config(void);
/*TX-------------*/
#ifdef IRTIM_TX
    static void Exti_Config(void);
#endif
/*RX-------------*/
#ifndef IRTIM_TX
    static void SysTick_Init(void);
    static void Delay_us(__IO u32 nTime);
    void TimingDelay_Decrement(void);
    static void NVIC_Configuration(void);
    static void IrDa_Init(void);
    uint8_t Get_Pulse_Time(void);
    static uint8_t IrDa_Process(void);
#endif
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    USART_Config();
#ifdef IRTIM_TX
    IRTIM_Config();
    Exti_Config();

    printf("IRTIM send test\n");

    while (1)
    {
        if (ZLG_flag == 1)
        {
            Write_IRdata(0xA2);

            ZLG_flag = 0;

        }
    }

#endif

#ifndef IRTIM_TX

    uint8_t key_val;
    SysTick_Init();
    NVIC_SetPriority (SysTick_IRQn, 0);
    printf("\r\n IRTIM receive test \r\n");
    IrDa_Init();

    while (1)
    {
        if ( frame_flag == 1 )
        {
            key_val = IrDa_Process();
            key_val = (((key_val & 0x80) >> 7) | ((key_val & 0x40) >> 5) | ((key_val & 0x20) >> 3) | ((key_val & 0x10) >> 1) | ((key_val & 0x08) << 1) | ((key_val & 0x04) << 3) | ((key_val & 0x02) << 5) | ((key_val & 0x01) << 7));

            printf("\r\n key_val=%d \r\n", key_val);

            switch ( key_val )
            {
                case 0:

                    printf("\r\n key_val=%d \r\n", key_val);
                    printf("\r\n _calibration_Error \r\n");
                    break;

                case 162:

                    printf("\r\n key_val=%d \r\n", key_val);
                    printf("\r\n Receive success \r\n");
                    break;



                default:
                    break;
            }
        }
    }

#endif
}

#ifdef IRTIM_TX
/**
  * @brief  Configure the EXTI.
  * @param  None
  * @retval None
  */
static void Exti_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;


    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    /*GPIO PA3*/
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    /* EXTI */
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);


    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource3);
    EXTI_ClearITPendingBit(EXTI_Line3);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}
#endif
/**
  * @brief  Configure the USART.
  * @param  None
  * @retval None
  */
void USART_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);
}


#ifndef IRTIM_TX
/**
  * @brief  SysTick
  * @param  None
  * @retval None
  */
static void SysTick_Init(void)
{
    /* SystemFrequency / 1000    1ms
     * SystemFrequency / 100000  10us
     * SystemFrequency / 1000000 1us
     */
    if (SysTick_Config(SystemCoreClock / 100000))
    {
        /* Capture error */
        while (1)
        {
        }
    }
}

/**
  * @brief  Delay time
  * @param  nTime: Delay time
  * @retval None
  */
static void Delay_us(__IO u32 nTime)
{

    TimingDelay = nTime;

    while (TimingDelay != 0)
    {
    }
}

/**
  * @brief  Pitch time
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}


/**
  * @brief  NVIC
  * @param  None
  * @retval None
  */
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}

/**
  * @brief  GPIO and EXTI init
  * @param  None
  * @retval None
  */
static void IrDa_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    /* config the extiline clock and SYSCFG clock */
    RCC_AHBPeriphClockCmd(IRDA_GPIO_CLK, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* config the NVIC */
    NVIC_Configuration();

    /* EXTI line gpio config */
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = IRDA_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(IRDA_GPIO_PORT, &GPIO_InitStructure);

    /* EXTI line mode config */
    SYSCFG_EXTILineConfig(IRDA_GPIO_PORT_SOURCE, IRDA_GPIO_PIN_SOURCE);
    EXTI_InitStructure.EXTI_Line = IRDA_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

/**
  * @brief  Get pulse time
  * @param  None
  * @retval None
  */
uint8_t Get_Pulse_Time(void)
{
    uint8_t time = 0;

    while ( IrDa_DATA_IN() )
    {
        time ++;
        Delay_us(2);

        if (time == 250)
            return time;
    }

    return time;
}

/**
  * @brief  IR data process
  * @param  None
  * @retval None
  */
static uint8_t IrDa_Process(void)
{
    uint8_t first_byte, sec_byte, tir_byte, fou_byte;

    first_byte = frame_data >> 24;
    sec_byte = (frame_data >> 16) & 0xff;
    tir_byte = frame_data >> 8;
    fou_byte = frame_data;

    printf("\r\n first_byte=%d \r\n", first_byte);
    printf("\r\n sec_byte=%d \r\n", sec_byte);
    printf("\r\n tir_byte=%d \r\n", tir_byte);
    printf("\r\n fou_byte=%d \r\n", fou_byte);

    frame_flag = 0;

    if ( (first_byte == (uint8_t)~sec_byte) && (first_byte == IRDA_ID) )
    {
        if ( tir_byte == (u8)~fou_byte )
            return tir_byte;
    }

    return 0;
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



