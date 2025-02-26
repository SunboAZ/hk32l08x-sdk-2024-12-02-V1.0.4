/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_gpio.c
* @brief:     GPIO initialization and configuration
* @author:    AE Team
* @version:   V1.0.0/2024-01-08
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_gpio.h"
#include "hk32l0xx_rcc.h"


/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup GPIO  GPIO
  * @brief GPIO driver modules
  * @{
  */

/** @defgroup GPIO_Private_Functions    GPIO_Private_Functions
  * @{
  */

/** @defgroup GPIO_Group1 Initialization and Configuration
 *  @brief   Initialization and Configuration
 *
@verbatim
 ===============================================================================
                    ##### Initialization and Configuration #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the GPIOx peripheral registers to their default reset
  *         values.
  * @param  GPIOx: where x can be (A, B, C, D, F) to select the GPIO peripheral.
  * @retval None
  */
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    if (GPIOx == GPIOA)
    {
        RCC_AHBPeriphResetCmd(RCC_AHBENR_IOPAEN, ENABLE);
        RCC_AHBPeriphResetCmd(RCC_AHBENR_IOPAEN, DISABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_AHBPeriphResetCmd(RCC_AHBENR_IOPBEN, ENABLE);
        RCC_AHBPeriphResetCmd(RCC_AHBENR_IOPBEN, DISABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_AHBPeriphResetCmd(RCC_AHBENR_IOPCEN, ENABLE);
        RCC_AHBPeriphResetCmd(RCC_AHBENR_IOPCEN, DISABLE);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_AHBPeriphResetCmd(RCC_AHBENR_IOPDEN, ENABLE);
        RCC_AHBPeriphResetCmd(RCC_AHBENR_IOPDEN, DISABLE);
    }
    else
    {
        if (GPIOx == GPIOF)
        {
            RCC_AHBPeriphResetCmd(RCC_AHBENR_IOPFEN, ENABLE);
            RCC_AHBPeriphResetCmd(RCC_AHBENR_IOPFEN, DISABLE);
        }
    }
}

/**
  * @brief  Initializes the GPIOx peripheral according to the specified
  *         parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A, B, C, D, F) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    uint32_t pinpos = 0x00, pos = 0x00, currentpin = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
    assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
    assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

    /*-------------------------- Configure the port pins -----------------------*/
    /*-- GPIO Mode Configuration --*/
    for (pinpos = 0x00; pinpos < 0x10; pinpos++)
    {
        pos = ((uint32_t)0x01) << pinpos;

        /* Get the port pins position */
        currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

        if (currentpin == pos)
        {
            if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
            {
                /* Check Speed mode parameters */
                assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));

                /* Speed mode configuration */
                GPIOx->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0 << (pinpos * 2));
                GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

                /* Check Output mode parameters */
                assert_param(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));

                /* Output mode configuration */
                GPIOx->OTYPER &= ~((GPIO_OTYPER_OT0) << ((uint16_t)pinpos));
                GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
            }

            GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));

            GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

            /* Pull-up Pull down resistor configuration */
            GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPD0 << ((uint16_t)pinpos * 2));
            GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
        }
    }

    /* config schmit*/
    if (GPIO_InitStruct->GPIO_Schmit == GPIO_Schmit_Disable)
    {
        GPIOx->IOSR |= (GPIO_InitStruct->GPIO_Pin);
    }
    else
    {
        GPIOx->IOSR &= ~(GPIO_InitStruct->GPIO_Pin);
    }

}

/**
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
    /* Reset GPIO init structure parameters values */
    GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
    GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct->GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL;
}

