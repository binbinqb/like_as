/**
 * @file    sh.h
 * @brief   sh 命令行解释器 —— 平台无关接口（唯一对外头）
 *
 * @details 本头是 shell 中间件唯一对外接口，源自 ULP8 的 `lib/shell`
 *          （`shell.c` / `cmd.c` / `history.c`，共 1735 行），按 Bcm_Frame
 *          的规则重写：**零动态内存、零 C 库 stdio**。
 *
 * @section SH_FEATURES 能力清单
 * | 组 | 能力 |
 * |---|---|
 * | 命令注册 | 段注册 @ref SH_EXPORT_CMD，core 遍历 `hal_sh_cmd` 段，无需手改链接脚本 |
 * | 分词 | 引号感知（`'a b'` / `"a b"` 保留空格），参数上限 @ref SH_MAX_ARGS |
 * | 行编辑 | 光标左右 / Home / End / 中间插入 / 中间删除 / 退格 / 历史上下 / 数字快调 |
 * | 历史 | 静态环形 @ref SH_HISTORY_DEPTH 条，与最新一条重复则跳过 |
 * | 循环执行 | 命令后缀 `&period`、`&period,nloops`、`&min~max`，静态 context 池 |
 * | 后台管理 | `pause` / `kill` 内建命令，Ctrl-C 暂停，Ctrl-X 清空 |
 * | 前缀 | `sh_opt_prefix("lv")` 后仅响应 `lvXXX`，用于单总线上多机共存 |
 * | 应答协议 | SCPI 风格 `<±n, msg`，@ref sh_cmd_error 等宏统一出口 |
 *
 * @section SH_NOT_ULP8 与 ULP8 的有意差异
 * | ULP8 | 本实现 | 原因 |
 * |---|---|---|
 * | `sys_malloc` / `sys_free` | 全静态（结构体 + 定长数组） | 编码规范 §7 禁止运行期动态分配 |
 * | `printf` / `sprintf` / `scanf` | 自含 @ref sh_print + 手写解析器 | 规避半主机挂死与库体积 |
 * | `sys_line` 全局行缓冲 | 各命令自带缓冲 | 全局共享缓冲有重入风险 |
 * | `console_t` 多通道枚举 | 单个 @ref sh_io_t 绑定 | BCM 只有 UART；多通道做成 cfg 开关 |
 * | 链表历史 | 定长槽环形 | 静态内存下环形更省、无碎片 |
 * | `goto error` 清理 | 显式 if + return | 编码规范 §6.1「goto 不应使用」 |
 *
 * @section SH_USAGE 使用流程
 * @code
 *   // ① 平台侧把 hal_uart 包成 sh_io_t（见 src/debug/sh_port.c）
 *   sh_bind_io(&sh_io_uart2);
 *   // ② 主循环推进（由切面 hal_aspect_task_hook 调用亦可）
 *   for (;;) { sh_task(); }
 * @endcode
 *
 * @note    本头零 HAL 依赖 —— 通过 @ref sh_io_t 函数指针与平台解耦，
 *          与 `IsoTp_DebugShim` 同一套路。
 * @warning 段边界符号 `hal_sh_cmd$$Base/Limit` 由链接器按段名自动生成，
 *          **不可手工定义**；段名有意沿用旧的 `hal_sh_cmd`（见 @ref SH_CMD_SECTION）。
 *
 * @author  binbina
 * @version 1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-10-26 | binbina | 初版。从 ULP8 lib/shell 移植全功能：段注册命令引擎、行编辑状态机、静态环形历史、& 循环执行（context 池深度 2）、前缀过滤、SCPI 应答协议；动态内存全部改为静态，printf 族改为自含格式化器；保留 hal_sh_* 旧符号别名以兼容既有 15 个命令文件 |
 * | V1.0.1 | 2026-10-28 | binbina | `hal_sh_print` 兼容宏改为 `((void)sh_print(...))`：修 MISRA C:2012 Required Rule 17.7（全仓 264 处调用均直接丢弃 `sh_print` 的返回值）。一处改动替代 264 处 `(void)`，语义不变 |
 */

#ifndef SH_H
#define SH_H

#include "sh_port.h"

