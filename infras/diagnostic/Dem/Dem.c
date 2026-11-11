/**
 * @file    Dem.c
 * @brief   诊断事件管理器（简化实现）：DTC 状态表 + 0x19/0x14 的后端
 *
 * @details @section DEM_SCOPE 这个文件是什么、不是什么
 *
 *          **是**：一个能驱动 Dcm 0x14 / 0x19 的 Dem，接口与 AUTOSAR 一致。
 *          `Dcm_Dsp.c` 里那 400 行现成的 0x19/0x14 实现**一行没改**就能用 ——
 *          前提是这 9 个 API 老老实实按规范返回。
 *
 *          **不是**：完整 Dem。没有去抖、没有老化、没有冻结帧。
 *          范围与理由见 `Dem_Cfg.h` 的 `@ref DEMCFG_SCOPE`。
 *
 *          @section DEM_LAYOUT DTC 表长什么样
 *          表就是 NvM 的 DTC 块 RAM 映像，4 条 × 16 字节，**零拷贝**：
 *
 *          @code
 *          struct {
 *              uint32 dtcCode;      // 低 24 位是 3 字节 UDS DTC，0 = 空槽
 *              uint16 occurCount;   // 发生次数（饱和 0xFFFF）
 *              uint16 firstBoot;    // 首次发生的启动序号
 *              uint16 lastBoot;     // 最近一次发生的启动序号
 *              uint8  channel;      // 哪一路 CAN
 *              uint8  errBits;      // 发生瞬间的错误位图（现场快照）
 *              uint8  fltConf;      // 发生瞬间的 FLTCONF
 *              uint8  status;       // 8 位 UDS 状态字节
 *          }  // = 16 字节
 *          @endcode
 *
 *          `errBits` / `fltConf` 是本工程特有的**现场快照**：完整 Dem 会把它做成
 *          "扩展数据记录"（用单独的 NvM 块 + 采集接口），这里直接塞进 DTC 条目 ——
 *          因为一共就 2 个字节，为它建一套记录机制不值得。
 *
 *          @section DEM_WHY_NOT_FULL 为什么不上完整 Dem
 *          完整实现 2070 行，还要配 `Dem_Cfg.c`（事件表 / DTC 表 / 内存目的 /
 *          去抖参数 / 冻结帧 / 老化阈值）。本工程只有一个故障源（CAN 总线），
 *          配出来的表 90% 是空转，出错时全是"配置写错了"而不是"逻辑坏了"。
 *
 *          真正需要升级的信号只有三个：① 要做老化；② 要做去抖；
 *          ③ 要 0x19 的快照/扩展数据子功能。到那时**只替换本文件**即可，
 *          调用方一行不用改。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：DTC 状态表 + Dem API 子集（供 Dcm 0x14/0x19 使用） |
 */

#include "Dem.h"
#include "Dem_Cfg.h"

#include "NvM.h"

#include <string.h>

/* ============================ [ 内部类型 ] ============================ */

/**
 * @brief 一条 DTC 记录（16 字节，直接映射 NvM 块的 1/4）
 * @warning 布局与 Flash 里的旧数据绑定。改字段只能往后接，
 *          不能改已有字段的顺序和宽度，否则老记录的字段会错位解释。
 */
typedef struct {
	uint32_t dtcCode;       /**< 低 24 位 = UDS DTC，0 = 空槽 */
	uint16_t occurCount;    /**< 发生次数（饱和） */
	uint16_t firstBoot;     /**< 首次发生的启动序号 */
	uint16_t lastBoot;      /**< 最近一次发生的启动序号 */
	uint8_t  channel;       /**< CAN 通道号 */
	uint8_t  errBits;       /**< 现场快照：错误位图 */
	uint8_t  fltConf;       /**< 现场快照：FLTCONF */
	uint8_t  status;        /**< 8 位 UDS 状态字节 */
} Dem_DtcRecordType;

