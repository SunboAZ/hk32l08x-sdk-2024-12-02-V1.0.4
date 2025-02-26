/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_it.c
* @brief:     Interrupt Service Routines
* @author:    AE Team
* @version:   V1.0.0/2024-01-04
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_it.h"
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/*TX------*/
/*Count(delay)*/
extern volatile unsigned int IRTIM_count;
/*Send flag*/
extern unsigned char IR_flag;
/*Key flag*/
extern unsigned int ZLG_flag;
/*RX------*/
extern uint32_t frame_data;
extern uint8_t  frame_cnt;
extern uint8_t  frame_flag;

uint8_t isr_cnt;
/* Private function prototypes -----------------------------------------------*/
extern void TimingDelay_Decrement(void);

/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @retval None
  */
void PendSV_Handler(void)
{
}
#ifndef IRTIM_TX
/**
  * @brief  This function handles SysTick Handler.
  * @retval None
  */
void SysTick_Handler(void)
{
    TimingDelay_Decrement();
}

/**
  * @brief  This function handles EXTI Handler.
  * @retval None
  */
void IRDA_EXTI_IRQHANDLER_FUN(void)
{
    uint8_t pulse_time = 0;
    uint8_t leader_code_flag = 0;
    uint8_t irda_data = 0;

    if (EXTI_GetITStatus(IRDA_EXTI_LINE) != RESET)
    {
        while (1)
        {
            if ( IrDa_DATA_IN() == SET )
            {
                pulse_time = Get_Pulse_Time();


                if ( (pulse_time >= 250) || (pulse_time <= 5) )

                {
                    break;
                }

                if (pulse_time >= 200 && pulse_time < 250)
                {
                    leader_code_flag = 1;
                }
                else if (pulse_time >= 10 && pulse_time < 50)
                {
                    irda_data = 0;
                }
                else if (pulse_time >= 50 && pulse_time < 100)
                {
                    irda_data = 1 ;
                }
                else if ( pulse_time >= 100 && pulse_time <= 200 )
                {

                    frame_flag = 1;

                    break;
                }

                if ( leader_code_flag == 1 )
                {
                    frame_data <<= 1;
                    frame_data += irda_data;

                }
            }
        }

        EXTI_ClearITPendingBit(IRDA_EXTI_LINE);
    }
}
#endif


#ifdef IRTIM_TX
/**
  * @brief  This function handles EXTI Handler.
  * @retval None
  */
void EXTI2_3_IRQHandler(void)
{

    if (EXTI_GetITStatus(EXTI_Line3) != RESET)
    {
        ZLG_flag = 1;
        printf("KEY interrupt----------\n");
    }

    EXTI_ClearITPendingBit(EXTI_Line3);

}

/**
  * @brief  This function handles TIM Handler.
  * @retval None
  */
void TIM2_IRQHandler(void)
{

    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        IRTIM_count++;

        if (IR_flag == 1)
        {
            TIM2->CCR1 = (uint16_t)(27);

        }
        else
        {
            TIM2->CCR1 = (uint16_t)(0);

        }

        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

    }
}
#endif
/******************************************************************************/
/*                 HK32L0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (KEIL_Startup_hk32l0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


