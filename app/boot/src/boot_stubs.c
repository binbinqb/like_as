/**
 * @file    boot_stubs.c
 * @brief   boot 里缺失的上层回调桩
 *
 * @details boot 链接的 BSW 模块有几处"向上调用"的回调，它们的实现
 *          本来在应用层（`app/app/src/`）。boot 没有应用层，但链接器
 *          不管这些 —— 符号必须存在。这里给最小实现。
 *
 *          | 符号 | 谁调 | 为什么 boot 需要 |
 *          |------|------|------------------|
 *          | `CanSM_ControllerBusOff` | `CanIf_ControllerBusOff()`（`#ifdef USE_CANSM`） | cfgs 循环给所有 app 都定义了 `USE_CANSM`，但 boot 不链 CanSM |
 *          | `Dcm_SessionChangeIndication` | `Dcm_Dsl.c` 的会话切换点 | 应用层用来做"进编程会话前落盘 NvM"之类的动作 |
 *
 * @note    **不要**在这里加业务逻辑。boot 的职责只有"选槽 / 校验 / 刷写"，
 *          任何看起来像"顺便做点什么"的代码都会让 boot 的语义变模糊。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-12 | binbina | 首版：CanSM bus-off 与 Dcm 会话切换桩 |
 */

#include "Std_Types.h"
#include "Dcm.h"
#include "platform_cvm0146.h"

/* ============================ [ 桩 ] ============================ */

/**
 * @brief DET 日志钩子（覆盖 `infras/system/Det/Det.c` 里的弱符号）
 *
 * @details 参数错误的唯一可见出口。没有它的话，`DET_VALIDATE` 只是
 *          `return E_NOT_OK` —— "模块没初始化"、"PDU 号越界"、"指针为空"
 *          在板上没有任何区别。
 *
 * @warning **boot 里这个函数比 app 里更重要**。app 有 `main.c` 的实现，
 *          而 boot 如果不提供，`Det.c` 那个空实现会让所有 DET 报错消失。
 *          排查"CAN 收不到帧"这类问题时，看不到 DET 就只能瞎猜 ——
 *          第一次跑 boot 就是栽在这上面：`CanIf_RxIndication` 的
 *          `DET_VALIDATE` 失败直接返回，串口一个字都没打。
 */
void Det_Log(uint16_t ModuleId, uint8_t ApiId, uint8_t ErrorId)
{
	Platform_Printf("[det] mod=%u api=0x%02x err=0x%02x\n",
	                (unsigned)ModuleId, (unsigned)ApiId, (unsigned)ErrorId);
}

/**
 * @brief CanIf 检测到 bus-off 时向上通知 CanSM
 * @param[in] ControllerId 控制器号
 *
 * @note boot 不做总线恢复 —— 刷写过程中 bus-off 的正确处置是
 *       **让诊断仪超时重试**，而不是自动重启控制器（那会让正在传输的
 *       0x36 数据块状态机错乱）。所以这里只打印一行，便于现场判断。
 */
void CanSM_ControllerBusOff(uint8_t ControllerId)
{
	Platform_Printf("[boot] CAN%u bus-off (flash will fail, check wiring)\n",
	                (unsigned)ControllerId);
}

/**
 * @brief 会话切换通知
 * @param[in] sesActive 切换前的会话
 * @param[in] sesNew    切换后的会话
 * @param[in] timeout   TRUE 表示因 S3 超时回到默认会话
 *
 * @note 应用层用这个钩子做"进编程会话前把 NvM 落盘"。
 *       boot 里没有需要落盘的东西 —— NvM 只在启动时读过一次，
 *       刷写过程本身不依赖 RAM 里的非易失数据。
 *       所以这里留空，只在超时回默认会话时打一行（说明诊断仪掉线了）。
 */
void Dcm_SessionChangeIndication(Dcm_SesCtrlType sesActive, Dcm_SesCtrlType sesNew,
                                 boolean timeout)
{
	if (timeout != FALSE) {
		Platform_Printf("[boot] session timeout: %u -> %u (tester gone?)\n",
		                (unsigned)sesActive, (unsigned)sesNew);
	}
}
