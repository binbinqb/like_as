/**
 * @file    led_biz.h
 * @brief   第一条完整业务闭环（10.6）：LED 控制 → 闪烁状态机 → 状态上报
 *
 * @details 这条链路刻意做成"最小但完整"的纵向切片，用来证明框架可用：
 *
 *          @code
 *           CAN1 0x18FEF121 (100 ms)
 *             → CanIf → PduR → Com → BcmSig → RTE
 *             → LedBiz 状态机（本模块）→ RTE → IoHwAb → 板载 LED
 *             → RTE → BcmSig → Com → 0x200 (CAN0, 100 ms)
 *          @endcode
 *
 *          @section LEDBIZ_BEHAVIOR 行为契约（第一版，刻意简单）
 *
 *          | 输入（RTE_PORT_LED_CTRL） | 动作 |
 *          |---|---|
 *          | `ON`（raw 1） | 启动闪烁：亮 500 ms → 灭 500 ms，循环 |
 *          | `OFF`（raw 0） | 停止并熄灭，模式=已停止 |
 *          | `ERROR/INVALID`（raw 2/3） | 不改输出，置"命令无效"故障位 |
 *          | 500 ms 无**有效**命令 | 停止并熄灭，置"通信超时"故障位 |
 *          | 上电至今没有有效命令 | 熄灭，模式=尚未收到命令（**不算故障**） |
 *
 *          @note 超时按"有效命令"计时，不是按"帧到达"计时：对方持续发
 *                raw 2/3（无效值）时帧是新鲜的，但按契约这不叫有效控制，
 *                500 ms 后同样停止。这个计时器在本模块内用 10 ms 拍计数，
 *                不依赖 `Platform_NowMs()` —— Host 用例可以逐拍精确驱动。
 *
 *          @section LEDBIZ_REPORT 上报语义（CAN0 0x200，100 ms）
 *
 *          | 信号 | 含义 |
 *          |---|---|
 *          | `LED_RUN_MODE` | raw 0=已停止 / 1=闪烁中 / 3=尚未收到命令 |
 *          | `LED_OUT` | **驱动成功提交**的状态，不是电气反馈（无采样回路） |
 *          | `LED_PHASE` | 当前相位：0=灭相 / 1=亮相（仅闪烁时有意义） |
 *          | `LED_FAULT_TIMEOUT` | 500 ms 无有效控制 |
 *          | `LED_FAULT_CMD` | 最近收到的是无效命令值 |
 *
 *          @warning `LED_OUT` 只能表示"我们成功把值交给了驱动"。板上没有
 *          灯电流/电压反馈，把它当"灯真的亮了"是错误解读 —— 将来加
 *          诊断回路要新增信号，不能改这个信号的含义。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-20 | binbina | 首版：启动/停止/闪烁/超时/无效命令 |
 */

#ifndef LED_BIZ_H
#define LED_BIZ_H

/**
 * @brief 初始化：状态清零并把输出置为安全态（熄灭 / 尚未收到命令）
 *
 * @note 必须在 `BcmSig_Init()` 之后调用：本函数通过 `Rte_Write()` 写
 *       端口影子，而影子由绑定层持有。放在之后可以覆盖绑定层的"全 OFF"
 *       初值，让上电第一拍上报的就是"尚未收到命令"而不是"已停止"。
 */
void LedBiz_Init(void);

/**
 * @brief 周期任务：10 ms 一拍，由 RTE 调度表驱动
 *
 * @note 非阻塞：闪烁用拍计数实现，不做 `DelayMs` 等待。
 * @note 读端口用 `Rte_Read()`、写端口用 `Rte_Write()`；本模块**不** include
 *       任何 Com/BcmSig/IoHwAb 头，换项目只改 `Board.json` 的端口绑定。
 */
void LedBiz_MainFunction(void);

#endif /* LED_BIZ_H */
