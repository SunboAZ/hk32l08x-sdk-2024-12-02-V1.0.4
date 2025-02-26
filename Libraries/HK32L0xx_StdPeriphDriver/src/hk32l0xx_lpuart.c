/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_lpuart.c
* @brief:     GPIO initialization and configuration
* @author:    AE Team
* @version:   V1.0.0/2024-01-08
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_lpuart.h"
#include "hk32l0xx_rcc.h"

/** @addtogroup HK32L0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup LPUART  LPUART
  * @brief LPUART driver modules
  * @{
  * @verbatim
===============================================================================
                        ##### LPUART specific features #####
===============================================================================
    [..]
        (#) Enable peripheral clock using RCC_APB1PeriphClockCmd(RCC_APB1Periph_LPUART1, ENABLE)
            function for LPUART1 .
        (#) According to the LPUART mode, enable the GPIO clocks using
            RCC_AHBPeriphClockCmd() function. (The I/O can be TX, RX, CTS, RTS
            or and DE).
        (#) Peripheral's alternate function:
            (++) Connect the pin to the desired peripherals' Alternate
                 Function (AF) using GPIO_PinAFConfig() function.
            (++) Configure the desired pin in alternate function by:
                 GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF.
            (++) Select the type, pull-up/pull-down and output speed via
                 GPIO_PuPd, GPIO_OType and GPIO_Speed members.
            (++) Call GPIO_Init() function.
        (#) Program the Baud Rate, Word Length , Stop Bit, Parity, Hardware
            flow control and Mode(Receiver/Transmitter) using the LPUART_Init()
            function.
        (#) Enable the NVIC and the corresponding interrupt using the function
            LPUART_ITConfig() if you need to use interrupt mode.
        (#) When using the DMA mode:
            (++) Configure the DMA using DMA_Init() function.
            (++) Active the needed channel Request using LPUART_DMACmd() function.
        (#) Enable the LPUART using the LPUART_Cmd() function.
        (#) Enable the DMA using the DMA_Cmd() function, when using DMA mode.
    [..]
            Refer to Multi-Processor, half-duplex, hardwae control, wakeup from stop mode
            for more details.

  *  @endverbatim
  *
  ******************************************************************************
  */

/** @defgroup LPUART_Private_Defines  LPUART_Private_Defines
  * @{
  */

/*!< LPUART CR1 register clear Mask ((~(uint32_t)0xEFFFE6F3)) */
#define LPUART_CR1_CLEAR_MASK     ((uint32_t)(LPUART_CR1_M0 | LPUART_CR1_PCE| \
                                              LPUART_CR1_PS | LPUART_CR1_TE | \
                                              LPUART_CR1_RE | LPUART_CR1_M1))

/*!< LPUART CR3 register clear Mask ((~(uint32_t)0xFFFFFCFF)) */
#define CR3_CLEAR_MASK            ((uint32_t)(LPUART_CR3_RTSE | LPUART_CR3_CTSE))

/*!< LPUART Interrupts mask */
#define IT_MASK                   ((uint32_t)0x000000FF)
/**
  * @}
  */

/** @defgroup LPUART_Private_Functions  LPUART_Private_Functions
  * @{
  */

/** @defgroup LPUART_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
          ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]
        This subsection provides a set of functions allowing to initialize the LPUART
        in asynchronous and in synchronous modes.
        (+) For the asynchronous mode only these parameters can be configured:
          (++) Baud Rate.
          (++) Word Length.
          (++) Stop Bit.
          (++) Parity: If the parity is enabled, then the MSB bit of the data written
               in the data register is transmitted but is changed by the parity bit.
               Depending on the frame length defined by the M bit (8-bits or 9-bits),
               the possible LPUART frame formats are as listed in the following table:

   +-------------------------------------------------------------+
   |   M bit |  PCE bit  |            LPUART frame                |
   |---------------------|---------------------------------------|
   |    00   |    0      |    | SB | 8 bit data | STB |          |
   |---------|-----------|---------------------------------------|
   |    00   |    1      |    | SB | 7 bit data | PB | STB |     |
   |---------|-----------|---------------------------------------|
   |    01   |    0      |    | SB | 9 bit data | STB |          |
   |---------|-----------|---------------------------------------|
   |    01   |    1      |    | SB | 8 bit data | PB | STB |     |
   |---------|-----------|---------------------------------------|
   |    10   |    0      |    | SB | 7 bit data | STB |          |
   |---------|-----------|---------------------------------------|
   |    10   |    1      |    | SB | 6 bit data | PB | STB |     |
   +-------------------------------------------------------------+


          (++) Hardware flow control.
          (++) Receiver/transmitter modes.
    [..] The LPUART_Init() function follows the LPUART  asynchronous configuration
         procedure(details for the procedure are available in reference manual.
        (+) For the synchronous mode in addition to the asynchronous mode parameters
            these parameters should be also configured:
            (++) LPUART Clock Enabled.
            (++) LPUART polarity.
            (++) LPUART phase.
            (++) LPUART LastBit.
    [..] These parameters can be configured using the LPUART_ClockInit() function.

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the LPUARTx peripheral registers to their default reset values.
  * @param  LPUARTx: LPUART peripheral.
  * @retval None
  */
void LPUART_DeInit(LPUART_TypeDef* LPUARTx)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));

    if (LPUARTx == LPUART)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_LPUART1, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_LPUART1, DISABLE);
    }
    else
    {

    }
}

/**
  * @brief  Initializes the LPUARTx peripheral according to the specified
  *         parameters in the LPUART_InitStruct .
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_InitStruct: pointer to a LPUART_InitTypeDef structure that contains
  *         the configuration information for the specified LPUART peripheral.
  * @retval None
  */
