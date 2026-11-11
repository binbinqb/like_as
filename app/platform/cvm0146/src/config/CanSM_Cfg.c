/**
 * @file    CanSM_Cfg.c
 * @brief   CanSM 的网络配置（CAN0，bor-off 两级恢复）
 *
 * @details @section CANSMCFG_C_WHY 为什么现在才接 CanSM
 *
 *          M5 时试过"bus-off 后软件重启控制器（STOPPED→STARTED）"，
 *          实测**控制器会永久静默**，于是当时的结论是"这条路走不通"，
 *          把相关代码删掉了，恢复完全交给硬件的 `BOFFREC`。
 *
 *          M10 接 Com 时那个现象**必现**了，才查到根因：
 *          `FlexCanDrv_GetDefaultCfg()` 漏初始化 `selected3bitSampling`，
 *          第二次 Configure 拿到栈垃圾 → `CTRL1.SMP` 翻转 → 采样点错位。
 *          在取默认值前 `memset(&cfg, 0, sizeof(cfg))` 之后就正常了。
 *
 *          所以 **CanSM 的软件恢复路径现在才真正可用**。这不是"新功能"，
 *          是补上当初因为一个 SDK 缺陷而被迫放弃的能力。
 *
 *          @section CANSMCFG_C_BOR bus-off 两级恢复怎么工作
 *
 *          @code
 *          bus-off 中断 → CanIf_ControllerBusOff → CanSM_ControllerBusOff
 *                ↓
 *          等 BorTimeL1(100 ms) → 重启控制器（STOPPED→STARTED）
 *                ↓ 成功？
 *             是 → 回到 FULLCOM，BusOffCounter = 0
 *             否 → BusOffCounter++，若 ≤ BorCounterL1ToL2(3) 继续用 L1
 *                  超过则改用 BorTimeL2(1000 ms) 重试
 *          @endcode
 *
 *          L1/L2 的区别是**退避时间**：短时间内反复 bus-off 说明是硬故障
 *          （线束短路），快速重试只会让错误计数暴涨、把 CPU 拖住；
 *          拉长到 L2 能让总线安静下来，也给故障诊断留出上报窗口。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：CAN0 单网络，L1 100ms / L2 1000ms / 3 次升级 |
 */

#include "CanSM.h"
#include "CanSM_Cfg.h"
#include "CanSM_Priv.h"

/* ============================ [ 网络配置 ] ============================ */

static const CanSM_NetworkConfigType CanSM_NetworkConfigs[] = {
	{
		/** @brief 用户自定义的 bus-off 退避时间回调；NULL = 用固定 BorTime */
		.UserGetBusOffDelayFnc    = NULL,

		/**
		 * @brief L1（快速恢复）等待时间
		 * @note  100 ms 足够覆盖 FlexCAN "128×11 个隐性位"的自动恢复窗口
		 *        （500 kbps 下约 2.8 ms），又不会让正常的总线抖动
		 *        拖太久才重发。M5 实测硬件自动恢复通常在几十毫秒内完成。
		 */
		.BorTimeL1                = CANSM_CONVERT_MS_TO_MAIN_CYCLES(100u),

		/** @brief L2（慢速恢复）等待时间：连续失败后拉长到 1 s */
		.BorTimeL2                = CANSM_CONVERT_MS_TO_MAIN_CYCLES(1000u),

		/**
		 * @brief 重启后等"发送已确保"的时间
		 * @note  重启控制器后要等一段时间再允许发送，否则第一帧可能在
		 *        控制器还没稳定出总线时发出去，直接又触发一次错误。
		 */
		.BorTimeTxEnsured         = CANSM_CONVERT_MS_TO_MAIN_CYCLES(50u),

		/** @brief Tx 超时恢复窗口 */
		.TxRecoveryTime           = CANSM_CONVERT_MS_TO_MAIN_CYCLES(100u),

		/** @brief 连续 bus-off 超过这个次数就从 L1 升级到 L2 */
		.BorCounterL1ToL2         = 3u,

		/** @brief 控制器号：CAN0 */
		.ControllerId             = 0u,

		/** @brief 收发器号：CAN0（本工程收发器由 GPIO STB 控制，见 CanAc） */
		.TransceiverId            = 0u,

		/** @brief 上报给 ComM 的通道号，与 `ComM_Cfg.c` 的 smHandle 对应 */
		.ComMHandle               = 0u,

		/** @brief 不用"轮询 Tx 确认"的方式判断恢复完成（没有对应实现） */
		.BorTxConfirmationPolling = FALSE,

		/** @brief 收发器不支持部分网络（PN） */
		.CanTrcvPnEnabled         = FALSE,
	},
};

/* ============================ [ 运行期上下文 ] ============================ */

static CanSM_ChannelContextType CanSm_ChannelContexts[ARRAY_SIZE(CanSM_NetworkConfigs)];

/* ============================ [ 总表 ] ============================ */

const CanSM_ConfigType CanSM_Config = {
	.networks              = CanSM_NetworkConfigs,
	.contexts              = CanSm_ChannelContexts,
	.numOfNetworks         = (uint8_t)ARRAY_SIZE(CanSM_NetworkConfigs),
	/**
	 * @brief 模式请求重发次数上限
	 * @note  CanSM 向 CanIf 请求控制器模式，若 CanIf 没在
	 *        `RequestRepetitionTime` 内完成，CanSM 会重发，最多这么多次。
	 *        取 2：我们的 CanIf 是同步返回的（直接调驱动），
	 *        正常情况下一次就成功；给 2 次是防驱动返回 BUSY。
	 */
	.ModeRequestRepetitionMax = 2u,
	.RequestRepetitionTime    = CANSM_CONVERT_MS_TO_MAIN_CYCLES(100u),
};
