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

/** @addtogroup DVSQ_Basic
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
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
    //ErrorStatus ErrLog;

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
    HK_EVAL_LEDInit(LED1);

    /* Configure LEDs */
    HK_EVAL_LEDOn(LED1);

    /* Output a message on Hyperterminal using printf function */
    printf("\n\r  *********************** DVSQ Basic Example ***********************\n\r");
    {
        uint32_t dividend = 0x1234;
        uint32_t divisor = 0x34;
        uint32_t remainder = 0;
        uint16_t result_sqr_fraction = 0;
        uint32_t result_div = 0, result_sqr = 0;
        float fraction = 0;

        /* init DVSQ */
        DVSQ_Init();

        /* Unsigned division operation */
        result_div = DVSQ_UDivsion(dividend, divisor, &remainder);
        printf("\n\r [Unsigned division] %d/%d=%d...%d\n\r", dividend, divisor, result_div, remainder);

        /* Square root operation */
        result_sqr = DVSQ_Sqrt(dividend);
        printf("\n\r [Square root] Suare(%d)=%d\n\r", dividend, result_sqr);

        /* High precision square root operation */
        result_sqr = DVSQ_SqrtH(dividend, &result_sqr_fraction);

        /* Fractional Part */
        fraction = (float)result_sqr_fraction / 65536;
        printf("\n\r [Square root High precision] Suare(%d)=%f\n\r", dividend, (float)(result_sqr + fraction));
    }

    /* Infinite loop */
    while (1)
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


