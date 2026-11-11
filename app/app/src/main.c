/**
 * @file    main.c
 * @brief   M1 里程碑：AUTOSAR MCAL（Port/Dio/Can）驱动真实 CAN 收发
 *
 * @details 验收判据（Kvaser ch0=CAN0 / ch1=CAN1，两路 @500 kbps）：
 *          1. **CAN0 TX 标准帧**：`0x123` 每 500 ms，DLC=8，8 字节逐帧全 +1；
 *          2. **CAN0 TX 扩展帧**：`0x18FF0002` 每 1000 ms（**29 位**），
 *             首字节递增，其余 `A5`；
 *          3. **CAN0 RX**：发 `0x321` → `pdu=0`；发 `0x18FF0001` → `pdu=1`；
 *          4. **CAN1 TX**：`0x124` 每 500 ms，首字节递增，其余 `C3`；
 *          5. **CAN1 RX**：发 `0x322` → `pdu=2`；
 *          6. **不影响 M0**：启动横幅、printf 自检、心跳、回显照常。
 *
 *          走的是 AUTOSAR 的正规路径，不是直接怼寄存器：
 *          ```
 *          Port_Init(NULL)                        引脚 MUX/方向/初始电平（含 CAN1 的 PTC6/PTC7/PTE13）
 *          Can_Init(NULL)                         装载两路通道配置
 *          CanIf_Init(NULL)                       所有控制器 PDU 模式置 OFFLINE
 *          CanIf_SetControllerMode(ch, STARTED)   → Can_SetControllerMode → CanAc_Init
 *          CanIf_SetTrcvMode(ch, NORMAL)          STB 拉低，收发器上总线
 *          CanIf_SetPduMode(ch, ONLINE)           **必须**，否则发送恒失败
 *          CanIf_Transmit(CANIF_TX_XXX, &pdu)     发送：只给逻辑 PDU 号
 *          App_CanIfRxIndication(pduId, pdu)      接收：CanIf_Cfg 挂上来的回调
 *          ```
 *
 *          @section M2_RX 应用层再也看不到 CAN ID，也看不到通道
 *          M1 的 `CanAc_RxIndication(controller, id, isExt, ...)` 把报文 ID 直接暴露给应用；
 *          M2 之后应用只拿到 `PduIdType`（`CANIF_RX_TEST` / `CANIF_RX_EXT_TEST` / `CANIF_RX_CAN1_TEST`）。
 *          加一条报文、改 ID、改掩码、把报文从 CAN0 挪到 CAN1 —— 应用一行不用动，
 *          全在 `CanIf_Cfg.c` / `Can_Cfg.c` 两张表里。
 *
 *          @warning 中断里不要打印。`Platform_Printf` 是阻塞轮询发送的，
 *          CAN 中断里阻塞几十微秒以上就可能丢下一帧。所以中断只置标志+拷数据，
 *          打印放主循环。
 *
 * @author  binbina
 * @version V2.8.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：启动 + 心跳 + 串口回显 |
 * | V1.1.0 | 2026-11-10 | binbina | 增加 printf 自检表（宽度/对齐/补零/精度/符号） |
 * | V1.2.0 | 2026-11-10 | binbina | M1：Port/Dio/Can 初始化，周期发 0x123，收 0x321 |
 * | V1.3.0 | 2026-11-10 | binbina | M2：接 CanIf，收发改为逻辑 PDU；增加 29 位扩展帧收发 |
 * | V1.4.0 | 2026-11-10 | binbina | M2b：开 CAN1（PTC6/PTC7 ALT3 + PTE13 STB），双通道收发 |
 * | V1.5.0 | 2026-11-10 | binbina | M4：接存储栈（NvM/FEE），启动计数 + 延迟落盘 + GC 压测 + DET |
 * | V1.6.0 | 2026-11-11 | binbina | M5：bus-off 检测/记录，故障快照持久化到 DTC 块 |
 * | V1.7.0 | 2026-11-11 | binbina | M6：故障表下沉为 Dem，接 Dcm 0x19/0x14；抽公共 ISO-TP 脚本 |
 * | V1.8.0 | 2026-11-11 | binbina | M7：0x27 安全访问（恒通过）+ 0x2E 写 DID（VIN 落 NvM） |
 * | V1.9.0 | 2026-11-11 | binbina | M9：接 CanNm/Nm 网络管理（0x500，200 ms），ComM 状态镜像 |
 * | V2.0.0 | 2026-11-11 | binbina | M10：接 Com 信号层（0x200，100 ms），位打包/大小端/信号超时 |
 * | V2.1.0 | 2026-11-11 | binbina | M11：EcuM 三阶段初始化 + ComM/CanSM 标准链路 |
 * | V2.2.0 | 2026-11-11 | binbina | M11b：修 CAN 低功耗死锁（平台管时钟 / STOPPED 只 freeze），链路全通 |
 * | V2.3.0 | 2026-11-11 | binbina | M12：唤醒源识别 + EcuM 唤醒接口 + STOP 模式手动睡眠（!z） |
 * | V2.4.0 | 2026-11-11 | binbina | M13：A/B 分区（双镜像 + 槽尾 meta + UDS 刷非活动槽） |
 * | V2.5.0 | 2026-11-11 | binbina | M14：通信矩阵承载能力（段掩码邮箱 + 硬件/软件双层过滤压测） |
 * | V2.6.0 | 2026-11-11 | binbina | M15：ADC 模块（as-master 无，按三段式补；双单元 + 多通道 + PDB/TRGMUX） |
 * | V2.7.0 | 2026-11-11 | binbina | M18：PWM 模块（PwmLite 4 路、0%/100% 静态电平、同实例同频约束） |
 * | V2.8.0 | 2026-11-11 | binbina | M19：CAN1 真实通信矩阵接入（34 RX 按 PF 分组 / 6 TX / 生成器注入） |
 */

#include "platform_cvm0146.h"

#include "Can.h"
#include "Can_Cfg.h"     /* CAN_CFG_NUM_CHANNELS：通道数由平台配置决定，应用不写死 */
#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "PduR.h"
#include "CanTp.h"
#include "Dcm.h"
#include "Dio.h"
#include "Dio_Cfg.h"
#include "Pwm.h"          /* M18：PWM 验收命令 !l/!L */
#include "Pwm_Cfg.h"
#include "Adc.h"         /* M15：ADC 标准接口 */
#include "Adc_Cfg.h"     /* ADC_CFG_GROUP_PROBE 等组号 */
#include "Port.h"

#include "NvM.h"         /* AUTOSAR 外观：NvM_Init / ReadBlock / WriteBlock / WriteAll */
#include "NvM_Cfg.h"     /* NVM_CFG_ID_*（块 id）与块长 */
#include "Det.h"
#include "Std_Timer.h"   /* 软件定时器：CanNm 的定时基础 */

/* 网络管理（M9）。应用**只碰 Nm/ComM**，不直接调 CanNm ——
 * 直接调 CanNm 等于"绕过 ComM 操作某根总线"，多总线时会状态不一致。
 * CanNm.h 只是为了让 `!m` 打印 CanNm 内部状态时才包含。 */
#include "Nm.h"
#include "ComM.h"
#include "CanNm.h"
#include "Nm_Cfg.h"

/* 信号层（M10）。应用只碰 `Com_SendSignal` / `Com_ReceiveSignal` ——
 * 看不见报文 ID、字节偏移、位序，那些都在 `Com_Cfg.c` 里。 */
#include "Com.h"
#include "Com_Cfg.h"

/* ECU 状态管理（M11）。应用只碰标准接口：
 *   EcuM_Init / EcuM_StartupTwo / EcuM_RequestRUN / EcuM_RequestPOST_RUN
 * 初始化顺序与 BSW 调度全在 `EcuM_Cfg.c` 的表里。 */
#include "EcuM.h"
#include "EcuM_Externals.h"  /* EcuM_EnableWakeupSources / EcuM_CheckWakeup（集成点，M12） */
#include "EcuM_Cfg.h"
#include "ComM_Cfg.h"   /* COMM_USER_APP / COMM_CHANNEL_CAN0 */

#include "Dem.h"          /* 事件上报：Dem_SetEventStatus（AUTOSAR BSW） */
#include "Dem_Cfg.h"      /* 事件号 / DTC 码 / Dem_DtcInfoType */

#include "boot_app.h"      /* A/B：槽地址对账 + 首次自注册 + 启动确认 */
#include "boot_flash_map.h" /* BOOT_SLOT_BASE：banner 里打印本镜像所在槽 */
#include "FlashLoader.h"  /* 0x31/0x34/0x36/0x37 的业务实现（平台层） */

#include <string.h>

/* ============================ [ 常量 ] ============================ */

/** @brief 心跳周期（ms） */
#define HEARTBEAT_MS        (1000u)

/**
 * @brief BSW 周期任务周期（ms）
 * @note  必须与 `CanTp_Cfg.h` / `Dcm_Cfg.h` 的 `*_MAIN_FUNCTION_PERIOD` 一致，
 *        否则定时器换算出来的超时不是真实毫秒数。
 */
#define BSW_PERIOD_MS       (10u)

/** @brief CAN 标准帧发送周期（ms） */
#define CAN_TX_PERIOD_MS    (500u)

/** @brief CAN 扩展帧发送周期（ms）：比标准帧慢一倍，方便在总线上区分 */
#define CAN_EXT_TX_PERIOD_MS (1000u)

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

/** @brief 已收到 `!`，下一个字符是命令 */
static bool s_cmdPending;

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

/* ============================ [ printf 自检 ] ============================ */

