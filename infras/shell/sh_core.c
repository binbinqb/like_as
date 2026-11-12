/**
 * @file    sh_core.c
 * @brief   sh 命令引擎 + 行编辑状态机（全部非阻塞）
 *
 * @details 本文件是 shell 的"大脑"，包含两套彼此独立的状态机：
 *
 *          @section SH_CORE_ENGINE ① 命令引擎
 *          - **查找**：遍历 `hal_sh_cmd` 段（链接器自动生成边界符号），线性比较命令名；
 *          - **分词**：引号感知，`'a b'` / `"a b"` 作为单个参数，引号本身被剥离；
 *          - **后缀**：识别 `&period` / `&period,nloops` / `&min~max` 转后台循环执行；
 *          - **执行**：同步调用命令函数，返回码遵循 @ref hal_status_t 语义。
 *
 *          @section SH_CORE_EDIT ② 行编辑状态机
 *          按键处理全程非阻塞，**绝不因等待 ESC 后续字节而卡住主循环**：
 *          ESC 之后启动超时计时（@ref SH_ESC_TIMEOUT_MS），超时未补齐即丢弃。
 *          这正是参考实现最严重缺陷的修法 —— 旧版收到 ESC 后无条件阻塞读两次，
 *          一旦上位机只发了单个 ESC，主循环就永久停在那里。
 *
 *          支持的编辑能力：
 *          | 按键 | 行为 |
 *          |---|---|
 *          | `←` / `→` | 光标左右移动 |
 *          | `Home` / `End` | 光标到行首 / 行尾 |
 *          | `↑` / `↓` | 历史回滚；**光标在数字上时改为数字 ±1 并立即执行** |
 *          | 退格 / `DEL` | 删除光标前一字符 |
 *          | 可打印字符 | 在光标处插入（支持行中插入） |
 *          | `Tab` | 打印命令列表（仅手动模式） |
 *          | `Alt+M` | 手动 / 自动模式切换 |
 *          | `Ctrl+R` | 立即执行 `*RST`（复位） |
 *          | `Ctrl+X` | 立即执行 `kill all`（清后台任务） |
 *          | `Ctrl+C` | 立即执行 `pause`（暂停后台任务） |
 *
 * @note    遵守 MISRA C:2012 Required 规则；**无 goto**（规范的"不应使用"条）。
 * @warning 本文件全部接口都在**任务上下文**调用，不可重入。
 *
 * @author  binbina
 * @version 1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-10-26 | binbina | 初版。移植 ULP8 shell.c + cmd.c 的命令引擎与行编辑；补齐旧 hal_sh 缺失的光标左右/Home/End/行中插入删除/数字快调；环执行改为静态 context 池（深度 2）；撤销 ULP8 的 goto error 清理写法 |
 */

#include "sh.h"
#include "sh_cfg.h"
#include "sh_internal.h"

#include <string.h>

/* ── ANSI 控制序列（只保留实际用到的几条） ──────────────────────── */
/** @brief 清除光标到行尾 */
#define SH_ANSI_CLR_EOL         "\033[K"
/** @brief 保存光标位置 */
#define SH_ANSI_SAVE_CUR        "\033[s"
/** @brief 恢复光标位置 */
#define SH_ANSI_REST_CUR        "\033[u"
/** @brief 光标左移一格 */
#define SH_ANSI_CUR_LEFT        "\033[D"
/** @brief 光标右移一格 */
#define SH_ANSI_CUR_RIGHT       "\033[C"

/* ── 组合键编码（ESC 前缀 + 后续字节压进同一个 uint32） ─────────── */
/** @brief Alt+m（小写） */
#define SH_KEY_ALT_M_L  (0x00001B00UL | (uint32_t)'m')
/** @brief Alt+M（大写） */
#define SH_KEY_ALT_M_U  (0x00001B00UL | (uint32_t)'M')
/** @brief 方向上 */
#define SH_KEY_UP       (0x001B5B00UL | (uint32_t)'A')
/** @brief 方向下 */
#define SH_KEY_DOWN     (0x001B5B00UL | (uint32_t)'B')
/** @brief 方向右 */
#define SH_KEY_RIGHT    (0x001B5B00UL | (uint32_t)'C')
/** @brief 方向左 */
#define SH_KEY_LEFT     (0x001B5B00UL | (uint32_t)'D')
/** @brief Home（ESC [ 1 ~） */
#define SH_KEY_HOME     (0x001B5B00UL | (uint32_t)'1')
/** @brief End（ESC [ 4 ~） */
#define SH_KEY_END      (0x001B5B00UL | (uint32_t)'4')

