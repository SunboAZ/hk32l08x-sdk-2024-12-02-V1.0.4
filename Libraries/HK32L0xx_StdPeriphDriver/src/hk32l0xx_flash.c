/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_flash.c
* @brief:     This file provides all the FLASH firmware functions.
* @author:    AE Team
* @version:   V1.0.0/2024-01-09
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_flash.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup FLASH FLASH
  * @brief FLASH driver modules
  * @{
  *
  @verbatim
  ===============================================================================
                     ##### How to use this driver #####
  ===============================================================================
  [..] This driver provides functions to configure and program the Flash
       memory of all HK32L0xx devices. These functions are split in 4 groups
       (#) FLASH Interface configuration functions: this group includes the
           management of following features:
           (++) Set the latency
           (++) Enable/Disable the prefetch buffer

       (#) FLASH Memory Programming functions: this group includes all needed
           functions to erase and program the main memory:
           (++) Lock and Unlock the Flash interface.
           (++) Erase function: Erase Page, erase all pages.
           (++) Program functions: Half Word and Word write.

       (#) FLASH Option Bytes Programming functions: this group includes all
           needed functions to:
           (++) Lock and Unlock the Flash Option bytes.
           (++) Launch the Option Bytes loader
           (++) Erase the Option Bytes
           (++)Set/Reset the write protection
           (++) Set the Read protection Level
           (++) Program the user option Bytes
           (++) Set/Reset the BOOT1 bit
           (++) Enable/Disable the VDDA Analog Monitoring
           (++) Get the user option bytes
           (++) Get the Write protection
           (++) Get the read protection status

       (#) FLASH Interrupts and flag management functions: this group includes
           all needed functions to:
           (++) Enable/Disable the flash interrupt sources
           (++) Get flags status
           (++) Clear flags
           (++) Get Flash operation status
           (++) Wait for last flash operation
  @endverbatim
  *
  ******************************************************************************
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup FLASH_Private_Defines FLASH_Private_Defines
  * @{
  */
#define OB_USER_RDP_DEFAULT   ((uint32_t)0x807F55AA)
#define OB_USER_RDP_LEVEL1    ((uint32_t)0x807FFF00)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup FLASH_Private_Functions FLASH_Private_Functions
  * @{
  */

/** @defgroup FLASH_Group1 FLASH Interface configuration functions
  *  @brief   FLASH Interface configuration functions
  *
@verbatim
    ===============================================================================
                  ##### FLASH Interface configuration functions #####
    ===============================================================================
    [..] FLASH_Interface configuration_Functions, includes the following functions:
         (+) void FLASH_SetLatency(uint32_t FLASH_Latency):
    [..] To correctly read data from Flash memory, the number of wait states (LATENCY)
         must be correctly programmed according to the frequency of the CPU clock (HCLK)
    [..]
         +--------------------------------------------- +
         |  Wait states  |   HCLK clock frequency (MHz) |
         |---------------|------------------------------|
         |0WS(1CPU cycle)|       0 < HCLK <= 24         |
         |---------------|------------------------------|
         |1WS(2CPU cycle)|       24 < HCLK <= 48        |
         +----------------------------------------------+
    [..]
         (+) void FLASH_PrefetchBufferCmd(FunctionalState NewState);
    [..]
         All these functions don't need the unlock sequence.
@endverbatim
  * @{
  */

/**
  * @brief  Sets the code latency value.
  * @param  FLASH_Latency: specifies the FLASH Latency value.
  *         This parameter can be one of the following values:
  *            @arg FLASH_Latency_0:  HCKL<=24MHz
  *            @arg FLASH_Latency_1:  24Mhz<HCKL<=48MHz
  *            @arg FLASH_Latency_2:  48Mhz<HCKL<=72MHz
  *            @arg FLASH_Latency_3:  FLASH three Latency cycle
  *            @arg FLASH_Latency_7:  FLASH seven Latency cycle
  *            @arg FLASH_Latency_9:  FLASH nine Latency cycle
  *            @arg FLASH_Latency_19: FLASH 19 Latency cycle
  *            @arg FLASH_Latency_39: FLASH 39 Latency cycle
  * @retval None
  */
void FLASH_SetLatency(uint32_t FLASH_Latency)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_FLASH_LATENCY(FLASH_Latency));

    /* Read the ACR register */
    tmpreg = FLASH->ACR;

    /* Sets the Latency value */
    tmpreg &= (uint32_t) (~((uint32_t)FLASH_ACR_LATENCY));
    tmpreg |= FLASH_Latency;

    /* Write the ACR register */
    FLASH->ACR = tmpreg;
}

/**
  * @brief  Enables or disables the Prefetch Buffer.
  * @param  NewState: new state of the FLASH prefetch buffer.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FLASH_PrefetchBufferCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        FLASH->ACR |= FLASH_ACR_PRFTBE;
    }
    else
    {
        FLASH->ACR &= (uint32_t)(~((uint32_t)FLASH_ACR_PRFTBE));
    }
}

/**
  * @brief  Checks whether the FLASH Prefetch Buffer status is set or not.
  * @retval FLASH Prefetch Buffer Status (SET or RESET).
  */
FlagStatus FLASH_GetPrefetchBufferStatus(void)
{
    FlagStatus bitstatus = RESET;

    if ((FLASH->ACR & FLASH_ACR_PRFTBS) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the new state of FLASH Prefetch Buffer Status (SET or RESET) */
    return bitstatus;
}

/**
  * @}
  */

/** @defgroup FLASH_Group2 FLASH Memory Programming functions
 *  @brief    FLASH Memory Programming functions
 *
@verbatim
    ===============================================================================
                    ##### FLASH Memory Programming functions #####
    ===============================================================================
    [..] The FLASH Memory Programming functions, includes the following functions:
       (+) void FLASH_Unlock(void);
       (+) void FLASH_Lock(void);
       (+) FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
       (+) FLASH_Status FLASH_EraseAllPages(void);
       (+) FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
    [..] Any operation of erase or program should follow these steps:
       (#) Call the FLASH_Unlock() function to enable the flash control register and
           program memory access
       (#) Call the desired function to erase page or program data
       (#) Call the FLASH_Lock() to disable the flash program memory access
      (recommended to protect the FLASH memory against possible unwanted operation)
@endverbatim
  * @{
  */

/**
  * @brief  Unlocks the FLASH control register and program memory access.
  * @retval None
  */
void FLASH_Unlock(void)
{
    if ((FLASH->CR & FLASH_CR_LOCK) != RESET)
    {
        /* Unlocking the program memory access */
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
    }
}

/**
  * @brief  Locks the Program memory access.
  * @retval None
  */
void FLASH_Lock(void)
{
    /* Set the LOCK Bit to lock the FLASH control register and program memory access */
    FLASH->CR |= FLASH_CR_LOCK;
}

/**
  * @brief  Erases a specified page in program memory.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  Page_Address: The page address in program memory to be erased.
  * @note   A Page is erased in the Program memory only if the address to load
  *         is the start address of a page.
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ErasePage(uint32_t Page_Address)
{
    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_FLASH_PROGRAM_ADDRESS(Page_Address));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
        /* If the previous operation is completed, proceed to erase the page */
        FLASH->CR |= FLASH_CR_PER;
        FLASH->AR  = Page_Address;
        FLASH->CR |= FLASH_CR_STRT;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        /* Disable the PER Bit */
        FLASH->CR &= ~FLASH_CR_PER;
    }

    /* Return the Erase Status */
    return status;
}

/**
  * @brief  Erases a specified half page in program memory.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  Page_Address: The page address in program memory to be erased.
  * @note   A Half Page is erased in the Program memory only if the address to load
  *         is the start address of a half page.
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_HalfErasePage(uint32_t Page_Address)
{
    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_FLASH_PROGRAM_ADDRESS(Page_Address));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
        /* If the previous operation is completed, proceed to erase the page */
        FLASH->ECR |= FLASH_ECR_HPER;
        FLASH->AR  = Page_Address;
        FLASH->CR |= FLASH_CR_STRT;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        /* Disable the HPER Bit */
        FLASH->ECR &= ~FLASH_ECR_HPER;
    }

    /* Return the Erase Status */
    return status;
}

/**
  * @brief  Erases all FLASH pages.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseAllPages(void)
{
    FLASH_Status status = FLASH_COMPLETE;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
        /* if the previous operation is completed, proceed to erase all pages */
        FLASH->CR |= FLASH_CR_MER;
        FLASH->CR |= FLASH_CR_STRT;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        /* Disable the MER Bit */
        FLASH->CR &= ~FLASH_CR_MER;
    }

    /* Return the Erase Status */
    return status;
}

