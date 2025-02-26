/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_syscfg.c
* @brief:     SYSCFG functions configure
* @author:    AE Team
* @version:   V1.0.0/2024-01-15
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_syscfg.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */
/** @defgroup SYSCFG SYSCFG
  * @brief SYSCFG driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SYSCFG_Private_Functions  SYSCFG Private Functions
  * @{
  */

/**
  * @brief  Deinitializes the SYSCFG registers to their default reset values.
  * @retval None
  */
void SYSCFG_DeInit(void)
{
    /* Set SYSCFG_CFGR1 register to reset value without affecting MEM_MODE bits */
    SYSCFG->CFGR1 &= SYSCFG_CFGR1_MEM_MODE;
    /* Set EXTICRx registers to reset value */
    SYSCFG->EXTICR1 = 0;
    SYSCFG->EXTICR2 = 0;
    SYSCFG->EXTICR3 = 0;
    SYSCFG->EXTICR4 = 0;
}

/**
  * @brief  Configures the memory mapping at address 0x00000000.
  * @param  SYSCFG_MemoryRemap: selects the memory remapping.
  *         This parameter can be one of the following values:
  *            @arg SYSCFG_MemoryRemap_Flash: Main Flash memory mapped at 0x00000000
  *            @arg SYSCFG_MemoryRemap_SystemMemory: System Flash memory mapped at 0x00000000
  *            @arg SYSCFG_MemoryRemap_SRAM: Embedded SRAM mapped at 0x00000000
  * @retval None
  */
void SYSCFG_MemoryRemapConfig(uint32_t SYSCFG_MemoryRemap)
{
    uint32_t tmpctrl = 0;

    /* Check the parameter */
    assert_param(IS_SYSCFG_MEMORY_REMAP(SYSCFG_MemoryRemap));

    /* Get CFGR1 register value */
    tmpctrl = SYSCFG->CFGR1;

    /* Clear MEM_MODE bits */
    tmpctrl &= (uint32_t) (~SYSCFG_CFGR1_MEM_MODE);

    /* Set the new MEM_MODE bits value */
    tmpctrl |= (uint32_t) SYSCFG_MemoryRemap;

    /* Set CFGR1 register with the new memory remap configuration */
    SYSCFG->CFGR1 = tmpctrl;
}

/**
  * @brief  Get the config for memory mapping at address 0x00000000.
  * @retval SYSCFG_MemoryRemap: selects the memory remapping.
  *         This parameter can be one of the following values:
  *            @arg SYSCFG_MemoryRemap_Flash: Main Flash memory mapped at 0x00000000
  *            @arg SYSCFG_MemoryRemap_SystemMemory: System Flash memory mapped at 0x00000000
  *            @arg SYSCFG_MemoryRemap_SRAM: Embedded SRAM mapped at 0x00000000
  */
uint32_t SYSCFG_GetMemoryRemapConfig(void)
{
    return (SYSCFG->CFGR1 & SYSCFG_CFGR1_MEM_MODE);
}


/**
  * @brief  Configure the PA9_10_PA11_12 remapping.
  * @param  NewState: new state of the PA9_PA10 channel remapping.
  * @retval None
  */
void SYSCFG_PA9PA10RemapConfig(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Remap the PA9_PA10 channel */
        SYSCFG->CFGR1 |= SYSCFG_CFGR1_PA9_10_PA11_12_REMAP;
    }
    else
    {
        /* use the default PA9_PA10 channel mapping */
        SYSCFG->CFGR1 &= (~SYSCFG_CFGR1_PA9_10_PA11_12_REMAP);
    }
}

/**
  * @brief  Configure the I2C fast mode plus driving capability.
  * @param  SYSCFG_I2CFastModePlus: selects the pin.
  *         This parameter can be one of the following values:
  *            @arg SYSCFG_I2CFastModePlus_PB6: Configure fast mode plus driving capability for PB6
  *            @arg SYSCFG_I2CFastModePlus_PB7: Configure fast mode plus driving capability for PB7
  *            @arg SYSCFG_I2CFastModePlus_PB8: Configure fast mode plus driving capability for PB8
  *            @arg SYSCFG_I2CFastModePlus_PB9: Configure fast mode plus driving capability for PB9
  *            @arg SYSCFG_I2CFastModePlus_PA9: Configure fast mode plus driving capability for PA9
  *            @arg SYSCFG_I2CFastModePlus_PA10: Configure fast mode plus driving capability for PA10
  *            @arg SYSCFG_I2CFastModePlus_I2C1: Configure fast mode plus driving capability for PB10, PB11, PF6 and PF7
  * @param  NewState: new state of the DMA channel remapping.
  *         This parameter can be:  ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG_I2CFastModePlusConfig(uint32_t SYSCFG_I2CFastModePlus, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SYSCFG_I2C_FMP(SYSCFG_I2CFastModePlus));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable fast mode plus driving capability for selected pin */
        SYSCFG->CFGR1 |= (uint32_t)SYSCFG_I2CFastModePlus;
    }
    else
    {
        /* Disable fast mode plus driving capability for selected pin */
        SYSCFG->CFGR1 &= (uint32_t)(~SYSCFG_I2CFastModePlus);
    }
}

