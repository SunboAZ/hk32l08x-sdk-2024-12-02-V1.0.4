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
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "hw_config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t Request = 0;

LINE_CODING linecoding =
{
    115200, /* baud rate*/
    0x00,   /* stop bits-1*/
    0x00,   /* parity - none*/
    0x08    /* no. of bits 8*/
};

/* --------------------------------------------------------------------------
                             Structures initializations
   -------------------------------------------------------------------------- */

DEVICE Device_Table =
{
    EP_NUM,
    1
};

DEVICE_PROP Device_Property =
{
    Virtual_Com_Port_init,
    Virtual_Com_Port_Reset,
    Virtual_Com_Port_Status_In,
    Virtual_Com_Port_Status_Out,
    Virtual_Com_Port_Data_Setup,
    Virtual_Com_Port_NoData_Setup,
    Virtual_Com_Port_Get_Interface_Setting,
    Virtual_Com_Port_GetDeviceDescriptor,
    Virtual_Com_Port_GetConfigDescriptor,
    Virtual_Com_Port_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
};

USER_STANDARD_REQUESTS User_Standard_Requests =
{
    Virtual_Com_Port_GetConfiguration,
    Virtual_Com_Port_SetConfiguration,
    Virtual_Com_Port_GetInterface,
    Virtual_Com_Port_SetInterface,
    Virtual_Com_Port_GetStatus,
    Virtual_Com_Port_ClearFeature,
    Virtual_Com_Port_SetEndPointFeature,
    Virtual_Com_Port_SetDeviceFeature,
    Virtual_Com_Port_SetDeviceAddress
};

ONE_DESCRIPTOR Device_Descriptor =
{
    (uint8_t*)Virtual_Com_Port_DeviceDescriptor,
    VIRTUAL_COM_PORT_SIZ_DEVICE_DESC
};

ONE_DESCRIPTOR Config_Descriptor =
{
    (uint8_t*)Virtual_Com_Port_ConfigDescriptor,
    VIRTUAL_COM_PORT_SIZ_CONFIG_DESC
};

ONE_DESCRIPTOR String_Descriptor[4] =
{
    {(uint8_t*)Virtual_Com_Port_StringLangID, VIRTUAL_COM_PORT_SIZ_STRING_LANGID},
    {(uint8_t*)Virtual_Com_Port_StringVendor, VIRTUAL_COM_PORT_SIZ_STRING_VENDOR},
    {(uint8_t*)Virtual_Com_Port_StringProduct, VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT},
    {(uint8_t*)Virtual_Com_Port_StringSerial, VIRTUAL_COM_PORT_SIZ_STRING_SERIAL}
};

/* Extern variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Extern function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Virtual COM Port Mouse init routine.
  * @retval None.
  */
void Virtual_Com_Port_init(void)
{
    /* Update the serial number string descriptor with the data from the unique
    ID*/
    Get_SerialNum();
    pInformation->Current_Configuration = 0;

    /* Connect the device */
    PowerOn();

    /* Perform basic device initialization operations */
    USB_SIL_Init();

    /* configure the USART to the default settings */
    USART_Config();
    bDeviceState = UNCONNECTED;
}

/**
  * @brief  Virtual_Com_Port Mouse reset routine
  * @retval None.
  */
void Virtual_Com_Port_Reset(void)
{
    /* Set Virtual_Com_Port DEVICE as not configured */
    pInformation->Current_Configuration = 0;

    /* Current Feature initialization */
    pInformation->Current_Feature = Virtual_Com_Port_ConfigDescriptor[7];

    /* Set Virtual_Com_Port DEVICE with the default Interface*/
    pInformation->Current_Interface = 0;
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
    SetEPType(ENDP1, EP_BULK);
    SetEPTxAddr(ENDP1, ENDP1_TXADDR);
    SetEPTxStatus(ENDP1, EP_TX_NAK);
    SetEPRxStatus(ENDP1, EP_RX_DIS);

    /* Initialize Endpoint 2 */
    SetEPType(ENDP2, EP_INTERRUPT);
    SetEPTxAddr(ENDP2, ENDP2_TXADDR);
    SetEPRxStatus(ENDP2, EP_RX_DIS);
    SetEPTxStatus(ENDP2, EP_TX_NAK);

    /* Initialize Endpoint 3 */
    SetEPType(ENDP3, EP_BULK);
    SetEPRxAddr(ENDP3, ENDP3_RXADDR);
    SetEPRxCount(ENDP3, VIRTUAL_COM_PORT_DATA_SIZE);
    SetEPRxStatus(ENDP3, EP_RX_VALID);
    SetEPTxStatus(ENDP3, EP_TX_DIS);

    /* Set this device to response on default address */
    SetDeviceAddress(0);
    bDeviceState = ATTACHED;
}

