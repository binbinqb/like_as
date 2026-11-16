/**
 * @file    mem_cmd.c
 * @brief   `mem` 命令（A6）：打印 RAM/栈/调度延迟的实测值
 *
 * @details 为什么把这三样放同一条命令里：它们回答的是同一个问题 ——
 *          **这套固件在最坏情况下还剩多少余量**。分开打会让人只看到
 *          "栈用了 20%"就放心，而真正的风险往往是"某一拍跑了 8 ms"。
 *
 *          数值全部来自运行时（链接脚本符号 + DWT），不是编译期估算：
 *          编译期估算给不出"FEE 擦除那一拍"的峰值。
 *
 * @note    百分比不在这里算。区域大小写在链接脚本 `.ld` 里，固件里再抄一份
 *          就会有两处真相。比值由 `tools/a6_budget.py` 解析 `.ld` + `.exe`
 *          一起算，这里只给**原始字节数**。
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "sh_cfg.h"          /* SH_EXPORT_CMD / SH_OK */
#include "platform_cvm0146.h"
#include "perf_mon.h"        /* DWT 周期计数与迟到量 */
#include "stack_mon.h"       /* 栈水位 */

#include <string.h>

/** @brief 静态 RW 区边界，由链接脚本符号给出 */
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

/**
 * @brief mem [clear] —— RAM / 栈 / 调度延迟实测值
 *
 * @param[in] argc 参数个数
 * @param[in] argv 参数数组（`argv[1] == "clear"` 时清零统计）
 * @return SH_OK
 *
 * @note  用法：`mem`
 *        - 第一行 `rw`：`.data` 与 `.bss` 各自的字节数（**分开打**：
 *          两者在链接脚本里落在不同 SRAM 区，相加再减首尾会把中间
 *          没用到的 60 KB 算进去，得出 74 KB 这种明显不对的数）
 *        - 第二行 `stack`：历史最深水位 / 栈总大小
 *        - 第三行 `tick`：SysTick 最坏迟到（被高优先级 ISR / 关中断推迟多久）
 *          与主循环单拍最坏耗时
 *
 * @note  `mem clear` 清零最大值。用途：启动阶段有 Flash 擦写与 NvM 读盘，
 *        它们会产生"真实但不代表稳态"的峰值；要看稳态必须清零后重新采样。
 *
 * @warning `stack` 读的是**本次上电以来**的最深水位。刚复位就读只有几百字节，
 *          必须跑完负载（诊断会话、NvM 写入、刷写）再看，数字才有意义。
 */
static int sh_cmd_mem(int argc, char *argv[])
{
	uint32_t data;
	uint32_t bss;
	uint32_t used;
	uint32_t total;

	if ((argc >= 2) && (strcmp(argv[1], "clear") == 0))
	{
		PerfMon_Reset();
		Platform_Puts("  stats cleared\n");
		return SH_OK;
	}

	data = (uint32_t)&__data_end__ - (uint32_t)&__data_start__;
	bss = (uint32_t)&__bss_end__ - (uint32_t)&__bss_start__;
	used = StackMon_UsedBytes();
	total = StackMon_TotalBytes();

	Platform_Printf("  rw    : data %u B + bss %u B = %u B\n",
	                (unsigned)data, (unsigned)bss, (unsigned)(data + bss));
	Platform_Printf("  stack : used %u / %u B  (left %u B)\n",
	                (unsigned)used, (unsigned)total, (unsigned)(total - used));
	Platform_Printf("  tick  : late max %u cyc / %u us | bsw max %u cyc / %u us\n",
	                (unsigned)PerfMon_TickLateMaxCycles(),
	                (unsigned)PerfMon_TickLateMaxUs(),
	                (unsigned)PerfMon_BswMaxCycles(),
	                (unsigned)PerfMon_BswMaxUs());

	return SH_OK;
}

SH_EXPORT_CMD(mem, sh_cmd_mem, "mem [clear] -- RAM / stack watermark / tick latency");
