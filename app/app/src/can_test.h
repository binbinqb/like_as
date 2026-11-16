/**
 * @file    can_test.h
 * @brief   CAN 周期发送 / 接收统计 / 总线故障（M2/M5/M14/M19）对外接口
 *
 * @details 实现在 `can_test.c`。主循环按周期调用 `CanTest_SendOne/SendCan1/
 *          SendExt/DrainRx` 与 `Fault_PollBusOff`；命令层（`cmd/can_cmd.c`
 *          与 `cmd/can_cmd.c`、`cmd/dtc_cmd.c`）调用具体函数。
 *
 * @note    头文件只依赖 `Std_Types.h` 的基础类型；实现文件才 include 各模块。
 *
 * @author  binbina
 * @version V1.0.0
 */

#ifndef CAN_TEST_H
#define CAN_TEST_H

#include <stdint.h>
#include "Std_Types.h"   /* boolean / TRUE / FALSE */

#ifdef __cplusplus
extern "C" {
#endif

/* ── 生命周期与周期任务 ───────────────────────────────────── */

/** @brief 初始化测试发送缓冲与邮箱计数基线 */
void CanTest_Init(void);

/**
 * @brief 开关"主循环自动周期发送"
 *
 * @param[in] on `TRUE` = 允许主循环按周期发 0x123 / 0x124 / 扩展帧；
 *               `FALSE` = 停发（默认）
 *
 * @note  **默认 `FALSE`**，这是 A3「测试隔离」的核心决定。
 *
 *        原因：`0x123`（CAN0 心跳）与 `0x124`（CAN1）是**驱动层自测帧**，
 *        不属于整车通信矩阵。它们留在量产固件里会带来三个真实问题：
 *        1. 两条非矩阵报文常年占用总线（0x123 每 500 ms、0x124 每 500 ms），
 *           整车网络管理/网关侧会报"未知报文"
 *        2. `0x124` 与 CAN1 上已接入 Com 的 6 条真实报文同通道，
 *           排查总线问题时多一条噪音源
 *        3. `CanIf_Transmit()` 失败时它会往串口打一行
 *           `[can] CanIf_Transmit(heartbeat) failed`，量产件上属于噪声日志
 *
 *        为什么不做成编译开关：做成编译开关就需要两个构建变体
 *        （量产 / 回归），而 M1/M2/M10/M11/M8 五项回归都依赖这些帧，
 *        每次跑回归都要重编一遍。运行时开关的代价只是脚本开头多一行。
 *
 * @warning 这个开关**只**控制主循环的自动周期发送。`CanTest_Burst()`、
 *          `CanTest_SendRealMatrix()` 等命令触发的发送不受影响 ——
 *          命令本来就是人工主动发起的，不存在"悄悄占据总线"的风险。
 */
void CanTest_SetAutoTx(boolean on);

/**
 * @brief 查询"主循环自动周期发送"当前是否打开
 *
 * @retval TRUE  打开（回归测试期间）
 * @retval FALSE 关闭（上电默认，量产状态）
 */
boolean CanTest_IsAutoTx(void);

/** @brief 发一帧 CAN0 标准帧（0x123，8 字节递增） */
void CanTest_SendOne(void);

/** @brief 发一帧 CAN1 标准帧（0x124，首字节递增） */
void CanTest_SendCan1(void);

/** @brief 发一帧扩展帧（0x18FFxxxx） */
void CanTest_SendExt(void);

/** @brief 排空接收队列并打印（主循环调用） */
void CanTest_DrainRx(void);

/** @brief bus-off 轮询检测（主循环调用） */
void Fault_PollBusOff(void);

/* ── 命令用 ───────────────────────────────────────────────── */

/** @brief 打印按邮箱/按 PDU 的接收计数 */
void CanTest_DumpRxCounters(void);

/** @brief 清零接收计数（邮箱 + PDU） */
void CanTest_ClearCounters(void);

/** @brief 高频突发发送（制造位错误用） */
void CanTest_Burst(uint16_t n);

/** @brief CAN1 真实矩阵发送（M19，6 条报文） */
void CanTest_SendRealMatrix(void);

/** @brief 打印故障快照表 */
void Fault_Dump(void);

/** @brief 清除 DTC（与 UDS 0x14 同一条后端） */
void Fault_ClearDtc(void);

/** @brief 注入一条 bus-off 记录（单节点造不出真 bus-off 时用） */
void Fault_InjectBusOff(void);

/** @brief 发送完成累计数（心跳打印用） */
uint32_t CanTest_GetTxOk(void);

#ifdef __cplusplus
}
#endif

#endif /* CAN_TEST_H */
