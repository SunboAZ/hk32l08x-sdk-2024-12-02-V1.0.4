/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_divsqrt.h
* @brief:     API file of divsqrt module
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_DIVSQRT_H
#define __HK32L0XX_DIVSQRT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx.h"
/** @addtogroup DVSQ
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** @defgroup DIVSQRT_Private_Defines          DIVSQRT_Private_Defines
  * @{
  */

#define DVSQ_BUSY_WAIT_EN                           1     /* If it is 1, it will judge and wait for DVSQ to be free before reading the DVSQ operation result register */

/* DVSQ register access pointer */
#define  DIVSQRT                                    DVSQ

/* DVSQ working state definition */
#define DVSQ_IDLE_NO_OPERATION                      ((uint32_t)0x00000000)                /* The accelerator is idle and has not performed a square root or division operation */
#define DVSQ_IDLE_SQRT                              ((uint32_t)0x20000000)                /* The accelerator is idle and the last operation completed was the square root operation */
#define DVSQ_IDLE_DIV                               ((uint32_t)0x40000000)                /* The accelerator is idle and the last operation completed is division */
#define DVSQ_BUSY_SQRT                              ((uint32_t)0xA0000000)                /* The accelerator is busy and performing a square root operation */
#define DVSQ_BUSY_DIV                               ((uint32_t)0xC0000000)                /* The accelerator is busy and is doing division */

/* Configure the startup mode of the DVSQ division operation */
#define DVSQ_EnableDivFastStart()                   DIVSQRT->CSR &= ~DVSQ_CSR_DFS         /* Enable the quick division function */
#define DVSQ_DisableDivFastStart()                  DIVSQRT->CSR |= DVSQ_CSR_DFS          /* Disable the quick division function */

/* Configures whether the DVSQ division is signed */
#define DVSQ_ConfigDivUnsigned()                    DIVSQRT->CSR |= DVSQ_CSR_UNSIGN_DIV   /* Configure the DVSQ to perform unsigned division mode */
#define DVSQ_ConfigDivSigned()                      DIVSQRT->CSR &= ~DVSQ_CSR_UNSIGN_DIV  /* Configure the DVSQ to perform signed division mode */

/* Configure the accuracy of DVSQ square operation */
#define DVSQ_ConfigSqrtPresHigh()                   DIVSQRT->CSR |= DVSQ_CSR_HPRESQRT    /* Configure DVSQ as high precision square operation mode */
#define DVSQ_ConfigSqrtPresNormal()                 DIVSQRT->CSR &= ~DVSQ_CSR_HPRESQRT    /* Set DVSQ to the common precision square operation mode */

/* When DVSQ_CSR_DFS in THE CSR is 1, the software starts the division operation.
When the bit is 0, the hardware automatically starts the division operation after
the value is written into the divisor register */
#define DVSQ_StartDivCalc()                         DIVSQRT->CSR |= DVSQ_CSR_DIV_SRT      /* Let's do division */

/* DVSQ busy status query */
#define DVSQ_IsBusy()                               ((DIVSQRT->CSR & DVSQ_CSR_BUSY)? 1:0) /* Return '1' to indicate busy; Return '0' for idle */

/* DVSQ waits idle */
#if (DVSQ_BUSY_WAIT_EN == 1)
#define DVSQ_Wait()                                 while(DVSQ_IsBusy())
#else
#define DVSQ_Wait()
#endif
/**
  * @}
  */
/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */
void DVSQ_Init(void);
void DVSQ_DeInit(void);
uint32_t DVSQ_Sqrt(uint32_t u32Radicand);
uint16_t DVSQ_SqrtH(uint32_t u32Radicand, uint16_t *fraction);
int32_t DVSQ_Divsion(int32_t i32Dividend, int32_t i32Divisor, int32_t *i32pRemainder);
uint32_t DVSQ_UDivsion(uint32_t u32Dividend, uint32_t u32Divisor, uint32_t *u32pRemainder);

#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_DIVSQRT_H */
