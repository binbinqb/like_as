/**
 * @file    NvM_Cfg.c
 * @brief   NvM 块表 + `NvM_Port*` 引擎实现（厂商 NvM/FEE 与 AUTOSAR 外观的接合点）
 *
 * @details @section NVMCFG_TWO_JOBS 本文件干两件事，界线要分清
 *
 *          **① 块表**（纯数据）—— 每块 5 个数组 + 一行块项：
 *          @code
 *          Nvm_BlockItemType            语义：块号/长度/是否立即写/CRC/优先级
 *            ├─ buff[]                 每个数据集的 {ROM 默认值, RAM 映像}
 *            ├─ info[]                 每个数据集的运行期状态（引擎内部改）
 *            └─ tempRamBuffPtr         拼包缓冲（数据 + CRC）
 *          @endcode
 *          看着啰嗦，但这正是"RAM 映像 + ROM 默认值 + 全块 CRC"三件事的落地方式。
 *
 *          **② `NvM_Port*` 实现**（把引擎包成中性接口）—— 见 `NvM_Port.h`。
 *          只有这里能同时看见厂商类型（`Nvm_Type` / `Nvm_BlockItemType`）
 *          和 AUTOSAR 侧的需求；`infras/memory/NvM/NvM.c` 一律看不见厂商头。
 *
 *          @section NVMCFG_TICK 两个 MainFunction 的调用顺序为什么是本文件负责
 *          引擎是两层（NvM → FEE），各自都要被 tick。如果让应用分别调，
 *          顺序错了或漏了一个，症状都是"作业永远 PENDING"，而且没有任何报错。
 *          所以这里把两层的 tick 收进一个函数 `NvM_PortMainFunction()`，
 *          **自下而上**（先 Fee 后 NvM）—— 上层这一拍就能看到下层这一拍的状态变化，
 *          比反过来快一拍收敛。
 *
 *          @section NVMCFG_ORDER 块表必须按块号升序
 *          `Nvm_Block_Search()` 是二分查找。乱序不报错，只是"搜不到"，
 *          表现为读写返回 `NVM_RETURN_NOT_OK` —— 和"队列满"同一个返回值，
 *          极易误判成队列问题。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：4 个块 + NvM_Port 实现 |
 */

#include <stddef.h>

#include "NvM_Cfg.h"
#include "NvM/NvM_Port.h"

#include "Fee_Cfg.h"

#include "fee/fee.h"
#include "nvm/nvm.h"
#include "nvm/nvm_types.h"
#include "nvm/nvm_queue.h"
#include "nvm/nvm_statemachine.h"

/* ============================ [ 与 FEE 的编译期对账 ] ============================ */
/*
 * 引擎写进 FEE 的字节数是 `dataSize + 1`（CRC8）。FEE 的块长若比它小，
 * `Fee_Write()` 会返回 OK 但只存了前半截 —— 读回来的 CRC 必然失败，
 * 现象是"每次上电都恢复默认值"，而两层日志都显示成功。
 * 所以这里用 #if 卡死，改一处漏改另一处直接编译不过。
 */
#if (FEE_CFG_BLK_BOOTCNT_BYTES != (NVM_CFG_BLK_BOOTCNT_SIZE + 1u))
#error "FEE 侧 BOOTCNT 块长必须等于 NvM 载荷 + 1 字节 CRC8"
#endif
#if (FEE_CFG_BLK_CONFIG_BYTES != (NVM_CFG_BLK_CONFIG_SIZE + 1u))
#error "FEE 侧 CONFIG 块长必须等于 NvM 载荷 + 1 字节 CRC8"
#endif
#if (FEE_CFG_BLK_VIN_BYTES != (NVM_CFG_BLK_VIN_SIZE + 1u))
#error "FEE 侧 VIN 块长必须等于 NvM 载荷 + 1 字节 CRC8"
#endif
#if (FEE_CFG_BLK_DTC_BYTES != (NVM_CFG_BLK_DTC_SIZE + 1u))
#error "FEE 侧 DTC 块长必须等于 NvM 载荷 + 1 字节 CRC8"
#endif

/* ============================ [ 块存储：ROM 默认 / RAM 映像 / 拼包缓冲 ] ============================ */

