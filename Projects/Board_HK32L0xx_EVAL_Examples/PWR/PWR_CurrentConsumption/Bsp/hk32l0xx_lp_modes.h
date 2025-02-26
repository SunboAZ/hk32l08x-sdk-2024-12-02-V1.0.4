/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_lp_modes.h
* @brief:     Header for hk32l0xx_lp_modes.h file.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_LP_MODES_H
#define __HK32L0XX_LP_MODES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#if !defined (SLEEP_MODE) && !defined (STOP_MODE) && !defined (LPRUN_MODE) && !defined (LPSLEEP_MODE) && !defined (LPSTOP_MODE)
/* Uncomment the corresponding line to select the HK32L0xx Low Power mode */

//#define LPRUN_MODE
//#define SLEEP_MODE
//#define LPSLEEP_MODE
//#define STOP_MODE
#define LPSTOP_MODE
#endif

#if !defined (SLEEP_MODE) && !defined (STOP_MODE) && !defined (LPRUN_MODE) && !defined (LPSLEEP_MODE) && !defined (LPSTOP_MODE)
#error "Please select first the target HK32L0xx Low Power mode to be measured (in hk32l0xx_lp_modes.h file)"
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SleepMode_Measure(void);
void StopMode_Measure(void);
void LPRunMode_Measure(void);
void LPSleepMode_Measure(void);
void LPStopMode_Measure(void);

#ifdef __cplusplus
}
#endif

#endif /* __HK32L0XX_LP_MODES_H */