/**
  * @brief  Locks GPIO Pins configuration registers.
  * @note   The locked registers are GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR,
  *         GPIOx_PUPDR, GPIOx_AFRL and GPIOx_AFRH.
  * @note   The configuration of the locked GPIO pins can no longer be modified
  *         until the next device reset.
  * @param  GPIOx: where x can be (A, B, C, D, F) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    __IO uint32_t tmp = 0x00010000;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    tmp |= GPIO_Pin;
    /* Set LCKK bit */
    GPIOx->LCKR = tmp;
    /* Reset LCKK bit */
    GPIOx->LCKR = GPIO_Pin;
    /* Set LCKK bit */
    GPIOx->LCKR = tmp;
    /* Read LCKK bit */
    tmp = GPIOx->LCKR;
    /* Read LCKK bit */
    tmp = GPIOx->LCKR;
}

/**
  * @}
  */

/** @defgroup GPIO_Group2 GPIO Read and Write
 *  @brief   GPIO Read and Write
 *
@verbatim
 ===============================================================================
                      ##### GPIO Read and Write #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Reads the specified input port pin bit.
  * @param  GPIOx: where x can be (A, B, C, D, F) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to read.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOF
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }

    return bitstatus;
}

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A, B, C, D, F) to select the GPIO peripheral.
  * @retval The input port pin value.
  */
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    return ((uint16_t)GPIOx->IDR);
}

/**
  * @brief  Reads the specified output data port bit.
  * @param  GPIOx: where x can be (A, B, C, D, F) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the port bit to read.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOF
  * @retval The output port pin value.
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if ((GPIOx->ODR & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }

    return bitstatus;
}

/**
  * @brief  Reads the specified GPIO output data port.
  * @param  GPIOx: where x can be (A, B, C, D, F) to select the GPIO peripheral.
  * @retval GPIO output data port value.
  */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    return ((uint16_t)GPIOx->ODR);
}

/**
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: where x can be (A, B, C, D, F) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOF
  * @retval None
  */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->BSRR = GPIO_Pin;
}

/**
  * @brief  Clears the selected data port bits.
  * @param  GPIOx: where x can be (A, B, C, D, F) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOF
  * @retval None
  */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->BRR = GPIO_Pin;
}

/**
  * @brief  Writes the selected data port bit.
  * @param  GPIOx: where x can be (A, B, C, D, F) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  * @param  BitVal: specifies the value to be written to the selected bit.
  *         This parameter can be one of the BitAction enumeration values:
  *         Bit_RESET: to clear the port pin
  *         Bit_SET: to set the port pin
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOF
  * @retval None
  */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    assert_param(IS_GPIO_BIT_ACTION(BitVal));

    if (BitVal != Bit_RESET)
    {
        GPIOx->BSRR = GPIO_Pin;
    }
    else
    {
        GPIOx->BRR = GPIO_Pin ;
    }
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (A, B, C, D, F) to select the GPIO peripheral.
  * @param  PortVal: specifies the value to be written to the port output data register.
  * @retval None
  */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    GPIOx->ODR = PortVal;
}

/**
  * @brief  Toggle the GPIO port.
  * @param  GPIOx: where x can be (A, B, C, D, F) to select the GPIO peripheral.
  * @param  GPIO_Pin: sGPIO_pins_define
  *         GPIO_Pin_0
  *         GPIO_Pin_1
  *         GPIO_Pin_2
  *         GPIO_Pin_3
  *         GPIO_Pin_4
  *         GPIO_Pin_5
  *         GPIO_Pin_6
  *         GPIO_Pin_7
  *         GPIO_Pin_8
  *         GPIO_Pin_9
  *         GPIO_Pin_10
  *         GPIO_Pin_11
  *         GPIO_Pin_12
  *         GPIO_Pin_13
  *         GPIO_Pin_14
  *         GPIO_Pin_15
  * @retval None
  */
void GPIO_Toggle(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->ODR ^= GPIO_Pin;
}

/**
  * @}
  */

