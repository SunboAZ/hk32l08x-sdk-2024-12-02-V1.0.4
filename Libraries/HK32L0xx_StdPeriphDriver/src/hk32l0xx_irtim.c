/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_irtim.c
* @brief:     IRTIM init and functions configure
* @author:    AE Team
* @version:   V1.0.0/2024-01-10
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_irtim.h"
#include "hk32l0xx_rcc.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup IRTIM IRTIM
  * @brief IRTIM driver modules
  * @{
  */

/** @defgroup IRTIM_Private_Defines IRTIM_Private_Defines
  * @{
  */
#define TIM_ENV TIM2
#define TIM_CAR TIM3
/*charge from  system clock config */
#define CLOCK_FREQUENCE SystemCoreClock
/**
  * @}
  */

/** @defgroup IRTIM_Private_Variables IRTIM_Private_Variables
  * @{
  */
/*8bit user code*/
volatile unsigned char irdata1 = 0;
/*Count end*/
unsigned int IR_endcount;
/*count*/
unsigned int IRTIM_count;
/*Send flag*/
volatile unsigned char IR_flag = 0;
/**
  * @}
  */

/** @defgroup IRTIM_Private_Functions IRTIM_Private_Functions
  * @{
  */

/**
  * @brief  IR output GPIO(PB9)  configurate
  * @retval None
  */
void IR_OutGpioConfig(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init( GPIOB, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_2);
    /*Strong driver*/
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C1_PB9_FMP;
}
/**
  * @brief  IRTIM carrier  configurate to 38KHz.Abide by NEC agreement.
  * @retval None
  */
void IRTIM_CarrierConfig(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    TIM_TimeBaseStructure.TIM_Period = CLOCK_FREQUENCE / 38000;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM_CAR, &TIM_TimeBaseStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CLOCK_FREQUENCE / 38000 / 2;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM_CAR, &TIM_OCInitStructure);
    /*if TIM_CAR=TIM15/16/17, need TIM_CtrlPWMOutputs(TIM_CAR, ENABLE);*/
    TIM_CCPreloadControl(TIM_CAR, DISABLE);
    TIM_Cmd(TIM_CAR, ENABLE);
}

/**
  * @brief  IRTIM envelope interrupt configurate
  * @retval None
  */
void IRTIM_EnvelopeNvicConfig(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/**
  * @brief  IRTIM envelope config.Abide by NEC agreement.
  * @retval None
  */
void IRTIM_EnvelopeConfig(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    TIM_TimeBaseStructure.TIM_Period = 26;
    /*cycle 26.3us*/
    TIM_TimeBaseStructure.TIM_Prescaler = CLOCK_FREQUENCE / 1000000 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM_ENV, &TIM_TimeBaseStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM_ENV, &TIM_OCInitStructure);
    /*if TIM_CAR=TIM15/16/17, need TIM_CtrlPWMOutputs(TIM_ENV, ENABLE);*/
    TIM_CCPreloadControl(TIM_ENV, DISABLE);
    TIM_ClearFlag(TIM_ENV, TIM_FLAG_Update);
    TIM_ITConfig(TIM_ENV, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM_ENV, ENABLE);
}

/*******************************************************
1/38kHz=26.3us , 0.56ms/26.3us=21.

          0: 0.56ms/0.565ms
          1: 0.56ms/1.685ms
********************************************************/
/**
  * @brief  Send IR data.Abide by NEC agreement.
  * @param  x_irdata: Data that needs to be sent
  * @retval None
  */
void Send_IRdata(unsigned char x_irdata)
{
    unsigned char i;
    unsigned char irdata;
    irdata = x_irdata;

    for (i = 0; i < 8; i++)
    {
        /*send 0.56ms 38KHz PWM*/
        IRTIM_count = 0;
        /*0.56ms / 26.3us = 21*/
        IR_endcount = 21;
        /*send flag*/
        IR_flag = 1;

        while (IRTIM_count < IR_endcount)
        {
        }

        /*0 delay (1.125ms-0.56ms=0.565ms);1 delay (2.25ms-0.56ms=1.685ms)*/
        if (irdata & 0x01)
        {
            /*1.685ms / 26.3us = 64*/
            IR_endcount = 64;
        }
        else
        {
            /*0.565ms / 26.3us = 21*/
            IR_endcount = 21;
        }

        IRTIM_count = 0;
        IR_flag = 0;

        while (IRTIM_count < IR_endcount)
        {
        }

        irdata = irdata >> 1;
    }
}

/**
  * @brief  Write IR data.Abide by NEC agreement.
  * @param  p_irdata: key data code
  * @retval None
  */
void Write_IRdata(unsigned char p_irdata)
{
    /* 9ms / 26.3us = 342 */
    IR_endcount = 342;
    IRTIM_count = 0;
    IR_flag = 1;

    while (IRTIM_count < IR_endcount)
    {
    }

    /*send 4.5ms stop code*/
    IRTIM_count = 0;
    /*4.5ms / 26.3us = 171 */
    IR_endcount = 171;
    IR_flag = 0;

    while (IRTIM_count < IR_endcount)
    {
    }

    /* user code */
    Send_IRdata(irdata1);
    /* user inverse code */
    Send_IRdata(~irdata1);
    /* key value */
    Send_IRdata(p_irdata);
    /*key value inverse code*/
    Send_IRdata(~p_irdata);
    /*send 0.56ms 38KHz PWM*/
    IRTIM_count = 0;
    /*0.56ms / 26.3us = 21*/
    IR_endcount = 21;
    IR_flag = 1;

    while (IRTIM_count < IR_endcount)
    {
    }

    IR_flag = 0;
    IRTIM_count = 0;
    /*2.1ms / 26.3us = 80 */
    IR_endcount = 80;
    IR_flag = 0;

    while (IRTIM_count < IR_endcount)
    {
    }

    /*send 0.56ms 38KHz PWM*/
    IRTIM_count = 0;
    /*0.56ms / 26.3us =21 */
    IR_endcount = 21;
    IR_flag = 1;

    while (IRTIM_count < IR_endcount)
    {
    }

    IR_flag = 0;
}
/**
  * @brief  IRTIM configurate gather
  * @retval None
  */
void IRTIM_Config(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    IR_OutGpioConfig();
    IRTIM_CarrierConfig();
    IRTIM_EnvelopeNvicConfig();
    IRTIM_EnvelopeConfig();
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