/**
  * @brief  Configure the LCD External Capacitors.
  * @param  SYSCFG_LCD_CAPA: selects the pin.
  *         This parameter can be one of the following values:
  *            @arg SYSCFG_LCD_CAPA_PB2: Control the connection of VLCD rail 1 on PB2
  *            @arg SYSCFG_LCD_CAPA_PB12: Control the connection of VLCD rail 2 on PB12
  *            @arg SYSCFG_LCD_CAPA_PB0: Control the connection of VLCD rail 3 on PB0
  * @param  NewState: new state of the VLCD connection.
  *         This parameter can be:  ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG_LCDCAPAConfig(uint32_t SYSCFG_LCD_CAPA, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SYSCFG_LCD_CAPA(SYSCFG_LCD_CAPA));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable rail connection for selected pin */
        SYSCFG->CFGR1 |= (uint32_t)SYSCFG_LCD_CAPA;
    }
    else
    {
        /* Disable rail connection for selected pin */
        SYSCFG->CFGR1 &= (uint32_t)(~SYSCFG_LCD_CAPA);
    }
}

/**
  * @brief  Selects the GPIO pin used as EXTI Line.
  * @param  EXTI_PortSourceGPIOx: selects the GPIO port to be used as source
  *         for EXTI lines where x can be (A, B, C, D, E or F).
  * @param  EXTI_PinSourcex: specifies the EXTI line to be configured.
  * @retval None
  */
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex)
{
    uint32_t tmp = 0x00;

    /* Check the parameters */
    assert_param(IS_EXTI_PORT_SOURCE(EXTI_PortSourceGPIOx));
    assert_param(IS_EXTI_PIN_SOURCE(EXTI_PinSourcex));

    tmp = ((uint32_t)0x0F) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03));

    switch (EXTI_PinSourcex >> 0x02)
    {
        case (uint8_t)0x00:
            SYSCFG->EXTICR1 &= ~tmp;
            SYSCFG->EXTICR1 |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
            break;

        case (uint8_t)0x01:
            SYSCFG->EXTICR2 &= ~tmp;
            SYSCFG->EXTICR2 |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
            break;

        case (uint8_t)0x02:
            SYSCFG->EXTICR3 &= ~tmp;
            SYSCFG->EXTICR3 |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
            break;

        case (uint8_t)0x03:
            SYSCFG->EXTICR4 &= ~tmp;
            SYSCFG->EXTICR4 |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
            break;

        default:
            break;
    }

}

/**
  * @brief  Connect the selected parameter to the break input of TIM1.
  * @param  SYSCFG_Break: selects the configuration to be connected to break
  *         input of TIM1
  *         This parameter can be any combination of the following values:
  *            @arg SYSCFG_Break_PVD: Connects the PVD event to the Break Input of TIM1
  *            @arg SYSCFG_Break_Lockup: Connects Lockup output of CortexM0 to the break input of TIM1.
  * @param  NewState: new state of BreakConfig.
  *         This parameter can be:  ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG_BreakConfig(uint32_t SYSCFG_Break, FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_SYSCFG_LOCK_CONFIG(SYSCFG_Break));

    if (NewState == ENABLE)
    {
        SYSCFG->CFGR2 |= (uint32_t) SYSCFG_Break;
    }
    else
    {
        SYSCFG->CFGR2 &= (uint32_t) (~SYSCFG_Break);
    }
}

/**
  * @brief  Set TIM3_CH4_REMAP.
  * @param  remap_source: specifies the remap source.
  *         This parameter can be one of the following values:
  *            @arg IS_SYSCFG_TIM3_CH4_REMAP.
  * @retval The new state of SYSCFG_Flag (SET or RESET).
  */
void SYSCFG_SetTimer3Ch4Remap(uint32_t remap_source)
{
    uint32_t temp;

    assert_param(IS_SYSCFG_TIM3_CH4_REMAP(remap_source));

    temp =  SYSCFG->CFGR2;

    temp &= (~SYSCFG_TIM3_CH4_REMAP_MASK);

    temp |= remap_source;

    SYSCFG->CFGR2 = temp;
}

/**
  * @brief  Get TIM3_CH4_REMAP.
  * @retval remap_source: specifies the remap source.
  *         This parameter can be one of the following values:
  *            @arg IS_SYSCFG_TIM3_CH4_REMAP.
  */
uint32_t SYSCFG_GetTimer3Ch4Remap(void)
{
    return (SYSCFG->CFGR2 & (SYSCFG_TIM3_CH4_REMAP_MASK));
}


/**
  * @brief  Lock CFGR3, then it can't be writen.
  * @retval None
  */
