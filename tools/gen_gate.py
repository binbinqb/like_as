#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    gen_gate.py
@brief   配置生成门禁：判断这一轮构建要不要重新生成配置

@details @section GATE_WHY 为什么需要门禁

         `config.py generate` 五步实测 **7.2 s**（三次 DBC 解析各约 1.8 s、
         `Com_Cfg.c` 527 KB 拷贝、67 项对账）。每次构建都跑一遍是给构建加
         固定税；完全不跑则是"改了 JSON 不生效"——后者更糟，而且没有任何提示。

         门禁把"要不要跑"压成一次哈希（`compute()` 实测 36 ms；整条
         `config.py sync` 端到端 500 ms，其中大头是解释器启动与 `config.py`
         的模块导入）：输入没变、产物也没被手改，就跳过；否则照旧跑完整五步。

         @section GATE_INPUTS 指纹覆盖哪些输入

         | 类别 | 文件 | 算进去的理由 |
         |------|------|--------------|
         | 配置源 | `Can/Can.json`、`CanIf/CanIf.json`、`PduR/PduR.json`、`Com/Com.json` | 直接决定产物 |
         | 矩阵 | `dbc/can0.dbc`、`dbc/can1.dbc` | 换一版矩阵，报文与信号全变 |
         | 生成器 | `tools/generator/**/*.py` | 改生成器等于改产物 |
         | 注入器 | `tools/sync_can.py`、`sync_canif.py`、`sync_pdur.py`、`config.py` | 只改 `@generated` 之间，但它变了也得重跑 |

         @section GATE_ARTIFACT 为什么还要比对产物

         手工改 `@generated` 区块**之外**的内容是允许的（那些是人工设计说明），
         所以判据不能是"产物变了就重生成"——那会把人工内容冲掉。
         这里只检测一件事：产物是否仍是上一次生成的**那一份**。
         不是 → 有人改过生成物、或者产物丢了 → 必须重新生成，否则
         "仓库里的配置"与"JSON 说的配置"从此不是一回事。

         @warning 比对前一律做 **LF 归一**：`Com_Cfg.c` 由生成器以文本模式写，
         Windows 下 `\\n` 被翻成 CRLF（实测工作区 527,384 B vs 仓库 510,550 B，
         差值 16,834 B 正好等于行数）。`.gitattributes` 的 `text eol=lf` 会让
         git 看不见这个差异，所以"重新生成无 diff"只在 git 层成立。
         若按原始字节比对，CRLF 的产物会永远被判成漂移。

