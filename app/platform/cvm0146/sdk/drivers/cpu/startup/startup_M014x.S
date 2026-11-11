; 
;  Copyright (c) 2022, Shenzhen CVA Innovation CO.,LTD
;  All rights reserved.
; 
;  Shenzhen CVA Innovation CO.,LTD (CVA chip) is supplying this file for use
;  exclusively with CVA's microcontroller products. This file can be freely
;  distributed within development tools that are supporting such microcontroller
;  products.
;  
;  THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
;  OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
;  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
;  CVA SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
;  OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.


;***************************************************************************
; Version: ICCARM Compiler Collection
;***************************************************************************

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:ROOT(2)

        EXTERN  main
        EXTERN  SystemInit
        EXTERN  init_data_bss
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA
        
__vector_table
        DCD   sfe(CSTACK)

        DCD   Reset_Handler                         ; -15, offset : 004H, Reset Handler
        DCD   NMI_Handler                           ; -14, offset : 008H, NMI Handler
        DCD   HardFault_Handler                     ; -13, offset : 00CH, Hard Fault Handler
        DCD   MemManage_Handler                     ; -12, offset : 010H, MPU Fault Handler
        DCD   BusFault_Handler                      ; -11, offset : 014H, Bus Fault Handler
        DCD   UsageFault_Handler                    ; -10, offset : 018H, Usage Fault Handler
