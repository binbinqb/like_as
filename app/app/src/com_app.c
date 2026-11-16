/**
 * @file    com_app.c
 * @brief   Com 信号层应用侧（M10）：信号更新、dump、分组启停
 *
 * @details 从 `main.c` 的「信号层（M10）」区整体迁出（M-Shell 命令迁移）。
 *          这里承载的是**应用变量**与发送节拍，不是 Com 模块本身：
 *          - `ComApp_Tick()` 由主循环 10 ms 节拍调用（须在 Com_MainFunction 之前）
 *          - `ComCmd_*` 供 `cmd/com_cmd.c` 与旧 `!v`/`!y` 分支共用
 *
 * @note 为什么必须"先更新、后 Com_MainFunction"：见 `ComApp_Tick` 的说明 ——
 *       两个节拍不一致会让验收脚本出现无法解释的"跳过"。
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "platform_cvm0146.h"
#include "Com.h"
#include "Com_Cfg.h"
#include "Com_Priv.h"    /* M22：`com can1` 要读 IPdu 的运行期 timer */

#include <stdbool.h>
#include <stdint.h>

/** @brief Com 的总配置表（`Com_Cfg.c` 里定义，生成物，只读） */
extern const Com_ConfigType Com_Config;

/* ============================ [ 信号层（M10） ] ============================ */

/**
 * @brief TX 滚动计数（应用侧的真实值）
 * @note  这是"应用变量"，和报文缓冲里的那个字节不是同一个东西。
 *        `Com_SendSignal()` 负责把它搬进报文缓冲。
 *        之所以要在应用侧留一份，是因为缓冲随时会被发送覆盖/初始化，
 *        应用不能拿它当自己的状态存储。
 */
static uint8_t s_comTxCounter;

/** @brief TX 状态位：固定 1，用于验证 **1 位信号**的位打包 */
static uint8_t s_comTxFlag = 1u;

/** @brief TX 模拟量：固定 0xABC，用于验证 **12 位跨字节**打包 */
static uint16_t s_comTxLevel = 0x0ABCu;

/** @brief 10 ms 拍计数：满 10 拍（100 ms）更新一次 TX 信号 */
static uint16_t s_comTick = COM_CONVERT_MS_TO_MAIN_CYCLES(100u);

/** @brief IPdu 分组当前是否运行（`!y` 用） */
static bool s_comGroupOn = true;

/**
 * @brief 应用侧的信号更新（在主循环里按 10 ms 节拍调用）
 *
 * @details @section COMAPP_TICK 为什么更新周期要和 CycleTime 对齐
 *
 *          `Com_MainFunctionTx()` 到点就把**当前缓冲**整帧发出去。
 *          如果应用更新比发送慢，同一帧值会被重复发好几次；
 *          如果比发送快，中间的若干次更新会被"跳过"，总线上只能看到
 *          其中一部分值。
 *
 *          两者都用同一个 10 ms 节拍、同一个周期（100 ms），
 *          并且**先更新、后调用 `Com_MainFunction()`**，
 *          于是每一帧恰好对应一个新值，脚本可以断言"每帧 +1"。
 *
 *          随机相位（比如应用用 `Platform_NowMs()` 自己判周期）会让
 *          偶发的跳过变得无法解释 —— 那不是 bug，是两个不同节拍的
 *          正常交错，但会让验收脚本时而过时而不时不过。
 */
void ComApp_Tick(void)
{
	uint8_t  c;
	uint8_t  f;
	uint16_t l;

	if (s_comTick > 0u) {
		s_comTick--;
	}
	if (s_comTick > 0u) {
		return;
	}
	s_comTick = COM_CONVERT_MS_TO_MAIN_CYCLES(100u);

	c = (uint8_t)(s_comTxCounter + 1u);
	f = s_comTxFlag;
	l = s_comTxLevel;

	/* 三个信号都发一遍，而不是只发变化的那个：
	 * 单发 counter 时，flag/level 只在 `Com_IpduGroupStart()` 那一次
	 * 被写进缓冲，之后一旦有人（比如 GC 之外的误写）改了缓冲，
	 * 就没有修复路径。每次全量刷新，代价是三次几字节的位操作。 */
	(void)Com_SendSignal((Com_SignalIdType)COM_SID_TX_COUNTER, &c);
	(void)Com_SendSignal((Com_SignalIdType)COM_SID_TX_FLAG, &f);
	(void)Com_SendSignal((Com_SignalIdType)COM_SID_TX_LEVEL, &l);

	s_comTxCounter = c;
}