@warning 客户 DBC 不入库（见 `.gitignore`）。缺 DBC 时的判定：

         | 情况 | 结论 | 为什么 |
         |------|------|--------|
         | 无状态文件 | `degrade` | 新克隆的正常路径：直接用已入库产物构建 |
         | 有状态、输入未变 | `skip` | 没有需要重做的事 |
         | 有状态、输入变了 | `blocked` | 配置改了却没有 DBC，生成不出来；继续构建等于拿旧配置冒充新配置 |
         | 有状态、产物漂移 | `skip` + 告警 | 没有 DBC 无法把它拉回来，只能让人知道 |

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-17 | binbina | 首版：输入/产物指纹、四种判定、并发锁 |
"""

import hashlib
import io
import json
import os
import time

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

CFG_REL = "app/platform/cvm0146/src/config"
STATE_REL = ".genstate.json"
LOCK_REL = ".genlock"

# 状态文件格式版本：改了 compute() 的算法/字段就 +1，旧状态自动作废。
STATE_VERSION = 1

# 拿不到锁时最多等多久（秒）；也是判定"锁是残留"的阈值。
LOCK_STALE_SEC = 600

# 输入：配置源（任何一份变了都要重生成）
INPUT_JSON = [
	"Can/Can.json",
	"CanIf/CanIf.json",
	"PduR/PduR.json",
	"Com/Com.json",
]

# 输入：通信矩阵（不入库，缺了走降级路径）
INPUT_DBC = [
	"dbc/can0.dbc",
	"dbc/can1.dbc",
]

# 输入：生成器源码目录（整个目录的 .py 都算）
INPUT_GEN_DIR = "tools/generator"

# 输入：注入脚本 + 入口本身
#
# 为什么**不**把自己（gen_gate.py）算进去：它只决定"跑不跑"，不产出产物。
# 算进去的后果是"改一次门禁 → 下次构建白跑 7 秒重生成"，而产物一个字节都不会变。
# 门禁算法本身变了、需要作废旧指纹时，改 STATE_VERSION 更直接。
INPUT_TOOLS = [
	"tools/sync_can.py",
	"tools/sync_canif.py",
	"tools/sync_pdur.py",
	"tools/config.py",
]

# 产物：生成链会重写的入库文件。
# 这份清单是**实测**出来的（`generate --force` 前后比对 config/ 全部 59 个
# 文件的 mtime），不是从脚本里读出来的 —— 读代码容易漏掉"拷入"这一步。
ARTIFACTS = [
	"Can_Cfg.c",
	"CanIf_Cfg.c",
	"CanIf_Cfg.h",
	"PduR_Cfg.c",
	"PduR_Cfg.h",
	"Com_Cfg.c",
	"Com_Cfg.h",
]


def cfg_dir(root=None):
	"""配置目录（root 可换，自测脚本用临时目录造缺陷树）。"""
	return os.path.join(root or ROOT, *CFG_REL.split("/"))


def _digest(path):
	"""文件的 LF 归一 md5；读不到返回 None（= 缺失）。"""
	try:
		with io.open(path, "rb") as f:
			data = f.read()
	except OSError:
		return None
	return hashlib.md5(data.replace(b"\r\n", b"\n")).hexdigest()


def _gen_py(root):
	"""列出生成器源码目录下的全部 .py（跳过 __pycache__）。"""
	d = os.path.join(root, *INPUT_GEN_DIR.split("/"))
	out = []
	for cur, dirs, files in os.walk(d):
		dirs[:] = sorted(x for x in dirs if x != "__pycache__")
		for fn in sorted(files):
			if fn.endswith(".py"):
				out.append(os.path.join(cur, fn))
	return out


def compute(root=None):
	"""算输入指纹 + 产物指纹。

	@param[in] root 仓库根，默认本文件所在目录的上一级

	@return dict
	        - `inputs`      {相对标签: md5}，缺失的输入不出现在表里
	        - `missing`     [缺失的输入标签]
	        - `artifacts`   {文件名: md5 或 None}
	        - `fingerprint` 输入整体指纹（缺失项也参与，这样 DBC 一出现就会变）
	"""
	root = root or ROOT
	inputs = {}
	missing = []

	def add(label, path):
		h = _digest(path)
		if h is None:
			missing.append(label)
		else:
			inputs[label] = h

	cd = cfg_dir(root)
	for rel in INPUT_JSON:
		add(rel, os.path.join(cd, *rel.split("/")))
	for rel in INPUT_DBC:
		add(rel, os.path.join(cd, *rel.split("/")))
	for rel in INPUT_TOOLS:
		add(rel, os.path.join(root, *rel.split("/")))
	for p in _gen_py(root):
		add(os.path.relpath(p, root).replace(os.sep, "/"), p)

	h = hashlib.md5()
	for k in sorted(inputs):
		h.update(("%s=%s\n" % (k, inputs[k])).encode("utf-8"))
	for k in sorted(missing):
		h.update(("MISSING:%s\n" % k).encode("utf-8"))

	artifacts = {}
	for name in ARTIFACTS:
		artifacts[name] = _digest(os.path.join(cd, name))

	return {
		"inputs": inputs,
		"missing": missing,
		"artifacts": artifacts,
		"fingerprint": h.hexdigest(),
	}


def state_path(root=None):
	"""状态文件路径（仓库根，已 gitignore）。"""
	return os.path.join(root or ROOT, STATE_REL)


def load_state(root=None):
	"""读状态；不存在 / 损坏 / 版本不符一律返回 None（当作首次）。"""
	try:
		with io.open(state_path(root), encoding="utf-8") as f:
			st = json.load(f)
	except (OSError, ValueError):
		return None
	if not isinstance(st, dict) or st.get("version") != STATE_VERSION:
		return None
	return st


def save_state(root=None):
	"""把当前输入/产物指纹落盘。

	@note 用 `tmp + os.replace` 原子替换：App / AppB 两个构建并发时，
	      读到半个 JSON 会直接抛异常，比慢一点更糟。
	"""
	root = root or ROOT
	st = compute(root)
	st["version"] = STATE_VERSION
	st["generated_at"] = time.strftime("%Y-%m-%dT%H:%M:%S")
	p = state_path(root)
	tmp = p + ".tmp"
	with io.open(tmp, "w", encoding="utf-8", newline="\n") as f:
		json.dump(st, f, ensure_ascii=False, indent=2, sort_keys=True)
		f.write("\n")
	os.replace(tmp, p)
	return st


def _changed_inputs(now, prev):
	"""列出"变了"的输入，用于把人指到具体文件。

	@note 只比**现在存在**的输入：DBC 被删掉不算"配置改了"（没法重生成，
	      也不该因此拦住构建）；JSON / 工具脚本缺失另有 `blocked` 分支兜住。
	"""
	old = prev.get("inputs", {})
	out = []
	for k, v in now["inputs"].items():
		if old.get(k) != v:
			out.append(k)
	return sorted(out)


def check(root=None, force=False):
	"""判定这一轮要不要重新生成。

	@param[in] root  仓库根
	@param[in] force 忽略指纹强制生成（`--force` / `--gen`）

	@return (action, reason, detail)
	        - `action` ∈ `{"run", "skip", "degrade", "blocked"}`
	        - `reason` 一行中文说明
	        - `detail` 涉及的文件标签列表（可为空）
	"""
	root = root or ROOT
	now = compute(root)
	prev = load_state(root)
	missing_dbc = [m for m in now["missing"] if m in INPUT_DBC]
	missing_src = [m for m in now["missing"] if m not in INPUT_DBC]

	if force:
		return "run", "显式要求重新生成（--force / --gen）", []
	if missing_src:
		return "blocked", "配置源缺失：%s" % "、".join(missing_src), missing_src

	if prev is None:
		if missing_dbc:
			return "degrade", "缺客户 DBC 且无生成记录：用已入库产物构建", missing_dbc
		return "run", "首次生成（无 %s）" % STATE_REL, []

	changed = _changed_inputs(now, prev)
	drift = [n for n in ARTIFACTS if prev.get("artifacts", {}).get(n) != now["artifacts"].get(n)]
	# 判据以**整体指纹**为准，逐文件差异只用来解释"到底哪个文件变了"。
	# 反过来（只比逐文件差异）会漏掉一类真实情况：被跟踪的输入**增减**
	# （比如往 INPUT_TOOLS 里加一个脚本），此时 now 里没有那个 key，
	# 逐文件比对看不到任何差异，指纹却已经变了。
	fp_same = prev.get("fingerprint") == now["fingerprint"]

	if fp_same and not drift:
		if missing_dbc:
			return "skip", "配置未变化（缺 DBC，用已入库产物）", missing_dbc
		return "skip", "配置与产物均未变化", []

	if not fp_same:
		if changed:
			reason = "输入变化：%s" % "、".join(changed[:3])
			detail = changed
		else:
			reason = "指纹变化（输入集或指纹算法变更，旧记录作废）"
			detail = []
		if missing_dbc:
			return ("blocked",
			        "配置源已改动（%s），但客户 DBC 缺失，无法重新生成" % (changed[0] if changed else "输入集"),
			        detail or missing_dbc)
		return "run", reason, detail

	# 走到这里 = 输入没变，只有产物漂移
	if missing_dbc:
		return ("skip",
		        "告警：产物被改动或丢失（%s），缺 DBC 无法重新生成" % "、".join(drift[:3]),
		        drift)
	return "run", "产物被改动或丢失：%s" % "、".join(drift[:3]), drift


def acquire_lock(root=None, timeout=LOCK_STALE_SEC):
	"""拿生成锁：App / AppB 两个构建并发时只允许一个进程真正生成。

	@param[in] timeout 最长等待秒数（同时是"残留锁"的判定阈值）

	@return True 拿到 / False 超时
	"""
	p = os.path.join(root or ROOT, LOCK_REL)
	deadline = time.time() + timeout
	while True:
		try:
			fd = os.open(p, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
		except FileExistsError:
			# 上一个进程崩了会留下锁：超过阈值没被删就当残留清掉。
			try:
				if time.time() - os.path.getmtime(p) > LOCK_STALE_SEC:
					os.remove(p)
					continue
			except OSError:
				pass
			if time.time() >= deadline:
				return False
			time.sleep(0.2)
			continue
		os.write(fd, str(os.getpid()).encode("ascii"))
		os.close(fd)
		return True


def release_lock(root=None):
	"""释放生成锁（不存在也算成功）。"""
	try:
		os.remove(os.path.join(root or ROOT, LOCK_REL))
	except OSError:
		pass