/**
  * @brief  Programs a word at a specified address.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
    FLASH_Status status = FLASH_COMPLETE;
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
        /* If the previous operation is completed, proceed to program the new first
        half word */
        FLASH->CR |= FLASH_CR_WPG;

        *(__IO uint32_t*)Address = (uint32_t)Data;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        /* Disable the PG Bit */
        FLASH->CR &= ~FLASH_CR_WPG;
    }

    /* Return the Program Status */
    return status;
}

/**
  * @}
  */

/** @defgroup FLASH_Group3 Option Bytes Programming functions
 *  @brief    Option Bytes Programming functions
 *
@verbatim
    ===============================================================================
                    ##### Option Bytes Programming functions #####
    ===============================================================================
    [..] The FLASH_Option Bytes Programming_functions, includes the following functions:
       (+) void FLASH_OptionByteUnlock(void);
       (+) void FLASH_OptionByteLock(void);
       (+) void FLASH_OptionByteLaunch(void);
       (+) FLASH_Status FLASH_OptionByteErase(void);
       (+) FLASH_Status FLASH_OptionByteEnableWRP(uint32_t OB_WRP);
       (+) FLASH_Status FLASH_OptionByteConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY, uint8_t OB_RDP, uint8_t OB_BOOT_SEL, uint8_t OB_BOOT01_BIT)
       (+) FLASH_OptionByteProgramData(uint32_t Address, uint8_t Data);
       (+) uint8_t FLASH_OptionByteGetUser(void);
       (+) uint32_t FLASH_OptionByteGetWRP(void);
       (+) FlagStatus FLASH_OptionByteGetRDP(void);
    [..] Any operation of erase or program should follow these steps:
       (#) Call the FLASH_OptionByteUnlock() function to enable the Option Bytes registers access
       (#) Once all needed option bytes to be programmed are correctly written, call the
           FLASH_OptionByteLaunch(void) function to launch the Option Bytes programming process.
       (#) Call the FLASH_OptionByteLock() to disable the Option Bytes registers access (recommended
           to protect the option Bytes against possible unwanted operations)
@endverbatim
  * @{
  */

