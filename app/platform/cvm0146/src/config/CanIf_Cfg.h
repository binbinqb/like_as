/**
 * @file    CanIf_Cfg.h
 * @brief   CAN Interface 的 PDU 编号与编译期开关
 *
 * @details @section CANIFCFG_ROLE 这个文件的角色
 *          它提供三类东西，缺一不可：
 *
 *          | 类别 | 内容 | 谁用 |
 *          |------|------|------|
 *          | **PDU 编号** | `CANIF_RX_*` / `CANIF_TX_*` | 应用调 `CanIf_Transmit()`、`CanIf_Cfg.c` 填表 |
 *          | **编译期开关** | PDU 模式、包池大小 | `CanIf.c` 的 `#if` |
 *          | **周期** | `CANIF_MAIN_FUNCTION_PERIOD` | 主循环调用 `CanIf_MainFunction()` 的节奏 |
 *
 *          @section CANIFCFG_ID 编号为什么从 0 连续
 *          AS 的实现把 `CanIf_Transmit(TxPduId)` 的 `TxPduId` **直接当数组下标**用
 *          （`CANIF_CONFIG->txPdus[TxPduId]`），所以编号必须是 `0..N-1` 连续，
 *          中间不能留空。RX 侧同理：`rxPduId` 会原样传给 `rxInd` 回调，
 *          M3 接 PduR 后它就是 PduR 的 `pathId`，也必须连续。
 *
 *          @section CANIFCFG_POOL 包池为什么是 0
 *          `CANIF_RX_PACKET_POOL_SIZE > 0` 会让收发变成"中断入池、主循环分发"，
 *          代价是多一层队列和 `mempool` 的 RAM 占用。
 *          BCM 的报文都是短帧、周期稳定，且当前 `CanAc_RxIsr` 是同步分发，
 *          所以先用 0；将来若中断里出现耗时（比如 Com 信号打包很重）再打开。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：2 收 2 发，含一条 29 位扩展帧 |
 */

#ifndef CANIF_CFG_H
#define CANIF_CFG_H

/* ============================ [ 通道 ] ============================ */

/** @brief 逻辑通道号（与 `Can_Cfg.h` 的 `CAN_CHL_CAN0/CAN1` 一致） */
#define CANIF_CHL_CAN0              (0u)
#define CANIF_CHL_CAN1              (1u)

/* ============================ [ RX PDU 编号 ] ============================ */
/*
 * 必须与 `CanIf_Cfg.c` 的 `CanIf_RxPdus_*[]` 顺序一致，且**全局**从 0 连续
 * （`rxPduId` 会原样传给应用，M3 接 PduR 后就是 PduR 的 `pathId`）。
 */

/** @brief CAN0：0x321 标准帧（M1 就有，用于回归） */
#define CANIF_RX_TEST               (0u)

/** @brief CAN0：0x18FF0001 扩展帧（M2 新增，验证 J1939） */
#define CANIF_RX_EXT_TEST          (1u)

/** @brief CAN1：0x322 标准帧 */
#define CANIF_RX_CAN1_TEST         (2u)

/**
 * @brief CAN1：0x18FF0100 的 **J1939 PGN 匹配**（掩码 0x1FFFFF00，忽略源地址）
 * @note  用来验证"一条过滤项匹配一组报文"。Foton 的 49 条 J1939 报文里，
 *        同一 PGN 不同源地址的情况很常见，靠它避免一条一条列。
 */
#define CANIF_RX_CAN1_PGN          (3u)

/**
 * @brief CAN0：诊断请求 0x7E0（M3）
 * @note  这个编号是 **CanIf 自己的编号**，不是 PduR 的 pathId。两者不同域：
 *        `rxPduId` 只交给本表的 `rxInd` 回调看，而 PduR 的 pathId 由
 *        `PduR_Cfg.h` 独立定义。换算是 `CanIf_Cfg.c` 里一个 3 行 shim ——
 *        显式写出来，比"让两套编号碰巧相等"可靠。
 */
