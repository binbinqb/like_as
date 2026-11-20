/**
 * @file    rte_sched.c
 * @brief   RTE runnable 调度表（10.5）：按 Board.json 生成的顺序与周期执行应用 runnable
 *
 * @details 表内容由 `tools/generator/BcmRte.py` 从 `Board.json` 的 `rte.schedule`
 *          生成到 `Rte_Schedule.h`，本文件只负责展开与执行：
 *
 *          | 要改什么                       | 改哪里                        |
 *          |--------------------------------|-------------------------------|
 *          | runnable 顺序 / 周期 / 增删    | `Board.json` → 重新生成       |
 *          | 调度机制本身（计数、分频）     | 本文件                        |
 *
 *          @section SCHED_ORDER 顺序语义
 *          表内顺序 = **同一拍内的执行顺序**，依赖关系靠表序表达：
 *          BcmSig 必须在 BcmBiz 之前（业务读的是本拍刚刷新的影子），
 *          AdcSampler 必须在 IoHwAb 之前（先发布样本，IoHwAb 再消费）。
 *          跨周期的依赖**不允许**：周期不同的两个 runnable 不会每拍都
 *          同拍执行，靠"跨周期顺序"表达的依赖必然偶发失效。
 *
 *          @section SCHED_TICK 分频机制
 *          每项维护一个倒数计数器：计数为 0 时执行并重装 `reload`
 *          （= period_ms / 10）。reload=1 即每拍执行。计数器静态初始化为 0，
 *          **首次调用即执行** —— 与"周期函数从上电起每拍都跑"的历史行为
 *          一致（从 main.c 收编时零行为变化）。
 *
 *          @section SCHED_WHY 为什么单独一个文件（而不是塞进 rte_cfg.c）
 *          表里引用 `ComApp_Tick` / `AdcSampler_MainFunction` 等函数，
 *          Host 的 `rte` 用例不链接这些模块（com_app.c / adc_sampler.c）。
 *          独立翻译单元让 Host 可以用**替身 runnable** 单独测调度逻辑
 *          （顺序、周期、计数），不必把整个应用拖进每个用例。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-20 | binbina | 首版：从 main.c 收编 5 个应用 runnable 调用 |
 */

#include "rte.h"
#include "rte_cfg.h"      /* Rte_SchedEntryType / Rte_SchedFunc */
#include "Rte_Schedule.h" /* RTE_SCHEDULE_LIST / RTE_SCHED_NUM（Board.json 生成） */

/** @brief 调度表：顺序与周期即配置（rte.schedule），reload 已折算成基准拍数 */
static const Rte_SchedEntryType Rte_SchedList[RTE_SCHED_NUM] = RTE_SCHEDULE_LIST;

/** @brief 每项的倒数计数器；0 = 到拍。静态初始化 0 → 上电首拍即执行 */
static uint8_t Rte_SchedCnt[RTE_SCHED_NUM];

/**
 * @brief RTE 周期入口：按调度表执行一遍到拍的 runnable（见 rte.h 接口说明）
 *
 * @note  reload ≥ 1 由生成规则 S2 保证（period_ms ≥ 10 且为 10 的倍数），
 *        计数器不会卡死；表项 func 为 NULL（空表占位）直接跳过。
 */
void Rte_MainFunction(void)
{
	uint16_t i;

	for (i = 0u; i < RTE_SCHED_NUM; i++)
	{
		if (Rte_SchedList[i].func == NULL)
		{
			continue;   /* 空表占位行：S4 允许 schedule 缺省为空 */
		}
		if (Rte_SchedCnt[i] == 0u)
		{
			/* 重装 reload-1：reload=1 时计数器常驻 0（每拍执行），
			 * reload=3 时依次 2→1→0（每 3 拍执行）。 */
			Rte_SchedCnt[i] = (uint8_t)(Rte_SchedList[i].reload - 1u);
			Rte_SchedList[i].func();
		}
		else
		{
			Rte_SchedCnt[i]--;
		}
	}
}