/*
 * 每块 5 个数组，命名统一为 Nvm_<Rom|Ram|Buff|Info|Temp>_<块>。
 * 数组长度一律用 NVM_CFG_BYTES()（载荷 + CRC 再 8 字节对齐），
 * 原因见 NvM_Cfg.h 的 @ref NVMCFG_ALIGN —— 开小了会踩掉相邻数组。
 */

/* ---- 0x10 启动计数 ---- */

/** @brief 出厂默认：计数 0 + 魔数 "BCM1"（用来区分"新片"与"真的数到 0"） */
static const uint8_t Nvm_Rom_BootCnt[NVM_CFG_BYTES(NVM_CFG_BLK_BOOTCNT_SIZE)] = {
	0x00u, 0x00u, 0x00u, 0x00u, 'B', 'C', 'M', '1'
};

static uint8_t Nvm_Ram_BootCnt[NVM_CFG_BYTES(NVM_CFG_BLK_BOOTCNT_SIZE)];

static const Nvm_BlockBuffType Nvm_Buff_BootCnt[1] = {
	{ Nvm_Rom_BootCnt, Nvm_Ram_BootCnt }
};

static Nvm_BlockInfoType Nvm_Info_BootCnt[1];

static uint8_t Nvm_Temp_BootCnt[NVM_CFG_BYTES(NVM_CFG_BLK_BOOTCNT_SIZE)];

/* ---- 0x20 车辆配置字 ---- */

/** @brief 出厂默认：首字节 0x01 作为"配置版本"，其余 0 */
static const uint8_t Nvm_Rom_Config[NVM_CFG_BYTES(NVM_CFG_BLK_CONFIG_SIZE)] = {
	0x01u
};

static uint8_t Nvm_Ram_Config[NVM_CFG_BYTES(NVM_CFG_BLK_CONFIG_SIZE)];

static const Nvm_BlockBuffType Nvm_Buff_Config[1] = {
	{ Nvm_Rom_Config, Nvm_Ram_Config }
};

static Nvm_BlockInfoType Nvm_Info_Config[1];

static uint8_t Nvm_Temp_Config[NVM_CFG_BYTES(NVM_CFG_BLK_CONFIG_SIZE)];

/* ---- 0x30 VIN ---- */

/** @brief 出厂默认 VIN：17 字节 ASCII，不带 '\0'（UDS 22 F1 90 也是 17 字节） */
static const uint8_t Nvm_Rom_Vin[NVM_CFG_BYTES(NVM_CFG_BLK_VIN_SIZE)] = {
	'C', 'V', 'M', '0', '1', '4', '6', 'M', '4', 'N', 'V', 'M', '0', '0', '0', '0', '1'
};

static uint8_t Nvm_Ram_Vin[NVM_CFG_BYTES(NVM_CFG_BLK_VIN_SIZE)];

static const Nvm_BlockBuffType Nvm_Buff_Vin[1] = {
	{ Nvm_Rom_Vin, Nvm_Ram_Vin }
};

static Nvm_BlockInfoType Nvm_Info_Vin[1];

static uint8_t Nvm_Temp_Vin[NVM_CFG_BYTES(NVM_CFG_BLK_VIN_SIZE)];

/* ---- 0x40 故障快照 ---- */

/** @brief 出厂默认：全 0 = 无故障 */
static const uint8_t Nvm_Rom_Dtc[NVM_CFG_BYTES(NVM_CFG_BLK_DTC_SIZE)] = {
	0x00u
};

static uint8_t Nvm_Ram_Dtc[NVM_CFG_BYTES(NVM_CFG_BLK_DTC_SIZE)];

static const Nvm_BlockBuffType Nvm_Buff_Dtc[1] = {
	{ Nvm_Rom_Dtc, Nvm_Ram_Dtc }
};

static Nvm_BlockInfoType Nvm_Info_Dtc[1];

static uint8_t Nvm_Temp_Dtc[NVM_CFG_BYTES(NVM_CFG_BLK_DTC_SIZE)];

/* ============================ [ 块项表 ] ============================ */

