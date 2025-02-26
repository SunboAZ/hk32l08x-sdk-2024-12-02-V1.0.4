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

/** @addtogroup BEEPER_Example
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
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDOff(LED1);

    GPIO_InitTypeDef GPIO_InitStructure;
    BEEPER_InitTypeDef BEEPER_InitStructure;

    /* GPIOF periph clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

    /* BEEPER periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_BEEPER, ENABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Enabel LSI clock */
    RCC_LSICmd(ENABLE);

    /* Wait untill LSI ready */
    while (!RCC_GetFlagStatus(RCC_FLAG_LSIRDY))
    {
    }

    /* Config GPIO */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOF, GPIO_PinSource6, GPIO_AF_14);

    /* Config BEEPER */
    BEEPER_InitStructure.BEEPER_Clock = BEEPER_CLOCK_LSI;
    BEEPER_InitStructure.BEEPER_Prescaler = BEEPER_Prescaler_16;
    BEEPER_Init(&BEEPER_InitStructure);

    /* Enable BEEPER */
    BEEPER_Cmd(ENABLE);

    HK_EVAL_LEDOn(LED1);

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



