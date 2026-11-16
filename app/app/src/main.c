/**
 * @file    main.c
 * @brief   M1 里程碑：AUTOSAR MCAL（Port/Dio/Can）驱动真实 CAN 收发
 *
 * @details 验收判据（Kvaser ch0=CAN0 / ch1=CAN1，两路 @500 kbps）：
 *          1. **CAN0 TX 标准帧**：`0x123` 每 500 ms，DLC=8，8 字节逐帧全 +1；
 *          2. **CAN0 TX 扩展帧**：`0x18FF0002` 每 1000 ms（**29 位**），
 *             首字节递增，其余 `A5`；
 *          3. **CAN0 RX**：发 `0x321` → `pdu=0`；发 `0x18FF0001` → `pdu=1`；
 *          4. **CAN1 TX**：`0x124` 每 500 ms，首字节递增，其余 `C3`；
 *          5. **CAN1 RX**：发 `0x322` → `pdu=2`；
 *          6. **不影响 M0**：启动横幅、printf 自检、心跳、回显照常。
 *
 *          走的是 AUTOSAR 的正规路径，不是直接怼寄存器：
 *          ```
 *          Port_Init(NULL)                        引脚 MUX/方向/初始电平（含 CAN1 的 PTC6/PTC7/PTE13）
 *          Can_Init(NULL)                         装载两路通道配置
 *          CanIf_Init(NULL)                       所有控制器 PDU 模式置 OFFLINE
 *          CanIf_SetControllerMode(ch, STARTED)   → Can_SetControllerMode → CanAc_Init
 *          CanIf_SetTrcvMode(ch, NORMAL)          STB 拉低，收发器上总线
 *          CanIf_SetPduMode(ch, ONLINE)           **必须**，否则发送恒失败
 *          CanIf_Transmit(CANIF_TX_XXX, &pdu)     发送：只给逻辑 PDU 号
 *          App_CanIfRxIndication(pduId, pdu)      接收：CanIf_Cfg 挂上来的回调
 *          ```
 *
 *          @section M2_RX 应用层再也看不到 CAN ID，也看不到通道
 *          M1 的 `CanAc_RxIndication(controller, id, isExt, ...)` 把报文 ID 直接暴露给应用；
 *          M2 之后应用只拿到 `PduIdType`（`CANIF_RX_TEST` / `CANIF_RX_EXT_TEST` / `CANIF_RX_CAN1_TEST`）。
 *          加一条报文、改 ID、改掩码、把报文从 CAN0 挪到 CAN1 —— 应用一行不用动，
 *          全在 `CanIf_Cfg.c` / `Can_Cfg.c` 两张表里。
 *
 *          @warning 中断里不要打印。`Platform_Printf` 是阻塞轮询发送的，
 *          CAN 中断里阻塞几十微秒以上就可能丢下一帧。所以中断只置标志+拷数据，
 *          打印放主循环。
 *
 * @author  binbina
 * @version V2.8.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：启动 + 心跳 + 串口回显 |
 * | V1.1.0 | 2026-11-10 | binbina | 增加 printf 自检表（宽度/对齐/补零/精度/符号） |
 * | V1.2.0 | 2026-11-10 | binbina | M1：Port/Dio/Can 初始化，周期发 0x123，收 0x321 |
 * | V1.3.0 | 2026-11-10 | binbina | M2：接 CanIf，收发改为逻辑 PDU；增加 29 位扩展帧收发 |
 * | V1.4.0 | 2026-11-10 | binbina | M2b：开 CAN1（PTC6/PTC7 ALT3 + PTE13 STB），双通道收发 |
 * | V1.5.0 | 2026-11-10 | binbina | M4：接存储栈（NvM/FEE），启动计数 + 延迟落盘 + GC 压测 + DET |
 * | V1.6.0 | 2026-11-11 | binbina | M5：bus-off 检测/记录，故障快照持久化到 DTC 块 |
 * | V1.7.0 | 2026-11-11 | binbina | M6：故障表下沉为 Dem，接 Dcm 0x19/0x14；抽公共 ISO-TP 脚本 |
 * | V1.8.0 | 2026-11-11 | binbina | M7：0x27 安全访问（恒通过）+ 0x2E 写 DID（VIN 落 NvM） |
 * | V1.9.0 | 2026-11-11 | binbina | M9：接 CanNm/Nm 网络管理（0x500，200 ms），ComM 状态镜像 |
 * | V2.0.0 | 2026-11-11 | binbina | M10：接 Com 信号层（0x200，100 ms），位打包/大小端/信号超时 |
 * | V2.1.0 | 2026-11-11 | binbina | M11：EcuM 三阶段初始化 + ComM/CanSM 标准链路 |
 * | V2.2.0 | 2026-11-11 | binbina | M11b：修 CAN 低功耗死锁（平台管时钟 / STOPPED 只 freeze），链路全通 |
 * | V2.3.0 | 2026-11-11 | binbina | M12：唤醒源识别 + EcuM 唤醒接口 + STOP 模式手动睡眠（!z） |
 * | V2.4.0 | 2026-11-11 | binbina | M13：A/B 分区（双镜像 + 槽尾 meta + UDS 刷非活动槽） |
 * | V2.5.0 | 2026-11-11 | binbina | M14：通信矩阵承载能力（段掩码邮箱 + 硬件/软件双层过滤压测） |
 * | V2.6.0 | 2026-11-11 | binbina | M15：ADC 模块（as-master 无，按三段式补；双单元 + 多通道 + PDB/TRGMUX） |
 * | V2.7.0 | 2026-11-11 | binbina | M18：PWM 模块（PwmLite 4 路、0%/100% 静态电平、同实例同频约束） |
 * | V2.8.0 | 2026-11-11 | binbina | M19：CAN1 真实通信矩阵接入（34 RX 按 PF 分组 / 6 TX / 生成器注入） |
 */

