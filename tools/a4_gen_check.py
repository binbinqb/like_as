# -*- coding: utf-8 -*-
"""A4 生成一致性检查：重新生成不该改变任何一个字节。

## 这个脚本回答什么问题

"改完 JSON / DBC 跑一遍生成器，会不会吃掉手写的东西？"
"版本库里那份 `Com_Cfg.c` 到底是哪次生成的？"

判据来自《框架就绪度评估》A4，四条：

| 编号 | 判据 | 为什么必须 |
|------|------|------------|
| C1 | 连跑两遍，两次产物逐字节相同 | 带时间戳的产物永远对不上，没法复核 |
| C2 | 每个生成物都有 `@generated` 标记 | 下一个人一眼能看出"别手改" |
| C3 | 生成物里不出现 `Generated at <星期> …` | 这是 C1 的直接死因 |
| C4 | `GEN/` 与拷入 `config/` 的那份一致 | 拷漏或拷错，编译用的还是旧的 |
| C5 | 注入区块 `@generated BEGIN/END` 成对且非空 | 区块断裂会把整文件改坏 |
| C6 | 应用层文件里不出现 `@generated` | 反向断言：生成器碰不到业务代码 |

## 三种产物形态（容易混淆，先分清）

1. **就地生成**：`Board` / `Shell`。`GEN/Xxx_Cfg.c` 由 `GEN/SConscript`
   直接参与编译，没有"拷入"这一步。
2. **生成后拷入**：`Com`。产物在 `GEN/`，人工（或脚本）拷到 `config/` 根，
   编译用的是 `config/Com_Cfg.c`。**这份是入 git 的**，所以最容易和
   `GEN/` 长出差异 —— C4 就是盯它。
3. **注入区块**：`CanIf` / `PduR`。整文件手写（带大量注释、M1~M14 的
   23 条 CAN0 配置），只有 `@generated BEGIN: …` 到 `END` 之间由
   `tools/sync_canif.py` / `sync_pdur.py` 改写。

## 用法

    python tools/a4_gen_check.py             # 跑生成器两遍 + 注入脚本 + 全部断言
    python tools/a4_gen_check.py --static    # 不跑生成器，只做 C2~C6 静态断言
    python tools/a4_gen_check.py -v          # 打印每个被比较的文件

@author binbina
"""

import hashlib
import io
import os
import re
import subprocess
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
CFG = os.path.join(ROOT, "app", "platform", "cvm0146", "src", "config")
APP_SRC = os.path.join(ROOT, "app", "app", "src")

# ── 产物清单 ────────────────────────────────────────────────────────────
# 就地生成：GEN/ 下的 .c 由 SConscript 直接编译
GEN_INPLACE = ["Board", "Shell"]
# 生成后拷入：GEN/ → config/ 根
GEN_COPY = ["Com"]
# 注入区块：手写文件里的 @generated BEGIN/END
INJECT_FILES = [
	os.path.join(CFG, "CanIf_Cfg.c"),
	os.path.join(CFG, "CanIf_Cfg.h"),
	os.path.join(CFG, "PduR_Cfg.c"),
	os.path.join(CFG, "PduR_Cfg.h"),
]
INJECT_SCRIPTS = ["tools/sync_canif.py", "tools/sync_pdur.py"]

# 需要跑生成器的 JSON（顺序与 doc/配置层约定.md 一致）
GEN_JSON = [
	os.path.join(CFG, "Board", "Board.json"),
	os.path.join(CFG, "Shell", "Shell.json"),
	os.path.join(CFG, "CanIf", "CanIf.json"),
	os.path.join(CFG, "PduR", "PduR.json"),
	os.path.join(CFG, "Com", "Com.json"),
]

# 反向断言对象：这几个文件永远不许被生成器覆盖
HANDWRITTEN_MUST_CLEAN = [
	os.path.join(APP_SRC, "main.c"),
	os.path.join(APP_SRC, "EcuM_Cfg.c"),
	os.path.join(APP_SRC, "bcm_sig_cfg.c"),
	os.path.join(CFG, "CanTp_Cfg.c"),
	os.path.join(CFG, "Dcm_Cfg.c"),
]

TIMESTAMP_RE = re.compile(r"Generated at \w{3} ")
TAG_RE = re.compile(r"^\s*\*\s*@generated\s*$", re.M)
BEGIN_RE = re.compile(r"@generated BEGIN:[^\n]*")
END_RE = re.compile(r"@generated END:[^\n]*")

