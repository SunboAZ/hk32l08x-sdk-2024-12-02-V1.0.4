/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_core.c
* @brief:     Standard protocol processing (USB v2.0).
* @author:    AE Team
* @version:   V1.0.0/2023-10-16
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"

/** @addtogroup HK32F39A_StdPeriph_Driver
  * @{
  */

/** @defgroup USB USB
  * @brief  USB driver modules
  * @{
  */

/** @defgroup usb_core usb_core
  * @{
    @verbatim
 ===============================================================================
                        ##### usb_core.c explain #####
 ===============================================================================
....[..]
   (#) This module is the "kernel" of the library. It implements all the functions described in
       Chapter 9 of the USB 2.0 specification.
   (#) The available subroutines cover handling of USB standard requests related to the control
       endpoint (ENDP0), offering the necessary code to accomplish the sequence of enumeration
       phase.
   (#) A state machine is implemented in order to process the different stages of the setup
       transactions.
   (#) The USB core module also implements a dynamic interface between the standard request
       and the user implementation using the structure User_Standard_Requests.
   (#) The USB core dispatches the class specific requests and some bus events to user program
       whenever it is necessary. User handling procedures are given in the Device_Property
       structure.
   (#) The different data and function structures used by the kernel are described in the following
       paragraphs.
    @endverbatim
  *
  ******************************************************************************
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup usb_core_Private_Defines usb_core_Private_Defines
  * @{
  */

#define ValBit(VAR,Place)    (VAR & (1 << Place))
#define SetBit(VAR,Place)    (VAR |= (1 << Place))
#define ClrBit(VAR,Place)    (VAR &= ((1 << Place) ^ 255))
#define Send0LengthData() { _SetEPTxCount(ENDP0, 0); \
        vSetEPTxStatus(EP_TX_VALID); \
    }

#define vSetEPRxStatus(st) (SaveRState = st)
#define vSetEPTxStatus(st) (SaveTState = st)

#define USB_StatusIn() Send0LengthData()
#define USB_StatusOut() vSetEPRxStatus(EP_RX_VALID)

#define StatusInfo0 StatusInfo.bw.bb1 /* Reverse bb0 & bb1 */
#define StatusInfo1 StatusInfo.bw.bb0

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup usb_core_Private_Variables usb_core_Private_Variables
  * @{
  */

uint16_t_uint8_t StatusInfo;
bool Data_Mul_MaxPacketSize = FALSE;

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/** @defgroup usb_core_Function_Prototypes usb_core_Function_Prototypes
  * @{
  */

static void DataStageOut(void);
static void DataStageIn(void);
static void NoData_Setup0(void);
static void Data_Setup0(void);

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/** @defgroup usb_core_Private_Functions usb_core_Private_Functions
  * @{
  */

/**
  * @brief  Return the current configuration variable address.
  * @param  Length: How many bytes are needed.
  * @retval Return 1 , if the request is invalid when "Length" is 0.
  *         Return "Buffer" if the "Length" is not 0.
  */
uint8_t *Standard_GetConfiguration(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = sizeof(pInformation->Current_Configuration);
        return 0;
    }

    pUser_Standard_Requests->User_GetConfiguration();
    return (uint8_t *)&pInformation->Current_Configuration;
}

/**
  * @brief  This routine is called to set the configuration value
  *         Then each class should configure device itself.
  * @retval Return USB_SUCCESS, if the request is performed.
  *         Return USB_UNSUPPORT, if the request is invalid.
  */
RESULT Standard_SetConfiguration(void)
{
    if ((pInformation->USBwValue0 <= Device_Table.Total_Configuration) && 
        (pInformation->USBwValue1 == 0) && 
        (pInformation->USBwIndex == 0)) /*call Back usb spec 2.0*/
    {
        pInformation->Current_Configuration = pInformation->USBwValue0;
        pUser_Standard_Requests->User_SetConfiguration();
        return USB_SUCCESS;
    }
    else
    {
        return USB_UNSUPPORT;
    }
}

/**
  * @brief  Return the Alternate Setting of the current interface.
  * @param  Length: How many bytes are needed.
  * @retval Return 0, if the request is invalid when "Length" is 0.
  *         Return "Buffer" if the "Length" is not 0.
  */
uint8_t *Standard_GetInterface(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = sizeof(pInformation->Current_AlternateSetting);
        return 0;
    }

    pUser_Standard_Requests->User_GetInterface();
    return (uint8_t *)&pInformation->Current_AlternateSetting;
}

