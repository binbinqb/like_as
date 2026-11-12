/**
 * @file    Dcm_Cfg.c
 * @brief   boot 版 Dcm 配置：会话 + 安全 + 刷写（0x10/11/27/31/34/36/37/3E）
 *
 * @details @section BOOTDCM_WHY 为什么 boot 要自带一份 Dcm 配置
 *
 *          app 的 `Dcm_Cfg.c` 有 823 行，包含 0x22（VIN + 零件号，走 NvM）、
 *          0x2E、0x14/0x19（走 Dem）、0x85。boot 一个都用不上，
 *          而且 **0x14/0x19 会硬链接 Dem** —— boot 不链 Dem，复用直接链接失败。
 *
 *          更重要的原因：**boot 与 app 的 UDS 服务集本来就该不同**。
 *          boot 只有"擦写 Flash"这一件事，服务越少攻击面越小；
 *          而 app 将来加新服务时，也不该被动把 boot 撑大。
 *
 * @warning 本文件的初始化器字段数**必须**与 `Dcm_Priv.h:558` 的
 *          `struct Dcm_Config_s` 在当前宏组合下严格一致。
 *          boot 的宏组合（`Dcm_Cfg.h`）：
 *          - 有 `DCM_USE_SERVICE_ROUTINE_CONTROL` → 有 `rtCtrlConfig`
 *          - 有 `DCM_USE_SERVICE_SECURITY_ACCESS` + `USE_NVM` → 尾部 3 个字段
 *          - 无 DDDID / rPDID / IOCtl / Memory → 对应字段不存在
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-12 | binbina | 首版：boot 专用 7 个服务 |
 */

#include <string.h>

#include "Dcm.h"
#include "Dcm_Cfg.h"
#include "Dcm_Priv.h"

#include "FlashLoader.h"    /* 0x31 例程 / 0x34/0x36/0x37 / 复位 */
#include "PduR_Cfg.h"       /* PDUR_DCM_TO_CANTP_TX */
#include "NvM.h"            /* SecurityNvMBlkId 的类型 */

/* ============================ [ 缓冲 ] ============================ */

/** @brief 诊断请求缓冲（CanTp 重组后落这里） */
static uint8_t Dcm_RxBuffer[DCM_RX_BUF_SIZE];

/** @brief 诊断响应缓冲（Dcm 组包，CanTp 从这里分段发） */
static uint8_t Dcm_TxBuffer[DCM_TX_BUF_SIZE];

/* ============================ [ 0x27 安全访问 ] ============================ */

/**
 * @section BOOTDCM_SEC27 boot 的 0x27 与 app 保持同一套占位实现
 *
 * 两边都是"固定种子 + 任意 key 都通过"。这么做的原因是
 * **真算法文件（《XX 诊断安全算法》）还没到**，而刷写链路必须能验证。
 *
 * 与 app 的唯一差别：**不依赖 NvM 的失败计数块**。
 * `SecurityNvMBlkId` 填 0xFF（不存在的块号），因为
 * `Dcm_CompareKey()` 恒通过 → `AttemptCounter` 永远是 0 →
 * NvM 写路径走不到。换成真算法时必须同时建 SECURITY 块并改这个值，
 * 否则第一次密钥校验失败就会对非法块发写请求（DET 报错）。
 */
static const uint8_t Dcm_SecSeed[4] = { 0x11u, 0x22u, 0x33u, 0x44u };

/**
 * @brief 请求种子（0x27 奇数子功能）
 * @param[out] Seed       输出缓冲
 * @param[out] ErrorCode  失败时的否定响应码
 * @return E_OK
 * @note  返回全 0 种子按 ISO 14229 表示"该等级已解锁"；这里返回非 0，
 *        是为了让测试仪真的走一遍 sendKey 流程。
 */
static Std_ReturnType Dcm_GetSeed(uint8_t *Seed, Dcm_NegativeResponseCodeType *ErrorCode)
{
	(void)ErrorCode;

	if (Seed == NULL) {
		return E_NOT_OK;
	}

	(void)memcpy(Seed, Dcm_SecSeed, sizeof(Dcm_SecSeed));
	return E_OK;
}

/**
 * @brief 校验密钥（0x27 偶数子功能）—— 恒通过
 * @param[in]  Key        测试仪发来的密钥
 * @param[out] ErrorCode  失败时的否定响应码
 * @return E_OK
 * @warning 开发期实现，**任何 4 字节都算对**。量产前必须换成真算法。
 */