/** @defgroup GPIO_Group3 GPIO Alternate functions configuration functions
 *  @brief   GPIO Alternate functions configuration functions
 *
@verbatim
 ===============================================================================
          ##### GPIO Alternate functions configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  selects the pin to used as Alternate function.
  * @param  GPIOx: where x can be (A, B, C, D, F) to select the GPIO peripheral.
  * @param  GPIO_PinSource: specifies the pin for the Alternate function.
  *         This parameter can be GPIO_PinSourcex where x can be (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOF
  * @param  GPIO_AF: selects the pin to used as Alternate function.
  *         This parameter can be one of the following value:
  *            @arg GPIO_AF_0: MCO, SWDIO, SWCLK, USART1_TX, USART1_RX, SPI2_NSS/I2S2_WS, SPI2_SCK/I2S2_CK, SPI1_NSS/I2S1_WS, SPI1_SCK/I2S1_CK,
  *                 SPI1_MISO/I2S1_MCK, SPI1_MOSI/I2S1_SD, TIM3_CH1, TIM3_CH2, TIM3_CH3, TIM3_CH4, TIM3_ETR
  *            @arg GPIO_AF_1: USART1_CTS, USART1_RTS/USART1_DE, USART1_TX, USART1_RX, USART1_CK, TIM3_CH1, TIM3_CH2, IROUT, TIM3_CH3, TIM3_CH4,
  *                 I2C1_SMBA, I2C1_SCL, I2C1_SDA, SPI2_NSS/I2S2_WS, SPI2_SCK/I2S2_CK, SPI2_MISO/I2S2_MCK, SPI2_MOSI/I2S2_SD
  *            @arg GPIO_AF_2: TIM2_CH2, TIM1_CH1, TIM1_CH2, TIM1_CH3, TIM1_CH4, TIM1_ETR, USB_NOE, TIM2_CH1/TIM2_ETR, TIM2_CH2, IROUT, TIM2_CH3,
  *                 TIM2_CH4, TIM1_BKIN, TIM1_CH1N, TIM1_CH2N, TIM1_CH3N, LPUART1_TX, LPUART1_RX, LPUART1_RTS/LPUART1_DE
  *            @arg GPIO_AF_3: MCO, I2C1_SMBA, LPUART1_TX, LPUART1_RX, LPUART1_CTS, LPUART1_RTS/LPUART1_DE
  *            @arg GPIO_AF_4: USART2_CTS, USART2_RTS/USART2_DE, USART2_CK, I2C1_SCL, I2C1_SDA, USART2_TX, USART2_RX, I2C2_SMBA, I2C2_SCL, I2C2_SDA
  *            @arg GPIO_AF_5: UART3_TX, UART3_RX, UART3_CTS, UART3_RTS/UART3_DE
  *            @arg GPIO_AF_6: I2C1_SMBA, I2C1_SCL, I2C1_SDA
  *            @arg GPIO_AF_7: COMP1_OUT, COMP2_OUT
  *            @arg GPIO_AF_8: EVENTOUT
  *            @arg GPIO_AF_9: USART2_TX, USART2_RX, UART4_TX, UART4_RX, UART4_CTS, UART4_RTS/UART4_DE
  *            @arg GPIO_AF_10: CLU0_O
  *            @arg GPIO_AF_11: CLU1_O
  *            @arg GPIO_AF_12: CLU2_O
  *            @arg GPIO_AF_13: CLU3_O
  *            @arg GPIO_AF_14: BEEPER
  * @note   The pin should already been configured in Alternate Function mode(AF)
  *         using GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
  * @note   Refer to the Alternate function mapping table in the device datasheet
  *         for the detailed mapping of the system and peripherals'alternate
  *         function I/O pins.
  * @retval None
  */
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
    uint32_t temp = 0x00;
    uint32_t temp_2 = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
    assert_param(IS_GPIO_AF(GPIO_AF));

    temp = ((uint32_t)(GPIO_AF) << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4));

    if ((GPIO_PinSource >> 0x03) == 1)
    {
        GPIOx->AFRH &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4));
        temp_2 = GPIOx->AFRH | temp;
        GPIOx->AFRH = temp_2;
    }
    else
    {
        GPIOx->AFRL &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4));
        temp_2 = GPIOx->AFRL | temp;
        GPIOx->AFRL = temp_2;
    }
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

/***************************** (C) COPYRIGHT HKMicroChip  *******************************/
