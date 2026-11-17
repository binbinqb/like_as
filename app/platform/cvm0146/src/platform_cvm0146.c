/**
 * @file    platform_cvm0146.c
 * @brief   CVM0146 平台初始化的具体实现（厂商 SDK 封装）
 *
 * @details 初始化序列照抄厂商 `examples/CVM0146/driver_examples/uart_polling_rx_tx`
 *          （SOSC 16 MHz → SOSC_DIV2 8 MHz → UART2），只做一处改动：
 *          打印走 `Platform_PutChar`，不依赖 newlib。
 *
 *          **不要**把 UART2 时钟源改成 FIRC：实测 `BRR` 会被算成 0，
 *          发送端永远等不到 TDRE，表现为"程序卡在 PutChar"，而 SysTick 照常走。
 *
 *          板级连接（来自《CVM0146 开发板快速入门》表 9）：
 *          | 信号 | MCU 端口 | 复用 |
 *          |------|----------|------|
 *          | UART2_RX | PTD17 | ALT3 |
 *          | UART2_TX | PTE12 | ALT3 |
 *          USB 转 UART 器件 CH340，PC 侧即 COM2。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：FIRC + UART2 控制台 + 极简 printf |
 */

#include "platform_cvm0146.h"
#include "platform_priv.h"
#include "lwrb.h"            /* 控制台 RX 环形缓冲（UART 中断 → 主循环） */
#include "Std_Critical.h"   /* imask_t + EnterCritical/ExitCritical 宏的底层类型 */
#include "perf_mon.h"        /* A6：SysTick 迟到量统计（中断里 5 条指令） */

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* ============================ [ 常量 ] ============================ */

/** @brief 控制台波特率（CH340 默认即可，PC 侧 COM2 需一致） */
#define PLATFORM_CONSOLE_BAUD   (115200u)

/**
 * @brief 内核时钟（Hz）
 *
 * @details `SystemInit()` 的默认分支把 FIRC 48 MHz 经 PLL ×15/3/2 升到 **120 MHz**，
 *          再以 DivCore=1 作为内核时钟。这里必须与它一致，否则 SysTick 的
 *          "1 ms" 就不是 1 ms（实测按 48 MHz 配，1 s 涨 2499 个 tick，正好 2.5×）。
 */
#define PLATFORM_CORE_CLOCK_HZ  (120000000u)

/* ============================ [ 全局 ] ============================ */

/**
 * @brief 厂商驱动的对象集合
 * @note  必须是全局且**唯一**：`Mcu_Init()` 只填结构体，驱动运行期靠这些句柄；
 *        放栈上会在 `Platform_Init()` 返回后失效（典型"初始化成功、一用就崩"）。
 *        由 `platform_priv.h` 暴露给 PortAc/DioAc/CanAc —— 它们必须用同一个对象，
 *        否则会出现"引脚配好了，CAN 用的却是另一个未初始化的驱动"。
 */
McuType g_mcu;

/** @brief 毫秒计数（SysTick 中断累加） */
static volatile uint32_t s_ms;

/* ── 控制台接收：UART2 中断 → 环形缓冲 → Platform_GetChar ──────────────
 *
 * 为什么必须走中断：
 *   轮询版 `Platform_GetChar` 直接读硬件 FIFO，而主循环里 NvM 擦除、
 *   CAN 突发接收等任务动辄占用几毫秒 —— 期间到达的字节**直接丢失**。
 *   实测症状：上位机连续发 `*IDN?\n`，板上收到 `*IDN` 或更少，
 *   命令既不执行也不报错（行编辑永远等不到回车）。
 *   改为中断收 + 512 字节环（远大于一次命令行的 128），主循环再慢也不丢。
 */
static uint8_t s_rxStorage[512];
static lwrb_t  s_rxRb;

/** @brief 控制台输出汇（NULL = 直写 UART；shell 绑定后指向 TX 环） */
static void (*s_consoleSink)(char c);

/** @brief 控制台输出一个字符（有汇走汇，无汇直写） */
static void Console_PutChar(char c);

/* ============================ [ 中断处理 ] ============================ */

/**
 * @brief SysTick 中断：毫秒计数
 * @note  厂商启动文件的向量表把 `SysTick_Handler` 声明为 weak，这里定义即覆盖。
 */
void SysTick_Handler(void)
{
	/* A6：量"这一拍迟到多久"。SysTick 是最低优先级（CMSIS 固定），
	 * 所以入口时刻的偏移就等于"被更高优先级 ISR 或关中断推迟了多久"。
	 * 开销约 5 条指令，常开 —— 关掉的测量等于没测。 */
	PerfMon_TickIsr();

	s_ms++;
}

/**
 * @brief UART2 收发中断：把收到的字节搬进环形缓冲
 * @details 只做"搬字节"这一件事（ISR 里不解析、不打印）：
 *          ① 一次搬空 FIFO（`GetRxCounter` 为 0 即止），避免下次中断前溢出；
 *          ② 环满时新字节丢弃（`lwrb_write` 返回值忽略）—— 环 512 字节，
 *             正常命令行 ≤128，只有异常流量才会满；
 *          ③ 不动 TDRE：发送仍是阻塞轮询（见 `Platform_PutChar`），
 *             这样 ISR 里不需要维护 TX 状态机。
 * @note  厂商启动文件的向量表把 `UART2_RxTx_Handler` 声明为 weak，这里定义即覆盖。
 */