/* ── 静态状态 ───────────────────────────────────────────────────── */

/** @brief 输入行缓冲 */
static char     s_line[SH_CMD_LINE_MAX];
/** @brief 当前行有效长度（不含 `\0`） */
static uint16_t s_line_len;
/** @brief 光标位置（= 新字符插入位置，0..line_len） */
static uint16_t s_caret;
/** @brief ESC 状态机：0 普通 / 1 已收 ESC / 2 已收 ESC [ / 3 已收 ESC [ 1|4 */
static uint8_t  s_esc;
/** @brief ESC 状态机暂存的数字键（'1' 或 '4'） */
static uint8_t  s_esc_code;
/** @brief ESC 序列起始时刻（ms），用于超时丢弃 */
static uint32_t s_esc_t0;

/** @brief 当前运行模式 */
static sh_mode_t s_mode;
/** @brief 配置位（@ref SH_CONFIG_MUTE 等） */
static uint32_t  s_config;
/** @brief 命令名前缀（NULL = 无前缀） */
static const char *s_prefix;

/** @brief 非循环命令专用上下文（静态，避免每次执行都要池分配） */
static sh_context_t s_ctx_main;

/**
 * @brief 阻塞读行（@ref sh_readline）专用标志
 * @details 置位时行编辑状态机在收到回车后**只结束本次读取**，不执行命令。
 */
static bool     s_rl_active;
/** @brief 阻塞读行已完成标志 */
static bool     s_rl_done;

/** @brief 当前正在执行的上下文（供 @ref sh_is_repeated 查询） */
sh_context_t *sh_ctx_current;

/* ══════════════════════════════════════════════════════════════════
 * 一、命令名前缀
 * ══════════════════════════════════════════════════════════════════ */

void sh_opt_prefix(const char *prefix)
{
    s_prefix = prefix;
}

/**
 * @brief 判断命令名是否带当前前缀
 * @param[in] name 命令名
 * @retval true  带前缀
 * @retval false 未设前缀 / 不带前缀
 */
static bool sh_has_prefix(const char *name)
{
#if (SH_FEATURE_PREFIX == 1U)
    bool yes = false;

    if ((s_prefix != NULL) && (name != NULL)) {
        size_t n = strlen(s_prefix);
        yes = (strncmp(name, s_prefix, n) == 0) ? true : false;
    }
    return yes;
#else
    (void)name;
    return false;
#endif
}

/**
 * @brief 去掉命令名的前缀部分
 * @param[in] name 命令名
 * @return 去掉前缀后的名字；无前缀时原样返回
 * @note  命令名**恰好等于**前缀时不剥离 —— 否则会得到空名字，
 *        反而不匹配任何命令。
 */
static const char *sh_skip_prefix(const char *name)
{
    if (sh_has_prefix(name)) {
        size_t n = strlen(s_prefix);
        if (name[n] != '\0') {
            return &name[n];
        }
    }
    return name;
}

/* ══════════════════════════════════════════════════════════════════
 * 二、命令段遍历与查找
 * ══════════════════════════════════════════════════════════════════ */

const sh_cmd_t *sh_cmd_find(const char *name)
{
    const sh_cmd_t *p;
    const char     *key;

    if (name == NULL) {
        return NULL;
    }
    key = sh_skip_prefix(name);

    for (p = SH_CMD_START; p < SH_CMD_STOP; p++) {
        if ((p->name == NULL) || (p->func == NULL)) {
            continue;
        }
        if (strcmp(p->name, key) == 0) {
            return p;
        }
    }
    return NULL;
}

void sh_cmd_list_print(void)
{
    const sh_cmd_t *p;

    for (p = SH_CMD_START; p < SH_CMD_STOP; p++) {
        if ((p->name == NULL) || (p->func == NULL)) {
            continue;
        }
        sh_print("  %-12s %s\r\n", p->name, (p->help != NULL) ? p->help : "");
    }
}