static Std_ReturnType Dcm_CompareKey(const uint8_t *Key, Dcm_NegativeResponseCodeType *ErrorCode)
{
	(void)Key;
	(void)ErrorCode;
	return E_OK;
}

/** @brief 安全等级表（只做 level 1） */
static const Dcm_SecLevelConfigType Dcm_SecLevels[] = {
	{
		Dcm_GetSeed,
		Dcm_CompareKey,
		0x01u,                  /* secLevel：对应子功能 0x01/0x02 */
		4u,                     /* seedSize */
		4u,                     /* keySize */
		/**
		 * @note **与 app 的关键差别**：boot 里 0x27 必须在**编程会话**可用。
		 *       app 写的是 `DCM_EXTENDED_MASK`（只在扩展会话），
		 *       而标准刷写流程是 `10 02` → `27 01/02` —— 编程会话下
		 *       如果 0x27 不可用，诊断仪会拿到 NRC 0x7F，刷写流程直接卡死。
		 */
		DCM_PROGRAMMING_MASK | DCM_EXTENDED_MASK,
	},
};

static const Dcm_SecurityAccessConfigType Dcm_SecurityAccessConfig = {
	Dcm_SecLevels,
	(uint8_t)ARRAY_SIZE(Dcm_SecLevels),
};

/**
 * @brief 安全访问失败计数（AUTOSAR 要求跨上电保持）
 *
 * @warning `Dcm_Dsl.c:27` 只在 `#ifndef USE_NVM` 时定义这个变量。
 *          boot 也带 NvM（`USE_NVM` 已定义），所以**必须由配置侧提供定义**，
 *          否则链接失败：`undefined reference to Dcm_NvmSecurityAccess_Ram`。
 *
 * @note  当前 `Dcm_CompareKey()` 恒通过 → `AttemptCounter` 恒为 0 →
 *        `NvM_WriteBlock()` 永远不会被调用，所以没有为它建 NvM 块，
 *        `SecurityNvMBlkId` 填不存在的块号（见 `Dcm_Config` 尾部）。
 *        换真算法时必须同时：① 建 SECURITY 块；② 让这个变量指向块的 RAM 映像；
 *        ③ 填真实的 `SecurityNvMBlkId`。
 */
Dcm_Nvm_SecurityAccessType Dcm_NvmSecurityAccess_Ram;

/* ============================ [ 0x10 会话控制 ] ============================ */

/** @brief boot 支持的会话：默认 / 编程 / 扩展 */
static const Dcm_SesCtrlType Dcm_SesCtrls[] = {
	DCM_DEFAULT_SESSION,
	DCM_PROGRAMMING_SESSION,
	DCM_EXTENDED_SESSION,
};

/**
 * @brief 会话切换许可回调
 *
 * @warning **必须提供，不能传 NULL**。`Dcm_Dsp.c:373` 没判空：
 *          ```c
 *          r = sesCtrlConfig->GetSesChgPermissionFnc(context->currentSession, sesCtrl, nrc);
 *          ```
 *          传 NULL 的后果是 `10 02` 一进来就跳到地址 0，
 *          CFSR 报 INVSTATE，进 HardFault。症状很有迷惑性 ——
 *          启动正常、只有发第一条诊断请求时整块板子静默。
 *
 * @note 这里无条件放行。量产会在"车速 > 0 不允许进编程会话"之类的条件下拒绝。
 */
static Std_ReturnType Dcm_GetSesChgPermission(Dcm_SesCtrlType sesActive,
                                              Dcm_SesCtrlType sesNew,
                                              Dcm_NegativeResponseCodeType *nrc)
{
	(void)sesActive;
	(void)sesNew;
	(void)nrc;
	return E_OK;
}

static const Dcm_SessionControlConfigType Dcm_SessionControlConfig = {
	Dcm_GetSesChgPermission,
	Dcm_SesCtrls,
	(uint8_t)ARRAY_SIZE(Dcm_SesCtrls),
};

/* ============================ [ 0x31 / 0x34 / 0x36 / 0x37 ] ============================ */

/**
 * @brief 例程运行上下文（Dcm 用它记"这个例程是否正在运行"）
 * @note  两个例程各一个，**不能共用** —— 共用会让"擦除刚结束"
 *        把"校验正在运行"的状态一起清掉。
 */
