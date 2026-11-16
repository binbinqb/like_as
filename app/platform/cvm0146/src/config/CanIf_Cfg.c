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
	/* ------------------------------------------------------------------
	 * 标准帧段（M14）：BCM 私有报文，用区间掩码合并成一两个表项
	 *
	 * `canid & mask == canid` 是硬要求（见 CAN1 表末尾的说明），
	 * 所以段基址必须是"区间下界"：0x0A0 配 0x7F8 覆盖 0x0A0~0x0A7。
	 * ------------------------------------------------------------------ */
	{
		App_CanIfRxIndication,          /* rxInd */
		CANIF_RX_STD_FAST,              /* rxPduId */
		CAN_HW_ID_STD_FAST,             /* canid：0x0A0 */
		/* 软件掩码用 **11 位原值**，不是 `CAN_HW_MASK_STD_FAST`。
		 * 那个宏是硬件值（左移 18 位），只给邮箱 RXIMR 用。
		 * 这里直接与未移位的 canid 比对，写 0x1FE00000 会一条都匹配不上。 */
		0x7F8u,                         /* mask：覆盖 0x0A0~0x0A7 */
		7u,                             /* hoh：CAN0 邮箱 7 */
	},
	{
		App_CanIfRxIndication,
		CANIF_RX_STD_LIGHT,
		CAN_HW_ID_STD_LIGHT,            /* 0x100 */
		0x7F8u,                         /* 软件掩码：覆盖 0x100~0x107（理由同上） */
		8u,                             /* hoh：CAN0 邮箱 8 */
	},
	{
		App_CanIfRxIndication,
		CANIF_RX_STD_BODY,
		CAN_HW_ID_STD_BODY,             /* 0x110，单条精确 */
		0x1FFFFFFFu,
		9u,                             /* hoh：CAN0 邮箱 9 */
	},

	/* ------------------------------------------------------------------
	 * 核心报文（M1~M10 的回归项，编号与语义一律不动）
	 * ------------------------------------------------------------------ */
	{
		CanIfCfg_ComRxIndication,       /* rxInd */
		CANIF_RX_COM_TEST,              /* rxPduId */
		CAN_HW_ID_COM_RX,               /* canid：0x201 */
		0x1FFFFFFFu,                    /* mask */
		14u,                            /* hoh：CAN0 邮箱 14 */
	},
	{
		App_CanIfRxIndication,          /* rxInd */
		CANIF_RX_TEST,                  /* rxPduId */
		0x321u,                         /* canid */
		0x1FFFFFFFu,                    /* mask */
		1u,                             /* hoh：CAN0 邮箱 1 */
	},
	{
		CanIfCfg_NmRxIndication,        /* rxInd */
		CANIF_RX_NM,                    /* rxPduId */
		CAN_HW_ID_NM,                   /* canid：0x500 */
		0x1FFFFFFFu,                    /* mask */
		12u,                            /* hoh：CAN0 邮箱 12 */
	},
	{
		CanIfCfg_DiagRxIndication,      /* rxInd */
		CANIF_RX_DIAG_REQ,              /* rxPduId */
		0x7E0u,                         /* canid */
		0x1FFFFFFFu,                    /* mask */
		5u,                             /* hoh：CAN0 邮箱 5 */
	},

	/**
	 * @section CANIFCFG_J1939 J1939 段（M8 / M14）
	 *
	 * @warning **顺序是硬约束，不是习惯。** `CanIf_RxDispatch()` 用的是
	 *          **二分查找**（`CanIf.c:104` 的 `l/h/m` 三指针），靠
	 *          `var->canid` 与来帧 ID 比较来收缩区间。所以：
	 *
	 *          1. 全表**严格按 `canid` 升序**；
	 *          2. **掩码项覆盖的区间之间不能重叠**，也不能与精确项重叠 ——
	 *             重叠时"命中哪一个"取决于二分走到哪一项，是未定义行为。
	 *
	 *          本工程在这一条上真的踩过：加 J1939 报文时把 0x18FF0001
	 *          留在了原位（排在 0x18FExxxx 之前），结果它自己收不到了。
	 *          为此 `CanIfCfg_CheckRxOrder()` 在初始化时自检，见文件末尾。
	 *
	 * @note M14 的段化设计：PGN 0xFExx 全部由邮箱 6（段掩码 0x1FFF0000）收进来，
	 *       这里再按 PGN 精确到 0x1FFFFF00 —— **硬件宽、软件窄**，
	 *       两层串联。硬件不放行的帧连中断都不会有，软件层再对也没用。
	 */

	/* PGN 0xFEA1 / FEB1 / FEC1（M8 的四个"不同 PGN"回归项，改走段邮箱） */
	{
		App_CanIfRxIndication, CANIF_RX_J1939_D, 0x18FEA100u, 0x1FFFFF00u, 6u,
	},
	{
		App_CanIfRxIndication, CANIF_RX_J1939_C, 0x18FEB100u, 0x1FFFFF00u, 6u,
	},
	{
		App_CanIfRxIndication, CANIF_RX_J1939_B, 0x18FEC100u, 0x1FFFFF00u, 6u,
	},

	/** PGN 0xFEE0 里程（M14 新增，1000 ms 慢变） */
	{
		App_CanIfRxIndication, CANIF_RX_J1939_ODO, 0x18FEE000u, 0x1FFFFF00u, 6u,
	},

	/** PGN 0xFEF1 车速（M8 回归项，改走段邮箱） */
	{
		App_CanIfRxIndication, CANIF_RX_J1939_A, 0x18FEF100u, 0x1FFFFF00u, 6u,
	},

	/**
	 * 0x18FF0001 —— **PGN 0xFF00 段内的精确项**（M2 的扩展帧回归）。
	 *
	 * @warning 它必须**排在 0x18FF0100 段项之前**：0x18FF0001 数值更小，
	 *          且精确项只占一个 ID，不与 [0x18FF0100, 0x18FF01FF] 重叠。
	 *          如果先写段项，二分在收缩区间时会跳过这一条。
	 */
	{
		App_CanIfRxIndication,          /* rxInd */
		CANIF_RX_EXT_TEST,              /* rxPduId */
		0x18FF0001u,                    /* canid */
		0x1FFFFFFFu,                    /* mask：精确匹配 */
		2u,                             /* hoh：CAN0 邮箱 2（FF 段） */
	},

	/** PGN 0xFF01 灯光状态（同 PGN 任意源地址 —— M8 的掩码分组回归项） */
	{
		App_CanIfRxIndication, CANIF_RX_J1939_PGN, 0x18FF0100u, 0x1FFFFF00u, 2u,
	},

	/** PGN 0xFF02 门锁状态（M14） */
	{
		App_CanIfRxIndication, CANIF_RX_J1939_DOOR, 0x18FF0200u, 0x1FFFFF00u, 2u,
	},

	/** PGN 0xFF03 雨刮状态（M14） */
	{
		App_CanIfRxIndication, CANIF_RX_J1939_WIPER, 0x18FF0300u, 0x1FFFFF00u, 2u,
	},

	/**
	 * PGN 0xFF04 **同一 PGN、三个不同源地址**（M14 的核心压测项）
	 * @note 这一条覆盖 0x18FF0401 / 0402 / 0405，验"一个表项收一组 SA"。
	 */
	{
		App_CanIfRxIndication, CANIF_RX_J1939_MULTI, 0x18FF0400u, 0x1FFFFF00u, 2u,
	},

	/** PGN 0xFF05 报警（M14） */
	{
		App_CanIfRxIndication, CANIF_RX_J1939_ALARM, 0x18FF0500u, 0x1FFFFF00u, 2u,
	},

	/** PGN 0xFF06 高频扩展帧（M14，20 ms，压扩展帧中断） */
	{
		App_CanIfRxIndication, CANIF_RX_J1939_FAST, 0x18FF0600u, 0x1FFFFF00u, 2u,
	},

	/**
	 * 最后一条：**段内最大 PGN** `0x18FFFF00`（PGN 0xFFFF、SA 0x00）。
	 * @note 二分查找最容易在两端出错，两端出错的表现是"只有最小/最大的那条收不到"。
	 *       0x0A0 验左端，这一条验右端。
	 * @warning 这里**不能用 29 位 ID 极值 `0x1FFFFF00`**：它的 bit[28:16] 是
	 *          `0x1FFFF`，不满足硬件段掩码 `0x1FFF0000` 要求的 `0x18FF0`，
	 *          压根不会进邮箱。M14 第一次跑就是这一条报 FAIL。
	 */
	{
		App_CanIfRxIndication, CANIF_RX_J1939_MAXID, CAN_HW_ID_J1939_MAXPGN, 0x1FFFFF00u, 2u,
	},
};

