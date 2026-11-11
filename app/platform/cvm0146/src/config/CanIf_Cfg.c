/**
 * @file    CanIf_Cfg.c
 * @brief   CanIf 配置表：RX 过滤表 + TX PDU 表 + 控制器上下文
 *
 * @details @section CANIFCFG_C_RX RX 过滤表的匹配规则
 *          `CanIf_RxDispatch()` 用**软件二分查找**在 `rxPdus[]` 里找目标：
 *          @code
 *          canid = Mailbox->CanId & CAN_CANID_MASK;   // 0x1FFFFFFF
 *          if (rxPdu->canid == (canid & rxPdu->mask)) 命中
 *          @endcode
 *          所以：
 *          - **表必须按 `canid` 升序排列**（二分查找的前提），否则在目标板上查不到；
 *          - `mask` 决定匹配精度：`0x1FFFFFFF` = ID 必须完全一致；
 *            要匹配一段 ID（如某个 PGN）就把低位清零；
 *          - 扩展帧不需要额外标记 —— `CanId` 的 bit31 在 `& CAN_CANID_MASK` 时被掩掉了。
 *
 *          @section CANIFCFG_C_ORDER 表顺序为什么重要
 *          二分查找要求有序。当前两条：`0x321` < `0x18FF0001`，顺序正确。
 *          M3 接 DBC 生成器后，生成器必须**排序后再输出**，
 *          否则症状是"某些报文偶尔收不到"——因为二分查找走错分支。
 *
 *          @section CANIFCFG_C_HOH hoh 字段填什么
 *          `hoh` 在 CanIf 里**只用于 Mirror 上报**，不参与分发
 *          （分发靠 `rxPduId`）。这里填真实的邮箱号，方便抓总线时对照。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：2 收 2 发，含 29 位扩展帧 |
 */

#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "CanIf_Priv.h"

#include "Can_HwCfg.h"
#include "PduR_CanIf.h"     /* M3：诊断 PDU 要走 PduR 往上 */
#include "PduR_Cfg.h"       /* PDUR_CANTP_TO_DCM_RX / PDUR_DCM_TO_CANTP_TX */

/* ============================ [ 外部回调 ] ============================ */
/*
 * 这些是"CanIf 之上的那一层"，现在直接是应用（M3 接 PduR 后换成
 * `PduR_CanIfRxIndication` / `PduR_CanIfTxConfirmation`，本文件不用改结构）。
 *
 * 刻意不 include 应用头：CanIf 的配置由 `LibraryCanIf` 编译，
 * 它看不到 `app/app/include`（也不该看到）。AS 的生成器用的是同一个手法，
 * 直接把 `void Xxx_RxIndication(...)` 的原型写进生成的 .c。
 */

/** @brief 收到一帧报文（应用实现） */
void App_CanIfRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);

/** @brief 一帧发送完成（应用实现） */
void App_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result);

/* ============================ [ PduR 适配 shim（M3） ] ============================ */

/**
 * @brief 诊断请求 0x7E0 → PduR 的 RX 路径
 *
 * @details 为什么需要这个 3 行函数：CanIf 的 `rxPduId` 与 PduR 的 `pathId`
 *          是**两套独立编号**。CanIf 只负责把 `rxPduId` 原样交给它的 `rxInd`；
 *          而 PduR 要求传入的 id 必须落在 `0..numOfRoutingPaths-1`，
 *          越界时（USE_DET 关闭）会**越界读路由表** → 调用垃圾函数指针。
 *
 *          所以这里显式做换算：CanIf 侧用 `CANIF_RX_DIAG_REQ`(4) 做唯一编号，
 *          PduR 侧用 `PDUR_CANTP_TO_DCM_RX`(0)。两套编号各自独立演化，互不牵连。
 */
static void CanIfCfg_DiagRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	(void)RxPduId;   /* 本平台只有一条诊断链路，不需要区分 */
	PduR_CanIfRxIndication((PduIdType)PDUR_CANIF_TO_CANTP_RX, PduInfoPtr);
}

