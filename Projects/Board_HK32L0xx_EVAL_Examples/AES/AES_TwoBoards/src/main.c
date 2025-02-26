/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body, This example provides AES encryption decryption  fuctions,Can Switch project A and B
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*              1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
/*Plaintext data encrypted on board A */
uint8_t BoardA_TxBuffer[AES_TEXT_SIZE] =
{
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
    0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
};

/*  After the A board is encrypted correctly, it should have the correct standard cipher text.  */
uint8_t BoardA_ExpectedCipherText[16] = {0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60,
                                         0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97
                                        };

/* Key for encryption and decryption on board A and board B*/
uint8_t BoardAB_EncryptionKey[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                                     0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
                                    };
/* A plate processing flow  */
#ifdef AES_TWO_BOARD_A
/* The encrypted ciphertext of board A, the ciphertext array stored, is also the array that board A will send to board B. */
uint8_t BoardA_CipherText[AES_TEXT_SIZE]  = {0};

/* Data cache received by board A */
uint8_t BoardA_RxBuffer[AES_TEXT_SIZE] = {0};

/* received data length */
uint8_t RxIndex = 0;

/* reception completion flag */
uint8_t RxDone = 0;
uint8_t ubButtonPress = 0;

/* Private function prototypes -----------------------------------------------*/
static void Display_PlainData(uint32_t datalength);
static void Display_EncryptedData(uint8_t mode, uint16_t keysize, uint32_t datalength);
static void AES_Function_Handle(void);
static void USART2_Config(uint32_t BaudRate);
static ErrorStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

#endif

/* Private macro -------------------------------------------------------------*/

/* B plate processing flow  */
#ifdef AES_TWO_BOARD_B

/* Private variables ---------------------------------------------------------*/

/* Data cache received by B board */
uint8_t BoardB_RxBuffer[AES_TEXT_SIZE] = {0};

/* received data length */
uint8_t RxIndex = 0;

/* reception completion flag */
uint8_t RxDone = 0;

/* After receiving the ciphertext and performing the decryption algorithm,
Board B stores the plaintext array, which is also the array that Board B will send to Board A. */
uint8_t BoardB_ComputedPlainText[AES_TEXT_SIZE] = {0};

/* Private function prototypes -----------------------------------------------*/

static void Display_DecryptedData(uint8_t mode, uint16_t keysize, uint32_t datalength);
static void USART2_Config(uint32_t BaudRate);
static ErrorStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

#endif

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Before executing the main function, the SystemInit() function has been called in the startup file xxstartup.s to configure the system clock. */

    /* Initialize LED2 */
    HK_EVAL_LEDInit(LED2);
    /*------------------------------- USART-------------------------------------*/

    /* USARTx configured as follow:
    - BaudRate = 115200
    - Word Length = USART_WordLength_8b
    - Stop Bit = USART_StopBits_1
    - Parity = USART_Parity_No
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;

    /* Initialize USART1 */
    HK_EVAL_COMInit(COM1, &USART_InitStructure);

    /* Serial port 2 configuration for communication between A and B boards */
    USART2_Config(115200);

    printf("AES Two Boards, Serial communication is adopted between A board and B board to realize encryption and decryption function.\r\n");

#ifdef AES_TWO_BOARD_A

    /* A plate processing flow */

    /* Initialize User push-button in EXTI mode */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_EXTI);
    printf("board A: This is board A,please reset Board B berfore next step.\r\n");

    /* Start to  continue */
    printf("Wait for User push-button press to start  encrypt/decrypt ...\r\n");

    /* Wait for User push-button press to continue */
    WaitForUserButtonPress();

    /* AES Handler */
    AES_Function_Handle();

    /* Infinite loop */
    while (1)
    {
        /* Primary data reception complete */
        if (RxDone)
        {
            RxDone = 0;

            /* Data checking of received data */
            if (Buffercmp(BoardA_TxBuffer, BoardA_RxBuffer, AES_TEXT_SIZE) == SUCCESS)
            {
                printf("board A: Received vaild\r\n");

                /* Display Plain Data*/
                Display_PlainData(AES_TEXT_SIZE);
            }
            else
            {
                printf("board A: Received invaild\r\n");
            }
        }
    }

