/**
 * @file    rte_cfg.c
 * @brief   RTE 端口表：业务语义名 → 绑定层信号号
 *
 * @details 表长必须等于 `RTE_PORT_NUM`。`Rte_Read` / `Rte_Write` 用
 *          `sizeof` 推出来的实际长度做越界判断，所以这张表少写一行不会
 *          静默读越界，而是让编号越界的端口统一返回错误。
 *
 * @note    新增端口的顺序：先在 `rte.h` 的 `Rte_PortIdType` 里加编号
 *          （**必须加在 `RTE_PORT_NUM` 之前**），再在这里加一行。两处
 *          顺序不一致会让端口读到别的信号 —— 这是本层唯一容易犯的错。
 *
 * @author  binbina
 * @version V0.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V0.1.0 | 2026-11-17 | binbina | 首版：驻车制动输入、制动灯输出 |
 */

#include "rte.h"
#include "rte_cfg.h"

#include "bcm_sig.h"   /* Bcm_SigRxIdType / Bcm_SigIdType：端口指向的信号 */

const Rte_PortCfgType Rte_PortCfg[RTE_PORT_NUM] =
{
	/* 方向        绑定层信号号 */
	{ RTE_DIR_IN,  (uint8_t)BCM_SIG_RX_PARK_BRAKE }, /**< RTE_PORT_PARK_BRAKE */
	{ RTE_DIR_OUT, (uint8_t)BCM_SIG_BRAKE }          /**< RTE_PORT_BRAKE_LAMP */
};

/* 编译期长度检查：表必须恰好 RTE_PORT_NUM 行。
 * 少写一行不会报错（C 会把缺的补 0），但会让"写了一个不存在的端口"
 * 静默成功；多写一行则是编译错误。用负数组长度把"少写"也变成编译错误。 */
typedef char Rte_PortCfg_SizeCheck[
	((sizeof(Rte_PortCfg) / sizeof(Rte_PortCfg[0])) == (size_t)RTE_PORT_NUM) ? 1 : -1];
