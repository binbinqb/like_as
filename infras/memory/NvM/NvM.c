/**
 * @file    NvM.c
 * @brief   NVRAM Manager —— AUTOSAR 外观（**实现是厂商引擎**）
 *
 * @details @section NVM_WHAT 这个文件是什么、不是什么
 *          它**不是**一份 NvM 实现。真正的状态机、队列、块缓存、CRC 校验、
 *          ROM 默认值修复全在 `infras/memory/vendor/nvm/`（厂商原样代码）。
 *          本文件只做三件事：
 *          1. **翻译接口**：`NvM_ReadBlock(BlockId, p)` → `NvM_PortRead(id, p)`；
 *          2. **翻译语义**：AUTOSAR 的"写块"永远要落盘，厂商引擎的
 *             `immediate=false` 只写 RAM —— 本工程把所有块配成立即写，
 *             把"延迟落盘"这件事交给 `NvM_SetRamBlockStatus` + `NvM_WriteAll`；
 *          3. **补齐 AUTOSAR 有、厂商没有的东西**：块状态映射、脏块掩码、
 *             `NvM_GetStatus()`、DET 参数检查。
 *
 *          @section NVM_WHY_PORT 为什么不直接 include 厂商头
 *          两边都定义 `NVM_REQ_*`：AUTOSAR 是宏，厂商是枚举成员。
 *          同一个编译单元里先 include 谁都会出事（先 AUTOSAR 则枚举定义被宏污染，
 *          编译不过；先厂商则宏在后面把枚举值全改成 0，**不报错但比较永远错**）。
 *          所以中间隔一层 `NvM_Port.h`（零厂商类型、零 AUTOSAR 类型）。
 *          细节见 `NvM_Port.h` 的 `@ref NVMPORT_WHY`。
 *
 *          @section NVM_DIRTY 脏块掩码为什么必须自己维护
 *          AUTOSAR 的 `NvM_WriteAll()` 只写"被标记为已修改"的块，没改的不写。
 *          厂商引擎的 `Nvm_WriteAll()` 是**全写**（`nvm_block.c:232` 的
 *          `Nvm_Block_GetWriteData()` 不判断是否修改过）。
 *          对 FEE 这种日志式存储，全写的代价不是时间、是**扇区寿命**：
 *          一次全写约 216 字节日志空间，12 KB 扇区 ≈ 50 次全写就要 GC 一次。
 *          BCM 每次下电都 WriteAll 的话，Flash 磨损会比预期快一个数量级。
 *          所以这里用 `NvM_DirtyMask` 自己筛，`NvM_WriteAll` 只推进脏块。
 *
 *          @section NVM_WRITEALL_LOOP WriteAll 为什么是"投一个、等一个"
 *          引擎的用户作业队列深 4（`NVM_CFG_QUEUE_NUM`），一次性把 5 个块全投进去
 *          会溢出，而溢出时的返回值（`NVM_RETURN_NOT_OK`）和"块号非法"是同一个，
 *          很难区分。所以 `NvM_MainFunction()` 每拍只在引擎空闲时投一个，
 *          投完立刻返回；下一拍再投下一个。5 个块 × 10 ms = 50 ms 写完，够快。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：AUTOSAR 外观 + 脏块 WriteAll + DET |
 */

#include <stddef.h>

#include "NvM.h"
#include "NvM_Port.h"

#include "Det.h"

/* ============================ [ 私有定义 ] ============================ */

/**
 * @brief AUTOSAR 模块 ID（NvM = 20，见 AUTOSAR CP 的 Module ID 分配表）
 * @note  DET 上报里要带这个号，才能在日志里区分"是 NvM 报的还是 Fee 报的"。
 */
#define NVM_MODULE_ID           (20u)

/** @brief DET API ID（本文件内自增，只用于定位是哪个人参检查失败的） */
#define NVM_API_INIT            (0x00u)
#define NVM_API_READ_BLOCK      (0x0Bu)
#define NVM_API_WRITE_BLOCK     (0x0Cu)
#define NVM_API_READ_ALL        (0x0Du)
#define NVM_API_WRITE_ALL       (0x0Eu)
#define NVM_API_GET_ERROR       (0x13u)
#define NVM_API_SET_RAM_STATUS  (0x14u)
#define NVM_API_GET_BLOCK_PTR   (0x15u)

