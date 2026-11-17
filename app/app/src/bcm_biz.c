/**
 * @file    bcm_biz.c
 * @brief   业务骨架的实现（A9）：驻车制动 → 制动灯
 *
 * @details @section BIZC_RULES 决策规则（这张表就是"业务"的全部）
 *
 *          | 输入有效性 | 值 | 输出（制动灯） | 健康状态 | 为什么 |
 *          |---|---|---|---|---|
 *          | `NEVER_RECEIVED` | — | OFF | `INIT` | 别人还没开机，不能当成"没踩手刹" |
 *          | `TIMEOUT`（< 去抖） | — | **保持** | 上次的 | 偶发丢帧不该让灯闪 |
 *          | `TIMEOUT`（≥ 去抖） | — | OFF | `LOST` | 灯亮着但没人知道状态，是错的 |
 *          | `INVALID` | — | **保持** | `INVALID` | 对方说"这个值不可用"，不是"值是 0" |
 *          | `VALID` | `ON` | ON | `OK` | — |
 *          | `VALID` | `OFF` | OFF | `OK` | — |
 *          | `VALID` | `FAULT` | OFF | `PEER_ERROR` | 对方报故障，先关（安全侧） |
 *
 *          @section BIZC_DEBOUNCE 为什么 TIMEOUT 要去抖
 *
 *          车身总线上一次仲裁拥塞、一次 FEE 擦除抖动就可能连丢两帧。
 *          不去抖的话，制动灯会在正常工况下偶发闪一下 —— 这在实车上
 *          会被当成"电路接触不良"，排查成本极高。
 *
 *          去抖值取 **3 s**：`CCVS` 周期 100 ms，3 s 等于连丢 30 帧，
 *          只有真掉线才会到这个量级。去抖期间输出**保持**，不关灯。
 *
 * @note    @section BIZC_WHYHOLD `INVALID` 为什么保持而不是关灯
 *
 *          "值不可用"不代表"值是 0"。若把 `INVALID` 当 OFF 处理，
 *          对方短暂无效时制动灯会灭 —— 而制动灯灭是**其他车看到的信号**，
 *          不该因为我们这边读不懂就改变。保持上一次的结论更安全。
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "bcm_biz.h"
#include "bcm_sig.h"

#include "platform.h"           /* Platform_NowMs：去抖计时（芯片无关，Host 也编这一份） */

/* ============================ [ 常量 ] ============================ */

/**
 * @brief 通信丢失去抖时间（ms）
 * @note  见文件头 @ref BIZC_DEBOUNCE。3 s = 30 个 CCVS 周期。
 */
#define BIZ_LOST_DEBOUNCE_MS    (3000u)

/* ============================ [ 状态 ] ============================ */

/** @brief 当前健康状态 */
static Bcm_BizHealthType s_health = BCM_BIZ_INIT;

/**
 * @brief 输入"开始不可信"的时刻（ms）
 * @note  只在 `TIMEOUT` 期间有意义：进入 TIMEOUT 时记一次，恢复有效时清零。
 *        用 `boolean` 标志而不是拿 0 当"没在计时" —— 上电后第 0 ms
 *        进入 TIMEOUT 的话，0 会被当成"没在计时"。
 */
static uint32_t s_lostSince;
static boolean s_lostTiming = FALSE;

/** @brief 是否接管输出（上电默认关，理由见 bcm_biz.h 的 BcmBiz_SetEnabled） */
static boolean s_enabled = FALSE;

/* ============================ [ 接口实现 ] ============================ */

void BcmBiz_Init(void)
{
	s_health = BCM_BIZ_INIT;
	s_lostSince = 0u;
	s_lostTiming = FALSE;
	s_enabled = FALSE;
}

void BcmBiz_MainFunction(void)
{
	Bcm_SwStateType st = BCM_SW_STATE_UNKNOWN;
	Bcm_SigValidityType v;
	boolean lampOn = FALSE;
	boolean hold = FALSE;

	if (FALSE == s_enabled)
	{
		return;   /* 没接管：不读输入、不写输出，把信号完全让给手工命令 */
	}

	v = BcmSig_RxRead(BCM_SIG_RX_PARK_BRAKE, &st);

	switch (v)
	{
	case BCM_SIG_VALID:
		s_lostTiming = FALSE;
		if (BCM_SW_STATE_ON == st)
		{
			lampOn = TRUE;
			s_health = BCM_BIZ_OK;
		}
		else if (BCM_SW_STATE_OFF == st)
		{
			lampOn = FALSE;
			s_health = BCM_BIZ_OK;
		}
		else
		{
			/* VALID 但值是 FAULT（对方报错）：关输出，安全侧 */
			lampOn = FALSE;
			s_health = BCM_BIZ_PEER_ERROR;
		}
		break;

	case BCM_SIG_INVALID:
		/* 见 @ref BIZC_WHYHOLD：保持上一次的输出 */
		hold = TRUE;
		s_health = BCM_BIZ_INVALID;
		break;

	case BCM_SIG_TIMEOUT:
		if (FALSE == s_lostTiming)
		{
			s_lostTiming = TRUE;
			s_lostSince = Platform_NowMs();
		}

		if ((uint32_t)(Platform_NowMs() - s_lostSince) >= BIZ_LOST_DEBOUNCE_MS)
		{
			lampOn = FALSE;
			s_health = BCM_BIZ_LOST;
		}
		else
		{
			hold = TRUE;   /* 去抖期内：灯保持，健康状态也不改 */
		}
		break;

	case BCM_SIG_NEVER_RECEIVED:
	default:
		s_lostTiming = FALSE;
		lampOn = FALSE;
		s_health = BCM_BIZ_INIT;
		break;
	}

	if (FALSE == hold)
	{
		(void)BcmSig_TxSet(BCM_SIG_BRAKE,
		                   (TRUE == lampOn) ? BCM_SW_STATE_ON : BCM_SW_STATE_OFF);
	}
}

Bcm_BizHealthType BcmBiz_BrakeHealth(void)
{
	return s_health;
}

void BcmBiz_SetEnabled(boolean on)
{
	if (on != s_enabled)
	{
		/* 切换时把去抖状态清掉：从"没接管"进入"接管"不该继承
		 * 上一轮的丢失计时，否则打开的第一拍就可能直接判 LOST。 */
		s_lostTiming = FALSE;
		s_health = BCM_BIZ_INIT;
		s_enabled = on;
	}
}

boolean BcmBiz_IsEnabled(void)
{
	return s_enabled;
}

const char *BcmBiz_HealthName(Bcm_BizHealthType h)
{
	static const char *const s_names[] = {
		"INIT", "OK", "INVALID", "PEER_ERROR", "LOST"
	};

	return ((uint32_t)h <= (uint32_t)BCM_BIZ_LOST) ? s_names[h] : "?";
}
