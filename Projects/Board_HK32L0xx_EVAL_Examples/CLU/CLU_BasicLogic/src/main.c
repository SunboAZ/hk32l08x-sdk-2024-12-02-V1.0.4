/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2024-01-12
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

/** @addtogroup CLU_BasicLogic
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const static uint8_t Func_A_and_B[4][3] =
{
    {0, 0, 0},
    {0, 1, 0},
    {1, 0, 0},
    {1, 1, 1},
};

const static uint8_t Func_A_or_B[4][3] =
{
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
};

const static uint8_t Func_A_xor_B[4][3] =
{
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 0},
};

const static uint8_t Func_Not_A_or_Not_B[4][3] =
{
    {0, 0, 1},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 0},
};

static uint32_t ErrFlag = 0;
static uint32_t Reply = 0xFFFF;


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

    while (1)
    {

        printf("\r\n +-------- Test CLU Basic Logic Function (&(and), |(or), ^(xor), ~(not)) --------+");

        printf("\r\n Please select the point of CLU ? (Please enter the following numbers)");
        printf("\r\n<0> Function=A&B");
        printf("\r\n<1> Function=A|B");
        printf("\r\n<2> Function=A^B");
        printf("\r\n<3> Function=(~A)|(~B) \r\n");
        Reply = 0xFFFF;

        while (Reply == 0xFFFF)
        {
            Reply = USART_Scanf(3, 1);
        }

        if (Reply == 0)
        {
            printf("\r\n ======== Test Function=A&B, use MXA and MXB channel of CLU0 ======== \r\n");

            printf("\r\n Please connect the pins as follows:");
            printf("\r\n< Test_Pin  |  MX_Pin >");
            printf("\r\n[   PB0  ----->  PA0  ]");
            printf("\r\n[   PB1  ----->  PA3  ]");
            printf("\r\n[   PF5  <-----  PF4  ]");
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

            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_3;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
            GPIO_Init(GPIOA, &GPIO_InitStructure);

            /* For CLU0 , MXA=PA0, MXB=PA3,Ignore MXC and MXD, Function=A&B */
            CLU0_MultiplexerInputConfig(CLU0_MXA_PA0, CLU0_MXB_PA3, 0, 0);
            CLU_SetOutputFunction(CLU0, (uint32_t)CLU_FUNCTION_AND(CLU_FUNCTION_A_INPUT_TRUE, CLU_FUNCTION_B_INPUT_TRUE));
            CLU_OutputSelection(CLU0, CLUxCF_OUTSEL__LUT);
            CLU_EnablePinOutput(CLU0, CLUxCF_OEN__ENABLE);
            CLU_Cmd(CLU0, ENABLE);

            /* Multiplex the PF4 pin as CLU0 output */
            GPIO_PinAFConfig(GPIOF, GPIO_PinSource4, GPIO_AF_10);

            ErrFlag = 0;

            for (uint32_t cnt = 0; cnt < 20; cnt++)
            {
                for (uint32_t j = 0; j < 4; j++)
                {
                    GPIO_WriteBit(GPIOB, GPIO_Pin_0, (BitAction)Func_A_and_B[j][0]);
                    GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction)Func_A_and_B[j][1]);
                    Delay_us(2);

                    if (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5) != Func_A_and_B[j][2])
                    {
                        ErrFlag = 1;
                    }
                }
            }

            if (ErrFlag == 1)
            {
                printf("\r\n #### Test Function=A&B error ! #### \r\n");
            }
            else
            {
                printf("\r\n **** Test Function=A&B success ! **** \r\n");
            }
        }
        else if (Reply == 1)
        {
            printf("\r\n ======== Test Function=A|B, use MXA and MXB channel of CLU1 ======== \r\n");

            printf("\r\n Please connect the pins as follows:");
            printf("\r\n< Test_Pin  |  MX_Pin >");
            printf("\r\n[   PB0  ----->  PA3  ]");
            printf("\r\n[   PB1  ----->  PA2  ]");
            printf("\r\n[   PF5  <-----  PF4  ]");
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

            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
            GPIO_Init(GPIOA, &GPIO_InitStructure);

            /* For CLU1 , MXA=PA3, MXB=PA2,Ignore MXC and MXD, Function=A|B */
            CLU1_MultiplexerInputConfig(CLU1_MXA_PA3, CLU1_MXB_PA2, 0, 0);
            CLU_SetOutputFunction(CLU1, (uint32_t)CLU_FUNCTION_OR(CLU_FUNCTION_A_INPUT_TRUE, CLU_FUNCTION_B_INPUT_TRUE));
            CLU_OutputSelection(CLU1, CLUxCF_OUTSEL__LUT);
            CLU_EnablePinOutput(CLU1, CLUxCF_OEN__ENABLE);
            CLU_Cmd(CLU1, ENABLE);

            /* Multiplex the PF4 pin as CLU1 output */
            GPIO_PinAFConfig(GPIOF, GPIO_PinSource4, GPIO_AF_11);

            ErrFlag = 0;

            for (uint32_t cnt = 0; cnt < 20; cnt++)
            {
                for (uint32_t j = 0; j < 4; j++)
                {
                    GPIO_WriteBit(GPIOB, GPIO_Pin_0, (BitAction)Func_A_or_B[j][0]);
                    GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction)Func_A_or_B[j][1]);
                    Delay_us(2);

                    if (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5) != Func_A_or_B[j][2])
                    {
                        ErrFlag = 1;
                    }
                }
            }

            if (ErrFlag == 1)
            {
                printf("\r\n #### Test Function=A|B error ! #### \r\n");
            }
            else
            {
                printf("\r\n **** Test Function=A|B success ! **** \r\n");
            }
        }
        else if (Reply == 2)
        {
            printf("\r\n ======== Test Function=A^B, use MXA and MXB channel of CLU2 ======== \r\n");

            printf("\r\n Please connect the pins as follows:");
            printf("\r\n< Test_Pin  |  MX_Pin >");
            printf("\r\n[   PB0  ----->  PA6  ]");
            printf("\r\n[   PB1  ----->  PA3  ]");
            printf("\r\n[   PF5  <-----  PF4  ]");
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

            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_3;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
            GPIO_Init(GPIOA, &GPIO_InitStructure);

            /* For CLU2 , MXA=PA6, MXB=PA3,Ignore MXC and MXD, Function=A|B */
            CLU2_MultiplexerInputConfig(CLU2_MXA_PA6, CLU2_MXB_PA3, 0, 0);
            CLU_SetOutputFunction(CLU2, (uint32_t)CLU_FUNCTION_XOR(CLU_FUNCTION_A_INPUT_TRUE, CLU_FUNCTION_B_INPUT_TRUE));
            CLU_OutputSelection(CLU2, CLUxCF_OUTSEL__LUT);
            CLU_EnablePinOutput(CLU2, CLUxCF_OEN__ENABLE);
            CLU_Cmd(CLU2, ENABLE);

            /* Multiplex the PF4 pin as CLU2 output */
            GPIO_PinAFConfig(GPIOF, GPIO_PinSource4, GPIO_AF_12);

            ErrFlag = 0;

            for (uint32_t cnt = 0; cnt < 20; cnt++)
            {
                for (uint32_t j = 0; j < 4; j++)
                {
                    GPIO_WriteBit(GPIOB, GPIO_Pin_0, (BitAction)Func_A_xor_B[j][0]);
                    GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction)Func_A_xor_B[j][1]);
                    Delay_us(2);

                    if (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5) != Func_A_xor_B[j][2])
                    {
                        ErrFlag = 1;
                    }
                }
            }

            if (ErrFlag == 1)
            {
                printf("\r\n #### Test Function=A^B error ! #### \r\n");
            }
            else
            {
                printf("\r\n **** Test Function=A^B success ! **** \r\n");
            }
        }
        else if (Reply == 3)
        {
            printf("\r\n ======== Test Function=(~A)|(~B), use MXA and MXB channel of CLU2 ======== \r\n");

            printf("\r\n Please connect the pins as follows:");
            printf("\r\n< Test_Pin  |  MX_Pin >");
            printf("\r\n[   PB0  ----->  PA12 ]");
            printf("\r\n[   PB1  ----->  PA11 ]");
            printf("\r\n[   PF5  <-----  PF4  ]");
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

            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_11;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
            GPIO_Init(GPIOA, &GPIO_InitStructure);

            /* For CLU3 , MXA=PA12, MXB=PA11,Ignore MXC and MXD, Function=A|B */
            CLU3_MultiplexerInputConfig(CLU3_MXA_PA12, CLU3_MXB_PA11, 0, 0);
            CLU_SetOutputFunction(CLU3, (uint32_t)CLU_FUNCTION_OR(CLU_FUNCTION_NOT(CLU_FUNCTION_A_INPUT_TRUE), CLU_FUNCTION_NOT(CLU_FUNCTION_B_INPUT_TRUE)));
            CLU_OutputSelection(CLU3, CLUxCF_OUTSEL__LUT);
            CLU_EnablePinOutput(CLU3, CLUxCF_OEN__ENABLE);
            CLU_Cmd(CLU3, ENABLE);

            /* Multiplex the PF4 pin as CLU3 output */
            GPIO_PinAFConfig(GPIOF, GPIO_PinSource4, GPIO_AF_13);

            ErrFlag = 0;

            for (uint32_t cnt = 0; cnt < 20; cnt++)
            {
                for (uint32_t j = 0; j < 4; j++)
                {
                    GPIO_WriteBit(GPIOB, GPIO_Pin_0, (BitAction)Func_Not_A_or_Not_B[j][0]);
                    GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction)Func_Not_A_or_Not_B[j][1]);
                    Delay_us(2);

                    if (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5) != Func_Not_A_or_Not_B[j][2])
                    {
                        ErrFlag = 1;
                    }
                }
            }

            if (ErrFlag == 1)
            {
                printf("\r\n #### Test Function=(~A)|(~B) error ! #### \r\n");
            }
            else
            {
                printf("\r\n **** Test Function=(~A)|(~B) success ! **** \r\n");
            }
        }
        else
        {
            printf("\r\n #### Your chose is error ####\r\n");
        }
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

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

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
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */

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

