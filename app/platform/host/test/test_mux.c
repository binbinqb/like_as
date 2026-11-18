/**
 * @file    test_mux.c
 * @brief   Host 上的 MuxManager 时序断言：共享 ABC、ADC 期间不切换、超时、故障
 *
 * @details @section TESTMUX_WHAT 覆盖什么
 *
 *          | # | 用例 | 期望 |
 *          |---|------|------|
 *          | 1 | 未采样 | `Mux_GetDin/GetAin` 返回 E_NOT_OK，不拿 0 充数 |
 *          | 2 | GPIO 读失败 | 该通道不发布（仍 E_NOT_OK），同总线的 ADC 通道不受影响 |
 *          | 3 | 一拍扫完一轮 | ABC 0..3 各写 1 次；每个 Y 都拿到对应 ABC 的值 |
 *          | 4 | 未用通道不扫描 | ABC 4..7 的写次数为 0（activeMask=0x0F） |
 *          | 5 | ADC 转换期间 ABC 稳定 | 延迟 2 次查询完成，全程 0 次"启动/取值 ABC 不一致" |
 *          | 6 | ADC 永不完成 | 超时计数增长、扫描继续（不卡死）、AIN 无样本、DIN 正常 |
 *          | 7 | ADC 启动失败 | 本拍不采样，超时计数不增长（不是超时） |
 *          | 8 | 通道校验 | 未启用 Y / 越界 dev / COM 类型不符 → E_NOT_OK |
 *          | 9 | IoHwAb 胶水 | `IoHwAb_MuxDinOps` 拆包后与 `Mux_GetDin` 一致 |
 *          | 10 | 序号递增 | 每发布一次 `seq` +1（IoHwAb 靠它判新样本） |
 *          | 11 | INH 未配置 | 不产生任何 INH 写操作 |
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.1.0 | 2026-11-18 | binbina | 首版：11 组时序断言 |
 */

#include <stdio.h>

#include "iohwab.h"
#include "mux.h"

/* Host 替身的观测与注入接口（mux_host_ops.c） */
extern void HostMux_Reset(void);
extern void HostMux_SetGpio(uint8 comCh, uint8 y, boolean level);
extern void HostMux_SetGpioFail(uint8 comCh, boolean fail);
extern void HostMux_SetAdc(uint8 comCh, uint8 y, uint16 raw);
extern void HostMux_SetAdcReadyAfter(uint8 comCh, uint8 polls);
extern void HostMux_SetAdcFail(uint8 comCh, boolean fail);
extern uint16 HostMux_GetSelectWrites(void);
extern uint8 HostMux_GetAbcWrites(uint8 abc);
extern uint16 HostMux_GetAbcStabilityViolations(void);
extern uint16 HostMux_GetInhWrites(void);
extern uint8 HostMux_GetLastAbc(void);

static int s_pass;
static int s_fail;

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
		Mux_MainFunction();
	}
}

/** @brief 按 ABC 给 COM 摆好一组值：GPIO 高在偶数 ABC、ADC 值 = 0x100+abc */
static void load_values(void)
{
	uint8 abc;

	for (abc = 0u; abc < 8u; abc++) {
		HostMux_SetGpio(0u, abc, ((abc & 1u) == 0u) ? TRUE : FALSE);
		HostMux_SetAdc(0u, abc, (uint16)(0x100u + abc));
	}
}