void UART2_RxTx_Handler(void)
{
	uint8_t b;

	while (UartDrv_GetRxCounter(&g_mcu.uartDrv2) > 0u) {
		b = (uint8_t)UartDrv_RxData(&g_mcu.uartDrv2);
		(void)lwrb_write(&s_rxRb, &b, 1u);
	}
	/* 清 RX 标志，防止电平未变时反复进出中断 */
	UartDrv_ClearStatus(&g_mcu.uartDrv2, UARTDRV_STATUS_RDRF);
}

/* ============================ [ 内部函数 ] ============================ */

/**
 * @brief boot 专用的最小驱动初始化（实现见文件末尾，受 `PLATFORM_BOOT_MINIMAL` 控制）
 * @param[in] obj 厂商驱动对象集合
 */
#ifdef PLATFORM_BOOT_MINIMAL
static void Platform_McuInitMinimal(McuType *obj);
#endif

/**
 * @brief 打开外设门控并选 UART2 时钟源
 *
 * @details 照抄厂商 `uart_polling_rx_tx` 的 `Clock_Config()`：SOSC（板载 16 MHz 晶振）
 *          → SOSC_DIV2（8 MHz）→ UART2。
 *
 *          **为什么不自己改成 FIRC**：试过 `source=CLOCKDRV_FIRC, div=1`，
 *          结果 UART2 的 BRR 被算成 0（`ClockDrv_GetFreq` 拿不到有效频率），
 *          发送端永远等不到 TDRE —— 表现为"程序卡在 Platform_PutChar"，
 *          而且 SysTick 照常走，很容易误判成"打印正常、只是串口没接"。
 *          厂商这条路径在本板上验证过，先照抄；要换源必须同时核对 `GetFreq`。
 */
static void Clock_Config(void)
{
	ClockDrv_ModuleClkConfigType clockConfig;

	/* 16 MHz 外部晶振（PDF §晶振电路），UART 与 PLL 都用它 */
	clockConfig.gating = true;
	(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv, CLOCKDRV_SOSC, &clockConfig);

	/* SOSC_DIV2 = 8 MHz，作为 UART2 的模块时钟 */
	clockConfig.gating = true;
	clockConfig.source = CLOCKDRV_SOSC;
	clockConfig.div    = 1;
	(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv, CLOCKDRV_SOSC_DIV2, &clockConfig);

	/* PORT A~E 门控：引脚复用必须先有端口时钟，否则写 MUX 寄存器无效 */
	clockConfig.gating = true;
	(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv, CLOCKDRV_PORTA, &clockConfig);
	(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv, CLOCKDRV_PORTB, &clockConfig);
	(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv, CLOCKDRV_PORTC, &clockConfig);
	(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv, CLOCKDRV_PORTD, &clockConfig);
	(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv, CLOCKDRV_PORTE, &clockConfig);

	/* UART2：门控 + 源 = SOSC_DIV2 */
	clockConfig.gating = true;
	clockConfig.source = CLOCKDRV_SOSC_DIV2;
	(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv, CLOCKDRV_UART2, &clockConfig);
}

/**
 * @brief 配 UART2 的引脚复用与波特率
 */
static void Uart2_Init(void)
{
	UartDrv_InitCfgType uartInitCfg;

	/* PTD17 = UART2_RX，PTE12 = UART2_TX（板载 CH340 → PC 的 COM2） */
	PinsDrv_SetMuxModeSel(&g_mcu.ptd, 17u, PINSDRV_MUX_ALT3);
	PinsDrv_SetMuxModeSel(&g_mcu.pte, 12u, PINSDRV_MUX_ALT3);

	UartDrv_GetDefaultConfig(&uartInitCfg);
	uartInitCfg.basicParameters.baudRate = PLATFORM_CONSOLE_BAUD;
	ClockDrv_GetFreq(&g_mcu.clockDrv, CLOCKDRV_UART2,
	                 &uartInitCfg.basicParameters.busClockFreq);
	UartDrv_SetConfig(&g_mcu.uartDrv2, &uartInitCfg);

	/* 接收改中断 + 环形缓冲（理由见文件头 `s_rxStorage` 的注释） */
	(void)lwrb_init(&s_rxRb, s_rxStorage, (lwrb_sz_t)sizeof(s_rxStorage));
	UartDrv_SetInterruptReq(&g_mcu.uartDrv2, UARTDRV_ISR_SRC_RX_FULL, true);
	NVIC_EnableIRQ(UART2_RxTx_IRQn);
}

/**
 * @brief printf 的格式说明（从格式串里解析出来的修饰符）
 * @note  独立成结构体而不是直接边解析边输出：宽度/对齐/补零需要**先知道
 *        整个字段的长度**才能决定前面补几个字符，边解析边吐字符做不到。
 */