/** @brief 脏块掩码位宽（块数不能超过 16） */
#define NVM_DIRTY_MASK_MAX      (16u)

/* ============================ [ 私有数据 ] ============================ */

/** @brief 是否已 `NvM_Init()` */
static bool NvM_Initialized;

/**
 * @brief 脏块掩码：bit i = 1 表示块 i 的 RAM 映像还没落盘
 * @note  上电时全 1：`NvM_ReadAll()` 之后，从没写过的块里装的是 ROM 默认值，
 *        也需要在第一次 `NvM_WriteAll()` 时落盘，否则"改回默认值"永远存不进去。
 */
static uint16_t NvM_DirtyMask;

/** @brief `NvM_WriteAll()` 正在推进 */
static bool NvM_WriteAllActive;

/** @brief `NvM_WriteAll()` 下一个要处理的块 id */
static uint16_t NvM_WriteAllNext;

/* ============================ [ 私有函数 ] ============================ */

/**
 * @brief 参数检查：块 id 是否合法
 * @retval true  合法
 * @retval false 越界（已上报 DET）
 */
static bool NvM_CheckBlockId(uint16_t BlockId, uint8_t ApiId)
{
	if (BlockId >= NvM_PortBlockCount()) {
		(void)Det_ReportError(NVM_MODULE_ID, 0u, ApiId, NVM_E_PARAM_BLOCK_ID);
		return false;
	}
	return true;
}

/**
 * @brief 把引擎的块状态翻译成 AUTOSAR 的请求结果
 * @param[in] id 块 id
 * @return `NVM_REQ_*`
 * @note  `UNINIT`（从未读写过）翻译成 `NVM_REQ_NOT_OK`：对上层来说
 *        "没有有效数据"和"上次失败"处置方式一样（都该回退默认值），
 *        而 AUTOSAR 没有"从未请求过"这个值。
 */
static NvM_RequestResultType NvM_MapBlockState(uint16_t id)
{
	switch (NvM_PortBlockState(id)) {
	case NVM_PORT_BLK_OK:
		return NVM_REQ_OK;
	case NVM_PORT_BLK_PENDING:
	case NVM_PORT_BLK_ERASE:
		return NVM_REQ_PENDING;
	case NVM_PORT_BLK_INTEGRITY_FAILED:
		return NVM_REQ_INTEGRITY_FAILED;
	case NVM_PORT_BLK_NOT_OK:
	case NVM_PORT_BLK_UNINIT:
	case NVM_PORT_BLK_ERROR:
	default:
		return NVM_REQ_NOT_OK;
	}
}

/**
 * @brief 标记某块为"已落盘"
 */
static void NvM_ClearDirty(uint16_t id)
{
	NvM_DirtyMask = (uint16_t)(NvM_DirtyMask & (uint16_t)~(1u << id));
}

/* ============================ [ 公共接口 ] ============================ */

/**
 * @brief 初始化 NvM
 *
 * @param[in] ConfigPtr AUTOSAR 配置指针
 * @warning **本参数被忽略**。块表在本工程是平台层编译期固定的
 *          （`app/platform/cvm0146/src/config/NvM_Cfg.c`），和 `Can_Init`/`Fee_Configure`
 *          的做法一致。传非 NULL 会让读者以为可以在运行期换表，那是做不到的
 *          （块表里全是 `const` 指针）。
 *
 * @note 本函数**异步**：返回后引擎还在扫描扇区，要持续调 `NvM_MainFunction()`
 *       直到 `NvM_GetStatus()` 返回 `MEMIF_IDLE`，再开始读写。
 */
void NvM_Init(const NvM_ConfigType *ConfigPtr)
{
	uint16_t count = NvM_PortBlockCount();

	(void)ConfigPtr;

	NvM_PortInit();

	if (count > NVM_DIRTY_MASK_MAX) {
		/* 块数超了掩码能表示的范围。不在这里截断 —— 那样会静默漏写块，
		 * 而是全 1，让 WriteAll 走"全写"的保守路径。 */
		NvM_DirtyMask = 0xFFFFu;
	} else {
		NvM_DirtyMask = (uint16_t)((1u << count) - 1u);
	}

	NvM_WriteAllActive = false;
	NvM_WriteAllNext   = 0u;
	NvM_Initialized    = true;
}

