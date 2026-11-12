/**
 * @file    can_test.c
 * @brief   CAN 周期发送 / 接收统计 / 总线故障记录（M2/M5/M14/M19）
 *
 * @details 从 `main.c` 整体迁出（M-Shell 命令迁移）：
 *          - `CanTest_*`：周期帧发送、接收排空、按 PDU 计数、突发/矩阵发送
 *          - `Fault_*`：bus-off 检测与故障快照
 *          - `CanTest_CmdExec`：旧 `!x` 单字符命令的完整分发（迁移期保留）
 *          - `App_CanIfRxIndication/App_CanIfTxConfirmation`：CanIf 回调
 *
 * @warning 回调运行在**中断上下文**：只拷贝与置标志，不得打印。
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "platform_cvm0146.h"
#include "can_test.h"

#include "Can.h"
#include "Can_Cfg.h"
#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "CanTp.h"
#include "Dcm.h"
#include "Dem.h"
#include "Dem_Cfg.h"
#include "PduR.h"
#include "NvM.h"        /* CanTest_Burst 里推进存储 */
#include "cmd/cmd_api.h"  /* 旧 !u/!v/!a/!d 等转调入口 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/* ============================ [ 全局 ] ============================ */

/** @brief 标准帧发送缓冲（内容每帧 +1，方便在 Kvaser 上看滚动） */
static uint8_t s_txData[8] = { 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u };

/** @brief CAN1 发送缓冲（首字节滚动，其余 C3 便于在总线上认出是 CAN1） */
static uint8_t s_tx1Data[8] = { 0u, 0xC3u, 0xC3u, 0xC3u, 0xC3u, 0xC3u, 0xC3u, 0xC3u };

/** @brief 扩展帧发送缓冲（首字节是滚动计数，其余填 A5 便于肉眼识别） */
static uint8_t s_extTxData[8] = { 0u, 0xA5u, 0xA5u, 0xA5u, 0xA5u, 0xA5u, 0xA5u, 0xA5u };

/** @brief 收到帧的暂存（中断写、主循环读） */
static volatile bool     s_rxFlag;
static volatile uint8_t  s_rxDlc;
static volatile PduIdType s_rxPduId;
static uint8_t           s_rxData[8];
static volatile uint32_t s_rxCount;

/**
 * @brief 按 **PDU 编号**分开的接收帧数（M14 压测）
 *
 * @details 存在的理由是硬件层计数**看不到软件过滤**：
 *          | 现象 | 含义 |
 *          |------|------|
 *          | 邮箱计数涨了、PDU 计数没涨 | CanIf 过滤表把帧丢了（表序 / 掩码 / canid 写错） |
 *          | 邮箱计数涨了、PDU 计数涨在别的项 | 过滤表区间重叠，帧被前一项截走 |
 *          | 两个都涨但数值不等 | 有一项被多个邮箱投递（重复配置） |
 *
 *          只验硬件计数时，这三类错**全部表现成"收到了"**，测不出来。
 *
 * @note 下标就是 `CANIF_RX_*`。诊断、NM、Com 三条走别的回调，
 *       在这里恒为 0 —— 那是正常的，不代表丢帧。
 */
static uint32_t s_rxPerPdu[CANIF_RX_PDU_NUM];

/** @brief 发送完成计数（CanIf 回调里累加） */
static volatile uint32_t s_txConfirmCount;

/* ============================ [ CanIf 回调 ] ============================ */

/**
 * @brief 收到一帧（由 `CanIf_Cfg.c` 的 rxInd 字段挂上来）
 *
 * @param[in] RxPduId     逻辑 PDU 号（`CANIF_RX_*`），**不是** CAN ID
 * @param[in] PduInfoPtr  净荷
 *
 * @warning 中断上下文：只拷贝与置标志，**不要打印**（`Platform_Printf` 是阻塞的）。
 * @note  M2 的关键变化：这个函数收到的 `RxPduId` 是**逻辑编号**，
 *        应用层再也看不到 0x321 / 0x18FF0001 这些报文细节 —— 这是分层的收益。
 */
void App_CanIfRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	uint8_t n;

	if ((PduInfoPtr == NULL) || (PduInfoPtr->SduDataPtr == NULL)) {
		return;
	}

	n = (PduInfoPtr->SduLength > 8u) ? 8u : (uint8_t)PduInfoPtr->SduLength;
	memcpy(s_rxData, PduInfoPtr->SduDataPtr, (size_t)n);
	s_rxDlc   = n;
	s_rxPduId = RxPduId;
	s_rxCount++;

	/* 压测计数（M14）：这是**软件过滤之后**的计数，
	 * 与平台层的按邮箱计数配合，才能区分"硬件没收到"和"软件丢了"。 */
	if (RxPduId < (PduIdType)CANIF_RX_PDU_NUM) {
		s_rxPerPdu[RxPduId]++;
	}

	s_rxFlag  = true;
}

/**
 * @brief 一帧发送完成
 * @note  当前只计数。M3 接 CanTp 后，这个回调是"分段发送可以发下一帧"的信号源。
 */
void App_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
	(void)TxPduId;
	if (E_OK == result) {
		s_txConfirmCount++;
	}
}

/* ============================ [ CAN 测试 ] ============================ */