uint32_t LPUART_Init(LPUART_TypeDef* LPUARTx, LPUART_InitTypeDef* LPUART_InitStruct)
{
    uint32_t divider = 0, apbclock = 0, tmpreg = 0;
    RCC_ClocksTypeDef RCC_ClocksStatus;
    uint32_t Result = 0;
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_BAUDRATE(LPUART_InitStruct->LPUART_BaudRate));
    assert_param(IS_LPUART_WORD_LENGTH(LPUART_InitStruct->LPUART_WordLength));
    assert_param(IS_LPUART_STOPBITS(LPUART_InitStruct->LPUART_StopBits));
    assert_param(IS_LPUART_PARITY(LPUART_InitStruct->LPUART_Parity));
    assert_param(IS_LPUART_MODE(LPUART_InitStruct->LPUART_Mode));
    assert_param(IS_LPUART_HARDWARE_FLOW_CONTROL(LPUART_InitStruct->LPUART_HardwareFlowControl));

    /* Disable LPUART */
    LPUARTx->CR1 &= (uint32_t)~((uint32_t)LPUART_CR1_UE);

    /*---------------------------- LPUART CR2 Configuration -----------------------*/
    tmpreg = LPUARTx->CR2;
    /* Clear STOP[13:12] bits */
    tmpreg &= (uint32_t)~((uint32_t)LPUART_CR2_STOP);

    /* Configure the LPUART Stop Bits, Clock, CPOL, CPHA and LastBit ------------*/
    /* Set STOP[13:12] bits according to LPUART_StopBits value */
    tmpreg |= (uint32_t)LPUART_InitStruct->LPUART_StopBits;

    /* Write to LPUART CR2 */
    LPUARTx->CR2 = tmpreg;

    /*---------------------------- LPUART CR1 Configuration -----------------------*/
    tmpreg = LPUARTx->CR1;
    /* Clear M, PCE, PS, TE and RE bits */
    tmpreg &= (uint32_t)~((uint32_t)LPUART_CR1_CLEAR_MASK);

    /* Configure the LPUART Word Length, Parity and mode ----------------------- */
    /* Set the M bits according to LPUART_WordLength value */
    /* Set PCE and PS bits according to LPUART_Parity value */
    /* Set TE and RE bits according to LPUART_Mode value */
    tmpreg |= (uint32_t)LPUART_InitStruct->LPUART_WordLength | LPUART_InitStruct->LPUART_Parity |
              LPUART_InitStruct->LPUART_Mode;

    /* Write to LPUART CR1 */
    LPUARTx->CR1 = tmpreg;

    /*---------------------------- LPUART CR3 Configuration -----------------------*/
    tmpreg = LPUARTx->CR3;
    /* Clear CTSE and RTSE bits */
    tmpreg &= (uint32_t)~((uint32_t)CR3_CLEAR_MASK);

    /* Configure the LPUART HFC -------------------------------------------------*/
    /* Set CTSE and RTSE bits according to LPUART_HardwareFlowControl value */
    tmpreg |= LPUART_InitStruct->LPUART_HardwareFlowControl;

    /* Write to LPUART CR3 */
    LPUARTx->CR3 = tmpreg;

    /*---------------------------- LPUART BRR Configuration -----------------------*/
    /* Configure the LPUART Baud Rate -------------------------------------------*/
    RCC_GetClocksFreq(&RCC_ClocksStatus);           //Clock source selection, need to refer to the RCC clock source type
    apbclock = RCC_ClocksStatus.LPUART1CLK_Frequency;

    if (apbclock != 0 )
    {
        if ((apbclock < (3U * LPUART_InitStruct->LPUART_BaudRate)) ||
                (apbclock > (4096U * LPUART_InitStruct->LPUART_BaudRate)))
        {
            Result = 1;
        }
        else
        {
            divider = (uint32_t)(((((uint64_t)(apbclock) * 256U)) + ((LPUART_InitStruct->LPUART_BaudRate) / 2U)) / (LPUART_InitStruct->LPUART_BaudRate));
            /* Write to LPUART BRR */
            LPUARTx->BRR = divider; //(uint16_t)
        }
    }
    else
    {
        Result = 2;
    }

    return Result;
}

/**
  * @brief  Fills each LPUART_InitStruct member with its default value.
  * @param  LPUART_InitStruct: pointer to a LPUART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void LPUART_StructInit(LPUART_InitTypeDef* LPUART_InitStruct)
{
    /* LPUART_InitStruct members default value */
    LPUART_InitStruct->LPUART_BaudRate = 9600;
    LPUART_InitStruct->LPUART_WordLength = LPUART_WordLength_8b;
    LPUART_InitStruct->LPUART_StopBits = LPUART_StopBits_1;
    LPUART_InitStruct->LPUART_Parity = LPUART_Parity_No ;
    LPUART_InitStruct->LPUART_Mode = LPUART_Mode_Rx | LPUART_Mode_Tx;
    LPUART_InitStruct->LPUART_HardwareFlowControl = LPUART_HardwareFlowControl_None;
}


/**
  * @brief  Enables or disables the specified LPUART peripheral.
  * @param  LPUARTx: LPUART peripheral.
  * @param  NewState: new state of the LPUARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPUART_Cmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected LPUART by setting the UE bit in the CR1 register */
        LPUARTx->CR1 |= LPUART_CR1_UE;
    }
    else
    {
        /* Disable the selected LPUART by clearing the UE bit in the CR1 register */
        LPUARTx->CR1 &= (uint32_t)~((uint32_t)LPUART_CR1_UE);
    }
}

/**
  * @brief  Enables or disables the LPUART's transmitter or receiver.
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_DirectionMode: specifies the LPUART direction.
  *         This parameter can be any combination of the following values:
  *            @arg LPUART_Mode_Tx: LPUART Transmitter
  *            @arg LPUART_Mode_Rx: LPUART Receiver
  * @param  NewState: new state of the LPUART transfer direction.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPUART_DirectionModeCmd(LPUART_TypeDef* LPUARTx, uint32_t LPUART_DirectionMode, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_MODE(LPUART_DirectionMode));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the LPUART's transfer interface by setting the TE and/or RE bits
           in the LPUART CR1 register */
        LPUARTx->CR1 |= LPUART_DirectionMode;
    }
    else
    {
        /* Disable the LPUART's transfer interface by clearing the TE and/or RE bits
           in the LPUART CR3 register */
        LPUARTx->CR1 &= (uint32_t)~LPUART_DirectionMode;
    }
}


