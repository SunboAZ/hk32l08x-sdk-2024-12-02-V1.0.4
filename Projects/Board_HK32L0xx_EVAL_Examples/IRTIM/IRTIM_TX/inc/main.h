/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.h
* @brief:     Main program header.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "hk32l0xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/*RX-------------*/
#define IRDA_ID 0

#define IRDA_GPIO_PORT                          GPIOA
#define IRDA_GPIO_CLK                           RCC_AHBPeriph_GPIOA
#define IRDA_GPIO_PIN                                   GPIO_Pin_3
#define IRDA_GPIO_PORT_SOURCE                 EXTI_PortSourceGPIOA
#define IRDA_GPIO_PIN_SOURCE                    EXTI_PinSource3

#define IRDA_EXTI_LINE                              EXTI_Line3
#define IRDA_EXTI_IRQN                              EXTI2_3_IRQn
#define IRDA_EXTI_IRQHANDLER_FUN            EXTI2_3_IRQHandler

#define  IrDa_DATA_IN()    GPIO_ReadInputDataBit(IRDA_GPIO_PORT,IRDA_GPIO_PIN)

/* Exported functions ------------------------------------------------------- */
/*RX-------------*/
uint8_t Get_Pulse_Time(void);

#ifdef __cplusplus
}
#endif  /* End of __cplusplus */

#endif /*__MAIN_H */

