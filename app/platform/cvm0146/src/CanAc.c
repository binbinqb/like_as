/**
 * @file    CanAc.c
 * @brief   Can 驱动的平台访问层（AUTOSAR CanAc → 厂商 FlexCanDrv）
 *
 * @details @section CANAC_SCOPE 这一层为什么比 Port/Dio 重得多
 *          AS 的 `infras/mcal/Can/Can.c` 只有 198 行，只做状态机与 DET 校验，
 *          **连 `Can_Write` 都没有实现** —— 整个"发一帧、收一帧"都留给平台。
 *          所以本文件必须自己补上 AUTOSAR 的 `Can_Write()`，并接中断把收到的帧
 *          交出去。这是读 AS 源码时最容易误判的一点：
 *          搜遍 `infras` 只有 `Can_Write` 的声明和调用者，没有定义。
 *
 *          本文件提供：
 *          | 接口 | 归属 | 说明 |
 *          |------|------|------|
 *          | `CanAc_GlobalInit/DeInit` | AS 声明 | 两路共用的一次性初始化（M1 空实现） |
 *          | `CanAc_Init/DeInit/SetSleepMode` | AS 声明 | 配置并启动控制器 |
 *          | `CanAc_SetupPinMode/WritePin` | AS 声明 | `USE_PORT` 下不调用，保留桩 |
 *          | `Can_Write` | **AUTOSAR 标准，AS 未实现** | 由 HOH 表 + 固定 ID 邮箱发出 |
 *
 *          @section CANAC_M2 M2 改动：收帧出口从"弱符号回调"改成"直接交给 CanIf"
 *          M1 用的是 `CanAc_RxIndication()` 弱符号，由应用覆盖后打到串口 —— 那是为了
 *          单独验证 MCAL。M2 起走 AUTOSAR 正规路径：
 *          @code
 *          CAN 中断 → CanAc_RxIsr() → 填 Can_HwType + PduInfoType
 *                   → CanIf_RxIndication() → CanIf_Cfg 里的 rxInd 回调 → 应用
 *          @endcode
 *          好处是**分发逻辑（ID 过滤、多路复用）离开平台层**，
 *          平台层只负责"把硬件帧翻译成 AS 的抽象结构"。
 *
 *          @section CANAC_HOH 硬件对象（HOH）为什么由平台定义
 *          AUTOSAR 里 `Can_Write(Hth, ...)` 的 `Hth` 是"硬件发送对象句柄"，
 *          它的定义完全依赖芯片邮箱布局，AS 的 `Can_ChannelConfigType` 里没有任何邮箱信息。
 *          所以这里用 `CanHw_Hohs[]` 表把 Hth 映射到"控制器 + 邮箱号 + 帧 ID"。
 *
 *          @warning **一个 HTH 只能发一个固定 ID**。厂商 `FlexCanDrv_SetTxMsg()`
 *          （`flexcan_drv.c:1494`）只写数据区，**不回写 ID，也不回写 DLC** ——
 *          这两者在 `FlexCanDrv_CfgMsgObj()` 时就烧进邮箱了，运行期改不了。
 *          所以 N 条 TX 报文就要有 N 个 HTH + N 个邮箱。
 *          CAN0 资源：`canRamNum=3`、单邮箱 16 B → `MCR[MAXMB]=96`。
 *          @warning `MAXMB` 只是**软件上限**，不代表硅片真的实现了 96 个。
 *          本工程只实测验证到 mb15 可用（mb16/17 曾因掩码问题收不到帧，
 *          那条路径没排除干扰），所以配表时**优先用低位邮箱**，
 *          别把关键报文放到 mb16 以上。
 *
 *          @section CANAC_BUSOFF Bus-off 检测为什么要单独做
 *          FlexCAN 的 `BOFFREC=1`（SDK 的 `FlexCanDrv_Configure` 无条件打开）
 *          让硬件在检测到 128×11 个隐性位后**自己回到 error-active**。
 *          这容易让人以为"bus-off 不需要管了"，但实际有三个问题它没解决：
 *
 *          1. **上层不知道发生过**。bus-off 期间被 abort 的 TX 报文永远不会产生
 *             `CanIf_TxConfirmation`，CanTp 只能靠 N_As 超时兜底；诊断侧更是一无所知，
 *             故障码无从记录。
 *          2. **进入瞬间的状态无法回溯**。`ESR1` 的 `FLTCONF` 在恢复后就回到 0，
 *             "到底是 ACK 错还是位错"只有中断里那一瞬间能读到。
 *          3. **反复 bus-off 等于总线瘫痪**。没有计数就无法区分"偶发一次"和"线束短路"。
 *
 *          所以这里开 `BOFFMSK`，在 `CANx_ORed_Handler` 里第一次发生时就抓现场
 *          （FLTCONF + ACK/位/CRC 错误标志）并计数，再把 `CanIf_ControllerBusOff()`
 *          报上去。**恢复动作不放中断里** —— 中断只记录，恢复由上层按 AUTOSAR
 *          的 CanSM 时序做（本项目暂无 CanSM，恢复策略见 `main.c` 的 `Fault_PollBusOff`）。
 *
 *          @warning **OR'ed 中断必须三个源都清**。`CANx_ORed` 是
 *          `BusOff OR TxWarning OR RxWarning` 的或，只要有一个标志挂着就一直重进中断。
 *          本工程不开告警中断（`warningIntEnable=false`），但清零仍然要做 ——
 *          否则将来谁把告警打开，现象会是" interrupts 打满 CPU、主循环完全不跑"。
 *
 * @author  binbina
 * @version V1.3.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：CAN0 500k，1 发 1 收，中断收帧 |
 * | V1.1.0 | 2026-11-10 | binbina | 邮箱表迁到 `Can_Cfg.c`；收帧改走 `CanIf_RxIndication`；增加扩展帧 |
 * | V1.2.0 | 2026-11-10 | binbina | 邮箱中断同时处理 TX 完成 → `CanIf_TxConfirmation` |
 * | V1.3.0 | 2026-11-11 | binbina | 开 bus-off 中断：抓现场 + 计数 + 上报；补 `warningIntEnable` 未初始化 |
 */

#include "Can.h"
#include "Can_Cfg.h"
#include "Can_Priv.h"
#include "Can_HwCfg.h"

#include "CanIf.h"
#include "CanIf_Can.h"   /* Can → CanIf 的上行接口（CanIf_RxIndication 在这里，不在 CanIf.h） */

#include "platform_priv.h"
#include "platform_cvm0146.h"   /* Platform_Printf：仅 CanAc_DbgDump 用 */

#include <string.h>

/* ============================ [ 常量 ] ============================ */

/** @brief 位时序的 SJW：20%（相对位时间，单位 0.01%） */
#define CANAC_SJW_PERMILLE  (2500u)

/**
 * @brief 单个控制器最多支持的邮箱条数
 * @note  这是**静态数组容量**，不是硬件上限（CAN0 实际有 96 个邮箱）。
 *        表里超过这个数会被截断，并由 `CanAc_TranslateMsgCfgs()` 返回错误。
 */
#define CANAC_MAX_MSG_CFGS  (32u)

/* ============================ [ 数据 ] ============================ */

