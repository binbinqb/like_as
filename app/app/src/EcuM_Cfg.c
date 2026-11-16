/**
 * @file    EcuM_Cfg.c
 * @brief   EcuM 的初始化表与 BSW 主函数表
 *
 * @details @section ECUMCFG_C_PHASES 三个阶段分别放什么
 *
 *          AUTOSAR 把初始化拆成三个阶段，**不是随便分的**：
 *
 *          | 阶段 | 时机 | 放什么 | 判据 |
 *          |------|------|--------|------|
 *          | **Zero** | 时钟/看门狗就绪前，最早 | MCAL 驱动（Port / Can） | 只依赖寄存器，不依赖任何 BSW |
 *          | **One** | 中断可用之后 | 通信栈、存储栈、诊断 | 需要能被上层调用的模块 |
 *          | **Two** | OS 启动之后 | 需要"世界已经安静下来"才能做的（读回 NVM、启动周期报文） | 依赖 One 阶段全部完成 |
 *
 *          本工程的实际映射：
 *
 *          @code
 *          Zero : Port_Init, Can_Init
 *          One  : CanIf, PduR, CanTp, Dcm, NvM(Init), Nm, CanNm, Com, ComM, CanSM
 *          Two  : Storage_InitData（NvM_ReadAll + 启动计数 + Dem）
 *          @endcode
 *
 *          @section ECUMCFG_C_ORDER One 阶段的顺序为什么是这样
 *
 *          - **CanIf 先于 PduR**：PduR 只存配置指针，但 CanIf_Init 会把
 *            控制器 PDU 模式置 OFFLINE，必须在任何收发动作之前；
 *          - **PduR 先于 CanTp/Dcm**：CanTp 的 RX 回调要经过 PduR，
 *            PduR 没 Init 时 `PduR_Config` 为空，`PduR_RxIndication` 会 DET 报错；
 *          - **Dcm 在 CanTp 之后**：Dcm 初始化不依赖 CanTp，但逻辑上
 *            诊断是 TP 的上层，放后面便于阅读；
 *          - **Nm 在 CanNm 之前**：`Nm.c` 的注释里写了"分发层先于被分发者"；
 *          - **ComM / CanSM 最后**：它们会**立即驱动**下层（CanSM 请求控制器
 *            模式、ComM 请求 NM），下层必须已经 Init 完毕。
 *
 *          @section ECUMCFG_C_MAIN 主函数表的顺序
 *
 *          每个 10 ms 调一次，顺序即执行顺序：
 *
 *          @code
 *          CanSM → ComM → Com → CanNm → Nm → CanTp → Dcm → NvM → Dem
 *          @endcode
 *
 *          - **CanSM 最先**：它处理 ComM 上一拍提的控制器模式请求，
 *            以及 bus-off 恢复计时。放后面会让恢复多等一拍；
 *          - **ComM 次之**：读 NM 回报的标志，决定要不要升降级；
 *          - **Com 在 CanNm 之前**：信号报文优先于 NM 报文发出，
 *            NM 报文晚几微秒不影响网络管理；
 *          - **NvM / Dem 最后**：NvM 的擦除是 1 KB 分片的，单次可能占用
 *            几毫秒。放前面会把上面所有模块的节拍推歪。
 *
 *          @warning **`Com_AppTick()` 不在这张表里**，它在
 *                   `EcuM_BswService()` 之前单独调用 —— 因为它必须在
 *                   `Com_MainFunction()` **之前**跑完（信号先更新、再发送），
 *                   而表遍历没法表达"插在某两项之间"。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：把 main.c 里手写的初始化与 10 ms 调度搬进配置表 |
 */

#include "EcuM.h"
#include "EcuM_Priv.h"
#include "EcuM_Cfg.h"

/* ---- 阶段 Zero ---- */
#include "Port.h"
#include "Can.h"
#include "Adc.h"        /* M15：ADC 属于 MCAL，排在 Port 之后 */
#include "Adc_Cfg.h"    /* Adc_Config：表项的 config 字段要用 */
#include "Pwm.h"        /* M18：PWM 同属 MCAL，排在 ADC 之后 */
#include "Pwm_Cfg.h"    /* Pwm_Config：同上 */

/* ---- 阶段 One ---- */
#include "CanIf.h"
#include "PduR.h"
#include "CanTp.h"
#include "Dcm.h"
#include "Nm.h"
#include "CanNm.h"
#include "Com.h"
#include "ComM.h"
#include "CanSM.h"

/* ---- 阶段 Two ---- */
#include "NvM.h"
#include "Dem.h"

/* ============================ [ 初始化表：Zero ] ============================ */

