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

#ifdef __cplusplus
extern "C" {
#endif

/* ── 生命周期与周期任务 ───────────────────────────────────── */

/** @brief 初始化测试发送缓冲与邮箱计数基线 */
void CanTest_Init(void);

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
