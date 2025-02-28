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

/** @addtogroup CORTEXM_ModePrivilege
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SP_PROCESS_SIZE             0x200  /* Process stack size */
#define SP_PROCESS                  0x02   /* Process stack */
#define SP_MAIN                     0x00   /* Main stack */
#define THREAD_MODE_PRIVILEGED      0x00   /* Thread mode has privileged access */
#define THREAD_MODE_UNPRIVILEGED    0x01   /* Thread mode has unprivileged access */

/* Private macro -------------------------------------------------------------*/

#if defined ( __CC_ARM   )
/**
  * @brief  __SVC function used to trigger svc handler
  * @param  None
  * @retval None
  */
__ASM void __SVC(void)
{
    SVC 0x01
    BX R14
}
#elif defined ( __ICCARM__ )

/**
  * @brief  __SVC function used to trigger svc handler
  * @param  None
  * @retval None
  */
static __INLINE  void __SVC()
{
    __ASM ("svc 0x01");
}
#elif defined   (  __GNUC__  )
/**
  * @brief  __SVC function used to trigger svc handler
  * @param  None
  * @retval None
  */
static __INLINE void __SVC()
{
    __ASM volatile ("svc 0x01");
}
#endif

/* Private variables ---------------------------------------------------------*/
__IO uint8_t PSPMemAlloc[SP_PROCESS_SIZE];
__IO uint32_t Index = 0, PSPValue = 0, CurrentStack = 0, ThreadMode = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
           this is done through SystemInit() function which is called from startup
           file (KEIL_Startup_hk32l0xx.s.s) before to branch to application main.
           To reconfigure the default setting of SystemInit() function, refer to
           system_hk32l0xx.c file
         */

    /* Switch Thread mode Stack from Main to Process -----------------------------*/

    /* Initialize memory reserved for Process Stack */
    for (Index = 0; Index < SP_PROCESS_SIZE; Index++)
    {
        PSPMemAlloc[Index] = 0x00;
    }

    /* Set Process stack value */
    __set_PSP((uint32_t)PSPMemAlloc + SP_PROCESS_SIZE);

    /* Select Process Stack as Thread mode Stack */
    __set_CONTROL(SP_PROCESS);

    __ISB();

    /* Get the Thread mode stack used */
    if ((__get_CONTROL() & 0x02) == SP_MAIN)
    {
        /* Main stack is used as the current stack */
        CurrentStack = SP_MAIN;
    }
    else
    {
        /* Process stack is used as the current stack */
        CurrentStack = SP_PROCESS;

        /* Get process stack pointer value */
        PSPValue = __get_PSP();
    }

    /* Switch Thread mode from privileged to unprivileged ------------------------*/
    /* Thread mode has unprivileged access */
    __set_CONTROL(THREAD_MODE_UNPRIVILEGED | SP_PROCESS);

    __ISB();

    /* Unprivileged access mainly affect ability to:
        - Use or not use certain instructions such as MSR fields
        - Access System Control Space (SCS) registers such as NVIC and SysTick */

    /* Check Thread mode privilege status */
    if ((__get_CONTROL() & 0x01) == THREAD_MODE_PRIVILEGED)
    {
        /* Thread mode has privileged access  */
        ThreadMode = THREAD_MODE_PRIVILEGED;
    }
    else
    {
        /* Thread mode has unprivileged access*/
        ThreadMode = THREAD_MODE_UNPRIVILEGED;
    }

    /* Switch back Thread mode from unprivileged to privileged -------------------*/
    /* Try to switch back Thread mode to privileged (Not possible, this can be
       done only in Handler mode) */
    __set_CONTROL(THREAD_MODE_PRIVILEGED | SP_PROCESS);

    __ISB();

    /* Generate a system call exception, and in the ISR switch back Thread mode
      to privileged */
    __SVC();

    /* Check Thread mode privilege status */
    if ((__get_CONTROL() & 0x01) == THREAD_MODE_PRIVILEGED)
    {
        /* Thread mode has privileged access  */
        ThreadMode = THREAD_MODE_PRIVILEGED;
    }
    else
    {
        /* Thread mode has unprivileged access*/
        ThreadMode = THREAD_MODE_UNPRIVILEGED;
    }

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


