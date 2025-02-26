/*******************************************************************************
* @copyright:  Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:   system_hk32l0xx.c
* @brief:      config system clock
* @author:     AE Team
* @version:    V1.0.0/2024-01-04
*                     1.Initial version
* @log:
*******************************************************************************/
#include "hk32l0xx.h"

#ifndef SYSCLK_SOURCE
    #error "Please define the value of SYSCLK_SOURCE !"
#endif

/*******************************************************************************
*  Clock Definitions
*******************************************************************************/
#if( SYSCLK_SOURCE == SYSCLK_SRC_HSE )
    uint32_t SystemCoreClock         = SYSCLK_FREQ_HSE;                            /*!< System Clock Frequency (Core Clock) */
    static void SetSysClockToHSE(void);
    #elif( SYSCLK_SOURCE == SYSCLK_SRC_PLL)
    #if defined SYSCLK_HSE8M_PLL_FREQ_4MHz
        uint32_t SystemCoreClock           = SYSCLK_HSE8M_PLL_FREQ_4MHz;             /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo4_HSE8M_PLL(void);
    #elif defined SYSCLK_HSE8M_PLL_FREQ_8MHz
        uint32_t SystemCoreClock           = SYSCLK_HSE8M_PLL_FREQ_8MHz;             /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo8_HSE8M_PLL(void);
    #elif defined SYSCLK_HSE8M_PLL_FREQ_12MHz
        uint32_t SystemCoreClock           = SYSCLK_HSE8M_PLL_FREQ_12MHz;                /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo12_HSE8M_PLL(void);
    #elif defined SYSCLK_HSE8M_PLL_FREQ_24MHz
        uint32_t SystemCoreClock           = SYSCLK_HSE8M_PLL_FREQ_24MHz;                /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo24_HSE8M_PLL(void);
    #elif defined SYSCLK_HSE8M_PLL_FREQ_32MHz
        uint32_t SystemCoreClock           = SYSCLK_HSE8M_PLL_FREQ_32MHz;                /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo32_HSE8M_PLL(void);
    #elif defined SYSCLK_HSE8M_PLL_FREQ_36MHz
        uint32_t SystemCoreClock           = SYSCLK_HSE8M_PLL_FREQ_36MHz;                /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo36_HSE8M_PLL(void);
    #elif defined SYSCLK_HSE8M_PLL_FREQ_48MHz
        uint32_t SystemCoreClock           = SYSCLK_HSE8M_PLL_FREQ_48MHz;                /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo48_HSE8M_PLL(void);
    #elif defined SYSCLK_HSI_PLL_FREQ_36MHz
        uint32_t SystemCoreClock           = SYSCLK_HSI_PLL_FREQ_36MHz;                  /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo36_HSI_PLL(void);
    #elif defined SYSCLK_HSI_PLL_FREQ_48MHz
        uint32_t SystemCoreClock           = SYSCLK_HSI_PLL_FREQ_48MHz;                  /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo48_HSI_PLL(void);
    #endif
    #elif( SYSCLK_SOURCE == SYSCLK_SRC_HSI8M)
    uint32_t SystemCoreClock         = SYSCLK_FREQ_HSI_8M;                         /*!< System Clock Frequency (Core Clock) */
    static void SetSysClockToHSI_8M(void);
    #elif( SYSCLK_SOURCE == SYSCLK_SRC_HSI16M)
    uint32_t SystemCoreClock         = SYSCLK_FREQ_HSI_16M;                        /*!< System Clock Frequency (Core Clock) */
    static void SetSysClockToHSI_16M(void);
    #elif( SYSCLK_SOURCE == SYSCLK_SRC_HSI48M)
    uint32_t SystemCoreClock         = SYSCLK_FREQ_HSI_48M;                        /*!< System Clock Frequency (Core Clock) */
    static void SetSysClockToHSI_48M(void);
    #elif( SYSCLK_SOURCE == SYSCLK_SRC_EXTCLK_IO)
    uint32_t SystemCoreClock         = SYSCLK_FREQ_EXTCLK;                         /*!< System Clock Frequency (Core Clock) */
    static void SetSysClockToEXTCLK(void);
    #elif( SYSCLK_SOURCE == SYSCLK_SRC_LSI)
    uint32_t SystemCoreClock         = SYSCLK_FREQ_LSI;                            /*!< System Clock Frequency (Core Clock) */
    static void SetSysClockToLSI(void);
    #elif( SYSCLK_SOURCE == SYSCLK_SRC_LSE)
    uint32_t SystemCoreClock         = SYSCLK_FREQ_LSE;                            /*!< System Clock Frequency (Core Clock) */
    static void SetSysClockToLSE(void);
    #elif( SYSCLK_SOURCE == SYSCLK_SRC_MSI)
    uint32_t SystemCoreClock         = SYSCLK_FREQ_MSI;                            /*!< System Clock Frequency (Core Clock) */
    static void SetSysClockToMSI(void);
