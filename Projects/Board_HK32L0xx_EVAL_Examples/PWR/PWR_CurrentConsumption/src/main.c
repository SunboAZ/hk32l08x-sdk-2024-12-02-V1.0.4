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
#include "hk32l0xx_lp_modes.h"

/** @addtogroup HK32L0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup PWR_CurrentConsumption
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t i = 0;
__IO uint32_t uwCounter = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Configure Tamper Button */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);
    /* Enable PWR APB1 Clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    /* Allow access to Backup */
    PWR_BackupAccessCmd(ENABLE);
    /* Reset RTC Domain */
    RCC_BackupResetCmd(ENABLE);
    RCC_BackupResetCmd(DISABLE);

    /* Loop while Tamper button is maintained pressed */
    while (HK_EVAL_PBGetState(BUTTON_KEY1) != RESET)
    {
    }

    /* Loop while Tamper button is maintained pressed */
    while (HK_EVAL_PBGetState(BUTTON_KEY1) == RESET)
    {
    }

#if defined (LPRUN_MODE)
    /* enter LP RUN mode */
    LPRunMode_Measure();
#elif defined (SLEEP_MODE)
    /* enter Sleep mode */
    SleepMode_Measure();
#elif defined (LPSLEEP_MODE)
    /* enter low power Sleep mode */
    LPSleepMode_Measure();
#elif defined (STOP_MODE)
    /* enter stop mode */
    StopMode_Measure();
#elif defined (LPSTOP_MODE)
    /* enter low power Stop mode */
    LPStopMode_Measure();
#else
    /* Initialize LED2 on EVAL board */
    HK_EVAL_LEDInit(LED2);

    /* Infinite loop */
    while (1)
    {
        /* Toggle The LED2 */
        HK_EVAL_LEDToggle(LED2);

        /* Inserted Delay */
        for (i = 0; i < 0x7FFF; i++)
        {
        }
    }

#endif
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

