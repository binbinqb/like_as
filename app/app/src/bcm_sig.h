/**
 * @file    bcm_sig.h
 * @brief   车身信号绑定层（M23）：把 Com 的 raw 位值翻译成业务语义
 *
 * @details @section BCMSIG_WHY 为什么需要这一层
 *
 *          M22 打通之后，`Com_ReceiveSignal()` 能取到信号了，但它取到的是
 *          **原始位值**，不是业务能用的东西。三件事没人做：
 *
 *          1. **raw → 语义**。2 bit 的灯状态有 4 个取值，含义是
 *             `灭 / 亮 / 故障 / 无效`。业务层要是按 `raw != 0 → 亮` 写，
 *             就会把"回路故障"当成"正常点亮" —— 对车身控制器是安全性错误。
 *          2. **词表不一致要归一**。全矩阵 281 个 `VAL_` 表、89 种写法：
 *             同一个"亮"有 `Active` / `On` / `有效` / `lamp on 灯亮；` 多种说法；
 *             同一个"无效"有 `Invalid` / `not used` / `NotAvailable` 多种说法。
 *             业务层不能为了读一个灯去认这些拼写。
 *          3. **命令型信号不是状态**。`CentralLockSw` 是
 *             `off / lock / unlock / not used`，`MRightFrontWinSw` 是
 *             `off / up / down / not used` —— 这些是**动作**，不是开关。
 *             用开关枚举去套，`unlock` 会被读成"开"。
 *
 *          @section BCMSIG_LAYER 分层位置与依赖方向
 *
 *          @code
 *           业务功能（灯光/雨刮/车窗…145 项）
 *                ↓ 只 include 本文件
 *           绑定层（本模块）  ← 唯一知道 Com 信号号的地方
 *                ↓
 *           Com（`Com_ReceiveSignal` / `Com_SendSignal`）
 *          @endcode
 *
 *          业务层**看不到** `COM_SID_xxx`、报文名、字节偏移、位序、raw 值。
 *          绑定层**不做决策** —— "门开了要不要点亮迎宾灯"是业务层的事；
 *          "门开状态的 raw 2 表示什么"是这一层的事。两者的分界线在这里。
 *
 * @note    @section BCMSIG_SCOPE 本版（V1.0.0）范围
 *          - 已绑：`BCM_LCSF`（0x18FE4021）的 11 个灯状态 **发送**信号
 *          - 已绑：`CCVS.ParkingBrakeSwitch` 1 个 **接收**信号（做通路的对照）
 *          - 未绑：其余 360 个。模拟量（如 `TachographVehicleSpeed`，
 *            factor = 1/256）需要 `物理值 = raw × factor + offset`，
 *            本版不涉及 —— 等做对应业务时再加，避免空转
 *
 * @author  binbina
 * @version V1.0.0
 */

#ifndef BCM_SIG_H
#define BCM_SIG_H

#include "Std_Types.h"

/* ============================ [ 业务侧类型 ] ============================ */

/**
 * @brief 开关量状态（业务层唯一需要认识的"灯/开关"语义）
 *
 * @details @section BCMSIG_4STATE 为什么是四档而不是 bool
 *
 *          四档是**故意的**，每一档在业务上都有不同后果：
 *
 *          | 取值 | 含义 | 业务后果 |
 *          |------|------|----------|
 *          | `UNKNOWN` | 无效值 / 对方未实现 / 还没收到过 | 保持上次动作，**不报 DTC** |
 *          | `OFF` | 灭 / 未激活 | 关输出 |
 *          | `ON` | 亮 / 激活 | 开输出 |
 *          | `FAULT` | 回路故障 / 对方报错 | 关输出 + **可以报 DTC** |
 *
 *          如果把 `FAULT` 并进 `UNKNOWN`，业务层就无法回答"这是它没告诉我，
 *          还是它告诉我坏了" —— 前者不该报故障，后者必须报。反过来，把
 *          `raw != 0` 一律当 `ON`，则是把故障当正常，最坏情况是雾灯该亮时
 *          不亮而仪表显示正常。
 *
 * @note  枚举值**不能随意调整顺序**：`bcm_sig.c` 的默认映射表按下标索引，
 *        且发送侧的 `Bcm_SwStateType → raw` 也依赖这个顺序。
 */