#endif

/** @addtogroup hk32l0xx_System_Private_Variables
  * @{
  */

__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

/**
  * @}
  */

/** @addtogroup hk32l0xx_System_Private_FunctionPrototypes
  * @{
  */

static void SetSysClock(void);

/**
  * @}
  */

/** @addtogroup hk32l0xx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  *         Initialize the Embedded Flash Interface, the PLL and update the
  *         SystemCoreClock variable.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
    /* Set HSION bit */
    RCC->CR |= (uint32_t)0x00000001;

    /* Reset SW[1:0], HPRE[3:0], PPRE1[2:0], PPRE2[2:0], MCO[3:0], MCOPRE[2:0] and PLLNODIV bits */
    RCC->CFGR &= (uint32_t)0x80FFC00C;

    /* Reset ESSS bit */
    RCC->CFGR4 &= ~RCC_CFGR4_ESSS;

    /* Reset HSEON, CSSON and PLLON bits */
    RCC->CR &= (uint32_t)0xFEF6FFFF;

    /* Reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits */
    RCC->CFGR &= (uint32_t)0xFFC0FFFF;

    /* Reset PREDIV1[3:0] bits */
    RCC->CFGR2 &= (uint32_t)0xFFFFFFF0;

    /* Reset USARTSW[1:0], I2CSW bits */
    RCC->CFGR3 &= (uint32_t)0xFFFFFFEC;

    /* Reset HSI16, HSI48 bit */
    RCC->CR2 &= (uint32_t)0xFFFFFFF6;

    /* Disable all interrupts */
    RCC->CIR = 0x00000000;

    /* Configure the System clock frequency, AHB/APBx prescalers and Flash settings */
    SetSysClock();

#ifdef VECT_TAB_SRAM
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_MEM_MODE; /* Vector Table Relocation in Internal SRAM. */
#else
    FLASH->INT_VEC_OFFSET = VECT_TAB_OFFSET ; /* Vector Table Relocation in Internal FLASH. */
#endif

}

/**
  * @brief  Update SystemCoreClock according to Clock Register Values
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.
  *
  * @note   - The system frequency computed by this function is not the real
  *           frequency in the chip. It is calculated based on the predefined
  *           constant and the selected clock source:
  *
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(*)
  *
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(**)
  *
  *           - If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(**)
  *             or HSI_VALUE(*) multiplied/divided by the PLL factors.
  *
  *         (*) HSI_VALUE is a constant defined in hk32l0xx.h file (default value
  *             8 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.
  *
  *         (**) HSE_VALUE is a constant defined in hk32l0xx.h file (default value
  *              8 MHz), user has to ensure that HSE_VALUE is same as the real
  *              frequency of the crystal used. Otherwise, this function may
  *              have wrong result.
  *
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate (void)
{
    uint32_t tmp = 0, pllmull = 0, pllsource = 0, prediv1factor = 0;

    /* Get SYSCLK source -------------------------------------------------------*/
    tmp = RCC->CFGR & RCC_CFGR_SWS;

    switch (tmp)
    {
        case 0x00:  /* HSI used as system clock */
            SystemCoreClock = HSI_VALUE;
            break;

        case 0x04:  /* HSE used as system clock */
            SystemCoreClock = HSE_VALUE;
            break;

        case 0x08:  /* PLL used as system clock */
            /* Get PLL clock source and multiplication factor ----------------------*/
            pllmull = RCC->CFGR & RCC_CFGR_PLLMUL;
            pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
            pllmull = ( pllmull >> 18) + 2;

            if (pllsource == 0x00)
            {
                /* HSI oscillator clock divided by 2 selected as PLL clock entry */
                SystemCoreClock = (HSI_VALUE >> 1) * pllmull;
            }
            else
            {
                prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV) + 1;
                /* HSE oscillator clock selected as PREDIV1 clock entry */
                SystemCoreClock = (HSE_VALUE / prediv1factor) * pllmull;
            }

            break;

        default: /* HSI used as system clock */
            SystemCoreClock = HSI_VALUE;
            break;
    }

    /* Compute HCLK clock frequency ----------------*/
    /* Get HCLK prescaler */
    tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
    /* HCLK clock frequency */
    SystemCoreClock >>= tmp;
}

/**
  * @brief  PMU(MBGP/LPBGP/LDO) Load Code
  * @retval None
  */