/*
 * 字段顺序（照 Nvm_BlockItemType）：
 *   number, dataSize, type, datasetNum, immediate, crc, priority, buff, info, temp
 *
 * ⚠ immediate 全部为 true，理由见 NvM_Cfg.h 的 @ref NVMCFG_IMMEDIATE：
 *   引擎的 false 分支只写 RAM，与 AUTOSAR 的 WriteBlock 语义冲突。
 *   "延迟落盘"由 NvM.c 的脏块掩码 + NvM_WriteAll() 实现。
 *
 * ⚠ 必须按块号升序（二分查找）。
 */
static const Nvm_BlockItemType Nvm_BlockItems[NVM_CFG_BLOCK_NUM] = {
	{
		(uint16_t)FEE_CFG_BLK_BOOTCNT,
		(uint16_t)NVM_CFG_BLK_BOOTCNT_SIZE,
		NVM_BLOCK_NORMAL,
		1u,
		true,
		NVM_CRC8,
		0u,                     /* 优先级 0 = 最高 */
		Nvm_Buff_BootCnt,
		Nvm_Info_BootCnt,
		Nvm_Temp_BootCnt,
	},
	{
		(uint16_t)FEE_CFG_BLK_CONFIG,
		(uint16_t)NVM_CFG_BLK_CONFIG_SIZE,
		NVM_BLOCK_NORMAL,
		1u,
		true,
		NVM_CRC8,
		1u,
		Nvm_Buff_Config,
		Nvm_Info_Config,
		Nvm_Temp_Config,
	},
	{
		(uint16_t)FEE_CFG_BLK_VIN,
		(uint16_t)NVM_CFG_BLK_VIN_SIZE,
		NVM_BLOCK_NORMAL,
		1u,
		true,
		NVM_CRC8,
		2u,
		Nvm_Buff_Vin,
		Nvm_Info_Vin,
		Nvm_Temp_Vin,
	},
	{
		(uint16_t)FEE_CFG_BLK_DTC,
		(uint16_t)NVM_CFG_BLK_DTC_SIZE,
		NVM_BLOCK_NORMAL,
		1u,
		true,
		NVM_CRC8,
		3u,
		Nvm_Buff_Dtc,
		Nvm_Info_Dtc,
		Nvm_Temp_Dtc,
	},
};

static const Nvm_BlockType Nvm_BlockTable = {
	NVM_CFG_BLOCK_NUM,
	Nvm_BlockItems,
};

/* ============================ [ 状态机表 ] ============================ */

/** @brief 状态机表：下标必须与 `Nvm_stateType` 的枚举值一一对应 */
static const Nvm_StateMachineType Nvm_StateMachines[] = {
	{ NULL,                            NULL                            },   /* UNINIT    = 0 */
	{ NULL,                            Nvm_StateMachine_Idle           },   /* IDLE      = 1 */
	{ Nvm_StateMachine_Read_Entry,     Nvm_StateMachine_Read           },   /* READ      = 2 */
	{ Nvm_StateMachine_Write_Entry,    Nvm_StateMachine_Write          },   /* WRITE     = 3 */
	{ Nvm_StateMachine_ReadAll_Entry,  Nvm_StateMachine_ReadAll        },   /* READALL   = 4 */
	{ Nvm_StateMachine_WriteAll_Entry, Nvm_StateMachine_WriteAll       },   /* WRITEALL  = 5 */
	{ Nvm_StateMachine_Erase_Entry,    Nvm_StateMachine_Erase          },   /* ERASE     = 6 */
	{ Nvm_StateMachine_EraseAll_Entry, Nvm_StateMachine_EraseAll       },   /* ERASEALL  = 7 */
	{ NULL,                            NULL                            },   /* INVALID   = 8 */
};

/* ============================ [ 作业队列与运行期 ] ============================ */

static Nvm_QueueMemberType Nvm_QueueMembers[NVM_CFG_QUEUE_NUM];

static Nvm_QueueType Nvm_Queue = {
	0u, NVM_CFG_QUEUE_NUM, Nvm_QueueMembers
};

static Nvm_EraseJobType          Nvm_EraseJob;
static Nvm_ReadJobType           Nvm_ReadJob;
static Nvm_WriteJobType          Nvm_WriteJob;
static Nvm_ReadAllJobType        Nvm_ReadAllJob;
static Nvm_WriteAllJobType       Nvm_WriteAllJob;
static Nvm_EraseAllJobType       Nvm_EraseAllJob;
static Nvm_ImmediateReadJobType  Nvm_ImmediateReadJob;
static Nvm_ImmediateWriteJobType Nvm_ImmediateWriteJob;