/**
 * @brief 打印 printf 格式化自检表
 *
 * @details 每一行都针对一个曾经踩过或极易踩的坑：
 *          | 用例 | 想验证的点 |
 *          |------|------------|
 *          | `%6u` / `%-6u` | 宽度是否被解析、左右对齐 |
 *          | `%06u` / `%08x` | 补零是否生效、补在符号之后 |
 *          | `%d` 负数 / `INT32_MIN` | 符号判定，且取负不溢出 |
 *          | `%+d` / `% d` | 正数也带符号 / 带空格 |
 *          | `%#x` | `0x` 前缀 |
 *          | `%.3d` / `%8.3d` | 精度=最少位数，以及精度与宽度叠加 |
 *          | `%-8s` / `%.3s` | 字符串左对齐 / 最大字符数截断 |
 *          | `%.0d` 传 0 | 精度 0 + 值为 0 时输出空（标准行为） |
 *          | `%%` | 转义为单个 `%` |
 *
 * @note 这是**验收代码**，不是生产代码：M2 之后可以整体删掉，或用编译开关关掉。
 */
static void PrintfSelfTest(void)
{
	Platform_Puts("-- printf self-test -------------------------------\n");

	Platform_Printf("  width    right |%6u|   left |%-6u|\n", 42u, 42u);
	Platform_Printf("  zero pad       |%06u|    hex |%08x|\n", 42u, 0xbeefu);
	Platform_Printf("  hex prefix     |%#x|          |%#X|\n", 0xbeefu, 0xbeefu);
	Platform_Printf("  negative       |%6d|  plus  |%+d|\n", -7, 7);
	Platform_Printf("  space flag     |% d|         |% d|\n", 7, -7);
	Platform_Printf("  precision      |%.3d|  w+p   |%8.3d|\n", 42, 42);
	Platform_Printf("  prec 0 of 0    |%.0d|  (should be empty)\n", 0);
	Platform_Printf("  int32 min      |%d|\n", (int)(-2147483647 - 1));
	Platform_Printf("  string         |%-8s|  trunc |%.3s|\n", "abc", "abcdef");
	Platform_Printf("  char |%c|  percent |100%%|\n", 'X');
	Platform_Printf("  pointer        |%p|\n", (void *)PrintfSelfTest);

	Platform_Puts("--------------------------------------------------\n\n");
}

/* ============================ [ 定时器自检 ] ============================ */

/**
 * @brief 软件定时器自检（启动时跑一次）
 *
 * @details 验的是**时间源**而不是定时器逻辑本身 —— 逻辑是从 as-master 原样
 *          摘过来的（含溢出处理），唯一可能配错的是 `Std_GetTime()`：
 *          它要是返回 0 或者单位搞错（ms 当 us），所有定时器都会"立刻超时"，
 *          而 CanNm 会因此疯狂发 NM 报文、永远不睡。
 *
 *          这类错误在 CAN 上表现是"NM 报文发得太密"，很难反推到时基上，
 *          所以在启动时花 50 ms 把它钉死。
 *
 * @note  允许 ±5 ms 误差：`Std_GetTime()` 的精度就是 1 ms，
 *        加上打印和循环开销。超出这个范围说明时基算错了。
 */
static void TimerSelfTest(void)
{
	Std_TimerType t;
	uint32_t t0;
	uint32_t elapsed;

	t0 = Platform_NowMs();
	Std_TimerInit(&t, 50000u);          /* 50000 us = 50 ms */
	while (!Std_IsTimerTimeout(&t)) {
		/* 忙等：这里就要看真实耗时，不能用 Platform_DelayMs 混过去 */
	}
	elapsed = Platform_NowMs() - t0;

	Platform_Printf("  timer : 50 ms 超时 -> 实测 %u ms (%s)\n",
	                (unsigned)elapsed,
	                ((elapsed >= 50u) && (elapsed <= 55u)) ? "ok" : "CHECK");
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
static void CanTest_Init(void)
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
static void Storage_CmdExec(char c);

/* 故障表打印同理：实现在总线故障区，早于 main 但晚于 CmdExec */
static void Fault_Dump(void);

/* 高频发送（`!f`）也在总线故障区，同样要前置声明 */
static void CanTest_Burst(uint16_t n);
static void CanTest_DumpRxCounters(void);
static void CanTest_SendRealMatrix(void);
static void PwmCmd_Exec(char c);

/* 网络管理（M9）实现在"网络管理"区，晚于 CmdExec */
static void Nm_CmdExec(char c);
static void Nm_DumpState(void);

/* 信号层（M10）实现在"信号层"区，晚于 CmdExec */
static void Com_CmdExec(char c);

/* ECU 状态管理（M11） */
static void EcuM_CmdExec(char c);

/**
 * @brief ADC 探针：启动一次组转换 → 等完成 → 读原始值 → 换算 mV（`!j`）
 *
 * @details 这是 M15 的**最小验证件**，只做一件事：证明
 *          `Adc_StartGroupConversion()` → PDB 软触发 → ADC 转换 → COCO
 *          → `Adc_ReadGroup()` 这条链路真的走通了。
 *
 * @note 为什么不用回调而用轮询：`CVM014x` 的 ADC 完成中断没有被 SDK 封装，
 *       只有 `AdcDrv_GetCocon()` 这个标志位。轮询虽然笨，但语义明确、
 *       不会引入中断优先级问题 —— 先证链路，再谈效率。
 *
 * @warning 超时给 5 ms 是**故意设小**的：一次 12 位转换在几十 MHz 的
 *          ADC 时钟下只要几微秒。如果 5 ms 都没完成，说明触发链路断了
 *          （PDB 没使能 / pretrigger 没配对 / ADC 没 Enable），
 *          而不是"再多等一会就好"。快速失败比慢速等待更容易定位。
 */
static void AdcCmd_Probe(void)
{
	uint8_t g;

	for (g = 0u; g < (uint8_t)ADC_CFG_NUM_GROUPS; g++) {
		Adc_ValueGroupType raw[ADC_CFG_MAX_CH_PER_GROUP];
		uint8_t  n = Adc_Cfg_GroupChannels[g];
		Adc_StatusType st;
		uint32_t t0;
		uint8_t  i;

		Adc_StartGroupConversion((Adc_GroupType)g);

		t0 = Platform_NowMs();
		do {
			st = Adc_GetGroupStatus((Adc_GroupType)g);
		} while ((st != ADC_COMPLETED) && ((Platform_NowMs() - t0) < 5u));

		if (st != ADC_COMPLETED) {
			Platform_Printf("[adc] g%u timeout, status=%u (PDB/trigger chain broken?)\n",
			                (unsigned)g, (unsigned)st);
			continue;
		}

		/* 显式传缓冲区：本探针不依赖 Adc_SetupResultBuffer，
		 * 顺便把"两条用法都支持"这件事验掉。 */
		if (Adc_ReadGroup((Adc_GroupType)g, raw) != E_OK) {
			Platform_Printf("[adc] g%u read failed\n", (unsigned)g);
			continue;
		}

		Platform_Printf("[adc] g%u:", (unsigned)g);
		for (i = 0u; i < n; i++) {
			/* 12 位满量程 4095 对应参考电压 3300 mV */
			Platform_Printf(" %u(%umV)", (unsigned)raw[i],
			                (unsigned)(((uint32_t)raw[i] * 3300u) / 4095u));
		}
		Platform_Puts("\n");
	}
}

/* ============================ [ PWM 验收（M18） ] ============================ */

/**
 * @brief 忙等若干毫秒（基于 SysTick 的 1 ms 计数）
 * @param[in] ms 毫秒数
 * @note  只用于验收命令，不用于业务逻辑 —— 忙等会占满 CPU。
 * @warning 若 `Platform_StopTick()` 被调用过，`Platform_NowMs()` 不再前进，
 *          这里会**死循环**。`!z`（STOP 模式）之后不要再发 `!l`。
 */
static void PwmCmd_DelayMs(uint32_t ms)
{
	uint32_t t0 = Platform_NowMs();

	while ((Platform_NowMs() - t0) < ms) {
		/* 空转等待 */
	}
}

/**
 * @brief 百分比 → 0x8000 满量程的占空比
 * @param[in] pct 0~100（超过 100 按 100 处理）
 * @return 占空比
 * @note  用百分比是因为**功能规范和人对频率/亮度的直觉都是百分比**
 *        （"占空比 20% → 90%"），而 `Pwm_SetDutyCycle()` 要的是 0~0x8000。
 *        换算只在这一个地方做，避免每个调用点各写一遍。
 */
static Pwm_DutyCycleType PwmCmd_Pct(uint32_t pct)
{
	if (pct > 100u) {
		pct = 100u;
	}

	return (Pwm_DutyCycleType)((pct * 0x8000u) / 100u);
}

/**
 * @brief PWM 验收命令（`!l` 演示 / `!L` 复位）
 *
 * @details 为什么需要这个命令：`Pwm` 模块像 `Adc` 一样，**编译通过不等于
 *          代码在跑** —— 没有任何调用点时整个模块会被 `--gc-sections` 丢弃，
 *          镜像里一个 `Pwm_*` 符号都不会有。
 *
 *          演示序列刻意做成**肉眼可见**：官方 `pwm_lite_output` 例程里
 *          `PTD0` / `PTE15` / `PTE16` 分别接 RGB 灯的三个颜色通道，所以
 *          改占空比能直接看到颜色/亮度的变化，不需要示波器。
 *
 *          | 步骤 | 内容 | 验什么 |
 *          |------|------|--------|
 *          | 1 | 全通道 0% | 0% 必须静态低（规范禁止尖峰） |
 *          | 2 | ch0 0→100% 分 10 步 | 顶灯渐亮的时序（IL001 是 20%→90%/2.5s） |
 *          | 3 | ch2 0→100% | 第二路独立输出 |
 *          | 4 | ch3 0→100% | 第三路独立输出 |
 *          | 5 | RGB 同时 50% | 多通道并发 |
 *          | 6 | 恢复配置表初值 | `Pwm_SetDutyCycle` 反复调用的稳定性 |
 */
static void PwmCmd_Exec(char c)
{
	uint16_t i;

	if (c == 'L') {
		/* 恢复配置表里的初值：顶灯灭、三路验证通道各回自己的固定占空比 */
		Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_DOME_LAMP, PwmCmd_Pct(0u));
		Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST1, PwmCmd_Pct(50u));
		Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST2, PwmCmd_Pct(25u));
		Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST3, PwmCmd_Pct(75u));
		Platform_Puts("  pwm restored: ch0=0% ch1=50% ch2=25% ch3=75%\n");
		return;
	}

	Platform_Printf("  pwm: %u ch @ 100Hz on PwmLite0  init=%s\n",
	                (unsigned)PWM_CFG_NUM_CHANNELS,
	                Pwm_IsInitialized() ? "OK" : "**FAILED**");
	Platform_Puts("   pad0=PTD0(RED) pad1=PTD1 pad2=PTE15(GREEN) pad3=PTE16(BLUE)\n");

	/* 1) 全灭：0% 走静态电平分支，波形上应是恒低而不是极窄脉冲 */
	for (i = 0u; i < (uint16_t)PWM_CFG_NUM_CHANNELS; i++) {
		Pwm_SetDutyCycle((Pwm_ChannelType)i, PwmCmd_Pct(0u));
	}
	Platform_Puts("   [1/6] all 0%\n");
	PwmCmd_DelayMs(200u);

	/* 2) 顶灯渐亮：0→100% 分 10 步，每步 150 ms（真实 IL001 是 20%→90% 用 2.5 s） */
	Platform_Puts("   [2/6] ch0 ramp 0->100%\n");
	for (i = 0u; i <= 10u; i++) {
		Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_DOME_LAMP,
		                 PwmCmd_Pct((uint32_t)i * 10u));
		PwmCmd_DelayMs(150u);
	}

	/* 3) 绿（PTE15）渐亮 */
	Platform_Puts("   [3/6] ch2 (GREEN) ramp\n");
	for (i = 0u; i <= 5u; i++) {
		Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST2,
		                 PwmCmd_Pct((uint32_t)i * 20u));
		PwmCmd_DelayMs(150u);
	}

	/* 4) 蓝（PTE16）渐亮 */
	Platform_Puts("   [4/6] ch3 (BLUE) ramp\n");
	for (i = 0u; i <= 5u; i++) {
		Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST3,
		                 PwmCmd_Pct((uint32_t)i * 20u));
		PwmCmd_DelayMs(150u);
	}

	/* 5) 三色同时 50%：多通道并发，肉眼看到接近白 */
	Platform_Puts("   [5/6] RGB all 50%\n");
	Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_DOME_LAMP, PwmCmd_Pct(50u));
	Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST2, PwmCmd_Pct(50u));
	Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST3, PwmCmd_Pct(50u));
	PwmCmd_DelayMs(600u);

	/* 6) 恢复初值 */
	Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_DOME_LAMP, PwmCmd_Pct(0u));
	Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST1, PwmCmd_Pct(50u));
	Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST2, PwmCmd_Pct(25u));
	Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST3, PwmCmd_Pct(75u));
	Platform_Puts("   [6/6] done, restored\n");
}

