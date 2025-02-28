/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_eval_i2c_tsensor.c
* @brief:     This file provides a set of functions needed to manage the I2C LM75
*             temperature sensor mounted on HK32FL0XX-EVAL board.
*             It implements a high level communication layer for read and write
*             from/to this sensor. The needed HK32FL0XX hardware resources (I2C and
*             GPIO) are defined in hk32l0xx_eval.h file, and the initialization is
*             performed in LM75_LowLevel_Init() function declared in hk32l0xx_eval.c
*             file.
*             You can easily tailor this driver to any other development board,
*             by just adapting the defines for hardware resources and
*             LM75_LowLevel_Init() function.
*             +-----------------------------------------------------------------+
*             |                        Pin assignment                           |
*             +---------------------------------------+-----------+-------------+
*             |  HK32FL0XX I2C Pins                   |   STLM75  |   Pin       |
*             +---------------------------------------+-----------+-------------+
*             | LM75_I2C_SDA_PIN/ SDA                 |   SDA     |    1        |
*             | LM75_I2C_SCL_PIN/ SCL                 |   SCL     |    2        |
*             | LM75_I2C_SMBUSALERT_PIN/ SMBUS ALERT  |   OS/INT  |    3        |
*             | .                                     |   GND     |    4  (0V)  |
*             | .                                     |   GND     |    5  (0V)  |
*             | .                                     |   GND     |    6  (0V)  |
*             | .                                     |   GND     |    7  (0V)  |
*             | .                                     |   VDD     |    8  (3.3V)|
*             +---------------------------------------+-----------+-------------+
* @author:    AE Team
* @version:   V1.0.0/2023-10-10
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_eval_i2c_tsensor.h"

/** @addtogroup Boards
  * @{
  */

/** @addtogroup HK32_EVAL
  * @{
  */

/** @addtogroup HK32L0XX_EVAL
  * @{
  */