/**
  * @brief  This routine is called to set the interface.
  *         Then each class should configure the interface them self.
  * @retval Return USB_SUCCESS, if the request is performed.
  *         Return USB_UNSUPPORT, if the request is invalid.
  */
RESULT Standard_SetInterface(void)
{
    RESULT Re;
    /*Test if the specified Interface and Alternate Setting are supported by
    the application Firmware*/
    Re = (*pProperty->Class_Get_Interface_Setting)(pInformation->USBwIndex0, pInformation->USBwValue0);

    if (pInformation->Current_Configuration != 0)
    {
        if ((Re != USB_SUCCESS) || (pInformation->USBwIndex1 != 0) || (pInformation->USBwValue1 != 0))
        {
            return  USB_UNSUPPORT;
        }
        else if (Re == USB_SUCCESS)
        {
            pUser_Standard_Requests->User_SetInterface();
            pInformation->Current_Interface = pInformation->USBwIndex0;
            pInformation->Current_AlternateSetting = pInformation->USBwValue0;
            return USB_SUCCESS;
        }
    }

    return USB_UNSUPPORT;
}

/**
  * @brief  Copy the device request data to "StatusInfo buffer".
  * @param  Length: How many bytes are needed.
  * @retval Return 0, if the request is at end of data block,
  *         or is invalid when "Length" is 0.
  */
uint8_t *Standard_GetStatus(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = 2;
        return 0;
    }

    /* Reset Status Information */
    StatusInfo.w = 0;

    if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
    {
        /*Get Device Status */
        uint8_t Feature = pInformation->Current_Feature;

        /* Remote Wakeup enabled */
        if (ValBit(Feature, 5))
        {
            SetBit(StatusInfo0, 1);
        }
        else
        {
            ClrBit(StatusInfo0, 1);
        }

        /* Bus-powered */
        if (ValBit(Feature, 6))
        {
            SetBit(StatusInfo0, 0);
        }
        else /* Self-powered */
        {
            ClrBit(StatusInfo0, 0);
        }
    }
    /*Interface Status*/
    else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
    {
        return (uint8_t *)&StatusInfo;
    }
    /*Get EndPoint Status*/
    else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
    {
        uint8_t Related_Endpoint;
        uint8_t wIndex0 = pInformation->USBwIndex0;

        Related_Endpoint = (wIndex0 & 0x0f);

        if (ValBit(wIndex0, 7))
        {
            /* IN endpoint */
            if (_GetTxStallStatus(Related_Endpoint))
            {
                SetBit(StatusInfo0, 0); /* IN Endpoint stalled */
            }
        }
        else
        {
            /* OUT endpoint */
            if (_GetRxStallStatus(Related_Endpoint))
            {
                SetBit(StatusInfo0, 0); /* OUT Endpoint stalled */
            }
        }
    }
    else
    {
        return NULL;
    }

    pUser_Standard_Requests->User_GetStatus();
    return (uint8_t *)&StatusInfo;
}

/**
  * @brief  Clear or disable a specific feature.
  * @retval Return USB_SUCCESS, if the request is performed.
  *         Return USB_UNSUPPORT, if the request is invalid.
  */