/**
 * @brief 初始化 MCAL 并启动 CAN0（M2：走 CanIf）
 *
 * @details 顺序不能换：
 *          1) `Port_Init()` 配 MUX —— 没有 MUX 的 CAN 引脚只是普通 GPIO，
 *             控制器配好了也一个波形都发不出来，而且不会有任何报错；
 *          2) `Can_Init()` 只把状态置 STOPPED 并装载配置；
 *          3) `CanIf_Init()` 把控制器 PDU 模式置 `CANIF_OFFLINE`；
 *          4) `CanIf_SetControllerMode(STARTED)` → `Can_SetControllerMode` → `CanAc_Init`
 *             真正配置并启动控制器；
 *          5) `CanIf_SetTrcvMode(NORMAL)` 拉低 STB，收发器上总线；
 *          6) **`CanIf_SetPduMode(ONLINE)` 必须调用**，否则 `CanIf_Transmit()`
 *             里 `if (CANIF_ONLINE == context->PduMode)` 不成立，发送恒返回 E_NOT_OK，
 *             现象是"初始化全成功，就是一帧都发不出去"。
 *
 * @note AS 的 `Port_Init`/`Can_Init` 忽略入参（内部用 `Port_Config`/`Can_Config`），
 *       所以这里传 NULL；写 `&Port_Config` 反而要额外声明那个 const 全局。
 */
void CanTest_Init(void)
{
	/* ------------------------------------------------------------------
	 * 这里**不再手工初始化通信栈**。
	 *
	 * 初始化顺序已经搬到 `EcuM_Cfg.c` 的三张表里（Zero / One / Two），
	 * 由 `EcuM_Init()` / `EcuM_StartupTwo()` 按表执行；
	 * 控制器与 PDU 的启动交给 `ComM → CanSM → CanIf` 这条标准链路
	 * （由 `ecum_callout.c` 的 `EcuM_AL_EnterRUN()` 触发）。
	 *
	 * 之前这个函数里有 9 行 `Xxx_Init(NULL)` + 一个启动控制器的循环 ——
	 * 每加一个模块就要回来改一次，而且顺序靠注释约定、编译器管不了。
	 * 现在顺序就是表里的行序，加模块只改表。
	 * ------------------------------------------------------------------ */

	/* CAN1 仍然是「测试用通道」：没有 NM、没有 Com，不在 ComM/CanSM 管理之下，
	 * 所以它的控制器要在这里手动启动。CAN0 不在这里启动 —— 那是 CanSM 的职责，
	 * 手工再启动一次会和 CanSM 的 PRE_FULLCOM 状态机抢控制器。
	 *
	 * 将来 CAN1 也要接 Com/NM 时，正确做法是给 ComM 加一个通道、
	 * 给 CanSM 加一个 network，然后把这三行删掉。 */
	(void)CanIf_SetControllerMode(1u, CAN_CS_STARTED);
	(void)CanIf_SetTrcvMode(1u, CANTRCV_TRCVMODE_NORMAL);
	(void)CanIf_SetPduMode(1u, CANIF_ONLINE);

	Platform_Puts("  can   : CAN0 + CAN1, 500 kbps\n");
	Platform_Puts("          CAN0 TX 0x123/500ms + 0x18FF0002/1000ms (ext)\n");
	Platform_Puts("          CAN0 RX 0x321 + 0x18FF0001 (ext)\n");
	Platform_Puts("          CAN1 TX 0x124/500ms\n");
	Platform_Puts("          CAN1 RX 0x322\n");
	Platform_Puts("  diag  : 0x7E0 -> 0x7E8 (ISO-TP, 10 03 / 22 F1 90 / 3E 00)\n");
	Platform_Puts("  stack : EcuM -> ComM -> CanSM -> CanIf (0x500 NM / 0x200 Sig)\n");

	/* 接收过滤表自检：二分查找要求"按 canid 升序 + 掩码项在末尾"，
	 * 违反了不会报错、只会"某条报文收不到"。这里只打日志不阻断 ——
	 * 报文收不到已经够烦，不该连诊断都进不去。 */
	if (!CanIfCfg_CheckRxOrder()) {
		Platform_Puts("  [warn] CanIf RX 过滤表顺序非法（二分查找会漏项）\n");
	}
}

/**
 * @brief 诊断会话切换通知（Dcm 要求应用实现）
 * @param[in] sesActive 切换前的会话
 * @param[in] sesNew    切换后的会话
 * @param[in] timeout   TRUE = S3 超时自动回默认，FALSE = 测试仪主动请求
 *
 * @note  AS 的 `Dcm.c` / `Dcm_Dsp.c` 直接调这个函数，没有弱符号兜底，
 *        所以**不实现就链接失败**（`undefined reference to Dcm_SessionChangeIndication`）。
 *        实现里可以做事：切换会话时停掉非诊断报文、改波特率、切 NvM 的写入模式等。
 *        这里只打一行日志，方便串口侧确认 `10 03` 真的生效了。
 *
 * @warning 在 Dcm 的主函数上下文被调用，不要做阻塞操作。
 */
void Dcm_SessionChangeIndication(Dcm_SesCtrlType sesActive, Dcm_SesCtrlType sesNew,
                                 boolean timeout)
{
	Platform_Printf("[dcm] session %u -> %u (%s)\n",
	                (unsigned)sesActive, (unsigned)sesNew,
	                (TRUE == timeout) ? "S3 timeout" : "requested");
}

