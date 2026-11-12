/**
 * @file    sh_cmd.c
 * @brief   sh 内建命令 —— help / ver / mode / history / pause / kill / vram / SCPI 组
 *
 * @details 内建命令与用户命令**同等待遇**：都通过 @ref SH_EXPORT_CMD 落入
 *          `hal_sh_cmd` 段，由 core 统一遍历。好处是 `help` 不需要特判内建项，
 *          新增内建命令也不必改引擎。
 *
 *          @section SH_CMD_LIST 命令清单
 *          | 命令 | 说明 | 与原 ULP8 的差异 |
 *          |---|---|---|
 *          | `help` / `*?` | 列出全部命令 | 合并为同一函数 |
 *          | `ver` | 版本 + TX 环诊断 | 新增 drop/backlog 显示 |
 *          | `mode [auto\|manual]` | 显示/切换模式 | 沿用 |
 *          | `history` | 打印历史 | 沿用 |
 *          | `pause [on\|off]` | 暂停/恢复后台任务 | 用 on/off 取代无参取反，避免"再按一次回到哪"的歧义 |
 *          | `kill all` | 清空后台任务 | 只支持 `all`（池深度 2，按序号杀没有价值） |
 *          | `vram [k [v]]` | 静态 KV 表 | 沿用语义，改为定长静态表 |
 *          | `*IDN?` | 板卡标识 | 沿用 |
 *          | `*ERR?` | 错误/断言统计 | **改为查 HAL 的 P2/P0 计数**（ULP8 查的是不存在的 sys_ecode） |
 *          | `*SYST?` | 毫秒时基 | ULP8 返回 sys_update 周期，本工程无此概念，改为返回时基 |
 *          | `*RST` | 复位 | 经 @ref sh_bind_reset 交平台执行 |
 *          | `echo` | 打印分词结果 | 沿用（调试引号解析用） |
 *
 *          **有意删除**（ULP8 有、本工程无对应硬件或概念）：
 *          `*UUID?`（无 UUID 服务）、`*WDT?`（看门狗由 hal_wdg 独立管理，
 *          不经 shell 喂）、`fault`（故意跑飞，调试器场景才需要）、
 *          `TSTP`（死循环测中断屏蔽，危险且无自动化价值）。
 *
 * @note    遵守 MISRA C:2012 Required 规则。
 * @warning `*RST` 会**真的复位**，自动化脚本调用前请确认目标板状态。
 *
 * @author  binbina
 * @version 1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-10-26 | binbina | 初版。合并 ULP8 cmd.c 的内建命令；*ERR? 改为查 HAL 的错误/断言计数；*RST 经 sh_bind_reset 交平台执行以维持分层；vram 改为定长静态表；删除无硬件对应的 4 条命令（UUID 查询、WDT 喂狗、fault、TSTP） |
 */

#include "sh.h"
#include "sh_cfg.h"
#include "sh_internal.h"

#include <string.h>

/* ══════════════════════════════════════════════════════════════════
 * 一、help / *?
 * ══════════════════════════════════════════════════════════════════ */

static int sh_builtin_help(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    sh_puts("SCPI-like:\r\n");
    sh_puts("  *IDN?          query board info\r\n");
    sh_puts("  *ERR?          query error / assert counters\r\n");
    sh_puts("  *SYST?         query millisecond timebase\r\n");
    sh_puts("  *RST           reset MCU\r\n");
    sh_puts("Built-in:\r\n");
    sh_puts("  help           list all commands\r\n");
    sh_puts("  ver            show shell version + tx diagnostics\r\n");
    sh_puts("  mode [a|m]     show/set mode (auto|manual)\r\n");
    sh_puts("  history        show command history\r\n");
    sh_puts("  pause [on|off] pause/resume background tasks\r\n");
    sh_puts("  kill all       kill all background tasks\r\n");
#if (SH_FEATURE_VRAM == 1U)
    sh_puts("  vram [k [v]]   virtual ram (key/value store)\r\n");
#endif
    sh_puts("  echo ...       print tokenized argv (for quote debugging)\r\n");
    sh_puts("Loop suffix:\r\n");
    sh_puts("  cmd&           repeat forever, default period\r\n");
    sh_puts("  cmd&100        repeat forever, 100 ms\r\n");
    sh_puts("  cmd&100,10     repeat 10 times, 100 ms\r\n");
    sh_puts("  cmd&100~500    random period in [100,500] ms\r\n");
    sh_puts("Commands:\r\n");
    sh_cmd_list_print();
    return HAL_OK;
}