#define CANIF_RX_DIAG_REQ           (4u)

/**
 * @brief CAN0：J1939 同 PGN 多源地址（掩码 0x1FFFFF00）
 * @note  M8 新增。这条 PDU 代表"一条过滤项匹配一组报文"的能力 ——
 *        Foton 的 49 条报文里，同一 PGN 不同源地址很常见。
 */
#define CANIF_RX_J1939_PGN          (5u)

/** @brief CAN0：四个不同 PGN 的 J1939 报文（M8，验证多邮箱并行） */
#define CANIF_RX_J1939_A            (6u)
#define CANIF_RX_J1939_B            (7u)
#define CANIF_RX_J1939_C            (8u)
#define CANIF_RX_J1939_D            (9u)

/**
 * @brief CAN0：网络管理报文 0x500（M9）
 * @note  它与其它 RX PDU 有一处本质区别：**它不交给应用，而交给 CanNm**。
 *        其余 PDU 的 `rxInd` 是 `App_CanIfRxIndication`（打串口），
 *        这一条是 `CanIfCfg_NmRxIndication`（转 PduR → CanNm）。
 *        验 NM 时如果看到 0x500 的报文被当成普通报文打印出来，
 *        说明这里配错了对象。
 */
#define CANIF_RX_NM                 (10u)

/**
 * @brief CAN0：Com 信号测试报文 0x200（M10）
 * @note  与 NM 那条同理：它交给 Com，不是交给应用。
 */
#define CANIF_RX_COM_TEST           (11u)

/* ============================ [ M14：通信矩阵压测（20 条） ] ============================ */
/*
 * 编号从 12 起**追加**，不动 0~11。理由：`main.c` 与各验收脚本是按编号
 * 做断言的（"发 0x321 → pdu=0"），重排编号会让所有历史回归静默失效。
 *
 * 命名规则：`CANIF_RX_<域>_<用途>`。域为 `STD`（标准帧）或 `J1939`。
 */

/** @brief 标准帧快变段 0x0A0~0x0A7（10 ms，压中断） */
#define CANIF_RX_STD_FAST           (12u)

/** @brief 标准帧灯光控制段 0x100~0x107 */
#define CANIF_RX_STD_LIGHT          (13u)

/** @brief 标准帧车身状态 0x110 */
#define CANIF_RX_STD_BODY           (14u)

/** @brief J1939 PGN 0xFF00 车辆状态（复用 0x18FF0001 精确项，见 CanIf_Cfg.c） */
#define CANIF_RX_J1939_VEH          (15u)

/** @brief J1939 PGN 0xFF02 门锁状态 */
#define CANIF_RX_J1939_DOOR         (16u)

/** @brief J1939 PGN 0xFF03 雨刮状态 */
#define CANIF_RX_J1939_WIPER        (17u)

/** @brief J1939 PGN 0xFF04 **同一 PGN 多源地址**（验证掩码分组） */
#define CANIF_RX_J1939_MULTI        (18u)

/** @brief J1939 PGN 0xFF05 报警 */
#define CANIF_RX_J1939_ALARM        (19u)

/** @brief J1939 PGN 0xFF06 高频扩展帧（20 ms，压扩展帧中断） */
#define CANIF_RX_J1939_FAST         (20u)

/** @brief J1939 PGN 0xFEE0 里程（1000 ms，慢变） */
#define CANIF_RX_J1939_ODO          (21u)

/** @brief J1939 ID 极值 0x1FFFFF00（验二分查找的右边界） */
#define CANIF_RX_J1939_MAXID        (22u)

/** @brief RX PDU 总数（配表时用于自检） */
#define CANIF_RX_PDU_NUM            (23u)

/* ============================ [ TX PDU 编号 ] ============================ */
/*
 * `CanIf_Transmit(TxPduId)` 直接拿它当 `txPdus[]` 下标，所以必须 0..N-1 连续。
 */

