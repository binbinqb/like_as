/**
 * @file    led_biz.c
 * @brief   LED 业务状态机（10.6 闭环）：启动/停止/闪烁/超时/无效命令
 *
 * @details 状态只有两个：`s_blinking` 与 `s_phaseOn`，加上三个计时/故障量。
 *          刻意不做通用状态机框架 —— 一个 40 行的 `switch` 都嫌多，
 *          用 if 写清楚比抽象更重要（下一个接手的人要能一眼看完）。
 *
 *          @section LEDBIZ_ORDER 与调度表顺序的关系
 *
 *          在 `Board.json` 的 `rte.schedule` 里本模块排在 `BcmSig` 之后
 *          （BcmSig → BcmBiz → LedBiz → ComApp → …）：
 *          - 读：本拍 `BcmSig_MainFunction()` 刚刷新的输入影子；
 *          - 写：`Rte_Write()` 写进影子，下一拍由 `BcmSig` 下发进 Com，
 *            再由 Com 的 100 ms 周期发出。
 *          整条"收到命令 → 动作"的延迟因此是 1 个 10 ms 拍，可接受。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-20 | binbina | 首版：启动/停止/闪烁/超时/无效命令 |
 */

#include "led_biz.h"

#include "rte.h"

/* ============================ [ 常量 ] ============================ */

/** @brief 调度拍周期（ms）：与 `Board.json` 的 period_ms 一致 */
#define LEDBIZ_TICK_MS          (10u)

/** @brief 闪烁半周期（ms）：亮 500 / 灭 500 */
#define LEDBIZ_BLINK_HALF_MS    (500u)

/** @brief 通信超时门限（ms）：500 ms 无有效命令即停止 */
#define LEDBIZ_TIMEOUT_MS       (500u)

/** @brief 半周期对应的拍数 */
#define LEDBIZ_BLINK_HALF_TICKS (LEDBIZ_BLINK_HALF_MS / LEDBIZ_TICK_MS)

/** @brief 超时门限对应的拍数 */
#define LEDBIZ_TIMEOUT_TICKS    (LEDBIZ_TIMEOUT_MS / LEDBIZ_TICK_MS)

/* ============================ [ 状态 ] ============================ */

static boolean s_cmdSeen;        /**< 上电至今是否收到过有效命令 */
static boolean s_blinking;       /**< 是否处于闪烁模式 */
static boolean s_phaseOn;        /**< 闪烁相位：TRUE = 亮相 */
static uint16_t s_phaseTicks;    /**< 当前相位已持续的拍数 */
static uint16_t s_sinceValidTicks; /**< 距最后一次**有效**命令的拍数（饱和） */
static boolean s_faultTimeout;   /**< 通信超时故障位 */
static boolean s_faultCmd;       /**< 无效命令故障位 */
static boolean s_ledCommitted;   /**< 最近一次**成功提交**给驱动的 LED 状态 */

/* ============================ [ 内部 ] ============================ */

/**
 * @brief 停止闪烁并熄灭（超时/停止命令共用）
 */
static void LedBiz_Stop(void)
{
	s_blinking = FALSE;
	s_phaseOn = FALSE;
	s_phaseTicks = 0u;
}

/* ============================ [ 接口 ] ============================ */

void LedBiz_Init(void)
{
	s_cmdSeen = FALSE;
	s_blinking = FALSE;
	s_phaseOn = FALSE;
	s_phaseTicks = 0u;
	s_sinceValidTicks = 0u;
	s_faultTimeout = FALSE;
	s_faultCmd = FALSE;
	s_ledCommitted = FALSE;

	/* 上电安全态：灯灭、模式=尚未收到命令（RTE_SWITCH_INVALID → raw 3）、
	 * 相位灭、两个故障位清零。写失败不阻断启动（Host 上直连 DOUT 会失败）。 */
	(void)Rte_Write(RTE_PORT_LED_R, RTE_SWITCH_OFF);
	(void)Rte_Write(RTE_PORT_LED_RUN_MODE, RTE_SWITCH_INVALID);
	(void)Rte_Write(RTE_PORT_LED_OUT, RTE_SWITCH_OFF);
	(void)Rte_Write(RTE_PORT_LED_PHASE, RTE_SWITCH_OFF);
	(void)Rte_Write(RTE_PORT_LED_FAULT_TIMEOUT, RTE_SWITCH_OFF);
	(void)Rte_Write(RTE_PORT_LED_FAULT_CMD, RTE_SWITCH_OFF);
}

