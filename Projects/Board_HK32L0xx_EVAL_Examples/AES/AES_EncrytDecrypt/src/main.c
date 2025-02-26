/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body, This example provides AES encryption decryption  fuctions
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*              1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define AES_TEXT_SIZE    16
#define ECB 0
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t ubButtonPress = 0;

AES_InitTypeDef AES_InitStructure;
AES_KeyInitTypeDef  AES_KeyInitStructure;

uint8_t PlainText[AES_TEXT_SIZE] =
{
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
    0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
};

uint8_t ComputedPlainText[AES_TEXT_SIZE]  = {0};

uint8_t ExpectedCipherText[AES_TEXT_SIZE]  =
{
    0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60,
    0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97
};

uint8_t CipherText[AES_TEXT_SIZE]  = {0};

uint8_t EncryptionKey[16]  = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                              0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
                             };

/* Private function prototypes -----------------------------------------------*/
static ErrorStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
static void Display_PlainData(uint32_t datalength);
static void Display_EncryptedData(uint8_t mode, uint16_t keysize, uint32_t datalength);
static void Display_DecryptedData(uint8_t mode, uint16_t keysize, uint32_t datalength);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Initialize LED1 */

    HK_EVAL_LEDInit(LED1);

    /* Initialize LED2 */

    HK_EVAL_LEDInit(LED2);

    /* ------------------------------- USART-------------------------------------*/

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

    /* Initialize User push-button in EXTI mode */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_EXTI);
    printf("AES EncryptDecrypt!Only provides encryption and decryption functions,is a basic example\r\n");

    /* Start to  continue */
    printf("Wait for User push-button press to start encrypt/decrypt ...\r\n");

    /* Wait for User push-button press to continue */
    WaitForUserButtonPress();

    /* AES  encrypt/decrypt */
    AES_Function_Handle();

    /* Infinite loop */
    while (1)
    {
    }
}

/**
  * @brief  Config AES  .
  * @retval None
  */
void AES_Function_Handle(void)
{
    /* AES CLK INIT */
    AES_DeInit();
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRYPT, ENABLE);

    /* Disable AES */
    AES_Cmd(DISABLE);
    /******************************************************************************/

    /*                             AES mode ECB 128keysize                        */
    /******************************************************************************/

    /* Display Plain Data*/
    Display_PlainData(AES_TEXT_SIZE);
    /*============================================================================
      Encryption ECB mode
    ==============================================================================*/

    /* Encrypt the plaintext message*/

    AES_ECB_Encrypt(EncryptionKey, 128, PlainText, AES_TEXT_SIZE, CipherText);

    if (Buffercmp(ExpectedCipherText, CipherText, AES_TEXT_SIZE) != ERROR)
    {
        printf("\r\n AES Encrypt OK! ExpectedCipherText: ");

        /* Display encrypted Data*/
        Display_EncryptedData(ECB, 128, AES_TEXT_SIZE);
        HK_EVAL_LEDOn(LED1);
    }
    else
    {
        printf("\r\nAES Encrypt Fail! no ExpectedCipherText!\r\n");
        HK_EVAL_LEDOff(LED1);
    }

    printf("\r\n");
    /******************************************************************************/
    /*                             AES mode ECB: Decryption                       */
    /******************************************************************************/
    AES_ECB_Decrypt(EncryptionKey, 128, CipherText, AES_TEXT_SIZE, ComputedPlainText);

    /* Read the ComputedPlainText and check content correctness */

    if (Buffercmp(PlainText, ComputedPlainText, AES_TEXT_SIZE) != ERROR)
    {
        /* OK */
        printf("\r\nAES Decrypt OK! ComputedPlainText: ");
        Display_DecryptedData(ECB, 128, AES_TEXT_SIZE);

        HK_EVAL_LEDOn(LED2);
    }
    else
    {
        /* KO */
        printf("\r\nAES Decrypt Fail!no ComputedPlainText!\r\n");
        HK_EVAL_LEDOff(LED2);
    }
}

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
        printf("[0x%02X]", PlainText[BufferCounter]);
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
        printf("[0x%02X]", CipherText[BufferCounter]);
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
        printf("[0x%02X]", ComputedPlainText[BufferCounter]);
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