/**
 * @brief CAN1 接收过滤表
 * @warning 同样**必须按 canid 升序**。当前只有一条，天然有序；
 *          加第二条时要注意"表内有序"，而不是"整表全局有序" ——
 *          `CanIf_RxDispatch()` 是按 `ControllerId` 选表后各自二分的。
 */
/* @generated BEGIN: CAN1 real matrix */
/* ---- PduR 回调 shim（M22）----
 *
 * 每条报文一个：`CanIf_RxPduType` / `CanIf_TxPduType` 只有函数指针、
 * 没有 context 字段，所以 pathId 只能靠「每条一个函数」带进去。
 * 先调 App 的统计回调再进 PduR —— 统计是 `!k` / `!b` 的数据源。
 */
static void CanIfCfg_TxPduR_CAN1_LCSF(PduIdType TxPduId, Std_ReturnType result)
{
	App_CanIfTxConfirmation(TxPduId, result);      /* `!b` burst 的确认计数 */
	PduR_CanIfTxConfirmation((PduIdType)PDUR_CAN1_BCM_LCSF_TX, result);
} /* BCM_LCSF → CANIF_TX_CAN1_LCSF */
static void CanIfCfg_TxPduR_CAN1_CTRL(PduIdType TxPduId, Std_ReturnType result)
{
	App_CanIfTxConfirmation(TxPduId, result);      /* `!b` burst 的确认计数 */
	PduR_CanIfTxConfirmation((PduIdType)PDUR_CAN1_BCM_CTRL_TX, result);
} /* BCM_Ctrl → CANIF_TX_CAN1_CTRL */
static void CanIfCfg_TxPduR_CAN1_OEL(PduIdType TxPduId, Std_ReturnType result)
{
	App_CanIfTxConfirmation(TxPduId, result);      /* `!b` burst 的确认计数 */
	PduR_CanIfTxConfirmation((PduIdType)PDUR_CAN1_BCM_OEL_TX, result);
} /* BCM_OEL → CANIF_TX_CAN1_OEL */
static void CanIfCfg_TxPduR_CAN1_OWW(PduIdType TxPduId, Std_ReturnType result)
{
	App_CanIfTxConfirmation(TxPduId, result);      /* `!b` burst 的确认计数 */
	PduR_CanIfTxConfirmation((PduIdType)PDUR_CAN1_BCM_OWW_TX, result);
} /* BCM_OWW → CANIF_TX_CAN1_OWW */
static void CanIfCfg_TxPduR_CAN1_DOOR(PduIdType TxPduId, Std_ReturnType result)
{
	App_CanIfTxConfirmation(TxPduId, result);      /* `!b` burst 的确认计数 */
	PduR_CanIfTxConfirmation((PduIdType)PDUR_CAN1_BCM_DOOR_CTRL_TX, result);
} /* BCM_DoorCtrl → CANIF_TX_CAN1_DOOR */
static void CanIfCfg_TxPduR_CAN1_DM1(PduIdType TxPduId, Std_ReturnType result)
{
	App_CanIfTxConfirmation(TxPduId, result);      /* `!b` burst 的确认计数 */
	PduR_CanIfTxConfirmation((PduIdType)PDUR_CAN1_BCM_DM1_TX, result);
} /* BCM_DM1 → CANIF_TX_CAN1_DM1 */