RESULT Standard_ClearFeature(void)
{
    uint32_t     Type_Rec = Type_Recipient;
    uint32_t     Status;


    if (Type_Rec == (STANDARD_REQUEST | DEVICE_RECIPIENT))
    {
        /*Device Clear Feature*/
        ClrBit(pInformation->Current_Feature, 5);
        return USB_SUCCESS;
    }
    else if (Type_Rec == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
    {
        /*EndPoint Clear Feature*/
        DEVICE* pDev;
        uint32_t Related_Endpoint;
        uint32_t wIndex0;
        uint32_t rEP;

        if ((pInformation->USBwValue != ENDPOINT_STALL) || (pInformation->USBwIndex1 != 0))
        {
            return USB_UNSUPPORT;
        }

        pDev = &Device_Table;
        wIndex0 = pInformation->USBwIndex0;
        rEP = wIndex0 & ~0x80;
        Related_Endpoint = ENDP0 + rEP;

        if (ValBit(pInformation->USBwIndex0, 7))
        {
            /*Get Status of endpoint & stall the request if the related_ENdpoint
            is Disabled*/
            Status = _GetEPTxStatus(Related_Endpoint);
        }
        else
        {
            Status = _GetEPRxStatus(Related_Endpoint);
        }

        if ((rEP >= pDev->Total_Endpoint) || (Status == 0) || (pInformation->Current_Configuration == 0))
        {
            return USB_UNSUPPORT;
        }


        if (wIndex0 & 0x80)
        {
            /* IN endpoint */
            if (_GetTxStallStatus(Related_Endpoint ))
            {
                ClearDTOG_TX(Related_Endpoint);
                SetEPTxStatus(Related_Endpoint, EP_TX_VALID);
            }
        }
        else
        {
            /* OUT endpoint */
            if (_GetRxStallStatus(Related_Endpoint))
            {
                if (Related_Endpoint == ENDP0)
                {
                    /* After clear the STALL, enable the default endpoint receiver */
                    SetEPRxCount(Related_Endpoint, Device_Property.MaxPacketSize);
                    _SetEPRxStatus(Related_Endpoint, EP_RX_VALID);
                }
                else
                {
                    ClearDTOG_RX(Related_Endpoint);
                    _SetEPRxStatus(Related_Endpoint, EP_RX_VALID);
                }
            }
        }

        pUser_Standard_Requests->User_ClearFeature();
        return USB_SUCCESS;
    }

    return USB_UNSUPPORT;
}

/**
  * @brief  Set or enable a specific feature of EndPoint
  * @retval Return USB_SUCCESS, if the request is performed.
  *         Return USB_UNSUPPORT, if the request is invalid.
  */
RESULT Standard_SetEndPointFeature(void)
{
    uint32_t    wIndex0;
    uint32_t    Related_Endpoint;
    uint32_t    rEP;
    uint32_t    Status;

    wIndex0 = pInformation->USBwIndex0;
    rEP = wIndex0 & ~0x80;
    Related_Endpoint = ENDP0 + rEP;

    if (ValBit(pInformation->USBwIndex0, 7))
    {
        /* get Status of endpoint & stall the request if the related_ENdpoint
        is Disabled*/
        Status = _GetEPTxStatus(Related_Endpoint);
    }
    else
    {
        Status = _GetEPRxStatus(Related_Endpoint);
    }

    if (Related_Endpoint >= Device_Table.Total_Endpoint || 
        pInformation->USBwValue != 0 || 
        Status == 0 || 
        pInformation->Current_Configuration == 0)
    {
        return USB_UNSUPPORT;
    }
    else
    {
        if (wIndex0 & 0x80)
        {
            /* IN endpoint */
            _SetEPTxStatus(Related_Endpoint, EP_TX_STALL);
        }

        else
        {
            /* OUT endpoint */
            _SetEPRxStatus(Related_Endpoint, EP_RX_STALL);
        }
    }

    pUser_Standard_Requests->User_SetEndPointFeature();
    return USB_SUCCESS;
}

/**
  * @brief  Set or enable a specific feature of Device.
  * @retval Return USB_SUCCESS, if the request is performed.
  *         Return USB_UNSUPPORT, if the request is invalid.
  */
RESULT Standard_SetDeviceFeature(void)
{
    SetBit(pInformation->Current_Feature, 5);
    pUser_Standard_Requests->User_SetDeviceFeature();
    return USB_SUCCESS;
}

/**
  * @brief  Standard_GetDescriptorData is used for descriptors transfer.
  *         This routine is used for the descriptors resident in Flash
  *         or RAM pDesc can be in either Flash or RAM
  *         The purpose of this routine is to have a versatile way to
  *         response descriptors request. It allows user to generate
  *         certain descriptors with software or read descriptors from
  *         external storage part by part.
  * @param  Length: Length of the data in this transfer.
  * @param  pDesc: A pointer points to descriptor struct.
    *                     The structure gives the initial address of the descriptor and
    *                     its original size.
  * @retval Address of a part of the descriptor pointed by the Usb_wOffset
  *         The buffer pointed by this address contains at least
  *         Length bytes.
*/
uint8_t *Standard_GetDescriptorData(uint16_t Length, ONE_DESCRIPTOR *pDesc)
{
    uint32_t  wOffset;

    wOffset = pInformation->Ctrl_Info.Usb_wOffset;

    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = pDesc->Descriptor_Size - wOffset;
        return 0;
    }

    return pDesc->Descriptor + wOffset;
}

/**
  * @brief  Data stage of a Control Write Transfer.
  * @retval None.
  */