results = []   # (编号, 是否通过, 说明)


def rel(p):
	return os.path.relpath(p, ROOT).replace("\\", "/")


def sha(p):
	h = hashlib.sha256()
	with open(p, "rb") as f:
		h.update(f.read())
	return h.hexdigest()


def read(p):
	return io.open(p, encoding="utf-8", errors="replace").read()


def gen_files():
	"""返回所有生成器产物（`config/<模块>/GEN/` 下的 .c/.h）。

	@note 这里用**目录扫描**而不是写死模块名：`CanIf` / `PduR` 的 GEN 产物
	      本身不参与编译（只有被注入的那几行进 `CanIf_Cfg.c`），但它仍然是
	      生成物，照样要受 C2/C3 约束 —— 漏掉它们等于给"生成器只是没写好
	      注释"留了口子。
	"""
	out = []
	for name in sorted(os.listdir(CFG)):
		d = os.path.join(CFG, name, "GEN")
		if not os.path.isdir(d):
			continue
		for f in sorted(os.listdir(d)):
			if f.endswith((".c", ".h")):
				out.append(os.path.join(d, f))
	return out


def snapshot():
	"""对"生成链会碰到的全部文件"取哈希。

	范围必须包含注入目标（CanIf_Cfg.c 等）—— 它们不在 GEN/ 下，
	但 sync_*.py 会改写它们，只盯 GEN/ 会漏掉最危险的那类改动。
	"""
	s = {}
	for p in gen_files() + INJECT_FILES:
		if os.path.isfile(p):
			s[rel(p)] = sha(p)
	return s


def run_generate():
	"""按顺序跑五个模块的生成器（force=True，不吃缓存）。"""
	sys.path.insert(0, os.path.join(ROOT, "tools"))
	from generator import Generate

	buf = io.StringIO()
	old = sys.stdout
	sys.stdout = buf
	try:
		Generate(GEN_JSON, force=True)
	finally:
		sys.stdout = old
	txt = buf.getvalue()
	if "Traceback" in txt or "Error" in txt:
		msg = [ln for ln in txt.splitlines() if "Error" in ln or "Traceback" in ln]
		results.append(("C0", False, "生成器报错：" + " | ".join(msg[:3])))


