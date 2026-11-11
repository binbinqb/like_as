/**
 * @file    Can_HwCfg.h
 * @brief   CAN 硬件资源表（邮箱表 + 硬件发送对象表）的契约
 *
 * @details @section HWCFG_WHY 为什么单独一个头，而不是塞进 Can_Cfg.h
 *          `Can_Cfg.h` 会被 `infras/mcal/Can/Can.c` 直接包含，它的内容属于 **BSW 可见**，
 *          一旦出现邮箱/句柄这类硬件概念，MCAL 就被绑死在这颗芯片上。
 *          而邮箱表本质上是"这块板子的硬件资源分配"，只有 `CanAc.c`（AC 层）该看见。
 *
 *          所以拆成两个文件：
 *
 *          | 文件 | 内容 | 谁能看见 |
 *          |------|------|----------|
 *          | `Can_Cfg.h`   | 通道数、波特率、采样点 | BSW + 平台 |
 *          | `Can_HwCfg.h` | 邮箱表、HTH 表、报文 ID | **只有平台**（`CanAc.c` + `Can_Cfg.c`） |
 *
 *          @section HWCFG_NEUTRAL 为什么类型里没有 `FlexCanDrv_*`
 *          本文件被 `Can_Cfg.c` 包含，而 `Can_Cfg.c` 是用 **Can 库的编译参数**编的
 *          （`-Iinfras/include -Iinfras/mcal/Can -Isrc/config`，**没有 SDK 路径**）。
 *          写成厂商类型会直接编译失败 —— 这不是巧合，是构建脚本"配置源编进模块库"的必然结果。
 *
 *          因此这里用中性类型（`uint32_t` / `bool` / 自有枚举），
 *          由 `CanAc.c` 在初始化时翻译成 `FlexCanDrv_MsgCfgType`。
 *          代价是多一层翻译，收益是**配置表可以整体由 DBC 生成器替换**，且不碰 SDK。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：邮箱表从 CanAc.c 迁出，为 DBC 生成做准备 |
 */

#ifndef CAN_HWCFG_H
#define CAN_HWCFG_H

#include <stdint.h>
#include <stdbool.h>

#include "Can_Cfg.h"

/* ============================ [ 报文 ID ] ============================ */

/**
 * @brief M1 心跳帧：板子周期发送，Kvaser 观察数据递增
 * @note  M2 接 CanIf 后，这条报文仍保留，用来证明"MCAL 通道没被 CanIf 搞坏"
 */
#define CAN_HW_ID_HEARTBEAT     (0x123u)

/** @brief M1 接收帧：Kvaser 发送，板子回显 */
#define CAN_HW_ID_TESTRX        (0x321u)

/** @brief M2 新增：29-bit 扩展帧验证（J1939 格式，PGN=0xFF00） */
#define CAN_HW_ID_EXT_RX        (0x18FF0001u)

/** @brief M2 新增：29-bit 扩展帧发送 */
#define CAN_HW_ID_EXT_TX        (0x18FF0002u)

/* ---- M8：多扩展帧邮箱压力验证（模拟 Foton 49 条 J1939 报文的场景）---- */

/**
 * @brief 组 A：同一 PGN（0xFF01）、不同源地址 —— 验证**一条掩码收一组**
 * @note  J1939 的 29 位 ID = 优先级(3) + PGN(18) + 源地址(8)。
 *        `0x18FF01xx` 里 `0x18` 是优先级+PGN 高位，`0xFF01` 是 PGN，`xx` 是源地址。
 *        掩码 `0x1FFFFF00` 忽略最低 8 位，所以任意源地址都能进同一个邮箱。
 */
#define CAN_HW_ID_J1939_PGN     (0x18FF0100u)

/** @brief 组 B：四个**不同 PGN** 的报文 —— 验证多个独立邮箱并行工作 */
#define CAN_HW_ID_J1939_A       (0x18FEF100u)   /**< PGN 0xFEF1 */
#define CAN_HW_ID_J1939_B       (0x18FEC100u)   /**< PGN 0xFEC1 */
#define CAN_HW_ID_J1939_C       (0x18FEB100u)   /**< PGN 0xFEB1 */
#define CAN_HW_ID_J1939_D       (0x18FEA100u)   /**< PGN 0xFEA1 */

