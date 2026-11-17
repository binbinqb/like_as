/**
 * @file    platform_host.c
 * @brief   Host 平台实现：虚拟时钟 + 标准输出控制台 + 外设空实现
 *
 * @details @section HOSTIMPL_SCOPE 实现范围
 *
 *          只实现业务代码真正会调到的那些：
 *
 *          | 接口 | 实现 | 理由 |
 *          |------|------|------|
 *          | `Platform_NowMs()` | 虚拟计数，由 `Host_AdvanceMs()` 推进 | 去抖/超时用例必须能"跳时间" |
 *          | `Platform_Puts/Printf` | stdio | 用例失败时能直接看到原因 |
 *          | `Platform_Flash*` | 全部返回 `E_OK` 并填 `0xFF` | 业务不碰 Flash；真测存储要接虚拟 NvM（V0.2） |
 *          | `Platform_CanRx*` | 恒 0 | 没有真实邮箱；CAN 计数只用于压测对账 |
 *          | `Platform_JumpToApp()` | 空 | Host 没有向量表 |
 *
 * @note  `Platform_InitTick()` 是空实现而不是"起线程"：Host 的时间**由测试
 *        显式推进**。起一个后台线程反而会让用例不可重复（同样的代码两次
 *        跑出不同结果，是 Host 测试最糟糕的失败模式）。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版 |
 */

#include "platform_host.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* ================================ [ LOCALS ] ================================ */

/** @brief 虚拟毫秒计数（唯一时间基准） */
static uint32_t s_ms = 0u;

/** @brief 控制台输出汇；NULL 表示直写 stdout */
static void (*s_sink)(char c) = NULL;

/* ============================== [ 时钟接口 ] ============================== */

void Host_AdvanceMs(uint32_t ms)
{
	s_ms += ms;
}

void Host_ResetClock(void)
{
	s_ms = 0u;
}

uint32_t Platform_NowMs(void)
{
	return s_ms;
}

void Platform_InitTick(void)
{
	/* 见文件头的说明：Host 的时间由测试推进，不起线程。 */
}

void Platform_StopTick(void)
{
	/* Host 没有节拍可停：`Host_AdvanceMs()` 不被调用就等于时间停了。 */
}

void Platform_StartTick(void)
{
}

void Platform_SetTickPeriodMs(uint32_t ms)
{
	(void)ms;   /* Host 的时间粒度恒为 1 ms，改周期没有意义 */
}

void Platform_EnterStopMode(void)
{
	/* 低功耗在 Host 上没有对应物。留空而不是 abort：功耗用例本来就要上板。 */
}

/* ============================== [ 控制台 ] ============================== */

/** @brief `Platform_Reset()` 被调用的次数（Host 上不真复位，只计数） */
static uint32_t s_resetCount;

uint32_t Host_GetResetCount(void)
{
	return s_resetCount;
}

void Platform_Reset(void)
{
	/* Host 上**不能真复位**：那等于 abort() 掉测试进程，"到底有没有请求
	 * 复位"这个最关键的断言就永远看不到结果。这里只计数，由用例断言。 */
	s_resetCount++;
}

void Platform_Init(void)
{
	s_ms = 0u;
	s_sink = NULL;
}

void Platform_PutChar(char c)
{
	(void)fputc((int)c, stdout);
}

void Platform_Puts(const char *s)
{
	if (NULL == s)
	{
		return;
	}

	if (NULL != s_sink)
	{
		while ('\0' != *s)
		{
			s_sink(*s);
			s++;
		}
	}
	else
	{
		(void)fputs(s, stdout);
	}
}

void Platform_SetConsoleSink(void (*fn)(char c))
{
	s_sink = fn;
}

int Platform_Printf(const char *fmt, ...)
{
	char buf[256];
	va_list ap;
	int n;

	if (NULL == fmt)
	{
		return 0;
	}

	va_start(ap, fmt);
	n = vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	if (n > 0)
	{
		/* 截断时也要把已有的部分打出来，否则用例失败时看到的是空行 */
		buf[sizeof(buf) - 1u] = '\0';
		Platform_Puts(buf);
	}

	return n;
}

int Platform_GetChar(void)
{
	return -1;   /* 无控制台输入：用例通过函数调用注入，不从 stdin 读 */
}

/* ============================ [ 唤醒 / 复位 ] ============================ */

uint8_t Platform_GetWakeupSource(void)
{
	return 0u;
}

const char *Platform_GetWakeupSourceName(uint8_t src)
{
	(void)src;
	return "host";
}

void Platform_ClearWakeupFlags(void)
{
}

void Platform_JumpToApp(uint32_t base)
{
	(void)base;
}

/* ============================== [ Flash ] ============================== */

Std_ReturnType Platform_FlashIsErased(uint32_t addr, uint32_t len)
{
	(void)addr;
	(void)len;
	return E_OK;
}

Std_ReturnType Platform_FlashEraseSector(uint32_t addr)
{
	(void)addr;
	return E_OK;
}

Std_ReturnType Platform_FlashWrite(uint32_t addr, const void *data, uint32_t len)
{
	(void)addr;
	(void)data;
	(void)len;
	return E_OK;   /* 真正需要存储语义时接虚拟 NvM，见 V0.2 计划 */
}

void Platform_FlashRead(uint32_t addr, void *buf, uint32_t len)
{
	(void)addr;

	if (NULL != buf)
	{
		(void)memset(buf, 0xFF, (size_t)len);
	}
}

/* ============================ [ CAN 计数 ] ============================ */

uint32_t Platform_CanRxTotal(uint8_t controller)
{
	(void)controller;
	return 0u;
}

uint32_t Platform_CanRxByMb(uint8_t controller, uint8_t mb)
{
	(void)controller;
	(void)mb;
	return 0u;
}

uint32_t Platform_CanIsrCount(uint8_t controller)
{
	(void)controller;
	return 0u;
}

void Platform_CanResetRxCounters(void)
{
}
