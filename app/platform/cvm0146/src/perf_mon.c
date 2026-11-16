/**
 * @file    perf_mon.c
 * @brief   DWT 周期计数器驱动的调度/延迟统计（A6）
 *
 * @details 为什么用裸地址访问 DWT 而不是 `core_cm4.h`：
 *          SDK 的 `reg/` 目录里有一份自己的 `core_cm4.h`，与 CMSIS 官方版
 *          对 `SCB` / `SysTick` 的字段定义会打架（`platform_cvm0146.c:824`
 *          已经因为同样的原因改用裸地址访问 NVIC）。只用到三个寄存器，
 *          直接写地址比引一份可能冲突的头文件更可控。
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "perf_mon.h"
#include "Board_Cfg.h"          /* BOARD_CORE_CLOCK_HZ：主频不在这里另写一份 */

/* ============================ [ 寄存器 ] ============================ */

/** @brief 调试异常与监视控制寄存器（Cortex-M4，固定地址） */
#define PERFMON_DEMCR       (*(volatile uint32_t *)0xE000EDFCu)
/** @brief DWT 控制寄存器 */
#define PERFMON_DWT_CTRL    (*(volatile uint32_t *)0xE0001000u)
/** @brief DWT 周期计数器 */
#define PERFMON_DWT_CYCCNT  (*(volatile uint32_t *)0xE0001004u)

/** @brief DEMCR.TRCENA：调试组件总开关，不开则 DWT 不计数 */
#define PERFMON_TRCENA      (1uL << 24)
/** @brief DWT_CTRL.CYCCNTENA：周期计数器使能 */
#define PERFMON_CYCCNTENA   (1uL << 0)

/* ============================ [ 统计量 ] ============================ */

/** @brief SysTick 一个节拍应有的周期数（120 MHz / 1 kHz = 120000） */
#define PERFMON_TICK_CYCLES (BOARD_CORE_CLOCK_HZ / 1000u)

static volatile uint32_t s_lastTickCycles;   /**< 上次 SysTick 入口时刻 */
static volatile uint32_t s_tickLateMax;      /**< 最坏迟到（周期） */
static volatile uint8_t  s_tickPrimed;       /**< 是否已有"上次"可比 */
static volatile uint32_t s_bswMax;           /**< 最坏单拍耗时（周期） */

/* ============================ [ 接口实现 ] ============================ */

void PerfMon_Init(void)
{
	PERFMON_DEMCR |= PERFMON_TRCENA;
	PERFMON_DWT_CYCCNT = 0u;
	PERFMON_DWT_CTRL |= PERFMON_CYCCNTENA;

	PerfMon_Reset();
}

void PerfMon_Reset(void)
{
	s_lastTickCycles = 0u;
	s_tickLateMax = 0u;
	s_tickPrimed = 0u;
	s_bswMax = 0u;
}

uint32_t PerfMon_Cycles(void)
{
	return PERFMON_DWT_CYCCNT;
}

uint32_t PerfMon_CyclesToUs(uint32_t cycles)
{
	/* 先乘 1000 再除主频：120 MHz 下 cycles 最大约 4.29e9，
	 * 乘 1000 会溢出 32 位。所以先做除法拿到毫秒的上界再补余数 ——
	 * 分两步算，避免 64 位除法（M4 上要走软件库，几十个周期）。 */
	uint32_t ms = cycles / (BOARD_CORE_CLOCK_HZ / 1000u);
	uint32_t rem = cycles % (BOARD_CORE_CLOCK_HZ / 1000u);

	return (ms * 1000u) + ((rem * 1000u) / (BOARD_CORE_CLOCK_HZ / 1000u));
}

void PerfMon_TickIsr(void)
{
	uint32_t now = PERFMON_DWT_CYCCNT;
	uint32_t delta;
	uint32_t late;

	if (0u != s_tickPrimed)
	{
		/* 无符号减法：CYCCNT 35.8 s 回卷时差值依然正确 */
		delta = now - s_lastTickCycles;
		if (delta > PERFMON_TICK_CYCLES)
		{
			late = delta - PERFMON_TICK_CYCLES;
			if (late > s_tickLateMax)
			{
				s_tickLateMax = late;
			}
		}
	}

	s_lastTickCycles = now;
	s_tickPrimed = 1u;
}

void PerfMon_TickResync(void)
{
	s_tickPrimed = 0u;
}

uint32_t PerfMon_TickLateMaxCycles(void)
{
	return s_tickLateMax;
}

uint32_t PerfMon_TickLateMaxUs(void)
{
	return PerfMon_CyclesToUs(s_tickLateMax);
}

void PerfMon_RecordBswCycles(uint32_t cycles)
{
	if (cycles > s_bswMax)
	{
		s_bswMax = cycles;
	}
}

uint32_t PerfMon_BswMaxCycles(void)
{
	return s_bswMax;
}

uint32_t PerfMon_BswMaxUs(void)
{
	return PerfMon_CyclesToUs(s_bswMax);
}
