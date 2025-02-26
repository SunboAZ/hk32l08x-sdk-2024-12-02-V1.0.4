/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32l0xx_eval_glass_lcd.h
* @brief:     hk32l0xx_eval_glass_lcd configuration file.
*             The file is the unique include file that the application programmer
*             is using in the C source code, it is a patch file.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32L0XX_EVAL_GLASS_LCD_H
#define __HK32L0XX_EVAL_GLASS_LCD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32l0xx_eval.h"

/** @addtogroup Boards
  * @{
  */

/** @addtogroup HK32_EVAL
  * @{
  */

/** @addtogroup HK32L0XX_EVAL_GLASS_LCD
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup HK32L0XX_EVAL_GLASS_LCD_Exported_Types
  * @{
  */

/**
  * @}
  */
/* Exported constants --------------------------------------------------------*/
/** @defgroup HK32L0XX_EVAL_GLASS_LCD_Exported_Constants
  * @{
  */

/**
  * @}
  */
/* Exported macro ------------------------------------------------------------*/
/** @defgroup HK32L0XX_EVAL_GLASS_LCD_Exported_Macros
  * @brief the macro that start with a '_'  is internal macro, propose be used in hk32l0xx_eval_glass_lcd.c.
  * @{
  */

/* Segment code serial number macro definition
   From top to bottom, from left to right
   index = (COMx-0) * 32 + SEGindex */
#define _LCD_HK_LOGO      31   /*corresponding to S11*/
#define _LCD_AC           125  /*corresponding to S10*/
#define _LCD_DC           63   /*corresponding to S12*/


#define _LCD_COLON0       123  /*corresponding to S9*/
#define _LCD_COLON1       116  /*corresponding to S26*/
#define _LCD_COLON2       115  /*corresponding to S30*/


#define _LCD_DOT0         121  /*corresponding to S7*/
#define _LCD_DOT1         119  /*corresponding to S8*/
#define _LCD_DOT2         6    /*corresponding to S1*/
#define _LCD_DOT3         8    /*corresponding to S2*/
#define _LCD_DOT4         10   /*corresponding to S3*/
#define _LCD_DOT5         12   /*corresponding to S4*/
#define _LCD_DOT6         14   /*corresponding to S5*/


#define _LCD_AM           118  /*corresponding to S18*/
#define _LCD_FM           86   /*corresponding to S17*/
#define _LCD_RX           54   /*corresponding to S16*/
#define _LCD_LOCK         22   /*corresponding to S15*/
#define _LCD_ALARM        20   /*corresponding to S23*/
#define _LCD_DEGREE       19   /*corresponding to S27*/


#define _LCD_PM           117  /*corresponding to S22*/
#define _LCD_CH           85   /*corresponding to S21*/
#define _LCD_TX           53   /*corresponding to S20*/
#define _LCD_BATTERY      21   /*corresponding to S19*/
#define _LCD_SIGNAL0      52   /*corresponding to S24*/
#define _LCD_SIGNAL1      84   /*corresponding to S25*/
#define _LCD_SIGNAL2      83   /*corresponding to S29*/
#define _LCD_DB           51   /*corresponding to S28*/


#define _LCD_MAX          95   /*corresponding to S13*/
#define _LCD_POS          127  /*corresponding to S14*/
#define _LCD_NEG          96   /*corresponding to S42*/
#define _LCD_MIN          64   /*corresponding to S41*/


#define _LCD_OHM_K        113  /*corresponding to S34*/
#define _LCD_OHM          114  /*corresponding to S38*/
#define _LCD_MA_M         81   /*corresponding to S33*/
#define _LCD_MA_A         82   /*corresponding to S37*/
#define _LCD_MV_M         49   /*corresponding to S32*/
#define _LCD_MV_V         50   /*corresponding to S36*/
#define _LCD_KW_K         17   /*corresponding to S31*/
#define _LCD_KW_W         18   /*corresponding to S35*/
#define _LCD_PERCENT      16   /*corresponding to S6*/


