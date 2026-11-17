/**
 * @file    Dcm_Cfg.c
 * @brief   Dcm 配置表：1 个物理通道 + 3 个服务 + 2 个 DID
 *
 * @details @section DCMCFG_WIRE 接线关系
 *          @code
 *          PduR(PDUR_CANTP_TO_DCM_RX) → Dcm_StartOfReception(0)
 *                            → Dcm_MainFunction() 解析 SID
 *                            → Dcm_DspXxx() 生成响应到 txBuffer
 *                            → Dcm_MainFunction_Response()
 *                            → PduR_TpTransmit(PDUR_DCM_TO_CANTP_TX) → CanTp 分段 → 0x7E8
 *          @endcode
 *
 *          @warning `Dcm_Channels[]` 的下标就是**诊断通道号**，必须与
 *          `PduR` 的 RX pathId 对齐（`Dcm_StartOfReception(id)` 用 id 索引通道）。
 *          当前只有一个通道，所以 RX pathId 恒为 0。
 *
 *          @section DCMCFG_DID DID 回调的约定
 *          `readDIdFnc(opStatus, data, length, errorCode)` 里：
 *          - `length` 是**配置表里给的长度**，不是请求里的长度；
 *          - 函数要把 `length` 个字节写进 `data`，返回 `E_OK`；
 *          - 失败时填 `*errorCode` 并返回 `E_NOT_OK`，Dcm 会自动发否定响应。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：0x10/0x22/0x3E，F190 VIN + F187 零件号 |
 */

#include "Dcm.h"
#include "Dcm_Cfg.h"
#include "Dcm_Priv.h"

#include "PduR_Cfg.h"

/* 0x2E 写 VIN 要落到 NvM 块；0x22 读的也是同一块。
 * 这是"配置层可以同时看见多个 BSW"的正当用法 —— 就像 NvM_Cfg.c
 * 同时看见 Fee 和 NvM 一样。分层约束的是**模块之间**，不是配置文件。 */
#include "NvM.h"
#include "NvM_Cfg.h"

/* A/B 刷写业务：0x31 / 0x34 / 0x36 / 0x37 的实现全在这里，
 * 配置层只负责"把哪个例程号挂到哪个函数"和"要什么会话/安全等级"。 */
#include "FlashLoader.h"

#include <string.h>

/* ============================ [ 通用掩码 ] ============================ */

/**
 * @brief `securityMask` 的取值：**允许** locked 与 level 1 两种状态
 *
 * @warning **`securityMask` 是"允许的等级集合"，不是"最低要求的等级"。**
 *          这一点踩过坑：最初填 `0x01`（只有 locked 允许），
 *          结果是 —— **解锁之后所有服务反而全被拒**，回 NRC 0x33。
 *          因为 `Dcm_Dsl.c:135` 是这么判的：
 *          @code
 *          if (0u != (sesSecAccess->securityMask & (1u << context->currentLevel)))
 *              r = E_OK;                                    // 命中才放行
 *          else
 *              *nrc = DCM_E_SECUTITY_ACCESS_DENIED;         // 0x33
 *          @endcode
 *          解锁后 `currentLevel = 1`，所以要允许它就得把 bit1 也置上。
 *
 * @note  `0x03` = bit0(LOCKED) | bit1(level 1) —— "锁没锁都能用"，
 *        等价于"这个服务不受安全访问限制"。本工程所有服务都用它，
 *        因为 0x27 只是把协议链路做出来，业务上暂时不限制任何能力。
 *
 * @note  将来要真限制某个服务（比如"0x2E 写 VIN 必须先解锁"），
 *        把那一项改成 `0x02`（**只**允许 level 1）即可 —— 改一个数，不动逻辑。
 *        那时 locked 状态下访问会得到 NRC 0x33，正是想要的行为。
 */
#define DCM_SEC_MASK_LOCKED_OR_L1   (0x03u)

/* ============================ [ 缓冲 ] ============================ */

/** @brief 诊断请求缓冲（CanTp 重组后落这里） */
static uint8_t Dcm_RxBuffer[DCM_RX_BUF_SIZE];

/** @brief 诊断响应缓冲（Dcm 组包，CanTp 从这里分段发） */
static uint8_t Dcm_TxBuffer[DCM_TX_BUF_SIZE];

/* ============================ [ DID 数据 ] ============================ */