/**
  * @brief  Unlocks the option bytes block access.
  * @retval None
  */
void FLASH_OptionByteUnlock(void)
{
    if ((FLASH->CR & FLASH_CR_OPTWRE) == RESET)
    {
        /* Unlocking the option bytes block access */
        FLASH->OPTKEYR = FLASH_OPTKEY1;
        FLASH->OPTKEYR = FLASH_OPTKEY2;
    }
}

/**
  * @brief  Locks the option bytes block access.
  * @retval None
  */
void FLASH_OptionByteLock(void)
{
    /* Set the OPTWREN Bit to lock the option bytes block access */
    FLASH->CR &= ~FLASH_CR_OPTWRE;

}

/**
  * @brief  Launch the option byte loading.
  * @retval None
  */
void FLASH_OptionByteLaunch(void)
{
    /* Set the OBL_Launch bit to launch the option byte loading */
    FLASH->CR |= FLASH_CR_OBL_LAUNCH;
}

/**
  * @brief  Erases the FLASH option bytes.
  * @note   To correctly run this function, the FLASH_OptionByteUnlock() function must be called before.
  * @note   Call the FLASH_OptionByteLock() to disable the flash control register access and the option
  *         bytes
  * @note   This functions erases all option bytes
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OptionByteErase(void)
{
    uint32_t rdptmp = OB_USER_RDP_DEFAULT;

    FLASH_Status status = FLASH_COMPLETE;

    /* Get the actual read protection Option Byte value */
    if (FLASH_OptionByteGetRDP() != RESET)
    {
        rdptmp = OB_USER_RDP_LEVEL1;
    }

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
        /* If the previous operation is completed, proceed to erase the option bytes */
        FLASH->CR |= FLASH_CR_OPTER;
        FLASH->AR = 0x1FFFF800;
        FLASH->CR |= FLASH_CR_STRT;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        if (status == FLASH_COMPLETE)
        {
            /* If the erase operation is completed, disable the OPTER Bit */
            FLASH->CR &= ~FLASH_CR_OPTER;

            /* Enable the Option Bytes Programming operation */
            FLASH->CR |= FLASH_CR_OPTPG;

            /* Restore the last read protection Option Byte value */
            OB->USERRDP = (uint32_t)rdptmp;

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

            if (status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CR &= ~FLASH_CR_OPTPG;
            }
        }
        else
        {
            if (status != FLASH_TIMEOUT)
            {
                /* Disable the OPTPG Bit */
                FLASH->CR &= ~FLASH_CR_OPTPG;
            }
        }
    }

    /* Return the erase status */
    return status;
}