static void LoadOptionData_BGPLDO_to_Pmu(void)
{
    uint32_t tmp_data = 0;  
    tmp_data = *((uint32_t *)(0x1ffff7f4));
    tmp_data = tmp_data>>16;
  
    /* PmuFlag non-existent */
    if(tmp_data != 0x659A)
    {
        tmp_data = 0;
      
        /* PWR Clock Enable */
        *(uint32_t *)((uint32_t)0x4002101C) |= (uint32_t)0x10000000;

        /* Unlock PMU register */
        *(uint32_t *)((uint32_t)0x4000704C) = 0x1985;       
        *(uint32_t *)((uint32_t)0x4000704C) = 0x0429;

        if (*(uint32_t *)(0x1fffdbe0) != 0xFFFFFFFF)
        {
            /* MBGP and LPBGP load */
            tmp_data = (uint32_t)((*(uint32_t *)(0x1fffdbe0)) & 0x00001F1F);
            tmp_data |= (uint32_t)((*(uint32_t *)((uint32_t)0x40007070)) & 0xE0E0);
            *(uint32_t *)((uint32_t)0x40007070) = tmp_data;
        }

        if (*(uint32_t *)(0x1fffdbe8) != 0xFFFFFFFF)
        {
            /* LDO_RUN load */
            tmp_data = (uint32_t)((*(uint32_t *)(0x1fffdbe8)) & 0x7FF);
            tmp_data |= (uint32_t)(((*(uint32_t *)(0x1fffdbe8)) & 0x000F) << 12);
            *(uint32_t *)((uint32_t)0x40007060) = tmp_data;
          
            /* normal_stop load */
            tmp_data = (uint32_t)((*(uint32_t *)(0x1fffdbe8)) & 0xF);
            if(tmp_data > 2)
            {
                tmp_data = tmp_data - 2;
                tmp_data |= (tmp_data << 12);             
                *(uint32_t *)((uint32_t)0x40007064) = tmp_data;
            }
             
            /* PWR_CR_VOS = 0x00, select load value */
            *(uint32_t *)((uint32_t)0x40007000) &= ~((uint32_t)0x03 << 11);
        }        
        
        /* lpstop/standby load */
        *((uint32_t*)0x40007068) = 0x13;
        /* lprun laod */
        *((uint32_t*)0x4000706C) = 0x44;
          
        /* Lock PMU register */
        *(uint32_t *)((uint32_t)0x4000704C) = 0xFFFF;        
        *(uint32_t *)((uint32_t)0x4000704C) = 0xFFFF;
         /* PWR Clock Disable */
        *(uint32_t *)((uint32_t)0x4002101C) &= ~((uint32_t)0x10000000);   
    }  
}

/**
  * @brief  Configures the System clock frequency, AHB/APBx prescalers and Flash
  *         settings.
  * @note   This function should be called only once the RCC clock configuration
  *         is reset to the default reset state (done in SystemInit() function).
  * @param  None
  * @retval None
  */
static void SetSysClock(void)
{
    /********************************************************************************************/   
    /* Flash Unlock */
    FLASH->KEYR = (uint32_t)0x45670123;
    FLASH->KEYR = (uint32_t)0xCDEF89AB;
    /* ECC Auto Correct Off */
    FLASH->CR &= (uint32_t)0xFFFEFFFF;
    /* Flash lock */
    FLASH->CR |= (uint32_t)0x80;

    /********************************************************************************************/
    /* LSI_TrimValue_ValidFlag = 1 */
    if ((*(uint32_t *)(0x1ffff7f8) & 0x0000FFFF) == 0x0000748B)
    {
        /* LSI Load */
        *(uint32_t *)((uint32_t)0x40021024) &= ~((uint32_t)(0x00000FFC));
        *(uint32_t *)((uint32_t)0x40021024) |= (uint32_t)((*(uint32_t *)(0x1ffff7f8) & 0x0FC00000) >> 16);
        *(uint32_t *)((uint32_t)0x40021024) |= (uint32_t)((*(uint32_t *)(0x1ffff7f8) & 0x000F0000) >> 14);
    }

    /********************************************************************************************/
    /* PMU(MBGP/LPBGP/LDO) Load */
    LoadOptionData_BGPLDO_to_Pmu();
    
    /********************************************************************************************/
    /* LPTIM1/2/3 reset */
    RCC->APB1RSTR |= 0x80000000 ;
    RCC->APB1RSTR |= 0x1 << 10 ;
    RCC->APB2RSTR |= 0x1 << 24 ;

    /********************************************************************************************/
    /* SYSCFG_CFGR1_PA9_PA10_PA11_PA12_REMAP Reload */
    RCC->APB2RSTR |= RCC_APB2RSTR_SYSCFGRST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_SYSCFGRST;
    

#if defined SYSCLK_FREQ_HSE
    SetSysClockToHSE();
#elif defined SYSCLK_HSE8M_PLL_FREQ_4MHz
    SetSysClockTo4_HSE8M_PLL();
#elif defined SYSCLK_HSE8M_PLL_FREQ_8MHz
    SetSysClockTo8_HSE8M_PLL();
#elif defined SYSCLK_HSE8M_PLL_FREQ_12MHz
    SetSysClockTo12_HSE8M_PLL();
#elif defined SYSCLK_HSE8M_PLL_FREQ_24MHz
    SetSysClockTo24_HSE8M_PLL();
#elif defined SYSCLK_HSE8M_PLL_FREQ_32MHz
    SetSysClockTo32_HSE8M_PLL();
#elif defined SYSCLK_HSE8M_PLL_FREQ_36MHz
    SetSysClockTo36_HSE8M_PLL();
#elif defined SYSCLK_HSE8M_PLL_FREQ_48MHz
    SetSysClockTo48_HSE8M_PLL();
#elif defined SYSCLK_HSI_PLL_FREQ_36MHz
    SetSysClockTo36_HSI_PLL();
#elif defined SYSCLK_HSI_PLL_FREQ_48MHz
    SetSysClockTo48_HSI_PLL();
#elif defined SYSCLK_FREQ_HSI_8M
    SetSysClockToHSI_8M();
#elif defined SYSCLK_FREQ_HSI_16M
    SetSysClockToHSI_16M();
#elif defined SYSCLK_FREQ_HSI_48M
    SetSysClockToHSI_48M();
#elif defined SYSCLK_FREQ_EXTCLK
    SetSysClockToEXTCLK();
#elif defined SYSCLK_FREQ_LSI
    SetSysClockToLSI();
#elif defined SYSCLK_FREQ_LSE
    SetSysClockToLSE();
#elif defined SYSCLK_SRC_MSI
    SetSysClockToMSI();
#endif

    /* If none of the define above is enabled, the HSI is used as System clock
       source (default after reset) */
}