/**
 * @brief 执行一条 `!` 命令（控制面验证用）
 * @param[in] c 命令字符
 *
 * @details 这些命令存在的唯一目的，是让 PC 侧的验收脚本能驱动 CanIf 的
 *          **控制面**（PDU 模式 / 控制器模式 / 收发器模式），而不用改固件重烧。
 *          只用正常路径收发是验不出这些的，而 M3 的 CanTp 完全依赖它们：
 *          `CanTp` 在会话不活跃时靠 `CanIf_SetPduMode` 收窄收发，
 *          `CanSM` 靠 `SetControllerMode` 做 bus-off 恢复。
 *
 *          | 命令 | 动作 | 预期现象 |
 *          |------|------|----------|
 *          | `!o` | `SetPduMode(OFFLINE)` | 板上仍能收，但**发不出去**（总线上无 0x123） |
 *          | `!n` | `SetPduMode(ONLINE)`  | 恢复发送 |
 *          | `!s` | `SetControllerMode(STOPPED)` | 控制器停止，收发全停 |
 *          | `!g` | `SetControllerMode(STARTED)` | 重新配置并启动，收发恢复 |
 *          | `!t` | `SetTrcvMode(SLEEP)`   | STB 拉高，收发器待机，总线上彻底没帧 |
 *          | `!r` | `SetTrcvMode(NORMAL)`  | STB 拉低，恢复 |
 *
 * @note 每次动作后都**回读**真实状态（`GetPduMode` / `GetControllerMode`），
 *       而不是只信返回值 —— 返回值 OK 但状态没变，是这类中间件最常见的问题。
 */

/* 存储侧的 `!` 命令（d/c/w/x）实现在文件后半段，这里先声明。
 * 两侧共用 `!` 前缀但命令字符不重叠，改一边不会踩到另一边。 */

/* 故障表打印同理：实现在总线故障区，早于 main 但晚于 CmdExec */
void Fault_Dump(void);

/* 高频发送（`!f`）也在总线故障区，同样要前置声明 */
void CanTest_Burst(uint16_t n);
void CanTest_DumpRxCounters(void);
void CanTest_SendRealMatrix(void);


/* 信号层（M10）实现在"信号层"区，晚于 CmdExec */



/**
 * @brief 发送一帧递增数据（标准帧）
 * @note  数据每帧 +1，是为了在 Kvaser 上"看出它在动"，而不只是"确实有一帧"。
 * @note  M2 的关键变化：应用只说"发 TxPdu 0"，**不用关心它的 CAN ID 和邮箱号** ——
 *        这两样都在 `CanIf_Cfg.c` / `Can_Cfg.c` 里。改 ID 不用动应用。
 */
void CanTest_SendOne(void)
{
	PduInfoType pdu;
	uint8_t i;

	pdu.SduDataPtr = s_txData;
	pdu.SduLength  = 8u;
	pdu.MetaDataPtr = NULL;

	if (CanIf_Transmit((PduIdType)CANIF_TX_HEARTBEAT, &pdu) != E_OK) {
		Platform_Puts("  [can] CanIf_Transmit(heartbeat) failed\n");
		return;
	}

	for (i = 0u; i < 8u; i++) {
		s_txData[i]++;
	}
}

/**
 * @brief 发送一帧递增数据（CAN1 标准帧）
 * @note  CAN0 每帧把 8 个字节全部 +1；CAN1 只滚首字节，其余恒 C3 ——
 *        两种滚动方式在 Kvaser 上一眼能分辨是"哪个通道的哪条报文"。
 */
void CanTest_SendCan1(void)
{
	PduInfoType pdu;

	pdu.SduDataPtr = s_tx1Data;
	pdu.SduLength  = 8u;
	pdu.MetaDataPtr = NULL;

	if (CanIf_Transmit((PduIdType)CANIF_TX_CAN1_TEST, &pdu) == E_OK) {
		s_tx1Data[0]++;
	} else {
		Platform_Puts("  [can] CanIf_Transmit(CAN1) failed\n");
	}
}

/**
 * @brief 发一轮 CAN1 真实矩阵的 6 条报文（M19 验收用）
 *
 * @details 每条报文的**首字节放一个可区分的序号**（`0xA1`~`0xA6`），
 *          这样 Kvaser 侧抓到帧后能一眼看出"哪一条到了、哪一条没到"，
 *          不需要去比对 ID 表。
 *
 * @note  这 6 条目前**只从这里发**，还没接 Com。接 Com 之后应用应当
 *        改信号值、由 `Com_MainFunctionTx` 按周期发 —— 直接调
 *        `CanIf_Transmit()` 会绕过 Com 的打包与周期，等于把分层拆掉。
 *        现在这么做是为了**单独验证 Tx 链路**（hoh → 邮箱 → 引脚）。
 *
 * @warning CAN1 上必须**有另一个节点**（Kvaser）提供 ACK，否则
 *          TEC 会涨到 128 进入 error passive，之后 `Can_Write()` 返回
 *          `CAN_BUSY`，表现为"发不出去"。这不是配置错。
 */
void CanTest_SendRealMatrix(void)
{
	static const struct {
		PduIdType pdu;
		uint8_t   tag;
		const char *name;
	} tx[] = {
		{ (PduIdType)CANIF_TX_CAN1_LCSF, 0xA1u, "0x18FE4021 LCSF" },
		{ (PduIdType)CANIF_TX_CAN1_CTRL, 0xA2u, "0x18FF0C21 CTRL" },
		{ (PduIdType)CANIF_TX_CAN1_OEL,  0xA3u, "0x0CFDCC21 OEL " },
		{ (PduIdType)CANIF_TX_CAN1_OWW,  0xA4u, "0x18FDCD21 OWW " },
		{ (PduIdType)CANIF_TX_CAN1_DOOR, 0xA5u, "0x18FE4E21 DOOR" },
		{ (PduIdType)CANIF_TX_CAN1_DM1,  0xA6u, "0x18FECA21 DM1 " },
	};
	PduInfoType pdu;
	uint8_t     data[8];
	uint8_t     i;
	uint8_t     j;
	uint8_t     okCount = 0u;

	/* 每条发 3 次：一帧也可能因为仲裁/总线错误丢掉，重复发便于肉眼核对 */
	for (i = 0u; i < (uint8_t)ARRAY_SIZE(tx); i++) {
		for (j = 0u; j < 8u; j++) {
			data[j] = (uint8_t)(tx[i].tag + j);
		}

		pdu.SduDataPtr  = data;
		pdu.SduLength   = 8u;
		pdu.MetaDataPtr = NULL;

		if (CanIf_Transmit(tx[i].pdu, &pdu) == E_OK) {
			okCount++;
			Platform_Printf("   tx %s  tag=0x%02X  ok\n",
			                tx[i].name, (unsigned)tx[i].tag);
		} else {
			Platform_Printf("   tx %s  **E_NOT_OK**（CAN1 无 ACK？）\n",
			                tx[i].name);
		}
	}

	Platform_Printf("   %u / %u sent\n", (unsigned)okCount,
	                (unsigned)ARRAY_SIZE(tx));
}

