/**
 * @file    ecum_callout.c
 * @brief   EcuM 的项目集成层（所有 `EcuM_AL_*` + BSW 调度）
 *
 * @details @section ECUMAL_WHY 为什么这一层必须有、而且必须在应用侧
 *
 *          `EcuM.c` 是**标准状态机**：它只知道"现在该调 DriverInitZero、
 *          该进 RUN、该睡了"，但**不知道这个 ECU 具体要初始化什么、
 *          进 RUN 时该启动哪根总线**。这些是 `EcuM_AL_*` 系列的职责，
 *          AUTOSAR 明确把它们列为**集成代码**（integration code），
 *          不属于 EcuM 模块本身。
 *
 *          所以：
 *          - `infras/system/EcuM/` 只有标准状态机（可以直接对照规范）；
 *          - 本文件承载全部项目决策，换 ECU 时只改这里。
 *
 *          @section ECUMAL_CHAIN 进 RUN 的链路（标准三层）
 *
 *          @code
 *          EcuM_RequestRUN(user)
 *                ↓  EcuM_MainFunction 检测到请求
 *          EcuM_AL_EnterRUN()
 *                ↓
 *          ComM_RequestComMode(USER_APP, FULL_COMMUNICATION)
 *                ↓  ComM 仲裁后
 *          ┌─────┴──────┐
 *          ↓            ↓
 *      Nm_NetworkRequest   CanSM_RequestComMode
 *          ↓            ↓
 *      CanNm 发 NM 报文   CanIf 启动控制器 + PDU ONLINE
 *          ↓
 *      ComM_Nm_NetworkMode → Com_IpduGroupStart（信号报文开始发）
 *          @endcode
 *
 *          **应用/集成层只碰 ComM 一个接口**，不直接调 Nm、不直接调 CanIf ——
 *          这正是 ComM 存在的意义。之前 `!a` 直接调 `Nm_NetworkRequest`，
 *          那是 bring-up 期的旁路，不是标准用法。
 *
 *          @section ECUMAL_ALLOWED 为什么要显式 ComM_CommunicationAllowed
 *
 *          AUTOSAR 里这个调用属于 **BswM**（Basic Software Mode Manager）：
 *          BswM 根据模式规则决定"这个通道现在允不允许通信"。
 *          本工程没有 BswM，所以由集成层在进 RUN 时直接放行 ——
 *          语义上等价于"BswM 规则：RUN 模式下允许所有通道通信"。
 *
 *          不调用它的后果：ComM 停在 `NO_COM_REQUEST_PENDING` 不动，
 *          NM 不会启动，总线上永远没有 NM 和信号报文，而且**不报错**。
 *
 * @warning `EcuM_AL_EnterSLEEP()` 目前**不会真正降低功耗**。
 *          真正的休眠要切 MCU 低功耗模式（`Mcu_SetMode`）并配置唤醒源，
 *          本工程还没做。所以**不要拿当前版本的电流数据当结论**。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：三阶段初始化 + BSW 调度 + RUN/POST_RUN 经 ComM |
 */

#include "EcuM.h"
#include "EcuM_Externals.h"
#include "EcuM_Priv.h"
#include "EcuM_Cfg.h"

#include "ComM.h"
#include "ComM_Cfg.h"
#include "NvM.h"

#include "platform_cvm0146.h"

/**
 * @brief EcuM 配置表（定义在 `EcuM_Cfg.c`）
 * @note  `EcuM_Priv.h` 只定义类型、不声明这个符号；
 *        `EcuM.c` 里是各自 `extern` 的。这里同样需要自己声明。
 */
extern const EcuM_ConfigType EcuM_Config;

/* ============================ [ 唤醒源（项目自定义） ] ============================ */

/* 唤醒源位定义在 `EcuM_Cfg.h`（应用层也要用），这里只做使用。 */

/**
 * @brief 当前允许的唤醒源位图
 * @note  由 `EcuM_EnableWakeupSources()` 置位、`EcuM_EnableWakeupSources(0)` 清除。
 *        实际"允不允许"取决于硬件（端口中断有没有使能），
 *        这个位图只是软件侧的一致性记录，用于排查"是没配还是没触发"。
 */
static EcuM_WakeupSourceType s_wakeupEnabled = 0u;

/* ============================ [ 当前模式（供诊断查询） ] ============================ */

