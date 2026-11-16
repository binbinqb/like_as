/**
 * @file    boot_fault.c
 * @brief   boot 的故障现场上报（HardFault / BusFault / MemManage）
 * @details 厂商 startup（`startup_M014x_gcc.S`）把**所有**异常入口都
 *          弱别名到同一个 `Default_Handler` 死循环，故障时既不打印也不留现场，
 *          表现就是"串口打到最后一行突然没声、几秒后被看门狗复位"。
 *
 *          排查 D1 第二步的 CAN 收发时，探针连续三次停在同一处，
 *          靠"加打印二分"已经无法判断是读寄存器总线错、栈溢出，还是
 *          打印本身写 UART 卡死 —— 所以这里补一个真正的上报器。
 *
 *          上报内容（ARMv7-M 架构寄存器，地址固定，不依赖任何 SDK）：
 *          - `CFSR`  可配置故障状态（低 8 位 MemManage / 中 8 位 BusFault / 高 16 位 UsageFault）
 *          - `HFSR`  硬故障状态（`FORCED` 置位说明是从上面三类升级上来的）
 *          - `MMFAR` 出错的取/存地址（`CFSR.MMARVALID` 为 1 时有效）
 *          - `BFAR`  出错的访问地址（`CFSR.BFARVALID` 为 1 时有效）
 *          - 出错指令地址 `PC` 与 `LR`（从异常入栈帧里取）
 *          - 栈指针 `SP` 与 `EXC_RETURN`（区分用的是 MSP 还是 PSP）
 *
 * @note    本文件**只属于 boot**。app 的异常入口保持原样（弱别名死循环），
 *          避免给已通过回归的 app 引入新的链接符号与尺寸变化。
 * @warning 处理函数里用的是 `Platform_Printf`（轮询 TDRE 直写 UART）。
 *          如果故障本身就是 UART 卡死引起的，这里会再次卡死 —— 但那也算
 *          一种结论：串口一行都不出，说明故障不在 CPU 侧的取指/访存。
 *
 * @author  binbina
 * @version 1.0
 * @date    2026-11-16
 */

#include <stdint.h>

#include "platform_cvm0146.h"

/* ============================ [ 常量 ] ============================ */

/** @brief SCB 寄存器基地址（ARMv7-M 标准，固定不可配） */
#define SCB_BASE            (0xE000ED00UL)

/** @brief 可配置故障状态寄存器 CFSR，偏移 0x28 */
#define SCB_CFSR            (*(volatile uint32_t *)(SCB_BASE + 0x28UL))

/** @brief 硬故障状态寄存器 HFSR，偏移 0x2C */
#define SCB_HFSR            (*(volatile uint32_t *)(SCB_BASE + 0x2CUL))

/** @brief MemManage 故障地址寄存器 MMFAR，偏移 0x34 */
#define SCB_MMFAR           (*(volatile uint32_t *)(SCB_BASE + 0x34UL))

/** @brief BusFault 故障地址寄存器 BFAR，偏移 0x38 */
#define SCB_BFAR            (*(volatile uint32_t *)(SCB_BASE + 0x38UL))

/** @brief CFSR.BFARVALID：BFAR 内容有效 */
#define CFSR_BFARVALID      (1UL << 15)

/** @brief CFSR.MMARVALID：MMFAR 内容有效 */
#define CFSR_MMARVALID      (1UL << 7)

/** @brief HFSR.FORCED：由 MemManage/BusFault/UsageFault 升级而来 */
#define HFSR_FORCED         (1UL << 30)

/* ============================ [ 内部函数 ] ============================ */

/**
 * @brief 异常入栈帧里各字段的下标
 * @note  异常发生时硬件按 `R0 R1 R2 R3 R12 LR PC xPSR` 顺序压栈，
 *        共 8 个字；`frame[5]` 就是出错指令地址。
 */
#define FRAME_R0            (0u)
#define FRAME_R1            (1u)
#define FRAME_R2            (2u)
#define FRAME_R3            (3u)
#define FRAME_R12           (4u)
#define FRAME_LR            (5u)
#define FRAME_PC            (6u)
#define FRAME_XPSR          (7u)

/**
 * @brief 故障上报主体
 * @param[in] frame 异常入栈帧起始地址（MSP 或 PSP）
 * @param[in] excReturn 异常返回码 `EXC_RETURN`（0xFFFFFFF9=线程+MSP，0xFFFFFFFD=线程+PSP）
 * @note  不返回，打完就原地死循环，等看门狗复位 —— 复位后能重复复现同一现场，
 *        比"自动恢复"更利于定位。
 * @note  `used` 属性不能省：本函数只被 `naked` 函数里的内联汇编 `b` 引用，
 *        编译器看不见这个引用，`-Os` 下会当成"未使用的 static"整段删掉，
 *        结果就是链接期 `undefined reference to Boot_FaultReport`。
 */