/**
 * @brief 翻译后的厂商格式邮箱表
 * @note  `Can_HwCfg.h` 的中性类型在这里一次性转成 `FlexCanDrv_MsgCfgType`，
 *        运行期（中断里）直接用，不再做任何转换。
 */
static FlexCanDrv_MsgCfgType s_flexCfgs[CAN_CFG_NUM_CHANNELS][CANAC_MAX_MSG_CFGS];

/** @brief 每个控制器实际翻译出的邮箱条数 */
static uint8_t s_flexCfgNum[CAN_CFG_NUM_CHANNELS];

/* ============================ [ 压测计数（M14） ] ============================ */

/**
 * @brief 单个控制器支持统计的最大邮箱号
 * @note  CVM014x 的 CAN0 RAM 是 3×512 B / 16 B = 96 个邮箱，
 *        但本工程最多用到 17。取 32 是"覆盖两组中断线"的最小整组，
 *        再大就要为没用到的邮箱白占 RAM（32×4 B×2 通道 = 256 B）。
 */
#define CANAC_MAX_MB    (32u)

/** @brief 累计接收帧数（每控制器） */
static uint32_t s_rxTotal[CAN_CFG_NUM_CHANNELS];

/**
 * @brief 按邮箱号分开的接收帧数
 * @note  分开记的理由：压测时"总数对得上但某一条总丢"是很常见的现象，
 *        这时只有按邮箱看才知道是哪个掩码区间出了问题。
 */
static uint32_t s_rxPerMb[CAN_CFG_NUM_CHANNELS][CANAC_MAX_MB];

/** @brief 邮箱中断进入次数（用来算"每次中断平均处理几帧"） */
static uint32_t s_isrCount[CAN_CFG_NUM_CHANNELS];

/**
 * @brief 发送句柄登记表：邮箱号 → `Can_PduType.swPduHandle`
 *
 * @details 发送完成中断里只知道"哪个邮箱发完了"，但 `CanIf_TxConfirmation()`
 *          要的是 **TxPduId**。所以在 `Can_Write()` 里把 `swPduHandle` 记下来，
 *          中断里反查。下标与 `s_flexCfgs[]` 的第二维一致（= 配置表项序号）。
 *
 * @note  M1 没有这个表，因为那时没有任何东西依赖发送完成；
 *        接 CanTp 之后它是必需的：分段发送必须"上一帧确认发出"才能发下一帧。
 */
static PduIdType s_txHandle[CAN_CFG_NUM_CHANNELS][CANAC_MAX_MSG_CFGS];

/**
 * @brief 每个控制器的 bus-off 累计次数（中断里 +1，主循环读）
 *
 * @details 用 `volatile uint16_t` 而不是 `uint32_t`：Cortex-M4 上 16 位对齐访问
 *          是单指令原子的，主循环读到的不会是"半个新值"。
 *          饱和在 `0xFFFF`，不回到 0 —— 回零会让上层误以为"恢复正常了"。
 *
 * @note  "计数变化"是上层感知 bus-off 的唯一入口。中断里不做恢复、不打印，
 *        所以这个计数器必须可靠，它是现象与代码之间唯一的事实。
 */
static volatile uint16_t s_busOffCnt[CAN_CFG_NUM_CHANNELS];

/**
 * @brief 每个控制器**首次** bus-off 时刻的现场快照
 *
 * @details `ESR1.FLTCONF` 在控制器自动恢复后立刻回到 error-active，
 *          事后再读只能读到 0。所以"是 ACK 错还是位错"这类信息
 *          只在中断当下能取到，必须在这里留一份。
 *          只记第一次：反复 bus-off 的根因通常就是第一次那个，
 *          每次都覆盖反而把最早、最干净的那份证据冲掉。
 */
static FlexCanDrv_ErrStatusType s_busOffSnap[CAN_CFG_NUM_CHANNELS];

/* ============================ [ 内部函数 ] ============================ */

/**
 * @brief 通道号 → 厂商驱动对象
 * @return 驱动对象；通道号越界返回 NULL
 */
static FlexCanDrvType *CanAc_GetObj(uint8_t controller)
{
	FlexCanDrvType *obj = NULL;

	switch (controller) {
	case 0u:
		obj = &g_mcu.flexCanDrv0;
		break;
	case 1u:
		obj = &g_mcu.flexCanDrv1;
		break;
	default:
		obj = NULL;
		break;
	}

	return obj;
}

/* ============================ [ 驱动等待超时 ] ============================ */

/**
 * @brief 单个等待上下文的轮询预算
 *
 * @details 取 200000：寄存器握手（LPMACK / FRZACK / SOFTRST 自清）在正常
 *          硬件上都是几个总线周期就完成，这个预算相当于**几十毫秒**，
 *          比正常值大三个数量级。取大一点是因为这里只为"防死机"，
 *          不为"检测慢"。
 */
#define CANAC_WAIT_SPIN_LIMIT   (200000u)

/**
 * @brief 每个控制器一份等待上下文
 * @note  必须**每通道独立**：CAN0/CAN1 各有自己的 `FlexCanDrvType`，
 *        共用一个计数器会让"CAN1 等待"把 CAN0 的预算也吃掉。
 */
typedef struct {
	volatile uint32_t spin;     /**< 已轮询次数 */
} CanAc_WaitCtxType;

static CanAc_WaitCtxType s_waitCtx[CAN_CFG_NUM_CHANNELS];

/**
 * @brief 该通道是否已经做过完整 `Configure`
 *
 * @details 为什么要记这个：`FlexCanDrv_Configure()` 内部会
 *          `MCR[MDIS]=1` → 等 `LPMACK` → 软复位 → 等 `LPMACK` 落下。
 *          而本平台的 CAN 模块**一旦进过低功耗就再也出不来**
 *          （实测清 `MDIS` 无效，MCR 恒定读回 `0xD890000F`；
 *          PCC 时钟位、软复位位、PCC 锁全部正常）。
 *          所以配置只做一次，之后 `STARTED` 只清 freeze/halt。
 *          详细证据见 `CanAc_Init()` 的 `@section CANAC_INIT_ONCE`。
 */
static bool s_configured[CAN_CFG_NUM_CHANNELS];

/**
 * @brief 驱动的等待超时回调（交给 `FlexCanDrvType::waitExpired`）
 * @param[in] context 指向本通道的 `CanAc_WaitCtxType`
 * @retval true  预算用尽，调用方应放弃并返回失败
 * @retval false 继续等
 *
 * @details @section CANAC_WAIT_WHY 为什么必须有这个回调
 *
 *          厂商 SDK 的 `FlexCanDrv_WaitExpired()`（`flexcan_drv.c:238`）是
 *          **唯一**的超时出口，而它只做两件事：
 *          @code
 *          if (obj->waitFailed) return true;
 *          if ((obj->waitExpired != 0) && obj->waitExpired(obj->waitContext))
 *              obj->waitFailed = true;
 *          return obj->waitFailed;
 *          @endcode
 *
 *          也就是说：**`waitExpired` 为 NULL 时，驱动里每一个
 *          `while (硬件握手位)` 都是无限循环。** 而厂商的
 *          `FlexCanDrv_Init()` 明确把 `waitExpired` 置 0，
 *          全仓也没有任何地方给它赋值。
 *
 *          后果不是"偶尔慢"，而是**整机硬死**：实测 M11 接上 CanSM 后，
 *          启动第一拍就卡在 `SoftReset` 的低功耗握手循环里 ——
 *          串口一行都不再输出、心跳停止，只能靠调试器看到
 *          PC 停在 `FlexCanDrv_EnableCanOperationClk`。
 *
 *          这类"硬件没就绪 → 整机静默"的故障在实车上无法诊断。
 *          所以补上预算：宁可让一次模式切换失败（有返回值、有日志），
 *          也不能让 ECU 停住。
 *
 * @warning 预算用尽后 `waitFailed` 会**置位且粘滞**，驱动后续所有等待
 *          会立即返回失败。所以每次调驱动前必须走 `CanAc_WaitBegin()`
 *          把它清掉。
 */