void DataStageOut(void)
{
    ENDPOINT_INFO *pEPinfo = &pInformation->Ctrl_Info;
    uint32_t save_rLength;

    save_rLength = pEPinfo->Usb_rLength;

    if (pEPinfo->CopyData && save_rLength)
    {
        uint8_t *Buffer;
        uint32_t Length;

        Length = pEPinfo->PacketSize;

        if (Length > save_rLength)
        {
            Length = save_rLength;
        }

        Buffer = (*pEPinfo->CopyData)(Length);
        pEPinfo->Usb_rLength -= Length;
        pEPinfo->Usb_rOffset += Length;
        PMAToUserBufferCopy(Buffer, GetEPRxAddr(ENDP0), Length);
    }

    if (pEPinfo->Usb_rLength != 0)
    {
        vSetEPRxStatus(EP_RX_VALID);/* re-enable for next data reception */
        SetEPTxCount(ENDP0, 0);
        vSetEPTxStatus(EP_TX_VALID);/* Expect the host to abort the data OUT stage */
    }

    /* Set the next State*/
    if (pEPinfo->Usb_rLength >= pEPinfo->PacketSize)
    {
        pInformation->ControlState = OUT_DATA;
    }
    else
    {
        if (pEPinfo->Usb_rLength > 0)
        {
            pInformation->ControlState = LAST_OUT_DATA;
        }
        else if (pEPinfo->Usb_rLength == 0)
        {
            /* USB spec: section 8.5.3.1 Reporting Status Results */
            pInformation->ControlState = WAIT_STATUS_IN;
            (*pProperty->Process_Status_IN)();

            if (pInformation->ControlState == STALLED)
            {
                /* command failed to complete:
                in this case we should return a STALL */
                vSetEPRxStatus(EP_RX_STALL);
                vSetEPTxStatus(EP_TX_STALL);
            }
            /* command completed successfully:
            send a zero-length packet during status stage */
            else
            {
                USB_StatusIn();
            }
        }
    }
}

/**
  * @brief  Data stage of a Control Read Transfer.
  * @retval None.
  */
void DataStageIn(void)
{
    ENDPOINT_INFO *pEPinfo = &pInformation->Ctrl_Info;
    uint32_t save_wLength = pEPinfo->Usb_wLength;
    uint32_t ControlState = pInformation->ControlState;

    uint8_t *DataBuffer;
    uint32_t Length;

    if ((save_wLength == 0) && (ControlState == LAST_IN_DATA))
    {
        if (Data_Mul_MaxPacketSize == TRUE)
        {
            /* No more data to send and empty packet */
            Send0LengthData();
            ControlState = LAST_IN_DATA;
            Data_Mul_MaxPacketSize = FALSE;
        }
        else
        {
            /* No more data to send so STALL the TX Status*/
            ControlState = WAIT_STATUS_OUT;
            vSetEPTxStatus(EP_TX_STALL);
        }

        goto Expect_Status_Out;
    }

    Length = pEPinfo->PacketSize;
    ControlState = (save_wLength <= Length) ? LAST_IN_DATA : IN_DATA;

    if (Length > save_wLength)
    {
        Length = save_wLength;
    }

    DataBuffer = (*pEPinfo->CopyData)(Length);

    UserToPMABufferCopy(DataBuffer, GetEPTxAddr(ENDP0), Length);

    SetEPTxCount(ENDP0, Length);

    pEPinfo->Usb_wLength -= Length;
    pEPinfo->Usb_wOffset += Length;
    vSetEPTxStatus(EP_TX_VALID);

    USB_StatusOut();/* Expect the host to abort the data IN stage */

Expect_Status_Out:
    pInformation->ControlState = ControlState;
}

/**
  * @brief  Proceed the processing of setup request without data stage.
  * @retval None.
  */
