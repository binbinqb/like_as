/**
 * @file    sh_io.c
 * @brief   sh 输出层 —— 自含格式化器 + TX 环形缓冲 + 平台 I/O 绑定
 *
 * @details 本文件解决三个问题，每个都对应一个已经踩过的坑：
 *
 *          @section SH_IO_FMT ① 不用 C 库 printf
 *          IAR 非 microlib 下 `printf` 走半主机（semihosting），没有调试器时
 *          在 `main()` 之前就 BKPT 挂死。故自带一个受限 `vsnprintf`：
 *          - 支持 `%[l][d i u x X s c %]`；
 *          - 支持 `%-N` 左对齐、`%0N` 零填充、`%+d` 强制符号，宽度 N ≤ 99；
 *          - **不支持**浮点、精度 `.N`、`*` 宽度 —— 用到即按未知转换原样输出。
 *
 *          ⚠ 历史缺陷：旧实现只解析 `%-N`，`%+d` 会把 `+` 当未知转换、把 `d`
 *          当普通字符输出 ⇒ `<%+d, OK>` 实际打印 `<+d, OK>`，SCPI 应答协议
 *          直接失效。`%02d` 同理退化为空格填充。本版已修正，见 @ref sh_emit_num。
 *
 *          @section SH_IO_TX ② 大批量输出不得阻塞主循环
 *          115200 8N1 下一字节 ≈ 86.8 µs，打印 430 B 要 37 ms —— 直接阻塞写
 *          会让主循环单圈耗时失控。故输出先入环形缓冲，由 @ref sh_task 每圈
 *          排空一片（≤ @ref SH_TX_CHUNK 字节 ⇒ 单圈阻塞 ≈ 0.69 ms）。
 *          **启动阶段例外**：首次 @ref sh_tx_drain 之前走阻塞直写，
 *          保证上电日志即时且严格有序（那时没有实时性要求）。
 *
 *          环形缓冲**复用 `kernel/lwrb`**，不另造一套指针运算：
 *          它与 CAN / UART 驱动用的是同一份实现，行为已经过实机验证，
 *          也减少了本项目需要自己维护的代码量。
 *          ⚠ lwrb 的可用容量是 `size - 1`（`r == w` 表示空，
 *          `w == r - 1` 表示满），故 @ref SH_TX_RING 为 1024 时实际可存 1023 字节。
 *
 *          @section SH_IO_BIND ③ 中间件不依赖 HAL
 *          `middleware/shell` 不得 include 任何 `hal_xxx.h`（分层单向）。
 *          平台能力通过 @ref sh_io_t 三个函数指针注入，与 `IsoTp_DebugShim`
 *          同一套路。绑定实现见 `src/debug/sh_port.c`。
 *
 * @note    遵守 MISRA C:2012 Required 规则。
 * @warning 全部输出接口**不可重入**（共用静态格式化缓冲）；
 *          本工程打印只出现在任务上下文，满足该前提。
 *
 * @author  binbina
 * @version 1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-10-26 | binbina | 初版。移植 ULP8 的 TX 环与非阻塞输出；格式化器补齐 `%+d` 强制符号与 `%0N` 零填充（原 hal_sh 缺失，导致 SCPI 应答与后台任务列表输出错误）；新增 sh_snprintf 替代 C 库 sprintf |
 * | V1.1.0 | 2026-10-26 | binbina | TX 环形缓冲改用 kernel/lwrb 实现，删除自维护的 head/tail 指针运算与位掩码取模，与 CAN/UART 驱动共用同一份已验证代码 |
 */

#include "sh.h"
#include "sh_cfg.h"
#include "sh_internal.h"

#include "lwrb.h"

#include <string.h>

/* ── 平台绑定与 TX 环状态 ───────────────────────────────────────── */

/** @brief 绑定的平台 I/O（由 @ref sh_bind_io 设置；NULL = 未绑定） */
static const sh_io_t *s_io;

/** @brief TX 环形缓冲底层存储 */
static uint8_t s_tx_storage[SH_TX_RING];
/** @brief TX 环形缓冲对象（lwrb） */
static lwrb_t  s_tx_rb;
/** @brief 1 = 环已就绪；0 = 未就绪（此时写入只计数不落盘） */
static uint8_t s_tx_ready;
/** @brief 环满丢弃字节数（诊断用；正常恒 0） */
static uint32_t s_tx_drop;
/** @brief 1 = 主循环已启动，输出改走排队（0 = 启动阶段，阻塞直写） */
static uint8_t s_tx_queue_mode;
/** @brief 1 = 输出静音（@ref SH_CONFIG_MUTE），丢弃全部待发内容 */
static bool    s_muted;

