/**
 * @file    CanNm_Cfg.c
 * @brief   CanNm 的通道配置（单通道 0x500，200 ms 周期）
 *
 * @details @section CANNMCFG_C_WHY 为什么用指定初始化器
 *
 *          `CanNm_ChannelConfigType` 有 14~24 个字段，其中 **6 组在 `#ifdef` 之内**
 *          （`CANNM_REMOTE_SLEEP_IND_ENABLED` / `CANNM_COM_USER_DATA_SUPPORT` /
 *          `CANNM_GLOBAL_PN_SUPPORT` / `CANNM_CAR_WAKEUP_SUPPORT`）。
 *
 *          位置初始化在一组开关翻转后就会**整体错位**，而且编译器不会报错 ——
 *          比如把 `PduCbvPosition` 的值写进 `PduNidPosition`，两处都是
 *          `uint8_t`，能编过、能跑，只是 NM 报文的字节布局全错。
 *
 *          指定初始化器按字段名绑定，开关怎么变都不会串位。AS 的代码生成器
 *          （`tools/generator/CanNm.py`）用位置初始化，是因为它自己控制生成，
 *          人和生成器不能比 —— 手写配置必须用指定初始化器。
 *
 *          @section CANNMCFG_C_TIMING 时间参数怎么定的
 *
 *          所有值先按**毫秒**写，再由 `CANNM_CONVERT_MS_TO_MAIN_CYCLES()` 换算。
 *          表格里同时给出真实毫秒值，方便对照示波器/报文时间戳。
 *
 *          | 参数 | ms | 周期数 | 约束 |
 *          |------|----|--------|------|
 *          | `MsgCycleTime` | 200 | 20 | NM 正常周期 |
 *          | `MsgTimeoutTime` | 500 | 50 | **必须 > `MsgCycleTime`**，否则每帧都判发送超时 |
 *          | `RepeatMessageTime` | 800 | 80 | = 4 × `MsgCycleTime` |
 *          | `NmTimeoutTime` | 2000 | 200 | 收不到任何 NM 报文多久后准备睡眠 |
 *          | `WaitBusSleepTime` | 2000 | 200 | 准备睡眠到真正睡眠的等待 |
 *          | `MsgReducedTime` | 100 | 10 | 只在本机是 NM 协调者时用，当前不生效 |
 *          | `ImmediateNmCycleTime` | 20 | 2 | 只有 `ImmediateNmTransmissions > 0` 时才用 |
 *
 *          @section CANNMCFG_C_200 为什么周期取 200 ms
 *
 *          量产 BCM 的 NM 周期常见 500 ms 或 1000 ms。这里取 200 ms 是**验证优先**：
 *          验收脚本要在 2~3 秒内数清 5~10 帧才能稳定判定周期对不对，
 *          500 ms 下要等 5 秒以上，脚本总时长翻倍。
 *
 *          改回量产值只需改这一个数 —— 但**同时要改 `RepeatMessageTime`**
 *          （它必须是 `MsgCycleTime` 的整数倍），否则 `RepeatMessage → NormalOperation`
 *          的时机与周期不成整比，报文发送会出现一次不均匀的间隔。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：单通道，0x500，200 ms |
 */

#include "CanNm.h"
#include "CanNm_Cfg.h"
#include "CanNm_Priv.h"

#include "CanIf_Cfg.h"

/* ============================ [ 通道配置 ] ============================ */

/**
 * @brief 本工程的 NM 节点号
 * @note  J1939/OSEK 里叫"源地址"，AUTOSAR NM 里叫 `NodeId`，
 *        写进 NM 报文的 `PduNidPosition` 指定的那一字节。
 *        **同一条总线上不能重复**，否则节点检测（`NodeDetectionEnabled`）会误判。
 *        实车上这个值是网络设计给定的，不是随便挑的。
 */
#define CANNMCFG_NODE_ID            (0x42u)

