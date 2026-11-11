/*
 * Copyright (c) 2022, Shenzhen CVA Innovation CO.,LTD
 * All rights reserved.
 *
 * Shenzhen CVA Innovation CO.,LTD (CVA chip) is supplying this file for use
 * exclusively with CVA's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * CVA SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 */

/*****************************************************************************/
/* Version: GNU Compiler Collection                                          */
/*****************************************************************************/
    .syntax unified
    .arch armv7-m

    .equ ACG_LOCK_REG,0x4007F880
    .equ ACG_SYS_REG,0x4007F810
    .equ CACHE_CTRL_REG,0xE0082000
    .equ SIM_FLASH_REG,0x4005F02C

    .section .isr_vector, "a"
    .align 2
    .globl __isr_vector
__isr_vector:
    .long   __StackTop                              /* -16, offset : 000H, Top of Stack */
    .long   Reset_Handler                           /* -15, offset : 004H, Reset Handler */
    .long   NMI_Handler                             /* -14, offset : 008H, NMI Handler */
    .long   HardFault_Handler                       /* -13, offset : 00CH, Hard Fault Handler */
    .long   MemManage_Handler                       /* -12, offset : 010H, MPU Fault Handler */
    .long   BusFault_Handler                        /* -11, offset : 014H, Bus Fault Handler */
    .long   UsageFault_Handler                      /* -10, offset : 018H, Usage Fault Handler */
    .long   Default_Handler                         /* -9, offset : 01CH, Reserved */
    .long   Default_Handler                         /* -8, offset : 020H, Reserved */
    .long   Default_Handler                         /* -7, offset : 024H, Reserved */
    .long   Default_Handler                         /* -6, offset : 028H, Reserved */
    .long   SVC_Handler                             /* -5, offset : 02CH, SVCall Handler */
    .long   DebugMon_Handler                        /* -4, offset : 030H, Debug Monitor Handler */
    .long   Default_Handler                         /* -3, offset : 034H, Reserved */
    .long   PendSV_Handler                          /* -2, offset : 038H, PendSV Handler */
    .long   SysTick_Handler                         /* -1, offset : 03CH, SysTick Handler */

                                                    /* External Interrupts */
    .long   DMA0_Handler                            /* 0, offset : 040H, DMA channel 0 transfer complete */
    .long   DMA1_Handler                            /* 1, offset : 044H, DMA channel 1 transfer complete */
    .long   DMA2_Handler                            /* 2, offset : 048H, DMA channel 2 transfer complete */
    .long   DMA3_Handler                            /* 3, offset : 04CH, DMA channel 3 transfer complete */
    .long   DMA4_Handler                            /* 4, offset : 050H, DMA channel 4 transfer complete */
    .long   DMA5_Handler                            /* 5, offset : 054H, DMA channel 5 transfer complete */
    .long   DMA6_Handler                            /* 6, offset : 058H, DMA channel 6 transfer complete */
    .long   DMA7_Handler                            /* 7, offset : 05CH, DMA channel 7 transfer complete */
    .long   DMA8_Handler                            /* 8, offset : 060H, DMA channel 8 transfer complete */
    .long   DMA9_Handler                            /* 9, offset : 064H, DMA channel 9 transfer complete */
    .long   DMA10_Handler                           /* 10, offset : 068H, DMA channel 10 transfer complete */
    .long   DMA11_Handler                           /* 11, offset : 06CH, DMA channel 11 transfer complete */
    .long   DMA12_Handler                           /* 12, offset : 070H, DMA channel 12 transfer complete */
    .long   DMA13_Handler                           /* 13, offset : 074H, DMA channel 13 transfer complete */
    .long   DMA14_Handler                           /* 14, offset : 078H, DMA channel 14 transfer complete */
    .long   DMA15_Handler                           /* 15, offset : 07CH, DMA channel 15 transfer complete */
    .long   DMA_Error_Handler                       /* 16, offset : 080H, DMA error interrupt channels 0-15 */
    .long   MCM_Handler                             /* 17, offset : 084H, FPU sources */
    .long   FTFC_Handler                            /* 18, offset : 088H, FTFC Command complete */
    .long   FTFC_ReadCollision_Handler              /* 19, offset : 08CH, FTFC Read collision */
    .long   Default_Handler                         /* 20, offset : 090H, Reserved */
    .long   FTFC_Fault_Handler                      /* 21, offset : 094H, FTFC Double bit fault detect */
    .long   WDOG_Handler                            /* 22, offset : 098H, Single interrupt vector for WDOG */
    .long   EWM_Handler                             /* 23, offset : 09CH, Single interrupt vector for EWM */
    .long   RCM_Handler                             /* 24, offset : 0A0H, RCM Asynchronous Interrupt */
    .long   I2C0_Handler                            /* 25, offset : 0A4H, I2C0 Master Interrupt */
    .long   SPI0_Handler                            /* 26, offset : 0A8H, SPI0 Interrupt */
    .long   SPI1_Handler                            /* 27, offset : 0ACH, SPI1 Interrupt */
    .long   SPI2_Handler                            /* 28, offset : 0B0H, SPI2 Interrupt */
    .long   SPI3_Handler                            /* 29, offset : 0B4H, SPI3 Interrupt */
    .long   Default_Handler                         /* 30, offset : 0B8H, Reserved */
    .long   UART0_RxTx_Handler                      /* 31, offset : 0BCH, UART0 Transmit / Receive Interrupt */
    .long   UART1_RxTx_Handler                      /* 32, offset : 0C0H, UART1 Transmit / Receive Interrupt */
    .long   UART2_RxTx_Handler                      /* 33, offset : 0C4H, UART2 Transmit / Receive Interrupt */
    .long   UART3_RxTx_Handler                      /* 34, offset : 0C8H, UART3 Transmit / Receive Interrupt */ 
    .long   FCCU_Handler                            /* 35, offset : 0CCH, FCCU Interrupt */
    .long   FCCU_CfgTO_Handler                      /* 36, offset : 0D0H, FCCU Configuration Timeout Interrupt */
    .long   PRNG_Handler                            /* 37, offset : 0D4H, PRNG Interrupt */
    .long   CSE_Handler                             /* 38, offset : 0D8H, CSE Interrupt */
    .long   ADC0_Handler                            /* 39, offset : 0DCH, ADC0 interrupt request */
    .long   ADC1_Handler                            /* 40, offset : 0E0H, ADC1 interrupt request */
    .long   PDB0_Handler                            /* 41, offset : 0E4H, PDB0 interrupt */
    .long   PDB1_Handler                            /* 42, offset : 0E8H, PDB1 interrupt */
    .long   CMP0_Handler                            /* 43, offset : 0ECH, CMP0 interrupt request */
    .long   Default_Handler                         /* 44, offset : 0F0H, Reserved */
    .long   LPTMR0_Handler                          /* 45, offset : 0F4H, LPTIMER interrupt request */
    .long   RTC_Handler                             /* 46, offset : 0F8H, RTC alarm interrupt */
    .long   RTC_Seconds_Handler                     /* 47, offset : 0FCH, RTC seconds interrupt */
    .long   LPIT0_Ch0_Handler                       /* 48, offset : 100H, LPIT0 channel 0 overflow interrupt */
    .long   LPIT0_Ch1_Handler                       /* 49, offset : 104H, LPIT0 channel 1 overflow interrupt */
    .long   LPIT0_Ch2_Handler                       /* 50, offset : 108H, LPIT0 channel 2 overflow interrupt */
    .long   LPIT0_Ch3_Handler                       /* 51, offset : 10CH, LPIT0 channel 3 overflow interrupt */
    .long   Default_Handler                         /* 52, offset : 110H, Reserved */
    .long   PORTA_Handler                           /* 53, offset : 114H, Port A pin detect interrupt */
    .long   PORTB_Handler                           /* 54, offset : 118H, Port B pin detect interrupt */
    .long   PORTC_Handler                           /* 55, offset : 11CH, Port C pin detect interrupt */
    .long   PORTD_Handler                           /* 56, offset : 120H, Port D pin detect interrupt */
    .long   PORTE_Handler                           /* 57, offset : 124H, Port E pin detect interrupt */
    .long   I2S_Slave_Handler                       /* 58, offset : 158H, I2S Slave interrupt */
    .long   I2S_Master_Handler                      /* 59, offset : 15CH, I2S Master interrupt */
    .long   MFT0_Ch0_Ch1_Handler                    /* 60, offset : 128H, MFT0 Channel 0 and 1 interrupt */
    .long   MFT0_Ch2_Ch3_Handler                    /* 61, offset : 12CH, MFT0 Channel 2 and 3 interrupt */
    .long   MFT0_Ch4_Ch5_Handler                    /* 62, offset : 130H, MFT0 Channel 4 and 5 interrupt */
    .long   MFT0_Ch6_Ch7_Handler                    /* 63, offset : 134H, MFT0 Channel 6 and 7 interrupt */
    .long   MFT0_Fault_Handler                      /* 64, offset : 138H, MFT0 Fault interrupt */
    .long   MFT0_Ovf_Reload_Handler                 /* 65, offset : 13CH, MFT0 Counter overflow and Reload interrupt */
    .long   MFT1_Ch0_Ch1_Handler                    /* 66, offset : 140H, MFT1 Channel 0 and 1 interrupt */
    .long   MFT1_Ch2_Ch3_Handler                    /* 67, offset : 144H, MFT1 Channel 2 and 3 interrupt */
    .long   MFT1_Ch4_Ch5_Handler                    /* 68, offset : 148H, MFT1 Channel 4 and 5 interrupt */
    .long   MFT1_Ch6_Ch7_Handler                    /* 69, offset : 14CH, MFT1 Channel 6 and 7 interrupt */
    .long   MFT1_Fault_Handler                      /* 70, offset : 150H, MFT1 Fault interrupt */
    .long   MFT1_Ovf_Reload_Handler                 /* 71, offset : 154H, MFT1 Counter overflow and Reload interrupt */
    .long   MFT2_Ch0_Ch1_Handler                    /* 72, offset : 160H, MFT2 Channel 0 and 1 interrupt */
    .long   MFT2_Ch2_Ch3_Handler                    /* 73, offset : 164H, MFT2 Channel 2 and 3 interrupt */
    .long   MFT2_Ch4_Ch5_Handler                    /* 74, offset : 168H, MFT2 Channel 4 and 5 interrupt */
    .long   MFT2_Ch6_Ch7_Handler                    /* 75, offset : 16CH, MFT2 Channel 6 and 7 interrupt */
    .long   MFT2_Fault_Handler                      /* 76, offset : 170H, MFT2 Fault interrupt */
    .long   MFT2_Ovf_Reload_Handler                 /* 77, offset : 174H, MFT2 Counter overflow and Reload interrupt */
    .long   MFT3_Ch0_Ch1_Handler                    /* 78, offset : 178H, MFT3 Channel 0 and 1 interrupt */
    .long   MFT3_Ch2_Ch3_Handler                    /* 79, offset : 17CH, MFT3 Channel 2 and 3 interrupt */
    .long   MFT3_Ch4_Ch5_Handler                    /* 80, offset : 180H, MFT3 Channel 4 and 5 interrupt */
    .long   MFT3_Ch6_Ch7_Handler                    /* 81, offset : 184H, MFT3 Channel 6 and 7 interrupt */
    .long   MFT3_Fault_Handler                      /* 82, offset : 188H, MFT3 Fault interrupt */
    .long   MFT3_Ovf_Reload_Handler                 /* 83, offset : 18CH, MFT3 Counter overflow and Reload interrupt */
    .long   MFT4_Ch0_Ch1_Handler                    /* 84, offset : 190H, MFT4 Channel 0 and 1 interrupt */
    .long   MFT4_Ch2_Ch3_Handler                    /* 85, offset : 194H, MFT4 Channel 2 and 3 interrupt */
    .long   MFT4_Ch4_Ch5_Handler                    /* 86, offset : 198H, MFT4 Channel 4 and 5 interrupt */
    .long   MFT4_Ch6_Ch7_Handler                    /* 87, offset : 19CH, MFT4 Channel 6 and 7 interrupt */
    .long   MFT4_Fault_Handler                      /* 88, offset : 1A0H, MFT4 Fault interrupt */
    .long   MFT4_Ovf_Reload_Handler                 /* 89, offset : 1A4H, MFT4 Counter overflow and Reload interrupt */
    .long   MFT5_Ch0_Ch1_Handler                    /* 90, offset : 1A8H, MFT5 Channel 0 and 1 interrupt */
    .long   MFT5_Ch2_Ch3_Handler                    /* 91, offset : 1ACH, MFT5 Channel 2 and 3 interrupt */
    .long   MFT5_Ch4_Ch5_Handler                    /* 92, offset : 1B0H, MFT5 Channel 4 and 5 interrupt */
    .long   MFT5_Ch6_Ch7_Handler                    /* 93, offset : 1B4H, MFT5 Channel 6 and 7 interrupt */
    .long   MFT5_Fault_Handler                      /* 94, offset : 1B8H, MFT5 Fault interrupt */
    .long   MFT5_Ovf_Reload_Handler                 /* 95, offset : 1BCH, MFT5 Counter overflow and Reload interrupt */
    .long   CMU_Firc_Handler                        /* 96, offset : 1C0H, CMU FIRC interrupt */
    .long   CMU_Pll_Handler                         /* 97, offset : 1C4H, CMU PLL interrupt */
    .long   CMU_Sosc_Handler                        /* 98, offset : 1C8H, CMU SOSC interrupt */
    .long   Default_Handler                         /* 99, offset : 1CCH, Reserved */
    .long   CAN0_ORed_Handler                       /* 100, offset : 1D0H, CAN0 OR'ed [Bus Off OR Transmit Warning OR Receive Warning] */
    .long   CAN0_Error_Handler                      /* 101, offset : 1D4H, CAN0 Interrupt indicating that errors were detected on the CAN bus */
    .long   CAN0_FrameWakeup_Handler                /* 102, offset : 1D8H, CAN0 Pretended Networking operation is enabled, and a valid message match or timeout during Low Power mode */
    .long   CAN0_ORed_0_15_MB_Handler               /* 103, offset : 1DCH, CAN0 OR'ed Message buffer (0-15) */
    .long   CAN0_ORed_16_31_MB_Handler              /* 104, offset : 1E0H, CAN0 OR'ed Message buffer (16-31) */
    .long   CAN0_ORed_32_47_MB_Handler              /* 105, offset : 1E4H, CAN0 OR'ed Message buffer (32-47) */
    .long   CAN0_ORed_48_63_MB_Handler              /* 106, offset : 1E8H, CAN0 OR'ed Message buffer (48-63) */
    .long   CAN0_ORed_64_79_MB_Handler              /* 107, offset : 1ECH, CAN0 OR'ed Message buffer (64-79) */
    .long   CAN0_ORed_80_95_MB_Handler              /* 108, offset : 1F0H, CAN0 OR'ed Message buffer (80-95) */
    .long   CAN0_EdgeWakeup_Handler                 /* 109, offset : 1F4H, CAN0 self wakeup by edge */
    .long   CAN0_EccErr_Handler                     /* 110, offset : 1F8H, CAN0 ECC error */
    .long   CAN0_ERxFIFO_Handler                    /* 111, offset : 1FCH, CAN0 Enhanced Rx FIFO related interrupts */
    .long   CAN1_ORed_Handler                       /* 112, offset : 200H, CAN1 OR'ed [Bus Off OR Transmit Warning OR Receive Warning] */
    .long   CAN1_Error_Handler                      /* 113, offset : 204H, CAN1 Interrupt indicating that errors were detected on the CAN bus */
    .long   CAN1_EccErr_Handler                     /* 114, offset : 208H, CAN1 ECC error */
    .long   CAN1_ORed_0_15_MB_Handler               /* 115, offset : 20CH, CAN1 OR'ed Message buffer (0-15) */
    .long   CAN1_ORed_16_31_MB_Handler              /* 116, offset : 210H, CAN1 OR'ed Message buffer (16-31) */
    .long   CAN1_ORed_32_47_MB_Handler              /* 117, offset : 214H, CAN1 OR'ed Message buffer (32-47) */
    .long   CAN1_ORed_48_63_MB_Handler              /* 118, offset : 218H, CAN1 OR'ed Message buffer (48-63) */
    .long   CAN1_EdgeWakeup_Handler                 /* 119, offset : 21CH, CAN1 self wakeup by edge */
    .long   CAN2_ORed_Handler                       /* 120, offset : 220H, CAN2 OR'ed [Bus Off OR Transmit Warning OR Receive Warning] */
    .long   CAN2_Error_Handler                      /* 121, offset : 224H, CAN2 Interrupt indicating that errors were detected on the CAN bus */
    .long   CAN2_EccErr_Handler                     /* 122, offset : 228H, CAN2 ECC error */
    .long   CAN2_ORed_0_15_MB_Handler               /* 123, offset : 22CH, CAN2 OR'ed Message buffer (0-15) */
    .long   CAN2_ORed_16_31_MB_Handler              /* 124, offset : 230H, CAN2 OR'ed Message buffer (16-32) */
    .long   Default_Handler                         /* 125, offset : 234H, Reserved */
    .long   Default_Handler                         /* 126, offset : 238H, Reserved */
    .long   CAN2_EdgeWakeup_Handler                 /* 127, offset : 23CH, CAN2 self wakeup by edge */
    .long   CAN3_ORed_Handler                       /* 128, offset : 240H, CAN3 OR'ed [Bus Off OR Transmit Warning OR Receive Warning] */
    .long   CAN3_Error_Handler                      /* 129, offset : 244H, CAN3 Interrupt indicating that errors were detected on the CAN bus */
    .long   CAN3_EccErr_Handler                     /* 130, offset : 248H, CAN3 ECC error */
    .long   CAN3_ORed_0_15_MB_Handler               /* 131, offset : 24CH, CAN3 OR'ed Message buffer (0-15) */
    .long   CAN3_ORed_16_31_MB_Handler              /* 132, offset : 250H, CAN3 OR'ed Message buffer (16-31) */
    .long   Default_Handler                         /* 133, offset : 254H, Reserved */
    .long   Default_Handler                         /* 134, offset : 258H, Reserved */
    .long   CAN3_EdgeWakeup_Handler                 /* 135, offset : 25CH, CAN3 self wakeup by edge */
    .long   Default_Handler                         /* 136 */
    .long   Default_Handler                         /* 137 */
    .long   Default_Handler                         /* 138 */
    .long   Default_Handler                         /* 139 */
    .long   Default_Handler                         /* 140 */
    .long   Default_Handler                         /* 141 */
    .long   Default_Handler                         /* 142 */
    .long   Default_Handler                         /* 143 */
    .long   Default_Handler                         /* 144 */
    .long   Default_Handler                         /* 145 */
    .long   Default_Handler                         /* 146 */
    .long   Default_Handler                         /* 147 */
    .long   Default_Handler                         /* 148 */
    .long   Default_Handler                         /* 149 */
    .long   Default_Handler                         /* 150 */
    .long   Default_Handler                         /* 151 */
    .long   Default_Handler                         /* 152 */
    .long   Default_Handler                         /* 153 */
    .long   Default_Handler                         /* 154 */
    .long   Default_Handler                         /* 155 */
    .long   Default_Handler                         /* 156 */
    .long   Default_Handler                         /* 157 */
    .long   Default_Handler                         /* 158 */
    .long   Default_Handler                         /* 159 */
    .long   Default_Handler                         /* 160 */
    .long   Default_Handler                         /* 161 */
    .long   Default_Handler                         /* 162 */
    .long   Default_Handler                         /* 163 */
    .long   Default_Handler                         /* 164 */
    .long   Default_Handler                         /* 165 */
    .long   Default_Handler                         /* 166 */
    .long   Default_Handler                         /* 167 */
    .long   Default_Handler                         /* 168 */
    .long   Default_Handler                         /* 169 */
    .long   Default_Handler                         /* 170 */
    .long   Default_Handler                         /* 171 */
    .long   Default_Handler                         /* 172 */
    .long   Default_Handler                         /* 173 */
    .long   Default_Handler                         /* 174 */
    .long   Default_Handler                         /* 175 */
    .long   Default_Handler                         /* 176 */
    .long   Default_Handler                         /* 177 */
    .long   Default_Handler                         /* 178 */
    .long   Default_Handler                         /* 179 */
    .long   Default_Handler                         /* 180 */
    .long   Default_Handler                         /* 181 */
    .long   Default_Handler                         /* 182 */
    .long   Default_Handler                         /* 183 */
    .long   Default_Handler                         /* 184 */
    .long   Default_Handler                         /* 185 */
    .long   Default_Handler                         /* 186 */
    .long   Default_Handler                         /* 187 */
    .long   Default_Handler                         /* 188 */
    .long   Default_Handler                         /* 189 */
    .long   Default_Handler                         /* 190 */
    .long   Default_Handler                         /* 191 */
    .long   Default_Handler                         /* 192 */
    .long   Default_Handler                         /* 193 */
    .long   Default_Handler                         /* 194 */
    .long   Default_Handler                         /* 195 */
    .long   Default_Handler                         /* 196 */
    .long   Default_Handler                         /* 197 */
    .long   Default_Handler                         /* 198 */
    .long   Default_Handler                         /* 199 */
    .long   Default_Handler                         /* 200 */
    .long   Default_Handler                         /* 201 */
    .long   Default_Handler                         /* 202 */
    .long   Default_Handler                         /* 203 */
    .long   Default_Handler                         /* 204 */
    .long   Default_Handler                         /* 205 */
    .long   Default_Handler                         /* 206 */
    .long   Default_Handler                         /* 207 */
    .long   Default_Handler                         /* 208 */
    .long   Default_Handler                         /* 209 */
    .long   Default_Handler                         /* 210 */
    .long   Default_Handler                         /* 211 */
    .long   Default_Handler                         /* 212 */
    .long   Default_Handler                         /* 213 */
    .long   Default_Handler                         /* 214 */
    .long   Default_Handler                         /* 215 */
    .long   Default_Handler                         /* 216 */
    .long   Default_Handler                         /* 217 */
    .long   Default_Handler                         /* 218 */
    .long   Default_Handler                         /* 219 */
    .long   Default_Handler                         /* 220 */
    .long   Default_Handler                         /* 221 */
    .long   Default_Handler                         /* 222 */
    .long   Default_Handler                         /* 223 */
    .long   Default_Handler                         /* 224 */
    .long   Default_Handler                         /* 225 */
    .long   Default_Handler                         /* 226 */
    .long   Default_Handler                         /* 227 */
    .long   Default_Handler                         /* 228 */
    .long   Default_Handler                         /* 229 */
    .long   Default_Handler                         /* 230 */
    .long   Default_Handler                         /* 231 */
    .long   Default_Handler                         /* 232 */
    .long   Default_Handler                         /* 233 */
    .long   Default_Handler                         /* 234 */
    .long   Default_Handler                         /* 235 */
    .long   Default_Handler                         /* 236 */
    .long   Default_Handler                         /* 237 */
    .long   Default_Handler                         /* 238 */
    .long   Default_Handler                         /* 239 */

    .size    __isr_vector, . - __isr_vector

    .text
    .thumb