/**
 * @section DCMCFG_VIN VIN 为什么没有常量了
 *
 * M3/M6 时 VIN 是这里的一个 `static const uint8_t Dcm_Vin[17]`，
 * 内容是 `CVM0146M3TEST0001`。做 0x2E 时发现这样不行：
 *
 * - 写：只能写进一个 RAM 副本，掉电就没了；
 * - 读：读的是常量，写多少都读不到新值；
 * - 更要命的是 **NvM 里还有一个 VIN 块**（`NVM_CFG_ID_VIN`，默认 `CVM0146M4NVM00001`）——
 *   两份数据不一致，而"看代码"和"看 `!d`"都各自显示正常。
 *
 * 所以现在 VIN 只有一个数据源：**NvM 的 VIN 块**。
 * 0x22 从它读、0x2E 往它写、掉电由 FEE 保证。ROM 默认值在 `NvM_Cfg.c` 里。
 */

/** @brief 0xF187 零件号（11 字节，ASCII，只读） */
static const uint8_t Dcm_PartNumber[11] = {
	'A', 'S', '-', 'C', 'V', 'M', '0', '1', '4', '6', 'A',
};

/* ============================ [ DID 回调 ] ============================ */

/**
 * @brief 读 0xF190 VIN（从 NvM 块读）
 * @param[in]  opStatus   操作状态（首次调用是 DCM_INITIAL）
 * @param[out] data       输出缓冲
 * @param[in]  length     期望长度（来自配置表，17）
 * @param[out] errorCode  失败时的否定响应码
 *
 * @note  每次都从 NvM 块的 RAM 映像取，不做缓存 —— 让 0x22 与 0x2E
 *        天然一致，也不会出现"改了块但读的是旧缓存"。
 */
static Std_ReturnType Dcm_ReadVin(Dcm_OpStatusType opStatus, uint8_t *data, uint16_t length,
                                  Dcm_NegativeResponseCodeType *errorCode)
{
	const uint8_t *ram = NULL;
	uint16_t len = 0u;

	(void)opStatus;

	if (length != (uint16_t)NVM_CFG_BLK_VIN_SIZE) {
		/* 配置表和实际数据长度对不上：这是编码错误，不是请求错误，
		 * 所以返回 generalReject 而不是长度错误 */
		*errorCode = DCM_E_GENERAL_REJECT;
		return E_NOT_OK;
	}

	if ((NvM_GetBlockDataPtrAndLength((NvM_BlockIdType)NVM_CFG_ID_VIN,
	                                  (void **)&ram, &len) != E_OK) ||
	    (ram == NULL) || (len < (uint16_t)NVM_CFG_BLK_VIN_SIZE)) {
		*errorCode = DCM_E_CONDITIONS_NOT_CORRECT;
		return E_NOT_OK;
	}

	(void)memcpy(data, ram, (size_t)NVM_CFG_BLK_VIN_SIZE);
	return E_OK;
}

/**
 * @brief 写 0xF190 VIN（写进 NvM 块并请求落盘）
 * @param[in] opStatus   操作状态
 * @param[in] data       新 VIN（17 字节，ASCII，不带结束符）
 * @param[in] length     长度（配置表里是 17，Dsp 已校验过请求长度）
 * @param[out] errorCode 失败时的否定响应码
 *
 * @note  顺序是"先改块 RAM，再请求落盘"：`NvM_WriteBlock(id, NULL)` 的语义
 *        就是"写这个块自己的 RAM 映像"。真正写 Flash 是异步的，
 *        但读侧读的也是同一份 RAM，所以**写得进去、立刻读得到**。
 *
 * @note  落盘请求被拒（引擎正忙）时返回 `conditionsNotCorrect`，
 *        让测试仪知道"这次没写成功"，而不是假装成功。
 *        此时 RAM 已被改动 —— 可接受：重启后会从 Flash 读回旧值。
 */
static Std_ReturnType Dcm_WriteVin(Dcm_OpStatusType opStatus, uint8_t *data, uint16_t length,
                                   Dcm_NegativeResponseCodeType *errorCode)
{
	uint8_t *ram = NULL;
	uint16_t len = 0u;

	(void)opStatus;

	if ((data == NULL) || (length != (uint16_t)NVM_CFG_BLK_VIN_SIZE)) {
		*errorCode = DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
		return E_NOT_OK;
	}

	/**
	 * @warning **引擎忙时必须如实报错，不能假装成功。**
	 *
	 *          实测：连续两次 `2E F1 90` 且间隔很短时，第二次的
	 *          `NvM_WriteBlock()` 会返回 `E_OK`（请求入队成功），但厂商引擎
	 *          对**同一块**的重复写请求在作业未完成时会丢弃它 ——
	 *          结果是"响应 6E F1 90、读回来还是上一次的值"。
	 *          这个现象几乎没法从协议层看出来，只能靠这里挡住。
	 *
	 *          返回 `conditionsNotCorrect`(0x22) 让测试仪知道"这次没写成"，
	 *          它会重试。真车上的诊断仪对 DID 写入本来就要做重试。
	 */
	if (NvM_GetStatus() != MEMIF_IDLE) {
		*errorCode = DCM_E_CONDITIONS_NOT_CORRECT;
		return E_NOT_OK;
	}

	if ((NvM_GetBlockDataPtrAndLength((NvM_BlockIdType)NVM_CFG_ID_VIN,
	                                  (void **)&ram, &len) != E_OK) ||
	    (ram == NULL) || (len < (uint16_t)NVM_CFG_BLK_VIN_SIZE)) {
		*errorCode = DCM_E_CONDITIONS_NOT_CORRECT;
		return E_NOT_OK;
	}

	(void)memcpy(ram, data, (size_t)NVM_CFG_BLK_VIN_SIZE);

	if (NvM_WriteBlock((NvM_BlockIdType)NVM_CFG_ID_VIN, NULL) != E_OK) {
		*errorCode = DCM_E_CONDITIONS_NOT_CORRECT;
		return E_NOT_OK;
	}

	return E_OK;
}