static const CanNm_ChannelConfigType CanNm_ChannelConfigs[] = {
	{
		/* ---- 时间（全部是"主函数周期数"，见文件头表格） ---- */
		.ImmediateNmCycleTime = CANNM_CONVERT_MS_TO_MAIN_CYCLES(20u),
		.MsgCycleOffset       = CANNM_CONVERT_MS_TO_MAIN_CYCLES(0u),   /* 0 = 下一拍就发 */
		.MsgCycleTime         = CANNM_CONVERT_MS_TO_MAIN_CYCLES(200u),
		.MsgReducedTime       = CANNM_CONVERT_MS_TO_MAIN_CYCLES(100u),
		.MsgTimeoutTime       = CANNM_CONVERT_MS_TO_MAIN_CYCLES(500u),
		.RepeatMessageTime    = CANNM_CONVERT_MS_TO_MAIN_CYCLES(800u),
		.NmTimeoutTime        = CANNM_CONVERT_MS_TO_MAIN_CYCLES(2000u),
		.WaitBusSleepTime     = CANNM_CONVERT_MS_TO_MAIN_CYCLES(2000u),

		/* ---- PDU ---- */
		.TxPdu                = (PduIdType)CANIF_TX_NM,

		/* ---- 身份 ---- */
		.NodeId               = CANNMCFG_NODE_ID,
		.nmNetworkHandle      = (NetworkHandleType)0u,

		/* ---- 行为开关 ---- */
		/**
		 * @brief 立即发送次数
		 * @note  这里是 **0**，即"不连发"，进入 `RepeatMessage` 后直接按
		 *        `MsgCycleTime` 走。量产通常配 3~10 次（快速唤醒整车网络），
		 *        但连发会让验收脚本的帧计数难以预测（首秒帧数 = 连发数 + 周期帧数），
		 *        所以验证阶段先关掉。打开只需把这个值改成 3。
		 */
		.ImmediateNmTransmissions = 0u,

		/**
		 * @brief CBV（控制位向量）在报文中的字节位置
		 * @note  1 = 第 2 字节。`CANNM_PDU_BYTE_0` 表示放在第 1 字节。
		 *        CBV 与 NID **不能占同一字节**，否则互相覆盖。
		 */
		.PduCbvPosition = CANNM_PDU_BYTE_1,

		/** @brief NID（节点号）位置：第 1 字节 */
		.PduNidPosition = CANNM_PDU_BYTE_0,

		/**
		 * @brief 主动唤醒位置位
		 * @note  开：本机主动请求网络时把 CBV 的 bit4（`0x10`）置上，
		 *        告诉总线上其它节点"这次是我叫醒的"。
		 */
		.ActiveWakeupBitEnabled = TRUE,

		/**
		 * @brief 被动模式
		 * @warning 必须 `FALSE`。被动模式下本机**永不主动发送** NM 报文，
		 *          只能被动响应别人。设成 TRUE 的现象是"`!a` 之后一帧 0x500 都没有"，
		 *          极难和"发送配置错了"区分开。
		 */
		.PassiveModeEnabled = FALSE,

		/** @brief 收到别人的 RepeatMessage 请求时上报 Nm（`Nm_RepeatMessageIndication`） */
		.RepeatMsgIndEnabled = TRUE,

		/** @brief 节点检测：从收到的 NM 报文里识别对端节点号 */
		.NodeDetectionEnabled = TRUE,
	},
};

/* ============================ [ 运行期上下文 ] ============================ */

/**
 * @brief 通道运行期状态（非 const，CanNm 会写）
 * @note  静态零初始化即可：`CanNm_Init()` 会把 `state` 设成 `NM_STATE_BUS_SLEEP`
 *        并清所有定时器。**不要**用 `memset` 之外的"聪明"初值，
 *        状态机第一次进 `CanNm_MainFunction` 时依赖的正是"全零 = 未开始"这个前提。
 */
static CanNm_ChannelContextType CanNm_ChannelContexts[1];

/* ============================ [ 总表 ] ============================ */

const CanNm_ConfigType CanNm_Config = {
	CanNm_ChannelConfigs,
	CanNm_ChannelContexts,
	(uint8_t)ARRAY_SIZE(CanNm_ChannelConfigs),
};