/* ══════════════════════════════════════════════════════════════════
 * 三、分词
 * ══════════════════════════════════════════════════════════════════ */

/**
 * @brief 引号感知分词（原地改写：把分隔符替换为 `\0`）
 * @param[in,out] line     输入行；返回时被改写为 `\0` 分隔的多段
 * @param[out]    argv     参数数组
 * @param[in]     max_args 数组容量
 * @return 参数个数（0 表示空行）
 *
 * @details 规则：
 *          - 空白（空格 / 制表符）分隔参数；
 *          - 参数**以引号开头**时，引号内的空白保留，引号本身被剥离；
 *          - 引号只在参数起始位置生效，`a"b` 不视为引用（与 ULP8 一致）。
 */
static uint32_t sh_tokenize(char *line, char **argv, uint32_t max_args)
{
    uint32_t ac = 0U;
    char    *p  = line;

    while ((*p != '\0') && (ac < max_args)) {
        char quote = '\0';

        /* 跳过前导空白 */
        while ((*p == ' ') || (*p == '\t')) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        if ((*p == '"') || (*p == '\'')) {
            quote = *p;
            p++;
        }

        argv[ac] = p;
        ac++;

        /* 读到一个参数，直到分隔符或配对引号 */
        while (*p != '\0') {
            if (quote != '\0') {
                if (*p == quote) {
                    *p = '\0';
                    p++;
                    break;
                }
            } else {
                if ((*p == ' ') || (*p == '\t')) {
                    *p = '\0';
                    p++;
                    break;
                }
            }
            p++;
        }
    }

    return ac;
}

/* ══════════════════════════════════════════════════════════════════
 * 四、命令执行
 * ══════════════════════════════════════════════════════════════════ */

int sh_exec_context(sh_context_t *ctx)
{
    int rc = SH_ERR;

    if ((ctx == NULL) || (ctx->cmd == NULL) || (ctx->cmd->func == NULL)) {
        return SH_ERR_PARAM;
    }
    if ((ctx->flags & SH_CTX_F_ISBUSY) != 0U) {
        return SH_ERR;              /* 防重入：同一 context 不允许并发执行 */
    }

    ctx->flags |= SH_CTX_F_ISBUSY;
    sh_ctx_current = ctx;           /* 供 sh_is_repeated / 命令回溯上下文 */

    rc = ctx->cmd->func((int)ctx->argc, ctx->argv);

    sh_ctx_current = NULL;
    ctx->flags &= (uint8_t)~SH_CTX_F_ISBUSY;
    return rc;
}

/**
 * @brief 去掉行首空白（原地前移）
 * @param[in,out] s 字符串
 * @return 新的行首指针（指向 s 内部）
 */
static char *sh_lstrip(char *s)
{
    char *p = s;

    while ((*p == ' ') || (*p == '\t')) {
        p++;
    }
    if (p != s) {
        size_t n = strlen(p);
        (void)memmove(s, p, n + 1U);
    }
    return s;
}

/**
 * @brief 去掉行尾空白（原地截断）
 * @param[in,out] s 字符串
 */
static void sh_rstrip(char *s)
{
    size_t n = strlen(s);

    while (n > 0U) {
        n--;
        if ((s[n] != ' ') && (s[n] != '\t')) {
            break;
        }
        s[n] = '\0';
    }
}

/**
 * @brief 把一个命令转成后台循环任务
 * @param[in] rawline **未经分词**的原始命令行（即 @ref sh_exec 的入参）
 * @param[in] ctx     已完成解析的上下文；此处只用其 @c cmd 指针
 * @param[in] sfx     已解析的循环后缀
 * @return 0 成功；负值表示池满
 *
 * @note  必须复制**原始**命令行，不能用 @p ctx->line：@ref sh_tokenize 是原地
 *        改写，它已把分隔符替换成 `\0`，`ctx->line` 里只剩 `argv[0]` 一段。
 *        照抄的后果实测为：`echo bg&100` 的后台任务每圈只打印
 *        `argv[0] = 'echo'`，`bg` 这个参数静默丢失 —— 命令行在，语义没了。
 *
 *        另外，@p rawline 里循环后缀 `&` 还没剥掉（`sh_exec` 只剥了内部副本），
 *        所以要在副本里再剥一次，否则 `&100` 会变成一个多余参数。
 */
