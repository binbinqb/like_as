/**
 * @file    sh_cfg.h
 * @brief   sh 命令行解释器 —— 编译期配置（全部可调常量集中于此）
 *
 * @details 本头只有宏常量，**零逻辑、零状态**（对应编码规范"cfg 层纯表"的精神）。
 *          改行为只改这里，不动实现文件。所有容量都与静态内存预算直接相关，
 *          调整前请先读 @ref SH_CFG_BUDGET。
 *
 * @section SH_CFG_BUDGET 静态内存预算（默认配置实测）
 * | 存储项 | 字节 |
 * |---|---|
 * | `s_line[SH_CMD_LINE_MAX]`                    | 128 |
 * | `s_tx_ring[SH_TX_RING]`                      | 1024 |
 * | `s_print_buf[SH_PRINT_BUF]`                  | 256 |
 * | `s_hist[SH_HISTORY_DEPTH][SH_HISTORY_LINE_MAX]` | 512 |
 * | `s_ctx_pool[SH_CTX_POOL]`（结构体 + 命令行副本） | 2 × 184 = 368 |
 * | `s_vram[SH_VRAM_TABLE]`                      | 8 × 52 = 416 |
 * | 游标 / 状态 / 统计                            | ~40 |
 * | **合计** | **≈ 2.7 KB** |
 *
 * @note  TX 环容量必须能装下"一条命令的最大输出"：超额部分被丢弃并计入
 *        @ref sh_tx_dropped（不静默）。新增输出行多的命令时请同步上调。
 *
 * @author  binbina
 * @version 1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-10-26 | binbina | 初版。集中 ULP8 shell 散落在 Kconfig 与各文件里的可调参数；循环 context 池按需求定为 2；新增静态内存预算表 |
 */

#ifndef SH_CFG_H
#define SH_CFG_H

