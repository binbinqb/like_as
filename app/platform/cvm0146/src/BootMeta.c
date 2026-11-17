/**
 * @file    BootMeta.c
 * @brief   A/B 槽元数据：读取、校验、写入、活动槽判定、镜像 CRC 校验
 *
 * @details 本文件只碰两类东西：`Platform_Flash*`（平台层的擦写）与
 *          `Crc_CalculateCRC32`（AUTOSAR CRC 库）。不碰任何寄存器，
 *          因此 boot 与 app 链接同一份实现，行为必然一致。
 *
 *          @section BOOTMETA_ORDER 写入顺序为什么是"先备后主"
 *          @code
 *          1. 擦备份扇区  →  写备份
 *          2. 擦主扇区    →  写主
 *          @endcode
 *          第 1 步完成时，备份已是新值、主还是旧值；第 2 步擦主时若掉电，
 *          备份仍在且是新值，读的时候"取 rollingCounter 大的"就能拿到新值。
 *          反过来（先主后备）在第 2 步擦备时掉电，主是新的、备是旧的，
 *          也能取到新值 —— 但第 1 步擦主时掉电就只剩旧备份，
 *          而镜像已经写完了，于是 boot 按旧计数启动新镜像，
 *          下次升级又会把新镜像当"非活动槽"擦掉。所以顺序不能反。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版 |
 */

#include <string.h>

#include "boot_meta.h"
#include "platform_cvm0146.h"
#include "Crc.h"

/* ============================ [ 宏 ] ============================ */

/** @brief CRC32 的 AUTOSAR 初值 */
#define BOOTMETA_CRC_INIT       (0xFFFFFFFFu)

/** @brief SRAM 上界（含栈顶 `__StackTop` = 0x2000F000） */
#define BOOTMETA_SRAM_TOP       (0x2000F000u)

/** @brief SRAM 下界（SRAM_L 起始） */
#define BOOTMETA_SRAM_BOTTOM    (0x1FFF0000u)

/** @brief 算镜像 CRC 时每次从 Flash 取的字节数
 *
 * @details 64 B 是"栈占用 + 调用次数"的折中：boot 的栈不大，取 1 KB 会白占
 *          1 KB；取 8 B 则要调 5 万多次（444 KB 上限）。64 B 时约 7000 次，
 *          全镜像校验实测仍是毫秒级 —— 它只在选槽时算**一次**。
 */
#define BOOTMETA_CRC_CHUNK      (256u)

/* ============================ [ 内部数据 ] ============================ */

/** @brief 两个槽的扫描缓存（`BootMeta_Init` 填充，之后只读） */
static Boot_SlotInfoType s_slotInfo[BOOT_SLOT_NUM];

/** @brief 是否已初始化，防止未调用 Init 就读到全 0 */
static uint8_t s_initialized = 0u;

/* ============================ [ 内部函数 ] ============================ */

/**
 * @brief 算一段 Flash 的 CRC32（经平台层分段读，不做裸指针访问）
 *
 * @details @section BOOTMETA_CRC_WHY 为什么不用 `(const uint8_t *)addr`
 *
 *          原先这一句是 `Crc_CalculateCRC32((const uint8_t *)base, ...)`，
 *          把 Flash 地址直接当指针用。板上 Flash 内存映射，能跑；但它带来两个
 *          实际问题：
 *
 *          1. **同一个函数里两条取数路径**：向量表用 `Platform_FlashRead()`，
 *             整镜像 CRC 用裸指针。将来 Flash 若加了缓存 / ECC / 间接映射，
 *             两条路径会静默分叉，表现是"向量表读得到、CRC 永远不对"。
 *          2. **无法离板验证**：Host 上 `(uint8_t *)0x20000` 是野地址，
 *             `BootMeta_CheckImage` 只好整段不测 —— 而选槽 / 回滚正是最需要
 *             反复回归的一段（见 `test_boot_meta.c`）。
 *
 *          代价是分段：`BOOTMETA_CRC_CHUNK`（256 B）一段，245 KB 镜像约 960 次
 *          `Platform_FlashRead`。这段代价是**量过的**（上板 `bootperf`，CYCCNT 计时）：
 *
 *          | 取数方式 | 245 KB 耗时 |
 *          |----------|-------------|
 *          | 裸指针一次算（改造前的写法） | 76 ms |
 *          | 256 B 分段（现在）           | 81 ms |
 *
 *          即离板可测换 5 ms（约 6%）。选槽只算一次，且这一版把"多算一次"也去掉了
 *          （原先调试打印为了显示实测 CRC 会再算一遍整镜像）。
 *
 * @param[in] base 镜像基址
 * @param[in] len  镜像长度（字节）
 * @return CRC32（AUTOSAR 初值 0xFFFFFFFF）
 */