/* ── 格式化器：输出游标 ─────────────────────────────────────────── */

/**
 * @brief 受限输出游标
 * @details 与 `snprintf` 语义一致：超容量只计数不写，返回值为"本应写入的字符数"。
 */
typedef struct {
    char  *dst;     /**< 目标缓冲 */
    size_t size;    /**< 容量（含 `\0` 位置） */
    size_t n;       /**< 已产生字符数（含被截断的） */
} sh_out_t;

/**
 * @brief 写一个字符到游标
 * @param[in,out] o 输出游标
 * @param[in]     c 待写字符
 */
static void sh_out_c(sh_out_t *o, char c)
{
    if (o->n < o->size) {
        o->dst[o->n] = c;
    }
    o->n++;
}

/* ── 格式化器：整数转换 ─────────────────────────────────────────── */

/**
 * @brief 无符号整数转字符串（2/10/16 进制）
 * @param[out] buf   输出缓冲，容量至少 12 字节（32 位最长 10 位 + 余量）
 * @param[in]  v     待转换值
 * @param[in]  base  进制：10 或 16
 * @param[in]  upper 十六进制是否用大写字母
 * @return 写入字符数（不含 `\0`）
 * @note  必须用与进制匹配的算法：曾把基 16 的 `v & 0xF` 配十进制数字表，
 *        nibble > 9 时越界读并把 `\0` 写进正文，导致整行输出被截断。
 */
static uint16_t sh_utoa(char *buf, unsigned long v, uint8_t base, bool upper)
{
    const char *digits = upper ? "0123456789ABCDEF" : "0123456789abcdef";
    char        rev[12];
    uint16_t    i = 0U;
    uint16_t    ri = 0U;

    if (v == 0UL) {
        buf[i] = '0';
        i++;
        return i;
    }

    while (v > 0UL) {
        unsigned long d = v % (unsigned long)base;
        rev[ri] = digits[(uint8_t)d];
        ri++;
        v /= (unsigned long)base;
    }
    while (ri > 0U) {
        ri--;
        buf[i] = rev[ri];
        i++;
    }
    return i;
}

/**
 * @brief 输出一个带符号/填充的数值字段
 * @param[in,out] o     输出游标
 * @param[in]     body  数字正文（不含符号）
 * @param[in]     blen  正文长度
 * @param[in]     sign  符号字符：`'-'` / `'+'` / `'\0'` 表示无符号
 * @param[in]     width 域宽（0 = 不填充）
 * @param[in]     left  true = 左对齐（`%-N`）
 * @param[in]     zero  true = 零填充（`%0N`）；左对齐时忽略
 *
 * @details 零填充必须把符号放在填充之前（`-007` 而不是 `00-7`）——
 *          这正是旧实现缺失的行为，`%04X` 会输出 `"  1F"` 而非 `"001F"`。
 */
static void sh_emit_num(sh_out_t *o, const char *body, uint16_t blen, char sign,
                        int width, bool left, bool zero)
{
    int      total = (int)blen + ((sign != '\0') ? 1 : 0);
    int      pad   = (width > total) ? (width - total) : 0;
    uint16_t i;

    if (left) {
        /* 左对齐：符号 + 正文 + 尾部空格 */
        if (sign != '\0') {
            sh_out_c(o, sign);
        }
        for (i = 0U; i < blen; i++) {
            sh_out_c(o, body[i]);
        }
        for (i = 0U; i < (uint16_t)pad; i++) {
            sh_out_c(o, ' ');
        }
    } else if (zero) {
        /* 零填充：符号 + 前导 0 + 正文 */
        if (sign != '\0') {
            sh_out_c(o, sign);
        }
        for (i = 0U; i < (uint16_t)pad; i++) {
            sh_out_c(o, '0');
        }
        for (i = 0U; i < blen; i++) {
            sh_out_c(o, body[i]);
        }
    } else {
        /* 右对齐空格填充 */
        for (i = 0U; i < (uint16_t)pad; i++) {
            sh_out_c(o, ' ');
        }
        if (sign != '\0') {
            sh_out_c(o, sign);
        }
        for (i = 0U; i < blen; i++) {
            sh_out_c(o, body[i]);
        }
    }
}

