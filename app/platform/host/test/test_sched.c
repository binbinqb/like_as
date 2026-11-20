/**
 * @file    test_sched.c
 * @brief   Host 用例：RTE runnable 调度表（真实配置驱动替身 runnable）
 *
 * @details 被 `host_build.py` 的 `sched` 套件编译：源码只有 `rte_sched.c`
 *          + 本文件。本文件用**与真实 `Board.json` 调度表同名**的替身函数
 *          接住函数指针，验证三件事：
 *
 *          | 断言 | 钉住什么 |
 *          |------|----------|
 *          | RTE_SCHED_NUM == 5 且全非 NULL | 真实配置确实进了生成物 |
 *          | 一拍内调用顺序 == 配置顺序 | "表序即执行序"（BcmSig 必须先于 BcmBiz 等） |
 *          | 连续 10 拍每个 runnable 各执行 10 次 | period 10ms 的分频语义（reload=1 每拍执行） |
 *
 *          ⚠ 替身函数名与 Board.json 的 `rte.schedule[].func` 一一对应；
 *            改配置不改本文件，断言 1/3 仍成立，断言 2 会报出真实顺序，
 *            按新顺序更新期望数组即可（顺序本来就是配置的一部分）。
 *
 *          多周期（reload>1）与变体配置的验证在 `tools/rte_sched_check.py`：
 *          那里用临时生成的变体 `Rte_Schedule.h` 编译同一份 rte_sched.c。
 *
 * @author  binbina
 * @version V1.0.0
 */

#include <stdio.h>
#include "rte.h"          /* Rte_MainFunction */
#include "Rte_Schedule.h" /* RTE_SCHED_NUM */

/* ============================ [ 替身 runnable ] ============================ */
/* 下标 = 期望顺序（真实配置：BcmSig → BcmBiz → ComApp → AdcSampler → IoHwAb） */

#define RTEST_N_STUB   (6)
static int s_order[64];   /**< 执行顺序记录（存替身下标） */
static int s_n;           /**< 已记录条数 */
static int s_cnt[RTEST_N_STUB]; /**< 每个替身的累计执行次数 */

static void Rec(int idx)
{
	if (s_n < (int)(sizeof(s_order) / sizeof(s_order[0]))) {
		s_order[s_n] = idx;
	}
	s_n++;
	s_cnt[idx]++;
}

/* 名字必须与 Board.json rte.schedule[].func 一致（见文件头说明） */
void BcmSig_MainFunction(void)     { Rec(0); }
void BcmBiz_MainFunction(void)     { Rec(1); }
void LedBiz_MainFunction(void)     { Rec(2); }
void ComApp_Tick(void)             { Rec(3); }
void AdcSampler_MainFunction(void) { Rec(4); }
void IoHwAb_MainFunction(void)     { Rec(5); }

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

static const char *EXP_ORDER[] = { "BcmSig", "BcmBiz", "LedBiz", "ComApp", "AdcSampler", "IoHwAb" };

int main(void)
{
	int i;
	int k;
	char buf[256];

	/* ---- 1. 真实配置进了生成物 ---- */
	Check("RTE_SCHED_NUM == 6", RTE_SCHED_NUM == RTEST_N_STUB, "实际=%d");

	/* ---- 2. 一拍内顺序 == 配置顺序 ---- */
	Rte_MainFunction();
	(void)sprintf(buf, "实际=%d", s_n);
	Check("一拍执行 6 个 runnable", s_n == RTEST_N_STUB, buf);
	for (k = 0; k < RTEST_N_STUB; k++) {
		if ((k < s_n) && (s_order[k] != k)) {
			break;
		}
	}
	if (s_n > (int)(sizeof(s_order) / sizeof(s_order[0]))) {
		/* 记录溢出：顺序断言仍然有效（前 RTEST_N_STUB 条已存下），
		 * 但计数断言会失真 —— 先报出来 */
		Check("一拍执行 5 个 runnable", 0, "超出记录缓冲，替身被多调");
	}
	Check("一拍内顺序 == 配置顺序（BcmSig→BcmBiz→LedBiz→ComApp→AdcSampler→IoHwAb）",
	      k == RTEST_N_STUB, "首个不符位置见上方顺序打印");

	printf("  order :");
	for (i = 0; i < s_n; i++) {
		printf(" %s", EXP_ORDER[s_order[i]]);
	}
	printf("\n");

	/* ---- 3. 连续 10 拍：每个 runnable 各 10 次（period 全 10ms） ---- */
	s_n = 0;
	for (k = 0; k < RTEST_N_STUB; k++) {
		s_cnt[k] = 0;   /* 第 2 步已各执行 1 次，清零后只统计这 10 拍 */
	}
	for (i = 0; i < 10; i++) {
		Rte_MainFunction();
	}
	for (k = 0; k < RTEST_N_STUB; k++) {
		if (s_cnt[k] != 10) {
			break;
		}
	}
	(void)sprintf(buf, "s_cnt=[%d,%d,%d,%d,%d,%d]",
	              s_cnt[0], s_cnt[1], s_cnt[2], s_cnt[3], s_cnt[4], s_cnt[5]);
	Check("连续 10 拍每个 runnable 执行 10 次（reload=1 每拍执行）",
	      k == RTEST_N_STUB, buf);

	printf("-- sched: %s\n", (s_bad == 0) ? "全部通过" : "有失败项");
	return (s_bad == 0) ? 0 : 1;
}
