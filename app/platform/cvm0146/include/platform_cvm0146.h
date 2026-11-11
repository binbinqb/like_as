/**
 * @file    platform_cvm0146.h
 * @brief   CVM0146 平台层（AS 平台层的 CVM014x 实现）—— 启动期最小接口
 *
 * @details 本文件是 `app/platform/cvm0146/` 对**上层**暴露的唯一入口。
 *          对应 AS 原项目中 `app/platform/<mcu>/src/simulator.c` 的角色：
 *          把厂商 SDK 的初始化序列收敛到一处，上层（应用 / BSW）不直接碰 SDK。
 *
 *          @section PLATFORM_LAYER 与 Bcm_Frame 的关系
 *          这里**没有**复制 Bcm_Frame 的 HAL：AS 原型优先验证“AS 的 BSW + 厂商 SDK
 *          能不能在 CVM0146 上跑通”。等 M1 接 CanIf 时，平台层的 `CanAc_*`
 *          才会决定是“包厂商 FlexCAN 驱动”还是“包 Bcm_Frame 的 hal_can”。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：时钟（FIRC）+ UART2 控制台 |
 */

#ifndef PLATFORM_CVM0146_H
#define PLATFORM_CVM0146_H

#include <stdint.h>

/* `Std_ReturnType` / `E_OK`：平台接口统一用 AUTOSAR 的返回约定。
 * 这不是 SDK 依赖 —— `Std_Types.h` 只有类型和常量，不碰任何寄存器，
 * 应用层本来就通过 `infras/include` 依赖它。 */
#include "Std_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 平台初始化：MCU 驱动句柄 → 时钟 → 控制台串口
 *
 * @details 顺序固定，且**必须在任何打印之前**调用：
 *          1) `Mcu_Init()` 填充厂商驱动的对象（只初始化结构，不动硬件）；
 *          2) 开 PORT 门控 + 选 UART2 时钟源；
 *          3) 配 UART2 引脚（PTD17 RX / PTE12 TX，ALT3）与波特率。
 *
 * @note M0 故意用 **FIRC 48 MHz** 而不是外部晶振：晶振起不来时 `Clock_Config`
 *       会卡在等待 SOSC ready，表现为“一行输出都没有”，无法与死机区分。
 *       等 M1 验证完 CAN 再切 SOSC + PLL 120 MHz（届时用串口先打点，卡住也看得见）。
 */
void Platform_Init(void);

/**
 * @brief 输出一个字符（阻塞等待发送寄存器空）
 * @param[in] c 字符；`'\n'` 会自动补 `'\r'`（多数串口终端需要 CRLF）
 */
void Platform_PutChar(char c);

/**
 * @brief 输出以 `'\0'` 结尾的字符串
 * @param[in] s 字符串；NULL 视为空串
 */
void Platform_Puts(const char *s);

/**
 * @brief 嵌入式格式化输出（不依赖 newlib）
 *
 * @details 支持的转换符：`%d %i %u %x %X %c %s %p %%`。
 *          支持的修饰符：
 *          | 类别 | 可用 | 说明 |
 *          |------|------|------|
 *          | 标志 | `-` `+` ` ` `#` `0` | 左对齐 / 正号 / 空格 / 进制前缀 / 补零 |
 *          | 宽度 | 数字、`*` | `%6u`、`%-6s`；负宽度等价左对齐 |
 *          | 精度 | `.数字`、`.*` | 整数=最少位数，字符串=最大字符数 |
 *          | 长度 | `l` `h` `hh` `z` | 只影响 `va_arg` 的取参宽度 |
 *
 *          **不支持**：浮点（`%f %e %g`）与 64 位（`%lld`）。遇到这两类会打印
 *          `<bad fmt %?> / <ll?>` 并**终止本次格式化**，而不是静默跳过——
 *          因为跳过会让 `va_arg` 与后续格式符错配，把整数当指针解引用，
 *          直接 HardFault，比少打一行日志严重得多。
 *
 *          为什么不用 newlib 的 `printf`：newlib 会拉进 `_sbrk/_write` 一整套
 *          syscall 桩，链接体积与故障面都变大。M1 起改用 AS `infras/libraries/libc`
 *          的实现，本函数届时删除。
 *
 * @param[in] fmt 格式串
 * @return 实际输出的字符数（遇到不支持的转换符时返回已输出的部分）
 *
 * @warning 宽度/精度必须是**编译期字面量**才零成本；`*` 会多读一个 `int` 参数。
 * @note    自检用例见 `app/demo/src/main.c` 的 `PrintfSelfTest()`，
 *          上板后可跑 `tools/m0_check.py` 自动核对全部 17 项。
 */
int Platform_Printf(const char *fmt, ...);

/**
 * @brief 启动 1 ms 时基（SysTick）
 *
 * @note 内核跑 PLL 120 MHz（`SystemInit` 默认），重载值 120000。
 *       若将来改时钟树，**必须同步改** `platform_cvm0146.c` 里的 `CORE_CLOCK_HZ`，
 *       否则 `Platform_NowMs()` 走得比真实时间慢/快，而且没有任何报错。
 */
