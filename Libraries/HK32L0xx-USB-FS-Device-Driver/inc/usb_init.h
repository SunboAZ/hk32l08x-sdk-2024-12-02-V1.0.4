/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd 
* @filename:  usb_init.h
* @brief:     Initialization routines & global variables.
* @author:    AE Team 
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_INIT_H
#define __USB_INIT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @addtogroup usb_init
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @defgroup usb_init_Exported_Functions usb_init_Exported_Functions
  * @{
  */
  
void USB_Init(void);

/**
  * @}
  */

/* External variables --------------------------------------------------------*/

/** @defgroup usb_init_External_Variables usb_init_External_Variables
  * @{
  */

/*  The number of current endpoint, it will be used to specify an endpoint */
extern uint8_t	EPindex;
/*  The number of current device, it is an index to the Device_Table */
/*extern uint8_t	Device_no; */
/*  Points to the DEVICE_INFO structure of current device */
/*  The purpose of this register is to speed up the execution */
extern DEVICE_INFO*	pInformation;
/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */
extern DEVICE_PROP*	pProperty;
/*  Temporary save the state of Rx & Tx status. */
/*  Whenever the Rx or Tx state is changed, its value is saved */
/*  in this variable first and will be set to the EPRB or EPRA */
/*  at the end of interrupt process */
extern USER_STANDARD_REQUESTS *pUser_Standard_Requests;

extern uint16_t	SaveState ;
extern uint16_t wInterrupt_Mask;

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __USB_INIT_H */

/******************* (C) COPYRIGHT   HKMicroChip *****END OF FILE****/