/** @brief 读 0xF187 零件号 */
static Std_ReturnType Dcm_ReadPartNumber(Dcm_OpStatusType opStatus, uint8_t *data, uint16_t length,
                                         Dcm_NegativeResponseCodeType *errorCode)
{
	(void)opStatus;

	if (length != (uint16_t)sizeof(Dcm_PartNumber)) {
		*errorCode = DCM_E_GENERAL_REJECT;
		return E_NOT_OK;
	}

	(void)memcpy(data, Dcm_PartNumber, sizeof(Dcm_PartNumber));
	return E_OK;
}

/* ============================ [ DID 表 ] ============================ */

/**
 * @brief DID 配置表
 * @note  `Dcm_SesSecAccessType` 在没定义 `DCM_USE_SERVICE_SECURITY_ACCESS` 时
 *        只有 **2 个字段**（sessionMask、miscMask）。定义那个宏会变成 3 个字段，
 *        这里的初始化器就得跟着改 —— 所以 M3 刻意不开安全访问。
 */
static const Dcm_rDIDConfigType Dcm_rDIDConfigs[] = {
	{
		0xF190u,                                        /* id：VIN */
		(uint16_t)NVM_CFG_BLK_VIN_SIZE,                 /* length：数据在 NvM 块里 */
		Dcm_ReadVin,                                    /* readDIdFnc */
		{ DCM_ANY_SESSION_MASK,                         /* sessionMask：任何会话可读 */
		  DCM_SEC_MASK_LOCKED_OR_L1,                    /* securityMask：不受限 */
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL },    /* miscMask */
	},
	{
		0xF187u,                                        /* id：零件号 */
		(uint16_t)sizeof(Dcm_PartNumber),
		Dcm_ReadPartNumber,
		{ DCM_ANY_SESSION_MASK,
		  DCM_SEC_MASK_LOCKED_OR_L1,
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL },
	},
};

/** @brief 0x22 服务的运行上下文（每条 DID 一个） */
static Dcm_ReadDIDContextType Dcm_ReadDIDContexts[ARRAY_SIZE(Dcm_rDIDConfigs)];

/** @brief 0x22 服务的 DID 索引表 */
static const Dcm_ReadDIDType Dcm_ReadDIDs[] = {
	{ &Dcm_ReadDIDContexts[0], &Dcm_rDIDConfigs[0] },
	{ &Dcm_ReadDIDContexts[1], &Dcm_rDIDConfigs[1] },
};

/** @brief 0x22 服务的配置 */
static const Dcm_ReadDIDConfigType Dcm_ReadDataByIdentifierConfig = {
	Dcm_ReadDIDs,
	(uint8_t)ARRAY_SIZE(Dcm_ReadDIDs),
};

/* ============================ [ 0x2E 写 DID ] ============================ */

#ifdef DCM_USE_SERVICE_WRITE_DATA_BY_IDENTIFIER

/**
 * @brief 可写的 DID 表
 *
 * @note  只有 VIN。**不要因为是"能写的都列上"就在这里加 F187（零件号）** ——
 *        零件号是出厂烧进去的，实车上不允许诊断仪改它。能写什么、由谁写，
 *        是产品定义不是技术方便。
 *
 * @note  `length` 必须与 `Dcm_WriteVin()` 内部的一致校验对齐。
 *        `Dcm_DspWriteDataByIdentifier` 会先检查
 *        `reqDataLen == length + 2`（2 = DID 本身），对不上直接回 NRC 0x13，
 *        所以长度写错的表现是"请求根本进不到回调"。
 */
