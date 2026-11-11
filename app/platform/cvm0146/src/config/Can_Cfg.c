/**
 * @file    Can_Cfg.c
 * @brief   CAN 通道配置表（波特率 / STB 引脚 / 硬件实例映射）
 *
 * @details 字段顺序按 `Can_Priv.h` 的 `Can_ChannelConfigType` 在
 *          **定义了 `USE_PORT`** 时的布局：
 *          `{ context, baudrate, TrcvPinSTB, samplePoint, hwInstanceId, NormalValueOfTrcvPinSTB }`
 *
 *          @section CANCFG_USE_PORT 为什么走 USE_PORT 分支
 *          定义了 `USE_PORT` 后，AS 的 Can 驱动用 `Dio_WriteChannel()` 控制收发器 STB，
 *          而不是自己维护一张 `CtrlPins` 表。好处：引脚 MUX 与电平控制都归 Port/Dio 管，
 *          Can 配置里只剩一个通道号，CAN 通道加一个也不用再抄一份引脚描述。
 *
 *          @section CANCFG_STB STB 极性
 *          TJA1044：**STB 低 = Normal，高 = Standby**。所以
 *          `NormalValueOfTrcvPinSTB = STD_LOW`，
 *          `CanIf_SetTrcvMode(NORMAL)` 会把它拉低，`SLEEP` 则拉回高。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：CAN0 500 kbps + PTC1 STB |
 */

#include "Can.h"
#include "Can_Cfg.h"
#include "Can_Priv.h"
#include "Can_HwCfg.h"

#include "Dio_Cfg.h"

/* ============================ [ 数据 ] ============================ */

/** @brief 每个通道的运行上下文（状态机 + 收发器模式），驱动运行期改写 */
static Can_ChannelContextType Can_ChannelContexts[CAN_CFG_NUM_CHANNELS];

/**
 * @brief 通道配置表
 * @warning 字段顺序由 `Can_Priv.h` 的结构体决定，**不是**按名字初始化。
 *          若将来打开 `CAN_USE_CTRL_AC_CONFIG_TYPE`，要在 context 后插入 acCfg。
 */
static const Can_ChannelConfigType Can_ChannelConfigs[CAN_CFG_NUM_CHANNELS] = {
	{
		&Can_ChannelContexts[0],              /* context */
		CAN_CFG_BAUDRATE,                     /* baudrate */
		DIO_CHANNEL_CAN0_STB,                 /* TrcvPinSTB（USE_PORT 分支） */
		(uint8_t)CAN_CFG_SAMPLE_POINT,        /* samplePoint，单位 1% */
		0u,                                   /* hwInstanceId = CAN0 */
		STD_LOW,                              /* NormalValueOfTrcvPinSTB：低=正常 */
	},
	{
		&Can_ChannelContexts[1],              /* context */
		CAN_CFG_BAUDRATE,                     /* baudrate */
		DIO_CHANNEL_CAN1_STB,                 /* TrcvPinSTB：PTE13 */
		(uint8_t)CAN_CFG_SAMPLE_POINT,        /* samplePoint */
		1u,                                   /* hwInstanceId = CAN1 */
		STD_LOW,                              /* 低=正常 */
	},
};

/**
 * @brief 硬件实例 → 通道号映射
 * @details `hwIns2ChlMap[0] = 0` 表示"硬件 CAN0 对应通道 0"。
 *          多控制器时这里描述物理实例与逻辑通道的重排（AS 的做法：
 *          产品可能把 CTRL2 当 CAN0 用，映射表就是为这种情况准备的）。
 */
static const uint8_t Can_HwIns2ChlMap[2] = { 0u, 1u };

const Can_ConfigType Can_Config = {
	Can_ChannelConfigs,
	Can_HwIns2ChlMap,
	(uint8_t)CAN_CFG_NUM_CHANNELS,
	(uint8_t)ARRAY_SIZE(Can_HwIns2ChlMap),
};

/* ============================ [ 邮箱表 ] ============================ */