typedef struct {
	bool left;   /**< `-` 左对齐（默认右对齐） */
	bool zero;   /**< `0` 数值补前导零（指定精度时失效） */
	bool plus;   /**< `+` 正数也输出正号 */
	bool space;  /**< ` ` 正数前输出一个空格 */
	bool alt;    /**< `#` 十六进制加 `0x`/`0X` 前缀 */
	int  width;  /**< 字段最小宽度，0 = 未指定 */
	int  prec;   /**< 精度（整数=最少位数，字符串=最大字符数），负数 = 未指定 */
	int  len;    /**< 长度修饰：0=int，1=long，-1=short，-2=char */
} FmtSpec;

/** @brief 重复输出同一个字符 n 次（n<=0 时什么都不做） */
static int EmitRepeat(char c, int n)
{
	int i;

	for (i = 0; i < n; i++) {
		Console_PutChar(c);
	}
	return (n > 0) ? n : 0;
}

/** @brief 输出定长字符序列 */
static int EmitChars(const char *s, int n)
{
	int i;

	for (i = 0; i < n; i++) {
		Console_PutChar(s[i]);
	}
	return n;
}

/**
 * @brief 数值的前导部分（符号 + 进制前缀）
 * @return 输出的字符数
 */
static int EmitLead(char sign, char prefix)
{
	int n = 0;

	if (sign != '\0') {
		Console_PutChar(sign);
		n++;
	}
	if (prefix != '\0') {
		Console_PutChar('0');
		Console_PutChar(prefix);
		n += 2;
	}
	return n;
}

/**
 * @brief 按字段宽度输出一个数值
 *
 * @details 三种排布，与 C 标准一致：
 *          - 左对齐：`lead + 前导零 + 数字` 再补空格；
 *          - 补零（`0` 且未指定精度）：`lead` 先出，再接零、数字——
 *            **零必须补在符号/前缀之后**，否则 `%+05d` 会输出 `000+7`；
 *          - 其余：空格 + `lead` + 前导零 + 数字。
 *
 * @param[in] sp     格式说明
 * @param[in] neg    是否为负
 * @param[in] prefix 进制前缀字符（`x`/`X`），无前缀传 `\0`
 * @param[in] digits 数字串（已转成 ASCII）
 * @param[in] ndig   数字串长度
 * @return 输出的字符数
 */
static int EmitNumber(const FmtSpec *sp, bool neg, char prefix,
                      const char *digits, int ndig)
{
	char sign = '\0';
	int lead;
	int zeros = 0;
	int excess = 0;
	int total;
	int n = 0;

	if (neg) {
		sign = '-';
	} else if (sp->plus) {
		sign = '+';
	} else if (sp->space) {
		sign = ' ';
	}

	lead = (sign != '\0') ? 1 : 0;
	if (prefix != '\0') {
		lead += 2;
	}
	if ((sp->prec >= 0) && (sp->prec > ndig)) {
		zeros = sp->prec - ndig;
	}

	total = lead + zeros + ndig;
	if (sp->width > total) {
		excess = sp->width - total;
	}

	if (sp->left) {
		n += EmitLead(sign, prefix);
		n += EmitRepeat('0', zeros);
		n += EmitChars(digits, ndig);
		n += EmitRepeat(' ', excess);
	} else if (sp->zero && (sp->prec < 0)) {
		n += EmitLead(sign, prefix);
		n += EmitRepeat('0', excess);
		n += EmitRepeat('0', zeros);
		n += EmitChars(digits, ndig);
	} else {
		n += EmitRepeat(' ', excess);
		n += EmitLead(sign, prefix);
		n += EmitRepeat('0', zeros);
		n += EmitChars(digits, ndig);
	}
	return n;
}

/**
 * @brief 按字段宽度输出一个字符串
 * @note  `0` 标志对字符串无意义（标准里是未定义行为），这里忽略。
 */
static int EmitText(const FmtSpec *sp, const char *s, int len)
{
	int excess = 0;
	int n = 0;

	if ((sp->prec >= 0) && (sp->prec < len)) {
		len = sp->prec;
	}
	if (sp->width > len) {
		excess = sp->width - len;
	}

	if (!sp->left) {
		n += EmitRepeat(' ', excess);
	}
	n += EmitChars(s, len);
	if (sp->left) {
		n += EmitRepeat(' ', excess);
	}
	return n;
}

/** @brief 是否十进制数字字符 */
static bool IsDigit(char c)
{
	return (c >= '0') && (c <= '9');
}

/**
 * @brief 无符号整数转字符串（不补零）
 * @param[out] buf  输出缓冲，至少 11 字节
 * @param[in]  val  待转换值
 * @param[in]  base 进制（10 或 16）
 * @param[in]  upper 十六进制是否用大写
 * @return 写入的字符数
 */
static int Utoa(char *buf, uint32_t val, uint32_t base, bool upper)
{
	const char *digits = upper ? "0123456789ABCDEF" : "0123456789abcdef";
	char tmp[11];
	int n = 0;
	int i;

	if (val == 0u) {
		buf[0] = '0';
		return 1;
	}
	while ((val != 0u) && (n < (int)sizeof(tmp))) {
		tmp[n++] = digits[val % base];
		val /= base;
	}
	for (i = 0; i < n; i++) {
		buf[i] = tmp[n - 1 - i];
	}
	return n;
}