static int sh_bg_spawn(const char *rawline, const sh_context_t *ctx,
                       const sh_suffix_t *sfx)
{
    sh_context_t *bg;
    char         *amp;

    bg = sh_ctx_alloc();
    if (bg == NULL) {
        sh_puts(SH_RET_NOMEM);
        return SH_ERR_NOMEM;
    }

    (void)memcpy(bg->line, rawline, sizeof(bg->line) - 1U);
    bg->line[sizeof(bg->line) - 1U] = '\0';

    amp = strrchr(bg->line, '&');
    if ((amp != NULL) && (amp != bg->line)) {
        *amp = '\0';
        sh_rstrip(bg->line);
    }

    bg->argc = (uint8_t)sh_tokenize(bg->line, bg->argv, SH_MAX_ARGS);
    bg->cmd  = ctx->cmd;

    bg->flags         = SH_CTX_F_LOOP;
    bg->period_ms     = sfx->period_ms;
    bg->period_max_ms = sfx->period_max_ms;
    bg->nloops        = sfx->nloops;
    bg->lopcnt        = 0U;
    bg->t_next        = sh_io_ms() + (uint32_t)sfx->period_ms;

    if (sfx->random) {
        bg->flags |= SH_CTX_F_RANDOM;
    }

    sh_bg_queue_add(bg);
    return SH_OK;
}

int sh_exec(const char *cmdline)
{
    char        *amp;
    sh_suffix_t  sfx;
    uint32_t     argc;
    int          rc;

    if (cmdline == NULL) {
        return SH_ERR_PARAM;
    }
    if ((s_ctx_main.flags & SH_CTX_F_ISBUSY) != 0U) {
        return SH_ERR;              /* 不可重入：命令内部不得再调 sh_exec */
    }

    /* ── ① 复制命令行到静态上下文 ── */
    (void)memset(&s_ctx_main, 0, sizeof(s_ctx_main));
    (void)memcpy(s_ctx_main.line, cmdline, sizeof(s_ctx_main.line) - 1U);
    s_ctx_main.line[sizeof(s_ctx_main.line) - 1U] = '\0';

    (void)sh_lstrip(s_ctx_main.line);
    if (s_ctx_main.line[0] == '\0') {
        return SH_OK;               /* 空行：什么也不做 */
    }

    /* ── ② 解析并剥离 `&` 循环后缀 ── */
    (void)memset(&sfx, 0, sizeof(sfx));
    amp = strrchr(s_ctx_main.line, '&');
    if ((amp != NULL) && (amp != s_ctx_main.line)) {
        if (!sh_parse_suffix(amp, &sfx)) {
            sh_puts(SH_RET_PARA);
            return SH_ERR_PARAM;
        }
        *amp = '\0';
        sh_rstrip(s_ctx_main.line);
        if (s_ctx_main.line[0] == '\0') {
            sh_puts(SH_RET_PARA);   /* 只有 "&100" 没有命令 */
            return SH_ERR_PARAM;
        }
    }

    /* ── ③ 执行前置钩子（拿到完整命令行，尚未分词）── */
    if (sh_on_exec(s_ctx_main.line) != 0) {
        return SH_OK;               /* 钩子拒绝执行：是否提示由钩子自己决定 */
    }

    /* ── ④ 分词并查找命令 ── */
    argc = sh_tokenize(s_ctx_main.line, s_ctx_main.argv, SH_MAX_ARGS);
    if (argc == 0U) {
        return SH_OK;
    }
    s_ctx_main.argc = (uint8_t)argc;
    s_ctx_main.cmd  = sh_cmd_find(s_ctx_main.argv[0]);
    if (s_ctx_main.cmd == NULL) {
        sh_puts(SH_RET_NOCMD);
        return SH_ERR_NOTFOUND;
    }

    /* ── ⑤ 执行 或 转后台 ── */
    if (sfx.loop) {
        rc = sh_bg_spawn(cmdline, &s_ctx_main, &sfx);
    } else {
        rc = sh_exec_context(&s_ctx_main);
    }
    return rc;
}

