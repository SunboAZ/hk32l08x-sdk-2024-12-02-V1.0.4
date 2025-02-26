/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2024-01-18
1.首次发布

******************************例程详细描述*****************************
功能描述:
 	本例程描述了IRTIM配置和红外NEC协议
	1. IRTIM_TX程序：TIM3为载波，TIM2编码为要发送的数据，PB9为数据输出端口（此功能为芯片的主要功能）。
	2. IRTIM_RX程序：PA3为数据接收端口，会用SYSTICK对接收的数据进行解码
	

时钟配置:
	本例程采用HSE48MHz作为系统时钟，用户如果需要更改系统时钟配置, 请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32L0XX全系列

涉及外设:
	IRTIM/ TIM2/ TIM3 /GPIO /RCC/ UART/SYSTICK
	
涉及管脚:	
	IRTIM_TX---PB9，IRTIM_RX---PA3

注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	    或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
	1. 下载IRTIM_TX程序到评估板1，
	2. 下载IRTIM_TX程序到评估板2，
	3. 板1的PB9连接IRTIM模块的IR_TX引脚，PA3连接IRTIM模块的Trigger引脚。
	4. 板2的PA3连接IRTIM模块的IR_RX引脚
	5. 复位板1和板2，然后按下IRTIM模块的KEY1按键，板1串口打印“KEY interrupt”，板2串口打印“Receive success”
***********************************************************************