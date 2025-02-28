/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd 
* @filename:  usb_def.h
* @brief:     Definitions related to USB Core.
* @author:    AE Team 
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DEF_H
#define __USB_DEF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @addtogroup USB
  * @brief  USB driver modules
  * @{
  */
  
/** @defgroup usb_def usb_def
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup usb_def_Exported_Types usb_def_Exported_Types
  * @{
  */
  
typedef enum _RECIPIENT_TYPE
{
	DEVICE_RECIPIENT,     /* Recipient device */
	INTERFACE_RECIPIENT,  /* Recipient interface */
	ENDPOINT_RECIPIENT,   /* Recipient endpoint */
	OTHER_RECIPIENT
} RECIPIENT_TYPE;


typedef enum _STANDARD_REQUESTS
{
	GET_STATUS = 0,
	CLEAR_FEATURE,
	RESERVED1,
	SET_FEATURE,
	RESERVED2,
	SET_ADDRESS,
	GET_DESCRIPTOR,
	SET_DESCRIPTOR,
	GET_CONFIGURATION,
	SET_CONFIGURATION,
	GET_INTERFACE,
	SET_INTERFACE,
	TOTAL_sREQUEST,  /* Total number of Standard request */
	SYNCH_FRAME = 12
} STANDARD_REQUESTS;

/* Definition of "USBwValue" */
typedef enum _DESCRIPTOR_TYPE
{
	DEVICE_DESCRIPTOR = 1,
	CONFIG_DESCRIPTOR,
	STRING_DESCRIPTOR,
	INTERFACE_DESCRIPTOR,
	ENDPOINT_DESCRIPTOR,
	DEVICE_BOS_DESCRIPTOR = 0xF
} DESCRIPTOR_TYPE;

/* Feature selector of a SET_FEATURE or CLEAR_FEATURE */
typedef enum _FEATURE_SELECTOR
{
	ENDPOINT_STALL,
	DEVICE_REMOTE_WAKEUP
} FEATURE_SELECTOR;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup usb_def_Exported_Constants usb_def_Exported_Constants
  * @{
  */

/* Definition of "USBbmRequestType" */
#define REQUEST_TYPE      0x60  /* Mask to get request type */
#define STANDARD_REQUEST  0x00  /* Standard request */
#define CLASS_REQUEST     0x20  /* Class request */
#define VENDOR_REQUEST    0x40  /* Vendor request */

#define RECIPIENT         0x1F  /* Mask to get recipient */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __USB_DEF_H */

/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
