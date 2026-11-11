/**
 * @file    ComM_Cfg.c
 * @brief   ComM 的通道表与用户表（1 通道 + 1 用户）
 *
 * @details @section COMMCFG_C_CHAIN 这张表决定了标准通信链路怎么串起来
 *
 *          @code
 *          ComM_RequestComMode(USER_APP, FULL_COMMUNICATION)
 *                    │
 *          ComM 通道 0 仲裁（所有用户都同意才降级/升级）
 *                    │
 *          ┌─────────┴──────────┐
 *          │ NmVariant = FULL   │ busType = CAN
 *          ↓                    ↓
 *        Nm_NetworkRequest   CanSM_RequestComMode
 *          ↓                    ↓
 *       CanNm（NM 报文）    CanIf → Can（控制器启停）
 *          │
 *      Com_IpduGroupStart（本表 ComIpduGroupIds）
 *          @endcode
 *
 *          **两条支路缺一不可**：
 *          - 只接 Nm：NM 报文在发，但控制器没启动（PDU 还是 OFFLINE），一帧也出不去；
 *          - 只接 CanSM：控制器在跑，但 NM 不知道网络该醒，Com 分组也不会启动。
 *
 *          @section COMMCFG_C_GROUPS ComIpduGroupIds 是 ComM 的"总开关"
 *
 *          `ComM_Nm_NetworkMode()` 会对这里列出的每个分组调
 *          `Com_IpduGroupStart(id, TRUE)`，`ComM_Nm_PrepareBusSleepMode()`
 *          调 `Com_IpduGroupStop(id)`。
 *
 *          也就是说 **Com 的收发是跟着 NM 状态自动开关的**，
 *          应用不需要自己调 `Com_IpduGroupStart`。
 *          本工程的 `!y` 命令仍然可以手动停组 —— 那是验收用的旁路，
 *          注意 NM 一旦重新进 NetworkMode，ComM 会把组又打开。
 *
 *          @warning 这里填的是 **Com 的 I-PDU 分组号**（`COM_GROUP_TEST` = 0），
 *                   不是 CanIf 的 PDU 号。两套编号不同，填错不会报错，
 *                   只会表现为"NM 起来了但信号报文不动"。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：CAN0 单通道，NM 全功能变体，挂 Com 分组 0 |
 */

#include "ComM.h"
#include "ComM_Cfg.h"
#include "ComM_Priv.h"

#include "Com_Cfg.h"     /* COM_GROUP_TEST：Com 的 I-PDU 分组号 */
#include "Nm_Cfg.h"      /* NM_CFG_CHANNEL_CAN0：Nm 通道号 */

/* ============================ [ 通道 0 的用户表 ] ============================ */

/** @brief 通道 0 上有哪些用户（当前只有应用） */
static const uint8_t ComM_Chl0Users[] = {
	(uint8_t)COMM_USER_APP,
};

/**
 * @brief 通道 0 管理的 Com I-PDU 分组
 * @note  只挂组 0（测试信号报文）。将来加真实信号报文时，
 *        如果它们和测试报文在同一个组里，这里不用改；
 *        如果分了新组，要在这里加一行。
 */
static const Com_IpduGroupIdType Com_Chl0IpduGroupIds[] = {
	(Com_IpduGroupIdType)COM_GROUP_TEST,
};

/* ============================ [ 通道配置 ] ============================ */

static const ComM_ChannelConfigType ComM_ChannelConfigs[] = {
	{
		.users               = ComM_Chl0Users,
		.ComIpduGroupIds     = Com_Chl0IpduGroupIds,
		/** @brief 传给 CanSM 的网络句柄（`CanSM_NetworkConfigs[]` 的下标） */
		.smHandle            = 0u,
		/** @brief 总线类型：CAN。决定 `ComM_BusSM_RequestMode` 走 CanSM 的哪个分支 */
		.busType             = COMM_BUS_TYPE_CAN,
		.numOfUsers          = (uint8_t)ARRAY_SIZE(ComM_Chl0Users),
		.numOfComIpduGroups  = (uint8_t)ARRAY_SIZE(Com_Chl0IpduGroupIds),
		/**
		 * @brief NM 变体：FULL
		 * @note  FULL    = 有完整 NM，由 NM 决定网络何时睡眠（本工程）
		 *        PASSIVE = 只能被动启动，不主动请求
		 *        LIGHT   = 没有 NM，靠 ComM 自己的定时器维持（需 `COMM_USE_VARIANT_LIGHT`）
		 *        NONE    = 没有 NM，ComM 直接控制 CanSM
		 */
		.NmVariant           = COMM_NM_VARIANT_FULL,
		/** @brief 传给 `Nm_*()` 的通道号，与 `Nm_Cfg.c` 的 handle 对应 */
		.nmHandle            = (NetworkHandleType)NM_CFG_CHANNEL_CAN0,
	},
};

/* ============================ [ 用户配置 ] ============================ */

/** @brief 用户 0（应用）关心哪些通道 */
static const uint8_t ComM_User0Channels[] = {
	(uint8_t)COMM_CHANNEL_CAN0,
};

static const ComM_UserConfigType ComM_UserConfigs[] = {
	{
		.channels     = ComM_User0Channels,
		.numOfChannels = (uint8_t)ARRAY_SIZE(ComM_User0Channels),
	},
};

/* ============================ [ 运行期上下文 ] ============================ */

/*
 * 这两组必须是非 const 的 RAM：ComM 会写 requestMode / state / nmFlag。
 * 静态零初始化即可 —— `ComM_Init()` 会把它们全部重置。
 */
static ComM_ChannelContextType ComM_ChannelContexts[ARRAY_SIZE(ComM_ChannelConfigs)];
static ComM_UserContextType    ComM_UserContexts[ARRAY_SIZE(ComM_UserConfigs)];

/* ============================ [ 总表 ] ============================ */

const ComM_ConfigType ComM_Config = {
	.channelConfigs = ComM_ChannelConfigs,
	.channelContexts = ComM_ChannelContexts,
	.userConfigs    = ComM_UserConfigs,
	.userContexts   = ComM_UserContexts,
	.numOfChannels  = (uint8_t)ARRAY_SIZE(ComM_ChannelConfigs),
	.numOfUsers     = (uint8_t)ARRAY_SIZE(ComM_UserConfigs),
};
