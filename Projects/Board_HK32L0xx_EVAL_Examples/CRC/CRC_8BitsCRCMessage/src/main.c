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

/** @addtogroup CRC_8BitsCRCMessage
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define countof(a)             (uint8_t)(sizeof(a) / sizeof(*(a)))
#define BUFFER_SIZE            (countof(CRCBuffer) - 1)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t CRCBuffer[] = "HK32L0xx CortexM0 Device running on HK32L08x-EVAL";
uint8_t ComputedCRC = 0;
uint8_t ExpectedCRC = 0xFA; /* The expected CRC value of CRCBuffer using the
                            polynomial x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1.
                            This value is already computed using on-line CRC tool */
/* Private function prototypes -----------------------------------------------*/
static void CRC_Config(void);
static uint8_t CRC_8BitsCompute(uint8_t* data, uint32_t size);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Initialize LEDs available on HK32L08x-EVAL board */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    /* Configure the CRC */
    CRC_Config();

    /* Compute the CRC value of the 8-bit buffer: CRCBuffer */
    ComputedCRC = CRC_8BitsCompute(CRCBuffer, BUFFER_SIZE);

    /* Check if the computed CRC matches the expected one */
    if (ComputedCRC != ExpectedCRC)
    {
        /* Turn on LED2 */
        HK_EVAL_LEDOn(LED2);
    }
    else
    {
        /* Turn on LED1 */
        HK_EVAL_LEDOn(LED1);
    }

    /* Infinite loop */
    while (1)
    {
    }
}

/**
  * @brief  Configure the CRC.
  * @param  None
  * @retval None
  */
static void CRC_Config(void)
{
    /* Enable CRC AHB clock interface */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

    /* DeInit CRC peripheral */
    CRC_DeInit();

    /* Init the INIT register */
    CRC_SetInitRegister(0);
}

/**
  * @brief  Compute CRC value for input message
  * @param  data: pointer at uint8_t
  * @param  size: the size of the input message
  * @retval The computed CRC value
  */
static uint8_t CRC_8BitsCompute(uint8_t* data, uint32_t size)
{
    uint8_t* dataEnd = data + size;

    /* Reset CRC data register to avoid overlap when computing new data stream */
    CRC_ResetDR();

    while (data < dataEnd)
    {
        /* Write the input data in the CRC data register */
        CRC_CalcCRC8bits(*data++);
    }

    /* Return the CRC value */
    return (uint8_t)CRC_GetCRC();
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