static const Dcm_WriteDIDType Dcm_WriteDIDs[] = {
	{
		0xF190u,                                        /* id：VIN */
		(uint16_t)NVM_CFG_BLK_VIN_SIZE,                 /* length：17 */
		Dcm_WriteVin,                                   /* writeDIdFnc */
		{ DCM_ANY_SESSION_MASK,                         /* sessionMask */
		  DCM_SEC_MASK_LOCKED_OR_L1,                    /* securityMask：不受限 */
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL },    /* miscMask */
	},
};

static const Dcm_WriteDIDConfigType Dcm_WriteDataByIdentifierConfig = {
	Dcm_WriteDIDs,
	(uint8_t)ARRAY_SIZE(Dcm_WriteDIDs),
};

#endif /* DCM_USE_SERVICE_WRITE_DATA_BY_IDENTIFIER */

/* ============================ [ 0x27 安全访问 ] ============================ */

#ifdef DCM_USE_SERVICE_SECURITY_ACCESS

/**
 * @section DCMCFG_SEC27 0x27 目前是"永远通过"
 *
 * 产品上这是不行的，但作为**协议链路验证**是必要的一步：
 * 先证明 seed/seed2key/sendKey 三段握手能走通、能置位 `currentLevel`、
 * 能被 `securityMask` 检查，再往里填真实的算法。
 *
 * 现在的行为：
 * - `27 01` → 返回固定种子 `11 22 33 44`
 * - `27 02 11 22 33 44`（或**任意** 4 字节）→ 恒 `E_OK`
 * - 解锁后 `Dcm_Dsl` 会把 `currentLevel` 置 1，但没有任何服务要求 level 1
 *   （所有 `securityMask` 都是 0x01），所以**行为上看不出变化** ——
 *   这是刻意的：先接通，不改变现有功能。
 *
 * 换成真算法只改一个函数：`Dcm_CompareKey()`。
 * 种子也应改成随机数（真实实现要抗重放），这里固定值是为了脚本可复现。
 */
static const uint8_t Dcm_SecSeed[4] = { 0x11u, 0x22u, 0x33u, 0x44u };

/**
 * @brief 请求种子（0x27 奇数子功能）
 * @param[out] Seed       输出缓冲（大小由配置表的 `seedSize` 决定）
 * @param[out] ErrorCode  失败时的否定响应码
 * @note  返回全 0 种子按 ISO 14229 表示"该等级已解锁、无需发 key"。
 *        这里返回非 0，是为了让测试仪**真的走一遍 sendKey 流程** ——
 *        否则 0x02 那一段永远测不到。
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
 * @brief 校验密钥（0x27 偶数子功能）—— **恒通过**
 * @param[in]  Key        测试仪发来的密钥
 * @param[out] ErrorCode  失败时的否定响应码
 * @warning 这是开发期实现，**任何 4 字节都算对**。
 *          量产前必须换成真算法，否则 0x27 等于没有。
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
		DCM_EXTENDED_MASK,       /* sessionMask：只在扩展会话可访问 */
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
 *          本工程定义了 `USE_NVM`（由平台 config 注册自动加），
 *          所以**必须由平台侧提供定义**，否则开 0x27 会链接失败：
 *          `undefined reference to Dcm_NvmSecurityAccess_Ram`。
 *
 * @note  当前 `Dcm_CompareKey()` 恒通过 → `AttemptCounter` 恒为 0 →
 *        `NvM_WriteBlock()` 永远不会被调用。所以**没有为它建 NvM 块**，
 *        `SecurityNvMBlkId` 填的是不存在的块号（见 `Dcm_Config` 尾部）。
 *        一旦换成真算法，必须同时：① 建 SECURITY 块；② 把这个变量
 *        指到块的 RAM 映像；③ 填真实的 `SecurityNvMBlkId`。
 */
Dcm_Nvm_SecurityAccessType Dcm_NvmSecurityAccess_Ram;

#endif /* DCM_USE_SERVICE_SECURITY_ACCESS */

/* ============================ [ 0x10 会话控制 ] ============================ */

/** @brief 本 ECU 支持的会话列表 */
static const Dcm_SesCtrlType Dcm_SesCtrls[] = {
	DCM_DEFAULT_SESSION,
	/* 编程会话：**App 不实现 0x34/0x36/0x37**，但必须承认这个会话 ——
	 * 否则诊断仪发 `10 02` 会被回 NRC 0x12，连"我要刷写"都表达不出来。
	 *
	 * 语义：进编程会话 = 请求把控制权交给 boot。实际动作在
	 * `Dcm_SessionChangeIndication()`（见 `can_test.c`）→
	 * `BootApp_RequestFlashMode()`：等 150 ms 让 `50 02` 发出去，写
	 * meta 标志，然后复位。boot 上电读到标志就停在 UDS。
	 *
	 * 注意这里**不做**"进编程会话就停应用报文"（AUTOSAR 常规做法）：
	 * 本工程还没有独立的诊断 CAN 通道，停报文会连诊断响应一起停掉。
	 * 真有需求时加到 `Dcm_GetSesChgPermission()` 里。 */
	DCM_PROGRAMMING_SESSION,
	DCM_EXTENDED_SESSION,
};

