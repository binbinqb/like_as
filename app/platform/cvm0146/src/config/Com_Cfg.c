/**
 * @file    Com_Cfg.c
 * @brief   Com 的信号 / 报文配置（1 个 TX + 1 个 RX 测试报文）
 *
 * @details @section COMCFG_C_SCOPE 这一版只验证机制，不接业务信号
 *
 *          灯光 / 门锁 / 雨刮这些真实信号的位布局来自整车通信矩阵，
 *          现在还没有。但 **Com 层的机制必须先验证正确** —— 它有三件
 *          很容易出错、且出错后极难定位的事：
 *
 *          1. **位级打包**：信号不是按字节对齐的。1 位的状态位可能落在
 *             某个字节的 bit1，12 位的模拟量会跨两个字节且不占满。
 *             打包错一个 bit，整车看到的就是一个永远不动作的灯。
 *          2. **大小端**：CAN 矩阵里同一个报文里可以混用 Intel/Motorola。
 *             搞反了不是"值不对"，而是"值差很远但看起来像真的"。
 *          3. **信号超时**：对端不发了，Com 要在规定时间内把信号置成
 *             替换值或初值。没有它，BCM 会把"上一个世纪的方向盘角度"
 *             当成当前值继续用。
 *
 *          所以这里刻意挑了**三个边界信号**：
 *
 *          | 信号 | 起始位 | 宽度 | 验证什么 |
 *          |------|--------|------|----------|
 *          | `TX_COUNTER` | 0 | 8 | 字节对齐的基本打包 |
 *          | `TX_FLAG` | **9** | **1** | **非字节对齐的单 bit**（落在 byte1 的 bit1） |
 *          | `TX_LEVEL` | 16 | **12** | **跨字节但不占满**（byte2 全部 + byte3 低 4 位） |
 *
 *          RX 侧用 `RX_TEMP` 的 **Motorola（大端）** 16 位来验第二条。
 *
 *          接真实信号时，**只要改这张表**：加 `Com_SignalConfigType` 条目、
 *          把信号指针指向对应 PDU 缓冲的字节偏移、填 BitPosition/BitSize。
 *          `Com.c` 一行都不用动。
 *
 *          @section COMCFG_C_LAYOUT 报文布局（可直接对着 Kvaser 看）
 *
 *          @code
 *          TX 0x200（本节点 → 总线，100 ms）
 *            byte0      : TX_COUNTER  滚动 0..255
 *            byte1 bit1 : TX_FLAG     固定 1（所以 byte1 = 0x02）
 *            byte2..3   : TX_LEVEL    固定 0xABC（byte2=0xBC, byte3=0x0A）
 *
 *          RX 0x201（总线 → 本节点）
 *            byte0      : RX_COUNTER
 *            byte2..3   : RX_TEMP     Motorola，高字节在前（01 23 → 291）
 *          @endcode
 *
 *          @note TX 0x200 / RX 0x201 **不同 ID**。曾经写成同一个 ID 图方便，
 *                结果接收测试没法做：板子每 100 ms 也在发 0x200，Kvaser 一注入
 *                就撞车（同 ID 同优先级），抓到的帧内容互相污染、错误计数上涨。
 *                真实总线里一个 ID 只有一个发送者，拆开才符合实际。
 *
 * @warning **信号指针直接指向 PDU 发送缓冲，没有 shadow buffer。**
 *          `Com_SendSignal()` 是就地改发送缓冲（`Com.c:174` → `comSendSignal`），
 *          而 `Com_MainFunctionTx()` 同时可能正在把这个缓冲交给 PduR。
 *          严格说这有撕裂风险（AUTOSAR 要求两份缓冲 + 切换）。
 *
 *          本工程不构成问题：8 字节缓冲、10 ms 发送节拍、应用只在主循环里
 *          改单字节信号，单字节写在 Cortex-M4 上是原子的。
 *          **但将来加 16/32 位信号时要注意** —— 那才会真的撕裂。
 *          真要修就在应用侧做双缓冲，或给 Com 加 shadow buffer。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：2 报文 5 信号，覆盖位打包/大小端/信号超时 |
 */

