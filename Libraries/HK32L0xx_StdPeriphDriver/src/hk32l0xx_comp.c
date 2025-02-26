/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_comp.c
* @brief:     API file of comp module
* @author:    AE Team
* @version:   V1.0.0/2024-01-08
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_comp.h"
#include "hk32l0xx_rcc.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */


/** @defgroup COMP COMP
  * @brief COMP driver modules
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup COMP_Private_Functions COMP_Private_Functions
  * @{
  */

/**
  * @brief  DeInitialize some features of COMP instance.
  * @retval None.
  */
void COMP_DeInit(void)
{

    /* Note: Hardware constraint (refer to description of this function):       */
    /*       COMP instance must not be locked.                                  */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_COMP, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_COMP, DISABLE);
}

/**
  * @brief  Initialize some features of COMP instance.
  * @param  COMPx: CMP1,CMP2.
  * @param  COMP_InitStruct: pointer to a COMP_InitTypeDef structure.
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: COMP registers are initialized
  *         - ERROR: COMP registers are not initialized
  */
ErrorStatus COMP_Init(uint8_t COMPx, COMP_InitTypeDef *COMP_InitStruct)
{
    ErrorStatus status = SUCCESS;

    if (COMP_IsLocked(COMPx) == 0U)
    {
        if (COMPx == CMP1)
        {
            COMP1->CSR &= ~( COMP1_CSR_COMP1INNSEL
                             | COMP1_CSR_COMP1WINOUT
                             | COMP1_CSR_COMP1POLARITY
                             | COMP1_CSR_COMP1HYST
                             | COMP1_CSR_COMP1PWRMD
                           );
            COMP1->CSR |= (  COMP_InitStruct->InputMinus
                             | COMP_InitStruct->WindowOut
                             | COMP_InitStruct->OutputPolarity
                             | COMP_InitStruct->Hysteresis
                             | COMP_InitStruct->PowerMode
                          );
        }
        else if (COMPx == CMP2)
        {
            COMP2->CSR &= ~(  COMP2_CSR_COMP2INNSEL
                              | COMP2_CSR_COMP2INPSEL
                              | COMP2_CSR_COMP2WINOUT
                              | COMP2_CSR_COMP2POLARITY
                              | COMP2_CSR_COMP2HYST
                              | COMP2_CSR_COMP2PWRMD
                           ) ;
            COMP2->CSR |= (  COMP_InitStruct->InputMinus
                             | COMP_InitStruct->InputPlus
                             | COMP_InitStruct->WindowOut
                             | COMP_InitStruct->OutputPolarity
                             | COMP_InitStruct->Hysteresis
                             | COMP_InitStruct->PowerMode
                          ) ;
        }
    }
    else
    {
        /* Initialization error: COMP instance is locked.                         */
        status = ERROR;
    }

    return status;
}

/**
  * @brief  Set window mode of a pair of comparators instances.
  * @param  WindowMode:
  *         COMP1_INPUT_PLUS_PA1.
  *         COMP1_INPUT_PLUS_COMP2.
  * @retval None.
  */
void COMP_SetCommonWindowMode(uint32_t WindowMode)
{
    COMP1->CSR &= ~COMP1_CSR_COMP1WM;
    COMP1->CSR |= WindowMode;
}

/**
  * @brief  Get window mode of a pair of comparators instances
  * @param  COMPx: CMP1.
  * @retval Window mode of a pair of comparators instances.
  */
uint32_t COMP_GetCommonWindowMode(uint8_t COMPx)
{
    uint32_t Temp;

    if (COMPx == CMP1)
    {
        Temp = (uint32_t)((COMP1->CSR & COMP1_CSR_COMP1WM)) >> COMP1_CSR_COMP1WM_Pos;
    }

    return Temp;
}

/**
  * @brief  Set comparator instance operating mode to adjust power and speed.
  * @param  COMPx: CMP1,CMP2.
  * @param  PowerMode:
  *         COMP_POWERMODE_LOWPOWER.
  *         COMP_POWERMODE_NORMALPOWER.
  * @retval None.
  */
void COMP_SetPowerMode(uint8_t COMPx, uint32_t PowerMode)
{
    if (COMPx == CMP1)
    {
        COMP1->CSR &= ~COMP1_CSR_COMP1PWRMD;
        COMP1->CSR |= PowerMode;
    }
    else if (COMPx == CMP2)
    {
        COMP2->CSR &= ~COMP2_CSR_COMP2PWRMD;
        COMP2->CSR |= PowerMode;
    }
}