#endif

    /* B plate processing flow  */
#ifdef AES_TWO_BOARD_B
    AES_DeInit();
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRYPT, ENABLE);
    printf("board B: This is board B\r\n");

    /* Infinite loop */
    while (1)
    {
        /*Primary data reception complete*/
        if (RxDone)
        {
            RxDone = 0;

            /*Data checking of received data*/
            if (Buffercmp(BoardA_ExpectedCipherText, BoardB_RxBuffer, AES_TEXT_SIZE) == SUCCESS)
            {
                printf("board B: Received vaild\r\n");
            }
            else
            {
                printf("board B: Received invaild\r\n");
            }

            /*=====================================================
                Decryption in ECB mode
            ======================================================*/
            /****************************************/
            /*                           AES 128   **/
            /****************************************/
            /* Decrypt the plaintext message  */
            AES_ECB_Decrypt( BoardAB_EncryptionKey, 128, BoardB_RxBuffer, AES_TEXT_SIZE, BoardB_ComputedPlainText);

            /* Read the CipherText and check content correctness */
            if (Buffercmp(BoardA_TxBuffer, BoardB_ComputedPlainText, AES_TEXT_SIZE) == SUCCESS)
            {
                printf("board B: AES ECB 128Keysize Decrypted ok\r\n");

                /* Display decrypted data*/
                Display_DecryptedData(ECB, 128, AES_TEXT_SIZE);
                printf("board B: Send BoardB_ComputedPlainText to Board A ...\r\n");

                for (uint32_t i = 0; i < AES_TEXT_SIZE; i++)
                {
                    USART_SendData(USART2, (unsigned char) BoardB_ComputedPlainText[i]);

                    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET)
                    {
                    }
                }

                printf("board B: Send BoardB_ComputedPlainText to Board A Finished ...\r\n");
            }
            else
            {
                printf("AES ECB 128Keysize Decrypted  Fail\r\n");
            }
        }
    }

#endif
}
/* A plate processing flow  */
#ifdef AES_TWO_BOARD_A
/**
  * @brief  AES Function  .
  * @param  None
  * @retval None
  */
static void AES_Function_Handle(void)
{
    /* clock initialization */
    AES_DeInit();
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRYPT, ENABLE);

    /* Display Plain Data*/
    Display_PlainData(AES_TEXT_SIZE);

    /* Encrypt the plaintext message*/
    AES_ECB_Encrypt(BoardAB_EncryptionKey, 128, BoardA_TxBuffer, AES_TEXT_SIZE, BoardA_CipherText);

    /* Read the CipherText and check content correctness */
    if (Buffercmp(BoardA_ExpectedCipherText, BoardA_CipherText, AES_TEXT_SIZE) == SUCCESS)
    {
        printf("board A: AES ECB 128Keysize Encrypted ok\r\n");

        /* Display encrypted Data*/
        Display_EncryptedData(ECB, 128, AES_TEXT_SIZE);
        printf("board A: Send CipherText to Board B ...\r\n");


        for (uint32_t i = 0; i < AES_TEXT_SIZE; i++)
        {
            USART_SendData(USART2, (unsigned char) BoardA_CipherText[i]);

            while (USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET)
            {
            }

        }

        printf("board A: Send CipherText to Board B Finished ...\r\n");
    }
    else
    {
        printf("board A: AES ECB 128Keysize Encrypted Fail\r\n");
    }
}
#endif

/**
  * @brief  USART2 NVIC Configuration  .
  * @param  None
  * @retval None
  */
static void NVICConfiguration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  USART2 Configuration  .
  * @param  None
  * @retval None
  */