/**
 * @brief 发送一帧扩展帧（29 位，0x18FF0002）
 * @note  单独一条，用来证明"同一个 CanIf 能同时带标准帧和扩展帧"，
 *        而且扩展帧不需要应用做任何特殊处理 —— 标志位在配置表里。
 */
void CanTest_SendExt(void)
{
	PduInfoType pdu;

	pdu.SduDataPtr = s_extTxData;
	pdu.SduLength  = 8u;
	pdu.MetaDataPtr = NULL;

	if (CanIf_Transmit((PduIdType)CANIF_TX_EXT_TEST, &pdu) == E_OK) {
		s_extTxData[0]++;
	} else {
		Platform_Puts("  [can] CanIf_Transmit(ext) failed\n");
	}
}

/**
 * @brief PDU 编号 → 人类可读名称（下标必须与 `CANIF_RX_*` 一一对应）
 *
 * @note  放文件级而不是函数内：`CanTest_DrainRx()` 打印单帧、
 *        `CanTest_DumpRxCounters()` 打印按 PDU 的计数，两处都要用。
 * @note  长度由 `CANIF_RX_PDU_NUM` 约束 —— 少写一条会直接编译不过。
 *        这比运行期打印成 `?` 好：`?` 和"收到未知 PDU"在现象上分不开，
 *        会让人误判成过滤器配错。
 * @note  诊断请求（PDU 4）与 NM（PDU 10）、Com（PDU 11）都不走
 *        `App_CanIfRxIndication`，名称只是占位。
 */
static const char *const s_pduName[CANIF_RX_PDU_NUM] = {
	"CAN0 0x321",           /* 0  CANIF_RX_TEST */
	"CAN0 0x18FF0001(ext)", /* 1  CANIF_RX_EXT_TEST */
	"CAN1 0x322",           /* 2  CANIF_RX_CAN1_TEST */
	"CAN1 0x18FF01xx(ext)", /* 3  CANIF_RX_CAN1_PGN */
	"CAN0 0x7E0(diag)",     /* 4  CANIF_RX_DIAG_REQ */
	"CAN0 0x18FF01xx(ext)", /* 5  CANIF_RX_J1939_PGN（灯光） */
	"CAN0 0x18FEF1xx(ext)", /* 6  CANIF_RX_J1939_A（车速） */
	"CAN0 0x18FEC1xx(ext)", /* 7  CANIF_RX_J1939_B */
	"CAN0 0x18FEB1xx(ext)", /* 8  CANIF_RX_J1939_C */
	"CAN0 0x18FEA1xx(ext)", /* 9  CANIF_RX_J1939_D */
	"CAN0 0x500(NM)",       /* 10 CANIF_RX_NM（不走本回调，占位） */
	"CAN0 0x201(com)",      /* 11 CANIF_RX_COM_TEST（不走本回调，占位） */
	"CAN0 0x0A0~A7",        /* 12 CANIF_RX_STD_FAST */
	"CAN0 0x100~107",       /* 13 CANIF_RX_STD_LIGHT */
	"CAN0 0x110",           /* 14 CANIF_RX_STD_BODY */
	"CAN0 0x18FF00xx(ext)", /* 15 CANIF_RX_J1939_VEH（预留） */
	"CAN0 0x18FF02xx(ext)", /* 16 CANIF_RX_J1939_DOOR */
	"CAN0 0x18FF03xx(ext)", /* 17 CANIF_RX_J1939_WIPER */
	"CAN0 0x18FF04xx(ext)", /* 18 CANIF_RX_J1939_MULTI */
	"CAN0 0x18FF05xx(ext)", /* 19 CANIF_RX_J1939_ALARM */
	"CAN0 0x18FF06xx(ext)", /* 20 CANIF_RX_J1939_FAST */
	"CAN0 0x18FEE0xx(ext)", /* 21 CANIF_RX_J1939_ODO */
	"CAN0 0x18FFFF00(ext)", /* 22 CANIF_RX_J1939_MAXID（段内最大 PGN） */

	/* ---- M19：CAN1 真实矩阵（23~56），编号见 CanIf_Cfg.h ---- */
	"CAN1 0x8CF00400 EEC1",	/* 23 */
	"CAN1 0x8CFD9200 EOI",	/* 24 */
	"CAN1 0x8CFE6CEE TCO1",	/* 25 */
	"CAN1 0x90FFB04D ESCL1",	/* 26 */
	"CAN1 0x90FFB24D ESCLM",	/* 27 */
	"CAN1 0x90FFB634 PEPS",	/* 28 */
	"CAN1 0x94F02B54 CRASH",	/* 29 */
	"CAN1 0x98EEFF00 ACL",	/* 30 */
	"CAN1 0x98F00000 ERC3",	/* 31 */
	"CAN1 0x98F0000F ERC1",	/* 32 */
	"CAN1 0x98F0010B EBC1",	/* 33 */
	"CAN1 0x98F00503 ETC2",	/* 34 */
	"CAN1 0x98FD0700 DLCC1",	/* 35 */
	"CAN1 0x98FDC40B EBC5",	/* 36 */
	"CAN1 0x98FE4F0B VDC1",	/* 37 */
	"CAN1 0x98FECA33 DM1",	/* 38 */
	"CAN1 0x98FEF100 CCVS1",	/* 39 */
	"CAN1 0x98FEF121 CCVS",	/* 40 */
	"CAN1 0x98FEF433 TIRE",	/* 41 */
	"CAN1 0x98FEF500 AMB",	/* 42 */
	"CAN1 0x98FF0534 PEPS1",	/* 43 */
	"CAN1 0x98FF0917 IC",	/* 44 */
	"CAN1 0x98FF0CEC DW",	/* 45 */
	"CAN1 0x98FF12EF VCU",	/* 46 */
	"CAN1 0x98FF4C56 ID1",	/* 47 */
	"CAN1 0x98FF4D56 ID2",	/* 48 */
	"CAN1 0x98FF4E56 ID3",	/* 49 */
	"CAN1 0x98FF7534 PEPS2",	/* 50 */
	"CAN1 0x98FF904D ESCL",	/* 51 */
	"CAN1 0x98FFBA19 EEC3",	/* 52 */
	"CAN1 0x98FFBC19 ECC2",	/* 53 */
	"CAN1 0x9CEBFF21 TP",	/* 54 */
	"CAN1 0x9CECFF21 TP",	/* 55 */
	"CAN1 0x9CFEC321 ETC5",	/* 56 */
};

