/**
 * @file    boot_meta.h
 * @brief   A/B 槽元数据的读写、校验与活动槽判定（boot 与 app 共用）
 *
 * @details @section BOOTMETA_WHO 谁在用这套接口
 *          | 调用方 | 做什么 | 时机 |
 *          |--------|--------|------|
 *          | boot `main` | `BootMeta_Init` → `BootMeta_GetActiveSlot` → `BootMeta_CheckImage` → 跳转 | 每次上电 |
 *          | boot `main` | `BootMeta_PrepareJump`（尝试次数 +1，超限判 INVALID） | 跳转前 |
 *          | app  `boot_app.c` | `BootMeta_Register`（首次烧写自注册）/ `BootMeta_Confirm` | 启动后 |
 *
 *          @section BOOTMETA_LAYOUT 两份 meta 的取舍
 *          每个槽尾部有主、备两份 meta（各占一个 2 KB 扇区）。
 *          读的时候**两份都读、取 `rollingCounter` 大的那份** ——
 *          写的时候顺序是"先备后主"，所以任何时刻掉电，
 *          最多丢掉正在写的这一份，另一份一定是完整的历史值。
 *
 *          @warning 不要改成"先主后备"。主 meta 被擦掉的瞬间若掉电，
 *          备里还是上一版的值，而镜像已经是新版 —— boot 会按旧 rollingCounter
 *          判定活动槽，表现为"升级成功但重启回到旧程序"。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：meta 主备读写 + 活动槽判定 + 镜像 CRC 校验 |
 */

#ifndef BOOT_META_H
#define BOOT_META_H

#include "Std_Types.h"
#include "boot_flash_map.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================ [ 类型 ] ============================ */

/** @brief 单个槽的扫描结果 */
typedef struct {
	uint8_t       metaValid;   /**< meta 结构本身有效（magic + CRC32 通过） */
	Boot_MetaType meta;        /**< 有效时为主备中较新的那份；无效时全 0 */
} Boot_SlotInfoType;

/** @brief `BootMeta_GetActiveSlot()` 的"没有可用槽"返回值 */
#define BOOT_NO_ACTIVE_SLOT     (0xFFu)

/* ============================ [ 接口 ] ============================ */

/**
 * @brief 读取两个槽的 meta（主备择优），填充内部缓存
 * @note  只读 meta，**不校验镜像**（镜像 CRC 要扫几十万字节，
 *        必须等确定要启动某个槽时再做，见 `BootMeta_CheckImage`）。
 *        上电调用一次即可。
 */
void BootMeta_Init(void);

/**
 * @brief 取某个槽的扫描结果
 * @param[in] slot 槽索引（0=A / 1=B）
 * @return 槽信息指针；`slot` 非法时返回 NULL
 */
const Boot_SlotInfoType *BootMeta_GetSlot(uint8_t slot);

/**
 * @brief 判定应该从哪个槽启动
 *
 * @details 规则（按优先级）：
 *          1. 排除 `metaValid == 0`（从未写过 / 结构损坏）；
 *          2. 排除 `state == EMPTY` 或 `INVALID`；
 *          3. 在剩下的里取 `rollingCounter` 最大者；
 *          4. 都没有 → 返回 `BOOT_NO_ACTIVE_SLOT`。
 *
 * @return 槽索引（0/1），或 `BOOT_NO_ACTIVE_SLOT`
 * @note  这里**只看 meta 不看镜像内容**。镜像坏了怎么办由调用方决定：
 *        boot 会再调 `BootMeta_CheckImage`，失败就换另一个槽。
 */
uint8_t BootMeta_GetActiveSlot(void);

/**
 * @brief 校验某个槽里的镜像（向量表合理性 + CRC32）
 *
 * @details 三道检查，任何一道不过就判失败：
 *          1. `imageSize` 在 `[8, BOOT_SLOT_IMAGE_MAX]` 内且 8 字节对齐；
 *          2. 向量表头两个字合理：初始 MSP 落在 SRAM 区间、
 *             Reset_Handler 落在本槽范围内（这是"镜像确实被烧到这个槽"的证据，
 *             CRC 通过但向量表是别的槽的地址时，跳过去必 HardFault）；
 *          3. `Crc_CalculateCRC32(槽基址, imageSize)` 等于 `meta.imageCrc`。
 *
 * @param[in] slot 槽索引
 * @retval E_OK     可以跳转
 * @retval E_NOT_OK meta 无效 / 镜像损坏 / 参数越界
 * @note  第 3 步要扫描整个镜像（当前约 147 KB，48 MHz 下约 6 ms），
 *        所以**每次上电只调一次**，不要放进循环。
 */
Std_ReturnType BootMeta_CheckImage(uint8_t slot);

/**
 * @brief 写某个槽的 meta（主备各一份，先备后主）
 * @param[in] slot 槽索引
 * @param[in] meta meta 内容（`crc` 字段由本函数重算并覆盖）
 * @retval E_OK     两份都写成功
 * @retval E_NOT_OK 参数非法或任一次擦/写失败
 * @note  函数内部会擦除两个 2 KB 扇区，**每次约 40~80 ms 关中断**。
 *        boot 里只在"回滚判定"时调一次，不要在周期任务里用。
 */
Std_ReturnType BootMeta_Write(uint8_t slot, Boot_MetaType *meta);

