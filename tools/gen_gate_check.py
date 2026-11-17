#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    gen_gate_check.py
@brief   配置生成门禁（`gen_gate.py`）的自测：十四个场景，逐条证伪

@details @section WHY 为什么门禁要有自测

         门禁的错误方式有两种，且**都很难在正常构建中发现**：

         - 判成 `skip` 但其实该生成 → 改了 JSON 不生效。构建成功、日志干净，
           只有上板才对不上，排查方向会歪到驱动上去。
         - 判成 `run` 但其实不用生成 → 每次构建白花 7.2 s，人会开始绕开它
           （直接改 config/ 里的 .c），门禁形同废纸。

         所以不能只测"正常路径"。这里用临时目录造一棵**缺陷树**，把
         输入变化 / 产物漂移 / 缺 DBC / 缺 JSON / 并发锁逐条打一遍。

         @section METHOD 为什么不 mock

         判定逻辑全在纯函数里（`compute()` / `check()` / `load_state()`），
         它们都接受 `root` 参数。所以直接喂一棵假树就行，不需要替身：
         测的是真代码，不是替身的替身。

         ⚠ 这里**只测判定**，不测生成链本身。生成链的等价性由
         `a4_gen_check.py`（C1~C6）与 `can_table_check.py`（67 项）负责。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-17 | binbina | 首版：14 个场景 |