/* ══════════════════════════════════════════════════════════════════
 * 五、行编辑 — 基础操作
 * ══════════════════════════════════════════════════════════════════ */

/**
 * @brief 清空当前行（缓冲 + 光标）
 */
static void sh_line_reset(void)
{
    s_line_len = 0U;
    s_caret    = 0U;
    s_line[0]  = '\0';
}

/**
 * @brief 在光标处插入一个字符（行中插入时后续内容右移）
 * @param[in] c 待插入字符
 * @note  行满时**静默丢弃**：覆盖已有内容比丢弃更糟（用户会以为输入成功）。
 */
static void sh_line_insert(uint8_t c)
{
    uint16_t i;

    if (s_line_len >= (uint16_t)(SH_CMD_LINE_MAX - 1U)) {
        return;
    }

    for (i = s_line_len; i > s_caret; i--) {
        s_line[i] = s_line[i - 1U];
    }
    s_line[s_caret] = (char)c;
    s_line_len++;
    s_caret++;
    s_line[s_line_len] = '\0';

    if (s_mode == SH_MODE_MANUAL) {
        /* 打出刚插入的字符 -> 保存光标 -> 清到行尾 -> 打印剩余 -> 恢复光标 */
        sh_putch((char)c);
        sh_puts(SH_ANSI_SAVE_CUR);
        sh_puts(SH_ANSI_CLR_EOL);
        sh_puts(&s_line[s_caret]);
        sh_puts(SH_ANSI_REST_CUR);
    }
}

/**
 * @brief 删除光标前一个字符（行中删除时后续内容左移）
 */
static void sh_line_del_back(void)
{
    uint16_t i;

    if (s_caret == 0U) {
        return;
    }

    for (i = (uint16_t)(s_caret - 1U); i < s_line_len; i++) {
        s_line[i] = s_line[i + 1U];
    }
    s_line_len--;
    s_caret--;
    s_line[s_line_len] = '\0';

    if (s_mode == SH_MODE_MANUAL) {
        sh_putch('\b');
        sh_puts(SH_ANSI_SAVE_CUR);
        sh_puts(SH_ANSI_CLR_EOL);
        sh_puts(&s_line[s_caret]);
        sh_puts(SH_ANSI_REST_CUR);
    }
}

/**
 * @brief 整行重绘（历史回滚、数字快调后使用）
 * @details 用空格覆盖旧内容再重画，避免残留字符；最后把光标退回 caret 位置。
 */
static void sh_line_redraw(void)
{
    uint16_t plen;
    uint16_t i;

    if (s_mode != SH_MODE_MANUAL) {
        return;
    }

    plen = (uint16_t)(sizeof(SH_PROMPT) - 1U);

    sh_putch('\r');
    for (i = 0U; i < (uint16_t)(s_line_len + plen); i++) {
        sh_putch(' ');
    }
    sh_putch('\r');
    sh_puts(SH_PROMPT);
    sh_puts(s_line);

    /* 光标归位到 caret：从行尾退回 (len - caret) 格 */
    for (i = s_caret; i < s_line_len; i++) {
        sh_puts(SH_ANSI_CUR_LEFT);
    }
}

/**
 * @brief 把历史条目回填到当前行
 * @param[in] h 历史字符串；NULL 表示清空当前行
 */
static void sh_line_apply_history(const char *h)
{
    size_t n;

    if (h == NULL) {
        sh_line_reset();
        sh_line_redraw();
        return;
    }

    n = strlen(h);
    if (n > (size_t)(SH_CMD_LINE_MAX - 1U)) {
        n = (size_t)(SH_CMD_LINE_MAX - 1U);
    }
    (void)memcpy(s_line, h, n);
    s_line[n] = '\0';
    s_line_len = (uint16_t)n;
    s_caret    = (uint16_t)n;
    sh_line_redraw();
}

/**
 * @brief 数字快调：光标所在数字段 ±1
 * @param[in] up true = 加一，false = 减一
 * @retval true  光标处是数字，已修改
 * @retval false 光标处不是数字，未修改
 *
 * @details ULP8 的招牌调试特性：`dio PA0 1` 把光标停在 `1` 上按 ↑，
 *          直接变成 `dio PA0 2` 并执行 —— 调参数不用重打整行。
 *          只影响**光标所在的那一段连续数字**（可跨 `.`，用于版本号 / IP 地址）。
 */
