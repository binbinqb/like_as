/**
 * @file    perf_mon.h
 * @brief   调度与中断延迟的实测指标（A6）：只用内核自带的 DWT 周期计数器
 *
 * @details @section PERFMON_WHY 为什么要测"迟到量"而不是"中断响应时间"
 *
 *          教科书写法是"用 GPIO 翻转 + 示波器测中断响应"，那要求台面上
 *          有一台示波器和一根探针，而且测的是"那一次"的响应，不是最坏值。
 *
 *          这里换一个等价但可长期开着的指标：**SysTick 的迟到量**。
 *
 *          `SysTick_Config()` 把 SysTick 设成**最低优先级**（CMSIS 的固定
 *          行为），它每 1 ms 到期一次。到期到进入 `SysTick_Handler` 之间
 *          只要有任何高优先级中断在跑、或有代码在关中断，入口时刻就会往后挪。
 *          于是：
 *
 *          @code
 *            迟到量 = (本次入口 CYCCNT - 上次入口 CYCCNT) - 1 ms 的周期数
 *          @endcode
 *
 *          这个值就是"最坏情况下中断被推迟了多久"的直接度量，单位是周期数，
 *          除以主频即微秒。它覆盖了全部"关中断 / 高优先级 ISR 占用"的场景，
 *          不需要示波器，也不需要在每个临界区插桩。
 *
 * @note    @section PERFMON_LIMITS 这个指标的边界
 *          - 只能测出**比 SysTick 优先级高、或在 SysTick 之前触发**的延迟。
 *            如果某个 ISR 与 SysTick 同优先级且排在前面，也算在内；真正漏掉的是
 *            "更高优先级 ISR 在 SysTick 已进入之后又抢占" —— 那不是延迟，
 *            是嵌套，与本指标无关。
 *          - 主频必须是真实主频（PLL 120 MHz）。用错主频会把 µs 数算错一半/一倍，
 *            所以换算用的常量取自 `BOARD_CORE_CLOCK_HZ`（Board.json），不在这里另写一份。
 *          - 计数器 32 位、120 MHz 下 **35.8 s** 回卷。用无符号减法，回卷不影响差值。
 *
 * @author  binbina
 * @version V1.0.0
 */

#ifndef PERF_MON_H
#define PERF_MON_H

#include "Std_Types.h"

/**
 * @brief 初始化：开 DWT 周期计数器、清零统计
 *
 * @details 必须在第一次 `Platform_InitTick()` **之前**调用：SysTick 一开
 *          就会进中断，而中断里要读 CYCCNT。顺序反了第一拍会读到 0，
 *          算出一次巨大的"迟到量"（假阳性）。
 *
 * @note  DWT 属于调试组件，但 `TRCENA` + `CYCCNTENA` 打开后不依赖调试器
 *        连接，脱机运行照常计数。
 */
void PerfMon_Init(void);

/**
 * @brief 取当前周期计数（用于给一段代码计时）
 *
 * @return DWT 周期计数；`PerfMon_Init()` 之前恒为 0
 *
 * @note  直接相减即可，回卷安全（无符号）。不要在中断里做除法。
 */
uint32_t PerfMon_Cycles(void);

/**
 * @brief 把周期数换成微秒（四舍五入到整数）
 *
 * @param[in] cycles 周期数
 * @return 微秒数
 */
uint32_t PerfMon_CyclesToUs(uint32_t cycles);

/**
 * @brief SysTick 入口处调用（**中断上下文**，只做几次加读）
 *
 * @note  开销约 5 条指令（读 CYCCNT、两次比较、两次条件写）。
 *        120 MHz 下约 42 ns —— 相对于 1 ms 的节拍可以忽略，
 *        所以默认常开，不做编译开关：**关掉的测量等于没测**。
 */
void PerfMon_TickIsr(void);

/**
 * @brief 最坏迟到量（周期）
 */
uint32_t PerfMon_TickLateMaxCycles(void);

/**
 * @brief 最坏迟到量（微秒）
 */
uint32_t PerfMon_TickLateMaxUs(void);

/**
 * @brief 记录一次"单拍耗时"（主循环里 `EcuM_BswService()` 前后各取一次时间）
 *
 * @param[in] cycles 本拍耗时（周期）
 *
 * @note  这个数回答的是另一个问题：**主循环一拍要跑多久**。
 *        它必须显著小于 10 ms 的节拍周期，否则下一拍会被推迟 ——
 *        与"迟到量"配合看，才能区分"被别人打断"还是"自己太慢"。
 */
void PerfMon_RecordBswCycles(uint32_t cycles);

/**
 * @brief 最坏单拍耗时（周期 / 微秒）
 */
uint32_t PerfMon_BswMaxCycles(void);
uint32_t PerfMon_BswMaxUs(void);

/**
 * @brief 复位全部统计（清最大值，便于"从现在开始测"）
 */
void PerfMon_Reset(void);

/**
 * @brief 告诉统计器"节拍周期刚被改过 / 刚停过"，丢掉上一次的时间基准
 *
 * @details 必须在 `Platform_SetTickPeriodMs()` / `Platform_StopTick()` /
 *          `Platform_StartTick()` 里调用。理由是一个具体的假阳性：
 *          这些接口会改写 SysTick 的装载值，下一拍的间隔不再是 1 ms，
 *          而统计器仍按 1 ms 算差值 —— 于是一次 100 ms 的低功耗延时会被
 *          记成"迟到 99 ms"，而且**这个最大值会一直留在统计里**，
 *          之后所有读数都带着它。
 *
 * @note  只丢基准，不清最大值：调用方若想清最大值，自己再调 `PerfMon_Reset()`。
 */
void PerfMon_TickResync(void);

#endif /* PERF_MON_H */