void NoData_Setup0(void)
{
    RESULT Result = USB_UNSUPPORT;
    uint32_t RequestNo = pInformation->USBbRequest;
    uint32_t ControlState;

#if (USB_CORE_DEBUG==1)
    printf("NoData_Setup0\r\n");
#endif

    if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
    {
        /* Device Request*/
        /* SET_CONFIGURATION*/
        if (RequestNo == SET_CONFIGURATION)
        {
            Result = Standard_SetConfiguration();
        }

        /*SET ADDRESS*/
        else if (RequestNo == SET_ADDRESS)
        {
            if ((pInformation->USBwValue0 > 127) 
             || (pInformation->USBwValue1 != 0)
             || (pInformation->USBwIndex != 0)
             || (pInformation->Current_Configuration != 0))
                /* Device Address should be 127 or less*/
            {
                ControlState = STALLED;
                goto exit_NoData_Setup0;
            }
            else
            {
                Result = USB_SUCCESS;
            }
        }
        /*SET FEATURE for Device*/
        else if (RequestNo == SET_FEATURE)
        {
            if ((pInformation->USBwValue0 == DEVICE_REMOTE_WAKEUP) && (pInformation->USBwIndex == 0))
            {
                Result = Standard_SetDeviceFeature();
            }
            else
            {
                Result = USB_UNSUPPORT;
            }
        }
        /*Clear FEATURE for Device */
        else if (RequestNo == CLEAR_FEATURE)
        {
            if (pInformation->USBwValue0 == DEVICE_REMOTE_WAKEUP
             && pInformation->USBwIndex == 0
             && ValBit(pInformation->Current_Feature, 5))
            {
                Result = Standard_ClearFeature();
            }
            else
            {
                Result = USB_UNSUPPORT;
            }
        }
    }

    /* Interface Request*/
    else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
    {
        /*SET INTERFACE*/
        if (RequestNo == SET_INTERFACE)
        {
            Result = Standard_SetInterface();
        }
    }

    /* EndPoint Request*/
    else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
    {
        /*CLEAR FEATURE for EndPoint*/
        if (RequestNo == CLEAR_FEATURE)
        {
            Result = Standard_ClearFeature();
        }
        /* SET FEATURE for EndPoint*/
        else if (RequestNo == SET_FEATURE)
        {
            Result = Standard_SetEndPointFeature();
        }
    }
    else
    {
        Result = USB_UNSUPPORT;
    }


    if (Result != USB_SUCCESS)
    {
        Result = (*pProperty->Class_NoData_Setup)(RequestNo);

        if (Result == USB_NOT_READY)
        {
            ControlState = PAUSE;
            goto exit_NoData_Setup0;
        }
    }

    if (Result != USB_SUCCESS)
    {
        ControlState = STALLED;

        goto exit_NoData_Setup0;
    }

    ControlState = WAIT_STATUS_IN;/* After no data stage SETUP */

#if (USB_CORE_DEBUG==1)
    printf("Send 0 length data\r\n");
#endif
    USB_StatusIn();

exit_NoData_Setup0:
    pInformation->ControlState = ControlState;
    return;
}

/**
  * @brief  Proceed the processing of setup request with data stage.
  * @retval None.
  */