/**
 * @brief 打印信号值（`!v`）
 *
 * @details 打印的是**两条不同路径的结果**，这正是一条命令同时看两件事的价值：
 *
 *          | 侧 | 数据来源 | 证明了什么 |
 *          |----|----------|------------|
 *          | tx | 应用自己的变量 | 应用想发什么 |
 *          | rx | `Com_ReceiveSignal()` | Com 从总线上解出了什么 |
 *
 *          tx 与 rx 之间隔着"打包 → 总线 → 解包"，两者一致说明整条链路通。
 *          验收脚本还会用 Kvaser 抓实际帧，三者对齐才算真的对。
 *
 * @note  rx 侧读不到（返回 E_NOT_OK）时打 `NG`。读不到的原因通常是
 *        Com 未初始化或信号 ID 越界 —— 不是"对端没发"，
 *        对端没发会读到超时替换值（0xEE），两者含义完全不同。
 */
static void Com_DumpSignals(void)
{
	uint8_t  rxCnt  = 0u;
	uint16_t rxTemp = 0u;
	Std_ReturnType r1;
	Std_ReturnType r2;

	r1 = Com_ReceiveSignal((Com_SignalIdType)COM_SID_RX_COUNTER, &rxCnt);
	r2 = Com_ReceiveSignal((Com_SignalIdType)COM_SID_RX_TEMP, &rxTemp);

	Platform_Printf("[com] tx cnt=%u flag=%u level=0x%03X | rx cnt=%u(%s) temp=%u(%s) | grp=%u\n",
	                (unsigned)s_comTxCounter, (unsigned)s_comTxFlag,
	                (unsigned)s_comTxLevel,
	                (unsigned)rxCnt, (r1 == E_OK) ? "ok" : "NG",
	                (unsigned)rxTemp, (r2 == E_OK) ? "ok" : "NG",
	                (unsigned)(s_comGroupOn ? 1u : 0u));
}

/**
 * @brief CAN1 的 6 条发送报文（`com can1` 用）
 * @note  PDU 号来自 `Com_Cfg.h` 的生成宏；名字用矩阵里的短名，
 *        与 `CanIf_Cfg.h` 的 `CANIF_TX_CAN1_*` 后缀对齐。
 */
static const struct {
	uint16_t    pdu;
	const char *name;
} s_can1Tx[] = {
	{ COM_CAN1_BCM_LCSF_TX,      "LCSF" },
	{ COM_CAN1_BCM_CTRL_TX,      "CTRL" },
	{ COM_CAN1_BCM_OEL_TX,       "OEL"  },
	{ COM_CAN1_BCM_OWW_TX,       "OWW"  },
	{ COM_CAN1_BCM_DOOR_CTRL_TX, "DOOR" },
	{ COM_CAN1_BCM_DM1_TX,       "DM1"  },
};

/**
 * @brief 打印 CAN1 报文状态（`com can1`）
 *
 * @details 为什么要单开一条命令，而不是塞进 `com sig`：
 *          `com sig` 打的是**测试报文**的信号值，用来验打包/解包；
 *          CAN1 的 34 条接收 + 6 条发送是**整车矩阵**，关心的是
 *          "有没有在发、下一拍还有多久、发送失败有没有重试"。
 *          这两类信息在排查时不会同时需要，混在一起只会让输出更难读。
 *
 *          典型用法：总线上**看不到**某条报文时先跑这条命令。
 *          - `t=` 一直不变（停在某个值）→ 该 IPdu 没被任何分组启动；
 *            `t=` 周期在 `0..CycleTime` 之间回卷 → 正常在发；
 *          - `retry=1` → `PduR_ComTransmit` 返回过失败，正在等
 *            `Com_MainFunction_Fast()` 重发。**本工程没在主循环里调
 *            `Com_MainFunction_Fast()`**，所以 `retry=1` 基本等于"卡死了"，
 *            要看 CanIf 那一侧是不是把 PDU 号配错（`Can_Write` 返回 E_NOT_OK）。
 */