static void CmdExec(char c)
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
	case 'K':
		/* M14 压测：k=打印接收计数（按邮箱）/ K=清零。
		 * 三个数字要一起看：RX 总数、ISR 次数、按邮箱细分。
		 *   总数 < 对端发送数  → 硬件层丢（掩码/邮箱满/总线错误）
		 *   总数对但应用没看到 → CanIf 软件过滤丢了（表序或掩码错）
		 *   ISR 次数 ≈ 总数   → 每次中断只处理 1 帧，中断开销大 */
		if (c == 'K') {
			uint8_t pdu;

			Platform_CanResetRxCounters();
			for (pdu = 0u; pdu < (uint8_t)CANIF_RX_PDU_NUM; pdu++) {
				s_rxPerPdu[pdu] = 0u;
			}
			Platform_Puts("  can rx counters cleared (mailbox + pdu)\n");
			return;
		}
		CanTest_DumpRxCounters();
		return;
	case 'u':
	case 'U':
	case 'q':
	case 'z':
		/* EcuM：u=释放 RUN / U=回 RUN / q=模式查询（M11）/ z=睡一次（M12） */
		EcuM_CmdExec(c);
		return;
	case 'M':
		/* CAN1 真实矩阵发送（M19）：6 条报文各发一次，首字节 0xA1~0xA6。
		 * Kvaser 挂在 CAN1 上才能收到（也需要它提供 ACK）。 */
		CanTest_SendRealMatrix();
		return;
	case 'l':
	case 'L':
		/* PWM 验收（M18）：l=演示扫描 / L=恢复初值。
		 * 开发板 PTD0/PTE15/PTE16 接 RGB 灯，改占空比肉眼可见。 */
		PwmCmd_Exec(c);
		return;
	case 'j':
		/* ADC 探针（M15）：读一次探针组，打印原始值与换算电压。
		 * 存在的意义是**验证链路**，不是业务功能 ——
		 * 在它出现之前，Adc 模块虽然编译通过，但整个被 --gc-sections 丢弃了
		 * （没有任何调用点），镜像里连一个 Adc_* 符号都没有。
		 * 这也是"编译通过 ≠ 代码在跑"的最好例证。 */
		AdcCmd_Probe();
		return;
	case 'v':
	case 'y':
		/* 信号层：v=信号 dump / y=分组启停（M10） */
		Com_CmdExec(c);
		return;
	case 'a':
	case 'A':
	case 'R':
	case 'm':
		/* 网络管理：a=请求网络 / R=释放网络 / m=状态 dump（M9） */
		Nm_CmdExec(c);
		return;
	case 'f':
		/* 高频发 100 帧（10 ms 间隔），配合 Kvaser 侧同 ID 冲突帧制造位错误。
		 * 为什么需要它：ACK 错误在 error passive 状态下**不再累加 TEC**
		 * （ISO 11898-1 §7.1.3 的特殊规则），所以"对端不应答"这条最直觉的
		 * 路径根本到不了 bus-off —— 必须靠位错误/格式错误这类硬错。 */
		CanTest_Burst(100u);
		return;
	case 'd':
	case 'c':
	case 'w':
	case 'x':
	case 'p':
		/* 存储命令：不涉及 CAN 控制面，转交后直接返回，
		 * 避免下面那段"回读 pduMode/ctrlMode"打出无关信息 */
		Storage_CmdExec(c);
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

/**
 * @brief 发送一帧递增数据（标准帧）
 * @note  数据每帧 +1，是为了在 Kvaser 上"看出它在动"，而不只是"确实有一帧"。
 * @note  M2 的关键变化：应用只说"发 TxPdu 0"，**不用关心它的 CAN ID 和邮箱号** ——
 *        这两样都在 `CanIf_Cfg.c` / `Can_Cfg.c` 里。改 ID 不用动应用。
 */
static void CanTest_SendOne(void)
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
static void CanTest_SendCan1(void)
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
static void CanTest_SendRealMatrix(void)
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
static void CanTest_SendExt(void)
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
static void CanTest_DrainRx(void)
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
static void CanTest_DumpRxCounters(void)
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

static void CanTest_Burst(uint16_t n)
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
static void Fault_PollBusOff(void)
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
static void Fault_Dump(void)
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

/* ============================ [ 网络管理（M9） ] ============================ */

/** @name ComM 状态名（下标 = `ComM_StateType` 取值） */
#define COMM_STATE_NAME_NUM     (5u)
static const char *const s_commStateName[COMM_STATE_NAME_NUM] = {
	"NO_COM_NO_PENDING",
	"NO_COM_REQUEST_PENDING",
	"FULL_COM_NETWORK_REQUESTED",
	"FULL_COM_READY_SLEEP",
	"SILENT_COM",
};

/** @name CanNm 状态名（下标 = `Nm_StateType` 取值） */
#define NM_STATE_NAME_NUM       (8u)
static const char *const s_nmStateName[NM_STATE_NAME_NUM] = {
	"UNINIT",
	"BUS_SLEEP",
	"PREPARE_BUS_SLEEP",
	"READY_SLEEP",
	"NORMAL_OPERATION",
	"REPEAT_MESSAGE",
	"SYNCHRONIZE",
	"OFFLINE",
};

/** @name CanNm 模式名（下标 = `Nm_ModeType` 取值） */
#define NM_MODE_NAME_NUM        (4u)
static const char *const s_nmModeName[NM_MODE_NAME_NUM] = {
	"BUS_SLEEP",
	"PREPARE_BUS_SLEEP",
	"SYNCHRONIZE",
	"NETWORK",
};

/* 说明：M9 时期这里有一个 `ComM_Log()` 弱符号覆盖，用来实时打印
 * ComM 状态变化。M11 换成 as-master 的 ComM 之后，它**没有这个钩子**
 * （标准 ComM 只有 `ComM_GetState` 查询，没有状态变化回调），
 * 所以那段日志被删掉了。
 *
 * 现在的做法：用 `!m` 查当前 ComM/CanNm 状态，用 `!q` 查 EcuM 状态。
 * 想看完整的时间线就用 Kvaser + 串口同时录，或者临时加打印再烧一次 ——
 * 比给参考实现打补丁更划算。 */