static bool sh_line_inc_dec(bool up)
{
    int32_t i;

    if (sh_is_digit(s_line[s_caret]) == false) {
        return false;
    }

    for (i = (int32_t)s_caret; i >= 0; i--) {
        char ch = s_line[i];

        if (ch == '.') {
            continue;               /* 允许跨过小数点，如 1.2.3 */
        }
        if (sh_is_digit(ch) == false) {
            break;
        }

        if (up) {
            if (ch != '9') {
                s_line[i] = (char)(ch + 1);
                return true;
            }
            s_line[i] = '0';        /* 9 -> 0 并继续进位 */
        } else {
            if (ch != '0') {
                s_line[i] = (char)(ch - 1);
                return true;
            }
            s_line[i] = '9';        /* 0 -> 9 并继续借位 */
        }
    }
    return true;
}

/* ══════════════════════════════════════════════════════════════════
 * 六、行编辑 — 按键处理
 * ══════════════════════════════════════════════════════════════════ */

/**
 * @brief 执行当前行（回车 / 快捷键触发）
 * @details 抽出成独立函数，因为"回车"与几条 Ctrl 组合键共用同一收尾路径。
 */
static void sh_line_commit(void)
{
    if (s_mode == SH_MODE_MANUAL) {
        sh_puts("\r\n");
    }

    /* 阻塞读行模式：只结束本次读取，不执行命令 */
    if (s_rl_active) {
        s_line[s_line_len] = '\0';
        s_rl_done = true;
        return;
    }

    sh_rstrip(s_line);
    sh_history_add(s_line);
    (void)sh_exec(s_line);

    sh_line_reset();
    sh_history_reset_cursor();

    if (s_mode == SH_MODE_MANUAL) {
        sh_puts(SH_PROMPT);
    }
}

/**
 * @brief 把一条预设命令填进当前行并立即执行
 * @param[in] cmd 命令字符串（字面量，长度必须 < SH_CMD_LINE_MAX）
 * @note  用于 Ctrl+R / Ctrl+C / Ctrl+X / Alt+M 这些"快捷键即命令"的场景。
 */
static void sh_line_inject(const char *cmd)
{
    size_t n = strlen(cmd);

    if (n > (size_t)(SH_CMD_LINE_MAX - 1U)) {
        n = (size_t)(SH_CMD_LINE_MAX - 1U);
    }
    (void)memcpy(s_line, cmd, n);
    s_line[n] = '\0';
    s_line_len = (uint16_t)n;
    s_caret    = 0U;
    sh_line_commit();
}

/**
 * @brief 处理 ESC 后续字节
 * @param[in] c 当前字节
 * @return true = 已消费（调用方不再按普通键处理）
 */