__vector_table_0x1c
        DCD   Default_Handler                       ; -9, offset : 01CH, Reserved
        DCD   Default_Handler                       ; -8, offset : 020H, Reserved
        DCD   Default_Handler                       ; -7, offset : 024H, Reserved
        DCD   Default_Handler                       ; -6, offset : 028H, Reserved
        DCD   SVC_Handler                           ; -5, offset : 02CH, SVCall Handler
        DCD   DebugMon_Handler                      ; -4, offset : 030H, Debug Monitor Handler
        DCD   Default_Handler                       ; -3, offset : 034H, Reserved
        DCD   PendSV_Handler                        ; -2, offset : 038H, PendSV Handler
        DCD   SysTick_Handler                       ; -1, offset : 03CH, SysTick Handler
        
                                                    ; External Interrupts
        DCD   DMA0_Handler                          ; 0, offset : 040H, DMA channel 0 transfer complete
        DCD   DMA1_Handler                          ; 1, offset : 044H, DMA channel 1 transfer complete
        DCD   DMA2_Handler                          ; 2, offset : 048H, DMA channel 2 transfer complete
        DCD   DMA3_Handler                          ; 3, offset : 04CH, DMA channel 3 transfer complete
        DCD   DMA4_Handler                          ; 4, offset : 050H, DMA channel 4 transfer complete
        DCD   DMA5_Handler                          ; 5, offset : 054H, DMA channel 5 transfer complete
        DCD   DMA6_Handler                          ; 6, offset : 058H, DMA channel 6 transfer complete
        DCD   DMA7_Handler                          ; 7, offset : 05CH, DMA channel 7 transfer complete
        DCD   DMA8_Handler                          ; 8, offset : 060H, DMA channel 8 transfer complete
        DCD   DMA9_Handler                          ; 9, offset : 064H, DMA channel 9 transfer complete
        DCD   DMA10_Handler                         ; 10, offset : 068H, DMA channel 10 transfer complete
        DCD   DMA11_Handler                         ; 11, offset : 06CH, DMA channel 11 transfer complete
        DCD   DMA12_Handler                         ; 12, offset : 070H, DMA channel 12 transfer complete
        DCD   DMA13_Handler                         ; 13, offset : 074H, DMA channel 13 transfer complete
        DCD   DMA14_Handler                         ; 14, offset : 078H, DMA channel 14 transfer complete
        DCD   DMA15_Handler                         ; 15, offset : 07CH, DMA channel 15 transfer complete
        DCD   DMA_Error_Handler                     ; 16, offset : 080H, DMA error interrupt channels 0-15
        DCD   MCM_Handler                           ; 17, offset : 084H, FPU sources
        DCD   FTFC_Handler                          ; 18, offset : 088H, FTFC Command complete
        DCD   FTFC_ReadCollision_Handler            ; 19, offset : 08CH, FTFC Read collision
        DCD   Default_Handler                       ; 20, offset : 090H, Reserved
        DCD   FTFC_Fault_Handler                    ; 21, offset : 094H, FTFC Double bit fault detect
        DCD   WDOG_Handler                          ; 22, offset : 098H, Single interrupt vector for WDOG
        DCD   EWM_Handler                           ; 23, offset : 09CH, Single interrupt vector for EWM
        DCD   RCM_Handler                           ; 24, offset : 0A0H, RCM Asynchronous Interrupt
        DCD   I2C0_Handler                          ; 25, offset : 0A4H, I2C0 Master Interrupt
        DCD   SPI0_Handler                          ; 26, offset : 0A8H, SPI0 Interrupt
        DCD   SPI1_Handler                          ; 27, offset : 0ACH, SPI1 Interrupt
        DCD   SPI2_Handler                          ; 28, offset : 0B0H, SPI2 Interrupt
        DCD   SPI3_Handler                          ; 29, offset : 0B4H, SPI2 Interrupt
        DCD   Default_Handler                       ; 30, offset : 0B8H, Reserved
        DCD   UART0_RxTx_Handler                    ; 31, offset : 0BCH, UART0 Transmit / Receive Interrupt
        DCD   UART1_RxTx_Handler                    ; 32, offset : 0C0H, UART1 Transmit / Receive Interrupt
        DCD   UART2_RxTx_Handler                    ; 33, offset : 0C4H, UART2 Transmit / Receive Interrupt      
        DCD   UART3_RxTx_Handler                    ; 34, offset : 0C8H, UART3 Transmit / Receive Interrupt
        DCD   FCCU_Handler                          ; 35, offset : 0CCH, FCCU Interrupt
        DCD   FCCU_CfgTO_Handler                    ; 36, offset : 0D0H, FCCU Configuration Timeout Interrupt
        DCD   PRNG_Handler                          ; 37, offset : 0D4H, PRNG Interrupt
        DCD   CSE_Handler                           ; 38, offset : 0D8H, CSE Interrupt
        DCD   ADC0_Handler                          ; 39, offset : 0DCH, ADC0 interrupt request
        DCD   ADC1_Handler                          ; 40, offset : 0E0H, ADC1 interrupt request
        DCD   PDB0_Handler                          ; 41, offset : 0E4H, PDB0 interrupt
        DCD   PDB1_Handler                          ; 42, offset : 0E8H, PDB1 interrupt
        DCD   CMP0_Handler                          ; 43, offset : 0ECH, CMP0 interrupt request
        DCD   Default_Handler                       ; 44, offset : 0F0H, Reserved
        DCD   LPTMR0_Handler                        ; 45, offset : 0F4H, LPTIMER interrupt request
        DCD   RTC_Handler                           ; 46, offset : 0F8H, RTC alarm interrupt
        DCD   RTC_Seconds_Handler                   ; 47, offset : 0FCH, RTC seconds interrupt
        DCD   LPIT0_Ch0_Handler                     ; 48, offset : 100H, LPIT0 channel 0 overflow interrupt
        DCD   LPIT0_Ch1_Handler                     ; 49, offset : 104H, LPIT0 channel 1 overflow interrupt
        DCD   LPIT0_Ch2_Handler                     ; 50, offset : 108H, LPIT0 channel 2 overflow interrupt
        DCD   LPIT0_Ch3_Handler                     ; 51, offset : 10CH, LPIT0 channel 3 overflow interrupt
        DCD   Default_Handler                       ; 52, offset : 110H, Reserved
        DCD   PORTA_Handler                         ; 53, offset : 114H, Port A pin detect interrupt
        DCD   PORTB_Handler                         ; 54, offset : 118H, Port B pin detect interrupt
        DCD   PORTC_Handler                         ; 55, offset : 11CH, Port C pin detect interrupt
        DCD   PORTD_Handler                         ; 56, offset : 120H, Port D pin detect interrupt
        DCD   PORTE_Handler                         ; 57, offset : 124H, Port E pin detect interrupt
        DCD   I2S_Slave_Handler					    ; 58, offset : 128H, I2S Slave interrupt
		DCD   I2S_Master_Handler                    ; 59, offset : 12CH, I2S Master interrupt
		DCD   MFT0_Ch0_Ch1_Handler                  ; 60, offset : 130H, MFT0 Channel 0 and 1 interrupt
        DCD   MFT0_Ch2_Ch3_Handler                  ; 61, offset : 134H, MFT0 Channel 2 and 3 interrupt
        DCD   MFT0_Ch4_Ch5_Handler                  ; 62, offset : 138H, MFT0 Channel 4 and 5 interrupt
        DCD   MFT0_Ch6_Ch7_Handler                  ; 63, offset : 13CH, MFT0 Channel 6 and 7 interrupt
        DCD   MFT0_Fault_Handler                    ; 64, offset : 140H, MFT0 Fault interrupt
        DCD   MFT0_Ovf_Reload_Handler               ; 65, offset : 144H, MFT0 Counter overflow and Reload interrupt
        DCD   MFT1_Ch0_Ch1_Handler                  ; 66, offset : 148H, MFT1 Channel 0 and 1 interrupt
        DCD   MFT1_Ch2_Ch3_Handler                  ; 67, offset : 14CH, MFT1 Channel 2 and 3 interrupt
        DCD   MFT1_Ch4_Ch5_Handler                  ; 68, offset : 150H, MFT1 Channel 4 and 5 interrupt
        DCD   MFT1_Ch6_Ch7_Handler                  ; 69, offset : 154H, MFT1 Channel 6 and 7 interrupt
        DCD   MFT1_Fault_Handler                    ; 70, offset : 158H, MFT1 Fault interrupt
        DCD   MFT1_Ovf_Reload_Handler               ; 71, offset : 15CH, MFT1 Counter overflow and Reload interrupt
        DCD   MFT2_Ch0_Ch1_Handler                  ; 72, offset : 160H, MFT2 Channel 0 and 1 interrupt
        DCD   MFT2_Ch2_Ch3_Handler                  ; 73, offset : 164H, MFT2 Channel 2 and 3 interrupt
        DCD   MFT2_Ch4_Ch5_Handler                  ; 74, offset : 168H, MFT2 Channel 4 and 5 interrupt
        DCD   MFT2_Ch6_Ch7_Handler                  ; 75, offset : 16CH, MFT2 Channel 6 and 7 interrupt
        DCD   MFT2_Fault_Handler                    ; 76, offset : 170H, MFT2 Fault interrupt
        DCD   MFT2_Ovf_Reload_Handler               ; 77, offset : 174H, MFT2 Counter overflow and Reload interrupt
        DCD   MFT3_Ch0_Ch1_Handler                  ; 78, offset : 178H, MFT3 Channel 0 and 1 interrupt
        DCD   MFT3_Ch2_Ch3_Handler                  ; 79, offset : 17CH, MFT3 Channel 2 and 3 interrupt
        DCD   MFT3_Ch4_Ch5_Handler                  ; 80, offset : 180H, MFT3 Channel 4 and 5 interrupt
        DCD   MFT3_Ch6_Ch7_Handler                  ; 81, offset : 184H, MFT3 Channel 6 and 7 interrupt
        DCD   MFT3_Fault_Handler                    ; 82, offset : 188H, MFT3 Fault interrupt
        DCD   MFT3_Ovf_Reload_Handler               ; 83, offset : 18CH, MFT3 Counter overflow and Reload interrupt
        DCD   MFT4_Ch0_Ch1_Handler                  ; 84, offset : 190H, MFT4 Channel 0 and 1 interrupt
        DCD   MFT4_Ch2_Ch3_Handler                  ; 85, offset : 194H, MFT4 Channel 2 and 3 interrupt
        DCD   MFT4_Ch4_Ch5_Handler                  ; 86, offset : 198H, MFT4 Channel 4 and 5 interrupt
        DCD   MFT4_Ch6_Ch7_Handler                  ; 87, offset : 19CH, MFT4 Channel 6 and 7 interrupt
        DCD   MFT4_Fault_Handler                    ; 88, offset : 1A0H, MFT4 Fault interrupt
        DCD   MFT4_Ovf_Reload_Handler               ; 89, offset : 1A4H, MFT4 Counter overflow and Reload interrupt 
        DCD   MFT5_Ch0_Ch1_Handler                  ; 90, offset : 1A8H, MFT5 Channel 0 and 1 interrupt
        DCD   MFT5_Ch2_Ch3_Handler                  ; 91, offset : 1ACH, MFT5 Channel 2 and 3 interrupt
        DCD   MFT5_Ch4_Ch5_Handler                  ; 92, offset : 1B0H, MFT5 Channel 4 and 5 interrupt
        DCD   MFT5_Ch6_Ch7_Handler                  ; 93, offset : 1B4H, MFT5 Channel 6 and 7 interrupt
        DCD   MFT5_Fault_Handler                    ; 94, offset : 1B8H, MFT5 Fault interrupt
        DCD   MFT5_Ovf_Reload_Handler               ; 95, offset : 1BCH, MFT5 Counter overflow and Reload interrupt 
        DCD   CMU_Firc_Handler                      ; 96, offset : 1C0H, CMU FIRC interrupt
        DCD   CMU_Pll_Handler                       ; 97, offset : 1C4H, CMU PLL interrupt
        DCD   CMU_Sosc_Handler                      ; 98, offset : 1C8H, CMU SOSC interrupt
        DCD   Default_Handler                       ; 99, offset : 1CCH, Reserved
        DCD   CAN0_ORed_Handler                     ; 100, offset : 1D0H, CAN0 OR'ed [Bus Off OR Transmit Warning OR Receive Warning]
        DCD   CAN0_Error_Handler                    ; 101, offset : 1D4H, CAN0 Interrupt indicating that errors were detected on the CAN bus
        DCD   CAN0_FrameWakeup_Handler              ; 102, offset : 1D8H, CAN0 Pretended Networking operation is enabled, and a valid message match or timeout during Low Power mode
        DCD   CAN0_ORed_0_15_MB_Handler             ; 103, offset : 1DCH, CAN0 OR'ed Message buffer (0-15)
        DCD   CAN0_ORed_16_31_MB_Handler            ; 104, offset : 1E0H, CAN0 OR'ed Message buffer (16-31)
        DCD   CAN0_ORed_32_47_MB_Handler            ; 105, offset : 1E4H, CAN0 OR'ed Message buffer (32-47)
        DCD   CAN0_ORed_48_63_MB_Handler            ; 106, offset : 1E8H, CAN0 OR'ed Message buffer (48-63)
        DCD   CAN0_ORed_64_79_MB_Handler            ; 107, offset : 1ECH, CAN0 OR'ed Message buffer (64-79)
        DCD   CAN0_ORed_80_95_MB_Handler            ; 108, offset : 1F0H, CAN0 OR'ed Message buffer (80-95)    
        DCD   CAN0_EdgeWakeup_Handler               ; 109, offset : 1F4H, CAN0 self wakeup by edge
        DCD   CAN0_EccErr_Handler                   ; 110, offset : 1F8H, CAN0 ECC error
        DCD   CAN0_ERxFIFO_Handler                  ; 111, offset : 1FCH, CAN0 ERx FIFO error
        DCD   CAN1_ORed_Handler                     ; 112, offset : 200H, CAN1 OR'ed [Bus Off OR Transmit Warning OR Receive Warning]
        DCD   CAN1_Error_Handler                    ; 113, offset : 204H, CAN1 Interrupt indicating that errors were detected on the CAN bus
        DCD   CAN1_EccErr_Handler                   ; 114, offset : 208H, CAN1 ECC error
        DCD   CAN1_ORed_0_15_MB_Handler             ; 115, offset : 20CH, CAN1 OR'ed Message buffer (0-15)
        DCD   CAN1_ORed_16_31_MB_Handler            ; 116, offset : 210H, CAN1 OR'ed Message buffer (16-31)
        DCD   CAN1_ORed_32_47_MB_Handler            ; 117, offset : 214H, CAN1 OR'ed Message buffer (32-47)
        DCD   CAN1_ORed_48_63_MB_Handler            ; 118, offset : 218H, CAN1 OR'ed Message buffer (48-63)
        DCD   CAN1_EdgeWakeup_Handler               ; 119, offset : 21CH, CAN1 self wakeup by edge
        DCD   CAN2_ORed_Handler                     ; 120, offset : 220H, CAN2 OR'ed [Bus Off OR Transmit Warning OR Receive Warning]
        DCD   CAN2_Error_Handler                    ; 121, offset : 224H, CAN2 Interrupt indicating that errors were detected on the CAN bus
        DCD   CAN2_EccErr_Handler                   ; 122, offset : 228H, CAN2 ECC error
        DCD   CAN2_ORed_0_15_MB_Handler             ; 123, offset : 22CH, CAN2 OR'ed Message buffer (0-15)
        DCD   CAN2_ORed_16_31_MB_Handler            ; 124, offset : 230H, CAN2 OR'ed Message buffer (16-32)
        DCD   Default_Handler                       ; 125, offset : 234H, Reserved
        DCD   Default_Handler                       ; 126, offset : 238H, Reserved
        DCD   CAN2_EdgeWakeup_Handler               ; 127, offset : 23CH, CAN2 self wakeup by edge
        DCD   CAN3_ORed_Handler                     ; 128, offset : 240H, CAN3 OR'ed [Bus Off OR Transmit Warning OR Receive Warning]
        DCD   CAN3_Error_Handler                    ; 129, offset : 244H, CAN3 Interrupt indicating that errors were detected on the CAN bus
        DCD   CAN3_EccErr_Handler                   ; 130, offset : 248H, CAN3 ECC error
        DCD   CAN3_ORed_0_15_MB_Handler             ; 131, offset : 24CH, CAN3 OR'ed Message buffer (0-15)
        DCD   CAN3_ORed_16_31_MB_Handler            ; 132, offset : 250H, CAN3 OR'ed Message buffer (16-31)
        DCD   Default_Handler                       ; 133, offset : 254H, Reserved
        DCD   Default_Handler                       ; 134, offset : 258H, Reserved
        DCD   CAN3_EdgeWakeup_Handler               ; 135, offset : 25CH, CAN3 self wakeup by edge
        DCD   Default_Handler                       ; 136 
        DCD   Default_Handler                       ; 137 
        DCD   Default_Handler                       ; 138 
        DCD   Default_Handler                       ; 139 
        DCD   Default_Handler                       ; 140 
        DCD   Default_Handler                       ; 141 
        DCD   Default_Handler                       ; 142 
        DCD   Default_Handler                       ; 143 
        DCD   Default_Handler                       ; 144 
        DCD   Default_Handler                       ; 145 
        DCD   Default_Handler                       ; 146 
        DCD   Default_Handler                       ; 147 
        DCD   Default_Handler                       ; 148 
        DCD   Default_Handler                       ; 149 
        DCD   Default_Handler                       ; 150 
        DCD   Default_Handler                       ; 151 
        DCD   Default_Handler                       ; 152 
        DCD   Default_Handler                       ; 153 
        DCD   Default_Handler                       ; 154 
        DCD   Default_Handler                       ; 155 
        DCD   Default_Handler                       ; 156 
        DCD   Default_Handler                       ; 157 
        DCD   Default_Handler                       ; 158 
        DCD   Default_Handler                       ; 159 
        DCD   Default_Handler                       ; 160 
        DCD   Default_Handler                       ; 161 
        DCD   Default_Handler                       ; 162 
        DCD   Default_Handler                       ; 163 
        DCD   Default_Handler                       ; 164 
        DCD   Default_Handler                       ; 165 
        DCD   Default_Handler                       ; 166 
        DCD   Default_Handler                       ; 167 
        DCD   Default_Handler                       ; 168 
        DCD   Default_Handler                       ; 169 
        DCD   Default_Handler                       ; 170 
        DCD   Default_Handler                       ; 171 
        DCD   Default_Handler                       ; 172 
        DCD   Default_Handler                       ; 173 
        DCD   Default_Handler                       ; 174 
        DCD   Default_Handler                       ; 175 
        DCD   Default_Handler                       ; 176 
        DCD   Default_Handler                       ; 177 
        DCD   Default_Handler                       ; 178 
        DCD   Default_Handler                       ; 179 
        DCD   Default_Handler                       ; 180 
        DCD   Default_Handler                       ; 181 
        DCD   Default_Handler                       ; 182 
        DCD   Default_Handler                       ; 183 
        DCD   Default_Handler                       ; 184 
        DCD   Default_Handler                       ; 185 
        DCD   Default_Handler                       ; 186 
        DCD   Default_Handler                       ; 187 
        DCD   Default_Handler                       ; 188 
        DCD   Default_Handler                       ; 189 
        DCD   Default_Handler                       ; 190 
        DCD   Default_Handler                       ; 191 
        DCD   Default_Handler                       ; 192 
        DCD   Default_Handler                       ; 193 
        DCD   Default_Handler                       ; 194 
        DCD   Default_Handler                       ; 195 
        DCD   Default_Handler                       ; 196 
        DCD   Default_Handler                       ; 197 
        DCD   Default_Handler                       ; 198 
        DCD   Default_Handler                       ; 199 
        DCD   Default_Handler                       ; 200 
        DCD   Default_Handler                       ; 201 
        DCD   Default_Handler                       ; 202 
        DCD   Default_Handler                       ; 203 
        DCD   Default_Handler                       ; 204 
        DCD   Default_Handler                       ; 205 
        DCD   Default_Handler                       ; 206 
        DCD   Default_Handler                       ; 207 
        DCD   Default_Handler                       ; 208 
        DCD   Default_Handler                       ; 209 
        DCD   Default_Handler                       ; 210 
        DCD   Default_Handler                       ; 211 
        DCD   Default_Handler                       ; 212 
        DCD   Default_Handler                       ; 213 
        DCD   Default_Handler                       ; 214 
        DCD   Default_Handler                       ; 215 
        DCD   Default_Handler                       ; 216 
        DCD   Default_Handler                       ; 217 
        DCD   Default_Handler                       ; 218 
        DCD   Default_Handler                       ; 219 
        DCD   Default_Handler                       ; 220 
        DCD   Default_Handler                       ; 221 
        DCD   Default_Handler                       ; 222 
        DCD   Default_Handler                       ; 223 
        DCD   Default_Handler                       ; 224 
        DCD   Default_Handler                       ; 225 
        DCD   Default_Handler                       ; 226 
        DCD   Default_Handler                       ; 227 
        DCD   Default_Handler                       ; 228 
        DCD   Default_Handler                       ; 229 
        DCD   Default_Handler                       ; 230 
        DCD   Default_Handler                       ; 231 
        DCD   Default_Handler                       ; 232 
        DCD   Default_Handler                       ; 233 
        DCD   Default_Handler                       ; 234 
        DCD   Default_Handler                       ; 235 
        DCD   Default_Handler                       ; 236 
        DCD   Default_Handler                       ; 237 
        DCD   Default_Handler                       ; 238 
        DCD   Default_Handler                       ; 239
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size 	EQU   __Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        CPSID   I               ; Mask interrupts
        ;; Init the rest of the registers
        LDR     R1,=0
        LDR     R2,=0
        LDR     R3,=0
        LDR     R4,=0
        LDR     R5,=0
        LDR     R6,=0
        LDR     R7,=0
        MOV     R8,R7
        MOV     R9,R7
        MOV     R10,R7
        MOV     R11,R7
        MOV     R12,R7