/**
  * @brief  Enables or disables the LPUART's most significant bit first
  *         transmitted/received following the start bit.
  * @param  LPUARTx: LPUART peripheral.
  * @param  NewState: new state of the LPUART most significant bit first
  *         transmitted/received following the start bit.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   This function has to be called before calling LPUART_Cmd() function.
  * @retval None
  */
void LPUART_MSBFirstCmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the most significant bit first transmitted/received following the
           start bit by setting the MSBFIRST bit in the CR2 register */
        LPUARTx->CR2 |= LPUART_CR2_MSBFIRST;
    }
    else
    {
        /* Disable the most significant bit first transmitted/received following the
           start bit by clearing the MSBFIRST bit in the CR2 register */
        LPUARTx->CR2 &= (uint32_t)~((uint32_t)LPUART_CR2_MSBFIRST);
    }
}

/**
  * @brief  Enables or disables the binary data inversion.
  * @param  LPUARTx: LPUART peripheral.
  * @param  NewState: new defined levels for the LPUART data.
  *         This parameter can be:
  *            @arg ENABLE: Logical data from the data register are send/received in negative
  *                 logic (1=L, 0=H). The parity bit is also inverted.
  *            @arg DISABLE: Logical data from the data register are send/received in positive
  *                 logic (1=H, 0=L)
  * @note   This function has to be called before calling LPUART_Cmd() function.
  * @retval None
  */
void LPUART_DataInvCmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the binary data inversion feature by setting the DATAINV bit in
           the CR2 register */
        LPUARTx->CR2 |= LPUART_CR2_DATAINV;
    }
    else
    {
        /* Disable the binary data inversion feature by clearing the DATAINV bit in
           the CR2 register */
        LPUARTx->CR2 &= (uint32_t)~((uint32_t)LPUART_CR2_DATAINV);
    }
}

/**
  * @brief  Enables or disables the Pin(s) active level inversion.
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_InvPin: specifies the LPUART pin(s) to invert.
  *         This parameter can be any combination of the following values:
  *            @arg LPUART_InvPin_Tx: LPUART Tx pin active level inversion.
  *            @arg LPUART_InvPin_Rx: LPUART Rx pin active level inversion.
  * @param  NewState: new active level status for the LPUART pin(s).
  *         This parameter can be:
  *            @arg ENABLE: pin(s) signal values are inverted (Vdd =0, Gnd =1).
  *            @arg DISABLE: pin(s) signal works using the standard logic levels (Vdd =1, Gnd =0).
  * @note   This function has to be called before calling LPUART_Cmd() function.
  * @retval None
  */
void LPUART_InvPinCmd(LPUART_TypeDef* LPUARTx, uint32_t LPUART_InvPin, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_INVERSTION_PIN(LPUART_InvPin));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the active level inversion for selected pins by setting the TXINV
           and/or RXINV bits in the LPUART CR2 register */
        LPUARTx->CR2 |= LPUART_InvPin;
    }
    else
    {
        /* Disable the active level inversion for selected requests by clearing the
           TXINV and/or RXINV bits in the LPUART CR2 register */
        LPUARTx->CR2 &= (uint32_t)~LPUART_InvPin;
    }
}

/**
  * @brief  Enables or disables the swap Tx/Rx pins.
  * @param  LPUARTx: LPUART peripheral.
  * @param  NewState: new state of the LPUARTx TX/RX pins pinout.
  *         This parameter can be:
  *            @arg ENABLE: The TX and RX pins functions are swapped.
  *            @arg DISABLE: TX/RX pins are used as defined in standard pinout
  * @note   This function has to be called before calling LPUART_Cmd() function.
  * @retval None
  */
void LPUART_SWAPPinCmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the SWAP feature by setting the SWAP bit in the CR2 register */
        LPUARTx->CR2 |= LPUART_CR2_SWAP;
    }
    else
    {
        /* Disable the SWAP feature by clearing the SWAP bit in the CR2 register */
        LPUARTx->CR2 &= (uint32_t)~((uint32_t)LPUART_CR2_SWAP);
    }
}
/**
  * @}
  */

/** @defgroup LPUART_Group2 STOP Mode functions
 *  @brief   STOP Mode functions
 *
@verbatim
 ===============================================================================
                        ##### STOP Mode functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage
         WakeUp from STOP mode.

    [..] The LPUART is able to WakeUp from Stop Mode if LPUART clock is set to HSI
         or LSE.

    [..] The WakeUp source is configured by calling LPUART_StopModeWakeUpSourceConfig()
         function.

    [..] After configuring the source of WakeUp and before entering in Stop Mode
         LPUART_STOPModeCmd() function should be called to allow LPUART WakeUp.

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified LPUART peripheral in STOP Mode.
  * @param  LPUARTx: LPUART peripheral.
  * @param  NewState: new state of the LPUARTx peripheral state in stop mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   This function has to be called when LPUART clock is set to HSI or LSE.
  * @retval None
  */
void LPUART_STOPModeCmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected LPUART in STOP mode by setting the UESM bit in the CR1
           register */
        LPUARTx->CR1 |= LPUART_CR1_UESM;
    }
    else
    {
        /* Disable the selected LPUART in STOP mode by clearing the UE bit in the CR1
           register */
        LPUARTx->CR1 &= (uint32_t)~((uint32_t)LPUART_CR1_UESM);
    }
}

/**
  * @brief  Selects the LPUART WakeUp method form stop mode.
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_WakeUpSource: specifies the selected LPUART wakeup method.
  *         This parameter can be one of the following values:
  *            @arg LPUART_WakeUpSource_AddressMatch: WUF active on address match.
  *            @arg LPUART_WakeUpSource_StartBit: WUF active on Start bit detection.
  *            @arg LPUART_WakeUpSource_RXNE: WUF active on RXNE.
  * @note   This function has to be called before calling LPUART_Cmd() function.
  * @retval None
  */
void LPUART_StopModeWakeUpSourceConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_WakeUpSource)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_STOPMODE_WAKEUPSOURCE(LPUART_WakeUpSource));

    LPUARTx->CR3 &= (uint32_t)~((uint32_t)LPUART_CR3_WUS);
    LPUARTx->CR3 |= LPUART_WakeUpSource;
}
/**
  * @}
  */

/** @defgroup LPUART_Group4 Data transfers functions
 *  @brief   Data transfers functions
 *
@verbatim
 ===============================================================================
                    ##### Data transfers functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage
         the LPUART data transfers.
    [..] During an LPUART reception, data shifts in least significant bit first
         through the RX pin. When a transmission is taking place, a write instruction to
         the LPUART_TDR register stores the data in the shift register.
    [..] The read access of the LPUART_RDR register can be done using
         the LPUART_ReceiveData() function and returns the RDR value.
         Whereas a write access to the LPUART_TDR can be done using LPUART_SendData()
         function and stores the written data into TDR.

@endverbatim
  * @{
  */

/**
  * @brief  Transmits single data through the LPUARTx peripheral.
  * @param  LPUARTx: LPUART peripheral.
  * @param  Data: the data to transmit.
  * @retval None
  */
void LPUART_SendData(LPUART_TypeDef* LPUARTx, uint16_t Data)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_DATA(Data));

    /* Transmit Data */
    LPUARTx->TDR = (Data & (uint16_t)0x01FF);
}

/**
  * @brief  Returns the most recent received data by the LPUARTx peripheral.
  * @param  LPUARTx: LPUART peripheral.
  * @retval The received data.
  */
uint16_t LPUART_ReceiveData(LPUART_TypeDef* LPUARTx)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));

    /* Receive Data */
    return (uint16_t)(LPUARTx->RDR & (uint16_t)0x01FF);
}

/**
  * @}
  */

/** @defgroup LPUART_Group5 MultiProcessor Communication functions
 *  @brief   Multi-Processor Communication functions
 *
@verbatim
 ===============================================================================
             ##### Multi-Processor Communication functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the LPUART
         multiprocessor communication.
    [..] For instance one of the LPUARTs can be the master, its TX output is
         connected to the RX input of the other LPUART. The others are slaves,
         their respective TX outputs are logically ANDed together and connected
         to the RX input of the master. LPUART multiprocessor communication is
         possible through the following procedure:
         (#) Program the Baud rate, Word length = 9 bits, Stop bits, Parity,
             Mode transmitter or Mode receiver and hardware flow control values
             using the LPUART_Init() function.
         (#) Configures the LPUART address using the LPUART_SetAddress() function.
         (#) Configures the wake up methode (LPUART_WakeUp_IdleLine or
             LPUART_WakeUp_AddressMark) using LPUART_WakeUpConfig() function only
             for the slaves.
         (#) Enable the LPUART using the LPUART_Cmd() function.
         (#) Enter the LPUART slaves in mute mode using LPUART_ReceiverWakeUpCmd()
             function.
    [..] The LPUART Slave exit from mute mode when receive the wake up condition.

@endverbatim
  * @{
  */

/**
  * @brief  Sets the address of the LPUART node.
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_Address: Indicates the address of the LPUART node.
  * @retval None
  */
void LPUART_SetAddress(LPUART_TypeDef* LPUARTx, uint8_t LPUART_Address)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));

    /* Clear the LPUART address */
    LPUARTx->CR2 &= (uint32_t)~((uint32_t)(LPUART_CR2_ADD));
    /* Set the LPUART address node */
    LPUARTx->CR2 |= ((uint32_t)LPUART_Address << (uint32_t)0x18);
}

/**
  * @brief  Enables or disables the LPUART's mute mode.
  * @param  LPUARTx: LPUART peripheral.
  * @param  NewState: new state of the LPUART mute mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPUART_MuteModeCmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the LPUART mute mode by setting the MME bit in the CR1 register */
        LPUARTx->CR1 |= LPUART_CR1_MME;
    }
    else
    {
        /* Disable the LPUART mute mode by clearing the MME bit in the CR1 register */
        LPUARTx->CR1 &= (uint32_t)~((uint32_t)LPUART_CR1_MME);
    }
}

/**
  * @brief  Selects the LPUART WakeUp method from mute mode.
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_WakeUp: specifies the LPUART wakeup method.
  *         This parameter can be one of the following values:
  *            @arg LPUART_WakeUp_IdleLine: WakeUp by an idle line detection
  *            @arg LPUART_WakeUp_AddressMark: WakeUp by an address mark
  * @retval None
  */
void LPUART_MuteModeWakeUpConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_WakeUp)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_MUTEMODE_WAKEUP(LPUART_WakeUp));

    LPUARTx->CR1 &= (uint32_t)~((uint32_t)LPUART_CR1_WAKE);
    LPUARTx->CR1 |= LPUART_WakeUp;
}

/**
  * @brief  Configure the the LPUART Address detection length.
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_AddressLength: specifies the LPUART address length detection.
  *         This parameter can be one of the following values:
  *            @arg LPUART_AddressLength_4b: 4-bit address length detection
  *            @arg LPUART_AddressLength_7b: 7-bit address length detection
  * @retval None
  */
void LPUART_AddressDetectionConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_AddressLength)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_ADDRESS_DETECTION(LPUART_AddressLength));

    LPUARTx->CR2 &= (uint32_t)~((uint32_t)LPUART_CR2_ADDM7);
    LPUARTx->CR2 |= LPUART_AddressLength;
}
/**
  * @}
  */