static bool sh_key_escape(uint8_t c)
{
    if (s_esc == 1U) {
        if ((c == 'm') || (c == 'M')) {
            s_esc = 0U;
            /* Alt+M：手动 / 自动模式切换 */
            (void)sh_set_mode((s_mode == SH_MODE_AUTO) ? SH_MODE_MANUAL : SH_MODE_AUTO);
            if (s_mode == SH_MODE_MANUAL) {
                sh_puts("\r\n");
                sh_puts(SH_PROMPT);
                sh_puts(s_line);
            } else {
                sh_puts("\r\n");
            }
            return true;
        }
        if (c == '[') {
            /* CSI 起始：进入序列累积态，**不要**在这里丢掉 ——
             * 早期实现在此直接置 s_esc=0，导致所有方向键失效。 */
            s_esc    = 2U;
            s_esc_t0 = sh_io_ms();
            return true;
        }
        s_esc = 0U;                 /* 其他 ESC 序列：整段丢弃，不阻塞 */
        return true;
    }

    if (s_esc == 2U) {
        s_esc = 0U;

        if (c == 'A') {
            /* ↑：光标在行尾时回滚历史；在行中且停在数字上时做数字 ±1 并立即执行 */
            if (s_caret < s_line_len) {
                if (sh_line_inc_dec(true)) {
                    sh_line_redraw();
                    sh_line_commit();
                }
            } else {
                sh_line_apply_history(sh_history_prev());
            }
        } else if (c == 'B') {
            /* ↓：光标在行尾时前进历史；在行中且停在数字上时做数字 ∓1 并立即执行 */
            if (s_caret < s_line_len) {
                if (sh_line_inc_dec(false)) {
                    sh_line_redraw();
                    sh_line_commit();
                }
            } else {
                sh_line_apply_history(sh_history_next());
            }
        } else if (c == 'C') {
            if (s_caret < s_line_len) {
                s_caret++;
                if (s_mode == SH_MODE_MANUAL) {
                    sh_puts(SH_ANSI_CUR_RIGHT);
                }
            }
        } else if (c == 'D') {
            if (s_caret > 0U) {
                s_caret--;
                if (s_mode == SH_MODE_MANUAL) {
                    sh_puts(SH_ANSI_CUR_LEFT);
                }
            }
        } else if ((c == '1') || (c == '4')) {
            s_esc_code = c;
            s_esc      = 3U;
            s_esc_t0   = sh_io_ms();
        } else {
            /* 未识别的 CSI 序列：丢弃 */
        }
        return true;
    }

    if (s_esc == 3U) {
        s_esc = 0U;

        if (c == '~') {
            if (s_esc_code == '1') {
                /* Home：光标到行首 */
                if ((s_mode == SH_MODE_MANUAL) && (s_caret > 0U)) {
                    sh_print("\033[%uD", (unsigned)s_caret);
                }
                s_caret = 0U;
            } else {
                /* End：光标到行尾 */
                if (s_mode == SH_MODE_MANUAL) {
                    uint16_t n = (uint16_t)(s_line_len - s_caret);
                    if (n > 0U) {
                        sh_print("\033[%uC", (unsigned)n);
                    }
                }
                s_caret = s_line_len;
            }
        }
        return true;
    }

    return false;
}

/**
 * @brief 处理普通键（非 ESC 续接）
 * @param[in] c 当前字节
 */
static void sh_key_normal(uint8_t c)
{
    switch (c) {
        case (uint8_t)'\r':
        case (uint8_t)'\n':
            sh_line_commit();
            break;

        case 0x08U:                 /* 退格 */
        case 0x7FU:                 /* DEL */
            sh_line_del_back();
            break;

        case 0x12U:                 /* Ctrl+R：复位 */
            sh_line_inject("*RST");
            break;

        case 0x18U:                 /* Ctrl+X：清后台任务 */
            sh_line_inject("kill all");
            break;

        case 0x03U:                 /* Ctrl+C：暂停后台任务 */
            sh_line_inject("pause");
            break;

        case (uint8_t)'\t':         /* Tab：列出全部命令（仅手动模式） */
            if (s_mode == SH_MODE_MANUAL) {
                sh_puts("\r\n");
                sh_cmd_list_print();
                sh_puts(SH_PROMPT);
                sh_puts(s_line);
            }
            break;

        default:
            if (sh_is_print((char)c)) {
                sh_line_insert(c);
            }
            break;
    }
}

/**
 * @brief 单字节入口（行编辑状态机核心）
 * @param[in] c 已接收字节
 * @details 两级分派：处于 ESC 序列中间时先交给续接处理；
 *          否则 ESC 开启新序列，其余按键走普通处理。
 */
static void sh_on_char(uint8_t c)
{
    if ((s_esc != 0U) && sh_key_escape(c)) {
        return;
    }

    if (c == 0x1BU) {
        s_esc    = 1U;
        s_esc_t0 = sh_io_ms();
        return;
    }

    sh_key_normal(c);
}

/* ══════════════════════════════════════════════════════════════════
 * 七、对外 API
 * ══════════════════════════════════════════════════════════════════ */

void sh_init(void)
{
    s_line_len  = 0U;
    s_caret     = 0U;
    s_esc       = 0U;
    s_esc_code  = 0U;
    s_esc_t0    = 0U;
    s_mode      = SH_DEFAULT_MODE;
    s_config    = 0U;
    s_prefix    = NULL;
    s_rl_active = false;
    s_rl_done   = false;

    sh_ctx_current = NULL;

    (void)memset(s_line, 0, sizeof(s_line));
    (void)memset(&s_ctx_main, 0, sizeof(s_ctx_main));

    sh_io_init();
    sh_io_set_mute(false);
    sh_history_clear();
    sh_bg_reset();
}

