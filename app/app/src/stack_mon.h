/**
 * @file    stack_mon.h
 * @brief   栈水位实测（A6）：用填充图案找出"栈最深用到哪里"
 *
 * @details @section STACKMON_WHY 为什么不用静态分析
 *
 *          `-fstack-usage` 只能给出"每个函数自己的帧有多大"，
 *          要算出最坏路径得把调用图乘起来 —— 而本工程的最深路径
 *          恰好是**中断嵌套 + 库里的大栈帧**（`printf` 系列、FEE 擦写），
 *          静态分析给不出可信数字。
 *
 *          填充法测的是**真的跑出来的最深处**：启动时把整个未用栈区写满
 *          一个固定图案，运行一段时间后从栈底往上找第一个被改过的字节，
 *          位置就是历史最深水位。
 *
 * @note    @section STACKMON_LIMIT 这个数字的含义与边界
 *
 *          - 它只反映**这次上电以来**去过的最深处。没跑过的业务分支不算数，
 *            所以要在"跑过全部验收脚本之后"读，数字才有意义。
 *          - 栈是**向下增长**的，水位越低说明用得越多。本模块统一换算成
 *            "已用字节数"（= 栈顶 - 最深处），越大越危险。
 *          - 填充在 `main()` 第一行执行，且关中断 —— 否则填充过程中
 *            来一个中断，它的栈帧会被后来的填充字节覆盖，直接跑飞。
 *
 * @author  binbina
 * @version V1.0.0
 */

#ifndef STACK_MON_H
#define STACK_MON_H

#include "Std_Types.h"

/**
 * @brief 用图案填满未使用的栈区（**必须在 main 的最前面调用**）
 *
 * @details 调用点越早越好：晚于任何一层调用，那段栈就已经被用过、
 *          水位会漏记。当前固定在 `main()` 的第一条语句，
 *          排在 `Platform_Init()` 之前。
 *
 * @note  内部关中断执行（约 2 KB 的填充，1~2 µs）。不关中断的后果是
 *        中断栈帧被覆盖 —— 现象是"偶尔死机"，且只在有中断时出现。
 */
void StackMon_Init(void);

/**
 * @brief 读当前水位
 *
 * @return 已用栈字节数（0 表示填充区一个字节都没被碰过）
 *
 * @note  每次调用都从头扫描（2 KB，约几十微秒），只在命令里调用，
 *        不要放进周期任务。
 */
uint32_t StackMon_UsedBytes(void);

/**
 * @brief 栈总大小（字节）
 */
uint32_t StackMon_TotalBytes(void);

#endif /* STACK_MON_H */