/** @defgroup LPUART_Group7 Halfduplex mode function
 *  @brief   Half-duplex mode function
 *
@verbatim
 ===============================================================================
                   ##### Half-duplex mode function #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the LPUART
         Half-duplex communication.
    [..] The LPUART can be configured to follow a single-wire half-duplex protocol
         where the TX and RX lines are internally connected.
    [..] LPUART Half duplex communication is possible through the following procedure:
         (#) Program the Baud rate, Word length, Stop bits, Parity, Mode transmitter
             or Mode receiver and hardware flow control values using the LPUART_Init()
            function.
         (#) Configures the LPUART address using the LPUART_SetAddress() function.
         (#) Enable the half duplex mode using LPUART_HalfDuplexCmd() function.
         (#) Enable the LPUART using the LPUART_Cmd() function.
         -@- The RX pin is no longer used.
         -@- In Half-duplex mode the following bits must be kept cleared:
             (+@) LINEN and CLKEN bits in the LPUART_CR2 register.
             (+@) SCEN and IREN bits in the LPUART_CR3 register.

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the LPUART's Half Duplex communication.
  * @param  LPUARTx: LPUART peripheral.
  * @param  NewState: new state of the LPUART Communication.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPUART_HalfDuplexCmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Half-Duplex mode by setting the HDSEL bit in the CR3 register */
        LPUARTx->CR3 |= LPUART_CR3_HDSEL;
    }
    else
    {
        /* Disable the Half-Duplex mode by clearing the HDSEL bit in the CR3 register */
        LPUARTx->CR3 &= (uint32_t)~((uint32_t)LPUART_CR3_HDSEL);
    }
}
/**
  * @}
  */
/** @defgroup LPUART_Group10 RS485 mode function
 *  @brief  RS485 mode function
 *
@verbatim
 ===============================================================================
                        ##### RS485 mode functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the LPUART
         RS485 flow control.
    [..] RS485 flow control (Driver enable feature) handling is possible through
         the following procedure:
         (#) Program the Baud rate, Word length = 8 bits, Stop bits, Parity,
             Transmitter/Receiver modes and hardware flow control values using
             the LPUART_Init() function.
         (#) Enable the Driver Enable using the LPUART_DECmd() function.
         (#) Configures the Driver Enable polarity using the LPUART_DEPolarityConfig()
             function.
         (#) Configures the Driver Enable assertion time using LPUART_SetDEAssertionTime()
             function and deassertion time using the LPUART_SetDEDeassertionTime()
             function.
         (#) Enable the LPUART using the LPUART_Cmd() function.
      -@-
       (+@) The assertion and dessertion times are expressed in sample time units (1/8 or
            1/16 bit time, depending on the oversampling rate).

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the LPUART's DE functionality.
  * @param  LPUARTx: LPUART peripheral.
  * @param  NewState: new state of the driver enable mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPUART_DECmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the DE functionality by setting the DEM bit in the CR3 register */
        LPUARTx->CR3 |= LPUART_CR3_DEM;
    }
    else
    {
        /* Disable the DE functionality by clearing the DEM bit in the CR3 register */
        LPUARTx->CR3 &= (uint32_t)~((uint32_t)LPUART_CR3_DEM);
    }
}

/**
  * @brief  Configures the LPUART's DE polarity
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_DEPolarity: specifies the DE polarity.
  *         This parameter can be one of the following values:
  *            @arg LPUART_DEPolarity_Low
  *            @arg LPUART_DEPolarity_High
  * @retval None
  */
void LPUART_DEPolarityConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_DEPolarity)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_DE_POLARITY(LPUART_DEPolarity));

    LPUARTx->CR3 &= (uint32_t)~((uint32_t)LPUART_CR3_DEP);
    LPUARTx->CR3 |= LPUART_DEPolarity;
}

/**
  * @brief  Sets the specified RS485 DE assertion time
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_DEAssertionTime: specifies the time between the activation of
  *         the DE signal and the beginning of the start bit
  * @retval None
  */
void LPUART_SetDEAssertionTime(LPUART_TypeDef* LPUARTx, uint32_t LPUART_DEAssertionTime)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_DE_ASSERTION_DEASSERTION_TIME(LPUART_DEAssertionTime));

    /* Clear the DE assertion time */
    LPUARTx->CR1 &= (uint32_t)~((uint32_t)LPUART_CR1_DEAT);
    /* Set the new value for the DE assertion time */
    LPUARTx->CR1 |= ((uint32_t)LPUART_DEAssertionTime << (uint32_t)0x15);
}

/**
  * @brief  Sets the specified RS485 DE deassertion time
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_DEDeassertionTime: specifies the time between the middle of the last
  *         stop bit in a transmitted message and the de-activation of the DE signal
  * @retval None
  */
void LPUART_SetDEDeassertionTime(LPUART_TypeDef* LPUARTx, uint32_t LPUART_DEDeassertionTime)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_DE_ASSERTION_DEASSERTION_TIME(LPUART_DEDeassertionTime));

    /* Clear the DE deassertion time */
    LPUARTx->CR1 &= (uint32_t)~((uint32_t)LPUART_CR1_DEDT);
    /* Set the new value for the DE deassertion time */
    LPUARTx->CR1 |= ((uint32_t)LPUART_DEDeassertionTime << (uint32_t)0x10);
}

/**
  * @}
  */

/** @defgroup LPUART_Group11 DMA transfers management functions
 *  @brief   DMA transfers management functions
 *
@verbatim
 ===============================================================================
               ##### DMA transfers management functions #####
 ===============================================================================
    [..] This section provides two functions that can be used only in DMA mode.
    [..] In DMA Mode, the LPUART communication can be managed by 2 DMA Channel
         requests:
         (#) LPUART_DMAReq_Tx: specifies the Tx buffer DMA transfer request.
         (#) LPUART_DMAReq_Rx: specifies the Rx buffer DMA transfer request.
    [..] In this Mode it is advised to use the following function:
         (+) void LPUART_DMACmd(LPUART_TypeDef* LPUARTx, uint16_t LPUART_DMAReq,
             FunctionalState NewState).
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the LPUART's DMA interface.
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_DMAReq: specifies the DMA request.
  *         This parameter can be any combination of the following values:
  *            @arg LPUART_DMAReq_Tx: LPUART DMA transmit request
  *            @arg LPUART_DMAReq_Rx: LPUART DMA receive request
  * @param  NewState: new state of the DMA Request sources.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPUART_DMACmd(LPUART_TypeDef* LPUARTx, uint32_t LPUART_DMAReq, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_DMAREQ(LPUART_DMAReq));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the DMA transfer for selected requests by setting the DMAT and/or
           DMAR bits in the LPUART CR3 register */
        LPUARTx->CR3 |= LPUART_DMAReq;
    }
    else
    {
        /* Disable the DMA transfer for selected requests by clearing the DMAT and/or
           DMAR bits in the LPUART CR3 register */
        LPUARTx->CR3 &= (uint32_t)~LPUART_DMAReq;
    }
}