/**
 * @brief 诊断响应 0x7E8 发送完成 → PduR 的 TX 路径
 * @note  CanTp 靠这个确认推进分段发送：没有它，多帧响应的第二帧永远不会发出去。
 */
static void CanIfCfg_DiagTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
	(void)TxPduId;
	PduR_CanIfTxConfirmation((PduIdType)PDUR_CANTP_TX_CONFIRM, result);
}

/**
 * @brief Com 信号报文 0x200 上行 → PduR → Com（M10）
 * @note  与 NM 同为"协议报文不交给应用"：应用只该看到
 *        `Com_ReceiveSignal()` 解出来的物理值，不该自己拆字节。
 */
static void CanIfCfg_ComRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	(void)RxPduId;
	PduR_CanIfRxIndication((PduIdType)PDUR_CANIF_TO_COM_RX, PduInfoPtr);
}

/**
 * @brief Com 信号报文 0x200 发送完成 → PduR → Com（M10）
 *
 * @details @section CANIFCFG_COMTXCFM 没有它会发生什么
 *
 *          `Com_TxConfirmation()` 是 Com 内部"发送成功"的唯一证据：
 *          它负责通知信号级 TxNotification、清 update bit、
 *          以及（开了 `COM_USE_TX_IPDU_CALLOUT` 时）做发送后处理。
 *
 *          本工程这两个可选通知都没开，所以**当前不接也不影响报文发送** ——
 *          但会留下一个隐患：将来打开 `COM_USE_TX_NOTIFICATION` 时，
 *          回调不会来，症状是"信号发出去了但应用永远收不到确认"。
 *          现在接上，成本是一条路由。
 */
static void CanIfCfg_ComTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
	(void)TxPduId;
	PduR_CanIfTxConfirmation((PduIdType)PDUR_COM_TX_CONFIRM, result);
}

/**
 * @brief 网络管理报文 0x500 上行 → PduR → CanNm（M9）
 *
 * @details @section CANIFCFG_NMRX 为什么 NM 报文不交给应用
 *
 *          NM 报文是**协议报文**，不是信号：`
 *          它的内容（NID / CBV）由 CanNm 状态机维护，应用只应当知道
 *          "网络醒了/睡了"这个结论，而不是自己去解析 8 个字节。
 *
 *          所以这里转给 PduR → CanNm，和应用层完全隔离。
 *          这样将来换 NM 参数（节点号、CBV 位置）应用一行都不用改。
 */
static void CanIfCfg_NmRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	(void)RxPduId;
	PduR_CanIfRxIndication((PduIdType)PDUR_CANIF_TO_CANNM_RX, PduInfoPtr);
}

/**
 * @brief 网络管理报文 0x500 发送完成 → PduR → CanNm（M9）
 *
 * @details @section CANIFCFG_NMTXCFM 这个确认不是"可选优化"，是功能依赖
 *
 *          `CanNm_TxConfirmation()` 在成功时做两件事（`CanNm.c:815`）：
 *          1. `TxCounter++` —— 立即发送模式下靠它判断"连发够了没有"；
 *          2. **取消 `TxTimeout` 定时器、重启 `NMTimeout`**。
 *
 *          少了这个确认，`TxTimeout` 会一直跑到超时（`MsgTimeoutTime`），
 *          然后 `Nm_TxTimeoutException()` 被调用 —— NM 会认为"总线发不出去"，
 *          在 `NormalOperation` 里反复报发送异常。**报文其实一直在正常发出**，
 *          只是状态机以为没发成。
 */
static void CanIfCfg_NmTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
	(void)TxPduId;
	PduR_CanIfTxConfirmation((PduIdType)PDUR_CANNM_TX_CONFIRM, result);
}

/* ============================ [ RX 过滤表 ] ============================ */