/**
 * @brief 会话切换许可回调
 *
 * @warning **必须提供，不能传 NULL**。`Dcm_Dsp.c:373` 是这么写的：
 *          ```c
 *          r = sesCtrlConfig->GetSesChgPermissionFnc(context->currentSession, sesCtrl, nrc);
 *          ```
 *          **没有判空**。传 NULL 的后果是：`10 03` 一进来就跳到地址 0，
 *          CFSR 报 `INVSTATE`（非法 EPSR），进 HardFault。
 *          症状很有迷惑性 —— 启动横幅、printf 自检都正常，
 *          只有发第一条诊断请求时整块板子静默，看起来像"CAN 收不到"。
 *
 * @note 这里无条件放行。真实项目会在这里做约束，例如：
 *       - 车速 > 0 不允许进扩展会话（NRC 0x22 conditionsNotCorrect）
 *       - 未解锁时不允许进编程会话
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

/**
 * @brief 0x10 服务的配置
 * @note  `GetSesChgPermissionFnc` 绝不能是 NULL（见上）。
 */
static const Dcm_SessionControlConfigType Dcm_SessionControlConfig = {
	Dcm_GetSesChgPermission,
	Dcm_SesCtrls,
	(uint8_t)ARRAY_SIZE(Dcm_SesCtrls),
};

/* ============================ [ 0x19 读故障码 ] ============================ */

#ifdef DCM_USE_SERVICE_READ_DTC_INFORMATION

/**
 * @brief 0x19 支持的子功能表
 *
 * @details 只注册三个，理由不是偷懒 —— `Dcm_Dsp.c` 里其余子功能实现
 *          调用了本工程 Dem 没有提供的接口（快照、扩展数据、镜像内存），
 *          注册进来会直接链接失败。**能编进来 ≠ 能用**，所以只报真能做的。
 *
 *          | 子功能 | 名称 | 响应 |
 *          |--------|------|------|
 *          | 0x01 | reportNumberOfDTCByStatusMask | `59 01 <availMask> 01 <countHi> <countLo>` |
 *          | 0x02 | reportDTCByStatusMask | `59 02 <availMask> {DTC[3] status}*` |
 *          | 0x0A | reportSupportedDTC | `59 0A <availMask> {DTC[3] status}*`（不过滤状态） |
 *
 * @note  三个子功能都要求 `DCM_MISC_SUB_FUNCTION` —— 少了它，
 *        `Dcm_DslServiceSesSecPhyFuncCheck` 会按"这个 SID 没有子功能"处理，
 *        测试仪发 `19 02 FF` 会拿到 NRC 0x13（长度/格式错），
 *        而不是正常响应。这是最容易漏的一位。
 */
static const Dcm_ReadDTCSubFunctionConfigType Dcm_ReadDTCSubFunctions[] = {
	{
		Dem_DspReportNumberOfDTCByStatusMask,
		{ DCM_ANY_SESSION_MASK, DCM_SEC_MASK_LOCKED_OR_L1,
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL | DCM_MISC_SUB_FUNCTION },
		0x01u,
	},
	{
		Dem_DspReportDTCByStatusMask,
		{ DCM_ANY_SESSION_MASK, DCM_SEC_MASK_LOCKED_OR_L1,
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL | DCM_MISC_SUB_FUNCTION },
		0x02u,
	},
	{
		Dem_DspReportSupportedDTC,
		{ DCM_ANY_SESSION_MASK, DCM_SEC_MASK_LOCKED_OR_L1,
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL | DCM_MISC_SUB_FUNCTION },
		0x0Au,
	},
};

static const Dcm_ReadDTCInfoConfigType Dcm_ReadDTCInfoConfig = {
	Dcm_ReadDTCSubFunctions,
	(uint8_t)ARRAY_SIZE(Dcm_ReadDTCSubFunctions),
};

#endif /* DCM_USE_SERVICE_READ_DTC_INFORMATION */

/* ============================ [ 刷写：0x31 / 0x34 / 0x36 / 0x37 / 0x11 ] ============================ */

#ifdef DCM_USE_SERVICE_ROUTINE_CONTROL