#ifdef START_FROM_FLASH
        IMPORT __RAM_START, __RAM_END
        ;; INIT ECC RAM

        LDR R1, =__RAM_START
        LDR R2, =__RAM_END

        SUBS    R2, R2, R1
        SUBS    R2, #1
        BLE .LC5

        MOVS    R0, #0
        MOVS    R3, #4
    .LC4:
        STR R0, [R1]
        ADD	R1, R1, R3
        SUBS R2, #4
        BGE .LC4
    .LC5:
#endif
        ;; Initialize the stack pointer
        LDR     R0, =sfe(CSTACK)
        MOV     R13,R0

#ifndef __NO_SYSTEM_INIT
        ;; Call the CMSIS system init routine
        LDR     R0, =SystemInit
        BLX     R0
#endif

        ;; Init .data and .bss sections
        LDR     R0, =init_data_bss
        BLX     R0
        CPSIE   I               ; Unmask interrupts
        BL      main
JumpToSelf
        B       JumpToSelf

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B .

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B .

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B .

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B .

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B .

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B .

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B .

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B .

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B .

        PUBWEAK  DMA0_Handler                       
        PUBWEAK  DMA1_Handler                       
        PUBWEAK  DMA2_Handler                       
        PUBWEAK  DMA3_Handler                       
        PUBWEAK  DMA4_Handler                       
        PUBWEAK  DMA5_Handler                       
        PUBWEAK  DMA6_Handler                       
        PUBWEAK  DMA7_Handler                       
        PUBWEAK  DMA8_Handler                       
        PUBWEAK  DMA9_Handler                       
        PUBWEAK  DMA10_Handler                      
        PUBWEAK  DMA11_Handler                      
        PUBWEAK  DMA12_Handler                      
        PUBWEAK  DMA13_Handler                      
        PUBWEAK  DMA14_Handler                      
        PUBWEAK  DMA15_Handler                      
        PUBWEAK  DMA_Error_Handler                  
        PUBWEAK  MCM_Handler                        
        PUBWEAK  FTFC_Handler                       
        PUBWEAK  FTFC_ReadCollision_Handler         
        PUBWEAK  FTFC_Fault_Handler                 
        PUBWEAK  WDOG_Handler                       
        PUBWEAK  EWM_Handler                        
        PUBWEAK  RCM_Handler                        
        PUBWEAK  I2C0_Handler                       
        PUBWEAK  SPI0_Handler                       
        PUBWEAK  SPI1_Handler                       
        PUBWEAK  SPI2_Handler
        PUBWEAK  SPI3_Handler  
        PUBWEAK  UART0_RxTx_Handler                 
        PUBWEAK  UART1_RxTx_Handler                 
        PUBWEAK  UART2_RxTx_Handler
        PUBWEAK  UART3_RxTx_Handler   
        PUBWEAK  FCCU_Handler                       
        PUBWEAK  FCCU_CfgTO_Handler                 
        PUBWEAK  PRNG_Handler                       
        PUBWEAK  CSE_Handler                        
        PUBWEAK  ADC0_Handler                       
        PUBWEAK  ADC1_Handler                       
        PUBWEAK  PDB0_Handler                       
        PUBWEAK  PDB1_Handler                       
        PUBWEAK  CMP0_Handler                       
        PUBWEAK  LPTMR0_Handler                     
        PUBWEAK  RTC_Handler                        
        PUBWEAK  RTC_Seconds_Handler                
        PUBWEAK  LPIT0_Ch0_Handler                  
        PUBWEAK  LPIT0_Ch1_Handler                  
        PUBWEAK  LPIT0_Ch2_Handler                  
        PUBWEAK  LPIT0_Ch3_Handler                  
        PUBWEAK  PORTA_Handler                      
        PUBWEAK  PORTB_Handler                      
        PUBWEAK  PORTC_Handler                      
        PUBWEAK  PORTD_Handler                      
        PUBWEAK  PORTE_Handler    
        PUBWEAK  I2S_Slave_Handler                  
        PUBWEAK  I2S_Master_Handler 		
        PUBWEAK  MFT0_Ch0_Ch1_Handler               
        PUBWEAK  MFT0_Ch2_Ch3_Handler               
        PUBWEAK  MFT0_Ch4_Ch5_Handler               
        PUBWEAK  MFT0_Ch6_Ch7_Handler               
        PUBWEAK  MFT0_Fault_Handler                 
        PUBWEAK  MFT0_Ovf_Reload_Handler            
        PUBWEAK  MFT1_Ch0_Ch1_Handler               
        PUBWEAK  MFT1_Ch2_Ch3_Handler               
        PUBWEAK  MFT1_Ch4_Ch5_Handler               
        PUBWEAK  MFT1_Ch6_Ch7_Handler               
        PUBWEAK  MFT1_Fault_Handler                 
        PUBWEAK  MFT1_Ovf_Reload_Handler                            
        PUBWEAK  MFT2_Ch0_Ch1_Handler               
        PUBWEAK  MFT2_Ch2_Ch3_Handler               
        PUBWEAK  MFT2_Ch4_Ch5_Handler               
        PUBWEAK  MFT2_Ch6_Ch7_Handler               
        PUBWEAK  MFT2_Fault_Handler                 
        PUBWEAK  MFT2_Ovf_Reload_Handler            
        PUBWEAK  MFT3_Ch0_Ch1_Handler               
        PUBWEAK  MFT3_Ch2_Ch3_Handler               
        PUBWEAK  MFT3_Ch4_Ch5_Handler               
        PUBWEAK  MFT3_Ch6_Ch7_Handler               
        PUBWEAK  MFT3_Fault_Handler                 
        PUBWEAK  MFT3_Ovf_Reload_Handler  
        PUBWEAK  MFT4_Ch0_Ch1_Handler   
        PUBWEAK  MFT4_Ch2_Ch3_Handler   
        PUBWEAK  MFT4_Ch4_Ch5_Handler   
        PUBWEAK  MFT4_Ch6_Ch7_Handler   
        PUBWEAK  MFT4_Fault_Handler     
        PUBWEAK  MFT4_Ovf_Reload_Handler
        PUBWEAK  MFT5_Ch0_Ch1_Handler   
        PUBWEAK  MFT5_Ch2_Ch3_Handler   
        PUBWEAK  MFT5_Ch4_Ch5_Handler   
        PUBWEAK  MFT5_Ch6_Ch7_Handler   
        PUBWEAK  MFT5_Fault_Handler     
        PUBWEAK  MFT5_Ovf_Reload_Handler
        PUBWEAK  CMU_Firc_Handler                   
        PUBWEAK  CMU_Pll_Handler                    
        PUBWEAK  CMU_Sosc_Handler                   
        PUBWEAK  CAN0_ORed_Handler                  
        PUBWEAK  CAN0_Error_Handler                 
        PUBWEAK  CAN0_FrameWakeup_Handler           
        PUBWEAK  CAN0_ORed_0_15_MB_Handler          
        PUBWEAK  CAN0_ORed_16_31_MB_Handler         
        PUBWEAK  CAN0_ORed_32_47_MB_Handler         
        PUBWEAK  CAN0_ORed_48_63_MB_Handler         
        PUBWEAK  CAN0_ORed_64_79_MB_Handler         
        PUBWEAK  CAN0_ORed_80_95_MB_Handler         
        PUBWEAK  CAN0_EdgeWakeup_Handler            
        PUBWEAK  CAN0_EccErr_Handler  
        PUBWEAK  CAN0_ERxFIFO_Handler
        PUBWEAK  CAN1_ORed_Handler                  
        PUBWEAK  CAN1_Error_Handler                 
        PUBWEAK  CAN1_EccErr_Handler                
        PUBWEAK  CAN1_ORed_0_15_MB_Handler          
        PUBWEAK  CAN1_ORed_16_31_MB_Handler         
        PUBWEAK  CAN1_ORed_32_47_MB_Handler         
        PUBWEAK  CAN1_ORed_48_63_MB_Handler         
        PUBWEAK  CAN1_EdgeWakeup_Handler            
        PUBWEAK  CAN2_ORed_Handler                  
        PUBWEAK  CAN2_Error_Handler                 
        PUBWEAK  CAN2_EccErr_Handler                
        PUBWEAK  CAN2_ORed_0_15_MB_Handler          
        PUBWEAK  CAN2_ORed_16_31_MB_Handler  
        PUBWEAK  CAN2_EdgeWakeup_Handler
        PUBWEAK  CAN3_ORed_Handler                  
        PUBWEAK  CAN3_Error_Handler                 
        PUBWEAK  CAN3_EccErr_Handler                
        PUBWEAK  CAN3_ORed_0_15_MB_Handler          
        PUBWEAK  CAN3_ORed_16_31_MB_Handler         
        PUBWEAK  CAN3_EdgeWakeup_Handler
        PUBWEAK  Default_Handler       
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA0_Handler
DMA1_Handler
DMA2_Handler
DMA3_Handler
DMA4_Handler
DMA5_Handler
DMA6_Handler
DMA7_Handler
DMA8_Handler
DMA9_Handler
DMA10_Handler
DMA11_Handler
DMA12_Handler
DMA13_Handler
DMA14_Handler
DMA15_Handler
DMA_Error_Handler
MCM_Handler
FTFC_Handler
FTFC_ReadCollision_Handler
FTFC_Fault_Handler
WDOG_Handler
EWM_Handler
RCM_Handler
I2C0_Handler
SPI0_Handler
SPI1_Handler
SPI2_Handler
SPI3_Handler
UART0_RxTx_Handler
UART1_RxTx_Handler
UART2_RxTx_Handler
UART3_RxTx_Handler
FCCU_Handler
FCCU_CfgTO_Handler
PRNG_Handler
CSE_Handler
ADC0_Handler
ADC1_Handler
PDB0_Handler
PDB1_Handler
CMP0_Handler
LPTMR0_Handler
RTC_Handler
RTC_Seconds_Handler
LPIT0_Ch0_Handler
LPIT0_Ch1_Handler
LPIT0_Ch2_Handler
LPIT0_Ch3_Handler
PORTA_Handler
PORTB_Handler
PORTC_Handler
PORTD_Handler
PORTE_Handler
I2S_Slave_Handler
I2S_Master_Handler
MFT0_Ch0_Ch1_Handler
MFT0_Ch2_Ch3_Handler
MFT0_Ch4_Ch5_Handler
MFT0_Ch6_Ch7_Handler
MFT0_Fault_Handler
MFT0_Ovf_Reload_Handler
MFT1_Ch0_Ch1_Handler
MFT1_Ch2_Ch3_Handler
MFT1_Ch4_Ch5_Handler
MFT1_Ch6_Ch7_Handler
MFT1_Fault_Handler
MFT1_Ovf_Reload_Handler
MFT2_Ch0_Ch1_Handler
MFT2_Ch2_Ch3_Handler
MFT2_Ch4_Ch5_Handler
MFT2_Ch6_Ch7_Handler
MFT2_Fault_Handler
MFT2_Ovf_Reload_Handler
MFT3_Ch0_Ch1_Handler
MFT3_Ch2_Ch3_Handler
MFT3_Ch4_Ch5_Handler
MFT3_Ch6_Ch7_Handler
MFT3_Fault_Handler
MFT3_Ovf_Reload_Handler	
MFT4_Ch0_Ch1_Handler   
MFT4_Ch2_Ch3_Handler   
MFT4_Ch4_Ch5_Handler   
MFT4_Ch6_Ch7_Handler   
MFT4_Fault_Handler     
MFT4_Ovf_Reload_Handler
MFT5_Ch0_Ch1_Handler   
MFT5_Ch2_Ch3_Handler   
MFT5_Ch4_Ch5_Handler   
MFT5_Ch6_Ch7_Handler   
MFT5_Fault_Handler     
MFT5_Ovf_Reload_Handler
CMU_Firc_Handler
CMU_Pll_Handler
CMU_Sosc_Handler
CAN0_ORed_Handler
CAN0_Error_Handler
CAN0_FrameWakeup_Handler
CAN0_ORed_0_15_MB_Handler
CAN0_ORed_16_31_MB_Handler
CAN0_ORed_32_47_MB_Handler
CAN0_ORed_48_63_MB_Handler
CAN0_ORed_64_79_MB_Handler
CAN0_ORed_80_95_MB_Handler
CAN0_EdgeWakeup_Handler
CAN0_EccErr_Handler
CAN0_ERxFIFO_Handler
CAN1_ORed_Handler
CAN1_Error_Handler
CAN1_EccErr_Handler
CAN1_ORed_0_15_MB_Handler
CAN1_ORed_16_31_MB_Handler
CAN1_ORed_32_47_MB_Handler
CAN1_ORed_48_63_MB_Handler
CAN1_EdgeWakeup_Handler
CAN2_ORed_Handler
CAN2_Error_Handler
CAN2_EccErr_Handler
CAN2_ORed_0_15_MB_Handler
CAN2_ORed_16_31_MB_Handler
CAN2_EdgeWakeup_Handler
CAN3_ORed_Handler
CAN3_Error_Handler
CAN3_EccErr_Handler
CAN3_ORed_0_15_MB_Handler
CAN3_ORed_16_31_MB_Handler
CAN3_EdgeWakeup_Handler
Default_Handler
        B Default_Handler

        END

/************************ (C) COPYRIGHT CVAChip *****END OF FILE****/