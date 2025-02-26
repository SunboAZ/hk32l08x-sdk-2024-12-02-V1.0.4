/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hw_config.c
* @brief:     Hardware Configuration & Setup.
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "usb_pwr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
EXTI_InitTypeDef EXTI_InitStructure;
extern __IO uint32_t packet_sent;
extern __IO uint8_t Send_Buffer[VIRTUAL_COM_PORT_DATA_SIZE] ;
extern __IO  uint32_t packet_receive;
extern __IO uint8_t Receive_length;
extern LINE_CODING linecoding;
uint8_t Receive_Buffer[64];
uint32_t Send_length;

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void IntToUnicode(uint32_t value, uint8_t* pbuf, uint8_t len);

/**
  * @brief  Configures Main system clocks & power.
  * @retval None.
  */
void Set_System(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Enable all GPIOs Clock*/
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ALLGPIO, ENABLE);

    /*  Configure USB DM/DP pins                */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


#if 0

    /* USB_DISCONNECT used as USB pull-up */
    GPIO_InitStructure.GPIO_Pin = USB_DISCONNECT_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(USB_DISCONNECT, &GPIO_InitStructure);

    /* Enable the USB disconnect GPIO clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIO_DISCONNECT, ENABLE);
#endif
#ifdef USB_LOW_PWR_MGMT_SUPPORT

    /*Enable the PWR cloc*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    /**********************************************************************
        Configure the EXTI line 18 connected internally to the USB IP
     **********************************************************************/
    EXTI_ClearITPendingBit(EXTI_Line18);
    EXTI_InitStructure.EXTI_Line = EXTI_Line18;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
#endif  /* USB_LOW_PWR_MGMT_SUPPORT */
}

/**
  * @brief  Configures USB Clock input (48MHz).
  * @retval None.
  */
void Set_USBClock(void)
{
    /* Enable USB clock */

    /* Select USBCLK source 48Mhz */
    RCC_USBCLKConfig(RCC_USBCLK_PLL);

    /* Enable the USB clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/**
  * @brief  Restores system clocks and power while exiting suspend mode
  * @retval None.
  */
void Leave_LowPowerMode(void)
{
    DEVICE_INFO* pInfo = &Device_Info;

    /* Set the device state to the correct state */
    if (pInfo->Current_Configuration != 0)
    {
        /* Device configured */
        bDeviceState = CONFIGURED;
    }
    else
    {
        bDeviceState = ATTACHED;
    }

    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));

    /*Enable SystemCoreClock*/
    SystemInit();
    Set_USBClock();
}

/**
  * @brief  Configures the USB interrupts
  * @retval None.
  */
void USB_Interrupts_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable the USB interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USB_DVSQ_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}

/**
  * @brief  Software Connection/Disconnection of USB Cable
  * @retval Status
  */
void USB_Cable_Config(FunctionalState NewState)
{
#if 0

    if (NewState != DISABLE)
    {
        GPIO_ResetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
    }
    else
    {
        GPIO_SetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
    }

#endif
}

/**
  * @brief  Create the serial number string descriptor.
  * @retval None.
  */
void Get_SerialNum(void)
{
    uint32_t Device_Serial0, Device_Serial1, Device_Serial2;
    Device_Serial0 = *(uint32_t*)ID1;
    Device_Serial1 = *(uint32_t*)ID2;
    Device_Serial2 = *(uint32_t*)ID3;
    Device_Serial0 += Device_Serial2;

    if (Device_Serial0 != 0)
    {
        IntToUnicode(Device_Serial0, &Virtual_Com_Port_StringSerial[2], 8);
        IntToUnicode(Device_Serial1, &Virtual_Com_Port_StringSerial[18], 4);
    }
}

/**
  * @brief  Convert Hex 32Bits value into char.
  * @retval None.
  */
static void IntToUnicode(uint32_t value, uint8_t* pbuf, uint8_t len)
{
    uint8_t idx = 0;

    for (idx = 0 ; idx < len ; idx ++)
    {
        if (((value >> 28)) < 0xA)
        {
            pbuf[ 2 * idx] = (value >> 28) + '0';
        }
        else
        {
            pbuf[2 * idx] = (value >> 28) + 'A' - 10;
        }

        value = value << 4;
        pbuf[ 2 * idx + 1] = 0;
    }
}

/**
  * @brief  send the data received from the HK32 to the PC through USB
  * @retval None.
  */
uint32_t CDC_Send_DATA(uint8_t* ptrBuffer, uint8_t Send_length)
{
    /*if max buffer is Not reached*/
    if (Send_length < VIRTUAL_COM_PORT_DATA_SIZE)
    {
        /*Sent flag*/
        packet_sent = 0;

        /* send  packet to PMA*/
        UserToPMABufferCopy((unsigned char*)ptrBuffer, ENDP1_TXADDR, Send_length);
        SetEPTxCount(ENDP1, Send_length);
        SetEPTxValid(ENDP1);
    }
    else
    {
        return 0;
    }

    return 1;
}

/**
  * @brief  receive the data from the PC to HK32 and send it through USB
  * @retval None.
  */
uint32_t CDC_Receive_DATA(void)
{
    /*Receive flag*/
    packet_receive = 0;
    SetEPRxValid(ENDP3);
    return 1 ;
}

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/