#if( SYSCLK_SOURCE == SYSCLK_SRC_HSE)
/**
  * @brief  Selects HSE as System clock source and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockToHSE(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);

        if (HSE_VALUE <= 24000000)
        {
            FLASH->ACR |= ((uint32_t)0x0) << FLASH_ACR_LATENCY_Pos;
        }
        else
        {
            if (HSE_VALUE <= 48000000)
            {
                FLASH->ACR |= (uint32_t)0x1 << FLASH_ACR_LATENCY_Pos;
            }
        }

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

        /* Select HSE as system clock source */
        RCC->CFGR4 &= ~RCC_CFGR4_ESSS;

        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)0x1 << RCC_CFGR_SW_Pos;

        /* Wait till HSE is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != ((uint32_t)0x1 << RCC_CFGR_SWS_Pos))
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock configuration. User can add here some code to deal with this error */
    }
}

#elif defined SYSCLK_HSE8M_PLL_FREQ_4MHz
/**
  * @brief  Sets System clock frequency to 4MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo4_HSE8M_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration*/
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= ((uint32_t)0x0) << FLASH_ACR_LATENCY_Pos;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

        /* PLL configuration: = HSE / prediv4 * 2 = 4 MHz */
        RCC->CFGR2 &= ~(RCC_CFGR2_PREDIV);
        RCC->CFGR2 |= (uint32_t)0x3 << RCC_CFGR2_PREDIV_Pos;

        RCC->CFGR4 &= ~RCC_CFGR4_PPSS;
        RCC->CFGR4 |= (uint32_t)0x0 << RCC_CFGR4_PPSS_Pos;

        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL));
        RCC->CFGR |= (uint32_t)((0x1 << RCC_CFGR_PLLSRC_Pos) | ((uint32_t)0x1 << RCC_CFGR_PLLXTPRE_Pos) | ((uint32_t)0x0 << RCC_CFGR_PLLMUL_Pos));

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= ~(RCC_CFGR_SW);
        RCC->CFGR |= (uint32_t)0x2 << RCC_CFGR_SW_Pos;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != ((uint32_t)0x2 << RCC_CFGR_SWS_Pos))
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}

#elif defined SYSCLK_HSE8M_PLL_FREQ_8MHz
/**
  * @brief  Sets System clock frequency to 8MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo8_HSE8M_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= ((uint32_t)0x0) << FLASH_ACR_LATENCY_Pos;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

        /* PLL configuration: = HSE / prediv2 * 2 = 8 MHz */
        RCC->CFGR2 &= ~(RCC_CFGR2_PREDIV);
        RCC->CFGR2 |= (uint32_t)0x1 << RCC_CFGR2_PREDIV_Pos;

        RCC->CFGR4 &= ~RCC_CFGR4_PPSS;
        RCC->CFGR4 |= (uint32_t)0x0 << RCC_CFGR4_PPSS_Pos;

        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL));
        RCC->CFGR |= (uint32_t)((0x1 << RCC_CFGR_PLLSRC_Pos) | ((uint32_t)0x1 << RCC_CFGR_PLLXTPRE_Pos) | ((uint32_t)0x0 << RCC_CFGR_PLLMUL_Pos));

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= ~(RCC_CFGR_SW);
        RCC->CFGR |= (uint32_t)0x2 << RCC_CFGR_SW_Pos;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != ((uint32_t)0x2 << RCC_CFGR_SWS_Pos))
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}