static Dcm_RoutineControlContextType Dcm_RtCtrlContexts[2];

/**
 * @brief 0x31 支持的例程（都是刷写必需）
 *
 * | 例程号 | 名称 | 参数 | 响应 |
 * |--------|------|------|------|
 * | FF00 | eraseMemory | `<addr 4B> <size 4B>` | `71 01 FF00 00` |
 * | FF01 | checkIntegrity | `<addr 4B> <size 4B> <crc 4B>` | `71 01 FF01 <0/1>` |
 *
 * @note `StopRoutineFnc` 一律 NULL：擦除与校验都是"要么做完、要么失败"，
 *       中途停止没有语义。传 NULL 时 Dcm 对 `31 02` 回 NRC 0x12，
 *       比注册一个空实现更诚实。
 * @note `securityMask = 0x02`（仅 level 1）：擦写 Flash 必须要求解锁。
 */
static const Dcm_RoutineControlType Dcm_RtCtrls[] = {
	{
		&Dcm_RtCtrlContexts[0],
		FlashLoader_EraseStart,             /* StartRoutineFnc */
		NULL,                               /* StopRoutineFnc：擦除不能中途停 */
		NULL,                               /* RequestResultRoutineFnc：结果就是响应本身 */
		FLASH_LOADER_RID_ERASE,             /* id = 0xFF00 */
		{ DCM_PROGRAMMING_MASK | DCM_EXTENDED_MASK | DCM_DEFAULT_MASK,
		  0x02u,                            /* securityMask：**仅** level 1 */
		  DCM_MISC_PHYSICAL | DCM_MISC_SUB_FUNCTION },
	},
	{
		&Dcm_RtCtrlContexts[1],
		FlashLoader_CheckStart,             /* StartRoutineFnc */
		NULL,
		NULL,
		FLASH_LOADER_RID_CHECK,             /* id = 0xFF01 */
		{ DCM_PROGRAMMING_MASK | DCM_EXTENDED_MASK | DCM_DEFAULT_MASK,
		  0x02u,
		  DCM_MISC_PHYSICAL | DCM_MISC_SUB_FUNCTION },
	},
};

static const Dcm_RoutineControlConfigType Dcm_RtCtrlConfig = {
	Dcm_RtCtrls,
	(uint8_t)ARRAY_SIZE(Dcm_RtCtrls),
};

/** @brief 0x34：唯一回调是"登记目标槽 + 给出块长" */
static const Dcm_RequestDownloadConfigType Dcm_RequestDownloadConfig = {
	FlashLoader_RequestDownload,
};

/**
 * @brief 0x36：写回调
 * @note  `ReadFnc` 留 NULL —— 上传方向（0x35）boot 不提供。
 *        填 NULL 时 Dcm 对上传路径回 NRC 0x22，而不是跳到空指针。
 */
static const Dcm_TransferDataConfigType Dcm_TransferDataConfig = {
	FlashLoader_WriteData,
	NULL,
};

static const Dcm_TransferExitConfigType Dcm_TransferExitConfig = {
	FlashLoader_TransferExit,
};

/* ============================ [ 0x11 ECU 复位 ] ============================ */

/**
 * @brief 0x11 的权限回调：无条件允许
 * @note  真正的限制在会话/安全掩码上（见服务表项），这里不必重复判。
 */
static Std_ReturnType Dcm_GetEcuResetPermission(Dcm_OpStatusType opStatus,
                                                Dcm_NegativeResponseCodeType *nrc)
{
	(void)opStatus;
	(void)nrc;
	return E_OK;
}

/**
 * @brief 0x11 配置
 * @note  `delay` 单位是 Dcm 主函数周期（10 ms），50 → 500 ms。
 *        留这段延时是为了让 `51 01` 正响应先发出去 ——
 *        立刻复位的话响应还在 CanTp 缓冲里，上位机只能看到超时。
 */
static const Dcm_EcuResetConfigType Dcm_EcuResetConfig = {
	Dcm_GetEcuResetPermission,
	50u,
};

/**
 * @brief Dcm 的复位执行点
 * @param[in] resetType 复位类型（未使用，两种类型在 Cortex-M 上都走 SYSRESETREQ）
 */
void Dcm_PerformReset(uint8_t resetType)
{
	(void)resetType;
	FlashLoader_PerformReset();
}

/* ============================ [ DID 占位 ] ============================ */