/**
 * @brief 打印 NM 三层状态（`!m`）
 *
 * @details @section NMDUMP_WHY 为什么要一次打三层
 *
 *          NM 是三层串联，任何一层卡住，现象都一样：**总线上没有 NM 报文**。
 *
 *          @code
 *          应用 → Nm → CanNm   （下面还有 CanIf → 硬件）
 *          @endcode
 *
 *          单看一层无法区分：
 *
 *          | 现象 | 可能的原因 |
 *          |------|------------|
 *          | `comm=NO_COM` 且 `cannm=BUS_SLEEP` | 应用没请求（`!a` 没发 / 发失败） |
 *          | `comm=FULL_COM` 但 `cannm=BUS_SLEEP` | Nm → CanNm 分发断了（`USE_CANNM` 没定义 / 通道号错） |
 *          | `cannm=NORMAL_OPERATION` 但总线无帧 | 发送侧：CanIf PDU / 邮箱 / 收发器 / 硬件 |
 *
 *          所以一条命令同时打三层，卡在哪一层一眼就看得出来。
 *
 * @note  `mode` 是 Nm 给应用的粗粒度视图（`NETWORK` / `BUS_SLEEP`），
 *        `state` 才是 CanNm 的精确状态机状态。两者不一致是正常的
 *        （比如 `REPEAT_MESSAGE` 时 mode 已经是 `NETWORK`）。
 */
static void Nm_DumpState(void)
{
	Nm_StateType   nmState = NM_STATE_UNINIT;
	Nm_ModeType    nmMode  = NM_MODE_BUS_SLEEP;
	ComM_StateType comm    = COMM_NO_COM_NO_PENDING_REQUEST;

	(void)CanNm_GetState((NetworkHandleType)NM_CFG_CHANNEL_CAN0, &nmState, &nmMode);
	(void)ComM_GetState((NetworkHandleType)NM_CFG_CHANNEL_CAN0, &comm);

	Platform_Printf("[nm] comm=%s(%u) cannm=%s(%u) mode=%s(%u)\n",
	                (comm < COMM_STATE_NAME_NUM) ? s_commStateName[comm] : "?",
	                (unsigned)comm,
	                (nmState < NM_STATE_NAME_NUM) ? s_nmStateName[nmState] : "?",
	                (unsigned)nmState,
	                (nmMode < NM_MODE_NAME_NUM) ? s_nmModeName[nmMode] : "?",
	                (unsigned)nmMode);
}

/**
 * @brief EcuM 的串口命令（`!u` / `!U` / `!q`）
 *
 * @param[in] c 命令字符
 *
 * @note  `!u` 走的是**标准关机路径**：释放 RUN 请求 + 请求 POST_RUN。
 *        之后 EcuM 状态机在下一拍调 `EcuM_AL_EnterPOST_RUN()`，
 *        它会撤销 ComM 的通信请求 → Nm 释放网络 → CanNm 进 ReadySleep
 *        → 2 s 后 PrepareBusSleep → ComM 停掉 Com 分组。
 *
 * @note  `!q` 读的是集成层自己记的模式（`EcuM_AL_GetMode`），
 *        因为 as-master 的 `EcuM.c` 没实现标准接口 `EcuM_GetCurrentMode()`。
 */
static void EcuM_CmdExec(char c)
{
	Std_ReturnType rc;

	switch (c) {
	case 'u':
		rc = EcuM_ReleaseRUN((EcuM_UserType)0u);
		if (rc == E_OK) {
			rc = EcuM_RequestPOST_RUN((EcuM_UserType)0u);
		}
		Platform_Printf("[ecum] ReleaseRUN + RequestPOST_RUN -> %s\n",
		                (rc == E_OK) ? "accepted" : "FAIL");
		break;

	case 'U':
		rc = EcuM_ReleasePOST_RUN((EcuM_UserType)0u);
		if (rc == E_OK) {
			rc = EcuM_RequestRUN((EcuM_UserType)0u);
		}
		Platform_Printf("[ecum] ReleasePOST_RUN + RequestRUN -> %s\n",
		                (rc == E_OK) ? "accepted" : "FAIL");
		break;

	case 'q':
		Platform_Printf("[ecum] mode=%u (0=OFF 1=STARTUP 2=RUN 3=POST_RUN 5=SLEEP)\n",
		                (unsigned)EcuM_AL_GetMode());
		break;

	case 'z':
		/**
		 * @brief 手动睡一次，醒来报告唤醒源（M12）
		 *
		 * @details @section CMDZ_WHY 这条命令验的是什么
		 *
		 *          它验证的是 **WFI 通路 + 唤醒源读取**，不是低功耗指标：
		 *          @code
		 *          配 100 ms 兜底节拍 → WFI → 被 tick 唤醒
		 *          → 读 PowerDrv_GetWakeupSource() → 恢复 1 ms 节拍
		 *          @endcode
		 *
		 *          @warning **为什么不完全停掉 SysTick**：
		 *          停了就有睡死风险 —— 本工程还没有可用的外部唤醒源
		 *          （收发器 WAKE 引脚硬件没接，PTE4 端口唤醒也没配）。
		 *          一旦睡死只能断电重启，这个代价不能由一条测试命令承担。
		 *
		 *          把节拍放大到 100 ms 有两个好处：
		 *          1. 兜底：100 ms 后一定醒，**不可能睡死**；
		 *          2. 可测：1 ms 节拍下 WFI 几乎立刻返回，什么都量不出；
		 *             100 ms 下能看到 `Platform_NowMs()` 只前进了 1，
		 *             而实际过了约 100 ms —— 这就是"CPU 真的停过"的证据。
		 *
		 * @note  睡着期间所有 10 ms 节拍任务都停了，醒来后
		 *        CanTp/Dcm/NM 的定时器会"跳"一下。这是停节拍的必然结果，
		 *        只在测试命令里出现，正常运行路径不会睡。
		 */
		Platform_Puts("[sleep] 进 STOP(Sleep) 模式，100 ms 兜底唤醒...\n");
		/* 走 EcuM 的标准接口使能唤醒源（当前只记录 + 打日志，
		 * 因为唯一能关的中断是 SysTick，而它是兜底，见 ecum_callout.c） */
		EcuM_EnableWakeupSources((EcuM_WakeupSourceType)ECUM_WKSOURCE_CAN0);

		{
			uint32_t t0 = Platform_NowMs();

			Platform_SetTickPeriodMs(100u);
			Platform_EnterStopMode();
			Platform_StartTick();

			Platform_Printf("[sleep] 醒来: tick +%u (约 %u ms), 唤醒源=%s(%u)\n",
			                (unsigned)(Platform_NowMs() - t0),
			                (unsigned)((Platform_NowMs() - t0) * 100u),
			                Platform_GetWakeupSourceName(Platform_GetWakeupSource()),
			                (unsigned)Platform_GetWakeupSource());
		}

		/* 走一遍标准唤醒链路：EcuM_CheckWakeup → ComM → Nm → CanNm
		 * 即使这次是 tick 唤醒（不是 CAN），也要让它跑一遍 ——
		 * 验证接口可达，并且日志能说清"实际是什么唤醒的"。 */
		EcuM_CheckWakeup((EcuM_WakeupSourceType)ECUM_WKSOURCE_CAN0);
		break;

	default:
		Platform_Printf("[ecum] unknown '%c'\n", c);
		break;
	}
}

/**
 * @brief 网络管理的串口命令（`!a` / `!R` / `!m`）
 *
 * @param[in] c 命令字符
 *
 * @note  **走 `Nm_*` 而不是 `CanNm_*`**：应用层不应该知道总线上用的是
 *        CAN 还是其它 NM。这条约束在只有一根 CAN 时看不出价值，
 *        但多一根 CAN 时，`CanNm_*` 的调用点就得全部改一遍。
 *
 * @note  `NetworkRequest` 只置一个标志，真正的动作在下一个
 *        `CanNm_MainFunction()` 里 —— 所以 `!a` 之后立刻 `!m` 看到的
 *        可能还是 `BUS_SLEEP`。这是 AUTOSAR 的异步语义，不是 bug。
 *        验收脚本里要等 50 ms 以上再查状态。
 */
