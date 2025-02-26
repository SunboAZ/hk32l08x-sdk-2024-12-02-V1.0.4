/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2024-01-23
1.首次发布

******************************例程详细描述*****************************
功能描述:
	此示例提供了如何使用I2C与STLM75（或兼容设备）
	I2C温度传感器进行通信，用于获取瞬时外部温度
	（-55°C至+125°C）。
	
	得益于HK32 I2C SMBus功能，我们可以轻松监控温度
	变化。这是由SMBus Alert管理的，它将生成一个
	中断，当系统温度超出所选范围时进行通知直至下降到下边界以下
	用户可以通过代码中的专用定义值来配置TOS和THYS寄存器值。
	
	默认情况下，示例将它们设置为（请参见main.c文件）：
	#define TEMPERATURE_THYS 31
	#define TEMPERATURE_TOS  32
	这两个参数定义了SMBA报警中断产生的位置：
	当温度超过上边界的时刻产生一次SMBA中断，
	再当温度降至下边界以下的时刻产生一次SMBA中断，
	报警产生时LED1与LED2会点亮直至下降到下边界以下。
	
	运行流程中的调试信息将通过串口1打印，可在PC端串口助手查看，
	包括温度值以及温度报警中断的产生等。
	
时钟配置:
	本例程采用HSE48MHz作为系统时钟，用户如果需要更改系统时钟配置，
	需要配置修改SYSCLK_SOURCE宏定义的。
	关于系统时钟如何配置，请参考对应用户手册或者RCC库函数及RCC相关例程。

适用芯片:
	HK32L0XX全系列

涉及外设:
	I2C
	
	USART1:
  - BaudRate = 115200
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  
  
涉及管脚:
	UART3 TX - PA4
	UART3 RX - PA5
	
	I2C SMBA - PB5
	I2C SCL - PB6
	I2C SDA - PB7
	
	LED1 - PF4
	LED2 - PF5
	
注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	   或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。
如何使用:
	1. 直接编译程序下载到评估板，重启评估板;
	2. 串口会打印功能描述中的信息。
***********************************************************************