static const EcuM_DriverInitItemType EcuM_DriverInitListZero[] = {
	{ (EcuM_DriverInitFncType)Port_Init, NULL },
	{ (EcuM_DriverInitFncType)Can_Init,  NULL },
	/**
	 * @brief ADC 初始化
	 * @note  这一项是**唯一带参数**的 MCAL 初始化项 —— 标准 `Adc_Init()`
	 *        要求传入配置指针，而其他模块（Port/Can）都是从自己的
	 *        `Xxx_Cfg.c` 里取全局实例、不接受参数。
	 *
	 * @note  表项的第二个字段就是给这种情形准备的：`EcuM_MainFunction()`
	 *        会把 `config` 原样传给 `InitFnc`。
	 *
	 * @warning 函数指针转换 `(EcuM_DriverInitFncType)Adc_Init` 在 ISO C 里
	 *          属于类型不兼容（`const Adc_ConfigType *` vs `const void *`），
	 *          严格说是 UB；但 ARM AAPCS 下所有指针参数走同一个寄存器，
	 *          实际安全。本工程对 `Mcu_Init` / `Port_Init` 一直这么处理，
	 *          保持一致。若将来过 MISRA 认证，需在外面包一层适配函数。
	 */
	{ (EcuM_DriverInitFncType)Adc_Init,  &Adc_Config },
	/**
	 * @brief PWM 初始化（M18）
	 * @note  与 `Adc_Init` 同构：标准 `Pwm_Init()` 也要求传入配置指针。
	 * @note  放在 `Adc_Init` 之后：两者都依赖 PORT 的时钟门控（`Clock_Config`
	 *        里已开 A~E），彼此无依赖，顺序只是为了"先输入后输出"的阅读顺序。
	 * @note  `Pwm_Init()` 内部会校验"同一 PwmLite 实例内频率是否一致"，
	 *        不一致时**拒绝初始化并打印** —— 见 `Pwm.c` 的
	 *        `Pwm_CheckPeriodConsistency()`。
	 */
	{ (EcuM_DriverInitFncType)Pwm_Init,  &Pwm_Config },
};

/* ============================ [ 初始化表：One ] ============================ */

static const EcuM_DriverInitItemType EcuM_DriverInitListOne[] = {
	{ (EcuM_DriverInitFncType)CanIf_Init,  NULL },
	{ (EcuM_DriverInitFncType)PduR_Init,   NULL },
	{ (EcuM_DriverInitFncType)CanTp_Init,  NULL },
	{ (EcuM_DriverInitFncType)Dcm_Init,    NULL },
	/**
	 * @brief 存储栈阶段一（`NvM_Init`）
	 * @note  用强制转换是因为它的原型是 `void Storage_InitStack(void)`，
	 *        而表要求 `void (*)(const void *)`。ARM AAPCS 下多传的参数
	 *        被忽略，与 as-master 对 `Mcu_Init` / `Port_Init` 的处理一致。
	 */
	{ (EcuM_DriverInitFncType)Storage_InitStack, NULL },
	{ (EcuM_DriverInitFncType)Nm_Init,     NULL },
	{ (EcuM_DriverInitFncType)CanNm_Init,  NULL },
	{ (EcuM_DriverInitFncType)Com_Init,    NULL },
	{ (EcuM_DriverInitFncType)ComM_Init,   NULL },
	{ (EcuM_DriverInitFncType)CanSM_Init,  NULL },
};

/* ============================ [ 初始化表：Two ] ============================ */

static const EcuM_DriverInitItemType EcuM_DriverInitListTwo[] = {
	{ (EcuM_DriverInitFncType)Storage_InitData, NULL },
};

/* ============================ [ 主函数表（10 ms） ] ============================ */