void Platform_InitTick(void);

/**
 * @brief 取开机以来的毫秒数
 * @return 毫秒计数（49.7 天回绕）
 */
uint32_t Platform_NowMs(void);

/**
 * @brief 非阻塞读一个字符
 * @return 0..255 为读到的字节；-1 表示当前没有数据
 */
int Platform_GetChar(void);

/* ============================ [ 低功耗 / 唤醒（M12） ] ============================ */

/**
 * @brief 取本次上电/复位是由什么唤醒的（厂商 `PowerDrvWakeupFlagType`）
 * @return 0=PORTA 1=PORTB 2=PORTC 3=PORTD 4=PORTE
 *         5=复位引脚 6=RTC 7=LPIT 8=LPTMR 9=CMP
 *         0xFF = 没有唤醒标志（正常冷启动）
 *
 * @note  **这是纯读操作**，不会改变任何状态，随时可以调。
 *        放在启动横幅里打一行，是排查"板子为什么自己醒了/为什么没睡"
 *        的第一手证据 —— 实车上没有调试器，只能靠这一行日志。
 *
 * @warning 厂商枚举里"无唤醒标志"是 **-1**（有符号），
 *          在 `uint8_t` 里会变成 0xFF，所以本接口统一返回 `uint8_t`
 *          并用 `PLATFORM_WAKEUP_NONE` 表示"无"。
 */
uint8_t Platform_GetWakeupSource(void);

/** @brief `Platform_GetWakeupSource()` 的"无唤醒标志"返回值 */
#define PLATFORM_WAKEUP_NONE    (0xFFu)

/**
 * @brief 唤醒源的短名字（用于打印）
 * @param[in] src `Platform_GetWakeupSource()` 的返回值
 * @return 常量字符串，永不为 NULL
 */
const char *Platform_GetWakeupSourceName(uint8_t src);

/**
 * @brief 清掉本次的唤醒标志（为下一次睡眠做准备）
 * @note  厂商的 `PowerDrv_GetWakeupSource()` 读的是粘滞标志，
 *        不清的话下一次醒来仍会报同一个源。每次睡眠**之前**必须调。
 */
void Platform_ClearWakeupFlags(void);

/**
 * @brief 进入 Cortex-M Sleep（厂商称 STOP 模式），直到有中断唤醒
 *
 * @details @section PLATFORM_STOP 它到底睡多深
 *
 *          厂商 `PowerDrv_SetPowerMode(POWERDRV_POWER_MODE_STOP)` 的实现是
 *          （`power_drv.c`）：
 *          @code
 *          SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;   // 清 DeepSleep 位
 *          __WFI();
 *          @endcode
 *          也就是说它是 **Cortex-M 的 Sleep 模式**（不是 DeepSleep）：
 *          - 内核时钟停，外设时钟保持；
 *          - **NVIC 仍在工作**，任何使能的中断都能唤醒。
 *
 *          这个特性很重要：**只要 SysTick 还开着，WFI 会在下一个 tick
 *          立刻返回**（1 ms）。所以：
 *          - 想量出"真的睡了多久"，调用前必须 `Platform_StopTick()`；
 *          - 反过来说，**忘了停 tick 也绝不会睡死** —— 最坏情况是
 *            "睡了 1 ms 又醒了"，是个安全的失败模式。
 *
 *          真正把电流降下来要停 SysTick 并进 DeepSleep/Standby，
 *          那属于下一步（需要确认唤醒源硬件，且一旦配错要断电恢复）。
 *
 * @pre   调用前必须配好至少一个唤醒源（否则靠 tick 立刻返回）
 * @note  返回后 `Platform_NowMs()` 可能没有前进（tick 停了），
 *        需要由调用者用 `Platform_StartTick()` 恢复。
 */
void Platform_EnterStopMode(void);

/**
 * @brief 停 SysTick（进睡眠前调用）
 * @warning 停掉之后 `Platform_NowMs()` **不再前进**，所有基于它的超时
 *          （CanTp 的 N_Bs、Dcm 的 S3、NM 的超时）都会"冻住"。
 *          所以只能在"已经确认要睡"之后调，醒来第一件事就是 `Platform_StartTick()`。
 */
void Platform_StopTick(void);

/**
 * @brief 改变 SysTick 的中断周期（毫秒）
 * @param[in] ms 新周期，必须 ≥ 1
 *
 * @details @section PLATFORM_TICK_PERIOD 为什么要动态改周期
 *
 *          进睡眠前把周期从 1 ms 放大到 100 ms，有两个作用：
 *          1. **兜底唤醒**：即使没有任何外设中断，100 ms 后 CPU 也一定会被叫醒 ——
 *             这保证 `!z` 这类手动睡眠命令**不可能把板子睡死**；
 *          2. **让"真的睡过"可测**：1 ms 节拍下 WFI 几乎立刻返回，
 *             量不出任何东西；100 ms 下能清楚看到 `Platform_NowMs()`
 *             只前进了 1，而墙钟过了 100 ms。
 *
 *          @warning `Platform_NowMs()` 的计数速率会随之改变。只在
 *          "已经决定要睡、所有超时逻辑都不再关心"的窗口里用。
 */
