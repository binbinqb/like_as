/**
 * @file    platform.h
 * @brief   平台层**与芯片无关**的那部分契约（时间、控制台、复位原因）
 *
 * @details @section PLATFORMIF_WHY 为什么需要一个与芯片无关的头
 *
 *          `platform_cvm0146.h` 里混着两类东西：
 *
 *          | 类别 | 例子 | 谁能用 |
 *          |------|------|--------|
 *          | 芯片相关 | `Platform_FlashEraseSector()`、`Platform_JumpToApp()` | 只有本平台 |
 *          | 芯片无关 | `Platform_NowMs()`、`Platform_Puts()` | **业务代码也要用** |
 *
 *          业务代码（`bcm_biz.c`、`rx_mon.c`）为了拿一个毫秒计数去 include
 *          `platform_cvm0146.h`，等于把业务焊死在 CVM0146 上——Host 构建
 *          第一次尝试就撞在这里。
 *
 *          本文件只声明第二类。两边平台各实现一份：
 *
 *          | 平台 | 实现 | 时间源 |
 *          |------|------|--------|
 *          | CVM0146 | `platform_cvm0146.c` | SysTick 1 ms |
 *          | Host | `app/platform/host/src/platform_host.c` | 可推进的虚拟时钟 |
 *
 * @note  `platform_cvm0146.h` 仍然保留自己的完整声明（含上面这些），
 *        所以在同一个编译单元里同时 include 两个头是合法的——重复的
 *        原型只要一致就不算冲突。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版：从 platform_cvm0146.h 抽出芯片无关子集 |
 */

#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 平台初始化（Host 上是空实现）
 */
void Platform_Init(void);

/**
 * @brief 输出一个字符
 * @param[in] c 字符
 */
void Platform_PutChar(char c);

/**
 * @brief 输出以 `'\0'` 结尾的字符串
 * @param[in] s 字符串；NULL 视为空串
 */
void Platform_Puts(const char *s);

/**
 * @brief 绑定控制台输出汇
 * @param[in] fn 每字符回调；NULL = 恢复默认出口
 */
void Platform_SetConsoleSink(void (*fn)(char c));

/**
 * @brief 格式化输出
 * @return 写出的字符数
 */
int Platform_Printf(const char *fmt, ...);

/**
 * @brief 启动 1 ms 节拍
 */
void Platform_InitTick(void);

/**
 * @brief 从上电到现在的毫秒数（`uint32_t`，约 49.7 天回绕）
 *
 * @details 所有业务定时（去抖、超时、NM 周期）都以它为唯一时间基准。
 *          Host 版本由测试代码用 `Host_AdvanceMs()` 手动推进，
 *          因此"3 秒去抖"这类用例可以瞬间跑完，不需要真的等 3 秒。
 */
uint32_t Platform_NowMs(void);

/**
 * @brief 非阻塞读一个控制台字符
 * @return 字符；无输入返回 -1
 */
int Platform_GetChar(void);

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_H */
