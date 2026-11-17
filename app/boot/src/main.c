/**
 * @file    main.c
 * @brief   Boot：选槽 → 校验 → 跳转（A/B 分区的启动管理器）
 *
 * @details @section BOOT_WHAT 它做什么、不做什么
 *          | 做 | 不做 |
 *          |----|------|
 *          | 读两个槽的 meta，判定活动槽 | 响应 UDS（刷写在 app 里做） |
 *          | 校验镜像 CRC32 | 初始化 CAN / 收发报文 |
 *          | 跳转前把 TESTING 的尝试次数 +1，超限判 INVALID（回滚） | 处理故障码、网络管理 |
 *          | 镜像全坏时停住并在串口报警 | 擦除非活动槽 |
 *
 *          之所以**不带刷写能力**：A/B 的核心价值是"升级只写非活动槽"，
 *          活动槽永远完好，因此不存在"刷一半变砖"的场景 ——
 *          刷写完全可以放在 app 里做，而且升级期间车上的功能不受影响。
 *          代价是两个槽都坏时只能靠 J-Link 救，这个概率来自"两个槽同时
 *          遭遇位翻转"，在 A/B 结构下极低。
 *
 *          @section BOOT_FLOW 上电流程
 *          @code
 *          Platform_Init()          时钟 + 串口
 *          BootMeta_Init()          读两槽 meta（主备择优）
 *          slot = GetActiveSlot()   rollingCounter 大的、且 state 不是 EMPTY/INVALID
 *          CheckImage(slot)         向量表 + CRC32
 *            ├─ 失败 → 换另一个槽再试
 *            └─ 都失败 → 停住报警
 *          PrepareJump(slot)        TESTING 时尝试次数 +1，超 3 次判 INVALID
 *          JumpToApp(base)          不返回
 *          @endcode
 *
 *          @section BOOT_FIRST 首次烧写（两个槽都没有 meta）
 *          J-Link 只烧 boot + app 两个 ELF 时，槽尾 meta 是 0xFF，两个槽都
 *          "无效"。此时走兜底路径：看向量表像不像话（SP 落在 SRAM、
 *          PC 落在槽内），像就直接跳。app 起来后会调 `BootMeta_Register()`
 *          补写 meta，从此进入正规流程。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：A/B 选槽 + 校验 + 跳转 |
 */

#include "platform_cvm0146.h"
#include "boot_meta.h"
#include "boot_flash_map.h"
#include "Crc.h"

#include "NvM.h"        /* boot 也带存储栈：编程会话下读 VIN 用 */
#include "NvM_Cfg.h"    /* NVM_CFG_ID_VIN / NVM_CFG_BLK_VIN_SIZE */

/* D1 第二步：刷写协议栈（无镜像 / 有刷写请求时停在 UDS，不跳 app） */
#include "Port.h"       /* Port_Init：引脚 MUX（CAN/STB） */
#include "Dio.h"        /* Dio_ReadChannel：回读收发器 STB 实际电平 */
#include "Dio_Cfg.h"    /* DIO_CHANNEL_CAN0_STB */
#include "Can.h"
#include "Can_Cfg.h"
#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "CanTp.h"
#include "CanTp_Cfg.h"
#include "PduR.h"
#include "PduR_Cfg.h"
#include "Dcm.h"
#include "Dcm_Cfg.h"

#include <string.h>     /* memset */

/* ============================ [ 配置表符号 ] ============================ */

/**
 * @brief 各模块配置表的外部声明
 *
 * @note  这些符号由 boot 自己的 `config/*_Cfg.c` 定义（不是 app 的那份）。
 *        它们**没有**在公共头里声明 —— as-master 的做法是让 EcuM 的
 *        驱动表直接引用，走的是"配置层知道配置层"的路子。
 *        boot 没有 EcuM，所以在这里显式声明，顺便把"boot 用哪份配置"写明白。
 */
extern const Can_ConfigType Can_Config;
extern const CanIf_ConfigType CanIf_Config;
extern const CanTp_ConfigType CanTp_Config;
extern const PduR_ConfigType PduR_Config;
extern const Dcm_ConfigType Dcm_Config;

/* ============================ [ 内部 ] ============================ */

/**
 * @brief 调试开关：强制停在 UDS 模式（不跳 app）
 *
 * @details 正常路径只在"没有可启动镜像"时进 UDS。但验证刷写链路时，
 *          app 通常是好的 —— 要去掉它才能触发，而擦除 app 需要
 *          J-Link 的 FLM 配置（`flash.py` 走 CSpyBat，命令行直连做不到）。
 *
 *          所以给一个编译期开关：`build.bat --app=Boot` 前设环境变量
 *          `BOOT_FORCE_UDS=1`（由 SConscript 转成 `-DBOOT_FORCE_UDS=1`）。
 *          **验证完必须去掉这个环境变量**，否则量产固件会永远停在 boot。
 */
#ifndef BOOT_FORCE_UDS
#define BOOT_FORCE_UDS 0
#endif

