#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    roadmap_build.py
@brief   生成 like_as 开发手册 V2.0（JSON 为源，HTML 为产物）

@details @section ROADMAP_WHY 为什么把 HTML 拆成「JSON 源 + 渲染器」
         V1.0 的 HTML 把 109 条任务直接写在 `<script>` 里，改一条任务要动
         一大段 JS 字面量，diff 不可读，也没法被脚本校验。V2.0 改成：

             doc/开发规划/roadmap.json      唯一事实源（可 diff、可校验）
             tools/roadmap_build.py         渲染器（本文件）
             doc/开发规划/like_as_roadmap_v2.html   产物（自动生成，勿手改）

         任务状态用五态而不是勾选：PASS / PARTIAL / TODO / BLOCKED / SKIP。
         勾选表达不了"做了什么但没做完"，也表达不了"被外部条件挡住"，
         这两类恰恰是最容易在交接时丢失的信息。

@note    用法：
             python tools/roadmap_build.py --import   # 从 V1 HTML 导入并应用修订
             python tools/roadmap_build.py            # 由 JSON 渲染 HTML

@author  binbina
@version V2.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V2.0.0 | 2026-11-17 | binbina | 首版：五态、依赖图、开发顺序、决策记录、当前任务 |
"""

import io
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
# 看板落在 doc/ 下、沿用**原来的文件名**：用户的书签和习惯路径不变，
# 升级的是内容（五态、依赖、决策、当前任务），不是位置。
OUT_DIR = os.path.join(ROOT, "doc")
JSON_PATH = os.path.join(OUT_DIR, "roadmap.json")
HTML_PATH = os.path.join(OUT_DIR, "like_as_development_roadmap.html")
SRC_HTML = r"G:/download/like_as_development_roadmap.html"

# 五态：顺序即看板展示顺序，键名同时作为 CSS 类名
STATES = [
	("PASS", "已实现，有验收证据"),
	("PARTIAL", "部分完成，仍有未验收内容"),
	("TODO", "尚未完成"),
	("BLOCKED", "被硬件 / 其他任务 / 决策挡住"),
	("SKIP", "当前条件无法验证（须记录原因）"),
]

# 每条证据都必须能追到一个可重跑的脚本或一次上板记录。
# 没有证据的 PASS 一律降级为 PARTIAL —— 这是 V1 的规则，V2 继续执行。
EVIDENCE = {
	("工程基线", 1): ("PASS", "a1_sched_check.py 0 FAIL；S3 实测 5.046 s（修复前 2.547 s）"),
	("工程基线", 2): ("PARTIAL", "rx_mon 到达时刻为单写者；PerfMon 读改写未加临界区，最坏保护时间未测"),
	("工程基线", 3): ("PARTIAL", "App 构建与 M/A 回归通过；AppB / Boot 本轮未复验"),
	("Can / CanAc", 3): ("PASS", "can_restart_check.py S5/S6：无 ACK 时 CAN_BUSY、bus-off 后占用释放"),
	("CanIf", 0): ("PASS", "can_restart_check.py 9/9；IF-01 已修（NULL 返回错误、合法指针可读）"),
	("CanTp", 0): ("PASS", "A1 发现 CanTp_ReSend 从未被调度并注册；S3 超时恢复标称值"),
	("Com", 4): ("PASS", "a2_validity_check.py 19/19；四态判定顺序 NEVER→TIMEOUT→INVALID→VALID"),
	("Com", 0): ("PASS", "dbc_init_check.py 12/12：初值字段、跨报文同名信号、冲突拒绝；超时按 timeout_factor×CycleTime"),
	("RTE / BcmSig", 3): ("PARTIAL", "BcmBiz 已不依赖 MCU 头（改 include platform.h），仍直接调 BcmSig、未走 RTE 端口"),
	("Shell / 调试监控", 2): ("PASS", "perf_mon / stack_mon：稳态迟到 0.4 µs、单拍 1.5 ms、栈 32.5%"),
	("PC-SIL / 自动测试", 0): ("PASS", "tools/host_build.py：MinGW-w64 16.2，14/14；同一份 bcm_sig/bcm_biz 源码"),
	("PC-SIL / 自动测试", 3): ("PASS", "a6_budget.py 6/6：Flash 52.1% / SRAM 13.1% / 栈 32.5% / 迟到 0.4 µs"),
}

# 需要显式标注挡住原因的任务：(模块名, 下标) -> 说明
BLOCKED = {
	("Can / CanAc", 2): "第三路 CAN 需硬件确认（芯片有 CAN0/1/2，当前配置只声明 2 路）",
	("IoHwAb / DIN / AIN", 2): "RS2260 / TCA9539 通道表未定，需原理图与器件手册",
	("Dcm", 2): "0x27 真算法属客户资产，需 OEM 安全方案与种子随机源定义",
	("Dem / Det", 1): "事件→DTC 映射需 OEM 诊断规范；infras 现把 DTC 码写死为 C00100",
}

# 任务级修订：文本、拆分、提前。键 =(模块名, V1 下标)
TASK_EDITS = {
	("配置工具 / Generator", 6): [
		{"text": "生成幂等性", "check": "两次生成逐字节一致", "state": "PASS",
		 "evidence": "a4_gen_check.py C1/C2/C3：去 wall-clock 时间戳后幂等"},
		{"text": "SCons 自动生成集成", "check": "配置改动触发重编，无需手工跑生成器", "state": "TODO",
		 "evidence": "当前由人工调 Generate()；SCons 未挂生成步骤"},
	],
	("Can / CanAc", 2): [
		{"text": "第三路 CAN", "check": "各通道独立、DLC 正确", "state": "BLOCKED",
		 "evidence": "芯片有 CAN0/1/2（CVM014x.h:352），配置 CAN_CFG_NUM_CHANNELS=2"},
		{"text": "CAN FD（若启用）", "check": "FD 长度与兼容性", "state": "BLOCKED",
		 "evidence": "项目矩阵未声明 FD 需求，未排期"},
	],
	("RTE / BcmSig", 2): [
		{"text": "明确为**新建最小 RTE 运行时**（生成器已有 Rte.py，运行时 Rte.h 是空壳）",
		 "check": "生成接口与绑定可重复，运行时能编译链接", "state": "TODO",
		 "evidence": "tools/generator/Rte.py 存在；infras/include/Rte.h 仅 include guard"},
	],
	("AB Bootloader / FlashTool", 2): [
		{"text": "复位恢复", "check": "运行中复位后可正常启动", "state": "TODO", "evidence": ""},
		{"text": "失败启动恢复", "check": "镜像校验失败进入回滚", "state": "TODO", "evidence": ""},
		{"text": "擦写中断电测试", "check": "掉电点注入后不越界且可恢复", "state": "SKIP",
		 "evidence": "缺少程控电源；A5/A8 同一结论"},
	],
	("Shell / 调试监控", 1): [
		{"text": "分离调试命令和生产逻辑（Release 隔离）", "check": "Release 禁用危险命令", "state": "TODO",
		 "evidence": "当前只有运行时开关 can auto off，符号未摘"},
	],
}

# 任务提前：模块名 -> (from_idx, to_idx)
TASK_MOVES = {
	"Com": (4, 3),   # 06.5 整理 RxMon/Com 职责 提到 06.4 之前
}


def parse_v1(path):
	"""从 V1 HTML 里抠出 modules 数组（括号匹配，跳过字符串内的括号）。"""
	s = io.open(path, encoding="utf-8").read()
	i = s.find("const modules=") + len("const modules=")
	depth, instr, esc, end = 0, False, False, None
	for k in range(i, len(s)):
		ch = s[k]
		if instr:
			if esc:
				esc = False
			elif ch == "\\":
				esc = True
			elif ch == '"':
				instr = False
			continue
		if ch == '"':
			instr = True
		elif ch == "[":
			depth += 1
		elif ch == "]":
			depth -= 1
			if depth == 0:
				end = k + 1
				break
	return json.loads(s[i:end])


def build_json():
	mods = parse_v1(SRC_HTML)

	# 模块级阶段与依赖：开发顺序按阶段推进，不按编号
	phase = {
		"工程基线": 1, "公共基础库": 1, "PC-SIL / 自动测试": 1,
		"配置工具 / Generator": 2,
		"Can / CanAc": 3, "CanIf": 3, "PduR": 3, "Com": 3, "CanTp": 3,
		"CanSM / CanNm / Nm / ComM": 3, "E2E / J1939Tp（按需）": 3,
		"RTE / BcmSig": 4, "BCM 应用组件": 4,
		"Port / Dio": 5, "Adc / Pwm": 5, "Spi / I2c": 5, "Mcu / Wdg / Gpt / Icu": 5,
		"IoHwAb / DIN / AIN": 5, "IoHwAb / HSD / LSD / Relay": 5,
		"Lin / LinAc": 6, "LinIf / LDF / LinTp": 6,
		"Dcm": 7, "Dem / Det": 7, "NvM / Fee / Flash": 7, "AB Bootloader / FlashTool": 7,
		"EcuM / 低功耗": 7, "Shell / 调试监控": 7,
		"版本发布 / 上游同步": 8,
	}
	deps = {
		"公共基础库": ["工程基线"],
		"配置工具 / Generator": ["工程基线"],
		"Can / CanAc": ["公共基础库"],
		"CanIf": ["Can / CanAc"],
		"PduR": ["CanIf"],
		"Com": ["PduR"],
		"CanTp": ["PduR"],
		"CanSM / CanNm / Nm / ComM": ["CanIf", "Com"],
		"RTE / BcmSig": ["Com", "PC-SIL / 自动测试"],
		"BCM 应用组件": ["RTE / BcmSig", "IoHwAb / HSD / LSD / Relay"],
		"IoHwAb / DIN / AIN": ["Port / Dio", "Spi / I2c"],
		"IoHwAb / HSD / LSD / Relay": ["Port / Dio"],
		"Dcm": ["CanTp"],
		"Dem / Det": ["Dcm"],
		"NvM / Fee / Flash": ["公共基础库"],
		"AB Bootloader / FlashTool": ["NvM / Fee / Flash", "Dcm"],
		"EcuM / 低功耗": ["CanSM / CanNm / Nm / ComM", "NvM / Fee / Flash"],
		"LinIf / LDF / LinTp": ["Lin / LinAc", "Com"],
		"版本发布 / 上游同步": ["PC-SIL / 自动测试"],
	}

	out = []
	for idx, m in enumerate(mods):
		name = m["name"]
		tasks = []
		for j, t in enumerate(m["tasks"]):
			tasks.append({"text": t["text"], "check": t["check"], "state": "TODO", "evidence": ""})

		# 先做拼接式修订（拆分/改文本），再按原文下标覆盖状态
		new_tasks = []
		for j, t in enumerate(tasks):
			key = (name, j)
			if key in TASK_EDITS:
				new_tasks.extend(TASK_EDITS[key])
			else:
				new_tasks.append(t)
		tasks = new_tasks

		# 状态回填：按"修订前"的下标查，拆分后的条目自己带了状态
		for j, t in enumerate(m["tasks"]):
			if (name, j) in TASK_EDITS:
				continue
			if (name, j) in EVIDENCE:
				st, ev = EVIDENCE[(name, j)]
				# 拆分后下标会位移，用文本匹配更稳
				for nt in tasks:
					if nt["text"] == t["text"]:
						nt["state"], nt["evidence"] = st, ev
						break
			if (name, j) in BLOCKED:
				for nt in tasks:
					if nt["text"] == t["text"] and nt["state"] == "TODO":
						nt["state"] = "BLOCKED"
						nt["evidence"] = BLOCKED[(name, j)]
						break

		if name in TASK_MOVES:
			f, to = TASK_MOVES[name]
			if f < len(tasks):
				item = tasks.pop(f)
				tasks.insert(to, item)

		mod = {
			"id": idx,
			"group": m["group"],
			"name": name,
			"status": m["status"],
			"phase": phase.get(name, 8),
			"deps": deps.get(name, []),
			"origin": m["origin"],
			"design": m["design"],
			"target": m["target"],
			"tasks": tasks,
		}
		if name == "RTE / BcmSig":
			mod["statusNote"] = "已有生成器基础（tools/generator/Rte.py），尚无运行时实现（Rte.h 为空壳）"
		out.append(mod)

	data = {
		"version": 2,
		"updated": "2026-11-17",
		"states": [{"key": k, "label": v} for k, v in STATES],
		"phases": [
			{"n": 1, "name": "基线与可验证性", "goal": "构建可复现、业务能在 Host 上被判定",
			 "exit": "host_build.py 通过 + 三镜像可构建"},
			{"n": 2, "name": "配置链", "goal": "DBC/JSON → C 一条命令，产物确定且可校验",
			 "exit": "a4 幂等 + 矩阵交叉对账无缺口"},
			{"n": 3, "name": "CAN 闭环", "goal": "Can/CanIf/PduR/Com/CanTp/NM 全链路稳定",
			 "exit": "收发、诊断多帧、bus-off、重启全绿"},
			{"n": 4, "name": "RTE 与业务垂直", "goal": "一条业务从信号到输出，不感知 Com/硬件",
			 "exit": "Host 与实板结果一致"},
			{"n": 5, "name": "IO 与外设", "goal": "逻辑通道表收敛引脚差异",
			 "exit": "负载状态表经评审，故障可上报"},
			{"n": 6, "name": "LIN", "goal": "LDF → Com 链路，双通道",
			 "exit": "调度表与休眠唤醒可验"},
			{"n": 7, "name": "服务与升级", "goal": "诊断、存储、A/B、低功耗",
			 "exit": "DTC/DID 清单落地，回滚可重复"},
			{"n": 8, "name": "交付", "goal": "版本、示例、许可、回归归档",
			 "exit": "无 OEM 文件也能跑通生成与 Host 测试"},
		],
		"decisions": [
			{"id": "D-CAN3", "date": "2026-11-17", "title": "第三路 CAN",
			 "decision": "保留为计划项，当前两路作为验收基线，等硬件确认后再启用。",
			 "impact": "03.3 拆成两条任务并标 BLOCKED；Can 配置维持 2 路。"},
			{"id": "D-ORDER", "date": "2026-11-17", "title": "Host 与 CLI 的顺序",
			 "decision": "先 26.1 Host 最小构建，再 02 CLI。",
			 "impact": "Host 已落地（14/14）；RTE 后续任务以 Host 判据为准。"},
			{"id": "D9", "date": "2026-11-17", "title": "infras 修改权限",
			 "decision": "有条件开放：允许修复、升级与增量扩展；禁止无依据的整体重构。每次改动记录上游实现、修改原因、影响范围、回归结果。",
			 "impact": "0x27 与 DTC 映射不再被权限挡住，改由 OEM 资料进度决定。"},
		],
		"current": {
			"module": 26, "task": 0,
			"text": "26.1 Host 最小构建（已完成，14/14）",
			"next": "10.3 最小 RTE 运行时：先定端口/类型/有效性接口，再接入 Host 用例",
		},
		"modules": out,
	}
	io.open(JSON_PATH, "w", encoding="utf-8", newline="\n").write(
		json.dumps(data, ensure_ascii=False, indent=1))
	print("wrote %s (%d modules, %d tasks)"
	      % (JSON_PATH, len(out), sum(len(m["tasks"]) for m in out)))



SHORT = {
	"工程基线": "工程基线", "公共基础库": "基础库", "配置工具 / Generator": "配置工具",
	"Can / CanAc": "Can", "CanIf": "CanIf", "PduR": "PduR", "Com": "Com",
	"CanTp": "CanTp", "CanSM / CanNm / Nm / ComM": "CanSM/Nm/ComM",
	"E2E / J1939Tp（按需）": "E2E/J1939Tp",
	"RTE / BcmSig": "RTE/BcmSig",
	"Port / Dio": "Port/Dio", "Adc / Pwm": "Adc/Pwm", "Spi / I2c": "Spi/I2c",
	"Mcu / Wdg / Gpt / Icu": "Mcu/Wdg",
	"IoHwAb / DIN / AIN": "IoHwAb 输入", "IoHwAb / HSD / LSD / Relay": "IoHwAb 输出",
	"Lin / LinAc": "Lin", "LinIf / LDF / LinTp": "LinIf/LDF",
	"Dcm": "Dcm", "Dem / Det": "Dem/Det", "NvM / Fee / Flash": "NvM/Fee",
	"AB Bootloader / FlashTool": "AB/Boot", "EcuM / 低功耗": "EcuM/低功耗",
	"Shell / 调试监控": "Shell",
	"BCM 应用组件": "BCM 业务",
	"PC-SIL / 自动测试": "PC-SIL",
	"版本发布 / 上游同步": "发布/同步",
}

PHASE_COLOR = ["#216b7c", "#2b6f92", "#26795c", "#a46b20", "#7a5aa8", "#2b6f92", "#8a5a2b", "#44546a"]


def deps_svg(data):
	"""阶段级依赖图：左列阶段编号 + 右列该阶段的模块 chip。

	为什么不做任务级 DAG：113 条任务连成图会变成一团毛线，读不出信息。
	阶段/模块级的依赖才回答"下一步该做什么"；任务级依赖放在模块页
	（每个模块列出 deps），查得到且不干扰。
	"""
	rows = []
	y = 26
	box_w = 560
	for ph in data["phases"]:
		mods = [m for m in data["modules"] if m["phase"] == ph["n"]]
		chips = []
		cx = 96
		cy = y + 34
		for m in mods:
			label = SHORT.get(m["name"], m["name"])
			w = 14 + len(label) * 12
			if cx + w > 96 + box_w:
				cx = 96
				cy += 30
			chips.append((cx, cy, w, label, m["id"]))
			cx += w + 8
		h = (cy - y) + 26
		rows.append((ph, y, h, chips))
		y += h + 12

	H = y + 10
	out = ['<svg viewBox="0 0 680 %d" width="100%%" role="img" xmlns="http://www.w3.org/2000/svg">' % H]
	out.append('<title>like_as 开发阶段与模块依赖</title>')
	out.append('<desc>8 个阶段自上而下推进，箭头表示阶段依赖，方块为该阶段包含的模块</desc>')
	out.append('<defs><marker id="ar" viewBox="0 0 10 10" refX="8" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse"><path d="M2 1L8 5L2 9" fill="none" stroke="context-stroke" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/></marker></defs>')
	for i, (ph, y0, h, chips) in enumerate(rows):
		c = PHASE_COLOR[i % len(PHASE_COLOR)]
		out.append('<rect x="20" y="%d" width="640" height="%d" rx="10" fill="%s" fill-opacity="0.05" stroke="%s" stroke-width="0.5"/>'
		           % (y0, h, c, c))
		out.append('<circle cx="48" cy="%d" r="13" fill="%s"/>' % (y0 + 18, c))
		out.append('<text x="48" y="%d" text-anchor="middle" dominant-baseline="central" font-size="12" fill="#fff">%d</text>'
		           % (y0 + 18, ph["n"]))
		out.append('<text x="70" y="%d" dominant-baseline="central" font-size="12" fill="#17283a" font-weight="500">%s</text>'
		           % (y0 + 18, ph["name"]))
		out.append('<text x="96" y="%d" dominant-baseline="central" font-size="10" fill="#617486">%s</text>'
		           % (y0 + h - 8, ph["goal"]))
		for (x, cy, w, label, mid) in chips:
			out.append('<a href="#m%d"><rect x="%d" y="%d" width="%d" height="22" rx="6" fill="#fff" stroke="%s" stroke-width="0.5"/>'
			           % (mid, x, cy - 11, w, c))
			out.append('<text x="%.0f" y="%d" text-anchor="middle" dominant-baseline="central" font-size="11" fill="#17283a">%s</text></a>'
			           % (x + w / 2.0, cy, label))
		if i + 1 < len(rows):
			out.append('<path d="M48 %d L48 %d" fill="none" stroke="#617486" stroke-width="1.5" marker-end="url(#ar)"/>'
			           % (y0 + h, y0 + h + 11))
	out.append('</svg>')
	return "".join(out)


CSS = """
:root{--bg:#f2f5f8;--paper:#fff;--ink:#17283a;--muted:#617486;--line:#dce4eb;--accent:#216b7c;--nav:#142638}
*{box-sizing:border-box}body{margin:0;color:var(--ink);background:var(--bg);font:14px/1.65 system-ui,"Microsoft YaHei",sans-serif}
a{color:var(--accent);text-decoration:none}button,select,textarea{font:inherit}
.layout{display:grid;grid-template-columns:264px minmax(0,1fr);min-height:100vh}
aside{background:var(--nav);color:#b8c9d7;padding:22px 12px;height:100vh;position:sticky;top:0;overflow:auto}
.brand{padding:0 10px 16px;border-bottom:1px solid #344657}.brand b{font-size:25px;color:#fff;letter-spacing:-1px}
.brand small{display:block;color:#a5b9cc;font-size:11px}
.navhead{font-size:11px;letter-spacing:.09em;margin:16px 10px 4px;color:#8da6ba}
.navbtn{border:0;background:none;color:inherit;width:100%;text-align:left;border-radius:6px;padding:7px 10px;display:flex;justify-content:space-between;gap:8px;font-size:13px;cursor:pointer}
.navbtn.active{background:#285267;color:#fff}.navbtn:hover{background:#233e52}
.navbtn span:first-child{overflow:hidden;text-overflow:ellipsis;white-space:nowrap}
aside{scrollbar-width:thin}.navbtn span:last-child{font-size:11px;color:#a7cbd6}
main{max-width:1180px;width:100%;padding:26px 32px 60px;margin:0 auto;align-self:start}
h1{font-size:27px;margin:6px 0 8px;letter-spacing:-.4px}h2{font-size:18px;margin:0 0 10px}h3{font-size:14px;margin:0 0 6px}
.eyebrow{font-size:11px;font-weight:700;letter-spacing:.12em;color:var(--accent);text-transform:uppercase}
.muted{color:var(--muted)}
.cards{display:grid;grid-template-columns:repeat(5,minmax(0,1fr));gap:10px;margin:16px 0}
.stat,.panel{background:var(--paper);border:1px solid var(--line);border-radius:10px}
.stat{padding:14px}.stat .num{font-size:24px;font-weight:500;margin:2px 0}
.panel{padding:18px;margin-bottom:14px}
.chip{display:inline-block;padding:1px 8px;border-radius:10px;font-size:11px;border:1px solid}
.PASS{color:#26795c;border-color:#9fd0bd;background:#eaf6f1}
.PARTIAL{color:#a46b20;border-color:#e6c893;background:#fdf4e5}
.TODO{color:#617486;border-color:#d3dae1;background:#f4f7f9}
.BLOCKED{color:#a32d2d;border-color:#eab3b3;background:#fdeeee}
.SKIP{color:#534ab7;border-color:#c2bee9;background:#f1f0fd}
.bar{height:6px;background:#e6ecf1;border-radius:4px;overflow:hidden;margin-top:6px}
.fill{height:100%;background:var(--accent)}
table{width:100%;border-collapse:collapse;font-size:13px}th,td{text-align:left;padding:7px 8px;border-bottom:1px solid var(--line);vertical-align:top}
th{color:var(--muted);font-weight:500;font-size:12px}
.task{display:grid;grid-template-columns:96px 1fr;gap:10px;padding:9px 0;border-bottom:1px solid var(--line)}
.task:last-child{border-bottom:0}.task label{font-size:13px}
.task small{display:block;color:var(--muted);font-size:11.5px;margin-top:2px}
.task select{width:96px;padding:3px;border:1px solid var(--line);border-radius:6px;background:#fff;font-size:11px}
.ev{color:#26795c;font-size:11.5px;margin-top:3px}
textarea{width:100%;min-height:70px;border:1px solid var(--line);border-radius:8px;padding:8px;resize:vertical}
.btn{background:#fff;border:1px solid var(--line);border-radius:6px;padding:6px 10px;cursor:pointer;font-size:12px}
.btn.p{background:var(--accent);color:#fff;border-color:var(--accent)}
.row{display:flex;gap:10px;flex-wrap:wrap;align-items:center}
.two{display:grid;grid-template-columns:1fr 1fr;gap:14px}
.dec{border-left:3px solid var(--accent);padding:6px 0 6px 12px;margin-bottom:12px}
.footer{color:var(--muted);font-size:11px;margin-top:22px}
@media(max-width:900px){.layout{grid-template-columns:1fr}aside{display:none}.cards{grid-template-columns:repeat(2,1fr)}.two{grid-template-columns:1fr}}
"""

JS = r"""
const KEY='like_as_roadmap_v2';
let st={over:{},notes:{}};
try{const x=JSON.parse(localStorage.getItem(KEY)||'null');if(x&&x.over)st=x}catch(e){}
const S=DATA.states.map(s=>s.key), LBL={};DATA.states.forEach(s=>LBL[s.key]=s.label);
const GROUPS=[...new Set(DATA.modules.map(m=>m.group))];
const state=(mi,ti)=>st.over[mi+'-'+ti]||DATA.modules[mi].tasks[ti].state;
const save=()=>{try{localStorage.setItem(KEY,JSON.stringify(st))}catch(e){}};
const cnt=(mi)=>{const m=DATA.modules[mi];let c={};S.forEach(s=>c[s]=0);m.tasks.forEach((t,ti)=>c[state(mi,ti)]++);return c};
const tot=()=>{let c={};S.forEach(s=>c[s]=0);DATA.modules.forEach((m,mi)=>{const x=cnt(mi);S.forEach(s=>c[s]+=x[s])});return c};
const pct=(a,b)=>b?Math.round(a/b*100):0;
const esc=s=>String(s??'').replace(/[&<>"']/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));
function bar(a,b){return `<div class="bar"><div class="fill" style="width:${pct(a,b)}%"></div></div>`}
function nav(r){const t=tot();let h=`<div class="navhead">总览</div>
<button class="navbtn ${r==='home'?'active':''}" onclick="go('home')"><span>完成度看板</span><span>${pct(t.PASS,t.PASS+t.PARTIAL+t.TODO)}%</span></button>
<button class="navbtn ${r==='order'?'active':''}" onclick="go('order')"><span>开发顺序</span></button>
<button class="navbtn ${r==='deps'?'active':''}" onclick="go('deps')"><span>依赖关系</span></button>
<button class="navbtn ${r==='current'?'active':''}" onclick="go('current')"><span>当前任务</span></button>
<button class="navbtn ${r==='dec'?'active':''}" onclick="go('dec')"><span>决策记录</span><span>${DATA.decisions.length}</span></button>`;
GROUPS.forEach(g=>{h+=`<div class="navhead">${esc(g)}</div>`;DATA.modules.forEach((m,mi)=>{if(m.group!==g)return;const c=cnt(mi);h+=`<button class="navbtn ${r===mi?'active':''}" onclick="go(${mi})"><span>${esc(m.name)}</span><span>${c.PASS}/${m.tasks.length}</span></button>`})});
document.getElementById('nav').innerHTML=h}
function go(r){location.hash=r==='home'?'home':(typeof r==='number'?'m'+r:r)}
function home(){const t=tot(),all=t.PASS+t.PARTIAL+t.TODO+t.BLOCKED+t.SKIP;
let h=`<div class="eyebrow">Engineering handbook · V2.0</div><h1>开发完成度看板</h1>
<p class="muted">继承 autoas/as，按 BCM 需求增量升级；状态来自可重跑的脚本与上板记录。</p>
<div class="cards">`;
[['PASS','已验收'],['PARTIAL','部分'],['TODO','待做'],['BLOCKED','受阻'],['SKIP','无法验证']].forEach(([k,n])=>{
h+=`<div class="stat"><div class="muted">${n} <span class="chip ${k}">${k}</span></div><div class="num">${t[k]}</div>${bar(t[k],all)}</div>`});
h+=`</div><div class="two"><section class="panel"><h2>各领域</h2>`;
GROUPS.forEach(g=>{let a=0,b=0;DATA.modules.forEach((m,mi)=>{if(m.group!==g)return;const c=cnt(mi);a+=c.PASS;b+=m.tasks.length});
h+=`<div class="row" style="justify-content:space-between"><strong>${esc(g)}</strong><span class="muted">${a}/${b}</span></div>${bar(a,b)}<div style="height:8px"></div>`});
h+=`</section><section class="panel"><h2>现在该做什么</h2><p><strong>${esc(DATA.current.text)}</strong></p><p class="muted">下一步：${esc(DATA.current.next)}</p>
<p style="margin-top:10px"><button class="btn p" onclick="go('current')">打开当前任务</button></p>
<h3 style="margin-top:14px">受阻项（${t.BLOCKED}）</h3>`;
DATA.modules.forEach((m,mi)=>m.tasks.forEach((tk,ti)=>{if(state(mi,ti)==='BLOCKED')h+=`<div class="muted" style="font-size:12px">· ${esc(m.name)} / ${esc(tk.text)}</div>`}));
h+=`</section></div><div class="footer">数据源 doc/roadmap.json，由 tools/roadmap_build.py 渲染。进度改动保存在本浏览器。</div>`;
return h}
function order(){let h=`<div class="eyebrow">顺序 / 不按模块编号</div><h1>开发顺序</h1><p class="muted">阶段之间是硬依赖；同阶段内的模块可并行。</p>`;
DATA.phases.forEach(p=>{const mods=DATA.modules.filter(m=>m.phase===p.n);
let a=0,b=0;mods.forEach(m=>{const mi=m.id,c=cnt(mi);a+=c.PASS;b+=m.tasks.length});
h+=`<section class="panel"><div class="row" style="justify-content:space-between"><h2>阶段 ${p.n} · ${esc(p.name)}</h2><span class="muted">${a}/${b}</span></div>
<p class="muted">目标：${esc(p.goal)}<br>出口：${esc(p.exit)}</p>${bar(a,b)}
<div class="row" style="margin-top:10px">${mods.map(m=>`<a class="btn" href="#m${m.id}">${esc(m.name)}</a>`).join('')}</div></section>`});
return h}
function deps(){return `<div class="eyebrow">依赖 / 阶段级</div><h1>依赖关系</h1>
<p class="muted">113 条任务画成 DAG 会成一团毛线；阶段级依赖才回答"下一步做什么"。任务级依赖见各模块页底部。</p>
<section class="panel">${DATA.depsSvg}</section>`}
function current(){const c=DATA.current,m=DATA.modules[c.module];
let h=`<div class="eyebrow">当前任务</div><h1>${esc(c.text)}</h1><p class="muted">下一步：${esc(c.next)}</p>`;
h+=`<section class="panel"><h2>模块 ${m.id} · ${esc(m.name)}</h2><p>${esc(m.target)}</p>
<div class="row">${m.tasks.map((t,i)=>`<span class="chip ${state(m.id,i)}">${esc(t.text).slice(0,18)}</span>`).join('')}</div></section>`;
h+=`<section class="panel"><h2>验收判据</h2><p class="muted">Host 与目标板编同一份业务源码；Host 能推进时间，因此去抖/超时类用例可秒级复现。</p>
<pre style="background:#f4f7f9;border:1px solid #dce4eb;border-radius:8px;padding:10px;font-size:12px;overflow:auto">python tools/host_build.py\n== like_as host test: BcmSig / BcmBiz ==\n-- 14 passed, 0 failed</pre></section>`;
return h}
function dec(){let h=`<div class="eyebrow">决策 / 可追溯</div><h1>设计决策记录</h1>`;
DATA.decisions.forEach(d=>{h+=`<div class="dec"><div class="row"><strong>${esc(d.id)}</strong><span class="muted">${esc(d.date)}</span><span class="chip PASS">${esc(d.title)}</span></div>
<p style="margin:4px 0">${esc(d.decision)}</p><p class="muted" style="font-size:12px">影响：${esc(d.impact)}</p></div>`});
return h}
function detail(mi){const m=DATA.modules[mi],c=cnt(mi);
let h=`<div class="eyebrow">${esc(m.group)} / 模块 ${String(mi+1).padStart(2,'0')}</div><h1>${esc(m.name)}</h1>
<div class="row"><span class="chip ${c.PASS===m.tasks.length?'PASS':'TODO'}">${c.PASS}/${m.tasks.length} PASS</span>
<span class="muted">阶段 ${m.phase}</span>${m.statusNote?`<span class="chip PARTIAL">${esc(m.statusNote)}</span>`:''}</div>`;
h+=`<div class="two" style="margin-top:12px"><section class="panel"><h3>设计来源</h3><p class="muted">${esc(m.origin)}</p></section>
<section class="panel"><h3>设计思路</h3><p class="muted">${esc(m.design)}</p></section></div>`;
h+=`<section class="panel"><h3>目标状态</h3><p class="muted">${esc(m.target)}</p>${m.deps.length?`<p class="muted" style="font-size:12px">依赖模块：${m.deps.map(d=>`<a href="#m${DATA.modules.findIndex(x=>x.name===d)}">${esc(d)}</a>`).join(' · ')}</p>`:''}</section>`;
h+=`<section class="panel"><h2>任务与验收</h2>`;
m.tasks.forEach((t,ti)=>{const s=state(mi,ti);
h+=`<div class="task"><div><select onchange="setState(${mi},${ti},this.value)">${S.map(k=>`<option value="${k}" ${k===s?'selected':''}>${k}</option>`).join('')}</select></div>
<div><label>${String(ti+1).padStart(2,'0')} · ${esc(t.text)}</label><small>验收：${esc(t.check)}</small>
${t.evidence?`<div class="ev">证据：${esc(t.evidence)}</div>`:''}</div></div>`});
h+=`</section><section class="panel"><h3>实施记录</h3><textarea placeholder="提交 SHA、测试证据、裁剪原因、阻塞事项…" oninput="note(${mi},this.value)">${esc(st.notes[mi]||'')}</textarea></section>`;
return h}
function setState(mi,ti,v){st.over[mi+'-'+ti]=v;save();render()}
function note(mi,v){st.notes[mi]=v;save()}
function exportState(){const b=new Blob([JSON.stringify({version:2,...st},null,2)],{type:'application/json'});const u=URL.createObjectURL(b);const a=document.createElement('a');a.href=u;a.download='like_as_progress_v2.json';a.click();setTimeout(()=>URL.revokeObjectURL(u),800)}
function importState(){const f=document.getElementById('file');f.value='';f.click()}
function render(){const h=location.hash.slice(1);let mi=/^m\d+$/.test(h)?Number(h.slice(1)):-1;
let body,route;
if(mi>=0&&mi<DATA.modules.length){route=mi;body=detail(mi)}else{route=h||'home';
body=route==='order'?order():route==='deps'?deps():route==='current'?current():route==='dec'?dec():home()}
nav(route);document.getElementById('view').innerHTML=body;window.scrollTo(0,0)}
document.getElementById('file').addEventListener('change',async e=>{try{const x=JSON.parse(await e.target.files[0].text());
if(!x.over)throw 0;st={over:x.over,notes:x.notes||{}};save();render()}catch(err){alert('导入失败：请选择有效的进度 JSON')}});
window.addEventListener('hashchange',render);render();
"""


def render_html(data):
	data = dict(data)
	data["depsSvg"] = deps_svg(data)
	return """<!doctype html><html lang="zh-CN"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>like_as · 开发手册 V2.0</title><style>%s</style></head><body>
<div class="layout"><aside><div class="brand"><b>like_as<span style="color:#5db4bf">.</span></b><small>BCM PLATFORM / HANDBOOK V2.0</small></div>
<nav id="nav" aria-label="模块导航"></nav>
<div style="padding:12px 8px 0"><button class="btn" onclick="exportState()">导出进度</button>
<button class="btn" onclick="importState()">导入进度</button></div></aside>
<main><div id="view"></div></main></div>
<input type="file" id="file" accept="application/json,.json" hidden>
<script>const DATA=%s;%s</script></body></html>""" % (CSS, json.dumps(data, ensure_ascii=False), JS)


if __name__ == "__main__":
	if "--import" in sys.argv:
		build_json()
	else:
		if not os.path.isfile(JSON_PATH):
			print("[ERROR] 缺少 %s，先运行 --import" % JSON_PATH)
			sys.exit(2)
		data = json.load(io.open(JSON_PATH, encoding="utf-8"))
		html = render_html(data)
		io.open(HTML_PATH, "w", encoding="utf-8", newline="\n").write(html)
		print("wrote %s (%.1f KB)" % (HTML_PATH, len(html) / 1024.0))
