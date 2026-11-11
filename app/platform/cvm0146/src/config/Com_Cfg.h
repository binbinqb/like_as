/**
 * @file    Com_Cfg.h
 * @brief   Com 的编译期开关与时基换算
 *
 * @details @section COMCFG_PERIOD 时间和 CanNm 一样，是"主函数拍数"
 *
 *          `Com_MainFunctionRx/Tx` 里的定时器都是 `uint16_t` 递减计数器
 *          （`Com.c:784` / `:846`），**每调一次减一**。所以配置表里
 *          `CycleTime` / `Timeout` 的单位不是毫秒，而是"主函数调用次数"。
 *
 *          `COM_CONVERT_MS_TO_MAIN_CYCLES()` 做这层换算，
 *          与 as-master 的代码生成器（`tools/generator/Com.py:277`）逐字一致。
 *
 *          @warning 误填毫秒值（比如 `CycleTime` 填 100 而不是 10）
 *                   会让报文周期变成 **1 秒**，慢 10 倍，且不报任何错。
 *
 *          @section COMCFG_MACROS 三个必须定义的宏
 *
 *          | 宏 | 不定义的后果 |
 *          |----|--------------|
 *          | `COM_USE_CAN` | `Com_MainFunctionTx()` / `Com_TriggerIPDUSend()` 整个函数体被编译掉（`Com.c:828`）。Com 变成**只收不发**：`Com_SendSignal` 照常改缓冲、返回 E_OK，但总线上永远没有帧 |
 *          | `COM_USE_SIGNAL_CONFIG` | 信号级的超时/替换/通知全部消失。少了 `rxConfig`，BCM 最需要的"信号丢失检测"就没了 |
 *          | `COM_MAIN_FUNCTION_PERIOD` | 换算宏失效，所有周期按"拍"直接当毫秒算 |
 *
 *          `COM_USE_CAN` 这一条最阴：不定义时编译**零告警**，
 *          运行期也**没有任何错误返回**，只是不发帧。
 *
 *          @section COMCFG_MAIN_FAST 为什么不启用 COM_USE_MAIN_FAST
 *
 *          AS 的生成器默认打开它，效果是给每个 TX 上下文加 `bTxRetry`，
 *          并把发送逻辑拆成 `Com_MainFunctionTx_Fast()`，需要以更快的周期
 *          单独调用。本工程：
 *
 *          - 只有 1 个 TX 报文、100 ms 周期，10 ms 节拍足够；
 *          - 多一个主函数就多一个"没被 tick 就永远不发"的位置
 *            （CanTp 上已经吃过一次这个亏）。
 *
 *          将来报文多了、需要 5 ms 甚至 1 ms 的发送节拍时再打开，
 *          并同时把 `Com_MainFunction_Fast()` 挂到快任务上。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：单 TX + 单 RX 测试报文，10 ms 主函数 |
 */

#ifndef COM_CFG_H
#define COM_CFG_H

/* ============================ [ 时基 ] ============================ */

/**
 * @brief `Com_MainFunction()` 的调用间隔（ms）
 * @warning 必须与 `main.c` 的 `BSW_PERIOD_MS` 一致。改一处不改另一处，
 *          所有 Com 周期按比例偏，且不报错。
 */
#ifndef COM_MAIN_FUNCTION_PERIOD
#define COM_MAIN_FUNCTION_PERIOD    (10u)
#endif

/**
 * @brief 毫秒 → 主函数拍数
 * @param[in] x 毫秒
 * @note  向上取整，避免小值被算成 0 拍（0 拍会让定时器永远不减）。
 */
#define COM_CONVERT_MS_TO_MAIN_CYCLES(x)                                                           \
	(((x) + COM_MAIN_FUNCTION_PERIOD - 1u) / COM_MAIN_FUNCTION_PERIOD)

/* ============================ [ 功能开关 ] ============================ */

/**
 * @brief 总线上有 CAN 报文（不定义则 `Com_MainFunctionTx` 整段被编译掉）
 * @warning 见文件头 `@section COMCFG_MACROS`。这是本文件里最重要的一行。
 */
#define COM_USE_CAN

/**
 * @brief 启用信号级配置（超时 / 替换值 / 通知）
 * @note  没有它就没有 `rxConfig`，也就没有"信号丢失 → 填替换值"这条能力。
 */
#define COM_USE_SIGNAL_CONFIG

/* 刻意不启用：
 *   COM_USE_SIGNAL_UPDATE_BIT   当前没有信号需要"更新位"，加了只是给每个信号
 *                               多一个字段并让发送后多一次清位循环
 *   COM_USE_RX_TIMEOUT          IPdu 级超时回调，本工程用信号级超时已足够
 *   COM_USE_RX_NOTIFICATION     IPdu 收到就回调，会与 main loop 打印抢串口
 *   COM_USE_TX_NOTIFICATION     同上，TX 确认回调对当前验证没有信息增量
 *   COM_USE_TX_IPDU_CALLOUT     发送前钩子，用不上
 *   COM_USE_MAIN_FAST           理由见文件头
 *   COM_USE_PB_CONFIG           编译后配置，本工程是编译前固定配置
 */

/* ============================ [ 信号编号 ] ============================ */

/**
 * @name 信号 ID（`Com_SendSignal` / `Com_ReceiveSignal` 的第一个参数）
 * @note  必须与 `Com_Cfg.c` 里 `Com_SignalConfigs[]` 的**数组下标**一致。
 *        Com.c 直接拿它当下标（`Com.c:452`），顺序错不会报错，
 *        只会读到邻居信号的配置 —— 现象是"改 A 影响 B"。
 *
 *        放在头文件里是为了让**应用只依赖配置头**，不依赖 `Com_Priv.h`。
 *        应用看得见"有哪些信号"，看不见"信号存在哪个字节"。
 */
/** @{ */
#define COM_SIG_TX_COUNTER      (0u)    /**< TX：滚动计数（8 位，字节 0） */
#define COM_SIG_TX_FLAG         (1u)    /**< TX：状态位（1 位，byte1 的 bit1） */
#define COM_SIG_TX_LEVEL        (2u)    /**< TX：模拟量（12 位，byte2 起跨字节） */
#define COM_SIG_RX_COUNTER      (3u)    /**< RX：对端计数（8 位，字节 0） */
#define COM_SIG_RX_TEMP         (4u)    /**< RX：温度（16 位，Motorola 大端） */
/** @} */

/* ============================ [ 报文与分组 ] ============================ */

/**
 * @name Com PDU ID
 * @note  内部报文索引，与 `Com_IPduConfigs[]` 下标一致。
 *        应用**不需要**它（应用只碰信号），列出来是为了让 PduR 路由表的
 *        `PduHandleId` 有个可读的来源。
 */
/** @{ */
#define COM_PDU_TX_TEST         (0u)
#define COM_PDU_RX_TEST         (1u)
/** @} */

/**
 * @brief IPdu 分组编号
 * @note  两个报文都挂在这一组。`Com_IpduGroupStop()` 能一次停掉收发，
 *        这是 BCM 的实用能力：诊断会话切到编程会话时停常规报文。
 */
#define COM_GROUP_TEST          (0u)

/** @brief 分组总数 */
#define COM_NUM_GROUPS          (1u)

#endif /* COM_CFG_H */
