/**
 * @file    boot_flash_map.h
 * @brief   A/B 分区 Flash 布局与槽元数据（boot 与 app 共用的唯一权威定义）
 *
 * @details @section BOOTMAP_WHY 为什么单独一个头文件
 *          boot 要知道"槽在哪、怎么判断有效"，app 要知道"我该往哪个槽写新镜像、
 *          meta 怎么存"。这两边一旦各写一份地址常量，改分区时必然漏改一处，
 *          而漏改的表现是"升级成功但重启后跑的是旧程序"——不报错、不崩溃，
 *          只是行为诡异，排查成本极高。所以地址和结构只在本文件出现一次。
 *
 *          @section BOOTMAP_LAYOUT 1 MB PFlash 的划分
 *          @code
 *          0x00000000  ┌──────────────────────┐
 *                      │ Boot         128 KB  │  选槽 / 校验 / 跳转 / 回滚 / 刷写服务
 *          0x00020000  ├──────────────────────┤
 *                      │ Slot A       448 KB  │  尾部 4 KB = meta（主 + 备）
 *          0x00090000  ├──────────────────────┤
 *                      │ Slot B       448 KB  │  尾部 4 KB = meta（主 + 备）
 *          0x00100000  └──────────────────────┘   （无预留区）
 *          @endcode
 *
 *          @section BOOTMAP_META meta 为什么放在槽尾部而不是单独一个区
 *          - **A/B 对称**：两个槽结构完全相同，boot 的比较逻辑只有一份，
 *            不存在"活动槽的 meta 在别处"这种特例分支；
 *          - **跟着镜像走**：镜像被整体擦除时，meta 在同一槽内一起被擦掉，
 *            不可能出现"镜像没了但 meta 还说自己有效"；
 *          - **掉电安全**：写 meta 是升级的最后一步，且主备两份 + CRC，
 *            任意时刻掉电最多丢一次 meta 更新，不会两个槽同时失效。
 *
 *          @section BOOTMAP_ACTIVE 活动槽怎么判定
 *          没有"当前槽"标志位。两个槽各存一个 `rollingCounter`（单调递增），
 *          **值大的就是活动槽**（与 as-master `bl_ab.c` 的
 *          `BL_USE_AB_ACTIVE_BASED_ON_META_ROLLING_COUNTER` 一致）。
 *          理由：标志位需要"先清旧的再置新的"，中间掉电就是两个都是活动/都不是；
 *          而比较计数值只有一次写操作，天然原子。
 *
 *          @section BOOTMAP_ALIGN 尺寸约束
 *          PFlash 扇区 2 KB、phrase 8 B。以下三条在文件末尾用 `#if` 硬校验：
 *          1. 每个槽大小必须是扇区整数倍（否则擦不干净尾部）；
 *          2. meta 区必须正好覆盖 2 个扇区（主备各一个）；
 *          3. `Boot_MetaType` 必须是 8 B 整数倍（phrase 写要求）。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：64K / 448K / 448K / 64K + 槽尾 meta |
 */

#ifndef BOOT_FLASH_MAP_H
#define BOOT_FLASH_MAP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================ [ 物理常量 ] ============================ */

/** @brief PFlash 总容量（CVM0146） */
#define BOOT_PFLASH_SIZE            (0x00100000u)

/** @brief PFlash 扇区大小（擦除粒度） */
#define BOOT_PFLASH_SECTOR_SIZE     (2048u)

/** @brief PFlash 最小写入粒度（phrase） */
#define BOOT_PFLASH_PHRASE_SIZE     (8u)

/* ============================ [ 分区 ] ============================ */

/** @brief Boot 区基址 */
#define BOOT_REGION_BASE            (0x00000000u)

/** @brief Boot 区大小（128 KB）
 *
 * @details 为什么从 64 KB 扩到 128 KB（D1 决策）：刷写服务（0x34/36/37）搬进 boot 后，
 *          boot 要额外链接 CanIf + CanTp + PduR + Dcm + 各自的配置表。
 *          实测 App 侧这几个模块 text 合计 18.9 KB，加上配置表与 CanAc 约 22 KB，
 *          64 KB 区只剩 8.9 KB 余量，装不下 —— 扩到 128 KB 后余量约 45 KB。
 */
#define BOOT_REGION_SIZE            (0x00020000u)

/** @brief Slot A 基址（boot 扩到 128 KB 后从 0x20000 起） */
#define BOOT_SLOT_A_BASE            (0x00020000u)

/** @brief Slot B 基址（A 槽 448 KB 之后：0x20000 + 0x70000 = 0x90000） */
#define BOOT_SLOT_B_BASE            (0x00090000u)

/** @brief 单个槽大小（448 KB） */
#define BOOT_SLOT_SIZE              (0x00070000u)