#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup sh Shell 中间件
 * @brief 自研命令行解释器，服务自动化测试与人工调试
 * @ingroup middleware
 * @{
 */

/* ── 命令描述符 ─────────────────────────────────────────────────── */

/**
 * @brief 命令函数签名
 * @param[in] argc 参数个数（argv[0] 为命令名自身）
 * @param[in] argv 参数数组，argv[0] = 命令名，argv[1..argc-1] = 实参
 * @return 命令返回码：0 = 成功；负值 = 错误（遵循 @ref hal_status_t 语义）
 * @note   argv 指向的行缓冲由 shell 持有，**命令不得保存该指针**超过本次调用。
 */
typedef int (*sh_cmd_func_t)(int argc, char *argv[]);

/**
 * @brief 命令描述符（落入 `hal_sh_cmd` 段，由 core 遍历）
 */
typedef struct {
    const char     *name;   /**< 命令名（@ref SH_EXPORT_CMD 自动字符串化） */
    sh_cmd_func_t   func;   /**< 命令函数 */
    const char     *help;   /**< 帮助文本（`help` 命令打印） */
} sh_cmd_t;

/**
 * @brief 命令描述符段名
 *
 * @details **有意沿用 ULP8 / 旧 hal_sh 的段名 `hal_sh_cmd`**：
 *          段名是链接器层面的契约，改名不会带来任何功能收益，却会让既有
 *          IAR 工程与已编译目标文件的注册项静默失配（表现为 `help` 命令列表
 *          变空，且**编译链接都不报错**）。接口前缀可以从 `hal_sh_` 收敛到
 *          `sh_`，但段名保持稳定。
 * @warning 若确需改名，必须同步验证 `.map` 中出现新段名并含预期项数。
 */
#define SH_CMD_SECTION      "hal_sh_cmd"

/* ── 段边界符号（按编译器分支，链接器自动生成，禁止手工定义） ───── */
#if defined(__ICCARM__)
    /** @brief IAR：段边界由 `#pragma section` 取得 */
    #pragma section = SH_CMD_SECTION
    #define SH_CMD_START    ((const sh_cmd_t *)__section_begin(SH_CMD_SECTION))
    #define SH_CMD_STOP     ((const sh_cmd_t *)__section_end(SH_CMD_SECTION))
#elif defined(__CC_ARM) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000))
    extern const sh_cmd_t hal_sh_cmd$$Base;     /**< 段首符号（armlink 生成） */
    extern const sh_cmd_t hal_sh_cmd$$Limit;    /**< 段尾符号（armlink 生成） */
    #define SH_CMD_START    (&hal_sh_cmd$$Base)
    #define SH_CMD_STOP     (&hal_sh_cmd$$Limit)
#elif defined(__GNUC__)
    extern const sh_cmd_t __start_hal_sh_cmd;   /**< 段首符号（GCC 生成） */
    extern const sh_cmd_t __stop_hal_sh_cmd;    /**< 段尾符号（GCC 生成） */
    #define SH_CMD_START    (&__start_hal_sh_cmd)
    #define SH_CMD_STOP     (&__stop_hal_sh_cmd)
#else
    #error "sh: unsupported compiler (need IAR / ARMCC / GCC)"
#endif

/**
 * @brief 导出一条命令到 `hal_sh_cmd` 段
 * @param[in] _name 命令名（标识符，宏内自动字符串化）
 * @param[in] _func 命令函数（签名 @ref sh_cmd_func_t）
 * @param[in] _help 帮助文本（字符串字面量）
 *
 * @note  生成 `static const` 段对象，无需在别处引用即被链接器保留
 *        （`used` 属性防止被优化掉）。
 * @warning 段属性属于实现细节，按编码规范 §5.2 只允许出现在本注册宏中，
 *          业务代码**不得**直接书写 `__attribute__((section(...)))`。
 * @code
 *   SH_EXPORT_CMD(dio, shell_dio, "dio -- list | name [0|1|t]");
 * @endcode
 */
#define SH_EXPORT_CMD(_name, _func, _help)                                  \
    static const sh_cmd_t _func##_shcmd                                     \
        __attribute__((used, section(SH_CMD_SECTION))) = {                  \
        .name = #_name, .func = (_func), .help = (_help) }

/**
 * @brief 导出一条**名称不是合法 C 标识符**的命令（如 `*IDN?`）
 * @param[in] _strname 命令名字符串字面量
 * @param[in] _ident   用于生成唯一符号名的 C 标识符（同文件内不得重复）
 * @param[in] _func    命令函数
 * @param[in] _help    帮助文本
 * @note  段注册宏必须能生成唯一的 `static` 对象名，而 `*IDN?` 无法作为标识符，
 *        故额外提供一个"标识符 + 显示名"分离的版本。
 * @code
 *   SH_EXPORT_CMD_AS("*IDN?", idn, sh_builtin_idn, "query board info");
 * @endcode
 */
#define SH_EXPORT_CMD_AS(_strname, _ident, _func, _help)                    \
    static const sh_cmd_t _ident##_shcmd                                    \
        __attribute__((used, section(SH_CMD_SECTION))) = {                  \
        .name = (_strname), .func = (_func), .help = (_help) }

/* ── 运行模式 ───────────────────────────────────────────────────── */

/**
 * @brief 运行模式（决定回显与提示符，不影响命令输出）
 * @note  与 @ref SH_CONFIG_MUTE 的区别：AUTO 只是**不回显不提示**，
 *        命令自身的输出照常打印（上位机脚本要读结果）；
 *        MUTE 是**连命令输出一起静默**（多机共享总线时用）。
 */
typedef enum {
    SH_MODE_AUTO   = 0,     /**< 自动模式：无回显、无提示符 */
    SH_MODE_MANUAL = 1      /**< 手动模式：回显 + 提示符 */
} sh_mode_t;

/* ── 配置位（可组合） ───────────────────────────────────────────── */
/** @brief 静默：连命令输出也不打印（多机共存时避免互相干扰） */
#define SH_CONFIG_MUTE      (1UL << 0)
/** @brief 锁定：不接收输入（行编辑整体跳过） */
#define SH_CONFIG_LOCK      (1UL << 1)
/** @brief 暂停：后台循环命令不推进（已入队的 context 保留） */
#define SH_CONFIG_PAUS      (1UL << 2)

/* ── shell 层返回码 ─────────────────────────────────────────────── */
/** @brief 成功 */
#define SH_OK               (0)
/** @brief 通用错误 */
#define SH_ERR              (-1)
/** @brief 命令不存在 */
#define SH_ERR_NOTFOUND     (-2)
/** @brief 参数错误 */
#define SH_ERR_PARAM        (-3)
/** @brief 资源不足（context 池满 / vram 表满 / 环形缓冲满） */
#define SH_ERR_NOMEM        (-4)

/* ── 应答协议文本（SCPI 风格，上位机按正则抓取） ────────────────── */
/** @brief 成功应答 */
#define SH_RET_OK       "<+0, OK!\n"
/** @brief 命令不存在 */
#define SH_RET_NOCMD    "<-1, cmd not exist\n"
/** @brief 参数错误 */
#define SH_RET_PARA     "<-100, cmd para error\n"
/** @brief 条件不满足 */
#define SH_RET_CNDS     "<-200, cmd refused dueto conditions are not met\n"
/** @brief 执行错误 */
#define SH_RET_EXEC     "<-300, cmd exec error\n"
/** @brief 内存不足 */
#define SH_RET_NOMEM    "<-400, no enough memory\n"

/** @brief 参数错误应答，带具体说明（字符串拼接，无运行期格式化开销） */
#define SH_RET_PARA_OF(info)    ("<-100, cmd para error(" info ")\n")
/** @brief 条件不满足应答，带具体说明 */
#define SH_RET_CNDS_OF(info)    ("<-200, cmd cnds error(" info ")\n")
/** @brief 执行错误应答，带具体说明 */
#define SH_RET_EXEC_OF(info)    ("<-300, cmd exec error(" info ")\n")

/* ── I/O 适配层（平台无关的关键：middleware 不 include 任何 hal_xxx.h） ── */

/**
 * @brief 平台 I/O 操作集
 * @details 由平台侧（如 `src/debug/sh_port.c`）实现并绑定，shell 只认这三个函数。
 */
typedef struct {
    /**
     * @brief 非阻塞读一个字节
     * @return 读到字节（0~255）；无数据返回 -1
     */
    int      (*getc)(void);

    /**
     * @brief 阻塞写一段字节
     * @param[in] data 数据指针，不得为 NULL
     * @param[in] len  字节数，可为 0（此时应直接返回）
     * @note  实现可以是阻塞的：shell 侧已用 TX 环把大批量输出摊成小片，
     *        单次调用长度不超过 @ref SH_TX_CHUNK。
     */
    void     (*write)(const uint8_t *data, uint16_t len);

    /**
     * @brief 毫秒时基
     * @return 单调递增的毫秒计数（允许回绕，shell 侧按无符号差处理）
     */
    uint32_t (*ms)(void);
} sh_io_t;

/* ── 对外 API ───────────────────────────────────────────────────── */

/**
 * @brief 绑定平台 I/O（只做绑定，不初始化硬件）
 * @param[in] io 操作集指针，不得为 NULL；指向的对象**必须常驻**（不得为栈变量）
 * @retval HAL_OK       绑定成功
 * @retval HAL_ERR_PARAM @p io 为 NULL 或三个函数指针有空
 * @pre  平台侧已完成 UART 初始化（本函数不碰硬件）
 * @note 可在运行期重新绑定（切换控制台通道），旧绑定被整体替换。
 */
hal_status_t sh_bind_io(const sh_io_t *io);

/**
 * @brief 复位 shell 内部状态
 * @details 清行缓冲、历史、后台队列、context 池、配置位，回到上电初值。
 *          不解除 I/O 绑定（绑定属于平台侧生命周期）。
 * @note  用于软复位后重新初始化；重复调用安全。
 */
void sh_init(void);

/**
 * @brief 主循环任务（每周期调用一次，非阻塞）
 * @details ① 排空 TX 环一片（≤ @ref SH_TX_CHUNK 字节）；
 *          ② 处理 ESC 序列超时；
 *          ③ 推进后台循环命令（@ref SH_CONFIG_PAUS 时跳过）；
 *          ④ 非阻塞读取 UART 字节喂入行编辑状态机；
 *          ⑤ 收到完整行则分词执行。
 * @warning 不得在 ISR 中调用（内部会写 UART）。
 */
void sh_task(void);

/**
 * @brief 上电横幅 + 初始提示符（进主循环前调用一次）
 * @details MANUAL 模式追加提示符，让人眼确认 shell 已就绪；
 *          AUTO 模式仅打印版本行。
 * @note  须在 @ref sh_bind_io 之后调用；内部只入队不阻塞。
 */
void sh_banner(void);

/**
 * @brief 格式化打印（替代 C 库 printf）
 * @param[in] fmt 格式串，支持 `%[l][duxXcs%]`、`%-N` 左对齐、`%0N` 零填充、
 *                `%+d` 强制符号；宽度 N ≤ 99
 * @param[in] ... 可变参数
 * @return 本应写入的字符数（不含结尾 `\0`，截断时仍计入）
 * @note  内部自含格式化器，**不依赖 C 库 stdio**，规避半主机挂死。
 * @warning @p fmt **必须是字符串字面量**，不得传入变量 —— 变量当格式串
 *          既是 MISRA C:2012 Rule 17.1 的问题，也会在内容含 `%s` 时读出野指针。
 * @warning 与 @ref sh_vprint 共用静态缓冲 ⇒ 不可重入（应用上下文内安全）。
 */
int sh_print(const char *fmt, ...);

/**
 * @brief 格式化打印（va_list 版）—— 供日志后端转发
 * @param[in] fmt 格式串，语义同 @ref sh_print
 * @param[in] ap  已由调用方 `va_start` 初始化的参数表
 * @return 本应写入的字符数（不含结尾 `\0`）
 * @note  供 `src/debug/log_backend.c` 把 `hal_log_emit` 的参数转进来。
 */
int sh_vprint(const char *fmt, va_list ap);

/**
 * @brief 格式化到指定缓冲（替代 C 库 snprintf）
 * @param[out] buf  输出缓冲，不得为 NULL
 * @param[in]  size 缓冲容量（含结尾 `\0` 位置）
 * @param[in]  fmt  格式串，语义同 @ref sh_print
 * @param[in]  ...  可变参数
 * @return 本应写入的字符数（不含 `\0`；≥ @p size 表示被截断）
 * @note  输出**保证以 `\0` 结尾**（@p size > 0 时）。
 */
int sh_snprintf(char *buf, size_t size, const char *fmt, ...);

/**
 * @brief 向控制台写字符串（原样输出，不做格式化）
 * @param[in] s 以 `\0` 结尾的字符串；NULL 时直接返回
 * @note  主循环启动前为阻塞直写（保证启动日志即时有序）；
 *        启动后为**入队**，由 @ref sh_task 每圈排空一片。
 */
void sh_puts(const char *s);

/**
 * @brief 向控制台写一个字符
 * @param[in] c 待发送字符
 */
void sh_putch(char c);

/**
 * @brief 排空 TX 环一片（每次最多 @ref SH_TX_CHUNK 字节）
 * @details 由 @ref sh_task 每圈调用。单独调用者需自行保证周期性
 *          （如 `hal_power_cmd` 休眠前主动排空，否则会丢最后几行输出）。
 * @note  首次调用即把输出切换为排队模式。
 */
void sh_tx_drain(void);

/** @brief TX 环积压字节数（诊断；持续非 0 = 输出速率超出串口带宽） */
uint16_t sh_tx_backlog(void);

/** @brief TX 环满丢弃字节数（诊断；正常恒 0，>0 说明需加大环容量） */
uint32_t sh_tx_dropped(void);

/**
 * @brief 执行一条命令行（外部注入，不经过行编辑）
 * @param[in] cmdline 命令行字符串，不得为 NULL
 * @return 命令返回码；命令不存在返回 @ref SH_ERR_NOTFOUND
 * @note  同步执行，返回时命令已跑完。支持 `&` 后缀（转后台，立即返回）。
 * @warning 不得在 ISR 中调用。
 */
int sh_exec(const char *cmdline);

/**
 * @brief 阻塞读一行（供需要交互确认的命令使用）
 * @param[in] prompt 提示符；NULL 表示不打印提示符
 * @return 读到的行（指向 shell 内部行缓冲，**不可长期持有**）
 * @details 内部自己轮询 @ref sh_io_t::getc，不依赖 @ref sh_task 推进。
 * @warning **会阻塞调用者**直到收到回车。裸机场景下调用期间主循环停摆，
 *          喂狗与周期任务需自行保证；RTOS 场景建议改用独立任务。
 * @warning 不得在 ISR 中调用。
 */
char *sh_readline(const char *prompt);

/**
 * @brief 绑定系统复位回调（供 `*RST` 内建命令使用）
 * @param[in] reset_fn 复位函数；NULL = 取消绑定（`*RST` 变为"不支持"）
 *
 * @details 为什么需要这个钩子：`*RST` 必须真正复位 MCU，而复位属于 HAL/平台层，
 *          `middleware/shell` **不得** include `hal_reset.h`（分层单向）。
 *          用一个函数指针把"要不要真的复位、怎么复位"交回平台侧，
 *          与 @ref sh_io_t 是同一套路。
 * @note  未绑定时 `*RST` 返回 `<-5, not supported`，而不是假装成功 ——
 *        "命令返回 OK 但系统没复位"会让自动化脚本误判。
 */
void sh_bind_reset(void (*reset_fn)(void));

/**
 * @brief 读取当前运行模式
 * @return 当前 @ref sh_mode_t
 */
sh_mode_t sh_get_mode(void);

/**
 * @brief 设置运行模式（只改状态，不打印提示符）
 * @param[in] mode 目标模式
 * @retval HAL_OK       成功
 * @retval HAL_ERR_PARAM @p mode 越界
 * @note  提示符刷新由调用方统一负责，避免重复输出。
 */
hal_status_t sh_set_mode(sh_mode_t mode);

/**
 * @brief 置位/清除配置位
 * @param[in] bits 配置位掩码（@ref SH_CONFIG_MUTE 等，可组合）
 * @param[in] on   true = 置位，false = 清除
 */
void sh_config_set(uint32_t bits, bool on);

/**
 * @brief 查询配置位是否全部置位
 * @param[in] bits 配置位掩码
 * @retval true  全部置位
 * @retval false 任一位未置位
 */
bool sh_config_get(uint32_t bits);

/**
 * @brief 设置命令名前缀（多机共存时只响应带前缀的命令）
 * @param[in] prefix 前缀字符串；NULL 取消前缀
 * @details 设置后 `lvGPIO` 与 `GPIO` 等价，用于同一条 UART 总线挂多个 MCU。
 * @note  前缀字符串**必须常驻**（不得为栈变量）。
 */
void sh_opt_prefix(const char *prefix);

/**
 * @brief 打印全部已注册命令（名称 + 帮助）
 * @details 遍历 `hal_sh_cmd` 段；供 `help` 内建命令与 Tab 键复用。
 */
void sh_cmd_list_print(void);

/**
 * @brief 按名查找命令描述符
 * @param[in] name 命令名（已去除前缀的原始输入）
 * @return 描述符指针；**未找到返回 NULL**
 * @note  未找到时由调用方决定如何应答（默认打印 `<-1, cmd not exist`）。
 *        不返回"兜底项"是刻意的：兜底项会让"命令名拼错"与"命令执行失败"
 *        无法区分，而调试场景下这两者的处理方式完全不同。
 */
const sh_cmd_t *sh_cmd_find(const char *name);

/**
 * @brief 严格解析十进制无符号整数（命令参数解析的唯一真源）
 * @param[in]  s   待解析字符串（以 `\0` 结尾）
 * @param[out] val 解析结果；**仅当返回 true 时有效**
 * @retval true  成功（非空且整串均为 `'0'`~`'9'`，未溢出 uint32）
 * @retval false 失败（空串 / NULL / 含非数字字符 / 溢出）
 * @details 严格要求"整串都是数字"：`"12a"` / `"-1"` / `" 12"` 一律判失败。
 *          调用方据此给出明确提示，**不要把解析失败静默当成 0**。
 * @note  不用 `strtoul` —— 它溢出时走半主机路径会挂死 shell。
 * @warning 本函数是 shell 参数解析的**唯一真源**。曾因各命令文件各写一份，
 *          且有的实现把非数字字符当 0 返回，导致 `adc read abc` 静默读第 0 路
 *          （现象为"命令没报错但结果不对"）。新增命令请一律调本函数。
 */
bool sh_parse_u32(const char *s, uint32_t *val);

/* ── 历史接口（core / 内建命令使用） ───────────────────────────── */

/**
 * @brief 追加一条命令到历史环形缓冲
 * @param[in] cmd 命令字符串（以 `\0` 结尾）；空串直接忽略
 * @note  与最新一条完全相同时跳过，避免连续重复。
 */
void sh_history_add(const char *cmd);

/**
 * @brief 回退到更早一条历史（上方向键）
 * @return 历史字符串指针；无更早历史返回 NULL
 */
const char *sh_history_prev(void);

/**
 * @brief 前进到更新一条历史（下方向键）
 * @return 历史字符串指针；已回到"最新之后"（空行）返回 NULL
 */
const char *sh_history_next(void);

/**
 * @brief 将历史游标复位到"最新之后"
 */
void sh_history_reset_cursor(void);

/* ── 后台循环执行接口（core / 内建命令使用） ───────────────────── */

/**
 * @brief 推进后台循环命令（由 @ref sh_task 每圈调用）
 * @details 遍历 context 池，到期者执行；执行完毕者释放槽位。
 * @note  @ref SH_CONFIG_PAUS 置位时本函数直接返回（任务保留不丢）。
 */
void sh_bg_run(void);

/**
 * @brief 清空全部后台循环任务
 * @return 被清掉的条数
 */
uint16_t sh_bg_kill_all(void);

/**
 * @brief 打印当前后台任务列表（供 `pause` 命令）
 */
void sh_bg_list_print(void);

/**
 * @brief 查询当前正在执行的命令是否处于循环模式
 * @retval 0 普通一次性命令
 * @retval 1 循环命令（第 2 次及以后执行）
 * @note  供命令自己判断"要不要每轮都打印表头"。
 *        只能在命令函数内部调用（依赖"当前 context"这一隐含上下文）。
 */
int sh_is_repeated(void);

/**
 * @brief 命令执行前置钩子（**弱符号**，默认放行）
 * @param[in] cmdline 待执行命令行（已剥离 `&` 后缀，尚未分词）
 * @return 0 = 继续执行；非 0 = 跳过本次执行
 *
 * @details 供上层插入访问控制 / 审计 / 命令别名等策略，**无需改 shell 实现**。
 *          钩子返回非 0 时 shell **不打印任何内容** —— 是否给出提示由钩子决定
 *          （安全场景下"命令存在但被拒绝"本身就是要隐瞒的信息）。
 * @warning 在任务上下文调用；实现不得阻塞超过一个主循环周期。
 */
int sh_on_exec(char *cmdline);

/* ── 前向声明：命令上下文（定义在 sh_bg.c，仅 core 需要细节） ───── */
struct sh_context_s;

/** @} */ /* end of defgroup sh */

/* ══════════════════════════════════════════════════════════════════
 * 兼容层：既有 15 个 `src/hal/<模块>/cmd/<模块>_cmd.c` 与 `debug` 下
 *         的用法都使用 `hal_sh_*` 旧符号。这里全部做成别名，**旧文件零改动**。
 *         新代码请直接用 `sh_*`。
 * ══════════════════════════════════════════════════════════════════ */

/** @brief 旧名兼容：命令段注册宏 */
#define HAL_SH_EXPORT_CMD(_name, _func, _desc)  SH_EXPORT_CMD(_name, _func, _desc)
/** @brief 旧名兼容：命令描述符类型 */
#define hal_sh_cmd_t                            sh_cmd_t
/** @brief 旧名兼容：命令函数签名类型 */
#define hal_sh_cmd_func_t                       sh_cmd_func_t
/** @brief 旧名兼容：格式化打印（**显式丢弃返回值**）
 *  @details `sh_print` 返回"本应输出的字符数"，全仓 264 处调用无一使用。
 *           裸写 `hal_sh_print(...)` 属 MISRA C:2012 **Required** Rule 17.7
 *           （返回值未使用须显式 `(void)`）。在此一处吞掉，比改 264 个调用点
 *           更安全：语义不变、无 diff 噪音、新代码写错也无所谓。
 *  @note 需要判断"是否真的输出成功"时**不要**用本宏，直接调 @ref sh_print。 */
#define hal_sh_print(...)                       ((void)sh_print(__VA_ARGS__))
/** @brief 旧名兼容：格式化打印（va_list） */
#define hal_sh_vprint                           sh_vprint
/** @brief 旧名兼容：主循环任务 */
#define hal_sh_task                             sh_task
/** @brief 旧名兼容：上电横幅 */
#define hal_sh_banner                           sh_banner
/** @brief 旧名兼容：严格解析 u32 */
#define hal_sh_parse_u32                        sh_parse_u32
/** @brief 旧名兼容：TX 环排空 */
#define hal_sh_tx_drain                         sh_tx_drain
/** @brief 旧名兼容：TX 环积压查询 */
#define hal_sh_tx_backlog                       sh_tx_backlog
/** @brief 旧名兼容：TX 环丢弃计数 */
#define hal_sh_tx_dropped                       sh_tx_dropped
/** @brief 旧名兼容：命令列表打印 */
#define hal_sh_cmd_list_print                   sh_cmd_list_print
/** @brief 旧名兼容：读模式 */
#define hal_sh_get_mode                         sh_get_mode
/** @brief 旧名兼容：设模式 */
#define hal_sh_set_mode                         sh_set_mode
/** @brief 旧名兼容：历史追加 */
#define hal_sh_history_add                      sh_history_add
/** @brief 旧名兼容：历史回退 */
#define hal_sh_history_prev                     sh_history_prev
/** @brief 旧名兼容：历史前进 */
#define hal_sh_history_next                     sh_history_next
/** @brief 旧名兼容：历史游标复位 */
#define hal_sh_history_reset_cursor             sh_history_reset_cursor

/** @brief 旧名兼容：成功 */
#define HAL_SH_OK                               SH_OK
/** @brief 旧名兼容：通用错误 */
#define HAL_SH_ERR                              SH_ERR
/** @brief 旧名兼容：命令不存在 */
#define HAL_SH_ERR_NOTFOUND                     SH_ERR_NOTFOUND
/** @brief 旧名兼容：参数错误 */
#define HAL_SH_ERR_PARAM                        SH_ERR_PARAM
/** @brief 旧名兼容：自动模式 */
#define HAL_SH_MODE_AUTO                        SH_MODE_AUTO
/** @brief 旧名兼容：手动模式 */
#define HAL_SH_MODE_MANUAL                      SH_MODE_MANUAL

#ifdef __cplusplus
}
#endif

#endif /* SH_H */