/** @brief 布局自检：不是 16 字节就会与块长错位，必须编译期发现 */
typedef char Dem_DtcRecordSizeCheck[(sizeof(Dem_DtcRecordType) == DEM_CFG_DTC_RECORD_BYTES) ? 1 : -1];

/* ============================ [ 状态 ] ============================ */

/** @brief DTC 表 = NvM 块 RAM 映像（`Dem_Init()` 之后有效） */
static Dem_DtcRecordType *s_dtcTable;

/** @brief 实际可用条目数（由块长换算，不是写死宏） */
static uint8_t s_dtcNum;

/** @brief 本次启动序号（低 16 位写进记录） */
static uint16_t s_bootSeq;

/** @brief 是否可用 */
static bool s_ready;

/** @brief 有未落盘的修改 */
static bool s_dirty;

/** @brief 最近一次 `Dem_SetDTCFilter()` 的状态掩码（0 = 不过滤） */
static uint8_t s_filterMask;

/** @brief `Dem_GetNextFilteredDTC()` 的遍历游标 */
static uint8_t s_iterIdx;

/** @brief `Dem_SelectDTC()` 选中的 DTC（供 `Dem_ClearDTC()` 用） */
static uint32_t s_selectedDtc;

/** @brief `Dem_DisableDTCSetting()` 是否把更新关掉了 */
static bool s_updateDisabled;

/* ============================ [ 内部函数 ] ============================ */

/**
 * @brief 按故障码查记录
 * @return 记录指针；没有返回 NULL
 *
 * @note  **只按 dtcCode 匹配，不看通道**。这是 Dem 的核心语义：
 *        一个 DTC 可以挂多个事件（CAN0 总线故障、CAN1 总线故障都归 U0001），
 *        它们合并到同一条记录上、次数累加。
 *
 *        如果按通道分开记，0x19 会读出两条一模一样的 `C00100` ——
 *        测试仪会认为这是两个独立故障，而实车上它就是"总线坏了"一件事。
 *        `channel` 字段只保留**首次**出故障的那一路，用于排查。
 */
static Dem_DtcRecordType *Dem_Find(uint32_t dtcCode)
{
	uint8_t i;

	if (!s_ready) {
		return NULL;
	}

	for (i = 0u; i < s_dtcNum; i++) {
		if (s_dtcTable[i].dtcCode == dtcCode) {
			return &s_dtcTable[i];
		}
	}

	return NULL;
}

/**
 * @brief 找一条空记录
 * @return 空槽指针；表满返回 NULL
 */
static Dem_DtcRecordType *Dem_Alloc(void)
{
	uint8_t i;

	if (!s_ready) {
		return NULL;
	}

	for (i = 0u; i < s_dtcNum; i++) {
		if (s_dtcTable[i].dtcCode == 0u) {
			return &s_dtcTable[i];
		}
	}

	return NULL;
}

/**
 * @brief 事件编号 → CAN 通道
 * @return 通道号；非法事件号返回 0xFF
 */
static uint8_t Dem_EventToChannel(Dem_EventIdType eventId)
{
	switch (eventId) {
	case DEM_CFG_EVENT_CAN0_BUSOFF:
		return 0u;
	case DEM_CFG_EVENT_CAN1_BUSOFF:
		return 1u;
	default:
		return 0xFFu;
	}
}

/**
 * @brief 记录一次"失败"：建条目 / 累加次数 / 置状态位 / 存现场
 * @param[in] channel  通道号
 * @param[in] errBits  现场快照（错误位图），0 表示不更新快照
 * @param[in] fltConf  现场快照（FLTCONF），仅 `errBits != 0` 时生效
 *
 * @note  状态位规则（ISO 14229-1 附录 D.3）：
 *        - `TF`    本次测试失败 —— 失败即置
 *        - `TFTOC` 本操作循环失败 —— 失败即置，操作循环切换时清
 *        - `PDTC`  待定 —— 失败即置（本实现无去抖，等同于 TF）
 *        - `CDTC`  已确认 —— 失败即置（完整 Dem 要连续失败若干次才置）
 *        - `WIR`   告警灯请求 —— 随 CDTC 置位
 *
 *        本实现把四个都"立刻置位"。这是简化，但**不会让测试仪误判**：
 *        报出来的每条 DTC 都是真的发生过，只是比完整 Dem 更早进入"已确认"。
 */