typedef enum
{
	BCM_SW_STATE_UNKNOWN = 0, /**< 无效 / 未收到 / 对方未实现 */
	BCM_SW_STATE_OFF,         /**< 灭 / 未激活 */
	BCM_SW_STATE_ON,          /**< 亮 / 激活 */
	BCM_SW_STATE_FAULT        /**< 故障 / 对方报错 */
} Bcm_SwStateType;

/**
 * @brief 发送信号的业务编号（BCM 主动上报的状态）
 *
 * @note  这是**业务语义名**，与报文名无关。`BCM_SIG_LOW_BEAM` 具体落在
 *        哪条报文、哪个字节、哪几位，只有 `bcm_sig_cfg.c` 知道。
 *        名字里的 `LOW_BEAM` 对应矩阵里的 `BCM_LowBeamSts`。
 */
typedef enum
{
	BCM_SIG_LOW_BEAM = 0,  /**< 近光灯状态（BCM_LowBeamSts） */
	BCM_SIG_HIGH_BEAM,     /**< 远光灯状态（BCM_HighBeamSts） */
	BCM_SIG_FRONT_FOG,     /**< 前雾灯状态（BCM_FrontFogSts） */
	BCM_SIG_TURN_R,        /**< 右转向灯状态（BCM_TurnRLightSts） */
	BCM_SIG_TURN_L,        /**< 左转向灯状态（BCM_TurnLLightSts） */
	BCM_SIG_DRL,           /**< 日间行车灯状态（BCM_DRLSts） */
	BCM_SIG_POSITION,      /**< 位置灯状态（BCM_PositionLightSts） */
	BCM_SIG_REAR_FOG,      /**< 后雾灯状态（BCM_RearFogSts） */
	BCM_SIG_REVERSE,       /**< 倒车灯状态（BackUpLightSt） */
	BCM_SIG_BRAKE,         /**< 制动灯状态（BrakelightST） */
	BCM_SIG_INTERIOR,      /**< 室内灯状态（InteriorLampSt） */
	BCM_SIG_TX_NUM         /**< 发送信号总数（不是有效编号） */
} Bcm_SigIdType;

/**
 * @brief 接收信号的业务编号（BCM 从总线读到的输入）
 *
 * @note  与发送分开两个枚举，避免"把该发的东西当输入读"这种编号混用。
 */
typedef enum
{
	BCM_SIG_RX_PARK_BRAKE = 0, /**< 手刹开关（ParkingBrakeSwitch） */
	BCM_SIG_RX_NUM             /**< 接收信号总数（不是有效编号） */
} Bcm_SigRxIdType;

/* ============================ [ 接口 ] ============================ */

/**
 * @brief 绑定层初始化：把全部发送信号置为已知初值并写进 Com
 *
 * @details 上电后、`EcuM_StartupTwo()` 之后、Com 开始周期发送之前调用。
 *
 *          为什么不能省：Com 的报文缓冲在初始化时是 `InitialValue`
 *          （矩阵里大多写 0）。raw 0 在业务语义里是 `OFF`，但如果业务层
 *          在第一次 `BcmSig_MainFunction()` 之前就去读，会读到
 *          `BCM_SW_STATE_UNKNOWN`（shadow 被显式清零），两边不一致。
 *          这里主动写一遍，让"Com 缓冲"与"业务 shadow"从第 0 拍就对齐。
 *
 * @note  接收侧 shadow 全部置 `UNKNOWN`：上电时还没有任何依据说"灯亮还是灭"，
 *        宁可让业务层看到"不知道"。但它只保持到第一次
 *        `BcmSig_MainFunction()` —— 那一拍会读到报文缓冲的 `InitialValue`
 *        （raw 0 = `OFF`），此后就变成 `OFF` 了，原因见 @ref BCMSIG_NORXFLAG。
 */
void BcmSig_Init(void);