/**
 * @brief 把收到的帧打印出来（主循环里调用，不在中断里）
 *
 * @note  打印的是**逻辑 PDU 号**而不是 CAN ID —— 这是 M2 之后的正常形态：
 *        应用看到的是"哪个 PDU"，不是"哪条报文"。报文 ID 归 CanIf 配置管。
 */
void CanTest_DrainRx(void)
{
	const char *name;
	uint8_t i;

	if (!s_rxFlag) {
		return;
	}
	s_rxFlag = false;

	name = (s_rxPduId < (PduIdType)ARRAY_SIZE(s_pduName)) ? s_pduName[s_rxPduId] : "?";

	Platform_Printf("[can] rx #%u pdu=%u (%s) dlc=%u data=",
	                (unsigned)s_rxCount, (unsigned)s_rxPduId, name,
	                (unsigned)s_rxDlc);
	for (i = 0u; i < s_rxDlc; i++) {
		Platform_Printf("%02x ", (unsigned)s_rxData[i]);
	}
	Platform_Puts("\n");
}

/* ============================ [ 总线故障（M5） ] ============================ */

/**
 * @brief 高频连续发送 N 帧（`!f`）
 *
 * @details 存在的理由只有一个：**把节点推到 bus-off 去做验收**。
 *
 *          直觉上"对端不应答"应该能造出 bus-off，但实测不行 ——
 *          节点到 error passive（TEC≥128）后，ISO 11898-1 规定
 *          **ACK 错误不再累加 TEC**，于是 TEC 永远卡在 128，永远进不了 bus-off。
 *          这是协议设计（防止一个孤立节点把自己锁死），不是芯片 bug。
 *
 *          能推过 256 的只有"硬错误"：位错误、格式错误、填充错误。
 *          制造方式是对端用同一个 ID 发**不同数据**：
 *          仲裁段全一致，数据段必然出现"我发隐性、读回显性"，
 *          发送方据此判定位错误，TEC += 8。
 *
 * @param[in] n 帧数
 * @note  帧间隔 10 ms：太快会互相覆盖同一个邮箱（`Can_Write` 对同一 HTH
 *        是覆盖语义），反而没机会在总线上参与仲裁。
 */
/**
 * @brief 打印 CAN 接收计数（M14 压测用）
 *
 * @details 三个数字一起看才能定位：
 *          | 现象 | 含义 |
 *          |------|------|
 *          | total < 对端发送数 | **硬件层**丢：掩码没放行 / 邮箱满 / 总线错误 |
 *          | total 正常但应用没看到 | **CanIf 软件过滤**丢了：表序或掩码错 |
 *          | perIsr ≈ 1.0 | 每次中断只处理 1 帧，中断开销最大 |
 *          | perIsr 明显 > 1 | 多帧积压后一起处理，说明主循环有延迟 |
 *
 * @note 按邮箱分开打印的原因：压测时"总数对得上但某一条总丢"很常见，
 *       这时只有看到具体是哪个 mb 少了，才能判断是哪个掩码区间有问题。
 */
void CanTest_DumpRxCounters(void)
{
	uint8_t ch;
	uint8_t mb;

	Platform_Puts("  can rx counters  (m = mailbox)\n");
	for (ch = 0u; ch < CAN_CFG_NUM_CHANNELS; ch++) {
		uint32_t total = Platform_CanRxTotal(ch);
		uint32_t isr = Platform_CanIsrCount(ch);
		uint32_t perInt = (isr != 0u) ? (total / isr) : 0u;
		uint32_t frac = (isr != 0u) ? ((total * 100u / isr) % 100u) : 0u;

		Platform_Printf("   CAN%u  total=%-6u isr=%-6u perISR=%u.%02u\n",
		                (unsigned)ch, (unsigned)total, (unsigned)isr,
		                (unsigned)perInt, (unsigned)frac);

		for (mb = 0u; mb < 18u; mb++) {
			uint32_t n = Platform_CanRxByMb(ch, mb);

			if (n != 0u) {
				Platform_Printf("     mb%-2u = %u\n", (unsigned)mb, (unsigned)n);
			}
		}
	}

	/* 软件过滤之后的计数（M14）。
	 * 与上面的按邮箱计数对照，就能判断 CanIf 有没有把帧丢掉或投错项：
	 *   邮箱有、PDU 没有 → 过滤表的 canid/mask 与硬件段不一致
	 *   邮箱有、PDU 有但落在别的编号 → 表项区间重叠，被前一项截走 */
	Platform_Puts("  pdu rx counters  (after CanIf software filter)\n");
	{
		uint8_t pdu;

		for (pdu = 0u; pdu < (uint8_t)CANIF_RX_PDU_NUM; pdu++) {
			if (s_rxPerPdu[pdu] != 0u) {
				Platform_Printf("     pdu %-2u = %-6u %s\n",
				                (unsigned)pdu, (unsigned)s_rxPerPdu[pdu],
				                s_pduName[pdu]);
			}
		}
	}
}

