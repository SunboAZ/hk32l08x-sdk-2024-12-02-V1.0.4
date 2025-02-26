/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_dac.c
* @brief:     DAC init and functions configure
* @author:    AE Team
* @version:   V1.0.0/2024-01-15
* @version:   V1.0.0/2024-01-15
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_dac.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */
/** @defgroup DAC DAC
  * @brief DAC driver modules
  * @{
@verbatim
           ##### How to use this driver #####
===============================================================================
   [..]
    (+) Enable DAC APB1 clock to get write access to DAC registers
      using RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE)

    (+) Configure DAC_OUTx in analog mode
      using GPIO_Init() function

    (+) Configure the DAC channel using DAC_Init()

    (+) Enable the DAC channel using DAC_Cmd()

@endverbatim
  *
  ******************************************************************************
  */

/** @defgroup DAC_Private_Defines  DAC Private Defines
  * @{
  */

/* CR register Mask */
#define CR_CLEAR_MASK              ((uint32_t)0x00000FFE)

/* DAC Dual Channels SWTRIG masks */
#define DUAL_SWTRIG_SET            ((uint32_t)0x00000001)
#define DUAL_SWTRIG_RESET          ((uint32_t)0xFFFFFFFE)

/* DHR registers offsets */
#define DHR12R_OFFSET             ((uint32_t)0x00000008)
#define DHR12RD_OFFSET             ((uint32_t)0x00000020)

/* DOR register offset */
#define DOR_OFFSET                 ((uint32_t)0x0000002C)
/**
  * @}
  */

/** @defgroup DAC_Private_Functions DAC Private Functions
  * @{
  */

/**
  * @brief  Deinitializes the DAC peripheral registers to their default reset values.
  * @retval None
  */
void DAC_DeInit(void)
{
    /* Enable DAC reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, ENABLE);
    /* Release DAC from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, DISABLE);
}

/**
  * @brief  Initializes the DAC peripheral according to the specified
  *         parameters in the DAC_InitStruct.
  * @param  DAC_InitStruct: pointer to a DAC_InitTypeDef structure that
  *         contains the configuration information for the specified DAC channel.
  * @retval None
  */
void DAC_Init(DAC_InitTypeDef* DAC_InitStruct)
{
    uint32_t tmpreg1 = 0, tmpreg2 = 0;
    /* Check the DAC parameters */
    assert_param(IS_DAC_TRIGGER(DAC_InitStruct->DAC_Trigger));
    assert_param(IS_DAC_GENERATE_WAVE(DAC_InitStruct->DAC_WaveGeneration));
    assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude));
    assert_param(IS_DAC_OUTPUT_BUFFER_STATE(DAC_InitStruct->DAC_OutputBuffer));
    /*---------------------------- DAC CR Configuration --------------------------*/
    /* Get the DAC CR value */
    tmpreg1 = DAC->CR;
    /* Clear BOFFx, TENx, TSELx, WAVEx and MAMPx bits */
    tmpreg1 &= ~(CR_CLEAR_MASK );
    /* Configure for the selected DAC channel: buffer output, trigger, wave generation,
       mask/amplitude for wave generation */
    /* Set TSELx and TENx bits according to DAC_Trigger value */
    /* Set WAVEx bits according to DAC_WaveGeneration value */
    /* Set MAMPx bits according to DAC_LFSRUnmask_TriangleAmplitude value */
    /* Set BOFFx bit according to DAC_OutputBuffer value */
    tmpreg2 = (DAC_InitStruct->DAC_Trigger | DAC_InitStruct->DAC_WaveGeneration |
               DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude | DAC_InitStruct->DAC_OutputBuffer);
    /* Calculate CR register value depending on DAC_Channel */
    tmpreg1 |= tmpreg2;
    /* Write to DAC CR */
    DAC->CR = tmpreg1;
}

/**
  * @brief  Fills each DAC_InitStruct member with its default value.
  * @param  DAC_InitStruct : pointer to a DAC_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
{
    /*--------------- Reset DAC init structure parameters values -----------------*/
    /* Initialize the DAC_Trigger member */
    DAC_InitStruct->DAC_Trigger = DAC_Trigger_None;
    /* Initialize the DAC_WaveGeneration member */
    DAC_InitStruct->DAC_WaveGeneration = DAC_WaveGeneration_None;
    /* Initialize the DAC_LFSRUnmask_TriangleAmplitude member */
    DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
    /* Initialize the DAC_OutputBuffer member */
    DAC_InitStruct->DAC_OutputBuffer = DAC_OutputBuffer_Enable;
}

/**
  * @brief  Enables or disables the specified DAC channel.
  * @param  NewState: new state of the DAC channel.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected DAC channel */
        DAC->CR |= DAC_CR_EN;
    }
    else
    {
        /* Disable the selected DAC channel */
        DAC->CR &= ~DAC_CR_EN;
    }
}

/**
  * @brief  Enables or disables the specified DAC interrupts.
  * @param  DAC_IT: specifies the DAC interrupt sources to be enabled or disabled.
  *         This parameter can be the following values:
  *            @arg DAC_IT_DMAUDR: DMA underrun interrupt mask
  * @param  NewState: new state of the specified DAC interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_ITConfig(uint32_t DAC_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_DAC_IT(DAC_IT));

    if (NewState != DISABLE)
    {
        /* Enable the selected DAC interrupts */
        DAC->CR |=  (DAC_IT );
    }
    else
    {
        /* Disable the selected DAC interrupts */
        DAC->CR &= (~(uint32_t)(DAC_IT ));
    }
}