/**
 * @brief 绑定层周期任务：接收侧取语义、发送侧下 raw
 *
 * @details 由主循环按 `COM_MAIN_FUNCTION_PERIOD`（10 ms）节拍调用，
 *          **必须在 `Com_MainFunctionTx()` 之前** —— 否则本次写入的
 *          发送值要等到下一拍才进缓冲，总线上的值会整体滞后 10 ms。
 *
 *          实现上分两趟：
 *          - **上行**：逐个 `Com_ReceiveSignal()` → 查映射表 → 存 shadow
 *          - **下行**：逐个 shadow → 反查 raw → `Com_SendSignal()`
 *
 * @warning @section BCMSIG_NORXFLAG 本层**不判断"是否收到过"**
 *
 *          查过 `Com.c:137 comReceiveSignal()` 的实现：只要参数合法它就返回
 *          `E_OK`（唯一例外是启用了 UpdateBit 且该位未置）。也就是说
 *          **返回值不携带"这一帧到底来过没有"的信息**，读到的可能只是
 *          报文缓冲里的 `InitialValue`。
 *
 *          所以本层不提供 `RxIsValid()` 之类的接口 —— 那会给出一个看起来
 *          可信、实际永远为真的标志，比没有更危险。判断"对方掉线"请用
 *          Com 的 IPdu 级超时（`Com_IPduRxConfigType.Timeout` +
 *          `RxDataTimeoutAction`），那是唯一有真实数据支撑的机制。
 *
 *          业务层能依赖的只有：`BCM_SW_STATE_UNKNOWN` 表示**这个值不可用**
 *          （raw 落在无效值上），其余三档表示"对方明确这么说了"。
 */
void BcmSig_MainFunction(void);

/**
 * @brief 读一个接收信号的业务语义
 *
 * @param[in] id 接收信号业务编号
 *
 * @return 业务语义值；`id` 越界、或 raw 落在无效值（默认表下 raw 3）时
 *         返回 `BCM_SW_STATE_UNKNOWN`
 *
 * @note  @warning 上电后对方尚未发帧时，读到的是报文缓冲的 `InitialValue`
 *        （矩阵里通常写 0）。0 在语义上是 `OFF`，因此**"还没收到"会被读成
 *        `OFF`，不是 `UNKNOWN`**。这是矩阵初值的既定含义，绑定层无法区分 ——
 *        需要区分时用 IPdu 超时，见 @ref BCMSIG_NORXFLAG。
 */
Bcm_SwStateType BcmSig_RxGet(Bcm_SigRxIdType id);

/**
 * @brief 设置一个发送信号的业务语义（业务层调用）
 *
 * @param[in] id 发送信号业务编号
 * @param[in] st 期望状态
 *
 * @retval E_OK     已写入 shadow，下一拍 `BcmSig_MainFunction()` 会下发
 * @retval E_NOT_OK `id` 越界，或 `st` 不是合法枚举值
 *
 * @note  @section BCMSIG_TXWHY 为什么业务层不能直接调 `Com_SendSignal()`
 *
 *        两个硬理由：
 *        1. **业务层不该知道 raw**。业务说"近光灯故障"，绑定层负责把它
 *           写成 `raw = 2`；业务说"灭"，写 `raw = 0`。业务层写不出 `2`。
 *        2. **拦住越界值**。矩阵里 `BCM_FrontFogSts` 的枚举表写了
 *           `4 "Invalid"`，可这个信号只有 2 bit，最大到 3。若业务照着自己
 *           的理解写 4，会被静默截断成 0 = `Inactive` = **灯灭了**。
 *           绑定层只接受 4 个合法枚举，写不出 4，这个坑被堵死在入口。
 *
 *        非法 `st`（例如 `(Bcm_SwStateType)7`）直接返回 `E_NOT_OK` 且
 *        不改 shadow，便于上层发现调用错误。
 */
Std_ReturnType BcmSig_TxSet(Bcm_SigIdType id, Bcm_SwStateType st);

/**
 * @brief 读一个发送信号当前被要求的状态（调试/回读用）
 *
 * @param[in] id 发送信号业务编号
 *
 * @return 当前 shadow 中的业务语义；`id` 越界返回 `BCM_SW_STATE_UNKNOWN`
 */
Bcm_SwStateType BcmSig_TxGet(Bcm_SigIdType id);

#endif /* BCM_SIG_H */
