/**
 * @file    storage_app.c
 * @brief   存储栈初始化（EcuM DriverInitOne/Two）与验收命令实现（M4）
 *
 * @details 从 `main.c` 的「存储（M4）」区整体迁出（M-Shell 命令迁移）。
 *          初始化函数由 EcuM 配置表调用（原型在 `EcuM_Cfg.h`），
 *          命令入口 `StorageCmd_*` 供 `cmd/nvm_cmd.c` 与旧 `!x` 分支共用。
 *
 * @note    输出仍用 `Platform_Printf/Puts`：初始化发生在 shell 就绪之前，
 *          此时控制台汇未绑定，走直写；绑定后自动进 TX 环（平台层的汇机制）。
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "platform_cvm0146.h"
#include "NvM.h"
#include "NvM_Cfg.h"
#include "Dem.h"
#include "Dem_Cfg.h"   /* Dem_SetBootSequence（启动序号） */

#include <stdbool.h>
#include <stdint.h>

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
 * @brief 打印所有块状态（`nvm dump` / 旧 `!d`）
 */
void StorageCmd_Dump(void)
{
	if (!s_storageReady) {
		Platform_Puts("[nvm] storage not ready\n");
		return;
	}
	Storage_Dump();
}

/**
 * @brief 脏块落盘（`nvm writeall` / 旧 `!c`）
 * @note 走脏块掩码，不是全写。
 */
void StorageCmd_WriteAll(void)
{
	if (!s_storageReady) {
		Platform_Puts("[nvm] storage not ready\n");
		return;
	}
	NvM_WriteAll();
	Platform_Puts("[nvm] WriteAll started (dirty blocks only)\n");
}

/**
 * @brief 改 RAM → 标脏 → WriteAll（`nvm touch` / 旧 `!w`）
 * @details 验证 AUTOSAR 的延迟落盘路径。
 */
void StorageCmd_Touch(void)
{
	uint8_t *ram = NULL;
	uint16_t len = 0u;

	if (!s_storageReady) {
		Platform_Puts("[nvm] storage not ready\n");
		return;
	}
	if (NvM_GetBlockDataPtrAndLength((NvM_BlockIdType)NVM_CFG_ID_CONFIG,
	                                 (void **)&ram, &len) != E_OK) {
		Platform_Puts("[nvm] config block unavailable\n");
		return;
	}
	ram[1]++;
	(void)NvM_SetRamBlockStatus((NvM_BlockIdType)NVM_CFG_ID_CONFIG, TRUE);
	NvM_WriteAll();
	Platform_Printf("[nvm] config[1]=%u marked dirty, WriteAll started\n",
	                (unsigned)ram[1]);
}

/**
 * @brief 连续写 400 次强制 GC（`nvm stress` / 旧 `!p`）
 */
void StorageCmd_Stress(void)
{
	if (!s_storageReady) {
		Platform_Puts("[nvm] storage not ready\n");
		return;
	}
	Storage_Stress();
}

/**
 * @brief 非法块 id（`nvm illegal` / 旧 `!x`）
 * @details 验证 DET 上报（应看到 `[det] mod=20 ...`）。
 */
void StorageCmd_Illegal(void)
{
	uint8_t tmp[8];

	if (!s_storageReady) {
		Platform_Puts("[nvm] storage not ready\n");
		return;
	}
	Platform_Printf("[nvm] illegal block id test: rc=%u\n",
	                (unsigned)NvM_ReadBlock((NvM_BlockIdType)(NVM_CFG_BLOCK_NUM + 5u),
	                                        tmp));
}

/**
 * @brief 存储栈是否就绪（供命令层判断）
 * @retval true  已初始化且启动计数写回成功
 */
bool Storage_IsReady(void)
{
	return s_storageReady;
}
