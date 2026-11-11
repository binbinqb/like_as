/**
 * @file    Dem_Cfg.h
 * @brief   Dem（诊断事件管理器）的平台配置
 *
 * @details @section DEMCFG_WHY 为什么 Dem 的配置放在平台层
 *          `infras/diagnostic/Dem/Dem.c` 是**与芯片无关**的 BSW ——
 *          它只认"DTC 表有 N 条""状态存在哪个 NvM 块"，
 *          不认 DFlash 的扇区大小、也不认块号怎么排。
 *
 *          这些平台相关的数字放在这里，和 `NvM_Cfg.h` / `Fee_Cfg.h` 同一个目录，
 *          原因和它们一样：**改板子只改 config，不动 infras**。
 *          依赖方向是 `Dem.c → Dem_Cfg.h`（编译期读宏），
 *          `Dem_Cfg.h → NvM_Cfg.h`（拿块 id），**不会反向**。
 *
 *          @section DEMCFG_SCOPE 这个 Dem 是简化实现
 *          完整 AUTOSAR Dem 有"事件去抖 → 置 pending → 确认 → 老化"四层状态机，
 *          2070 行起步。本工程只有 CAN 总线这一类故障源，所以只实现
 *          Dcm 0x19/0x14 真正要用到的 9 个 API，状态直接由
 *          `Dem_SetEventStatus()` 的入参决定，没有去抖和老化。
 *
 *          | 能力 | 本实现 | 完整 Dem |
 *          |------|--------|----------|
 *          | DTC 状态字节（8 位 UDS） | ✅ | ✅ |
 *          | 发生次数 / 首次末次启动 | ✅ | ✅ |
 *          | 0x19 子功能 0x01/0x02/0x0A | ✅ | ✅ |
 *          | 0x14 清故障码 | ✅ | ✅ |
 *          | 去抖（计数/时间） | ❌ | ✅ |
 *          | 老化 / healed | ❌ | ✅ |
 *          | 冻结帧 / 扩展数据 | ❌（现场快照存 DTC 条目里） | ✅ |
 *
 *          需要上面这三样时，把这个文件换成完整 Dem 的配置即可 ——
 *          对外的 `Dem_SetEventStatus()` / `Dem_*DTC*()` 接口完全一致。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：DTC 表复用 NvM 的 DTC 块（4 槽 × 16 字节） |
 */

#ifndef DEM_CFG_H
#define DEM_CFG_H

#include "Dem.h"
#include "NvM_Cfg.h"

/* ============================ [ 存储 ] ============================ */

/**
 * @brief DTC 状态表所在的 NvM 块
 * @note  复用 M5 就建好的 DTC 块：64 字节 = 4 条 × 16 字节。
 *        块内容由 Dem 独占，别的模块不要直接写它。
 */
#define DEM_CFG_NVM_BLOCK_ID        (NVM_CFG_ID_DTC)

/** @brief 该块的载荷长度（不含 CRC） */
#define DEM_CFG_NVM_BLOCK_BYTES     (NVM_CFG_BLK_DTC_SIZE)

/** @brief 一条 DTC 记录的长度（必须与 `Dem_DtcRecordType` 一致） */
#define DEM_CFG_DTC_RECORD_BYTES    (16u)

/**
 * @brief DTC 表容量 —— 由块长推出来，改块长自动跟着变
 * @note  刻意**不带 `(uint8_t)` 强转**：本宏要参与 `Dem_Cfg.c` 的 `#if` 对账，
 *        预处理阶段不认类型转换（`missing binary operator before token "("`）。
 *        需要窄化时在使用处显式转。
 */
#define DEM_CFG_MAX_DTC             (DEM_CFG_NVM_BLOCK_BYTES / DEM_CFG_DTC_RECORD_BYTES)

/* ============================ [ 事件 ] ============================ */