/**
 * @brief CAN0 接收过滤表
 * @warning **必须按 canid 升序**，否则 `CanIf_RxDispatch()` 的二分查找会漏。
 * @note  `rxPduId` 用 `CANIF_RX_*` 宏，不要写裸数字 —— M3 接 PduR 后
 *        这个值就是 PduR 的 `pathId`，改一处即可。
 */
static const CanIf_RxPduType CanIf_RxPdus_CAN0[] = {
	/**
	 * 0x201 Com 信号测试（M10）：交给 PduR → Com。
	 * @note 必须是全表第一条 —— 二分查找要求 canid 升序，0x201 最小。
	 *       顺序错了这条会**静默收不到**（M8 踩过同样的坑）。
	 * @note 收 0x201 而不是 0x200：0x200 是本节点的发送 ID，
	 *       同 ID 会让注入测试撞车（见 `Can_HwCfg.h` 的说明）。
	 */
	{
		CanIfCfg_ComRxIndication,       /* rxInd */
		CANIF_RX_COM_TEST,              /* rxPduId */
		CAN_HW_ID_COM_RX,               /* canid：0x201 */
		0x1FFFFFFFu,                    /* mask */
		14u,                            /* hoh：CAN0 邮箱 14 */
	},

	/* 0x321 标准帧：M1 就有的报文，保留做回归 */
	{
		App_CanIfRxIndication,          /* rxInd */
		CANIF_RX_TEST,                  /* rxPduId */
		0x321u,                         /* canid */
		0x1FFFFFFFu,                    /* mask：ID 必须完全一致 */
		1u,                             /* hoh：CAN0 邮箱 1 */
	},

	/**
	 * 0x500 网络管理（M9）：交给 PduR → CanNm，**不交给应用**。
	 * @note 位置在 0x321 与 0x7E0 之间，因为二分查找要求 canid 升序 ——
	 *       这不只是为了好看，顺序错了这条会静默收不到（见 M8 的坑）。
	 */
	{
		CanIfCfg_NmRxIndication,        /* rxInd */
		CANIF_RX_NM,                    /* rxPduId */
		CAN_HW_ID_NM,                   /* canid：0x500 */
		0x1FFFFFFFu,                    /* mask */
		12u,                            /* hoh：CAN0 邮箱 12（NM 专用接收） */
	},

	/* 0x7E0 诊断请求（M3）：交给 PduR → CanTp 重组 → Dcm */
	{
		CanIfCfg_DiagRxIndication,      /* rxInd */
		CANIF_RX_DIAG_REQ,              /* rxPduId */
		0x7E0u,                         /* canid */
		0x1FFFFFFFu,                    /* mask */
		5u,                             /* hoh：CAN0 邮箱 5 */
	},

	/**
	 * @section CANIFCFG_J1939 M8：J1939 多报文（模拟 Foton 场景）
	 *
	 * @warning **顺序是硬约束，不是习惯。** `CanIf_RxDispatch()` 用的是
	 *          **二分查找**（`CanIf.c:104` 的 `l/h/m` 三指针），靠
	 *          `var->canid` 与来帧 ID 比较来收缩区间。所以：
	 *
	 *          1. 全表**严格按 `canid` 升序**；
	 *          2. **所有掩码项必须排在精确项之后**（掩码项代表一个 ID 区间，
	 *             夹在中间会让二分在某个方向判错）。
	 *
	 *          这两条都不会报错，症状只是"某条报文收不到"。
	 *          本工程在这一条上真的踩过：加 J1939 报文时把 0x18FF0001
	 *          留在了原位（排在 0x18FExxxx 之前），结果它自己收不到了，
	 *          而新加的四条全正常 —— 看起来像"老功能被新配置破坏了"，
	 *          实际是表序坏了。
	 *          为此 `CanIfCfg_CheckRxOrder()` 在初始化时自检，见文件末尾。
	 */

	/* 四个不同 PGN，精确匹配，按 canid 升序 */
	{
		App_CanIfRxIndication, CANIF_RX_J1939_D, 0x18FEA100u, 0x1FFFFFFFu, 10u,
	},
	{
		App_CanIfRxIndication, CANIF_RX_J1939_C, 0x18FEB100u, 0x1FFFFFFFu, 9u,
	},
	{
		App_CanIfRxIndication, CANIF_RX_J1939_B, 0x18FEC100u, 0x1FFFFFFFu, 8u,
	},
	{
		App_CanIfRxIndication, CANIF_RX_J1939_A, 0x18FEF100u, 0x1FFFFFFFu, 7u,
	},

	/* 0x18FF0001 扩展帧（M2）：单条 J1939 报文，精确匹配。
	 * 它比 0x18FExxxx 大，所以必须排在它们**之后** —— 这正是踩过的坑。 */
	{
		App_CanIfRxIndication,          /* rxInd */
		CANIF_RX_EXT_TEST,              /* rxPduId */
		0x18FF0001u,                    /* canid */
		0x1FFFFFFFu,                    /* mask */
		2u,                             /* hoh：CAN0 邮箱 2 */
	},

	/* 最后一条：同 PGN 任意源地址（唯一的掩码项，必须放全表末尾） */
	{
		App_CanIfRxIndication,          /* rxInd */
		CANIF_RX_J1939_PGN,             /* rxPduId */
		0x18FF0100u,                    /* canid（PGN 基址，落在掩码范围内） */
		0x1FFFFF00u,                    /* mask：忽略最低 8 位源地址 */
		6u,                             /* hoh：CAN0 邮箱 6（硬件掩码同值） */
	},
};