void Data_Setup0(void)
{
    uint8_t *(*CopyRoutine)(uint16_t);
    RESULT Result;
    uint32_t Request_No = pInformation->USBbRequest;

    uint32_t Related_Endpoint, Reserved;
    uint32_t wOffset, Status;

#if (USB_CORE_DEBUG==1)
    printf("Data_Setup0\r\n");
#endif

    CopyRoutine = NULL;
    wOffset = 0;

    /*GET DESCRIPTOR*/
    if (Request_No == GET_DESCRIPTOR)
    {
#if (USB_CORE_DEBUG==1)
        printf("Get DESC");
#endif

        if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
        {
            uint8_t wValue1 = pInformation->USBwValue1;

            if (wValue1 == DEVICE_DESCRIPTOR)
            {
                CopyRoutine = pProperty->GetDeviceDescriptor;
            }

#ifdef LPM_ENABLED
            else if (wValue1 == DEVICE_BOS_DESCRIPTOR)
            {
                CopyRoutine = pProperty->GetBosDescriptor;
            }

#endif
            else if (wValue1 == CONFIG_DESCRIPTOR)
            {
                CopyRoutine = pProperty->GetConfigDescriptor;
            }
            else if (wValue1 == STRING_DESCRIPTOR)
            {
                CopyRoutine = pProperty->GetStringDescriptor;
            }  /* End of GET_DESCRIPTOR */
            else if (wValue1 == 0x06)
            {
                SetEPRxStatus(ENDP0, EP_RX_STALL);
		        SetEPTxStatus(ENDP0, EP_TX_STALL);
            }  /* End of GET_DESCRIPTOR */
        }
    }

    /*GET STATUS*/
    else if ((Request_No == GET_STATUS) && 
             (pInformation->USBwValue == 0) && 
             (pInformation->USBwLength == 0x0002) && 
             (pInformation->USBwIndex1 == 0))
    {
#if (USB_CORE_DEBUG == 1)
        printf("GET STATUS\r\n");
#endif

        /* GET STATUS for Device*/
        if ((Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT)) && 
            (pInformation->USBwIndex == 0))
        {
            CopyRoutine = Standard_GetStatus;
        }

        /* GET STATUS for Interface*/
        else if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
        {
            if (((*pProperty->Class_Get_Interface_Setting)(pInformation->USBwIndex0, 0) == USB_SUCCESS) && (pInformation->Current_Configuration != 0))
            {
                CopyRoutine = Standard_GetStatus;
            }
        }

        /* GET STATUS for EndPoint*/
        else if (Type_Recipient == (STANDARD_REQUEST | ENDPOINT_RECIPIENT))
        {
            Related_Endpoint = (pInformation->USBwIndex0 & 0x0f);
            Reserved = pInformation->USBwIndex0 & 0x70;

            if (ValBit(pInformation->USBwIndex0, 7))
            {
                /*Get Status of endpoint & stall the request if the related_ENdpoint
                is Disabled*/
                Status = _GetEPTxStatus(Related_Endpoint);
            }
            else
            {
                Status = _GetEPRxStatus(Related_Endpoint);
            }

            if ((Related_Endpoint < Device_Table.Total_Endpoint) && (Reserved == 0) && (Status != 0))
            {
                CopyRoutine = Standard_GetStatus;
            }
        }
    }

    /*GET CONFIGURATION*/
    else if (Request_No == GET_CONFIGURATION)
    {
        if (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT))
        {
            CopyRoutine = Standard_GetConfiguration;
        }
    }
    /*GET INTERFACE*/
    else if (Request_No == GET_INTERFACE)
    {
        if ((Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT)) && 
            (pInformation->Current_Configuration != 0) && 
            (pInformation->USBwValue == 0) && 
            (pInformation->USBwIndex1 == 0) && 
            (pInformation->USBwLength == 0x0001) && 
            ((*pProperty->Class_Get_Interface_Setting)(pInformation->USBwIndex0, 0) == USB_SUCCESS))
        {
            CopyRoutine = Standard_GetInterface;
        }
    }

    if (CopyRoutine)
    {
        pInformation->Ctrl_Info.Usb_wOffset = wOffset;
        pInformation->Ctrl_Info.CopyData = CopyRoutine;
        /* sb in the original the cast to word was directly */
        /* now the cast is made step by step */
        (*CopyRoutine)(0);
        Result = USB_SUCCESS;
    }
    else
    {
        Result = (*pProperty->Class_Data_Setup)(pInformation->USBbRequest);

        if (Result == USB_NOT_READY)
        {
            pInformation->ControlState = PAUSE;
            return;
        }
    }

    if (pInformation->Ctrl_Info.Usb_wLength == 0xFFFF)
    {
        /* Data is not ready, wait it */
        pInformation->ControlState = PAUSE;
        return;
    }

    if ((Result == USB_UNSUPPORT) || (pInformation->Ctrl_Info.Usb_wLength == 0))
    {
        /* Unsupported request */
        pInformation->ControlState = STALLED;

        return;
    }


    if (ValBit(pInformation->USBbmRequestType, 7))
    {
        /* Device ==> Host */
        __IO uint32_t wLength = pInformation->USBwLength;

        /* Restrict the data length to be the one host asks for */
        if (pInformation->Ctrl_Info.Usb_wLength > wLength)
        {
            pInformation->Ctrl_Info.Usb_wLength = wLength;
        }

        else if (pInformation->Ctrl_Info.Usb_wLength < pInformation->USBwLength)
        {
            if (pInformation->Ctrl_Info.Usb_wLength < pProperty->MaxPacketSize)
            {
                Data_Mul_MaxPacketSize = FALSE;
            }
            else if ((pInformation->Ctrl_Info.Usb_wLength % pProperty->MaxPacketSize) == 0)
            {
                Data_Mul_MaxPacketSize = TRUE;
            }
        }

        pInformation->Ctrl_Info.PacketSize = pProperty->MaxPacketSize;
        DataStageIn();
    }
    else
    {
        pInformation->ControlState = OUT_DATA;
        vSetEPRxStatus(EP_RX_VALID); /* enable for next data reception */
    }

    return;
}

