/**
 * @file    test_bcm.c
 * @brief   Host 上的业务用例：BcmSig 四态 + BcmBiz 去抖
 *
 * @details @section HOSTTEST_WHAT 这个用例证明什么
 *
 *          它不证明"协议栈对"，只证明**业务语义在可控时间下是对的**：
 *
 *          | 用例 | 期望 |
 *          |------|------|
 *          | 上电未收到任何帧 | `NEVER_RECEIVED`，不是 `OFF` |
 *          | 收到 raw=1 | `VALID` + `ON` |
 *          | 收到 raw=3（对方说无效） | `INVALID`，且业务保持上一次输出 |
 *          | 300 ms 内没有新帧 | `TIMEOUT` |
 *          | 丢失 1 s | 制动灯保持（去抖窗口内） |
 *          | 丢失 3.5 s | 制动灯熄灭（判 LOST） |
 *
 *          @note 关键点在"时间由测试推进"：目标板上验一次去抖要真等 3.5 s，
 *          这里 0 秒跑完。反过来说，**Host 通过不代表时序精度合格**——
 *          抖动、ISR 延迟只能上板测。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版：6 组断言 |
 */

#include <stdio.h>

#include "bcm_sig.h"
#include "bcm_biz.h"
#include "rx_mon.h"
#include "com_stub.h"
#include "Com_Cfg.h"      /* COM_SID_xxx：与目标板同一份生成配置，避免测试自己编信号号 */
#include "platform_host.h"
#include "CanIf_Cfg.h"

/* ============================ [ 断言框架 ] ============================ */

static int s_pass = 0;
static int s_fail = 0;

/**
 * @brief 一条断言
 * @param[in] cond 条件
 * @param[in] what 描述
 */
static void check(int cond, const char *what)
{
	if (0 != cond)
	{
		s_pass++;
		(void)printf("  PASS  %s\n", what);
	}
	else
	{
		s_fail++;
		(void)printf("  FAIL  %s\n", what);
	}
}

/* ============================ [ 用例辅助 ] ============================ */

/**
 * @brief 模拟"总线上来了一帧 CCVS，手刹 = raw"
 *
 * @details 目标板上这两件事分别发生在：CanIf 回调里 `RxMon_OnRx()`、
 *          Com 解包后 `Com_ReceiveSignal()` 读到新值。Host 上由这里
 *          一次做完——**顺序与目标板一致**：先到，后读。
 */
static void inject_park_brake(uint8_t raw)
{
	HostCom_SetRx((Com_SignalIdType)COM_SID_ParkingBrakeSwitch, raw);
	RxMon_OnRx((PduIdType)CANIF_RX_CAN1_CCVS);
}

/**
 * @brief 跑一个业务拍（顺序与 main.c 一致）
 */
static void run_beat(void)
{
	BcmSig_MainFunction();
	BcmBiz_MainFunction();
}

/**
 * @brief 推进时间并跑拍
 */
static void elapse(uint32_t ms)
{
	Host_AdvanceMs(ms);
	run_beat();
}

/* ============================== [ 用例 ] ============================== */