static const EcuM_DriverMainFncType EcuM_DriverMainList[] = {
	CanSM_MainFunction,   /* 控制器模式请求 + bus-off 恢复计时 */
	ComM_MainFunction,    /* 通信模式仲裁 */
	Com_MainFunction,     /* 信号打包/周期发送 + 解包 + 信号超时 */
	/**
	 * @brief 发送失败重试（`bTxRetry` 的唯一推进者）
	 * @note  M22 之前这张表里没有它，后果是：`PduR_ComTransmit` 只要失败一次
	 *        （CanIf 邮箱忙、Can_Write 提前返回），Com 就把 `bTxRetry` 置起
	 *        等重发 —— 而**没人推进这个标志**，那条报文就永远停在"发过一次"。
	 *        现象极隐蔽：Kvaser 上每个 ID 只出现 1 帧，`com can1` 里
	 *        `retry=1`，而 t 还在正常回卷。
	 *        它和 `Com_MainFunction` 同周期调用即可（内部只扫 bTxRetry 为真的项）。
	 */
	Com_MainFunction_Fast,
	CanNm_MainFunction,   /* NM 状态机 */
	Nm_MainFunction,      /* Nm 分发层（当前为空实现） */
	CanTp_MainFunction,   /* ISO-TP 分段/重组 + N_As/N_Cr 告警递减 */
	/**
	 * @brief ISO-TP 重发 —— `CanTp_ReSend()` 的**唯一**内部调用者
	 *
	 * @note A1 发现的漏调度（2026-11-16）。`CanTp_ReSend(Channel)` 在
	 *       `CanTp.c` 里只有一个内部调用点：`CanTp_MainFunction_ChannelFast()`
	 *       的 `case CANTP_RESEND_CF`（`CanTp.c:1119`），而该函数只被本函数
	 *       调用。本函数在此之前**从未被调用**，于是：
	 *
	 *       `CanTp_TransmitCF()` 里 `CanIf_Transmit()` 返回 `E_NOT_OK`
	 *       （TX 邮箱全忙）→ 状态置 `CANTP_RESEND_CF` + 启动 N_As 告警
	 *       → **没人推进重发** → N_As 超时 → `CanTp_MainFunction_Channel()`
	 *       走 `default:` 分支直接 `ResetToIdle` + `TxConfirmation(E_NOT_OK)`。
	 *
	 *       现象：刷写偶发失败（打回 NRC 0x78 之后再也等不到下一帧），
	 *       重刷一次往往就好 —— 因为邮箱不总是满。这是典型的
	 *       "只在总线负载高时出现"的缺陷，台架空载跑一百次也复现不了。
	 *
	 * @note 库注释说本函数"通常 1 ms 一次"。本工程只有 10 ms 节拍，
	 *       重发晚 10 ms 完全可接受（N_As 是 1000 ms 量级），
	 *       所以直接放进本表即可，不需要为它单独建 1 ms 任务。
	 * @warning 不要删。删掉就等于 `CANTP_RESEND_CF` 成为死状态。
	 */
	CanTp_MainFunction_Fast,
	Dcm_MainFunction,     /* 诊断会话/服务处理 */
	NvM_MainFunction,     /* 存储栈推进（含 Fee） */
	Dem_MainFunction,     /* DTC 落盘 */
};

/**
 * @brief 存储类主函数表
 * @note  只给 `EcuM_MemoryService()` 用 —— 那是"阻塞等待存储空闲"时
 *        循环推进的对象。本工程不再用它等 NvM（存储栈有自己的超时），
 *        但保留这张表，`EcuM_EnsureMemoryIdle()` 仍可用。
 */
static const EcuM_DriverMainFncType EcuM_DriverMainMemList[] = {
	NvM_MainFunction,
};

/* ============================ [ 主函数表（快速任务） ] ============================ */

/*
 * 本工程只有一个 10 ms 节拍，没有更快的任务。
 * `numOfMainFast = 0`，`EcuM_BswServiceFast()` 调用时什么都不做。
 * 将来要做 1 ms 任务（比如 PWM 占空比更新）时在这里加。
 */
static const EcuM_DriverMainFncType EcuM_DriverMainFastList[] = {
	NULL,
};

/* ============================ [ 总表 ] ============================ */

const EcuM_ConfigType EcuM_Config = {
	.DriverInitListZero   = EcuM_DriverInitListZero,
	.DriverInitListOne    = EcuM_DriverInitListOne,
	.DriverInitListTwo    = EcuM_DriverInitListTwo,
	.DriverMainList       = EcuM_DriverMainList,
	.DriverMemMainList    = EcuM_DriverMainMemList,
	.DriverMainFastList   = EcuM_DriverMainFastList,
	.numOfZero            = (uint16_t)ARRAY_SIZE(EcuM_DriverInitListZero),
	.numOfOne             = (uint16_t)ARRAY_SIZE(EcuM_DriverInitListOne),
	.numOfTwo             = (uint16_t)ARRAY_SIZE(EcuM_DriverInitListTwo),
	.numOfMain            = (uint16_t)ARRAY_SIZE(EcuM_DriverMainList),
	.numOfMainMem         = (uint16_t)ARRAY_SIZE(EcuM_DriverMainMemList),
	/** @brief 快速任务表只有一个占位 NULL，长度必须写 0 而不是 ARRAY_SIZE */
	.numOfMainFast        = 0u,
	.TMinWakup            = ECUM_CONVERT_MS_TO_MAIN_CYCLES(ECUM_MIN_WAKEUP_TIME),
};