static bool CanAc_WaitExpired(void *context)
{
	CanAc_WaitCtxType *ctx = (CanAc_WaitCtxType *)context;

	if (ctx == NULL) {
		/* 没有上下文就无法计时。返回 false 保持原厂行为（无限等），
		 * 但正常路径不会走到这里：`CanAc_WaitBegin()` 一定会设上下文。 */
		return false;
	}

	ctx->spin++;
	return (ctx->spin > CANAC_WAIT_SPIN_LIMIT) ? true : false;
}

/**
 * @brief 打开某通道的 CAN 模块时钟（PCC）
 * @param[in] controller 通道号
 * @retval true  时钟已开（读回校验通过）
 * @retval false 通道非法，或写完后读回仍为 0
 *
 * @details @section CANAC_CLOCK 为什么平台层要管时钟
 *
 *          PCC 里 CAN 有**两个**时钟位，缺一不可：
 *          @code
 *          CK_EN0[9]  CAN0 工作时钟（operation clock）
 *          CK_EN1[28] CAN0 配置时钟（CFG clock）
 *          @endcode
 *
 *          厂商驱动里只有 `FlexCanDrv_EnableCanCfgClk()`（内部 static inline）
 *          会设这两个位，而它**只在 `Configure()` 开头被调用**。
 *          于是出现一个致命的不对称：
 *
 *          - 先 `Configure` → 顺带开了时钟 → 后面一切都正常（M1~M10 就是这样）；
 *          - 先 `SetSleepMode`/`DeInit` → 没有时钟 → 模块对 `MCR` 的写入
 *            全部无效 → `MDIS` 清不掉 → `LPMACK` 永远是 1 →
 *            驱动里那些等待循环永远不退出。
 *
 *          实测证据（CAN0，`0x40038000`）：
 *          @code
 *          MCR 恒为 0xD890000F  (MDIS=1 LPMACK=1 NOTRDY=1)
 *          调试器 w4 清 MDIS    → 读回不变
 *          PCC CK_EN0/CK_EN1    → CAN0 两位都是 1（因为 CAN1 的 Configure 顺带设过）
 *          @endcode
 *          也就是说：**只要有一次在时钟没开的时候碰了 MCR，模块就再也起不来**，
 *          而这条路径在 CanSM 接管之后是必然会走到的（NOCOM 会先 SLEEP）。
 *
 *          所以时钟使能必须由平台显式做，且在**任何**驱动调用之前。
 *          这也是分层的正当归属：PCC 是 SoC 的时钟树，不是 CAN 驱动的知识。
 *
 * @note  PCC 默认加锁，写时钟位之前必须先写解锁键。这里写完不重新加锁 ——
 *        与厂商 `EnableCanCfgClk` 的做法一致，重新加锁会让后续
 *        `Configure` 内部的时钟操作失败。
 */
static bool CanAc_EnableClock(uint8_t controller)
{
	PccRegType *pcc;
	uint8_t en0;
	uint8_t en1;

	if (controller >= CAN_CFG_NUM_CHANNELS) {
		return false;
	}

	pcc = CanAc_GetObj(controller)->pccReg;
	if (pcc == NULL) {
		return false;
	}

	PccReg_SetLockKey(pcc, 0x70637577u);      /* 解锁 PCC */

	if (controller == 0u) {
		PccReg_SetCkEn1CfgCan0(pcc, 1u);      /* 配置时钟 */
		PccReg_SetCkEn0Can0(pcc, 1u);         /* 工作时钟 */
		en0 = PccReg_GetCkEn0Can0(pcc);
		en1 = PccReg_GetCkEn1CfgCan0(pcc);
	} else {
		PccReg_SetCkEn1CfgCan1(pcc, 1u);
		PccReg_SetCkEn0Can1(pcc, 1u);
		en0 = PccReg_GetCkEn0Can1(pcc);
		en1 = PccReg_GetCkEn1CfgCan1(pcc);
	}

	return ((en0 != 0u) && (en1 != 0u)) ? true : false;
}

/**
 * @brief 装上等待超时钩子并重置预算
 * @param[in] controller 通道号
 * @return 该通道的驱动对象；通道非法时返回 NULL
 *
 * @note  每次调用厂商驱动**之前**都要调一次，两件事：
 *        1. 清 `waitFailed`（它粘滞，上次超时会让这次立刻失败）；
 *        2. 清 `spin`（重新给满预算）。
 */
static FlexCanDrvType *CanAc_WaitBegin(uint8_t controller)
{
	FlexCanDrvType *obj;

	if (controller >= CAN_CFG_NUM_CHANNELS) {
		return NULL;
	}

	obj = CanAc_GetObj(controller);
	if (obj == NULL) {
		return NULL;
	}

	s_waitCtx[controller].spin = 0u;
	obj->waitExpired = CanAc_WaitExpired;
	obj->waitContext = &s_waitCtx[controller];
	obj->waitFailed = false;

	return obj;
}

/**
 * @brief 把平台中性邮箱表翻译成厂商格式
 * @param[in] controller 通道号
 * @return E_OK 成功；E_NOT_OK 表过长（被截断）或通道越界
 *
 * @note 只在 `CanAc_Init()` 里调用一次。翻译结果是 static 数组，
 *       所以重复 Init 同一通道不会累积、也不会泄漏。
 */
static Std_ReturnType CanAc_TranslateMsgCfgs(uint8_t controller)
{
	const CanHw_MsgTableType *table;
	uint8_t num;
	uint8_t i;

	if (controller >= CAN_CFG_NUM_CHANNELS) {
		return E_NOT_OK;
	}

	table = &CanHw_MsgTables[controller];
	num = table->num;

	if (num > CANAC_MAX_MSG_CFGS) {
		/* 截断会让"配了却没生效"变成静默故障，所以返回错误让 Init 失败 */
		s_flexCfgNum[controller] = 0u;
		return E_NOT_OK;
	}

	for (i = 0u; i < num; i++) {
		const CanHw_MsgCfgType *src = &table->cfgs[i];
		FlexCanDrv_MsgCfgType *dst = &s_flexCfgs[controller][i];

		dst->msgBufId       = src->msgBufId;
		dst->msgBufLen      = src->msgBufLen;
		dst->msgId          = src->msgId;
		dst->isExtMsgId     = src->isExt;
		dst->msgType        = (src->dir == CAN_HW_MB_TX) ? FLEXCANDRV_MSGTYPE_TX
		                                                 : FLEXCANDRV_MSGTYPE_RX;
		dst->dlc            = (FlexCanDrv_DLCType)src->dlc;
		dst->isFd           = false;          /* M2 只用经典 CAN */
		dst->intEnable      = src->intEnable;
		dst->individualMask = src->individualMask;
	}

	s_flexCfgNum[controller] = num;

	return E_OK;
}