/**
  * @brief  Write protects the desired pages
  * @note   To correctly run this function, the FLASH_OptionByteUnlock() function must be called before.
  * @note   Call the FLASH_OptionByteLock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  OB_WRP: specifies the address of the pages to be write protected.
  *         This parameter can be:
  *            @arg OB_WRP_Pages0to3..OB_WRP_Pages124to127
  *            @arg OB_WRP_AllPages
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OptionByteEnableWRP(uint32_t OB_WRP)
{
    uint32_t WRP01_Data = 0xFFFFFFFF, WRP23_Data = 0xFFFFFFFF;

    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_OB_WRP(OB_WRP));

    OB_WRP = (uint32_t)(~OB_WRP);
    WRP01_Data = (uint32_t)((OB_WRP & OB_WRP0_WRP0) | (((OB_WRP >> 8) & OB_WRP0_WRP0) << 16));
    WRP23_Data = (uint32_t)(((OB_WRP >> 16) & OB_WRP0_WRP0) | (((OB_WRP >> 24) & OB_WRP0_WRP0) << 16));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
        FLASH->CR |= FLASH_CR_OPTPG;

        if (WRP01_Data != 0xFF00FF)
        {
            OB->WRP01 = WRP01_Data;

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
        }

        if ((status == FLASH_COMPLETE) && (WRP23_Data != 0xFF00FF))
        {
            OB->WRP23 = WRP23_Data;

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
        }

        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= ~FLASH_CR_OPTPG;
        }
    }

    /* Return the write protection operation Status */
    return status;
}

/**
  * @brief  Programs the FLASH User Option Byte and RDP.
  * @note   To correctly run this function, the FLASH_OptionByteUnlock() function must be called before.
  * @note   Call the FLASH_OptionByteLock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  OB_IWDG: Selects the WDG mode
  *            @arg OB_IWDG_SW: Software WDG selected
  *            @arg OB_IWDG_HW: Hardware WDG selected
  * @param  OB_STOP: Reset event when entering STOP mode.
  *            @arg OB_STOP_NoRST: No reset generated when entering in STOP
  *            @arg OB_STOP_RST: Reset generated when entering in STOP
  * @param  OB_STDBY: Reset event when entering Standby mode.
  *            @arg OB_STDBY_NoRST: No reset generated when entering in STANDBY
  *            @arg OB_STDBY_RST: Reset generated when entering in STANDBY
  * @param  OB_RDP: FLASH_ReadProtection_Level: specifies the read protection level.
  *            @arg OB_RDP_Level_0: No protection
  *            @arg OB_RDP_Level_1: Read protection of the memory
  *            @arg OB_RDP_Level_2: Chip protection
  * @param  OB_BOOT_SEL:
  *            @arg OB_BOOT0_SW:
  *            @arg OB_BOOT0_HW:
  * @param  OB_BOOT01_BIT:
  *            @arg OB_BOOT0_SET|OB_BOOT1_RESET  :ram boot
  *            @arg OB_BOOT0_SET|OB_BOOT1_SET    :system memory boot
  *            @arg OB_BOOT0_RESET|OB_BOOT1_RESET:main Flash boot
  *            @arg OB_BOOT0_RESET|OB_BOOT1_SET  :main Flash boot
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OptionByteConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY, uint8_t OB_RDP, uint8_t OB_BOOT_SEL, uint8_t OB_BOOT01_BIT)
{
    FLASH_Status status = FLASH_COMPLETE;
    uint32_t udata = (uint32_t)((((uint32_t)(OB_IWDG | OB_STOP | OB_STDBY | OB_BOOT_SEL | OB_BOOT01_BIT | 0x60)) << 16)
                                | OB_RDP);
    /* Check the parameters */
    assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
    assert_param(IS_OB_STOP_SOURCE(OB_STOP));
    assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));
    assert_param(IS_OB_RDP(OB_RDP));
    assert_param(IS_OB_BOOT0SW(OB_BOOT_SEL));
    assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CR |= FLASH_CR_OPTPG;

        *(__IO uint32_t*)0x1ffff800 = udata;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        if (status != FLASH_TIMEOUT)
        {
            /* If the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= ~FLASH_CR_OPTPG;
        }
    }

    /* Return the Option Byte program Status */
    return status;
}