/* ── 格式化器：主循环 ───────────────────────────────────────────── */

/**
 * @brief 自含 vsnprintf（仅支持子集，不依赖 C 库 stdio）
 * @param[out] dst  输出缓冲；可为 NULL 但此时 @p size 必须为 0（仅计长度）
 * @param[in]  size 缓冲容量（含 `\0` 位置）
 * @param[in]  fmt  格式串
 * @param[in]  ap   可变参数表
 * @return 本应写入的字符数（不含 `\0`；≥ @p size 表示被截断）
 */
static int sh_vsnprintf(char *dst, size_t size, const char *fmt, va_list ap)
{
    sh_out_t o;

    o.dst  = dst;
    o.size = size;
    o.n    = 0U;

    while (*fmt != '\0') {
        bool left = false;
        bool zero = false;
        bool plus = false;
        int  width = 0;
        bool is_long = false;
        char conv;
        char body[12];
        uint16_t blen = 0U;
        char sign = '\0';

        if (*fmt != '%') {
            sh_out_c(&o, *fmt);
            fmt++;
            continue;
        }
        fmt++;                                  /* 跳过 '%' */
        if (*fmt == '%') {                      /* "%%" -> "%" */
            sh_out_c(&o, '%');
            fmt++;
            continue;
        }
        if (*fmt == '\0') {
            break;                              /* 尾部孤立 '%'：丢弃 */
        }

        /* ── 标志位（可叠加：%-0+）── */
        for (;;) {
            if (*fmt == '-') {
                left = true;
                fmt++;
            } else if (*fmt == '0') {
                zero = true;
                fmt++;
            } else if (*fmt == '+') {
                plus = true;
                fmt++;
            } else {
                break;
            }
        }

        /* ── 宽度（N ≤ 99，超出部分忽略）── */
        while ((*fmt >= '0') && (*fmt <= '9')) {
            if (width < 100) {
                width = (width * 10) + (int)(*fmt - '0');
                if (width > 99) {
                    width = 99;
                }
            }
            fmt++;
        }

        /* ── 长度修饰 ── */
        if (*fmt == 'l') {
            is_long = true;
            fmt++;
        }

        conv = *fmt;
        if (conv == '\0') {
            break;                              /* "%l" 结尾：丢弃 */
        }
        fmt++;

        switch (conv) {
            case 'd':
            case 'i': {
                long          v  = is_long ? va_arg(ap, long) : (long)va_arg(ap, int);
                unsigned long uv;
                if (v < 0L) {
                    /* 先 +1 再取负，规避 LONG_MIN 取负溢出（UB） */
                    uv   = (unsigned long)(-(v + 1L)) + 1UL;
                    sign = '-';
                } else {
                    uv   = (unsigned long)v;
                    sign = plus ? '+' : '\0';
                }
                blen = sh_utoa(body, uv, 10U, false);
                sh_emit_num(&o, body, blen, sign, width, left, zero);
                break;
            }
            case 'u': {
                unsigned long v = is_long ? va_arg(ap, unsigned long)
                                          : (unsigned long)va_arg(ap, unsigned int);
                blen = sh_utoa(body, v, 10U, false);
                sh_emit_num(&o, body, blen, '\0', width, left, zero);
                break;
            }
            case 'x': {
                unsigned long v = is_long ? va_arg(ap, unsigned long)
                                          : (unsigned long)va_arg(ap, unsigned int);
                blen = sh_utoa(body, v, 16U, false);
                sh_emit_num(&o, body, blen, '\0', width, left, zero);
                break;
            }
            case 'X': {
                unsigned long v = is_long ? va_arg(ap, unsigned long)
                                          : (unsigned long)va_arg(ap, unsigned int);
                blen = sh_utoa(body, v, 16U, true);
                sh_emit_num(&o, body, blen, '\0', width, left, zero);
                break;
            }
            case 'c': {
                int ch = va_arg(ap, int);
                body[0] = (char)ch;
                blen = 1U;
                sh_emit_num(&o, body, blen, '\0', width, left, false);
                break;
            }
            case 's': {
                const char *s = va_arg(ap, const char *);
                size_t      slen;
                size_t      k;
                int         pad;
                if (s == NULL) {
                    s = "(null)";
                }
                slen = strlen(s);
                pad  = (width > (int)slen) ? (width - (int)slen) : 0;
                if (!left) {
                    for (k = 0U; k < (size_t)pad; k++) {
                        sh_out_c(&o, ' ');
                    }
                }
                for (k = 0U; k < slen; k++) {
                    sh_out_c(&o, s[k]);
                }
                if (left) {
                    for (k = 0U; k < (size_t)pad; k++) {
                        sh_out_c(&o, ' ');
                    }
                }
                break;
            }
            default: {
                /* 未知转换：原样输出 '%' 与该字符，便于发现格式串写错 */
                sh_out_c(&o, '%');
                sh_out_c(&o, conv);
                break;
            }
        }
    }

    /* 保证以 \0 结尾（容量允许时） */
    if (o.size > 0U) {
        size_t end = (o.n < o.size) ? o.n : (o.size - 1U);
        o.dst[end] = '\0';
    }
    return (int)o.n;
}

