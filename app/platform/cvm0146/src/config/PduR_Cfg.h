/**
 * @file    PduR_Cfg.h
 * @brief   PDU Router 的路由路径编号
 *
 * @details @section PDURCFG_TOPO 一条 ISO-TP 诊断链路要过 4 条路径
 *          这是最容易搞错的地方：**TP 型报文要过两次 PduR**。
 *          @code
 *          N-PDU（单帧 CAN 报文）          SDU（重组后的整条诊断请求）
 *          0x7E0 → CanIf → PduR → CanTp  →  PduR → Dcm
 *                    path2                path0
 *          @endcode
 *
 *          | pathId | 方向 | Src | Dest | 用到的回调 |
 *          |--------|------|-----|------|------------|
 *          | 0 | SDU 上行 | CanTp | Dcm   | `TpRxIndication` / `StartOfReception` / `CopyRxData` |
 *          | 1 | SDU 下行 | Dcm   | CanTp | `Transmit` / `CopyTxData` / `TxConfirmation` |
 *          | 2 | N-PDU 上行 | CanIf | CanTp | `RxIndication` |
 *          | 3 | N-PDU 发送确认 | CanTp | CanIf | `TxConfirmation` |
 *
 *          @section PDURCFG_WHY 为什么 path0 必须是 0
 *          **PduR 的 RX pathId 在 Dcm 那侧被当成"通道号"用**：
 *          `Dcm_StartOfReception(id,...)` 里有 `DET_VALIDATE(id < config->numOfChls)`。
 *          当前只有 1 个诊断通道，所以 SDU 上行路径必须是 0。
 *          其余三条编号只在本文件内自洽，不影响别处。
 *
 *          @section PDURCFG_CONFIRM 为什么 path3 的 Src 是 CanTp
 *          `PduR_TxConfirmation(pathId)` 把结果交给 **`SrcPduRef->api->TxConfirmation`**
 *          —— 确认永远是"往上游走"。CanIf 的 N-PDU 发送确认要回到 CanTp，
 *          所以这条路径的 Src 必须是 CanTp、Dest 才是 CanIf。
 *          写成"Src=CanIf, Dest=CanTp"会得到一个空指针调用（静默失败）。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：2 条路径（错误的单跳拓扑） |
 * | V1.1.0 | 2026-11-10 | binbina | 改为 4 条路径：N-PDU 与 SDU 各一对 |
 */

#ifndef PDUR_CFG_H
#define PDUR_CFG_H

/* ============================ [ 路由路径 ] ============================ */

/**
 * @brief SDU 上行：CanTp（重组完）→ Dcm
 * @warning 必须是 0：Dcm 拿 RX pathId 当通道索引用
 */
#define PDUR_CANTP_TO_DCM_RX    (0u)

/** @brief SDU 下行：Dcm → CanTp（开始分段发送） */
#define PDUR_DCM_TO_CANTP_TX    (1u)

/** @brief N-PDU 上行：CanIf（收到一帧 0x7E0）→ CanTp */
#define PDUR_CANIF_TO_CANTP_RX  (2u)

/** @brief N-PDU 发送确认：CanTp ← CanIf（0x7E8 那帧发出去了） */
#define PDUR_CANTP_TX_CONFIRM   (3u)

/**
 * @brief N-PDU 上行：CanIf（收到一帧 0x500）→ CanNm（M9）
 *
 * @note  这是唯一一条"目的地是 BSW 协议模块而不是 Dcm"的路径。
 *        它没有对应的 TP 分层 —— NM 报文固定 8 字节，不需要重组，
 *        所以 **一帧直接到 CanNm**，中间只过 PduR 这一层。
 *
 * @warning 这条路径的 `DestPduRef->PduHandleId` 必须是 **0**，
 *          不是 CanIf 的 PDU 号。因为 `CanNm_RxIndication(RxPduId, ...)`
 *          把第一个参数当**通道下标**用（`CanNm.c:851`：
 *          `context = &CANNM_CONFIG->ChannelContexts[RxPduId]`），
 *          传 10 就是越界读。这是 PduR 与 CanNm 的一个语义错配，
 *          AS 靠"配置里填 0"化解，我们照做。
 */
#define PDUR_CANIF_TO_CANNM_RX  (4u)

/**
 * @brief N-PDU 发送确认：CanNm ← CanIf（0x500 那帧发出去了，M9）
 *
 * @note  同样是反向的"确认往上游走"：Src = CanNm，Dest = CanIf。
 *        与 `PDUR_CANTP_TX_CONFIRM` 的拓扑完全一致。
 *
 * @warning 同样要求 `SrcPduRef->PduHandleId = 0`：
 *          `PduR_TxConfirmation()` 会把 `SrcPduRef->PduHandleId` 传下去，
 *          而 `CanNm_TxConfirmation(TxPduId, ...)` 也拿它当通道下标。
 */
#define PDUR_CANNM_TX_CONFIRM   (5u)