/**
 * @brief 邮箱中断处理：分发 RX 帧、上报 TX 完成
 * @note  在中断上下文调用。`CanIf_RxIndication` 里不要做耗时操作。
 *        `PduInfoType.SduDataPtr` 指向栈上的 `msg.data`，
 *        所以 CanIf 必须在返回前就把数据用完或拷走（当前实现在 `CANIF_RX_PACKET_POOL_SIZE=0`
 *        时是同步分发，满足这个约束）。
 *
 * @note  TX 与 RX 共用同一个中断线（邮箱 0~15 一组），所以必须**两个分支都看**。
 *        只处理 RX 的话，TX 完成标志会一直挂着，下一帧发送前不清会读到陈旧标志。
 */
static void CanAc_MbIsr(uint8_t controller, FlexCanDrvType *obj)
{
	FlexCanDrv_MsgObjType msg;
	Can_HwType mailbox;
	PduInfoType pdu;
	uint32_t i;

	if ((obj == NULL) || (controller >= CAN_CFG_NUM_CHANNELS)) {
		return;
	}

	for (i = 0u; i < (uint32_t)s_flexCfgNum[controller]; i++) {
		const FlexCanDrv_MsgCfgType *cfg = &s_flexCfgs[controller][i];

		if (!FlexCanDrv_GetMsgObjFlag(obj, (uint8_t)cfg->msgBufId)) {
			continue;
		}

		/* 先清标志再取数据：不清会立刻再进一次中断，取到的是同一帧 */
		FlexCanDrv_ClearMsgObjFlag(obj, (uint8_t)cfg->msgBufId);

		if (cfg->msgType == FLEXCANDRV_MSGTYPE_TX) {
			/* 发送完成：把 Can_Write() 时登记的 TxPduId 报上去 */
			CanIf_TxConfirmation(s_txHandle[controller][i]);
			continue;
		}

		memset(&msg, 0, sizeof(msg));
		msg.msgBufId = (uint8_t)cfg->msgBufId;
		FlexCanDrv_GetRxMsg(obj, &msg);

		/* AUTOSAR 约定：CanId 的 bit31 表示扩展帧 */
		mailbox.CanId = msg.msgId;
		if (cfg->isExtMsgId) {
			mailbox.CanId |= CAN_EXTENDED_ID_TYPE;
		}
		mailbox.Hoh = (Can_HwHandleType)cfg->msgBufId;
		mailbox.ControllerId = controller;

		/* 压测计数（M14）：在交给 CanIf **之前**记账。
		 * 记在这里而不是 CanIf 里，是为了区分两种"丢"：
		 *   - 这里没涨   → 硬件层就没收到（掩码没放行 / 邮箱满 / 总线错误）
		 *   - 这里涨了但应用没看到 → CanIf 软件过滤把帧丢了（表序或掩码错）
		 * 压测时这两个数字对不上，问题定位就完全是两个方向。 */
		s_rxTotal[controller]++;
		if (cfg->msgBufId < CANAC_MAX_MB) {
			s_rxPerMb[controller][cfg->msgBufId]++;
		}

		pdu.SduDataPtr = &msg.data[0];
		pdu.SduLength = msg.dlc;
		pdu.MetaDataPtr = NULL;

		CanIf_RxIndication(&mailbox, &pdu);
	}
}

/* ============================ [ 中断入口 ] ============================ */

/**
 * @brief CAN0 邮箱 0~15 中断
 * @note  邮箱号按 16 个一组共用中断线，所以处理函数要遍历整组而不只是自己那一个。
 *        处理函数本身不区分组：`CanAc_MbIsr()` 遍历的是**配置表里的全部邮箱**，
 *        各自检查自己的中断标志，所以两组共用一个实现是安全的
 *        （已处理的邮箱标志被清掉，第二次进来不会重复上报）。
 */
void CAN0_ORed_0_15_MB_Handler(void)
{
	s_isrCount[0]++;
	CanAc_MbIsr(0u, &g_mcu.flexCanDrv0);
}

/**
 * @brief CAN0 邮箱 16~31 中断（M14：标准帧段邮箱 16/17 落在这组）
 *
 * @details @section CANAC_MBGRP 为什么邮箱会跨组
 *          邮箱号是**连续分配**的，而中断线按 16 个一组切。M14 把标准帧段
 *          放到邮箱 15/16/17，正好跨在 `0~15` 与 `16~31` 的边界上：
 *
 *          | 邮箱 | 归属组 | 用途 |
 *          |------|--------|------|
 *          | 15 | 0~15 | 标准帧快变段 0x0A0~0x0A7 |
 *          | 16 | **16~31** | 标准帧灯光段 0x100~0x107 |
 *          | 17 | **16~31** | 标准帧车身 0x110 |
 *
 *          **只开 0~15 那条中断的后果**：邮箱 16/17 收到帧后标志位一直挂着，
 *          不进中断也就没人读 —— 邮箱一直是满的，后续帧全丢。
 *          而 `CanIf` 那边看起来一切正常（表配了、掩码也对），
 *          症状是"0x100 段和 0x110 一条都收不到，0x0A0 段却正常"。
 *
 * @note 真要配到 48 个以上邮箱时，还要补 `CAN0_ORed_48_63_MB_Handler`。
 *       本工程最多用到 17，两条中断足够。
 */
void CAN0_ORed_16_31_MB_Handler(void)
{
	s_isrCount[0]++;
	CanAc_MbIsr(0u, &g_mcu.flexCanDrv0);
}

/**
 * @brief CAN1 邮箱 0~15 中断
 * @note  与 CAN0 共用同一套处理逻辑，只是控制器号不同。
 *        两个中断各自独立挂载，因为它们是不同的 NVIC 向量（115 vs 103）。
 */
void CAN1_ORed_0_15_MB_Handler(void)
{
	s_isrCount[1]++;
	CanAc_MbIsr(1u, &g_mcu.flexCanDrv1);
}

/* ============================ [ 中断入口：总线错误 ] ============================ */

/**
 * @brief 总线错误中断处理：抓 bus-off 现场、计数、上报 CanIf
 * @param[in] controller 通道号
 * @param[in] obj        厂商驱动对象
 *
 * @details 执行顺序不能换：
 *          1. 读 `ESR1` 判断是哪个源（读不会清标志，`BOFFINT/TWRNINT/RWRNINT` 都是写 1 清）；
 *          2. **先把三个源都清掉**，再上报。晚清一步，退出中断后立刻重入，
 *             表现是中断里死循环、主循环一行都不跑；
 *          3. 记快照（只记第一次）与计数；
 *          4. `CanIf_ControllerBusOff()` 报上去。
 *
 * @note  中断里**不做恢复**。恢复要等 `SetControllerMode(STOPPED→STARTED)`
 *        这种带延时的时序动作，放在中断里会把中断关几百毫秒。
 *        这里只保证"上层一定能知道发生过"。
 *
 * @warning `FlexCanDrv_GetErrorStatusFlag()` 只填自己读到的字段，
 *          不 memset 的话 `fltConfSts` 之外全是栈垃圾。厂商实现里
 *          `wakeUpInt` 还误用了 `ERRINT` 的掩码（复制粘贴错误），
 *          所以本函数只信 `fltConfSts` 与几个错误位，不信 `wakeUpInt`。
 */
