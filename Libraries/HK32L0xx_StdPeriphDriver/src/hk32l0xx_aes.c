/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_aes.c
* @brief:     This file provides firmware functions to manage the following
*             functionalities of the AES peripheral:
*             + Configuration
*             + Read/Write operations
*             + DMA transfers management
*             + Interrupts and flags management
* @author:    AE Team
* @version:   V1.0.0/2024-01-15
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_aes.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup AES AES
  * @brief AES driver modules
  * @{
    @verbatim
 ===============================================================================
                        ##### AES Peripheral features #####
 ===============================================================================
....[..]
   (#) The Advanced Encryption Standard hardware accelerator (AES) can be used
       to both encipher and decipher data using AES algorithm.
   (#) The AES supports 4 operation modes:
       (++) Encryption: It consumes 214 clock cycle when processing one 128-bit block
       (++) Decryption: It consumes 214 clock cycle when processing one 128-bit block
       (++) Key derivation for decryption: It consumes 80 clock cycle when processing one 128-bit block
       (++) Key Derivation and decryption: It consumes 288 clock cycle when processing one 128-bit blobk
  (#) The AES peripheral supports write/read error handling with interrupt capability.
  (#) Automatic data flow control with support of direct memory access (DMA) using
      2 channels, one for incoming data, and one for outcoming data.

                      ##### How to use this driver #####
 ===============================================================================
    [..]
        (#) AES AHB clock must be enabled to get write access to AES registers
            using RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRYPT, ENABLE).
        (#) Initialize the key using AES_KeyInit().
        (#) Configure the AES operation mode using AES_Init().
        (#) If required, enable interrupt source using AES_ITConfig() and
            enable the AES interrupt vector using NVIC_Init().
        (#) If required, when using the DMA mode.
            (##) Configure the DMA using DMA_Init().
            (##) Enable DMA requests using AES_DMAConfig().
        (#) Enable the AES peripheral using AES_Cmd().
    @endverbatim
  *
  ******************************************************************************
*/

/** @defgroup AES_Private_Defines AES_Private_Defines
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/*AES_Private_Defines*/
#define AES_TIMEOUT_VALUE           ((uint32_t) 0x00010000)
#define CR_MODE_CLEAR_MASK          ((uint32_t)0xFFFFFF81)
#define CR2_KEYSIZE_CLEAR_MASK      ((uint32_t)0xFFFFFFFC)
#define IS_BIT_CLR(REG,BIT)         (((REG) & (BIT)) == RESET)
/**
  * @}
  */

/** @defgroup AES_Private_Variables AES_Private_Variables
  * @{
  */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* AES_Private_Variables */
AES_PAR sAesPar = { 0 };

/*PendingTimeout :Pending  in interrupt mode,The aes operation will be suspended when a higher priority interrupt occurs in aes operations,so we need a timeout counter*/
uint32_t PendingTimeout = 0xFFFFFFFE;
/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup AES_Private_Functions AES_Private_Functions
  * @{
  */

/** @defgroup AES_Group1 Initialization and configuration
 *  @brief   Initialization and configuration.
 *
@verbatim
 ===============================================================================
                ##### Initialization and configuration #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes AES peripheral registers to their default reset values.
  * @retval None
  */
void AES_DeInit(void)
{
    /* Enable AES reset state */
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_CRYPT, ENABLE);
    /* Release AES from reset state */
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_CRYPT, DISABLE);
}

/**
  * @brief  Initializes the AES peripheral according to the specified parameters
  *         in the AES_InitStruct:
  *         - AES_Operation: specifies the operation mode (encryption, decryption).
  * @note   If AES is already enabled, use AES_Cmd(DISABLE) before setting the new
  *         configuration (When AES is enabled, setting configuration is forbidden).
  * @param  AES_InitStruct: pointer to an AES_InitTypeDef structure that contains
  *         the configuration information for AES peripheral.
  * @retval None
  */
void AES_Init(AES_InitTypeDef* AES_InitStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_AES_MODE(AES_InitStruct->AES_Operation));


    /* Get AES CR register value */
    tmpreg = AES->CR1;

    /* Clear  MODE[1:0] bits */
    tmpreg &= (uint32_t)CR_MODE_CLEAR_MASK;

    tmpreg |= AES_InitStruct->AES_Operation;

    AES->CR1 = (uint32_t) tmpreg;


}

/**
  * @brief  Initializes the AES Keys according to the specified parameters in the AES_KeyInitStruct.
  * @param  AES_KeyInitStruct: pointer to an AES_KeyInitTypeDef structure that
  *         contains the configuration information for the specified AES Keys.
  * @param  Key: string of key
  * @note   This function must be called while the AES is disabled.
  * @note   In encryption, key derivation and key derivation + decryption modes,
  *         AES_KeyInitStruct must contain the encryption key.
  *         In decryption mode, AES_KeyInitStruct must contain the decryption key.
  * @retval None
  */
void AES_KeyInit(AES_KeyInitTypeDef* AES_KeyInitStruct, uint8_t *Key)
{
    uint32_t tmpreg = 0;
    uint32_t keyaddr = (uint32_t)Key;

    assert_param(IS_AES_KEYSIZE(AES_KeyInitStruct->AES_KeySize));

    /* Get AES CR2 register value */
    tmpreg = AES->CR2;

    /* Clear  keysize[1:0] bits */
    tmpreg &= (uint32_t)CR2_KEYSIZE_CLEAR_MASK;

    tmpreg |= AES_KeyInitStruct->AES_KeySize;

    AES->CR2 = (uint32_t) tmpreg;

    if (AES_KeyInitStruct->AES_KeySize == AES_KEYSIZE_128B)
    {
        AES->KEYR3 = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        AES->KEYR2 = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        AES->KEYR1 = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        AES->KEYR0 = __REV(*(uint32_t*)(keyaddr));

    }
    else if (AES_KeyInitStruct->AES_KeySize == AES_KEYSIZE_192B)
    {
        AES->KEYR5 = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        AES->KEYR4 = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        AES->KEYR3 = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        AES->KEYR2 = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        AES->KEYR1 = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        AES->KEYR0 = __REV(*(uint32_t*)(keyaddr));
    }
    else
    {
        AES->KEYR7 = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        AES->KEYR6 = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        AES->KEYR5 = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        AES->KEYR4 = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        AES->KEYR3 = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        AES->KEYR2 = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        AES->KEYR1 = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        AES->KEYR0 = __REV(*(uint32_t*)(keyaddr));
    }
}




/**
  * @brief  Enable or disable the AES peripheral.
  * @param  NewState: new state of the AES peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   The key must be written while AES is disabled.
  * @retval None
  */
void AES_Cmd(FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the AES peripheral */
        AES->CR1 |= (uint32_t) AES_CR1_EN;   /**< AES Enable */
    }
    else
    {
        /* Disable the AES peripheral */
        AES->CR1 &= (uint32_t)(~AES_CR1_EN);  /**< AES Disable */
    }
}


/**
  * @brief  Random number of TRNG output to randomize the AES clock.
  * @param  NewState:  new state of the AES Random fuction.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void AES_ClkRandom(FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable randomize the AES clock */
        AES->CR2 |= (uint32_t) AES_CR2_RANDOM_CLK_EN;
    }
    else
    {
        /* Disable randomize the AES clock  */
        AES->CR2 &= (uint32_t)(~AES_CR2_RANDOM_CLK_EN);
    }
}



/**
  * @brief  Write data in DINR register to be processed by AES peripheral.
  * @note   To process 128-bit data (4 * 32-bit), this function must be called
  *         four times to write the 128-bit data in the 32-bit register DINR.
  * @note   When an unexpected write to DOUTR register is detected, WRERR flag is
  *         set.
  * @param  Data: The data to be processed.
  * @retval None
  */
void AES_WriteSubData(uint32_t Data)
{
    /* Write Data */
    AES->DINR = Data;
}

/**
  * @brief  Returns the data in DOUTR register processed by AES peripheral.
  * @note   This function must be called four times to get the 128-bit data.
  * @note   When an unexpected read of DINR register is detected, RDERR flag is
  *         set.
  * @retval The processed data.
  */
uint32_t AES_ReadSubData(void)
{
    /* Read Data */
    return AES->DOUTR;
}
/**
  * @}
  */

/** @defgroup AES_Group2 DMA transfers management functions
 *  @brief   DMA transfers management function.
 *
@verbatim
 ===============================================================================
               ##### DMA transfers management functions #####
 ===============================================================================

@endverbatim
  * @{
  */
/**
  * @brief  Configures the AES DMA interface.
  * @param  AES_DMATransfer: Specifies the AES DMA transfer.
  *         This parameter can be one of the following values:
  *            @arg AES_DMATransfer_In: When selected, DMA manages the data input phase.
  *            @arg AES_DMATransfer_Out: When selected, DMA manages the data output phase.
  *            @arg AES_DMATransfer_InOut: When selected, DMA manages both the data input/output phases.
  * @param  NewState Indicates the new state of the AES DMA interface.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   The DMA has no action in key derivation mode.
  * @retval None
  */
void AES_DMAConfig(uint32_t AES_DMATransfer, FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_AES_DMA_TRANSFER(AES_DMATransfer));

    if (NewState != DISABLE)
    {
        /* Enable the DMA transfer */
        AES->CR1 |= (uint32_t) AES_DMATransfer;
    }
    else
    {
        /* Disable the DMA transfer */
        AES->CR1 &= (uint32_t)(~AES_DMATransfer);
    }
}

/**
  * @}
  */

/** @defgroup AES_Group3 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions.
 *
@verbatim

 ===============================================================================
           ##### Interrupts and flags management functions #####
 ===============================================================================
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified AES interrupt.
  * @param  AES_IT: Specifies the AES interrupt source to enable/disable.
  *         This parameter can be any combinations of the following values:
  *            @arg AES_IT_CC: Computation Complete Interrupt. If enabled, once CCF
  *                 flag is set an interrupt is generated.
  *            @arg AES_IT_ERR: Error Interrupt. If enabled, once a read error
  *                 flags (RDERR) or write error flag (WRERR) is set,
  *                 an interrupt is generated.
  * @param  NewState: The new state of the AES interrupt source.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void AES_ITConfig(uint32_t AES_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_AES_IT(AES_IT));

    if (NewState != DISABLE)
    {
        AES->CR1 |= (uint32_t) AES_IT;    /**< AES_IT Enable */
    }
    else
    {
        AES->CR1 &= (uint32_t)(~AES_IT);  /**< AES_IT Disable */
    }
}

/**
  * @brief  Checks whether the specified AES flag is set or not.
  * @param  AES_FLAG specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg AES_FLAG_CCF: Computation Complete Flag is set by hardware when
  *                 he computation phase is completed.
  *            @arg AES_FLAG_RDERR: Read Error Flag is set when an unexpected read
  *                 operation of DOUTR register is detected.
  *            @arg AES_FLAG_WRERR: Write Error Flag  is set when an unexpected write
  *                 operation in DINR is detected.
  * @retval FlagStatus (SET or RESET)
  */
FlagStatus AES_GetFlagStatus(uint32_t AES_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check parameters */
    assert_param(IS_AES_FLAG(AES_FLAG));

    if ((AES->SR1 & AES_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the AES_FLAG status */
    return  bitstatus;
}

/**
  * @brief  Clears the AES flags.
  * @param  AES_FLAG: specifies the flag to clear.
  *         This parameter can be:
  *            @arg AES_FLAG_CCF: Computation Complete Flag is cleared by setting CCFC
  *                 bit in CR register.
  *            @arg AES_FLAG_RDERR: Read Error is cleared by setting ERRC bit in
  *                 CR register.
  *            @arg AES_FLAG_WRERR: Write Error is cleared by setting ERRC bit in
  *                 CR register.
  * @retval None
  */
void AES_ClearFlag(uint32_t AES_FLAG)
{
    /* Check the parameters */
    assert_param(IS_AES_FLAG(AES_FLAG));

    /* Check if AES_FLAG is AES_FLAG_CCF */
    if (AES_FLAG == AES_FLAG_CCF)
    {
        /* Clear CCF flag by setting CCFC bit */
        AES->CR1 |= (uint32_t) AES_CR1_CCFC;
    }
    else /* AES_FLAG is AES_FLAG_RDERR or AES_FLAG_WRERR */
    {
        /* Clear RDERR and WRERR flags by setting ERRC bit */
        AES->CR1 |= (uint32_t) AES_CR1_ERRC;
    }
}

/**
  * @brief  Checks whether the specified AES interrupt has occurred or not.
  * @param  AES_IT: Specifies the AES interrupt pending bit to check.
  *         This parameter can be:
  *            @arg AES_IT_CC: Computation Complete Interrupt.
  *            @arg AES_IT_ERR: Error Interrupt.
  * @retval ITStatus The new state of AES_IT (SET or RESET).
  */
ITStatus AES_GetITStatus(uint32_t AES_IT)
{
    ITStatus itstatus = RESET;
    uint32_t cciebitstatus = RESET, ccfbitstatus = RESET;

    /* Check parameters */
    assert_param(IS_AES_GET_IT(AES_IT));

    cciebitstatus = AES->CR1 & AES_CR1_CCFIE;
    ccfbitstatus =  AES->SR1 & AES_SR1_CCF;

    /* Check if AES_IT is AES_IT_CC */
    if (AES_IT == AES_IT_CC)
    {
        /* Check the status of the specified AES interrupt */
        if (((cciebitstatus) != (uint32_t)RESET) && ((ccfbitstatus) != (uint32_t)RESET))
        {
            /* Interrupt occurred */
            itstatus = SET;
        }
        else
        {
            /* Interrupt didn't occur */
            itstatus = RESET;
        }
    }
    else /* AES_IT is AES_IT_ERR */
    {
        /* Check the status of the specified AES interrupt */
        if ((AES->CR1 & AES_CR1_ERRIE) != RESET)
        {
            /* Check if WRERR or RDERR flags are set */
            if ((AES->SR1 & (uint32_t)(AES_SR1_WRERR | AES_SR1_RDERR)) != (uint16_t)RESET)
            {
                /* Interrupt occurred */
                itstatus = SET;
            }
            else
            {
                /* Interrupt didn't occur */
                itstatus = RESET;
            }
        }
        else
        {
            /* Interrupt didn't occur */
            itstatus = (ITStatus) RESET;
        }
    }

    /* Return the AES_IT status */
    return itstatus;
}

/**
  * @brief  Clears the AES's interrupt pending bits.
  * @param  AES_IT: specifies the interrupt pending bit to clear.
  *         This parameter can be any combinations of the following values:
  *            @arg AES_IT_CC: Computation Complete Interrupt.
  *            @arg AES_IT_ERR: Error Interrupt.
  * @retval None
  */
void AES_ClearITPendingBit(uint32_t AES_IT)
{
    /* Check the parameters */
    assert_param(IS_AES_IT(AES_IT));

    /* Clear the interrupt pending bit */
    AES->CR1 |= (uint32_t) (AES_IT >> (uint32_t) 0x00000002);
}

/**
  * @brief  IT function called under interruption context to continue encryption or decryption
  * @param  pu8CrypInBuffPtr: Pointer to CRYP processing (encryption, decryption,...) buffer
  * @param  u16CrypInCount: Counter of inputed data
  * @param  pu8CrypOutBuffPtr: Pointer to CRYP processing (encryption, decryption,...) buffer
  * @param  u16CrypOutCount: Counter of outputed data
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: Operation done
  *         - ERROR: Operation failed
  */
ErrorStatus AES_EncryptDecryptIT(uint8_t* pu8CrypInBuffPtr, uint16_t u16CrypInCount, uint8_t* pu8CrypOutBuffPtr, uint16_t u16CrypOutCount)
{
    uint32_t inputaddr = 0U, outputaddr = 0U;

    /* Get the last Output data address */
    outputaddr = (uint32_t)pu8CrypOutBuffPtr;

    /* Read the Output block from the Output Register */
    *(uint32_t*)(outputaddr) = AES_ReadSubData();
    outputaddr += 4U;
    *(uint32_t*)(outputaddr) = AES_ReadSubData();
    outputaddr += 4U;
    *(uint32_t*)(outputaddr) = AES_ReadSubData();
    outputaddr += 4U;
    *(uint32_t*)(outputaddr) = AES_ReadSubData();

    pu8CrypOutBuffPtr += 16U;
    u16CrypOutCount -= 16U;

    /* Check if all input text is encrypted or decrypted */
    if (u16CrypOutCount == 0U)
    {
        /* Disable Computation Complete Interrupt */
        AES_ClearITPendingBit(AES_IT_CC);
        AES_ClearITPendingBit(AES_IT_ERR);

    }
    else /* Process the rest of input text */
    {
        /* Get the last Intput data adress */
        inputaddr = (uint32_t)pu8CrypInBuffPtr;

        /* Write the Input block in the Data Input register */
        AES_WriteSubData(*(uint32_t*)(inputaddr));
        inputaddr += 4;
        AES_WriteSubData(*(uint32_t*)(inputaddr));
        inputaddr += 4;
        AES_WriteSubData(*(uint32_t*)(inputaddr));
        inputaddr += 4;
        AES_WriteSubData(*(uint32_t*)(inputaddr));
        inputaddr += 4;

        pu8CrypInBuffPtr += 16U;
        u16CrypInCount -= 16U;

    }

    return SUCCESS;
}


/**
  * @}
  */

/** @defgroup AES_Group4 Pending and Resume config functions
 *  @brief   Pending and Resume config functions.
 *
@verbatim

 ===============================================================================
           ##### Pending and Resume config functions #####
 ===============================================================================
@endverbatim
  * @{
  */

/**
  * @brief  Pending configuration in interrupt mode , The aes operation will be suspended
  *         when a higher priority interrupt occurs in aes operations.
  * @retval None
  */
void AES_SetPendingConfigIT(void)
{
    /*0.Save the value of the corresponding register*/
    sAesPar.u32Aes_cr =  AES->CR1;
    sAesPar.u32Aes_cr2 =  AES->CR2;
    sAesPar.u32Aes_sr2 = AES->SR2;
    sAesPar.u32Aes_sr = AES->SR1;

    /*1.If dma is used to clear aes.dmainen*/
    if (READ_BIT(AES->CR1, AES_CR1_DMAINEN))
    {
        CLEAR_BIT(AES->CR1, AES_CR1_DMAINEN);
    }

    /*2. wait AES_SR.CCF to be Seted*/
    /* Wait for DRDY flag to be set */
    do
    {
        PendingTimeout++;
    } while ((PendingTimeout != AES_TIMEOUT_VALUE) && (IS_BIT_CLR(AES->SR1, AES_SR1_CCF)));


    /*3.If dma is used, the operation of dma read dout will still be done by removing the aes.
    dmaout.dmaouten clear hardware. if no dma is used, read the 4-times _ doutr register and press the result stack*/
    if (READ_BIT(AES->CR1, AES_CR1_DMAOUTEN))
    {
        CLEAR_BIT(AES->CR1, AES_CR1_DMAOUTEN);
    }
    else
    {
        sAesPar.u32Aes_Doutr3 = AES->DOUTR;
        sAesPar.u32Aes_Doutr2 = AES->DOUTR;
        sAesPar.u32Aes_Doutr1 = AES->DOUTR;
        sAesPar.u32Aes_Doutr0 = AES->DOUTR;
    }

    /*4.set bit cr register to clear ccf flag*/
    SET_BIT(AES->CR1, AES_CR1_CCFC);

    /*5. clear bit cr register to disable AES*/
    CLEAR_BIT(AES->CR1, AES_CR1_EN);

    /*6.pending AES_DINR*/
    sAesPar.u32Aes_Dinr3 = AES->DINR ;
    sAesPar.u32Aes_Dinr2 = AES->DINR ;
    sAesPar.u32Aes_Dinr1 = AES->DINR ;
    sAesPar.u32Aes_Dinr0 = AES->DINR ;

    /*7.Read the  aes _ keyrx,  registers and press the stack*/
    sAesPar.u32Aes_keyr7 =  AES->KEYR7;
    sAesPar.u32Aes_keyr6 =  AES->KEYR6;
    sAesPar.u32Aes_keyr5 =  AES->KEYR5;
    sAesPar.u32Aes_keyr4 =  AES->KEYR4;
    sAesPar.u32Aes_keyr3 =  AES->KEYR3;
    sAesPar.u32Aes_keyr2 =  AES->KEYR2;
    sAesPar.u32Aes_keyr1 =  AES->KEYR1;
    sAesPar.u32Aes_keyr0 =  AES->KEYR0;

}

/**
  * @brief  Resume , The aes operation will be Resumed when a higher priority interrupt over in aes operations.  .
  * @retval None
  */
void AES_SetResumeConfigIT(void)
{

    /*1. Set AES_CR.en to 0 and turn off AES*/
    CLEAR_BIT(AES->CR1, AES_CR1_EN);

    /*2. Resume AES_KEYRx config*/
    AES->KEYR7 = sAesPar.u32Aes_keyr7 ;
    AES->KEYR6 = sAesPar.u32Aes_keyr6 ;
    AES->KEYR5 = sAesPar.u32Aes_keyr5 ;
    AES->KEYR4 = sAesPar.u32Aes_keyr4 ;
    AES->KEYR3 = sAesPar.u32Aes_keyr3 ;
    AES->KEYR2 = sAesPar.u32Aes_keyr2 ;
    AES->KEYR1 = sAesPar.u32Aes_keyr1 ;
    AES->KEYR0 = sAesPar.u32Aes_keyr0 ;


    /*3. Resume AES_DOUTR*/
    AES->DOUTR = sAesPar.u32Aes_Doutr3 ;
    AES->DOUTR = sAesPar.u32Aes_Doutr2 ;
    AES->DOUTR = sAesPar.u32Aes_Doutr1 ;
    AES->DOUTR = sAesPar.u32Aes_Doutr0 ;

    /*4.Resume AES_DINR*/
    AES->DINR = sAesPar.u32Aes_Dinr3 ;
    AES->DINR = sAesPar.u32Aes_Dinr2 ;
    AES->DINR = sAesPar.u32Aes_Dinr1 ;
    AES->DINR = sAesPar.u32Aes_Dinr0 ;

    /*5. Resume AES_CR1,AES_CR2 config*/
    AES->CR2 = sAesPar.u32Aes_cr2;
    AES->CR1 = sAesPar.u32Aes_cr;

    /*6.set AES_CR2.CCF_SET and AES_CR2.INT_RESUME*/
    SET_BIT(AES->CR2, AES_CR2_INT_RESUME);
    SET_BIT(AES->CR2, AES_CR2_CCF_SET);

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