/**
  * @brief  Get comparator instance operating mode to adjust power and speed.
  * @param  COMPx: CMP1,CMP2.
  * @retval Comparator instance operating mode to adjust power and speed.
  */
uint32_t COMP_GetPowerMode(uint8_t COMPx)
{
    uint32_t Temp;

    if (COMPx == CMP1)
    {
        Temp = (uint32_t)((COMP1->CSR & COMP1_CSR_COMP1PWRMD)) >> COMP1_CSR_COMP1PWRMD_Pos;
    }
    else if (COMPx == CMP2)
    {
        Temp = (uint32_t)((COMP2->CSR & COMP2_CSR_COMP2PWRMD)) >> COMP2_CSR_COMP2PWRMD_Pos;
    }

    return Temp;
}

/**
  * @brief  Set comparator instance output polarity.
  * @param  COMPx: CMP1,CMP2.
  * @param  OutputPolarity:
  *         COMP_OUTPUTPOL_NONINVERTED.
  *         COMP_OUTPUTPOL_INVERTED.
  * @retval None.
  */
void COMP_SetOutputPolarity(uint8_t COMPx, uint32_t OutputPolarity)
{
    if (COMPx == CMP1)
    {
        COMP1->CSR &= ~COMP1_CSR_COMP1POLARITY;
        COMP1->CSR |= OutputPolarity;
    }
    else if (COMPx == CMP2)
    {
        COMP2->CSR &= ~COMP2_CSR_COMP2POLARITY;
        COMP2->CSR |= OutputPolarity;
    }
}

/**
  * @brief  Get comparator instance output polarity.
  * @param  COMPx: CMP1,CMP2.
  * @retval Comparator instance output polarity.
  */
uint32_t COMP_GetOutputPolarity(uint8_t COMPx)
{
    uint32_t Temp;

    if (COMPx == CMP1)
    {
        Temp = (uint32_t)((COMP1->CSR & COMP1_CSR_COMP1POLARITY)) >> COMP1_CSR_COMP1POLARITY_Pos;
    }
    else if (COMPx == CMP2)
    {
        Temp = (uint32_t)((COMP2->CSR & COMP2_CSR_COMP2POLARITY)) >> COMP2_CSR_COMP2POLARITY_Pos;
    }

    return Temp;
}

/**
  * @brief  Enable comparator.
  * @param  COMPx: CMP1,CMP2.
  * @retval None.
  */
void COMP_Enable(uint8_t COMPx)
{
    if (COMPx == CMP1)
    {
        COMP1->CSR &= ~COMP1_CSR_COMP1EN;
        COMP1->CSR |= COMP1_CSR_COMP1EN;
    }
    else if (COMPx == CMP2)
    {
        COMP2->CSR &= ~COMP2_CSR_COMP2EN;
        COMP2->CSR |= COMP2_CSR_COMP2EN;
    }
}

/**
  * @brief  Disable comparator.
  * @param  COMPx: CMP1,CMP2.
  * @retval None.
  */
void COMP_Disable(uint8_t COMPx)
{
    if (COMPx == CMP1)
    {
        COMP1->CSR &= ~COMP1_CSR_COMP1EN;
    }
    else if (COMPx == CMP2)
    {
        COMP2->CSR &= ~COMP2_CSR_COMP2EN;
    }
}

/**
  * @brief  Get comparator enable state.
  * @param  COMPx: CMP1,CMP2.
  * @retval Comparator enable state.
  */
uint32_t COMP_IsEnabled(uint8_t COMPx)
{
    uint32_t Temp;

    if (COMPx == CMP1)
    {
        Temp = (uint32_t)((COMP1->CSR & COMP1_CSR_COMP1EN)) >> COMP1_CSR_COMP1EN_Pos;
    }
    else if (COMPx == CMP2)
    {
        Temp = (uint32_t)((COMP2->CSR & COMP2_CSR_COMP2EN)) >> COMP2_CSR_COMP2EN_Pos;
    }

    return Temp;
}

/**
  * @brief  Lock comparator.
  * @param  COMPx: CMP1,CMP2.
  * @retval None.
  */