/**
 * @brief 信号上行：CanIf → Com（M10）
 *
 * @note  Dest 侧填 **Com 的 PDU 号**（`COM_CANTEST_RX_TEST`），
 *        因为 `Com_RxIndication(RxPduId)` 拿它当 `IPduConfigs[]` 下标
 *        （`Com.c:605`：`&COM_CONFIG->IPduConfigs[RxPduId]`）。
 */
#define PDUR_CANIF_TO_COM_RX    (6u)

/**
 * @brief 信号发送确认：Com ← CanIf（M10）
 *
 * @note  确认往上游走，Src 必须是 Com，`SrcPduRef->PduHandleId`
 *        要填 **Com 的 PDU 号**，因为 `Com_TxConfirmation(TxPduId)`
 *        也拿它当 `IPduConfigs[]` 下标。
 */
#define PDUR_COM_TX_CONFIRM     (7u)

/**
 * @brief 手写路径数：诊断 4 + NM 2 + 测试 2
 * @note  改这里的同时必须改 `PduR_Cfg.c` 里的 `PduR_SrcPdu[]` / `PduR_DstPdu[]` /
 *        `PduR_RoutingPaths[]` 三张表 —— 它们是**全量初始化**，
 *        少一条是编译错（`-Wmissing-field-initializers` 不报，但其余条目会
 *        整体前移一位），所以宁可让它显式写在一起。
 *
 *        原第 6 条 `PDUR_COM_TO_CANIF_TX` 已删除（2026-11-18）：它的
 *        `PduHandleId` 与生成段 `PDUR_CANTEST_TX_TEST` 指向同一个 Com PDU，
 *        但全工程 0 处引用 —— `Com_Cfg.c` 用的是生成段那条。删后
 *        手工段 9→8，`Can.json` 的 `pdurIdBase` 同步 9→8，否则
 *        `PduR_SrcPdu[]` 第 8 项会留洞（索引不连续）。
 */
#define PDUR_MANUAL_PATHS       (8u)

/* @generated BEGIN: CAN1 real matrix */
/*
 * CAN1 报文路由（由 tools/sync_pdur.py 从 dbc/can1.dbc 生成，勿手改）
 *
 * 每条报文一条路径：RX 是 CanIf→Com，TX 是 Com→CanIf。
 * 路径号从 8u 起 —— 0~7u 归诊断/NM/测试（见文件前半部分）。
 */