/**
 * @brief DID 配置表占位
 *
 * @details boot 不开 0x22，这张表永远不会被遍历（`numOfrDIDs = 0`）。
 *          但 `Dcm_ConfigType` 要求这个指针存在，给个 1 元素占位避免 NULL。
 *
 * @note  将来要支持"编程会话读 VIN"：在这里加一条 `0xF190`，
 *        回调里 `NvM_ReadBlock(NVM_CFG_ID_VIN, ...)`（boot 已有 NvM 通路），
 *        再把 `numOfrDIDs` 改成 1、`Dcm_Cfg.h` 打开
 *        `DCM_USE_SERVICE_READ_DATA_BY_IDENTIFIER` 即可。
 */
static const Dcm_rDIDConfigType Dcm_rDIDConfigs[] = {
	{
		0u,
		0u,
		NULL,
		{ DCM_ANY_SESSION_MASK,
		  DCM_SEC_MASK_LOCKED_OR_L1,
		  DCM_MISC_PHYSICAL },
	},
};

/* ============================ [ 服务表 ] ============================ */

/**
 * @brief 支持的服务
 * @note  顺序不影响查找（Dcm 按 SID 线性匹配）。
 * @note  刷写五项（0x31/34/36/37）与 0x11 的 `securityMask = 0x02`
 *        —— **必须先 `27` 解锁**。擦写 Flash 的能力不能开放给任何接上总线的设备。
 */
static const Dcm_ServiceType Dcm_UdsServices[] = {
	{
		SID_DIAGNOSTIC_SESSION_CONTROL,
		{ DCM_ANY_SESSION_MASK,
		  DCM_SEC_MASK_LOCKED_OR_L1,          /* securityMask：不受限 */
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL | DCM_MISC_SUB_FUNCTION },
		Dcm_DspSessionControl,
		(const void DCM_CONST *)&Dcm_SessionControlConfig,
	},
	{
		SID_TESTER_PRESENT,
		{ DCM_ANY_SESSION_MASK,
		  DCM_SEC_MASK_LOCKED_OR_L1,
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL | DCM_MISC_SUB_FUNCTION },
		Dcm_DspTesterPresent,
		NULL,                       /* 3E 没有额外配置 */
	},
	{
		SID_SECURITY_ACCESS,
		/* 0x27 本身**必须**在 locked 状态可用，否则永远解不了锁 */
		{ DCM_ANY_SESSION_MASK,
		  DCM_SEC_MASK_LOCKED_OR_L1,
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL | DCM_MISC_SUB_FUNCTION },
		Dcm_DspSecurityAccess,
		(const void DCM_CONST *)&Dcm_SecurityAccessConfig,
	},
	{
		SID_ROUTINE_CONTROL,
		{ DCM_PROGRAMMING_MASK | DCM_EXTENDED_MASK | DCM_DEFAULT_MASK,
		  0x02u,                    /* 仅 level 1：擦除/校验要解锁 */
		  DCM_MISC_PHYSICAL | DCM_MISC_SUB_FUNCTION },
		Dcm_DspRoutineControl,
		(const void DCM_CONST *)&Dcm_RtCtrlConfig,
	},
	{
		SID_REQUEST_DOWNLOAD,
		{ DCM_PROGRAMMING_MASK | DCM_EXTENDED_MASK,
		  0x02u,
		  DCM_MISC_PHYSICAL },
		Dcm_DspRequestDownload,
		(const void DCM_CONST *)&Dcm_RequestDownloadConfig,
	},
	{
		SID_TRANSFER_DATA,
		{ DCM_PROGRAMMING_MASK | DCM_EXTENDED_MASK,
		  0x02u,
		  DCM_MISC_PHYSICAL },
		Dcm_DspTransferData,
		(const void DCM_CONST *)&Dcm_TransferDataConfig,
	},
	{
		SID_REQUEST_TRANSFER_EXIT,
		{ DCM_PROGRAMMING_MASK | DCM_EXTENDED_MASK,
		  0x02u,
		  DCM_MISC_PHYSICAL },
		Dcm_DspRequestTransferExit,
		(const void DCM_CONST *)&Dcm_TransferExitConfig,
	},
	{
		SID_ECU_RESET,
		{ DCM_PROGRAMMING_MASK | DCM_EXTENDED_MASK | DCM_DEFAULT_MASK,
		  0x02u,
		  DCM_MISC_PHYSICAL | DCM_MISC_SUB_FUNCTION },
		Dcm_DspEcuReset,
		(const void DCM_CONST *)&Dcm_EcuResetConfig,
	},
};