/* ══════════════════════════════════════════════════════════════════
 * 二、ver / mode / history
 * ══════════════════════════════════════════════════════════════════ */

static int sh_builtin_ver(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    sh_print("sh %s\r\n", SH_VERSION_STR);
    /* TX 诊断：backlog 持续非 0 = 输出速率超出串口带宽；
     * dropped > 0 = 环满丢字节（输出被截断），需加大 SH_TX_RING */
    sh_print("tx ring: backlog=%u drop=%u%s\r\n",
             (unsigned)sh_tx_backlog(),
             (unsigned)sh_tx_dropped(),
             (sh_tx_dropped() != 0U) ? "  <-- CHECK!" : "");
    return HAL_OK;
}

static int sh_builtin_mode(int argc, char *argv[])
{
    if (argc >= 2) {
        if (strcmp(argv[1], "auto") == 0) {
            (void)sh_set_mode(SH_MODE_AUTO);
        } else if (strcmp(argv[1], "manual") == 0) {
            (void)sh_set_mode(SH_MODE_MANUAL);
        } else {
            sh_puts(SH_RET_PARA_OF("mode [auto|manual]"));
            return SH_ERR_PARAM;
        }
    }
    sh_print("mode: %s\r\n", (sh_get_mode() == SH_MODE_AUTO) ? "auto" : "manual");
    return HAL_OK;
}

static int sh_builtin_history(int argc, char *argv[])
{
    const char *h;

    (void)argc;
    (void)argv;

    sh_history_reset_cursor();
    while ((h = sh_history_prev()) != NULL) {
        sh_print("  %s\r\n", h);
    }
    /* 必须复位：否则打印完历史后，用户按 ↑ 会从上一条继续往前，
     * 而不是从最新一条开始 —— 表现为"历史乱跳"。 */
    sh_history_reset_cursor();
    return HAL_OK;
}

/* ══════════════════════════════════════════════════════════════════
 * 三、pause / kill
 * ══════════════════════════════════════════════════════════════════ */

static int sh_builtin_pause(int argc, char *argv[])
{
    bool target = sh_config_get(SH_CONFIG_PAUS);

    if (argc >= 2) {
        if (strcmp(argv[1], "on") == 0) {
            target = true;
        } else if (strcmp(argv[1], "off") == 0) {
            target = false;
        } else {
            sh_puts(SH_RET_PARA_OF("pause [on|off]"));
            return SH_ERR_PARAM;
        }
    } else {
        target = !target;           /* 无参：翻转 */
    }

    sh_config_set(SH_CONFIG_PAUS, target);

    if (target) {
        sh_puts("<+0, bg task paused\r\n");
        sh_bg_list_print();
    } else {
        sh_puts("<+0, bg task continues\r\n");
    }
    return HAL_OK;
}

static int sh_builtin_kill(int argc, char *argv[])
{
    uint16_t n;

    if ((argc < 2) || (strcmp(argv[1], "all") != 0)) {
        sh_puts(SH_RET_PARA_OF("kill all"));
        return SH_ERR_PARAM;
    }

    n = sh_bg_kill_all();
    sh_print("<+0, killed %u task(s)\r\n", (unsigned)n);
    return HAL_OK;
}

/* ══════════════════════════════════════════════════════════════════
 * 四、vram（静态 KV 表）
 * ══════════════════════════════════════════════════════════════════ */

#if (SH_FEATURE_VRAM == 1U)

/**
 * @brief vram 表项
 * @note  键值都用定长数组：ULP8 用 `sys_malloc(len_name + len_data)` 每次写都
 *        重新分配，静态化后必然要给定上限，超长键值被截断而非报错 ——
 *        调试用的 KV 表，截断比"拒绝写入"更符合使用习惯。
 */