/**
 * @brief 运行期总状态
 * @note  初值 UNINIT：`Nvm_Configure()` 会改写成 IDLE。
 *        两者都不等于 `FEE_STATE_INVALID`，所以 `Nvm_MainFunction()` 从第一拍就会跑。
 */
static Nvm_RunTimeType Nvm_RunTime = {
	NVM_STATE_UNINIT,
	NVM_STATE_UNINIT,
	&Nvm_Queue,
	&Nvm_EraseJob,
	&Nvm_ReadJob,
	&Nvm_WriteJob,
	&Nvm_ReadAllJob,
	&Nvm_WriteAllJob,
	&Nvm_EraseAllJob,
	&Nvm_ImmediateReadJob,
	&Nvm_ImmediateWriteJob,
};

/* ============================ [ FEE 桥接方法 ] ============================ */

/**
 * @brief 把引擎的写请求转给 FEE
 * @param[in] blockNumber 块号（引擎已把数据集编号加进去了）
 * @param[in] dataBuffer  数据（长度 = 载荷 + CRC8）
 * @param[in] notificationPtr 引擎的通知回调，**不透传**给 FEE
 * @return true 请求已受理（不代表已写完，结果靠 `getJobResult()` 查）
 * @note 通知回调不透传：两个模块的通知类型不同，而且引擎是**轮询**
 *       `getJobResult()` 判断完成的，回调传下去也没人用。
 */
volatile uint32_t NvM_Cfg_WriteCount;

static bool NvM_Cfg_WriteFee(uint16_t blockNumber, uint8_t *dataBuffer,
                             NvmNotificationPtrType notificationPtr)
{
	(void)notificationPtr;
	NvM_Cfg_WriteCount++;

	return (Fee_Write(&Fee_Driver, blockNumber, dataBuffer, NULL) == FEE_RETURN_OK) ? true : false;
}

/**
 * @brief 把引擎的读请求转给 FEE
 * @param[in] blockNumber 块号
 * @param[in] blockOffset 引擎固定传 0（`NVM_BLOCK_MAIN_IDX`）；FEE 不支持块内偏移
 * @param[out] dataBuffer 读出缓冲（长度必须 ≥ FEE 侧块长，见 NvM_Cfg.h 的对账）
 * @param[in] notificationPtr 同上，不透传
 * @return true 请求已受理
 */
static bool NvM_Cfg_ReadFee(uint16_t blockNumber, uint16_t blockOffset,
                            uint8_t *dataBuffer, NvmNotificationPtrType notificationPtr)
{
	(void)notificationPtr;

	return (Fee_Read(&Fee_Driver, blockNumber, blockOffset, dataBuffer, NULL) == FEE_RETURN_OK) ? true : false;
}

/**
 * @brief 把 FEE 的上次作业结果转成引擎的枚举
 * @note  两个枚举值完全一致（OK/NOT_OK/PENDING/BL_INCONSISTENT/BL_INVALID），
 *        所以这里直接强转，但加了注释说明"为什么可以"。
 */
static NVM_JobResultType NvM_Cfg_GetJobResult(void)
{
	return (NVM_JobResultType)Fee_GetJobResult(&Fee_Driver);
}

/**
 * @brief 把 FEE 的状态转成引擎的状态
 * @note  用显式 switch 而不是强转：枚举顺序一旦变化，编译器会报
 *        `-Wswitch` 缺分支（本工程开了 `-Wall`），而不是让引擎永远以为下层在忙。
 */
static Nvm_StatusType NvM_Cfg_GetFeeStatus(void)
{
	switch (Fee_GetStatus(&Fee_Driver)) {
	case FEE_STATUS_IDLE:
		return NVM_STATUS_IDLE;
	case FEE_STATUS_READ:
		return NVM_STATUS_READ;
	case FEE_STATUS_WRITE:
		return NVM_STATUS_WRITE;
	case FEE_STATUS_GC:
		return NVM_STATUS_GC;
	case FEE_STATUS_UNINIT:
		/* 初始化/扫描阶段：对上层来说就是"还轮不到你"，当成忙处理 */
		return NVM_STATUS_UNKNOW;
	case FEE_STATUS_ERROR:
	default:
		return NVM_STATUS_ERROR;
	}
}