__attribute__((used)) static void Boot_FaultReport(uint32_t *frame, uint32_t excReturn)
{
	uint32_t cfsr = SCB_CFSR;
	uint32_t hfsr = SCB_HFSR;

	Platform_Printf("\n[fault] ==== CPU exception ====\n");
	Platform_Printf("[fault] cfsr=%08x hfsr=%08x\n",
	                (unsigned)cfsr, (unsigned)hfsr);

	/* 升级路径说明：看 UFSR/MMFSR/BFSR 哪一段非零就知道是哪一类 */
	if ((hfsr & HFSR_FORCED) != 0u) {
		Platform_Printf("[fault] forced: mmfsr=%02x bfsr=%02x ufsr=%04x\n",
		                (unsigned)(cfsr & 0xFFu),
		                (unsigned)((cfsr >> 8) & 0xFFu),
		                (unsigned)((cfsr >> 16) & 0xFFFFu));
	}

	if ((cfsr & CFSR_BFARVALID) != 0u) {
		Platform_Printf("[fault] BFAR (bad access addr) = %08x\n",
		                (unsigned)SCB_BFAR);
	}
	if ((cfsr & CFSR_MMARVALID) != 0u) {
		Platform_Printf("[fault] MMFAR (bad access addr) = %08x\n",
		                (unsigned)SCB_MMFAR);
	}

	Platform_Printf("[fault] pc=%08x lr=%08x xpsr=%08x\n",
	                (unsigned)frame[FRAME_PC],
	                (unsigned)frame[FRAME_LR],
	                (unsigned)frame[FRAME_XPSR]);
	Platform_Printf("[fault] r0=%08x r1=%08x r2=%08x r3=%08x r12=%08x\n",
	                (unsigned)frame[FRAME_R0], (unsigned)frame[FRAME_R1],
	                (unsigned)frame[FRAME_R2], (unsigned)frame[FRAME_R3],
	                (unsigned)frame[FRAME_R12]);
	Platform_Printf("[fault] sp=%08x exc_return=%08x\n",
	                (unsigned)(uintptr_t)frame, (unsigned)excReturn);

	/* 故障地址上的原始值：读数本身可能再触发一次故障，所以单独打印，
	 * 便于区分"地址没实现（总线错）"还是"值不对（逻辑错）" */
	if ((cfsr & CFSR_BFARVALID) != 0u) {
		Platform_Printf("[fault] *BFAR = %08x\n", (unsigned)*(volatile uint32_t *)SCB_BFAR);
	}

	for (;;) {
		__asm volatile ("nop");
	}
}

/* ============================ [ 异常入口 ] ============================ */

/**
 * @brief 硬故障入口
 * @note  必须 `naked`：要在编译器压栈之前拿到**异常入栈帧**的真实地址，
 *        否则 `msp` 已被序言改过，取到的 PC/LR 全是错的。
 * @warning 覆盖的是 startup 里的弱符号，向量表在链接期指向本函数。
 */
__attribute__((naked, noreturn)) void HardFault_Handler(void)
{
	__asm volatile (
		"mov  r1, lr          \n"   /* EXC_RETURN：bit2=1 表示用的是 PSP */
		"movs r0, #4          \n"
		"tst  r0, r1          \n"
		"beq  1f              \n"
		"mrs  r0, psp         \n"
		"b    2f              \n"
		"1:                   \n"
		"mrs  r0, msp         \n"
		"2:                   \n"
		"b    Boot_FaultReport\n"
	);
}

/**
 * @brief 内存管理故障入口（未使能 MemManage 时不会触发，仍然留着兜底）
 */
__attribute__((naked, noreturn)) void MemManage_Handler(void)
{
	__asm volatile (
		"mov  r1, lr          \n"
		"movs r0, #4          \n"
		"tst  r0, r1          \n"
		"beq  1f              \n"
		"mrs  r0, psp         \n"
		"b    2f              \n"
		"1:                   \n"
		"mrs  r0, msp         \n"
		"2:                   \n"
		"b    Boot_FaultReport\n"
	);
}

/**
 * @brief 总线故障入口（未使能 BusFault 时不会触发，仍然留着兜底）
 */
__attribute__((naked, noreturn)) void BusFault_Handler(void)
{
	__asm volatile (
		"mov  r1, lr          \n"
		"movs r0, #4          \n"
		"tst  r0, r1          \n"
		"beq  1f              \n"
		"mrs  r0, psp         \n"
		"b    2f              \n"
		"1:                   \n"
		"mrs  r0, msp         \n"
		"2:                   \n"
		"b    Boot_FaultReport\n"
	);
}

/**
 * @brief 用法故障入口（除零、非对齐访问、非法指令…）
 */
__attribute__((naked, noreturn)) void UsageFault_Handler(void)
{
	__asm volatile (
		"mov  r1, lr          \n"
		"movs r0, #4          \n"
		"tst  r0, r1          \n"
		"beq  1f              \n"
		"mrs  r0, psp         \n"
		"b    2f              \n"
		"1:                   \n"
		"mrs  r0, msp         \n"
		"2:                   \n"
		"b    Boot_FaultReport\n"
	);
}
