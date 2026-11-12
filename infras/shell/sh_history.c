/**
 * @file    sh_history.c
 * @brief   sh 命令历史 —— 静态槽环形缓冲
 *
 * @details 存储为固定大小静态二维数组，**不依赖堆**，上/下方向键回滚，
 *          超出深度后覆盖最旧一条。
 *
 *          @section SH_HIST_CURSOR 游标模型
 *          | 游标值 | 含义 |
 *          |---|---|
 *          | `-1` | "最新之后"（即当前空行，等待新输入） |
 *          | `0`  | 最新一条 |
 *          | 增大 | 更早的历史 |
 *
 *          @section SH_HIST_WHY 为什么不用 ULP8 的链表 + 字节预算
 *          ULP8 用 `sys_malloc` 为每条历史分配节点，并维护"总字节预算"与
 *          "条数上限"两个维度。在静态内存约束下，链表节点无法预分配（长度不定），
 *          而"定长槽 + 环形覆盖"用一块固定数组就同时满足了两个上限：
 *          条数上限 = @ref SH_HISTORY_DEPTH，字节上限 = 深度 × 行宽。
 *          代价是长命令被截断到 @ref SH_HISTORY_LINE_MAX - 1 字节 —— 对本工程
 *          128 字节的行缓冲来说，只有极长命令行会受影响，可接受。
 *
 * @note    遵守 MISRA C:2012 Required 规则。
 * @warning 返回的字符串指针指向内部静态槽，**调用方必须立即使用**，
 *          下一次 `add`/`prev`/`next` 可能改写其内容。
 *
 * @author  binbina
 * @version 1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-10-26 | binbina | 初版。沿用静态槽环形设计替换 ULP8 的堆链表历史；保留"与最新一条重复则跳过"语义 |
 */

#include "sh.h"
#include "sh_cfg.h"

#include <string.h>

/* ── 静态存储 ───────────────────────────────────────────────────── */

/** @brief 历史槽（环形） */
static char    s_hist[SH_HISTORY_DEPTH][SH_HISTORY_LINE_MAX];
/** @brief 下一个写入位置（环形） */
static uint8_t s_head;
/** @brief 已存条数（≤ SH_HISTORY_DEPTH） */
static uint8_t s_count;
/** @brief 历史游标（-1 = 最新之后） */
static int8_t  s_cur = -1;

/* ── 内部：游标换算槽下标 ───────────────────────────────────────── */

/**
 * @brief 由游标值换算历史槽下标
 * @param[in] cur 游标（0 = 最新，越大越早）
 * @return 槽下标
 */
static uint8_t sh_hist_index(int8_t cur)
{
    uint8_t offset = (uint8_t)((uint8_t)cur % SH_HISTORY_DEPTH);

    /* 最新一条位于 head 的前一格；cur 越大越往更早走 */
    return (uint8_t)((s_head + SH_HISTORY_DEPTH - 1U - offset) % SH_HISTORY_DEPTH);
}

/* ── 对外接口 ───────────────────────────────────────────────────── */

void sh_history_add(const char *cmd)
{
    size_t n;

    if ((cmd == NULL) || (cmd[0] == '\0')) {
        sh_history_reset_cursor();
        return;
    }

    /* 与最新一条完全相同则跳过（连续重复执行同一命令不占槽位） */
    if (s_count > 0U) {
        uint8_t last = (s_head == 0U) ? (uint8_t)(SH_HISTORY_DEPTH - 1U)
                                      : (uint8_t)(s_head - 1U);
        if (strcmp(s_hist[last], cmd) == 0) {
            s_cur = -1;
            return;
        }
    }

    n = strlen(cmd);
    if (n > (size_t)(SH_HISTORY_LINE_MAX - 1U)) {
        n = (size_t)(SH_HISTORY_LINE_MAX - 1U);
    }
    (void)memcpy(s_hist[s_head], cmd, n);
    s_hist[s_head][n] = '\0';

    s_head = (uint8_t)((s_head + 1U) % SH_HISTORY_DEPTH);
    if (s_count < SH_HISTORY_DEPTH) {
        s_count++;
    }
    s_cur = -1;
}

const char *sh_history_prev(void)
{
    if (s_count == 0U) {
        return NULL;
    }
    if (s_cur >= (int8_t)(s_count - 1U)) {
        return NULL;                /* 已是最旧一条 */
    }
    s_cur++;
    return s_hist[sh_hist_index(s_cur)];
}

const char *sh_history_next(void)
{
    if (s_cur < 0) {
        return NULL;                /* 已在最新之后 */
    }
    if (s_cur == 0) {
        s_cur = -1;
        return NULL;                /* 回到空行 */
    }
    s_cur--;
    return s_hist[sh_hist_index(s_cur)];
}

void sh_history_reset_cursor(void)
{
    s_cur = -1;
}

/**
 * @brief 复位历史（清空全部槽位）
 * @note  仅 @ref sh_init 使用；不对外声明，避免命令误清用户历史。
 */
void sh_history_clear(void)
{
    s_head  = 0U;
    s_count = 0U;
    s_cur   = -1;
    (void)memset(s_hist, 0, sizeof(s_hist));
}
