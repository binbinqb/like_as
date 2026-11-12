/**
 * @file    sh_internal.h
 * @brief   sh 中间件 —— 模块内部跨文件接口（**不对外**）
 *
 * @details 本头供 `middleware/shell` 内部各 `.c` 互相引用，**不是**对外契约：
 *          命令作者只需要包含 @ref sh.h。
 *
 *          | 内容 | 使用方 |
 *          |---|---|
 *          | 参数解析器（`sscanf` 的替代） | `sh_core` / `sh_bg` / `sh_cmd` |
 *          | 命令上下文与静态池 | `sh_core` / `sh_bg` / `sh_cmd` |
 *          | 历史清空 | `sh_core`（`sh_init`） |
 *
 * @warning 外部模块**不得**包含本头。需要新能力请加在 `sh.h`。
 *
 * @author  binbina
 * @version 1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-10-26 | binbina | 初版。集中命令上下文定义与手写解析器声明，替代 ULP8 对 sscanf 的依赖 |
 */

#ifndef SH_INTERNAL_H
#define SH_INTERNAL_H

#include "sh.h"
#include "sh_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup sh_int sh 内部接口 */
/** @ingroup sh */
/** @{ */

/* ══════════════════════════════════════════════════════════════════
 * 一、字符分类（替代 ctype.h）
 *
 * 不用 `isdigit`/`isprint` 的理由：MISRA C:2012 Rule 21.x 要求 ctype 函数的
 * 参数必须是 `unsigned char` 可表示值或 EOF，而 `char` 在这些平台上是有符号的，
 * 传入 >0x7F 的字节属于未定义行为。自己写两行更省心，也不增加库依赖。
 * ══════════════════════════════════════════════════════════════════ */

/**
 * @brief 是否十进制数字
 * @param[in] c 待判断字符
 * @retval true  `'0'`~`'9'`
 * @retval false 其他
 */
bool sh_is_digit(char c);

/**
 * @brief 是否可打印 ASCII 字符（不含空格以下与 DEL）
 * @param[in] c 待判断字符
 * @retval true  0x20 ~ 0x7E
 * @retval false 其他
 */
bool sh_is_print(char c);

/* ══════════════════════════════════════════════════════════════════
 * 二、基础数值解析（sscanf 的替代）
 * ══════════════════════════════════════════════════════════════════ */

/**
 * @brief 从字符串当前位置解析十进制无符号整数，并推进指针
 * @param[in,out] ps  字符串指针的指针；成功时推进到最后一个数字之后
 * @param[out]    out 解析结果；**仅当返回 true 时有效**
 * @retval true  至少解析到一位数字且未溢出 uint32
 * @retval false 当前位置不是数字 / 溢出 / 参数为 NULL
 * @note  失败时**不推进** @p ps，调用方可据此原地报错。
 */
bool sh_take_u32(const char **ps, uint32_t *out);

/**
 * @brief 解析区间表达式 `"a-b"` 或 `"a"`，并推进指针
 * @param[in,out] ps    字符串指针的指针
 * @param[out]    start 区间起点（含）；**仅当返回 true 时有效**
 * @param[out]    stop  区间终点（含）；单值 `"a"` 时等于 @p start
 * @retval true  解析成功
 * @retval false 首字符不是数字 / 上半段非法 / 参数为 NULL
 * @note  若 `a > b` 自动交换，调用方无需关心顺序。
 */
bool sh_parse_range(const char **ps, uint32_t *start, uint32_t *stop);

/**
 * @brief 解析位图表达式到指定宽度的缓冲
 * @param[in]  str     表达式，如 `"0,2-5,8"`；特殊标记 `"all"` / `"none"`
 * @param[out] pattern 位图缓冲（按位存放，位 0 = 字节 0 的 bit0）
 * @param[in]  bits    位图总位数（= 缓冲容量 × 8）
 * @return 出错的段数；0 表示全部解析成功
 *
 * @details 语义（沿用 ULP8）：
 *          - `"all"` 先把全部位置 1，此后各段变为**清除**；
 *          - `"none"` 先把全部位清 0，此后各段变为**置位**；
 *          - 段之间用 `,` 分隔，单段为 `"a"` 或 `"a-b"`（含两端）。
 * @note  调用前缓冲内容被整体清零，无需预清。
 */
int sh_parse_pattern(const char *str, uint8_t *pattern, uint32_t bits);

/**
 * @brief 解析位图表达式为 32 位掩码（`sh_parse_pattern` 的便捷包装）
 * @param[in] str 表达式，语义同 @ref sh_parse_pattern
 * @return 位掩码；解析出错返回 0
 * @note  只覆盖低 32 位，超出的位被忽略。
 */