/** @addtogroup HK32L0XX_EVAL_I2C_TSENSOR
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define LM75_SD_SET                0x01 /* Set SD bit in the configuration register */
#define LM75_SD_RESET              0xFE /* Reset SD bit in the configuration register */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t  LM75Timeout = LM75_LONG_TIMEOUT;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup HK32FL0XX_EVAL_I2C_TSENSOR_Private_Functions
  * @{
  */
/**
  * @brief  DeInitializes peripherals used by the LM75 driver.
  * @param  None
  * @retval None
  */
void LM75_LowLevel_DeInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Disable LM75_I2C */
    I2C_Cmd(LM75_I2C, DISABLE);

    /* DeInitializes the LM75_I2C */
    I2C_DeInit(LM75_I2C);

    /* LM75_I2C Periph clock disable */
    RCC_APB1PeriphClockCmd(LM75_I2C_CLK, DISABLE);

    /* Configure LM75_I2C pins: SCL */
    GPIO_InitStructure.GPIO_Pin = LM75_I2C_SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(LM75_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

    /* Configure LM75_I2C pins: SDA */
    GPIO_InitStructure.GPIO_Pin = LM75_I2C_SDA_PIN;
    GPIO_Init(LM75_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);

    /* Configure LM75_I2C pin: SMBUS ALERT */
    GPIO_InitStructure.GPIO_Pin = LM75_I2C_SMBUSALERT_PIN;
    GPIO_Init(LM75_I2C_SMBUSALERT_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Initializes the I2C source clock and IOs used to drive the LM75
  * @param  None
  * @retval None
  */
void LM75_LowLevel_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* LM75_I2C Periph clock enable */
    RCC_APB1PeriphClockCmd(LM75_I2C_CLK, ENABLE);

    /* Configure the I2C clock source. The clock is derived from the HSI */
    RCC_I2C1CLKConfig(RCC_I2C1CLK_HSI8M);
    /* LM75_I2C_SCL_GPIO_CLK, LM75_I2C_SDA_GPIO_CLK
         and LM75_I2C_SMBUSALERT_GPIO_CLK Periph clock enable */
    RCC_AHBPeriphClockCmd(LM75_I2C_SCL_GPIO_CLK | LM75_I2C_SDA_GPIO_CLK |
                          LM75_I2C_SMBUSALERT_GPIO_CLK, ENABLE);

    /* Connect PXx to I2C_SCL */
    GPIO_PinAFConfig(LM75_I2C_SCL_GPIO_PORT, LM75_I2C_SCL_SOURCE, LM75_I2C_SCL_AF);

    /* Connect PXx to I2C_SDA */
    GPIO_PinAFConfig(LM75_I2C_SDA_GPIO_PORT, LM75_I2C_SDA_SOURCE, LM75_I2C_SDA_AF);

    /* Connect PXx to I2C_SMBUSALER */
    GPIO_PinAFConfig(LM75_I2C_SMBUSALERT_GPIO_PORT, LM75_I2C_SMBUSALERT_SOURCE, LM75_I2C_SMBUSALERT_AF);

    /* Configure LM75_I2C pins: SCL */
    GPIO_InitStructure.GPIO_Pin = LM75_I2C_SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(LM75_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

    /* Configure LM75_I2C pins: SDA */
    GPIO_InitStructure.GPIO_Pin = LM75_I2C_SDA_PIN;
    GPIO_Init(LM75_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);

    /* Configure LM75_I2C pin: SMBUS ALERT */
    GPIO_InitStructure.GPIO_Pin = LM75_I2C_SMBUSALERT_PIN;
    GPIO_Init(LM75_I2C_SMBUSALERT_GPIO_PORT, &GPIO_InitStructure);
}
/**
  * @brief  DeInitializes the LM75_I2C.
  * @param  None
  * @retval None
  */
void LM75_DeInit(void)
{
    LM75_LowLevel_DeInit();
}

/**
  * @brief  Initializes the LM75_I2C.
  * @param  None
  * @retval None
  */
void LM75_Init(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
    LM75_LowLevel_Init();

    /* LM75_I2C configuration */
    I2C_InitStructure.I2C_Mode = I2C_Mode_SMBusHost;
    I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
    I2C_InitStructure.I2C_DigitalFilter = 0x00;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_Timing = LM75_I2C_TIMING;

    /* Apply LM75_I2C configuration after enabling it */
    I2C_Init(LM75_I2C, &I2C_InitStructure);

    /* LM75_I2C Peripheral Enable */
    I2C_Cmd(LM75_I2C, ENABLE);
}

/**
  * @brief  Checks the LM75 status.
  * @param  None
  * @retval ErrorStatus: LM75 Status (ERROR or SUCCESS).
  */
ErrorStatus LM75_GetStatus(void)
{
    uint32_t I2C_TimeOut = I2C_TIMEOUT;

    /* Configure slave address, nbytes, reload, end mode and start or stop generation */
    I2C_TransferHandling(LM75_I2C, LM75_ADDR, 0, I2C_AutoEnd_Mode, I2C_No_StartStop);

    /* Clear NACKF and STOPF */
    I2C_ClearFlag(LM75_I2C, I2C_ICR_NACKCF | I2C_ICR_STOPCF);

    /* Generate start */
    I2C_GenerateSTART(LM75_I2C, ENABLE);

    /* Wait until timeout elapsed */
    while ((I2C_GetFlagStatus(LM75_I2C, I2C_ISR_STOPF) == RESET) && (I2C_TimeOut-- != 0))
    {
    }

    /* Check if Temp sensor is ready for use */
    if ((I2C_GetFlagStatus(LM75_I2C, I2C_ISR_NACKF) != RESET) || (I2C_TimeOut == 0))
    {
        /* Clear NACKF and STOPF */
        I2C_ClearFlag(LM75_I2C, I2C_ICR_NACKCF | I2C_ICR_STOPCF);
        return ERROR;
    }
    else
    {
        /* Clear STOPF */
        I2C_ClearFlag(LM75_I2C, I2C_ICR_STOPCF);
        return SUCCESS;
    }
}

/**
  * @brief  Read the specified register from the LM75.
  * @param  RegName: specifies the LM75 register to be read.
  *         This parameter can be one of the following values:
  *            @arg LM75_REG_TEMP: temperature register
  *            @arg LM75_REG_TOS: Over-limit temperature register
  *            @arg LM75_REG_THYS: Hysteresis temperature register
  * @retval LM75 register value.
  */
uint16_t LM75_ReadReg(uint8_t RegName)
{
    uint8_t LM75_BufferRX[2] = {0, 0};
    uint16_t tmp = 0;
    uint32_t DataNum = 0;

    /* Test on BUSY Flag */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_BUSY) != RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Configure slave address, nbytes, reload, end mode and start or stop generation */
    I2C_TransferHandling(LM75_I2C, LM75_ADDR, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);

    /* Wait until TXIS flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TXIS) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Send Register address */
    I2C_SendData(LM75_I2C, (uint8_t)RegName);

    /* Wait until TC flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TC) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Configure slave address, nbytes, reload, end mode and start or stop generation */
    I2C_TransferHandling(LM75_I2C, LM75_ADDR, 2, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);

    /* Reset local variable */
    DataNum = 0;

    /* Wait until all data are received */
    while (DataNum != 2)
    {
        /* Wait until RXNE flag is set */
        LM75Timeout = LM75_LONG_TIMEOUT;

        while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_RXNE) == RESET)
        {
            if ((LM75Timeout--) == 0)
            {
                return LM75_TIMEOUT_UserCallback();
            }
        }

        /* Read data from RXDR */
        LM75_BufferRX[DataNum] = I2C_ReceiveData(LM75_I2C);

        /* Update number of received data */
        DataNum++;
    }

    /* Wait until STOPF flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_STOPF) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Clear STOPF flag */
    I2C_ClearFlag(LM75_I2C, I2C_ICR_STOPCF);

    /* Store LM75_I2C received data */
    tmp = (uint16_t)(LM75_BufferRX[0] << 8);
    tmp |= LM75_BufferRX[1];

    /* return a Reg value */
    return (uint16_t)tmp;
}