void COMP_Lock(uint8_t COMPx)
{
    if (COMPx == CMP1)
    {
        COMP1->CSR &= ~COMP1_CSR_COMP1LOCK;
        COMP1->CSR |= COMP1_CSR_COMP1LOCK;
    }
    else if (COMPx == CMP2)
    {
        COMP2->CSR &= ~COMP2_CSR_COMP2LOCK;
        COMP2->CSR |= COMP2_CSR_COMP2LOCK;
    }
}

/**
  * @brief  Get comparator lock state.
  * @param  COMPx: CMP1,CMP2.
  * @retval Comparator lock state.
  */
uint32_t COMP_IsLocked(uint8_t COMPx)
{
    uint32_t Temp;

    if (COMPx == CMP1)
    {
        Temp = (uint32_t)((COMP1->CSR & COMP1_CSR_COMP1LOCK)) >> COMP1_CSR_COMP1LOCK_Pos;
    }
    else if (COMPx == CMP2)
    {
        Temp = (uint32_t)((COMP2->CSR & COMP2_CSR_COMP2LOCK)) >> COMP2_CSR_COMP2LOCK_Pos;
    }

    return Temp;
}

/**
  * @brief  Read comparator instance output level.
  * @param  COMPx: CMP1,CMP2.
  * @retval Comparator instance output level.
  */
uint32_t COMP_ReadOutputLevel(uint8_t COMPx)
{
    uint32_t Temp;

    if (COMPx == CMP1)
    {
        Temp = (uint32_t)((COMP1->CSR & COMP1_CSR_COMP1VALUE)) >> COMP1_CSR_COMP1VALUE_Pos;
    }
    else if (COMPx == CMP2)
    {
        Temp = (uint32_t)((COMP2->CSR & COMP2_CSR_COMP2VALUE)) >> COMP2_CSR_COMP2VALUE_Pos;
    }

    return Temp;
}

/**
  * @brief  Set comparator instance NonInverting input.
  * @param  COMPx: CMP1,CMP2.
  * @param  InputNonInverting:
  *         COMP1_INPUT_PLUS_PA1.
  *         COMP2_INPUT_PLUS_PA3.
  *         COMP2_INPUT_PLUS_PB4.
  *         COMP2_INPUT_PLUS_PB5.
  *         COMP2_INPUT_PLUS_PB6.
  *         COMP2_INPUT_PLUS_PB7.
  * @retval None.
  */
void COMP_SetInputNonInverting(uint8_t COMPx, uint32_t InputNonInverting)
{
    if (COMPx == CMP1)
    {
        COMP1->CSR &= ~COMP1_CSR_COMP1WM;
        COMP1->CSR |= InputNonInverting;
    }
    else if (COMPx == CMP2)
    {
        COMP2->CSR &= ~COMP2_CSR_COMP2INPSEL;
        COMP2->CSR |= InputNonInverting;
    }
}

/**
  * @brief  Get comparator instance NonInverting input.
  * @param  COMPx: CMP1,CMP2.
  * @retval Comparator instance NonInverting input.
  */
uint32_t COMP_GetInputNonInverting(uint8_t COMPx)
{
    uint32_t Temp;

    if (COMPx == CMP1)
    {
        Temp = (uint32_t)((COMP1->CSR & COMP1_CSR_COMP1WM) >> COMP1_CSR_COMP1WM_Pos);
    }
    else if (COMPx == CMP2)
    {
        Temp = (uint32_t)((COMP2->CSR & COMP2_CSR_COMP2INPSEL) >> COMP2_CSR_COMP2INPSEL_Pos);
    }

    return Temp;
}

/**
  * @brief  Set comparator instance Inverting input.
  * @param  COMPx: CMP1,CMP2.
  * @param  InputInverting:
  *         COMP1_INPUT_MINUS_PA0.
  *         COMP1_INPUT_MINUS_DAC_PA4.
  *         COMP1_INPUT_MINUS_PA5.
  *         COMP1_INPUT_MINUS_1_4VREFINT.
  *         COMP1_INPUT_MINUS_1_2VREFINT.
  *         COMP1_INPUT_MINUS_3_4VREFINT.
  *         COMP2_INPUT_MINUS_VREFINT.
  *         COMP2_INPUT_MINUS_PA2.
  *         COMP2_INPUT_MINUS_DAC_PA4.
  *         COMP2_INPUT_MINUS_PA5.
  *         COMP2_INPUT_MINUS_1_4VREFINT.
  *         COMP2_INPUT_MINUS_1_2VREFINT.
  *         COMP2_INPUT_MINUS_3_4VREFINT.
  *         COMP2_INPUT_MINUS_PB3.
  * @retval None.
  */
