/**
 * @file    rte_cfg.c
 * @brief   RTE 端口表：业务语义名 → 绑定层信号号
 *
 * @details 表长必须等于 `RTE_PORT_NUM`。`Rte_Read` / `Rte_Write` 用
 *          `sizeof` 推出来的实际长度做越界判断，所以这张表少写一行不会
 *          静默读越界，而是让编号越界的端口统一返回错误。
 *
 * @note    V0.2.0 起，端口名与表内容都来自 `Board.json` 的 `rte.ports`，
 *          由 `tools/generator/BcmRte.py` 生成到 `Rte_Ports.h`。
 *          **不要**在这里手工改表 —— 改了会在下次构建被覆盖。
 *
 * @author  binbina
 * @version V0.2.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V0.1.0 | 2026-11-17 | binbina | 首版：驻车制动输入、制动灯输出 |
 * | V0.2.0 | 2026-11-18 | binbina | 表改为展开生成的 RTE_PORT_CFG_LIST |
 */

#include "rte.h"
#include "rte_cfg.h"
#include "Rte_Ports.h"   /* RTE_PORT_CFG_LIST：端口表初始化列表（Board.json 生成） */

#include "bcm_sig.h"     /* Bcm_SigRxIdType / Bcm_SigIdType */
#include "IoHwAb_Cfg.h"  /* IOHWAB_* 通道号 */

const Rte_PortCfgType Rte_PortCfg[RTE_PORT_NUM] =
	RTE_PORT_CFG_LIST;

/* 编译期长度检查：表必须恰好 RTE_PORT_NUM 行。
 * 少写一行不会报错（C 会把缺的补 0），但会让"写了一个不存在的端口"
 * 静默成功；多写一行则是编译错误。用负数组长度把"少写"也变成编译错误。 */
typedef char Rte_PortCfg_SizeCheck[
	((sizeof(Rte_PortCfg) / sizeof(Rte_PortCfg[0])) == (size_t)RTE_PORT_NUM) ? 1 : -1];