int main(void)
{
	Bcm_SwStateType st = BCM_SW_STATE_UNKNOWN;
	Bcm_SigValidityType v;

	(void)printf("== like_as host test: BcmSig / BcmBiz ==\n");

	/* ---------- 1. 上电：TX 初值为 OFF，RX 为 NEVER ---------- */
	Host_ResetClock();
	HostCom_Reset();
	RxMon_Init();
	BcmSig_Init();
	BcmBiz_Init();

	check(HostCom_GetTx((Com_SignalIdType)COM_SID_BrakelightST) == 0u,
	      "上电：制动灯 raw = 0 (OFF)，不产生总线跳变");

	v = BcmSig_RxRead(BCM_SIG_RX_PARK_BRAKE, &st);
	check(v == BCM_SIG_NEVER_RECEIVED,
	      "上电：未收到任何帧 → NEVER_RECEIVED（不是 OFF）");

	/* ---------- 2. 收到有效 ON ---------- */
	inject_park_brake(1u);
	run_beat();
	v = BcmSig_RxRead(BCM_SIG_RX_PARK_BRAKE, &st);
	check((v == BCM_SIG_VALID) && (st == BCM_SW_STATE_ON),
	      "raw=1 → VALID + ON");

	/* ---------- 3. 收到 raw=3（对方说无效） ---------- */
	inject_park_brake(3u);
	run_beat();
	v = BcmSig_RxRead(BCM_SIG_RX_PARK_BRAKE, &st);
	check((v == BCM_SIG_INVALID) && (st == BCM_SW_STATE_UNKNOWN),
	      "raw=3 → INVALID + UNKNOWN（值不可用）");

	/* ---------- 4. 300 ms 无新帧 → TIMEOUT ---------- */
	inject_park_brake(1u);
	elapse(100u);
	v = BcmSig_RxRead(BCM_SIG_RX_PARK_BRAKE, &st);
	check(v == BCM_SIG_VALID, "100 ms 内 → 仍 VALID");

	elapse(400u);
	v = BcmSig_RxRead(BCM_SIG_RX_PARK_BRAKE, &st);
	check(v == BCM_SIG_TIMEOUT, "超过 300 ms 无新帧 → TIMEOUT");

	/* ---------- 5. BcmBiz：写影子 vs 写 Com 差一拍 ---------- */
	inject_park_brake(1u);
	BcmBiz_SetEnabled(TRUE);
	run_beat();

	/* 这一拍里 BcmSig_MainFunction 先跑（写的是上一拍的影子），
	 * BcmBiz 后跑（只改影子）。所以 Com 里的值仍然是 0。
	 * 这不是 bug，是**契约**：`BcmSig_TxSet()` 只改影子，
	 * 真正落到 Com 在下一拍 —— 测试必须把这个延迟显式断言出来，
	 * 否则"晚一拍"这种缺陷会被"等两拍"的断言掩盖。 */
	check(HostCom_GetTx((Com_SignalIdType)COM_SID_BrakelightST) == 0u,
	      "BcmSig_TxSet 只改影子：同一拍内 Com 尚未更新");

	run_beat();   /* 下一拍：BcmSig_MainFunction 把影子写进 Com */
	check(HostCom_GetTx((Com_SignalIdType)COM_SID_BrakelightST) == 1u,
	      "下一拍：手刹 ON → 制动灯 raw = 1");

	elapse(1000u);   /* 已超输入超时 300 ms，但未到 3 s 去抖 */
	check(HostCom_GetTx((Com_SignalIdType)COM_SID_BrakelightST) == 1u,
	      "丢失 1 s（去抖窗口内）→ 制动灯保持");
	check(BcmBiz_BrakeHealth() != BCM_BIZ_LOST,
	      "丢失 1 s → health 尚未判 LOST");

	/* ---------- 6. 超过 3 s → 关灯 ---------- */
	elapse(3000u);   /* 判 LOST、置影子 OFF */
	elapse(0u);      /* 再一拍把 OFF 落进 Com（与上面同一条契约） */
	check(HostCom_GetTx((Com_SignalIdType)COM_SID_BrakelightST) == 0u,
	      "丢失 4 s → 制动灯熄灭");
	check(BcmBiz_BrakeHealth() == BCM_BIZ_LOST,
	      "丢失 4 s → health = LOST");

	/* ---------- 7. 恢复：再来有效 ON ---------- */
	inject_park_brake(1u);
	run_beat();
	elapse(0u);
	check(HostCom_GetTx((Com_SignalIdType)COM_SID_BrakelightST) == 1u,
	      "输入恢复 → 制动灯重新点亮");
	check(BcmBiz_BrakeHealth() == BCM_BIZ_OK,
	      "输入恢复 → health = OK");

	(void)printf("-- %d passed, %d failed\n", s_pass, s_fail);

	return (0 == s_fail) ? 0 : 1;
}
