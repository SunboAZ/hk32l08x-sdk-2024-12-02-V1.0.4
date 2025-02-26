/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2024-01-04
1.首次发布

******************************例程详细描述*****************************
功能描述:
	本例程演示了低功耗模式的进入和唤醒配置。
	在hk32l0xx_lp_modes.c中包括了Low-Power Run、Sleep、Low-Power Sleep、Stop、Low-Power Stop低功耗模式的配置，
	通过在hk32l0xx_lp_modes.h中打开和关闭对应的宏定义来选择相应的低功耗模式：
                LPRUN_MODE：Low-Power Run模式，按下按键KEY1进入 Low-Power Run，按下KEY2产生EXTI中断，在中断中退出Low-Power Run模式，
	退出后将系统时钟配置为HSE+PLL48M
             （对应L08X数据手册工作电流特性表中：低功耗运行模式（Low-Power Run））

	SLEEP_MODE：Sleep模式，按下按键KEY1进入Sleep，按下KEY2产生EXTI中断，在中断中退出Sleep模式，退出后将系统时钟配置为HSE+PLL48M，
	同时LED1循环亮灭
             （对应L08X数据手册工作电流特性表中：睡眠模式（Sleep））

	LPSLEEP_MODE：Low-Power Sleep模式，按下按键KEY1进入Low-Power Sleep，按下KEY2产生EXTI中断，在中断中退出Low-Power Sleep模式，
	退出后将系统时钟配置为HSE+PLL48M，同时LED1循环亮灭
             （对应L08X数据手册工作电流特性表中：低功耗睡眠模式（Low-Power Sleep））

	STOP_MODE：Stop模式，按下按键KEY1进入Stop，按下KEY2产生EXTI中断，在中断中退出Stop模式，退出后将系统时钟配置为HSE+PLL48M，
	同时LED1循环亮灭
             （对应L08X数据手册工作电流特性表中：停机模式（Stop））

	LPSTOP_MODE：Low-Power Stop模式，按下按键KEY1进入Low-Power Stop，按下KEY2产生EXTI中断，在中断中退出Low-Power Stop模式，
	退出后将系统时钟配置为HSE+PLL48M，同时LED1循环亮灭
             （对应L08X数据手册工作电流特性表中：低功耗停机模式(Low-Power Stop））          
                               
时钟配置:
	本例程采用HSE+PLL48MHz作为系统时钟，用户如果需要更改系统时钟配置，请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32L0xx全系列

涉及外设:
	PWR/EXTI/GPIO
	
涉及管脚:	
	KEY1 -----------> PB2
	KEY2 -----------> PC13(WKUP2)
	LED1 -----------> PF4
	LED2 -----------> PF5

注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。
	3. 使用HK32L08x-EVAL board测试功耗时，去掉JMP3，将万用表调整到电流档接到JMP3两端。
	若需要保证功耗测试尽可能的低，可以去掉HK32L08x-EVAL board JMP6和JMP4的跳帽
如何使用:
	1. 直接编译程序下载到评估版，重启评估版;
	2. 选择需要测试的低功耗模式，通过按键唤醒后，观察LED亮灭现象。
***********************************************************************