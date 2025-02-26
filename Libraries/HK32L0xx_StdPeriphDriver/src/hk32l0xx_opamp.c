/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_opamp.c
* @brief:     This file provides firmware functions to manage the following
*             functionalities of the EMACC peripheral:
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
#include "hk32l0xx_opamp.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */


/** @defgroup OPAMP OPAMP
  * @brief OPAMP driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/*Private macro -------------------------------------------------------------*/
/*Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup OPAMP_Private_Functions OPAMP_Private_Functions
  * @{
  */

/** @defgroup OPAMP_Group1 Initialization and configuration
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
  * @brief  Deinitializes the OPAMP peripheral registers to their default reset values.
  * @retval None.
  */
void OPAMP_DeInit(void)
{
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_OPAMP, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_OPAMP, DISABLE);
}

/**
  * @brief  Initialize some features of OPAMP instance.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @param  OPAMP_InitStruct: Pointer to a OPAMP_InitTypeDef structure.
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: OPAMP registers are initialized
  *         - ERROR: OPAMP registers are not initialized
  */
ErrorStatus OPAMP_Init(OPAMP_TypeDef *OPAMPx, OPAMP_InitTypeDef *OPAMP_InitStruct)
{
    ErrorStatus status = SUCCESS;

    if (OPAMP_IsLocked(OPAMPx) == 0U)
    {
        OPAMPx->CSR &= ~( OPAMP_CSR_CALON
                          |     OPAMP_CSR_VP_SEL
                          |     OPAMP_CSR_VM_SEL
                        );
        OPAMPx->CSR |=  ( OPAMP_InitStruct->FunctionalMode
                          |     OPAMP_InitStruct->InputNonInverting
                          |     OPAMP_InitStruct->InputInverting
                        );

    }
    else
    {
        /* Initialization error: OPAMP instance is locked.                        */
        status = ERROR;
    }

    return status;
}

/**
  * @brief  Enable or Disable the OPAMP peripheral.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @param  NewState: new state of the OPAMP peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void OPAMP_Cmd(OPAMP_TypeDef *OPAMPx, FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the OPAMP peripheral */
        OPAMPx->CSR |= OPAMP_CSR_OPAEN;;   /**< OPAMP Enable */
    }
    else
    {
        /* Disable the OPAMP peripheral */
        OPAMPx->CSR &= ~OPAMP_CSR_OPAEN;  /**< OPAMP Disable */
    }
}


/**
  * @brief  Get OPAMP instance enable state.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @retval OPAMP instance enable state.
  */
uint32_t OPAMP_IsEnabled(OPAMP_TypeDef *OPAMPx)
{
    return (uint32_t)((OPAMPx->CSR & OPAMP_CSR_OPAEN)) >> OPAMP_CSR_OPAEN_Pos;
}

/**
  * @brief  Lock OPAMP instance.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @retval None.
  */
void OPAMP_Lock(OPAMP_TypeDef *OPAMPx)
{
    OPAMPx->CSR &= ~OPAMP_CSR_LOCK;
    OPAMPx->CSR |= OPAMP_CSR_LOCK;
}

/**
  * @brief  Get OPAMP lock state.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @retval OPAMP lock state.
  */
uint32_t OPAMP_IsLocked(OPAMP_TypeDef *OPAMPx)
{
    return (uint32_t)((OPAMPx->CSR & OPAMP_CSR_LOCK)) >> OPAMP_CSR_LOCK_Pos;
}
/**
  * @}
  */

/** @defgroup OPAMP_Group2 setting and getting
 *  @brief   setting and getting.
 *
@verbatim
 ===============================================================================
                ##### Setting and getting #####
 ===============================================================================

@endverbatim
  * @{
  */
/**
  * @brief  Set OPAMP instance operating mode.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @param  Mode: OPAMP_MODE_FUNCTIONAL,OPAMP_MODE_CALIBRATION.
  * @retval None.
  */
void OPAMP_SetMode(OPAMP_TypeDef *OPAMPx, uint32_t Mode)
{
    OPAMPx->CSR &= ~OPAMP_CSR_CALON;
    OPAMPx->CSR |= Mode;
}