void SYSCFG_SetModifyLock(void)
{
    uint32_t temp;

    temp = SYSCFG->CFGR3;

    temp |= SYSCFG_CFGR3_REF_LOCK;
    SYSCFG->CFGR3 = temp;
}

/**
  * @brief  Get CFGR3 Lock Status.
  * @retval The new state of REF_LOCK (SET or RESET).
  */
FlagStatus SYSCFG_GetModifyLock(void)
{
    uint32_t temp;
    FlagStatus bitstatus = RESET;

    temp = SYSCFG->CFGR3;

    if (temp & SYSCFG_CFGR3_REF_LOCK_Mask)
    {
        bitstatus = SET;
    }

    return  bitstatus;
}

/**
  * @brief  Get VREFINT_RDYF Status.
  * @retval The new state of VREFINT_RDYF (SET or RESET).
  */
FlagStatus SYSCFG_GetVrefIntReady(void)
{
    uint32_t temp;
    FlagStatus bitstatus = RESET;

    temp = SYSCFG->CFGR3;

    if (temp & SYSCFG_CFGR3_VREFINT_RDYF_Mask)
    {
        bitstatus = SET;
    }

    return  bitstatus;
}

/**
  * @brief  Set Analog Enable Status.
  * @param  AFlag: selects the flag to be cleared.
  *         This parameter can be any combination of the following values:
  *            @arg SYSCFG_FLAG_ANALOG_EN_definition.
  * @param  NewState: new state of the ADCx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void SYSCFG_SetAnalogEn(uint32_t AFlag, FunctionalState NewState)
{
    assert_param(IS_VALID_SYSCFG_FLAG_ANALOG_EN(AFlag));


    if (NewState == DISABLE)
    {
        SYSCFG->CFGR3 &= (~AFlag);
    }
    else
    {
        SYSCFG->CFGR3 |= AFlag;
    }
}


/**
  * @brief  Get Analog Enable Status.
  * @param  AFlag: selects the flag to be set.
  *         This parameter can be one of the following values:
  *            @arg SYSCFG_FLAG_ANALOG_EN_definition.
  * @retval FunctionalState: ENABLE or DISABLE.
  */
FunctionalState SYSCFG_GetAnalogEn(uint32_t AFlag)
{
    FunctionalState funstatus = DISABLE;

    assert_param(IS_SYSCFG_FLAG_ANALOG_EN(AFlag));

    if (SYSCFG->CFGR3 & AFlag)
    {
        funstatus = ENABLE;
    }

    return funstatus;
}

/**
  * @brief  set SEL_VREF_OUT.
  * @param  AFlag: selects the flag to be set.
  *         This parameter can be one of the following values:
  *            @arg SYSCFG_FLAG_SEL_VREF_OUT.
  * @param  NewState: new state of the ADCx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void SYSCFG_SetSelVrefOut(uint32_t AFlag, FunctionalState NewState)
{
    uint32_t temp;

    assert_param(IS_VALID_SYSCFG_FLAG_SEL_VREF_OUT(AFlag));

    temp = SYSCFG->CFGR3;

    if (NewState == DISABLE)
    {

        temp &= (~AFlag);
    }
    else
    {
        temp &= (~SYSCFG_FLAG_SEL_VREF_MASK);

        temp |= AFlag;
    }

    SYSCFG->CFGR3 = temp;
}


/**
  * @brief  Get SEL_VREF_OUT.
  * @retval return parameter can be one of the following values:
  *            @arg SYSCFG_FLAG_SEL_VREF_OUT.
  */
uint32_t SYSCFG_GetSelVrefOut(void)
{
    uint32_t slct;

    slct = (SYSCFG->CFGR3 & SYSCFG_FLAG_SEL_VREF_MASK);

    return slct;
}



/**
  * @brief  VREFINT reference for ADC enable bit.
  * @param  NewState: new state of the ADC Vref Enable.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG_ADCVrefEnableCmd(FunctionalState NewState)
{
    uint32_t temp;

    temp = SYSCFG->CFGR3;

    if (NewState == DISABLE)
    {
        temp &= (~SYSCFG_CFGR3_ENBUF_VREFINT_ADC_Mask);
    }
    else
    {
        temp |= SYSCFG_CFGR3_ENBUF_VREFINT_ADC;
    }

    SYSCFG->CFGR3 = temp;
}

/**
  * @brief  Get VREFINT reference for ADC enable bit Status.
  * @retval The new state of ENBUF_VREFINT_ADC (SET or RESET).
  */
FlagStatus SYSCFG_GetADCVrefEnableStatus(void)
{
    uint32_t temp;
    FlagStatus bitstatus = RESET;

    temp = SYSCFG->CFGR3;

    if (temp & SYSCFG_CFGR3_ENBUF_VREFINT_ADC_Mask)
    {
        bitstatus = SET;
    }

    return  bitstatus;
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