/* ── I/O 绑定 ───────────────────────────────────────────────────── */

hal_status_t sh_bind_io(const sh_io_t *io)
{
    if ((io == NULL) || (io->getc == NULL) || (io->write == NULL) || (io->ms == NULL)) {
        return HAL_ERR_PARAM;
    }
    s_io = io;
    return HAL_OK;
}

int sh_io_getc(void)
{
    if (s_io == NULL) {
        return -1;
    }
    return s_io->getc();
}

uint32_t sh_io_ms(void)
{
    if (s_io == NULL) {
        return 0U;
    }
    return s_io->ms();
}

void sh_io_set_mute(bool on)
{
    s_muted = on;
    if (on) {
        /* 静音前已入队的内容也一并丢弃：否则"静音"看起来没生效，
         * 而实际上只是旧内容延迟送出，排查时极易误判。 */
        if (s_tx_ready != 0U) {
            lwrb_reset(&s_tx_rb);
        }
    }
}

/* ── TX 环 ──────────────────────────────────────────────────────── */

/**
 * @brief TX 环初始化（由 @ref sh_init 调用）
 * @details 重复调用安全（`lwrb_init` 会把读写指针复位）。
 *          @ref SH_TX_RING 为 1024 时**实际可存 1023 字节** ——
 *          lwrb 用"写指针 = 读指针 - 1"表示满，必然浪费一格。
 */
void sh_io_init(void)
{
    s_tx_ready = lwrb_init(&s_tx_rb, s_tx_storage, (lwrb_sz_t)SH_TX_RING);
    s_tx_drop  = 0U;
}

/**
 * @brief 把一段字节压入 TX 环（环满则丢弃并计数）
 * @param[in] data 数据指针
 * @param[in] len  长度
 * @note  环未就绪（`lwrb_init` 失败）时全部计入丢弃，不静默吞掉。
 */
/** @brief 排空前向声明（@ref sh_tx_push 在环满时要就地排空） */
void sh_tx_drain(void);

/**
 * @brief 把一段字节压入 TX 环；环满时**就地排空续写**，不丢数据
 *
 * @param[in] data 数据指针
 * @param[in] len  长度
 *
 * @details 原实现环满即丢弃并只加计数 —— 对命令输出是错的：`help` 约 1.4 KB
 *          而环只有 1023 字节可用，实测尾部 457 字节**静默消失**，使用者看到
 *          半截命令列表，只有 `ver` 的 drop 计数能证明丢了东西。
 *
 *          改为"满了就排一片再写"：
 *            - 短输出（绝大多数）永远不会进入这个分支 ⇒ 仍是非阻塞的；
 *            - 只有超过环容量的长输出才会有界阻塞，时长由数据量决定，
 *              与 `s_tx_queue_mode == 0` 时的直写等价；
 *            - UART 侧无进展（`s_io == NULL` 或排空后仍写不进）时**放弃剩余并计数**，
 *              绝不死循环。
 *
 * @note  环未就绪（`s_tx_ready == 0`）时仍然全丢弃 —— 那说明 `sh_init()` 没跑，
 *        是装配错误，不是背压。
 */