#include "Com.h"
#include "Com_Cfg.h"
#include "Com_Priv.h"

#include "PduR_Cfg.h"

/* 信号 / 报文 / 分组的编号统一放在 `Com_Cfg.h`，应用层也要用，
 * 定义在这两个文件里会导致两份不同的值而不报错。 */

/* ============================ [ PDU 数据缓冲 ] ============================ */

/**
 * @brief TX 报文的发送缓冲
 * @note  这不是"应用变量"，而是**报文镜像**：信号配置里的 `ptr` 指向它的某个字节，
 *        `Com_SendSignal()` 直接改这里，`Com_MainFunctionTx()` 直接把它交给 PduR。
 *        所以必须非 const。
 */
static uint8_t Com_TxPduData_Test[8];

/**
 * @brief RX 报文的接收缓冲
 * @note  `Com_RxIndication()` 把收到的 8 字节整段 memcpy 到这里，
 *        信号再从里面按位取。同样必须非 const。
 */
static uint8_t Com_RxPduData_Test[8];

/* ============================ [ 初值与替换值 ] ============================ */

/*
 * 这些常量只在 `Com_IpduGroupStart(0, TRUE)` 时被写进缓冲一次。
 * 类型必须与信号的 `type` 匹配 —— `comGetSignalValue()` 是按
 * `signal->type` 决定读几个字节的（`Com.c:78`），
 * 用 `uint16_t` 常量喂 `COM_UINT8` 信号会读到错误的那一半。
 */

static const uint8_t  Com_InitValue_TxCounter = 0x00u;
static const uint8_t  Com_InitValue_TxFlag    = 0x01u;   /**< 1 位信号，值 1 */
static const uint16_t Com_InitValue_TxLevel   = 0x0ABCu; /**< 12 位信号，值 0xABC */
static const uint8_t  Com_InitValue_RxCounter = 0x00u;
static const uint16_t Com_InitValue_RxTemp    = 0x0000u;

/**
 * @brief `RX_COUNTER` 信号超时后的替换值
 * @note  取 0xEE 而不是 0：0 是合法计数值，看不出来是"超时被替换"还是
 *        "对端真的发了 0"。0xEE 在计数滚动里几乎不可能恰好出现。
 */
static const uint8_t  Com_SubstValue_RxCounter = 0xEEu;

/* ============================ [ 运行期上下文 ] ============================ */

/*
 * 定时器和状态都存在这里。必须是 RAM 且非 const —— Com.c 会写它。
 * 静态零初始化即可：`Com_IpduGroupStart()` 会按配置重新装载所有定时器。
 */

static Com_SignalRxContextType Com_RxContext_RxCounter;
static Com_SignalRxContextType Com_RxContext_RxTemp;

static Com_IPduRxContextType   Com_RxContext_Test;
static Com_IPduTxContextType   Com_TxContext_Test;

/* ============================ [ 信号配置 ] ============================ */

/**
 * @brief RX 信号 `RX_COUNTER` 的超时配置
 *
 * @details 这里体现的是 **信号级** 超时（AUTOSAR 的
 *          `ComSignalDataTimeoutAction`），和 IPdu 级超时是两回事：
 *          - IPdu 级：整帧不来 → 认为总线/对端挂了；
 *          - 信号级：帧可能还在来，但这个信号的位置一直是旧的
 *            （对端把该信号置为"无效"时常见）。
 *
 *          `RxDataTimeoutAction = COM_ACTION_SUBSTITUTE` 表示超时后
 *          把替换值写进信号位置，`Com_ReceiveSignal()` 读到的就是这个值。
 *          应用**不需要**自己维护"上次收到的时间"。
 */
