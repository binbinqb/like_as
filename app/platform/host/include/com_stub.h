/**
 * @file    com_stub.h
 * @brief   Host 侧的 Com 替身：只做"信号值的存取"，不做打包/超时/通知
 *
 * @details @section COMSTUB_WHY 为什么是替身而不是真 Com
 *
 *          真 `Com.c` 需要 IPdu 缓冲、MainFunction 节拍、PduR 路径，一路
 *          牵连到 CanIf 与驱动。Host V0.1 的目标是**验证业务语义**
 *          （raw→语义映射、四态判定、去抖窗口），不是验证 Com 的打包。
 *
 *          所以这里把 Com 收敛成一张"信号号 → 原始值"的表：
 *
 *          | 业务动作 | Host 上的实际行为 |
 *          |----------|-------------------|
 *          | `BcmSig_MainFunction()` 读 RX | 从本表取 `HostCom_SetRx()` 写入的值 |
 *          | `BcmSig_MainFunction()` 写 TX | 写进本表，`HostCom_GetTx()` 可查 |
 *
 *          @warning **本替身不模拟**：打包/解包、Intel/Motorola 位序、周期
 *          发送、超时、UpdateBit、InvalidValue。这些必须在目标板上验
 *          （M23/M14 已经覆盖了位序与打包）。它只保证"业务拿到的 raw 是
 *          测试指定的那个值"，从而让业务逻辑可以被单独判定。
 *
 *          @note 当前绑定的 12 个信号在 Com 配置里都是 `UINT8`（≤8 bit），
 *          因此替身按 **1 字节** 存取。将来绑 16/32 位信号时要在这里
 *          补长度表，否则高字节会被静默丢掉——那是假通过。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版 |
 */

#ifndef COM_STUB_H
#define COM_STUB_H

#include "Std_Types.h"
#include "Com.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 清空全部信号值（每个用例开头调用）
 */
void HostCom_Reset(void);

/**
 * @brief 设置业务将读到的原始值（模拟"总线上来了一帧"）
 *
 * @param[in] id  信号号（`COM_SID_xxx`）
 * @param[in] raw 原始值，按 1 字节存
 */
void HostCom_SetRx(Com_SignalIdType id, uint8_t raw);

/**
 * @brief 读回业务写出的原始值（验证"发出去的到底是什么"）
 *
 * @param[in] id 信号号
 * @return 最近一次 `Com_SendSignal()` 写入的值；从未写过返回 0
 */
uint8_t HostCom_GetTx(Com_SignalIdType id);

#ifdef __cplusplus
}
#endif

#endif /* COM_STUB_H */