/**
 * @brief NvM 主函数
 * @note  必须周期性调用（本工程在 10 ms BSW 调度里）。它做两件事：
 *        1. 推动引擎状态机（转发给 `NvM_PortMainFunction()`）；
 *        2. 推进 `NvM_WriteAll()` 的脏块队列。
 * @warning 顺序不能反：先推引擎再判忙闲。反过来的话，上一拍投的作业
 *          这一拍才算"忙完"，会白等一拍 —— 5 个块就要多花 50 ms。
 */
void NvM_MainFunction(void)
{
	uint16_t id;

	NvM_PortMainFunction();

	if (!NvM_WriteAllActive) {
		return;
	}

	/* 引擎还忙着（含队列里压着刚投的作业），等下一拍 */
	if (NvM_PortIsBusy()) {
		return;
	}

	/* 找下一个还没落盘的块，投一个就返回 */
	while (NvM_WriteAllNext < NvM_PortBlockCount()) {
		id = NvM_WriteAllNext;
		NvM_WriteAllNext++;

		if ((NvM_DirtyMask & (uint16_t)(1u << id)) == 0u) {
			continue;   /* 不脏，跳过 */
		}

		if (NvM_PortWrite(id, NvM_PortBlockRam(id)) != NVM_PORT_RET_OK) {
			/* 受理失败（队列满/引擎拒绝）：把游标退回去，下一拍重试同一个块。
			 * 不能前进 —— 前进就等于把这个块的数据丢了，而且没人会知道。 */
			NvM_WriteAllNext = id;
			return;
		}

		NvM_ClearDirty(id);
		return;
	}

	/* 所有脏块都投完了 */
	NvM_WriteAllActive = false;
}

/**
 * @brief 读一个块到指定缓冲
 * @param[in]  BlockId    块 id
 * @param[out] NvM_DstPtr 目的缓冲（长度 ≥ `NvM_GetBlockDataPtrAndLength` 给出的长度）
 * @retval E_OK     作业已受理（**不代表已读完**，要等 `NvM_GetErrorStatus` 变化）
 * @retval E_NOT_OK 参数非法或引擎拒绝
 */
Std_ReturnType NvM_ReadBlock(NvM_BlockIdType BlockId, void *NvM_DstPtr)
{
	if (!NvM_Initialized) {
		(void)Det_ReportError(NVM_MODULE_ID, 0u, NVM_API_READ_BLOCK, NVM_E_UNINIT);
		return E_NOT_OK;
	}
	if (!NvM_CheckBlockId((uint16_t)BlockId, NVM_API_READ_BLOCK)) {
		return E_NOT_OK;
	}
	if (NvM_DstPtr == NULL) {
		(void)Det_ReportError(NVM_MODULE_ID, 0u, NVM_API_READ_BLOCK, NVM_E_PARAM_POINTER);
		return E_NOT_OK;
	}

	if (NvM_PortRead((uint16_t)BlockId, (uint8_t *)NvM_DstPtr) != NVM_PORT_RET_OK) {
		return E_NOT_OK;
	}

	return E_OK;
}