#include "platform_cvm0146.h"
#include "sh_app.h"
#include "cmd/cmd_api.h"
#include "can_test.h"   /* CanTest_* / Fault_*（从 main.c 迁出） */   /* 旧 !x 命令 → cmd/ 实现的桥（迁移期） */

#include "Can.h"
#include "Can_Cfg.h"     /* CAN_CFG_NUM_CHANNELS：通道数由平台配置决定，应用不写死 */
#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "PduR.h"
#include "CanTp.h"
#include "Dcm.h"
#include "Dio.h"
#include "Dio_Cfg.h"
#include "Pwm.h"          /* M18：PWM 验收命令 !l/!L */
#include "Pwm_Cfg.h"
#include "Adc.h"         /* M15：ADC 标准接口 */
#include "Adc_Cfg.h"     /* ADC_CFG_GROUP_PROBE 等组号 */
#include "Port.h"

#include "NvM.h"         /* AUTOSAR 外观：NvM_Init / ReadBlock / WriteBlock / WriteAll */
#include "NvM_Cfg.h"     /* NVM_CFG_ID_*（块 id）与块长 */
#include "Det.h"
#include "Std_Timer.h"   /* 软件定时器：CanNm 的定时基础 */

/* 网络管理（M9）。应用**只碰 Nm/ComM**，不直接调 CanNm ——
 * 直接调 CanNm 等于"绕过 ComM 操作某根总线"，多总线时会状态不一致。
 * CanNm.h 只是为了让 `!m` 打印 CanNm 内部状态时才包含。 */
#include "Nm.h"
#include "ComM.h"
#include "CanNm.h"
#include "Nm_Cfg.h"

/* 信号层（M10）。应用只碰 `Com_SendSignal` / `Com_ReceiveSignal` ——
 * 看不见报文 ID、字节偏移、位序，那些都在 `Com_Cfg.c` 里。 */
#include "Com.h"
#include "Com_Cfg.h"

/* 车身信号绑定层（M23）。业务侧**只** include 这一个头：
 * 它看得见 `Bcm_SwStateType` 与 `BCM_SIG_xxx`，看不见 `COM_SID_xxx`、
 * 报文名、字节偏移 —— 那些都在 `bcm_sig_cfg.c` 的表里。 */
#include "bcm_sig.h"
#include "rx_mon.h"       /* A2：CAN 接收到达监视（清零必须在总线上线前） */