static const Nvm_MethodType Nvm_Methods = {
	NvM_Cfg_WriteFee,
	NvM_Cfg_ReadFee,
	FeeAc_CalcCrc8,
	NvM_Cfg_GetJobResult,
	NvM_Cfg_GetFeeStatus,
};

/* ============================ [ 导出实例 ] ============================ */

const NvmType NvM_Driver = {
	&Nvm_BlockTable,
	Nvm_StateMachines,
	&Nvm_Methods,
	&Nvm_RunTime,
};

/* ============================ [ NvM_Port 实现 ] ============================ */
/*
 * 这一节是 `infras/memory/NvM/NvM.c` 与厂商引擎之间**唯一**的接合点。
 * 上面那些表、下面这些函数，构成了"引擎"对 AUTOSAR 外观的全部可见面。
 */

/**
 * @brief 初始化存储栈（DFlash 适配 → FEE → NvM，自下而上）
 * @note  顺序不能换：`FeeAc_Init()` 关缓存并配 flash 驱动，
 *        `Fee_Configure()` 只初始化状态机、不碰 Flash，
 *        `Nvm_Configure()` 同理。真正的扇区扫描发生在之后的每一拍
 *        `NvM_PortMainFunction()` 里。
 */
void NvM_PortInit(void)
{
	FeeAc_Init();
	Fee_Configure(&Fee_Driver);
	Nvm_Configure(&NvM_Driver);
}

/**
 * @brief 推动两层状态机
 * @note  顺序**自下而上**：先 FEE 后 NvM。反过来的话，上层这一拍看到的是
 *        下层上一拍的状态，收敛会慢一拍（BlockState 要多等一个 10 ms 才变）。
 */
void NvM_PortMainFunction(void)
{
	Fee_MainFunction(&Fee_Driver);
	Nvm_MainFunction(&NvM_Driver);
}

/**
 * @brief 引擎是否忙
 * @retval true  状态机不在 IDLE，或队列里还有没被取走的作业
 * @note  两个条件都要看：状态机在没有作业时也是 IDLE，但队列里可能压着
 *        上一拍刚投进去的作业。
 */
bool NvM_PortIsBusy(void)
{
	if (Nvm_GetStatus(&NvM_Driver) != NVM_STATE_IDLE) {
		return true;
	}
	if (Nvm_Queue_CheckEmpty(NvM_Driver.runtime->queue) != NVM_RETURN_OK) {
		return true;
	}
	return false;
}

/** @brief 块总数 */
uint16_t NvM_PortBlockCount(void)
{
	return (uint16_t)NVM_CFG_BLOCK_NUM;
}

/**
 * @brief 取块的有效数据长度
 * @note  返回的是 `dataSize`（载荷，不含 CRC），不是 FEE 侧块长 ——
 *        上层不需要知道 CRC 占了几字节。
 */
uint16_t NvM_PortBlockSize(uint16_t id)
{
	if (id >= (uint16_t)NVM_CFG_BLOCK_NUM) {
		return 0u;
	}

	return Nvm_BlockItems[id].dataSize;
}

/**
 * @brief 取块的 RAM 映像地址
 * @note  `NvM_WriteBlock(id, NULL)` 的写入源就是它。
 */
uint8_t *NvM_PortBlockRam(uint16_t id)
{
	if (id >= (uint16_t)NVM_CFG_BLOCK_NUM) {
		return NULL;
	}

	return (uint8_t *)Nvm_BlockItems[id].buff[0].ramBuffPtr;
}

/**
 * @brief 请求读块
 * @note  `Nvm_Read` 是异步的：受理后作业进队列，真正的数据在
 *        若干拍 `NvM_PortMainFunction()` 之后才落到 `dst`。
 */
NvM_PortRetType NvM_PortRead(uint16_t id, uint8_t *dst)
{
	if ((id >= (uint16_t)NVM_CFG_BLOCK_NUM) || (dst == NULL)) {
		return NVM_PORT_RET_NOT_OK;
	}

	if (Nvm_Read(&NvM_Driver, Nvm_BlockItems[id].number, dst) != NVM_RETURN_OK) {
		return NVM_PORT_RET_NOT_OK;
	}

	return NVM_PORT_RET_OK;
}