/** @brief 每槽尾部 meta 区大小（2 个扇区：主 + 备） */
#define BOOT_SLOT_META_SIZE         (0x00001000u)

/**
 * @brief 单槽可放镜像的最大字节数（448 KB − 4 KB = 444 KB）
 * @note  0x31 擦除与 0x34 请求下载都必须先过这个上限，
 *        否则会把 meta 一起写掉，表现为"刷完重启跑回旧版本"。
 */
#define BOOT_SLOT_IMAGE_MAX         (BOOT_SLOT_SIZE - BOOT_SLOT_META_SIZE)

/** @brief 预留区基址（紧随 B 槽之后） */
#define BOOT_RESERVED_BASE          (0x00100000u)

/**
 * @brief 预留区大小
 *
 * @details D1 后为 **0**：128K + 448K + 448K 正好 1 MB，没有预留空间。
 *          标定/参数区以后要走 NVM（DFlash/FEE），不占 PFlash 槽区。
 */
#define BOOT_RESERVED_SIZE          (0x00000000u)

/** @brief 槽数量 */
#define BOOT_SLOT_NUM               (2u)

/** @brief 槽索引：A */
#define BOOT_SLOT_INDEX_A           (0u)

/** @brief 槽索引：B */
#define BOOT_SLOT_INDEX_B           (1u)

/** @brief 取槽基址（index 必须是编译期常量或已验证 0/1） */
#define BOOT_SLOT_BASE(idx) \
	(((idx) == BOOT_SLOT_INDEX_A) ? BOOT_SLOT_A_BASE : BOOT_SLOT_B_BASE)

/** @brief 取槽主 meta 地址（槽尾倒数第 2 个扇区） */
#define BOOT_SLOT_META_PRIMARY(idx) \
	(BOOT_SLOT_BASE(idx) + BOOT_SLOT_SIZE - BOOT_SLOT_META_SIZE)

/** @brief 取槽备份 meta 地址（槽尾最后 1 个扇区） */
#define BOOT_SLOT_META_BACKUP(idx) \
	(BOOT_SLOT_BASE(idx) + BOOT_SLOT_SIZE - BOOT_PFLASH_SECTOR_SIZE)

/* ============================ [ 槽状态 ] ============================ */

/**
 * @brief 槽的启动状态
 *
 * @details 状态迁移只有一条合法路径，其余都是"从上次掉电的位置继续"：
 *          @code
 *          EMPTY ──0x37 写完镜像──► TESTING ──app 自检通过──► CONFIRMED
 *                                      │
 *                                      └──连续启动失败满 3 次──► INVALID
 *          @endcode
 *
 *          @note `TESTING` 存在的意义：新镜像第一次启动时谁也不能保证它能跑起来
 *                （时钟配错、看门狗喂不上、总线起不来）。标记为 TESTING 期间
 *                boot 每次跳转前把 `bootAttempts` +1；app 起来后调
 *                `Boot_ConfirmRunning()` 清回 0 并置 CONFIRMED。
 *                次数超限则判 INVALID，下次上电自动回滚到另一个槽。
 */
typedef enum {
	BOOT_SLOT_EMPTY     = 0u,   /**< 未烧写过（magic 不匹配或已擦除） */
	BOOT_SLOT_TESTING   = 1u,   /**< 新刷入，尚未被 app 确认 */
	BOOT_SLOT_CONFIRMED = 2u,   /**< app 启动并自检通过 */
	BOOT_SLOT_INVALID   = 3u,   /**< 连续启动失败，作废 */
} Boot_SlotStateType;

/** @brief 允许的最大连续启动尝试次数，超过即判 INVALID */
#define BOOT_MAX_BOOT_ATTEMPTS      (3u)

/* ============================ [ 元数据 ] ============================ */

/** @brief meta 魔数：`'M' 'E' 'T' 'A'`（小端存储后读出即 0x4154454D） */
#define BOOT_META_MAGIC             (0x4154454Du)

/* ============================ [ 刷写请求 ] ============================ */

/**
 * @brief `Boot_MetaType.reserved[0]` 的取值：App → boot 的一次性刷写请求
 *
 * @details 用途：诊断仪发 `10 03`（进编程会话）时，App **没有** 0x34/0x36/0x37
 *          的实现（那是 boot 的服务），必须把控制权交给 boot。做法就是在这里
 *          放一个标志再复位；boot 上电读到它就停在 UDS，而不是跳 App。
 *
 *          | 值 | 含义 |
 *          |----|------|
 *          | `0xFF` | 无请求 —— **同时也是 Flash 擦除态**，所以旧镜像写的 meta（reserved 全 0xFF）天然被解释成"无请求"，不需要版本兼容分支 |
 *          | `0x01` | App 请求：下次上电停在 boot 的 UDS 刷写模式 |
 *
 *          @warning 一次性。boot 读到 `0x01` 后**先清成 0xFF 再进 UDS**，
 *          否则刷完复位又会进 UDS，App 永远起不来（表现为"刷成功了但一直停
 *          在 boot"）。清除失败时 boot 选择**正常启动**而不是进 UDS ——
 *          宁可刷不了，也不能把板子变成只能刷机的砖。
 */