/**
 * @brief 记录集成层最后一次进入的模式
 *
 * @note  为什么不用 `EcuM_GetCurrentMode()`：**as-master 的 `EcuM.c`
 *        没有实现它**（`EcuM.h` 里声明了，但 .c 里没有定义，
 *        链接时才会发现）。它的状态存在 `EcuM.c` 内部的 `static EcuM_Contxt`，
 *        外部读不到。
 *
 *        与其给参考实现打补丁，不如在这里记一份 —— `EcuM_AL_EnterXxx`
 *        本来就是这个 ECU 唯一"知道自己在哪个模式"的地方，
 *        而且这份记录与 `EcuM.c` 的状态机**必然同步**（状态机只通过
 *        这三个回调告知外界）。
 */
static EcuM_ModeType s_ecuMMode = ECUM_MODE_OFF;

EcuM_ModeType EcuM_AL_GetMode(void)
{
	return s_ecuMMode;
}

/* ============================ [ 初始化：三个阶段 ] ============================ */

void EcuM_AL_SetProgrammableInterrupts(void)
{
	/* 本工程的 NVIC 优先级在 `IrqDrv_EnableIrq()` 时逐个设置，
	 * 没有"全局重排优先级"的需求。保留空实现是为了满足接口。 */
}

void EcuM_AL_DriverInitZero(void)
{
	uint16_t i;
	const EcuM_DriverInitItemType *item;

	for (i = 0u; i < EcuM_Config.numOfZero; i++) {
		item = &EcuM_Config.DriverInitListZero[i];
		item->InitFnc(item->config);
	}
}

void EcuM_AL_DriverInitOne(void)
{
	uint16_t i;
	const EcuM_DriverInitItemType *item;

	for (i = 0u; i < EcuM_Config.numOfOne; i++) {
		item = &EcuM_Config.DriverInitListOne[i];
		item->InitFnc(item->config);
	}
}

/**
 * @brief 阶段二：NvM 读回 + 启动计数 + Dem 绑定
 *
 * @note **这里刻意不做 `NvM_ReadAll()`。**
 *       as-master 的版本会在遍历列表前调用
 *       `EcuM_EnsureMemoryIdle(); NvM_ReadAll();`，但那个 `EnsureMemoryIdle`
 *       是 `do { MemoryService(); } while (MEMIF_IDLE != NvM_GetStatus());`
 *       —— 一旦 NvM 没初始化（`MEMIF_UNINIT`），这个循环**永远不退出**。
 *
 *       本工程的存储栈自己管这一套：`Storage_InitData()` 里有 5 s 超时、
 *       有耗时统计、失败时打印后返回而不是死等。把这套逻辑让给 EcuM 的
 *       通用 callout 反而丢掉了保护，所以读回动作留在存储模块自己身上。
 */
void EcuM_AL_DriverInitTwo(void)
{
	uint16_t i;
	const EcuM_DriverInitItemType *item;

	for (i = 0u; i < EcuM_Config.numOfTwo; i++) {
		item = &EcuM_Config.DriverInitListTwo[i];
		item->InitFnc(item->config);
	}
}

/* ============================ [ 主函数调度 ] ============================ */

/** @brief 只推进存储类主函数（供阻塞等待使用） */
void EcuM_MemoryService(void)
{
	uint16_t i;

	for (i = 0u; i < EcuM_Config.numOfMainMem; i++) {
		EcuM_Config.DriverMemMainList[i]();
	}
}

/**
 * @brief 阻塞直到存储栈空闲
 * @warning **调用前 NvM 必须已初始化。** 未初始化时
 *          `NvM_GetStatus()` 返回 `MEMIF_UNINIT`（不等于 `MEMIF_IDLE`），
 *          这里会死循环。本工程当前没有调用点（见 `EcuM_AL_DriverInitTwo`
 *          的说明），保留它是因为 `EcuM.h` 声明了这个接口，
 *          将来做"关机前写回所有块"时会用到。
 */
void EcuM_EnsureMemoryIdle(void)
{
	while (MEMIF_IDLE != NvM_GetStatus()) {
		EcuM_MemoryService();
	}
}

/** @brief 10 ms BSW 调度：按 `EcuM_DriverMainList` 的顺序跑一遍 */
void EcuM_BswService(void)
{
	uint16_t i;

	for (i = 0u; i < EcuM_Config.numOfMain; i++) {
		EcuM_Config.DriverMainList[i]();
	}
}

/** @brief 快速任务调度（本工程 numOfMainFast = 0，空转） */
void EcuM_BswServiceFast(void)
{
	uint16_t i;

	for (i = 0u; i < EcuM_Config.numOfMainFast; i++) {
		EcuM_Config.DriverMainFastList[i]();
	}

	EcuM_MemoryService();
}

/* ============================ [ 模式进入：RUN / POST_RUN / SLEEP ] ============================ */

