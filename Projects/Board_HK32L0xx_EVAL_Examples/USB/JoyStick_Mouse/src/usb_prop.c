/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_prop.c
* @brief:     All processing related to Joystick Mouse Demo.
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "usb_prop.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t ProtocolValue;

/* -------------------------------------------------------------------------- */
/*  Structures initializations */
/* -------------------------------------------------------------------------- */

DEVICE Device_Table =
{
    EP_NUM,
    1
};

DEVICE_PROP Device_Property =
{
    Joystick_init,
    Joystick_Reset,
    Joystick_Status_In,
    Joystick_Status_Out,
    Joystick_Data_Setup,
    Joystick_NoData_Setup,
    Joystick_Get_Interface_Setting,
    Joystick_GetDeviceDescriptor,
    Joystick_GetConfigDescriptor,
    Joystick_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
};
USER_STANDARD_REQUESTS User_Standard_Requests =
{
    Joystick_GetConfiguration,
    Joystick_SetConfiguration,
    Joystick_GetInterface,
    Joystick_SetInterface,
    Joystick_GetStatus,
    Joystick_ClearFeature,
    Joystick_SetEndPointFeature,
    Joystick_SetDeviceFeature,
    Joystick_SetDeviceAddress
};

ONE_DESCRIPTOR Device_Descriptor =
{
    (uint8_t*)Joystick_DeviceDescriptor,
    JOYSTICK_SIZ_DEVICE_DESC
};

ONE_DESCRIPTOR Config_Descriptor =
{
    (uint8_t*)Joystick_ConfigDescriptor,
    JOYSTICK_SIZ_CONFIG_DESC
};

ONE_DESCRIPTOR Joystick_Report_Descriptor =
{
    (uint8_t *)Joystick_ReportDescriptor,
    JOYSTICK_SIZ_REPORT_DESC
};

ONE_DESCRIPTOR Mouse_Hid_Descriptor =
{
    (uint8_t*)Joystick_ConfigDescriptor + JOYSTICK_OFF_HID_DESC,
    JOYSTICK_SIZ_HID_DESC
};

ONE_DESCRIPTOR String_Descriptor[4] =
{
    {(uint8_t*)Joystick_StringLangID, JOYSTICK_SIZ_STRING_LANGID},
    {(uint8_t*)Joystick_StringVendor, JOYSTICK_SIZ_STRING_VENDOR},
    {(uint8_t*)Joystick_StringProduct, JOYSTICK_SIZ_STRING_PRODUCT},
    {(uint8_t*)Joystick_StringSerial, JOYSTICK_SIZ_STRING_SERIAL}
};

/* Extern variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Extern function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Joystick Mouse init routine.
  * @retval None.
  */
void Joystick_init(void)
{
    /* Update the serial number string descriptor with the data from the unique ID*/
    Get_SerialNum();

    pInformation->Current_Configuration = 0;

    /* Connect the device */
    PowerOn();

    /* Perform basic device initialization operations */
    USB_SIL_Init();

    bDeviceState = UNCONNECTED;
}

/**
  * @brief  Joystick Mouse reset routine.
  * @retval None.
  */
void Joystick_Reset(void)
{
    /* Set Joystick_DEVICE as not configured */
    pInformation->Current_Configuration = 0;
    pInformation->Current_Interface = 0;/*the default Interface*/

    /* Current Feature initialization */
    pInformation->Current_Feature = Joystick_ConfigDescriptor[7];
    SetBTABLE(BTABLE_ADDRESS);

    /* Initialize Endpoint 0 */
    SetEPType(ENDP0, EP_CONTROL);
    SetEPTxStatus(ENDP0, EP_TX_STALL);
    SetEPRxAddr(ENDP0, ENDP0_RXADDR);
    SetEPTxAddr(ENDP0, ENDP0_TXADDR);
    Clear_Status_Out(ENDP0);
    SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
    SetEPRxValid(ENDP0);

    /* Initialize Endpoint 1 */
    SetEPType(ENDP1, EP_INTERRUPT);
    SetEPTxAddr(ENDP1, ENDP1_TXADDR);
    SetEPTxCount(ENDP1, 4);
    SetEPRxStatus(ENDP1, EP_RX_DIS);
    SetEPTxStatus(ENDP1, EP_TX_NAK);

    /* Set this device to response on default address */
    SetDeviceAddress(0);
    bDeviceState = ATTACHED;
}

/**
  * @brief  Update the device state to configured.
  * @retval None.
  */