typedef struct {
    char name[SH_VRAM_NAME_MAX];    /**< 键名 */
    char value[SH_VRAM_VALUE_MAX];  /**< 键值 */
    bool used;                      /**< 槽位已占用 */
} sh_vram_item_t;

/** @brief vram 静态表 */
static sh_vram_item_t s_vram[SH_VRAM_TABLE];

/**
 * @brief 按键名查找 vram 表项
 * @param[in] name 键名
 * @return 表项指针；未找到返回 NULL
 * @note  返回**非 const** 指针：设置路径要改写表项。查询路径用
 *        `const sh_vram_item_t *` 接收即可（加限定是安全的，去掉限定不是，
 *        否则违反 MISRA C:2012 Rule 11.8）。
 */
static sh_vram_item_t *sh_vram_find(const char *name)
{
    uint32_t i;

    for (i = 0U; i < (uint32_t)SH_VRAM_TABLE; i++) {
        if ((s_vram[i].used) && (strcmp(s_vram[i].name, name) == 0)) {
            return &s_vram[i];
        }
    }
    return NULL;
}

/**
 * @brief 取一个空闲 vram 槽并写入键名
 * @param[in] name 键名（超长截断）
 * @return 表项指针；表满返回 NULL
 */
static sh_vram_item_t *sh_vram_alloc(const char *name)
{
    uint32_t i;

    for (i = 0U; i < (uint32_t)SH_VRAM_TABLE; i++) {
        if (s_vram[i].used == false) {
            s_vram[i].used = true;
            sh_str_copy(s_vram[i].name, (size_t)SH_VRAM_NAME_MAX, name);
            s_vram[i].value[0] = '\0';
            return &s_vram[i];
        }
    }
    return NULL;
}

static int sh_builtin_vram(int argc, char *argv[])
{
    uint32_t i;

    if (argc >= 3) {
        /* 设置：vram key value */
        sh_vram_item_t *it = sh_vram_find(argv[1]);

        if (it == NULL) {
            it = sh_vram_alloc(argv[1]);
            if (it == NULL) {
                sh_puts(SH_RET_NOMEM);
                return SH_ERR_NOMEM;
            }
        }
        sh_str_copy(it->value, (size_t)SH_VRAM_VALUE_MAX, argv[2]);
        sh_puts(SH_RET_OK);
        return HAL_OK;
    }

    if (argc == 2) {
        /* 查询单个键 */
        const sh_vram_item_t *it = sh_vram_find(argv[1]);

        if (it == NULL) {
            sh_puts(SH_RET_PARA_OF("key not found"));
            return SH_ERR_PARAM;
        }
        sh_print("<+0, {%s:%s}\r\n", it->name, it->value);
        return HAL_OK;
    }

    /* 列出全部 */
    sh_puts("<+0, {");
    for (i = 0U; i < (uint32_t)SH_VRAM_TABLE; i++) {
        if (s_vram[i].used) {
            sh_print("%s:%s, ", s_vram[i].name, s_vram[i].value);
        }
    }
    sh_puts("}\r\n");
    return HAL_OK;
}

#endif /* SH_FEATURE_VRAM */

/* ══════════════════════════════════════════════════════════════════
 * 五、SCPI 组：*IDN? / *ERR? / *SYST? / *RST
 * ══════════════════════════════════════════════════════════════════ */

static int sh_builtin_idn(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    sh_print("<+0, '%s,sh-%s'\r\n", SH_BOARD_NAME, SH_VERSION_STR);
    return HAL_OK;
}

static int sh_builtin_err(int argc, char *argv[])
{
    hal_err_t last = { HAL_OK, 0U, 0U };

    (void)argc;
    (void)argv;

    /* 直接查 HAL 的 P2（致命错误）与 P0（断言）计数 ——
     * 这两条通道是 hal_comm.c 保证"恒记录"的，不依赖应用层是否接钩子。 */
    sh_print("<+0, errors=%u asserts=%u\r\n",
             (unsigned)hal_error_count(),
             (unsigned)hal_assert_count());

    if (hal_error_get_last(&last) == HAL_OK) {
        sh_print("     last=%d inst=%u extra=0x%04X\r\n",
                 (int)last.code,
                 (unsigned)last.instance,
                 (unsigned)last.extra);
    }
    return HAL_OK;
}