/**
 * @brief 例程运行上下文（Dcm 用它记"这个例程是否正在运行"）
 * @note  两个例程各一个，**不能共用** —— 共用会让"擦除刚结束"把
 *        "校验正在运行"的状态一起清掉。
 */
static Dcm_RoutineControlContextType Dcm_RtCtrlContexts[2];

/**
 * @brief 0x31 支持的例程
 *
 * @details 只注册两个，都是刷写必需：
 *          | 例程号 | 名称 | 参数 | 响应 |
 *          |--------|------|------|------|
 *          | FF00 | eraseMemory | `<addr 4B> <size 4B>` | `71 01 FF00 00` |
 *          | FF01 | checkIntegrity | `<addr 4B> <size 4B> <crc 4B>` | `71 01 FF01 <0/1>` |
 *
 *          @note `StopRoutineFnc` 一律 NULL：擦除与校验都是"要么做完、要么失败"，
 *          中途停止没有语义（停下来也只会在 Flash 里留半擦的扇区）。
 *          传 NULL 时 Dcm 对 `31 02` 回 NRC 0x12（子功能不支持），
 *          比注册一个空实现更诚实。
 *
 *          @note `securityMask = 0x02`：**只允许 level 1**（解锁后）。
 *          这是与其它服务不同的地方 —— 0x22/0x2E 用的是 `0x03`（锁没锁都行），
 *          但擦写 Flash 必须要求解锁，否则任何接了总线的设备都能把 ECU 擦空。
 */
static const Dcm_RoutineControlType Dcm_RtCtrls[] = {
	{
		&Dcm_RtCtrlContexts[0],
		FlashLoader_EraseStart,             /* StartRoutineFnc */
		NULL,                               /* StopRoutineFnc：擦除不能中途停 */
		NULL,                               /* RequestResultRoutineFnc：结果就是响应本身 */
		FLASH_LOADER_RID_ERASE,             /* id = 0xFF00 */
		{ DCM_EXTENDED_MASK | DCM_DEFAULT_MASK,  /* sessionMask：扩展/编程会话 */
		  0x02u,                            /* securityMask：**仅** level 1 */
		  DCM_MISC_PHYSICAL | DCM_MISC_SUB_FUNCTION },
	},
	{
		&Dcm_RtCtrlContexts[1],
		FlashLoader_CheckStart,             /* StartRoutineFnc */
		NULL,
		NULL,
		FLASH_LOADER_RID_CHECK,             /* id = 0xFF01 */
		{ DCM_EXTENDED_MASK | DCM_DEFAULT_MASK,
		  0x02u,
		  DCM_MISC_PHYSICAL | DCM_MISC_SUB_FUNCTION },
	},
};

static const Dcm_RoutineControlConfigType Dcm_RtCtrlConfig = {
	Dcm_RtCtrls,
	(uint8_t)ARRAY_SIZE(Dcm_RtCtrls),
};

#endif /* DCM_USE_SERVICE_ROUTINE_CONTROL */

#ifdef DCM_USE_SERVICE_REQUEST_DOWNLOAD
/** @brief 0x34：唯一的回调是"登记目标槽 + 给出块长" */
static const Dcm_RequestDownloadConfigType Dcm_RequestDownloadConfig = {
	FlashLoader_RequestDownload,
};
#endif

#if defined(DCM_USE_SERVICE_REQUEST_DOWNLOAD) || defined(DCM_USE_SERVICE_REQUEST_UPLOAD)
/**
 * @brief 0x36：写回调
 * @note  `ReadFnc` 留 NULL —— 上传方向（0x35）本工程不提供。
 *        填 NULL 时 Dcm 对上传路径回 NRC 0x22，而不是跳到空指针。
 */
static const Dcm_TransferDataConfigType Dcm_TransferDataConfig = {
	FlashLoader_WriteData,
	NULL,
};
#endif

#ifdef DCM_USE_SERVICE_REQUEST_TRANSFER_EXIT
static const Dcm_TransferExitConfigType Dcm_TransferExitConfig = {
	FlashLoader_TransferExit,
};
#endif

#ifdef DCM_USE_SERVICE_ECU_RESET

/**
 * @brief 0x11 的权限回调：无条件允许
 * @param[in]  opStatus 未使用
 * @param[out] nrc      未使用
 * @return 恒 E_OK
 * @note  真正的限制在会话/安全掩码上（见服务表项），这里不必重复判。
 *        `opStatus` 为 `DCM_CANCEL` 时 Dcm 也会调本函数，返回 E_OK 无害。
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
 * @note  `delay` 单位是 **Dcm 主函数周期（10 ms）**，50 → 500 ms。
 *        留这段延时是为了让 `51 01` 正响应先发出去 ——
 *        立刻复位的话响应还在 CanTp 缓冲里，上位机只能看到超时。
 */