/**
  * @brief  Write to the specified register of the LM75.
  * @param  RegName: specifies the LM75 register to be written.
  *         This parameter can be one of the following values:
  *            @arg LM75_REG_TOS: Over-limit temperature register
  *            @arg LM75_REG_THYS: Hysteresis temperature register
  * @param  RegValue: value to be written to LM75 register.
  * @retval None
  */
uint8_t LM75_WriteReg(uint8_t RegName, uint16_t RegValue)
{
    uint32_t DataNum = 0;
    uint8_t LM75_BufferTX[2] = {0, 0};
    LM75_BufferTX[0] = (uint8_t)(RegValue >> 8);
    LM75_BufferTX[1] = (uint8_t)(RegValue);

    /* Test on BUSY Flag */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_BUSY) != RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Configure slave address, nbytes, reload, end mode and start or stop generation */
    I2C_TransferHandling(LM75_I2C, LM75_ADDR, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);

    /* Wait until TXIS flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TXIS) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Send Register address */
    I2C_SendData(LM75_I2C, (uint8_t)RegName);

    /* Wait until TCR flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TCR) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Configure slave address, nbytes, reload, end mode and start or stop generation */
    I2C_TransferHandling(LM75_I2C, LM75_ADDR, 2, I2C_AutoEnd_Mode, I2C_No_StartStop);

    while (DataNum != 2)
    {
        /* Wait until TXIS flag is set */
        LM75Timeout = LM75_LONG_TIMEOUT;

        while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TXIS) == RESET)
        {
            if ((LM75Timeout--) == 0)
            {
                return LM75_TIMEOUT_UserCallback();
            }
        }

        /* Write data to TXDR */
        I2C_SendData(LM75_I2C, (uint8_t)(LM75_BufferTX[DataNum]));

        /* Update number of transmitted data */
        DataNum++;
    }

    /* Wait until STOPF flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_STOPF) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Clear STOPF flag */
    I2C_ClearFlag(LM75_I2C, I2C_ICR_STOPCF);
    return LM75_OK;
}