void Joystick_SetConfiguration(void)
{
    DEVICE_INFO *pInfo = &Device_Info;

    if (pInfo->Current_Configuration != 0)
    {
        /* Device configured */
        bDeviceState = CONFIGURED;
    }
}

/**
  * @brief  Update the device state to addressed.
  * @retval None.
  */
void Joystick_SetDeviceAddress(void)
{
    bDeviceState = ADDRESSED;
}

/**
  * @brief  Joystick status IN routine.
  * @retval None.
  */
void Joystick_Status_In(void)
{}

/**
  * @brief  Joystick status OUT routine.
  * @retval None.
  */
void Joystick_Status_Out(void)
{}

/**
  * @brief  Handle the data class specific requests.
  * @param  Request Nb.
  * @retval USB_UNSUPPORT or USB_SUCCESS.
  */
RESULT Joystick_Data_Setup(uint8_t RequestNo)
{
    uint8_t *(*CopyRoutine)(uint16_t);

    CopyRoutine = NULL;

    if ((RequestNo == GET_DESCRIPTOR)
            && (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
            && (pInformation->USBwIndex0 == 0))
    {
        if (pInformation->USBwValue1 == REPORT_DESCRIPTOR)
        {
            CopyRoutine = Joystick_GetReportDescriptor;
        }
        else if (pInformation->USBwValue1 == HID_DESCRIPTOR_TYPE)
        {
            CopyRoutine = Joystick_GetHIDDescriptor;
        }

    } /* End of GET_DESCRIPTOR */

    /*** GET_PROTOCOL ***/
    else if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT)) && RequestNo == GET_PROTOCOL)
    {
        CopyRoutine = Joystick_GetProtocolValue;
    }

    if (CopyRoutine == NULL)
    {
        return USB_UNSUPPORT;
    }

    pInformation->Ctrl_Info.CopyData = CopyRoutine;
    pInformation->Ctrl_Info.Usb_wOffset = 0;
    (*CopyRoutine)(0);
    return USB_SUCCESS;
}

/**
  * @brief  handle the no data class specific requests
  * @param  Request Nb.
  * @retval USB_UNSUPPORT or USB_SUCCESS.
  */
RESULT Joystick_NoData_Setup(uint8_t RequestNo)
{
    if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT)) && (RequestNo == SET_PROTOCOL))
    {
        return Joystick_SetProtocol();
    }

    else
    {
        return USB_UNSUPPORT;
    }
}

/**
  * @brief  Gets the device descriptor.
  * @param  Length
  * @retval The address of the device descriptor.
  */
uint8_t *Joystick_GetDeviceDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/**
  * @brief  Gets the configuration descriptor.
  * @param  Length
  * @retval The address of the configuration descriptor.
  */
uint8_t *Joystick_GetConfigDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/**
  * @brief  Gets the string descriptors according to the needed index
  * @param  Length
  * @retval The address of the string descriptors.
  */
uint8_t *Joystick_GetStringDescriptor(uint16_t Length)
{
    uint8_t wValue0 = pInformation->USBwValue0;

    if (wValue0 >= 4)
    {
        return NULL;
    }
    else
    {
        return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
    }
}

/**
  * @brief  Gets the HID report descriptor.
  * @param  Length
  * @retval The address of the configuration descriptor.
  */
uint8_t *Joystick_GetReportDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Joystick_Report_Descriptor);
}

/**
  * @brief  Gets the HID descriptor.
  * @param  Length
  * @retval The address of the configuration descriptor.
  */
uint8_t *Joystick_GetHIDDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Mouse_Hid_Descriptor);
}

/**
  * @brief  tests the interface and the alternate setting according to the
  *         supported one.
  * @param  Interface : interface number.
  * @param  AlternateSetting : Alternate Setting number.
  * @retval USB_SUCCESS or USB_UNSUPPORT.
  */
RESULT Joystick_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
    if (AlternateSetting > 0)
    {
        return USB_UNSUPPORT;
    }
    else if (Interface > 0)
    {
        return USB_UNSUPPORT;
    }

    return USB_SUCCESS;
}

/**
  * @brief  Joystick Set Protocol request routine.
  * @retval USB SUCCESS.
  */
RESULT Joystick_SetProtocol(void)
{
    uint8_t wValue0 = pInformation->USBwValue0;
    ProtocolValue = wValue0;
    return USB_SUCCESS;
}

/**
  * @brief  get the protocol value
  * @param  Length.
  * @retval address of the protocol value.
  */
uint8_t *Joystick_GetProtocolValue(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = 1;
        return NULL;
    }
    else
    {
        return (uint8_t *)(&ProtocolValue);
    }
}

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/