static void CanAc_OredIsr(uint8_t controller, FlexCanDrvType *obj)
{
	FlexCanDrv_ErrStatusType st;

	if ((obj == NULL) || (controller >= CAN_CFG_NUM_CHANNELS)) {
		return;
	}

	memset(&st, 0, sizeof(st));
	FlexCanDrv_GetErrorStatusFlag(obj, &st);

	/* 无论走了哪条分支，三个源都必须清 —— 否则挂着的标志会让中断反复触发 */
	FlexCanDrv_ClearErrStatusFlag(obj,
	                              (uint32_t)FLEXCANDRV_ESR_STATUS_BOFFINT_MASK |
	                              (uint32_t)FLEXCANDRV_ESR_STATUS_TWRNINT_MASK |
	                              (uint32_t)FLEXCANDRV_ESR_STATUS_RWRNINT_MASK);

	if (st.busOffInt == 0u) {
		/* 只可能是告警中断（当前未开）。不清已经清过，直接返回 */
		return;
	}

	if (s_busOffCnt[controller] == 0u) {
		/* 第一次：留现场。后续的不覆盖，原因见 s_busOffSnap 的注释 */
		s_busOffSnap[controller] = st;
	}
	if (s_busOffCnt[controller] != 0xFFFFu) {
		s_busOffCnt[controller]++;
	}

	/* AUTOSAR 正规路径：Can 驱动在中断里上报 CanIf。
	 * 本项目没有 CanSM，所以 CanIf 内部这一路当前是空动作（`#ifdef USE_CANSM`），
	 * 但接口必须调 —— 将来接 CanSM 时不用回来改驱动。 */
	CanIf_ControllerBusOff(controller);
}

/** @brief CAN0 总线错误中断（NVIC 100，`BusOff OR TxWarn OR RxWarn`） */
void CAN0_ORed_Handler(void)
{
	CanAc_OredIsr(0u, &g_mcu.flexCanDrv0);
}

/** @brief CAN1 总线错误中断（NVIC 112） */
void CAN1_ORed_Handler(void)
{
	CanAc_OredIsr(1u, &g_mcu.flexCanDrv1);
}

/* ============================ [ AS 声明的 AC 接口 ] ============================ */

Std_ReturnType CanAc_GlobalInit(const Can_ConfigType *Config)
{
	/* 两路共用的一次性初始化：M1 没有需要在这里做的事
	 * （CAN 的 PCC 时钟由 FlexCanDrv_Configure 自己开，引脚由 Port_Init 配） */
	(void)Config;
	return E_OK;
}

Std_ReturnType CanAc_GlobalDeInit(const Can_ConfigType *Config)
{
	(void)Config;
	return E_OK;
}