/**
 * @brief CAN1 接收过滤表
 * @warning 同样**必须按 canid 升序**。当前只有一条，天然有序；
 *          加第二条时要注意"表内有序"，而不是"整表全局有序" ——
 *          `CanIf_RxDispatch()` 是按 `ControllerId` 选表后各自二分的。
 */
static const CanIf_RxPduType CanIf_RxPdus_CAN1[] = {
	/* 0x322 标准帧 */
	{
		App_CanIfRxIndication,          /* rxInd */
		CANIF_RX_CAN1_TEST,             /* rxPduId */
		0x322u,                         /* canid */
		0x1FFFFFFFu,                    /* mask */
		1u,                             /* hoh：CAN1 邮箱 1 */
	},
	/**
	 * J1939 PGN 匹配示例：ID = 0x18FF0100，掩码 0x1FFFFF00。
	 * 匹配式是 `rxPdu->canid == (canid & rxPdu->mask)`，所以：
	 *   收到 0x18FF01AB → 0x18FF01AB & 0x1FFFFF00 = 0x18FF0100 → **命中**
	 *   收到 0x18FF0200 → 0x18FF0200 & 0x1FFFFF00 = 0x18FF0200 → 不命中
	 * 即"同一 PGN、任意源地址都收"，这正是 J1939 的常规用法。
	 *
	 * @warning **表里的 `canid` 必须本身就在掩码范围内**，即 `canid & mask == canid`。
	 *          因为比较的是"掩码后的来帧 ID"与"原样存储的 canid"是否相等：
	 *          若写 `canid=0x18FF0100` 却配 `mask=0x1FFF0000`，则
	 *          `0x18FF0100 & 0x1FFF0000 = 0x18FF0000 != 0x18FF0100`，**永远匹配不上**。
	 *          这个错误不会报任何警，症状只是"这条报文收不到"。
	 */
	{
		App_CanIfRxIndication,          /* rxInd */
		CANIF_RX_CAN1_PGN,              /* rxPduId */
		0x18FF0100u,                    /* canid（PGN 基址） */
		0x1FFFFF00u,                    /* mask：忽略最低 8 位（源地址） */
		2u,                             /* hoh：CAN1 邮箱 2（硬件掩码 0x1FFF0000） */
	},
};

