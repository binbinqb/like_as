/**
 * @file    test_adc_sampler.c
 * @brief   Host 上的 AdcSampler 断言：完成才发布、失败/超时不发布、组独立
 *
 * @details @section TESTADC_WHAT 覆盖什么
 *
 *          | # | 用例 | 期望 |
 *          |---|------|------|
 *          | 1 | 未采样 | `GetRaw` 返回 E_NOT_OK，不给 0 充数 |
 *          | 2 | 启动与发布时序 | 第 1 拍只启动、第 2 拍才发布（不在同一拍抢跑） |
 *          | 3 | 多通道同组 | 2 通道组一次转换发布两个槽位 |
 *          | 4 | 序号递增 | 每发布一次 +1（IoHwAb 靠它判新样本） |
 *          | 5 | 转换延迟 | 延迟 2 次查询期间不发布，就绪后才发布 |
 *          | 6 | 转换永不完成 | 超时计数增长、不发布，**另一组不受影响** |
 *          | 7 | 读失败 | 不发布、seq 不变（上层转 STALE） |
 *          | 8 | 启动失败 | 不产生发布，也不计入超时 |
 *          | 9 | 参数校验 | 越界组/槽位 → E_NOT_OK |
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.1.0 | 2026-11-18 | binbina | 首版：9 组断言 |
 */

#include <stdio.h>

#include "adc_sampler.h"

extern void HostAdc_Reset(void);
extern void HostAdc_SetValue(uint8 group, uint8 slot, uint16 raw);
extern void HostAdc_SetReadyAfter(uint8 group, uint8 polls);
extern void HostAdc_SetStartFail(uint8 group, boolean fail);
extern void HostAdc_SetReadFail(uint8 group, boolean fail);
extern uint16 HostAdc_GetStarts(void);

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

static void run_ticks(int n)
{
	int i;

	for (i = 0; i < n; i++) {
		AdcSampler_MainFunction();
	}
}

int main(void)
{
	uint16 raw = 0u;
	uint16 seq = 0u;
	uint16 seq0 = 0u;
	uint32 tmo0 = 0u;

	(void)printf("== AdcSampler（Host，V1.1.0）==\n");

	HostAdc_SetValue(0u, 0u, 1111u);
	HostAdc_SetValue(0u, 1u, 2222u);
	HostAdc_SetValue(1u, 0u, 3333u);
	HostAdc_SetReadyAfter(0u, 0u);
	HostAdc_SetReadyAfter(1u, 0u);
	HostAdc_Reset();
	AdcSampler_Init();

	/* ---- 1) 未采样 ---- */
	check(AdcSampler_GetRaw(0u, 0u, &raw, &seq) == E_NOT_OK,
	      "未采样时 GetRaw = E_NOT_OK（不给 0 充数）");

	/* ---- 2) 第一拍只启动 ---- */
	run_ticks(1);
	check(HostAdc_GetStarts() == 2u, "第 1 拍启动了两个组");
	check(AdcSampler_GetRaw(0u, 0u, &raw, &seq) == E_NOT_OK,
	      "第 1 拍没有结果（转换未完成，不抢跑）");

	/* ---- 3) 第二拍发布，多通道同组 ---- */
	run_ticks(1);
	check((AdcSampler_GetRaw(0u, 0u, &raw, &seq) == E_OK) && (raw == 1111u),
	      "第 2 拍发布组 0 槽位 0 = 1111");
	check((AdcSampler_GetRaw(0u, 1u, &raw, &seq) == E_OK) && (raw == 2222u),
	      "同一次转换发布组 0 槽位 1 = 2222");
	check((AdcSampler_GetRaw(1u, 0u, &raw, &seq) == E_OK) && (raw == 3333u),
	      "组 1 同时发布 3333");

	/* ---- 4) 序号递增：每两拍 +1 ---- */
	(void)AdcSampler_GetRaw(0u, 0u, &raw, &seq0);
	run_ticks(2);
	(void)AdcSampler_GetRaw(0u, 0u, &raw, &seq);
	check((uint16)(seq - seq0) == 1u, "两拍后 seq 恰好 +1");

	/* ---- 5) 转换延迟：期间不发布 ---- */
	HostAdc_SetReadyAfter(0u, 2u);
	HostAdc_Reset();
	AdcSampler_Init();
	run_ticks(2);
	check(AdcSampler_GetRaw(0u, 0u, &raw, &seq) == E_NOT_OK,
	      "延迟 2 次查询：第 2 拍仍无结果");
	run_ticks(2);
	check(AdcSampler_GetRaw(0u, 0u, &raw, &seq) == E_OK,
	      "延迟结束后发布");

	/* ---- 6) 永不完成：超时，且不影响另一组 ---- */
	HostAdc_SetReadyAfter(0u, 255u);
	HostAdc_SetReadyAfter(1u, 0u);
	HostAdc_Reset();
	AdcSampler_Init();
	tmo0 = AdcSampler_GetTimeouts();
	run_ticks(12);
	check(AdcSampler_GetTimeouts() > tmo0, "组 0 一直不完成 → 超时计数增长");
	check(AdcSampler_GetRaw(0u, 0u, &raw, &seq) == E_NOT_OK,
	      "超时的组不发布假值");
	check(AdcSampler_GetRaw(1u, 0u, &raw, &seq) == E_OK,
	      "另一组照常采样（组间互不阻塞）");

	/* ---- 7) 读失败：不发布、seq 不变 ---- */
	HostAdc_SetReadyAfter(0u, 0u);
	HostAdc_Reset();
	AdcSampler_Init();
	run_ticks(2);
	(void)AdcSampler_GetRaw(0u, 0u, &raw, &seq0);
	HostAdc_SetReadFail(0u, TRUE);
	run_ticks(2);
	check(AdcSampler_GetRaw(0u, 0u, &raw, &seq) == E_OK
	      && (seq == seq0),
	      "读失败：沿用上一个序号（seq 不变 → 上层转 STALE）");
	HostAdc_SetReadFail(0u, FALSE);

	/* ---- 8) 启动失败：不计入超时 ---- */
	HostAdc_SetStartFail(0u, TRUE);
	tmo0 = AdcSampler_GetTimeouts();
	run_ticks(5);
	check(AdcSampler_GetTimeouts() == tmo0, "启动失败不计入超时");
	HostAdc_SetStartFail(0u, FALSE);

	/* ---- 9) 参数校验 ---- */
	run_ticks(4);
	check(AdcSampler_GetRaw(0u, 2u, &raw, &seq) == E_NOT_OK,
	      "组 0 只有 2 个槽位：slot=2 被拒");
	check(AdcSampler_GetRaw(9u, 0u, &raw, &seq) == E_NOT_OK,
	      "未配置的组号被拒");

	(void)printf("-- %d 通过，%d 失败\n", s_pass, s_fail);
	return (s_fail == 0) ? 0 : 1;
}