static void Nm_CmdExec(char c)
{
	Std_ReturnType rc;

	switch (c) {
	case 'a':
		/*
		 * @note **M11 起走 ComM，不再直接调 `Nm_NetworkRequest`。**
		 *
		 *       AUTOSAR 里应用不能绕过通信管理器直接操作某根总线：
		 *       否则 ComM 认为"没有通信需求"，而 NM 已经在发报文，
		 *       两边状态长期不一致。多总线时这种不一致会直接导致
		 *       "一根线醒了、另一根没醒"。
		 *
		 *       链路：ComM_RequestComMode → 仲裁 → Nm_NetworkRequest
		 *             → CanNm_NetworkRequest → NM 报文发出
		 */
		rc = ComM_RequestComMode((ComM_UserHandleType)COMM_USER_APP,
		                         (ComM_ModeType)COMM_FULL_COMMUNICATION);
		Platform_Printf("[comm] RequestComMode(FULL) -> %s\n", (rc == E_OK) ? "accepted" : "FAIL");
		break;

	case 'A':
		/**
		 * @brief 模拟"总线活动把 ECU 唤醒"（`ComM_EcuM_WakeUpIndication`）
		 *
		 * @details @section NMPASSIVE 为什么不再直接调 `Nm_PassiveStartUp`
		 *
		 *          M9 时这里是直接 `Nm_PassiveStartUp()`。接上 ComM 之后那是
		 *          **越层调用**：ComM 并不知道有人在被动启动，它的 `nmFlag`
		 *          与通道状态还是旧的，于是"NM 在发报文、ComM 认为没通信"，
		 *          两边长期不一致。
		 *
		 *          AUTOSAR 的标准入口是：
		 *          @code
		 *          收发器检测到总线活动 → EcuM_CheckWakeup
		 *                → ComM_EcuM_WakeUpIndication(channel)
		 *                → ComM 置 COMM_NM_FLAG_NETWORK_START
		 *                → 下一拍 MainFunction 走 PassiveStartup
		 *                → Nm_PassiveStartUp → CanNm 进 RepeatMessage
		 *          @endcode
		 *
		 *          @warning **as-master 的 ComM 没有实现 `ComM_EcuM_WakeUpIndication()`**
		 *          （`ComM.h:105` 只有声明，全仓无定义，链接期才报错）。
		 *          所以这里调用**同一条链路的后半段**
		 *          `ComM_Nm_NetworkStartIndication()` —— 它做的事完全一样：
		 *          `ComM.c:612` 置 `COMM_NM_FLAG_NETWORK_START`，
		 *          下一拍 `ComM_MainFunction()` 就会走 `COMM_NOCOM_STARTUP_PASSIVE`
		 *          → `ComM_Nm_PassiveStartup()`。
		 *
		 *          等 M12 接上收发器唤醒中断后，正确写法是在 EcuM 的
		 *          wakeup 处理里补一个 `ComM_EcuM_WakeUpIndication()` 的实现
		 *          （一行转调本函数），而不是在应用层继续调 Nm 侧入口。
		 *
		 * @note  被动启动不置 `CANNM_REQUEST_MASK`：报文里的 CBV 主动唤醒位是 0，
		 *        表示"我是被叫醒的，不是我叫醒的"。跑完 `RepeatMessageTime`
		 *        之后如果本地没有通信请求，会自动落到 `ReadySleep` 再睡回去。
		 */
		ComM_Nm_NetworkStartIndication((NetworkHandleType)COMM_CHANNEL_CAN0);
		Platform_Puts("[comm] Nm NetworkStartIndication -> issued\n");
		break;

	case 'R':
		rc = ComM_RequestComMode((ComM_UserHandleType)COMM_USER_APP,
		                         (ComM_ModeType)COMM_NO_COMMUNICATION);
		Platform_Printf("[comm] RequestComMode(NO_COM) -> %s\n", (rc == E_OK) ? "accepted" : "FAIL");
		break;

	case 'm':
		Nm_DumpState();
		break;

	default:
		Platform_Printf("[nm] unknown '%c'\n", c);
		break;
	}
}

/* ============================ [ 信号层（M10） ] ============================ */

/**
 * @brief TX 滚动计数（应用侧的真实值）
 * @note  这是"应用变量"，和报文缓冲里的那个字节不是同一个东西。
 *        `Com_SendSignal()` 负责把它搬进报文缓冲。
 *        之所以要在应用侧留一份，是因为缓冲随时会被发送覆盖/初始化，
 *        应用不能拿它当自己的状态存储。
 */
static uint8_t s_comTxCounter;

/** @brief TX 状态位：固定 1，用于验证 **1 位信号**的位打包 */
static uint8_t s_comTxFlag = 1u;

/** @brief TX 模拟量：固定 0xABC，用于验证 **12 位跨字节**打包 */
static uint16_t s_comTxLevel = 0x0ABCu;

/** @brief 10 ms 拍计数：满 10 拍（100 ms）更新一次 TX 信号 */
static uint16_t s_comTick = COM_CONVERT_MS_TO_MAIN_CYCLES(100u);

/** @brief IPdu 分组当前是否运行（`!y` 用） */
static bool s_comGroupOn = true;

/**
 * @brief 应用侧的信号更新（在主循环里按 10 ms 节拍调用）
 *
 * @details @section COMAPP_TICK 为什么更新周期要和 CycleTime 对齐
 *
 *          `Com_MainFunctionTx()` 到点就把**当前缓冲**整帧发出去。
 *          如果应用更新比发送慢，同一帧值会被重复发好几次；
 *          如果比发送快，中间的若干次更新会被"跳过"，总线上只能看到
 *          其中一部分值。
 *
 *          两者都用同一个 10 ms 节拍、同一个周期（100 ms），
 *          并且**先更新、后调用 `Com_MainFunction()`**，
 *          于是每一帧恰好对应一个新值，脚本可以断言"每帧 +1"。
 *
 *          随机相位（比如应用用 `Platform_NowMs()` 自己判周期）会让
 *          偶发的跳过变得无法解释 —— 那不是 bug，是两个不同节拍的
 *          正常交错，但会让验收脚本时而过时而不时不过。
 */
static void Com_AppTick(void)
{
	uint8_t  c;
	uint8_t  f;
	uint16_t l;

	if (s_comTick > 0u) {
		s_comTick--;
	}
	if (s_comTick > 0u) {
		return;
	}
	s_comTick = COM_CONVERT_MS_TO_MAIN_CYCLES(100u);

	c = (uint8_t)(s_comTxCounter + 1u);
	f = s_comTxFlag;
	l = s_comTxLevel;

	/* 三个信号都发一遍，而不是只发变化的那个：
	 * 单发 counter 时，flag/level 只在 `Com_IpduGroupStart()` 那一次
	 * 被写进缓冲，之后一旦有人（比如 GC 之外的误写）改了缓冲，
	 * 就没有修复路径。每次全量刷新，代价是三次几字节的位操作。 */
	(void)Com_SendSignal((Com_SignalIdType)COM_SIG_TX_COUNTER, &c);
	(void)Com_SendSignal((Com_SignalIdType)COM_SIG_TX_FLAG, &f);
	(void)Com_SendSignal((Com_SignalIdType)COM_SIG_TX_LEVEL, &l);

	s_comTxCounter = c;
}

/**
 * @brief 打印信号值（`!v`）
 *
 * @details 打印的是**两条不同路径的结果**，这正是一条命令同时看两件事的价值：
 *
 *          | 侧 | 数据来源 | 证明了什么 |
 *          |----|----------|------------|
 *          | tx | 应用自己的变量 | 应用想发什么 |
 *          | rx | `Com_ReceiveSignal()` | Com 从总线上解出了什么 |
 *
 *          tx 与 rx 之间隔着"打包 → 总线 → 解包"，两者一致说明整条链路通。
 *          验收脚本还会用 Kvaser 抓实际帧，三者对齐才算真的对。
 *
 * @note  rx 侧读不到（返回 E_NOT_OK）时打 `NG`。读不到的原因通常是
 *        Com 未初始化或信号 ID 越界 —— 不是"对端没发"，
 *        对端没发会读到超时替换值（0xEE），两者含义完全不同。
 */
static void Com_DumpSignals(void)
{
	uint8_t  rxCnt  = 0u;
	uint16_t rxTemp = 0u;
	Std_ReturnType r1;
	Std_ReturnType r2;

	r1 = Com_ReceiveSignal((Com_SignalIdType)COM_SIG_RX_COUNTER, &rxCnt);
	r2 = Com_ReceiveSignal((Com_SignalIdType)COM_SIG_RX_TEMP, &rxTemp);

	Platform_Printf("[com] tx cnt=%u flag=%u level=0x%03X | rx cnt=%u(%s) temp=%u(%s) | grp=%u\n",
	                (unsigned)s_comTxCounter, (unsigned)s_comTxFlag,
	                (unsigned)s_comTxLevel,
	                (unsigned)rxCnt, (r1 == E_OK) ? "ok" : "NG",
	                (unsigned)rxTemp, (r2 == E_OK) ? "ok" : "NG",
	                (unsigned)(s_comGroupOn ? 1u : 0u));
}

/**
 * @brief 信号层的串口命令（`!v` / `!y`）
 *
 * @param[in] c 命令字符
 *
 * @note  `!y` 停的是 **IPdu 分组**，不是 Com 本身。区别很重要：
 *        分组停了之后 `Com_SendSignal()` 照常成功（只是改缓冲），
 *        `Com_MainFunctionTx()` 跳过这个组不发 —— 恢复时不需要
 *        重新初始化 Com，一帧都不会丢配置。
 *
 * @note  停组时把 `s_comTxCounter` 一起清零：`Com_IpduGroupStart(TRUE)`
 *        会用初值重刷报文缓冲，如果应用侧计数器不清零，
 *        恢复后的第一帧会和缓冲里的初值不一致，看起来像"丢了几帧"。
 */
static void Com_CmdExec(char c)
{
	switch (c) {
	case 'v':
		Com_DumpSignals();
		break;

	case 'y':
		if (s_comGroupOn) {
			Com_IpduGroupStop((Com_IpduGroupIdType)COM_GROUP_TEST);
			s_comGroupOn = false;
			Platform_Puts("[com] group 0 STOPPED (TX/RX suspended)\n");
		} else {
			Com_IpduGroupStart((Com_IpduGroupIdType)COM_GROUP_TEST, TRUE);
			s_comTxCounter = 0u;
			s_comTick = COM_CONVERT_MS_TO_MAIN_CYCLES(100u);
			s_comGroupOn = true;
			Platform_Puts("[com] group 0 STARTED (100 ms)\n");
		}
		break;

	default:
		Platform_Printf("[com] unknown '%c'\n", c);
		break;
	}
}

/* ============================ [ 存储（M4） ] ============================ */

