/**
 * @file    bootfault_cmd.c
 * @brief   `bootfault` 命令：把当前槽的 meta 做成"陈旧/丢失"，用于验证 Boot 的降级与回滚
 *
 * @details @section BF_WHY 为什么需要这条命令
 *
 *          22.3 要验证的是"镜像校验失败之后会怎样"。这个状态**没法用 UDS 造出来**：
 *
 *          | 服务 | 限制 | 后果 |
 *          |------|------|------|
 *          | `0x31` 擦除 | 只接受槽基址，且拒绝活动槽 | 擦不到正在跑的那一槽 |
 *          | `0x34` 下载 | 同上 | 写不到镜像中间某个字节 |
 *          | `0x37` 收尾 | CRC 从 Flash **回读**算 | meta 永远与镜像自洽 |
 *
 *          最后一条是决定性的：经 UDS 刷进去的镜像，meta 里的 CRC 必然是它自己的，
 *          "meta 有效但镜像 CRC 不符"这个状态在 UDS 路径上根本到不了。
 *          而它恰恰是 J-Link 直烧 app、或 Flash 位翻转之后 Boot 会看到的现场。
 *
 *          所以用一条**只在开发构建里存在**的串口命令直接把 meta 做坏。
 *
 *          @section BF_SAFE 为什么这样改是安全的
 *
 *          只改 meta（`imageCrc` / 整条 meta），**不动镜像本身**：
 *            - 开发构建：Boot 会降级成 TESTING 照跳，镜像其实是好的 → 板子照常跑；
 *              连续复位 4 次后该槽判 INVALID 并回滚到另一槽 —— 这正是要观察的行为。
 *            - 量产构建：这条命令根本不存在（`BOOT_MODE_PRODUCTION` 编译期剔除）。
 *
 *          @warning 不要在这里加"改镜像一个字节"的功能。那会让下一次启动
 *          必然跑飞，而恢复只能靠 J-Link —— 验证成本远高于收益。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版：meta-crc / meta-blank |
 */

#if !defined(SH_DISABLE_CMD_BOOTFAULT) && !defined(BOOT_MODE_PRODUCTION)

#include <string.h>

#include "sh_cfg.h"
#include "platform_cvm0146.h"
#include "boot_meta.h"
#include "boot_flash_map.h"

/**
 * @brief 把活动槽的 `imageCrc` 改坏（镜像本身不动）
 *
 * @details 制造出的现场：meta 结构完好、`imageCrc` 与槽内镜像不符 —— 等价于
 *          "用 J-Link 重烧了 app，槽尾 meta 还是旧镜像的 CRC"。
 *
 * @return 0 成功；-1 没有活动槽
 */