uint32_t BootMeta_CalcImageCrc(uint32_t base, uint32_t len)
{
	uint8_t  buf[BOOTMETA_CRC_CHUNK];
	uint32_t crc = BOOTMETA_CRC_INIT;
	uint32_t done = 0u;
	boolean  first = TRUE;

	while (done < len) {
		uint32_t n = len - done;

		if (n > (uint32_t)sizeof(buf)) {
			n = (uint32_t)sizeof(buf);
		}
		Platform_FlashRead(base + done, buf, n);
		/* AUTOSAR 的分段约定：上一次的**结果**作为本次 startValue，
		 * 且 isFirstCall = FALSE（函数内部会先反 finalize 再续算）。 */
		crc = Crc_CalculateCRC32(buf, n, crc, first);
		first = FALSE;
		done += n;
	}

	return crc;
}

/**
 * @brief 判断 slot 参数是否合法
 * @param[in] slot 槽索引
 * @retval 1 合法
 * @retval 0 非法
 */
static uint8_t BootMeta_IsSlotValid(uint8_t slot)
{
	return (slot < BOOT_SLOT_NUM) ? 1u : 0u;
}

/**
 * @brief 读一份 meta 并校验结构（magic + CRC32）
 * @param[in]  addr meta 地址
 * @param[out] meta 读出的内容（校验失败时内容不可信）
 * @retval 1 有效
 * @retval 0 无效（全 0xFF / magic 不符 / CRC 不符）
 */
static uint8_t BootMeta_ReadOne(uint32_t addr, Boot_MetaType *meta)
{
	uint32_t crc;

	Platform_FlashRead(addr, meta, (uint32_t)sizeof(Boot_MetaType));

	if (meta->magic != BOOT_META_MAGIC) {
		return 0u;
	}
	if (meta->slot >= BOOT_SLOT_NUM) {
		return 0u;
	}

	crc = BootMeta_CalcCrc(meta);

	return (crc == meta->crc) ? 1u : 0u;
}

/**
 * @brief 把一份 meta 写到指定地址（擦扇区 + 写 32 字节）
 * @param[in] addr 目标地址（扇区起始）
 * @param[in] meta 内容
 * @retval E_OK     成功
 * @retval E_NOT_OK 擦除或写入失败
 */
static Std_ReturnType BootMeta_WriteOne(uint32_t addr, const Boot_MetaType *meta)
{
	uint8_t buf[sizeof(Boot_MetaType)];

	(void)memcpy(buf, meta, sizeof(buf));

	/* 长度必须是 phrase 整数倍，`boot_flash_map.h` 已用 #error 保证 */
	if (Platform_FlashEraseSector(addr) != E_OK) {
		return E_NOT_OK;
	}

	return Platform_FlashWrite(addr, buf, (uint32_t)sizeof(buf));
}

/* ============================ [ 对外接口 ] ============================ */

uint32_t BootMeta_CalcCrc(const Boot_MetaType *meta)
{
	Boot_MetaType tmp;

	if (meta == NULL) {
		return 0u;
	}

	(void)memcpy(&tmp, meta, sizeof(tmp));
	tmp.crc = 0u;

	return Crc_CalculateCRC32((const uint8_t *)&tmp, (uint32_t)sizeof(tmp),
	                          BOOTMETA_CRC_INIT, TRUE);
}