void LedBiz_MainFunction(void)
{
	Rte_SwitchType cmd = RTE_SWITCH_INVALID;
	Rte_StatusType st;
	boolean validCmd;

	st = Rte_Read(RTE_PORT_LED_CTRL, &cmd);

	/* 有效命令 = 端口可读且值是 ON/OFF。raw 2/3 映射成 ERROR/INVALID，
	 * 属于"对方说了话，但不是有效命令"，不刷新超时计时。 */
	validCmd = (boolean)((RTE_E_OK == st) &&
	                     ((RTE_SWITCH_ON == cmd) || (RTE_SWITCH_OFF == cmd)));

	if (TRUE == validCmd)
	{
		s_sinceValidTicks = 0u;
		s_faultCmd = FALSE;
		s_faultTimeout = FALSE;   /* 有效命令即视为通信恢复，清超时故障 */

		if (FALSE == s_cmdSeen)
		{
			s_cmdSeen = TRUE;
		}

		if (RTE_SWITCH_ON == cmd)
		{
			if (FALSE == s_blinking)
			{
				/* 启动瞬间从"亮相"开始：验收要求能立刻看到灯亮 */
				s_blinking = TRUE;
				s_phaseOn = TRUE;
				s_phaseTicks = 0u;
			}
		}
		else
		{
			LedBiz_Stop();
		}
	}
	else
	{
		/* 值无效（raw 2 → ERROR，raw 3 → E_INVALID）→ 记录故障位，不改输出。
		 * 注意 `Rte_Read` 对 "对方报 FAULT" 返回的是 E_OK + ERROR，不是
		 * E_INVALID —— 只看返回值会把"对方明确报无效"漏掉。 */
		if ((RTE_E_INVALID == st) ||
		    ((RTE_E_OK == st) &&
		     ((RTE_SWITCH_ERROR == cmd) || (RTE_SWITCH_INVALID == cmd))))
		{
			s_faultCmd = TRUE;
		}

		/* 超时按"有效命令"计时：帧再新鲜，只要值无效/类型不符就不算数 */
		if (s_sinceValidTicks < LEDBIZ_TIMEOUT_TICKS)
		{
			s_sinceValidTicks++;
		}

		if ((s_sinceValidTicks >= LEDBIZ_TIMEOUT_TICKS) && (TRUE == s_cmdSeen))
		{
			if ((TRUE == s_blinking) || (TRUE == s_phaseOn))
			{
				LedBiz_Stop();
			}
			s_faultTimeout = TRUE;
		}
	}

	/* 闪烁推进：非阻塞，靠拍计数 */
	if (TRUE == s_blinking)
	{
		s_phaseTicks++;
		if (s_phaseTicks >= LEDBIZ_BLINK_HALF_TICKS)
		{
			s_phaseTicks = 0u;
			s_phaseOn = (boolean)((TRUE == s_phaseOn) ? FALSE : TRUE);
		}
	}

	/* 输出：只有驱动**成功提交**才更新 LED_OUT 的语义（无电气反馈） */
	{
		boolean ledOn = (boolean)((TRUE == s_blinking) && (TRUE == s_phaseOn));

		if (E_OK == Rte_Write(RTE_PORT_LED_R,
		                      (TRUE == ledOn) ? RTE_SWITCH_ON : RTE_SWITCH_OFF))
		{
			s_ledCommitted = ledOn;
		}
	}

	/* 上报：模式 / 输出 / 相位 / 两个故障位 */
	if (FALSE == s_cmdSeen)
	{
		(void)Rte_Write(RTE_PORT_LED_RUN_MODE, RTE_SWITCH_INVALID); /* raw 3 = 尚未收到命令 */
	}
	else
	{
		(void)Rte_Write(RTE_PORT_LED_RUN_MODE,
		                (TRUE == s_blinking) ? RTE_SWITCH_ON : RTE_SWITCH_OFF);
	}

	(void)Rte_Write(RTE_PORT_LED_OUT,
	                (TRUE == s_ledCommitted) ? RTE_SWITCH_ON : RTE_SWITCH_OFF);
	(void)Rte_Write(RTE_PORT_LED_PHASE,
	                (TRUE == s_phaseOn) ? RTE_SWITCH_ON : RTE_SWITCH_OFF);
	(void)Rte_Write(RTE_PORT_LED_FAULT_TIMEOUT,
	                (TRUE == s_faultTimeout) ? RTE_SWITCH_ON : RTE_SWITCH_OFF);
	(void)Rte_Write(RTE_PORT_LED_FAULT_CMD,
	                (TRUE == s_faultCmd) ? RTE_SWITCH_ON : RTE_SWITCH_OFF);
}