void Platform_SetTickPeriodMs(uint32_t ms);

/**
 * @brief 重新启动 SysTick（醒来后调用）
 * @note  会重装 1 ms 周期。`Platform_NowMs()` 的累计值**不补偿**
 *        睡眠期间的时间 —— 因为睡眠期间本来就没有 tick，
 *        补偿反而会让所有超时逻辑误判。需要墙钟时间请另配 RTC。
 */
void Platform_StartTick(void);

/* ============================ [ PFlash 擦写 ] ============================ */
/*
 * 刷写（boot 写 meta / app 写非活动槽）唯一的底层入口。
 * 地址与分区的语义在 `boot_flash_map.h`，本组函数只认"裸地址 + 长度"。
 *
 * @warning 擦/写期间会**关全局中断**（单扇区约 20~40 ms）。因此：
 *          - 整片擦除必须由上层分片，每片之间开中断喂狗、处理 CAN；
 *          - 不要在 CAN 接收中断里直接调用（会自锁在关中断里）。
 */

/**
 * @brief 判断一段 PFlash 是否为擦除态（全 0xFF）
 * @param[in] addr 起始地址（8 字节对齐）
 * @param[in] len  字节数（8 的整数倍）
 * @retval E_OK     全 0xFF，可直接写
 * @retval E_NOT_OK 有非 0xFF 字节 / 参数越界或未对齐
 * @note  走 FTFC 的 SCTRD1S 硬件判空命令，不是 CPU 逐字节比较。
 */
Std_ReturnType Platform_FlashIsErased(uint32_t addr, uint32_t len);

/**
 * @brief 擦除**一个** PFlash 扇区（2 KB）
 * @param[in] addr 扇区起始地址，必须 2 KB 对齐
 * @retval E_OK     擦除成功且回读确认全 0xFF
 * @retval E_NOT_OK 地址不对齐 / 越界 / 命令失败 / 擦完仍有残留
 * @note  已经是擦除态时**直接返回 E_OK、不重复擦**，省擦写寿命。
 * @warning 只能擦不在执行中的扇区。boot 擦 meta（槽尾）、app 擦另一个槽
 *          都满足；但**不要擦自己正在跑的扇区**，那会导致取指失败。
 */
Std_ReturnType Platform_FlashEraseSector(uint32_t addr);

/**
 * @brief 写入 PFlash（按 8 字节 phrase 逐条烧写 + 回读校验）
 * @param[in] addr 目标地址（8 字节对齐）
 * @param[in] data 源数据
 * @param[in] len  字节数（8 的整数倍）
 * @retval E_OK     全部写入并校验通过
 * @retval E_NOT_OK 参数非法 / 目标区未擦净 / 烧写命令失败 / 回读不一致
 * @pre   目标区域必须已擦除，否则返回 E_NOT_OK（不会写坏，只是拒绝）
 */
Std_ReturnType Platform_FlashWrite(uint32_t addr, const void *data, uint32_t len);

/**
 * @brief 读取 PFlash 到缓冲区
 * @param[in]  addr 源地址
 * @param[out] buf  目的缓冲
 * @param[in]  len  字节数
 * @note  PFlash 可寻址，直接 `memcpy`。参数越界时**什么都不做**
 *        （不清缓冲、不报错）—— 调用方应先自行校验地址。
 */
void Platform_FlashRead(uint32_t addr, void *buf, uint32_t len);

/* ============================ [ 跳转到应用 ] ============================ */

/**
 * @brief 从 boot 跳到应用镜像（不返回）
 *
 * @details 跳转前依次做四件事，缺任何一件都会在 app 侧表现为
 *          "偶尔 HardFault"或"第一个中断跑飞"：
 *          1. 停 SysTick（避免 boot 的中断打到即将失效的向量表上）；
 *          2. 关掉并清除全部 NVIC 中断（boot 使能过 UART2 接收）；
 *          3. `VTOR` 指向镜像自己的向量表（app 的 `init_data_bss()` 随后
 *             会把它改到 RAM，那才是最终值）；
 *          4. 用镜像首字重设 MSP，再跳到第二个字。
 *
 * @param[in] base 镜像基址（必须与链接地址一致，否则代码里的绝对地址全错）
 * @warning 向量表头两个字段为 0 / 0xFFFFFFFF 时**直接返回、不跳转**。
 *          调用方应当已经用 `BootMeta_CheckImage()` 做过完整校验，
 *          这里只是最后一道保险。
 * @note  不返回。若目标函数意外返回，本函数就地死循环等看门狗复位。
 */
void Platform_JumpToApp(uint32_t base);

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_CVM0146_H */
