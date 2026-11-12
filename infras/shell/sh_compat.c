/**
 * @file    sh_compat.c
 * @brief   sh 平台适配的弱默认实现
 *
 * @details `err` 内建命令要查 Bcm_Frame HAL 的错误记录，本工程暂无该机制。
 *          这里给**弱符号**默认实现：命令仍可用（打印 errors=0 asserts=0），
 *          等以后真接了错误记录，应用层给一个强符号即可覆盖，shell 零改动。
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "sh_port.h"

__attribute__((weak)) uint32_t hal_error_count(void)
{
	return 0u;
}

__attribute__((weak)) uint32_t hal_assert_count(void)
{
	return 0u;
}

__attribute__((weak)) hal_status_t hal_error_get_last(hal_err_t *out)
{
	(void)out;
	return HAL_ERR_NOT_SUPPORTED;
}
