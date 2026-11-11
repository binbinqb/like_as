/**
 * @file    EcuM_Cfg.h
 * @brief   EcuM 的周期宏 + 本工程提供的初始化入口声明
 *
 * @details @section ECUMCFG_WHY 为什么这份配置在应用层
 *
 *          AUTOSAR 的 `EcuM_ConfigType` 是一张"这个 ECU 按什么顺序初始化"
 *          的表。表里要引用 `Storage_InitStack()` 这类**应用函数**，
 *          所以配置必须和应用同层 —— 放 `infras` 会让 BSW 反过来依赖应用。
 *
 *          `infras/system/EcuM/` 只保留标准状态机（`EcuM.c`）；
 *          所有 `EcuM_AL_*` 集成代码在 `ecum_callout.c`。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：10 ms 主函数，Wakeup 保持 2 s |
 */

#ifndef ECUM_CFG_H
#define ECUM_CFG_H

#include "EcuM.h"

/* ============================ [ 时基 ] ============================ */

/**
 * @brief `EcuM_MainFunction()` 的调用间隔（ms）
 * @warning 必须与 `main.c` 的 `BSW_PERIOD_MS` 一致。
 *
 * @note  EcuM 的定时器只有 `Twakeup` 一个（睡眠→唤醒后保持多久），
 *        它按"主函数拍数"递减（`EcuM.c:96`）。所以
 *        `TMinWakup` 必须用 `ECUM_CONVERT_MS_TO_MAIN_CYCLES()` 换算。
 */
#ifndef ECUM_MAIN_FUNCTION_PERIOD
#define ECUM_MAIN_FUNCTION_PERIOD   (10u)
#endif

#define ECUM_CONVERT_MS_TO_MAIN_CYCLES(x)                                                          \
	(((x) + ECUM_MAIN_FUNCTION_PERIOD - 1u) / ECUM_MAIN_FUNCTION_PERIOD)

/**
 * @brief 唤醒后至少保持多久才允许再次睡眠（ms）
 * @note  真实项目里这个值由"收发器唤醒后总线需要多长时间稳定"决定，
 *        以及"唤醒事件要不要等应用确认"（`EcuM_ValidateWakeupEvent`）。
 *        本工程没有收发器唤醒中断，这个值只在 `!u` 释放 RUN 之后
 *        的睡眠循环里起作用。
 */
#define ECUM_MIN_WAKEUP_TIME        (2000u)

/* ============================ [ 本工程提供的初始化入口 ] ============================ */

/**
 * @brief 存储栈初始化（阶段一）：`NvM_Init` + 等待空闲
 * @note  实现在 `main.c`。`NvM_Init` 内部会完成 `FeeAc_Init()` 与
 *        `Fee_Configure()`（见 `NvM_PortInit`），所以 EcuM 的 Zero 阶段
 *        不需要单独列 Fee 的初始化。
 *
 * @warning 必须放在 **DriverInitOne**：`EcuM_StartupTwo()` 之前的任何
 *          NvM 访问都要求 NvM 已初始化，否则 `NvM_GetStatus()` 返回
 *          `MEMIF_UNINIT`，上层若拿它跟 `MEMIF_IDLE` 比就会死等。
 */
void Storage_InitStack(void);

/**
 * @brief 存储栈初始化（阶段二）：`NvM_ReadAll` + 启动计数 + Dem 绑定
 * @note  实现在 `main.c`。放在 **DriverInitTwo**（`EcuM_StartupTwo`
 *        之后），语义上对应 AUTOSAR 的"OS 启动后读回非易失数据"。
 */
void Storage_InitData(void);

/**
 * @brief 读集成层当前所处的 EcuM 模式
 * @return `ECUM_MODE_OFF` / `STARTUP` / `RUN` / `POST_RUN` / `SHUTDOWN` / `SLEEP`
 * @note  存在的理由见 `ecum_callout.c`：as-master 的 `EcuM.c` 没有实现
 *        标准接口 `EcuM_GetCurrentMode()`。
 */
EcuM_ModeType EcuM_AL_GetMode(void);

/* ============================ [ 唤醒源（项目自定义） ] ============================ */

/**
 * @brief 本项目新增的唤醒源：CAN0 总线活动（bit8）
 * @note  定义与使用都在 `ecum_callout.c` / `main.c` 这一层，
 *        不改 AS 的 `EcuM.h`（那里只有 POWER / RESET / WDG 这类通用源）。
 */
#define ECUM_WKSOURCE_CAN0      ((EcuM_WakeupSourceType)0x0100u)

#endif /* ECUM_CFG_H */
