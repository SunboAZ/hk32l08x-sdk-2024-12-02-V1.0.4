/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2024-01-14
1.首次发布

******************************例程详细描述*****************************
功能描述:
    本例演示如何使用RTC亚秒功能及侵入检查的特性。演示了一个
    高精度秒表，并可在备份寄存器其中记录2个时间节点（使用4个
    寄存器，2个记录时分秒，2个记录亚秒）。


    本例程通过按键进行控制，通过串口进行显示。

    本例首次启动后，从00:00:00:000开始计时，显示格式为 时：分：秒：亚秒。
    可通过下列按键控制秒表：
        1）KEY1按键长按超过2秒，启动秒表。
        2）KEY1按键按下， 在备份寄存器中记录按下时的精确时间（最多2次）；
        3）长按Tamp键 1S，秒表停止走时，并清空所有记录.

时钟配置:
	本例程采用HSE48MHz作为系统时钟，用户如果需要更改系统时钟配置，请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32L0xx全系列

涉及外设:
	UART / EXTI / RTC /GPIO
	
涉及管脚:	
	UART3 Pin：
        UART3_TX  ------------>  PA4
        UART3_RX  ------------>  PA5

    KEY1 --------------->  PB2
	KEY2（RTC_TAMPER）-->  PC13

	
注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。
	
如何使用:
    1. 直接编译程序下载到评估版，重启评估版;
    2. 通过串口打印，按键操作确认RTC是否正常工作;
***********************************************************************