static void Dem_StoreFailed(uint8_t channel, uint8_t errBits, uint8_t fltConf)
{
	Dem_DtcRecordType *rec;

	rec = Dem_Find(DEM_CFG_DTC_CAN_BUSOFF);
	if (rec == NULL) {
		rec = Dem_Alloc();
	}
	if (rec == NULL) {
		return;                 /* 表满：丢弃新事件，不覆盖老记录 */
	}

	if (rec->dtcCode == 0u) {
		rec->dtcCode    = DEM_CFG_DTC_CAN_BUSOFF;
		rec->channel    = channel;
		rec->occurCount = 1u;
		rec->firstBoot  = s_bootSeq;
	} else if (rec->occurCount != 0xFFFFu) {
		rec->occurCount++;
	}

	/* 现场快照只在**首次**失败时记：后续的快照会被前一次的恢复过程污染
	 * （恢复期间还会继续 ACK/位错误），拿它当根因会误判 */
	if ((errBits != 0u) && (rec->occurCount == 1u)) {
		rec->errBits = errBits;
		rec->fltConf = fltConf;
	}

	rec->lastBoot = s_bootSeq;
	rec->status  |= (uint8_t)(DEM_UDS_STATUS_TF | DEM_UDS_STATUS_TFTOC |
	                          DEM_UDS_STATUS_PDTC | DEM_UDS_STATUS_CDTC |
	                          DEM_UDS_STATUS_WIR);
	s_dirty = true;
}

/**
 * @brief 记录一次"通过"：清 TF，其余状态位保留
 * @note  完整 Dem 会按"连续通过 N 次"逐步清 PDTC/CDTC、减老化计数。
 *        本实现只清 TF —— 语义是"这次测试过了，但历史故障仍在"，
 *        测试仪据此看到的 `0x09`（TF=0, CDTC=1）是正确的。
 */
static void Dem_StorePassed(uint8_t channel)
{
	Dem_DtcRecordType *rec;

	rec = Dem_Find(DEM_CFG_DTC_CAN_BUSOFF);
	if (rec == NULL) {
		return;
	}

	rec->status &= (uint8_t)(~DEM_UDS_STATUS_TF);
	s_dirty = true;
}

/** @brief 判断记录是否满足当前过滤掩码 */
static bool Dem_MatchFilter(const Dem_DtcRecordType *rec)
{
	if (rec->dtcCode == 0u) {
		return false;
	}
	if (s_filterMask == 0u) {
		return true;            /* 掩码 0 = 不按状态过滤（0x19 0x0A 用的就是这个） */
	}
	return ((rec->status & s_filterMask) != 0u) ? true : false;
}

/* ============================ [ 公共 API ] ============================ */

void Dem_PreInit(void)
{
	s_dtcTable        = NULL;
	s_dtcNum          = 0u;
	s_bootSeq         = 0u;
	s_ready           = false;
	s_dirty           = false;
	s_filterMask      = 0u;
	s_iterIdx         = 0u;
	s_selectedDtc     = 0u;
	s_updateDisabled  = false;
}

/**
 * @brief 初始化：取 DTC 块的 RAM 映像
 * @param[in] ConfigPtr 本实现不使用（配置全在 `Dem_Cfg.h`）
 * @pre   `NvM_ReadAll()` 已完成
 * @note  签名保留 `const Dem_ConfigType *` 是为了与 AUTOSAR 一致 ——
 *        将来换成完整 Dem 时，调用方不用改。
 */