#elif defined SYSCLK_HSE8M_PLL_FREQ_12MHz
/**
  * @brief  Sets System clock frequency to 12MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo12_HSE8M_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= ((uint32_t)0x0) << FLASH_ACR_LATENCY_Pos;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

        /* PLL configuration: = HSE / prediv2 * 3 = 12 MHz */
        RCC->CFGR2 &= ~(RCC_CFGR2_PREDIV);
        RCC->CFGR2 |= (uint32_t)0x1 << RCC_CFGR2_PREDIV_Pos;

        RCC->CFGR4 &= ~RCC_CFGR4_PPSS;
        RCC->CFGR4 |= (uint32_t)0x0 << RCC_CFGR4_PPSS_Pos;

        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL));
        RCC->CFGR |= (uint32_t)((0x1 << RCC_CFGR_PLLSRC_Pos) | ((uint32_t)0x1 << RCC_CFGR_PLLXTPRE_Pos) | ((uint32_t)0x1 << RCC_CFGR_PLLMUL_Pos));

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= ~(RCC_CFGR_SW);
        RCC->CFGR |= (uint32_t)0x2 << RCC_CFGR_SW_Pos;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != ((uint32_t)0x2 << RCC_CFGR_SWS_Pos))
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}

#elif defined SYSCLK_HSE8M_PLL_FREQ_24MHz
/**
  * @brief  Sets System clock frequency to 24MHz and configure HCLK, PCLK2 and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo24_HSE8M_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= ((uint32_t)0x0) << FLASH_ACR_LATENCY_Pos;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

        /* PLL configuration: = HSE * pllmul3 = 24 MHz */
        RCC->CFGR2 &= ~(RCC_CFGR2_PREDIV);
        RCC->CFGR2 |= (uint32_t)0x0 << RCC_CFGR2_PREDIV_Pos;

        RCC->CFGR4 &= ~RCC_CFGR4_PPSS;
        RCC->CFGR4 |= (uint32_t)0x0 << RCC_CFGR4_PPSS_Pos;

        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL));
        RCC->CFGR |= (uint32_t)((0x1 << RCC_CFGR_PLLSRC_Pos) | ((uint32_t)0x0 << RCC_CFGR_PLLXTPRE_Pos) | ((uint32_t)0x1 << RCC_CFGR_PLLMUL_Pos));

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= ~(RCC_CFGR_SW);
        RCC->CFGR |= (uint32_t)0x2 << RCC_CFGR_SW_Pos;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != ((uint32_t)0x2 << RCC_CFGR_SWS_Pos))
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}

#elif defined SYSCLK_HSE8M_PLL_FREQ_32MHz
/**
  * @brief  Sets System clock frequency to 32MHz and configure HCLK, PCLK2 and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo32_HSE8M_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= ((uint32_t)0x1) << FLASH_ACR_LATENCY_Pos;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

        /* PLL configuration: = HSE * pllmul4 = 32 MHz */
        RCC->CFGR2 &= ~(RCC_CFGR2_PREDIV);
        RCC->CFGR2 |= (uint32_t)0x0 << RCC_CFGR2_PREDIV_Pos;

        RCC->CFGR4 &= ~RCC_CFGR4_PPSS;
        RCC->CFGR4 |= (uint32_t)0x0 << RCC_CFGR4_PPSS_Pos;

        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL));
        RCC->CFGR |= (uint32_t)((0x1 << RCC_CFGR_PLLSRC_Pos) | ((uint32_t)0x0 << RCC_CFGR_PLLXTPRE_Pos) | ((uint32_t)0x2 << RCC_CFGR_PLLMUL_Pos));

        RCC->CFGR2 &= ~RCC_CFGR2_PREDIV;
        RCC->CFGR2 |= (uint32_t)0x0 << RCC_CFGR2_PREDIV_Pos;

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        RCC->CFGR4 &= ~RCC_CFGR4_ESSS;
        RCC->CFGR4 |= ((uint32_t)0x0) << RCC_CFGR4_ESSS_Pos;

        /* Select PLL as system clock source */
        RCC->CFGR &= ~(RCC_CFGR_SW);
        RCC->CFGR |= (uint32_t)0x2 << RCC_CFGR_SW_Pos;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != ((uint32_t)0x2 << RCC_CFGR_SWS_Pos))
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}