/**
  * @brief  Update the device state to configured.
  * @retval None.
  */
void Virtual_Com_Port_SetConfiguration(void)
{
    DEVICE_INFO* pInfo = &Device_Info;

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
void Virtual_Com_Port_SetDeviceAddress(void)
{
    bDeviceState = ADDRESSED;
}

/**
  * @brief  Virtual COM Port Status In Routine.
  * @retval None.
  */
void Virtual_Com_Port_Status_In(void)
{
    if (Request == SET_LINE_CODING)
    {
        USART_Config();
        Request = 0;
    }
}

/**
  * @brief  Virtual COM Port Status OUT Routine.
  * @retval None.
  */
void Virtual_Com_Port_Status_Out(void)
{}

/**
  * @brief  handle the data class specific requests
  * @param  Request Nb.
  * @retval USB_UNSUPPORT or USB_SUCCESS.
  */
RESULT Virtual_Com_Port_Data_Setup(uint8_t RequestNo)
{
    uint8_t*    (*CopyRoutine)(uint16_t);
    CopyRoutine = NULL;

    if (RequestNo == GET_LINE_CODING)
    {
        if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
        {
            CopyRoutine = Virtual_Com_Port_GetLineCoding;
        }
    }
    else if (RequestNo == SET_LINE_CODING)
    {
        if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
        {
            CopyRoutine = Virtual_Com_Port_SetLineCoding;
        }

        Request = SET_LINE_CODING;
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
  * @brief  handle the no data class specific requests.
  * @param  Request Nb.
  * @retval USB_UNSUPPORT or USB_SUCCESS.
  */
RESULT Virtual_Com_Port_NoData_Setup(uint8_t RequestNo)
{
    if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
    {
        if (RequestNo == SET_COMM_FEATURE)
        {
            return USB_SUCCESS;
        }
        else if (RequestNo == SET_CONTROL_LINE_STATE)
        {
            return USB_SUCCESS;
        }
    }

    return USB_UNSUPPORT;
}

/**
  * @brief  Gets the device descriptor.
  * @param  Length.
  * @retval The address of the device descriptor.
  */
uint8_t* Virtual_Com_Port_GetDeviceDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/**
  * @brief  get the configuration descriptor.
  * @param  Length.
  * @retval The address of the configuration descriptor.
  */
uint8_t* Virtual_Com_Port_GetConfigDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/**
  * @brief  Gets the string descriptors according to the needed index
  * @param  Length.
  * @retval The address of the string descriptors.
  */
uint8_t* Virtual_Com_Port_GetStringDescriptor(uint16_t Length)
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
  * @brief  test the interface and the alternate setting according to the
  *         supported one.
  * @param  Interface : interface number.
  * @param  AlternateSetting : Alternate Setting number.
  * @retval The address of the string descriptors.
  */
RESULT Virtual_Com_Port_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
    if (AlternateSetting > 0)
    {
        return USB_UNSUPPORT;
    }
    else if (Interface > 1)
    {
        return USB_UNSUPPORT;
    }

    return USB_SUCCESS;
}

/**
  * @brief  send the linecoding structure to the PC host.
  * @param  Length.
  * @retval Linecoding structure base address.
  */
uint8_t* Virtual_Com_Port_GetLineCoding(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = sizeof(linecoding);
        return NULL;
    }

    return (uint8_t*)&linecoding;
}

/**
  * @brief  Set the linecoding structure fields.
  * @param  Length.
  * @retval Linecoding structure base address.
  */
uint8_t* Virtual_Com_Port_SetLineCoding(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = sizeof(linecoding);
        return NULL;
    }

    return (uint8_t*)&linecoding;
}

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/


