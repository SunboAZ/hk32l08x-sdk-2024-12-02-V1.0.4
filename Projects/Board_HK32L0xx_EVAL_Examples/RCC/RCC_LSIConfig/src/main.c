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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void Delay(__IO uint32_t nCount);
static void LSIEnableError(void);
static void LSIEnableConfig(void);
static void LSIGetSta(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Initialize LED1 and LED2 */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    /* Turn Off LED1 and LED2 */
    HK_EVAL_LEDOff(LED1);
    HK_EVAL_LEDOff(LED2);

    /* Configures EXTI Line */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_EXTI);

    /* Output HSE clock on MCO1 pin(PA8) ****************************************/

    /* Enable the GPIOA Clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* MCO pin configuration: PA8 */
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Schmit = GPIO_Schmit_Disable;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_0);

    /* Output System Clock on MCO pin */
    RCC_MCOConfig(RCC_MCOSource_LSI, RCC_MCOPrescaler_1);

    while (1)
    {
        /* Get LSI State */
        LSIGetSta();
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
  * @brief  LSI State Switch.
  * @retval None
  */
void LSIStaSwitch(void)
{
    if ((RCC->CSR & RCC_CSR_LSION) !=  RCC_CSR_LSION)
    {
        /* Enable LSI */
        LSIEnableConfig();
    }
    else
    {
        /* Disable LSI */
        RCC_LSICmd(DISABLE);
    }
}

/**
  * @brief  Get LSI State.
  * @retval None
  */
static void LSIGetSta(void)
{
    if ((RCC->CSR & RCC_CSR_LSION) !=  RCC_CSR_LSION)
    {
        /* Turn Off LED2 */
        HK_EVAL_LEDOff(LED2);

        /* If LSI is Off, Toggle LED1 */
        HK_EVAL_LEDToggle(LED1);
        Delay(0x3FFFF);
    }
    else
    {
        /* Turn Off LED1 */
        HK_EVAL_LEDOff(LED1);

        /* If LSI is On, Toggle LED2 */
        HK_EVAL_LEDToggle(LED2);
        Delay(0x4FFFF);
    }
}

/**
  * @brief  LSI Enable Config.
  * @retval None
  */
static void LSIEnableConfig(void)
{
    __IO uint32_t StartUpCounter = 0, LSIStatus = 0;

    RCC_LSICmd(ENABLE);

    /* Wait till LSI is ready and if Time out is reached exit */
    do
    {
        LSIStatus = RCC->CSR & RCC_CSR_LSIRDY;
        StartUpCounter++;
    } while ((LSIStatus == 0) && (StartUpCounter != 0xFFFF));


    if ((RCC->CSR & RCC_CSR_LSIRDY) == RESET)
    {
        /* LSI Enable Fail */
        LSIEnableError();
    }
}

/**
  * @brief  LSI Enable Error.
  * @retval None
  */
static void LSIEnableError(void)
{
    /* Turn Off LED1 and LED2 */
    HK_EVAL_LEDOff(LED1);
    HK_EVAL_LEDOff(LED2);

    while (1)
    {
        /* Toggle LED1/LED2 */
        HK_EVAL_LEDToggle(LED1);
        HK_EVAL_LEDToggle(LED2);
        Delay(0x3FFFF);
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



