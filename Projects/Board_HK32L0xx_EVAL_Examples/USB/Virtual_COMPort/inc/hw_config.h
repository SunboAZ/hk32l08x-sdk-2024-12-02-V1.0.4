/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hw_config.h
* @brief:     Hardware Configuration & Setup.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
#include "usb_type.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Set_System(void);
void Set_USBClock(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void USB_Cable_Config (FunctionalState NewState);
bool USART_Config(void);
void USB_To_USART_Send_Data(uint8_t* data_buffer, uint8_t Nb_bytes);
void USART_To_USB_Send_Data(void);
void Handle_USBAsynchXfer (void);
void GPIO_Configuration(void);
void EXTI_Configuration(void);
void ADC_Configuration(void);
void ADC30x_Configuration(void);
void Get_SerialNum(void);
void VCP_SendRxBufPacketToUsb(void);
void VCP_Data_InISR(void);
void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nCount);

#ifdef __cplusplus
}
#endif

#endif  /*__HW_CONFIG_H */

/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/