/**
  * @brief  Enables or disables the LPUART's DMA interface when reception error occurs.
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_DMAOnError: specifies the DMA status in case of reception error.
  *         This parameter can be any combination of the following values:
  *            @arg LPUART_DMAOnError_Enable: DMA receive request enabled when the LPUART DMA
  *                 reception error is asserted.
  *            @arg LPUART_DMAOnError_Disable: DMA receive request disabled when the LPUART DMA
  *                 reception error is asserted.
  * @retval None
  */
void LPUART_DMAReceptionErrorConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_DMAOnError)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_DMAONERROR(LPUART_DMAOnError));

    /* Clear the DMA Reception error detection bit */
    LPUARTx->CR3 &= (uint32_t)~((uint32_t)LPUART_CR3_DDRE);
    /* Set the new value for the DMA Reception error detection bit */
    LPUARTx->CR3 |= LPUART_DMAOnError;
}

/**
  * @}
  */

/** @defgroup LPUART_Group12 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to configure the
         LPUART Interrupts sources, Requests and check or clear the flags or pending bits status.
         The user should identify which mode will be used in his application to
         manage the communication: Polling mode, Interrupt mode.

 *** Polling Mode ***
 ====================
    [..] In Polling Mode, the SPI communication can be managed by these flags:
         (#) LPUART_FLAG_REACK: to indicate the status of the Receive Enable
             acknowledge flag
         (#) LPUART_FLAG_TEACK: to indicate the status of the Transmit Enable
             acknowledge flag.
         (#) LPUART_FLAG_WU: to indicate the status of the Wake up flag.
         (#) LPUART_FLAG_RWU: to indicate the status of the Receive Wake up flag.
         (#) LPUART_FLAG_SBK: to indicate the status of the Send Break flag.
         (#) LPUART_FLAG_CM: to indicate the status of the Character match flag.
         (#) LPUART_FLAG_BUSY: to indicate the status of the Busy flag.
         (#) LPUART_FLAG_nCTSS: to indicate the status of the Inverted nCTS input
             bit status.
         (#) LPUART_FLAG_TXE: to indicate the status of the transmit buffer register.
         (#) LPUART_FLAG_RXNE: to indicate the status of the receive buffer register.
         (#) LPUART_FLAG_TC: to indicate the status of the transmit operation.
         (#) LPUART_FLAG_IDLE: to indicate the status of the Idle Line.
         (#) LPUART_FLAG_CTS: to indicate the status of the nCTS input.
         (#) LPUART_FLAG_NE: to indicate if a noise error occur.
         (#) LPUART_FLAG_FE: to indicate if a frame error occur.
         (#) LPUART_FLAG_PE: to indicate if a parity error occur.
         (#) LPUART_FLAG_ORE: to indicate if an Overrun error occur.
    [..] In this Mode it is advised to use the following functions:
         (+) FlagStatus LPUART_GetFlagStatus(LPUART_TypeDef* LPUARTx, uint16_t LPUART_FLAG).
         (+) void LPUART_ClearFlag(LPUART_TypeDef* LPUARTx, uint16_t LPUART_FLAG).

 *** Interrupt Mode ***
 ======================
    [..] In Interrupt Mode, the LPUART communication can be managed by 8 interrupt
         sources and 10 pending bits:
         (+) Pending Bits:
             (##) LPUART_IT_WU: to indicate the status of the Wake up interrupt.
             (##) LPUART_IT_CM: to indicate the status of Character match interrupt.
             (##) LPUART_IT_CTS: to indicate the status of CTS change interrupt.
             (##) LPUART_IT_TC: to indicate the status of Transmission complete interrupt.
             (##) LPUART_IT_IDLE: to indicate the status of IDLE line detected interrupt.
             (##) LPUART_IT_ORE: to indicate the status of OverRun Error interrupt.
             (##) LPUART_IT_NE: to indicate the status of Noise Error interrupt.
             (##) LPUART_IT_FE: to indicate the status of Framing Error interrupt.
             (##) LPUART_IT_PE: to indicate the status of Parity Error interrupt.

         (+) Interrupt Source:
             (##) LPUART_IT_WU: specifies the interrupt source for Wake up interrupt.
             (##) LPUART_IT_CM: specifies the interrupt source for Character match
                  interrupt.
             (##) LPUART_IT_CTS: specifies the interrupt source for CTS change interrupt.
             (##) LPUART_IT_TXE: specifies the interrupt source for Tansmit Data
                  Register empty interrupt.
             (##) LPUART_IT_TC: specifies the interrupt source for Transmission
                  complete interrupt.
             (##) LPUART_IT_RXNE: specifies the interrupt source for Receive Data
                  register not empty interrupt.
             (##) LPUART_IT_IDLE: specifies the interrupt source for Idle line
                  detection interrupt.
             (##) LPUART_IT_PE: specifies the interrupt source for Parity Error interrupt.
             (##) LPUART_IT_ERR: specifies the interrupt source for Error interrupt
                  (Frame error, noise error, overrun error)
             -@@- Some parameters are coded in order to use them as interrupt
                 source or as pending bits.
    [..] In this Mode it is advised to use the following functions:
         (+) void LPUART_ITConfig(LPUART_TypeDef* LPUARTx, uint16_t LPUART_IT, FunctionalState NewState).
         (+) ITStatus LPUART_GetITStatus(LPUART_TypeDef* LPUARTx, uint16_t LPUART_IT).
         (+) void LPUART_ClearITPendingBit(LPUART_TypeDef* LPUARTx, uint16_t LPUART_IT).

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified LPUART interrupts.
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_IT: specifies the LPUART interrupt sources to be enabled or disabled.
  *         This parameter can be one of the following values:
  *            @arg LPUART_IT_WU:  Wake up interrupt, not available for  devices.
  *            @arg LPUART_IT_CM:  Character match interrupt.
  *            @arg LPUART_IT_CTS:  CTS change interrupt.
  *            @arg LPUART_IT_TXE:  Tansmit Data Register empty interrupt.
  *            @arg LPUART_IT_TC:  Transmission complete interrupt.
  *            @arg LPUART_IT_RXNE:  Receive Data register not empty interrupt.
  *            @arg LPUART_IT_IDLE:  Idle line detection interrupt.
  *            @arg LPUART_IT_PE:  Parity Error interrupt.
  *            @arg LPUART_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @param  NewState: new state of the specified LPUARTx interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPUART_ITConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_IT, FunctionalState NewState)
{
    uint32_t LPUARTreg = 0, itpos = 0, itmask = 0;
    uint32_t LPUARTxbase = 0;
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_CONFIG_IT(LPUART_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    LPUARTxbase = (uint32_t)LPUARTx;

    /* Get the LPUART register index */
    LPUARTreg = (((uint16_t)LPUART_IT) >> 0x08);

    /* Get the interrupt position */
    itpos = LPUART_IT & IT_MASK;
    itmask = (((uint32_t)0x01) << itpos);

    if (LPUARTreg == 0x02) /* The IT is in CR2 register */
    {
        LPUARTxbase += 0x04;
    }
    else if (LPUARTreg == 0x03) /* The IT is in CR3 register */
    {
        LPUARTxbase += 0x08;
    }
    else /* The IT is in CR1 register */
    {
    }

    if (NewState != DISABLE)
    {
        *(__IO uint32_t*)LPUARTxbase  |= itmask;
    }
    else
    {
        *(__IO uint32_t*)LPUARTxbase &= ~itmask;
    }
}