/**
 * @brief J1939 的 PGN 掩码：保留高 21 位，忽略最低 8 位（源地址）
 * @note  0x1FFFFFFF 是全掩码（ID 必须完全一致）；0x1FFFFF00 才允许源地址变化。
 */
#define CAN_HW_MASK_J1939_PGN   (0x1FFFFF00u)

/* ---- M9：CAN 网络管理（CanNm）---- */

/**
 * @brief NM 报文 ID：0x500，标准帧，8 字节
 *
 * @details @section CANHWCFG_NMID 为什么是 0x500
 *
 *          AUTOSAR 没有规定 NM 的 CAN ID，它由**整车网络设计**给定。
 *          常见分配是 0x400 / 0x500 / 0x600 段，避开车身信号区（0x000~0x3FF）
 *          和诊断区（0x7E0~0x7EF）。
 *
 *          本工程取 0x500 只是"一个不冲突的占位值"。接 Foton 项目时
 *          必须换成通信矩阵里给的 NM 报文 ID —— 猜错的现象是
 *          **板子自己发得挺欢，但整车网络里没人理它**（因为大家都在别的 ID 上）。
 *
 * @note TX 和 RX 用同一个 ID：NM 是"一方发送、多方接收"的广播语义，
 *       标准做法就是所有节点在同一个 ID 上收发。
 *       本机发出的帧不会被自己的接收邮箱收到（FlexCAN 的 `MCR.SRXDIS` 默认禁用自收），
 *       所以这条不会自激。
 */
#define CAN_HW_ID_NM            (0x500u)

/* ---- M10：Com 信号层测试报文 ---- */

/**
 * @brief 信号发送报文：0x200（本节点 → 总线，100 ms）
 * @note  接收用 **0x201**，不是同一个 ID。
 *
 *        最初为了"一路 Kvaser 同时看收发"把两者写成同一个 ID，
 *        结果是**没法做接收测试**：板子每 100 ms 也在发 0x200，
 *        Kvaser 一注入就撞车 —— 同 ID 同优先级，仲裁必然让一方
 *        反复重发，错误计数一路涨，抓到的帧内容也会互相污染。
 *
 *        拆开之后 TX/RX 互不干扰，也才符合真实总线（一个 ID 只有一个发送者）。
 */
#define CAN_HW_ID_COM_TX        (0x200u)

/** @brief 信号接收报文：0x201（总线 → 本节点） */
#define CAN_HW_ID_COM_RX        (0x201u)

/* ---- CAN1（通信 2）：与 CAN0 用不同 ID，Kvaser 上一眼能分清是哪一路 ---- */

/** @brief CAN1 发送：0x124（CAN0 是 0x123） */
#define CAN_HW_ID_CAN1_TX       (0x124u)

/** @brief CAN1 接收：0x322（CAN0 是 0x321） */
#define CAN_HW_ID_CAN1_RX       (0x322u)

/* ---- M3 诊断（ISO 15765-2 物理寻址）---- */

/** @brief 诊断请求（测试仪 → ECU）：0x7E0 */
#define CAN_HW_ID_DIAG_REQ      (0x7E0u)

/** @brief 诊断响应（ECU → 测试仪）：0x7E8 */
#define CAN_HW_ID_DIAG_RESP     (0x7E8u)

/* ============================ [ 类型 ] ============================ */

/**
 * @brief 邮箱方向
 * @note  取值刻意与 `FlexCanDrv_MsgType_t` 一致（TX=0, RX=1），翻译时可直接强转；
 *        这样写是为了让 `CanAc.c` 的翻译代码不用 switch。改 SDK 枚举顺序时这里要跟着改。
 */
typedef enum {
	CAN_HW_MB_TX = 0,   /**< 发送邮箱 */
	CAN_HW_MB_RX = 1    /**< 接收邮箱 */
} CanHw_MbDirType;

/**
 * @brief 单个邮箱的配置（中性类型，不含任何厂商类型）
 * @note  字段顺序与 `FlexCanDrv_MsgCfgType` 一一对应，但不是同一个类型 ——
 *        翻译在 `CanAc_TranslateMsgCfgs()` 里一次完成，运行期不再转换。
 */