void BootMeta_Init(void)
{
	uint8_t slot;

	for (slot = 0u; slot < BOOT_SLOT_NUM; slot++) {
		Boot_MetaType primary;
		Boot_MetaType backup;
		uint8_t       primaryOk;
		uint8_t       backupOk;

		(void)memset(&s_slotInfo[slot], 0, sizeof(s_slotInfo[slot]));

		primaryOk = BootMeta_ReadOne(BOOT_SLOT_META_PRIMARY(slot), &primary);
		backupOk  = BootMeta_ReadOne(BOOT_SLOT_META_BACKUP(slot), &backup);

		if ((primaryOk != 0u) && (backupOk != 0u)) {
			/* 两份都有效：取 rollingCounter 大的（写顺序"先备后主"，
			 * 所以正常情况下主 >= 备；相等时优先主） */
			s_slotInfo[slot].meta = (backup.rollingCounter > primary.rollingCounter)
			                        ? backup : primary;
			s_slotInfo[slot].metaValid = 1u;
		} else if (primaryOk != 0u) {
			s_slotInfo[slot].meta = primary;
			s_slotInfo[slot].metaValid = 1u;
		} else if (backupOk != 0u) {
			s_slotInfo[slot].meta = backup;
			s_slotInfo[slot].metaValid = 1u;
		} else {
			/* 两份都无效：保持全 0，metaValid = 0 */
		}
	}

	s_initialized = 1u;
}

const Boot_SlotInfoType *BootMeta_GetSlot(uint8_t slot)
{
	if ((s_initialized == 0u) || (BootMeta_IsSlotValid(slot) == 0u)) {
		return NULL;
	}

	return &s_slotInfo[slot];
}

uint8_t BootMeta_GetActiveSlot(void)
{
	uint8_t slot;
	uint8_t best = BOOT_NO_ACTIVE_SLOT;
	uint32_t bestCounter = 0u;

	if (s_initialized == 0u) {
		return BOOT_NO_ACTIVE_SLOT;
	}

	for (slot = 0u; slot < BOOT_SLOT_NUM; slot++) {
		const Boot_SlotInfoType *info = &s_slotInfo[slot];

		if (info->metaValid == 0u) {
			continue;
		}
		if ((info->meta.state == (uint8_t)BOOT_SLOT_EMPTY) ||
		    (info->meta.state == (uint8_t)BOOT_SLOT_INVALID)) {
			continue;
		}

		if ((best == BOOT_NO_ACTIVE_SLOT) || (info->meta.rollingCounter > bestCounter)) {
			best = slot;
			bestCounter = info->meta.rollingCounter;
		}
	}

	return best;
}

Std_ReturnType BootMeta_CheckImageEx(uint8_t slot, uint32_t *measuredCrc)
{
	uint32_t base;
	uint32_t sp;
	uint32_t pc;
	const Boot_SlotInfoType *info;

	if (measuredCrc != NULL) {
		*measuredCrc = 0u;
	}

	if ((s_initialized == 0u) || (BootMeta_IsSlotValid(slot) == 0u)) {
		return E_NOT_OK;
	}

	info = &s_slotInfo[slot];
	if (info->metaValid == 0u) {
		return E_NOT_OK;
	}

	/* 1) 长度必须落在可用镜像区内。
	 *
	 *    @warning **不要在这里要求 8 字节（phrase）对齐** —— 这是踩过的坑：
	 *    镜像长度是 `__CUSTOM_END - __VECTOR_TABLE`，等于 `.text` +
	 *    `.interrupts` + `.data` 的 ROM 副本之和，实测 154804，**% 8 == 4**。
	 *    CRC32 覆盖任意长度都成立；刷写时最后一个 phrase 由硬件用 0xFF 补齐，
	 *    补出来的部分不在 imageSize 里，也不参与 CRC。
	 *    一度按 phrase 对齐来判，结果 boot 每次都报 "image CRC failed"，
	 *    而调试打印里算出来的 CRC 和 meta 里的期望值一模一样 ——
	 *    因为失败的根本不是 CRC，是它前面这道长度检查。
	 *
	 *    只要求 4 字节对齐：Cortex-M 的向量表与 Thumb 指令都是 4 字节粒度。 */
	if ((info->meta.imageSize < BOOT_PFLASH_PHRASE_SIZE) ||
	    (info->meta.imageSize > BOOT_SLOT_IMAGE_MAX) ||
	    ((info->meta.imageSize % 4u) != 0u)) {
		return E_NOT_OK;
	}

	base = BOOT_SLOT_BASE(slot);

	/* 2) 向量表头两个字：初始 MSP 与 Reset_Handler。
	 *    这一步能抓住"CRC 算的是一段别的东西"——比如镜像被整体搬到了另一个槽，
	 *    但 meta 里的 CRC 还是按原槽算的（这种时候 CRC 会失败，但先检查
	 *    向量表能立刻给出更明确的原因）。 */
	Platform_FlashRead(base, &sp, 4u);
	Platform_FlashRead(base + 4u, &pc, 4u);

	if ((sp < BOOTMETA_SRAM_BOTTOM) || (sp > BOOTMETA_SRAM_TOP)) {
		return E_NOT_OK;
	}
	if ((pc < base) || (pc >= (base + info->meta.imageSize))) {
		return E_NOT_OK;
	}

	/* 3) 整镜像 CRC32 */
	{
		uint32_t crc = BootMeta_CalcImageCrc(base, info->meta.imageSize);

		if (measuredCrc != NULL) {
			*measuredCrc = crc;
		}
		return (crc == info->meta.imageCrc) ? E_OK : E_NOT_OK;
	}
}