/**
 * @brief CAN0 邮箱表
 * @note  顺序即邮箱号顺序，`CanAc` 初始化时按本表逐条写硬件。
 *        改本表 = 改这块板子的硬件资源分配，不需要动 `CanAc.c`。
 *
 * @warning ID、扩展位、DLC 三者在 `CfgMsgObj` 时写死，运行期改不了
 *          （厂商 `SetTxMsg` 只写数据区），所以一条报文一个邮箱。
 */
static const CanHw_MsgCfgType CanHw_MsgCfgs0[] = {
	/**
	 * @section CANCFG_MB0_14 M14：15 个邮箱承载 20+ 条报文
	 *
	 * 邮箱分配的核心思路是**按段分组**，不是一条报文一个邮箱：
	 *
	 * | mb | 方向 | 覆盖范围 | 承载报文数 |
	 * |----|------|----------|-----------|
	 * | 2 | RX | `0x18FFxxxx` 全段（PGN 0xFF00~0xFFFF） | 车辆/灯光/门锁/雨刮/报警… |
	 * | 6 | RX | `0x18FExxxx` 全段（PGN 0xFE00~0xFEFF） | 车速/里程/… |
	 * | 7 | RX | `0x0A0~0x0A7` | 快变模拟量段 |
	 * | 8 | RX | `0x100~0x107` | 灯光控制段 |
	 * | 9 | RX | `0x110` | 车身状态 |
	 *
	 * 49 条报文的 Foton 矩阵用这套结构也是 **6 个接收邮箱**就够。
	 *
	 * @warning **真正要小心的不是邮箱号，是掩码的位位置。**
	 *
	 *          M14 在这里误判过一次，值得记下来：把标准帧段配到 mb7/8/9 后，
	 *          mb8/mb9 一条都收不到（连带 mb12/mb14 的 NM、Com 也哑了）。
	 *          当时读到 `MCR[MAXMB]=96` 却只有 mb0~mb7 有计数，就判断成
	 *          "这颗芯片只实现了 8 个邮箱"——**这个结论是错的**。
	 *
	 *          真相是 `CAN_HW_MASK_STD_FAST` 少了 18 位移位（见
	 *          `Can_HwCfg.h` 的 `CAN_HW_STD_ID_SHIFT` 说明）：11 位的 `0x7F8`
	 *          落在 bit[10:3]，而那几位在 ID 域里恒为 0，于是 mb7 变成
	 *          **全收邮箱**，把排在它后面的所有标准帧都截走了。
	 *          推翻"8 邮箱"判断的证据是：早前 mb15 配同一套掩码时**它自己是好的**
	 *          （只有它后面的 mb16/17 收不到）——说明 mb15 完全可用。
	 *
	 *          教训：**"某个邮箱收不到"优先怀疑掩码/邮箱序号配错，
	 *          而不是先怀疑硬件容量。** 全收邮箱的隐蔽性在于它没有任何报错，
	 *          只表现为"后面的报文全丢"。
	 *
	 * @note 邮箱 10、15 空着不用，留给"某条报文必须独占邮箱"的场合
	 *       （比如将来接 CAN FD 或需要独立时间戳的报文）。
	 */

	/* mb0：TX 心跳 0x123。TX 也开中断：发送完成回调 CanIf_TxConfirmation()，
	 *      CanTp 的分段发送依赖这个信号 */
	{ 0u,  1u, CAN_HW_ID_HEARTBEAT,     false, CAN_HW_MB_TX, 8u, true,  0u },

	/* mb1：RX 0x321 标准帧，全掩码（M1 回归项） */
	{ 1u,  1u, CAN_HW_ID_TESTRX,        false, CAN_HW_MB_RX, 8u, true,  0xFFFFFFFFu },

	/* mb2：RX J1939 段 0x18FFxxxx（PGN 0xFF00~0xFFFF 全部） */
	{ 2u,  1u, CAN_HW_ID_J1939_SEG_FF,  true,  CAN_HW_MB_RX, 8u, true,  CAN_HW_MASK_J1939_SEG },

	/* mb3：TX 0x18FF0002 扩展帧 */
	{ 3u,  1u, CAN_HW_ID_EXT_TX,        true,  CAN_HW_MB_TX, 8u, true,  0u },

	/* mb4：TX 诊断响应 0x7E8 */
	{ 4u,  1u, CAN_HW_ID_DIAG_RESP,     false, CAN_HW_MB_TX, 8u, true,  0u },

	/* mb5：RX 诊断请求 0x7E0（CanTp 从这里取 N-PDU） */
	{ 5u,  1u, CAN_HW_ID_DIAG_REQ,      false, CAN_HW_MB_RX, 8u, true,  0xFFFFFFFFu },

	/* mb6：RX J1939 段 0x18FExxxx（PGN 0xFE00~0xFEFF 全部） */
	{ 6u,  1u, CAN_HW_ID_J1939_SEG_FE,  true,  CAN_HW_MB_RX, 8u, true,  CAN_HW_MASK_J1939_SEG },

	/* mb7~mb9：RX 标准帧段（M14）—— 三段覆盖 BCM 私有报文区 0x0A0~0x11F */
	{ 7u,  1u, CAN_HW_ID_STD_FAST,      false, CAN_HW_MB_RX, 8u, true,  CAN_HW_MASK_STD_FAST },
	{ 8u,  1u, CAN_HW_ID_STD_LIGHT,     false, CAN_HW_MB_RX, 8u, true,  CAN_HW_MASK_STD_LIGHT },
	{ 9u,  1u, CAN_HW_ID_STD_BODY,      false, CAN_HW_MB_RX, 8u, true,  0xFFFFFFFFu },

	/**
	 * @section CANCFG_NM M9：网络管理报文 0x500
	 *
	 * TX 与 RX 各占一个邮箱，**同一个 ID**。FlexCAN 的邮箱方向配置期定死
	 * （`CS.CODE`），想"发完还能收别人的"就必须两个邮箱。
	 *
	 * @note 本机发出的 0x500 不会被自己的 mb12 收到 —— `MCR.SRXDIS` 默认禁用自收，
	 *       所以不会出现"自己叫醒自己"（否则 CanNm 永远进不了 ReadySleep）。
	 */
	{ 11u, 1u, CAN_HW_ID_NM,            false, CAN_HW_MB_TX, 8u, false, 0u },
	{ 12u, 1u, CAN_HW_ID_NM,            false, CAN_HW_MB_RX, 8u, true,  0xFFFFFFFFu },

	/**
	 * @section CANCFG_COM M10：Com 信号层测试报文
	 * 发 0x200 / 收 0x201（不同 ID，避免注入测试与自发报文撞车）。
	 */
	{ 13u, 1u, CAN_HW_ID_COM_TX,        false, CAN_HW_MB_TX, 8u, false, 0u },
	{ 14u, 1u, CAN_HW_ID_COM_RX,        false, CAN_HW_MB_RX, 8u, true,  0xFFFFFFFFu },
};