/**
  * @brief  Enables the specified LPUART's Request.
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_Request: specifies the LPUART request.
  *         This parameter can be any combination of the following values:
  *            @arg LPUART_Request_RXFRQ: Receive data flush ReQuest
  *            @arg LPUART_Request_MMRQ: Mute Mode ReQuest
  *            @arg LPUART_Request_SBKRQ: Send Break ReQuest
  * @param  NewState: new state of the DMA interface when reception error occurs.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPUART_RequestCmd(LPUART_TypeDef* LPUARTx, uint32_t LPUART_Request, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_REQUEST(LPUART_Request));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the LPUART ReQuest by setting the dedicated request bit in the RQR
        register.*/
        LPUARTx->RQR |= LPUART_Request;
    }
    else
    {
        /* Disable the LPUART ReQuest by clearing the dedicated request bit in the RQR
        register.*/
        LPUARTx->RQR &= (uint32_t)~LPUART_Request;
    }
}

/**
  * @brief  Enables or disables the LPUART's Overrun detection.
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_OVRDetection: specifies the OVR detection status in case of OVR error.
  *         This parameter can be any combination of the following values:
  *            @arg LPUART_OVRDetection_Enable: OVR error detection enabled when
  *                 the LPUART OVR error is asserted.
  *            @arg LPUART_OVRDetection_Disable: OVR error detection disabled when
  *                 the LPUART OVR error is asserted.
  * @retval None
  */
void LPUART_OverrunDetectionConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_OVRDetection)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_OVRDETECTION(LPUART_OVRDetection));

    /* Clear the OVR detection bit */
    LPUARTx->CR3 &= (uint32_t)~((uint32_t)LPUART_CR3_OVRDIS);
    /* Set the new value for the OVR detection bit */
    LPUARTx->CR3 |= LPUART_OVRDetection;
}

/**
  * @brief  Checks whether the specified LPUART flag is set or not.
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg LPUART_FLAG_REACK:  Receive Enable acknowledge flag.
  *            @arg LPUART_FLAG_TEACK:  Transmit Enable acknowledge flag.
  *            @arg LPUART_FLAG_WU:  Wake up flag, not available for   devices.
  *            @arg LPUART_FLAG_RWU:  Receive Wake up flag, not available for   devices.
  *            @arg LPUART_FLAG_SBK:  Send Break flag.
  *            @arg LPUART_FLAG_CM:  Character match flag.
  *            @arg LPUART_FLAG_BUSY:  Busy flag.
  *            @arg LPUART_FLAG_nCTSS:  Inverted nCTS input bit status.
  *            @arg LPUART_FLAG_CTS:  CTS Change flag.
  *            @arg LPUART_FLAG_TXE:  Transmit data register empty flag.
  *            @arg LPUART_FLAG_TC:  Transmission Complete flag.
  *            @arg LPUART_FLAG_RXNE:  Receive data register not empty flag.
  *            @arg LPUART_FLAG_IDLE:  Idle Line detection flag.
  *            @arg LPUART_FLAG_ORE:  OverRun Error flag.
  *            @arg LPUART_FLAG_NF:  Noise Error flag.
  *            @arg LPUART_FLAG_FE:  Framing Error flag.
  *            @arg LPUART_FLAG_PE:  Parity Error flag.
  * @retval The new state of LPUART_FLAG (SET or RESET).
  */