Std_ReturnType BootMeta_CheckImage(uint8_t slot)
{
	return BootMeta_CheckImageEx(slot, NULL);
}

Std_ReturnType BootMeta_Write(uint8_t slot, Boot_MetaType *meta)
{
	Std_ReturnType ret;

	if ((meta == NULL) || (BootMeta_IsSlotValid(slot) == 0u)) {
		return E_NOT_OK;
	}

	meta->magic = BOOT_META_MAGIC;
	meta->slot  = slot;
	meta->crc   = BootMeta_CalcCrc(meta);

	/* 先备后主，见文件头 @section BOOTMETA_ORDER */
	ret = BootMeta_WriteOne(BOOT_SLOT_META_BACKUP(slot), meta);
	if (ret != E_OK) {
		return E_NOT_OK;
	}

	ret = BootMeta_WriteOne(BOOT_SLOT_META_PRIMARY(slot), meta);
	if (ret != E_OK) {
		return E_NOT_OK;
	}

	/* 更新缓存，让同一上电周期内的后续判断看到最新值 */
	s_slotInfo[slot].meta = *meta;
	s_slotInfo[slot].metaValid = 1u;

	return E_OK;
}

Std_ReturnType BootMeta_PrepareJump(uint8_t slot)
{
	Boot_MetaType meta;
	const Boot_SlotInfoType *info;

	if (s_initialized == 0u) {
		return E_NOT_OK;
	}
	if (BootMeta_IsSlotValid(slot) == 0u) {
		return E_NOT_OK;
	}

	info = &s_slotInfo[slot];
	if (info->metaValid == 0u) {
		/* 无 meta 的"首次烧写"路径：不计数，直接放行。
		 * app 起来后会调 `BootMeta_Register` 补写 meta。 */
		return E_OK;
	}

	if (info->meta.state != (uint8_t)BOOT_SLOT_TESTING) {
		/* CONFIRMED 直接放行，**不写 Flash** —— 见头文件 @note */
		return E_OK;
	}

	meta = info->meta;
	if (meta.bootAttempts < 0xFFu) {
		meta.bootAttempts++;
	}

	if (meta.bootAttempts > BOOT_MAX_BOOT_ATTEMPTS) {
		meta.state = (uint8_t)BOOT_SLOT_INVALID;
		(void)BootMeta_Write(slot, &meta);
		return E_NOT_OK;
	}

	return BootMeta_Write(slot, &meta);
}

Std_ReturnType BootMeta_Confirm(uint8_t slot)
{
	Boot_MetaType meta;
	const Boot_SlotInfoType *info;

	if ((s_initialized == 0u) || (BootMeta_IsSlotValid(slot) == 0u)) {
		return E_NOT_OK;
	}

	info = &s_slotInfo[slot];
	if (info->metaValid == 0u) {
		return E_NOT_OK;
	}

	if ((info->meta.state == (uint8_t)BOOT_SLOT_CONFIRMED) && (info->meta.bootAttempts == 0u)) {
		/* 已经确认过：不重复写，省擦写寿命 */
		return E_OK;
	}

	meta = info->meta;
	meta.state        = (uint8_t)BOOT_SLOT_CONFIRMED;
	meta.bootAttempts = 0u;

	return BootMeta_Write(slot, &meta);
}

