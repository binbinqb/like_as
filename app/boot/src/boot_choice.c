/**
 * @file    boot_choice.c
 * @brief   选槽判定：按 meta + 镜像校验决定跳哪一槽（开发/量产两套策略）
 *
 * @details @section CHOICE_FLOW 判定顺序
 *
 *          @code
 *          slot = GetActiveSlot()          跳过 EMPTY / INVALID，取 counter 最大者
 *          ├─ 有活动槽
 *          │   ├─ CheckImage(OK)          → 跳它
 *          │   ├─ 失败 + 开发模式          → DemoteToTesting(保留计数) → 跳它
 *          │   │                             （计数兜底：真跑不起来，第 4 次判 INVALID 回滚）
 *          │   ├─ 失败 + 量产模式          → 判 INVALID → 看另一槽
 *          │   └─ 另一槽也失败             → 开发可看向量表兜底；量产直接等刷写
 *          └─ 无活动槽                     → 同上（开发兜底 / 量产等刷写）
 *          PrepareJump(chosen)             TESTING 累加计数，超限 → 回滚另一槽
 *          @endcode
 *
 *          @section CHOICE_PROD 量产与开发的差别（`BOOT_MODE_PRODUCTION`）
 *
 *          | 情形 | 开发（默认） | 量产 |
 *          |------|--------------|------|
 *          | meta 完好、镜像 CRC 不符 | 降级 TESTING 后照跳 | **判 INVALID，回滚** |
 *          | 没有有效 meta、向量表像话 | 跳（首次烧写路径） | **不跳，停 UDS** |
 *
 *          开发模式保留前两种宽松路径的唯一理由：J-Link 直接重烧 app 后，
 *          槽尾 meta 还是旧 CRC，此时若拒绝启动就形成"烧完能跑一次、
 *          一复位就停住"的死锁 —— 而能修正 meta 的 app 根本没机会跑。
 *
 * @warning `BootMeta_DemoteToTesting()` **不能**清零尝试次数，否则每次上电都
 *          走一遍降级、计数恒为 1，永不回滚（22.3 修的 D1，见该函数注释）。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 从 main.c 抽出；加量产策略与 INVALID 落盘 |
 */

#include "boot_choice.h"
#include "boot_meta.h"
#include "platform_cvm0146.h"

/* ============================ [ 内部函数 ] ============================ */

#if BOOT_ALLOW_VECTOR_FALLBACK
/**
 * @brief 看向量表"像不像一个镜像"（只看初始 SP 与 Reset_Handler）
 *
 * @details 这是**首次烧写**的兜底判据：J-Link 只烧了 boot + app 两个 ELF，
 *          槽尾 meta 还是 0xFF，此时没有任何 CRC 可比。
 *
 * @warning 它**不验证镜像完整性**。量产模式下这条路径被
 *          `BOOT_ALLOW_VECTOR_FALLBACK` 关掉（见 `boot_flash_map.h`）。
 *
 * @param[in] base 槽基址
 * @retval 1 像
 * @retval 0 不像
 */
static uint8_t Boot_LooksLikeImage(uint32_t base)
{
	uint32_t sp;
	uint32_t pc;
	uint32_t entry;

	Platform_FlashRead(base, &sp, 4u);
	Platform_FlashRead(base + 4u, &pc, 4u);

	/* SP：SRAM_L(0x1FFF0000) ~ StackTop(0x2000F000)，且 8 字节对齐 */
	if ((sp < 0x1FFF0000u) || (sp > 0x2000F000u) || ((sp & 0x7u) != 0u)) {
		return 0u;
	}

	/* PC：Thumb 模式下最低位是 1，比对地址前先清掉 */
	entry = pc & ~1u;
	if ((entry < base) || (entry >= (base + BOOT_SLOT_IMAGE_MAX))) {
		return 0u;
	}

	return 1u;
}
#endif /* BOOT_ALLOW_VECTOR_FALLBACK */

#if !BOOT_ALLOW_STALE_META
/**
 * @brief 把某个槽判为 INVALID 并落盘（量产：镜像不可信就别再选它）
 *
 * @note 只在量产模式下存在：开发模式走"降级 TESTING 照跳"，不需要判死。
 *
 * @param[in] slot 槽索引
 */
static void Boot_InvalidateSlot(uint8_t slot)
{
	const Boot_SlotInfoType *info = BootMeta_GetSlot(slot);
	Boot_MetaType meta;

	if ((info == NULL) || (info->metaValid == 0u)) {
		return;
	}

	meta = info->meta;
	meta.state        = (uint8_t)BOOT_SLOT_INVALID;
	meta.bootAttempts = 0u;

	(void)BootMeta_Write(slot, &meta);
}
#endif /* !BOOT_ALLOW_STALE_META */

/**
 * @brief 打印某槽镜像的调试信息（SP / PC / 实测 CRC / meta 期望 CRC）
 *
 * @param[in] slot 槽索引
 */