void sh_task(void)
{
    int c;

    /* ① 排空 TX 环一片：把阻塞开销摊到多圈 */
    sh_tx_drain();

    /* ② ESC 序列超时丢弃：这是"绝不卡死主循环"的关键前提 */
    if ((s_esc != 0U) && ((uint32_t)(sh_io_ms() - s_esc_t0) >= (uint32_t)SH_ESC_TIMEOUT_MS)) {
        s_esc = 0U;
    }

    /* ③ 推进后台循环命令（暂停位由 sh_bg_run 内部判断） */
    sh_bg_run();

    /* ④ 锁定态不接收输入，但输出照常（否则无法诊断"为什么没反应"） */
    if ((s_config & SH_CONFIG_LOCK) != 0U) {
        return;
    }

    /* ⑤ 非阻塞读取全部待处理字节 */
    while ((c = sh_io_getc()) >= 0) {
        sh_on_char((uint8_t)c);
    }
}

void sh_banner(void)
{
    sh_print("\r\nsh %s ready", SH_VERSION_STR);
    if (s_mode == SH_MODE_MANUAL) {
        sh_print("  (MANUAL, Alt+M -> AUTO)\r\n" SH_PROMPT);
    } else {
        sh_print("  (AUTO, Alt+M -> MANUAL)\r\n");
    }
}

sh_mode_t sh_get_mode(void)
{
    return s_mode;
}

hal_status_t sh_set_mode(sh_mode_t mode)
{
    if ((mode != SH_MODE_AUTO) && (mode != SH_MODE_MANUAL)) {
        return HAL_ERR_PARAM;
    }
    if (mode != s_mode) {
        s_mode = mode;
        sh_line_reset();
        sh_history_reset_cursor();
    }
    return HAL_OK;
}

void sh_config_set(uint32_t bits, bool on)
{
    if (on) {
        s_config |= bits;
    } else {
        s_config &= (uint32_t)~bits;
    }

    /* 静音位要同步到输出层：判断放在最底层，命令侧零改动 */
    if ((bits & SH_CONFIG_MUTE) != 0U) {
        sh_io_set_mute((s_config & SH_CONFIG_MUTE) != 0U);
    }
}

bool sh_config_get(uint32_t bits)
{
    return ((s_config & bits) == bits) ? true : false;
}

char *sh_readline(const char *prompt)
{
    /* 不可嵌套：s_line 只有一份，嵌套会让内层覆盖外层的输入 */
    if (s_rl_active) {
        return NULL;
    }

    sh_line_reset();
    sh_history_reset_cursor();
    s_rl_done   = false;
    s_rl_active = true;

    if ((prompt != NULL) && (s_mode == SH_MODE_MANUAL)) {
        sh_puts(prompt);
    }

    while (s_rl_done == false) {
        int c = sh_io_getc();

        if (c >= 0) {
            sh_on_char((uint8_t)c);
        }
        /* 必须在本循环里排空：否则提示符卡在 TX 环里出不去，
         * 人看到的是一行没有提示符的光标，误以为命令没响应。 */
        sh_tx_drain();
    }

    s_rl_active = false;
    return s_line;
}

int sh_is_repeated(void)
{
    int yes = 0;

    if ((sh_ctx_current != NULL) && ((sh_ctx_current->flags & SH_CTX_F_LOOP) != 0U)) {
        yes = (sh_ctx_current->lopcnt > 0U) ? 1 : 0;
    }
    return yes;
}

/**
 * @brief 命令执行前置钩子（**弱符号**，默认放行）
 * @param[in] cmdline 待执行命令行（已剥离 `&` 后缀）
 * @return 0 = 继续执行；非 0 = 跳过执行
 *
 * @details 供上层插入访问控制 / 审计 / 命令别名等策略，**无需改本文件**。
 *          返回非 0 时 shell 不打印任何内容 —— 是否提示由钩子自己决定。
 * @warning 在任务上下文调用；实现不得阻塞超过一个主循环周期。
 */
__attribute__((weak)) int sh_on_exec(char *cmdline)
{
    (void)cmdline;
    return 0;
}
