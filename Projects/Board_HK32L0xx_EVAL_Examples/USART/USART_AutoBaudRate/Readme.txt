/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2024-01-17
1.首次发布

******************************例程详细描述*****************************
功能描述:
	本示例为USART1使用自动适配波特率功能，上电等待数据。接收数据并自动适配波特率。
	匹配成功亮起LED1,失败亮起LED2。
	

时钟配置:
	本例程采用HSE+PLL48MHz作为系统时钟，用户如果需要更改系统时钟配置，请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32L0xx全系列

涉及外设:
	GPIO
	USART1
涉及管脚:	
	PA9--->TX
	PA10--->RX

注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
	1. 直接编译程序下载到评估版，重启评估版;
	2.上电后上位机发送一个数据，匹配成功LED1亮起，失败LED2亮起。
***********************************************************************