/* ============================ [ 对外接口 ] ============================ */

void Platform_Init(void)
{
#ifdef PLATFORM_BOOT_MINIMAL
	/* boot 专用：只初始化 clock/flash/power/reset/uart 五个驱动，
	 * 见文件末尾 `Platform_McuInitMinimal` 的说明。
	 * `Mcu_Init()` 会把 20 多个外设驱动的 .o 全部拉进镜像（56 KB），
	 * 64 KB 的 boot 区装不下还有余量的版本。 */
	Platform_McuInitMinimal(&g_mcu);
#else
	Mcu_Init(&g_mcu);
#endif
	Clock_Config();
	Uart2_Init();
}

void Platform_PutChar(char c)
{
	if (c == '\n') {
		/* 串口终端按 CRLF 处理换行；只发 LF 时很多工具会"阶梯式"输出 */
		while (UartDrv_GetStatus(&g_mcu.uartDrv2, UARTDRV_STATUS_TDRE) == false) {
		}
		UartDrv_TxData(&g_mcu.uartDrv2, (uint16_t)'\r');
	}
	while (UartDrv_GetStatus(&g_mcu.uartDrv2, UARTDRV_STATUS_TDRE) == false) {
	}
	UartDrv_TxData(&g_mcu.uartDrv2, (uint16_t)(uint8_t)c);
}

/**
 * @brief 控制台输出一个字符：有汇走汇（shell TX 环），无汇直写 UART
 * @details 直写路径（`Platform_PutChar`）**只给 shell 的 TX 排空用**：
 *          排空本身已在 shell 上下文，再经汇会形成递归。
 *          其余所有输出（`Platform_Puts` / `Platform_Printf`）都经本函数，
 *          保证与命令输出同一条队列、不会互相插进行中间。
 */
static void Console_PutChar(char c)
{
	if (s_consoleSink != NULL) {
		s_consoleSink(c);
	} else {
		Platform_PutChar(c);
	}
}

void Platform_Reset(void)
{
	Platform_Puts("[platform] reset now\n");

	/* 关中断再复位：SysTick 还在跑，若在 NVIC_SystemReset() 前的几条指令
	 * 之间来中断，可能又打出半行日志，看起来像"复位前还在跑别的代码"。
	 * 这里没有需要保存的状态，直接断。 */
	__asm volatile ("cpsid i");

	NVIC_SystemReset();

	/* NVIC_SystemReset 的 AIRCR 写入要几个周期才生效，编译器不知道它不返回，
	 * 不加这个死循环会继续往下执行（并可能被优化成 fall-through 到下一个函数）。 */
	for (;;) {
		__asm volatile ("nop");
	}
}

void Platform_SetConsoleSink(void (*fn)(char c))
{
	s_consoleSink = fn;
}

void Platform_Puts(const char *s)
{
	if (s == NULL) {
		return;
	}
	while (*s != '\0') {
		Console_PutChar(*s++);
	}
}

