/**
 * @file    sh_bg.c
 * @brief   sh 后台循环执行 —— 静态 context 池 + 周期调度
 *
 * @details 实现 `cmd&period` / `cmd&period,nloops` / `cmd&min~max` 三种循环写法。
 *          与 ULP8 的实现差异全部源于**禁止动态内存**：
 *
 *          | 维度 | ULP8 | 本实现 |
 *          |---|---|---|
 *          | 上下文存储 | `sys_malloc` 每条命令一次 | 静态池 @ref SH_CTX_POOL 个槽 |
 *          | 池满行为 | 堆耗尽返回 NULL，静默失败 | 明确返回 `<-400, no enough memory` |
 *          | 随机周期 | `rand()`（需初始化种子 + C 库） | 自含 LCG，种子取上电时基 |
 *          | 定时判断 | `time_get` / `time_left` | `sh_io_ms()` 无符号差值（回绕安全） |
 *
 *          **池深度按需求定为 2**：可同时跑两条周期命令。每个槽占用
 *          `sizeof(sh_context_t)` = 184 字节（含 96 字节命令行副本），
 *          两个槽共 368 字节。加一个槽约 +184 字节 RAM。
 *
 * @note    遵守 MISRA C:2012 Required 规则。
 * @warning 调度精度取决于 @ref sh_task 的调用周期：若主循环 10 ms 一圈，
 *          则 5 ms 的周期实际按 10 ms 执行。@ref SH_BG_PERIOD_MIN_MS
 *          已按常见主循环节拍给出下限。
 *
 * @author  binbina
 * @version 1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-10-26 | binbina | 初版。把 ULP8 基于 malloc 的 context 链表改为静态池（深度 2）；rand() 改为自含 LCG；time_get/time_left 改为毫秒差值与无符号回绕比较 |
 */

#include "sh.h"
#include "sh_cfg.h"
#include "sh_internal.h"

#include <string.h>

/* ── 静态池与队列 ───────────────────────────────────────────────── */

/** @brief 后台 context 静态池（对外可见以便核算 RAM 占用） */
sh_context_t sh_ctx_pool[SH_CTX_POOL];

/** @brief 后台队列头（单链表，节点即池内元素） */
static sh_context_t *s_bg_head;

/** @brief 随机数状态（LCG） */
static uint32_t s_rand_state = 0x12345678UL;

/* ── 随机数（替代 C 库 rand） ───────────────────────────────────── */

/**
 * @brief 线性同余随机数
 * @return 15 位无符号随机值
 * @details 用 glibc 的经典参数（乘 1103515245、加 12345），取高 15 位。
 *          调试场景的"随机周期"只需要看起来不规律，不需要统计质量，
 *          所以不引入 C 库 `rand()`（它要额外的种子初始化与库体积）。
 */
static uint32_t sh_rand(void)
{
    s_rand_state = (s_rand_state * 1103515245UL) + 12345UL;
    return (s_rand_state >> 16) & 0x7FFFU;
}

/* ── 池管理 ─────────────────────────────────────────────────────── */

sh_context_t *sh_ctx_alloc(void)
{
    uint32_t i;

    for (i = 0U; i < (uint32_t)SH_CTX_POOL; i++) {
        if ((sh_ctx_pool[i].flags & SH_CTX_F_INUSE) == 0U) {
            (void)memset(&sh_ctx_pool[i], 0, sizeof(sh_context_t));
            sh_ctx_pool[i].flags = SH_CTX_F_INUSE;
            return &sh_ctx_pool[i];
        }
    }
    return NULL;
}

void sh_ctx_free(sh_context_t *ctx)
{
    if (ctx == NULL) {
        return;
    }
    /* 只清标志位，不清整个结构体：argv 指向自身 line[]，
     * 整体清零会让"已释放"的槽看起来像"有内容但无效"，排查时更迷惑。 */
    ctx->flags = 0U;
    ctx->next  = NULL;
    ctx->cmd   = NULL;
    ctx->argc  = 0U;
    ctx->line[0] = '\0';
}

/* ── 队列管理 ───────────────────────────────────────────────────── */

void sh_bg_queue_add(sh_context_t *ctx)
{
    if (ctx == NULL) {
        return;
    }
    ctx->next  = s_bg_head;         /* 头插：池深度小，顺序无关紧要 */
    s_bg_head  = ctx;
}

