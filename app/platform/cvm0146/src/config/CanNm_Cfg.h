/**
 * @file    CanNm_Cfg.h
 * @brief   CAN 网络管理（CanNm）的编译期开关与时基换算
 *
 * @details @section CANNMCFG_PERIOD 主函数周期决定了所有时间的单位
 *
 *          `CANNM_MAIN_FUNCTION_PERIOD` 是 **`CanNm_MainFunction()` 的调用间隔（毫秒）**，
 *          必须是 10 —— 与 `main.c` 里 BSW 任务的 `BSW_PERIOD_MS` 一致。
 *
 *          但配置表里的时间字段**不是毫秒，是"主函数周期数"**。这层换算由
 *          `CANNM_CONVERT_MS_TO_MAIN_CYCLES()` 完成，和 as-master 的代码生成器
 *          （`tools/generator/CanNm.py:95`）逐字一致。
 *
 *          @code
 *          MsgCycleTime = 200 ms
 *            → CANNM_CONVERT_MS_TO_MAIN_CYCLES(200)
 *            → (200 + 10 - 1) / 10 = 20 个周期
 *            → nmSetAlarm() 换算成 20 × 10 ms = 200 ms 的真实定时器
 *          @endcode
 *
 *          **为什么这层容易出错**：`nmSetAlarm()` 的公式是
 *          `v * 1000u * CANNM_MAIN_FUNCTION_PERIOD` 微秒。如果误把毫秒值直接填进
 *          配置表（比如填 200 而不是 20），实得周期是 **2 秒**，比预期慢 10 倍 ——
 *          而现象是"NM 报文发得太稀"，不会报任何错。
 *
 *          @section CANNMCFG_FEATURES 开/关的功能
 *
 *          | 开关 | 状态 | 理由 |
 *          |------|------|------|
 *          | `CANNM_USE_STD_TIMER` | **开** | M8 已移植 `Std_Timer`（含 32 位微秒回绕处理）。用它而不是 `uint16_t` 计数，好处是**不依赖主函数被准时调用** —— 主循环被 FEE 擦除卡住 5 ms 时，周期不会累积漂移 |
 *          | `CANNM_REQUEST_BIT_AUTO_SET` | **开** | 本地有请求时自动置 CBV 的"重复报文请求位"。别的节点看到这一位会进 RepeatMessage，是真实 NM 行为；关掉它 CBV 永远是 0，看不出对不对 |
 *          | `CANNM_REMOTE_SLEEP_IND_ENABLED` | 关 | 需要额外的 `RemoteSleepIndTime` 定时器和"远端睡眠检测"语义，本工程单节点场景验不出来 |
 *          | `CANNM_COORDINATOR_SYNC_SUPPORT` | 关 | 需要 NM 协调者角色。BCM 不是协调者 |
 *          | `CANNM_GLOBAL_PN_SUPPORT` | 关 | 部分网络（PN）需要 `PnFilterMask` 和 Com 配合，等 Com 上来再开 |
 *          | `CANNM_CAR_WAKEUP_SUPPORT` | 关 | 依赖 `CanIf` 传 `MetaDataPtr`（含硬件邮箱信息），当前 `CanIf` 传的是 NULL |
 *          | `CANNM_COM_USER_DATA_SUPPORT` | 关 | 需要 Com 提供用户数据。**关掉同时也去掉了对 `PduR_CanNmTxConfirmation` 的依赖** |
 *
 * @warning 关掉一个开关不等于"少一个功能"，而是**结构体字段也会变少**
 *          （`CanNm_ChannelConfigType` 里那些字段都在 `#ifdef` 内）。
 *          所以 `CanNm_Cfg.c` 的初始化**必须用指定初始化器**，
 *          位置初始化会在开关变化时静默错位。见那个文件的说明。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：单通道 CanNm，200 ms 周期，10 ms 主函数 |
 */

#ifndef CANNM_CFG_H
#define CANNM_CFG_H

/* ============================ [ 时基 ] ============================ */

/**
 * @brief `CanNm_MainFunction()` 的调用间隔（ms）
 * @warning 必须与 `main.c` 的 `BSW_PERIOD_MS` 一致。
 *          改这里不改那里，所有 NM 定时都会按比例偏 —— 且不报错。
 */
#ifndef CANNM_MAIN_FUNCTION_PERIOD
#define CANNM_MAIN_FUNCTION_PERIOD  (10u)
#endif

/**
 * @brief 毫秒 → 主函数周期数
 * @param[in] x 毫秒
 * @note  向上取整，避免 `MsgCycleOffset=0` 这类小值被算成 0 周期。
 */
#define CANNM_CONVERT_MS_TO_MAIN_CYCLES(x)                                                         \
	(((x) + CANNM_MAIN_FUNCTION_PERIOD - 1u) / CANNM_MAIN_FUNCTION_PERIOD)

/* ============================ [ 功能开关 ] ============================ */

/**
 * @brief 用 `Std_Timer` 做 NM 定时（而不是内部 `uint16_t` 计数）
 * @note  见文件头 `@section CANNMCFG_FEATURES`。
 */
#define CANNM_USE_STD_TIMER

/**
 * @brief 本地有请求时自动置 CBV 的"重复报文请求位"（bit0）
 * @note  ISO 11898 之外，这一位由 AUTOSAR NM 定义。置上之后，
 *        总线上其它节点会进入 `RepeatMessage`，属于正常的 NM 扩散行为。
 */
#define CANNM_REQUEST_BIT_AUTO_SET

/* 以下功能本工程不开，理由见文件头表格。刻意保留注释形式，
 * 让下一个接手的人知道"这里曾经考虑过"，而不是以为漏配了。 */
/* #define CANNM_REMOTE_SLEEP_IND_ENABLED */
/* #define CANNM_COORDINATOR_SYNC_SUPPORT */
/* #define CANNM_GLOBAL_PN_SUPPORT */
/* #define CANNM_CAR_WAKEUP_SUPPORT */
/* #define CANNM_PASSIVE_STARTUP_REPEAT_ENABLED */
/* #define CANNM_COM_USER_DATA_SUPPORT */

#endif /* CANNM_CFG_H */
