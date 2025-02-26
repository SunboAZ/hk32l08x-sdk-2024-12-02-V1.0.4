;;******************** (C) COPYRIGHT 2020 HK ********************
;* file               : startup_hk32l0xx.s
;* author             : AE Team
;* Version            : V1.1.0
;* date               : 12.30.2021
;* Description        : hk32l08x devices vector table for EWARM toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == __iar_program_start,
;*                      - Set the vector table entries with the exceptions ISR 
;*                        address
;*                      - Configure the system clock
;*                      - Branches to main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the Cortex-M0 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;*******************************************************************************

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
                DCD     Reset_Handler                  ; Reset Handler
                DCD     NMI_Handler                    ; NMI Handler
                DCD     HardFault_Handler              ; Hard Fault Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     SVC_Handler                    ; SVCall Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     PendSV_Handler                 ; PendSV Handler
                DCD     SysTick_Handler                ; SysTick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler                ; Window Watchdog
                DCD     PVD_IRQHandler                 ; PVD and VDDIO2 supply comparator
                DCD     RTC_IRQHandler                 ; RTC
                DCD     FLASH_IRQHandler               ; FLASH
                DCD     RCC_IRQHandler                 ; RCC
                DCD     EXTI0_1_IRQHandler             ; EXTI Line 0 and Line 1
                DCD     EXTI2_3_IRQHandler             ; EXTI Line 2 and Line 3            
                DCD     EXTI4_15_IRQHandler            ; EXTI Line 4 to Line 15 
                DCD     LPUART_IRQHandler              ; UART3 
                DCD     DMA_CH1_IRQHandler             ; DMA1 Channel1
                DCD     DMA_CH2_3_IRQHandler           ; DMA1 Channel2 and Channel3
                DCD     DMA_CH4_7_IRQHandler           ; DMA1 Channel4 to Channel7
                DCD     ADC_COMP_IRQHandler            ; ADC and comparator 1 and 2
                DCD     TIM1_IRQHandler                ; LPTIMER1
                DCD     UART3_4_IRQHandler             ; UART4
                DCD     TIM2_IRQHandler                ; TIM2
                DCD     TIM3_IRQHandler                ; TIM3
                DCD     DAC_IRQHandler                 ; DAC
                DCD     LPTIM1_3_IRQHandler            ; LPTIMER2
                DCD     TIM14_IRQHandler               ; LPUART1
                DCD     TIM15_IRQHandler               ; LPTIMER3 
                DCD     TIM16_IRQHandler               ; DIVSQR 
                DCD     TIM17_IRQHandler               ; TIM1
                DCD     I2C1_IRQHandler                ; I2C1
                DCD     I2C2_IRQHandler                ; I2C2 
                DCD     SPI1_IRQHandler                ; SPI1
                DCD     SPI2_IRQHandler                ; SPI2 
                DCD     USART1_IRQHandler              ; USART1
                DCD     USART2_IRQHandler              ; USART2 
                DCD     AES_TRNG_EMACC_IRQHandler      ; AES and RNG 
                DCD     LCD_CAN_IRQHandler             ; LCD 
                DCD     USB_DVSQ_IRQHandler            ; USB event interrupt
     
        
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0
        
        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler
        
        
        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
        B HardFault_Handler
       
        
        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler
       
        
        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
        B PendSV_Handler
        
        
        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler
        
        
        PUBWEAK WWDG_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDG_IRQHandler
        B WWDG_IRQHandler

	
	PUBWEAK PVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PVD_IRQHandler
        B PVD_IRQHandler

                
        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler
        
                
        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FLASH_IRQHandler
        B FLASH_IRQHandler
        
                
        PUBWEAK RCC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCC_IRQHandler
        B RCC_IRQHandler
        
                
        PUBWEAK EXTI0_1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI0_1_IRQHandler
        B EXTI0_1_IRQHandler
        
                
        PUBWEAK EXTI2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_3_IRQHandler
        B EXTI2_3_IRQHandler
        
                
        PUBWEAK EXTI4_15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI4_15_IRQHandler
        B EXTI4_15_IRQHandler                      
        
                
        PUBWEAK LPUART_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPUART_IRQHandler
        B LPUART_IRQHandler
        
                
        PUBWEAK DMA_CH1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_CH1_IRQHandler
        B DMA_CH1_IRQHandler
        
                
        PUBWEAK DMA_CH2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_CH2_3_IRQHandler
        B DMA_CH2_3_IRQHandler
        
                 
        PUBWEAK DMA_CH4_7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_CH4_7_IRQHandler
        B DMA_CH4_7_IRQHandler
        
                
        PUBWEAK ADC_COMP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_COMP_IRQHandler
        B ADC_COMP_IRQHandler
        
                
        PUBWEAK TIM1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_IRQHandler
        B TIM1_IRQHandler                        
        
                
        PUBWEAK UART3_4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART3_4_IRQHandler
        B UART3_4_IRQHandler
        
                
        PUBWEAK TIM2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM2_IRQHandler
        B TIM2_IRQHandler
        

        PUBWEAK TIM3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM3_IRQHandler
        B TIM3_IRQHandler
        
                
        PUBWEAK DAC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DAC_IRQHandler
        B DAC_IRQHandler
        
                
        PUBWEAK LPTIM1_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPTIM1_3_IRQHandler
        B LPTIM1_3_IRQHandler
        
                
        PUBWEAK TIM14_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM14_IRQHandler
        B TIM14_IRQHandler


        PUBWEAK TIM15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM15_IRQHandler
        B TIM15_IRQHandler


	PUBWEAK TIM16_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM16_IRQHandler
        B TIM16_IRQHandler


	PUBWEAK TIM17_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM17_IRQHandler
        B TIM17_IRQHandler


	PUBWEAK I2C1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_IRQHandler
        B I2C1_IRQHandler


	PUBWEAK I2C2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_IRQHandler
        B I2C2_IRQHandler


	PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler


	PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_IRQHandler
        B SPI2_IRQHandler


	PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_IRQHandler
        B USART1_IRQHandler


	PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART2_IRQHandler
        B USART2_IRQHandler


	PUBWEAK AES_TRNG_EMACC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
AES_TRNG_EMACC_IRQHandler
        B AES_TRNG_EMACC_IRQHandler


	PUBWEAK LCD_CAN_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LCD_CAN_IRQHandler
        B LCD_CAN_IRQHandler


	PUBWEAK USB_DVSQ_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB_DVSQ_IRQHandler
        B USB_DVSQ_IRQHandler
       

        END
;******************** (C) COPYRIGHT 2021 HK ********************