/**
  * @brief  Get OPAMP mode calibration or functional.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @retval OPAMP operating mode.
  */
uint32_t OPAMP_GetMode(OPAMP_TypeDef *OPAMPx)
{
    return (uint32_t)((OPAMPx->CSR & OPAMP_CSR_CALON)) >> OPAMP_CSR_CALON_Pos;
}

/**
  * @brief  Set OPAMP PGA gain.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @param  PGAGain:
  *            @arg OPAMP_PGA_GAIN_2.
  *            @arg OPAMP_PGA_GAIN_4.
  *            @arg OPAMP_PGA_GAIN_8.
  *            @arg OPAMP_PGA_GAIN_16.
  *            @arg OPAMP_PGA_GAIN_2_VM0.
  *            @arg OPAMP_PGA_GAIN_4_VM0.
  *            @arg OPAMP_PGA_GAIN_8_VM0.
  *            @arg OPAMP_PGA_GAIN_16_VM0.
  *            @arg OPAMP_PGA_GAIN_2_VM1.
  *            @arg OPAMP_PGA_GAIN_4_VM1.
  *            @arg OPAMP_PGA_GAIN_8_VM1.
  *            @arg OPAMP_PGA_GAIN_16_VM1.
  * @retval None.
  */
void OPAMP_SetPGAGain(OPAMP_TypeDef *OPAMPx, uint32_t PGAGain)
{
    OPAMPx->CSR &= ~(OPAMP_CSR_PGA_GAIN_1 | OPAMP_CSR_PGA_GAIN_0);
    OPAMPx->CSR |= PGAGain;
}

/**
  * @brief  Get OPAMP PGA gain.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @retval OPAMP PGA gain.
  */
uint32_t OPAMP_GetPGAGain(OPAMP_TypeDef *OPAMPx)
{
    return (uint32_t)((OPAMPx->CSR & OPAMP_CSR_PGA_GAIN)) >> OPAMP_CSR_PGA_GAIN_Pos;
}

/**
  * @brief  Set OPAMP non-inverting input connection.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @param  InputNonInverting:
  *            @arg OPAMP_INPUT_NONINVERT_VP0.
  *            @arg OPAMP_INPUT_NONINVERT_VP1.
  *            @arg OPAMP_INPUT_NONINVERT_VP2.
  *            @arg OPAMP_INPUT_NONINVERT_VP3.
  * @retval None.
  */
void OPAMP_SetInputNonInverting(OPAMP_TypeDef *OPAMPx, uint32_t InputNonInverting)
{
    OPAMPx->CSR &= ~OPAMP_CSR_VP_SEL;
    OPAMPx->CSR |= InputNonInverting;
}

/**
  * @brief  Get OPAMP non-inverting input connection.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @retval OPAMP non-inverting input connection.
  */
uint32_t OPAMP_GetInputNonInverting(OPAMP_TypeDef *OPAMPx)
{
    return (uint32_t)((OPAMPx->CSR & OPAMP_CSR_VP_SEL)) >> OPAMP_CSR_VP_SEL_Pos;
}

/**
  * @brief  Set OPAMP inverting input.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @param  InputInverting:
  *            @arg OPAMP_INPUT_INVERT_VM0.
  *            @arg OPAMP_INPUT_INVERT_VM1.
  *            @arg OPAMP_MODE_PGA.
  *            @arg OPAMP_MODE_FOLLOWER.
  * @retval None.
  */
void OPAMP_SetInputInverting(OPAMP_TypeDef *OPAMPx, uint32_t InputInverting)
{
    OPAMPx->CSR &= ~OPAMP_CSR_VM_SEL;
    OPAMPx->CSR |= InputInverting;
}

/**
  * @brief  Get OPAMP inverting input.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @retval OPAMP inverting input.
  */
uint32_t OPAMP_GetInputInverting(OPAMP_TypeDef *OPAMPx)
{
    return (uint32_t)((OPAMPx->CSR & OPAMP_CSR_VM_SEL)) >> OPAMP_CSR_VM_SEL_Pos;
}

