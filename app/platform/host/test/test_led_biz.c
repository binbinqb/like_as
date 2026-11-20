/**
 * @file    test_led_biz.c
 * @brief   Host 用例：LED 闭环业务（10.6）—— 启动/停止/闪烁/超时/无效/恢复
 *
 * @details 编译进 `led_biz` 套件：真实 `led_biz.c` + `bcm_sig.c` + `rte.c`
 *          + IoHwAb Host 替身 + Com 替身。驱动方式与板上一致：
 *
 *          ```
 *          HostCom_SetRx(COM_SID_ParkingBrakeSwitch, raw)   模拟总线值
 *          RxMon_OnRx(CANIF_RX_CAN1_CCVS)                   模拟帧到达
 *          Host_AdvanceMs(10)                               推进虚拟时间
 *          BcmSig_MainFunction()                            绑定层刷新
 *          LedBiz_MainFunction()                            业务一拍
 *          ```
 *
 *          @warning `LED_R` 在板上是 `source=direct`，Host 的 GpioDoutOps 是
 *          空桩（返回 E_NOT_OK）。因此本用例**不**断言 `LED_OUT` 跟随亮灭，
 *          而是断言 `LED_PHASE`（闪烁状态机的真实相位）与 `LED_RUN_MODE`；
 *          `LED_OUT` 只在有真实驱动的板上才能验证 —— 这正是"没有电气反馈
 *          就不能宣称灯亮了"的诚实做法。
 *
 * @author  binbina
 * @version V1.0.0
 */

#include <stdio.h>

#include "led_biz.h"
#include "bcm_sig.h"
#include "rte.h"

#include "Com_Cfg.h"     /* COM_SID_ParkingBrakeSwitch / COM_SID_Led* */
#include "CanIf_Cfg.h"   /* CANIF_RX_CAN1_CCVS */
#include "com_stub.h"
#include "platform_host.h"
#include "rx_mon.h"

/* ============================ [ 断言 ] ============================ */

static int s_bad;

static void Check(const char *name, int cond, const char *detail)
{
	printf("  %s  %s%s%s\n", cond ? "PASS" : "FAIL", name,
	       cond ? "" : "   ", cond ? "" : detail);
	if (!cond) {
		s_bad++;
	}
}

/* ============================ [ 驱动 ] ============================ */

/**
 * @brief 跑一拍：给原始值 / 可选模拟到达 / 推进 10 ms / 两个周期任务
 */
static void Tick(uint8_t raw, int arrived)
{
	HostCom_SetRx((Com_SignalIdType)COM_SID_ParkingBrakeSwitch, raw);
	Host_AdvanceMs(10u);
	if (arrived) {
		RxMon_OnRx((PduIdType)CANIF_RX_CAN1_CCVS);
	}
	BcmSig_MainFunction();
	LedBiz_MainFunction();
}

/** @brief 连续跑 n 拍，输入恒定 */
static void Run(uint8_t raw, int arrived, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		Tick(raw, arrived);
	}
}

