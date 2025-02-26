/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_clu.c
* @brief:     CLU init and functions configure
* @author:    AE Team
* @version:   V1.0.0/2024-01-15
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_clu.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup CLU CLU
  * @brief CLU driver modules
  * @{
  */

/** @defgroup CLU_Private_Functions CLU Private Functions
  * @{
  */

/**
  * @brief  Initializes the CLU peripheral according to the specified parameters
  *         in the CLU_InitStruct.
  * @param  CLU_InitStruct: pointer to a CLU_InitTypeDef structure that contains
  *         the configuration information for the specified CLU peripheral.
  * @retval None
  */
void CLU_Init(CLU_InitTypeDef* CLU_InitStruct)
{
    /* Check the parameters */
    assert_param(IS_CLEN0_CEN(CLU_InitStruct->CLU_Enable));

    /* CLU0 Configuration */
    if (CLU_InitStruct->CLU_Enable & CLEN0_C0EN__ENABLE)
    {
        /* Check parameters */
        assert_param(IS_CLUxMX_MXA_SELECTION(CLU_InitStruct->CLU0_MXA));
        assert_param(IS_CLUxMX_MXB_SELECTION(CLU_InitStruct->CLU0_MXB));
        assert_param(IS_CLUxMX_MXC_SELECTION(CLU_InitStruct->CLU0_MXC));
        assert_param(IS_CLUxMX_MXD_SELECTION(CLU_InitStruct->CLU0_MXD));
        assert_param(IS_CLUxFN_FUNCTION(CLU_InitStruct->CLU0_FN));
        assert_param(IS_CLUxCF_CLKSEL(CLU_InitStruct->CLU0_ClkSel));
        assert_param(IS_CLUxCF_CLKINV(CLU_InitStruct->CLU0_ClkInv));
        assert_param(IS_CLUxCF_OEN(CLU_InitStruct->CLU0_PinOut));
        assert_param(IS_CLUxCF_OUTSEL(CLU_InitStruct->CLU0_OutSel));

        /* Configurable Logic Unit 0 Multiplexer Configuration */
        CLU->CLU0_MX = (uint32_t)((uint32_t)CLU_InitStruct->CLU0_MXA | (uint32_t)CLU_InitStruct->CLU0_MXB | (uint32_t)CLU_InitStruct->CLU0_MXC | (uint32_t)CLU_InitStruct->CLU0_MXD);
        CLU->CLU0_MX |= (uint32_t)0x1F << 16;

        /* Configurable Logic Unit 0 Function Select Configuration */
        CLU->CLU0_FN = (uint8_t)CLU_InitStruct->CLU0_FN;

        /* Configurable Logic Unit 0 Configuration */
        CLU->CLU0_CTL = (CLU->CLU0_CTL & ~(CLU_CLU0_CTL_CLKSEL | CLU_CLU0_CTL_CLKINV | CLU_CLU0_CTL_OEN | CLU_CLU0_CTL_OUTSEL)) | \
                        (CLU_InitStruct->CLU0_ClkSel << CLU_CLU0_CTL_CLKSEL_Pos) | (CLU_InitStruct->CLU0_ClkInv << CLU_CLU0_CTL_CLKINV_Pos) | \
                        (CLU_InitStruct->CLU0_PinOut << CLU_CLU0_CTL_OEN_Pos) | (CLU_InitStruct->CLU0_OutSel << CLU_CLU0_CTL_OUTSEL_Pos) ;

        /* Configurable Logic 0 Enable*/
        CLU->CTL |= CLEN0_C0EN__ENABLE;

    }

    /* CLU1 Configuration */
    if (CLU_InitStruct->CLU_Enable & CLEN0_C1EN__ENABLE)
    {
        /* Check parameters */
        assert_param(IS_CLUxMX_MXA_SELECTION(CLU_InitStruct->CLU1_MXA));
        assert_param(IS_CLUxMX_MXB_SELECTION(CLU_InitStruct->CLU1_MXB));
        assert_param(IS_CLUxMX_MXC_SELECTION(CLU_InitStruct->CLU1_MXC));
        assert_param(IS_CLUxMX_MXD_SELECTION(CLU_InitStruct->CLU1_MXD));
        assert_param(IS_CLUxFN_FUNCTION(CLU_InitStruct->CLU1_FN));
        assert_param(IS_CLUxCF_CLKSEL(CLU_InitStruct->CLU1_ClkSel));
        assert_param(IS_CLUxCF_CLKINV(CLU_InitStruct->CLU1_ClkInv));
        assert_param(IS_CLUxCF_OEN(CLU_InitStruct->CLU1_PinOut));
        assert_param(IS_CLUxCF_OUTSEL(CLU_InitStruct->CLU1_OutSel));

        /* Configurable Logic Unit 1 Multiplexer Configuration */
        CLU->CLU1_MX = (uint32_t)CLU_InitStruct->CLU1_MXA | (uint32_t)CLU_InitStruct->CLU1_MXB | (uint32_t)CLU_InitStruct->CLU1_MXC | (uint32_t)CLU_InitStruct->CLU1_MXD;
        CLU->CLU1_MX |= (uint32_t)0x1F << 16;

        /* Configurable Logic Unit 1 Function Select Configuration */
        CLU->CLU1_FN = (uint8_t)CLU_InitStruct->CLU1_FN;

        /* Configurable Logic Unit 1 Configuration */
        CLU->CLU1_CTL = (CLU->CLU1_CTL & ~(CLU_CLU1_CTL_CLKSEL | CLU_CLU1_CTL_CLKINV | CLU_CLU1_CTL_OEN | CLU_CLU1_CTL_OUTSEL)) | \
                        (CLU_InitStruct->CLU1_ClkSel << CLU_CLU1_CTL_CLKSEL_Pos) | (CLU_InitStruct->CLU1_ClkInv << CLU_CLU1_CTL_CLKINV_Pos) | \
                        (CLU_InitStruct->CLU1_PinOut << CLU_CLU1_CTL_OEN_Pos) | (CLU_InitStruct->CLU1_OutSel << CLU_CLU1_CTL_OUTSEL_Pos) ;

        /* Configurable Logic 1 Enable*/
        CLU->CTL |= CLEN0_C1EN__ENABLE;

    }

    /* CLU2 Configuration */
    if (CLU_InitStruct->CLU_Enable & CLEN0_C2EN__ENABLE)
    {
        /* Check parameters */
        assert_param(IS_CLUxMX_MXA_SELECTION(CLU_InitStruct->CLU2_MXA));
        assert_param(IS_CLUxMX_MXB_SELECTION(CLU_InitStruct->CLU2_MXB));
        assert_param(IS_CLUxMX_MXC_SELECTION(CLU_InitStruct->CLU2_MXC));
        assert_param(IS_CLUxMX_MXD_SELECTION(CLU_InitStruct->CLU2_MXD));
        assert_param(IS_CLUxFN_FUNCTION(CLU_InitStruct->CLU2_FN));
        assert_param(IS_CLUxCF_CLKSEL(CLU_InitStruct->CLU2_ClkSel));
        assert_param(IS_CLUxCF_CLKINV(CLU_InitStruct->CLU2_ClkInv));
        assert_param(IS_CLUxCF_OEN(CLU_InitStruct->CLU2_PinOut));
        assert_param(IS_CLUxCF_OUTSEL(CLU_InitStruct->CLU2_OutSel));

        /* Configurable Logic Unit 2 Multiplexer Configuration */
        CLU->CLU2_MX = (uint32_t)CLU_InitStruct->CLU2_MXA | (uint32_t)CLU_InitStruct->CLU2_MXB | (uint32_t)CLU_InitStruct->CLU2_MXC | (uint32_t)CLU_InitStruct->CLU2_MXD;
        CLU->CLU2_MX |= (uint32_t)0x1F << 16;

        /* Configurable Logic Unit 2 Function Select Configuration */
        CLU->CLU2_FN = (uint8_t)CLU_InitStruct->CLU2_FN;

        /* Configurable Logic Unit 2 Configuration */
        CLU->CLU2_CTL = (CLU->CLU2_CTL & ~(CLU_CLU2_CTL_CLKSEL | CLU_CLU2_CTL_CLKINV | CLU_CLU2_CTL_OEN | CLU_CLU2_CTL_OUTSEL)) | \
                        (CLU_InitStruct->CLU2_ClkSel << CLU_CLU2_CTL_CLKSEL_Pos) | (CLU_InitStruct->CLU2_ClkInv << CLU_CLU2_CTL_CLKINV_Pos) | \
                        (CLU_InitStruct->CLU2_PinOut << CLU_CLU2_CTL_OEN_Pos) | (CLU_InitStruct->CLU2_OutSel << CLU_CLU2_CTL_OUTSEL_Pos) ;

        /* Configurable Logic 2 Enable*/
        CLU->CTL |= CLEN0_C2EN__ENABLE;

    }

    /* CLU3 Configuration */
    if (CLU_InitStruct->CLU_Enable & CLEN0_C3EN__ENABLE)
    {
        /* Check parameters */
        assert_param(IS_CLUxMX_MXA_SELECTION(CLU_InitStruct->CLU3_MXA));
        assert_param(IS_CLUxMX_MXB_SELECTION(CLU_InitStruct->CLU3_MXB));
        assert_param(IS_CLUxMX_MXC_SELECTION(CLU_InitStruct->CLU3_MXC));
        assert_param(IS_CLUxMX_MXD_SELECTION(CLU_InitStruct->CLU3_MXD));
        assert_param(IS_CLUxFN_FUNCTION(CLU_InitStruct->CLU3_FN));
        assert_param(IS_CLUxCF_CLKSEL(CLU_InitStruct->CLU3_ClkSel));
        assert_param(IS_CLUxCF_CLKINV(CLU_InitStruct->CLU3_ClkInv));
        assert_param(IS_CLUxCF_OEN(CLU_InitStruct->CLU3_PinOut));
        assert_param(IS_CLUxCF_OUTSEL(CLU_InitStruct->CLU3_OutSel));

        /* Configurable Logic Unit 3 Multiplexer Configuration */
        CLU->CLU3_MX = (uint32_t)CLU_InitStruct->CLU3_MXA | (uint32_t)CLU_InitStruct->CLU3_MXB | (uint32_t)CLU_InitStruct->CLU3_MXC | (uint32_t)CLU_InitStruct->CLU3_MXD;
        CLU->CLU3_MX |= (uint32_t)0x1F << 16;

        /* Configurable Logic Unit 3 Function Select Configuration */
        CLU->CLU3_FN = (uint8_t)CLU_InitStruct->CLU3_FN;

        /* Configurable Logic Unit 3 Configuration */
        CLU->CLU3_CTL = (CLU->CLU3_CTL & ~(CLU_CLU3_CTL_CLKSEL | CLU_CLU3_CTL_CLKINV | CLU_CLU3_CTL_OEN | CLU_CLU3_CTL_OUTSEL)) | \
                        (CLU_InitStruct->CLU3_ClkSel << CLU_CLU3_CTL_CLKSEL_Pos) | (CLU_InitStruct->CLU3_ClkInv << CLU_CLU3_CTL_CLKINV_Pos) | \
                        (CLU_InitStruct->CLU3_PinOut << CLU_CLU3_CTL_OEN_Pos) | (CLU_InitStruct->CLU3_OutSel << CLU_CLU3_CTL_OUTSEL_Pos) ;

        /* Configurable Logic 3 Enable*/
        CLU->CTL |= CLEN0_C3EN__ENABLE;

    }

}

/**
  * @brief  Configurable Logic Unit 0 Multiplexer Input
  * @param  MultiplexerInputA: Specify the input source for Multiplexer A.
  *            @arg CLU0_MXA_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU0_MXA_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU0_MXA_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU0_MXA_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU0_MXA_TIM1_BRK      : TIM1_BRK
  *            @arg CLU0_MXA_TIM1_CC1      : TIM1_CC1
  *            @arg CLU0_MXA_TIM1_COM      : TIM1_COM
  *            @arg CLU0_MXA_TIM1_TRIG     : TIM1_TRIG
  *            @arg CLU0_MXA_TIM1_UP       : TIM1_UP
  *            @arg CLU0_MXA_COMP1_OUT     : COMP1_OUT
  *            @arg CLU0_MXA_COMP2_OUT     : COMP2_OUT
  *            @arg CLU0_MXA_COMP3_OUT     : COMP3_OUT
  *            @arg CLU0_MXA_PA0           : PA0
  *            @arg CLU0_MXA_PA1           : PA1
  *            @arg CLU0_MXA_PA2           : PA2
  *            @arg CLU0_MXA_PC10          : PC10
  * @param  MultiplexerInputB: Specify the input source for Multiplexer B.
  *            @arg CLU0_MXB_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU0_MXB_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU0_MXB_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU0_MXB_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU0_MXB_ADC1_EOC      : ADC1_EOC
  *            @arg CLU0_MXB_ADC1_AWD      : ADC1_AWD
  *            @arg CLU0_MXB_ADC1_EOSEQ    : ADC1_EOSEQ
  *            @arg CLU0_MXB_TIM6_UP       : TIM6_UP
  *            @arg CLU0_MXB_TIM14_CC1     : TIM14_CC1
  *            @arg CLU0_MXB_COMP1_OUT     : COMP1_OUT
  *            @arg CLU0_MXB_COMP2_OUT     : COMP2_OUT
  *            @arg CLU0_MXB_COMP3_OUT     : COMP3_OUT
  *            @arg CLU0_MXB_PA3           : PA3
  *            @arg CLU0_MXB_PA4           : PA4
  *            @arg CLU0_MXB_PA5           : PA5
  *            @arg CLU0_MXB_PB1           : PB1
  * @param  MultiplexerInputC: Specify the input source for Multiplexer C.
  *            @arg CLU0_MXC_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU0_MXC_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU0_MXC_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU0_MXC_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU0_MXC_COMP1_OUT     : COMP1_OUT
  *            @arg CLU0_MXC_COMP2_OUT     : COMP2_OUT
  *            @arg CLU0_MXC_COMP3_OUT     : COMP3_OUT
  *            @arg CLU0_MXC_TIM14_UP      : TIM14_UP
  *            @arg CLU0_MXC_TIM15_CC1     : TIM15_CC1
  *            @arg CLU0_MXC_TIM15_UP      : TIM15_UP
  *            @arg CLU0_MXC_TIM2_TRIG     : TIM2_TRIG
  *            @arg CLU0_MXC_TIM16_UP      : TIM16_UP
  *            @arg CLU0_MXC_PA6           : PA6
  *            @arg CLU0_MXC_PA7           : PA7
  *            @arg CLU0_MXC_PA11          : PA11
  *            @arg CLU0_MXC_PC11          : PC11
  * @param  MultiplexerInputD: Specify the input source for Multiplexer D.
  *            @arg CLU0_MXD_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU0_MXD_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU0_MXD_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU0_MXD_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU0_MXD_COMP1_OUT     : COMP1_OUT
  *            @arg CLU0_MXD_COMP2_OUT     : COMP2_OUT
  *            @arg CLU0_MXD_RTC_OUT       : RTC_OUT
  *            @arg CLU0_MXD_TIM16_COM     : TIM16_COM
  *            @arg CLU0_MXD_TIM1_UP       : TIM1_UP
  *            @arg CLU0_MXD_TIM2_CC1      : TIM2_CC1
  *            @arg CLU0_MXD_PA12          : PA12
  *            @arg CLU0_MXD_PA13          : PA13
  *            @arg CLU0_MXD_PA14          : PA14
  *            @arg CLU0_MXD_PC12          : PC12
  * @retval None
  */
void CLU0_MultiplexerInputConfig(uint32_t MultiplexerInputA, uint32_t MultiplexerInputB, uint32_t MultiplexerInputC, uint32_t MultiplexerInputD)
{
    /* Check parameters */
    assert_param(IS_CLU0_MXA_INPUT(MultiplexerInputA));
    assert_param(IS_CLU0_MXB_INPUT(MultiplexerInputB));
    assert_param(IS_CLU0_MXC_INPUT(MultiplexerInputC));
    assert_param(IS_CLU0_MXD_INPUT(MultiplexerInputD));

    /* Clear MXA, MXB, MXC, MXD bits */
    CLU->CLU0_MX &= (uint32_t)(~(CLU_CLU0_MX_MXA | CLU_CLU0_MX_MXB | CLU_CLU0_MX_MXC | CLU_CLU0_MX_MXD));

    /* Set MXA, MXB, MXC, MXD bits according to MultiplexerInputA, MultiplexerInputB, MultiplexerInputC, MultiplexerInputD value */
    CLU->CLU0_MX |= (uint32_t)(MultiplexerInputA | MultiplexerInputB | MultiplexerInputC | MultiplexerInputD);
}

/**
  * @brief  Configurable Logic Unit 1 Multiplexer Input
  * @param  MultiplexerInputA: Specify the input source for Multiplexer A.
  *            @arg CLU1_MXA_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU1_MXA_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU1_MXA_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU1_MXA_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU1_MXA_TIM1_BRK      : TIM1_BRK
  *            @arg CLU1_MXA_TIM1_CC1      : TIM1_CC1
  *            @arg CLU1_MXA_TIM1_COM      : TIM1_COM
  *            @arg CLU1_MXA_TIM1_TRIG     : TIM1_TRIG
  *            @arg CLU1_MXA_TIM1_UP       : TIM1_UP
  *            @arg CLU1_MXA_COMP1_OUT     : COMP1_OUT
  *            @arg CLU1_MXA_COMP2_OUT     : COMP2_OUT
  *            @arg CLU1_MXA_COMP3_OUT     : COMP3_OUT
  *            @arg CLU1_MXA_PA3           : PA3
  *            @arg CLU1_MXA_PA4           : PA4
  *            @arg CLU1_MXA_PA5           : PA5
  *            @arg CLU1_MXA_PC10          : PC10
  * @param  MultiplexerInputB: Specify the input source for Multiplexer B.
  *            @arg CLU1_MXB_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU1_MXB_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU1_MXB_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU1_MXB_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU1_MXB_ADC1_EOC      : ADC1_EOC
  *            @arg CLU1_MXB_ADC1_AWD      : ADC1_AWD
  *            @arg CLU1_MXB_ADC1_EOSEQ    : ADC1_EOSEQ
  *            @arg CLU1_MXB_TIM6_UP       : TIM6_UP
  *            @arg CLU1_MXB_TIM14_CC1     : TIM14_CC1
  *            @arg CLU1_MXB_COMP1_OUT     : COMP1_OUT
  *            @arg CLU1_MXB_COMP2_OUT     : COMP2_OUT
  *            @arg CLU1_MXB_COMP3_OUT     : COMP3_OUT
  *            @arg CLU1_MXB_PA0           : PA0
  *            @arg CLU1_MXB_PA1           : PA1
  *            @arg CLU1_MXB_PA2           : PA2
  *            @arg CLU1_MXB_PB1           : PB1
  * @param  MultiplexerInputC: Specify the input source for Multiplexer C.
  *            @arg CLU1_MXC_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU1_MXC_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU1_MXC_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU1_MXC_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU1_MXC_COMP1_OUT     : COMP1_OUT
  *            @arg CLU1_MXC_COMP2_OUT     : COMP2_OUT
  *            @arg CLU1_MXC_COMP3_OUT     : COMP3_OUT
  *            @arg CLU1_MXC_TIM14_UP      : TIM14_UP
  *            @arg CLU1_MXC_TIM15_CC1     : TIM15_CC1
  *            @arg CLU1_MXC_TIM15_UP      : TIM15_UP
  *            @arg CLU1_MXC_TIM2_TRIG     : TIM2_TRIG
  *            @arg CLU1_MXC_TIM16_UP      : TIM16_UP
  *            @arg CLU1_MXC_PA12          : PA12
  *            @arg CLU1_MXC_PA13          : PA13
  *            @arg CLU1_MXC_PA14          : PA14
  *            @arg CLU1_MXC_PC11          : PC11
  * @param  MultiplexerInputD: Specify the input source for Multiplexer D.
  *            @arg CLU1_MXD_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU1_MXD_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU1_MXD_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU1_MXD_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU1_MXD_COMP1_OUT     : COMP1_OUT
  *            @arg CLU1_MXD_COMP2_OUT     : COMP2_OUT
  *            @arg CLU1_MXD_RTC_OUT       : RTC_OUT
  *            @arg CLU1_MXD_TIM16_COM     : TIM16_COM
  *            @arg CLU1_MXD_TIM1_UP       : TIM1_UP
  *            @arg CLU1_MXD_TIM2_CC1      : TIM2_CC1
  *            @arg CLU1_MXD_PA6           : PA6
  *            @arg CLU1_MXD_PA7           : PA7
  *            @arg CLU1_MXD_PA11          : PA11
  *            @arg CLU1_MXD_PC12          : PC12
  * @retval None
  */
void CLU1_MultiplexerInputConfig(uint32_t MultiplexerInputA, uint32_t MultiplexerInputB, uint32_t MultiplexerInputC, uint32_t MultiplexerInputD)
{
    /* Check parameters */
    assert_param(IS_CLU1_MXA_INPUT(MultiplexerInputA));
    assert_param(IS_CLU1_MXB_INPUT(MultiplexerInputB));
    assert_param(IS_CLU1_MXC_INPUT(MultiplexerInputC));
    assert_param(IS_CLU1_MXD_INPUT(MultiplexerInputD));

    /* Clear MXA, MXB, MXC, MXD bits */
    CLU->CLU1_MX &= (uint32_t)(~(CLU_CLU1_MX_MXA | CLU_CLU1_MX_MXB | CLU_CLU1_MX_MXC | CLU_CLU1_MX_MXD));

    /* Set MXA, MXB, MXC, MXD bits according to MultiplexerInputA, MultiplexerInputB, MultiplexerInputC, MultiplexerInputD value */
    CLU->CLU1_MX |= (uint32_t)(MultiplexerInputA | MultiplexerInputB | MultiplexerInputC | MultiplexerInputD);
}

/**
  * @brief  Configurable Logic Unit 2 Multiplexer Input
  * @param  MultiplexerInputA: Specify the input source for Multiplexer A.
  *            @arg CLU2_MXA_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU2_MXA_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU2_MXA_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU2_MXA_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU2_MXA_TIM1_BRK      : TIM1_BRK
  *            @arg CLU2_MXA_TIM1_CC1      : TIM1_CC1
  *            @arg CLU2_MXA_TIM1_COM      : TIM1_COM
  *            @arg CLU2_MXA_TIM1_TRIG     : TIM1_TRIG
  *            @arg CLU2_MXA_TIM1_UP       : TIM1_UP
  *            @arg CLU2_MXA_COMP1_OUT     : COMP1_OUT
  *            @arg CLU2_MXA_COMP2_OUT     : COMP2_OUT
  *            @arg CLU2_MXA_COMP3_OUT     : COMP3_OUT
  *            @arg CLU2_MXA_PA6           : PA6
  *            @arg CLU2_MXA_PA7           : PA7
  *            @arg CLU2_MXA_PA11          : PA11
  *            @arg CLU2_MXA_PC10          : PC10
  * @param  MultiplexerInputB: Specify the input source for Multiplexer B.
  *            @arg CLU2_MXB_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU2_MXB_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU2_MXB_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU2_MXB_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU2_MXB_ADC1_EOC      : ADC1_EOC
  *            @arg CLU2_MXB_ADC1_AWD      : ADC1_AWD
  *            @arg CLU2_MXB_ADC1_EOSEQ    : ADC1_EOSEQ
  *            @arg CLU2_MXB_TIM6_UP       : TIM6_UP
  *            @arg CLU2_MXB_TIM14_CC1     : TIM14_CC1
  *            @arg CLU2_MXB_COMP1_OUT     : COMP1_OUT
  *            @arg CLU2_MXB_COMP2_OUT     : COMP2_OUT
  *            @arg CLU2_MXB_COMP3_OUT     : COMP3_OUT
  *            @arg CLU2_MXB_PA3           : PA3
  *            @arg CLU2_MXB_PA4           : PA4
  *            @arg CLU2_MXB_PA5           : PA5
  *            @arg CLU2_MXB_PB1           : PB1
  * @param  MultiplexerInputC: Specify the input source for Multiplexer C.
  *            @arg CLU2_MXC_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU2_MXC_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU2_MXC_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU2_MXC_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU2_MXC_COMP1_OUT     : COMP1_OUT
  *            @arg CLU2_MXC_COMP2_OUT     : COMP2_OUT
  *            @arg CLU2_MXC_COMP3_OUT     : COMP3_OUT
  *            @arg CLU2_MXC_TIM14_UP      : TIM14_UP
  *            @arg CLU2_MXC_TIM15_CC1     : TIM15_CC1
  *            @arg CLU2_MXC_TIM15_UP      : TIM15_UP
  *            @arg CLU2_MXC_TIM2_TRIG     : TIM2_TRIG
  *            @arg CLU2_MXC_TIM16_UP      : TIM16_UP
  *            @arg CLU2_MXC_PA0           : PA0
  *            @arg CLU2_MXC_PA1           : PA1
  *            @arg CLU2_MXC_PA2           : PA2
  *            @arg CLU2_MXC_PC11          : PC11
  * @param  MultiplexerInputD: Specify the input source for Multiplexer D.
  *            @arg CLU2_MXD_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU2_MXD_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU2_MXD_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU2_MXD_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU2_MXD_COMP1_OUT     : COMP1_OUT
  *            @arg CLU2_MXD_COMP2_OUT     : COMP2_OUT
  *            @arg CLU2_MXD_RTC_OUT       : RTC_OUT
  *            @arg CLU2_MXD_TIM16_COM     : TIM16_COM
  *            @arg CLU2_MXD_TIM1_UP       : TIM1_UP
  *            @arg CLU2_MXD_TIM2_CC1      : TIM2_CC1
  *            @arg CLU2_MXD_PA12          : PA12
  *            @arg CLU2_MXD_PA13          : PA13
  *            @arg CLU2_MXD_PA14          : PA14
  *            @arg CLU2_MXD_PC12          : PC12
  * @retval None
  */
void CLU2_MultiplexerInputConfig(uint32_t MultiplexerInputA, uint32_t MultiplexerInputB, uint32_t MultiplexerInputC, uint32_t MultiplexerInputD)
{
    /* Check parameters */
    assert_param(IS_CLU2_MXA_INPUT(MultiplexerInputA));
    assert_param(IS_CLU2_MXB_INPUT(MultiplexerInputB));
    assert_param(IS_CLU2_MXC_INPUT(MultiplexerInputC));
    assert_param(IS_CLU2_MXD_INPUT(MultiplexerInputD));

    /* Clear MXA, MXB, MXC, MXD bits */
    CLU->CLU2_MX &= (uint32_t)(~(CLU_CLU2_MX_MXA | CLU_CLU2_MX_MXB | CLU_CLU2_MX_MXC | CLU_CLU2_MX_MXD));

    /* Set MXA, MXB, MXC, MXD bits according to MultiplexerInputA, MultiplexerInputB, MultiplexerInputC, MultiplexerInputD value */
    CLU->CLU2_MX |= (uint32_t)(MultiplexerInputA | MultiplexerInputB | MultiplexerInputC | MultiplexerInputD);
}

/**
  * @brief  Configurable Logic Unit 3 Multiplexer Input
  * @param  MultiplexerInputA: Specify the input source for Multiplexer A.
  *            @arg CLU3_MXA_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU3_MXA_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU3_MXA_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU3_MXA_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU3_MXA_TIM1_BRK      : TIM1_BRK
  *            @arg CLU3_MXA_TIM1_CC1      : TIM1_CC1
  *            @arg CLU3_MXA_TIM1_COM      : TIM1_COM
  *            @arg CLU3_MXA_TIM1_TRIG     : TIM1_TRIG
  *            @arg CLU3_MXA_TIM1_UP       : TIM1_UP
  *            @arg CLU3_MXA_COMP1_OUT     : COMP1_OUT
  *            @arg CLU3_MXA_COMP2_OUT     : COMP2_OUT
  *            @arg CLU3_MXA_COMP3_OUT     : COMP3_OUT
  *            @arg CLU3_MXA_PA12          : PA12
  *            @arg CLU3_MXA_PA13          : PA13
  *            @arg CLU3_MXA_PA14          : PA14
  *            @arg CLU3_MXA_PC10          : PC10
  * @param  MultiplexerInputB: Specify the input source for Multiplexer B.
  *            @arg CLU3_MXB_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU3_MXB_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU3_MXB_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU3_MXB_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU3_MXB_ADC1_EOC      : ADC1_EOC
  *            @arg CLU3_MXB_ADC1_AWD      : ADC1_AWD
  *            @arg CLU3_MXB_ADC1_EOSEQ    : ADC1_EOSEQ
  *            @arg CLU3_MXB_TIM6_UP       : TIM6_UP
  *            @arg CLU3_MXB_TIM14_CC1     : TIM14_CC1
  *            @arg CLU3_MXB_COMP1_OUT     : COMP1_OUT
  *            @arg CLU3_MXB_COMP2_OUT     : COMP2_OUT
  *            @arg CLU3_MXB_COMP3_OUT     : COMP3_OUT
  *            @arg CLU3_MXB_PA6           : PA6
  *            @arg CLU3_MXB_PA7           : PA7
  *            @arg CLU3_MXB_PA11          : PA11
  *            @arg CLU3_MXB_PB1           : PB1
  * @param  MultiplexerInputC: Specify the input source for Multiplexer C.
  *            @arg CLU3_MXC_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU3_MXC_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU3_MXC_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU3_MXC_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU3_MXC_COMP1_OUT     : COMP1_OUT
  *            @arg CLU3_MXC_COMP2_OUT     : COMP2_OUT
  *            @arg CLU3_MXC_COMP3_OUT     : COMP3_OUT
  *            @arg CLU3_MXC_TIM14_UP      : TIM14_UP
  *            @arg CLU3_MXC_TIM15_CC1     : TIM15_CC1
  *            @arg CLU3_MXC_TIM15_UP      : TIM15_UP
  *            @arg CLU3_MXC_TIM2_TRIG     : TIM2_TRIG
  *            @arg CLU3_MXC_TIM16_UP      : TIM16_UP
  *            @arg CLU3_MXC_PA3           : PA3
  *            @arg CLU3_MXC_PA4           : PA4
  *            @arg CLU3_MXC_PA5           : PA5
  *            @arg CLU3_MXC_PC11          : PC11
  * @param  MultiplexerInputD: Specify the input source for Multiplexer D.
  *            @arg CLU3_MXD_CLU0_OUT_INTER: CLU0_OUT_INTER
  *            @arg CLU3_MXD_CLU1_OUT_INTER: CLU1_OUT_INTER
  *            @arg CLU3_MXD_CLU2_OUT_INTER: CLU2_OUT_INTER
  *            @arg CLU3_MXD_CLU3_OUT_INTER: CLU3_OUT_INTER
  *            @arg CLU3_MXD_COMP1_OUT     : COMP1_OUT
  *            @arg CLU3_MXD_COMP2_OUT     : COMP2_OUT
  *            @arg CLU3_MXD_RTC_OUT       : RTC_OUT
  *            @arg CLU3_MXD_TIM16_COM     : TIM16_COM
  *            @arg CLU3_MXD_TIM1_UP       : TIM1_UP
  *            @arg CLU3_MXD_TIM2_CC1      : TIM2_CC1
  *            @arg CLU3_MXD_PA0           : PA0
  *            @arg CLU3_MXD_PA1           : PA1
  *            @arg CLU3_MXD_PA2           : PA2
  *            @arg CLU3_MXD_PC12          : PC12
  * @retval None
  */
void CLU3_MultiplexerInputConfig(uint32_t MultiplexerInputA, uint32_t MultiplexerInputB, uint32_t MultiplexerInputC, uint32_t MultiplexerInputD)
{
    /* Check parameters */
    assert_param(IS_CLU3_MXA_INPUT(MultiplexerInputA));
    assert_param(IS_CLU3_MXB_INPUT(MultiplexerInputB));
    assert_param(IS_CLU3_MXC_INPUT(MultiplexerInputC));
    assert_param(IS_CLU3_MXD_INPUT(MultiplexerInputD));

    /* Clear MXA, MXB, MXC, MXD bits */
    CLU->CLU3_MX &= (uint32_t)(~(CLU_CLU3_MX_MXA | CLU_CLU3_MX_MXB | CLU_CLU3_MX_MXC | CLU_CLU3_MX_MXD));

    /* Set MXA, MXB, MXC, MXD bits according to MultiplexerInputA, MultiplexerInputB, MultiplexerInputC, MultiplexerInputD value */
    CLU->CLU3_MX |= (uint32_t)(MultiplexerInputA | MultiplexerInputB | MultiplexerInputC | MultiplexerInputD);
}

/**
  * @brief  Enable input channel of CLUx
  * @param  CLUx: Select the CLU(CLU0,CLU1,CLU2,CLU3) to be configured.
  * @param  inputchan: This parameter can be one of the following values:
  *            @arg CLUxMX_InputChannel__MXA
  *            @arg CLUxMX_InputChannel__MXB
  *            @arg CLUxMX_InputChannel__MXC
  *            @arg CLUxMX_InputChannel__MXD
  *            @arg CLUxMX_InputChannel__CARRY_IN
  * @param  NewState: new state of the oversampling.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval output status
  */
void CLU_InputChannelEN(CLUx_Selecte_TypeDef CLUx, CLUxMX_InputChannel_Typedef inputchan, FunctionalState NewState)
{
    /* Check parameters */
    assert_param(IS_CLU_ALL_CLUx(CLUx));
    assert_param(IS_CLUxMX_InputChannel(inputchan));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (CLUx == CLU0)
    {
        if (NewState != DISABLE)
        {
            CLU->CLU0_MX |= (uint32_t)0x10000 << inputchan;
        }
        else
        {
            CLU->CLU0_MX &= ~(uint32_t)((uint32_t)0x10000 << inputchan);
        }
    }
    else if (CLUx == CLU1)
    {
        if (NewState != DISABLE)
        {
            CLU->CLU1_MX |= (uint32_t)0x10000 << inputchan;
        }
        else
        {
            CLU->CLU1_MX &= ~(uint32_t)((uint32_t)0x10000 << inputchan);
        }
    }
    else if (CLUx == CLU2)
    {
        if (NewState != DISABLE)
        {
            CLU->CLU2_MX |= (uint32_t)0x10000 << inputchan;
        }
        else
        {
            CLU->CLU2_MX &= ~(uint32_t)((uint32_t)0x10000 << inputchan);
        }
    }
    else
    {
        if (CLUx == CLU3)
        {
            if (NewState != DISABLE)
            {
                CLU->CLU3_MX |= (uint32_t)0x10000 << inputchan;
            }
            else
            {
                CLU->CLU3_MX &= ~(uint32_t)((uint32_t)0x10000 << inputchan);
            }
        }
    }
}



/**
  * @brief  Specify the clock source of the CLU D flip-flop,and whether
  *         to Invert the clock
  * @param  CLUx: Select the CLU(CLU0,CLU1,CLU2,CLU3) to be configured.
  * @param  clock: CLU D flip-flop Clock Selection.
  * @param  clockInvert: CLU D flip-flop Clock Invert.
  * @retval None
  */
void CLU_InitDFlipflop(CLUx_Selecte_TypeDef CLUx, CLUxCF_CLKSEL_TypeDef clock, CLUxCF_CLKINV_TypeDef clockInvert)
{
    /* Check parameters */
    assert_param(IS_CLU_ALL_CLUx(CLUx));
    assert_param(IS_CLUxCF_CLKSEL(clock));
    assert_param(IS_CLUxCF_CLKINV(clockInvert));

    if (CLUx == CLU0)
    {
        CLU->CLU0_CTL &= ~CLU_CLU0_CTL_CLKSEL;
        CLU->CLU0_CTL &= ~CLU_CLU0_CTL_CLKINV;
        CLU->CLU0_CTL |= ((uint32_t)clock) << CLU_CLU0_CTL_CLKSEL_Pos;
        CLU->CLU0_CTL |= ((uint32_t)clockInvert) << CLU_CLU0_CTL_CLKINV_Pos;
    }
    else if (CLUx == CLU1)
    {
        CLU->CLU1_CTL &= ~CLU_CLU1_CTL_CLKSEL;
        CLU->CLU1_CTL &= ~CLU_CLU1_CTL_CLKINV;
        CLU->CLU1_CTL |= ((uint32_t)clock) << CLU_CLU1_CTL_CLKSEL_Pos;
        CLU->CLU1_CTL |= ((uint32_t)clockInvert) << CLU_CLU1_CTL_CLKINV_Pos;
    }
    else if (CLUx == CLU2)
    {
        CLU->CLU2_CTL &= ~CLU_CLU2_CTL_CLKSEL;
        CLU->CLU2_CTL &= ~CLU_CLU2_CTL_CLKINV;
        CLU->CLU2_CTL |= ((uint32_t)clock) << CLU_CLU2_CTL_CLKSEL_Pos;
        CLU->CLU2_CTL |= ((uint32_t)clockInvert) << CLU_CLU2_CTL_CLKINV_Pos;
    }
    else
    {
        if (CLUx == CLU3)
        {
            CLU->CLU3_CTL &= ~CLU_CLU3_CTL_CLKSEL;
            CLU->CLU3_CTL &= ~CLU_CLU3_CTL_CLKINV;
            CLU->CLU3_CTL |= ((uint32_t)clock) << CLU_CLU3_CTL_CLKSEL_Pos;
            CLU->CLU3_CTL |= ((uint32_t)clockInvert) << CLU_CLU3_CTL_CLKINV_Pos;
        }
    }

}

/**
  * @brief  Reset D flip-flop.
  * @param  CLUx: Select the CLU(CLU0,CLU1,CLU2,CLU3) to be configured.
  * @retval None
  */
void CLU_ResetDFlipflop(CLUx_Selecte_TypeDef CLUx)
{
    /* Check parameters */
    assert_param(IS_CLU_ALL_CLUx(CLUx));

    if (CLUx == CLU0)
    {
        CLU->CLU0_CTL |= CLU_CLU0_CTL_RST;
    }
    else if (CLUx == CLU1)
    {
        CLU->CLU1_CTL |= CLU_CLU1_CTL_RST;
    }
    else if (CLUx == CLU2)
    {
        CLU->CLU2_CTL |= CLU_CLU2_CTL_RST;
    }
    else
    {
        if (CLUx == CLU3)
        {
            CLU->CLU3_CTL |= CLU_CLU3_CTL_RST;
        }
    }
}

/**
  * @brief  Set D flip-flop.
  * @param  CLUx: Select the CLU(CLU0,CLU1,CLU2,CLU3) to be configured.
  * @retval None
  */
void CLU_SetDFlipflop(CLUx_Selecte_TypeDef CLUx)
{
    /* Check parameters */
    assert_param(IS_CLU_ALL_CLUx(CLUx));

    if (CLUx == CLU0)
    {
        CLU->CLU0_CTL |= CLU_CLU0_CTL_SET;
    }
    else if (CLUx == CLU1)
    {
        CLU->CLU1_CTL |= CLU_CLU1_CTL_SET;
    }
    else if (CLUx == CLU2)
    {
        CLU->CLU2_CTL |= CLU_CLU2_CTL_SET;
    }
    else
    {
        if (CLUx == CLU3)
        {
            CLU->CLU3_CTL |= CLU_CLU3_CTL_SET;
        }
    }
}

/**
  * @brief  Configure CLU output function.
  * @param  CLUx: Select the CLU(CLU0,CLU1,CLU2,CLU3) to be configured.
  * @param  function: CLU Look-Up-Table function select.
  * @retval None
  */
void CLU_SetOutputFunction(CLUx_Selecte_TypeDef CLUx, CLUxFN_Function_TypeDef function)
{
    /* Check parameters */
    assert_param(IS_CLU_ALL_CLUx(CLUx));
    assert_param(IS_CLUxFN_FUNCTION(function));

    if (CLUx == CLU0)
    {
        CLU->CLU0_FN = function;
    }
    else if (CLUx == CLU1)
    {
        CLU->CLU1_FN = function;
    }
    else if (CLUx == CLU2)
    {
        CLU->CLU2_FN = function;
    }
    else
    {
        if (CLUx == CLU3)
        {
            CLU->CLU3_FN = function;
        }
    }

}

/**
  * @brief  Enbale CLU
  * @param  CLUx: Select CLU enable flag
  * @param  NewState: Select enable or disable
  * @retval none
  */
void CLU_Cmd(CLUx_Selecte_TypeDef CLUx, FunctionalState NewState)
{
    /* Check parameters */
    assert_param(IS_CLU_ALL_CLUx(CLUx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        CLU->CTL |= (uint32_t)((uint32_t)1 << CLUx);
    }
    else
    {
        CLU->CTL &= ~((uint32_t)((uint32_t)1 << CLUx));
    }
}

/**
  * @brief  Configure CLU output mode
  * @param  CLUx: Select the CLU(CLU0,CLU1,CLU2,CLU3) to be configured.
  * @param  OutSel: Output select(LUT or DFF)
  * @retval none
  */
void CLU_OutputSelection(CLUx_Selecte_TypeDef CLUx, CLUxCF_OUTSEL_TypeDef OutSel)
{
    /* Check parameters */
    assert_param(IS_CLU_ALL_CLUx(CLUx));
    assert_param(IS_CLUxCF_OUTSEL(OutSel));

    if (CLUx == CLU0)
    {
        CLU->CLU0_CTL &= ~CLU_CLU0_CTL_OUTSEL;
        CLU->CLU0_CTL |= ((uint32_t)OutSel) << CLU_CLU0_CTL_OUTSEL_Pos;
    }
    else if (CLUx == CLU1)
    {
        CLU->CLU1_CTL &= ~CLU_CLU1_CTL_OUTSEL;
        CLU->CLU1_CTL |= ((uint32_t)OutSel) << CLU_CLU1_CTL_OUTSEL_Pos;
    }
    else if (CLUx == CLU2)
    {
        CLU->CLU2_CTL &= ~CLU_CLU2_CTL_OUTSEL;
        CLU->CLU2_CTL |= ((uint32_t)OutSel) << CLU_CLU2_CTL_OUTSEL_Pos;
    }
    else
    {
        if (CLUx == CLU3)
        {
            CLU->CLU3_CTL &= ~CLU_CLU3_CTL_OUTSEL;
            CLU->CLU3_CTL |= ((uint32_t)OutSel) << CLU_CLU3_CTL_OUTSEL_Pos;
        }
    }
}

/**
  * @brief  Configurate CLU pin output
  * @param  CLUx: Select the CLU(CLU0,CLU1,CLU2,CLU3) to be configured.
  * @param  PinOut: CLU pin output enable.
  * @retval none.
  */
void CLU_EnablePinOutput(CLUx_Selecte_TypeDef CLUx, CLUxCF_OEN_TypeDef PinOut)
{
    /* Check parameters */
    assert_param(IS_CLU_ALL_CLUx(CLUx));
    assert_param(IS_CLUxCF_OEN(PinOut));

    if (CLUx == CLU0)
    {
        CLU->CLU0_CTL &= ~CLU_CLU0_CTL_OEN;
        CLU->CLU0_CTL |= ((uint32_t)PinOut) << CLU_CLU0_CTL_OEN_Pos;
    }
    else if (CLUx == CLU1)
    {
        CLU->CLU1_CTL &= ~CLU_CLU1_CTL_OEN;
        CLU->CLU1_CTL |= ((uint32_t)PinOut) << CLU_CLU1_CTL_OEN_Pos;
    }
    else if (CLUx == CLU2)
    {
        CLU->CLU2_CTL &= ~CLU_CLU2_CTL_OEN;
        CLU->CLU2_CTL |= ((uint32_t)PinOut) << CLU_CLU2_CTL_OEN_Pos;
    }
    else
    {
        if (CLUx == CLU3)
        {
            CLU->CLU3_CTL &= ~CLU_CLU3_CTL_OEN;
            CLU->CLU3_CTL |= ((uint32_t)PinOut) << CLU_CLU3_CTL_OEN_Pos;
        }
    }
}

/**
  * @brief  Config trigger source of ADC work from CLU.
  * @param  CLUx: Select the CLU(CLU0,CLU1,CLU2,CLU3) to be configured.
  * @retval None.
  */
void CLU_TriggADCToWork(CLUx_Selecte_TypeDef CLUx)
{
    /* Check parameters */
    assert_param(IS_CLU_ALL_CLUx(CLUx));

    /* Set trigger source of ADC work from CLU */
    CLU->CTL &= ~(uint32_t)CLU_CTL_TO_ADC_SEL;
    CLU->CTL |= (uint32_t)CLUx << CLU_CTL_TO_ADC_SEL_Pos;
}

/**
  * @brief  Config trigger source of DAC work from CLU.
  * @param  CLUx: Select the CLU(CLU0,CLU1,CLU2,CLU3) to be configured.
  * @retval None.
  */
void CLU_TriggDACToWork(CLUx_Selecte_TypeDef CLUx)
{
    /* Check parameters */
    assert_param(IS_CLU_ALL_CLUx(CLUx));

    /* Set trigger source of DAC work from CLU */
    CLU->CTL &= ~(uint32_t)CLU_CTL_TO_DAC_SEL;
    CLU->CTL |= (uint32_t)CLUx << CLU_CTL_TO_DAC_SEL_Pos;
}

/**
  * @brief  Get CLU output status
  * @param  CLUx: Select the CLU(CLU0,CLU1,CLU2,CLU3) to be configured.
  * @retval output status
  */
FlagStatus CLU_GetOutput(CLUx_Selecte_TypeDef CLUx)
{
    FlagStatus bitstatus = RESET;

    /* Check parameters */
    assert_param(IS_CLU_ALL_CLUx(CLUx));

    if (CLUx == CLU0)
    {
        if ((CLU->OUT_SYNC & CLU_OUT_SYNC_CLU0_OUT_SYNC) != RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else if (CLUx == CLU1)
    {
        if ((CLU->OUT_SYNC & CLU_OUT_SYNC_CLU1_OUT_SYNC) != RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else if (CLUx == CLU2)
    {
        if ((CLU->OUT_SYNC & CLU_OUT_SYNC_CLU2_OUT_SYNC) != RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else
    {
        if (CLUx == CLU3)
        {
            if ((CLU->OUT_SYNC & CLU_OUT_SYNC_CLU3_OUT_SYNC) != RESET)
            {
                bitstatus = SET;
            }
            else
            {
                bitstatus = RESET;
            }
        }
    }

    return bitstatus;
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