/**
 * @brief 把上下文从后台队列摘除
 * @param[in] ctx 待摘除的上下文
 * @note  找不到时静默返回（不 assert）：调度路径上的断言会直接把整机停住，
 *        而"想摘一个不在队列里的节点"最多说明调用方逻辑有冗余，不值得停机。
 */
static void sh_bg_unlink(sh_context_t *ctx)
{
    sh_context_t *prev = NULL;
    sh_context_t *cur  = s_bg_head;

    while (cur != NULL) {
        if (cur == ctx) {
            if (prev == NULL) {
                s_bg_head = cur->next;
            } else {
                prev->next = cur->next;
            }
            cur->next = NULL;
            return;
        }
        prev = cur;
        cur  = cur->next;
    }
}

/* ── 周期调度 ───────────────────────────────────────────────────── */

/**
 * @brief 计算某上下文的下一个周期
 * @param[in] ctx 上下文
 * @return 周期（ms）
 */
static uint16_t sh_bg_period_next(const sh_context_t *ctx)
{
    uint32_t range;
    uint32_t span;

    if ((ctx->flags & SH_CTX_F_RANDOM) == 0U) {
        return ctx->period_ms;
    }

    range = (uint32_t)ctx->period_max_ms - (uint32_t)ctx->period_ms;
    if (range == 0U) {
        return ctx->period_ms;
    }

    /* +1 让上限可达：&100~500 应能取到 500 */
    span = (sh_rand() % (range + 1UL));
    return (uint16_t)((uint32_t)ctx->period_ms + span);
}

void sh_bg_run(void)
{
    sh_context_t *ctx;
    sh_context_t *next;
    uint32_t      now;

    /* 暂停位：任务保留不丢，恢复后继续按时执行 */
    if (sh_config_get(SH_CONFIG_PAUS)) {
        return;
    }

    now = sh_io_ms();
    ctx = s_bg_head;

    while (ctx != NULL) {
        next = ctx->next;           /* 先取后继：本节点可能被释放 */

        /* 到期判断用无符号差值，天然抵御 32 位回绕；
         * 强转有符号后比较，可正确处理"还差几毫秒"与"已超时"两种情况。 */
        if ((int32_t)(now - ctx->t_next) >= 0) {
            (void)sh_exec_context(ctx);

            ctx->lopcnt++;
            if (ctx->lopcnt >= ctx->nloops) {
                sh_bg_unlink(ctx);
                sh_ctx_free(ctx);
            } else {
                ctx->t_next = now + (uint32_t)sh_bg_period_next(ctx);
            }
        }
        ctx = next;
    }
}

uint16_t sh_bg_kill_all(void)
{
    sh_context_t *ctx = s_bg_head;
    uint16_t      n   = 0U;

    while (ctx != NULL) {
        sh_context_t *next = ctx->next;

        ctx->next = NULL;
        sh_ctx_free(ctx);
        n++;
        ctx = next;
    }
    s_bg_head = NULL;
    return n;
}

void sh_bg_list_print(void)
{
    const sh_context_t *ctx = s_bg_head;
    uint32_t            i   = 0U;

    if (ctx == NULL) {
        sh_print("bg tasks: none\r\n");
        return;
    }

    sh_print("bg tasks:\r\n");
    while (ctx != NULL) {
        uint32_t k;

        sh_print("  %02u: period=%04ums nloops=%04u done=%04u  ",
                 (unsigned)i,
                 (unsigned)ctx->period_ms,
                 (unsigned)ctx->nloops,
                 (unsigned)ctx->lopcnt);

        /* 不能直接打印 ctx->line：@ref sh_tokenize 是原地改写，line[] 已被
         * 切成多段 `\0` 结尾，`%s` 只输出 argv[0] —— `echo bg` 会显示成
         * `echo`，看着像参数丢了。按 argv 重建才准确。 */
        for (k = 0U; k < (uint32_t)ctx->argc; k++) {
            sh_print("%s%s", (k == 0U) ? "" : " ", ctx->argv[k]);
        }
        sh_puts("\r\n");

        i++;
        ctx = ctx->next;
    }
}

void sh_bg_reset(void)
{
    (void)sh_bg_kill_all();

    /* 清空整个池（含未入队的槽），避免复位后残留旧命令 */
    (void)memset(sh_ctx_pool, 0, sizeof(sh_ctx_pool));

    /* 随机种子取上电时基：每次复位后的序列不同，但同一上电周期内可复现 */
    s_rand_state = sh_io_ms() | 0x00000001UL;
}
