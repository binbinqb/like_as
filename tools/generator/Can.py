#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    Can.py
@brief   由 `Can/Can.json` 生成 `Can_Cfg.c` 的邮箱表与 HTH 表

@details @section CANPY_WHY 为什么邮箱表必须由配置生成
          手写这张表有两个"不报错、只失效"的坑：

          | 坑 | 手写时的表现 | 生成后 |
          |----|--------------|--------|
          | HTH 的 `mb` 与邮箱表对不上 | `Can_Write` 只校验 ID，**不校验邮箱号** → 发出去的是别人的报文 / 根本发不出 | 生成时强制一致 |
          | 掩码位位置写错 | 某个邮箱变成全收，把后面的段全截走（M14 踩过） | 掩码由 JSON 的语义值给出，且带越界检查 |

          @section CANPY_SCOPE 生成范围
          只生成**数据**，不生成通道配置：
          - `Can_ChannelConfigs` 里有 `context` 指针、`TrcvPinSTB` 引脚、采样点，
            属于板级绑定，且 `context` 是运行期变量 → 继续手写；
          - 波特率已经由 `Board.json` 生成（`BOARD_CANx_BITRATE`）。

@note    输出的是**数值**而不是 `CAN_HW_ID_*` 宏：宏会造成"JSON 一份、头文件一份"
          的双来源。语义名通过行尾注释保留，`Can_HwCfg.h` 的宏仍供调试探针使用，
          一致性由 `tools/can_table_check.py` 校验。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-17 | binbina | 首版：邮箱表 + HTH 表 |
