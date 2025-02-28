/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2024-1-20
1.首次发布

****************************** 例程描述********************************
功能描述：
本例程描述了如何使用AES 硬件加速器去加密数据然后解密数据的配置流程和功能使用。
时钟配置：
本例程采用HSE8M + PLL = 48MHz作为系统时钟，用户如果需要更改系统时钟配置，需要在
                        USART_Config函数之前完成，关于系统时钟如何配置，请参考对应用户手册或者RCC库函数及RCC相关例程。

适用芯片：
HK32L0xx全系列

涉及外设：
UART3 / GPIO / AES

涉及管脚：
UART3_TX-------------- > PA4
UART3_RX-------------- > PA5
KEY1-------------- > PB2
LED1-------------- > PF4
LED2-------------- > PF5

注意事项：
1. 推荐使用MDK5.00及其以上版本编译本工程（MDK - ARM）
或者IAR8.22及其以上版本编译本工程(EWARM)；
2. 使用之前检测电源VCC、GND等是否正常。

如何使用：
1. 直接编译程序下载到评估版，重启评估版；
2. LED2会一直闪烁，直到按下按键KEY；
3. 通过串口打印和LED1 / LED2表征 AES 的执行结果。
4. LED1常亮，表示加密正确；LED2常亮，表示解密正确。
5. 还可以通过与Expected_Results.txt中的值比对，判断结果是否正确。
***********************************************************************

****************************** 版权申明********************************
本例程所有版权归深圳市航顺芯片技术研发有限公司2015 - 2024
***********************************************************************