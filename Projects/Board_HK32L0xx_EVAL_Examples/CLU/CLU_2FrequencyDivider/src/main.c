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
#include <stdio.h>
#include "hk32l0xx_eval.h"


/** @addtogroup HK32L0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup CLU_2FrequencyDivder
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
static uint32_t Reply = 0xffff;

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void GPIO_Config(void);
static void USART_Config(void);
static void Delay_us(__IO uint32_t TCounter);
static uint32_t USART_Scanf(uint32_t max_value, uint32_t count);

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
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_Config();
    GPIO_Config();
    CLU->CLU0_MX |= (uint32_t)0x1F << 16;
    CLU->CLU1_MX |= (uint32_t)0x1F << 16;
    CLU->CLU2_MX |= (uint32_t)0x1F << 16;
    CLU->CLU3_MX |= (uint32_t)0x1F << 16;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* For CLU0 , MXA=PA1, MXB=PA2,Ignore MXC and MXD, Function= ~A */
    CLU0_MultiplexerInputConfig(CLU0_MXA_CLU0_OUT_INTER, CLU0_MXB_CLU0_OUT_INTER, 0, 0);
    CLU_SetOutputFunction(CLU0, (uint32_t)CLU_FUNCTION_NOT(CLU_FUNCTION_A_INPUT_TRUE));
    CLU_OutputSelection(CLU0, CLUxCF_OUTSEL__D_FF);
    CLU_EnablePinOutput(CLU0, CLUxCF_OEN__ENABLE);

    /* Multiplex the PF4 pin as CLU0 output */
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource4, GPIO_AF_10);

    printf("\r\n +-------- Test D-Flip-Flop Function --------+\r\n");
    printf("\r\n Please select the clock of D-Flip-Flop ?  (Please enter the following numbers)");
    printf("\r\n <1> Carry-in as D-Flip-Flop clock ");
    printf("\r\n <2> MXA_Input as D-Flip-Flop clock ");
    printf("\r\n <3> SYSCLK as D-Flip-Flop clock ");

    Reply = 0xFFFF;

    while (Reply == 0xFFFF)
    {
        Reply = USART_Scanf(3, 1);
    }

    if (Reply == 1)
    {
        printf("\r\n========= Your choose is \" <1> Carry-in as D-Flip-Flop clock ============\" ");
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        /* For CLU3 , MXA=PA12,Ignore MXB,MXC and MXD, Function=A */
        CLU3_MultiplexerInputConfig(CLU3_MXA_PA12, 0, 0, 0);
        CLU_SetOutputFunction(CLU3, (uint32_t)CLU_FUNCTION_A_INPUT_TRUE);
        CLU_OutputSelection(CLU3, CLUxCF_OUTSEL__LUT);
        CLU_EnablePinOutput(CLU3, CLUxCF_OEN__ENABLE);
        CLU_Cmd(CLU3, ENABLE);
        CLU0_MultiplexerInputConfig(CLU0_MXA_CLU0_OUT_INTER, 0, 0, 0);
        CLU_InitDFlipflop(CLU0, CLUxCF_CLKSEL__CARRY_IN, CLUxCF_CLKINV__NORMAL);
        printf("\r\n Please connect the pins as follows:");
        printf("\r\n< Test_Pin  |  MX_Pin >");
        printf("\r\n[  PB0   ----->  PA12 ]");
        printf("\r\n[Probe1  <-----  PF4 ]");
        printf("\r\n[Probe2  <-----  PB0  ]");
        printf("\r\n <3>Already connected    <4>Not connected successfully   (Please enter the number between '<' and '>' ) ");
        Reply = 0xFFFF;

        while ((Reply == 0xFFFF) || (Reply != 3))
        {
            Reply = USART_Scanf(4, 1);

            if (Reply != 3)
            {
                printf("\r\n#### Please reconnect and enter the number ! #### \r\n");
            }
        }

        printf("\r\n Please view the oscilloscope waveform ! \r\n");
    }
    else if (Reply == 2)
    {
        printf("\r\n Your choose is \" <2> MXA_Input as D-Flip-Flop clock \" ");
        CLU_SetOutputFunction(CLU0, (uint32_t)CLU_FUNCTION_NOT(CLU_FUNCTION_B_INPUT_TRUE));
        CLU0_MultiplexerInputConfig(CLU0_MXA_PA1, CLU0_MXB_CLU0_OUT_INTER, 0, 0);
        CLU_InitDFlipflop(CLU0, CLUxCF_CLKSEL__MXA_INPUT, CLUxCF_CLKINV__NORMAL);
        printf("\r\n Please connect the pins as follows:");
        printf("\r\n< Test_Pin  |  MX_Pin >");
        printf("\r\n[  PB0   ----->  PA1  ]");
        printf("\r\n[Probe1  <-----  PF4  ]");
        printf("\r\n[Probe2  <-----  PB0  ]");
        printf("\r\n <3>Already connected    <4>Not connected successfully   (Please enter the number between '<' and '>' ) ");
        Reply = 0xFFFF;

        while ((Reply == 0xFFFF) || (Reply != 3))
        {
            Reply = USART_Scanf(4, 1);

            if (Reply != 3)
            {
                printf("\r\n#### Please reconnect and enter the number ! #### \r\n");
            }
        }

        printf("\r\n Please view the oscilloscope waveform ! \r\n");
    }
    else if (Reply == 3)
    {
        printf("\r\n Your choose is \" <3> SYSCLK as D-Flip-Flop clock \" ");

        /* Config PA8 as MCO output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_0);
        RCC_MCOConfig(RCC_MCOSource_SYSCLK, RCC_MCOPrescaler_1);
        CLU_InitDFlipflop(CLU0, CLUxCF_CLKSEL__SYSCLK, CLUxCF_CLKINV__NORMAL);
        printf("\r\n Please connect the pins as follows:");
        printf("\r\n< Test_Pin  |  MX_Pin >");
        printf("\r\n[Probe1  <-----  PF4  ]");
        printf("\r\n[Probe2  <-----  PA8  ]");
        printf("\r\n <3>Already connected    <4>Not connected successfully   (Please enter the number between '<' and '>' ) ");
        Reply = 0xFFFF;

        while ((Reply == 0xFFFF) || (Reply != 3))
        {
            Reply = USART_Scanf(4, 1);

            if (Reply != 3)
            {
                printf("\r\n#### Please reconnect and enter the number ! #### \r\n");
            }
        }

        printf("\r\n Please view the oscilloscope waveform ! \r\n");
    }
    else
    {
        printf("\r\n #### Your choose is error ,please restart #### \r\n");
    }

    CLU_Cmd(CLU0, ENABLE);

    while (1)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_0);
        Delay_us(3);
        GPIO_ResetBits(GPIOB, GPIO_Pin_0);
        Delay_us(7);
    }
}


/**
  * @brief  Configure GPIO peripheral, used to CLU output/input.
  * @param  None
  * @retval None
  */
static void GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Enable GPIO Clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

    /* Configure PB0/PB1/PB2/PB8 of GPIO to output pwm signal, used connected MXA/MXB/MXC/MXD of CLU */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_8);

    /* Configure PF4 as CLU output */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
}