"""

#: 字段默认值 —— 不是"偷懒"，而是这三项在当前工程里是**结构常量**：
#:
#: | 字段 | 默认 | 依据 |
#: |------|------|------|
#: | `len` | 1 | 未启用多帧邮箱（分帧由 CanTp 做，不靠邮箱深度） |
#: | `dlc` | 8 | 经典 CAN，所有报文都是 8 字节 |
#: | `int` | True | **TX 也要开**：TX 完成中断是 CanTp 分段发送的节拍源（`CanAc.c:810`） |
DEFAULT_LEN = 1
DEFAULT_DLC = 8
DEFAULT_INT = True

#: 方向 → C 枚举
DIR_ENUM = {"TX": "CAN_HW_MB_TX", "RX": "CAN_HW_MB_RX"}


def _hex(v, width=None):
	"""数值 → `0x..u`。

	@note `width` 是**右对齐**（不是 ljust）：十六进制位数不齐时，右对齐能让
	      `u` 后缀落在同一列，而且 `0x123` 与 `u` 不会被空格拆开（踩过）。
	"""
	s = "0x%X" % v
	if width:
		s = s.rjust(width)
	return s + "u"


def _field_widths(entries):
	"""算 id / mask 两列的宽度，让生成出来的表像手写的一样对齐。"""
	wid = len(_hex(0))
	for e in entries:
		wid = max(wid, len(_hex(int(e["id"], 0))))
	return wid


def _mask_of(e):
	"""RX 默认全掩码、TX 恒 0（TX 的受控字段被 `Can_Write` 忽略，但仍要填）。"""
	if "mask" in e:
		return int(e["mask"], 0)
	return 0xFFFFFFFF if e["dir"] == "RX" else 0


def _validate(entries, ch):
	"""生成前的结构校验。宁可在这里失败，也不要生成一张"能编过但收不到"的表。"""
	seen = set()
	for e in entries:
		mb = e["mb"]
		if mb in seen:
			raise SystemExit("CAN%d: 邮箱号 %d 重复" % (ch, mb))
		seen.add(mb)

		if mb > 63:
			# CVM0146 的 FlexCAN 每个控制器 64 个邮箱（MCR[MAXMB] 编码是 n-1）
			raise SystemExit("CAN%d: 邮箱号 %d 超出 0..63" % (ch, mb))

		cid = int(e["id"], 0)
		if e["ext"]:
			if cid > 0x1FFFFFFF:
				raise SystemExit("CAN%d mb%d: 扩展帧 ID 0x%X 越界" % (ch, mb, cid))
		else:
			if cid > 0x7FF:
				raise SystemExit("CAN%d mb%d: 标准帧 ID 0x%X > 0x7FF（扩展帧要写 ext=true）"
				                 % (ch, mb, cid))

		if e["dir"] == "TX" and "hth" not in e:
			raise SystemExit("CAN%d mb%d: TX 邮箱没有 hth 编号" % (ch, mb))
		if e["dir"] == "RX" and "hth" in e:
			raise SystemExit("CAN%d mb%d: RX 邮箱不该有 hth" % (ch, mb))

		mask = _mask_of(e)
		if e["dir"] == "TX" and mask != 0:
			raise SystemExit("CAN%d mb%d: TX 邮箱的掩码必须是 0" % (ch, mb))
		if e["dir"] == "RX" and (mask & ~0x1FFFFFFF) and not e["ext"]:
			# 标准帧只看低 11 位；给 0xFFFFFFFF 是合法写法（"完全一致"）
			pass


def gen_mailbox_table(cfg, ch):
	"""生成一个通道的 `static const CanHw_MsgCfgType CanHw_MsgCfgs<ch>[] = {...};`"""
	channel = None
	for c in cfg["channels"]:
		if c["index"] == ch:
			channel = c
			break
	if channel is None:
		raise SystemExit("Can.json 缺少 channels[%d]" % ch)

	entries = channel["mailboxes"]
	_validate(entries, ch)
	wid = _field_widths(entries)

	lines = []
	lines.append("static const CanHw_MsgCfgType CanHw_MsgCfgs%u[] = {" % ch)
	for e in entries:
		dlc = e.get("dlc", DEFAULT_DLC)
		ln = e.get("len", DEFAULT_LEN)
		it = "true" if e.get("int", DEFAULT_INT) else "false"
		mask = _mask_of(e)
		note = e.get("note")

		if note:
			lines.append("\t/* %s */" % note)

		lines.append(
			"\t{ %2uu, %uu, %s, %-5s, %-12s, %uu, %-5s, %s },   /**< mb%-2u %-12s %s 0x%X */"
			% (e["mb"], ln, _hex(int(e["id"], 0), wid),
			   "true" if e["ext"] else "false",
			   DIR_ENUM[e["dir"]], dlc, it, _hex(mask, wid),
			   e["mb"], e.get("name", ""), e["dir"], int(e["id"], 0)))
	lines.append("};")
	return "\n".join(lines), len(entries)


def gen_hth_table(cfg):
	"""生成 `const CanHw_HohType CanHw_Hohs[CAN_HW_HOH_NUM] = {...};`

	@note HTH 编号是 `CanIf_Cfg.c` 的 `hoh` 字段引用的**外部契约**，
	      所以按 `hth` 显式排序，不按通道/邮箱顺序自动分配。
	"""
	rows = []
	for c in cfg["channels"]:
		for e in c["mailboxes"]:
			if e["dir"] == "TX":
				rows.append({
					"hth": e["hth"], "controller": c["index"], "mb": e["mb"],
					"id": int(e["id"], 0), "dlc": e.get("dlc", DEFAULT_DLC),
					"name": e.get("name", ""),
				})

	rows.sort(key=lambda r: r["hth"])
	if [r["hth"] for r in rows] != list(range(len(rows))):
		raise SystemExit("hth 编号必须是 0..N-1 连续：%s" % [r["hth"] for r in rows])

	# HTH 与邮箱的对应关系必须一致，否则 Can_Write 会拿错邮箱发错 ID
	for r in rows:
		for c in cfg["channels"]:
			if c["index"] != r["controller"]:
				continue
			hit = [e for e in c["mailboxes"] if e["mb"] == r["mb"] and e["dir"] == "TX"]
			if len(hit) != 1:
				raise SystemExit("HTH%d 指向 CAN%d mb%d，但表里没有唯一的 TX 邮箱"
				                 % (r["hth"], r["controller"], r["mb"]))

	wid = max(len(_hex(r["id"])) for r in rows) if rows else 4
	lines = ["const CanHw_HohType CanHw_Hohs[CAN_HW_HOH_NUM] = {"]
	for r in rows:
		lines.append(
			"\t{ %uu, %2uu, %s, %uu },   /**< HTH%-2u CAN%u mb%-2u %-12s 0x%X */"
			% (r["controller"], r["mb"], _hex(r["id"], wid), r["dlc"],
			   r["hth"], r["controller"], r["mb"], r["name"], r["id"]))
	lines.append("};")
	return "\n".join(lines), len(rows)


def gen_all(cfg):
	"""返回三块 C 代码与统计信息（供 `sync_can.py` 注入）。"""
	blocks = {}
	stats = {}
	for ch in range(len(cfg["channels"])):
		code, n = gen_mailbox_table(cfg, ch)
		blocks["CAN%u mailboxes" % ch] = code
		stats["CAN%u" % ch] = n
	code, n = gen_hth_table(cfg)
	blocks["HTH table"] = code
	stats["HTH"] = n
	return blocks, stats