/** @brief CAN0：0x123 心跳帧 */
#define CANIF_TX_HEARTBEAT          (0u)

/** @brief CAN0：0x18FF0002 扩展帧 */
#define CANIF_TX_EXT_TEST          (1u)

/** @brief CAN1：0x124 心跳帧 */
#define CANIF_TX_CAN1_TEST         (2u)

/** @brief CAN0：诊断响应 0x7E8（M3） */
#define CANIF_TX_DIAG_RESP         (3u)

/**
 * @brief CAN0：网络管理报文 0x500（M9）
 * @note  这条 PDU 只被 `CanNm` 用（`nmSendMessage()` 直接调 `CanIf_Transmit`），
 *        应用**不应**自己发它 —— 手工发会让 NM 状态机与实际总线不同步。
 */
#define CANIF_TX_NM                (4u)

/**
 * @brief CAN0：Com 信号测试报文 0x200（M10）
 * @note  这条只被 Com 用（`Com_MainFunctionTx` → `PduR_ComTransmit` →
 *        `CanIf_Transmit`）。应用改的是**信号**，不是这条 PDU ——
 *        直接发 PDU 会绕过 Com 的周期与打包，等于把分层拆掉。
 */
#define CANIF_TX_COM_TEST          (5u)

/** @brief TX PDU 总数 */
#define CANIF_TX_PDU_NUM            (6u)

/* ============================ [ 周期 ] ============================ */

/**
 * @brief `CanIf_MainFunction()` 的调用周期（ms）
 * @note  当前只用它算 TxTimeout 的 tick 数；没开 `CANIF_USE_TX_TIMEOUT` 时不影响运行。
 */
#define CANIF_MAIN_FUNCTION_PERIOD  (10u)

#define CANIF_CONVERT_MS_TO_MAIN_CYCLES(x)                                                         \
	(((x) + CANIF_MAIN_FUNCTION_PERIOD - 1u) / CANIF_MAIN_FUNCTION_PERIOD)

/* ============================ [ 编译期开关 ] ============================ */

/* 以下三项**不定义**即为关闭（与 AS 的生成器保持一致：注释掉就是关闭）：
 *   CANIF_USE_PB_CONFIG     —— Post-Build 配置，RAM 里放指针，支持运行期换表
 *   CANIF_USE_TX_CALLOUT    —— 发送前回调，可用于 E2E 保护
 *   CANIF_USE_TX_TIMEOUT    —— 发送超时监控，依赖 CanSM
 */
/* #define CANIF_USE_PB_CONFIG */

/* ============================ [ 包池 ] ============================ */

#ifndef CANIF_RX_PACKET_POOL_SIZE
#define CANIF_RX_PACKET_POOL_SIZE   (0u)
#endif

#ifndef CANIF_TX_PACKET_POOL_SIZE
#define CANIF_TX_PACKET_POOL_SIZE   (0u)
#endif

/**
 * @brief 单个包的净荷上限（字节）
 * @note  `CanIf.c` 的 `CanIf_RxPacketType` **无条件**使用这个宏（不受池大小保护），
 *        所以即使池为 0 也必须定义，否则编译报未定义标识符。
 */
#ifndef CANIF_RX_PACKET_DATA_SIZE
#define CANIF_RX_PACKET_DATA_SIZE   (8u)
#endif

#ifndef CANIF_TX_PACKET_DATA_SIZE
#define CANIF_TX_PACKET_DATA_SIZE   (8u)
#endif

/* ============================ [ 配置自检 ] ============================ */

/**
 * @brief 检查接收过滤表是否满足二分查找的前置条件（升序 + 掩码项在末尾）
 * @retval true  合法
 * @retval false 有乱序
 * @note  由 `main.c` 的 `CanTest_Init()` 调用，失败只打串口不阻断启动 ——
 *        报文收不到已经够烦了，不该连诊断都进不去。
 */
bool CanIfCfg_CheckRxOrder(void);

#endif /* CANIF_CFG_H */
