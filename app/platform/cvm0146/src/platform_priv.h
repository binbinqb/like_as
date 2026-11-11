/**
 * @file    platform_priv.h
 * @brief   CVM0146 平台层内部共享声明（**不对外**，只有 src/ 下的文件包含）
 *
 * @details 平台层的几个 AC 实现（PortAc / DioAc / CanAc）都要同一个厂商
 *          `McuType`：里面持有各外设驱动的句柄（ptd/pte/flexCanDrv0...）。
 *          这个对象由 `Platform_Init()` 一次性 `Mcu_Init()` 填好，之后只读，
 *          所以做成全局而不是每个文件各建一份——
 *          **各建一份的后果是：引脚配好了，但 CAN 用的是另一个未初始化的驱动对象。**
 *
 *          `McuType` 来自厂商 `mcu.h`，因此本头文件会引入 SDK 类型。
 *          这就是把它放在 `src/` 而不是 `include/` 的原因：
 *          `include/platform_cvm0146.h` 必须保持"零 SDK"，应用层才能只依赖平台接口。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：共享 McuType + 端口基址映射 |
 */

#ifndef PLATFORM_PRIV_H
#define PLATFORM_PRIV_H

#include "mcu.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================ [ 全局 ] ============================ */

/**
 * @brief 厂商驱动对象集合（`Platform_Init()` 里 `Mcu_Init()` 填充）
 * @note  只读使用；不要在别处重新 `Mcu_Init()`，那会把已配好的外设全部复位。
 */
extern McuType g_mcu;

/* ============================ [ 工具 ] ============================ */

/**
 * @brief 把平台的端口号（0=A..4=E）映射成厂商的端口对象
 *
 * @param[in] port 端口号，取值 `PORT_PORT_A`..`PORT_PORT_E`（见 Port_Cfg.h）
 * @return 端口对象指针；端口号非法时返回 NULL（调用方必须判空）
 *
 * @note 返回 NULL 而不是断言：配置表写错端口号时，应该"这一根脚不配"，
 *       而不是让整块板子停在断言里——后者在现场排查成本高得多。
 */
PinsDrvType *Platform_GetPort(uint8_t port);

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_PRIV_H */