#define BOOT_META_REQ_NONE          (0xFFu)
#define BOOT_META_REQ_FLASH         (0x01u)

/**
 * @brief 槽尾元数据（主备各存一份，共 32 字节）
 *
 * @warning **字段只增不改、不改顺序**。boot 与 app 是两个独立镜像，
 *          升级过渡期一定存在"新 boot 读旧 meta"或"旧 app 写新 meta"的组合。
 *          改字段顺序会让旧镜像把 `imageCrc` 当 `imageSize` 读，
 *          表现是"CRC 校验永远失败"，但 meta 本身 CRC 又是对的 —— 极难定位。
 *          真要加字段，往 `reserved` 里挪，或提升 `version` 并做兼容分支。
 */
typedef struct {
	uint32_t magic;              /**< 必须是 BOOT_META_MAGIC */
	uint32_t rollingCounter;     /**< 全局单调递增，两槽比较定活动槽 */
	uint32_t imageSize;         /**< 镜像字节数（含向量表，不含 meta） */
	uint32_t imageCrc;          /**< 镜像 CRC32：从槽基址起 imageSize 字节 */
	uint32_t programmingCounter; /**< 本槽累计烧写次数（寿命统计） */
	uint8_t  versionMajor;       /**< 应用版本：主 */
	uint8_t  versionMinor;       /**< 应用版本：次 */
	uint8_t  versionPatch;       /**< 应用版本：修订 */
	uint8_t  slot;               /**< 槽索引（0=A / 1=B），防 meta 被搬错槽 */
	uint8_t  state;              /**< Boot_SlotStateType */
	uint8_t  bootAttempts;       /**< 本次 TESTING 已尝试启动次数 */
	uint8_t  reserved[2];        /**< reserved[0] = BOOT_META_REQ_*（刷写请求）；
	                                  reserved[1] 保留。擦除态 0xFF = 无请求 */
	uint32_t crc;                /**< 本结构 CRC32（计算时本字段置 0） */
} Boot_MetaType;

/* ============================ [ 编译期对账 ] ============================ */

/* 槽大小必须是扇区整数倍：否则 `eraseSlot` 按扇区循环会漏掉尾部，
 * 而漏掉的那一段永远不是 0xFF，下次写 phrase 时预检失败 ——
 * 症状是"刷到某个地址之后就再也写不进去"。 */
#if ((BOOT_SLOT_SIZE % BOOT_PFLASH_SECTOR_SIZE) != 0u)
#error "BOOT_SLOT_SIZE 必须是 PFlash 扇区（2 KB）的整数倍"
#endif

/* meta 区必须正好 2 个扇区：主一份、备一份，各占一个扇区。
 * 若大于 2 个扇区，主备之间会有用不到的空隙；小于则两份挤在同一扇区，
 * 擦主 meta 会把备 meta 一起擦掉，等于没有备份。 */
#if (BOOT_SLOT_META_SIZE != (2u * BOOT_PFLASH_SECTOR_SIZE))
#error "BOOT_SLOT_META_SIZE 必须正好是 2 个 PFlash 扇区"
#endif

/* meta 结构必须是 phrase 整数倍：`FlashDrv_ProgramPhrase()` 一次写 8 字节，
 * 写入长度不是 8 的倍数时最后一段会用 0xFF 补齐 —— 补在结构体外面就无所谓，
 * 但如果结构体本身跨了 phrase 边界而长度算错，会把相邻扇区内容带出来。
 *
 * 这里只能用 `_Static_assert`，不能用 `#if`：预处理阶段 `sizeof` 尚未求值，
 * 写 `#if (sizeof(T) % 8)` 会报 "missing binary operator before token" ——
 * 因为预处理器把 `sizeof` 当成未定义标识符（展开为 0），后面跟着 `(` 就语法错。 */
_Static_assert((sizeof(Boot_MetaType) % BOOT_PFLASH_PHRASE_SIZE) == 0u,
               "Boot_MetaType length must be a multiple of the flash phrase size (8)");

/* 四个区间必须严丝合缝拼满 1 MB，不能重叠也不能有洞 */
#if ((BOOT_REGION_SIZE + (BOOT_SLOT_NUM * BOOT_SLOT_SIZE) + BOOT_RESERVED_SIZE) != BOOT_PFLASH_SIZE)
#error "分区之和必须等于 BOOT_PFLASH_SIZE（1 MB）"
#endif

#ifdef __cplusplus
}
#endif

#endif /* BOOT_FLASH_MAP_H */
