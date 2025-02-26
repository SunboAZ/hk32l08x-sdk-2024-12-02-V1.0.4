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
/** @addtogroup HK32L0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
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
    GPIO_InitTypeDef        GPIO_InitStructure;

    /* GPIOC Periph clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* Configure PA1 and PA2 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    while (1)
    {
        /* Set PA1 and PA2 */
        GPIOA->BSRR = 0x06;

        /* Reset PA1 and PA2 */
        GPIOA->BRR = 0x06;

        /* Set PA1 and PA2 */
        GPIOA->BSRR = 0x06;

        /* Reset PA1 and PA2 */
        GPIOA->BRR = 0x06;

        /* Set PA1 and PA2 */
        GPIOA->BSRR = 0x06;

        /* Reset PA1 and PA2 */
        GPIOA->BRR = 0x06;

        /* Set PA1 and PA2 */
        GPIOA->BSRR = 0x06;

        /* Reset PA1 and PA2 */
        GPIOA->BRR = 0x06;

        /* Set PA1 and PA2 */
        GPIOA->BSRR = 0x06;

        /* Reset PA1 and PA2 */
        GPIOA->BRR = 0x06;

        /* Set PA1 and PA2 */
        GPIOA->BSRR = 0x06;

        /* Reset PA1 and PA2 */
        GPIOA->BRR = 0x06;

        /* Set PA1 and PA2 */
        GPIOA->BSRR = 0x06;

        /* Reset PA1 and PA2 */
        GPIOA->BRR = 0x06;

        /* Set PA1 and PA2 */
        GPIOA->BSRR = 0x06;

        /* Reset PA1 and PA2 */
        GPIOA->BRR = 0x06;

        /* Set PA1 and PA2 */
        GPIOA->BSRR = 0x06;

        /* Reset PA1 and PA2 */
        GPIOA->BRR = 0x06;

        /* Set PA1 and PA2 */
        GPIOA->BSRR = 0x06;

        /* Reset PA1 and PA2 */
        GPIOA->BRR = 0x06;
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