static void Boot_DebugImage(uint8_t slot)
{
	const Boot_SlotInfoType *info = BootMeta_GetSlot(slot);
	uint32_t base;
	uint32_t sp;
	uint32_t pc;
	uint32_t crc;

	if ((info == NULL) || (info->metaValid == 0u)) {
		return;
	}

	base = BOOT_SLOT_BASE(slot);
	Platform_FlashRead(base, &sp, 4u);
	Platform_FlashRead(base + 4u, &pc, 4u);
	/* 与 `BootMeta_CheckImage()` 用同一份算法，避免"打印说对、校验说错" */
	crc = BootMeta_CalcImageCrc(base, info->meta.imageSize);

	Platform_Printf("[boot] dbg slot %c: sp=%08X pc=%08X size=%u crc=%08X expect=%08X\n",
	                (slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B',
	                (unsigned)sp, (unsigned)pc,
	                (unsigned)info->meta.imageSize,
	                (unsigned)crc, (unsigned)info->meta.imageCrc);
}

/**
 * @brief 主槽不可用时的候选：另一个槽
 *
 * @details 先用完整校验；校验不过再按模式决定要不要看向量表。
 *
 * @param[in] badSlot 已经确定不可用的槽
 * @return 可跳的槽号，或 `BOOT_NO_ACTIVE_SLOT`
 */
static uint8_t Boot_TryOtherSlot(uint8_t badSlot)
{
	uint8_t other = (badSlot == BOOT_SLOT_INDEX_A) ? BOOT_SLOT_INDEX_B : BOOT_SLOT_INDEX_A;

	Platform_Printf("[boot] slot %c unusable, try slot %c\n",
	                (badSlot == BOOT_SLOT_INDEX_A) ? 'A' : 'B',
	                (other == BOOT_SLOT_INDEX_A) ? 'A' : 'B');

	if (BootMeta_CheckImage(other) == E_OK) {
		return other;
	}

#if BOOT_ALLOW_VECTOR_FALLBACK
	if (Boot_LooksLikeImage(BOOT_SLOT_BASE(other)) != 0u) {
		/* 另一个槽也没有可用 meta，但向量表像话 —— 首次烧写路径 */
		return other;
	}
#else
	Platform_Puts("[boot] vector fallback disabled (production build)\n");
#endif

	return BOOT_NO_ACTIVE_SLOT;
}

/* ============================ [ 对外接口 ] ============================ */

Boot_ChoiceType Boot_ChooseSlot(void)
{
	Boot_ChoiceType choice;
	uint8_t slot;
	uint8_t chosen = BOOT_NO_ACTIVE_SLOT;

	choice.decision = BOOT_DECISION_WAIT_FLASH;
	choice.slot     = BOOT_NO_ACTIVE_SLOT;

	/* ---- 第一步：按 meta 选活动槽 ---- */
	slot = BootMeta_GetActiveSlot();

	if (slot != BOOT_NO_ACTIVE_SLOT) {
		Platform_Printf("[boot] active slot : %c (rolling counter)\n",
		                (slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B');

		Boot_DebugImage(slot);

		/* ---- 第二步：校验镜像 ---- */
		if (BootMeta_CheckImage(slot) == E_OK) {
			chosen = slot;
		} else {
#if BOOT_ALLOW_STALE_META
			/* 开发模式：meta 完好但镜像对不上 —— 最常见的原因是"用 J-Link 重烧了
			 * app，但槽尾 meta 还是旧镜像的 CRC"。此时**不能直接判死**：
			 * 那会形成"烧完能跑一次、一复位就 HALT"的死锁，因为唯一能修正
			 * meta 的 app 根本没机会启动。
			 *
			 * 降级成 TESTING 再跳，两种结局都安全：
			 *   - app 起来了 → 它按当前镜像重写 meta；
			 *   - app 起不来 → 复位后尝试次数累加，第 4 次判 INVALID 并回滚。
			 *     （前提是 DemoteToTesting 不清零计数，见 22.3 的 D1） */
			if (BootMeta_DemoteToTesting(slot) == E_OK) {
				Platform_Printf("[boot] slot %c check failed, "
				                "boot anyway as TESTING (meta may be stale)\n",
				                (slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B');
				chosen = slot;
			} else {
				chosen = Boot_TryOtherSlot(slot);
			}
#else
			/* 量产模式：**不执行未经验证的镜像**。
			 * 先把这个槽判死（否则下次上电又会选它），再看另一个槽。 */
			Platform_Printf("[boot] slot %c image rejected (production build)\n",
			                (slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B');
			Boot_InvalidateSlot(slot);
			chosen = Boot_TryOtherSlot(slot);
#endif
		}
	} else {
#if BOOT_ALLOW_VECTOR_FALLBACK
		/* ---- 首次烧写：没有任何有效 meta，靠向量表兜底 ---- */
		Platform_Puts("[boot] no valid meta, fallback to vector table probe\n");

		if (Boot_LooksLikeImage(BOOT_SLOT_A_BASE) != 0u) {
			chosen = BOOT_SLOT_INDEX_A;
		} else if (Boot_LooksLikeImage(BOOT_SLOT_B_BASE) != 0u) {
			chosen = BOOT_SLOT_INDEX_B;
		}
#else
		Platform_Puts("[boot] no valid meta, vector fallback disabled "
		              "(production build) -> wait for flash\n");
#endif
	}

	if (chosen == BOOT_NO_ACTIVE_SLOT) {
		return choice;                       /* WAIT_FLASH */
	}

	/* ---- 第三步：跳转前的尝试计数（回滚触发点） ---- */
	if (BootMeta_PrepareJump(chosen) != E_OK) {
		uint8_t other = (chosen == BOOT_SLOT_INDEX_A) ? BOOT_SLOT_INDEX_B : BOOT_SLOT_INDEX_A;

		Platform_Printf("[boot] slot %c exceeded boot attempts, rollback to slot %c\n",
		                (chosen == BOOT_SLOT_INDEX_A) ? 'A' : 'B',
		                (other == BOOT_SLOT_INDEX_A) ? 'A' : 'B');

		if (BootMeta_CheckImage(other) != E_OK) {
			/* 回滚目标也坏了 —— 进 UDS，让诊断仪能救回来 */
			return choice;                   /* WAIT_FLASH */
		}
		chosen = other;
	}

	choice.decision = BOOT_DECISION_JUMP;
	choice.slot     = chosen;
	return choice;
}
