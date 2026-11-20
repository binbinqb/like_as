#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""通信栈回归基线：一条命令跑完静态检查 + 上板用例，出统一结论。

## 为什么需要它

各验收脚本是**按里程碑**写的，退出码约定不统一（有的失败也返回 0），
一条一条跑既容易漏、也没法在交付前说"基线是绿的"。本脚本只做三件事：

1. 按固定顺序执行用例表；
2. 用"退出码 + 输出里的失败计数"双重判定（**不信任退出码**）；
3. 落盘每例完整日志，打印一张汇总表。

## 两段基线

| 段 | 用例 | 需要硬件 |
|---|---|---|
| 静态 | 邮箱表对账、TX 中断语义、PduR 路由、硬编码守卫、生成门禁、生成物幂等 | 否 |
| 上板 | 全 TX 邮箱覆盖、M3 诊断、M10 Com、M19 CAN1 接收、Com 重试 | 是（Kvaser ch0+ch1、COM2） |

用法：
	python tools/regress_comm.py                # 全跑
	python tools/regress_comm.py --static-only  # 只跑静态段（CI 可用）
	python tools/regress_comm.py --only m3,m10 # 指定用例

@author binbina
"""

import argparse
import io
import os
import re
import subprocess
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = sys.executable
LOG_DIR = os.path.join(ROOT, "build", "regress")

# (键, 说明, 命令, 段, 超时秒)
CASES = [
	("can_table",   "邮箱表/HTH 对账 + TX 中断语义", [PY, "tools/can_table_check.py"], "static", 120),
	("pdu_route",   "PduR 50 条路由静态核对",       [PY, "tools/pdu_route_check.py"], "static", 120),
	("check_pdu",   "PDU 注册一致性",               [PY, "tools/config.py", "check-pdu"], "static", 120),
	("hardcode",    "硬编码守卫（12 项）",          [PY, "tools/hardcode_check.py"], "static", 120),
	("gen_gate",    "生成门禁自测（15 场景）",      [PY, "tools/gen_gate_check.py"], "static", 300),
	("a4_gen",      "生成物幂等（7 项）",           [PY, "tools/a4_gen_check.py"], "static", 300),
	("mux_cfg",     "MUX/ADC 配置规则（26 项）",        [PY, "tools/mux_cfg_check.py"], "static", 120),
	("rte_cfg",     "RTE 端口规则（14 项）",            [PY, "tools/rte_cfg_check.py"], "static", 120),
	("rte_portmap", "换项目：业务不含下层符号 + 变体可编译", [PY, "tools/rte_portmap_check.py"], "static", 180),
	("rte_sched",   "调度表规则 S1~S4 + 变体运行（16 项）",  [PY, "tools/rte_sched_check.py"], "static", 180),
	("can_tx_all",  "全 TX 邮箱覆盖（12 个）",      [PY, "tools/can_tx_all_check.py"], "hw", 120),
	("m3",          "诊断链路（18 项）",            [PY, "tools/m3_check.py"], "hw", 180),
	("m10",         "Com 信号层（22 项）",          [PY, "tools/m10_check.py"], "hw", 180),
	("m19",         "CAN1 接收（34 条）",           [PY, "tools/m19_check.py"], "hw", 240),
	("com_retry",   "Com 发送重试（5 项）",         [PY, "tools/com_retry_check.py"], "hw", 120),
	("led_loop",    "LED 闭环：启动/停止/超时/无效/恢复", [PY, "tools/led_loop_check.py"], "hw", 120),
]

RE_FAIL_CN = re.compile(r"(\d+)\s*项失败")
RE_FAILED = re.compile(r"(\d+)\s*failed")


def verdict(rc, out):
	"""退出码 + 失败计数双重判定。

	@note 本工程的验收脚本退出码不统一：`can_table_check` / `hardcode_check`
	      即使有 FAIL 也返回 0（历史遗留）。只信退出码会把红的说成绿的。
	"""
	if rc != 0:
		return False, "rc=%d" % rc
	if "[FAIL]" in out or "FAIL " in out:
		return False, "输出含 FAIL"
	for m in RE_FAIL_CN.finditer(out):
		if int(m.group(1)):
			return False, "%s 项失败" % m.group(1)
	for m in RE_FAILED.finditer(out):
		if int(m.group(1)):
			return False, "%s failed" % m.group(1)
	return True, "ok"


def jlink_reset():
	"""硬件段开始前复位一次。

	@note 静态段不打开 Kvaser，板子的 Com 仍按 100 ms 发 —— 没有节点 ACK，
	      7 秒足够把 CAN0/CAN1 打进 bus-off，CanSM 会把 PDU 模式置成
	      `TX_OFFLINE`，后续所有上板用例都会"发不出去"。
	      2026-11-18 首版套件就因此让 com_retry 误报 4 项 FAIL。
	"""
	jlink = r"C:\Program Files\SEGGER\JLink\JLink.exe"
	cmd = os.path.join(LOG_DIR, "_reset.cmd")
	with io.open(cmd, "w", encoding="ascii") as f:
		f.write("r\ng\nqc\n")
	try:
		subprocess.run([jlink, "-NoGui", "1", "-device", "CVM0146",
		                "-if", "SWD", "-speed", "4000", "-CommandFile", cmd],
		               capture_output=True, timeout=30, stdin=subprocess.DEVNULL)
		return True
	except Exception:
		return False


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--static-only", action="store_true")
	ap.add_argument("--hw-only", action="store_true")
	ap.add_argument("--no-reset", action="store_true",
	                help="硬件段前不复位（默认会复位，见 jlink_reset 的说明）")
	ap.add_argument("--only", default="", help="逗号分隔的用例键")
	args = ap.parse_args()

	only = [x.strip() for x in args.only.split(",") if x.strip()]
	cases = []
	for c in CASES:
		key, desc, cmd, seg, tmo = c
		if args.static_only and seg != "static":
			continue
		if args.hw_only and seg != "hw":
			continue
		if only and key not in only:
			continue
		cases.append(c)

	stamp = time.strftime("%H%M%S")
	os.makedirs(LOG_DIR, exist_ok=True)
	logdir = os.path.join(LOG_DIR, "run_%s" % stamp)
	os.makedirs(logdir, exist_ok=True)

	print("== 通信栈回归基线（%d 例）==" % len(cases))
	print("   日志目录：%s" % logdir)
	print()

	rows = []
	for key, desc, cmd, seg, tmo in cases:
		if seg == "hw" and not args.no_reset:
			# 每个上板用例前都复位：用例之间的空隙里 Com 仍在发，
			# 没有 ACK 就会把对端打进 bus-off，且 CanSM 可能把 PDU 模式
			# 留在 TX_OFFLINE。一次复位比在用例里做状态修复更确定
			# （实测：只在硬件段前复位一次，com_retry 仍会撞上残留状态）。
			if not jlink_reset():
				print("  [WARN] J-Link 复位失败：%s 可能受残留状态影响" % key)
			else:
				time.sleep(3.0)
		t0 = time.time()
		try:
			p = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True,
			                   timeout=tmo, stdin=subprocess.DEVNULL)
			out = (p.stdout or "") + (p.stderr or "")
			ok, why = verdict(p.returncode, out)
		except subprocess.TimeoutExpired as e:
			out = (e.stdout or "") if isinstance(e.stdout, str) else ""
			ok, why = False, "超时 %ds" % tmo
		dt = time.time() - t0

		path = os.path.join(logdir, "%s.log" % key)
		with io.open(path, "w", encoding="utf-8") as f:
			f.write(out)
		rows.append((key, desc, seg, ok, why, dt, path))
		print("  [%s] %-11s %-28s %5.1fs  %s"
		      % ("PASS" if ok else "FAIL", key, desc, dt,
		         "" if ok else why))

	bad = [r for r in rows if not r[3]]
	print()
	print("== 汇总：%d 例，通过 %d，失败 %d ==" % (len(rows), len(rows) - len(bad), len(bad)))
	if bad:
		for key, desc, seg, ok, why, dt, path in bad:
			print("  FAIL %s（%s）→ %s" % (key, why, path))
	return 1 if bad else 0


if __name__ == "__main__":
	sys.exit(main())