/**
  * @brief  Set OPAMP non-inverting input secondary connection.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @param  InputNonInverting This parameter can be one of the following values:
  *            @arg OPAMP_INPUT_NONINVERT_VP0_SEC.
  *            @arg OPAMP_INPUT_NONINVERT_VP1_SEC.
  *            @arg OPAMP_INPUT_NONINVERT_VP2_SEC.
  *            @arg OPAMP_INPUT_NONINVERT_VP3_SEC.
  * @retval None.
  */
void OPAMP_SetInputNonInvertingSecondary(OPAMP_TypeDef *OPAMPx, uint32_t InputNonInverting)
{
    OPAMPx->CSR &= ~OPAMP_CSR_VPS_SEL;
    OPAMPx->CSR |= InputNonInverting;
}

/**
  * @brief  Get OPAMP non-inverting input secondary connection
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @retval OPAMP non-inverting input secondary connection.
  */
uint32_t OPAMP_GetInputNonInvertingSecondary(OPAMP_TypeDef *OPAMPx)
{
    return (uint32_t)((OPAMPx->CSR & OPAMP_CSR_VPS_SEL)) >> OPAMP_CSR_VPS_SEL_Pos;
}

/**
  * @brief  Set OPAMP inverting input secondary connection.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @param  InputInverting This parameter can be one of the following values:
  *            @arg OPAMP_INPUT_INVERT_VM0_SEC.
  *            @arg OPAMP_INPUT_INVERT_VM1_SEC.
  * @retval None.
  */
void OPAMP_SetInputInvertingSecondary(OPAMP_TypeDef *OPAMPx, uint32_t InputInverting)
{
    OPAMPx->CSR &= ~OPAMP_CSR_VMS_SEL;
    OPAMPx->CSR |= InputInverting;
}

/**
  * @brief  Get OPAMP inverting input secondary connection.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @retval OPAMP inverting input secondary connection.
  */
uint32_t OPAMP_GetInputInvertingSecondary(OPAMP_TypeDef *OPAMPx)
{
    return (uint32_t)((OPAMPx->CSR & OPAMP_CSR_VMS_SEL)) >> OPAMP_CSR_VMS_SEL_Pos;
}

/**
  * @brief  Set OPAMP inputs multiplexer mode.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @param  InputsMuxMode This parameter can be one of the following values:
  *            @arg OPAMP_INPUT_MUX_DISABLE.
  *            @arg OPAMP_INPUT_MUX_SECOND_ENABLE.
  * @retval None.
  */
void OPAMP_SetInputsMuxMode(OPAMP_TypeDef *OPAMPx, uint32_t InputsMuxMode)
{
    OPAMPx->CSR &= ~OPAMP_CSR_TCM_EN;
    OPAMPx->CSR |= InputsMuxMode;
}

/**
  * @brief  Get OPAMP inputs multiplexer mode.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @retval OPAMP inputs multiplexer mode.
  */
uint32_t OPAMP_GetInputsMuxMode(OPAMP_TypeDef *OPAMPx)
{
    return (uint32_t)((OPAMPx->CSR & OPAMP_CSR_TCM_EN)) >> OPAMP_CSR_TCM_EN_Pos;
}

/**
  * @brief  Set OPAMP trimming mode.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @param  TrimmingMode This parameter can be one of the following values:
  *            @arg OPAMP_TRIMMING_FACTORY.
  *            @arg OPAMP_TRIMMING_USER.
  * @retval None.
  */
void OPAMP_SetTrimmingMode(OPAMP_TypeDef *OPAMPx, uint32_t TrimmingMode)
{
    OPAMPx->CSR &= ~OPAMP_CSR_USER_TRIM;
    OPAMPx->CSR |= TrimmingMode;
}

/**
  * @brief  Get OPAMP trimming mode.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @retval OPAMP trimming mode.
  */
uint32_t OPAMP_GetTrimmingMode(OPAMP_TypeDef *OPAMPx)
{
    return (uint32_t)((OPAMPx->CSR & OPAMP_CSR_USER_TRIM)) >> OPAMP_CSR_USER_TRIM_Pos;
}

