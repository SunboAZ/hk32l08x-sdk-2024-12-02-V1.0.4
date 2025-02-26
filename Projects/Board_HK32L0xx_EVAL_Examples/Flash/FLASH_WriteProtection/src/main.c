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
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define FLASH_PAGE_SIZE                ((uint16_t)0x400)
#define FLASH_PAGES_TO_BE_PROTECTED    (OB_WRP_Pages24to27)

#define BANK1_WRITE_START_ADDR         ((uint32_t)0x08006000)
#define BANK1_WRITE_END_ADDR           ((uint32_t)0x08007000)

/* Uncomment this line to program the Flash pages */
#define FLASH_PAGE_PROGRAM

/* Uncomment this line to Enable Write Protection */
#define WRITE_PROTECTION_ENABLE

/* Uncomment this line to Disable Write Protection */
//#define WRITE_PROTECTION_DISABLE

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t EraseCounter = 0x0, Address = 0x0;
uint32_t Data = 0x12345678;
uint32_t WRPR_Value = 0xFFFFFFFF, ProtectedPages = 0x0;
uint32_t NbrOfPage;
__IO FLASH_Status FLASHStatus = FLASH_COMPLETE;
__IO TestStatus MemoryProgramStatus = PASSED;

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
         file (KEIL_Startup_hk32l0xx.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_hk32l0xx.c file
       */

    /* Unlocks the FLASH control register and program memory access */
    FLASH_Unlock();

    /* Unlocks the option bytes block access */
    FLASH_OptionByteUnlock();

    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR | FLASH_FLAG_SIZE_ERR);

    /* Get pages write protection status */
    WRPR_Value = FLASH_OptionByteGetWRP();

#ifdef WRITE_PROTECTION_DISABLE

    /* Get pages already write protected */
    ProtectedPages = ~(WRPR_Value | FLASH_PAGES_TO_BE_PROTECTED);

    /* Check if desired pages are already write protected */
    if ((WRPR_Value | (~FLASH_PAGES_TO_BE_PROTECTED)) != 0xFFFFFFFF )
    {
        /* Erase all the option Bytes */
        FLASHStatus = FLASH_OptionByteErase();

        /* Check if there is write protected pages */
        if (ProtectedPages != 0x0)
        {
            /* Restore write protected pages */
            FLASHStatus = FLASH_OptionByteEnableWRP(ProtectedPages);
        }

        /* Generate System Reset to load the new option byte values */
        FLASH_OptionByteLaunch();
    }

#elif defined WRITE_PROTECTION_ENABLE

    /* Get current write protected pages and the new pages to be protected */
    ProtectedPages =  (~WRPR_Value) | FLASH_PAGES_TO_BE_PROTECTED;

    /* Check if desired pages are not yet write protected */
    if (((~WRPR_Value) & FLASH_PAGES_TO_BE_PROTECTED ) != FLASH_PAGES_TO_BE_PROTECTED)
    {

        /* Erase all the option Bytes because if a program operation is
          performed on a protected page, the Flash memory returns a
          protection error */
        FLASHStatus = FLASH_OptionByteErase();

        /* Enable the pages write protection */
        FLASHStatus = FLASH_OptionByteEnableWRP(ProtectedPages);

        /* Generate System Reset to load the new option byte values */
        FLASH_OptionByteLaunch();
    }

#endif /* WRITE_PROTECTION_DISABLE */

#ifdef FLASH_PAGE_PROGRAM

    /* Get pages write protection status */
    WRPR_Value = FLASH_OptionByteGetWRP();

    /* Get the number of pages to be erased */
    NbrOfPage = (BANK1_WRITE_END_ADDR - BANK1_WRITE_START_ADDR) / FLASH_PAGE_SIZE;

    /* The selected pages are not write protected */
    if ( (WRPR_Value & FLASH_PAGES_TO_BE_PROTECTED) != 0x00)
    {
        /* Clear pending flags */
        FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR | FLASH_FLAG_SIZE_ERR);

        /* erase the FLASH pages */
        for (EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
        {
            FLASHStatus = FLASH_ErasePage(BANK1_WRITE_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
        }

        /* FLASH Word program of data 0x12345678 at addresses defined by  BANK1_WRITE_START_ADDR and BANK1_WRITE_END_ADDR */
        Address = BANK1_WRITE_START_ADDR;

        while ((Address < BANK1_WRITE_END_ADDR) && (FLASHStatus == FLASH_COMPLETE))
        {
            FLASHStatus = FLASH_ProgramWord(Address, Data);
            Address = Address + 4;
        }

        /* Check the correctness of written data */
        Address = BANK1_WRITE_START_ADDR;

        while ((Address < BANK1_WRITE_END_ADDR) && (MemoryProgramStatus != FAILED))
        {
            if ((*(__IO uint32_t*) Address) != Data)
            {
                MemoryProgramStatus = FAILED;
            }

            Address += 4;
        }
    }
    else
    {
        /* Error to program the flash : The desired pages are write protected */
        MemoryProgramStatus = FAILED;
    }

#endif /* FLASH_PAGE_PROGRAM */

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



