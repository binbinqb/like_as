/**
 * @file    test_iohwab.c
 * @brief   Host 上的 IoHwAb Core 用例：消抖、极性、滤波、四态、安全状态
 *
 * @details @section IOHWABTEST_WHAT 覆盖什么
 *
 *          | # | 用例 | 期望 |
 *          |---|------|------|
 *          | 1 | 上电未采样 | 读 DIN 返回 E_OK 但 status=NEVER，值不可当 LOW 用 |
 *          | 2 | DIN 消抖 | 跳变后未满 20 拍不提交；满拍后 VALID |
 *          | 3 | DIN 极性 | activeLevel=LOW：引脚低 → 逻辑 1 |
 *          | 4 | AIN 滤波与定点换算 | 8 拍收敛；phys = raw×factor/1000+offset |
 *          | 5 | AIN 超时 | 连续失败达 staleTicks → STALE，两倍 → ERROR |
 *          | 6 | DOUT 安全状态与极性 | Init 后为 safeLevel；写 1 → 电气高（host 高有效） |
 *          | 7 | PWM 与越界 | 5000 生效；10001 / 非法 ID / 直连 LED 均 E_NOT_OK |
 *
 *          第 7 条里"直连 LED 在 Host 返回 E_NOT_OK"是刻意的：Host 没有 GPIO，
 *          不允许假装点亮成功。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-18 | binbina | 首版：7 组断言 |
 */

#include <stdio.h>

#include "iohwab.h"
#include "IoHwAb_Cfg.h"   /* 通道枚举（Board.json 生成） */

/* Host 后端的故障注入接口（iohwab_host_ops.c） */
extern void HostIo_SetDin(uint16 ch, boolean level);
extern void HostIo_SetDinFail(uint16 ch, boolean fail);
extern void HostIo_SetAin(uint16 ch, uint16 raw);
extern void HostIo_SetAinFail(uint16 ch, boolean fail);
extern boolean HostIo_GetDoutLevel(uint16 ch);
extern uint16 HostIo_GetPwm(uint16 ch);

static int s_pass;
static int s_fail;

/**
 * @brief 断言
 * @param[in] cond 条件
 * @param[in] what 描述
 */
static void check(int cond, const char *what)
{
	if (0 != cond) {
		s_pass++;
		(void)printf("  PASS  %s\n", what);
	} else {
		s_fail++;
		(void)printf("  FAIL  %s\n", what);
	}
}

/** @brief 跑 N 个 10 ms 节拍 */
static void run_ticks(int n)
{
	int i;

	for (i = 0; i < n; i++) {
		IoHwAb_MainFunction();
	}
}