/* ECU 状态管理（M11）。应用只碰标准接口：
 *   EcuM_Init / EcuM_StartupTwo / EcuM_RequestRUN / EcuM_RequestPOST_RUN
 * 初始化顺序与 BSW 调度全在 `EcuM_Cfg.c` 的表里。 */
#include "EcuM.h"
#include "EcuM_Externals.h"  /* EcuM_EnableWakeupSources / EcuM_CheckWakeup（集成点，M12） */
#include "EcuM_Cfg.h"
#include "ComM_Cfg.h"   /* COMM_USER_APP / COMM_CHANNEL_CAN0 */

#include "Dem.h"          /* 事件上报：Dem_SetEventStatus（AUTOSAR BSW） */
#include "Dem_Cfg.h"      /* 事件号 / DTC 码 / Dem_DtcInfoType */

#include "boot_app.h"      /* A/B：槽地址对账 + 首次自注册 + 启动确认 */
#include "boot_flash_map.h" /* BOOT_SLOT_BASE：banner 里打印本镜像所在槽 */
#include "FlashLoader.h"  /* 0x31/0x34/0x36/0x37 的业务实现（平台层） */

#include <string.h>

/* ============================ [ 常量 ] ============================ */

/** @brief 心跳周期（ms） */
#define HEARTBEAT_MS        (1000u)

/**
 * @brief BSW 周期任务周期（ms）
 * @note  必须与 `CanTp_Cfg.h` / `Dcm_Cfg.h` 的 `*_MAIN_FUNCTION_PERIOD` 一致，
 *        否则定时器换算出来的超时不是真实毫秒数。
 */
#define BSW_PERIOD_MS       (10u)

/** @brief CAN 标准帧发送周期（ms） */
#define CAN_TX_PERIOD_MS    (500u)

/** @brief CAN 扩展帧发送周期（ms）：比标准帧慢一倍，方便在总线上区分 */
#define CAN_EXT_TX_PERIOD_MS (1000u)

/* ============================ [ printf 自检 ] ============================ */

/**
 * @brief 打印 printf 格式化自检表
 *
 * @details 每一行都针对一个曾经踩过或极易踩的坑：
 *          | 用例 | 想验证的点 |
 *          |------|------------|
 *          | `%6u` / `%-6u` | 宽度是否被解析、左右对齐 |
 *          | `%06u` / `%08x` | 补零是否生效、补在符号之后 |
 *          | `%d` 负数 / `INT32_MIN` | 符号判定，且取负不溢出 |
 *          | `%+d` / `% d` | 正数也带符号 / 带空格 |
 *          | `%#x` | `0x` 前缀 |
 *          | `%.3d` / `%8.3d` | 精度=最少位数，以及精度与宽度叠加 |
 *          | `%-8s` / `%.3s` | 字符串左对齐 / 最大字符数截断 |
 *          | `%.0d` 传 0 | 精度 0 + 值为 0 时输出空（标准行为） |
 *          | `%%` | 转义为单个 `%` |
 *
 * @note 这是**验收代码**，不是生产代码：M2 之后可以整体删掉，或用编译开关关掉。
 */
static void PrintfSelfTest(void)
{
	Platform_Puts("-- printf self-test -------------------------------\n");

	Platform_Printf("  width    right |%6u|   left |%-6u|\n", 42u, 42u);
	Platform_Printf("  zero pad       |%06u|    hex |%08x|\n", 42u, 0xbeefu);
	Platform_Printf("  hex prefix     |%#x|          |%#X|\n", 0xbeefu, 0xbeefu);
	Platform_Printf("  negative       |%6d|  plus  |%+d|\n", -7, 7);
	Platform_Printf("  space flag     |% d|         |% d|\n", 7, -7);
	Platform_Printf("  precision      |%.3d|  w+p   |%8.3d|\n", 42, 42);
	Platform_Printf("  prec 0 of 0    |%.0d|  (should be empty)\n", 0);
	Platform_Printf("  int32 min      |%d|\n", (int)(-2147483647 - 1));
	Platform_Printf("  string         |%-8s|  trunc |%.3s|\n", "abc", "abcdef");
	Platform_Printf("  char |%c|  percent |100%%|\n", 'X');
	Platform_Printf("  pointer        |%p|\n", (void *)PrintfSelfTest);

	Platform_Puts("--------------------------------------------------\n\n");
}

