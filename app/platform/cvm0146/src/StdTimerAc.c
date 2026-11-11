/**
 * @file    StdTimerAc.c
 * @brief   软件定时器的时间源（平台访问层）
 *
 * @details @section TIMERAC_WHY 为什么只有这一个函数
 *          `infras/system/timer/std_timer.c` 是**与平台无关**的定时器逻辑，
 *          它唯一的外部依赖就是 `Std_GetTime()` —— "从上电到现在过了多少微秒"。
 *
 *          这个函数必须由平台提供，因为只有平台知道时基从哪来：
 *          PC 上是 `gettimeofday()`，本工程是 SysTick（`Platform_NowMs()`）。
 *
 *          把这一行单独放一个文件，是为了让"换 MCU"这件事的影响面
 *          限制在 `app/platform/<chip>/` 里 —— 和 `CanAc.c` / `FeeAc.c` 一个道理。
 *
 *          @section TIMERAC_PRECISION 精度说明
 *          `Platform_NowMs()` 是 **1 ms** 计数，乘 1000 得到微秒，
 *          所以精度是 1 ms 而不是 1 us。为什么够用：
 *
 *          | 使用者 | 最短定时 | 1 ms 误差的影响 |
 *          |--------|----------|-----------------|
 *          | CanNm 的 NM 周期发送 | 数十 ms | 可忽略 |
 *          | NM 超时 / 等待睡眠 | 数百 ms ~ 数秒 | 可忽略 |
 *
 *          真要微秒级精度（比如位时序测量）不能用这里的软定时器，
 *          应该直接读 DWT->CYCCNT 或定时器捕获寄存器。
 *
 * @warning `Platform_NowMs() * 1000u` 在 **71.6 分钟**处溢出 32 位——
 *          这不是 bug，`std_timer.c` 的 `OVERFLOW` 分支处理的正是这件事。
 *          不要在调用侧再补一遍判断，两边都判反而会出错。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：SysTick 毫秒计数转微秒 |
 */

#include "Std_Timer.h"

#include "platform_cvm0146.h"

std_time_t Std_GetTime(void)
{
	/* 1 ms 计数 → 微秒。溢出由 std_timer.c 的 OVERFLOW 分支负责，
	 * 这里刻意不做任何饱和/裁剪。 */
	return (std_time_t)Platform_NowMs() * 1000u;
}