"""

import io
import os
import shutil
import sys
import tempfile
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import gen_gate  # noqa: E402

results = []


def record(code, ok, msg):
	results.append((code, ok, msg))
	print("  [%s] %-4s %s" % ("PASS" if ok else "FAIL", code, msg))


def write(path, text, newline=None):
	os.makedirs(os.path.dirname(path), exist_ok=True)
	with io.open(path, "w", encoding="utf-8", newline=newline) as f:
		f.write(text)


def read(path):
	with io.open(path, encoding="utf-8") as f:
		return f.read()


def cfg_of(root):
	return os.path.join(root, *gen_gate.CFG_REL.split("/"))


def make_tree(tmp, with_dbc=True):
	"""造一棵最小的"仓库"：输入、产物、生成器源码都齐。"""
	cfg = cfg_of(tmp)
	for rel in gen_gate.INPUT_JSON:
		write(os.path.join(cfg, *rel.split("/")), "// %s\n" % rel)
	if with_dbc:
		for rel in gen_gate.INPUT_DBC:
			write(os.path.join(cfg, *rel.split("/")), "// %s\n" % rel)
	for name in gen_gate.ARTIFACTS:
		write(os.path.join(cfg, name), "/* %s */\n" % name)
	for rel in gen_gate.INPUT_TOOLS:
		write(os.path.join(tmp, *rel.split("/")), "# %s\n" % rel)
	write(os.path.join(tmp, *gen_gate.INPUT_GEN_DIR.split("/"), "Can.py"), "# gen\n")


def new_tree(with_dbc=True):
	tmp = tempfile.mkdtemp(prefix="gen_gate_")
	make_tree(tmp, with_dbc)
	return tmp


def act(root, force=False):
	action, reason, detail = gen_gate.check(root, force=force)
	return action, reason, detail


def expect(root, want, kw="", force=False):
	action, reason, detail = act(root, force)
	ok = action == want and (kw == "" or kw in reason)
	return ok, "%s → %s（%s）" % (want, action, reason), detail


# ============================== 场景 ==============================


def case_basic():
	"""G1~G3：首次该生成、生成完该跳过、改了 JSON 该重新生成。"""
	tmp = new_tree()
	try:
		ok, msg, _ = expect(tmp, "run", "首次")
		record("G1", ok, "无状态 → run：" + msg)

		gen_gate.save_state(tmp)
		ok, msg, _ = expect(tmp, "skip")
		record("G2", ok, "生成后 → skip：" + msg)

		p = os.path.join(cfg_of(tmp), "CanIf", "CanIf.json")
		write(p, read(p) + "// touched\n")
		ok, msg, detail = expect(tmp, "run", "CanIf.json")
		record("G3", ok and "CanIf/CanIf.json" in detail,
		       "改 CanIf.json → run 且指名到文件：" + msg)
	finally:
		shutil.rmtree(tmp, ignore_errors=True)


def case_matrix():
	"""G4：换一版 DBC 必须重新生成（这是最容易被漏掉的输入）。"""
	tmp = new_tree()
	try:
		gen_gate.save_state(tmp)
		p = os.path.join(cfg_of(tmp), "dbc", "can1.dbc")
		write(p, read(p) + "// V0.5\n")
		ok, msg, detail = expect(tmp, "run", "can1.dbc")
		record("G4", ok and "dbc/can1.dbc" in detail, "改 can1.dbc → run：" + msg)
	finally:
		shutil.rmtree(tmp, ignore_errors=True)


def case_generator():
	"""G5：改生成器 = 改产物；新增一个生成器文件也算。"""
	tmp = new_tree()
	try:
		gen_gate.save_state(tmp)
		p = os.path.join(tmp, *gen_gate.INPUT_GEN_DIR.split("/"), "Com.py")
		write(p, "# new generator\n")
		ok, msg, _ = expect(tmp, "run", "Com.py")
		record("G5", ok, "新增 tools/generator/Com.py → run：" + msg)
	finally:
		shutil.rmtree(tmp, ignore_errors=True)


def case_artifact_drift():
	"""G6~G8：产物被改 / 丢失要重生成；只换行尾（CRLF↔LF）不算改。"""
	tmp = new_tree()
	try:
		gen_gate.save_state(tmp)
		p = os.path.join(cfg_of(tmp), "Com_Cfg.c")
		write(p, read(p) + "/* hand edit */\n")
		ok, msg, _ = expect(tmp, "run", "产物")
		record("G6", ok, "手改产物 Com_Cfg.c → run：" + msg)

		gen_gate.save_state(tmp)
		p = os.path.join(cfg_of(tmp), "CanIf_Cfg.h")
		os.remove(p)
		ok, msg, _ = expect(tmp, "run", "产物")
		record("G7", ok, "删产物 CanIf_Cfg.h → run：" + msg)

		gen_gate.save_state(tmp)
		p = os.path.join(cfg_of(tmp), "Com_Cfg.c")
		body = read(p).replace("\n", "\r\n")
		write(p, body, newline="")
		ok, msg, _ = expect(tmp, "skip")
		record("G8", ok, "产物转成 CRLF（内容等价）→ 仍 skip：" + msg)
	finally:
		shutil.rmtree(tmp, ignore_errors=True)


def case_no_dbc():
	"""G9~G11：缺客户 DBC 的三条路径（这是新克隆机器上的真实状态）。"""
	tmp = new_tree(with_dbc=False)
	try:
		ok, msg, _ = expect(tmp, "degrade", "DBC")
		record("G9", ok, "缺 DBC + 无状态 → degrade：" + msg)

		gen_gate.save_state(tmp)
		ok, msg, _ = expect(tmp, "skip")
		record("G10", ok, "缺 DBC + 输入未变 → skip：" + msg)

		p = os.path.join(cfg_of(tmp), "Com", "Com.json")
		write(p, read(p) + "// touched\n")
		ok, msg, _ = expect(tmp, "blocked", "DBC")
		record("G11", ok, "缺 DBC + 改了 JSON → blocked：" + msg)
	finally:
		shutil.rmtree(tmp, ignore_errors=True)


def case_force_and_missing_src():
	"""G12~G13：--force 无条件生成；配置源本身缺失要拦住。"""
	tmp = new_tree()
	try:
		gen_gate.save_state(tmp)
		ok, msg, _ = expect(tmp, "run", "--force", force=True)
		record("G12", ok, "配置未变 + --force → run：" + msg)

		os.remove(os.path.join(cfg_of(tmp), "PduR", "PduR.json"))
		ok, msg, _ = expect(tmp, "blocked", "配置源缺失")
		record("G13", ok, "缺 PduR.json → blocked：" + msg)
	finally:
		shutil.rmtree(tmp, ignore_errors=True)


def case_lock():
	"""G14：生成锁互斥，释放后可再拿（App / AppB 并发构建的串行化）。"""
	tmp = new_tree()
	try:
		first = gen_gate.acquire_lock(tmp, timeout=1)
		t0 = time.time()
		second = gen_gate.acquire_lock(tmp, timeout=0.4)
		waited = time.time() - t0
		gen_gate.release_lock(tmp)
		third = gen_gate.acquire_lock(tmp, timeout=1)
		gen_gate.release_lock(tmp)
		ok = first and (not second) and third and 0.3 < waited < 5
		record("G14", ok, "锁互斥并释放：first=%s second=%s third=%s 等待 %.1fs"
		       % (first, second, third, waited))
	finally:
		shutil.rmtree(tmp, ignore_errors=True)


def case_fingerprint_integrity():
	"""G15：**整体指纹必须真的参与判定**。

	这是首版的一个真缺陷：`fingerprint` 算出来了却只用来存盘，判定只看
	"逐文件差异"。那样一来，**被跟踪的输入集发生变化**（往 INPUT_TOOLS
	里加/删一个脚本）时，逐文件比对看不到任何差异（`now` 里根本没有那个 key），
	于是判成 skip —— 改了门禁自己的输入范围，却不重新生成。

	复现方式就是真改一次输入集：临时从 INPUT_TOOLS 里摘掉一项。
	"""
	tmp = new_tree()
	saved = list(gen_gate.INPUT_TOOLS)
	try:
		gen_gate.save_state(tmp)
		gen_gate.INPUT_TOOLS.remove("tools/config.py")  # 模拟"输入集变了"
		ok, msg, _ = expect(tmp, "run", "指纹变化")
		record("G15", ok, "被跟踪输入集变化 → run：" + msg)
	finally:
		gen_gate.INPUT_TOOLS[:] = saved
		shutil.rmtree(tmp, ignore_errors=True)


def main():
	print("== 配置生成门禁自测（gen_gate.py）==")
	base = new_tree()
	try:
		print("临时树：%s" % base)
	finally:
		shutil.rmtree(base, ignore_errors=True)

	case_basic()
	case_matrix()
	case_generator()
	case_artifact_drift()
	case_no_dbc()
	case_force_and_missing_src()
	case_lock()
	case_fingerprint_integrity()

	fail = sum(1 for _c, ok, _m in results if not ok)
	print("-- %d 个场景，%d 项失败" % (len(results), fail))
	return 0 if fail == 0 else 1


if __name__ == "__main__":
	sys.exit(main())
