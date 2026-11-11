/**
 * @file    Fee_Cfg.c
 * @brief   FEE 配置表：扇区实例、块实例、运行期对象，以及最终的 `Fee_Driver`
 *
 * @details 本文件只有数据和"把数据串起来的指针"，没有任何逻辑 —— 这是本工程的
 *          `cfg` 层约定（改功能 = 改表，不改代码）。真正的算法全在
 *          `infras/memory/Fee` 里，DFlash 访问全在 `src/FeeAc.c` 里。
 *
 *          @section FEECFG_INIT 三层结构为什么要这么套
 *          @code
 *          FeeType Fee_Driver
 *            ├─ sector   : Fee_SectorType   扇区表 + 块表（谁是活动扇区、每个块多长）
 *            ├─ flsMethod: FeeAc_FlsMethod  5 个函数指针（怎么读写 DFlash）
 *            ├─ runtime  : Fee_RunTimeType  状态机 + 当前作业 + GC 上下文 + 作业槽
 *            └─ buff     : Fee_Cache        拼包头用的 RAM
 *          @endcode
 *          厂商把它拆这么细是为了支持"多实例 + 运行期重配"。本工程只有一个
 *          DFlash 实例，所以全部 static 化、只导出 `Fee_Driver` 一个符号。
 *
 *          @warning `Fee_Runtime` 的字段**必须显式初始化**。`Fee_Configure()` 只覆盖
 *          `mainFunFsm` 和作业状态，`activeSector` 若不置 NULL，上电第一次
 *          `Fee_MainFunction()` 会拿野指针去判扇区状态。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：2 扇区 × 4 块 |
 */

#include <stddef.h>

#include "Fee_Cfg.h"

/* ============================ [ 扇区 ] ============================ */

/** @brief 每个扇区的运行期信息（扫描位置、剩余地址、擦除片进度、状态、错误码） */
static Fee_SectorInfoType Fee_SectorInfos[FEE_CFG_SECTOR_NUM];

/**
 * @brief 扇区表
 * @note  第 3 个字段是 `eraseSectionNum`（**不是**扇区大小）：擦除时按
 *        1 KB 片逐片擦，这个数决定擦几次。写错会漏擦尾部 → 那 1 KB 永远不是全 0xFF
 *        → 写块时预检失败 → 表现为"写到某个位置之后就再也写不进去"。
 */
static const Fee_SectorConfigType Fee_SectorCfgs[FEE_CFG_SECTOR_NUM] = {
	{
		(Fee_AddressType)FEE_CFG_SECTOR0_ADDR,
		(Fee_AddressType)(FEE_CFG_SECTOR0_ADDR + FEE_CFG_SECTOR_BYTES),
		FEE_CFG_ERASE_SECTION_NUM,
		&Fee_SectorInfos[0],
	},
	{
		(Fee_AddressType)FEE_CFG_SECTOR1_ADDR,
		(Fee_AddressType)(FEE_CFG_SECTOR1_ADDR + FEE_CFG_SECTOR_BYTES),
		FEE_CFG_ERASE_SECTION_NUM,
		&Fee_SectorInfos[1],
	},
};

/* ============================ [ 块 ] ============================ */

/**
 * @brief 块配置表：块号 + 字节数
 * @warning **必须按块号升序排列**。`Fee_SearchBlock()` 用的是二分查找，
 *          乱序的后果不是报错，而是"某些块永远找不到"——写它返回 `BL_INVALID`，
 *          读它返回 `BL_INVALID`，看起来像块没定义。
 * @note   字节数是"载荷 + CRC8"，即 NvM 侧 `dataSize + 1`。
 *          末尾有 `#if` 对账，不怕改漏。
 */
static const Fee_BlockConfigType Fee_BlockCfgs[FEE_CFG_BLOCK_NUM] = {
	{ (uint16_t)FEE_CFG_BLK_BOOTCNT, (uint16_t)FEE_CFG_BLK_BOOTCNT_BYTES },
	{ (uint16_t)FEE_CFG_BLK_CONFIG,  (uint16_t)FEE_CFG_BLK_CONFIG_BYTES  },
	{ (uint16_t)FEE_CFG_BLK_VIN,     (uint16_t)FEE_CFG_BLK_VIN_BYTES     },
	{ (uint16_t)FEE_CFG_BLK_DTC,     (uint16_t)FEE_CFG_BLK_DTC_BYTES     },
};

/** @brief 每个块的最新数据落在 Flash 哪个地址（初始化时扫描扇区头重建） */
static Fee_BlockInfoType Fee_BlockInfos[FEE_CFG_BLOCK_NUM];