int Platform_Printf(const char *fmt, ...)
{
	va_list ap;
	const char *p;
	int count = 0;

	if (fmt == NULL) {
		return 0;
	}

	va_start(ap, fmt);
	p = fmt;
	while (*p != '\0') {
		FmtSpec sp;

		if (*p != '%') {
			Console_PutChar(*p);
			p++;
			count++;
			continue;
		}
		p++;    /* 跳过 '%' */

		/* ---- 1) 标志 ---- */
		sp.left  = false;
		sp.zero  = false;
		sp.plus  = false;
		sp.space = false;
		sp.alt   = false;
		sp.width = 0;
		sp.prec  = -1;
		sp.len   = 0;
		for (;;) {
			if (*p == '-') {
				sp.left = true;
			} else if (*p == '0') {
				sp.zero = true;
			} else if (*p == '+') {
				sp.plus = true;
			} else if (*p == ' ') {
				sp.space = true;
			} else if (*p == '#') {
				sp.alt = true;
			} else {
				break;
			}
			p++;
		}

		/* ---- 2) 宽度（数字或 '*' 取参数） ---- */
		if (*p == '*') {
			sp.width = va_arg(ap, int);
			p++;
			if (sp.width < 0) {     /* 负宽度 = 左对齐 + 绝对值，标准行为 */
				sp.left  = true;
				sp.width = -sp.width;
			}
		} else {
			while (IsDigit(*p)) {
				sp.width = (sp.width * 10) + (int)(*p - '0');
				p++;
			}
		}

		/* ---- 3) 精度 ---- */
		if (*p == '.') {
			p++;
			sp.prec = 0;
			if (*p == '*') {
				sp.prec = va_arg(ap, int);
				p++;
				if (sp.prec < 0) {  /* 负精度按"未指定"处理，标准行为 */
					sp.prec = -1;
				}
			} else {
				while (IsDigit(*p)) {
					sp.prec = (sp.prec * 10) + (int)(*p - '0');
					p++;
				}
			}
		}

		/* ---- 4) 长度修饰 ---
		 * 只区分"要不要按 long 取参"：本平台是 32 位，int 与 long 同宽，
		 * 但**取参类型必须与实参类型一致**，否则 va_arg 读取的槽位错位。
		 * `ll` 显式不支持：64 位格式化会拖进 __aeabi_uldivmod，且日志里用不到。
		 */
		if (*p == 'l') {
			p++;
			if (*p == 'l') {
				Platform_Puts("<ll?>");
				count += 5;
				break;
			}
			sp.len = 1;
		} else if (*p == 'h') {
			p++;
			if (*p == 'h') {
				p++;
				sp.len = -2;
			} else {
				sp.len = -1;
			}
		} else if (*p == 'z') {
			p++;
			sp.len = 0;     /* 本工具链 size_t == unsigned int，按 int 取参 */
		} else {
			sp.len = 0;
		}

		/* ---- 5) 转换符 ---- */
		switch (*p) {
		case 'd':
		case 'i': {
			long v;
			uint32_t mag;
			char buf[12];
			int nd;

			if (sp.len == 1) {
				v = va_arg(ap, long);
			} else {
				v = (long)va_arg(ap, int);
			}
			/* 二进制补码取负：写成 (uint32_t)0 - (uint32_t)v 而不是 -v，
			 * 否则 INT32_MIN 取负溢出（编译器 UB，实测 -O2 下会得到负数残留） */
			mag = ((uint32_t)v & 0x80000000u) != 0u
			      ? ((uint32_t)0 - (uint32_t)v) : (uint32_t)v;
			nd = ((sp.prec == 0) && (mag == 0u)) ? 0 : Utoa(buf, mag, 10u, false);
			count += EmitNumber(&sp, ((uint32_t)v & 0x80000000u) != 0u, '\0', buf, nd);
			break;
		}
		case 'u':
		case 'x':
		case 'X': {
			uint32_t v;
			uint32_t base = (*p == 'u') ? 10u : 16u;
			char buf[12];
			int nd;

			if (sp.len == 1) {
				v = (uint32_t)va_arg(ap, unsigned long);
			} else {
				v = (uint32_t)va_arg(ap, unsigned int);
			}
			nd = ((sp.prec == 0) && (v == 0u)) ? 0 : Utoa(buf, v, base, (*p == 'X'));
			/* `#` 且值为 0 时不加前缀（标准如此） */
			count += EmitNumber(&sp, false,
			                    (sp.alt && (v != 0u)) ? *p : '\0', buf, nd);
			break;
		}
		case 'p': {
			uint32_t v = (uint32_t)(uintptr_t)va_arg(ap, void *);
			char buf[12];
			int nd = Utoa(buf, v, 16u, false);
			count += EmitNumber(&sp, false, 'x', buf, nd);
			break;
		}
		case 'c': {
			char c = (char)va_arg(ap, int);
			count += EmitText(&sp, &c, 1);
			break;
		}
		case 's': {
			const char *sv = va_arg(ap, const char *);
			int len = 0;

			if (sv == NULL) {
				sv = "(null)";
			}
			while ((sv[len] != '\0') && ((sp.prec < 0) || (len < sp.prec))) {
				len++;
			}
			count += EmitText(&sp, sv, len);
			break;
		}
		case '%':
			Console_PutChar('%');
			count++;
			break;
		case '\0':
			/* 末尾孤立的 '%'：原样输出，不吞掉也不读参数 */
			Console_PutChar('%');
			count++;
			p--;
			break;
		default:
			/* 未实现的转换符：显式报错并**终止**本次格式化。
			 * 不能"原样输出后继续"——那会让 va_arg 的位置与后续格式符错配，
			 * 把整数当指针解引用，直接 HardFault（比少打一行日志严重得多）。 */
			Platform_Puts("<bad fmt %");
			Console_PutChar(*p);
			Platform_Puts(">");
			count += 12;
			va_end(ap);
			return count;
		}
		p++;
	}
	va_end(ap);
	return count;
}

int Platform_GetChar(void)
{
	uint8_t b;

	if (lwrb_read(&s_rxRb, &b, 1u) != 1u) {
		return -1;
	}
	return (int)b;
}

void Platform_InitTick(void)
{
	/* 失败说明重载值超出 24 位，通常意味着 CORE_CLOCK_HZ 写错了 */
	(void)SysTick_Config(PLATFORM_CORE_CLOCK_HZ / 1000u);
	PerfMon_TickResync();   /* 节拍首次启动：第一拍没有"上一拍"，不计迟到 */
}

uint32_t Platform_NowMs(void)
{
	return s_ms;
}

PinsDrvType *Platform_GetPort(uint8_t port)
{
	PinsDrvType *p = NULL;

	switch (port) {
	case 0u:
		p = &g_mcu.pta;
		break;
	case 1u:
		p = &g_mcu.ptb;
		break;
	case 2u:
		p = &g_mcu.ptc;
		break;
	case 3u:
		p = &g_mcu.ptd;
		break;
	case 4u:
		p = &g_mcu.pte;
		break;
	default:
		p = NULL;
		break;
	}

	return p;
}