int sh_pattern_get(const char *str);

/**
 * @brief 解析十六进制无符号整数（可带 `0x` 前缀）
 * @param[in]  s   待解析字符串
 * @param[out] out 解析结果；**仅当返回 true 时有效**
 * @retval true  成功（至少一位十六进制数字，未溢出）
 * @retval false 失败（空串 / NULL / 含非法字符 / 溢出）
 */
bool sh_xtoi(const char *s, uint32_t *out);

/**
 * @brief 在字符串表中线性查找
 * @param[in] s    目标字符串，不得为 NULL
 * @param[in] list 字符串表
 * @param[in] n    表项数
 * @return 命中下标；未命中返回 -1
 */
int sh_in_list_str(const char *s, const char *const *list, uint32_t n);

/**
 * @brief 有界字符串复制（替代 strncpy：保证结尾 `\0` 且不补零填充）
 * @param[out] dst 目标缓冲，不得为 NULL
 * @param[in]  cap 目标容量（含 `\0` 位置），必须 > 0
 * @param[in]  src 源字符串，不得为 NULL
 * @details 超长源被**截断**到 `cap - 1` 字节。与 `strncpy` 的区别是
 *          后者在源短时不保证 `\0`、源长时又会把整个缓冲填满 `\0`，
 *          两种行为都不是本项目想要的。
 */
void sh_str_copy(char *dst, size_t cap, const char *src);

/* ══════════════════════════════════════════════════════════════════
 * 三、循环执行后缀解析（替代 sscanf("&%d~%d") / sscanf("&%d, %d")）
 * ══════════════════════════════════════════════════════════════════ */

/**
 * @brief 循环后缀解析结果
 */
typedef struct {
    bool     loop;          /**< true = 该命令要后台循环执行 */
    bool     random;        /**< true = 随机周期模式（`&min~max`） */
    uint16_t period_ms;     /**< 固定周期；random 模式时为**最小**周期 */
    uint16_t nloops;        /**< 执行次数；@ref SH_BG_NLOOPS_FOREVER = 无限 */
    uint16_t period_max_ms; /**< random 模式的**最大**周期；非 random 时无意义 */
} sh_suffix_t;

/**
 * @brief 解析命令行的循环后缀
 * @param[in]  suffix 指向 `'&'` 的字符串（`strrchr(cmdline, '&')` 的结果）
 * @param[out] out    解析结果；**仅当返回 true 时有效**
 * @retval true  合法后缀
 * @retval false 格式非法（如 `&abc`、`&100-`）
 *
 * @details 支持三种写法：
 *          | 写法 | 含义 |
 *          |---|---|
 *          | `cmd&`          | 默认周期 @ref SH_BG_PERIOD_DEF_MS，无限循环 |
 *          | `cmd&100`       | 周期 100 ms，无限循环 |
 *          | `cmd&100,10`    | 周期 100 ms，执行 10 次 |
 *          | `cmd&100~500`   | 周期在 [100, 500] ms 内随机，无限循环 |
 * @note  逗号后的空格被容忍（`&100, 10` 与 `&100,10` 等价）。
 */
bool sh_parse_suffix(const char *suffix, sh_suffix_t *out);

/* ══════════════════════════════════════════════════════════════════
 * 四、命令上下文与静态池
 * ══════════════════════════════════════════════════════════════════ */

/** @brief 上下文标志：槽位已占用 */
#define SH_CTX_F_INUSE      (1U << 0)
/** @brief 上下文标志：循环模式 */
#define SH_CTX_F_LOOP       (1U << 1)
/** @brief 上下文标志：随机周期模式 */
#define SH_CTX_F_RANDOM     (1U << 2)
/** @brief 上下文标志：命令正在执行（防重入） */
#define SH_CTX_F_ISBUSY     (1U << 3)

/**
 * @brief 命令执行上下文
 * @details 一条命令从解析到执行完毕的载体。**全部静态**：
 *          `line[]` 内嵌命令行副本，`argv[]` 指向 `line[]` 内部，
 *          因此无需任何动态分配，也不会出现"argv 指向已释放内存"。
 *
 *          | 字段 | 大小 | 说明 |
 *          |---|---|---|
 *          | `argv[SH_MAX_ARGS]` | 64 | 指向 `line[]` 内部 |
 *          | `cmd` | 4 | 命中的命令描述符 |
 *          | `next` | 4 | 后台链表（池内串联） |
 *          | `t_next` | 4 | 下次执行时刻（ms） |
 *          | `period_ms` / `period_max_ms` | 4 | 周期 / 随机模式上限 |
 *          | `nloops` / `lopcnt` | 4 | 总次数 / 已执行次数 |
 *          | `argc` / `flags` | 2 | 参数个数 / 标志位 |
 *          | `line[SH_CTX_LINE_MAX]` | 96 | 命令行副本 |
 *          | **合计** | **184** | 与 sh_cfg.h 的预算表一致 |
 */