void Dem_Init(const Dem_ConfigType *ConfigPtr)
{
	void *ram = NULL;
	uint16_t len = 0u;

	(void)ConfigPtr;

	Dem_PreInit();

	if (NvM_GetBlockDataPtrAndLength((NvM_BlockIdType)DEM_CFG_NVM_BLOCK_ID,
	                                 &ram, &len) != E_OK) {
		return;
	}
	if ((ram == NULL) || (len < (uint16_t)DEM_CFG_NVM_BLOCK_BYTES)) {
		return;
	}

	s_dtcTable = (Dem_DtcRecordType *)ram;
	s_dtcNum   = (uint8_t)(len / (uint16_t)DEM_CFG_DTC_RECORD_BYTES);
	if (s_dtcNum > DEM_CFG_MAX_DTC) {
		s_dtcNum = DEM_CFG_MAX_DTC;
	}
	s_ready = true;
}

void Dem_Shutdown(void)
{
	s_ready = false;
	s_dtcTable = NULL;
}

/** @brief 记下本次启动序号，用于 DTC 的 firstBoot/lastBoot */
void Dem_SetBootSequence(uint32_t bootSeq)
{
	s_bootSeq = (uint16_t)(bootSeq & 0xFFFFu);
}

Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus)
{
	return Dem_SetEventStatusWithMonitorData(EventId, EventStatus, 0u, 0u);
}

/**
 * @brief 上报事件状态（带监视数据）
 * @param[in] EventId     事件号（`DEM_CFG_EVENT_*`）
 * @param[in] EventStatus `FAILED` / `PREFAILED` 记故障，`PASSED` / `PREPASSED` 清 TF
 * @param[in] monitorData0 现场数据 0：错误位图（0 = 不更新快照）
 * @param[in] monitorData1 现场数据 1：FLTCONF
 * @retval E_NOT_OK 事件号非法、未初始化，或 DTC 更新被 0x85 关掉了
 *
 * @note  `monitorData0/1` 是本工程扩展的用法：完整 Dem 里这两个参数
 *        喂给"扩展数据记录"，这里直接存进 DTC 条目当现场快照。
 */
Std_ReturnType Dem_SetEventStatusWithMonitorData(Dem_EventIdType EventId,
                                                 Dem_EventStatusType EventStatus,
                                                 Dem_MonitorDataType monitorData0,
                                                 Dem_MonitorDataType monitorData1)
{
	uint8_t channel;

	if (!s_ready) {
		return E_NOT_OK;
	}
	if (s_updateDisabled) {
		/* 0x85 关掉 DTC 更新后，事件照样监视，但不许改状态表 */
		return E_NOT_OK;
	}

	channel = Dem_EventToChannel(EventId);
	if (channel == 0xFFu) {
		return E_NOT_OK;
	}

	switch (EventStatus) {
	case DEM_EVENT_STATUS_FAILED:
	case DEM_EVENT_STATUS_PREFAILED:
	case DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED:
		Dem_StoreFailed(channel, (uint8_t)(monitorData0 & 0xFFu),
		                (uint8_t)(monitorData1 & 0xFFu));
		return E_OK;

	case DEM_EVENT_STATUS_PASSED:
	case DEM_EVENT_STATUS_PREPASSED:
		Dem_StorePassed(channel);
		return E_OK;

	default:
		return E_NOT_OK;
	}
}

Std_ReturnType Dem_ResetEventStatus(Dem_EventIdType EventId)
{
	uint8_t channel;

	if (!s_ready) {
		return E_NOT_OK;
	}

	channel = Dem_EventToChannel(EventId);
	if (channel == 0xFFu) {
		return E_NOT_OK;
	}

	Dem_StorePassed(channel);
	return E_OK;
}