/**
 * @brief 写一个块
 *
 * @param[in] BlockId    块 id
 * @param[in] NvM_SrcPtr 数据源；**传 NULL 表示"写该块自己的 RAM 映像"**
 * @retval E_OK     作业已受理
 * @retval E_NOT_OK 参数非法或引擎拒绝
 *
 * @note `NvM_SrcPtr == NULL` 是 AUTOSAR 的标准用法，Dcm 的 0x27 安全访问计数
 *       就是这么写的（计数直接加在 `Dcm_NvmSecurityAccess_Ram` 上，
 *       然后 `NvM_WriteBlock(id, NULL)` 把它刷进 Flash）。
 *
 * @note 受理成功后立刻清脏标志：本工程所有块都配成立即写
 *       （`NvM_Cfg.c` 的 `immediate = true`），引擎收到就真的写 Flash，
 *       不存在"只写了 RAM"的情况。如果将来有人把某个块改成 `immediate=false`，
 *       **必须同时**去掉这里清脏标志的动作，否则那块数据永远进不了 Flash。
 */
Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId, const void *NvM_SrcPtr)
{
	const uint8_t *src;

	if (!NvM_Initialized) {
		(void)Det_ReportError(NVM_MODULE_ID, 0u, NVM_API_WRITE_BLOCK, NVM_E_UNINIT);
		return E_NOT_OK;
	}
	if (!NvM_CheckBlockId((uint16_t)BlockId, NVM_API_WRITE_BLOCK)) {
		return E_NOT_OK;
	}

	src = (NvM_SrcPtr != NULL) ? (const uint8_t *)NvM_SrcPtr
	                           : NvM_PortBlockRam((uint16_t)BlockId);
	if (src == NULL) {
		(void)Det_ReportError(NVM_MODULE_ID, 0u, NVM_API_WRITE_BLOCK, NVM_E_PARAM_POINTER);
		return E_NOT_OK;
	}

	if (NvM_PortWrite((uint16_t)BlockId, src) != NVM_PORT_RET_OK) {
		return E_NOT_OK;
	}

	NvM_ClearDirty((uint16_t)BlockId);

	return E_OK;
}

/**
 * @brief 标记块的 RAM 映像"已修改，待落盘"
 * @param[in] BlockId      块 id
 * @param[in] BlockChanged TRUE = 已修改
 * @retval E_OK     标记成功
 * @retval E_NOT_OK 参数非法
 * @note  传 FALSE 不清除脏标志：AUTOSAR 语义是"恢复为未修改"，
 *        但那意味着丢弃用户刚写进 RAM 的数据，本工程不提供这个能力，
 *        所以按"标记 TRUE 有效、FALSE 忽略"处理。
 */
Std_ReturnType NvM_SetRamBlockStatus(NvM_BlockIdType BlockId, boolean BlockChanged)
{
	if (!NvM_Initialized) {
		(void)Det_ReportError(NVM_MODULE_ID, 0u, NVM_API_SET_RAM_STATUS, NVM_E_UNINIT);
		return E_NOT_OK;
	}
	if (!NvM_CheckBlockId((uint16_t)BlockId, NVM_API_SET_RAM_STATUS)) {
		return E_NOT_OK;
	}

	if (TRUE == BlockChanged) {
		NvM_DirtyMask = (uint16_t)(NvM_DirtyMask | (uint16_t)(1u << BlockId));
	}

	return E_OK;
}

/**
 * @brief 取块的上次作业结果
 * @param[in]  BlockId         块 id
 * @param[out] RequestResultPtr 结果
 * @retval E_OK     查询成功
 * @retval E_NOT_OK 参数非法
 */
Std_ReturnType NvM_GetErrorStatus(NvM_BlockIdType BlockId,
                                  NvM_RequestResultType *RequestResultPtr)
{
	if (!NvM_Initialized) {
		(void)Det_ReportError(NVM_MODULE_ID, 0u, NVM_API_GET_ERROR, NVM_E_UNINIT);
		return E_NOT_OK;
	}
	if (!NvM_CheckBlockId((uint16_t)BlockId, NVM_API_GET_ERROR)) {
		return E_NOT_OK;
	}
	if (RequestResultPtr == NULL) {
		(void)Det_ReportError(NVM_MODULE_ID, 0u, NVM_API_GET_ERROR, NVM_E_PARAM_POINTER);
		return E_NOT_OK;
	}

	*RequestResultPtr = NvM_MapBlockState((uint16_t)BlockId);

	return E_OK;
}

/**
 * @brief 取块的 RAM 映像地址与有效长度
 * @param[in]  BlockId  块 id
 * @param[out] pDataPtr RAM 地址
 * @param[out] pLength  有效数据长度（不含 CRC 与对齐填充）
 * @retval E_OK     成功
 * @retval E_NOT_OK 参数非法
 * @note  Dem 上报故障快照时走这个接口直接改 RAM，再由 `NvM_WriteBlock(id, NULL)`
 *        统一落盘 —— 比"先 memcpy 到自己的缓冲再写"少一次拷贝。
 */