void CanTest_Burst(uint16_t n)
{
	uint16_t i;
	uint32_t t0;
	uint32_t done = 0u;

	for (i = 0u; i < n; i++) {
		CanTest_SendOne();
		done++;

		/* 忙等 10 ms，但期间照常推进存储引擎，
		 * 否则一次 burst 会把 NvM 的作业卡住 1 秒 */
		t0 = Platform_NowMs();
		while ((uint32_t)(Platform_NowMs() - t0) < 10u) {
			NvM_MainFunction();
		}
	}

	Platform_Printf("[can] burst %u frames sent\n", (unsigned)done);
}

/**
 * @brief bus-off 之后复查硬件是否已自行恢复的等待时间（ms）
 * @details FlexCAN 的自动恢复要等 128×11 个**隐性位**。500 kbps 下约 2.8 ms，
 *          但总线可能一直有干扰源在制造显性位 —— 那种情况下永远等不到。
 *          200 ms 足够覆盖正常恢复，又不会让"真故障"拖太久才兜底。
 */
#define BUSOFF_RECOVER_MS       (200u)

/** @brief 各通道上一次看到的 bus-off 计数（用来识别"有新事件"） */
static uint16_t s_lastBusOffCnt[CAN_CFG_NUM_CHANNELS];

/** @brief 各通道最近一次 bus-off 的时刻（ms） */
static uint32_t s_busOffAtMs[CAN_CFG_NUM_CHANNELS];

/** @brief 各通道是否在等"硬件自动恢复"的复查 */
static bool s_busOffPending[CAN_CFG_NUM_CHANNELS];

/**
 * @brief 轮询 bus-off：检测 → 记录 → 复查硬件是否已恢复（主循环里调用）
 *
 * @details 三段逻辑：
 *          1. **检测**：比较平台层的累计计数与上次看到的值。
 *             中断只 +1，这里才是唯一做决策的地方（中断里不做业务）。
 *          2. **记录**：`Dem_SetEventStatusWithMonitorData()` —— 把"CANx 故障"
 *             连同现场快照交给 Dem，它负责累加次数、分配槽位、落盘。
 *          3. **复查**：等 `BUSOFF_RECOVER_MS` 后看 `FLTCONF` 有没有回到 error-active。
 *
 * @note  **恢复动作刻意不做软件重启**，这是个踩过的坑，不是偷懒：
 *
 *        FlexCAN 的 `CTRL1.BOFFREC = 0`（厂商 `SetBusOffRecEnable(true)` 写的正是这个值，
 *        注意 FlexCAN 里 **0 才是自动恢复使能**，1 是禁止）保证硬件在 128×11 个隐性位后
 *        自己回到 error-active，所以软件不需要介入。
 *
 *        而"软件兜底重启"在本平台**实测有害**：`Can_SetControllerMode(STOPPED→STARTED)`
 *        会走 `CanAc_DeInit`(SoftReset) → `CanAc_Init`(Configure)，
 *        实测二次 Configure 之后控制器不再发送任何帧
 *        （`ESR1.IDLE=1`、`TEC=0`、`CanIf_Transmit` 仍返回 E_OK，
 *        表现为"总线安静得像没配置过"，且 `waitFailed` 为 0 —— 不是超时退出）。
 *        也就是说：一次 bus-off 触发软件重启，会把"能自己好的控制器"变成"永久哑掉"。
 *        这比不恢复严重得多，所以这里只告警，把决定权留给上层业务。
 *
 * @note  真要做硬恢复，可靠手段是整机 `NVIC_SystemReset()`（EcuM 级别的恢复），
 *        而不是在运行期重新 Configure 外设。等 M6 接 EcuM 时再走那条路。
 */