Std_ReturnType Dem_GetEventUdsStatus(Dem_EventIdType EventId, Dem_UdsStatusByteType *UDSStatusByte)
{
	Dem_DtcRecordType *rec;
	uint8_t channel;

	if ((UDSStatusByte == NULL) || (!s_ready)) {
		return E_NOT_OK;
	}

	channel = Dem_EventToChannel(EventId);
	if (channel == 0xFFu) {
		return E_NOT_OK;
	}

	rec = Dem_Find(DEM_CFG_DTC_CAN_BUSOFF);
	*UDSStatusByte = (rec != NULL) ? rec->status : 0u;
	return E_OK;
}

Std_ReturnType Dem_GetDTCStatusAvailabilityMask(uint8_t ClientId,
                                                Dem_UdsStatusByteType *DTCStatusMask,
                                                Dem_DTCOriginType DTCOrigin)
{
	(void)ClientId;
	(void)DTCOrigin;

	if (DTCStatusMask == NULL) {
		return E_NOT_OK;
	}

	/* 老实报自己能表达的状态位。谎报会让测试仪等一个永远不会置的位。 */
	*DTCStatusMask = (Dem_UdsStatusByteType)DEM_CFG_STATUS_AVAILABILITY_MASK;
	return E_OK;
}

Std_ReturnType Dem_SetDTCFilter(uint8_t ClientId, uint8_t DTCStatusMask,
                                Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin,
                                boolean FilterWithSeverity, Dem_DTCSeverityType DTCSeverityMask,
                                boolean FilterForFaultDetectionCounter)
{
	(void)ClientId;
	(void)DTCFormat;
	(void)DTCOrigin;
	(void)FilterWithSeverity;
	(void)DTCSeverityMask;
	(void)FilterForFaultDetectionCounter;

	if (!s_ready) {
		return E_NOT_OK;
	}

	s_filterMask = DTCStatusMask;
	s_iterIdx    = 0u;
	return E_OK;
}

Std_ReturnType Dem_GetNumberOfFilteredDTC(uint8_t ClientId, uint16_t *NumberOfFilteredDTC)
{
	uint8_t i;
	uint16_t n = 0u;

	(void)ClientId;

	if ((NumberOfFilteredDTC == NULL) || (!s_ready)) {
		return E_NOT_OK;
	}

	for (i = 0u; i < s_dtcNum; i++) {
		if (Dem_MatchFilter(&s_dtcTable[i])) {
			n++;
		}
	}

	*NumberOfFilteredDTC = n;
	return E_OK;
}

Std_ReturnType Dem_GetNextFilteredDTC(uint8_t ClientId, uint32_t *DTC, uint8_t *DTCStatus)
{
	(void)ClientId;

	if ((DTC == NULL) || (DTCStatus == NULL) || (!s_ready)) {
		return E_NOT_OK;
	}

	/* 每次进来都从游标继续，直到表尾 —— 这正是 0x19 的遍历语义 */
	while (s_iterIdx < s_dtcNum) {
		if (Dem_MatchFilter(&s_dtcTable[s_iterIdx])) {
			*DTC       = s_dtcTable[s_iterIdx].dtcCode & 0x00FFFFFFu;
			*DTCStatus = s_dtcTable[s_iterIdx].status;
			s_iterIdx++;
			return E_OK;
		}
		s_iterIdx++;
	}

	return E_NOT_OK;    /* 遍历结束：0x19 靠这个返回值停下来 */
}

Std_ReturnType Dem_SelectDTC(uint8_t ClientId, uint32_t DTC, Dem_DTCFormatType DTCFormat,
                             Dem_DTCOriginType DTCOrigin)
{
	(void)ClientId;
	(void)DTCFormat;
	(void)DTCOrigin;

	if (!s_ready) {
		return E_NOT_OK;
	}

	/* 0x14 的 groupOfDTC：0xFFFFFF = 全部，否则按码匹配 */
	s_selectedDtc = DTC & 0x00FFFFFFu;
	return E_OK;
}