/* ============================ [ 临界区 ] ============================ */

/**
 * @brief 进入临界区（关中断），返回进入前的中断状态
 * @return 进入前的 PRIMASK（bit0=1 表示当时已经关中断）
 *
 * @details BSW 里的 `EnterCritical()` / `ExitCritical()` 是配对宏
 *          （`Std_Critical.h`），底层就落在这两个函数上：
 *          @code
 *          imask_t imask = Std_EnterCritical();   // 保存旧状态 + 关中断
 *          ... 临界区 ...
 *          Std_ExitCritical(imask);               // 按旧状态决定是否开中断
 *          @endcode
 *
 *          @section CRIT_SAVED 为什么必须"保存再恢复"，不能无脑开中断
 *          如果 `ExitCritical()` 里直接 `cpsie i`，那么从**中断上下文**里调用
 *          （此时中断本来就是关的）会提前打开中断，导致重入。
 *          所以恢复的是"进入前的状态"，而不是"打开"。
 *
 *          @section CRIT_ASM 为什么用内联汇编而不是 CMSIS 的 `__get_PRIMASK()`
 *          CMSIS 核心头不在本工程的默认 include 路径里（`sdk/drivers/cpu/cmsis`
 *          需要单独加 `-I`），而 `mrs`/`cpsid` 两条指令是 Cortex-M 的通用约定，
 *          写成内联汇编反而少一个依赖。
 *
 * @note 只用 PRIMASK，不用 BASEPRI。BASEPRI 能给中断分级（让高优先级中断仍然响应），
 *       但当前工程没有"必须在临界区里响应某个中断"的需求，PRIMASK 更简单可靠。
 */
imask_t Std_EnterCritical(void)
{
	imask_t mask;

	/* 读 PRIMASK（0=开中断，1=关中断），再关中断 */
	__asm volatile("mrs %0, primask" : "=r"(mask)::"memory");
	__asm volatile("cpsid i" ::: "memory");

	return mask;
}

/**
 * @brief 退出临界区，恢复到 `Std_EnterCritical()` 之前的中断状态
 * @param[in] mask `Std_EnterCritical()` 的返回值
 */
void Std_ExitCritical(imask_t mask)
{
	/* 只有"进入前是开中断"才重新打开；bit0=1 说明之前就关着，保持关 */
	if (0u == (mask & 1u)) {
		__asm volatile("cpsie i" ::: "memory");
	}
}

/* ============================ [ 低功耗 / 唤醒（M12） ] ============================ */

uint8_t Platform_GetWakeupSource(void)
{
	PowerDrvWakeupFlagType src;

	src = PowerDrv_GetWakeupSource(&g_mcu.powerDrv);

	/* 厂商用 -1 表示"没有唤醒标志"。枚举是有符号的，
	 * 直接强转成 uint8_t 会得到 0xFF —— 正好与 PLATFORM_WAKEUP_NONE 一致，
	 * 但这里显式比较，避免依赖"负数补码"这种隐含假设。 */
	if ((int)src < 0) {
		return PLATFORM_WAKEUP_NONE;
	}

	return (uint8_t)src;
}

const char *Platform_GetWakeupSourceName(uint8_t src)
{
	static const char *const names[] = {
		"PORTA", "PORTB", "PORTC", "PORTD", "PORTE",
		"RSTPIN", "RTC", "LPIT", "LPTMR", "CMP",
	};

	if ((src != PLATFORM_WAKEUP_NONE) && (src < (uint8_t)(sizeof(names) / sizeof(names[0])))) {
		return names[src];
	}

	return "NONE";
}

void Platform_ClearWakeupFlags(void)
{
	PowerDrv_ClrAllWakupFlags(&g_mcu.powerDrv);
}

void Platform_StopTick(void)
{
	/* 关 SysTick 中断与计数器。清 COUNTFLAG 由 SysTick 硬件负责，
	 * 这里只保证"不会再产生 tick"，否则 WFI 会立刻被它叫醒。 */
	SysTick->CTRL = 0u;
	SysTick->VAL  = 0u;

	/* A6：节拍停了，上一拍的基准作废。不作废的话，睡眠 N ms 之后
	 * 第一拍会被记成"迟到 N ms"，且这个假峰值永久留在统计里。 */
	PerfMon_TickResync();
}

void Platform_SetTickPeriodMs(uint32_t ms)
{
	if (ms == 0u) {
		ms = 1u;
	}

	(void)SysTick_Config((PLATFORM_CORE_CLOCK_HZ / 1000u) * ms);
	PerfMon_TickResync();   /* 周期变了，1 ms 的基准不再成立（见 perf_mon.h） */
}

void Platform_StartTick(void)
{
	/* 重新装载 1 ms 周期。**不补偿**睡眠期间的时间：
	 * 睡眠时本来就没有 tick，补偿会让 CanTp/Dcm/NM 的超时逻辑误判
	 * （它们要的是"运行了多久"，不是"过了多久"）。
	 * 需要墙钟时间必须另配 RTC —— 这是设计选择，不是遗漏。 */
	(void)SysTick_Config(PLATFORM_CORE_CLOCK_HZ / 1000u);
	PerfMon_TickResync();   /* 从别的周期（或停机）恢复到 1 ms，基准同样作废 */
}