/** @brief 0x18FE4021 BCM_LCSF（发送） */
#define PDUR_CAN1_BCM_LCSF_TX              (8u)
/** @brief 0x18FF0C21 BCM_Ctrl（发送） */
#define PDUR_CAN1_BCM_CTRL_TX              (9u)
/** @brief 0x0CFDCC21 BCM_OEL（发送） */
#define PDUR_CAN1_BCM_OEL_TX               (10u)
/** @brief 0x18FDCD21 BCM_OWW（发送） */
#define PDUR_CAN1_BCM_OWW_TX               (11u)
/** @brief 0x18FE4E21 BCM_DoorCtrl（发送） */
#define PDUR_CAN1_BCM_DOOR_CTRL_TX         (12u)
/** @brief 0x18FECA21 BCM_DM1（发送） */
#define PDUR_CAN1_BCM_DM1_TX               (13u)
/** @brief 0x14F02B54 Crash_Notification（接收，来自 NODE_54） */
#define PDUR_CAN1_CRASH_NOTIFICATION_RX    (14u)
/** @brief 0x18FEF500 AMB_Ambient_Conditions（接收，来自 NODE_00） */
#define PDUR_CAN1_AMB_AMBIENT_CONDITIONS_RX (15u)
/** @brief 0x18FF0534 PEPS1（接收，来自 NODE_34） */
#define PDUR_CAN1_PEPS1_RX                 (16u)
/** @brief 0x18FF7534 PEPS2（接收，来自 NODE_34） */
#define PDUR_CAN1_PEPS2_RX                 (17u)
/** @brief 0x10FFB634 PEPS_ESCLM（接收，来自 NODE_34） */
#define PDUR_CAN1_PEPS_ESCLM_RX            (18u)
/** @brief 0x18EEFF00 ACL（接收，来自 NODE_00） */
#define PDUR_CAN1_ACL_RX                   (19u)
/** @brief 0x0CFD9200 EOI（接收，来自 NODE_00） */
#define PDUR_CAN1_EOI_RX                   (20u)
/** @brief 0x18F00503 ETC2（接收，来自 NODE_03） */
#define PDUR_CAN1_ETC2_RX                  (21u)
/** @brief 0x10FFB04D ESCL1（接收，来自 NODE_4D） */
#define PDUR_CAN1_ESCL1_RX                 (22u)
/** @brief 0x10FFB24D ESCLM_PEPS（接收，来自 NODE_4D） */
#define PDUR_CAN1_ESCLM_PEPS_RX            (23u)
/** @brief 0x18FF904D ESCL_NM（接收，来自 NODE_4D） */
#define PDUR_CAN1_ESCL_NM_RX               (24u)
/** @brief 0x18FF0CEC DW_State（接收，来自 NODE_EC） */
#define PDUR_CAN1_DW_STATE_RX              (25u)
/** @brief 0x18FF0917 IC_MSG（接收，来自 NODE_17） */
#define PDUR_CAN1_IC_MSG_RX                (26u)
/** @brief 0x0CF00400 EEC1_Electronic_Engine_Controller_1（接收，来自 NODE_00） */
#define PDUR_CAN1_EEC1_ELECTRONIC_ENGINE_CONTROLLER_1_RX (27u)
/** @brief 0x18FEF121 CCVS（接收，来自 NODE_21） */
#define PDUR_CAN1_CCVS_RX                  (28u)
/** @brief 0x18FF12EF VCU_4（接收，来自 NODE_EF） */
#define PDUR_CAN1_VCU_4_RX                 (29u)
/** @brief 0x0CFE6CEE TCO1（接收，来自 NODE_EE） */
#define PDUR_CAN1_TCO1_RX                  (30u)
/** @brief 0x18FEF433 TireCondition（接收，来自 NODE_33） */
#define PDUR_CAN1_TIRE_CONDITION_RX        (31u)
/** @brief 0x18FECA33 DM1_TPMS（接收，来自 NODE_33） */
#define PDUR_CAN1_DM1_TPMS_RX              (32u)
/** @brief 0x18F0010B EBC1_Electronic_Brake_Controller_1（接收，来自 NODE_0B） */
#define PDUR_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX (33u)
/** @brief 0x18FDC40B EBC5_Electronic_Brake_Controller_5（接收，来自 NODE_0B） */
#define PDUR_CAN1_EBC5_ELECTRONIC_BRAKE_CONTROLLER_5_RX (34u)
/** @brief 0x18FD0700 DLCC1_Direct_Lamp_Control_Command_1（接收，来自 NODE_00） */
#define PDUR_CAN1_DLCC1_DIRECT_LAMP_CONTROL_COMMAND_1_RX (35u)
/** @brief 0x18FEF100 CCVS1_Cruise_Control_Vehicle_Speed_1（接收，来自 NODE_00） */
#define PDUR_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX (36u)
/** @brief 0x18FE4F0B VDC1_Vehicle_Dynamic_Stability_Control_1（接收，来自 NODE_0B） */
#define PDUR_CAN1_VDC1_VEHICLE_DYNAMIC_STABILITY_CONTROL_1_RX (37u)
/** @brief 0x18F0000F ERC1（接收，来自 NODE_0F） */
#define PDUR_CAN1_ERC1_RX                  (38u)
/** @brief 0x18F00000 ERC3（接收，来自 NODE_00） */
#define PDUR_CAN1_ERC3_RX                  (39u)
/** @brief 0x1CFEC321 ETC5（接收，来自 NODE_21） */
#define PDUR_CAN1_ETC5_RX                  (40u)
/** @brief 0x18FFBA19 EEC3（接收，来自 NODE_19） */
#define PDUR_CAN1_EEC3_RX                  (41u)
/** @brief 0x18FFBC19 ECC2（接收，来自 NODE_19） */
#define PDUR_CAN1_ECC2_RX                  (42u)
/** @brief 0x18FF4C56 ID1（接收，来自 NODE_56） */
#define PDUR_CAN1_ID1_RX                   (43u)
/** @brief 0x18FF4D56 ID2（接收，来自 NODE_56） */
#define PDUR_CAN1_ID2_RX                   (44u)
/** @brief 0x18FF4E56 ID3（接收，来自 NODE_56） */
#define PDUR_CAN1_ID3_RX                   (45u)
/** @brief 0x1CECFF21 TP_CM（接收，来自 NODE_21） */
#define PDUR_CAN1_TP_CM_RX                 (46u)
/** @brief 0x1CEBFF21 TP_DT（接收，来自 NODE_21） */
#define PDUR_CAN1_TP_DT_RX                 (47u)
/** @brief 0x200 信号测试帧（M10） */
#define PDUR_CANTEST_TX_TEST               (48u)
/** @brief 0x201 信号测试帧（M10） */
#define PDUR_CANTEST_RX_TEST               (49u)

/**
 * @brief 生成段路径数（供 PDUR_NUM_ROUTING_PATHS 相加）
 * @note  = DBC 40 条 + `PduR.json` 的 `manualPaths` 2 条。
 *        这个加法必须写在产物里：数字本身不解释来源，下次矩阵升版
 *        按 DBC 条数算总数就会少算 2 条（`check-pdu` 只会报索引错位，
 *        不会告诉你少的是手工路径）。
 */
#define PDUR_CAN1_PATHS         (42u)
/* @generated END: CAN1 real matrix */

/** @brief 路径总数（= `RoutingPaths[]` 长度） */
#define PDUR_NUM_ROUTING_PATHS  (PDUR_MANUAL_PATHS + PDUR_CAN1_PATHS)

#endif /* PDUR_CFG_H */