/**
 * @brief 清除选中的 DTC（0x14 的后端）
 *
 * @details 语义按 ISO 14229-1：
 *          - `groupOfDTC == 0xFFFFFF` → 清**全部**
 *          - 其它值 → 只清匹配该码的记录
 *
 *          清掉的不只是状态位，**整条记录变成空槽**（counT/启动序号一起归零）——
 *          这与"清除故障码"的实车语义一致：清完再读，那条 DTC 就不存在了。
 */
Std_ReturnType Dem_ClearDTC(uint8_t ClientId)
{
	uint8_t i;
	uint8_t cleared = 0u;

	(void)ClientId;

	if (!s_ready) {
		return E_NOT_OK;
	}

	for (i = 0u; i < s_dtcNum; i++) {
		if (s_dtcTable[i].dtcCode == 0u) {
			continue;
		}
		if ((s_selectedDtc == 0x00FFFFFFu) ||
		    ((s_dtcTable[i].dtcCode & 0x00FFFFFFu) == s_selectedDtc)) {
			(void)memset(&s_dtcTable[i], 0, sizeof(s_dtcTable[i]));
			cleared++;
		}
	}

	if (cleared != 0u) {
		s_dirty = true;
	}

	/* 清码成功即视为"操作循环重新开始"：遍历游标也复位 */
	s_iterIdx = 0u;
	return E_OK;
}

Std_ReturnType Dem_DisableDTCSetting(uint8_t ClientId)
{
	(void)ClientId;
	s_updateDisabled = true;
	return E_OK;
}

Std_ReturnType Dem_EnableDTCSetting(uint8_t ClientId)
{
	(void)ClientId;
	s_updateDisabled = false;
	return E_OK;
}

/**
 * @brief 周期任务：脏数据落盘
 * @note  放进 10 ms 节拍。内部判断引擎是否空闲，非空闲直接返回，不阻塞 ——
 *        与 M4 里 `Fault_MainFunction()` 的策略一致。
 */
void Dem_MainFunction(void)
{
	if ((!s_ready) || (!s_dirty)) {
		return;
	}

	if (NvM_GetStatus() != MEMIF_IDLE) {
		return;
	}

	if (NvM_WriteBlock((NvM_BlockIdType)DEM_CFG_NVM_BLOCK_ID, NULL) == E_OK) {
		s_dirty = false;
	}
}

/* ============================ [ 本工程扩展 ] ============================ */

/**
 * @brief 取第 N 条非空记录（`!b` 命令用）
 * @param[in]  index 从 0 开始的"第几条非空"
 * @param[out] rec   输出
 * @retval true  找到
 * @retval false 没有更多
 *
 * @note  不加这个函数的话，`!b` 要自己去摸 Dem 内部的表 —— 那就把
 *        "表在哪、怎么遍历"泄漏到应用层了。查询接口由 Dem 自己提供，
 *        应用只认 `Dem_DtcInfoType`。
 */
bool Dem_GetRecordByIndex(uint8_t index, Dem_DtcInfoType *rec)
{
	uint8_t i;
	uint8_t n = 0u;

	if ((rec == NULL) || (!s_ready)) {
		return false;
	}

	for (i = 0u; i < s_dtcNum; i++) {
		if (s_dtcTable[i].dtcCode == 0u) {
			continue;
		}
		if (n == index) {
			rec->dtcCode    = s_dtcTable[i].dtcCode & 0x00FFFFFFu;
			rec->occurCount = s_dtcTable[i].occurCount;
			rec->firstBoot  = s_dtcTable[i].firstBoot;
			rec->lastBoot   = s_dtcTable[i].lastBoot;
			rec->channel    = s_dtcTable[i].channel;
			rec->errBits    = s_dtcTable[i].errBits;
			rec->fltConf    = s_dtcTable[i].fltConf;
			rec->status     = s_dtcTable[i].status;
			return true;
		}
		n++;
	}

	return false;
}

/** @brief DTC 表容量（`!b` 打印"容量 N"用） */
uint8_t Dem_GetDtcCapacity(void)
{
	return s_dtcNum;
}