static void sh_tx_push(const uint8_t *data, uint16_t len)
{
    const uint8_t *p      = data;
    uint32_t       remain = (uint32_t)len;
    lwrb_sz_t      written;

    if ((s_tx_ready == 0U) || (data == NULL)) {
        s_tx_drop += (uint32_t)len;
        return;
    }

    written = lwrb_write(&s_tx_rb, p, (lwrb_sz_t)remain);
    p      += written;
    remain -= (uint32_t)written;

    while (remain > 0U) {
        if (s_io == NULL) {
            s_tx_drop += remain;        /* 无出口：计数后放弃，不死循环 */
            return;
        }
        sh_tx_drain();                  /* 排一片（≤ SH_TX_CHUNK）腾空间 */

        written = lwrb_write(&s_tx_rb, p, (lwrb_sz_t)remain);
        if (written == 0U) {
            s_tx_drop += remain;        /* 排空也没腾出空间：UART 异常 */
            return;
        }
        p      += written;
        remain -= (uint32_t)written;
    }
}

void sh_tx_drain(void)
{
    uint8_t   chunk[SH_TX_CHUNK];
    lwrb_sz_t got;

    s_tx_queue_mode = 1U;           /* 主循环已跑：此后输出改走排队 */

    if ((s_io == NULL) || (s_tx_ready == 0U)) {
        return;
    }

    got = lwrb_read(&s_tx_rb, chunk, (lwrb_sz_t)SH_TX_CHUNK);
    if (got > 0UL) {
        s_io->write(chunk, (uint16_t)got);
    }
}

uint16_t sh_tx_backlog(void)
{
    return (uint16_t)lwrb_get_full(&s_tx_rb);
}

uint32_t sh_tx_dropped(void)
{
    return s_tx_drop;
}

/* ── 输出接口 ───────────────────────────────────────────────────── */

void sh_puts(const char *s)
{
    size_t len;

    if ((s_io == NULL) || (s == NULL) || s_muted) {
        return;
    }
    len = strlen(s);
    if (len > 0xFFFFU) {
        len = 0xFFFFU;              /* 截断到环形缓冲可寻址范围 */
    }

    if (s_tx_queue_mode == 0U) {
        /* 启动阶段：阻塞直写，保证上电日志即时且严格有序 */
        s_io->write((const uint8_t *)s, (uint16_t)len);
        return;
    }
    /* 只入队、不在此排空：一条命令常连续打印十几行，
     * 若每次都排空一片，单圈阻塞会被行数乘起来（实测 20 行 → 17 ms）。
     * 排空统一由 sh_task 每圈一片完成。 */
    sh_tx_push((const uint8_t *)s, (uint16_t)len);
}

void sh_putch(char c)
{
    uint8_t b = (uint8_t)c;

    if ((s_io == NULL) || s_muted) {
        return;
    }
    if (s_tx_queue_mode == 0U) {
        s_io->write(&b, 1U);
        return;
    }
    sh_tx_push(&b, 1U);
}

int sh_vprint(const char *fmt, va_list ap)
{
    static char buf[SH_PRINT_BUF];  /* 裸机单线程，静态缓冲安全 */
    int         n;

    n = sh_vsnprintf(buf, sizeof(buf), fmt, ap);
    sh_puts(buf);
    return n;
}

int sh_print(const char *fmt, ...)
{
    va_list ap;
    int     n;

    va_start(ap, fmt);
    n = sh_vprint(fmt, ap);
    va_end(ap);
    return n;
}

int sh_snprintf(char *buf, size_t size, const char *fmt, ...)
{
    va_list ap;
    int     n;

    va_start(ap, fmt);
    n = sh_vsnprintf(buf, size, fmt, ap);
    va_end(ap);
    return n;
}

/* ── 半主机桩（非 microlib 下提供，避免无调试器时 BKPT 挂死）────── */
#if (defined(__CC_ARM) || defined(__ARMCC_VERSION)) && !defined(__MICROLIB__)
__asm(".global __use_no_semihosting\n\t");

void _sys_exit(int x)                 { (void)x; for (;;) { } }
int  _sys_close(int f)                { (void)f; return -1; }
int  _sys_open(const char *p, int o)  { (void)p; (void)o; return -1; }
int  _sys_read(int f, char *b, int n){ (void)f; (void)b; (void)n; return 0; }
int  _sys_write(int f, const char *b, int n) { (void)f; (void)b; (void)n; return n; }
int  _sys_istty(int f)                { (void)f; return 0; }
int  _sys_seek(int f, long o)         { (void)f; (void)o; return -1; }
long _sys_flen(int f)                 { (void)f; return 0L; }
void _ttywrch(int ch)                 { (void)ch; }
#endif
