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
#include "hk32l0xx_eval.h"

/** @addtogroup HK32L0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup CAN_FIFOExtension
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
CanTxMsg TxMessage = {0};
CanRxMsg RxMessage = {0};
uint8_t KeyNumber = 0x0;
extern __IO uint8_t MsgReceived;
CAN_FilterInitTypeDef  CAN_FilterInitStructure;
/* Private function prototypes -----------------------------------------------*/
static void CAN_Config(void);
static void Display_TransmittedMsg(uint8_t PushNumber);
void Display_ReceivedMsg(void);
void Delay(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Configure Push button key */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

    /* USART configuration */
    USART_InitTypeDef USART_InitStruct;

    USART_StructInit(&USART_InitStruct);
    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    HK_EVAL_COMInit(COM1, &USART_InitStruct);

    /* CAN configuration */
    CAN_Config();

    while (1)
    {
        while (HK_EVAL_PBGetState(BUTTON_KEY1) == RESET)
        {
            if (KeyNumber == 41) KeyNumber = 0;

            Display_TransmittedMsg(KeyNumber);

            KeyNumber++;

            Delay();

            while (HK_EVAL_PBGetState(BUTTON_KEY1) != SET)
            {
            }
        }

        if (MsgReceived != 0)
        {
            Display_ReceivedMsg();
            MsgReceived = 0;
        }
    }
}

/**
  * @brief  Configures the CAN.
  * @param  None
  * @retval None
  */
static void CAN_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    CAN_InitTypeDef   CAN_InitStructure;

    /* CAN GPIOs configuration **************************************************/

    /* Enable GPIO clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* Connect CAN pins to AF4 */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_4);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_4);

    /* Configure CAN RX and TX pins */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* NVIC configuration *******************************************************/
    NVIC_InitStructure.NVIC_IRQChannel = LCD_CAN_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* CAN configuration ********************************************************/

    /* Enable CAN clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN, ENABLE);

    /* CAN register init */
    CAN_DeInit();
    CAN_StructInit(&CAN_InitStructure);

    /* CAN cell init */
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = ENABLE;
    CAN_InitStructure.CAN_TXFP = ENABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;

    /* CAN Baudrate = 1MBps (CAN clocked at 48 MHz) */
    CAN_InitStructure.CAN_BS1 = CAN_BS1_10tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStructure.CAN_Prescaler = 3;
    CAN_Init(&CAN_InitStructure);

    /* CAN filter init "FIFO0" */
    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x6420;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

    /* Transmit Structure preparation */
    TxMessage.StdId = 0x321;
    TxMessage.ExtId = 0x00;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.DLC = 1;

    /* Enable FIFO 0 full Interrupt */
    CAN_ITConfig(CAN_IT_FF0, ENABLE);

    /* Enable FIFO 1 full Interrupt */
    CAN_ITConfig(CAN_IT_FF1, ENABLE);
}


/**
  * @brief  printf transmitted msg.
  * @param  None
  * @retval None
  */
static void Display_TransmittedMsg(uint8_t PushNumber)
{
    uint8_t dataindex = 0;

    uint8_t TxMessages[6] = { 0, 1, 2, 3, 4, 5 };

    for (dataindex = 0 ; dataindex < 6 ; dataindex++)
    {

        TxMessage.Data[0] = (uint8_t)(TxMessages[dataindex] + (6 * PushNumber));

        CAN_Transmit(&TxMessage);

        printf("Send Message Num %d = %d \r\n", dataindex + 1, TxMessage.Data[0] );

    }

}

/**
  * @brief  printf received msg.
  * @param  None.
  * @retval None
  */
void Display_ReceivedMsg(void)
{
    uint8_t dataindex = 0;

    for (dataindex = 0 ; dataindex < 6 ; dataindex++)
    {
        if (dataindex < 3)
        {
            /* read data from CAN1 FIFO 0 */
            CAN_Receive(CAN_FIFO0, &RxMessage);
        }
        else
        {
            /* read data from CAN1 FIFO 1 */
            CAN_Receive(CAN_FIFO1, &RxMessage);
        }

        printf("Message received Num %d = %d \r\n", dataindex + 1, RxMessage.Data[0]);
    }
}

/**
  * @brief  Delay
  * @param  None
  * @retval None
  */
void Delay(void)
{
    uint32_t nTime = 0x0000;

    for (nTime = 0; nTime < 0xFFFFF; nTime++)
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

/**
  * @}
  */

