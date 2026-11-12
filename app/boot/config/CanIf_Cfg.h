/**
 * @file    CanIf_Cfg.h
 * @brief   boot 版 CAN Interface 配置：1 条诊断接收 + 1 条诊断响应
 *
 * @details @section BOOTCANIF_WHY 为什么 boot 不复用 app 的 CanIf_Cfg
 *
 *          app 的 `CANIF_RX_PDU_NUM = 57`（34 条 Foton 矩阵 + 私有报文 + J1939 段），
 *          `CANIF_TX_DIAG_RESP = 3`（前面还排着心跳/扩展帧/CAN1 心跳）。
 *          这些表是 `const` 数组，链接器不会按 PDU 裁剪 ——
 *          复用就等于把 56 条用不上的过滤项搬进 boot。
 *
 *          更关键的是 **PDU id 语义**：app 里 `CANIF_TX_DIAG_RESP` 是 3，
 *          `CanTp_Cfg.c` 里把它当 `CanIfTxPduId` 用。boot 只有一条 TX PDU，
 *          编号重新从 0 排，语义更清楚；`CanTp_Cfg.c` 原样复用不受影响
 *          （它只引用宏名，不关心数值）。
 *
 * @note    底层邮箱配置（`Can_Cfg.c` / `Can_HwCfg.h`）**复用 app 那份**，
 *          因为那是 M2/M19 验证过的硬件配置，改它没有收益、只有风险。
 *          所以这里的 `hoh` 必须与 `Can_Cfg.c` 里的邮箱号严格对应：
 *          0x7E0 → CAN0 邮箱 5；0x7E8 → HTH 3（CAN0 邮箱 4）。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-12 | binbina | 首版：boot 专用 1RX + 1TX |
 */

#ifndef CANIF_CFG_H
#define CANIF_CFG_H

/* ============================ [ 通道 ] ============================ */

/** @brief CAN0：唯一使用的控制器（诊断 0x7E0/0x7E8 挂在这里） */
#define CANIF_CHL_CAN0              (0u)

/** @brief 控制器总数（boot 只用 CAN0） */
#define CANIF_CTRL_NUM              (1u)

/* ============================ [ PDU 编号 ] ============================ */

/**
 * @brief 诊断请求 0x7E0 的 RX PDU 号
 * @note  CanIf 侧的唯一编号；上 PduR 时换成 `PDUR_CANIF_TO_CANTP_RX`，
 *        换算在 `CanIfCfg_DiagRxIndication()` 里做 ——
 *        与 app 版的做法一致（CanIf 的 PDU 号与 PduR pathId 是两套编号体系）。
 */
#define CANIF_RX_DIAG_REQ           (0u)

/** @brief 接收 PDU 总数 */
#define CANIF_RX_PDU_NUM            (1u)

/** @brief 诊断响应 0x7E8 的 TX PDU 号（`CanTp_Cfg.c` 引用它） */
#define CANIF_TX_DIAG_RESP          (0u)

/** @brief 发送 PDU 总数 */
#define CANIF_TX_PDU_NUM            (1u)

/* ============================ [ 收发缓冲 ] ============================ */

/**
 * @brief 报文池尺寸：0 = 同步收发（中断里直接回调，不入池）
 *
 * @note  boot 只有这样简单：Dcm 的响应是同步组包后交给 CanTp，
 *        不需要"中断入池、主循环分发"那种解耦。开池会多占 RAM
 *        且引入一层分发延迟，对刷写没有好处。
 */
#ifndef CANIF_RX_PACKET_POOL_SIZE
#define CANIF_RX_PACKET_POOL_SIZE   (0u)
#endif

#ifndef CANIF_TX_PACKET_POOL_SIZE
#define CANIF_TX_PACKET_POOL_SIZE   (0u)
#endif

#ifndef CANIF_RX_PACKET_DATA_SIZE
#define CANIF_RX_PACKET_DATA_SIZE   (8u)
#endif

#ifndef CANIF_TX_PACKET_DATA_SIZE
#define CANIF_TX_PACKET_DATA_SIZE   (8u)
#endif

#endif /* CANIF_CFG_H */