/**
  * @brief  Configure USART peripheral, used to print.
  * @param  None
  * @retval None
  */
static void USART_Config(void)
{
    USART_InitTypeDef USART_InitStructure;

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

/**
  * @brief  Delay Us
  * @param  TCounter: Delay counter
  * @retval None
  */
static void Delay_us(__IO uint32_t TCounter)
{
    while (TCounter--)
    {
        for (uint32_t i = 0; i < 5; i++)
        {
        }
    }
}

/**
  * @brief  Gets numeric values from the hyperterminal.
  * @param  MaxValue: The maximum value of the allowed input, the input value
  *         must be less than MaxValue.
  * @param  Count: The Count of the input characters.
  * @retval Return the numeric values from the hyperterminal.
  */
static uint32_t USART_Scanf(uint32_t MaxValue, uint32_t Count)
{
    uint32_t index = 0;
    uint32_t tmp[5] = {0, 0};

    while (index < Count)
    {
        /* Loop until RXNE = 1 */
        while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_RXNE) == RESET)
        {
        }

        tmp[index++] = (USART_ReceiveData(EVAL_COM1));

        if ((tmp[index - 1] < 0x30) || (tmp[index - 1] > 0x39))
        {
            printf("\n\rPlease enter valid number between 0 and 9");
            index--;
        }
    }

    if (Count == 1)
    {
        index = tmp[0] - 0x30;
    }
    else if (Count == 2)
    {
        /* Calculate the Corresponding value */
        index = (tmp[1] - 0x30) + ((tmp[0] - 0x30) * 10);
    }
    else if (Count == 3)
    {
        /* Calculate the Corresponding value */
        index = (tmp[2] - 0x30) + ((tmp[1] - 0x30) * 10) + ((tmp[0] - 0x30) * 100);
    }
    else if (Count == 4)
    {
        /* Calculate the Corresponding value */
        index = (tmp[3] - 0x30) + ((tmp[2] - 0x30) * 10) + ((tmp[1] - 0x30) * 100) + ((tmp[0] - 0x30) * 1000);
    }
    else if (Count == 5)
    {
        /* Calculate the Corresponding value */
        index = (tmp[4] - 0x30) + ((tmp[3] - 0x30) * 10) + ((tmp[2] - 0x30) * 100) + ((tmp[1] - 0x30) * 1000) + ((tmp[0] - 0x30) * 10000);
    }
    else
    {

    }

    /* Checks */
    if (index > MaxValue)
    {
        printf("\n\rPlease enter valid number between 0 and %d", MaxValue);
        return 0xFFFF;
    }

    return index;
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