void Fault_PollBusOff(void)
{
	Can_BusOffInfoType info;
	uint8_t ch;

	for (ch = 0u; ch < (uint8_t)CAN_CFG_NUM_CHANNELS; ch++) {
		/* --- 1) 新事件？ --- */
		if (CanAc_GetBusOffInfo(ch, &info)) {
			if (info.count != s_lastBusOffCnt[ch]) {
				s_lastBusOffCnt[ch] = info.count;
				s_busOffAtMs[ch] = Platform_NowMs();
				s_busOffPending[ch] = true;

				/* 只记第一次的现场。后续的 errBits 往往被前一次的恢复过程污染
				 * （恢复期间 ACK/位错误会继续累加），拿它当根因会误判 */
				if (info.count == 1u) {
					(void)Dem_SetEventStatusWithMonitorData(
						(ch == 0u) ? DEM_CFG_EVENT_CAN0_BUSOFF : DEM_CFG_EVENT_CAN1_BUSOFF,
						DEM_EVENT_STATUS_FAILED,
						(Dem_MonitorDataType)info.errBits,
						(Dem_MonitorDataType)info.fltConf);
					Platform_Printf("[can] BUS-OFF ch%u flt=%u err=0x%02x%s%s%s%s\n",
					                (unsigned)ch, (unsigned)info.fltConf,
					                (unsigned)info.errBits,
					                ((info.errBits & CAN_BUSOFF_ERR_ACK) != 0u) ? " ack" : "",
					                ((info.errBits & CAN_BUSOFF_ERR_BIT0) != 0u) ? " bit0" : "",
					                ((info.errBits & CAN_BUSOFF_ERR_CRC) != 0u) ? " crc" : "",
					                ((info.errBits & CAN_BUSOFF_ERR_STUFF) != 0u) ? " stuff" : "");
				} else {
					Platform_Printf("[can] BUS-OFF ch%u again (#%u), recovery check pending\n",
					                (unsigned)ch, (unsigned)info.count);
				}
			}
		}

		/* --- 2) 到点复查硬件是否已自行恢复 --- */
		if (s_busOffPending[ch] &&
		    ((uint32_t)(Platform_NowMs() - s_busOffAtMs[ch]) >= (uint32_t)BUSOFF_RECOVER_MS)) {
			s_busOffPending[ch] = false;

			if (CanAc_IsBusOff(ch)) {
				/* 还在 bus-off：说明总线上一直有显性位压着（短路 / 其它节点持续错误帧），
				 * 这种物理故障靠重启控制器解决不了，只能报出去让人查线束。 */
				Platform_Printf("[can] ch%u 仍在 bus-off（%u ms），硬件自动恢复未生效，"
				                "请检查线束\n",
				                (unsigned)ch,
				                (unsigned)(Platform_NowMs() - s_busOffAtMs[ch]));
			} else {
				Platform_Printf("[can] ch%u bus-off 已由硬件自动恢复（%u ms）\n",
				                (unsigned)ch,
				                (unsigned)(Platform_NowMs() - s_busOffAtMs[ch]));
			}
		}
	}
}

/**
 * @brief 打印 DTC 表（`!b`）
 *
 * @note  输出格式照 UDS 0x19 的响应布局排：`DTC 三字节 + 状态字节`，
 *        后面再补 `cnt / boot / 现场快照` 这些串口才有的信息。
 *        诊断仪读到的和这里看到的必须是同一份数据 —— 因为两者
 *        走的是同一个后端（`Dem_GetNextFilteredDTC` 与 `Dem_GetRecordByIndex`
 *        读的是同一张表）。
 *
 * @note  `st` 是 8 位 UDS 状态字节，位含义见 ISO 14229-1 附录 D.3：
 *        `0x09` = TF(at) + CDTC，`0xAF` = 全套（本工程首次失败就置这些位）。
 */
void Fault_Dump(void)
{
	Dem_DtcInfoType rec;
	uint8_t n = 0u;
	uint8_t i;

	/* 先数一遍：表头要打"几条"，而 Dem 的遍历接口是单向游标，不能回头 */
	while ((n < 0xFFu) && Dem_GetRecordByIndex(n, &rec)) {
		n++;
	}

	Platform_Printf("[dtc] %u 条已记录（容量 %u）\n",
	                (unsigned)n, (unsigned)Dem_GetDtcCapacity());
	if (n == 0u) {
		Platform_Puts("[dtc] 无故障\n");
		return;
	}

	for (i = 0u; i < n; i++) {
		if (!Dem_GetRecordByIndex(i, &rec)) {
			break;
		}
		Platform_Printf("[dtc] %u: %06X ch=%u st=0x%02x cnt=%u boot #%u..#%u"
		                " err=0x%02x flt=%u\n",
		                (unsigned)i, (unsigned)rec.dtcCode,
		                (unsigned)rec.channel, (unsigned)rec.status,
		                (unsigned)rec.occurCount,
		                (unsigned)rec.firstBoot, (unsigned)rec.lastBoot,
		                (unsigned)rec.errBits, (unsigned)rec.fltConf);
	}
}


/**
 * @brief 清零接收计数（旧 `!K`）
 * @details 邮箱计数与按 PDU 计数一起清 —— 只清一半会让下一步对不上。
 */
void CanTest_ClearCounters(void)
{
	uint8_t pdu;

	Platform_CanResetRxCounters();
	for (pdu = 0u; pdu < (uint8_t)CANIF_RX_PDU_NUM; pdu++) {
		s_rxPerPdu[pdu] = 0u;
	}
	Platform_Puts("  can rx counters cleared (mailbox + pdu)\n");
}

/**
 * @brief 发送完成累计数（心跳打印用）
 */
uint32_t CanTest_GetTxOk(void)
{
	return s_txConfirmCount;
}

/**
 * @brief 旧 `!x` 单字符命令分发（迁移期，与 cmd/can_cmd.c 共用同一批实现）
 * @param[in] c 命令字符
 */