void Platform_EnterStopMode(void)
{
	/**
	 * @note 清唤醒标志必须在这里做，不能交给调用者 ——
	 *       `PowerDrv_GetWakeupSource()` 读的是粘滞标志，
	 *       不清的话醒来后仍会报"上一次"的源，排查时会指错方向。
	 */
	Platform_ClearWakeupFlags();

	/* 厂商实现：清 SLEEPDEEP + __WFI()（见 power_drv.c 的 SetPowerMode）。
	 *
	 * 注意它是 **Sleep 而不是 DeepSleep**：NVIC 仍然工作。
	 * 所以只要还有任何中断源（SysTick / CAN / UART）在跑，
	 * WFI 会在下一个中断立刻返回 —— 这是个**安全的失败模式**，
	 * 最坏情况是"几乎没睡"，绝不会把板子睡死。 */
	PowerDrv_SetPowerMode(&g_mcu.powerDrv, POWERDRV_POWER_MODE_STOP);
}

/* ============================ [ 跳转到应用 ] ============================ */

/*
 * Cortex-M 的核内寄存器直接用地址访问，不引 CMSIS：
 * 平台层已经依赖厂商 SDK 的头，再加一个 CMSIS 头会让 `SCB` 这类宏
 * 与 SDK 里的同名定义打架（SDK 的 reg 目录里有自己的 core_cm4.h 副本）。
 */
#define PLATFORM_SCB_VTOR       (*(volatile uint32_t *)0xE000ED08u)
#define PLATFORM_NVIC_ICER      ((volatile uint32_t *)0xE000E180u)
#define PLATFORM_NVIC_ICPR      ((volatile uint32_t *)0xE000E280u)
#define PLATFORM_SYST_CSR       (*(volatile uint32_t *)0xE000E010u)
#define PLATFORM_NVIC_LINES     (8u)

void Platform_JumpToApp(uint32_t base)
{
	uint32_t sp;
	uint32_t pc;
	uint32_t i;

	/* 参数检查：向量表头两个字必须像个向量表。
	 * 这里判得比 `BootMeta_CheckImage` 松（只判非 0 和非 0xFFFFFFFF），
	 * 因为详细校验是调用方的事，本函数只负责"不跳进明显的垃圾"。 */
	sp = *(volatile uint32_t *)(base);
	pc = *(volatile uint32_t *)(base + 4u);
	if ((sp == 0u) || (sp == 0xFFFFFFFFu) || (pc == 0u) || (pc == 0xFFFFFFFFu)) {
		return;
	}

	__asm volatile ("cpsid i" ::: "memory");

	/* 1) 停 SysTick。app 的 `Platform_InitTick()` 会按 1 ms 重装，
	 *    但**重装之前的这段时间里**如果 SysTick 还在跑，它的中断会打到
	 *    boot 的向量表上 —— 而 boot 的 RAM 向量表马上要被 app 覆盖。 */
	PLATFORM_SYST_CSR = 0u;

	/* 2) 关掉并清掉所有外部中断：boot 里使能过的（UART2）不关，
	 *    app 初始化 UART2 之前来一个接收中断就会跳进 boot 的 ISR。 */
	for (i = 0u; i < PLATFORM_NVIC_LINES; i++) {
		PLATFORM_NVIC_ICER[i] = 0xFFFFFFFFu;
		PLATFORM_NVIC_ICPR[i] = 0xFFFFFFFFu;
	}

	/* 3) VTOR 先指到镜像自己的向量表。app 的 `init_data_bss()` 随后会把
	 *    向量表复制到 RAM 并把 VTOR 改到 RAM —— 那一步才是最终生效的。
	 *    这里设置只是为了"从跳转到 app 初始化完成"这段窗口里，
	 *    万一来个中断也能找到正确的表。 */
	PLATFORM_SCB_VTOR = base;

	/* 4) 换栈指针再跳。顺序不能反：先设 MSP 再取 pc，
	 *    否则换栈之后 locals 全没了（这里 pc/sp 已在寄存器里，
	 *    但编译器仍可能从栈上重新读 —— 加 memory clobber 阻断这种优化）。 */
	__asm volatile ("msr msp, %0" :: "r" (sp) : "memory");
	__asm volatile ("dsb" ::: "memory");
	__asm volatile ("isb" ::: "memory");

	((void (*)(void))pc)();

	/* 正常不会到这里（app 是死循环）。真到了说明 pc 指向的函数返回了，
	 * 那就地停住，等看门狗复位 —— 比跳回 boot 主循环安全。 */
	for (;;) {
		__asm volatile ("nop");
	}
}

/* ============================ [ boot 用的精简驱动初始化 ] ============================ */

#ifdef PLATFORM_BOOT_MINIMAL

#include "drivers/cpu/startup/system_M014x.h"

