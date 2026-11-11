/**
 * @file    boot_app.h
 * @brief   应用侧的 A/B 配合动作：自注册与启动确认
 *
 * @details boot 与 app 各管一半：
 *          | 动作 | 谁做 | 时机 |
 *          |------|------|------|
 *          | 选槽、校验、跳转、回滚 | boot | 上电 |
 *          | 补写 meta（首次烧写） | app `BootApp_Init` | 平台初始化后 |
 *          | 声明"我跑起来了" | app `BootApp_Confirm` | BSW 全起来之后 |
 *
 *          @section BOOTAPP_CONFIRM 为什么确认要等 BSW 起来
 *          `BootApp_Confirm` 是"新镜像能跑"的唯一证据。如果放在 `main` 开头，
 *          那么"时钟配好了、但 CAN 起不来导致整车功能全失"这种镜像也会被
 *          判为成功，回滚机制形同虚设。所以要等 `EcuM_RequestRUN` 之后
 *          （CAN 控制器已 STARTED、收发器已 NORMAL）再确认。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：自注册 + 启动确认 |
 */

#ifndef BOOT_APP_H
#define BOOT_APP_H

#include <stdint.h>

/**
 * @brief 应用版本号（写进 meta，可通过 0x22 读出）
 * @note  与 `main.c` 文件头的 `@version` 保持一致。**改版本号时两处都要改** ——
 *        这里改漏了不会报错，只是升级后诊断仪读到的还是旧版本，很难发现。
 */
#define APP_VERSION_MAJOR       (2u)
#define APP_VERSION_MINOR       (7u)
#define APP_VERSION_PATCH       (0u)

/**
 * @brief 应用启动第一步：核对槽地址 + 必要时补写 meta
 *
 * @details 做三件事：
 *          1. **对账**：链接地址（`__VECTOR_TABLE`）必须等于 `APP_SLOT_INDEX`
 *             对应的槽基址。不等说明烧错了文件（把 AppB 的镜像刷进了 A 槽），
 *             此时**直接停住**而不是继续跑 —— 带着错地址运行会随机跳飞，
 *             现场表现为"偶发死机"，比启动失败难查得多。
 *          2. 算镜像 CRC32（`__VECTOR_TABLE` → `__CUSTOM_END`）；
 *          3. 本槽 meta 无效时调 `BootMeta_Register` 补写（首次 J-Link 烧写的场景）。
 *
 * @pre `Platform_Init()` 已调用（要打印诊断信息，且 `BootMeta_*` 依赖 flash 驱动）
 * @note 每次上电都会调，但**只有 meta 无效时才写 Flash**，正常运行零擦写。
 */
void BootApp_Init(void);

/**
 * @brief 应用启动成功确认：把 meta 置 CONFIRMED、尝试次数清零
 *
 * @details 只在新镜像第一次成功启动时写一次 Flash。之后每次上电都是
 *          "读 meta → 已是 CONFIRMED → 直接返回"，不产生擦写。
 *
 * @pre 通信栈已进入 RUN（CAN 已 STARTED），否则"跑起来"这个判断不可信
 */
void BootApp_Confirm(void);

/**
 * @brief 取本镜像所在的槽索引（0=A / 1=B）
 * @return 槽索引
 */
uint8_t BootApp_GetSlot(void);

#endif /* BOOT_APP_H */