/** @brief 块表：配置 + 运行期信息配对 */
static const Fee_BlockType Fee_Blocks[FEE_CFG_BLOCK_NUM] = {
	{ &Fee_BlockCfgs[0], &Fee_BlockInfos[0] },
	{ &Fee_BlockCfgs[1], &Fee_BlockInfos[1] },
	{ &Fee_BlockCfgs[2], &Fee_BlockInfos[2] },
	{ &Fee_BlockCfgs[3], &Fee_BlockInfos[3] },
};

/** @brief 扇区集合（`sectorSize` 在这里是**扇区个数**，厂商命名如此） */
static const Fee_SectorType Fee_Sector = {
	(uint16_t)FEE_CFG_SECTOR_NUM,
	&Fee_SectorCfgs[0],
	(uint16_t)FEE_CFG_BLOCK_NUM,
	&Fee_Blocks[0],
};

/* ============================ [ 运行期对象 ] ============================ */

/** @brief 系统作业槽（GC 用，由 FEE 内部发起） */
static Fee_JobControlBlockType Fee_SysJob = {
	FEE_JOB_UNLOCK, 0u, 0u, FEE_JOB_OP_UNDEFINE, NULL, NULL
};

/** @brief 用户作业槽（读/写，由 `Fee_Read()` / `Fee_Write()` 发起） */
static Fee_JobControlBlockType Fee_UserJob = {
	FEE_JOB_UNLOCK, 0u, 0u, FEE_JOB_OP_UNDEFINE, NULL, NULL
};

/**
 * @brief 当前正在执行的作业副本（`runtime->job` 指向它）
 *
 * @warning **必须是独立的第三个对象，不能复用 `Fee_SysJob` 或 `Fee_UserJob`。**
 *
 *          原因是 `Fee_GetSysJob()` / `Fee_GetUserJob()` 都是
 *          "把作业槽整个结构体拷进 `runtime->job`"：
 *          @code
 *          (*config) = *obj->userJob;      // fee_jobs.h:141
 *          @endcode
 *          如果 `runtime->job` 指向 `Fee_SysJob`，那么取用户作业时会把 READ/WRITE
 *          连同 `lock = FEE_JOB_LOCK` 一起写进**系统作业槽**。后果是：
 *          - `Fee_GetSysJob()` 从此永远返回 true（sysJob 已被锁）；
 *          - 而它的 `op` 是 READ，不是 GC，于是 `Fee_MainFunction` 的 IDLE 分支
 *            什么都不做，也**永远轮不到 `Fee_GetUserJob`**；
 *          - 引擎状态一直是 IDLE、`jobResult` 一直是 PENDING、块状态一直是
 *            PENDING —— 三个"正常"的值凑成一个死锁，没有任何报错。
 *          这个坑的实际表现是 `NvM_ReadAll()` 永久超时。
 */
static Fee_JobControlBlockType Fee_JobCurrent = {
	FEE_JOB_UNLOCK, 0u, 0u, FEE_JOB_OP_UNDEFINE, NULL, NULL
};

/**
 * @brief 作业调度槽
 * @note  `accept` 初始 false：`Fee_Configure()` 会把它保持为 false，
 *        直到初始化 + 扫描完成（`Fee_EnableJobs()`）才放开 —— 这就是
 *        "上电后头几百毫秒内调 Fee_Write 会返回 NOT_OK" 的原因，不是 bug。
 */
static Fee_JobsType Fee_Jobs = {
	false, &Fee_UserJob, &Fee_SysJob
};

/** @brief GC 上下文（整扇区搬迁用） */
static Fee_GcRuntimeType Fee_GcRuntime = {
	FEE_GC_INIT, FEE_GC_COPY_WRITE_MARK, NULL, 0u, NULL, NULL, NULL, FEE_GC_STATE_NO_ERROR
};

/**
 * @brief 运行期总状态
 * @note  初值直接放在 ERROR/初始化失败态，`Fee_Configure()` 会改写成 INITIALIZATION。
 *        这样万一有人忘了调 `Fee_Configure()`，状态机会立刻暴露问题，
 *        而不是从一个"看起来正常"的 IDLE 开始乱跑。
 */
static Fee_RunTimeType Fee_Runtime = {
	FEE_MAIN_FUN_FSM_ERROR,
	FEE_INITIALIZATION_ERROR,
	&Fee_Jobs,
	NULL,                     /* activeSector：必须显式 NULL，见文件头 @warning */
	&Fee_JobCurrent,          /* job：当前作业副本，**不能**指向 SysJob，见上方 @warning */
	&Fee_GcRuntime,
	FEE_JOB_RESULT_OK
};

/** @brief 拼包头的临时缓存（FEE 内部使用，不要外部引用） */
static uint8_t Fee_Cache[FEE_CFG_CACHE_BYTES];

/* ============================ [ 导出实例 ] ============================ */

const FeeType Fee_Driver = {
	&Fee_Sector,
	&FeeAc_FlsMethod,
	&Fee_Runtime,
	(void *)&Fee_Cache[0],
};