/**
 * @brief 事件编号
 * @details 一个"事件"是监视器给出的"好/坏"结论，一个 DTC 可以挂多个事件
 *          （比如 CAN0 和 CAN1 的总线故障都归到 U0001）。
 *          本工程两个通道各一个事件，DTC 相同、用 `channel` 字段区分。
 */
#define DEM_CFG_EVENT_CAN0_BUSOFF   (0u)
#define DEM_CFG_EVENT_CAN1_BUSOFF   (1u)
#define DEM_CFG_EVENT_NUM           (2u)

/* ============================ [ DTC ] ============================ */

/**
 * @brief U0001 —— "高速 CAN 通信总线"
 * @note  3 字节 DTC：`0xC00100` = `11 00 0000`（U 类，第一位 0，第二位 0）+ `01`。
 */
#define DEM_CFG_DTC_CAN_BUSOFF      (0x00C00100u)

/**
 * @brief 支持的 DTC 状态位
 * @details bit0 TF（本次测试失败）、bit1 TFTOC（本驾驶循环失败）、
 *          bit2 PDTC（待定）、bit3 CDTC（已确认）、bit7 WIR（告警灯请求）。
 *          **不支持** TNCSLC/TFSLC/TNCTOC（这三个是"自上次清码后"类计数，
 *          需要完整的操作循环管理，本实现没有）。
 *
 *          0x19 响应里的 availabilityMask 就是这个值 —— 它告诉测试仪
 *          "这个 ECU 能报哪些状态位"，不要谎报。
 */
/* 同样不带强转，理由同上（要参与 `#if` 对账） */
#define DEM_CFG_STATUS_AVAILABILITY_MASK                                                \
	(DEM_UDS_STATUS_TF | DEM_UDS_STATUS_TFTOC | DEM_UDS_STATUS_PDTC |                  \
	 DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_WIR)

/* ============================ [ 本工程扩展接口 ] ============================ */
/*
 * 下面这些**不属于** AUTOSAR Dem 标准接口，是给串口调试命令（`!b`）用的。
 * 放在这里而不是 Dem.h：Dem.h 与 as-master 保持逐字节一致，
 * 将来整包换上游版本时不会因为夹带私有声明产生冲突。
 */

/**
 * @brief 一条 DTC 的可读视图（把内部 16 字节记录拍平成字段）
 * @note  只读快照，改它不影响 Dem 内部状态
 */
typedef struct {
	uint32_t dtcCode;      /**< 3 字节 UDS DTC（低 24 位） */
	uint16_t occurCount;   /**< 发生次数 */
	uint16_t firstBoot;    /**< 首次发生的启动序号 */
	uint16_t lastBoot;     /**< 最近一次发生的启动序号 */
	uint8_t  channel;      /**< CAN 通道号 */
	uint8_t  errBits;      /**< 现场快照：错误位图（`CAN_BUSOFF_ERR_*`） */
	uint8_t  fltConf;      /**< 现场快照：FLTCONF */
	uint8_t  status;       /**< 8 位 UDS 状态字节 */
} Dem_DtcInfoType;

/**
 * @brief 按"第几条非空"取 DTC 记录（调试用）
 * @param[in]  index 从 0 开始的序号（跳过空槽）
 * @param[out] rec   输出
 * @retval true  找到
 * @retval false 没有更多，或 Dem 未初始化
 */
bool Dem_GetRecordByIndex(uint8_t index, Dem_DtcInfoType *rec);

/** @brief DTC 表容量（`!b` 打印"容量 N"用） */
uint8_t Dem_GetDtcCapacity(void);

/**
 * @brief 记下本次启动序号（写进 DTC 的 firstBoot/lastBoot）
 * @param[in] bootSeq 启动计数（取低 16 位）
 * @note  AUTOSAR 用操作循环（OperationCycle）表达时间，
 *        本工程没有 EcuM，用"启动次数"替代 —— 语义等价且更直观。
 */
void Dem_SetBootSequence(uint32_t bootSeq);

#endif /* DEM_CFG_H */