void ComCmd_DumpCan1(void)
{
	uint8_t i;
	uint8_t doorSw  = 0u;
	uint8_t parkBrk = 0u;
	uint16_t tacho  = 0u;
	Std_ReturnType r0;
	Std_ReturnType r1;
	Std_ReturnType r2;

	Platform_Puts("  can1 tx pdus (t = 剩余拍数，10 ms/拍)\n");
	for (i = 0u; i < (uint8_t)ARRAY_SIZE(s_can1Tx); i++) {
		const Com_IPduConfigType *p = &Com_Config.IPduConfigs[s_can1Tx[i].pdu];

		if (NULL == p->txConfig) {
			Platform_Printf("   %-5s pdu=%-2u  <无 txConfig>\n",
			                s_can1Tx[i].name, (unsigned)s_can1Tx[i].pdu);
			continue;
		}
		Platform_Printf("   %-5s pdu=%-2u t=%-4u cycle=%-3u retry=%u len=%u\n",
		                s_can1Tx[i].name, (unsigned)s_can1Tx[i].pdu,
		                (unsigned)p->txConfig->context->timer,
		                (unsigned)p->txConfig->CycleTime,
#ifdef COM_USE_MAIN_FAST
		                (unsigned)p->txConfig->context->bTxRetry,
#else
		                0u,
#endif
		                (unsigned)p->length);
	}

	/* 三条**已知布局**的接收信号，专供上板对拍：
	 *   IC_MSG  0x18FF0917 byte1 bit4-5 → DoorOpenSw
	 *   CCVS    0x18FEF121 byte0 bit2-3 → ParkingBrakeSwitch
	 *   TCO1    0x18CFE6CEE byte6-7     → TachographVehicleSpeed（小端）
	 * 注入 `32 00 00 00 00 00 34 12` 到 0x18FEF121 之类，就能一眼看出
	 * 位偏移和字节序有没有配错 —— 这三条覆盖"位偏移""跨字节""16 位小端"。 */
	r0 = Com_ReceiveSignal((Com_SignalIdType)COM_SID_DoorOpenSw, &doorSw);
	r1 = Com_ReceiveSignal((Com_SignalIdType)COM_SID_ParkingBrakeSwitch, &parkBrk);
	r2 = Com_ReceiveSignal((Com_SignalIdType)COM_SID_TachographVehicleSpeed, &tacho);
	Platform_Printf("  can1 rx signals: DoorOpenSw=%u(%s) ParkBrake=%u(%s) TachoSpeed=%u(%s)\n",
	                (unsigned)doorSw,  (r0 == E_OK) ? "ok" : "NG",
	                (unsigned)parkBrk, (r1 == E_OK) ? "ok" : "NG",
	                (unsigned)tacho,   (r2 == E_OK) ? "ok" : "NG");
}

/**
 * @brief 信号层的串口命令（`!v` / `!y`）
 *
 * @param[in] c 命令字符
 *
 * @note  `!y` 停的是 **IPdu 分组**，不是 Com 本身。区别很重要：
 *        分组停了之后 `Com_SendSignal()` 照常成功（只是改缓冲），
 *        `Com_MainFunctionTx()` 跳过这个组不发 —— 恢复时不需要
 *        重新初始化 Com，一帧都不会丢配置。
 *
 * @note  停组时把 `s_comTxCounter` 一起清零：`Com_IpduGroupStart(TRUE)`
 *        会用初值重刷报文缓冲，如果应用侧计数器不清零，
 *        恢复后的第一帧会和缓冲里的初值不一致，看起来像"丢了几帧"。
 */

/**
 * @brief 打印全部 TX/RX 信号（`com sig` / 旧 `!v`）
 */
void ComCmd_DumpSignals(void)
{
	Com_DumpSignals();
}

/**
 * @brief 分组启停（`com group` / 旧 `!y`）
 * @note 停的是 **IPdu 分组**，不是 Com 本身：分组停了之后
 *       `Com_SendSignal()` 照常成功（只是改缓冲），`Com_MainFunctionTx()`
 *       跳过这个组不发 —— 恢复时不需要重新初始化 Com，配置不会丢。
 * @note 停组时把 `s_comTxCounter` 一起清零：`Com_IpduGroupStart(TRUE)`
 *       会用初值重刷报文缓冲，如果应用侧计数器不清零，恢复后的第一帧
 *       会和缓冲里的初值不一致，看起来像"丢了几帧"。
 */
void ComCmd_GroupToggle(void)
{
	if (s_comGroupOn) {
		Com_IpduGroupStop((Com_IpduGroupIdType)COM_GROUP_ID_CANTEST);
		s_comGroupOn = false;
		Platform_Puts("[com] group 0 STOPPED (TX/RX suspended)\n");
	} else {
		Com_IpduGroupStart((Com_IpduGroupIdType)COM_GROUP_ID_CANTEST, TRUE);
		s_comTxCounter = 0u;
		s_comTick = COM_CONVERT_MS_TO_MAIN_CYCLES(100u);
		s_comGroupOn = true;
		Platform_Puts("[com] group 0 STARTED (100 ms)\n");
	}
}