/* Reset Handler */

    .thumb_func
    .align 2
    .globl   Reset_Handler
    .weak    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    cpsid   i               /* Mask interrupts */

    /* Init the rest of the registers */
    ldr     r1,=0
    ldr     r2,=0
    ldr     r3,=0
    ldr     r4,=0
    ldr     r5,=0
    ldr     r6,=0
    ldr     r7,=0
    mov     r8,r7
    mov     r9,r7
    mov     r10,r7
    mov     r11,r7
    mov     r12,r7

    /* Set DIV_CORE to 0x00 */
    ldr r0, =ACG_LOCK_REG
    ldr r1, =0xFA8623E4
    str r1, [r0]

    ldr r0, =ACG_SYS_REG
    ldr r1, =0x00
    str r1, [r0]

    ldr r0, =ACG_LOCK_REG
    ldr r1, =0x00
    str r1, [r0]

    /* Enable cache and prefetch */
    ldr r0, =CACHE_CTRL_REG
    ldr r1, =0x1C7
    str r1, [r0]

    ldr r0, =SIM_FLASH_REG
    ldr r1, [r0]
    orr r1, r1,#0x01
    str r1, [r0]
#ifdef START_FROM_FLASH

    /* Init ECC RAM */
    ldr r1, =__RAM_START
    ldr r2, =__RAM_END

    subs    r2, r1
    subs    r2, #1
    ble .LC5

    movs    r0, 0
    movs    r3, #4
