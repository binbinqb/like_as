/**
 * @file    CriticalAc.c
 * @brief   Host 临界区实现：空操作（单线程模型）
 *
 * @details @section HOSTCRIT_WHY 为什么可以是空操作
 *
 *          `EnterCritical()` 的语义是"挡住中断，直到 `ExitCritical()`"。
 *          Host 进程里没有中断，业务代码也不会被抢占，所以这里只保留
 *          接口形状，不做任何事。
 *
 *          @warning **不要因此认为临界区代码可以在 Host 上验证**。
 *          如果一段代码在目标板上靠关中断保护共享变量，Host 跑通不代表
 *          它是对的——Host 只会告诉你"单线程下逻辑自洽"。
 *          真正的验证手段是：静态审查 + 上板压力测试（M14 那一类）。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版：空实现 |
 */

#include "Std_Critical.h"

imask_t Std_EnterCritical(void)
{
	return 0u;
}

void Std_ExitCritical(imask_t mask)
{
	(void)mask;
}