static const Dcm_EcuResetConfigType Dcm_EcuResetConfig = {
	Dcm_GetEcuResetPermission,
	50u,
};

/**
 * @brief Dcm 的复位执行点（`Dcm_Dsl.c:248` 调用）
 * @param[in] resetType 复位类型（0x01 硬复位 / 0x03 软复位）
 * @note  两种类型在 Cortex-M 上走同一条路：`AIRCR.SYSRESETREQ`。
 *        "软复位"若要保留外设状态，应该改成跳回向量表而不是系统复位，
 *        但那样 Flash 里的升级标志就不一定重新加载 —— 对 A/B 来说
 *        系统复位才是正确行为。
 */
void Dcm_PerformReset(uint8_t resetType)
{
	(void)resetType;
	FlashLoader_PerformReset();
}

#endif /* DCM_USE_SERVICE_ECU_RESET */

/* ============================ [ 服务表 ] ============================ */

/** @brief 支持的服务（顺序不影响查找，Dcm 按 SID 线性匹配） */
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
		SID_READ_DATA_BY_IDENTIFIER,
		{ DCM_ANY_SESSION_MASK,
		  DCM_SEC_MASK_LOCKED_OR_L1,          /* securityMask：不受限 */
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL },
		Dcm_DspReadDataByIdentifier,
		(const void DCM_CONST *)&Dcm_ReadDataByIdentifierConfig,
	},
	{
		SID_TESTER_PRESENT,
		{ DCM_ANY_SESSION_MASK,
		  DCM_SEC_MASK_LOCKED_OR_L1,          /* securityMask：不受限 */
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL | DCM_MISC_SUB_FUNCTION },
		Dcm_DspTesterPresent,
		NULL,                       /* 3E 没有额外配置 */
	},
#ifdef DCM_USE_SERVICE_CLEAR_DIAGNOSTIC_INFORMATION
	{
		SID_CLEAR_DIAGNOSTIC_INFORMATION,
		{ DCM_ANY_SESSION_MASK,
		  DCM_SEC_MASK_LOCKED_OR_L1,          /* securityMask：不受限 */
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL },
		Dcm_DspClearDTC,
		NULL,                       /* 0x14 用 Dem 自己的"选中 DTC"状态，无配置项 */
	},
#endif
#ifdef DCM_USE_SERVICE_READ_DTC_INFORMATION
	{
		SID_READ_DTC_INFORMATION,
		{ DCM_ANY_SESSION_MASK,
		  DCM_SEC_MASK_LOCKED_OR_L1,          /* securityMask：不受限 */
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL | DCM_MISC_SUB_FUNCTION },
		Dcm_DspReadDTCInformation,
		(const void DCM_CONST *)&Dcm_ReadDTCInfoConfig,
	},
#endif
#ifdef DCM_USE_SERVICE_SECURITY_ACCESS
	{
		SID_SECURITY_ACCESS,
		/* 0x27 本身**必须**在 locked 状态可用，否则永远解不了锁 ——
		 * 这是唯一一个 `securityMask` 不能设成 level 限制的服务。 */
		{ DCM_ANY_SESSION_MASK,
		  DCM_SEC_MASK_LOCKED_OR_L1,          /* securityMask：locked 也能请求 */
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL | DCM_MISC_SUB_FUNCTION },
		Dcm_DspSecurityAccess,
		(const void DCM_CONST *)&Dcm_SecurityAccessConfig,
	},
#endif
#ifdef DCM_USE_SERVICE_WRITE_DATA_BY_IDENTIFIER
	{
		SID_WRITE_DATA_BY_IDENTIFIER,
		{ DCM_ANY_SESSION_MASK,
		  DCM_SEC_MASK_LOCKED_OR_L1,          /* securityMask：暂时不受限 */
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL },
		Dcm_DspWriteDataByIdentifier,
		(const void DCM_CONST *)&Dcm_WriteDataByIdentifierConfig,
	},
#endif
	/* ------------------------------------------------------------------
	 * 刷写链路（A/B）
	 *
	 * 这五项与 0x22/0x2E 有一个关键区别：**securityMask 是 0x02**
	 * （只允许 level 1，即"必须先 27 解锁"），而不是 0x03（锁没锁都行）。
	 * 擦写 Flash 的能力不能开放给任何接上总线的设备。
	 *
	 * sessionMask 用 `DCM_EXTENDED_MASK | DCM_DEFAULT_MASK`：
	 * 允许在扩展会话或编程会话里刷写。之所以放开扩展会话，
	 * 是因为本工程没有独立的编程会话流程（10 02 之后还要切回来），
	 * 扩展会话少一次切换、少一个出错环节。量产若要求严格按
	 * "10 02 → 刷写 → 11 01" 走，把这里改成 `0x02u` 即可（编程会话掩码）。
	 * ------------------------------------------------------------------ */