/**
 * @brief bring-up 开关：进刷写模式时主动发 8 帧自检（默认开）
 *
 * @details @section BOOT_PROBE_WHY 为什么需要主动发帧
 *          "Kvaser 发 0x7E0 → boot 一声不响"这一条现象，软件层能查的
 *          都已经查完了（`MCR/CTRL1/IMASK1/NVIC` 与 app 逐位相同、`ECR=0`）。
 *          剩下两种可能**修法完全相反**，必须先用一次主动发送把它们分开：
 *
 *          | 探针结果 | 结论 | 方向 |
 *          |----------|------|------|
 *          | `TEC` 涨 / `FLTCONF` 变 1 | 帧没被 ACK，收发器没真正上总线 | 硬件：STB 电平、EN、供电、线束 |
 *          | `TEC=0` 且 `IFLAG1` bit4 置起 | 发送链路完全正常 | 软件：RX 引脚 / 邮箱 / 对端 |
 *
 *          @warning 定位完就把它置 0：正常刷写时它会在总线上插 8 帧
 *          `0xA0..0xA7` 的 0x7E8，上位机会把它们当成诊断响应。
 */
#ifndef BOOT_CAN_PROBE
#define BOOT_CAN_PROBE 0
#endif

/**
 * @brief 存储自检的等待上限（ms）
 *
 * @details 与 app 侧 `STORAGE_TIMEOUT_MS` 同量级。为什么需要这么长：
 *          `NvM_Init` 里 FEE 要做扇区扫描，**新片/掉电恢复时**要擦扇区
 *          并重写扇区头，实测 app 侧首次上电这一步要几百 ms。
 *          超时不等于失败 —— 只表示这次没等到，启动照常继续。
 */
#define BOOT_NVM_TIMEOUT_MS     (2000u)

/**
 * @brief 等到存储栈空闲（`NvM_Init` / 读请求完成）
 * @param[in] timeoutMs 超时（ms）
 * @retval true  已空闲
 * @retval false 超时
 *
 * @warning **`NvM_Init()` 之后必须等这一步，不能直接 `NvM_ReadBlock`。**
 *          这是本次集成踩到的坑：`NvM_Init` 只是把 FEE 的扇区扫描排进队列，
 *          队列还没跑完时发读请求，会拿到 `NVM_REQ_NOT_OK`（rc=1）——
 *          看起来像"boot 读不了 DFlash"，实际是初始化没完成。
 *          app 侧一直是 `NvM_Init` → 等 idle → `NvM_ReadAll` 才没暴露这个问题。
 */
static bool Boot_NvmWaitIdle(uint32_t timeoutMs)
{
	uint32_t t0 = Platform_NowMs();
	MemIf_StatusType st;

	for (;;) {
		st = NvM_GetStatus();
		if (st == MEMIF_IDLE) {
			return true;
		}

		NvM_MainFunction();

		if ((uint32_t)(Platform_NowMs() - t0) >= timeoutMs) {
			return false;
		}
	}
}

/**
 * @brief 读一个 NvM 块并等结果（带超时）
 * @param[in]  id  块 id
 * @param[out] dst 目标缓冲（长度必须等于该块的配置长度）
 * @return `NVM_REQ_*`；超时返回 `NVM_REQ_PENDING`
 *
 * @note  `NvM_ReadBlock` 只是入队，真实读由 `NvM_MainFunction` 推进。
 *        这里自旋等待 —— boot 是单线程启动路径，没有别的活要干。
 */
static NvM_RequestResultType Boot_NvmRead(NvM_BlockIdType id, void *dst)
{
	NvM_RequestResultType st = NVM_REQ_PENDING;
	uint32_t t0;

	if (NvM_ReadBlock(id, dst) != E_OK) {
		/* 入队就被拒 —— 打印下层状态，否则只剩一个 rc=1 什么也看不出 */
		Platform_Printf("[boot] nvm: enqueue FAIL id=%u fee=%u nvm=%u jobs=0x%02x\n",
		                (unsigned)id,
		                (unsigned)NvM_PortDbgFeeState(),
		                (unsigned)NvM_PortDbgNvmState(),
		                (unsigned)NvM_PortDbgJobs());
		return NVM_REQ_NOT_OK;
	}

	t0 = Platform_NowMs();
	while ((Platform_NowMs() - t0) < BOOT_NVM_TIMEOUT_MS) {
		NvM_MainFunction();
		if ((NvM_GetErrorStatus(id, &st) == E_OK) && (st != NVM_REQ_PENDING)) {
			break;
		}
	}

	return st;
}