static int bf_meta_crc(void)
{
	uint8_t slot = BootMeta_GetActiveSlot();
	const Boot_SlotInfoType *info;
	Boot_MetaType meta;
	uint32_t oldCrc;

	if (slot == BOOT_NO_ACTIVE_SLOT) {
		sh_print("<+1, no active slot (nothing to corrupt)\r\n");
		return -1;
	}

	info = BootMeta_GetSlot(slot);
	if ((info == NULL) || (info->metaValid == 0u)) {
		sh_print("<+1, slot %c has no valid meta\r\n",
		         (slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B');
		return -1;
	}

	/* ⚠ 旧值必须在 Write **之前**存下来。
	 * `BootMeta_Write()` 会同步更新内部缓存 `s_slotInfo[slot].meta`，
	 * 而 `info` 正指向那块缓存 —— 写完之后 `info->meta.imageCrc` 已经是新值，
	 * 拿它当 "was" 打印就会出现 "0x222566B1 (was 0x222566B1)" 这种自欺欺人的输出。
	 * （2026-11-17 上板时被日志抓出来的。） */
	oldCrc = info->meta.imageCrc;
	meta = info->meta;
	meta.imageCrc ^= 0xFFFFFFFFu;      /* 一定对不上，且不依赖原值 */

	if (BootMeta_Write(slot, &meta) != E_OK) {
		sh_print("<+1, write meta failed\r\n");
		return -1;
	}

	sh_print("<+0, slot %c meta.imageCrc=0x%08X (was 0x%08X); reset to observe\r\n",
	         (slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B',
	         (unsigned)meta.imageCrc, (unsigned)oldCrc);
	return 0;
}

/**
 * @brief 把两个槽的 meta 都抹成 0xFF（模拟"从没烧写过"）
 *
 * @details 开发构建下 Boot 会走向量表兜底（能启动）；量产构建下会停在 UDS。
 *          用来验证这两条策略的差别。
 *
 * @return 0
 */
static int bf_meta_blank(void)
{
	uint8_t slot;

	for (slot = 0u; slot < BOOT_SLOT_NUM; slot++) {
		(void)Platform_FlashEraseSector(BOOT_SLOT_META_PRIMARY(slot));
		(void)Platform_FlashEraseSector(BOOT_SLOT_META_BACKUP(slot));
	}

	sh_print("<+0, both slots' meta erased; reset to observe "
	         "(dev: vector fallback / prod: wait for flash)\r\n");
	return 0;
}

/** @brief 十进制解析（不用 `strtoul`：它会拉进 newlib 的 locale 数据，实测 +1 KB） */
static uint32_t bf_dec(const char *s)
{
	uint32_t v = 0u;

	while ((*s >= '0') && (*s <= '9')) {
		v = (v * 10u) + (uint32_t)(*s - '0');
		s++;
	}
	return v;
}

/**
 * @brief 把活动槽置为 TESTING 并直接设定"已启动失败次数"
 *
 * @details @section BF_TESTING 为什么需要它
 *
 *          只靠 `meta-crc` 验不到"计数累加 → 判 INVALID → 回滚"：
 *          CRC 改坏之后，App 只要还能起来，就会在启动自检里发现
 *          `imageSize/imageCrc` 与 meta 不符并**重写 meta**（`BootApp_Init` 的
 *          self-register），计数随之清零。于是每次上电都是"降级一次、修好一次"，
 *          永远累加不到阈值 —— 除非镜像真的坏到起不来（那就要靠另一槽兜底，
 *          成本高且不好反复做）。
 *
 *          这条命令直接把"已经连续失败 N 次"这个状态摆出来：下一轮上电
 *          `PrepareJump` 累加到 N+1，超过 3 就判 INVALID 并回滚。
 *          镜像本身是好的，所以**最坏结果只是回滚到另一槽**，不会变砖。
 *
 * @param[in] attempts 要设定的已失败次数（0~255）
 * @return 0 成功
 */
static int bf_testing(uint32_t attempts)
{
	uint8_t slot = BootMeta_GetActiveSlot();
	const Boot_SlotInfoType *info;
	Boot_MetaType meta;

	if (slot == BOOT_NO_ACTIVE_SLOT) {
		sh_print("<+1, no active slot\r\n");
		return -1;
	}

	info = BootMeta_GetSlot(slot);
	if ((info == NULL) || (info->metaValid == 0u)) {
		sh_print("<+1, slot %c has no valid meta\r\n",
		         (slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B');
		return -1;
	}

	if (attempts > 0xFFu) {
		attempts = 0xFFu;
	}

	meta = info->meta;
	meta.state        = (uint8_t)BOOT_SLOT_TESTING;
	meta.bootAttempts = (uint8_t)attempts;

	if (BootMeta_Write(slot, &meta) != E_OK) {
		sh_print("<+1, write meta failed\r\n");
		return -1;
	}

	sh_print("<+0, slot %c TESTING attempts=%u; reset -> next boot will be %u "
	         "(>3 => INVALID + rollback)\r\n",
	         (slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B',
	         (unsigned)attempts, (unsigned)(attempts + 1u));
	return 0;
}

/**
 * @brief bootfault —— 制造 Boot 启动判定的故障现场
 * @param[in] argc 参数个数（1 = 打印用法）
 * @param[in] argv 参数数组：`meta-crc` | `meta-blank` | `testing <n>`
 * @return 0 成功
 */
static int sh_cmd_bootfault(int argc, char *argv[])
{
	if (argc < 2) {
		sh_print("usage: bootfault <meta-crc|meta-blank|testing N>\r\n");
		sh_print("  meta-crc    : active slot's meta.imageCrc ^= 0xFFFFFFFF (image untouched)\r\n");
		sh_print("  meta-blank  : erase both slots' meta (simulate never-programmed)\r\n");
		sh_print("  testing N   : active slot -> TESTING with bootAttempts=N\r\n");
		sh_print("                (N=3 -> next boot hits the 3-attempt limit)\r\n");
		sh_print("  dev build only; reset the board to observe boot decision\r\n");
		return SH_OK;
	}

	if (strcmp(argv[1], "meta-crc") == 0) {
		(void)bf_meta_crc();
	} else if (strcmp(argv[1], "meta-blank") == 0) {
		(void)bf_meta_blank();
	} else if (strcmp(argv[1], "testing") == 0) {
		if (argc < 3) {
			sh_print("<+1, usage: bootfault testing <n>\r\n");
		} else {
			(void)bf_testing(bf_dec(argv[2]));
		}
	} else {
		sh_print("<+1, unknown action '%s'\r\n", argv[1]);
	}

	return SH_OK;
}

SH_EXPORT_CMD(bootfault, sh_cmd_bootfault,
              "dev only: corrupt boot meta to test fallback/rollback");

#endif /* !SH_DISABLE_CMD_BOOTFAULT && !BOOT_MODE_PRODUCTION */
