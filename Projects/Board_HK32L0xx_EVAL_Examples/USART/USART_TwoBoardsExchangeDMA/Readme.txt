/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2024-01-17
1.首次发布

******************************例程详细描述*****************************
功能描述:
	本示例为USART1使用DMA发送数据和接收数据的功能。BPS为115200。
	1.上电后,先按下BOARD2按键1，BOARD2等待接收数据。
	2.再按下BOARD1的按键1会向BOARD2发送数据“USART DMA : USART1_BOARD1 -> USART1_BOARD2 using DMA Tx and Rx Flag”
	并等待接收数据。
	3.BOARD2收到后发送"USART DMA : USART1_BOARD2 -> USART1_BOARD1 using DMA Tx and Rx Flag"，并比较接收数据是否与
	约定的一致，一致则亮起LED1,LED2
	4.BOARD1收到数据后比较是否与约定的一致，一致则亮起LED1,LED2。

时钟配置:
	本例程采用HSE+PLL48MHz作为系统时钟，用户如果需要更改系统时钟配置，请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32L0xx全系列

涉及外设:
	GPIO
	USART1
	DMA
涉及管脚:	
	BOARD1_PA9<--->BOARD2_PA10
	BOARD1_PA10<--->BOARD2_PA9

注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
	1. 直接编译程序下载到评估版，重启评估版;
	2.先按下BOARD2的按键1，再按下BOARD1的按键1，随后LED1,LED2亮起。验证成功
***********************************************************************