/**
  * @brief  Get the device request data and dispatch to individual process.
  * @retval Post0_Process.
  */
uint8_t Setup0_Process(void)
{

    union
    {
        uint8_t* b;
        uint16_t* w;
    } pBuf;

    uint16_t offset = 1;

    pBuf.b = PMAAddr + (uint8_t *)(_GetEPRxAddr(ENDP0) * 2); /* *2 for 32 bits addr */

    if (pInformation->ControlState != PAUSE)
    {
        pInformation->USBbmRequestType = *pBuf.b++; /* bmRequestType */
        pInformation->USBbRequest = *pBuf.b++; /* bRequest */
        pBuf.w += offset;  /* word not accessed because of 32 bits addressing */
        pInformation->USBwValue = ByteSwap(*pBuf.w++); /* wValue */
        pBuf.w += offset;  /* word not accessed because of 32 bits addressing */
        pInformation->USBwIndex  = ByteSwap(*pBuf.w++); /* wIndex */
        pBuf.w += offset;  /* word not accessed because of 32 bits addressing */
        pInformation->USBwLength = *pBuf.w; /* wLength */
    }

    pInformation->ControlState = SETTING_UP;

    if (pInformation->USBwLength == 0)
    {
        /* Setup with no data stage */
        NoData_Setup0();
    }
    else
    {
        /* Setup with data stage */
        Data_Setup0();
    }

    return Post0_Process();
}

/**
  * @brief  Process the IN token on all default endpoint.
  * @retval Post0_Process.
  */
uint8_t In0_Process(void)
{
    uint32_t ControlState = pInformation->ControlState;

    if ((ControlState == IN_DATA) || (ControlState == LAST_IN_DATA))
    {
        DataStageIn();
        /* ControlState may be changed outside the function */
        ControlState = pInformation->ControlState;
    }

    else if (ControlState == WAIT_STATUS_IN)
    {
        if ((pInformation->USBbRequest == SET_ADDRESS) && (Type_Recipient == (STANDARD_REQUEST | DEVICE_RECIPIENT)))
        {
            SetDeviceAddress(pInformation->USBwValue0);
            pUser_Standard_Requests->User_SetDeviceAddress();
        }

        (*pProperty->Process_Status_IN)();
        ControlState = STALLED;
    }

    else
    {
        ControlState = STALLED;
    }

    pInformation->ControlState = ControlState;

    return Post0_Process();
}

/**
  * @brief  Process the OUT token on all default endpoint.
  * @retval Post0_Process.
  */
uint8_t Out0_Process(void)
{
    uint32_t ControlState = pInformation->ControlState;

    if ((ControlState == IN_DATA) || (ControlState == LAST_IN_DATA))
    {
        /* host aborts the transfer before finish */
        ControlState = STALLED;
    }
    else if ((ControlState == OUT_DATA) || (ControlState == LAST_OUT_DATA))
    {
        DataStageOut();
        ControlState = pInformation->ControlState; /* may be changed outside the function */
    }

    else if (ControlState == WAIT_STATUS_OUT)
    {
        (*pProperty->Process_Status_OUT)();
        ControlState = STALLED;
    }


    /* Unexpect state, STALL the endpoint */
    else
    {
        ControlState = STALLED;
    }

    pInformation->ControlState = ControlState;

    return Post0_Process();
}

/**
  * @brief  Stall the Endpoint 0 in case of error.
  * @retval 0 if the control State is in PAUSE
  *         1 if not.
  */
uint8_t Post0_Process(void)
{
    SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);

    if (pInformation->ControlState == STALLED)
    {
        vSetEPRxStatus(EP_RX_STALL);
        vSetEPTxStatus(EP_TX_STALL);
    }

    return (pInformation->ControlState == PAUSE);
}

/**
  * @brief  Set the device and all the used Endpoints addresses.
  * @param  Val: device address.
  * @retval None.
  */
void SetDeviceAddress(uint8_t Val)
{
    uint32_t i;
    uint32_t nEP = Device_Table.Total_Endpoint;

    /* set address in every used endpoint */
    for (i = 0; i < nEP; i++)
    {
        _SetEPAddress((uint8_t)i, (uint8_t)i);
    } /* for */

    _SetDADDR(Val | DADDR_EF); /* set device address and enable function */
}

/**
  * @brief  No operation function.
  * @retval None.
  */
void NOP_Process(void)
{
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

/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