/**
  * @brief  Read Temperature register of LM75: double temperature value.
  * @param  None
  * @retval LM75 measured temperature value.
  */
uint16_t LM75_ReadTemp(void)
{
    uint8_t LM75_BufferRX[2] = {0, 0};
    uint16_t tmp = 0;
    uint32_t DataNum = 0;

    /* Test on BUSY Flag */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_BUSY) != RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Configure slave address, nbytes, reload, end mode and start or stop generation */
    I2C_TransferHandling(LM75_I2C, LM75_ADDR, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);

    /* Wait until TXIS flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TXIS) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Send Register address */
    I2C_SendData(LM75_I2C, (uint8_t)LM75_REG_TEMP);

    /* Wait until TC flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TC) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Configure slave address, nbytes, reload, end mode and start or stop generation */
    I2C_TransferHandling(LM75_I2C, LM75_ADDR, 2, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);

    /* Reset local variable */
    DataNum = 0;

    /* Wait until all data are received */
    while (DataNum != 2)
    {
        /* Wait until RXNE flag is set */
        LM75Timeout = LM75_LONG_TIMEOUT;

        while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_RXNE) == RESET)
        {
            if ((LM75Timeout--) == 0)
            {
                return LM75_TIMEOUT_UserCallback();
            }
        }

        /* Read data from RXDR */
        LM75_BufferRX[DataNum] = I2C_ReceiveData(LM75_I2C);

        /* Update number of received data */
        DataNum++;
    }

    /* Wait until STOPF flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_STOPF) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Clear STOPF flag */
    I2C_ClearFlag(LM75_I2C, I2C_ICR_STOPCF);

    /* Store LM75_I2C received data */
    tmp = (uint16_t)(LM75_BufferRX[0] << 8);
    tmp |= LM75_BufferRX[1];

    /* Return Temperature value */
    return (uint16_t)(tmp >> 7);
}

/**
  * @brief  Read the configuration register from the LM75.
  * @param  None
  * @retval LM75 configuration register value.
  */
uint8_t LM75_ReadConfReg(void)
{
    uint8_t LM75_BufferRX[2] = {0, 0};

    /* Test on BUSY Flag */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_BUSY) != RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Configure slave address, nbytes, reload, end mode and start or stop generation */
    I2C_TransferHandling(LM75_I2C, LM75_ADDR, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);

    /* Wait until TXIS flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TXIS) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Send Register address */
    I2C_SendData(LM75_I2C, (uint8_t)LM75_REG_CONF);

    /* Wait until TC flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TC) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Configure slave address, nbytes, reload, end mode and start or stop generation */
    I2C_TransferHandling(LM75_I2C, LM75_ADDR, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);

    /* Wait until RXNE flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_RXNE) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Read data from RXDR */
    LM75_BufferRX[0] = I2C_ReceiveData(LM75_I2C);

    /* Wait until STOPF flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_STOPF) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Clear STOPF flag */
    I2C_ClearFlag(LM75_I2C, I2C_ICR_STOPCF);

    /* Return Register value */
    return (uint8_t)LM75_BufferRX[0];
}

/**
  * @brief  Write to the configuration register of the LM75.
  * @param  RegValue: specifies the value to be written to LM75 configuration
  *         register.
  * @retval None
  */