#define _LCD_BUSY         32   /*corresponding to S40*/
#define _LCD_ERROR        0    /*corresponding to S39*/
#define _LCD_AUTO         1    /*corresponding to S43*/
#define _LCD_RUN          33   /*corresponding to S44*/
#define _LCD_PAUSE        65   /*corresponding to S45*/
#define _LCD_STOP         97   /*corresponding to S46*/
#define _LCD_KPA          98   /*corresponding to S50*/
#define _LCD_K            66   /*corresponding to S49*/
#define _LCD_G            34   /*corresponding to S48*/
#define _LCD_CMS_C        2    /*corresponding to S47*/
#define _LCD_CMS_M        3    /*corresponding to S51*/
#define _LCD_CMS_S        35   /*corresponding to S52*/
#define _LCD_L            67   /*corresponding to S53*/
#define _LCD_M3           99   /*corresponding to S54*/
#define _LCD_MKHZ_M       68   /*corresponding to S57*/
#define _LCD_MKHZ_K       36   /*corresponding to S56*/
#define _LCD_MKHZ_HZ      4    /*corresponding to S55*/


#define _LCD_PRODUCT_LOG  100  /*corresponding to S58*/


/* Corresponding value of the seven-segment code at position 1 */
#define _LCD_1A           101
#define _LCD_1B           102
#define _LCD_1C           38
#define _LCD_1D           5
#define _LCD_1E           37
#define _LCD_1F           69
#define _LCD_1G           70

/* Corresponding value of the seven-segment code at position 2 */
#define _LCD_2A           103
#define _LCD_2B           104
#define _LCD_2C           40
#define _LCD_2D           7
#define _LCD_2E           39
#define _LCD_2F           71
#define _LCD_2G           72

/* Corresponding value of the seven-segment code at position 3 */
#define _LCD_3A           105
#define _LCD_3B           106
#define _LCD_3C           42
#define _LCD_3D           9
#define _LCD_3E           41
#define _LCD_3F           73
#define _LCD_3G           74

/* Corresponding value of the seven-segment code at position 4 */
#define _LCD_4A           107
#define _LCD_4B           108
#define _LCD_4C           44
#define _LCD_4D           11
#define _LCD_4E           43
#define _LCD_4F           75
#define _LCD_4G           76

/* Corresponding value of the seven-segment code at position 5 */
#define _LCD_5A           109
#define _LCD_5B           110
#define _LCD_5C           46
#define _LCD_5D           13
#define _LCD_5E           45
#define _LCD_5F           77
#define _LCD_5G           78

/* Corresponding value of the seven-segment code at position 6 */
#define _LCD_6A           111
#define _LCD_6B           112
#define _LCD_6C           48
#define _LCD_6D           15
#define _LCD_6E           47
#define _LCD_6F           79
#define _LCD_6G           80

/* Corresponding value of the seven-segment code at position 7 */
#define _LCD_7A           24
#define _LCD_7B           23
#define _LCD_7C           87
#define _LCD_7D           120
#define _LCD_7E           88
#define _LCD_7F           56
#define _LCD_7G           55

/* Corresponding value of the seven-segment code at position 8 */
#define _LCD_8A           26
#define _LCD_8B           25
#define _LCD_8C           89
#define _LCD_8D           122
#define _LCD_8E           90
#define _LCD_8F           58
#define _LCD_8G           57

/* Corresponding value of the seven-segment code at position 9 */
#define _LCD_9A           28
#define _LCD_9B           27
#define _LCD_9C           91
#define _LCD_9D           124
#define _LCD_9E           92
#define _LCD_9F           60
#define _LCD_9G           59

/* Corresponding value of the seven-segment code at position 10 */
#define _LCD_10A          30
#define _LCD_10B          29
#define _LCD_10C          93
#define _LCD_10D          126
#define _LCD_10E          94
#define _LCD_10F          62
#define _LCD_10G          61


/* Each number is represented in seven segments*/
#define DIGIT_NUMBER_SEG    7

/**
  * @}
  */
/* Exported functions ------------------------------------------------------- */
/** @defgroup HK32L0XX_EVAL_GLASS_LCD_Exported_Functions
  * @{
  */
void LCD_GlassInit(void);
void LCD_GlassClear(void);
void LCD_GlassDisplaySeg(uint8_t SegNum);
void LCD_GlassClearSeg(uint8_t SegNum);
void LCD_GlassUpdate(void);
void LCD_GlassDisplayDigit(unsigned char Value, unsigned char Position );
void LCD_GlassDisplayIntOnBigNumArea(int Value);
void LCD_GlassDisplayFloatOnBigNumArea(float Value, uint8_t NumOfDecimal);
void LCD_GlassDisplayUintOnSmallNumArea( uint16_t Value);
void LCD_GlassScrollNum(uint32_t Value, uint16_t nScroll, uint32_t ScrollSpeed);
void LCD_GlassDisplayHKLog(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__HK32L0XX_EVAL_GLASS_LCD_H */

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

/**
  * @}
  */