/**
  * @brief  Set OPAMP offset to calibrate the selected transistors.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @param  TransistorsDiffPair This parameter can be one of the following values:
  *            @arg OPAMP_TRIMMING_PMOS_VREF_3_3PC_VDDA.
  *            @arg OPAMP_TRIMMING_PMOS_VREF_10PC_VDDA.
  *            @arg OPAMP_TRIMMING_NMOS_VREF_50PC_VDDA.
  *            @arg OPAMP_TRIMMING_NMOS_VREF_90PC_VDDA.
  * @retval None.
  */
void OPAMP_SetCalibrationSelection(OPAMP_TypeDef *OPAMPx, uint32_t TransistorsDiffPair)
{
    OPAMPx->CSR &= ~OPAMP_CSR_CALSEL;
    OPAMPx->CSR |= TransistorsDiffPair;
}

/**
  * @brief  Get OPAMP offset to calibrate the selected transistors.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @retval OPAMP offset to calibrate the selected transistors.
  */
uint32_t OPAMP_GetCalibrationSelection(OPAMP_TypeDef *OPAMPx)
{
    return (uint32_t)((OPAMPx->CSR & OPAMP_CSR_CALSEL)) >> OPAMP_CSR_CALSEL_Pos;
}

/**
  * @brief  Set OPAMP calibration internal reference voltage to output.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @param  CalibrationVrefOutput This parameter can be one of the following values:
  *            @arg OPAMP_VREF_OUTPUT_DISABLE.
  *            @arg OPAMP_VREF_OUTPUT_ENABLE.
  * @retval None.
  */
void OPAMP_SetCalibrationVrefOutput(OPAMP_TypeDef *OPAMPx, uint32_t CalibrationVrefOutput)
{
    OPAMPx->CSR &= ~OPAMP_CSR_TSTREF;
    OPAMPx->CSR |= CalibrationVrefOutput;
}

/**
  * @brief  Get OPAMP calibration internal reference voltage to output.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @retval OPAMP calibration internal reference voltage to output.
  */
uint32_t OPAMP_GetCalibrationVrefOutput(OPAMP_TypeDef *OPAMPx)
{
    return (uint32_t)((OPAMPx->CSR & OPAMP_CSR_TSTREF)) >> OPAMP_CSR_TSTREF_Pos;
}

/**
  * @brief  Get OPAMP calibration result of toggling output.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @retval OPAMP calibration result of toggling output.
  */
uint32_t OPAMP_IsCalibrationOutputSet(OPAMP_TypeDef *OPAMPx)
{
    return (uint32_t)((OPAMPx->CSR & OPAMP_CSR_OUTCAL)) >> OPAMP_CSR_OUTCAL_Pos;
}

/**
  * @brief  Set OPAMP trimming factor for the selected transistors.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @param  TransistorsDiffPair This parameter can be one of the following values:
  *            @arg OPAMP_TRIMMING_NMOS.
  *            @arg OPAMP_TRIMMING_PMOS.
  * @param  TrimmingValue 0x00...0x1F.
  * @retval None.
  */
void OPAMP_SetTrimmingValue(OPAMP_TypeDef* OPAMPx, uint32_t TransistorsDiffPair, uint32_t TrimmingValue)
{
    OPAMPx->CSR &= ~(TransistorsDiffPair & OPAMP_TRIMMING_VALUE_MASK);
    OPAMPx->CSR |= TrimmingValue;
}

/**
  * @brief  Get OPAMP trimming factor for the selected transistors.
  * @param  OPAMPx: OPA1,OPA2,OPA3.
  * @param  TransistorsDiffPair This parameter can be one of the following values:
  *            @arg OPAMP_TRIMMING_NMOS.
  *            @arg OPAMP_TRIMMING_PMOS.
  * @retval OPAMP trimming factor for the selected transistors.
  */
uint32_t OPAMP_GetTrimmingValue(OPAMP_TypeDef* OPAMPx, uint32_t TransistorsDiffPair)
{
    return (uint32_t)(READ_BIT(OPAMPx->CSR, (TransistorsDiffPair & OPAMP_TRIMMING_VALUE_MASK))
                      >> (POSITION_VAL(TransistorsDiffPair & OPAMP_TRIMMING_VALUE_MASK))
                     );
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