/**
 * @brief 启动计数块里"魔数"的偏移
 * @details 块内容 = `uint32 计数 + uint32 魔数`。
 *          魔数的用途是区分"新片（数据区全 0xFF → ReadAll 装的是 ROM 默认值）"
 *          和"真的数到了 0"。没有它的话，一块从没写过的芯片和一个计数为 0 的
 *          芯片无法区分，掉电测试会得出错误结论。
 */
#define BOOTCNT_MAGIC_OFF       (4u)

/** @brief 魔数取值：ASCII "BCM1" 按小端拼成 u32 */
#define BOOTCNT_MAGIC           (0x314D4342u)

/**
 * @brief 等待存储栈作业完成的超时（ms）
 * @note  上电首次（扇区全擦）需要：擦 12 个 1 KB 扇区 + 写扇区头 + 扫描 2×12 KB，
 *        实测在百毫秒量级；给 5 s 是留足余量并在超时时能明确报出来。
 */
#define STORAGE_TIMEOUT_MS      (5000u)

/**
 * @brief 压力测试的写入次数（`!p`）
 * @details FEE 的扇区是 12 KB，每次写一个 CONFIG 块消耗
 *          `ALIGN8(32+1)=40` 字节数据 + 16 字节块头 = 56 字节。
 *          12288 / 56 ≈ 219 次把活动扇区写满，第 220 次起触发 GC
 *          （搬备份扇区 + 擦活动扇区）。取 400 次可以跑过 **1~2 次 GC**，
 *          而 GC 是这套存储栈里唯一"平时看不出来、坏起来丢全部数据"的路径。
 */
#define STORAGE_STRESS_CNT      (400u)

/** @brief 本机启动次数（ReadAll 之后 +1 再写回） */
static uint32_t s_bootCount;

/** @brief 存储栈是否初始化成功（失败时后面的命令直接跳过，不去踩未初始化的引擎） */
static bool s_storageReady;

/**
 * @brief 等存储栈完全空闲（含初始化、扇区扫描、写作业）
 * @param[in] timeoutMs 超时
 * @retval true  空闲
 * @retval false 超时
 * @note  必须**在同一处**同时驱动 `NvM_MainFunction()`，因为引擎的状态推进
 *        完全靠这只函数。光等不驱动 = 永远等不到。
 */
static bool Storage_WaitIdle(uint32_t timeoutMs)
{
	uint32_t t0 = Platform_NowMs();
	MemIf_StatusType st;

	for (;;) {
		st = NvM_GetStatus();     /* 先取一次快照，循环判断和打印用同一个值 */
		if (st == MEMIF_IDLE) {
			return true;
		}

		NvM_MainFunction();

		if ((uint32_t)(Platform_NowMs() - t0) >= timeoutMs) {
			/* 超时才打现场：正常路径一行都不打，不干扰验收脚本的逐行断言。 */
			Platform_Printf("[nvm] TIMEOUT %u ms: memif=%u fee=%u nvm=%u rjob=%u jr=%u jobs=0x%02x w=%u\n",
			                (unsigned)(Platform_NowMs() - t0), (unsigned)st,
			                (unsigned)NvM_PortDbgFeeState(),
			                (unsigned)NvM_PortDbgNvmState(), (unsigned)NvM_PortDbgReadJob(),
			                (unsigned)NvM_PortDbgJobResult(), (unsigned)NvM_PortDbgJobs(),
			                (unsigned)NvM_Cfg_WriteCount);
			return false;
		}
	}
}

/** @brief 小端取 u32（不依赖对齐，也不依赖编译器的大小端设置） */
static uint32_t Storage_GetU32(const uint8_t *p)
{
	return (uint32_t)p[0]
	     | ((uint32_t)p[1] << 8)
	     | ((uint32_t)p[2] << 16)
	     | ((uint32_t)p[3] << 24);
}

/** @brief 小端写 u32 */
static void Storage_PutU32(uint8_t *p, uint32_t v)
{
	p[0] = (uint8_t)(v & 0xFFu);
	p[1] = (uint8_t)((v >> 8) & 0xFFu);
	p[2] = (uint8_t)((v >> 16) & 0xFFu);
	p[3] = (uint8_t)((v >> 24) & 0xFFu);
}

/**
 * @brief 存储栈初始化 + 启动计数
 *
 * @details 顺序（每一步都必须等上一步真完成，引擎是异步的）：
 *          @code
 *          NvM_Init()        配置引擎，此后引擎开始扇区扫描
 *          Storage_WaitIdle() 等扫描结束（新片会先擦扇区 + 写扇区头）
 *          NvM_ReadAll()     全部块读进 RAM（读不消耗寿命）
 *          Storage_WaitIdle() 等读完
 *          改 BOOTCNT 的 RAM 映像 → NvM_WriteBlock(id, NULL)
 *          @endcode
 *
 *          @note `NvM_WriteBlock(id, NULL)` 用块**自己的 RAM 映像**作数据源，
 *          这是 AUTOSAR 的标准用法 —— Dcm 的 0x27 安全访问计数
 *          （`NvM_WriteBlock(SecurityNvMBlkId, NULL)`）走的就是这条路。
 *          这里先用启动计数把这条路径验证通，将来开 0x27 就不用再怀疑接口。
 */
/** @brief 阶段一（`NvM_Init`）耗时（ms），供阶段二打横幅用 */
static uint32_t s_storageInitMs;

/**
 * @brief 存储栈初始化 · 阶段一：`NvM_Init`（EcuM DriverInitOne）
 *
 * @note  为什么拆成两段：AUTOSAR 把初始化分成 Zero / One / Two，
 *        `NvM_ReadAll` 属于 Two（"OS 启动后读回非易失数据"），
 *        而 `NvM_Init` 属于 One（"模块可用"）。EcuM 的配置表
 *        需要这两个入口分开，才能把读回放到正确时机。
 *
 * @note  `NvM_Init` 内部会完成 `FeeAc_Init()` 与 `Fee_Configure()`
 *        （见 `NvM_Cfg.c` 的 `NvM_PortInit`），所以 EcuM 的 Zero 阶段
 *        不需要单独列 Fee 的初始化。
 */
void Storage_InitStack(void)
{
	uint32_t t0 = Platform_NowMs();

	NvM_Init(NULL);
	if (!Storage_WaitIdle(STORAGE_TIMEOUT_MS)) {
		Platform_Printf("  nvm   : init TIMEOUT (%u ms)\n",
		                (unsigned)(Platform_NowMs() - t0));
		return;
	}

	s_storageInitMs = Platform_NowMs() - t0;
}

/**
 * @brief 存储栈初始化 · 阶段二：读回 + 启动计数 + Dem 绑定（EcuM DriverInitTwo）
 *
 * @warning **超时保护必须保留。** as-master 的 `EcuM_AL_DriverInitTwo`
 *          用一个不带超时的 `while (MEMIF_IDLE != NvM_GetStatus())` 等读回，
 *          一旦存储栈异常就永久卡死、连串口都进不去。这里每个等待都有
 *          `STORAGE_TIMEOUT_MS`，超时打印后返回，至少还能打诊断。
 */
void Storage_InitData(void)
{
	uint8_t *ram = NULL;
	uint16_t len = 0u;
	uint32_t t0;
	uint32_t tRead;

	t0 = Platform_NowMs();
	NvM_ReadAll();
	if (!Storage_WaitIdle(STORAGE_TIMEOUT_MS)) {
		Platform_Printf("  nvm   : ReadAll TIMEOUT (%u ms)\n",
		                (unsigned)(Platform_NowMs() - t0));
		return;
	}
	tRead = Platform_NowMs() - t0;

	if ((NvM_GetBlockDataPtrAndLength((NvM_BlockIdType)NVM_CFG_ID_BOOTCNT,
	                                  (void **)&ram, &len) != E_OK) ||
	    (ram == NULL) || (len < NVM_CFG_BLK_BOOTCNT_SIZE)) {
		Platform_Puts("  nvm   : bootcnt block unavailable\n");
		return;
	}

	if (Storage_GetU32(&ram[BOOTCNT_MAGIC_OFF]) != BOOTCNT_MAGIC) {
		s_bootCount = 0u;       /* 新片或被擦过 */
	} else {
		s_bootCount = Storage_GetU32(&ram[0]);
	}

	s_bootCount++;
	Storage_PutU32(&ram[0], s_bootCount);
	Storage_PutU32(&ram[BOOTCNT_MAGIC_OFF], BOOTCNT_MAGIC);

	if (NvM_WriteBlock((NvM_BlockIdType)NVM_CFG_ID_BOOTCNT, NULL) != E_OK) {
		Platform_Puts("  nvm   : bootcnt write REJECTED\n");
		return;
	}
	if (!Storage_WaitIdle(STORAGE_TIMEOUT_MS)) {
		Platform_Puts("  nvm   : bootcnt write TIMEOUT\n");
		return;
	}

	s_storageReady = true;

	/* Dem 也挂在 DTC 块的 RAM 映像上，同样必须在 ReadAll 之后。
	 * 顺序：先 Dem_Init 拿到表指针，再告诉它本次启动序号（写进 firstBoot/lastBoot）。 */
	Dem_Init(NULL);
	Dem_SetBootSequence(s_bootCount);

	Platform_Printf("  nvm   : DFlash 2x12 KB, %u blocks, boot #%u (init %u ms, read %u ms)\n",
	                (unsigned)NVM_CFG_BLOCK_NUM, (unsigned)s_bootCount,
	                (unsigned)s_storageInitMs, (unsigned)tRead);
}

