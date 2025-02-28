/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2024-01-14
1.首次发布

******************************例程详细描述*****************************
功能描述:
    本例演示RTC使用LSI时钟时，通过测量LSI时钟频率，来校准RTC分频系数。
    本例中，使用TIM14校准RTC分频。

    配置LSI为RTC时钟源，芯片复位后，使用LSI默认频率（32.768K）配置RTC分频。
    配置ALARM每1秒产生一次中断，其中断服务中翻转LED1。

    由于LSI的频率不准确，因此LED1的翻转周期也不准确。

    按下TAMPER键后，启动RTC时钟频率测试：
        1）配置TIM14 通道1输入捕获RTC时钟，测量LSI时钟周期。
        2）根据上述实测值，重新配置RTC预分频系数。配置完成后，亮LED2.

    校准后，可以观测LED1的翻转频率，准确度有大幅提升。

时钟配置:
	本例程采用HSE48MHz作为系统时钟，用户如果需要更改系统时钟配置，请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32L0xx全系列

涉及外设:
	UART / TIM / RTC
	
涉及管脚:	
	UART3 Pin：
        UART3_TX  ------------>  PA4
        UART3_RX  ------------>  PA5
	LED1 ------------>  PF4
    LED2 ------------>  PF5
    KEY1 ------------>  PB2
	
	
注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。
	
如何使用:
	1. 直接编译程序下载到评估版，重启评估版;
    2. 通过LED闪灯和串口打印，按键操作确认RTC是否正常工作;
***********************************************************************