#elif defined SYSCLK_HSE8M_PLL_FREQ_36MHz
/**
  * @brief  Sets System clock frequency to 36MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo36_HSE8M_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration*/
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= ((uint32_t)0x1) << FLASH_ACR_LATENCY_Pos;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

        /* PLL configuration: = HSE / prediv2 * pllmul9 = 36 MHz */
        RCC->CFGR2 &= ~(RCC_CFGR2_PREDIV);
        RCC->CFGR2 |= (uint32_t)0x1 << RCC_CFGR2_PREDIV_Pos;

        RCC->CFGR4 &= ~RCC_CFGR4_PPSS;
        RCC->CFGR4 |= (uint32_t)0x0 << RCC_CFGR4_PPSS_Pos;

        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL));
        RCC->CFGR |= (uint32_t)((0x1 << RCC_CFGR_PLLSRC_Pos) | ((uint32_t)0x1 << RCC_CFGR_PLLXTPRE_Pos) | ((uint32_t)0x7 << RCC_CFGR_PLLMUL_Pos));

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        RCC->CFGR4 &= ~RCC_CFGR4_ESSS;
        RCC->CFGR4 |= ((uint32_t)0x0) << RCC_CFGR4_ESSS_Pos;

        /* Select PLL as system clock source */
        RCC->CFGR &= ~(RCC_CFGR_SW);
        RCC->CFGR |= (uint32_t)0x2 << RCC_CFGR_SW_Pos;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != ((uint32_t)0x2 << RCC_CFGR_SWS_Pos))
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}
#elif defined SYSCLK_HSE8M_PLL_FREQ_48MHz
/**
  * @brief  Sets System clock frequency to 48MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo48_HSE8M_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= ((uint32_t)0x2) << FLASH_ACR_LATENCY_Pos;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

        /* PLL configuration: = HSE  * pllmul6 = 48 MHz */
        RCC->CFGR2 &= ~(RCC_CFGR2_PREDIV);
        RCC->CFGR2 |= (uint32_t)0x0 << RCC_CFGR2_PREDIV_Pos;

        RCC->CFGR4 &= ~RCC_CFGR4_PPSS;
        RCC->CFGR4 |= (uint32_t)0x0 << RCC_CFGR4_PPSS_Pos;

        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL));
        RCC->CFGR |= (uint32_t)((0x1 << RCC_CFGR_PLLSRC_Pos) | ((uint32_t)0x0 << RCC_CFGR_PLLXTPRE_Pos) | ((uint32_t)0x4 << RCC_CFGR_PLLMUL_Pos));

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= ~(RCC_CFGR_SW);
        RCC->CFGR |= (uint32_t)0x2 << RCC_CFGR_SW_Pos;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != ((uint32_t)0x2 << RCC_CFGR_SWS_Pos))
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}


#elif defined SYSCLK_HSI_PLL_FREQ_36MHz

static void SetSysClockTo36_HSI_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSI */
    RCC->CR |= ((uint32_t)RCC_CR_HSION);

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)0x1 << FLASH_ACR_LATENCY_Pos;


        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;


        /*  PLL configuration: PLLCLK = HSI8M / prediv2 * pllmul9 = 36 MHz */
        RCC->CFGR2 &= ~(RCC_CFGR2_PREDIV);
        RCC->CFGR2 |= (uint32_t)0x1 << RCC_CFGR2_PREDIV_Pos;

        RCC->CFGR4 &= ~RCC_CFGR4_PPSS;
        RCC->CFGR4 |= (uint32_t)0x1 << RCC_CFGR4_PPSS_Pos;

        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL));
        RCC->CFGR |= (uint32_t)((0x1 << RCC_CFGR_PLLSRC_Pos) | ((uint32_t)0x1 << RCC_CFGR_PLLXTPRE_Pos) | ((uint32_t)0x7 << RCC_CFGR_PLLMUL_Pos));

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)0x2 << RCC_CFGR_SW_Pos;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != ((uint32_t)0x2 << RCC_CFGR_SWS_Pos))
        {
        }
    }
    else
    {

    }
}

#elif defined SYSCLK_HSI_PLL_FREQ_48MHz

static void SetSysClockTo48_HSI_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSI */
    RCC->CR |= ((uint32_t)RCC_CR_HSION);

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 1 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)0x2 << FLASH_ACR_LATENCY_Pos;


        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;


        /*  PLL configuration: PLLCLK = HSI8M * pllmul6 = 36 MHz */
        RCC->CFGR2 &= ~(RCC_CFGR2_PREDIV);
        RCC->CFGR2 |= (uint32_t)0x0 << RCC_CFGR2_PREDIV_Pos;

        RCC->CFGR4 &= ~RCC_CFGR4_PPSS;
        RCC->CFGR4 |= (uint32_t)0x1 << RCC_CFGR4_PPSS_Pos;

        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL));
        RCC->CFGR |= (uint32_t)((0x1 << RCC_CFGR_PLLSRC_Pos) | ((uint32_t)0x0 << RCC_CFGR_PLLXTPRE_Pos) | ((uint32_t)0x4 << RCC_CFGR_PLLMUL_Pos));

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)0x2 << RCC_CFGR_SW_Pos;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != ((uint32_t)0x2 << RCC_CFGR_SWS_Pos))
        {
        }
    }
    else
    {
    }
}