/**
 * @brief 请求写块
 * @warning `Nvm_Write` 的入参不是 `const`，这里必须强转。
 *          安全性在于引擎只把 `src` 当源（`memcpy` 到自己的 temp 缓冲），
 *          不会写回 —— 这一点在 `nvm_statemachine.c:158` 的 `NVM_WRITEFSM_INIT`
 *          分支里可以直接确认。
 */
NvM_PortRetType NvM_PortWrite(uint16_t id, const uint8_t *src)
{
	if ((id >= (uint16_t)NVM_CFG_BLOCK_NUM) || (src == NULL)) {
		return NVM_PORT_RET_NOT_OK;
	}

	if (Nvm_Write(&NvM_Driver, Nvm_BlockItems[id].number, (uint8_t *)src) != NVM_RETURN_OK) {
		return NVM_PORT_RET_NOT_OK;
	}

	return NVM_PORT_RET_OK;
}

/** @brief 请求把全部块读进 RAM 映像 */
NvM_PortRetType NvM_PortReadAll(void)
{
	if (Nvm_ReadAll(&NvM_Driver) != NVM_RETURN_OK) {
		return NVM_PORT_RET_NOT_OK;
	}

	return NVM_PORT_RET_OK;
}

/**
 * @brief 查询块状态
 * @note  强转成立：`NvM_PortBlockStateType` 的取值是照 `Nvm_BlockState` 抄的。
 *        如果哪天 SDK 改了那个枚举，编译器不会拦（两个不同枚举之间强转合法），
 *        所以 `NvM_Cfg.h` 里留了注释说明对应关系，改的时候要一起改。
 */
NvM_PortBlockStateType NvM_PortBlockState(uint16_t id)
{
	if (id >= (uint16_t)NVM_CFG_BLOCK_NUM) {
		return NVM_PORT_BLK_ERROR;
	}

	return (NvM_PortBlockStateType)Nvm_GetBlockStatus(&NvM_Driver,
	                                                 Nvm_BlockItems[id].number);
}

/**
 * @brief 取底层 FEE 的原始状态码（调试用）
 * @note  `Fee_StatusType` 的取值：0=UNINIT 1=IDLE 2=READ 3=WRITE 4=GC 5=UNKNOW 6=ERROR
 */
uint8_t NvM_PortDbgFeeState(void)
{
	return (uint8_t)Fee_GetStatus(&Fee_Driver);
}

/**
 * @brief 取 NvM 立即读作业的子状态（调试用）
 * @return `NVM_IMMEDIATEREADFSM_*`：1=MAIN 2=MAIN_RETRY 3=WMF 4=FINISH 5=READERROR 0xFF=ERROR
 */
uint8_t NvM_PortDbgReadJob(void)
{
	return (uint8_t)Nvm_ImmediateReadJob.job;
}

/**
 * @brief 取 NvM 状态机状态（调试用）
 * @return `Nvm_stateType`：0=UNINIT 1=IDLE 2=READ 3=WRITE 4=READALL 5=WRITEALL 6=ERASE 7=ERASEALL
 */
uint8_t NvM_PortDbgNvmState(void)
{
	return (uint8_t)Nvm_RunTime.state;
}

/**
 * @brief 取 FEE 的上次作业结果（调试用）
 * @return `Fee_JobResultType`：0=OK 1=NOT_OK 2=PENDING 3=BL_INCONSISTENT 4=BL_INVALID
 */
uint8_t NvM_PortDbgJobResult(void)
{
	return (uint8_t)Fee_GetJobResult(&Fee_Driver);
}

/**
 * @brief 作业槽与锁的状态打包（调试用）
 * @return bit0-1=userJob->lock  bit2-3=sysJob->lock  bit4=jobs->accept
 * @note  `lock` 取值：1=LOCK 2=UNLOCK
 */
uint8_t NvM_PortDbgJobs(void)
{
	const Fee_RunTimeType *rt = Fee_Driver.runtime;
	uint8_t v = 0u;

	v = (uint8_t)((uint8_t)rt->jobs->userJob->lock & 0x03u);
	v |= (uint8_t)(((uint8_t)rt->jobs->sysJob->lock & 0x03u) << 2);
	v |= (uint8_t)(((uint8_t)rt->jobs->sysJob->op & 0x07u) << 4);

	return v;
}