typedef struct {
	uint16_t       msgBufId;        /**< 邮箱号（0 起） */
	uint16_t       msgBufLen;       /**< 邮箱深度，1=单帧；>1 表示同一邮箱收多帧 */
	uint32_t       msgId;           /**< 帧 ID（11 位或 29 位，由 isExt 决定） */
	bool           isExt;           /**< true=29 位扩展帧 */
	CanHw_MbDirType dir;            /**< 发送 / 接收 */
	uint8_t        dlc;             /**< 数据长度 0..8（经典 CAN） */
	bool           intEnable;       /**< RX 是否使能邮箱中断；TX 恒为 false */
	uint32_t       individualMask;  /**< RX 独立掩码；0xFFFFFFFF = ID 必须完全一致 */
} CanHw_MsgCfgType;

/**
 * @brief 硬件发送对象（HTH）：`Can_Write()` 的 `Hth` 即本表下标
 *
 * @warning **一个 HTH 只能发一个固定 ID**。厂商 `FlexCanDrv_SetTxMsg()` 只写数据区，
 *          不回写 ID 与 DLC（见 `flexcan_drv.c:1494`），所以 ID 在 `CfgMsgObj` 时就定死了。
 *          要发 N 条不同 ID 的报文，就得有 N 个 HTH + N 个邮箱。
 *          这条约束在 96 个邮箱的容量下不构成问题（BCM 的 TX 报文远少于 96）。
 */
typedef struct {
	uint8_t  controller;    /**< 0=CAN0, 1=CAN1 */
	uint16_t msgBufId;      /**< 该 HTH 占用的邮箱号 */
	uint32_t canId;         /**< 该邮箱的固定 ID（`Can_Write` 校验用） */
	uint8_t  dlc;           /**< 该邮箱固定 DLC（`Can_Write` 补齐用） */
} CanHw_HohType;

/** @brief 一个通道的邮箱表 */
typedef struct {
	const CanHw_MsgCfgType *cfgs;   /**< 邮箱配置数组 */
	uint8_t                 num;    /**< 数组长度 */
} CanHw_MsgTableType;

/* ============================ [ HTH 编号 ] ============================ */
/*
 * CanIf_Cfg.c 的 `hoh` 字段直接引用这些宏 —— 两处硬编码变成一个宏，
 * 邮箱表改号时不会出现"CanIf 指向了别的邮箱"这类静默错误。
 */

/** @brief HTH 0：CAN0 心跳帧 0x123 */
#define CAN_HW_HTH_CAN0_HEARTBEAT   (0u)

/** @brief HTH 1：CAN0 扩展帧 0x18FF0002 */
#define CAN_HW_HTH_CAN0_EXT_TX      (1u)

/** @brief HTH 2：CAN1 心跳帧 0x124 */
#define CAN_HW_HTH_CAN1_HEARTBEAT   (2u)

/** @brief HTH 3：CAN0 诊断响应 0x7E8（M3） */
#define CAN_HW_HTH_DIAG_RESP        (3u)

/**
 * @brief HTH 4：CAN0 网络管理报文 0x500（M9）
 * @note  NM 报文是周期发送的，`CanNm` 每 200 ms 调一次 `CanIf_Transmit()`。
 *        固定 ID 的约定见上面 `@warning` —— `SetTxMsg()` 只写数据区，
 *        所以 0x500 必须在 `CfgMsgObj()` 时就绑死在这个邮箱上。
 */
#define CAN_HW_HTH_NM               (4u)

/**
 * @brief HTH 5：CAN0 信号报文 0x200（M10）
 * @note  Com 每 100 ms 发一次。同样受"一个 HTH 只能发一个固定 ID"的约束。
 */
#define CAN_HW_HTH_COM              (5u)

/** @brief HTH 表长度 */
#define CAN_HW_HOH_NUM              (6u)

/* ============================ [ 表 ] ============================ */

/** @brief 每个通道的邮箱表，下标 = 通道号 */
extern const CanHw_MsgTableType CanHw_MsgTables[CAN_CFG_NUM_CHANNELS];

/** @brief HTH 表，下标 = `Can_Write()` 的 `Hth` */
extern const CanHw_HohType CanHw_Hohs[CAN_HW_HOH_NUM];

#endif /* CAN_HWCFG_H */
