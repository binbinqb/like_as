/**
 * @file    iohwab_mux.c
 * @brief   IoHwAb 的 MUX 能力胶水：把 MuxManager 的样本接到逻辑通道
 *
 * @details @section IOHWABMUX_WHY 为什么这层只有十几行
 *
 *          MuxManager 负责"什么时候采样、ABC 怎么排"，IoHwAb 负责"逻辑值、
 *          消抖、滤波、极性"。两者之间只差一件小事：**通道号怎么解释**。
 *
 *          这里把 `IoHwAb` 的 `channel`（`(dev << 8) | y`）拆成设备与 Y 通道，
 *          去查 Mux 的已发布样本，并把 `seq` 原样递上去 —— IoHwAb Core 用它
 *          判断"这一拍有没有新数据"，扫描慢或停摆时自然转 `STALE`。
 *
 *          @section IOHWABMUX_ELEC 只传电气量
 *
 *          `Mux_GetDin()` 返回的是 **COM 引脚电平**（TRUE = 高），不是逻辑值。
 *          极性由 IoHwAb Core 按表项 `activeLevel` 转换 —— 本文件不取反。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.1.0 | 2026-11-18 | binbina | 首版：MUX 通道拆包 + 样本序号透传 |
 */

#include "iohwab.h"
#include "mux.h"

/**
 * @brief 读 MUX 数字通道（电气电平）
 * @param[in]  channel `(dev << 8) | y`
 * @param[out] level   电气电平
 * @param[out] seq     样本序号（Mux 发布时 +1）
 * @return E_OK / E_NOT_OK（通道未启用或尚未采到）
 */
static Std_ReturnType iohwabmux_DinRead(uint16 channel, boolean *level,
                                        uint16 *seq)
{
	uint8 dev = (uint8)(channel >> 8);
	uint8 y = (uint8)(channel & 0xFFu);

	return Mux_GetDin(dev, y, level, seq);
}

/**
 * @brief 读 MUX 模拟通道（原始 ADC 值）
 * @param[in]  channel `(dev << 8) | y`
 * @param[out] raw     原始值
 * @param[out] seq     样本序号
 * @return E_OK / E_NOT_OK
 */
static Std_ReturnType iohwabmux_AinRead(uint16 channel, uint16 *raw,
                                        uint16 *seq)
{
	uint8 dev = (uint8)(channel >> 8);
	uint8 y = (uint8)(channel & 0xFFu);

	return Mux_GetAin(dev, y, raw, seq);
}

const IoHwAb_DinOpsType IoHwAb_MuxDinOps = { iohwabmux_DinRead };
const IoHwAb_AinOpsType IoHwAb_MuxAinOps = { iohwabmux_AinRead };