/**
 * @brief boot 专用的最小驱动初始化（只填 boot 真正用到的 5 个句柄）
 *
 * @details @section MCUMIN_WHY 为什么不直接调 `Mcu_Init()`
 *          厂商的 `Mcu_Init()` 一次性初始化 20 多个外设驱动（ADC/EDMA/EIM/ERM/
 *          EWM/FCCU/I2C/I2SM/I2SS/LPIT/LPTMR/MFT/MPU/PDB/PINS/PRNG/PWMLITE/
 *          RTC/SPI/TRGMUX/WDG …）。链接器按目标文件粒度取符号，
 *          只要 `Mcu_Init` 被引用，这些驱动的 `.o` 就全部进镜像 ——
 *          实测把 boot 从 ~15 KB 撑到 **56 KB**，64 KB 的 boot 区只剩 8 KB 余量，
 *          随便加几行调试代码就顶穿。
 *
 *          boot 真正需要的只有五个：
 *          | 驱动 | 用途 |
 *          |------|------|
 *          | ClockDrv | 开 SOSC / 端口门控 / UART2 时钟（`Clock_Config` 依赖） |
 *          | FlashDrv | 擦写槽尾 meta（`Platform_Flash*` 依赖） |
 *          | PowerDrv | `Platform_EnterStopMode` / 唤醒源查询 |
 *          | ResetDrv | `Platform_GetWakeupSource` 读复位/唤醒标志 |
 *          | UartDrv  | 串口打印 |
 *
 *          @warning **参数必须与 `Mcu_Init()` 逐字一致**。这些 `*_Init` 不只是
 *          存指针，有的会顺手算分频/写寄存器；参数不同会导致
 *          boot 与 app 的外设状态不一致（最典型是 UART 波特率对不上，
 *          表现为 boot 打印乱码、app 正常）。改 `Mcu_Init` 时这里要同步。
 */
static void Platform_McuInitMinimal(McuType *obj)
{
	ClockDrv_InitParamsType clockInitParams;

	clockInitParams.fircFreq     = CPU_INT_FAST_CLK_HZ;
	clockInitParams.sircFreq     = CPU_INT_SLOW_CLK_HZ;
	clockInitParams.xtalClkFreq  = CPU_XTAL_CLK_HZ;
	clockInitParams.rtcClkInFreq = 0;
	clockInitParams.tclkFreq[0]  = 0;
	clockInitParams.tclkFreq[1]  = 0;
	clockInitParams.tclkFreq[2]  = 0;
	ClockDrv_Init(&obj->clockDrv, ACG, APC, SCG, PCC, &clockInitParams);

	FlashDrv_Init(&obj->flashDrv, FTFC);

	PowerDrv_Init(&obj->powerDrv, PMC, ACG);

	ResetDrv_Init(&obj->resetDrv, RCM, PCC, APC);

	/* PinsDrv 不能省：`Clock_Config()` 只开了 PORT 的**时钟门控**，
	 * 而 `Uart2_Init()` 配引脚走的是 `g_mcu.ptd/pte` 里的端口基址 ——
	 * 没调 `PinsDrv_Init` 时那些指针是 NULL，写 PCR 寄存器会直接打到
	 * 地址 0x44（NULL + 索引×4），进 HardFault 且 BFAR=0x44。
	 * 这个坑第一次跑 boot 就踩到了，症状是串口一个字都不出。 */
	PinsDrv_Init(&obj->pta, PORTA, GPIOA);
	PinsDrv_Init(&obj->ptb, PORTB, GPIOB);
	PinsDrv_Init(&obj->ptc, PORTC, GPIOC);
	PinsDrv_Init(&obj->ptd, PORTD, GPIOD);
	PinsDrv_Init(&obj->pte, PORTE, GPIOE);

	UartDrv_Init(&obj->uartDrv2, UART2);

	/* flexCAN：D1 第二步起 boot 要刷写，必须能收发。
	 *
	 * 两个实例都初始化，因为 `Can_Cfg.c`（boot 复用 app 那份）配了 2 个通道，
	 * `Can_Init()` 会遍历全部通道 —— 只初始化 CAN0 的话，CAN1 那个句柄是
	 * 全 0，`CanAc_Init` 写它的寄存器指针会打到地址 0，进 HardFault。
	 *
	 * `canRamNum` 是每个实例的 CAN RAM 块数，必须与 `mcu.c` 的
	 * `Mcu_Init()` 完全一致（那是 M2/M19 验证过的分配），否则邮箱编号
	 * 会整体错位 —— 表现是"某个邮箱永远收不到"，且没有任何报错。 */
	{
		FlexCanDrv_InitHwParType canInitHwPar;

		canInitHwPar.canInstanceIdx = 0;
		canInitHwPar.canRamNum      = 3;
		FlexCanDrv_Init(&obj->flexCanDrv0, CAN0, PCC, SCG, SIM, &canInitHwPar);

		canInitHwPar.canInstanceIdx = 1;
		canInitHwPar.canRamNum      = 2;
		FlexCanDrv_Init(&obj->flexCanDrv1, CAN1, PCC, SCG, SIM, &canInitHwPar);
	}
}

#endif /* PLATFORM_BOOT_MINIMAL */