#elif defined SYSCLK_FREQ_EXTCLK
static void SetSysClockToEXTCLK(void)
{

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable EXCLK */
    //enable EXTIO PA4/PA13/PA14

    /* Configure PA4 as CLOCK input */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*CLOCK select */
    RCC->CFGR4 &= (uint32_t)((uint32_t)~(RCC_CFGR4_EXTCLK_SEL));
    RCC->CFGR4 |= (uint32_t)0x0 << RCC_CFGR4_EXTCLK_SEL_Pos;

    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);

    if (SYSCLK_FREQ_EXTCLK <= 24000000)
    {
        FLASH->ACR |= ((uint32_t)0x0) << FLASH_ACR_LATENCY_Pos;
    }
    else
    {
        if (SYSCLK_FREQ_EXTCLK <= 48000000)
        {
            FLASH->ACR |= ((uint32_t)1) << FLASH_ACR_LATENCY_Pos;
        }
    }

    /* HCLK = SYSCLK */
    RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

    /* PCLK = HCLK */
    RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

    /* Select EXTCLK as system clock source */
    RCC->CFGR4 |= RCC_CFGR4_ESSS;

    RCC->CFGR4 &= (uint32_t)((uint32_t)~(RCC_CFGR4_ESW));
    RCC->CFGR4 |= (uint32_t)0x4 << RCC_CFGR4_ESW_Pos;

    /* Wait till EXTCLK is used as system clock source */
    while ((RCC->CFGR4 & (uint32_t)RCC_CFGR4_ESWS) != ((uint32_t)0x4 << RCC_CFGR4_ESWS_Pos))
    {
    }
}


#elif defined SYSCLK_FREQ_HSI_48M
static void SetSysClockToHSI_48M(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSI */
    RCC->CR2 |= ((uint32_t)RCC_CR2_HSI48ON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR2 & RCC_CR2_HSI48RDY;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR2 & RCC_CR2_HSI48RDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {

        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 1 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= ((uint32_t)0x2) << FLASH_ACR_LATENCY_Pos;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

        /* Select HSI48 as system clock source */
        RCC->CFGR4 |= RCC_CFGR4_ESSS;

        RCC->CFGR4 &= ~(RCC_CFGR4_ESW);
        RCC->CFGR4 |= (uint32_t)0x2 << RCC_CFGR4_ESW_Pos;

        /* Wait till HSI is used as system clock source */
        while ((RCC->CFGR4 & (uint32_t)RCC_CFGR4_ESWS) != ((uint32_t)0x2 << RCC_CFGR4_ESWS_Pos))
        {
        }
    }
    else
    {
        /* If fails to start-up */
    }
}

#elif defined SYSCLK_FREQ_HSI_16M
static void SetSysClockToHSI_16M(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSI */
    RCC->CR2 |= ((uint32_t)RCC_CR2_HSI16ON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR2 & RCC_CR2_HSI16RDY;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR2 & RCC_CR2_HSI16RDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {

        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)0x0 << FLASH_ACR_LATENCY_Pos;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

        /* Select HSI16 as system clock source */
        RCC->CFGR4 |= RCC_CFGR4_ESSS;

        RCC->CFGR4 &= ~(RCC_CFGR4_ESW);
        RCC->CFGR4 |= (uint32_t)0x3 << RCC_CFGR4_ESW_Pos;

        /* Wait till HSI is used as system clock source */
        while ((RCC->CFGR4 & (uint32_t)RCC_CFGR4_ESWS) != ((uint32_t)0x3 << RCC_CFGR4_ESWS_Pos))
        {
        }
    }
    else
    {
        /* If fails to start-up */
    }
}

#elif defined SYSCLK_FREQ_HSI_8M
static void SetSysClockToHSI_8M(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSI */
    RCC->CR |= ((uint32_t)RCC_CR_HSION);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {

        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= ((uint32_t)0) << FLASH_ACR_LATENCY_Pos;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

        /* Select HSI as system clock source */
        RCC->CFGR4 &= ~RCC_CFGR4_ESSS;

        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_SW_Pos;

        /* Wait till HSI is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != ((uint32_t)0x0 << RCC_CFGR_SWS_Pos))
        {
        }
    }
    else
    {
        /* If fails to start-up */
    }
}

#elif defined SYSCLK_FREQ_LSI
/* Alias word address of LSION bit */
static void SetSysClockToLSI(void)
{
    __IO uint32_t StartUpCounter = 0, LSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable LSI */
    RCC->CSR |= RCC_CSR_LSION;

    /* Wait till LSI is ready and if Time out is reached exit */
    do
    {
        LSIStatus = RCC->CSR & RCC_CSR_LSIRDY;
        StartUpCounter++;
    } while ((LSIStatus == 0) && (StartUpCounter != 0xFFFF));

    if ((RCC->CSR & RCC_CSR_LSIRDY) != RESET)
    {
        LSIStatus = (uint32_t)0x01;
    }
    else
    {
        LSIStatus = (uint32_t)0x00;
    }

    if (LSIStatus == (uint32_t)0x01)
    {

        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= ((uint32_t)0) << FLASH_ACR_LATENCY_Pos;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

        /* Select LSI as system clock source */
        RCC->CFGR4 |= RCC_CFGR4_ESSS;

        RCC->CFGR4 &= ~(RCC_CFGR4_ESW);
        RCC->CFGR4 |= (uint32_t)0x1 << RCC_CFGR4_ESW_Pos;

        /* Wait till HSI is used as system clock source */
        while ((RCC->CFGR4 & (uint32_t)RCC_CFGR4_ESWS) != ((uint32_t)0x1 << RCC_CFGR4_ESWS_Pos))
        {
        }
    }
    else
    {
        /* If fails to start-up */
    }
}

#elif defined SYSCLK_FREQ_LSE
static void SetSysClockToLSE(void)
{
    __IO uint32_t StartUpCounter = 0, LSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable LSE */
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_PWR, ENABLE );
    PWR->CR |= PWR_CR_DBP;

    //RCC->BDCR |= RCC_LSE_Bypass | RCC_LSE_ON;
    RCC->BDCR |= RCC_LSE_ON;

    /* Wait till LSE is ready and if Time out is reached exit */
    do
    {
        LSEStatus = RCC->BDCR & RCC_BDCR_LSERDY;
        StartUpCounter++;
    } while ((LSEStatus == 0) && (StartUpCounter != 0xFFFFFF));

    if ((RCC->BDCR & RCC_BDCR_LSERDY) != RESET)
    {
        LSEStatus = (uint32_t)0x01;
    }
    else
    {
        LSEStatus = (uint32_t)0x00;
    }

    if (LSEStatus == (uint32_t)0x01)
    {

        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= ((uint32_t)0) << FLASH_ACR_LATENCY_Pos;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

        /* Select LSE as system clock source */
        RCC->CFGR4 |= RCC_CFGR4_ESSS;

        RCC->CFGR4 &= ~(RCC_CFGR4_ESW);
        RCC->CFGR4 |= (uint32_t)0x0 << RCC_CFGR4_ESW_Pos;

        /* Wait till LSE is used as system clock source */
        while ((RCC->CFGR4 & (uint32_t)RCC_CFGR4_ESWS) != ((uint32_t)0x0 << RCC_CFGR4_ESWS_Pos))
        {
        }

    }
    else
    {
        /* If fails to start-up */
    }
}