/* ============================ [ 定时器自检 ] ============================ */

/**
 * @brief 软件定时器自检（启动时跑一次）
 *
 * @details 验的是**时间源**而不是定时器逻辑本身 —— 逻辑是从 as-master 原样
 *          摘过来的（含溢出处理），唯一可能配错的是 `Std_GetTime()`：
 *          它要是返回 0 或者单位搞错（ms 当 us），所有定时器都会"立刻超时"，
 *          而 CanNm 会因此疯狂发 NM 报文、永远不睡。
 *
 *          这类错误在 CAN 上表现是"NM 报文发得太密"，很难反推到时基上，
 *          所以在启动时花 50 ms 把它钉死。
 *
 * @note  允许 ±5 ms 误差：`Std_GetTime()` 的精度就是 1 ms，
 *        加上打印和循环开销。超出这个范围说明时基算错了。
 */
static void TimerSelfTest(void)
{
	Std_TimerType t;
	uint32_t t0;
	uint32_t elapsed;

	t0 = Platform_NowMs();
	Std_TimerInit(&t, 50000u);          /* 50000 us = 50 ms */
	while (!Std_IsTimerTimeout(&t)) {
		/* 忙等：这里就要看真实耗时，不能用 Platform_DelayMs 混过去 */
	}
	elapsed = Platform_NowMs() - t0;

	Platform_Printf("  timer : 50 ms 超时 -> 实测 %u ms (%s)\n",
	                (unsigned)elapsed,
	                ((elapsed >= 50u) && (elapsed <= 55u)) ? "ok" : "CHECK");
}

/* ============================ [ 入口 ] ============================ */

