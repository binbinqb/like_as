/**
 * @file    stack_mon.c
 * @brief   栈水位实测的实现（A6）：0xA5 填充 + 从栈底上扫
 *
 * @details 两个链接脚本符号是唯一的栈边界来源：
 *          - `__StackLimit`：栈区最低地址（`.stack` 段的起点）
 *          - `__StackTop`  ：栈区最高地址（复位后 SP 的初值）
 *
 *          两者都在 `CVM0146_app_a.ld` 里定义，长度 = `STACK_SIZE`（默认 2 KB）。
 *          本文件不重复写 2 KB 这个数 —— 改链接脚本时这里自动跟着变。
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "stack_mon.h"

#include "Std_Critical.h"   /* EnterCritical / ExitCritical */

/* ============================ [ 链接脚本符号 ] ============================ */

extern uint32_t __StackLimit;   /**< 栈底（低地址） */
extern uint32_t __StackTop;     /**< 栈顶（高地址，SP 初值） */

/* ============================ [ 常量 ] ============================ */

/**
 * @brief 填充图案
 * @note  选 0xA5 而不是 0x00：全局区清零后本来就有大量 0x00，
 *        用 0 做图案无法区分"没被写过"和"被写过又写成 0"。
 *        0xA5 在正常 C 代码里极少连续出现，误判概率低。
 */
#define STACKMON_PATTERN    (0xA5u)

/**
 * @brief 填充时在"当前 SP"下方保留的字节数
 *
 * @details 填充是从栈底到 `sp - STACKMON_RESERVE` 这一段。留出这一截的
 *          理由：`StackMon_Init` 自己的帧、`main` 的帧都在 SP 之上，
 *          而编译器可能已经为将要调用的函数预留了 spill 区。
 *          96 字节足够覆盖，代价是水位读数至少会比真实值小 96 字节 ——
 *          偏保守（读数偏小 = 报警偏晚），所以下面 `UsedBytes` 里补回来。
 */
#define STACKMON_RESERVE    (96u)

/* ============================ [ 内部 ] ============================ */

/**
 * @brief 读当前 SP
 * @note  用 `mov` 直接取，不依赖编译器内置函数的名字差异（GCC/ARMCC 不同）。
 */
static uint32_t currentSp(void)
{
	uint32_t sp;

	__asm volatile("mov %0, sp" : "=r"(sp));

	return sp;
}

/* ============================ [ 接口实现 ] ============================ */

void StackMon_Init(void)
{
	volatile uint8_t *base = (volatile uint8_t *)&__StackLimit;
	uint32_t top = currentSp();
	uint32_t stop;
	uint32_t i;

	if (top <= (uint32_t)base)
	{
		return;   /* 链接脚本符号异常，宁可不填也不越界写 */
	}

	/* 从栈底填到"当前 SP - 保留量"，绝不越过当前 SP */
	stop = top - STACKMON_RESERVE;
	if (stop > (uint32_t)base)
	{
		EnterCritical();
		for (i = 0u; (uint32_t)base + i < stop; i++)
		{
			base[i] = (uint8_t)STACKMON_PATTERN;
		}
		ExitCritical();
	}
}

uint32_t StackMon_UsedBytes(void)
{
	const volatile uint8_t *base = (const volatile uint8_t *)&__StackLimit;
	uint32_t total = StackMon_TotalBytes();
	uint32_t i;

	/* 从栈底往上找第一个不再是图案的字节 —— 那就是历史最深位置 */
	for (i = 0u; i < total; i++)
	{
		if (base[i] != (uint8_t)STACKMON_PATTERN)
		{
			/* 被改过的那一字节就是最深点；已用 = 栈顶 - 该地址。
			 * 加回保留量：`StackMon_Init` 没填的那 96 字节也是真用掉的。 */
			return total - i + STACKMON_RESERVE;
		}
	}

	return 0u;
}

uint32_t StackMon_TotalBytes(void)
{
	return (uint32_t)&__StackTop - (uint32_t)&__StackLimit;
}