#elif defined SYSCLK_FREQ_MSI
static void SetSysClockToMSI(void)
{
    __IO uint32_t StartUpCounter = 0, MSIStatus = 0;

    RCC->CR2 &= ~RCC_CR2_MSIRANGE;

    switch (SYSCLK_FREQ_MSI)
    {
        case MSIRANGE_VALUE_262KHz:
            RCC->CR2 |= (uint32_t)0x2 << RCC_CR2_MSIRANGE_Pos;
            break;

        case MSIRANGE_VALUE_524KHz:
            RCC->CR2 |= (uint32_t)0x3 << RCC_CR2_MSIRANGE_Pos;
            break;

        case MSIRANGE_VALUE_1_05MHz:
            RCC->CR2 |= (uint32_t)0x4 << RCC_CR2_MSIRANGE_Pos;
            break;

        case MSIRANGE_VALUE_2_1MHz:
            RCC->CR2 |= (uint32_t)0x5 << RCC_CR2_MSIRANGE_Pos;
            break;

        case MSIRANGE_VALUE_4_2MHz:
            RCC->CR2 |= (uint32_t)0x6 << RCC_CR2_MSIRANGE_Pos;
            break;

        default:
            RCC->CR2 |= (uint32_t)0x5 << RCC_CR2_MSIRANGE_Pos;
            break;
    }

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable MSI */
    RCC->CSR |= RCC_CSR_MSION;

    /* Wait till MSI is ready and if Time out is reached exit */
    do
    {
        MSIStatus = RCC->CR2 & RCC_CR2_MSIRDY;
        StartUpCounter++;
    } while ((MSIStatus == 0) && (StartUpCounter != 0xFFFF));

    if ((RCC->CR2 & RCC_CR2_MSIRDY) != RESET)
    {
        MSIStatus = (uint32_t)0x01;
    }
    else
    {
        MSIStatus = (uint32_t)0x00;
    }

    if (MSIStatus == (uint32_t)0x01)
    {

        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= ((uint32_t)0) << FLASH_ACR_LATENCY_Pos;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;

        /* PCLK = HCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_PPRE_Pos;

        /* Select MSI as system clock source */
        RCC->CFGR4 |= RCC_CFGR4_ESSS;

        RCC->CFGR4 &= ~(RCC_CFGR4_ESW);
        RCC->CFGR4 |= (uint32_t)0x5 << RCC_CFGR4_ESW_Pos;

        /* Wait till MSI is used as system clock source */
        while ((RCC->CFGR4 & (uint32_t)RCC_CFGR4_ESWS) != ((uint32_t)0x5 << RCC_CFGR4_ESWS_Pos))
        {
        }

    }
    else
    {
        /* If fails to start-up */
    }
}


#endif

/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