void COMP_SetInputInverting(uint8_t COMPx, uint32_t InputInverting)
{
    if (COMPx == CMP1)
    {
        COMP1->CSR &= ~COMP1_CSR_COMP1INNSEL;
        COMP1->CSR |= InputInverting;
    }
    else if (COMPx == CMP2)
    {
        COMP2->CSR &= ~COMP2_CSR_COMP2INNSEL;
        COMP2->CSR |= InputInverting;
    }
}

/**
  * @brief  Get comparator instance Inverting input.
  * @param  COMPx: CMP1,CMP2.
  * @retval Comparator instance Inverting input.
  */
uint32_t COMP_GetInputInverting(uint8_t COMPx)
{
    uint32_t Temp;

    if (COMPx == CMP1)
    {
        Temp = (uint32_t)((COMP1->CSR & COMP1_CSR_COMP1INNSEL)) >> COMP1_CSR_COMP1INNSEL_Pos;
    }
    else if (COMPx == CMP2)
    {
        Temp = (uint32_t)((COMP2->CSR & COMP2_CSR_COMP2INNSEL)) >> COMP2_CSR_COMP2INNSEL_Pos;
    }

    return Temp;
}

/**
  * @brief  Set comparator hysteresis value.
  * @param  COMPx: CMP1,CMP2.
  * @param  hysteresis:
  *         COMP_HYSTERESIS_DISABLE.
  *         COMP_HYSTERESIS_LEVEL1.
  *         COMP_HYSTERESIS_LEVEL2.
  *         COMP_HYSTERESIS_LEVEL3.
  * @retval None.
  */
void COMP_SetHysteresis(uint8_t COMPx, uint32_t hysteresis)
{
    if (COMPx == CMP1)
    {
        COMP1->CSR &= ~COMP1_CSR_COMP1HYST;
        COMP1->CSR |= hysteresis;
    }
    else if (COMPx == CMP2)
    {
        COMP2->CSR &= ~COMP2_CSR_COMP2HYST;
        COMP2->CSR |= hysteresis;
    }
}
/**
  * @brief  Get comparator hysteresis value.
  * @param  COMPx: CMP1,CMP2.
  * @retval Comparator hysteresis value.
  */
uint32_t COMP_GetHysteresis(uint8_t COMPx)
{
    uint32_t Temp;

    if (COMPx == CMP1)
    {
        Temp = (uint32_t)((COMP1->CSR & COMP1_CSR_COMP1HYST)) >> COMP1_CSR_COMP1HYST_Pos;
    }
    else if (COMPx == CMP2)
    {
        Temp = (uint32_t)((COMP2->CSR & COMP2_CSR_COMP2HYST)) >> COMP2_CSR_COMP2HYST_Pos;
    }

    return Temp;
}

/**
  * @brief  Set comparator valid output bit.
  * @param  COMPx: CMP1,CMP2.
  * @param  output:
  *         COMP_OUTPUT_Valid_0.
  *         COMP_OUTPUT_Valid_1.
  * @retval None.
  */
void COMP_SetValidoutput(uint8_t COMPx, uint32_t output)
{
    if (COMPx == CMP1)
    {
        COMP1->CSR &= ~COMP1_CSR_COMP1VALID;
        COMP1->CSR |= output;
    }
    else if (COMPx == CMP2)
    {
        COMP2->CSR &= ~COMP2_CSR_COMP2VALID;
        COMP2->CSR |= output;
    }
}

/**
  * @brief  Get comparator valid output bit value.
  * @param  COMPx: CMP1,CMP2.
  * @retval Comparator valid output bit value.
  */
uint32_t COMP_GetValidoutput(uint8_t COMPx)
{
    uint32_t Temp;

    if (COMPx == CMP1)
    {
        Temp = (uint32_t)((COMP1->CSR & COMP1_CSR_COMP1VALID)) >> COMP1_CSR_COMP1VALID_Pos;
    }
    else if (COMPx == CMP2)
    {
        Temp = (uint32_t)((COMP2->CSR & COMP2_CSR_COMP2VALID)) >> COMP2_CSR_COMP2VALID_Pos;
    }

    return Temp;
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