/**
 * @brief 连续写 CONFIG 块 N 次，强制触发 FEE 的 GC（`!p`）
 *
 * @details 为什么必须专门测 GC：
 *          FEE 是日志式存储，平时只往活动扇区尾部追加；写满后要把每个块的
 *          **最新版本**搬到备份扇区、再把活动扇区擦掉。这条路径平时一次都走不到，
 *          出错的表现是"跑了几个星期之后数据突然全没了"。
 *          它的正确性无法靠读代码保证 —— 只能真写满一遍看数据还在不在。
 *
 * @note 阻塞式实现（每写一次等引擎空闲）。测试命令不需要并发，
 *       循环里等清楚比"发一堆请求再看结果"容易定位得多。
 */
static void Storage_Stress(void)
{
	uint8_t *ram = NULL;
	uint16_t len = 0u;
	uint16_t i;
	uint32_t t0 = Platform_NowMs();

	if (NvM_GetBlockDataPtrAndLength((NvM_BlockIdType)NVM_CFG_ID_CONFIG,
	                                 (void **)&ram, &len) != E_OK) {
		Platform_Puts("[nvm] stress: config block unavailable\n");
		return;
	}

	for (i = 0u; i < (uint16_t)STORAGE_STRESS_CNT; i++) {
		ram[2]++;       /* 第 3 字节当写计数（与 !w 用的 [1] 分开，互不干扰） */

		if (NvM_WriteBlock((NvM_BlockIdType)NVM_CFG_ID_CONFIG, NULL) != E_OK) {
			Platform_Printf("[nvm] stress REJECTED at #%u\n", (unsigned)i);
			return;
		}
		if (!Storage_WaitIdle(STORAGE_TIMEOUT_MS)) {
			Platform_Printf("[nvm] stress TIMEOUT at #%u\n", (unsigned)i);
			return;
		}
	}

	Platform_Printf("[nvm] stress done: %u writes in %u ms, config[2]=%u\n",
	                (unsigned)STORAGE_STRESS_CNT,
	                (unsigned)(Platform_NowMs() - t0), (unsigned)ram[2]);
}

/**
 * @brief 打印所有块的状态与前 8 字节
 * @note  `st` 是 AUTOSAR 的 `NvM_RequestResultType`：
 *        0=OK 1=NOT_OK 2=PENDING 3=INTEGRITY_FAILED。
 *        掉电测试就靠它 —— **拔电重启后 `st` 仍然是 0** 才算数据保住了。
 */
static void Storage_Dump(void)
{
	static const char *const names[NVM_CFG_BLOCK_NUM] = { "BOOTCNT", "CONFIG", "VIN", "DTC" };
	uint8_t *ram;
	uint16_t len;
	uint16_t i;
	uint16_t j;
	NvM_RequestResultType st;

	Platform_Printf("[nvm] status=%u dump:\n", (unsigned)NvM_GetStatus());

	for (i = 0u; i < (uint16_t)NVM_CFG_BLOCK_NUM; i++) {
		ram = NULL;
		len = 0u;
		st  = NVM_REQ_NOT_OK;

		(void)NvM_GetBlockDataPtrAndLength((NvM_BlockIdType)i, (void **)&ram, &len);
		(void)NvM_GetErrorStatus((NvM_BlockIdType)i, &st);

		Platform_Printf("  %u %-8s len=%u st=%u data=",
		                (unsigned)i, names[i], (unsigned)len, (unsigned)st);

		if (ram != NULL) {
			for (j = 0u; (j < 8u) && (j < len); j++) {
				Platform_Printf("%02x ", (unsigned)ram[j]);
			}
		}
		Platform_Puts("\n");
	}
}

/**
 * @brief 存储相关的串口命令（`!` 前缀）
 * @param[in] c 命令字符
 * @note  与 CAN 的控制命令共用 `!` 前缀，命令字符不重复：
 *        CAN 用 o/n/s/g/t/r，存储用 d/c/w/x。
 */
static void Storage_CmdExec(char c)
{
	uint8_t *ram;
	uint16_t len;
	uint8_t tmp[8];

	if (!s_storageReady) {
		Platform_Puts("[nvm] storage not ready\n");
		return;
	}

	switch (c) {
	case 'd':
		Storage_Dump();
		break;

	case 'c':
		/* 把"已修改"的块全部落盘（脏块掩码，不是全写） */
		NvM_WriteAll();
		Platform_Puts("[nvm] WriteAll started (dirty blocks only)\n");
		break;

	case 'w':
		/* 验证 AUTOSAR 的延迟落盘路径：改 RAM → 标脏 → WriteAll */
		ram = NULL;
		len = 0u;
		if (NvM_GetBlockDataPtrAndLength((NvM_BlockIdType)NVM_CFG_ID_CONFIG,
		                                 (void **)&ram, &len) != E_OK) {
			Platform_Puts("[nvm] config block unavailable\n");
			break;
		}
		ram[1]++;
		(void)NvM_SetRamBlockStatus((NvM_BlockIdType)NVM_CFG_ID_CONFIG, TRUE);
		NvM_WriteAll();
		Platform_Printf("[nvm] config[1]=%u marked dirty, WriteAll started\n",
		                (unsigned)ram[1]);
		break;

	case 'p':
		/* 连续写 400 次，强制触发 GC —— 验证"写满一个扇区后数据不丢" */
		Storage_Stress();
		break;

	case 'x':
		/* 故意用非法块 id，验证 DET 上报（应该看到 [det] mod=20 ...） */
		Platform_Printf("[nvm] illegal block id test: rc=%u\n",
		                (unsigned)NvM_ReadBlock((NvM_BlockIdType)(NVM_CFG_BLOCK_NUM + 5u),
		                                        tmp));
		break;

	default:
		Platform_Printf("[nvm] unknown '%c'\n", c);
		break;
	}
}

/**
 * @brief DET 日志钩子（覆盖 `infras/system/Det/Det.c` 里的弱符号）
 * @note  参数错误的唯一可见出口。没有它的话，`NvM_ReadBlock()` 只返回
 *        `E_NOT_OK`，"块 id 写错了"和"引擎忙"在板上没有任何区别。
 */
void Det_Log(uint16_t ModuleId, uint8_t ApiId, uint8_t ErrorId);

void Det_Log(uint16_t ModuleId, uint8_t ApiId, uint8_t ErrorId)
{
	Platform_Printf("[det] mod=%u api=0x%02x err=0x%02x\n",
	                (unsigned)ModuleId, (unsigned)ApiId, (unsigned)ErrorId);
}

/* ============================ [ 入口 ] ============================ */