Std_ReturnType CanAc_Init(uint8_t Controller, const Can_ChannelConfigType *config)
{
	FlexCanDrv_ControllerCfgType cfg;
	FlexCanDrvType *obj;
	uint32_t busClk = 0u;
	uint32_t i;

	if (config == NULL) {
		return E_NOT_OK;
	}
	if (Controller >= CAN_CFG_NUM_CHANNELS) {
		return E_NOT_OK;
	}

	/* 装等待超时钩子并重置预算：**必须在下一次调厂商驱动之前**。
	 * `waitFailed` 是粘滞标志，上一次超时会让这一整轮 Configure 立刻失败。 */
	obj = CanAc_WaitBegin(Controller);
	if (obj == NULL) {
		return E_NOT_OK;
	}
	/* 0) 先把平台中性表翻译成厂商格式，失败就不启动控制器 */
	if (CanAc_TranslateMsgCfgs(Controller) != E_OK) {
		return E_NOT_OK;
	}

	/**
	 * @section CANAC_INIT_ONCE 为什么只在**第一次**做完整 Configure
	 *
	 *          `Can_SetControllerMode(CAN_CS_STARTED)` 会被反复调用：
	 *          CanSM 每次从 NOCOM 回到 FULLCOM 都会走一遍
	 *          `PRE_FULLCOM → STARTED`。而 `FlexCanDrv_Configure()` 内部会
	 *          `MCR[MDIS]=1` → 等 `LPMACK` → 软复位 → 等 `LPMACK` 落下。
	 *
	 *          @warning **这个"进低功耗再出来"的往返在本平台上不可靠。**
	 *          实测：CAN0 一旦被置过 `MDIS=1`，之后再清 `MDIS` 无效 ——
	 *          连调试器直接 `w4` 写 MCR 都读回原值（`0xD890000F` 恒定），
	 *          同时 PCC 的 `CK_EN0/CK_EN1` 两位都是 1、`SW_RST=0`、`LOCK=0`，
	 *          也就是说"时钟开着、没复位、没加锁"，但模块就是不接受写入。
	 *          CAN1 因为只 Configure 过一次，一直正常。
	 *
	 *          所以这里把 Configure 收敛成**每通道只做一次**（`s_configured`）。
	 *          之后的 STARTED 只做"清 freeze/halt"，O(1) 且没有低功耗往返，
	 *          既符合 AUTOSAR 的语义（配置在 `Can_Init` 阶段完成，
	 *          `Can_SetControllerMode` 只切运行状态），也彻底绕开了这个缺陷。
	 *
	 *          @note 附带好处：M10 那个"第二次 Configure 时
	 *                `selected3bitSampling` 拿到栈垃圾导致 SMP 位翻转"
	 *                的问题，从此**不会再被触发**（虽然 memset 的修复保留着）。
	 */
	if (!s_configured[Controller]) {
		/* 1) **先整块清零，再取厂商默认值。**
		 *
		 * @warning 这一步必须排在 `FlexCanDrv_GetDefaultCfg()` **之前**。
		 *          `cfg` 是栈上的局部变量，而 `GetDefaultCfg()`
		 *          （`flexcan_drv.c:389`）**漏掉了 `selected3bitSampling` 字段**
		 *          （还可能漏掉别的）。不清零的话，没被赋值的字段就是上一次
		 *          函数调用残留的栈内容 —— 同一份代码，第一次拿到 0、
		 *          第二次可能拿到 1。清零是根治而不是打补丁。
		 */
		(void)memset(&cfg, 0, sizeof(cfg));
		FlexCanDrv_GetDefaultCfg(&cfg);

		cfg.clkSrc               = FLEXCANDRV_CLKSRC_CHICLK;  /* 模块时钟取 APB */
		cfg.fdEnable             = false;                      /* 只用经典 CAN */
		cfg.fdISOEnable          = false;
		cfg.fifoEnable           = false;                      /* 用邮箱而不是 FIFO，便于逐帧匹配 ID */
		cfg.enhancefifoEnable    = false;
		cfg.individualMaskEnable = true;                       /* 每个邮箱独立掩码 */
		cfg.msgBufDataLenSel     = FLEXCANDRV_MB_SIZE_BYTE_8;

		/* 总线错误中断：只开 bus-off。
		 *
		 * ⚠ `warningIntEnable` 必须显式写 false：`GetDefaultCfg()` 漏掉了
		 * 这个字段，不赋值就是栈垃圾，会随机打开 Tx/Rx 告警中断 ——
		 * 而 `CANx_ORed` 是三个源的或，一旦 NVIC 打开就是中断风暴。
		 *
		 * `errorIntEnable` 也不开：它每错一帧触发一次，干扰大的总线上
		 * 会吃满 CPU，而错误类型在 bus-off 那一刻的快照里已经拿得到。 */
		cfg.busoffIntEnable      = true;
		cfg.errorIntEnable       = false;
		cfg.warningIntEnable     = false;

		cfg.msgNum               = s_flexCfgNum[Controller];
		cfg.msgCfg               = s_flexCfgs[Controller];

		/* 2) 位时序：必须用实际模块时钟算，写死会得到错误的波特率
		 *    （现象是总线上完全没帧，或者对端报 form/ack error） */
		(void)ClockDrv_GetFreq(&g_mcu.clockDrv, CLOCKDRV_APB, &busClk);
		FlexCanDrv_BitTimingCalc(&cfg.bitTiming, busClk, config->baudrate,
		                         (uint16_t)((uint32_t)config->samplePoint * 100u),
		                         (uint16_t)CANAC_SJW_PERMILLE, 0u);

		/* 3) 配置 + 启动（Configure 内部含软复位、RAM 初始化、进 Normal 模式） */
		FlexCanDrv_Configure(obj, &cfg);

		/**
		 * @note Configure 里任何一个硬件握手失败都会**提前 return**
		 *       （`waitFailed` 被 `CanAc_WaitExpired()` 置起来），
		 *       函数本身没有返回值可判，只能回看标志。
		 *
		 *       不检查的后果：控制器实际没启动，但 `context->state`
		 *       记为 STARTED，之后所有"启动"请求都被当成已启动而跳过，
		 *       通道**永久静默且无法恢复**。
		 */
		if (obj->waitFailed) {
			Platform_Printf("[can] ch%u Configure 握手超时（MCR=0x%08x CTRL1=0x%08x）\n",
			                (unsigned)Controller, (unsigned)obj->flexCanReg->MCR,
			                (unsigned)obj->flexCanReg->CTRL1);
			return E_NOT_OK;
		}

		s_configured[Controller] = true;
	} else {
		/**
		 * @brief 已配置过：只清 freeze/halt，让控制器重新上总线
		 *
		 * @note  `FlexCanDrv_Start()` 做的就是这件事（清 `FRZ`+`HALT`，
		 *        再等 `FRZACK` 落下）。这里直接用它，不再碰 `MDIS`。
		 *        邮箱配置、位时序、掩码全部保留，所以是 O(1) 的。
		 */
		FlexCanDrv_Start(obj);
		if (obj->waitFailed) {
			Platform_Printf("[can] ch%u 启动超时（MCR=0x%08x）\n",
			                (unsigned)Controller, (unsigned)obj->flexCanReg->MCR);
			return E_NOT_OK;
		}
	}

	/* 3b) Configure 里任何一个硬件握手失败都会**提前 return**（`waitFailed`
	 *     被 `CanAc_WaitExpired()` 置起来），函数本身没有返回值可判。
	 *     所以只能在这里回看标志 —— 把它变成明确的 `E_NOT_OK`，
	 *     让 `Can_SetControllerMode()` 不把状态置成 STARTED。
	 *
	 *     不检查的后果：控制器实际没启动，但 `context->state` 记为 STARTED，
	 *     之后所有"启动"请求都被当成已经启动而跳过，通道**永久静默且无法恢复**。 */
	if (obj->waitFailed) {
		Platform_Printf("[can] ch%u Configure 握手超时（CTRL1=0x%08x），控制器未启动\n",
		                (unsigned)Controller, (unsigned)obj->flexCanReg->CTRL1);
		return E_NOT_OK;
	}

	/* 4) 打开邮箱中断并放开 NVIC
	 *    按 intEnable 打开，而不是"只开 RX"：TX 完成中断是 CanTp 分段发送的
	 *    节拍源，漏掉它会让上层永远等不到 confirmation。 */
	for (i = 0u; i < (uint32_t)cfg.msgNum; i++) {
		if (cfg.msgCfg[i].intEnable) {
			FlexCanDrv_EnableMsgObjInterrupt(obj, (uint8_t)cfg.msgCfg[i].msgBufId);
		}
	}

	if (Controller == 0u) {
		IrqDrv_EnableIrq(CAN0_ORed_0_15_MB_IRQn);
		/* M14：邮箱 16/17（标准帧段）落在 16~31 组。
		 * 漏掉这条的症状是"0x100 段和 0x110 一条都收不到，0x0A0 段却正常"，
		 * 因为邮箱 16/17 收到帧后没人读，一直满着。 */
		IrqDrv_EnableIrq(CAN0_ORed_16_31_MB_IRQn);
		IrqDrv_EnableIrq(CAN0_ORed_IRQn);         /* bus-off 上报（NVIC 100） */
	} else if (Controller == 1u) {
		IrqDrv_EnableIrq(CAN1_ORed_0_15_MB_IRQn);
		IrqDrv_EnableIrq(CAN1_ORed_IRQn);         /* NVIC 112 */
	} else {
		/* 多通道时在这里继续加；漏掉这一步的症状是"能发不能收" */
	}

	return E_OK;
}

/**
 * @brief 停止控制器（`CAN_CS_STOPPED`）：只进 freeze + halt，不碰低功耗
 *
 * @details @section CANAC_DEINIT_FREEZE 为什么不调 `FlexCanDrv_SoftReset()`
 *
 *          M2~M10 这里调的是 `SoftReset`，那时能工作只是因为
 *          **每次 STOPPED 之前控制器都在运行**，`LPMACK=0`，
 *          `SoftReset` 会跳过它的低功耗分支。
 *
 *          M11 接上 CanSM 之后顺序变了。CanSM 进 NOCOM 是四步
 *          （`CanSM.c:55~90`）：
 *          @code
 *          CanIf_SetControllerMode(STOPPED)
 *          CanIf_SetControllerMode(SLEEP)     // 模块断电
 *          CanIf_SetTrcvMode(NORMAL)
 *          CanIf_SetTrcvMode(STANDBY)
 *          @endcode
 *          于是第二次进 PRE_NOCOM 时控制器已经睡过 ——
 *          一旦走到低功耗分支就再也出不来，整条链路死在这里。
 *
 *          @warning **本平台的 FlexCAN 不能做低功耗往返。** 实测证据：
 *          - `MCR` 恒定读回 `0xD890000F`（`MDIS=1, LPMACK=1, NOTRDY=1`）；
 *          - 用调试器直接 `w4` 写 MCR 清 `MDIS`，**读回不变**；
 *          - 同时 `PCC.CK_EN0/CK_EN1` 的 CAN0 位都是 1、`SW_RST=0`、`LOCK=0`
 *            —— 时钟开着、没复位、没加锁，但模块就是不接受写入；
 *          - 同一份代码的 CAN1（只 Configure 过一次、没睡过）一直正常。
 *
 *          所以本函数只做 AUTOSAR 对 STOPPED 要求的事：**停止通信**。
 *          模块保持供电、配置保持有效，`STARTED` 只需清 `FRZ`/`HALT` 即可，
 *          O(1) 且没有任何硬件握手。
 *
 * @note  真正的省电不在这里：CAN 侧的电流主要花在收发器上，
 *        那由 `CanSM` 驱动 STB 引脚（`CanIf_SetTrcvMode`）控制；
 *        整机低功耗属于 `EcuM_AL_EnterSLEEP()` / `Mcu_SetMode`，M12 的事。
 *        把"关模块时钟"塞进 MCAL 的 STOPPED/SLEEP 是把两件事混在一起，
 *        代价就是这里踩到的不可恢复状态。
 *
 * @param[in] Controller 通道号
 * @param[in] config     通道配置（未使用）
 * @retval E_OK     已停止
 * @retval E_NOT_OK 通道非法，或 `FRZACK` 超时
 *
 * @note  失败时不报 E_OK：`Can_SetControllerMode()` 只在 E_OK 时把状态置
 *        STOPPED。报成功但没停，上层不会再重试，通道就静默了。
 */