/**
 * @brief 进入 RUN：请求通信 + 放行通道
 *
 * @details 顺序很重要：
 *          1. `ComM_RequestComMode(FULL)` —— 先把"我要通信"的意图落下；
 *          2. `ComM_CommunicationAllowed(TRUE)` —— 再放开闸门。
 *
 *          反过来也能工作（ComM 的 `NO_COM_REQUEST_PENDING` 状态会等这个标志），
 *          但先请求后放行更符合"用户提出需求、BswM 批准"的语义，
 *          也避免出现"已放行但没有请求"的一拍空转。
 */
void EcuM_AL_EnterRUN(void)
{
	(void)ComM_RequestComMode((ComM_UserHandleType)COMM_USER_APP,
	                          (ComM_ModeType)COMM_FULL_COMMUNICATION);
	ComM_CommunicationAllowed((NetworkHandleType)COMM_CHANNEL_CAN0, TRUE);

	s_ecuMMode = ECUM_MODE_RUN;
	Platform_Puts("  [ecum] RUN\n");
}

/**
 * @brief 进入 POST_RUN：撤销通信请求
 *
 * @note  ComM → Nm_NetworkRelease → CanNm 进 ReadySleep，
 *        发完 RepeatMessage 后停发；2 s 后 NM 进 PrepareBusSleep，
 *        ComM 收到通知后 `Com_IpduGroupStop` 停掉信号报文。
 *
 *        所以**这里不需要手动停 Com 分组** —— 那是 ComM 的职责。
 */
void EcuM_AL_EnterPOST_RUN(void)
{
	ComM_CommunicationAllowed((NetworkHandleType)COMM_CHANNEL_CAN0, FALSE);
	(void)ComM_RequestComMode((ComM_UserHandleType)COMM_USER_APP,
	                          (ComM_ModeType)COMM_NO_COMMUNICATION);

	s_ecuMMode = ECUM_MODE_POST_RUN;
	Platform_Puts("  [ecum] POST_RUN\n");
}

/**
 * @brief 进入 SLEEP
 *
 * @warning **当前不会真正进入低功耗。** 真正的休眠需要：
 *          1. `Mcu_SetMode(MCU_MODE_SLEEP)` 切时钟/停外设；
 *          2. 配置唤醒源（CAN 收发器 WAKE 引脚 → GPIO 中断）；
 *          3. 唤醒后走 `EcuM_CheckWakeup` → `ComM_EcuM_WakeUpIndication`
 *             → `Nm_PassiveStartUp` 这条标准链路。
 *
 *          这三件事都要硬件与时钟驱动配合，属于 M12 的范围。
 *          现在只打日志 —— **不要用当前版本测电流**。
 */
void EcuM_AL_EnterSLEEP(void)
{
	/**
	 * @details @section ECUMAL_SLEEP_ORDER 睡眠是"按顺序退"而不是"直接 WFI"
	 *
	 *          `EcuM_MainFunction()` 走到这里时，`bRequestRun` 与
	 *          `bRequestPostRun` 都已经是 FALSE，也就是说
	 *          `EcuM_AL_EnterPOST_RUN()` 早就跑过了 —— 它已经：
	 *          @code
	 *          ComM_CommunicationAllowed(FALSE)
	 *          ComM_RequestComMode(NO_COM)
	 *          @endcode
	 *
	 *          之后 ComM 会让 NM 释放网络、CanNm 走 ReadySleep →
	 *          PrepareBusSleep，最后 CanSM 把控制器停掉、收发器进 standby。
	 *          **这一整套是异步的，需要好几秒**（NmTimeout 2 s + WaitBusSleep 2 s）。
	 *
	 *          所以本函数**不在这里做 WFI**。理由：
	 *          1. 这时总线上可能还有报文没发完，立刻睡会把它们截断；
	 *          2. 真正的"可以睡了"信号是 `ComM_GetState() == COMM_NO_COM_NO_PENDING_REQUEST`
	 *             **并且** CanSM 报告控制器已停 —— 那是 2~5 s 之后的事；
	 *          3. 急着睡还有硬件风险：本平台的 CAN 模块低功耗态不可逆
	 *             （见 README「M11 的两个致命坑」②），必须确认它已经停稳。
	 *
	 *          因此这里只做两件事：记录状态 + 打日志。
	 *          **真正的 WFI 由应用在确认"总线已静"之后主动调用**
	 *          （`!z` 命令，或将来由更上层的电源策略触发）。
	 *
	 * @warning **当前不会降低功耗。** 本函数返回后 MCU 仍全速运行，
	 *          只是通信栈处于"已停"状态。要测电流必须等
	 *          `!z` 那条路径（它才真正 WFI），而且 `!z` 用的是
	 *          100 ms 兜底唤醒，测出的也不是最终的低功耗数值。
	 *          真正的低功耗要停 SysTick + 进 DeepSleep/Standby + 端口唤醒，
	 *          属 M13。
	 */
	s_ecuMMode = ECUM_MODE_SLEEP;
	Platform_Puts("  [ecum] SLEEP (通信已停；真正 WFI 需总线静默后手动触发)\n");
}

