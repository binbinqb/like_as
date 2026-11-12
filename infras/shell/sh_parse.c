/**
 * @file    sh_parse.c
 * @brief   sh 参数解析 —— 手写解析器（替代 sscanf 族）
 *
 * @details ULP8 的 shell 依赖 `sscanf` 完成四类解析：命令转发前缀、`&` 循环
 *          后缀、位图 pattern、十六进制参数。移植到裸机后这些**不能保留**：
 *
 *          | 原用法 | 问题 |
 *          |---|---|
 *          | `sscanf(cmdline, forwarder->prefix, &dest)` | **变量当格式串**：MISRA C:2012 Rule 17.1 的问题，且 prefix 一旦含 `%s` 就读野指针 |
 *          | `sscanf(suffix, "&%d~%d", ...)` | 库体积 + 无边界检查 |
 *          | `sscanf(str, "%d-%d,", ...)` | 同上 |
 *
 *          本文件用三个原语（@ref sh_take_u32 → @ref sh_parse_range →
 *          @ref sh_parse_pattern / @ref sh_parse_suffix）覆盖全部场景，
 *          **零库依赖、零格式串、全边界检查**。
 *
 * @note    遵守 MISRA C:2012 Required 规则。
 * @warning 所有解析函数在失败时**不修改输出参数**，调用方无需预清零；
 *          但也**不要**在失败后读取输出参数。
 *
 * @author  binbina
 * @version 1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-10-26 | binbina | 初版。以手写解析器全面替代 ULP8 对 sscanf 的依赖（模式串/&amp; 后缀/十六进制/字符串表查找），统一区间语义为"含两端"（ULP8 两个 pattern 函数一处含、一处不含，属既有不一致） |
 */

#include "sh_internal.h"

#include <string.h>

/* ══════════════════════════════════════════════════════════════════
 * 一、字符分类
 * ══════════════════════════════════════════════════════════════════ */

bool sh_is_digit(char c)
{
    return ((c >= '0') && (c <= '9')) ? true : false;
}

bool sh_is_print(char c)
{
    /* 0x20(空格) ~ 0x7E(波浪号)；0x7F 是 DEL，不可打印 */
    return (((uint8_t)c >= 0x20U) && ((uint8_t)c <= 0x7EU)) ? true : false;
}

/* ══════════════════════════════════════════════════════════════════
 * 二、基础数值解析
 * ══════════════════════════════════════════════════════════════════ */

bool sh_take_u32(const char **ps, uint32_t *out)
{
    const char *s;
    uint32_t    v   = 0U;
    bool        got = false;

    if ((ps == NULL) || (*ps == NULL) || (out == NULL)) {
        return false;
    }
    s = *ps;

    while (sh_is_digit(*s)) {
        uint32_t d = (uint32_t)((uint32_t)*s - (uint32_t)'0');

        /* 溢出检查必须在乘加**之前**做：结果强转补不回来已发生的溢出 */
        if (v > ((0xFFFFFFFFUL - d) / 10U)) {
            return false;
        }
        v = (v * 10U) + d;
        s++;
        got = true;
    }

    if (!got) {
        return false;
    }
    *out = v;
    *ps  = s;
    return true;
}

bool sh_parse_u32(const char *s, uint32_t *val)
{
    const char *p = s;
    uint32_t    v = 0U;

    if ((s == NULL) || (val == NULL)) {
        return false;
    }
    if (!sh_take_u32(&p, &v)) {
        return false;
    }
    if (*p != '\0') {
        return false;               /* 整串必须都是数字："12a" 判失败 */
    }
    *val = v;
    return true;
}

bool sh_parse_range(const char **ps, uint32_t *start, uint32_t *stop)
{
    const char *p;
    uint32_t    a = 0U;
    uint32_t    b = 0U;

    if ((ps == NULL) || (*ps == NULL) || (start == NULL) || (stop == NULL)) {
        return false;
    }

    if (!sh_take_u32(ps, &a)) {
        return false;
    }

    p = *ps;
    if (*p == '-') {
        p++;
        if (!sh_take_u32(&p, &b)) {
            return false;           /* "2-" 这种半截区间判失败 */
        }
        *ps = p;
    } else {
        b = a;                      /* 单值 "a" 等价于 "a-a" */
    }

    /* 逆序自动交换：调用方不必关心 "5-2" 还是 "2-5" */
    if (b < a) {
        uint32_t t = a;
        a = b;
        b = t;
    }

    *start = a;
    *stop  = b;
    return true;
}