/* ============================ [ TX PDU 表 ] ============================ */

/**
 * @brief CAN0 发送 PDU 表
 * @note  `hoh` 用 `CAN_HW_HTH_*` 宏引用 `Can_Cfg.c` 的 HTH 表，
 *        避免"CanIf 指向了别的邮箱"这类静默错误。
 *        `ControllerId` 必须是 `CanIf_CtrlContexts[]` 的合法下标。
 */
static const CanIf_TxPduType CanIf_TxPdus[] = {
	/* 0x123 心跳帧：HTH 0 → CAN0 邮箱 0 */
	{
		App_CanIfTxConfirmation,        /* txConfirm */
		CANIF_TX_HEARTBEAT,             /* txPduId */
		CAN_HW_ID_HEARTBEAT,            /* canid */
		NULL,                           /* p_canid：固定 ID */
		CAN_HW_HTH_CAN0_HEARTBEAT,      /* hoh */
		CANIF_CHL_CAN0,                 /* ControllerId */
	},
	/* 0x18FF0002 扩展帧：HTH 1 → CAN0 邮箱 3 */
	{
		App_CanIfTxConfirmation,        /* txConfirm */
		CANIF_TX_EXT_TEST,              /* txPduId */
		CAN_HW_ID_EXT_TX,               /* canid */
		NULL,                           /* p_canid */
		CAN_HW_HTH_CAN0_EXT_TX,         /* hoh */
		CANIF_CHL_CAN0,                 /* ControllerId */
	},
	/* 0x124 心跳帧：HTH 2 → CAN1 邮箱 0 */
	{
		App_CanIfTxConfirmation,        /* txConfirm */
		CANIF_TX_CAN1_TEST,             /* txPduId */
		CAN_HW_ID_CAN1_TX,              /* canid */
		NULL,                           /* p_canid */
		CAN_HW_HTH_CAN1_HEARTBEAT,      /* hoh */
		CANIF_CHL_CAN1,                 /* ControllerId */
	},
	/* 0x7E8 诊断响应（M3）：HTH 3 → CAN0 邮箱 4 */
	{
		CanIfCfg_DiagTxConfirmation,    /* txConfirm */
		CANIF_TX_DIAG_RESP,             /* txPduId */
		CAN_HW_ID_DIAG_RESP,            /* canid */
		NULL,                           /* p_canid */
		CAN_HW_HTH_DIAG_RESP,           /* hoh */
		CANIF_CHL_CAN0,                 /* ControllerId */
	},
	/* 0x500 网络管理（M9）：HTH 4 → CAN0 邮箱 11 */
	{
		CanIfCfg_NmTxConfirmation,      /* txConfirm：推进 CanNm 的 TxCounter / 定时器 */
		CANIF_TX_NM,                    /* txPduId */
		CAN_HW_ID_NM,                   /* canid */
		NULL,                           /* p_canid：固定 ID */
		CAN_HW_HTH_NM,                  /* hoh */
		CANIF_CHL_CAN0,                 /* ControllerId */
	},
	/* 0x200 Com 信号测试（M10）：HTH 5 → CAN0 邮箱 13 */
	{
		CanIfCfg_ComTxConfirmation,     /* txConfirm */
		CANIF_TX_COM_TEST,              /* txPduId */
		CAN_HW_ID_COM_TX,               /* canid：0x200 */
		NULL,                           /* p_canid：固定 ID */
		CAN_HW_HTH_COM,                 /* hoh */
		CANIF_CHL_CAN0,                 /* ControllerId */
	},
};

/* ============================ [ 控制器 ] ============================ */

/**
 * @brief 每个控制器的运行上下文（PDU 模式等），`CanIf_Init` 会改写
 * @note  必须是**非 const**：`CanIf_SetPduMode()` 会把 `PduMode` 改成 ONLINE。
 * @note  数组长度跟着通道宏走 —— 加通道时这里自动扩容，不会漏。
 */