/**
 * @brief CAN1 邮箱表：**实车整车网**（Foton L1 通信矩阵）
 *
 * @details @section CANCFG_CAN1_LAYOUT 15 个邮箱承载 M8 测试 + 真实矩阵
 *
 * | mb | 方向 | 内容 | 说明 |
 * |----|------|------|------|
 * | 0 / 1 | TX / RX | `0x124` / `0x322` | M8 验证过的测试报文，**保留作为对照物** |
 * | 2~7 | TX | 6 条真实发送报文 | 一条报文一个邮箱（ID 在 CfgMsgObj 时写死） |
 * | 8~14 | RX | 7 个 PF 段 | 覆盖 34 条接收报文 |
 *
 * **为什么保留 0x124/0x322**：上板验证真实矩阵时，需要一个"确实能收发"的
 * 参照物。如果全部换成真实报文，就分不清"新配置生效了"还是"某条路径恰好还在跑"。
 * 而且 M8 的回归脚本依赖它们。
 *
 * @warning **邮箱号从 0 重新开始**：每个控制器有自己的邮箱 RAM，互不干扰。
 *          CAN0 用 mb0~mb14，CAN1 也从 mb0 开始，不冲突。
 */
static const CanHw_MsgCfgType CanHw_MsgCfgs1[] = {
	/* ---- M8 测试报文（保留）---- */

	/** mb0：TX `0x124` 标准帧，首字节递增 —— Kvaser 侧可肉眼确认发送节奏 */
	{ 0u, 1u, CAN_HW_ID_CAN1_TX, false, CAN_HW_MB_TX, 8u, true,  0u },

	/** mb1：RX `0x322` 标准帧，全掩码 —— 与 CAN0 的 0x321 配对，验两路独立 */
	{ 1u, 1u, CAN_HW_ID_CAN1_RX, false, CAN_HW_MB_RX, 8u, true,  0xFFFFFFFFu },

	/* ---- M19：真实矩阵的 6 条发送报文 ---- */
	/*
	 * @note 每条报文独占一个邮箱，因为厂商 `FlexCanDrv_SetTxMsg()` 只写数据区，
	 *       **不回写 ID 与 DLC** —— 那两项在 `CfgMsgObj()` 时就烧进邮箱了。
	 *       这条约束决定了 N 条 TX 报文必须有 N 个邮箱 + N 个 HTH。
	 */
	{ 2u, 1u, CAN_HW_ID_TX_LCSF,  true, CAN_HW_MB_TX, 8u, true,  0u },
	{ 3u, 1u, CAN_HW_ID_TX_CTRL,  true, CAN_HW_MB_TX, 8u, true,  0u },
	{ 4u, 1u, CAN_HW_ID_TX_OEL,   true, CAN_HW_MB_TX, 8u, true,  0u },
	{ 5u, 1u, CAN_HW_ID_TX_OWW,   true, CAN_HW_MB_TX, 8u, true,  0u },
	{ 6u, 1u, CAN_HW_ID_TX_DOOR,  true, CAN_HW_MB_TX, 8u, true,  0u },
	{ 7u, 1u, CAN_HW_ID_TX_DM1,   true, CAN_HW_MB_TX, 8u, true,  0u },

	/* ---- M19：真实矩阵的 7 个接收 PF 段 ---- */
	/*
	 * @details @section CANCFG_PF_WHY 为什么按 PF 分组而不是一条报文一个邮箱
	 *
	 *          34 条接收报文的 **PGN 全不相同**（PS 字节各异），若一条一个邮箱要
	 *          34 个；按 PF（bit23:16，即 EDP+PF）分组只要 **7 个**。
	 *
	 *          代价是硬件层放行得比实际需要更宽（同一个 PF 下可能有本工程不用的
	 *          PGN），由 CanIf 的软件掩码 `0x1FFFFF00` 再精确到 PGN。
	 *          这正是"硬件宽、软件窄"——**反过来做不到**：硬件不放行的帧
	 *          连中断都不会有，软件配得再对也没机会执行。
	 *
	 * @warning 掩码必须用 `CAN_HW_MASK_J1939_PF`（`0x00FF0000`），
	 *          **不能用 CAN0 测试通道的 `0x1FFF0000`**。区别在 bit28:26：
	 *          `0x1FFF0000` 要求优先级也匹配，而真实矩阵里 `0x0CFDCC21` 是 P=3、
	 *          `0x18FEF100` 是 P=6 —— 用含优先级的掩码会让 P 不一致的帧被硬件
	 *          静默丢弃，症状是"某些 PGN 收得到、某些收不到"。
	 */
	{ 8u,  1u, CAN_HW_ID_PF_EB, true, CAN_HW_MB_RX, 8u, true, CAN_HW_MASK_J1939_PF },
	{ 9u,  1u, CAN_HW_ID_PF_EC, true, CAN_HW_MB_RX, 8u, true, CAN_HW_MASK_J1939_PF },
	{ 10u, 1u, CAN_HW_ID_PF_EE, true, CAN_HW_MB_RX, 8u, true, CAN_HW_MASK_J1939_PF },
	{ 11u, 1u, CAN_HW_ID_PF_F0, true, CAN_HW_MB_RX, 8u, true, CAN_HW_MASK_J1939_PF },
	{ 12u, 1u, CAN_HW_ID_PF_FD, true, CAN_HW_MB_RX, 8u, true, CAN_HW_MASK_J1939_PF },
	{ 13u, 1u, CAN_HW_ID_PF_FE, true, CAN_HW_MB_RX, 8u, true, CAN_HW_MASK_J1939_PF },
	{ 14u, 1u, CAN_HW_ID_PF_FF, true, CAN_HW_MB_RX, 8u, true, CAN_HW_MASK_J1939_PF },
};