static const Com_SignalRxConfigType Com_SignalRxConfig_RxCounter = {
	.context                  = &Com_RxContext_RxCounter,
	.TimeoutSubstitutionValue = &Com_SubstValue_RxCounter,
	.FirstTimeout             = COM_CONVERT_MS_TO_MAIN_CYCLES(0u),     /* 0 = 用 Timeout */
	.Timeout                  = COM_CONVERT_MS_TO_MAIN_CYCLES(1000u),  /* 1 s 没更新 → 替换 */
	.DataInvalidAction        = COM_ACTION_NONE,
	.RxDataTimeoutAction      = COM_ACTION_SUBSTITUTE,
};

/**
 * @brief RX 信号 `RX_TEMP` 的超时配置
 * @note  用 `COM_ACTION_REPLACE`：超时后回初值 0。温度这种量"0 度"是可接受的
 *        安全默认值，而计数类的替换成 0 会与真实值混淆，所以才用 0xEE。
 *        这个区别说明：**超时动作选什么是由信号语义决定的，不是技术偏好。**
 */
static const Com_SignalRxConfigType Com_SignalRxConfig_RxTemp = {
	.context                  = &Com_RxContext_RxTemp,
	.TimeoutSubstitutionValue = NULL,
	.FirstTimeout             = COM_CONVERT_MS_TO_MAIN_CYCLES(0u),
	.Timeout                  = COM_CONVERT_MS_TO_MAIN_CYCLES(1000u),
	.DataInvalidAction        = COM_ACTION_NONE,
	.RxDataTimeoutAction      = COM_ACTION_REPLACE,
};

/**
 * @brief 全部信号（下标即 `Com_SignalIdType`）
 *
 * @warning **必须用指定初始化器。** `Com_SignalConfigType` 的字段会随
 *          `COM_USE_SIGNAL_CONFIG` / `COM_USE_SIGNAL_UPDATE_BIT` / `USE_SHELL`
 *          增减，位置初始化在开关翻转后会整体错位，而且编译器不报错 ——
 *          `BitPosition` 和 `BitSize` 都是 `uint16_t`，串位后能编能跑，
 *          只是所有信号都取错位。
 */
