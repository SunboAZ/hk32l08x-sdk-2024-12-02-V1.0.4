/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2024-01-15
1.首次发布

******************************例程详细描述*****************************
功能描述:
	本例程描述了LCD的初始配置流程，以及如何配置LCD的blink频率。
    LCD的时钟配置的LSI，上电以后，LCD闪烁模式配置为"LCD_BLINKMODE_ALLSEG_ALLCOM"，屏幕会显示16，此时频闪较快。
    按下开发板上的KEY1键，会更改LCD的blink频率，此时LCD也会显示对应的blink分频系数，每按一次，blink频率会更改一次。
    
    案件次数、LCD blink频率、LCD显示之间的对应关系如下：
    按第1次KEY1键 -->blink 32分频   --> LCD显示32
    按第2次KEY1键 -->blink 64分频   --> LCD显示64
    按第3次KEY1键 -->blink 128分频  --> LCD显示128
    按第4次KEY1键 -->blink 256分频  --> LCD显示256
    按第5次KEY1键 -->blink 512分频  --> LCD显示512
    按第6次KEY1键 -->blink 1024分频 --> LCD显示1024
    按第7次KEY1键 -->blink 1024分频 --> LCD显示1024
    ...                                 
    按第n次KEY1键 -->blink 1024分频 --> LCD显示1024

时钟配置:
	本例程采用HSE+PLL48MHz作为系统时钟，用户如果需要更改系统时钟配置，请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32L0xx全系列

涉及外设:
	LCD/RCC/EXTI
	
涉及管脚:	

EXTI pin:
	KEY1  --> PB2

LCD pin:
    COM0  --> PA8
    COM1  --> PA9
    COM2  --> PA10
    COM3  --> PB9
    SEG0  --> PA1
    SEG1  --> PA2
    SEG2  --> PA3
    SEG3  --> PA6
    SEG4  --> PA7
    SEG5  --> PB0
    SEG6  --> PB1
    SEG7  --> PB3
    SEG8  --> PB4
    SEG9  --> PB5
    SEG10 --> PB10
    SEG11 --> PB11
    SEG12 --> PB12
    SEG13 --> PB13
    SEG14 --> PB14
    SEG15 --> PB15
    SEG16 --> PB8
    SEG17 --> PA15
    SEG18 --> PC0
    SEG19 --> PC1
    SEG20 --> PC2
    SEG21 --> PC3
    SEG22 --> PC4
    SEG23 --> PC5
    SEG24 --> PC6
    SEG25 --> PC7
    SEG26 --> PC8
    SEG27 --> PC9
    SEG28 --> PC10
    SEG29 --> PC11
    SEG30 --> PC12
    SEG31 --> PD2

注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。
如何使用:
	1. 直接编译程序下载到评估版，重启评估版;
***********************************************************************