/** @brief 一张服务表就够了 */
static const Dcm_ServiceTableType Dcm_UdsServiceTable = {
	Dcm_UdsServices,
	(uint8_t)ARRAY_SIZE(Dcm_UdsServices),
};

static P2CONST(Dcm_ServiceTableType, DCM_CONST, DCM_CONST)
	Dcm_ServiceTables[] = { &Dcm_UdsServiceTable };

/* ============================ [ 计时 ] ============================ */

/** @brief 诊断计时（单位：主函数周期数） */
static const Dcm_TimingConfigType Dcm_TimingConfig = {
	/**
	 * @note S3Server 是 **5 秒**：boot 里不能更短 —— 诊断仪刷写时
	 *       如果中间停顿（比如人在看日志），回到默认会话会中断刷写。
	 *       也不能更长：编程会话无限期挂着是安全隐患。
	 */
	DCM_CONVERT_MS_TO_MAIN_CYCLES(5000u),   /* S3Server */
	DCM_CONVERT_MS_TO_MAIN_CYCLES(20u),     /* P2ServerAdjust */
	DCM_CONVERT_MS_TO_MAIN_CYCLES(20u),     /* P2StarServerAdjust */
	DCM_CONVERT_MS_TO_MAIN_CYCLES(50u),     /* P2ServerMax */
	DCM_CONVERT_MS_TO_MAIN_CYCLES(5000u),   /* P2StarServerMax */
};

/** @brief 诊断响应参数 */
static const Dcm_DslDiagRespConfigType Dcm_DslDiagRespConfig = {
	8u,                                     /* MaxNumRespPend：最多 8 个 0x78 */
};

/* ============================ [ 通道 ] ============================ */

/**
 * @brief 诊断通道
 * @warning `TxPduId` 是 **PduR 的 TX pathId**（不是 CanIf 的），
 *          Dcm 通过它把响应交给 `PduR_TpTransmit()`。
 */
static const Dcm_ChannelType Dcm_Channels[] = {
	{
		(PduIdType)PDUR_DCM_TO_CANTP_TX,     /* TxPduId */
		DCM_PHYSICAL_REQUEST,               /* reqType */
	},
};

/* ============================ [ 总表 ] ============================ */

/**
 * @warning 字段顺序见 `Dcm_Priv.h:558` 的 `struct Dcm_Config_s`。
 *          当前宏组合下依次是：
 *          ServiceVerificationFnc, rx/txBuffer, rx/txBufferSize,
 *          channles, numOfChls, serviceTables, numOfServiceTables,
 *          timing, dslDisgResp, rDIDs, numOfrDIDs,
 *          rtCtrlConfig,                                  ← ROUTINE_CONTROL
 *          SecurityNumAttDelay, SecurityDelayTime, SecurityNvMBlkId
 *                                                         ← SECURITY_ACCESS + USE_NVM
 */
const Dcm_ConfigType Dcm_Config = {
	NULL,                                   /* ServiceVerificationFnc：不额外校验 */
	Dcm_RxBuffer,
	Dcm_TxBuffer,
	(PduLengthType)sizeof(Dcm_RxBuffer),
	(PduLengthType)sizeof(Dcm_TxBuffer),
	Dcm_Channels,
	(uint8_t)ARRAY_SIZE(Dcm_Channels),
	Dcm_ServiceTables,
	(uint8_t)ARRAY_SIZE(Dcm_ServiceTables),
	&Dcm_TimingConfig,
	&Dcm_DslDiagRespConfig,
	Dcm_rDIDConfigs,
	0u,                                     /* numOfrDIDs = 0：boot 不开 0x22 */
	&Dcm_RtCtrlConfig,
	0u,                                     /* SecurityNumAttDelay：不延迟 */
	0u,                                     /* SecurityDelayTime：不延迟 */
	/**
	 * @brief SecurityNvMBlkId
	 * @warning 填 **0xFF = 不存在的块号**：`Dcm_CompareKey()` 恒通过、
	 *          `AttemptCounter` 永远是 0、`NvM_WriteBlock()` 走不到。
	 *          换真算法前必须建 SECURITY 块并改这里，否则第一次密钥校验
	 *          失败就会对非法块发写请求（DET 报错）。
	 */
	(NvM_BlockIdType)0xFFu,
};