static const Com_SignalConfigType Com_SignalConfigs[] = {
	/* ---- TX ---- */
	[COM_SIG_TX_COUNTER] = {
		.ptr          = &Com_TxPduData_Test[0],
		.initPtr      = &Com_InitValue_TxCounter,
		.rxConfig     = NULL,
		.txConfig     = NULL,
		.HandleId     = COM_SIG_TX_COUNTER,
		.PduId        = COM_PDU_TX_TEST,
		.BitPosition  = 0u,          /* 字节内 bit 偏移 */
		.BitSize      = 8u,
		.type         = COM_UINT8,
		.Endianness   = COM_LITTLE_ENDIAN,
		.isGroupSignal = FALSE,
	},
	[COM_SIG_TX_FLAG] = {
		.ptr          = &Com_TxPduData_Test[1],
		.initPtr      = &Com_InitValue_TxFlag,
		.rxConfig     = NULL,
		.txConfig     = NULL,
		.HandleId     = COM_SIG_TX_FLAG,
		.PduId        = COM_PDU_TX_TEST,
		/**
		 * @note **1** 而不是 0：起始位是 9，落在 byte1 的 bit1。
		 *       `ptr` 指向 byte1，`BitPosition` 是"在该字节内的偏移"。
		 *       这是整个配置里最容易写错的一处 —— 写成 9 会越过字节，
		 *       写到 byte2 上去，而 `BitSize=1` 又不会触发任何越界检查。
		 */
		.BitPosition  = 1u,
		.BitSize      = 1u,
		.type         = COM_UINT8,
		.Endianness   = COM_LITTLE_ENDIAN,
		.isGroupSignal = FALSE,
	},
	[COM_SIG_TX_LEVEL] = {
		.ptr          = &Com_TxPduData_Test[2],
		.initPtr      = &Com_InitValue_TxLevel,
		.rxConfig     = NULL,
		.txConfig     = NULL,
		.HandleId     = COM_SIG_TX_LEVEL,
		.PduId        = COM_PDU_TX_TEST,
		.BitPosition  = 0u,
		/**
		 * @note 12 位 = 1.5 字节，跨 byte2/byte3 但不占满 byte3。
		 *       byte3 的高 4 位保持初值 0 —— 验收脚本会检查这一点，
		 *       因为"把 12 位写成 16 位"是这类配置最常见的错误，
		 *       症状是对端读到的值偶尔正确、偶尔多出 0x?000。
		 */
		.BitSize      = 12u,
		.type         = COM_UINT16,
		.Endianness   = COM_LITTLE_ENDIAN,
		.isGroupSignal = FALSE,
	},

	/* ---- RX ---- */
	[COM_SIG_RX_COUNTER] = {
		.ptr          = &Com_RxPduData_Test[0],
		.initPtr      = &Com_InitValue_RxCounter,
		.rxConfig     = &Com_SignalRxConfig_RxCounter,
		.txConfig     = NULL,
		.HandleId     = COM_SIG_RX_COUNTER,
		.PduId        = COM_PDU_RX_TEST,
		.BitPosition  = 0u,
		.BitSize      = 8u,
		.type         = COM_UINT8,
		.Endianness   = COM_LITTLE_ENDIAN,
		.isGroupSignal = FALSE,
	},
	[COM_SIG_RX_TEMP] = {
		.ptr          = &Com_RxPduData_Test[2],
		.initPtr      = &Com_InitValue_RxTemp,
		.rxConfig     = &Com_SignalRxConfig_RxTemp,
		.txConfig     = NULL,
		.HandleId     = COM_SIG_RX_TEMP,
		.PduId        = COM_PDU_RX_TEST,
		/**
		 * @warning **大端信号的 `BitPosition` 是 7，不是 0。**
		 *
		 *          这是本工程遇到的第二个"配错不报错"的陷阱，实测才发现的：
		 *          填 0 时，总线上 `01 23`（0x0123）读出来是 **0x9180** ——
		 *          正好左移 7 位（`0x0123 << 7`）。填 0xFFFF 读出来是 0xFF80，
		 *          同一个位移规律。
		 *
		 *          原因在 `Std_BitGetBigEndian()`（`std_bit.c:33`）：
		 *          @code
		 *          uint16_t lsbIndex = ((bitPos ^ 0x7u) + bitSize - 1u) ^ 7u;
		 *          ...
		 *          uint8_t bitsRead = (8 * nBytes) - (7u - (bitPos & 0x07u));
		 *          @endcode
		 *          它把 `bitPos` 当作**从字节 LSB 数起的位序号**，
		 *          而大端信号的起点是"该字节的最高位"，序号是 **7**。
		 *          填 0 等于说"从最低位开始"，于是整体挪了 7 位。
		 *
		 *          **大端信号的 `BitPosition` 要用 `7 - (起始位在字节内的偏移)`**：
		 *          字节对齐（偏移 0）→ 7；从字节第 4 位起 → 3。
		 *          小端信号不受影响，仍是 `起始位 & 7`。
		 *
		 *          验证方法：抓一帧已知内容的报文，用 `!v` 读回来对。
		 *          对不上就先怀疑这里，而不是怀疑接收链路。
		 */
		.BitPosition  = 7u,
		.BitSize      = 16u,
		.type         = COM_UINT16,
		/**
		 * @note **Motorola（大端）**：总线上 byte2 是高字节、byte3 是低字节。
		 *       写成 LITTLE 不会报错，只是读出来的值高低字节颠倒 ——
		 *       温度 0x0123 会变成 0x2301（25 度变成 8961 度）。
		 *       这类错误在实车上表现为"数值离谱但总能编成合法范围"，
		 *       比直接读失败更难发现。
		 */
		.Endianness   = COM_BIG_ENDIAN,
		.isGroupSignal = FALSE,
	},
};

/* ============================ [ 报文内信号索引表 ] ============================ */

/*
 * `Com_IPduConfigType.signals` 的类型是 `const Com_SignalConfigType **`
 * （指针本身可变），所以这里不能声明成 `*const []`，否则类型不匹配。
 */