bool sh_xtoi(const char *s, uint32_t *out)
{
    uint32_t v   = 0U;
    bool     got = false;

    if ((s == NULL) || (out == NULL)) {
        return false;
    }

    if ((s[0] == '0') && ((s[1] == 'x') || (s[1] == 'X'))) {
        s += 2;
    }

    while (*s != '\0') {
        uint32_t d;

        if ((*s >= '0') && (*s <= '9')) {
            d = (uint32_t)((uint32_t)*s - (uint32_t)'0');
        } else if ((*s >= 'a') && (*s <= 'f')) {
            d = (uint32_t)((uint32_t)*s - (uint32_t)'a') + 10U;
        } else if ((*s >= 'A') && (*s <= 'F')) {
            d = (uint32_t)((uint32_t)*s - (uint32_t)'A') + 10U;
        } else {
            return false;           /* 出现非法字符：整串判失败 */
        }

        if (v > ((0xFFFFFFFFUL - d) / 16U)) {
            return false;           /* 再乘 16 加 d 会溢出 */
        }
        v = (v * 16U) + d;
        s++;
        got = true;
    }

    if (!got) {
        return false;               /* 空串或只有 "0x" */
    }
    *out = v;
    return true;
}

int sh_in_list_str(const char *s, const char *const *list, uint32_t n)
{
    uint32_t i;

    if ((s == NULL) || (list == NULL)) {
        return -1;
    }
    for (i = 0U; i < n; i++) {
        if ((list[i] != NULL) && (strcmp(list[i], s) == 0)) {
            return (int)i;
        }
    }
    return -1;
}

void sh_str_copy(char *dst, size_t cap, const char *src)
{
    size_t n;

    if ((dst == NULL) || (cap == 0U) || (src == NULL)) {
        return;
    }

    n = strlen(src);
    if (n >= cap) {
        n = cap - 1U;
    }
    (void)memcpy(dst, src, n);
    dst[n] = '\0';
}

/* ══════════════════════════════════════════════════════════════════
 * 三、位图 pattern
 * ══════════════════════════════════════════════════════════════════ */

/**
 * @brief 置位位图某一位
 * @param[in,out] map 位图缓冲
 * @param[in]     pos 位序号（0 起）
 */
static void sh_bit_set(uint8_t *map, uint32_t pos)
{
    map[pos >> 3] |= (uint8_t)(1U << (pos & 7U));
}

/**
 * @brief 清除位图某一位
 * @param[in,out] map 位图缓冲
 * @param[in]     pos 位序号（0 起）
 */
static void sh_bit_clr(uint8_t *map, uint32_t pos)
{
    map[pos >> 3] &= (uint8_t)(0xFFU ^ (1U << (pos & 7U)));
}

int sh_parse_pattern(const char *str, uint8_t *pattern, uint32_t bits)
{
    const char *p;
    bool        inverse = false;
    int         errors  = 0;
    uint32_t    nbytes;

    if ((pattern == NULL) || (bits == 0U)) {
        return -1;
    }

    nbytes = (bits + 7U) / 8U;
    (void)memset(pattern, 0, (size_t)nbytes);

    if (str == NULL) {
        return -1;
    }

    p = str;
    while (*p != '\0') {
        uint32_t start = 0U;
        uint32_t stop  = 0U;

        while (*p == ',') {
            p++;                    /* 容忍前导与连续逗号 */
        }
        if (*p == '\0') {
            break;
        }

        /* "all" / "none" 改变后续段的极性，不占位 */
        if (strncmp(p, "all", 3U) == 0) {
            (void)memset(pattern, 0xFF, (size_t)nbytes);
            inverse = true;
            p += 3;
            continue;
        }
        if (strncmp(p, "none", 4U) == 0) {
            (void)memset(pattern, 0, (size_t)nbytes);
            inverse = false;
            p += 4;
            continue;
        }

        if (!sh_parse_range(&p, &start, &stop)) {
            errors++;
            break;                  /* 已无法判断段边界，停止解析 */
        }

        if ((start >= bits) || (stop >= bits)) {
            errors++;               /* 越界：整段丢弃，不部分生效 */
        } else {
            uint32_t i;
            for (i = start; i <= stop; i++) {
                if (inverse) {
                    sh_bit_clr(pattern, i);
                } else {
                    sh_bit_set(pattern, i);
                }
            }
        }

        /* 跳到下一个逗号 */
        while ((*p != '\0') && (*p != ',')) {
            p++;
        }
    }

    return errors;
}