/**
 * @brief 存储栈自检：初始化 NvM，再读两个块验证 DFlash 通路
 *
 * @details boot 集成 NvM 的目的（D1 决策）：编程会话下诊断仪可能要读
 *          VIN（`22 F1 90`），而 app 不在时只有 boot 能回答。
 *
 *          自检读两个块，含义完全不同：
 *
 *          | 块 | 谁写 | 预期结果 | 失败意味着 |
 *          |---|---|---|---|
 *          | BOOTCNT | app 每次启动写 | `NVM_REQ_OK` | **DFlash 通路断了** |
 *          | VIN | 诊断仪 `2E F1 90` | OK 或 NOT_OK 都正常 | — |
 *
 * @warning 第一版只读 VIN，实测返回 `NVM_REQ_NOT_OK`，差点被当成"boot 读不了
 *          DFlash"。实际原因是 `NvM_MapBlockState()` 把 `NVM_PORT_BLK_UNINIT`
 *          （从未写过）映射成 NOT_OK —— VIN 从来没被 `2E` 写过，是"未配置"
 *          不是"故障"。**验证通路要用一定有数据的块**，这就是 BOOTCNT 存在的意义。
 *
 * @warning **失败绝不阻止启动**。存储坏了仍然要能刷写、能跳 app ——
 *          否则一块 DFlash 故障会让 ECU 变砖，那比读不到 VIN 严重得多。
 */
static void Boot_StorageSelfTest(void)
{
	/* ⚠ 缓冲必须按 `NVM_CFG_BYTES()` 对齐后的大小开，不能直接用块的数据长度。
	 *
	 * 引擎的读路径最后一步是
	 *   `memcpy(userBuff, cpyBuff, readJob->datasize)`  （nvm_statemachine.c:117）
	 * 而 `datasize` 是 **FEE 块长对齐后**的值：BOOTCNT 8 字节数据 → FEE 侧 9 字节
	 * （数据 + CRC8）→ `NVM_CFG_BYTES(8)` = 16。给 8 字节的栈数组会被多写 8 字节。
	 * 第一版就是这么写的，栈上恰好有余量才没崩 —— 属于"看起来能跑"的未定义行为。
	 */
	uint8_t bootCnt[NVM_CFG_BYTES(NVM_CFG_BLK_BOOTCNT_SIZE)];
	uint8_t vin[NVM_CFG_BYTES(NVM_CFG_BLK_VIN_SIZE)];
	NvM_RequestResultType stCnt;
	NvM_RequestResultType stVin;
	uint8_t i;

	NvM_Init(NULL);

	/* 等 FEE 扇区扫描跑完 —— 少了这一步，下面的读请求会拿到 NOT_OK */
	if (!Boot_NvmWaitIdle(BOOT_NVM_TIMEOUT_MS)) {
		Platform_Puts("[boot] nvm: init TIMEOUT, skip storage check\n");
		return;
	}

	/* ---- ⓪ 先把全部块读进 RAM（与 app 侧的启动路径一致）----
	 *
	 * 为什么 boot 也要 ReadAll，而不是直接 ReadBlock 一个块：
	 * 实测直接 ReadBlock 会拿到 NOT_OK —— 块状态在"读完一次"之前是
	 * NVM_PORT_BLK_UNINIT，而 NvM_MapBlockState 把 UNINIT 映射成 NOT_OK。
	 * ReadAll 才是把"每个块都读到 RAM"这件事做完的那一步。
	 */
	NvM_ReadAll();
	if (!Boot_NvmWaitIdle(BOOT_NVM_TIMEOUT_MS)) {
		Platform_Printf("[boot] nvm: ReadAll TIMEOUT fee=%u nvm=%u jobs=0x%02x\n",
		                (unsigned)NvM_PortDbgFeeState(),
		                (unsigned)NvM_PortDbgNvmState(),
		                (unsigned)NvM_PortDbgJobs());
		return;
	}

	/* ---- ① BOOTCNT：app 每次启动写，一定有数据 → 验证 DFlash 通路 ---- */
	(void)memset(bootCnt, 0, sizeof(bootCnt));
	stCnt = Boot_NvmRead((NvM_BlockIdType)NVM_CFG_ID_BOOTCNT, bootCnt);

	if (stCnt == NVM_REQ_OK) {
		/* 块格式（见 app 侧 Storage_InitData）：[0..3] 小端计数，[4..7] magic。
		 * 字节序是**小端** —— 与 app 的 Storage_GetU32 一致，别按大端解析。
		 * magic 不对说明这辆车从没写过这个块（新片），不是故障。 */
		Platform_Printf("[boot] nvm: DFlash ok, bootCnt = %u\n",
		                (unsigned)((uint32_t)bootCnt[0] |
		                           ((uint32_t)bootCnt[1] << 8) |
		                           ((uint32_t)bootCnt[2] << 16) |
		                           ((uint32_t)bootCnt[3] << 24)));
	} else {
		Platform_Printf("[boot] nvm: DFlash FAIL rc=%u fee=%u nvm=%u rjob=%u jr=%u jobs=0x%02x\n",
		                (unsigned)stCnt,
		                (unsigned)NvM_PortDbgFeeState(),
		                (unsigned)NvM_PortDbgNvmState(),
		                (unsigned)NvM_PortDbgReadJob(),
		                (unsigned)NvM_PortDbgJobResult(),
		                (unsigned)NvM_PortDbgJobs());
	}

	/* ---- ② VIN：可能从未被写过，NOT_OK 属正常（未配置） ---- */
	(void)memset(vin, 0, sizeof(vin));
	stVin = Boot_NvmRead((NvM_BlockIdType)NVM_CFG_ID_VIN, vin);

	if (stVin == NVM_REQ_OK) {
		Platform_Puts("[boot] nvm: VIN = ");
		/* 只打有效载荷 17 字节，不含对齐 padding */
		for (i = 0u; i < (uint8_t)NVM_CFG_BLK_VIN_SIZE; i++) {
			Platform_PutChar((vin[i] != 0u) ? (char)vin[i] : '.');
		}
		Platform_Puts("\n");
	} else {
		/* UNINIT 也走这里：不是故障，只是这辆车还没写过 VIN */
		Platform_Printf("[boot] nvm: VIN not programmed (rc=%u)\n",
		                (unsigned)stVin);
	}
}