#ifdef DCM_USE_SERVICE_ROUTINE_CONTROL
	{
		SID_ROUTINE_CONTROL,
		{ DCM_EXTENDED_MASK | DCM_DEFAULT_MASK,
		  0x02u,                              /* securityMask：仅 level 1 */
		  DCM_MISC_PHYSICAL | DCM_MISC_SUB_FUNCTION },
		Dcm_DspRoutineControl,
		(const void DCM_CONST *)&Dcm_RtCtrlConfig,
	},
#endif
#ifdef DCM_USE_SERVICE_REQUEST_DOWNLOAD
	{
		SID_REQUEST_DOWNLOAD,
		{ DCM_EXTENDED_MASK | DCM_DEFAULT_MASK,
		  0x02u,
		  DCM_MISC_PHYSICAL },                /* 下载不允许功能寻址 */
		Dcm_DspRequestDownload,
		(const void DCM_CONST *)&Dcm_RequestDownloadConfig,
	},
#endif
#ifdef DCM_USE_SERVICE_TRANSFER_DATA
	{
		SID_TRANSFER_DATA,
		{ DCM_EXTENDED_MASK | DCM_DEFAULT_MASK,
		  0x02u,
		  DCM_MISC_PHYSICAL },
		Dcm_DspTransferData,
		(const void DCM_CONST *)&Dcm_TransferDataConfig,
	},
#endif
#ifdef DCM_USE_SERVICE_REQUEST_TRANSFER_EXIT
	{
		SID_REQUEST_TRANSFER_EXIT,
		{ DCM_EXTENDED_MASK | DCM_DEFAULT_MASK,
		  0x02u,
		  DCM_MISC_PHYSICAL },
		Dcm_DspRequestTransferExit,
		(const void DCM_CONST *)&Dcm_TransferExitConfig,
	},
#endif
#ifdef DCM_USE_SERVICE_ECU_RESET
	{
		SID_ECU_RESET,
		/* 复位本身不改变 Flash，任意会话可用；但仍要求解锁，
		 * 避免总线上的设备随手把 ECU 复位打断别人的刷写。 */
		{ DCM_ANY_SESSION_MASK,
		  0x02u,
		  DCM_MISC_PHYSICAL | DCM_MISC_FUNCTIONAL | DCM_MISC_SUB_FUNCTION },
		Dcm_DspEcuReset,
		(const void DCM_CONST *)&Dcm_EcuResetConfig,
	},
#endif
};

/** @brief 一张服务表就够了（多表用于"不同诊断通道不同服务集"） */
static const Dcm_ServiceTableType Dcm_UdsServiceTable = {
	Dcm_UdsServices,
	(uint8_t)ARRAY_SIZE(Dcm_UdsServices),
};

static P2CONST(Dcm_ServiceTableType, DCM_CONST, DCM_CONST)
	Dcm_ServiceTables[] = { &Dcm_UdsServiceTable };

/* ============================ [ 计时 ] ============================ */

/** @brief 诊断计时（单位：主函数周期数） */
static const Dcm_TimingConfigType Dcm_TimingConfig = {
	DCM_CONVERT_MS_TO_MAIN_CYCLES(5000u),   /* S3Server：5 s 无请求回默认会话 */
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
	(uint8_t)ARRAY_SIZE(Dcm_rDIDConfigs),
#ifdef DCM_USE_SERVICE_ROUTINE_CONTROL
	/* --- 顺序必须与 Dcm_ConfigType 一致：rDIDs → rtCtrlConfig → Security* --- */
	&Dcm_RtCtrlConfig,
#endif
#ifdef DCM_USE_SERVICE_SECURITY_ACCESS
	/* --- 下面三项顺序必须与 Dcm_ConfigType 尾部一致 --- */
	0u,                                     /* SecurityNumAttDelay：不延迟 */
	0u,                                     /* SecurityDelayTime：不延迟 */
	/**
	 * @brief SecurityNvMBlkId
	 * @warning 填的是 **0xFF = 不存在的块号**，因为当前 `Dcm_CompareKey()`
	 *          恒通过、`AttemptCounter` 永远是 0、`NvM_WriteBlock()` 走不到。
	 *          换成真算法前必须建 SECURITY 块并把这里改成真实块号 ——
	 *          否则第一次密钥校验失败就会触发一次对非法块的写请求（DET 报错）。
	 */
	(NvM_BlockIdType)0xFFu,
#endif
};