FlagStatus LPUART_GetFlagStatus(LPUART_TypeDef* LPUARTx, uint32_t LPUART_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_FLAG(LPUART_FLAG));

    if ((LPUARTx->ISR & LPUART_FLAG) != (uint16_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * @brief  Clears the LPUARTx's pending flags.
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_FLAG: specifies the flag to clear.
  *         This parameter can be any combination of the following values:
  *            @arg LPUART_FLAG_WU:  Wake up flag, not available for   devices.
  *            @arg LPUART_FLAG_CM:  Character match flag.
  *            @arg LPUART_FLAG_CTS:  CTS Change flag.
  *            @arg LPUART_FLAG_TC:  Transmission Complete flag.
  *            @arg LPUART_FLAG_IDLE:  IDLE line detected flag.
  *            @arg LPUART_FLAG_ORE:  OverRun Error flag.
  *            @arg LPUART_FLAG_NF: Noise Error flag.
  *            @arg LPUART_FLAG_FE: Framing Error flag.
  *            @arg LPUART_FLAG_PE:   Parity Errorflag.
  * @note   RXNE pending bit is cleared by a read to the LPUART_RDR register
  *         (LPUART_ReceiveData()) or by writing 1 to the RXFRQ in the register
  *         LPUART_RQR (LPUART_RequestCmd()).
  * @note   TC flag can be also cleared by software sequence: a read operation
  *         to LPUART_SR register (LPUART_GetFlagStatus()) followed by a write
  *         operation to LPUART_TDR register (LPUART_SendData()).
  * @note   TXE flag is cleared by a write to the LPUART_TDR register (LPUART_SendData())
  *         or by writing 1 to the TXFRQ in the register LPUART_RQR (LPUART_RequestCmd()).
  * @note   SBKF flag is cleared by 1 to the SBKRQ in the register LPUART_RQR
  *         (LPUART_RequestCmd()).
  * @retval None
  */
void LPUART_ClearFlag(LPUART_TypeDef* LPUARTx, uint32_t LPUART_FLAG)
{
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_CLEAR_FLAG(LPUART_FLAG));

    LPUARTx->ICR = LPUART_FLAG;
}

/**
  * @brief  Checks whether the specified LPUART interrupt has occurred or not.
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_IT: specifies the LPUART interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg LPUART_IT_WU:  Wake up interrupt, not available for   devices.
  *            @arg LPUART_IT_CM:  Character match interrupt.
  *            @arg LPUART_IT_CTS:  CTS change interrupt.
  *            @arg LPUART_IT_TXE:  Tansmit Data Register empty interrupt.
  *            @arg LPUART_IT_TC:  Transmission complete interrupt.
  *            @arg LPUART_IT_RXNE:  Receive Data register not empty interrupt.
  *            @arg LPUART_IT_IDLE:  Idle line detection interrupt.
  *            @arg LPUART_IT_ORE:  OverRun Error interrupt.
  *            @arg LPUART_IT_NE:  Noise Error interrupt.
  *            @arg LPUART_IT_FE:  Framing Error interrupt.
  *            @arg LPUART_IT_PE:  Parity Error interrupt.
  * @retval The new state of LPUART_IT (SET or RESET).
  */
ITStatus LPUART_GetITStatus(LPUART_TypeDef* LPUARTx, uint32_t LPUART_IT)
{
    uint32_t bitpos = 0, itmask = 0, LPUARTreg = 0;
    ITStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_GET_IT(LPUART_IT));

    /* Get the LPUART register index */
    LPUARTreg = (((uint16_t)LPUART_IT) >> 0x08);
    /* Get the interrupt position */
    itmask = LPUART_IT & IT_MASK;
    itmask = (uint32_t)0x01 << itmask;

    if (LPUARTreg == 0x01) /* The IT  is in CR1 register */
    {
        itmask &= LPUARTx->CR1;
    }
    else if (LPUARTreg == 0x02) /* The IT  is in CR2 register */
    {
        itmask &= LPUARTx->CR2;
    }
    else /* The IT  is in CR3 register */
    {
        itmask &= LPUARTx->CR3;
    }

    bitpos = LPUART_IT >> 0x10;
    bitpos = (uint32_t)0x01 << bitpos;
    bitpos &= LPUARTx->ISR;

    if ((itmask != (uint16_t)RESET) && (bitpos != (uint16_t)RESET))
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * @brief  Clears the LPUARTx's interrupt pending bits.
  * @param  LPUARTx: LPUART peripheral.
  * @param  LPUART_IT: specifies the interrupt pending bit to clear.
  *         This parameter can be one of the following values:
  *            @arg LPUART_IT_WU:  Wake up interrupt, not available for   devices.
  *            @arg LPUART_IT_CM:  Character match interrupt.
  *            @arg LPUART_IT_CTS:  CTS change interrupt.
  *            @arg LPUART_IT_TC:  Transmission complete interrupt.
  *            @arg LPUART_IT_IDLE:  IDLE line detected interrupt.
  *            @arg LPUART_IT_ORE:  OverRun Error interrupt.
  *            @arg LPUART_IT_NE:  Noise Error interrupt.
  *            @arg LPUART_IT_FE:  Framing Error interrupt.
  *            @arg LPUART_IT_PE:  Parity Error interrupt.
  * @note   RXNE pending bit is cleared by a read to the LPUART_RDR register
  *         (LPUART_ReceiveData()) or by writing 1 to the RXFRQ in the register
  *         LPUART_RQR (LPUART_RequestCmd()).
  * @note   TC pending bit can be also cleared by software sequence: a read
  *         operation to LPUART_SR register (LPUART_GetITStatus()) followed by
  *         a write operation to LPUART_TDR register (LPUART_SendData()).
  * @note   TXE pending bit is cleared by a write to the LPUART_TDR register
  *         (LPUART_SendData()) or by writing 1 to the TXFRQ in the register
  *         LPUART_RQR (LPUART_RequestCmd()).
  * @retval None
  */
void LPUART_ClearITPendingBit(LPUART_TypeDef* LPUARTx, uint32_t LPUART_IT)
{
    uint32_t bitpos = 0, itmask = 0;
    /* Check the parameters */
    assert_param(IS_LPUART_PERIPH(LPUARTx));
    assert_param(IS_LPUART_CLEAR_IT(LPUART_IT));

    bitpos = LPUART_IT >> 0x10;
    itmask = ((uint32_t)0x01 << (uint32_t)bitpos);
    LPUARTx->ICR = (uint32_t)itmask;
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

/***************************** (C) COPYRIGHT HKMicroChip  *****************************/