void CanTest_CmdExec(char c)
{
	Std_ReturnType rc = E_OK;
	Can_ControllerStateType ctrlMode = CAN_CS_UNINIT;
	CanIf_PduModeType pduMode = CANIF_OFFLINE;

	switch (c) {
	case 'o':
		rc = CanIf_SetPduMode(0u, CANIF_OFFLINE);
		break;
	case 'n':
		rc = CanIf_SetPduMode(0u, CANIF_ONLINE);
		break;
	case 's':
		rc = CanIf_SetControllerMode(0u, CAN_CS_STOPPED);
		break;
	case 'g':
		rc = CanIf_SetControllerMode(0u, CAN_CS_STARTED);
		break;
	case 't':
		rc = CanIf_SetTrcvMode(0u, CANTRCV_TRCVMODE_SLEEP);
		break;
	case 'r':
		rc = CanIf_SetTrcvMode(0u, CANTRCV_TRCVMODE_NORMAL);
		break;
	case 'b':
		/* 看故障快照表 —— 不需要动 CAN 控制面，直接返回 */
		Fault_Dump();
		return;
	case 'B':
		/* 清故障码：走 0x14 的同一条后端路径（Dem_SelectDTC + Dem_ClearDTC），
		 * 不是绕过协议直接抹表 —— 这样串口命令和 UDS 命令的结果必然一致，
		 * 不会出现"串口清掉了、诊断仪还读得到"这种两套行为。 */
		if ((Dem_SelectDTC(0u, 0x00FFFFFFu, DEM_DTC_FORMAT_UDS,
		                   DEM_DTC_ORIGIN_PRIMARY_MEMORY) == E_OK) &&
		    (Dem_ClearDTC(0u) == E_OK)) {
			Platform_Puts("[dtc] cleared via Dem_ClearDTC (write when engine idle)\n");
		} else {
			Platform_Puts("[dtc] clear FAILED\n");
		}
		return;
	case 'i':
		/* 故障注入：直接喂一条 bus-off 记录给故障表。
		 *
		 * **为什么需要注入而不是真造一次 bus-off：**
		 * 单节点实验室造不出 bus-off，这不是配置问题，是 CAN 协议本身：
		 *   ① 对端不应答（最直觉的路径）只能把 TEC 推到 128（error passive），
		 *      ISO 11898-1 §7.1.3 规定 error passive 下 **ACK 错误不再累加 TEC**，
		 *      于是 TEC 死死卡在 128，永远到不了 256 的 bus-off 门槛；
		 *   ② 想越过 128 只能靠位错误/格式错误，需要对端用**同一 ID、不同数据**
		 *      精确地同时发送。实测用 Kvaser 连发 1.7 万帧去撞，TEC 只涨到 1~7
		 *      —— 要么对端赢仲裁（板子根本没发），要么板子发完（对端没撞上）。
		 *
		 * 所以走故障注入验证**链路**（记录 → 分配槽位 → 落盘 → 掉电保持），
		 * 这比"造不出就不验"实在。真实 bus-off 的触发条件已在
		 * `CanAc_OredIsr()` 里由硬件保证，中断路径本身用 `!e` 看 BOFFMSK/BOFFINT 可查。
		 */
		if (Dem_SetEventStatusWithMonitorData(DEM_CFG_EVENT_CAN0_BUSOFF,
		                                      DEM_EVENT_STATUS_FAILED,
		                                      (Dem_MonitorDataType)CAN_BUSOFF_ERR_ACK,
		                                      2u) == E_OK) {
			Platform_Puts("[dtc] injected: CAN0 bus-off (ack error), see !b\n");
		} else {
			Platform_Puts("[dtc] inject FAILED (Dem 未初始化?)\n");
		}
		return;
	case 'e':
		/* 寄存器现场：TEC/REC 有没有涨、BOFFMSK 开没开、当前 FLTCONF */
		CanAc_DbgDump(0u);
		return;
	case 'k':
		CanTest_DumpRxCounters();
		return;
	case 'K':
		CanTest_ClearCounters();
		return;
	case 'u':
		/* 旧入口（m11/m12 脚本仍用）：RUN → POST_RUN */
		EcumCmd_RequestPostRun();
		return;
	case 'U':
		EcumCmd_RequestRun();
		return;
	case 'q':
		EcumCmd_Mode();
		return;
	case 'z':
		EcumCmd_SleepOnce();
		return;
	case 'M':
		/* CAN1 真实矩阵发送（M19）：6 条报文各发一次，首字节 0xA1~0xA6。
		 * Kvaser 挂在 CAN1 上才能收到（也需要它提供 ACK）。 */
		CanTest_SendRealMatrix();
		return;
	case 'v':
		/* 旧入口（m10 脚本仍用）：信号 dump */
		ComCmd_DumpSignals();
		return;
	case 'y':
		ComCmd_GroupToggle();
		return;
	case 'a':
		/* 旧入口（m9 脚本仍用）：请求网络 */
		NmCmd_Request();
		return;
	case 'A':
		NmCmd_PassiveStartup();
		return;
	case 'R':
		NmCmd_Release();
		return;
	case 'm':
		NmCmd_DumpState();
		return;
	case 'f':
		/* 高频发 100 帧（10 ms 间隔），配合 Kvaser 侧同 ID 冲突帧制造位错误。
		 * 为什么需要它：ACK 错误在 error passive 状态下**不再累加 TEC**
		 * （ISO 11898-1 §7.1.3 的特殊规则），所以"对端不应答"这条最直觉的
		 * 路径根本到不了 bus-off —— 必须靠位错误/格式错误这类硬错。 */
		CanTest_Burst(100u);
		return;
	case 'd':
		/* 旧入口（m4 脚本仍用）：块状态 dump */
		StorageCmd_Dump();
		return;
	case 'c':
		StorageCmd_WriteAll();
		return;
	case 'w':
		StorageCmd_Touch();
		return;
	case 'x':
		StorageCmd_Illegal();
		return;
	case 'p':
		StorageCmd_Stress();
		return;
	default:
		Platform_Printf("[cmd] unknown '%c'\n", c);
		return;
	}

	(void)CanIf_GetPduMode(0u, &pduMode);
	(void)CanIf_GetControllerMode(0u, &ctrlMode);
	Platform_Printf("[cmd] %c rc=%u pduMode=%u ctrlMode=%u\n",
	                c, (unsigned)rc, (unsigned)pduMode, (unsigned)ctrlMode);
}
