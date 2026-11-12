/**
 * @file    sh_app.c
 * @brief   Shell 平台绑定：UART2 控制台 + `!x` 旧命令兼容桥
 *
 * @details 三层职责，全部集中在本文件，shell 中间件保持平台无关：
 *          1. `sh_io_t` 三件套 → Platform_PutChar / Platform_GetChar / Platform_NowMs
 *          2. **迁移期兼容桥**：旧验收脚本（m2~m19_check.py）发的是
 *             `!` + 单字符、**不带回车**的命令（如 `!k`），而 shell 按行
 *             分发（需回车）。桥的做法是：读到 `!` 先吞掉，把紧随的一个
 *             字符交给 main.c 的旧 CmdExec；其余字符全部送进 shell。
 *             ⇒ 旧脚本零改动继续跑，新命令（`help`/`ver`/`can ...`）并行可用。
 *          3. 命令迁移完成后，删掉桥 + 旧 CmdExec 即可，shell 无感。
 *
 * @note    `*RST` 未绑定复位回调：命令会明确回 `<-5, not supported`，
 *          不假装成功（自动化脚本据此判断）。
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "sh.h"
#include "sh_app.h"
#include "platform_cvm0146.h"

#include <stdbool.h>

/**
 * @brief 读一个字节
 * @return 0~255 送 shell；-1 无数据
 * @note  旧 `!x` 兼容桥已删除（验收脚本已全部切到新命令）。
 *        现在串口收到的每个字节都进 shell 行编辑。
 */
static int sh_app_getc(void)
{
	return Platform_GetChar();
}

/** @brief 阻塞写一段（Platform_PutChar 是原始直写通道，不再经过控制台汇） */
static void sh_app_write(const uint8_t *data, uint16_t len)
{
	while (len-- > 0u) {
		Platform_PutChar((char)(*data));
		data++;
	}
}

/**
 * @brief 控制台输出汇：平台层所有字符串输出逐字符进 shell 的 TX 环
 * @details 这样心跳、CAN 收帧打印、命令输出排在同一条队列里，
 *          不会再出现"alive #16"插进命令输出行中间的情况。
 * @warning 本函数会被 `Platform_Printf` 高频调用，只能做入队，不得阻塞。
 */
static void sh_app_console_sink(char c)
{
	sh_putch(c);
}

/** @brief 毫秒时基 */
static uint32_t sh_app_ms(void)
{
	return (uint32_t)Platform_NowMs();
}

/** @brief I/O 操作集（必须常驻，不得为栈变量） */
static const sh_io_t s_shIo = {
	.getc = sh_app_getc,
	.write = sh_app_write,
	.ms = sh_app_ms,
};

void ShApp_Init(void)
{
	(void)sh_bind_io(&s_shIo);
	sh_init();
	/* 汇必须在 sh_init 之后绑定：sh_init 之前的输出走直写，
	 * 保证"上电到 shell 就绪"之间的早期打印（时钟/PLL 自检）不丢。 */
	Platform_SetConsoleSink(sh_app_console_sink);
	sh_banner();
}

void ShApp_Task(void)
{
	sh_task();
}