int main(void)
{
	boolean v = FALSE;
	IoHwAb_StatusType st = IOHWAB_STATUS_NEVER;
	sint32 phys = 0;
	uint16 raw = 0;

	(void)printf("== IoHwAb Core（Host）==\n");

	/* ---- 1) 上电未采样 ---- */
	HostIo_SetDin(0u, TRUE);        /* 高电平；activeLevel=LOW → 逻辑 0 */
	IoHwAb_Init();
	check(IoHwAb_DinRead((IoHwAb_DinId)IOHWAB_DIN_DOOR_FL, &v, &st) == E_OK,
	      "DIN 读调用合法（E_OK）");
	check(st == IOHWAB_STATUS_NEVER,
	      "DIN 未采样时 status=NEVER（不能当 LOW 用）");

	/* ---- 2) 消抖：debounceMs=20 → 2 拍（10 ms/拍） ---- */
	run_ticks(1);
	check(IoHwAb_DinRead((IoHwAb_DinId)IOHWAB_DIN_DOOR_FL, &v, &st) == E_OK
	      && (st == IOHWAB_STATUS_NEVER),
	      "DIN 1 拍（< 消抖 2 拍）仍为 NEVER");
	run_ticks(1);
	check((IoHwAb_DinRead((IoHwAb_DinId)IOHWAB_DIN_DOOR_FL, &v, &st) == E_OK)
	      && (st == IOHWAB_STATUS_VALID) && (v == FALSE),
	      "DIN 满 2 拍后 VALID，逻辑值 0（引脚高、低有效）");

	/* ---- 3) 极性：引脚低 → 逻辑 1 ---- */
	HostIo_SetDin(0u, FALSE);
	run_ticks(2);
	check((IoHwAb_DinRead((IoHwAb_DinId)IOHWAB_DIN_DOOR_FL, &v, &st) == E_OK)
	      && (st == IOHWAB_STATUS_VALID) && (v == TRUE),
	      "DIN 低有效：引脚低 → 逻辑 1");

	/* ---- 4) AIN 滤波与定点换算 ---- */
	HostIo_SetAin(0u, 2048u);
	run_ticks(30);                   /* shift=3：时间常数约 8 拍，30 拍后基本收敛 */
	check(IoHwAb_AinReadRaw((IoHwAb_AinId)IOHWAB_AIN_VBAT, &raw, &st) == E_OK
	      && (st == IOHWAB_STATUS_VALID) && (raw > 1900u) && (raw <= 2048u),
	      "AIN_VBAT 30 拍滤波后接近 2048");
	check(IoHwAb_AinReadPhys((IoHwAb_AinId)IOHWAB_AIN_VBAT, &phys, &st) == E_OK,
	      "AIN_VBAT 物理量读取合法");
	/* factor=33 → 2048×33/1000 ≈ 67（滤波未完全收敛时允许 ±2） */
	check((phys >= 62) && (phys <= 67),
	      "AIN_VBAT phys = raw×33/1000（定点，允许滤波残差）");

	/* ---- 5) AIN 超时：STALE → ERROR ---- */
	HostIo_SetAinFail(1u, TRUE);
	run_ticks(50);                   /* staleMs=500 → 50 拍 STALE；100 拍 ERROR */
	check(IoHwAb_AinReadRaw((IoHwAb_AinId)IOHWAB_AIN_TEMP, &raw, &st) == E_OK
	      && (st == IOHWAB_STATUS_STALE),
	      "AIN_TEMP 失败 50 拍 → E_OK 但 status=STALE（应用必须看状态）");
	run_ticks(60);
	(void)IoHwAb_AinReadRaw((IoHwAb_AinId)IOHWAB_AIN_TEMP, &raw, &st);
	check(st == IOHWAB_STATUS_ERROR,
	      "AIN_TEMP 失败 110 拍 → ERROR");
	HostIo_SetAinFail(1u, FALSE);

	/* ---- 6) DOUT 安全状态与极性 ---- */
	IoHwAb_Init();                   /* 重新初始化，回到安全状态 */
	check(HostIo_GetDoutLevel(0u) == FALSE,
	      "Init 后 Host0 输出 = safeLevel（低）");
	check(IoHwAb_DoutWrite((IoHwAb_DoutId)IOHWAB_DOUT_HOST0, TRUE) == E_OK
	      && (HostIo_GetDoutLevel(0u) == TRUE),
	      "Host0 高有效：写逻辑 1 → 电气 1");
	check(IoHwAb_DoutReadBack((IoHwAb_DoutId)IOHWAB_DOUT_HOST0, &v) == E_OK
	      && (v == TRUE),
	      "Host0 回读逻辑 1");

	/* ---- 7) 安全状态批量、PWM、越界与"不伪造" ---- */
	check(IoHwAb_DoutWrite((IoHwAb_DoutId)IOHWAB_DOUT_HOST0, TRUE) == E_OK, "Host0 再写 1");
	IoHwAb_SetAllSafe();
	check(HostIo_GetDoutLevel(0u) == FALSE, "SetAllSafe 把 Host0 拉回安全值");

	check(IoHwAb_PwmSetDuty((IoHwAb_PwmId)IOHWAB_PWM_DIM_HOST, 5000u) == E_OK
	      && (HostIo_GetPwm(0u) == 5000u),
	      "PWM 50% 生效");
	check(IoHwAb_PwmSetDuty((IoHwAb_PwmId)IOHWAB_PWM_DIM_HOST, 10001u) == E_NOT_OK,
	      "PWM duty 越界被拒");
	check(IoHwAb_DinRead((IoHwAb_DinId)99, &v, &st) == E_NOT_OK,
	      "非法 DIN ID 被拒");
	check(IoHwAb_DoutWrite((IoHwAb_DoutId)IOHWAB_DOUT_LED_R, TRUE) == E_NOT_OK,
	      "直连 LED 在 Host 返回 E_NOT_OK（不伪造成功）");

	(void)printf("-- %d 通过，%d 失败\n", s_pass, s_fail);
	return (s_fail == 0) ? 0 : 1;
}