Std_ReturnType CanAc_DeInit(uint8_t Controller, const Can_ChannelConfigType *config)
{
	FlexCanDrvType *obj;

	(void)config;

	obj = CanAc_WaitBegin(Controller);
	if (obj == NULL) {
		return E_NOT_OK;
	}

	/* 同样先保证时钟：CanSM 可能在第一次 Configure 之前就请求 STOPPED，
	 * 那时模块还停在复位态（MDIS=1），没有时钟连 freeze 位都写不进去。 */
	if (!CanAc_EnableClock(Controller)) {
		Platform_Printf("[can] ch%u PCC 时钟使能失败\n", (unsigned)Controller);
		return E_NOT_OK;
	}

	/**
	 * @note **模块处于低功耗（`LPMACK=1`）时直接返回 E_OK。**
	 *
	 *       复位后 `MCR[MDIS]` 默认就是 1，芯片一起来模块就在低功耗态。
	 *       此时置 `FRZ`/`HALT` 是无效的（寄存器被忽略），`FRZACK` 永远不置位。
	 *       而"低功耗"本身就意味着控制器不可能在总线上通信 ——
	 *       正好满足 `CAN_CS_STOPPED` 的语义，所以直接报成功。
	 *
	 *       不这样处理会死锁：CanSM 第一步就请求 STOPPED，
	 *       永远失败就永远到不了 FULLCOM，通道一次都启动不起来。
	 */
	if (FlexCanReg_GetLowPowerAck(obj->flexCanReg) != 0u) {
		return E_OK;
	}

	/* 同时置 FRZ 与 HALT 才真正进 freeze 并停止总线活动 */
	FlexCanReg_SetFreezeMode(obj->flexCanReg, true);
	FlexCanReg_SetHaltMode(obj->flexCanReg, true);

	while (FlexCanReg_GetFreezeAck(obj->flexCanReg) == 0u) {
		if (CanAc_WaitExpired(obj->waitContext)) {
			Platform_Printf("[can] ch%u freeze 超时（MCR=0x%08x LPMACK=%u）\n",
			                (unsigned)Controller, (unsigned)obj->flexCanReg->MCR,
			                (unsigned)FlexCanReg_GetLowPowerAck(obj->flexCanReg));
			return E_NOT_OK;
		}
	}

	return E_OK;
}

/**
 * @brief 控制器睡眠（`CAN_CS_SLEEP`）
 *
 * @details 与 STOPPED **完全相同**：进 freeze + halt，不关模块时钟。
 *
 * @warning 不要在这里写 `MCR[MDIS]=1`。原因见 `CanAc_DeInit()` 的
 *          `@section CANAC_DEINIT_FREEZE`：本平台的 CAN 模块进低功耗后
 *          出不来，写 `MDIS` 等于把这个通道永久报废。
 *
 *          从功耗角度看这样做没有损失：CAN 节点在总线睡眠时的电流
 *          主要由收发器决定，而 `CanSM` 已经把 STB 拉到 standby。
 *          MCU 侧要省电应该走 `EcuM_AL_EnterSLEEP()` → `Mcu_SetMode()`，
 *          那是整机行为，不是单个 CAN 控制器能做主的。
 */
Std_ReturnType CanAc_SetSleepMode(uint8_t Controller, const Can_ChannelConfigType *config)
{
	return CanAc_DeInit(Controller, config);
}

Std_ReturnType CanAc_SetupPinMode(const Can_CtrlPinType *pin)
{
	/* USE_PORT 已定义：引脚 MUX 统一由 Port_Cfg 配置，Can 不再管引脚。
	 * 保留这个桩是为了让 Can_Priv.h 的接口集保持完整（切回非 USE_PORT 时用）。 */
	(void)pin;
	return E_OK;
}

Std_ReturnType CanAc_WritePin(const Can_CtrlPinType *pin, uint8_t value)
{
	(void)pin;
	(void)value;
	return E_OK;
}

/* ============================ [ AUTOSAR 发送接口（AS 未实现） ] ============================ */

Std_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo)
{
	const CanHw_HohType *hoh;
	FlexCanDrvType *obj;
	FlexCanDrv_MsgObjType msg;
	uint32_t id;
	uint32_t i;

	if (PduInfo == NULL) {
		return E_NOT_OK;
	}
	if (PduInfo->sdu == NULL) {
		return E_NOT_OK;
	}
	if ((uint32_t)Hth >= (uint32_t)CAN_HW_HOH_NUM) {
		return E_NOT_OK;
	}

	hoh = &CanHw_Hohs[Hth];
	obj = CanAc_GetObj(hoh->controller);
	if (obj == NULL) {
		return E_NOT_OK;
	}

	id = PduInfo->id & CAN_CANID_MASK;
	if (id != hoh->canId) {
		/* 邮箱的 ID 在配置时就定了（SetTxMsg 不写 ID），这里发别的 ID
		 * 只会发出去一帧"ID 不对"的报文，静默失败比返回错误更难查 */
		return E_NOT_OK;
	}
	if ((uint32_t)PduInfo->length > (uint32_t)hoh->dlc) {
		/* DLC 同样在配置时定死，超长会写坏数据区 */
		return E_NOT_OK;
	}

	/* 登记发送句柄：中断里要靠它把"邮箱发完了"翻译成 TxPduId。
	 * 用 msgBufId 反查配置表下标，找不到就说明 HTH 表与邮箱表不一致（配置错误） */
	for (i = 0u; i < (uint32_t)s_flexCfgNum[hoh->controller]; i++) {
		if (s_flexCfgs[hoh->controller][i].msgBufId == hoh->msgBufId) {
			s_txHandle[hoh->controller][i] = PduInfo->swPduHandle;
			break;
		}
	}

	memset(&msg, 0, sizeof(msg));
	msg.msgBufId = (uint8_t)hoh->msgBufId;
	msg.dlc      = hoh->dlc;
	/* 短帧补零：硬件 DLC 固定，所以长度不够的部分必须是确定的 0，
	 * 而不是上一帧的残留数据 */
	if (PduInfo->length > 0u) {
		(void)memcpy(&msg.data[0], PduInfo->sdu, (size_t)PduInfo->length);
	}

	/* 先写数据再触发发送：反过来会发出一帧"上一次的数据" */
	FlexCanDrv_SetTxMsg(obj, &msg);
	FlexCanDrv_TransmitMsg(obj, &msg);

	return E_OK;
}