/**
  * @brief  Enables or disables the specified DAC channel DMA request.
  * @param  NewState: new state of the selected DAC channel DMA request.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_DMACmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected DAC channel DMA request */
        DAC->CR |= DAC_CR_DMAEN;
    }
    else
    {
        /* Disable the selected DAC channel DMA request */
        DAC->CR &= ~DAC_CR_DMAEN;
    }
}

/**
  * @brief  Enables or disables the selected DAC channel software trigger.
  * @param  NewState: new state of the selected DAC channel software trigger.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_SoftwareTriggerCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable software trigger for the selected DAC channel */
        DAC->SWTRIGR |= (uint32_t)DAC_SWTRIGR_SWTRIG;
    }
    else
    {
        /* Disable software trigger for the selected DAC channel */
        DAC->SWTRIGR &= ~((uint32_t)DAC_SWTRIGR_SWTRIG);
    }
}

/**
  * @brief  Enables or disables the selected DAC channel wave generation.
  * @param  DAC_Wave: Specifies the wave type to enable or disable.
  *         This parameter can be one of the following values:
  *            @arg DAC_Wave_Noise: noise wave generation
  *            @arg DAC_Wave_Triangle: triangle wave generation
  * @param  NewState: new state of the selected DAC channel wave generation.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_WaveGenerationCmd(uint32_t DAC_Wave, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_DAC_WAVE(DAC_Wave));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected wave generation for the selected DAC channel */
        DAC->CR |= DAC_Wave ;
    }
    else
    {
        /* Disable the selected wave generation for the selected DAC channel */
        DAC->CR &= ~(DAC_Wave );
    }
}

/**
  * @brief  Set the specified data holding register value for DAC channel1.
  * @param  DAC_Align: Specifies the data alignment for DAC channel1.
  *         This parameter can be one of the following values:
  *            @arg DAC_Align_8b_R: 8bit right data alignment selected
  *            @arg DAC_Align_12b_L: 12bit left data alignment selected
  *            @arg DAC_Align_12b_R: 12bit right data alignment selected
  * @param  Data : Data to be loaded in the selected data holding register.
  * @retval None
  */
void DAC_SetChannelData(uint32_t DAC_Align, uint16_t Data)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_DAC_ALIGN(DAC_Align));
    assert_param(IS_DAC_DATA(Data));

    tmp = (uint32_t)DAC_BASE;
    tmp += DHR12R_OFFSET + DAC_Align;

    /* Set the DAC channel1 selected data holding register */
    *(__IO uint32_t *) tmp = Data;
}

/**
  * @brief  Returns the last data output value of the selected DAC channel.
  * @retval The selected DAC channel data output value.
  */
uint16_t DAC_GetDataOutputValue(void)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */

    tmp = (uint32_t) DAC_BASE ;
    tmp += DOR_OFFSET;

    /* Returns the DAC channel data output register value */
    return (uint16_t) (*(__IO uint32_t*) tmp);
}

/**
  * @brief  Checks whether the specified DAC flag is set or not.
  * @param  DAC_FLAG: specifies the flag to check.
  *         This parameter can be only of the following value:
  *            @arg DAC_FLAG_DMAUDR: DMA underrun flag
  * @retval The new state of DAC_FLAG (SET or RESET).
  */
FlagStatus DAC_GetFlagStatus(uint32_t DAC_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_DAC_FLAG(DAC_FLAG));

    /* Check the status of the specified DAC flag */
    if ((DAC->SR & (DAC_FLAG )) != (uint8_t)RESET)
    {
        /* DAC_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* DAC_FLAG is reset */
        bitstatus = RESET;
    }

    /* Return the DAC_FLAG status */
    return  bitstatus;
}

/**
  * @brief  Clears the DAC channelx's pending flags.
  * @param  DAC_FLAG: specifies the flag to clear.
  *         This parameter can be of the following value:
  *            @arg DAC_FLAG_DMAUDR: DMA underrun flag
  * @retval None
  */
void DAC_ClearFlag( uint32_t DAC_FLAG)
{
    /* Check the parameters */

    assert_param(IS_DAC_FLAG(DAC_FLAG));

    /* Clear the selected DAC flags */
    DAC->SR = (DAC_FLAG );
}

/**
  * @brief  Checks whether the specified DAC interrupt has occurred or not.
  * @param  DAC_IT: specifies the DAC interrupt source to check.
  *         This parameter can be the following values:
  *            @arg DAC_IT_DMAUDR: DMA underrun interrupt mask
  * @retval The new state of DAC_IT (SET or RESET).
  */
ITStatus DAC_GetITStatus( uint32_t DAC_IT)
{
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    /* Check the parameters */
    assert_param(IS_DAC_IT(DAC_IT));

    /* Get the DAC_IT enable bit status */
    enablestatus = (DAC->CR & (DAC_IT )) ;

    /* Check the status of the specified DAC interrupt */
    if (((DAC->SR & (DAC_IT )) != (uint32_t)RESET) && enablestatus)
    {
        /* DAC_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* DAC_IT is reset */
        bitstatus = RESET;
    }

    /* Return the DAC_IT status */
    return  bitstatus;
}

/**
  * @brief  Clears the DAC channelx's interrupt pending bits.
  * @param  DAC_IT: specifies the DAC interrupt pending bit to clear.
  *         This parameter can be the following values:
  *            @arg DAC_IT_DMAUDR: DMA underrun interrupt mask
  * @retval None
  */
void DAC_ClearITPendingBit(uint32_t DAC_IT)
{
    /* Check the parameters */
    assert_param(IS_DAC_IT(DAC_IT));
    /* Clear the selected DAC interrupt pending bits */
    DAC->SR = (DAC_IT );
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

/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