static int sh_builtin_syst(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    sh_print("<+0, ms=%lu\r\n", (unsigned long)sh_io_ms());
    return HAL_OK;
}

/** @brief 系统复位回调（NULL = 平台未绑定） */
static void (*s_reset_fn)(void);

void sh_bind_reset(void (*reset_fn)(void))
{
    s_reset_fn = reset_fn;
}

static int sh_builtin_rst(int argc, char *argv[])
{
    uint32_t guard = 0U;

    (void)argc;
    (void)argv;

    if (s_reset_fn == NULL) {
        /* 明确报"不支持"，不假装成功：自动化脚本会据此判断复位是否真的发生 */
        sh_puts("<-5, reset not supported (sh_bind_reset not called)\r\n");
        return HAL_ERR_NOT_SUPPORTED;
    }

    sh_puts(SH_RET_OK);

    /* 复位前必须把应答真正送出去，否则串口上什么也看不到，
     * 上位机会以为"命令丢了"而不是"板子正在复位"。
     * 加 guard 上限：万一 TX 侧卡住，宁可复位也不要死在这里。 */
    sh_tx_drain();
    while ((sh_tx_backlog() != 0U) && (guard < 64U)) {
        sh_tx_drain();
        guard++;
    }

    s_reset_fn();
    return HAL_OK;
}

/* ══════════════════════════════════════════════════════════════════
 * 六、echo（分词调试）
 * ══════════════════════════════════════════════════════════════════ */

static int sh_builtin_echo(int argc, char *argv[])
{
    int i;

    for (i = 0; i < argc; i++) {
        sh_print("argv[%d] = '%s'\r\n", i, argv[i]);
    }
    return HAL_OK;
}

/* ══════════════════════════════════════════════════════════════════
 * 七、命令注册（与用户命令同待遇，都在 hal_sh_cmd 段内）
 * ══════════════════════════════════════════════════════════════════ */

#if (SH_FEATURE_HELP == 1U)
SH_EXPORT_CMD(help, sh_builtin_help, "list all commands");
SH_EXPORT_CMD_AS("*?", sh_alias_help, sh_builtin_help, "list all commands (SCPI)");
#endif

#if (SH_FEATURE_VER_CMD == 1U)
SH_EXPORT_CMD(ver, sh_builtin_ver, "show shell version + tx diagnostics");
#endif

#if (SH_FEATURE_MODE_CMD == 1U)
SH_EXPORT_CMD(mode, sh_builtin_mode, "show/set mode: mode [auto|manual]");
#endif

#if (SH_FEATURE_HISTORY_CMD == 1U)
SH_EXPORT_CMD(history, sh_builtin_history, "show command history");
#endif

/* pause / kill 属于循环执行的一部分，恒定编入（池深度可为 0 时也无害） */
SH_EXPORT_CMD(pause, sh_builtin_pause, "pause/resume background tasks: pause [on|off]");
SH_EXPORT_CMD(kill, sh_builtin_kill, "kill background tasks: kill all");

#if (SH_FEATURE_VRAM == 1U)
SH_EXPORT_CMD(vram, sh_builtin_vram, "virtual ram: vram [key [value]]");
#endif

#if (SH_FEATURE_SCPI_CMD == 1U)
SH_EXPORT_CMD_AS("*IDN?", sh_alias_idn,  sh_builtin_idn,  "query board info");
SH_EXPORT_CMD_AS("*ERR?", sh_alias_err,  sh_builtin_err,  "query error/assert counters");
SH_EXPORT_CMD_AS("*SYST?", sh_alias_syst, sh_builtin_syst, "query millisecond timebase");
SH_EXPORT_CMD_AS("*RST",  sh_alias_rst,  sh_builtin_rst,  "reset MCU");
SH_EXPORT_CMD(echo, sh_builtin_echo, "print tokenized argv (quote debugging)");
#endif