static void USART2_Config(uint32_t BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* Enable GPIOA clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);


    /* Configure GPIO of USART Tx to push-pull multiplexing mode*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure USART Rx GPIO to push-pull multiplexing mode*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Enable USART2 clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    /* Connect PXx to USARTx_Tx */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_4 );

    /* Connect PXx to USARTx_Rx */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_4);

    /*Configure serial port operating parameters  */
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART2, &USART_InitStructure);

    /* Enable serial port */
    USART_Cmd(USART2, ENABLE);

    /* Make sure the flag is cleared before receiving data */
    USART_ClearITPendingBit(USART2, USART_IT_RXNE);

    /* Enable serial receive interrupt and idle interrupt*/
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
    NVICConfiguration();
}

/* A plate processing flow  */
#ifdef AES_TWO_BOARD_A
/**
  * @brief  Display Plain Data
  * @param  datalength: length of the data to display
  * @retval None
  */
static void Display_PlainData(uint32_t datalength)
{
    uint32_t BufferCounter = 0;
    uint32_t count = 0;
    printf(" =================================================================\n\r");
    printf(" Plain Data :\n\r");
    printf(" --------------------------------------------------------------------\n\r");

    for (BufferCounter = 0; BufferCounter < datalength; BufferCounter++)
    {
        printf("[0x%02X]", BoardA_TxBuffer[BufferCounter]);
        count++;

        if (count == 16)
        {
            count = 0;
            printf("  Block %d \n\r", BufferCounter / 16);
        }
    }

    printf(" --------------------------------------------------------------------\n\r");
}

/**
  * @brief  Display Encrypted Data
  * @param  mode: chaining mode
  * @param  keysize: AES key size used
  * @param  datalength: length of the data to display
  * @retval None
  */
static void Display_EncryptedData(uint8_t mode, uint16_t keysize, uint32_t datalength)
{
    uint32_t BufferCounter = 0;
    uint32_t count = 0;
    printf("\n\r =================================================================\n\r");
    printf(" Encrypted Data with AES %d  Mode  ", keysize );

    if (mode == ECB)
    {
        printf("ECB\n\r");
    }

    printf(" --------------------------------------------------------------------\n\r");

    for (BufferCounter = 0; BufferCounter < datalength; BufferCounter++)
    {
        printf("[0x%02X]", BoardA_CipherText[BufferCounter]);
        count++;

        if (count == 16)
        {
            count = 0;
            printf(" Block %d \n\r", BufferCounter / 16);
        }
    }

    printf(" --------------------------------------------------------------------\n\r");
    printf(" =================================================================\n\r");
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }
}
/**
  * @brief  Wait for User push-button press to start transfer.
  * @param  None
  * @retval None
  */
void WaitForUserButtonPress(void)
{
    while (ubButtonPress == 0)
    {
        HK_EVAL_LEDToggle(LED2);
        Delay(0x3FFFF);
    }

    /* Turn LED2 off */
    HK_EVAL_LEDOff(LED2);
}

#endif

/* B plate processing flow  */
#ifdef AES_TWO_BOARD_B
/**
  * @brief  Display Decrypted Data
  * @param  mode: chaining mode
  * @param  keysize: AES key size used
  * @param  datalength: length of the data to display
  * @retval None
  */
static void Display_DecryptedData(uint8_t mode, uint16_t keysize, uint32_t datalength)
{
    uint32_t BufferCounter = 0;
    uint32_t count = 0;
    printf("\n\r =================================================================\n\r");
    printf(" Decrypted Data with AES %d  Mode  ", keysize );

    if (mode == ECB)
    {
        printf("ECB\n\r");
    }

    printf(" --------------------------------------------------------------------\n\r");

    for (BufferCounter = 0; BufferCounter < datalength; BufferCounter++)
    {
        printf("[0x%02X]", BoardB_ComputedPlainText[BufferCounter]);
        count++;

        if (count == 16)
        {
            count = 0;
            printf(" Block %d \n\r", BufferCounter / 16);
        }
    }

    printf(" --------------------------------------------------------------------\n\r");
    printf(" =================================================================\n\r");
}
#endif
/**
  * @brief  Compares two 8-bit buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval - SUCCESS: pBuffer1 identical to pBuffer2
  *         - ERROR: pBuffer1 differs from pBuffer2
  */
ErrorStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return ERROR;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return SUCCESS;
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
}
#endif /* USE_FULL_ASSERT */