def run_inject():
	for script in INJECT_SCRIPTS:
		p = os.path.join(ROOT, script)
		if not os.path.isfile(p):
			results.append(("C0", False, "缺少注入脚本 %s" % script))
			continue
		r = subprocess.run([sys.executable, p], cwd=ROOT,
						   stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
		if r.returncode != 0:
			results.append(("C0", False, "%s 失败：%s" % (
				script, r.stdout.decode("utf-8", "replace").strip()[-200:])))


def check_c1(s0, s1, s2, verbose):
	"""连跑两遍：第一遍相对原始状态的变化是"重生成带来的"，第二遍必须为零。"""
	changed_1 = sorted([k for k in set(s1) | set(s0) if s0.get(k) != s1.get(k)])
	if changed_1:
		results.append(("C1a", True,
						"首次重生成改动了 %d 个文件（GEN/ 不入库，属正常）：%s"
						% (len(changed_1), ", ".join(changed_1[:4]))))
	else:
		results.append(("C1a", True, "首次重生成零改动（入库副本与产物已同步）"))

	changed_2 = sorted([k for k in set(s2) | set(s1) if s1.get(k) != s2.get(k)])
	if changed_2:
		results.append(("C1b", False,
						"第二遍又改了 %d 个文件，不幂等：%s"
						% (len(changed_2), ", ".join(changed_2[:6]))))
	else:
		results.append(("C1b", True, "连跑两遍逐字节相同（%d 个文件）" % len(s2)))


def check_c2_c3(files):
	no_tag, has_ts = [], []
	for p in files:
		t = read(p)
		if not TAG_RE.search(t):
			no_tag.append(rel(p))
		if TIMESTAMP_RE.search(t):
			has_ts.append(rel(p))
	if no_tag:
		results.append(("C2", False, "缺 @generated 标记：%s" % ", ".join(no_tag)))
	else:
		results.append(("C2", True, "%d 个生成物均带 @generated" % len(files)))
	if has_ts:
		results.append(("C3", False, "仍带生成时间戳：%s" % ", ".join(has_ts)))
	else:
		results.append(("C3", True, "无 wall-clock 时间戳"))


def check_c4():
	bad = []
	for m in GEN_COPY:
		d = os.path.join(CFG, m, "GEN")
		if not os.path.isdir(d):
			bad.append("%s/GEN 不存在" % m)
			continue
		for name in sorted(os.listdir(d)):
			if not name.endswith((".c", ".h")):
				continue
			src = os.path.join(d, name)
			dst = os.path.join(CFG, name)
			if not os.path.isfile(dst):
				bad.append("%s 未拷入 config/" % name)
			elif sha(src) != sha(dst):
				bad.append("%s 与 GEN 版不一致" % name)
	if bad:
		results.append(("C4", False, "；".join(bad) +
						" → 重新生成后请把 GEN/ 的产物拷到 config/（或加 --sync）"))
	else:
		results.append(("C4", True, "config/ 副本与 GEN/ 产物逐字节一致"))


def sync_copy():
	"""把 GEN_COPY 模块的产物拷进 `config/` 根（C4 的修复动作）。

	不放进生成器里做：`tools/generator` 是上游 SSAS 的代码，
	"拷到哪"是本工程自己的约定（见 `doc/配置层约定.md` §3），
	混进去会让下次同步上游时冲突。
	"""
	for m in GEN_COPY:
		d = os.path.join(CFG, m, "GEN")
		for name in sorted(os.listdir(d)):
			if not name.endswith((".c", ".h")):
				continue
			src = os.path.join(d, name)
			dst = os.path.join(CFG, name)
			if os.path.isfile(dst) and sha(src) == sha(dst):
				continue
			io.open(dst, "wb").write(io.open(src, "rb").read())
			print("  sync %s" % rel(dst))


def check_c5():
	bad = []
	for p in INJECT_FILES:
		if not os.path.isfile(p):
			bad.append("%s 不存在" % rel(p))
			continue
		t = read(p)
		nb, ne = len(BEGIN_RE.findall(t)), len(END_RE.findall(t))
		if nb == 0 and ne == 0:
			continue          # 该文件本来就没有生成区块，合法
		if nb != ne:
			bad.append("%s BEGIN/END 不配对（%d/%d）" % (rel(p), nb, ne))
			continue
		# 区块体非空：BEGIN 行之后紧跟 END 视为空区块
		for m in BEGIN_RE.finditer(t):
			tail = t[m.end():]
			nxt = END_RE.search(tail)
			if nxt is not None and tail[:nxt.start()].strip() == "":
				bad.append("%s 存在空生成区块" % rel(p))
	if bad:
		results.append(("C5", False, "；".join(bad)))
	else:
		results.append(("C5", True, "注入区块成对且非空"))


def check_c6():
	"""反向断言：应用层文件里出现 @generated 说明生成器越界改业务代码。"""
	bad = []
	for p in HANDWRITTEN_MUST_CLEAN:
		if not os.path.isfile(p):
			continue
		t = read(p)
		if "@generated" in t:
			bad.append(rel(p))
	if bad:
		results.append(("C6", False, "手写文件被标成生成物：%s" % ", ".join(bad)))
	else:
		results.append(("C6", True, "应用层/手写控制文件均未被生成器触碰"))


def main():
	static = "--static" in sys.argv
	verbose = "-v" in sys.argv
	files = gen_files()
	if not files:
		print("没有找到任何生成物，检查 CFG 路径：%s" % CFG)
		return 1

	if static:
		results.append(("C1", True, "跳过（--static）"))
	else:
		s0 = snapshot()
		run_generate()
		run_inject()
		s1 = snapshot()
		run_generate()
		run_inject()
		s2 = snapshot()
		check_c1(s0, s1, s2, verbose)

	if "--sync" in sys.argv:
		print("== 把 GEN/ 产物拷入 config/ ==")
		sync_copy()

	check_c2_c3(files)
	check_c4()
	check_c5()
	check_c6()

	print("== A4 生成一致性 ==")
	fail = 0
	for code, ok, msg in results:
		print("  [%s] %-4s %s" % ("PASS" if ok else "FAIL", code, msg))
		if not ok:
			fail += 1
	print("-- %d 项断言，%d 项失败" % (len(results), fail))
	return 0 if fail == 0 else 1


if __name__ == "__main__":
	sys.exit(main())