static CanIf_CtrlContextType CanIf_CtrlContexts[CANIF_CHL_CAN1 + 1u];

/** @brief 每个控制器的 RX 过滤表与超时参数（下标与 CtrlContexts 一致） */
static const CanIf_CtrlConfigType CanIf_CtrlConfigs[] = {
	{
		CanIf_RxPdus_CAN0,                          /* rxPdus */
		(uint16_t)ARRAY_SIZE(CanIf_RxPdus_CAN0),    /* numOfRxPdus */
		/* 下面一项只在 CANIF_USE_TX_TIMEOUT && USE_CANSM 时存在 */
	},
	{
		CanIf_RxPdus_CAN1,                          /* rxPdus */
		(uint16_t)ARRAY_SIZE(CanIf_RxPdus_CAN1),    /* numOfRxPdus */
	},
};

/* ============================ [ 总表 ] ============================ */

const CanIf_ConfigType CanIf_Config = {
	CanIf_TxPdus,                               /* txPdus */
	CanIf_CtrlContexts,                         /* CtrlContexts */
	CanIf_CtrlConfigs,                          /* CtrlConfigs */
	(uint16_t)ARRAY_SIZE(CanIf_TxPdus),         /* numOfTxPdus */
	(uint8_t)ARRAY_SIZE(CanIf_CtrlContexts),    /* numOfCtrls */
};

/* ============================ [ 配置自检 ] ============================ */

/**
 * @brief 检查接收过滤表是否满足二分查找的前置条件
 * @retval true  两张表都合法
 * @retval false 有乱序，或掩码项不在末尾
 *
 * @details 为什么需要它：`CanIf_RxDispatch()`（`CanIf.c:104`）用**二分查找**，
 *          但 C 语言没法在编译期检查"数组是否有序"，所以只能在初始化时验一遍。
 *
 *          要检查的两条：
 *          1. **精确项严格升序** —— 乱序会让二分跳过某些项；
 *          2. **掩码项必须排在所有精确项之后** —— 掩码项代表一个 ID 区间，
 *             夹在中间会让二分的区间收缩方向判错。
 *
 *          违反任何一条都**不会报错**，症状只是"某条报文收不到"。
 *          本工程真的踩过：加 J1939 报文时把 `0x18FF0001` 留在原位
 *          （排在 `0x18FExxxx` 之前），结果它自己收不到了，
 *          而新加的四条全正常 —— 看起来像"老功能被新配置破坏"。
 *
 * @note  判据里用 `0x1FFFFFFF`（全掩码）来区分"精确项"和"掩码项"。
 *        将来如果真需要一条 `mask=0x1FFFFFFF` 但又想表达"区间"的项，
 *        这个判据会误判 —— 那时要引入显式的 `isMask` 字段。
 */
bool CanIfCfg_CheckRxOrder(void)
{
	const CanIf_CtrlConfigType *ctrl;
	uint16_t i;
	uint8_t c;
	bool seenMask;

	for (c = 0u; c < CanIf_Config.numOfCtrls; c++) {
		ctrl = &CanIf_Config.CtrlConfigs[c];
		seenMask = false;

		for (i = 0u; i < ctrl->numOfRxPdus; i++) {
			if (ctrl->rxPdus[i].mask != 0x1FFFFFFFu) {
				seenMask = true;        /* 掩码项：此后不许再出现精确项 */
				continue;
			}
			if (seenMask) {
				return false;           /* 精确项排在掩码项之后 */
			}
			if (i > 0u) {
				/* 与前一项比。前一项可能是掩码项，但它已被 seenMask 挡住，
				 * 走到这里前一项一定是精确项。 */
				if (ctrl->rxPdus[i].canid <= ctrl->rxPdus[i - 1u].canid) {
					return false;       /* 未严格升序 */
				}
			}
		}
	}

	return true;
}