/**
  * @brief  Programs a word(32bit) at a specified Option Byte Data address.
  * @note   To correctly run this function, the FLASH_OptionByteUnlock() function must be called before.
  * @note   Call the FLASH_OptionByteLock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OptionByteProgramData(uint32_t Address, uint32_t Data)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_OB_DATA_ADDRESS(Address));
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
        /* Enables the Option Bytes Programming operation */
        FLASH->CR |= FLASH_CR_OPTPG;
        *(__IO uint32_t*)Address = Data;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        if (status != FLASH_TIMEOUT)
        {
            /* If the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= ~FLASH_CR_OPTPG;
        }
    }

    /* Return the Option Byte Data Program Status */
    return status;
}

/**
  * @brief  Returns the FLASH User Option Bytes values.
  * @retval The FLASH User Option Bytes .
  */
uint8_t FLASH_OptionByteGetUser(void)
{
    /* Return the User Option Byte */
    return (uint8_t)(FLASH->OBR >> 8);
}

/**
  * @brief  Returns the FLASH Write Protection Option Bytes value.
  * @retval The FLASH Write Protection Option Bytes value
  */
uint32_t FLASH_OptionByteGetWRP(void)
{
    /* Return the FLASH write protection Register value */
    return (uint32_t)(FLASH->WRPR);
}

/**
  * @brief  Checks whether the FLASH Read out Protection Status is set or not.
  * @retval FLASH ReadOut Protection Status(SET or RESET)
  */
FlagStatus FLASH_OptionByteGetRDP(void)
{
    FlagStatus readstatus = RESET;

    if ((uint8_t)(FLASH->OBR & (FLASH_OBR_RDPRT_0 | FLASH_OBR_RDPRT_1)) != RESET)
    {
        readstatus = SET;
    }
    else
    {
        readstatus = RESET;
    }

    return readstatus;
}

/**
  * @}
  */

/** @defgroup FLASH_Group4 Interrupts and flags management functions
 *  @brief    Interrupts and flags management functions
 *
@verbatim
 ===============================================================================
             ##### Interrupts and flags management functions #####
 ===============================================================================
        (#) Enables or disables the specified FLASH interrupts.
        (#) Checks whether the specified FLASH flag is set or not.
        (#) Clears the FLASH's pending flags.
        (#) Returns the FLASH Status.
        (#) Waits for a FLASH operation to complete or a TIMEOUT to occur.
        (#) ECC auto config.
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified FLASH interrupts.
  * @param  FLASH_IT: specifies the FLASH interrupt sources to be enabled or
  *         disabled.
  *         This parameter can be any combination of the following values:
  *            @arg FLASH_IT_EOP: FLASH end of programming Interrupt
  *            @arg FLASH_IT_ERR: FLASH Error Interrupt
  *            @arg FLASH_IT_ECC1BIT_ERR: FLASH EEC1BIT Error Interrupt
  *            @arg FLASH_IT_ECC2BIT_ERR: FLASH EEC2BIT Error Interrupt
  * @param  NewState: new state of the ECC config.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FLASH_IT(FLASH_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the interrupt sources */
        FLASH->CR |= FLASH_IT;
    }
    else
    {
        /* Disable the interrupt sources */
        FLASH->CR &= ~(uint32_t)FLASH_IT;
    }
}