int main(void)
{
	char buf[240];

	HostCom_Reset();
	RxMon_Init();
	BcmSig_Init();
	LedBiz_Init();

	/* ---- 1. 上电默认：尚未收到命令、灯灭、无故障 ---- */
	Run(0u, 0, 3);   /* 一帧都没到 */
	(void)sprintf(buf, "mode=%d out=%d phase=%d ft=%d fc=%d",
	              (int)BcmSig_TxGet(BCM_SIG_LED_RUN_MODE),
	              (int)BcmSig_TxGet(BCM_SIG_LED_OUT),
	              (int)BcmSig_TxGet(BCM_SIG_LED_PHASE),
	              (int)BcmSig_TxGet(BCM_SIG_LED_FAULT_TIMEOUT),
	              (int)BcmSig_TxGet(BCM_SIG_LED_FAULT_CMD));
	Check("上电默认：模式=未收到命令(UNKNOWN)、灯灭、无故障",
	      (BcmSig_TxGet(BCM_SIG_LED_RUN_MODE) == BCM_SW_STATE_UNKNOWN) &&
	      (BcmSig_TxGet(BCM_SIG_LED_OUT) == BCM_SW_STATE_OFF) &&
	      (BcmSig_TxGet(BCM_SIG_LED_PHASE) == BCM_SW_STATE_OFF) &&
	      (BcmSig_TxGet(BCM_SIG_LED_FAULT_TIMEOUT) == BCM_SW_STATE_OFF) &&
	      (BcmSig_TxGet(BCM_SIG_LED_FAULT_CMD) == BCM_SW_STATE_OFF),
	      buf);

	/* ---- 2. 启动闪烁：立刻亮相，500 ms 后翻灭相 ---- */
	Tick(1u, 1);
	(void)sprintf(buf, "mode=%d phase=%d", (int)BcmSig_TxGet(BCM_SIG_LED_RUN_MODE),
	              (int)BcmSig_TxGet(BCM_SIG_LED_PHASE));
	Check("启动：模式=闪烁、相位=亮相", 
	      (BcmSig_TxGet(BCM_SIG_LED_RUN_MODE) == BCM_SW_STATE_ON) &&
	      (BcmSig_TxGet(BCM_SIG_LED_PHASE) == BCM_SW_STATE_ON), buf);

	Run(1u, 1, 48);   /* 共 49 拍 = 490 ms，仍在亮相 */
	Check("490 ms 仍在亮相（半周期未到）",
	      BcmSig_TxGet(BCM_SIG_LED_PHASE) == BCM_SW_STATE_ON, "");
	Run(1u, 1, 1);    /* 第 50 拍 = 500 ms，翻灭相 */
	Check("500 ms 翻到灭相（非阻塞计时）",
	      BcmSig_TxGet(BCM_SIG_LED_PHASE) == BCM_SW_STATE_OFF, "");
	Run(1u, 1, 49);   /* 99 拍 */
	Check("990 ms 仍在灭相", BcmSig_TxGet(BCM_SIG_LED_PHASE) == BCM_SW_STATE_OFF, "");
	Run(1u, 1, 1);    /* 100 拍 = 1 s，回亮相 */
	Check("1 s 回到亮相（周期 1 s）",
	      BcmSig_TxGet(BCM_SIG_LED_PHASE) == BCM_SW_STATE_ON, "");

	/* ---- 3. 停止命令：熄灭、模式=已停止 ---- */
	Tick(0u, 1);
	(void)sprintf(buf, "mode=%d phase=%d ft=%d",
	              (int)BcmSig_TxGet(BCM_SIG_LED_RUN_MODE),
	              (int)BcmSig_TxGet(BCM_SIG_LED_PHASE),
	              (int)BcmSig_TxGet(BCM_SIG_LED_FAULT_TIMEOUT));
	Check("停止：模式=已停止、相位=灭、无故障",
	      (BcmSig_TxGet(BCM_SIG_LED_RUN_MODE) == BCM_SW_STATE_OFF) &&
	      (BcmSig_TxGet(BCM_SIG_LED_PHASE) == BCM_SW_STATE_OFF) &&
	      (BcmSig_TxGet(BCM_SIG_LED_FAULT_TIMEOUT) == BCM_SW_STATE_OFF),
	      buf);

	/* ---- 4. 无效命令：不改输出，置"命令无效" ---- */
	Tick(1u, 1);          /* 先启动 */
	Run(2u, 1, 5);        /* 连续发无效值 raw 2（帧仍然新鲜） */
	(void)sprintf(buf, "mode=%d cmd=%d timeout=%d",
	              (int)BcmSig_TxGet(BCM_SIG_LED_RUN_MODE),
	              (int)BcmSig_TxGet(BCM_SIG_LED_FAULT_CMD),
	              (int)BcmSig_TxGet(BCM_SIG_LED_FAULT_TIMEOUT));
	Check("无效命令：模式保持闪烁、置命令无效、不置超时",
	      (BcmSig_TxGet(BCM_SIG_LED_RUN_MODE) == BCM_SW_STATE_ON) &&
	      (BcmSig_TxGet(BCM_SIG_LED_FAULT_CMD) == BCM_SW_STATE_ON) &&
	      (BcmSig_TxGet(BCM_SIG_LED_FAULT_TIMEOUT) == BCM_SW_STATE_OFF),
	      buf);

	/* ---- 5. 超时：500 ms 无有效控制 → 停止 + 超时故障 ---- */
	Run(2u, 1, 55);       /* 继续只发无效值：有效命令计时到 500 ms */
	(void)sprintf(buf, "mode=%d phase=%d timeout=%d",
	              (int)BcmSig_TxGet(BCM_SIG_LED_RUN_MODE),
	              (int)BcmSig_TxGet(BCM_SIG_LED_PHASE),
	              (int)BcmSig_TxGet(BCM_SIG_LED_FAULT_TIMEOUT));
	Check("超时：模式=已停止、相位=灭、置超时故障",
	      (BcmSig_TxGet(BCM_SIG_LED_RUN_MODE) == BCM_SW_STATE_OFF) &&
	      (BcmSig_TxGet(BCM_SIG_LED_PHASE) == BCM_SW_STATE_OFF) &&
	      (BcmSig_TxGet(BCM_SIG_LED_FAULT_TIMEOUT) == BCM_SW_STATE_ON),
	      buf);

	/* ---- 6. 通信恢复：有效命令到达 → 清故障、重新闪烁 ---- */
	Tick(1u, 1);
	(void)sprintf(buf, "mode=%d phase=%d timeout=%d cmd=%d",
	              (int)BcmSig_TxGet(BCM_SIG_LED_RUN_MODE),
	              (int)BcmSig_TxGet(BCM_SIG_LED_PHASE),
	              (int)BcmSig_TxGet(BCM_SIG_LED_FAULT_TIMEOUT),
	              (int)BcmSig_TxGet(BCM_SIG_LED_FAULT_CMD));
	Check("恢复：有效命令清除两个故障位并重新闪烁",
	      (BcmSig_TxGet(BCM_SIG_LED_RUN_MODE) == BCM_SW_STATE_ON) &&
	      (BcmSig_TxGet(BCM_SIG_LED_PHASE) == BCM_SW_STATE_ON) &&
	      (BcmSig_TxGet(BCM_SIG_LED_FAULT_TIMEOUT) == BCM_SW_STATE_OFF) &&
	      (BcmSig_TxGet(BCM_SIG_LED_FAULT_CMD) == BCM_SW_STATE_OFF),
	      buf);

	/* ---- 7. LED_OUT 的诚实语义：Host 直连 DOUT 不可写 → 保持 OFF ---- */
	(void)sprintf(buf, "out=%d（Host GpioDoutOps 为空桩，写必失败）",
	              (int)BcmSig_TxGet(BCM_SIG_LED_OUT));
	Check("LED_OUT 只在驱动成功提交时更新（Host 上保持 OFF）",
	      BcmSig_TxGet(BCM_SIG_LED_OUT) == BCM_SW_STATE_OFF, buf);

	printf("-- led_biz: %s\n", (s_bad == 0) ? "全部通过" : "有失败项");
	return (s_bad == 0) ? 0 : 1;
}