static const Com_SignalConfigType *Com_TxPduSignals[] = {
	&Com_SignalConfigs[COM_SIG_TX_COUNTER],
	&Com_SignalConfigs[COM_SIG_TX_FLAG],
	&Com_SignalConfigs[COM_SIG_TX_LEVEL],
};

static const Com_SignalConfigType *Com_RxPduSignals[] = {
	&Com_SignalConfigs[COM_SIG_RX_COUNTER],
	&Com_SignalConfigs[COM_SIG_RX_TEMP],
};

/* ============================ [ 报文配置 ] ============================ */

/**
 * @brief TX 报文的周期配置
 * @note  `TxPduId` 是 **PduR 的路径号**，不是 CanIf 的 PDU 号。
 *        链路是 Com → PduR(path 6) → CanIf(CANIF_TX_COM_TEST)。
 *        这两个编号故意分开：换总线（CAN→LIN）时只改路由表，Com 配置不动。
 */
static const Com_IPduTxConfigType Com_IPduTxConfig_Test = {
	.context      = &Com_TxContext_Test,
	.FirstTime    = COM_CONVERT_MS_TO_MAIN_CYCLES(0u),    /* 0 = 用 CycleTime */
	.CycleTime    = COM_CONVERT_MS_TO_MAIN_CYCLES(100u),  /* 100 ms */
	.TxPduId      = (PduIdType)PDUR_COM_TO_CANIF_TX,
};

static const Com_IPduRxConfigType Com_IPduRxConfig_Test = {
	.context      = &Com_RxContext_Test,
	.FirstTimeout = COM_CONVERT_MS_TO_MAIN_CYCLES(0u),
	.Timeout      = COM_CONVERT_MS_TO_MAIN_CYCLES(1000u),
};

/**
 * @brief Com PDU 表（下标即 `Com_RxIndication` / `Com_TxConfirmation` 的 PDU id）
 * @note  `GroupRefMask` 的 bit0 = 组 0。两个报文都挂组 0，
 *        所以 `Com_IpduGroupStop(0)` 能一次停掉收发。
 *        分组是 BCM 的实用能力：诊断会话切到编程会话时停掉常规报文，
 *        只在诊断报表里留心跳 —— 不需要逐个报文去操作。
 */
static const Com_IPduConfigType Com_IPduConfigs[] = {
	[COM_PDU_TX_TEST] = {
		.ptr          = Com_TxPduData_Test,
		.dynLen       = NULL,
		.signals      = Com_TxPduSignals,
		.rxConfig     = NULL,
		.txConfig     = &Com_IPduTxConfig_Test,
		.GroupRefMask = (Com_GroupMaskType)(1u << COM_GROUP_TEST),
		.length       = 8u,
		.numOfSignals = (uint8_t)ARRAY_SIZE(Com_TxPduSignals),
	},
	[COM_PDU_RX_TEST] = {
		.ptr          = Com_RxPduData_Test,
		.dynLen       = NULL,
		.signals      = Com_RxPduSignals,
		.rxConfig     = &Com_IPduRxConfig_Test,
		.txConfig     = NULL,
		.GroupRefMask = (Com_GroupMaskType)(1u << COM_GROUP_TEST),
		.length       = 8u,
		.numOfSignals = (uint8_t)ARRAY_SIZE(Com_RxPduSignals),
	},
};

/* ============================ [ 全局上下文 ] ============================ */

/** @brief 分组启用状态与 DCM 通信控制状态（`USE_DCM` 下多一个字段） */
static Com_GlobalContextType Com_GlobalContext;

/* ============================ [ 总表 ] ============================ */

const Com_ConfigType Com_Config = {
	.IPduConfigs   = Com_IPduConfigs,
	.SignalConfigs = Com_SignalConfigs,
	.context       = &Com_GlobalContext,
	.numOfIPdus    = (uint16_t)ARRAY_SIZE(Com_IPduConfigs),
	.numOfSignals  = (uint16_t)ARRAY_SIZE(Com_SignalConfigs),
	.numOfGroups   = 1u,
};