int main(void)
{
	boolean lvl = FALSE;
	uint16 raw = 0u;
	uint16 seq = 0u;
	boolean s1 = FALSE;
	uint16 q1 = 0u;
	uint16 q2 = 0u;

	(void)printf("== MuxManager（Host，V1.1.0）==\n");

	load_values();
	HostMux_Reset();
	Mux_Init();

	/* ---- 1) 未采样不给假值 ---- */
	check(Mux_GetDin(0u, 0u, &lvl, &seq) == E_NOT_OK,
	      "未扫描前 DIN 返回 E_NOT_OK（不拿 0 充数）");
	check(Mux_GetAin(1u, 0u, &raw, &seq) == E_NOT_OK,
	      "未扫描前 AIN 返回 E_NOT_OK");

	/* ---- 2) GPIO 失败只影响自己 ---- */
	HostMux_SetGpioFail(0u, TRUE);
	run_ticks(1);
	check(Mux_GetDin(0u, 0u, &lvl, &seq) == E_NOT_OK,
	      "GPIO 读失败：本通道不发布");
	check(Mux_GetAin(1u, 0u, &raw, &seq) == E_OK,
	      "同总线 ADC 通道不受 GPIO 失败影响");
	HostMux_SetGpioFail(0u, FALSE);

	/* ---- 3) 一拍扫完一轮 ---- */
	HostMux_Reset();
	Mux_Init();
	run_ticks(1);
	check(Mux_GetScanRounds() == 1u, "settle=0 + ADC 立即就绪：一拍扫完一轮");
	check((HostMux_GetSelectWrites() == 4u)
	      && (HostMux_GetAbcWrites(0u) == 1u) && (HostMux_GetAbcWrites(1u) == 1u)
	      && (HostMux_GetAbcWrites(2u) == 1u) && (HostMux_GetAbcWrites(3u) == 1u),
	      "ABC 0..3 各写一次");
	check((HostMux_GetAbcWrites(4u) == 0u) && (HostMux_GetAbcWrites(7u) == 0u),
	      "activeMask 外的 ABC 4/7 从不扫描");
	check((Mux_GetDin(0u, 1u, &lvl, &seq) == E_OK) && (lvl == FALSE)
	      && (Mux_GetDin(0u, 2u, &lvl, &seq) == E_OK) && (lvl == TRUE),
	      "GPIO 取值跟随 ABC（Y1 低、Y2 高，电气量原样传出）");
	check((Mux_GetAin(1u, 3u, &raw, &seq) == E_OK) && (raw == 0x103u),
	      "ADC Y3 读到 0x103（同一 COM，不同 ABC）");

	/* ---- 4) ADC 转换期间 ABC 必须稳定 ---- */
	HostMux_Reset();
	HostMux_SetAdcReadyAfter(0u, 2u);
	Mux_Init();
	run_ticks(1);
	check((HostMux_GetSelectWrites() == 1u) && (HostMux_GetLastAbc() == 0u),
	      "ADC 未完成：本拍不切 ABC（只写了 ABC0）");
	run_ticks(30);
	check(HostMux_GetAbcStabilityViolations() == 0u,
	      "全程 0 次\"启动/取值 ABC 不一致\"");
	check(Mux_GetScanRounds() >= 1u, "延迟转换下仍能扫完至少一轮");
	check((Mux_GetAin(1u, 0u, &raw, &seq) == E_OK) && (raw == 0x100u),
	      "延迟转换后取到的仍是 ABC0 的值（不是别的通道）");

	/* ---- 5) ADC 永不完成：超时后继续扫，不卡死 ---- */
	HostMux_Reset();
	HostMux_SetAdcReadyAfter(0u, 255u);
	Mux_Init();
	run_ticks(40);
	check(Mux_GetAdcTimeouts() > 0u, "ADC 超时被计数");
	check(Mux_GetScanRounds() > 0u, "超时后扫描继续（一轮坏器件不卡死整条链）");
	check(Mux_GetAin(1u, 0u, &raw, &seq) == E_NOT_OK,
	      "超时的 AIN 通道无样本（不发布旧值/假值）");
	check(Mux_GetDin(0u, 0u, &lvl, &seq) == E_OK,
	      "同总线 GPIO 通道照常采样");

	/* ---- 6) ADC 启动失败：不算超时 ---- */
	HostMux_Reset();
	HostMux_SetAdcReadyAfter(0u, 0u);
	HostMux_SetAdcFail(0u, TRUE);
	Mux_Init();
	run_ticks(3);
	check(Mux_GetAdcTimeouts() == 0u, "启动失败不计入超时");
	check(Mux_GetAin(1u, 1u, &raw, &seq) == E_NOT_OK, "启动失败：AIN 无样本");
	HostMux_SetAdcFail(0u, FALSE);

	/* ---- 7) 通道校验 ---- */
	run_ticks(2);
	check(Mux_GetDin(0u, 5u, &lvl, &seq) == E_NOT_OK,
	      "activeMask 外的 Y 通道被拒");
	check(Mux_GetDin(9u, 0u, &lvl, &seq) == E_NOT_OK, "越界设备索引被拒");
	check(Mux_GetAin(0u, 0u, &raw, &seq) == E_NOT_OK,
	      "GPIO 设备不允许按 AIN 取（COM 类型不符）");

	/* ---- 8) IoHwAb 胶水：拆包 + 序号透传 ---- */
	(void)Mux_GetDin(0u, 2u, &s1, &q1);
	check((IoHwAb_MuxDinOps.Read != NULL) &&
	      (IoHwAb_MuxDinOps.Read(IOHWAB_MUX_CH(0u, 2u), &lvl, &q2) == E_OK)
	      && (q2 == q1) && (lvl == s1),
	      "IoHwAb_MuxDinOps 与 Mux_GetDin 返回同一序号与电平");
	(void)Mux_GetAin(1u, 2u, &raw, &q1);
	check((IoHwAb_MuxAinOps.ReadRaw != NULL) &&
	      (IoHwAb_MuxAinOps.ReadRaw(IOHWAB_MUX_CH(1u, 2u), &raw, &q2) == E_OK)
	      && (q2 == q1) && (raw >= 0x100u),
	      "IoHwAb_MuxAinOps 拆包正确（dev<<8 | y）");

	/* ---- 9) 序号每发布一次 +1 ---- */
	{
		uint16 seq0 = 0u;
		uint16 seq1 = 0u;

		(void)Mux_GetDin(0u, 0u, &lvl, &seq0);
		run_ticks(1);
		(void)Mux_GetDin(0u, 0u, &lvl, &seq1);
		check((uint16)(seq1 - seq0) == 1u, "一轮扫描后 seq 恰好 +1");
	}

	/* ---- 10) INH 未配置：不产生写操作 ---- */
	check(HostMux_GetInhWrites() == 0u, "inhChannel = MUX_NO_CHANNEL 时不写 INH");

	(void)printf("-- %d 通过，%d 失败\n", s_pass, s_fail);
	return (s_fail == 0) ? 0 : 1;
}
