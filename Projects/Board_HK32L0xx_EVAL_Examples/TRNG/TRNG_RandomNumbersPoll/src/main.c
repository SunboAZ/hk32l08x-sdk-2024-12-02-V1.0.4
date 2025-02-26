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

/** @addtogroup TRNG_RandomNumbersPoll
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define    NB_OF_GENERATED_RANDOM_NUMBERS      8       /* Nb of Random numbers generated after eash User button press */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Array used for storing generated Random 32bit Numbers */
uint32_t aRandom32bit[NB_OF_GENERATED_RANDOM_NUMBERS];
uint8_t ubButtonPress = 0;
USART_InitTypeDef USART_InitStructure;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void Delay(__IO uint32_t nCount);
static void Configure_Config(void);
static void RandomNumbersGeneration(void);
static void WaitForUserButtonPress(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
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
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    /* Initialize UART3 */
    HK_EVAL_COMInit(COM1, &USART_InitStructure);

    /* Initialize User push-button in EXTI mode */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_EXTI);

    /* Configure TRNG (TRNG IP configuration : Clock enabling) */
    Configure_Config();

    /* Wait for User push-button press to trigger random numbers generation */
    WaitForUserButtonPress();

    /* Generate Random Numbers series */
    RandomNumbersGeneration();

    /* Infinite loop */
    while (1)
    {
    }
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
static void Delay(__IO uint32_t nCount)
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
static void WaitForUserButtonPress(void)
{
    while (ubButtonPress == 0)
    {
        HK_EVAL_LEDToggle(LED2);
        Delay(0x3FFFF);
    }

    /* Turn LED2 off */
    HK_EVAL_LEDOff(LED2);
}

/**
  * @brief  This function configures TRNG Instance.
  * @note   This function is used to :
  *         - Enable peripheral clock for TRNG.
  * @param  None
  * @retval None
  */
static void Configure_Config(void)
{
    /* Enable TRNG clock source */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_TRNG, ENABLE);
}

/**
  * @brief  This function performs several random numbers generation.
  * @note   Generated random numbers are stored in global variable array, so that
  *         generated values could be observed by user by watching variable content
  *         in specific debugger window
  * @param  None
  * @retval None
  */
static void RandomNumbersGeneration(void)
{
    uint8_t index = 0;

    /* Generate Random 32bit Numbers */
    for (index = 0; index < NB_OF_GENERATED_RANDOM_NUMBERS; index++)
    {
        /* Initialize random numbers generation */
        TRNG_Cmd(ENABLE);

        /* Wait until one TRNG number is ready */
        while (TRNG_GetFlagStatus(TRNG_FLAG_DRDY) == RESET)
        {
        }

        /* Otherwise, no error detected : Value of generated random number could be retrieved
        and stored in dedicated array */
        if (TRNG_GetRandomNumber(&aRandom32bit[index]))
        {
            /* Display the Random number value on the  USART */
            printf("Random32bit:0x%x    count:%d\r\n", aRandom32bit[index], index + 1);
        }
        else
        {
            /* Clock or Seed Error detected. Set LED to blinking mode (Error type)*/
            HK_EVAL_LEDToggle(LED2);
            Delay(0x3FFFF);
        }
    }

    /* Values of Generated Random numbers are now available in aRandom32bit array.
     LED2 is turned on */
    HK_EVAL_LEDOn(LED2);
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