/* ============================ [ 唤醒源管理（M12） ] ============================ */

/**
 * @brief 使能/关闭唤醒源（EcuM 集成点）
 * @param[in] wakeupSource 位图；传 0 表示全部关闭
 *
 * @details @section ECUMAL_WKSRC 这一层为什么不能省
 *
 *          AUTOSAR 把"哪些源能把 ECU 叫醒"放在 EcuM 配置里：
 *          进入睡眠前必须**只保留**需要的源，否则一个无关的中断
 *          （比如调试串口）就会把 ECU 反复叫醒，表现为"睡不下去"。
 *
 *          本工程目前的实际情况：
 *
 *          | 源 | 状态 |
 *          |---|---|
 *          | `SysTick` | **始终开着** —— 既是兜底也是节拍源，不能关 |
 *          | CAN0 邮箱中断 | 由 `CanSM` 决定，控制器一停就没有了 |
 *          | CAN0 RX 引脚中断 | ❌ 没配。PTE4 是 CAN 复用脚，要做唤醒需在睡前切成 GPIO 边沿中断 |
 *          | 收发器 WAKE 引脚 | ❌ 硬件上没接（`Can_Cfg` 只有 STB） |
 *
 *          所以当前这里只记录位图、打日志，**不真正关任何中断** ——
 *          因为唯一能关的只有 SysTick，而它是兜底，关了就有睡死风险。
 *
 * @note  等 M13 把 PTE4 的端口唤醒做出来，这里才需要真正去
 *        `IrqDrv_EnableIrq/DisableIrq`，并通过 `Port` 切引脚复用。
 */
void EcuM_EnableWakeupSources(EcuM_WakeupSourceType wakeupSource)
{
	s_wakeupEnabled = wakeupSource;

	Platform_Printf("  [ecum] wakeup sources = 0x%04x%s\n",
	                (unsigned)wakeupSource,
	                ((wakeupSource & ECUM_WKSOURCE_CAN0) != 0u) ? " (CAN0)" : "");
}

/**
 * @brief 确认唤醒源（EcuM 集成点，唤醒后调用）
 * @param[in] wakeupSource 待确认的源
 *
 * @details 它要做的是"**核实**这个源确实触发了，并把结果通知出去"：
 *          只相信硬件标志，不相信"谁调用了谁"。
 *
 *          本工程用平台层读到的真实唤醒源（`PowerDrv_GetWakeupSource()`）
 *          来判断，而不是看传进来的位图 —— 因为位图是软件**希望**的，
 *          硬件标志才是**事实**。两者不一致正是最需要日志的场景
 *          （比如"以为配了 CAN 唤醒，实际是被 RTC 叫醒的"）。
 *
 * @note 确认到 CAN0 之后调 `ComM_EcuM_WakeUpIndication()` —— 这是
 *       标准链路（SWS_ComM）：EcuM → ComM → Nm → CanNm passive startup。
 *       M11 时 `!A` 走的也是这条，只不过是从应用层直接进 ComM。
 */
void EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource)
{
	uint8_t src = Platform_GetWakeupSource();

	Platform_Printf("  [ecum] CheckWakeup req=0x%04x hw=%s\n",
	                (unsigned)wakeupSource, Platform_GetWakeupSourceName(src));

	/* 端口唤醒（PORTC/PORTE）在本工程的接线里只可能来自 CAN 收发器：
	 * CAN0 的 RX 在 PTE4、CAN1 的 RX 在 PTC6。 */
	if ((src == 2u) || (src == 4u)) {          /* PORTC / PORTE */
		ComM_EcuM_WakeUpIndication((NetworkHandleType)COMM_CHANNEL_CAN0);
		Platform_Puts("  [ecum] -> CAN0 wakeup, ComM notified\n");
	}
}

/**
 * @brief 结束唤醒源确认（EcuM 集成点）
 * @param[in] WakeupSource 待结束确认的源
 * @note  本工程没有"必须成对清除"的硬件动作，留空实现以满足接口。
 *        真实的 PNC/部分网络场景会在这里回收临时使能的源。
 */
void EcuM_EndCheckWakeup(EcuM_WakeupSourceType WakeupSource)
{
	(void)WakeupSource;
}