int main(void)
{
	uint32_t nextBeat = 0u;
	uint32_t nextTx   = 0u;
	uint32_t nextExt  = 0u;
	uint32_t nextBsw  = 0u;
	uint32_t beat     = 0u;

	Platform_Init();
	Platform_InitTick();

	/* A2 到达监视清零：必须在总线上线之前。
	 *
	 * 清在这里而不是 `BcmSig_Init()`：`BcmSig_Init()` 在 RUN 之后才跑，
	 * 那时 CAN1 可能已经收到过帧，清零会把"真的来过"抹掉，于是上电后
	 * 头 300 ms 的信号全被判成 NEVER_RECEIVED（比不判还误导）。 */
	RxMon_Init();

	Platform_Puts("\n");
	Platform_Puts("========================================\n");
	Platform_Puts("  AS / CVM0146  bring-up  (M4)\n");
	Platform_Puts("  build : " __DATE__ " " __TIME__ "\n");
	Platform_Puts("  core  : PLL 120 MHz\n");
	Platform_Puts("  uart  : UART2 115200 8N1  (PC: COM2)\n");
	/* A/B：本镜像链接在哪个槽。与 boot 打印的 "jump to slot X" 对照，
	 * 能一眼看出"是不是真的换了镜像"—— 升级排查时这是第一个要确认的事。 */
	Platform_Printf("  slot  : %c  (link 0x%08X)\n",
	                (APP_SLOT_INDEX == 0) ? 'A' : 'B',
	                (unsigned)BOOT_SLOT_BASE((uint8_t)APP_SLOT_INDEX));

	/* 本次上电/复位是被什么唤醒的 —— 实车没有调试器，这一行是
	 * 排查"为什么自己醒了 / 为什么没睡"的第一手证据。
	 * 纯读操作，不影响任何状态。 */
	Platform_Printf("  wake  : %s (%u)%s\n",
	                Platform_GetWakeupSourceName(Platform_GetWakeupSource()),
	                (unsigned)Platform_GetWakeupSource(),
	                (Platform_GetWakeupSource() == PLATFORM_WAKEUP_NONE)
	                    ? "  [cold boot]" : "  [woken from low power]");

	/* 定时器自检放在最前：50 ms 忙等，此时通信栈还没起，不干扰任何周期断言 */
	TimerSelfTest();

	/* ------------------------------------------------------------------
	 * A/B 分区配合（M13）
	 *
	 * 1) 对账：本镜像的链接地址必须等于 `APP_SLOT_INDEX` 对应的槽基址，
	 *    不等说明烧错了文件（把 AppB 刷进了 A 槽）—— 就地停住，
	 *    否则第一次解引用全局变量就跳飞，现场表现为"偶发死机"。
	 * 2) 首次烧写（槽尾 meta 是 0xFF）时补写 meta，让下次上电走正规流程。
	 *    已有 meta 时**不碰 Flash**，正常启动零擦写。
	 * ------------------------------------------------------------------ */
	BootApp_Init();

	/* 刷写业务初始化：锁定"当前活动槽"，之后 0x31/0x34 一律拒绝擦写它。
	 * 放在 BootApp_Init 之后 —— 后者刚扫过 meta，这里再扫一次是幂等的；
	 * 顺序反过来也能工作，但会多读一次 Flash（约 1 ms）。 */
	FlashLoader_Init();

	/* ------------------------------------------------------------------
	 * 启动序列交给 EcuM，**不再手工按顺序调 Init**
	 *
	 * 三个阶段对应 `EcuM_Cfg.c` 的三张表：
	 *   EcuM_Init()       → DriverInitZero（Port / Can）
	 *                     + DriverInitOne （CanIf … CanSM + NvM_Init）
	 *   EcuM_StartupTwo() → DriverInitTwo （NvM_ReadAll + 启动计数 + Dem）
	 *
	 * 之所以必须先 `StartupTwo` 再 `RequestRUN`：进 RUN 会立刻让
	 * ComM/CanSM 启动总线并开始发 NM 报文，而 NM 的状态上报依赖
	 * NvM/Dem 已经就绪（故障要能落盘）。顺序反了不会崩，但
	 * 总线起来后最初几秒的故障记录会丢。
	 * ------------------------------------------------------------------ */
	EcuM_Init();
	EcuM_StartupTwo();

	/* ------------------------------------------------------------------
	 * ADC 初始化（M15 最小验证）
	 *
	 * @note 位置说明：必须排在 `EcuM_Init()` 之后 —— ADC 引脚的方向/MUX
	 *       由 `Port_Init()` 配置，而 Port 在 EcuM 的 `DriverInitZero` 里。
	 *       排在前面的症状是"ADC 能转，但读到的永远是 0 或满量程"
	 *       （引脚还挂在别的复用功能上）。
	 *
	 * @note TODO：正式版应把这一步挪进 `EcuM_Cfg.c` 的 `DriverInitOne` 表，
	 *       和 CanIf/CanNm 一样由表驱动。现在直接调是为了让最小验证先跑起来。
	 * ------------------------------------------------------------------ */
	/* ADC 已归位到 `EcuM_Cfg.c` 的 `DriverInitListZero`（Port → Can → Adc），
	 * 由 `EcuM_Init()` 统一按表调用，这里不再手工初始化 ——
	 * 顺序由表保证，以后加模块只改表不改 main。
	 *
	 * 探针用显式缓冲区读组结果（`Adc_ReadGroup(g, raw)`），
	 * 所以全程不调 `Adc_SetupResultBuffer()`；它是给"先绑定、后异步读"
	 * 的用法留的，两条路径 `Adc_ReadGroup` 都支持。 */

	/* 应用请求 RUN。`EcuM_RequestRUN` 只置标志，真正的动作在
	 * `EcuM_MainFunction()` 里 —— 所以紧接着推一次，让 RUN 同步生效，
	 * 后面的横幅打印与周期发送才能在确定的时机开始。 */
	(void)EcuM_RequestRUN((EcuM_UserType)0u);
	EcuM_MainFunction();

	/* ------------------------------------------------------------------
	 * A/B 启动确认：**放在 RUN 生效之后**，不是 main 开头。
	 *
	 * 这是"新镜像能跑"的唯一证据。放在开头的话，"时钟起来了但 CAN 起不来"
	 * 这种镜像也会被判成功，回滚机制就白做了。等 CAN 控制器 STARTED、
	 * 收发器 NORMAL 之后再确认，语义才成立。
	 *
	 * 只在新镜像第一次启动时写一次 Flash；之后每次上电读 meta 发现
	 * 已是 CONFIRMED 就直接返回，不再擦写。
	 * ------------------------------------------------------------------ */
	BootApp_Confirm();

	CanTest_Init();

	/* 车身信号绑定层（M23）：把 11 个灯状态置 OFF 并写进 Com 发送缓冲。
	 * 放在这里而不是 `EcuM_Init` 的表里，理由和 `CanTest_Init` 一样 ——
	 * 它依赖 Com 已经 `Com_Init()` 完毕（`EcuM_Cfg.c` 的 DriverInitOne），
	 * 而这一步已在上面 `EcuM_StartupTwo()` 之前完成。 */
	BcmSig_Init();

	Platform_Puts("========================================\n\n");

	PrintfSelfTest();

	/* Shell 接入：绑定 UART2 控制台、打印横幅。
	 * 放在自检之后 —— 命令要访问的 BSW 已全部初始化完毕。 */
	ShApp_Init();

	Platform_Puts("  commands: type `help`  (can / dtc / nm / com / nvm / ecum / adc / pwm / board)\n\n");

	for (;;) {
		/* 1) 串口输入：交给 shell（行编辑 + 回显 + 命令分发）
		 *    验收脚本已全部切到新命令（见 tools 下各 xxx_check.py 的 CMD_MAP），
		 *    旧 `!x` 兼容桥与单字符分发已删除。 */
		ShApp_Task();

		/* 2) CAN 自测帧周期发送（500 ms / 1000 ms）
		 *
		 *    ★ A3 测试隔离：`0x123`（CAN0 心跳）和 `0x124`（CAN1）是
		 *    **驱动层自测帧**，不属于整车通信矩阵。它们默认不发 ——
		 *    `s_autoTx` 上电为 `FALSE`，只有 `can auto on` 才打开。
		 *
		 *    为什么必须隔离：这两条帧常年占着总线（各 500 ms 一帧），
		 *    网关/网络管理侧会报"未知报文"；而 `0x124` 与 CAN1 上已经
		 *    接入 Com 的 6 条真实报文同通道，排查总线问题时多一条噪音源。
		 *    更要紧的是发送失败时它会往串口打
		 *    `[can] CanIf_Transmit(heartbeat) failed` —— 量产件上刷屏。
		 *
		 *    保留而不是删除的理由：M1/M2 验收的就是"CAN 驱动能不能收发"，
		 *    删掉等于把驱动层唯一的端到端自测手段拆了。
		 *
		 *    注意 `Fault_PollBusOff()` 与 `CanTest_DrainRx()` **不在**这个
		 *    开关里：前者只读寄存器，后者只在中断已置标志时打一行串口，
		 *    都不会主动占总线。 */
		if (CanTest_IsAutoTx()) {
			if ((uint32_t)(Platform_NowMs() - nextTx) >= CAN_TX_PERIOD_MS) {
				nextTx = Platform_NowMs();
				CanTest_SendOne();      /* CAN0 0x123：8 字节全递增 */
				CanTest_SendCan1();     /* CAN1 0x124：首字节递增 */
			}
			if ((uint32_t)(Platform_NowMs() - nextExt) >= CAN_EXT_TX_PERIOD_MS) {
				nextExt = Platform_NowMs();
				CanTest_SendExt();
			}
		}

		/* 3) CAN 收帧打印（只打印中断已收到的帧，不主动发送） */
		CanTest_DrainRx();

		/* 3b) 总线故障：检测 bus-off、记录、复查恢复
		 *     放在主循环而不是中断里，理由见 `Fault_PollBusOff` 的注释 */
		Fault_PollBusOff();

		/* 4) BSW 周期任务：**必须按固定周期调用，不能放在自由循环里**
		 *
		 *    定时器型模块（CanTp / Dcm / Com / Nm）的计数都是"每次
		 *    MainFunction 递减一次"（见 `CanTp_Priv.h` 的 `CanTpSignalAlarm`），
		 *    配置里的 N_Bs / N_Cr / S3 按 `XXX_MAIN_FUNCTION_PERIOD` 毫秒
		 *    折算成 tick 数。扔进无节拍的 while(1)，主循环每秒跑几万次，
		 *    100 tick 的 N_Bs 会在几百微秒内耗尽 —— 多帧传输立刻超时。
		 *    症状很有迷惑性：**单帧全通，多帧一律失败**。
		 *
		 *    ★★ 唯一归属（A1）
		 *    BSW 模块只在 `EcuM_DriverMainList` 里注册、只在
		 *    `EcuM_BswService()` 里被调用一次。**本文件不得再直接调用
		 *    任何 BSW 的 `*_MainFunction()`。**
		 *
		 *    历史教训：2026-11-16 之前这里直接调了 CanTp / Dcm / NvM / Dem
		 *    各一次，叠加表里的同名项 = 四个模块每拍各跑两次。后果不是
		 *    "跑得快一点"，而是**所有时间基准减半**：S3 标称 5 s 实际
		 *    2.5 s、N_Bs/N_Cr 折半、Dem 落盘节奏翻倍。而当时所有
		 *    "静默 6.5 s 看是否掉会话"的测试**依然是绿的**（它只断言
		 *    "掉了"，不断言"何时掉"）—— 这类错误只能靠
		 *    `tools/a1_sched_check.py` 的静态唯一性判据拦住。
		 *
		 *    应用层不在此列：`BcmSig_MainFunction()` / `ComApp_Tick()`
		 *    不在 BSW 调度表里，必须留在下面，且**必须在
		 *    `EcuM_BswService()` 之前**（要抢在 Com 打包前把新值写进报文
		 *    缓冲，否则第一帧发出去的是上一拍的旧值，差一帧）。
		 */
		if ((uint32_t)(Platform_NowMs() - nextBsw) >= BSW_PERIOD_MS) {
			nextBsw = Platform_NowMs();

			/* 车身信号绑定层（M23）先跑：把业务语义翻成 raw 写进 Com。
			 * 必须排在任何消费信号的业务逻辑之前（读到的是本拍输入）。 */
			BcmSig_MainFunction();
			ComApp_Tick();

			/* BSW 调度交给 EcuM：按 `EcuM_DriverMainList` 的顺序跑一遍
			 * （CanSM → ComM → Com → ComFast → CanNm → Nm → CanTp →
			 *  Dcm → NvM → Dem）。顺序和内容都在配置表里。
			 *
			 * 两个表内顺序是刻意的，不是随手排的：
			 * - Nm 在 NvM 之前：Nm 每 200 ms 发一帧，周期精度依赖主函数
			 *   被准时调用；放在 FEE 擦除之后会被拖出几毫秒抖动。
			 * - NvM / Dem 在表尾：FEE 擦除是 1 KB 分片的，单次可能占用
			 *   几毫秒，放前面会把 UDS 的 10 ms 节拍推歪。 */
			EcuM_BswService();

			/* 状态机单独推进：负责 RUN / POST_RUN / SLEEP 的迁移，
			 * 与 BSW 主函数是两件事（AUTOSAR 里也是两个入口），
			 * 所以它**不在** `EcuM_DriverMainList` 里。 */
			EcuM_MainFunction();
		}

		/* 6) 心跳 */
		if ((uint32_t)(Platform_NowMs() - nextBeat) >= HEARTBEAT_MS) {
			nextBeat = Platform_NowMs();
			beat++;
			Platform_Printf("[%6u ms] alive #%u txok=%u\n",
			                (unsigned)Platform_NowMs(), (unsigned)beat,
			                (unsigned)CanTest_GetTxOk());
		}
	}
}

/* ============================ [ DET 钩子 ] ============================ */

/**
 * @brief DET 日志钩子（覆盖 `infras/system/Det/Det.c` 里的弱符号）
 *
 * @details 参数错误的唯一可见出口。没有它的话，`NvM_ReadBlock()` 只返回
 *          `E_NOT_OK`，"块 id 写错了"和"引擎忙"在板上没有任何区别。
 *
 * @note 弱符号覆盖依赖“有且只有一份强定义”。本函数原先随存储区一起放在
 *       `main.c`，M-Shell 迁移存储代码时被误删，导致 `[det]` 行消失、
 *       m4 的 DET 用例失败 —— 现在固定在文件末尾，不再跟着业务代码搬。
 */
void Det_Log(uint16_t ModuleId, uint8_t ApiId, uint8_t ErrorId)
{
	Platform_Printf("[det] mod=%u api=0x%02x err=0x%02x\n",
	                (unsigned)ModuleId, (unsigned)ApiId, (unsigned)ErrorId);
}
