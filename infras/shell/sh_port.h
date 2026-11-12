/**
 * @file    sh_port.h
 * @brief   sh 命令行解释器 —— 平台类型适配（替代 Bcm_Frame 的 hal_comm.h）
 *
 * @details 本工程没有 Bcm_Frame 的 HAL 状态码体系（`hal_comm.h`），
 *          sh 只用到其中 3 个状态码 + 1 个错误记录结构。
 *          为保持 shell 实现文件**零改动**，在此提供最小同名类型。
 *
 * @note    新增用量前先确认 `grep -ho "HAL_..." infra/shell/` 的清单，
 *          不要把 Bcm_Frame 整套 HAL 搬进来。
 *
 * @author  binbina
 * @version V1.0.0
 */

#ifndef SH_PORT_H
#define SH_PORT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief 状态码（只保留 shell 实际用到的三个） */
typedef enum {
	HAL_OK = 0,                    /**< 成功 */
	HAL_ERR_PARAM = -1,            /**< 参数非法 */
	HAL_ERR_NOT_SUPPORTED = -2,    /**< 不支持（未绑定的可选能力） */
} hal_status_t;

/** @brief 错误上下文（字段名与 sh_cmd.c 的打印一一对应） */
typedef struct {
	hal_status_t code;             /**< 错误码 */
	uint16_t     instance;         /**< 实例号 */
	uint16_t     extra;            /**< 附加信息 */
} hal_err_t;

/** @brief 累计错误计数（`err` 内建命令打印用；无实现时恒 0） */
uint32_t hal_error_count(void);

/** @brief 累计断言计数（同上） */
uint32_t hal_assert_count(void);

/** @brief 最近一条错误；未实现时返回 HAL_ERR_NOT_SUPPORTED */
hal_status_t hal_error_get_last(hal_err_t *out);

#ifdef __cplusplus
}
#endif

#endif /* SH_PORT_H */