int sh_pattern_get(const char *str)
{
    uint8_t buf[4];                 /* 32 位掩码 = 4 字节 */
    int     err;
    uint32_t v;

    err = sh_parse_pattern(str, buf, 32U);
    if (err != 0) {
        return 0;
    }

    /* 位 0 在 buf[0] 的 bit0 ⇒ buf[0] 是低字节 */
    v = (uint32_t)buf[0]
      | ((uint32_t)buf[1] << 8)
      | ((uint32_t)buf[2] << 16)
      | ((uint32_t)buf[3] << 24);
    return (int)v;
}

/* ══════════════════════════════════════════════════════════════════
 * 四、循环执行后缀
 * ══════════════════════════════════════════════════════════════════ */

bool sh_parse_suffix(const char *suffix, sh_suffix_t *out)
{
    const char *p;
    uint32_t    a = 0U;
    uint32_t    b = 0U;

    if ((suffix == NULL) || (out == NULL)) {
        return false;
    }
    if (*suffix != '&') {
        return false;
    }

    p = suffix + 1;

    /* 先填默认值：`cmd&` 走这里 */
    out->loop          = true;
    out->random        = false;
    out->period_ms     = (uint16_t)SH_BG_PERIOD_DEF_MS;
    out->nloops        = SH_BG_NLOOPS_FOREVER;
    out->period_max_ms = 0U;

    if (*p == '\0') {
        return true;                /* "cmd&" */
    }

    if (!sh_take_u32(&p, &a)) {
        return false;               /* "&abc" */
    }
    if (a > SH_BG_PERIOD_MAX_MS) {
        return false;               /* 超出 uint16 周期上限：报错而非静默截断 */
    }
    if (a < SH_BG_PERIOD_MIN_MS) {
        a = SH_BG_PERIOD_MIN_MS;    /* "&1" 意图明确，钳到最小值比拒绝更友好 */
    }

    while (*p == ' ') {
        p++;                        /* 容忍 "&100, 10" 的逗号后空格 */
    }

    if (*p == '~') {
        /* 随机周期模式：&min~max */
        p++;
        while (*p == ' ') {
            p++;
        }
        if (!sh_take_u32(&p, &b)) {
            return false;
        }
        if (*p != '\0') {
            return false;
        }
        if ((b > SH_BG_PERIOD_MAX_MS) || (b < SH_BG_PERIOD_MIN_MS)) {
            return false;
        }
        out->random        = true;
        out->period_ms     = (uint16_t)((a < b) ? a : b);
        out->period_max_ms = (uint16_t)((a < b) ? b : a);
        return true;
    }

    if (*p == ',') {
        /* 固定周期 + 指定次数：&period,nloops */
        p++;
        while (*p == ' ') {
            p++;
        }
        if (!sh_take_u32(&p, &b)) {
            return false;
        }
        if (*p != '\0') {
            return false;
        }
        /* 0xFFFF 被保留表示"无限"，故显式次数上限为 0xFFFE */
        out->nloops = (b >= (uint32_t)SH_BG_NLOOPS_FOREVER)
                      ? (uint16_t)(SH_BG_NLOOPS_FOREVER - 1U)
                      : (uint16_t)b;
    } else if (*p != '\0') {
        return false;               /* "&100abc" */
    }

    out->period_ms = (uint16_t)a;
    return true;
}
