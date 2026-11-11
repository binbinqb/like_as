/**
 * @file    std_timer.c
 * @brief   软件定时器（MCU 版）：AS 的逻辑 + 平台提供的时间源
 *
 * @details @section TIMER_WHY 为什么不直接抄 AS 的那个文件
 *          as-master 的 `system/timer/std_timer.c` 在 PC 上编译，
 *          时间源是 `timeGetTime()`（Windows）/ `gettimeofday()`（Linux），
 *          还带着 `StbM` / `CanTSyn` 的条件分支。整份拷过来在 MCU 上编译不过。
 *
 *          所以这里**只保留逻辑，把时间源摘出去**：
 *
 *          @code
 *          std_timer.c（本文件）      定时器的状态机与溢出处理
 *                  ↓ 调用
 *          Std_GetTime()              平台实现（StdTimerAc.c → Platform_NowMs）
 *          @endcode
 *
 *          这样 `infras` 不依赖任何平台头，换 MCU 只改 `StdTimerAc.c` 一行。
 *
 *          @section TIMER_OVERFLOW 溢出处理为什么不能省
 *          `std_time_t` 是 32 位微秒 → **71.6 分钟回绕一次**。
 *          直接用 `if (now >= deadline)` 判断超时，回绕那一下会得到一个
 *          巨大的负数（或 0xFFFFFFFF），表现为"定时器要么立刻超时、要么永不超时"。
 *
 *          AS 的做法是把状态分成 `NO_OVERFLOW` / `OVERFLOW` 两种：
 *          设置时如果 `curTime + timeout` 会越过 `STD_TIME_MAX`，就把
 *          剩余量存进 `timer->time` 并标记为 OVERFLOW，超时判断时走另一个分支。
 *          这段逻辑是这套定时器唯一不平凡的地方，**原样保留**。
 *
 * @note  本工程用不到 `Std_Sleep()` / `Std_GetDateTime()`（PC 上的调试辅助），
 *        故意不提供 —— 缺了它们一旦有人调用就链接失败，比提供空实现安全。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：从 as-master 摘出逻辑，时间源改由平台提供 |
 */

#include "Std_Timer.h"

#include "Std_Debug.h"

/* ============================ [ 内部常量 ] ============================ */

/**
 * @brief 定时器状态
 * @note  取值与 AS 原版一致。`STD_TIMER_STARTED` 只表示"正在计时"，
 *        与是否溢出无关 —— 溢出是**在设置时**就决定了的事。
 */
#define STD_TIMER_STARTED           (1u)
#define STD_TIMER_SET_NO_OVERFLOW   (2u)
#define STD_TIMER_SET_OVERFLOW      (3u)

/**
 * @brief 单次设置的最大超时（半个计数周期）
 * @note  超过这个值就无法区分"刚设置"和"已经绕了一圈"，
 *        所以 `Std_TimerSet()` 会断言拒绝。
 */
#define STD_TIMER_SET_MAX           (STD_TIME_MAX / 2u)

/* ============================ [ 接口实现 ] ============================ */

void Std_TimerStart(Std_TimerType *timer)
{
	if (timer == NULL) {
		return;
	}

	timer->status = (uint8_t)STD_TIMER_STARTED;
	timer->time   = Std_GetTime();
}

void Std_TimerStop(Std_TimerType *timer)
{
	if (timer == NULL) {
		return;
	}

	timer->status = 0u;
}

bool Std_IsTimerStarted(Std_TimerType *timer)
{
	if (timer == NULL) {
		return false;
	}

	return (timer->status != 0u) ? true : false;
}

/**
 * @brief 已运行时间（微秒）
 * @return 从 `Std_TimerStart()` 到现在的时间；未启动返回 0
 * @note  这里也做了回绕处理：`curTime < timer->time` 说明跨过了 0xFFFFFFFF。
 */
std_time_t Std_GetTimerElapsedTime(Std_TimerType *timer)
{
	std_time_t curTime;
	std_time_t elapsed = 0u;

	if ((timer == NULL) || (timer->status == 0u)) {
		return 0u;
	}

	curTime = Std_GetTime();
	if (curTime > timer->time) {
		elapsed = curTime - timer->time;
	} else {
		elapsed = (STD_TIME_MAX - timer->time) + 1u + curTime;
	}

	return elapsed;
}

/**
 * @brief 设置超时（从现在起算，或从上次到期点起算）
 * @param[in] timer   定时器
 * @param[in] timeout 超时（微秒）
 *
 * @note  语义要点：**如果定时器已在运行，新的到期点是"上次到期点 + timeout"**，
 *        而不是"现在 + timeout"。这样周期调用 `Std_TimerSet(t, cycle)` 不会
 *        因为调用抖动而累积漂移 —— CanNm 的周期发送就依赖这个语义。
 */
void Std_TimerSet(Std_TimerType *timer, std_time_t timeout)
{
	std_time_t curTime;

	if (timer == NULL) {
		return;
	}

	asAssert(timeout <= STD_TIMER_SET_MAX);

	if (0u == timer->status) {
		curTime = Std_GetTime();
	} else {
		curTime = timer->time;
	}

	if (timeout <= (STD_TIME_MAX - curTime)) {
		timer->time   = curTime + timeout;
		timer->status = (uint8_t)STD_TIMER_SET_NO_OVERFLOW;
	} else {
		timer->time   = timeout - 1u - (STD_TIME_MAX - curTime);
		timer->status = (uint8_t)STD_TIMER_SET_OVERFLOW;
	}
}

void Std_TimerInit(Std_TimerType *timer, std_time_t timeout)
{
	if (timer == NULL) {
		return;
	}

	Std_TimerStop(timer);
	Std_TimerSet(timer, timeout);
}

/**
 * @brief 是否已超时
 * @retval true  已到期（**不自动复位**，需要调用方自己 `Std_TimerSet` 重新装载）
 * @retval false 未到期，或定时器未启动
 *
 * @note  两个分支的判断依据：
 *        - `NO_OVERFLOW`：到期点在未来，`now >= time` 即到期；
 *        - `OVERFLOW`：到期点已经绕过一圈，`now >= time` 且距离不超过半个周期。
 *        另外 `NO_OVERFLOW` 分支里还有一条 `(time - now) > SET_MAX` ——
 *        那是"设置后过了太久、已经绕回"的兜底。
 */
bool Std_IsTimerTimeout(Std_TimerType *timer)
{
	bool r = false;
	std_time_t curTime;

	if (timer == NULL) {
		return false;
	}

	curTime = Std_GetTime();

	switch (timer->status) {
	case STD_TIMER_SET_NO_OVERFLOW:
		if (curTime >= timer->time) {
			r = true;
		} else if ((timer->time - curTime) > STD_TIMER_SET_MAX) {
			r = true;
		} else {
			/* not expired */
		}
		break;

	case STD_TIMER_SET_OVERFLOW:
		if (curTime >= timer->time) {
			if ((curTime - timer->time) <= STD_TIMER_SET_MAX) {
				r = true;
			}
		} else {
			/* not expired */
		}
		break;

	default:
		/* STD_TIMER_STARTED 或 0：都还没设定到期点，不算超时 */
		break;
	}

	return r;
}
