/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2024-01-04
1.首次发布

******************************例程详细描述*****************************
功能描述:
					1. 本示例介绍如何开启和关闭FLASH的写保护。
						 - 启用写保护:
							 要启用写保护，在main.c文件中注释"#define WRITE_PROTECTION_DISABLE"
							 取消注释"#define WRITE_PROTECTION_ENABLE"（默认）。		
							 为了使能某几页写保护，用户必须调用FLASH_EnableWriteProtection函数。
							 该函数的参数将定义要保护的页数量。然后使用FLASH_OB_Launch()函数进
							 行系统重置，加载新的选项字节值。
					   - 取消写保护:
               要禁用写保护，在main.c文件中注释"#define WRITE_PROTECTION_ENABLE"
							 取消注释"#define WRITE_PROTECTION_DISABLE"。	
               要禁用Flash的写保护，需要擦除选项字节。该操作由FLASH_OptionByteErase函数完成。
               然后使用FLASH_OB_Launch()函数进行系统重置，加载新的选项字节值。
					2.  如果启用写保护，程序将FLASH_PAGES_TO_BE_PROTECTED选择的flash页使能写保护（其他
							页的读保护状态保持原样）
              如果取消写保护，程序将FLASH_PAGES_TO_BE_PROTECTED选择的flash页取消写保护（其他
							页的读保护状态保持原样）				
							程序判断如果FLASH_PAGES_TO_BE_PROTECTED选择的flash页没有写保护，则执行擦除和写
							操作。通过MemoryProgramStatus变量确认程序执行情况。
时钟配置:
	本例程采用HSE+PLL48MHz作为系统时钟，用户如果需要更改系统时钟配置，请参考对应用户手册或者
	RCC库函数及RCC相关例程。

适用芯片:
	HK32L0xx全系列

涉及外设:
	Flash
	
涉及管脚:	
	无

注意事项:
	1. 推荐使用MDK5.00及其以上版本编译本工程（MDK-ARM）
	          或者IAR8.22及其以上版本编译本工程(EWARM);
	2. 使用之前检测电源VCC、GND等是否正常。
如何使用:
	1. 直接编译程序下载到评估版，重启评估版;
	2. 确认变量MemoryProgramStatus是否为FAILED表示写保护使能生效，flash擦写失败；
		 在main.c文件中注释"#define WRITE_PROTECTION_ENABLE"，取消注释"#define WRITE_PROTECTION_DISABLE"
		 再编译下载到评估版，重启评估版。	确认变量MemoryProgramStatus是否为PASSED表示写保护取消成功，
		 flash擦写成功。
***********************************************************************