static void CanIfCfg_RxPduR_CAN1_EEC1_ELECTRONIC_ENGINE_CONTROLLER_1(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_EEC1_ELECTRONIC_ENGINE_CONTROLLER_1_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_EOI(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_EOI_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_TCO1(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_TCO1_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_ESCL1(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_ESCL1_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_ESCLM_PEPS(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_ESCLM_PEPS_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_PEPS_ESCLM(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_PEPS_ESCLM_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_CRASH_NOTIFICATION(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_CRASH_NOTIFICATION_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_ACL(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_ACL_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_ERC3(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_ERC3_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_ERC1(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_ERC1_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_ETC2(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_ETC2_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_DLCC1_DIRECT_LAMP_CONTROL_COMMAND_1(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_DLCC1_DIRECT_LAMP_CONTROL_COMMAND_1_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_EBC5_ELECTRONIC_BRAKE_CONTROLLER_5(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_EBC5_ELECTRONIC_BRAKE_CONTROLLER_5_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_VDC1_VEHICLE_DYNAMIC_STABILITY_CONTROL_1(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_VDC1_VEHICLE_DYNAMIC_STABILITY_CONTROL_1_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_DM1_TPMS(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_DM1_TPMS_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_CCVS(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_CCVS_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_TIRE_CONDITION(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_TIRE_CONDITION_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_AMB_AMBIENT_CONDITIONS(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_AMB_AMBIENT_CONDITIONS_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_PEPS1(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_PEPS1_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_IC_MSG(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_IC_MSG_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_DW_STATE(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_DW_STATE_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_VCU_4(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_VCU_4_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_ID1(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_ID1_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_ID2(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_ID2_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_ID3(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_ID3_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_PEPS2(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_PEPS2_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_ESCL_NM(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_ESCL_NM_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_EEC3(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_EEC3_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_ECC2(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_ECC2_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_TP_DT(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_TP_DT_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_TP_CM(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_TP_CM_RX, PduInfoPtr);
}
static void CanIfCfg_RxPduR_CAN1_ETC5(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	App_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */
	PduR_CanIfRxIndication((PduIdType)PDUR_CAN1_ETC5_RX, PduInfoPtr);
}

static const CanIf_RxPduType CanIf_RxPdus_CAN1[] = {
	{
		CanIfCfg_RxPduR_CAN1_EEC1_ELECTRONIC_ENGINE_CONTROLLER_1,	/* rxInd */
		CANIF_RX_CAN1_EEC1_ELECTRONIC_ENGINE_CONTROLLER_1,
		0x0CF00400u,			/* canid：PF=0xF0 */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		11u,			/* hoh：mb11（PF=0xF0 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_EOI,	/* rxInd */
		CANIF_RX_CAN1_EOI,
		0x0CFD9200u,			/* canid：PF=0xFD */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		12u,			/* hoh：mb12（PF=0xFD 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_TCO1,	/* rxInd */
		CANIF_RX_CAN1_TCO1,
		0x0CFE6CEEu,			/* canid：PF=0xFE */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		13u,			/* hoh：mb13（PF=0xFE 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_ESCL1,	/* rxInd */
		CANIF_RX_CAN1_ESCL1,
		0x10FFB04Du,			/* canid：PF=0xFF */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		14u,			/* hoh：mb14（PF=0xFF 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_ESCLM_PEPS,	/* rxInd */
		CANIF_RX_CAN1_ESCLM_PEPS,
		0x10FFB24Du,			/* canid：PF=0xFF */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		14u,			/* hoh：mb14（PF=0xFF 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_PEPS_ESCLM,	/* rxInd */
		CANIF_RX_CAN1_PEPS_ESCLM,
		0x10FFB634u,			/* canid：PF=0xFF */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		14u,			/* hoh：mb14（PF=0xFF 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_CRASH_NOTIFICATION,	/* rxInd */
		CANIF_RX_CAN1_CRASH_NOTIFICATION,
		0x14F02B54u,			/* canid：PF=0xF0 */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		11u,			/* hoh：mb11（PF=0xF0 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_ACL,	/* rxInd */
		CANIF_RX_CAN1_ACL,
		0x18EEFF00u,			/* canid：PF=0xEE */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		10u,			/* hoh：mb10（PF=0xEE 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_ERC3,	/* rxInd */
		CANIF_RX_CAN1_ERC3,
		0x18F00000u,			/* canid：PF=0xF0 */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		11u,			/* hoh：mb11（PF=0xF0 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_ERC1,	/* rxInd */
		CANIF_RX_CAN1_ERC1,
		0x18F0000Fu,			/* canid：PF=0xF0 */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		11u,			/* hoh：mb11（PF=0xF0 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1,	/* rxInd */
		CANIF_RX_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1,
		0x18F0010Bu,			/* canid：PF=0xF0 */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		11u,			/* hoh：mb11（PF=0xF0 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_ETC2,	/* rxInd */
		CANIF_RX_CAN1_ETC2,
		0x18F00503u,			/* canid：PF=0xF0 */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		11u,			/* hoh：mb11（PF=0xF0 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_DLCC1_DIRECT_LAMP_CONTROL_COMMAND_1,	/* rxInd */
		CANIF_RX_CAN1_DLCC1_DIRECT_LAMP_CONTROL_COMMAND_1,
		0x18FD0700u,			/* canid：PF=0xFD */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		12u,			/* hoh：mb12（PF=0xFD 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_EBC5_ELECTRONIC_BRAKE_CONTROLLER_5,	/* rxInd */
		CANIF_RX_CAN1_EBC5_ELECTRONIC_BRAKE_CONTROLLER_5,
		0x18FDC40Bu,			/* canid：PF=0xFD */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		12u,			/* hoh：mb12（PF=0xFD 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_VDC1_VEHICLE_DYNAMIC_STABILITY_CONTROL_1,	/* rxInd */
		CANIF_RX_CAN1_VDC1_VEHICLE_DYNAMIC_STABILITY_CONTROL_1,
		0x18FE4F0Bu,			/* canid：PF=0xFE */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		13u,			/* hoh：mb13（PF=0xFE 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_DM1_TPMS,	/* rxInd */
		CANIF_RX_CAN1_DM1_TPMS,
		0x18FECA33u,			/* canid：PF=0xFE */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		13u,			/* hoh：mb13（PF=0xFE 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1,	/* rxInd */
		CANIF_RX_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1,
		0x18FEF100u,			/* canid：PF=0xFE */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		13u,			/* hoh：mb13（PF=0xFE 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_CCVS,	/* rxInd */
		CANIF_RX_CAN1_CCVS,
		0x18FEF121u,			/* canid：PF=0xFE */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		13u,			/* hoh：mb13（PF=0xFE 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_TIRE_CONDITION,	/* rxInd */
		CANIF_RX_CAN1_TIRE_CONDITION,
		0x18FEF433u,			/* canid：PF=0xFE */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		13u,			/* hoh：mb13（PF=0xFE 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_AMB_AMBIENT_CONDITIONS,	/* rxInd */
		CANIF_RX_CAN1_AMB_AMBIENT_CONDITIONS,
		0x18FEF500u,			/* canid：PF=0xFE */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		13u,			/* hoh：mb13（PF=0xFE 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_PEPS1,	/* rxInd */
		CANIF_RX_CAN1_PEPS1,
		0x18FF0534u,			/* canid：PF=0xFF */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		14u,			/* hoh：mb14（PF=0xFF 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_IC_MSG,	/* rxInd */
		CANIF_RX_CAN1_IC_MSG,
		0x18FF0917u,			/* canid：PF=0xFF */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		14u,			/* hoh：mb14（PF=0xFF 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_DW_STATE,	/* rxInd */
		CANIF_RX_CAN1_DW_STATE,
		0x18FF0CECu,			/* canid：PF=0xFF */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		14u,			/* hoh：mb14（PF=0xFF 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_VCU_4,	/* rxInd */
		CANIF_RX_CAN1_VCU_4,
		0x18FF12EFu,			/* canid：PF=0xFF */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		14u,			/* hoh：mb14（PF=0xFF 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_ID1,	/* rxInd */
		CANIF_RX_CAN1_ID1,
		0x18FF4C56u,			/* canid：PF=0xFF */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		14u,			/* hoh：mb14（PF=0xFF 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_ID2,	/* rxInd */
		CANIF_RX_CAN1_ID2,
		0x18FF4D56u,			/* canid：PF=0xFF */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		14u,			/* hoh：mb14（PF=0xFF 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_ID3,	/* rxInd */
		CANIF_RX_CAN1_ID3,
		0x18FF4E56u,			/* canid：PF=0xFF */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		14u,			/* hoh：mb14（PF=0xFF 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_PEPS2,	/* rxInd */
		CANIF_RX_CAN1_PEPS2,
		0x18FF7534u,			/* canid：PF=0xFF */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		14u,			/* hoh：mb14（PF=0xFF 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_ESCL_NM,	/* rxInd */
		CANIF_RX_CAN1_ESCL_NM,
		0x18FF904Du,			/* canid：PF=0xFF */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		14u,			/* hoh：mb14（PF=0xFF 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_EEC3,	/* rxInd */
		CANIF_RX_CAN1_EEC3,
		0x18FFBA19u,			/* canid：PF=0xFF */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		14u,			/* hoh：mb14（PF=0xFF 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_ECC2,	/* rxInd */
		CANIF_RX_CAN1_ECC2,
		0x18FFBC19u,			/* canid：PF=0xFF */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		14u,			/* hoh：mb14（PF=0xFF 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_TP_DT,	/* rxInd */
		CANIF_RX_CAN1_TP_DT,
		0x1CEBFF21u,			/* canid：PF=0xEB */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		8u,			/* hoh：mb8（PF=0xEB 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_TP_CM,	/* rxInd */
		CANIF_RX_CAN1_TP_CM,
		0x1CECFF21u,			/* canid：PF=0xEC */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		9u,			/* hoh：mb9（PF=0xEC 段） */
	},
	{
		CanIfCfg_RxPduR_CAN1_ETC5,	/* rxInd */
		CANIF_RX_CAN1_ETC5,
		0x1CFEC321u,			/* canid：PF=0xFE */
		0x1FFFFFFFu,	/* mask：精确匹配，忽略源地址 */
		13u,			/* hoh：mb13（PF=0xFE 段） */
	},
};
/* @generated END: CAN1 real matrix */

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

	/* ---- M19：CAN1 真实矩阵的 6 条发送报文 ---- */
	/*
	 * @warning `hoh` 与 `CanHw_Hohs[]` 的 `msgBufId` 必须逐条对应
	 *          （HTH 6 → CAN1 mb2 … HTH 11 → CAN1 mb7）。
	 *          `Can_Write()` 会校验 `hoh->canId`，ID 写错会返回 `E_NOT_OK`；
	 *          但**邮箱号写错它发现不了**，只会发到别的邮箱上去。
	 */
	{
		CanIfCfg_TxPduR_CAN1_LCSF,        /* txConfirm */
		CANIF_TX_CAN1_LCSF,             /* txPduId */
		CAN_HW_ID_TX_LCSF,              /* canid：0x18FE4021 */
		NULL,                           /* p_canid */
		CAN_HW_HTH_CAN1_LCSF,           /* hoh：HTH 6 → CAN1 mb2 */
		CANIF_CHL_CAN1,                 /* ControllerId */
	},
	{
		CanIfCfg_TxPduR_CAN1_CTRL,
		CANIF_TX_CAN1_CTRL,
		CAN_HW_ID_TX_CTRL,              /* 0x18FF0C21 */
		NULL,
		CAN_HW_HTH_CAN1_CTRL,           /* HTH 7 → CAN1 mb3 */
		CANIF_CHL_CAN1,
	},
	{
		CanIfCfg_TxPduR_CAN1_OEL,
		CANIF_TX_CAN1_OEL,
		CAN_HW_ID_TX_OEL,               /* 0x0CFDCC21，P=3 */
		NULL,
		CAN_HW_HTH_CAN1_OEL,            /* HTH 8 → CAN1 mb4 */
		CANIF_CHL_CAN1,
	},
	{
		CanIfCfg_TxPduR_CAN1_OWW,
		CANIF_TX_CAN1_OWW,
		CAN_HW_ID_TX_OWW,               /* 0x18FDCD21 */
		NULL,
		CAN_HW_HTH_CAN1_OWW,            /* HTH 9 → CAN1 mb5 */
		CANIF_CHL_CAN1,
	},
	{
		CanIfCfg_TxPduR_CAN1_DOOR,
		CANIF_TX_CAN1_DOOR,
		CAN_HW_ID_TX_DOOR,              /* 0x18FE4E21 */
		NULL,
		CAN_HW_HTH_CAN1_DOOR,           /* HTH 10 → CAN1 mb6 */
		CANIF_CHL_CAN1,
	},
	{
		CanIfCfg_TxPduR_CAN1_DM1,
		CANIF_TX_CAN1_DM1,
		CAN_HW_ID_TX_DM1,               /* 0x18FECA21 */
		NULL,
		CAN_HW_HTH_CAN1_DM1,            /* HTH 11 → CAN1 mb7 */
		CANIF_CHL_CAN1,
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
 * @retval false 有项自身不合法，或有乱序
 *
 * @details 为什么需要它：`CanIf_RxDispatch()`（`CanIf.c:104`）用**二分查找**，
 *          但 C 语言没法在编译期检查"数组是否有序"，所以只能在初始化时验一遍。
 *
 *          检查两条：
 *          1. **每一项都落在自己的掩码区间内** —— `canid & mask == canid`。
 *             不满足时这条**永远匹配不上**（比较的是"掩码后的来帧 ID"与
 *             "原样存储的 canid"是否相等）。典型错法：写 `canid=0x18FF0100`
 *             却配 `mask=0x1FFF0000`，`0x18FF0100 & 0x1FFF0000 = 0x18FF0000`
 *             `!= 0x18FF0100`，于是静默失效。
 *          2. **全表按 `canid` 严格升序**（精确项与掩码项一起比）。
 *
 *          违反任何一条都**不会报错**，症状只是"某条报文收不到"。
 *          本工程真的踩过：加 J1939 报文时把 `0x18FF0001` 留在原位
 *          （排在 `0x18FExxxx` 之前），结果它自己收不到了，
 *          而新加的四条全正常 —— 看起来像"老功能被新配置破坏"。
 *
 * @note  **不检查"掩码区间是否重叠"**，这是刻意的：
 *        重叠与否取决于 `canid` 的**高位**，而掩码可能只覆盖低位。
 *        例如 CAN0 的 `0x0A0 + mask 0x7F8` 只匹配 11 位标准 ID 的 bit3~10，
 *        扩展帧 `0x18FF00A0` 的低 11 位同样是 `0x0A0` —— 按"区间重叠"
 *        判会报错，但实际运行完全正常（扩展帧由 J1939 段邮箱先收走）。
 *        写成通用检查会大量误报，反而把这个函数变成"永远在警告"的噪声。
 *        重叠由**表的设计者**保证，见各表顶部的注释。
 */
bool CanIfCfg_CheckRxOrder(void)
{
	const CanIf_CtrlConfigType *ctrl;
	const CanIf_RxPduType *p;
	uint16_t i;
	uint8_t c;

	for (c = 0u; c < CanIf_Config.numOfCtrls; c++) {
		ctrl = &CanIf_Config.CtrlConfigs[c];

		for (i = 0u; i < ctrl->numOfRxPdus; i++) {
			p = &ctrl->rxPdus[i];

			/* 1) 自身必须落在自己的掩码区间内 */
			if ((p->canid & p->mask) != p->canid) {
				return false;
			}

			/* 2) 与上一项严格升序（精确项和掩码项一起比） */
			if ((i > 0u) && (p->canid <= ctrl->rxPdus[i - 1u].canid)) {
				return false;
			}
		}
	}

	return true;
}