int main(void)
{
	uint32_t nextBeat = 0u;
	uint32_t nextTx   = 0u;
	uint32_t nextExt  = 0u;
	uint32_t nextBsw  = 0u;
	uint32_t beat     = 0u;
	int ch;

	Platform_Init();
	Platform_InitTick();

	Platform_Puts("\n");
	Platform_Puts("========================================\n");
	Platform_Puts("  AS / CVM0146  bring-up  (M4)\n");
	Platform_Puts("  build : " __DATE__ " " __TIME__ "\n");
	Platform_Puts("  core  : PLL 120 MHz\n");
	Platform_Puts("  uart  : UART2 115200 8N1  (PC: COM2)\n");
	/* A/B：本镜像链接在哪个槽。与 boot 打印的 "jump to slot X" 对照，
	 * 能一眼看出"是不是真的换了镜像"—— 升级排查时这是第一个要确认的事。 */
	Platform_Printf("  slot  : %c  (link 0x%08X)\n",
	                (APP_SLOT_INDEX == 0) ? 'A' : 'B',
	                (unsigned)BOOT_SLOT_BASE((uint8_t)APP_SLOT_INDEX));

	/* 本次上电/复位是被什么唤醒的 —— 实车没有调试器，这一行是
	 * 排查"为什么自己醒了 / 为什么没睡"的第一手证据。
	 * 纯读操作，不影响任何状态。 */
	Platform_Printf("  wake  : %s (%u)%s\n",
	                Platform_GetWakeupSourceName(Platform_GetWakeupSource()),
	                (unsigned)Platform_GetWakeupSource(),
	                (Platform_GetWakeupSource() == PLATFORM_WAKEUP_NONE)
	                    ? "  [cold boot]" : "  [woken from low power]");

	/* 定时器自检放在最前：50 ms 忙等，此时通信栈还没起，不干扰任何周期断言 */
	TimerSelfTest();

	/* ------------------------------------------------------------------
	 * A/B 分区配合（M13）
	 *
	 * 1) 对账：本镜像的链接地址必须等于 `APP_SLOT_INDEX` 对应的槽基址，
	 *    不等说明烧错了文件（把 AppB 刷进了 A 槽）—— 就地停住，
	 *    否则第一次解引用全局变量就跳飞，现场表现为"偶发死机"。
	 * 2) 首次烧写（槽尾 meta 是 0xFF）时补写 meta，让下次上电走正规流程。
	 *    已有 meta 时**不碰 Flash**，正常启动零擦写。
	 * ------------------------------------------------------------------ */
	BootApp_Init();

	/* 刷写业务初始化：锁定"当前活动槽"，之后 0x31/0x34 一律拒绝擦写它。
	 * 放在 BootApp_Init 之后 —— 后者刚扫过 meta，这里再扫一次是幂等的；
	 * 顺序反过来也能工作，但会多读一次 Flash（约 1 ms）。 */
	FlashLoader_Init();

	/* ------------------------------------------------------------------
	 * 启动序列交给 EcuM，**不再手工按顺序调 Init**
	 *
	 * 三个阶段对应 `EcuM_Cfg.c` 的三张表：
	 *   EcuM_Init()       → DriverInitZero（Port / Can）
	 *                     + DriverInitOne （CanIf … CanSM + NvM_Init）
	 *   EcuM_StartupTwo() → DriverInitTwo （NvM_ReadAll + 启动计数 + Dem）
	 *
	 * 之所以必须先 `StartupTwo` 再 `RequestRUN`：进 RUN 会立刻让
	 * ComM/CanSM 启动总线并开始发 NM 报文，而 NM 的状态上报依赖
	 * NvM/Dem 已经就绪（故障要能落盘）。顺序反了不会崩，但
	 * 总线起来后最初几秒的故障记录会丢。
	 * ------------------------------------------------------------------ */
	EcuM_Init();
	EcuM_StartupTwo();

	/* ------------------------------------------------------------------
	 * ADC 初始化（M15 最小验证）
	 *
	 * @note 位置说明：必须排在 `EcuM_Init()` 之后 —— ADC 引脚的方向/MUX
	 *       由 `Port_Init()` 配置，而 Port 在 EcuM 的 `DriverInitZero` 里。
	 *       排在前面的症状是"ADC 能转，但读到的永远是 0 或满量程"
	 *       （引脚还挂在别的复用功能上）。
	 *
	 * @note TODO：正式版应把这一步挪进 `EcuM_Cfg.c` 的 `DriverInitOne` 表，
	 *       和 CanIf/CanNm 一样由表驱动。现在直接调是为了让最小验证先跑起来。
	 * ------------------------------------------------------------------ */
	/* ADC 已归位到 `EcuM_Cfg.c` 的 `DriverInitListZero`（Port → Can → Adc），
	 * 由 `EcuM_Init()` 统一按表调用，这里不再手工初始化 ——
	 * 顺序由表保证，以后加模块只改表不改 main。
	 *
	 * 探针用显式缓冲区读组结果（`Adc_ReadGroup(g, raw)`），
	 * 所以全程不调 `Adc_SetupResultBuffer()`；它是给"先绑定、后异步读"
	 * 的用法留的，两条路径 `Adc_ReadGroup` 都支持。 */

	/* 应用请求 RUN。`EcuM_RequestRUN` 只置标志，真正的动作在
	 * `EcuM_MainFunction()` 里 —— 所以紧接着推一次，让 RUN 同步生效，
	 * 后面的横幅打印与周期发送才能在确定的时机开始。 */
	(void)EcuM_RequestRUN((EcuM_UserType)0u);
	EcuM_MainFunction();

	/* ------------------------------------------------------------------
	 * A/B 启动确认：**放在 RUN 生效之后**，不是 main 开头。
	 *
	 * 这是"新镜像能跑"的唯一证据。放在开头的话，"时钟起来了但 CAN 起不来"
	 * 这种镜像也会被判成功，回滚机制就白做了。等 CAN 控制器 STARTED、
	 * 收发器 NORMAL 之后再确认，语义才成立。
	 *
	 * 只在新镜像第一次启动时写一次 Flash；之后每次上电读 meta 发现
	 * 已是 CONFIRMED 就直接返回，不再擦写。
	 * ------------------------------------------------------------------ */
	BootApp_Confirm();

	CanTest_Init();

	Platform_Puts("========================================\n\n");

	PrintfSelfTest();

	Platform_Puts("type anything, it will be echoed back\n");
	Platform_Puts("  !o !n = CAN0 PDU offline/online\n");
	Platform_Puts("  !s !g = CAN0 controller stop/start\n");
	Platform_Puts("  !t !r = CAN0 transceiver sleep/normal\n");
	Platform_Puts("  !d !c = nvm dump / WriteAll\n");
	Platform_Puts("  !w !x = nvm touch CONFIG / illegal block id\n");
	Platform_Puts("  !p    = nvm stress 400 writes (force GC)\n");
	Platform_Puts("  !a !R = nm network request / release\n");
	Platform_Puts("  !A    = nm passive startup (woken by network)\n");
	Platform_Puts("  !m    = nm state (comm / cannm / mode)\n");
	Platform_Puts("  !v    = com signals (tx / rx)\n");
	Platform_Puts("  !y    = com ipdu group stop / start\n");
	Platform_Puts("  !u !U = ecum release RUN (POST_RUN) / back to RUN\n");
	Platform_Puts("  !q    = ecum mode\n");
	Platform_Puts("  !z    = sleep once (STOP mode, 100 ms fallback wake)\n");
	Platform_Puts("  !b !B = dtc dump / clear (CAN bus-off snapshot)\n");
	Platform_Puts("  !i    = inject one bus-off record (fault injection)\n");
	Platform_Puts("  !e !f = CAN0 registers / burst 100 frames\n");
	Platform_Puts("  !k !K = can rx counters / clear (stress)\n");
	Platform_Puts("  !M    = CAN1 real matrix TX (6 msgs, tag A1~A6)\n\n");

	for (;;) {
		/* 1) 串口输入：`!x` 是控制命令，其余原样回显
		 *    （回显是 M0 的验收项，不能被命令解析破坏，所以用 `!` 前缀区分） */
		ch = Platform_GetChar();
		if (ch >= 0) {
			Platform_PutChar((char)ch);
			if (s_cmdPending) {
				s_cmdPending = false;
				CmdExec((char)ch);
			} else if (ch == '!') {
				s_cmdPending = true;
			}
		}

		/* 2) CAN 标准帧周期发送（500 ms，两个通道各一帧） */
		if ((uint32_t)(Platform_NowMs() - nextTx) >= CAN_TX_PERIOD_MS) {
			nextTx = Platform_NowMs();
			CanTest_SendOne();      /* CAN0 0x123：8 字节全递增 */
			CanTest_SendCan1();     /* CAN1 0x124：首字节递增 */
		}

		/* 3) CAN 扩展帧周期发送（1000 ms） */
		if ((uint32_t)(Platform_NowMs() - nextExt) >= CAN_EXT_TX_PERIOD_MS) {
			nextExt = Platform_NowMs();
			CanTest_SendExt();
		}

		/* 4) CAN 收帧打印 */
		CanTest_DrainRx();

		/* 4b) 总线故障：检测 bus-off、记录、复查恢复
		 *     放在主循环而不是中断里，理由见 `Fault_PollBusOff` 的注释 */
		Fault_PollBusOff();

		/* 5) BSW 周期任务：**必须按固定周期调用，不能放在自由循环里**
		 *
		 *    `CanTp` / `Dcm` 的定时器是"每次 MainFunction 递减一次"（见
		 *    `CanTp_Priv.h` 的 `CanTpSignalAlarm`），而配置里的 N_Bs/N_Cr/S3
		 *    是按 `XXX_MAIN_FUNCTION_PERIOD` 毫秒折算成 tick 数的。
		 *    如果把这两个函数直接扔进无节拍的 while(1)，主循环每秒跑几万次，
		 *    100 tick 的 N_Bs 会在几百微秒内耗尽 —— 多帧传输立刻超时中断。
		 *
		 *    症状很有迷惑性：**单帧全通，多帧一律失败**（单帧不依赖任何定时器）。
		 */
		if ((uint32_t)(Platform_NowMs() - nextBsw) >= BSW_PERIOD_MS) {
			nextBsw = Platform_NowMs();
			CanTp_MainFunction();
			Dcm_MainFunction();
			/* NM 放在存储**之前**：它每 200 ms 才发一帧，本身几乎不耗时
			 * （一次 CanIf_Transmit + 几个定时器判断），但**周期精度依赖
			 * 主函数被准时调用**。放在 FEE 擦除之后会让 NM 周期被拖出
			 * 几毫秒的抖动 —— 单看一次无所谓，实测 Kvaser 上的间隔会周期性
			 * 出现一个偏长的值，容易被误判成"定时器算错了"。 */
			/* 应用侧信号更新：**必须在 `EcuM_BswService()` 之前**。
			 * 它要抢在 `Com_MainFunction()` 前面把新值写进报文缓冲，
			 * 否则第一帧发出去的是上一拍的旧值（差一帧）。
			 * 这一步是应用逻辑，不属于 BSW 调度表。 */
			Com_AppTick();

			/* BSW 调度交给 EcuM：按 `EcuM_DriverMainList` 的顺序跑一遍
			 * （CanSM → ComM → Com → CanNm → Nm → CanTp → Dcm → NvM → Dem）。
			 * 顺序和内容都在配置表里，这里不再逐行列出。 */
			EcuM_BswService();

			/* 状态机单独推进：它负责 RUN / POST_RUN / SLEEP 的迁移，
			 * 与 BSW 主函数是两件事（AUTOSAR 里也是两个入口）。 */
			EcuM_MainFunction();
			/* 存储放在这一拍的**最后**：FEE 的擦除是 1 KB 分片的，
			 * 单次可能占用几毫秒。放前面会把 UDS 的 10 ms 节拍推歪，
			 * 而存储本身对几十毫秒的抖动不敏感 —— 让时间敏感的先用 CPU。 */
			NvM_MainFunction();
			/* Dem 的落盘紧跟在存储推进之后：同一拍里先推进引擎、
			 * 再看它是否空闲，比"先请求再推进"少一次无谓的 BUSY */
			Dem_MainFunction();
		}

		/* 6) 心跳 */
		if ((uint32_t)(Platform_NowMs() - nextBeat) >= HEARTBEAT_MS) {
			nextBeat = Platform_NowMs();
			beat++;
			Platform_Printf("[%6u ms] alive #%u txok=%u\n",
			                (unsigned)Platform_NowMs(), (unsigned)beat,
			                (unsigned)s_txConfirmCount);
		}
	}
}