/* ============================ [ 平台扩展：总线状态查询 ] ============================ */

/**
 * @brief 取某通道的 bus-off 统计与首次快照
 * @note  主循环上下文调用。读的是 `volatile` 计数器与一份普通结构体，
 *        中断可能正在写 `s_busOffSnap` —— 最坏情况是读到"计数已 +1、
 *        快照还是旧的"，不会读到撕裂的值（结构体字段都是 ≤16 位）。
 *        验收脚本靠"计数变化"触发，不依赖快照与计数严格同步。
 */
bool CanAc_GetBusOffInfo(uint8_t controller, Can_BusOffInfoType *info)
{
	const FlexCanDrv_ErrStatusType *snap;

	if ((info == NULL) || (controller >= CAN_CFG_NUM_CHANNELS)) {
		return false;
	}

	snap = &s_busOffSnap[controller];

	info->count   = s_busOffCnt[controller];
	info->fltConf = (uint8_t)snap->fltConfSts;
	info->errBits = (uint8_t)(((snap->bit1Err  != 0u) ? CAN_BUSOFF_ERR_BIT1  : 0u) |
	                          ((snap->bit0Err  != 0u) ? CAN_BUSOFF_ERR_BIT0  : 0u) |
	                          ((snap->ackErr   != 0u) ? CAN_BUSOFF_ERR_ACK   : 0u) |
	                          ((snap->crcErr   != 0u) ? CAN_BUSOFF_ERR_CRC   : 0u) |
	                          ((snap->formErr  != 0u) ? CAN_BUSOFF_ERR_FORM  : 0u) |
	                          ((snap->stuffErr != 0u) ? CAN_BUSOFF_ERR_STUFF : 0u));

	return true;
}

/**
 * @brief 控制器当前是否处于 bus-off
 * @note  与 `CanAc_GetBusOffInfo()` 的区别：这个读**实时**状态，
 *        计数为零也可能为 true（中断还没跑到），反之计数非零此刻通常已是 false。
 */
bool CanAc_IsBusOff(uint8_t controller)
{
	FlexCanDrvType *obj;
	FlexCanDrv_ErrStatusType st;

	obj = CanAc_GetObj(controller);
	if (obj == NULL) {
		return false;
	}

	memset(&st, 0, sizeof(st));
	FlexCanDrv_GetErrorStatusFlag(obj, &st);

	return (st.fltConfSts == FLEXCANDRV_FLTCONFSTS_BUSOFF) ? true : false;
}

/**
 * @brief 清零 bus-off 计数与快照
 * @warning 会清掉唯一的现场证据，只在验收脚本要求"从零开始"时用。
 */
void CanAc_ClearBusOffInfo(uint8_t controller)
{
	if (controller >= CAN_CFG_NUM_CHANNELS) {
		return;
	}

	s_busOffCnt[controller] = 0u;
	memset(&s_busOffSnap[controller], 0, sizeof(s_busOffSnap[controller]));
}

/* ============================ [ 调试 ] ============================ */

/**
 * @brief 打印控制器的关键寄存器（**仅供 bring-up 排查**）
 * @param[in] controller 通道号
 *
 * @details 为什么会需要它：bus-off 是"硬件状态机内部的事"，
 *          AUTOSAR 接口只能看到"当前是否 bus-off"，看不到
 *          `TEC/REC`、`FLTCONF`、`BOFFMSK` 这些决定性证据。
 *          排查"为什么没进中断"时，第一步永远是确认
 *          **错误计数到底涨没涨**——涨了说明总线真的在错，
 *          没涨说明帧根本没发出去，两个方向的修法完全相反。
 */
void CanAc_DbgDump(uint8_t controller)
{
	FlexCanDrvType *obj;
	const FlexCanRegType *r;
	uint32_t mcr;
	uint32_t ctrl1;
	uint32_t ecr;
	uint32_t esr1;

	obj = CanAc_GetObj(controller);
	if (obj == NULL) {
		return;
	}
	r = obj->flexCanReg;

	mcr   = r->MCR;
	ctrl1 = r->CTRL1;
	ecr   = r->ECR;
	esr1  = r->ESR1;

	Platform_Printf("[canreg] ch%u mcr=%08x ctrl1=%08x ecr=%08x esr1=%08x\n",
	                (unsigned)controller, (unsigned)mcr, (unsigned)ctrl1,
	                (unsigned)ecr, (unsigned)esr1);
	/* 中断使能与标志：排查"收不到帧"的第一现场。
	 * mb5（0x7E0）对应 IMASK1 的 bit5 —— 若这里是 0，说明
	 * `FlexCanDrv_EnableMsgObjInterrupt()` 没生效，帧收进来也不会进中断。 */
	Platform_Printf("[canreg]  IMASK1=%08x IFLAG1=%08x IMASK2=%08x\n",
	                (unsigned)r->IMASK1, (unsigned)r->IFLAG1, (unsigned)r->IMASK2);
	Platform_Printf("[canreg]  waitFailed=%u \n", (unsigned)(obj->waitFailed ? 1u : 0u));
	Platform_Printf("[canreg]  TEC=%u REC=%u FLTCONF=%u BOFFINT=%u BOFFMSK=%u ERRMSK=%u\n",
	                (unsigned)((ecr >> FLEXCAN_ECR_TXERRCNT_SHIFT) & 0xFFu),
	                (unsigned)((ecr >> FLEXCAN_ECR_RXERRCNT_SHIFT) & 0x7Fu),
	                (unsigned)((esr1 & FLEXCAN_ESR1_FLTCONF_MASK) >> FLEXCAN_ESR1_FLTCONF_SHIFT),
	                (unsigned)((esr1 & FLEXCAN_ESR1_BOFFINT_MASK) >> FLEXCAN_ESR1_BOFFINT_SHIFT),
	                (unsigned)((ctrl1 & FLEXCAN_CTRL1_BOFFMSK_MASK) >> FLEXCAN_CTRL1_BOFFMSK_SHIFT),
	                (unsigned)((ctrl1 & FLEXCAN_CTRL1_ERRMSK_MASK) >> FLEXCAN_CTRL1_ERRMSK_SHIFT));
}


/* ============================ [ 压测接口（M14） ] ============================ */

uint32_t Platform_CanRxTotal(uint8_t controller)
{
	if (controller >= CAN_CFG_NUM_CHANNELS) {
		return 0u;
	}
	return s_rxTotal[controller];
}

uint32_t Platform_CanRxByMb(uint8_t controller, uint8_t mb)
{
	if ((controller >= CAN_CFG_NUM_CHANNELS) || (mb >= CANAC_MAX_MB)) {
		return 0u;
	}
	return s_rxPerMb[controller][mb];
}

uint32_t Platform_CanIsrCount(uint8_t controller)
{
	if (controller >= CAN_CFG_NUM_CHANNELS) {
		return 0u;
	}
	return s_isrCount[controller];
}

void Platform_CanResetRxCounters(void)
{
	uint8_t c;

	for (c = 0u; c < CAN_CFG_NUM_CHANNELS; c++) {
		uint8_t m;

		s_rxTotal[c] = 0u;
		s_isrCount[c] = 0u;
		for (m = 0u; m < CANAC_MAX_MB; m++) {
			s_rxPerMb[c][m] = 0u;
		}
	}
}