.LC4:
    str r0, [r1]
    add	r1, r1, r3
    subs r2, 4
    bge .LC4
.LC5:
#endif

    /* Initialize the stack pointer */
    ldr     r0,=__StackTop
    mov     r13,r0

#ifndef __NO_SYSTEM_INIT
    /* Call the system init routine */
    ldr     r0,=SystemInit
    blx     r0
#endif

    /* Init .data and .bss sections */
    ldr     r0,=init_data_bss
    blx     r0
    cpsie   i               /* Unmask interrupts */
    bl      main

JumpToSelf:
    b       JumpToSelf

    .pool
    .size Reset_Handler, . - Reset_Handler

    .align  1
    .thumb_func
    .weak Default_Handler
    .type Default_Handler, %function
Default_Handler:
    b       Default_Handler
    .size Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro def_irq_handler  handler_name
    .weak \handler_name
    .set  \handler_name, Default_Handler
    .endm

/* Exception Handlers */
    def_irq_handler     NMI_Handler
    def_irq_handler     HardFault_Handler
    def_irq_handler     MemManage_Handler
    def_irq_handler     BusFault_Handler
    def_irq_handler     UsageFault_Handler
    def_irq_handler     SVC_Handler
    def_irq_handler     DebugMon_Handler
    def_irq_handler     PendSV_Handler
    def_irq_handler     SysTick_Handler
    def_irq_handler     DMA0_Handler
    def_irq_handler     DMA1_Handler
    def_irq_handler     DMA2_Handler
    def_irq_handler     DMA3_Handler
    def_irq_handler     DMA4_Handler
    def_irq_handler     DMA5_Handler
    def_irq_handler     DMA6_Handler
    def_irq_handler     DMA7_Handler
    def_irq_handler     DMA8_Handler
    def_irq_handler     DMA9_Handler
    def_irq_handler     DMA10_Handler
    def_irq_handler     DMA11_Handler
    def_irq_handler     DMA12_Handler
    def_irq_handler     DMA13_Handler
    def_irq_handler     DMA14_Handler
    def_irq_handler     DMA15_Handler
    def_irq_handler     DMA_Error_Handler
    def_irq_handler     MCM_Handler
    def_irq_handler     FTFC_Handler
    def_irq_handler     FTFC_ReadCollision_Handler
    def_irq_handler     FTFC_Fault_Handler
    def_irq_handler     WDOG_Handler
    def_irq_handler     EWM_Handler
    def_irq_handler     RCM_Handler
    def_irq_handler     I2C0_Handler
    def_irq_handler     SPI0_Handler
    def_irq_handler     SPI1_Handler
    def_irq_handler     SPI2_Handler
    def_irq_handler     SPI3_Handler
    def_irq_handler     UART0_RxTx_Handler
    def_irq_handler     UART1_RxTx_Handler
    def_irq_handler     UART2_RxTx_Handler
    def_irq_handler     UART3_RxTx_Handler
    def_irq_handler     FCCU_Handler
    def_irq_handler     FCCU_CfgTO_Handler
    def_irq_handler     PRNG_Handler
    def_irq_handler     CSE_Handler
    def_irq_handler     ADC0_Handler
    def_irq_handler     ADC1_Handler
    def_irq_handler     PDB0_Handler
    def_irq_handler     PDB1_Handler
    def_irq_handler     CMP0_Handler
    def_irq_handler     LPTMR0_Handler
    def_irq_handler     RTC_Handler
    def_irq_handler     RTC_Seconds_Handler
    def_irq_handler     LPIT0_Ch0_Handler
    def_irq_handler     LPIT0_Ch1_Handler
    def_irq_handler     LPIT0_Ch2_Handler
    def_irq_handler     LPIT0_Ch3_Handler
    def_irq_handler     PORTA_Handler
    def_irq_handler     PORTB_Handler
    def_irq_handler     PORTC_Handler
    def_irq_handler     PORTD_Handler
    def_irq_handler     PORTE_Handler
    def_irq_handler     I2S_Slave_Handler
    def_irq_handler     I2S_Master_Handler
    def_irq_handler     MFT0_Ch0_Ch1_Handler
    def_irq_handler     MFT0_Ch2_Ch3_Handler
    def_irq_handler     MFT0_Ch4_Ch5_Handler
    def_irq_handler     MFT0_Ch6_Ch7_Handler
    def_irq_handler     MFT0_Fault_Handler
    def_irq_handler     MFT0_Ovf_Reload_Handler
    def_irq_handler     MFT1_Ch0_Ch1_Handler
    def_irq_handler     MFT1_Ch2_Ch3_Handler
    def_irq_handler     MFT1_Ch4_Ch5_Handler
    def_irq_handler     MFT1_Ch6_Ch7_Handler
    def_irq_handler     MFT1_Fault_Handler
    def_irq_handler     MFT1_Ovf_Reload_Handler
    def_irq_handler     MFT2_Ch0_Ch1_Handler
    def_irq_handler     MFT2_Ch2_Ch3_Handler
    def_irq_handler     MFT2_Ch4_Ch5_Handler
    def_irq_handler     MFT2_Ch6_Ch7_Handler
    def_irq_handler     MFT2_Fault_Handler
    def_irq_handler     MFT2_Ovf_Reload_Handler
    def_irq_handler     MFT3_Ch0_Ch1_Handler
    def_irq_handler     MFT3_Ch2_Ch3_Handler
    def_irq_handler     MFT3_Ch4_Ch5_Handler
    def_irq_handler     MFT3_Ch6_Ch7_Handler
    def_irq_handler     MFT3_Fault_Handler
    def_irq_handler     MFT3_Ovf_Reload_Handler
    def_irq_handler     MFT4_Ch0_Ch1_Handler
    def_irq_handler     MFT4_Ch2_Ch3_Handler
    def_irq_handler     MFT4_Ch4_Ch5_Handler
    def_irq_handler     MFT4_Ch6_Ch7_Handler
    def_irq_handler     MFT4_Fault_Handler
    def_irq_handler     MFT4_Ovf_Reload_Handler
    def_irq_handler     MFT5_Ch0_Ch1_Handler
    def_irq_handler     MFT5_Ch2_Ch3_Handler
    def_irq_handler     MFT5_Ch4_Ch5_Handler
    def_irq_handler     MFT5_Ch6_Ch7_Handler
    def_irq_handler     MFT5_Fault_Handler
    def_irq_handler     MFT5_Ovf_Reload_Handler
    def_irq_handler     CMU_Firc_Handler
    def_irq_handler     CMU_Pll_Handler
    def_irq_handler     CMU_Sosc_Handler
    def_irq_handler     CAN0_ORed_Handler
    def_irq_handler     CAN0_Error_Handler
    def_irq_handler     CAN0_FrameWakeup_Handler
    def_irq_handler     CAN0_ORed_0_15_MB_Handler
    def_irq_handler     CAN0_ORed_16_31_MB_Handler
    def_irq_handler     CAN0_ORed_32_47_MB_Handler
    def_irq_handler     CAN0_ORed_48_63_MB_Handler
    def_irq_handler     CAN0_ORed_64_79_MB_Handler
    def_irq_handler     CAN0_ORed_80_95_MB_Handler
    def_irq_handler     CAN0_EdgeWakeup_Handler
    def_irq_handler     CAN0_EccErr_Handler
    def_irq_handler     CAN0_ERxFIFO_Handler
    def_irq_handler     CAN1_ORed_Handler
    def_irq_handler     CAN1_Error_Handler
    def_irq_handler     CAN1_EccErr_Handler
    def_irq_handler     CAN1_ORed_0_15_MB_Handler
    def_irq_handler     CAN1_ORed_16_31_MB_Handler
    def_irq_handler     CAN1_ORed_32_47_MB_Handler
    def_irq_handler     CAN1_ORed_48_63_MB_Handler
    def_irq_handler     CAN1_EdgeWakeup_Handler
    def_irq_handler     CAN2_ORed_Handler
    def_irq_handler     CAN2_Error_Handler
    def_irq_handler     CAN2_EccErr_Handler
    def_irq_handler     CAN2_ORed_0_15_MB_Handler
    def_irq_handler     CAN2_ORed_16_31_MB_Handler
    def_irq_handler     CAN2_EdgeWakeup_Handler
    def_irq_handler     CAN3_ORed_Handler
    def_irq_handler     CAN3_Error_Handler
    def_irq_handler     CAN3_EccErr_Handler
    def_irq_handler     CAN3_ORed_0_15_MB_Handler
    def_irq_handler     CAN3_ORed_16_31_MB_Handler
    def_irq_handler     CAN3_EdgeWakeup_Handler

    .end
