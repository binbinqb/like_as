/**
 * @file    platform_host.h
 * @brief   Host（PC）平台实现：虚拟时钟 + 控制台 + 空外设
 *
 * @details @section HOST_WHY 这个平台存在的理由
 *
 *          目标不是"在 PC 上跑整个 BSW"，而是**给业务代码一个可判定的运行环境**：
 *
 *          | 能力 | CVM0146 | Host |
 *          |------|---------|------|
 *          | 业务源码 | 同一份 | 同一份 |
 *          | 时间 | SysTick 1 ms，只能等 | 虚拟时钟，可一次跳 3 s |
 *          | CAN | 真实收发 | `com_stub.c` 注入/读回 |
 *          | Flash / 看门狗 / 低功耗 | 真实硬件 | 空实现 |
 *
 *          所以 Host 能回答"去抖窗口到了没有""超时后状态对不对""值有没有被
 *          正确翻译"，不能回答"时序抖不抖""Flash 擦多久"——后者必须上板。
 *
 * @warning 这是**单线程**模型：`Std_EnterCritical()` 是空操作。任何依赖
 *          "中断会被挡住"的推理在 Host 上不成立，不要拿 Host 结果证明
 *          并发安全。并发只能靠静态审查 + 上板压力测试。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版：虚拟时钟、控制台、外设空实现 |
 */

#ifndef PLATFORM_HOST_H
#define PLATFORM_HOST_H

#include <stdint.h>

#include "Std_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 把虚拟时钟向前推 @p ms 毫秒
 *
 * @param[in] ms 推进量
 *
 * @note 只是加计数，**不执行任何周期任务**。调用者负责在推进前后
 *       自己调用 `BcmSig_MainFunction()` 等，否则测的是"时间过去了，
 *       但没人跑"——这是 Host 用例最常见的假通过。
 */
void Host_AdvanceMs(uint32_t ms);

/**
 * @brief 把虚拟时钟清零（每个用例开头调用，保证互不影响）
 */
void Host_ResetClock(void);

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_HOST_H */