#include "sh.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup sh_cfg Shell 配置
 * @brief sh 可调参数集中处
 * @ingroup sh
 * @{
 */

/* ── 版本 ───────────────────────────────────────────────────────── */
/** @brief 版本字符串（`ver` 命令与横幅打印） */
#define SH_VERSION_STR              "1.0.0"

/** @brief 板卡标识（`*IDN?` 命令首字段；由应用层按实际产品改写） */
#define SH_BOARD_NAME               "CVM014x-BCM"

/* ── 行编辑容量 ─────────────────────────────────────────────────── */
/**
 * @brief 输入行缓冲长度（含结尾 `\0`）
 * @note  实际可输入字符数为 `SH_CMD_LINE_MAX - 1`。超长输入被**静默丢弃**
 *        （不覆盖已有内容），避免半行命令被误执行。
 */
#define SH_CMD_LINE_MAX             (128U)

/**
 * @brief 单条命令最多参数个数（`argv` 数组容量，含 argv[0]）
 * @note  超出部分被丢弃，命令只看到前 N-1 个实参。
 */
#define SH_MAX_ARGS                 (16U)

/** @brief ESC 序列补齐超时（ms）：超时未补齐则丢弃 ESC，绝不阻塞主循环 */
#define SH_ESC_TIMEOUT_MS           (200U)

/* ── 提示符与模式 ───────────────────────────────────────────────── */
/** @brief 手动模式提示符（尾部含空格） */
#define SH_PROMPT                   "CVM014x >> "

/**
 * @brief 上电默认模式
 * @note  手动模式：有提示符 + 回显，供人工 bring-up；`Alt+M` 或
 *        `mode auto` 切到自动模式供上位机脚本使用。
 */
#define SH_DEFAULT_MODE             (SH_MODE_MANUAL)

/* ── 输出 ───────────────────────────────────────────────────────── */
/**
 * @brief 单次排空 TX 环的最大字节数
 * @details 排空用阻塞写分片发送，单次阻塞时间 ≈ chunk × 一字节线上时间
 *          （115200 8N1 ≈ 86.8 µs）⇒ 8 × 86.8 µs ≈ 0.69 ms < 1 ms。
 * @warning 若降低控制台波特率，必须同步调小本值，保持 `chunk × 10 / baud ≤ 1ms`。
 */
#define SH_TX_CHUNK                 (8U)

/**
 * @brief TX 环形缓冲容量（字节），**必须是 2 的幂**（用位掩码取代取模）
 * @warning 溢出字节被丢弃并计入 @ref sh_tx_dropped；`ver` 命令会显示该计数，
 *          持续非 0 说明需要上调本值。
 */
#define SH_TX_RING                  (1024U)

/** @brief @ref sh_print 内部格式化缓冲大小（字节） */
#define SH_PRINT_BUF                (256U)

/* ── 历史 ───────────────────────────────────────────────────────── */
/** @brief 历史环形缓冲深度（最多回滚 N 条） */
#define SH_HISTORY_DEPTH            (8U)

/** @brief 单条历史最大长度（含 `\0`），超出截断 */
#define SH_HISTORY_LINE_MAX         (64U)

/* ── 循环执行（& 后缀） ─────────────────────────────────────────── */
/**
 * @brief 后台 context 静态池深度
 * @details 每项占 `sizeof(sh_context_t) + SH_CTX_LINE_MAX` 字节。池满时
 *          新命令返回 @ref SH_RET_NOMEM，**不静默丢弃**。
 * @note  按需求定为 2：可同时跑两条周期命令（如 `adc read&200` 与
 *        `dio list&500` 并存）。每加一个约 +184 字节 RAM。
 */
#define SH_CTX_POOL                 (2U)

/** @brief 单个 context 可保存的命令行长度（含 `\0`），超出截断 */
#define SH_CTX_LINE_MAX             (96U)

/** @brief 循环命令默认周期（ms），`cmd&` 不带数字时使用 */
#define SH_BG_PERIOD_DEF_MS         (1000U)

/**
 * @brief 循环命令最小周期（ms）
 * @note  低于此值等于让主循环空转（命令执行本身就要几十微秒），
 *        解析时钳到本值而非报错 —— `&1` 意图明确，拒绝它没有好处。
 */
#define SH_BG_PERIOD_MIN_MS         (10U)

/**
 * @brief 循环命令最大周期（ms）
 * @note  周期字段是 uint16（65535 ms ≈ 65 s）。超过本值判为格式错误，
 *        **不做静默截断** —— 截断后的周期与用户意图无关，比报错更危险。
 */
#define SH_BG_PERIOD_MAX_MS         (60000U)

/** @brief 循环命令默认次数，`cmd&` 不带次数时表示无限循环 */
#define SH_BG_NLOOPS_FOREVER        (0xFFFFU)

/* ── 命令前缀（多机共存） ───────────────────────────────────────── */
/**
 * @brief 启用命令名前缀过滤（`sh_opt_prefix`）
 * @note  0 = 关闭（前缀函数存在但恒不匹配，节省 Flash）；1 = 启用。
 *        BCM 单 MCU 场景默认关闭。
 */
#define SH_FEATURE_PREFIX           (0U)

/* ── 命令转发 ───────────────────────────────────────────────────── */
/**
 * @brief 启用命令转发（把命令原样转给远端节点）
 * @note  0 = 关闭（`sh_forward` 接口保留但直接返回不支持）。
 *        BCM 单 MCU 无远端可转发，默认关闭。
 */
#define SH_FEATURE_FORWARD          (0U)

/** @brief 转发目标静态表容量（仅 @ref SH_FEATURE_FORWARD = 1 时占用 RAM） */
#define SH_FORWARD_TABLE            (4U)

/** @brief 转发前缀最大长度（含 `\0`） */
#define SH_FORWARD_PREFIX_MAX       (16U)

/* ── 虚拟内存（vram 命令的 KV 表） ──────────────────────────────── */
/** @brief 启用 `vram` 内建命令 */
#define SH_FEATURE_VRAM             (1U)

/** @brief vram 表项数 */
#define SH_VRAM_TABLE               (8U)

/** @brief vram 键名最大长度（含 `\0`） */
#define SH_VRAM_NAME_MAX            (12U)

/** @brief vram 值最大长度（含 `\0`） */
#define SH_VRAM_VALUE_MAX           (32U)

/* ── 内建命令开关 ───────────────────────────────────────────────── */
/** @brief 启用 `help` */
#define SH_FEATURE_HELP             (1U)
/** @brief 启用 `history` */
#define SH_FEATURE_HISTORY_CMD      (1U)
/** @brief 启用 `mode` */
#define SH_FEATURE_MODE_CMD         (1U)
/** @brief 启用 `ver` */
#define SH_FEATURE_VER_CMD          (1U)
/** @brief 启用 `*IDN?` / `*ERR?` / `*SYST?` 等 SCPI 内建命令 */
#define SH_FEATURE_SCPI_CMD         (1U)

/* ── 编译期一致性检查 ───────────────────────────────────────────── */
/**
 * @brief 编译期断言（C99 无 `_Static_assert`，用负数组宽度实现）
 * @param[in] _cond 必须为真的条件
 * @param[in] _tag  唯一标识（拼进类型名，避免重定义）
 * @note  失败时报 "negative array size"，错误信息里带 _tag。
 */
#define SH_STATIC_ASSERT(_cond, _tag)   typedef char sh_sa_##_tag[(_cond) ? 1 : -1]

/** @brief TX 环必须是 2 的幂（位掩码取模的前提） */
SH_STATIC_ASSERT((SH_TX_RING & (SH_TX_RING - 1U)) == 0U, tx_ring_pow2);
/** @brief TX 分片不得大于环容量，否则单次排空会越界 */
SH_STATIC_ASSERT(SH_TX_CHUNK <= SH_TX_RING, tx_chunk_le_ring);
/** @brief 参数个数至少为 1（argv[0] 必须存在） */
SH_STATIC_ASSERT(SH_MAX_ARGS >= 1U, max_args_ge1);
/** @brief context 池必须留出至少 1 个槽位（否则 `&` 后缀永远不可用） */
SH_STATIC_ASSERT(SH_CTX_POOL >= 1U, ctx_pool_ge1);
/** @brief context 命令行必须能装下最短命令（含 `\0`） */
SH_STATIC_ASSERT(SH_CTX_LINE_MAX >= 8U, ctx_line_ge8);

/** @} */ /* end of defgroup sh_cfg */

#ifdef __cplusplus
}
#endif

#endif /* SH_CFG_H */
