/**
 * @file    StdTimerAc.c
 * @brief   Host 时间源：把 `Std_GetTime()` 接到虚拟毫秒时钟
 *
 * @details 与 `app/platform/cvm0146/src/StdTimerAc.c` 一一对应，只是时间源
 *          从 SysTick 换成 `Platform_NowMs()`（Host 上由测试推进）。
 *
 *          保留 `* 1000u` 的写法：`std_timer.c` 的溢出分支是按"微秒计数会
 *          回绕"设计的，Host 上如果改成纳秒精度反而绕过了那条分支，测的
 *          就不是目标代码的行为。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版 |
 */

#include "Std_Timer.h"

#include "platform.h"

std_time_t Std_GetTime(void)
{
	return (std_time_t)Platform_NowMs() * 1000u;
}