Std_ReturnType BootMeta_DemoteToTesting(uint8_t slot)
{
	Boot_MetaType meta;
	const Boot_SlotInfoType *info;

	if ((s_initialized == 0u) || (BootMeta_IsSlotValid(slot) == 0u)) {
		return E_NOT_OK;
	}

	info = &s_slotInfo[slot];
	if (info->metaValid == 0u) {
		/* 连 meta 结构都读不出来（全 0xFF / magic 不符），没有"降级"的对象。
		 * 这种槽只能走 boot 的"向量表兜底"路径。 */
		return E_NOT_OK;
	}

	meta = info->meta;
	meta.state = (uint8_t)BOOT_SLOT_TESTING;

	/* @warning **不要在这里把 `bootAttempts` 清零。**（22.3 修的第 1 个缺陷）
	 *
	 * 清零看起来"重新开始计数"很合理，但 boot 每次上电只要镜像 CRC 不符就会
	 * 再调一次本函数：清零 → `PrepareJump` 加到 1 → 上电 → 再清零 → 还是 1。
	 * 计数永远到不了 `BOOT_MAX_BOOT_ATTEMPTS`，于是**永不判 INVALID、永不回滚**，
	 * 板子每次上电都往同一个坏镜像里跳。Host 用例 `test_boot_meta.c` 的 B4
	 * 用 10 轮上电复现了这一点（计数恒为 1）。
	 *
	 * 保留原值才能让"降级照跳"这条开发路径仍然有兜底：镜像真坏时跳进去不返回，
	 * 复位后计数 +1，第 4 次判 INVALID 并回滚到另一个槽。
	 *
	 * 唯一需要清零的是"从 CONFIRMED 降级"这种一次性的情形 —— 而 CONFIRMED 的
	 * `bootAttempts` 本来就是 0（见 `BootMeta_Confirm`），不需要额外处理。 */

	return BootMeta_Write(slot, &meta);
}

Std_ReturnType BootMeta_Register(uint8_t slot, uint32_t imageSize, uint32_t imageCrc,
                                 uint8_t major, uint8_t minor, uint8_t patch)
{
	Boot_MetaType meta;
	uint32_t nextCounter = 1u;
	uint8_t other;

	if (BootMeta_IsSlotValid(slot) == 0u) {
		return E_NOT_OK;
	}
	if ((imageSize < BOOT_PFLASH_PHRASE_SIZE) || (imageSize > BOOT_SLOT_IMAGE_MAX)) {
		return E_NOT_OK;
	}

	/* rollingCounter 取"两个槽的较大值 + 1"，保证：
	 *   1) 单调递增 —— 上次是 5 就不会退回 3（否则 boot 会去启动另一个槽）；
	 *   2) 本槽登记后一定是最新的 —— boot 比较时它最大。
	 *
	 * 踩过的坑：最初写成"另一个槽 + 1"。当本槽 rc=5、另一个槽是空的（rc=0）时，
	 * J-Link 重烧后自注册会把本槽的 rc 从 5 改回 1 —— 计数倒退，
	 * 如果此时另一个槽恰好是 3，boot 就会去启动那个更旧的镜像。 */
	other = (slot == BOOT_SLOT_INDEX_A) ? BOOT_SLOT_INDEX_B : BOOT_SLOT_INDEX_A;
	if (s_initialized != 0u) {
		if (s_slotInfo[slot].metaValid != 0u) {
			nextCounter = s_slotInfo[slot].meta.rollingCounter;
		}
		if ((s_slotInfo[other].metaValid != 0u) &&
		    (s_slotInfo[other].meta.rollingCounter > nextCounter)) {
			nextCounter = s_slotInfo[other].meta.rollingCounter;
		}
	}
	nextCounter++;

	(void)memset(&meta, 0, sizeof(meta));
	meta.rollingCounter     = nextCounter;
	meta.imageSize          = imageSize;
	meta.imageCrc           = imageCrc;
	meta.programmingCounter = 1u;
	meta.versionMajor       = major;
	meta.versionMinor       = minor;
	meta.versionPatch       = patch;
	meta.state              = (uint8_t)BOOT_SLOT_TESTING;
	meta.bootAttempts       = 0u;
	meta.reserved[0]        = 0xFFu;
	meta.reserved[1]        = 0xFFu;

	return BootMeta_Write(slot, &meta);
}
