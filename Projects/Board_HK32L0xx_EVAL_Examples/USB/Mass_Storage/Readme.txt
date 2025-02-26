/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2024-1-12
1. 首次发布

****************************** 例程描述********************************
功能描述：
	1. 本例程提供了基于HK32芯片的USB全速设备说明;
	2. 本例程描述了USB - FS设备与PC主机通过bulk传输通讯;
	3. 本例程支持BOT(bulk only transfer)协议，并且使用SCSI(small computer system interface)指令;
	4. 本例程描述了USB设备被枚举为USB - FS大容量设备，它使用USB - FS设备的Mass Storage驱动程序.
	5. HK32存储空间使用SPI Flash

时钟配置：
	1. 本例程采用HSE8MHz倍频到48MHz作为系统时钟，用户如果需要更改系统时钟配置，请参考对应用户手册或者
	    RCC库函数及RCC相关例程.

适用芯片：
	HK32L0xx全系列

涉及外设：
	USB
	SPI1

涉及管脚:	
	PA11-->USB_DM
	PA12-->USB_DP

	PA4-->SPI_CS
	PA5-->SPI_SCK
	PA6-->SPI_MISO
	PA7-->SPI_MOSI

注意事项：
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	    或者IAR8.22及其以上版本编译本工程(EWARM)；
	2. 使用之前检测电源VCC、GND等是否正常。
如何使用：
	1. 直接编译程序下载到评估板，重启评估板;
	2. 通过设备管理器查看设备是否枚举成功；
***********************************************************************