/**
 * @brief 打印镜像校验的中间量（排查 CRC 不一致时用）
 * @param[in] slot 槽索引
 * @note  正式版可以删掉，但它只占几十字节，留着方便现场定位
 *        "boot 说 CRC 错、但工具算出来是对的"这类问题。
 */
static void Boot_DebugImage(uint8_t slot)
{
	const Boot_SlotInfoType *info = BootMeta_GetSlot(slot);
	uint32_t base;
	uint32_t sp;
	uint32_t pc;
	uint32_t crc;

	if ((info == NULL) || (info->metaValid == 0u)) {
		return;
	}

	base = BOOT_SLOT_BASE(slot);
	Platform_FlashRead(base, &sp, 4u);
	Platform_FlashRead(base + 4u, &pc, 4u);
	crc = Crc_CalculateCRC32((const uint8_t *)base, info->meta.imageSize,
	                         0xFFFFFFFFu, TRUE);

	Platform_Printf("[boot] dbg slot %c: sp=%08X pc=%08X size=%u crc=%08X expect=%08X\n",
	                (slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B',
	                (unsigned)sp, (unsigned)pc,
	                (unsigned)info->meta.imageSize,
	                (unsigned)crc, (unsigned)info->meta.imageCrc);
}

/**
 * @brief 停住：镜像全坏且刷写栈也起不来时的最终状态
 *
 * @details 不跳转、不复位，就地打一行提示然后死循环。
 *          **故意不自动复位** —— 复位后会重复同样的失败流程，
 *          串口日志被刷屏反而看不清第一次的原因。
 *
 * @note   正常路径**不走这里**：没有可启动镜像时进 `Boot_UdsLoop()` 等刷写。
 *          只有连 CAN 都起不来（硬件故障）才落到这个死循环。
 */
static void Boot_Halt(const char *reason)
{
	Platform_Printf("\n[boot] HALT: %s\n", reason);
	Platform_Puts("[boot] no bootable image. Flash boot + app via J-Link:\n");
	Platform_Puts("       python tools/flash.py --boot\n");

	for (;;) {
		__asm volatile ("nop");
	}
}

/* ============================ [ UDS 刷写模式（D1 第二步） ] ============================ */

/**
 * @brief App 请求刷写后，多久没有诊断仪进编程会话就放弃（ms）
 *
 * @details 30000 的依据：诊断仪点"开始刷写"到发出 `10 02` 通常 < 3 s；
 *          30 s 足够覆盖"连错通道、重连、重选文件"这类人为操作，
 *          又不至于让车停在 boot 太久被用户当成故障。
 *
 * @note 一旦进了编程会话就不再计时（见 `Boot_UdsLoop` 的 `engaged`）。
 */
#define BOOT_FLASH_IDLE_TIMEOUT_MS      (30000u)

/**
 * @brief 刷写模式初始化：自下而上拉起 CAN 协议栈
 * @retval E_OK     就绪
 * @retval E_NOT_OK CAN 控制器起不来（硬件故障）
 *
 * @details 初始化顺序与 app 的 EcuM 表一致，只是少了 CanSM/ComM 那几层
 *          （boot 不做网络管理）：
 *          @code
 *          Can_Init      邮箱 + 滤波器 + 中断
 *          CanIf_Init    所有控制器 PDU 模式置 OFFLINE
 *          CanTp_Init / PduR_Init / Dcm_Init
 *          CanIf_SetControllerMode(CAN0, STARTED)   → Can_SetControllerMode
 *          CanIf_SetPduMode(CAN0, ONLINE)           **必须**，否则发送恒失败
 *          @endcode
 *
 * @warning `SetPduMode(ONLINE)` 不能漏。漏了的表现是"收得到、发不出去"：
 *          CanIf 在 OFFLINE 下直接丢 `CanIf_Transmit()`，且不报错 ——
 *          诊断仪看到的是 0x7E8 一声不响，只能靠 P2 超时退出。
 */
static Std_ReturnType Boot_UdsInit(void)
{
	/**
	 * @warning **`Platform_InitTick()` 必须调，否则 Dcm 永远不应答。**
	 *
	 *          这是 D1 第二步最后一个"什么都对但没有响应"的原因：
	 *          `Platform_NowMs()` 依赖 SysTick 中断累加 `s_ms`，
	 *          而 tick 初始化在 app 里是由 EcuM 调的 —— boot 没有 EcuM，
	 *          于是 `s_ms` 恒为 0，`Boot_UdsLoop()` 里的
	 *          @code
	 *          if ((Platform_NowMs() - next) >= DCM_MAIN_FUNCTION_PERIOD)
	 *          @endcode
	 *          条件永远不成立 → `CanTp_MainFunction()` / `Dcm_MainFunction()`
	 *          **一次都没执行过**。
	 *
	 *          现象极具误导性：CAN 收发硬件全好（主动发帧上位机收得到、
	 *          RX 邮箱 `CS.CODE` 能看到 FULL），只是诊断仪发什么都是"石沉大海"，
	 *          连 NRC 都没有 —— 因为报文进了 CanTp 的缓冲，却没人跑状态机。
	 */
	Platform_InitTick();

	/**
	 * @warning **`Port_Init()` 必须先调，且不能省。**
	 *          它把 CAN0_RX/TX（PE4/PE5）、STB（PC1）等引脚配成复用功能。
	 *          漏了它的表现是"CAN 初始化全部返回成功、总线上一个字都没有" ——
	 *          引脚还是普通 GPIO，收发器的 TX 根本没接到 CAN 控制器上。
	 *          这个错误没有任何报错，只能靠示波器或"发不出去"发现。
	 */
	Port_Init(NULL);        /* NULL = 用本工程的 Port_Config（与 app 同一份） */

	Can_Init(&Can_Config);
	CanIf_Init(&CanIf_Config);
	CanTp_Init(&CanTp_Config);
	PduR_Init(&PduR_Config);
	Dcm_Init(&Dcm_Config);

	if (CanIf_SetControllerMode(CANIF_CHL_CAN0, CAN_CS_STARTED) != E_OK) {
		return E_NOT_OK;
	}

	/**
	 * @warning **`CanIf_SetTrcvMode(NORMAL)` 不能省，它才是拉低 STB 的那一步。**
	 *
	 *          这是本次集成踩得最久的一个坑：以为 `SetControllerMode(STARTED)`
	 *          就把 CAN 拉起来了，实际它只管控制器（清 HALT、配邮箱），
	 *          **收发器仍然停在 Standby**（STB 引脚为高，收发器不把总线差分
	 *          信号转给控制器）。
	 *
	 *          症状极具迷惑性：`Can_Init` 全部成功、`MCR` 的 MDIS/HALT 都是 0、
	 *          `IMASK1` 的邮箱中断已使能、`ECR=0` 无错误 —— 但 `IFLAG1=0`，
	 *          总线上发多少帧都收不到。
	 *
	 *          app 里这一步由 **CanSM** 在 FULLCOM 时调
	 *          （见 `main.c` 的初始化注释：`CanIf_SetTrcvMode(ch, NORMAL) STB 拉低`）。
	 *          boot 没有 CanSM，必须自己补。
	 */
	if (CanIf_SetTrcvMode(CANIF_CHL_CAN0, CANTRCV_TRCVMODE_NORMAL) != E_OK) {
		return E_NOT_OK;
	}

	if (CanIf_SetPduMode(CANIF_CHL_CAN0, CANIF_ONLINE) != E_OK) {
		return E_NOT_OK;
	}

	return E_OK;
}

/**
 * @brief 刷写主循环：不返回（只能靠 0x11 复位或断电退出）
 *
 * @note  为什么是 10 ms 固定节拍而不是自由循环：
 *        `CanTp` / `Dcm` 的定时器是"每次 MainFunction 递减一次"，
 *        配置里的 N_Bs / N_Cr / S3 都是按 `*_MAIN_FUNCTION_PERIOD`
 *        折成 tick 的。扔进自由循环的话，100 tick 的 N_Bs 会在几百微秒内
 *        耗尽 —— **单帧全通、多帧一律失败**（单帧不依赖定时器）。
 */
static uint8_t Boot_UdsLoop(uint32_t idleTimeoutMs)
{
	uint32_t next = Platform_NowMs();
	uint32_t start = Platform_NowMs();
	uint8_t  engaged = 0u;   /* 诊断仪已进非默认会话 → 正在刷，不再超时 */
#if BOOT_CAN_PROBE
	uint32_t nextSt = Platform_NowMs();
	uint32_t stCnt  = 0u;
#endif

	Platform_Puts("[boot] UDS flash mode: 0x7E0 -> 0x7E8 @ 500 kbps\n");
	Platform_Puts("[boot] sequence: 10 02 | 27 01/02 | 31 01 FF00 | 34 | 36 | 37 | 11 01\n");

	/* 寄存器快照：CAN 起不来的现场只有这里能看出来
	 * （MCR 的 MDIS、CTRL0 的 HALT、ECR 的错误计数） */
	CanAc_DbgDump(0u);

#if BOOT_CAN_PROBE
	/**
	 * @brief 主动发帧自检：只在能进刷写模式时执行，约 30 ms
	 *
	 * @note  为什么放在这里而不是 `Boot_UdsInit()` 里：Init 失败会走
	 *        `Boot_Halt()`，而探针本身要打印的正是"为什么失败"，
	 *        放在 Init 内部会被那条错误路径跳过。
	 *
	 *        收发器 STB 的实际电平也一起打出来 —— `PDOR` 读到 0
	 *        只说明引脚为低，**不说明它被驱动为低**（输入模式下
	 *        `PDOR` 反映的是外部电平）。所以同时看 `Dio_ReadChannel`。
	 */
	Platform_Printf("[boot] STB(CAN0) = %u（0=低=Normal，1=高=Standby）\n",
	                (unsigned)Dio_ReadChannel(DIO_CHANNEL_CAN0_STB));
	CanAc_DbgProbe(0u);
#endif

	for (;;) {
		Dcm_SesCtrlType sesNow = DCM_DEFAULT_SESSION;

		if ((uint32_t)(Platform_NowMs() - next) >= DCM_MAIN_FUNCTION_PERIOD) {
			next = Platform_NowMs();
			CanTp_MainFunction();
			Dcm_MainFunction();
		}

		/* ---- 空闲超时回退 ----
		 *
		 * 为什么需要：进入刷写模式有两类原因，性质完全不同 ——
		 *
		 * | 原因 | 有镜像可跑吗 | 超时退出安全吗 |
		 * |------|--------------|----------------|
		 * | App 请求（`10 02`） | 有，而且刚确认过能跑 | **必须**：诊断仪放弃/掉线时不能把车锁死在 boot |
		 * | 没有有效镜像 | 没有 | 不能：退出也没东西可跳 |
		 *
		 * 场景：诊断仪发了 `10 02`，App 写完标志复位，然后工具崩了 / 线掉了 /
		 * 用户关钥匙。下次上电车就停在 boot —— 现场表现是"整车不工作"，
		 * 而且没有任何故障码。所以这里必须有退路。
		 *
		 * `engaged` 的作用：一旦诊断仪进了编程会话就**永不再超时**，否则
		 * 刷到一半（比如正在等人点确认）会被踢出去，比不刷更危险。 */
		if (idleTimeoutMs != 0u) {
			if ((Dcm_GetSesCtrlType(&sesNow) == E_OK) &&
			    (sesNow != DCM_DEFAULT_SESSION)) {
				engaged = 1u;
			}

			if ((0u == engaged) &&
			    ((uint32_t)(Platform_NowMs() - start) >= idleTimeoutMs)) {
				Platform_Puts("[boot] no tester, leaving flash mode\n");
				return 1u;
			}
		}
#if BOOT_CAN_PROBE
		/* 接收侧状态行：每秒一次，最多 12 行。
		 * 与中断里的计数对照，判断"帧进了邮箱但没人取"还是"中断根本没进"。 */
		if ((stCnt < 12u) && ((uint32_t)(Platform_NowMs() - nextSt) >= 1000u)) {
			nextSt = Platform_NowMs();
			stCnt++;
			CanAc_DbgStatus(0u);
		}
#endif
		/* 邮箱收发全在中断里（`CanAc_MbIsr`），主循环不需要轮询 CAN */
	}
}

/**
 * @brief 进入刷写模式（打印原因 → 起协议栈 → 死循环）
 * @param[in] reason 为什么要停在 boot（打印出来便于现场判断）
 *
 * @note  CAN 起不来时退化成 `Boot_Halt()` —— 至少串口还能告诉人"是硬件问题"。
 */
static uint8_t Boot_EnterUds(const char *reason, uint32_t idleTimeoutMs)
{
	Platform_Printf("\n[boot] %s\n", reason);
	Platform_Puts("[boot] entering UDS flash mode ...\n");

	if (Boot_UdsInit() != E_OK) {
		Boot_Halt("CAN controller failed to start");
	}

	return Boot_UdsLoop(idleTimeoutMs);
}

/**
 * @brief 没有 meta 时的兜底判断：这个地址上像不像一个应用镜像
 *
 * @details 只看向量表头（不做 CRC —— 没有 meta 就没有期望的 CRC 值）：
 *          1. 初始 MSP 落在 SRAM 区间且 8 字节对齐；
 *          2. Reset_Handler 落在本槽的可执行范围内（Thumb 位允许为 1）。
 *
 * @param[in] base 槽基址
 * @retval 1 像
 * @retval 0 不像
 */
static uint8_t Boot_LooksLikeImage(uint32_t base)
{
	uint32_t sp = *(volatile uint32_t *)(base);
	uint32_t pc = *(volatile uint32_t *)(base + 4u);
	uint32_t entry;

	/* SP：SRAM_L(0x1FFF0000) ~ StackTop(0x2000F000)，且 8 字节对齐 */
	if ((sp < 0x1FFF0000u) || (sp > 0x2000F000u) || ((sp & 0x7u) != 0u)) {
		return 0u;
	}

	/* PC：Thumb 模式下最低位是 1，比对地址前先清掉 */
	entry = pc & ~1u;
	if ((entry < base) || (entry >= (base + BOOT_SLOT_IMAGE_MAX))) {
		return 0u;
	}

	return 1u;
}

/**
 * @brief 打印一个槽的关键信息（一行）
 * @param[in] slot 槽索引
 */
static void Boot_PrintSlot(uint8_t slot)
{
	const Boot_SlotInfoType *info = BootMeta_GetSlot(slot);
	static const char *const stateName[] = { "EMPTY", "TESTING", "CONFIRMED", "INVALID" };

	if (info == NULL) {
		return;
	}

	if (info->metaValid == 0u) {
		Platform_Printf("  slot %c : 0x%06X  %-9s  (no meta)\n",
		                (slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B',
		                (unsigned)BOOT_SLOT_BASE(slot), "EMPTY");
		return;
	}

	Platform_Printf("  slot %c : 0x%06X  %-9s  rc=%-4u size=%-7u crc=%08X  v%u.%u.%u\n",
	                (slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B',
	                (unsigned)BOOT_SLOT_BASE(slot),
	                stateName[info->meta.state & 0x3u],
	                (unsigned)info->meta.rollingCounter,
	                (unsigned)info->meta.imageSize,
	                (unsigned)info->meta.imageCrc,
	                (unsigned)info->meta.versionMajor,
	                (unsigned)info->meta.versionMinor,
	                (unsigned)info->meta.versionPatch);
}

/* ============================ [ main ] ============================ */

int main(void)
{
	uint8_t slot;
	uint8_t other;
	uint8_t chosen = BOOT_NO_ACTIVE_SLOT;

	Platform_Init();

	Platform_Puts("\n");
	Platform_Puts("========================================\n");
	Platform_Puts("  AS / CVM0146  boot  (A/B)\n");
	Platform_Puts("  build : " __DATE__ " " __TIME__ "\n");
	Platform_Puts("  map   : boot 128K | A 448K | B 448K\n");
	Platform_Puts("========================================\n");

	BootMeta_Init();

	Boot_PrintSlot(BOOT_SLOT_INDEX_A);
	Boot_PrintSlot(BOOT_SLOT_INDEX_B);

	/* 存储自检（DFlash / NvM）：为"编程会话下读 VIN"预留通路。
	 * 失败只打印，不影响下面的选槽与跳转 —— 存储坏了也要能刷能跳。 */
	Boot_StorageSelfTest();

#if BOOT_FORCE_UDS
	/* 调试：不跳 app，直接进刷写模式（验证 UDS 链路用） */
	(void)Boot_EnterUds("BOOT_FORCE_UDS=1 (debug build, not for production)", 0u);
#endif

	/* ---- 第 0 步：App 请求的刷写交接 ----
	 *
	 * 诊断仪发 `10 02`（编程会话）时，App 写 `reserved[0] = REQ_FLASH` 再复位；
	 * 这里读到就停在 UDS，而不是跳 App。
	 *
	 * 放在选槽之前：此时刚读完 meta，不需要算镜像 CRC（几十万字节、十几毫秒）；
	 * 而"要不要进 UDS"与"哪个槽的镜像有效"无关 —— 刷写就是要覆盖它。
	 *
	 * **清除必须在进 UDS 之前**：否则刷完复位又读到标志、又进 UDS，App 永远
	 * 起不来（现场表现是"升级成功但一直停在 boot"）。清除失败则正常启动 ——
	 * 宁可这次刷不了，也不能把板子变成只能刷机的砖。 */
	{
		uint8_t reqSlot = BootMeta_GetActiveSlot();

		if (reqSlot != BOOT_NO_ACTIVE_SLOT) {
			const Boot_SlotInfoType *reqInfo = BootMeta_GetSlot(reqSlot);

			if ((reqInfo != NULL) && (reqInfo->metaValid != 0u) &&
			    (reqInfo->meta.reserved[0] == (uint8_t)BOOT_META_REQ_FLASH)) {
				Boot_MetaType reqMeta = reqInfo->meta;

				reqMeta.reserved[0] = (uint8_t)BOOT_META_REQ_NONE;

				if (BootMeta_Write(reqSlot, &reqMeta) == E_OK) {
					/* 30 s：够诊断仪连上、进编程会话、开始擦除；
					 * 超时说明"只是发了 10 02 然后什么都没做"，
					 * 这时必须回退到正常启动，否则整车无法工作。 */
					if (Boot_EnterUds("flash requested by app (10 02 programming session)",
					                  BOOT_FLASH_IDLE_TIMEOUT_MS) == 0u) {
						Boot_Halt("flash mode returned without timeout");
					}
					Platform_Puts("[boot] resume normal boot after idle timeout\n");
				} else {
					Platform_Puts("[boot] flash request found but cannot clear; "
					              "booting normally\n");
				}
			}
		}
	}

	/* ---- 第一步：按 meta 选活动槽 ---- */
	slot = BootMeta_GetActiveSlot();

	if (slot != BOOT_NO_ACTIVE_SLOT) {
		Platform_Printf("[boot] active slot : %c (rolling counter)\n",
		                (slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B');

		Boot_DebugImage(slot);

		/* ---- 第二步：校验镜像，坏了就换另一个槽 ---- */
		if (BootMeta_CheckImage(slot) == E_OK) {
			chosen = slot;
		} else if (BootMeta_DemoteToTesting(slot) == E_OK) {
			/* meta 完好但镜像对不上 —— 最常见的原因是"用 J-Link 重烧了 app，
			 * 但槽尾 meta 还是旧镜像的 CRC"。此时**不能直接判死**：
			 * 那会形成"烧完能跑一次、一复位就 HALT"的死锁，因为
			 * 唯一能修正 meta 的 app 根本没机会启动。
			 *
			 * 降级成 TESTING 再跳，两种结局都安全：
			 *   - app 起来了 → 它按当前镜像重写 meta；
			 *   - app 起不来 → 复位后尝试次数累加，3 次后判 INVALID 并回滚。 */
			Platform_Printf("[boot] slot %c check failed, "
			                "boot anyway as TESTING (meta may be stale)\n",
			                (slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B');
			chosen = slot;
		} else {
			other = (slot == BOOT_SLOT_INDEX_A) ? BOOT_SLOT_INDEX_B : BOOT_SLOT_INDEX_A;
			Platform_Printf("[boot] slot %c image CRC failed, try slot %c\n",
			                (slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B',
			                (other == BOOT_SLOT_INDEX_A) ? 'A' : 'B');
			if (BootMeta_CheckImage(other) == E_OK) {
				chosen = other;
			} else if (Boot_LooksLikeImage(BOOT_SLOT_BASE(other)) != 0u) {
				/* 另一个槽也没有可用 meta，但向量表像话 —— 首次烧写路径 */
				chosen = other;
			}
		}
	} else {
		/* ---- 首次烧写：没有任何有效 meta，靠向量表兜底 ---- */
		Platform_Puts("[boot] no valid meta, fallback to vector table probe\n");

		if (Boot_LooksLikeImage(BOOT_SLOT_A_BASE) != 0u) {
			chosen = BOOT_SLOT_INDEX_A;
		} else if (Boot_LooksLikeImage(BOOT_SLOT_B_BASE) != 0u) {
			chosen = BOOT_SLOT_INDEX_B;
		}
	}

	if (chosen == BOOT_NO_ACTIVE_SLOT) {
		/* 没有可启动镜像 —— 这是 D1 第二步的核心场景：
		 * app 被擦掉了，boot 停在 UDS 等诊断仪刷写，而不是死等 J-Link。 */
		(void)Boot_EnterUds("no valid image in slot A or B, waiting for flash", 0u);
	}

	/* ---- 第三步：跳转前的尝试计数（回滚触发点） ---- */
	if (BootMeta_PrepareJump(chosen) != E_OK) {
		/* 该槽刚被判 INVALID（连续启动失败超限），换另一个 */
		other = (chosen == BOOT_SLOT_INDEX_A) ? BOOT_SLOT_INDEX_B : BOOT_SLOT_INDEX_A;
		Platform_Printf("[boot] slot %c exceeded boot attempts, rollback to slot %c\n",
		                (chosen == BOOT_SLOT_INDEX_A) ? 'A' : 'B',
		                (other == BOOT_SLOT_INDEX_A) ? 'A' : 'B');

		if (BootMeta_CheckImage(other) != E_OK) {
			/* 回滚目标也坏了 —— 同样进 UDS，让诊断仪能救回来 */
			(void)Boot_EnterUds("rollback target also invalid, waiting for flash", 0u);
		}
		chosen = other;
	}

	Platform_Printf("[boot] jump to slot %c  base=0x%06X  entry=0x%06X\n",
	                (chosen == BOOT_SLOT_INDEX_A) ? 'A' : 'B',
	                (unsigned)BOOT_SLOT_BASE(chosen),
	                (unsigned)(*(volatile uint32_t *)(BOOT_SLOT_BASE(chosen) + 4u) & ~1u));
	Platform_Puts("========================================\n");

	Platform_JumpToApp(BOOT_SLOT_BASE(chosen));

	/* `Platform_JumpToApp` 只在向量表明显非法时返回，走不到这里 */
	Boot_Halt("jump returned");
	return 0;
}