uint8_t LM75_WriteConfReg(uint8_t RegValue)
{
    uint8_t LM75_BufferTX = 0;
    LM75_BufferTX = (uint8_t)(RegValue);

    /* Test on BUSY Flag */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_BUSY) != RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Configure slave address, nbytes, reload, end mode and start or stop generation */
    I2C_TransferHandling(LM75_I2C, LM75_ADDR, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);

    /* Wait until TXIS flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TXIS) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Send Register address */
    I2C_SendData(LM75_I2C, (uint8_t)LM75_REG_CONF);

    /* Wait until TCR flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TCR) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Configure slave address, nbytes, reload, end mode and start or stop generation */
    I2C_TransferHandling(LM75_I2C, LM75_ADDR, 1, I2C_AutoEnd_Mode, I2C_No_StartStop);

    /* Wait until TXIS flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TXIS) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Write data to TXDR */
    I2C_SendData(LM75_I2C, (uint8_t)LM75_BufferTX);

    /* Wait until STOPF flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_STOPF) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Clear STOPF flag */
    I2C_ClearFlag(LM75_I2C, I2C_ICR_STOPCF);
    return LM75_OK;
}

/**
  * @brief  Enables or disables the LM75.
  * @param  NewState: specifies the LM75 new status. This parameter can be ENABLE
  *         or DISABLE.
  * @retval None
  */
uint8_t LM75_ShutDown(FunctionalState NewState)
{
    uint8_t LM75_BufferRX[2] = {0, 0};
    uint8_t LM75_BufferTX = 0;
    __IO uint8_t RegValue = 0;

    /* Test on BUSY Flag */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_BUSY) != RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Configure slave address, nbytes, reload, end mode and start or stop generation */
    I2C_TransferHandling(LM75_I2C, LM75_ADDR, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);

    /* Wait until TXIS flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TXIS) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Send Register address */
    I2C_SendData(LM75_I2C, (uint8_t)LM75_REG_CONF);

    /* Wait until TC flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TC) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Configure slave address, nbytes, reload, end mode and start or stop generation */
    I2C_TransferHandling(LM75_I2C, LM75_ADDR, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);

    /* Wait until RXNE flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_RXNE) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Read data from RXDR */
    LM75_BufferRX[0] = I2C_ReceiveData(LM75_I2C);

    /* Wait until STOPF flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_STOPF) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Clear STOPF flag */
    I2C_ClearFlag(LM75_I2C, I2C_ICR_STOPCF);

    /* Get received data */
    RegValue = (uint8_t)LM75_BufferRX[0];

    /*---------------------------- Transmission Phase ---------------------------*/

    /* Enable or disable SD bit */
    if (NewState != DISABLE)
    {
        /* Enable LM75 */
        LM75_BufferTX = RegValue & LM75_SD_RESET;
    }
    else
    {
        /* Disable LM75 */
        LM75_BufferTX = RegValue | LM75_SD_SET;
    }

    /* Test on BUSY Flag */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_BUSY) != RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Configure slave address, nbytes, reload, end mode and start or stop generation */
    I2C_TransferHandling(LM75_I2C, LM75_ADDR, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);
    /* Wait until TXIS flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TXIS) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Send Register address */
    I2C_SendData(LM75_I2C, (uint8_t)LM75_REG_CONF);
    /* Wait until TCR flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TCR) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Configure slave address, nbytes, reload, end mode and start or stop generation */
    I2C_TransferHandling(LM75_I2C, LM75_ADDR, 1, I2C_AutoEnd_Mode, I2C_No_StartStop);
    /* Wait until TXIS flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_TXIS) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Write data to TXDR */
    I2C_SendData(LM75_I2C, (uint8_t)LM75_BufferTX);
    /* Wait until STOPF flag is set */
    LM75Timeout = LM75_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(LM75_I2C, I2C_ISR_STOPF) == RESET)
    {
        if ((LM75Timeout--) == 0)
        {
            return LM75_TIMEOUT_UserCallback();
        }
    }

    /* Clear STOPF flag */
    I2C_ClearFlag(LM75_I2C, I2C_ICR_STOPCF);
    return LM75_OK;
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

/**
  * @}
  */