typedef struct sh_context_s {
    char                 *argv[SH_MAX_ARGS];    /**< 参数数组，指向 line[] 内部 */
    const sh_cmd_t       *cmd;                  /**< 命中的命令描述符 */
    struct sh_context_s  *next;                 /**< 后台链表指针（池内） */
    uint32_t              t_next;               /**< 下次执行时刻（ms） */
    uint16_t              period_ms;            /**< 周期（ms）；random 时为下限 */
    uint16_t              period_max_ms;        /**< random 模式周期上限（ms） */
    uint16_t              nloops;               /**< 总执行次数 */
    uint16_t              lopcnt;               /**< 已执行次数 */
    uint8_t               argc;                 /**< 参数个数 */
    uint8_t               flags;                /**< @ref SH_CTX_F_INUSE 等 */
    char                  line[SH_CTX_LINE_MAX];/**< 命令行副本；分词后已被切成多段 `\0`，显示须用 argv 重建 */
} sh_context_t;

/** @brief 上下文静态池（定义在 sh_bg.c） */
extern sh_context_t sh_ctx_pool[SH_CTX_POOL];

/**
 * @brief 从静态池申请一个上下文槽
 * @return 上下文指针；池满返回 NULL
 * @note  返回时已清零（`line[]` 除外，由调用方写入）。
 */
sh_context_t *sh_ctx_alloc(void);

/**
 * @brief 归还上下文槽
 * @param[in,out] ctx 上下文指针；NULL 时忽略
 */
void sh_ctx_free(sh_context_t *ctx);

/**
 * @brief 把已执行的循环上下文重新挂到后台队列
 * @param[in,out] ctx 上下文
 * @note  只在 @ref SH_CTX_F_LOOP 置位且未达次数上限时调用。
 */
void sh_bg_queue_add(sh_context_t *ctx);

/* ══════════════════════════════════════════════════════════════════
 * 五、执行与历史杂项
 * ══════════════════════════════════════════════════════════════════ */

/**
 * @brief 执行一个已绑定的上下文（同步）
 * @param[in,out] ctx 上下文，`cmd` 与 `argv` 必须已就绪
 * @return 命令返回码
 * @note  内部设置 @ref SH_CTX_F_ISBUSY 防重入；执行完毕清除。
 */
int sh_exec_context(sh_context_t *ctx);

/**
 * @brief 清空历史（供 @ref sh_init）
 */
void sh_history_clear(void);

/**
 * @brief 初始化 TX 环形缓冲（供 @ref sh_init）
 * @details 用 `kernel/lwrb` 重新初始化输出环并清零丢弃计数。重复调用安全。
 * @note  不解除 I/O 绑定，也不改变"阻塞直写 / 排队"模式 ——
 *        模式由首次 @ref sh_tx_drain 决定，复位不应让已启动的系统退回阻塞写。
 */
void sh_io_init(void);

/**
 * @brief 从绑定通道非阻塞读一个字节
 * @return 读到字节（0~255）；未绑定或无数据返回 -1
 */
int sh_io_getc(void);

/**
 * @brief 取毫秒时基
 * @return 平台毫秒计数；未绑定时返回 0
 * @note  返回值仅用于**差值**比较，回绕安全（无符号减法）。
 */
uint32_t sh_io_ms(void);

/**
 * @brief 设置输出静音（对应 @ref SH_CONFIG_MUTE）
 * @param[in] on true = 此后所有输出被丢弃（含 TX 环已有内容不再送出）
 * @note  静音判断放在最底层 @ref sh_puts / @ref sh_putch，而不是各命令里 ——
 *        否则每个命令都要自己判一次，漏一处就静音不彻底。
 *        格式化仍然执行（浪费少量 CPU），换取调用点零改动。
 */
void sh_io_set_mute(bool on);

/**
 * @brief 复位后台执行状态（清空 context 池与队列，供 @ref sh_init）
 */
void sh_bg_reset(void);

/** @brief 当前正在执行的上下文（供 @ref sh_is_repeated 查询） */
extern sh_context_t *sh_ctx_current;

/** @} */ /* end of defgroup sh_int */

#ifdef __cplusplus
}
#endif

#endif /* SH_INTERNAL_H */