/**
 * @brief 跳转前的准备：`TESTING` 状态下把尝试次数 +1，超限则判 INVALID
 *
 * @param[in] slot 槽索引
 * @retval E_OK     可以跳转
 * @retval E_NOT_OK 已超过 `BOOT_MAX_BOOT_ATTEMPTS`，该槽已标记 INVALID
 * @note  只有 `state == TESTING` 会累加；`CONFIRMED` 直接返回 E_OK 不写 Flash ——
 *        否则每次上电都擦一次扇区，10 万次擦写寿命几个月就没了。
 */
Std_ReturnType BootMeta_PrepareJump(uint8_t slot);

/**
 * @brief app 启动自检通过后调用：置 CONFIRMED、尝试次数清零
 * @param[in] slot 槽索引
 * @retval E_OK     已确认（或本来就是 CONFIRMED，无需写）
 * @retval E_NOT_OK 写失败
 * @note  这是"新镜像能跑"的唯一证据。没调它，boot 会一直按 TESTING 计数，
 *        三次启动不起来就自动回滚 —— 这正是回滚机制的触发点。
 */
Std_ReturnType BootMeta_Confirm(uint8_t slot);

/**
 * @brief 首次烧写（meta 为空）时由 app 自注册
 *
 * @details 用链接期符号 `__VECTOR_TABLE` / `__CUSTOM_END` 算本站镜像的
 *          起始与长度，自己算 CRC 并写入 meta。这样 J-Link 只烧
 *          boot + app 两个 ELF 就能跑起来，不需要额外的"造 meta"工具。
 *
 * @param[in] slot      槽索引（必须与链接地址一致，函数内会断言）
 * @param[in] imageSize 镜像字节数（`__CUSTOM_END - __VECTOR_TABLE`）
 * @param[in] imageCrc  镜像 CRC32
 * @param[in] major     版本主号（写 0 表示未知）
 * @param[in] minor     版本次号
 * @param[in] patch     版本修订号
 * @retval E_OK     已写入
 * @retval E_NOT_OK 地址与槽不符 / 写失败
 * @note  `rollingCounter` 取"另一个槽的当前值 + 1"，保证自注册后本槽成为活动槽。
 *        若另一个槽的 meta 也无效，从 1 开始。
 */
Std_ReturnType BootMeta_Register(uint8_t slot, uint32_t imageSize, uint32_t imageCrc,
                                 uint8_t major, uint8_t minor, uint8_t patch);

/**
 * @brief 把某个槽降级为 TESTING（**保留**已累计的尝试次数）
 *
 * @details 用在"meta 结构完好但镜像校验失败"的场合 —— 最典型的场景是
 *          **用 J-Link 直接重烧了 app，槽尾 meta 还记着旧镜像的 CRC**。
 *          这时候 boot 如果直接判"镜像损坏"就不跳转，app 永远没机会
 *          跑起来修正 meta，于是形成死锁：烧完还能跑一次，一复位就 HALT。
 *
 *          降级成 TESTING 后跳转，两种结局都是安全的：
 *            - app 起来了 → 它调用 `BootMeta_Register()` 按当前镜像重写 meta；
 *            - app 起不来 → 复位后 `BootMeta_PrepareJump()` 累加尝试次数，
 *              满 `BOOT_MAX_BOOT_ATTEMPTS` 次自动判 INVALID 并回滚到另一个槽。
 *
 *          @warning 第二条成立的前提是**本函数不清零 `bootAttempts`**。
 *          22.3 之前这里清了一次零，结果 boot 每次上电都走一遍降级，
 *          计数被反复清回 1，永不 INVALID —— 回滚能力实际上被废掉。
 *          详见 `BootMeta.c` 对应实现处的说明与 Host 用例 B4。
 *
 *          @note 量产构建（`BOOT_MODE_PRODUCTION=1`）**不调用**本函数：
 *          镜像 CRC 失败直接判 INVALID 并回滚，不执行未经验证的镜像。
 *
 * @param[in] slot 槽索引
 * @retval E_OK     已降级
 * @retval E_NOT_OK meta 本身无效（没法降级）/ 写失败
 */
Std_ReturnType BootMeta_DemoteToTesting(uint8_t slot);

/**
 * @brief 计算 meta 结构自身的 CRC32
 * @param[in] meta 待计算的结构（`crc` 字段会被临时视作 0）
 * @return CRC32
 * @note  公开出来是为了让刷写工具与固件用同一份算法，避免"工具算的和
 *        ECU 算的不一样，但两边都自认为对"。
 */
uint32_t BootMeta_CalcCrc(const Boot_MetaType *meta);

/**
 * @brief 算一段 Flash 的 CRC32（经平台层分段读，不做裸指针访问）
 *
 * @details 板上 Flash 是内存映射的，`(const uint8_t *)addr` 也能读；但那样会让
 *          上层代码依赖"映射"这个平台细节，且同一函数里出现两条取数路径
 *          （向量表走 `Platform_FlashRead()`、CRC 走裸指针）。统一到这里之后：
 *
 *          - 选槽校验（`BootMeta_CheckImage`）与调试打印（`Boot_DebugImage`）
 *            用的是**同一份**算法，不会一处对一处错；
 *          - 该函数能在 Host 上跑（Flash 换成内存数组），启动判定才可测。
 *
 * @param[in] base 起始地址
 * @param[in] len  长度（字节）
 * @return CRC32（AUTOSAR 初值 0xFFFFFFFF）
 */
uint32_t BootMeta_CalcImageCrc(uint32_t base, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* BOOT_META_H */