/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @param  FLASH_FLAG: specifies the FLASH flag to check.
  *         This parameter can be one of the following values:
  *            @arg FLASH_FLAG_BSY: FLASH write/erase operations in progress flag
  *            @arg FLASH_FLAG_PGERR: FLASH Programming error flag flag
  *            @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
  *            @arg FLASH_FLAG_EOP: FLASH End of Programming flag
  *            @arg FLASH_FLAG_SIZE_ERR: FLASH size err of Programming flag
  *            @arg FLASH_FLAG_ECC1BIT_ERR: FLASH ECC1BIT err of Programming flag
  *            @arg FLASH_FLAG_ECC2BIT_ERR: FLASH ECC2BIT err of Programming flag
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG));

    if ((FLASH->SR & FLASH_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the new state of FLASH_FLAG (SET or RESET) */
    return bitstatus;
}

/**
  * @brief  Clears the FLASH's pending flags.
  * @param  FLASH_FLAG: specifies the FLASH flags to clear.
  *         This parameter can be any combination of the following values:
  *            @arg FLASH_FLAG_PGERR: FLASH Programming error flag flag
  *            @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
  *            @arg FLASH_FLAG_EOP: FLASH End of Programming flag
  *            @arg FLASH_FLAG_SIZE_ERR: FLASH size err of Programming flag
  *            @arg FLASH_FLAG_ECC1BIT_ERR: FLASH ECC1BIT err of Programming flag
  *            @arg FLASH_FLAG_ECC2BIT_ERR: FLASH ECC2BIT err of Programming flag
  * @retval None
  */
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
    /* Check the parameters */
    assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG));

    /* unlock the flash to reset the falsh_cr_lock */
    if ((FLASH->CR & FLASH_CR_LOCK)  != RESET)
    {
        /* Unlocking the program memory access */
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;

        /* Clear the flags */
        FLASH->SR = FLASH_FLAG;
        /* set the FLASH_CR_LOCK bit */
        FLASH->CR |= FLASH_CR_LOCK;
    }
    else
    {
        /* Clear the flags */
        FLASH->SR = FLASH_FLAG;
    }

}

/**
  * @brief  Returns the FLASH Status.
  * @retval FLASH Status: The returned value can be:
  *         FLASH_BUSY, FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP or FLASH_COMPLETE.
  */
FLASH_Status FLASH_GetStatus(void)
{
    FLASH_Status FLASHstatus = FLASH_COMPLETE;

    if ((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY)
    {
        FLASHstatus = FLASH_BUSY;
    }
    else
    {
        if ((FLASH->SR & (uint32_t)FLASH_FLAG_WRPERR) != (uint32_t)0x00)
        {
            FLASHstatus = FLASH_ERROR_WRP;
        }
        else
        {
            if (((FLASH->SR & (uint32_t)(FLASH_SR_PGERR)) != (uint32_t)0x00)
                    || ((FLASH->SR & (uint32_t)(FLASH_SR_SIZEERR)) != (uint32_t)0x00))
            {
                FLASHstatus = FLASH_ERROR_PROGRAM;
            }
            else
            {
                FLASHstatus = FLASH_COMPLETE;
            }
        }
    }

    /* Return the FLASH Status */
    return FLASHstatus;
}


/**
  * @brief  Waits for a FLASH operation to complete or a TIMEOUT to occur.
  * @param  Timeout: FLASH programming Timeout
  * @retval FLASH Status: The returned value can be: FLASH_BUSY,
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout)
{
    FLASH_Status status = FLASH_COMPLETE;

    /* Check for the FLASH Status */
    status = FLASH_GetStatus();

    /* Wait for a FLASH operation to complete or a TIMEOUT to occur */
    while ((status == FLASH_BUSY) && (Timeout != 0x00))
    {
        status = FLASH_GetStatus();
        Timeout--;
    }

    if (Timeout == 0x00 )
    {
        status = FLASH_TIMEOUT;
    }

    /* Return the operation status */
    return status;
}

/**
  * @brief  ECC auto config.
  * @param  NewState: new state of the ECC config.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FLASH_EccConfig(FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        FLASH->CR |= FLASH_CR_ECC_AUTO_CORRECT;
    }
    else
    {
        FLASH->CR &= (uint32_t)~FLASH_CR_ECC_AUTO_CORRECT;
    }
}

/**
  * @brief  Return the unique device identifier (UID based on 96 bits)
  * @param  UID: pointer to 3 words array.
  * @retval void
  */
void Sys_GetDevice96BitUID(uint32_t *UID)
{
    UID[0] = *((uint32_t *)UID_BASE);
    UID[1] = *((uint32_t *)(UID_BASE + 4U));
    UID[2] = *((uint32_t *)(UID_BASE + 8U));
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
