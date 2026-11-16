# -*- coding: utf-8 -*-
"""统计 CAN1 TX/RX 报文的信号构成（一次性分析脚本，M23 设计依据）

@details 输出三样东西：
         1. TX 报文里 2-bit 状态枚举信号的数量与取值词表
         2. 全矩阵里"同一语义、不同写法"的词表分布
         3. TX 信号里哪些**没有**枚举表（占位不明，无法翻译）

@author binbina
"""

import io
import re
import sys
from collections import Counter, defaultdict

DBC = "app/platform/cvm0146/src/config/dbc/can1.dbc"


def load(path):
	txt = io.open(path, encoding="utf-8", errors="replace").read()

	# VAL_ 在 DBC 里是**集中放在文件末尾**的，不跟在 BO_ 后面。
	# 按 BO_ 切块会把所有 VAL_ 都归到最后一条报文上（实测因此把 56 个
	# TX 信号的枚举表全判成"缺失"，差点得出反向结论）。
	# 所以必须先全局收集，再按 msg_id 回填。
	val_by_id = defaultdict(dict)
	for vm in re.finditer(r"(?m)^VAL_ (\d+) (\S+) (.*);", txt):
		mid = int(vm.group(1)) & 0x1FFFFFFF
		pairs = re.findall(r'(\d+)\s+"([^"]*)"', vm.group(3))
		val_by_id[mid][vm.group(2)] = [(int(v), lab) for v, lab in pairs]

	# 按 BO_ 切块，每块含该报文的所有 SG_
	blocks = re.split(r"(?m)^(?=BO_ )", txt)
	out = []
	for b in blocks:
		m = re.match(r"BO_ (\d+) (\S+):\s*(\d+)\s+(\S+)", b)
		if not m:
			continue
		mid = int(m.group(1)) & 0x1FFFFFFF
		sigs = []
		for sg in re.finditer(
				r"(?m)^\s+SG_ (\S+)\s*:\s*(\d+)\|(\d+)@([01])([+-])", b):
			sigs.append({
				"name": sg.group(1),
				"start": int(sg.group(2)),
				"size": int(sg.group(3)),
				"le": sg.group(4) == "1",
				"sign": sg.group(5),
			})
		out.append({
			"id": mid, "name": m.group(2), "dlc": int(m.group(3)),
			"node": m.group(4), "sigs": sigs,
			"vals": val_by_id.get(mid, {}),
		})
	return out


def main():
	msgs = load(DBC)
	tx = [m for m in msgs if m["node"] == "BCM"]
	rx = [m for m in msgs if m["node"] != "BCM"]
	nsig = sum(len(m["sigs"]) for m in msgs)

	print("=" * 78)
	print("CAN1：%d 条报文 / %d 个信号（TX %d 条 / RX %d 条）"
	      % (len(msgs), nsig, len(tx), len(rx)))
	print("=" * 78)

	print("\n--- TX 报文逐条 ---")
	for m in tx:
		n2 = sum(1 for s in m["sigs"] if s["size"] == 2)
		nov = sum(1 for s in m["sigs"] if s["name"] not in m["vals"])
		print("  %-16s 0x%08X  sigs=%-3d 2bit=%-3d 无枚举=%-3d"
		      % (m["name"], m["id"], len(m["sigs"]), n2, nov))

	print("\n--- TX 的 2-bit 状态信号明细（前 20 条）---")
	cnt = 0
	for m in tx:
		for s in m["sigs"]:
			if s["size"] != 2:
				continue
			labs = m["vals"].get(s["name"])
			if labs is None:
				desc = "（无枚举表）"
			else:
				desc = " | ".join("%d=%s" % (v, l) for v, l in labs)
			print("  %-12s %-30s %s" % (m["name"], s["name"], desc))
			cnt += 1
			if cnt >= 20:
				break
		if cnt >= 20:
			break

	# 同一语义、不同写法：归一化后统计"一义多词"
	print("\n--- 词表分布（全矩阵 %d 个 VAL_ 表）---"
	      % sum(len(m["vals"]) for m in msgs))
	vocab = Counter()
	for m in msgs:
		for sn, labs in m["vals"].items():
			vocab[tuple(l for _, l in labs)] += 1
	print("  不同词表数：%d" % len(vocab))
	for v, n in vocab.most_common(10):
		print("    %3d 条  %s" % (n, " / ".join(v)))

	# "on/fault/invalid" 这组语义的写法有几种
	print("\n--- 同一语义的写法分歧（2-bit 状态）---")
	groups = defaultdict(list)
	for m in msgs:
		for sn, labs in m["vals"].items():
			if len(labs) != 4:
				continue
			key = tuple(l.strip().lower() for _, l in labs)
			groups[key].append("%s.%s" % (m["name"], sn))
	for key, users in sorted(groups.items(), key=lambda x: -len(x[1])):
		print("  %-46s x%-3d  例：%s"
		      % (" / ".join(key), len(users), users[0]))


if __name__ == "__main__":
	sys.exit(main())