Std_ReturnType NvM_GetBlockDataPtrAndLength(NvM_BlockIdType BlockId, void **pDataPtr,
                                            uint16_t *pLength)
{
	if (!NvM_Initialized) {
		(void)Det_ReportError(NVM_MODULE_ID, 0u, NVM_API_GET_BLOCK_PTR, NVM_E_UNINIT);
		return E_NOT_OK;
	}
	if (!NvM_CheckBlockId((uint16_t)BlockId, NVM_API_GET_BLOCK_PTR)) {
		return E_NOT_OK;
	}
	if ((pDataPtr == NULL) || (pLength == NULL)) {
		(void)Det_ReportError(NVM_MODULE_ID, 0u, NVM_API_GET_BLOCK_PTR, NVM_E_PARAM_POINTER);
		return E_NOT_OK;
	}

	*pDataPtr = (void *)NvM_PortBlockRam((uint16_t)BlockId);
	*pLength  = NvM_PortBlockSize((uint16_t)BlockId);

	return E_OK;
}

/**
 * @brief 把全部块读进各自的 RAM 映像（上电快启动）
 * @note  不消耗 Flash 寿命，全部读一遍没有代价。读不到的块由引擎自动
 *        装 ROM 默认值，并把块状态标成 `INTEGRITY_FAILED`。
 */
void NvM_ReadAll(void)
{
	if (!NvM_Initialized) {
		(void)Det_ReportError(NVM_MODULE_ID, 0u, NVM_API_READ_ALL, NVM_E_UNINIT);
		return;
	}

	(void)NvM_PortReadAll();
}

/**
 * @brief 把所有"已修改"的块落盘
 * @note  只是**启动**一个后台过程，真正的写由 `NvM_MainFunction()` 逐块推进。
 *        要确认写完，轮询 `NvM_GetStatus()` 回到 `MEMIF_IDLE`。
 */
void NvM_WriteAll(void)
{
	if (!NvM_Initialized) {
		(void)Det_ReportError(NVM_MODULE_ID, 0u, NVM_API_WRITE_ALL, NVM_E_UNINIT);
		return;
	}

	NvM_WriteAllNext   = 0u;
	NvM_WriteAllActive = true;
}

/**
 * @brief 取消 `NvM_WriteAll()`
 * @note  已经投进引擎的块**不会**被取消，只是不再投后续的块。
 */
void NvM_CancelWriteAll(void)
{
	NvM_WriteAllActive = false;
}

/**
 * @brief 取 NvM 模块状态
 * @return `MEMIF_UNINIT` / `MEMIF_IDLE` / `MEMIF_BUSY`
 * @note  用于上电流程"等存储栈就绪"：`NvM_Init()` 之后循环
 *        `NvM_MainFunction()` 直到本函数返回 `MEMIF_IDLE`。
 */
MemIf_StatusType NvM_GetStatus(void)
{
	if (!NvM_Initialized) {
		return MEMIF_UNINIT;
	}

	if (NvM_WriteAllActive || NvM_PortIsBusy()) {
		return MEMIF_BUSY;
	}

	return MEMIF_IDLE;
}

/**
 * @brief 作业结束通知
 * @note  厂商引擎用"轮询块状态"判完成，不走回调（`NvM_Cfg.c` 里给引擎的
 *        notification 传的是 NULL）。本函数保留是为了满足 `NvM.h` 的接口契约，
 *        当前无人调用。
 */
void NvM_JobEndNotification(void)
{
}

/**
 * @brief 作业错误通知（同上，保留接口）
 */
void NvM_JobErrorNotification(void)
{
}

/**
 * @brief 取版本信息
 * @param[out] versionInfo 版本结构
 */
void NvM_GetVersionInfo(Std_VersionInfoType *versionInfo)
{
	if (versionInfo == NULL) {
		return;
	}

	versionInfo->vendorID         = 0u;      /* 本工程自制外观，无厂商 ID */
	versionInfo->moduleID         = NVM_MODULE_ID;
	versionInfo->sw_major_version = 1u;
	versionInfo->sw_minor_version = 0u;
	versionInfo->sw_patch_version = 0u;
}