/** @brief 每个通道一张邮箱表，下标 = 通道号 */
const CanHw_MsgTableType CanHw_MsgTables[CAN_CFG_NUM_CHANNELS] = {
	{ CanHw_MsgCfgs0, (uint8_t)ARRAY_SIZE(CanHw_MsgCfgs0) },   /* 0 = CAN0 */
	{ CanHw_MsgCfgs1, (uint8_t)ARRAY_SIZE(CanHw_MsgCfgs1) },   /* 1 = CAN1 */
};

/**
 * @brief 硬件发送对象表：下标即 `Can_Write()` 的 `Hth`
 * @note  `CanIf_Cfg.c` 的 `hoh` 字段引用 `CAN_HW_HTH_*` 宏，不要写裸数字。
 */
const CanHw_HohType CanHw_Hohs[CAN_HW_HOH_NUM] = {
	/* HTH 0 → CAN0 邮箱 0，发 0x123 */
	{ 0u, 0u, CAN_HW_ID_HEARTBEAT, 8u },
	/* HTH 1 → CAN0 邮箱 3，发 0x18FF0002 */
	{ 0u, 3u, CAN_HW_ID_EXT_TX,    8u },
	/* HTH 2 → CAN1 邮箱 0，发 0x124 */
	{ 1u, 0u, CAN_HW_ID_CAN1_TX,   8u },
	/* HTH 3 → CAN0 邮箱 4，发 0x7E8（诊断响应，M3） */
	{ 0u, 4u, CAN_HW_ID_DIAG_RESP, 8u },
	/* HTH 4 → CAN0 邮箱 11，发 0x500（NM，M9） */
	{ 0u, 11u, CAN_HW_ID_NM,       8u },
	/* HTH 5 → CAN0 邮箱 13，发 0x200（Com 信号，M10） */
	{ 0u, 13u, CAN_HW_ID_COM_TX,   8u },

	/* ---- M19：CAN1 真实矩阵的 6 条发送报文 ---- */
	/*
	 * @warning 这里的 `msgBufId` 必须与 `CanHw_MsgCfgs1[]` 的邮箱号**逐条对应**。
	 *          对错了不会报错，只会"发出去的是别的 ID"或者"发不出去" ——
	 *          `Can_Write()` 里有 ID 校验（`CanAc.c:962` 比对 `hoh->canId`），
	 *          所以 ID 错会返回 `E_NOT_OK`，但**邮箱号错不会**被它发现。
	 */
	/* HTH 6  → CAN1 邮箱 2，发 0x18FE4021 BCM_LCSF */
	{ 1u,  2u, CAN_HW_ID_TX_LCSF,  8u },
	/* HTH 7  → CAN1 邮箱 3，发 0x18FF0C21 BCM_CTRL */
	{ 1u,  3u, CAN_HW_ID_TX_CTRL,  8u },
	/* HTH 8  → CAN1 邮箱 4，发 0x0CFDCC21 BCM_OEL */
	{ 1u,  4u, CAN_HW_ID_TX_OEL,   8u },
	/* HTH 9  → CAN1 邮箱 5，发 0x18FDCD21 BCM_OWW */
	{ 1u,  5u, CAN_HW_ID_TX_OWW,   8u },
	/* HTH 10 → CAN1 邮箱 6，发 0x18FE4E21 BCM_DOOR_CTRL */
	{ 1u,  6u, CAN_HW_ID_TX_DOOR,  8u },
	/* HTH 11 → CAN1 邮箱 7，发 0x18FECA21 BCM_DM1 */
	{ 1u,  7u, CAN_HW_ID_TX_DM1,   8u },
};
