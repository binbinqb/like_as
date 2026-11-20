#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    config_editor.py
@brief   项目适配层：把上游 `tools/json.editor`（PyQt5 配置 GUI）接到本仓库配置链

@details 上游编辑器原样保留，本文件只做四件"接缝"的事：

          | 接缝 | 上游默认 | 本项目 |
          |---|---|---|
          | JSON 方言 | PascalCase（`Networks`） | camelCase（`networks`）→ **按现有 JSON 自动推导 schema** |
          | 模块集合 | 14 个 AUTOSAR 模块 | Board / Can / Shell / Com / CanIf / PduR |
          | 保存 | 直接写 JSON（schema 外字段会丢） | **先写临时副本 + 字段树对比**，确认不丢字段才回写真源 |
          | 生成 | 调用自带的 generator | 调 `tools/config.py generate`（含 sync/注入/Com 拷入） |

          @section SEC 保存守卫为什么必须有
          schema 是"编辑器认识的字段"的白名单，不在 schema 里的键在保存时会被
          静默丢掉。本项目的 JSON 带 `_comment`、`shimPrefixRx`、`hohFrom` 等
          项目字段，一旦丢失，生成器行为会悄悄变化。所以保存前比较**字段路径集合**，
          缺一个就拒绝写盘并列出来。

          @section USAGE 用法
          ```
          python tools/config_editor.py              # 打开（GUI）
          python tools/config_editor.py --check      # 只检查 schema 覆盖率
          python tools/config_editor.py --make-schema# 重新推导项目 schema
          python tools/config_editor.py --self-test  # 无界面自检（CI 可用）
          ```

@author  binbina
@version V1.0.0
"""

import argparse
import importlib.util
import io
import json
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CFG = os.path.join(ROOT, "app", "platform", "cvm0146", "src", "config")
EDITOR_DIR = os.path.join(ROOT, "tools", "json.editor")
SCHEMA_PROJECT = os.path.join(EDITOR_DIR, "schema.project.json")
TMP_DIR = os.path.join(ROOT, "build", "config", "editor")

# 本项目实际维护的配置模块（顺序即 GUI 标签页顺序）
MODULES = [
	("Board", os.path.join(CFG, "Board", "Board.json")),
	("Can", os.path.join(CFG, "Can", "Can.json")),
	("Shell", os.path.join(CFG, "Shell", "Shell.json")),
	("CanIf", os.path.join(CFG, "CanIf", "CanIf.json")),
	("PduR", os.path.join(CFG, "PduR", "PduR.json")),
	("Com", os.path.join(CFG, "Com", "Com.json")),
]


# ============================ [ JSON 工具 ] ============================

def load_json(path):
	with io.open(path, encoding="utf-8") as f:
		return json.load(f)


def key_paths(obj, prefix=""):
	"""字段路径集合：只关心"有哪些字段"，不关心数组长度与取值。"""
	out = set()
	if isinstance(obj, dict):
		for k, v in obj.items():
			p = "%s.%s" % (prefix, k)
			out.add(p)
			out |= key_paths(v, p)
	elif isinstance(obj, list):
		for v in obj:
			out |= key_paths(v, prefix + "[]")
	return out


def detect_indent(path, default=2):
	try:
		lines = io.open(path, encoding="utf-8").read().splitlines()
	except Exception:  # noqa: BLE001
		return default
	for ln in lines[1:]:
		if ln.strip():
			return max(1, len(ln) - len(ln.lstrip()))
	return default


def _fmt(v, lv, ind):
	"""保形序列化：标量列表与"扁平字典列表"压成一行（Board 的 ports/schedule 风格）。"""
	pad = " " * (ind * lv)
	if isinstance(v, dict):
		if not v:
			return "{}"
		rows = []
		for k, val in v.items():
			rows.append("%s%s: %s" % (" " * (ind * (lv + 1)),
			                          json.dumps(k, ensure_ascii=False),
			                          _fmt(val, lv + 1, ind)))
		return "{\n" + ",\n".join(rows) + "\n" + pad + "}"
	if isinstance(v, list):
		if not v:
			return "[]"
		if all(not isinstance(x, (dict, list)) for x in v):
			return "[" + ", ".join(json.dumps(x, ensure_ascii=False) for x in v) + "]"
		if all(isinstance(x, dict) and
		       all(not isinstance(y, (dict, list)) for y in x.values()) for x in v):
			rows = []
			for x in v:
				body = ", ".join("%s: %s" % (json.dumps(k, ensure_ascii=False),
				                            json.dumps(val, ensure_ascii=False))
				                 for k, val in x.items())
				rows.append("%s{ %s }" % (" " * (ind * (lv + 1)), body))
			return "[\n" + ",\n".join(rows) + "\n" + pad + "]"
		rows = [" " * (ind * (lv + 1)) + _fmt(x, lv + 1, ind) for x in v]
		return "[\n" + ",\n".join(rows) + "\n" + pad + "]"
	return json.dumps(v, ensure_ascii=False)


def dump_preserve(path, obj, indent=None):
	if indent is None:
		indent = detect_indent(path)
	with io.open(path, "w", encoding="utf-8", newline="\n") as f:
		f.write(_fmt(obj, 0, indent) + "\n")


# ============================ [ schema 推导 ] ============================

def infer(v):
	"""从现有 JSON 推导 schema 片段。数组元素做并集，保证不丢字段。"""
	if isinstance(v, bool):
		return {"type": "bool", "default": v}
	if isinstance(v, int):
		return {"type": "integer", "default": v}
	if isinstance(v, float):
		return {"type": "number", "default": v}
	if isinstance(v, str):
		return {"type": "string", "default": v}
	if isinstance(v, list):
		return {"type": "array", "items": infer_list(v)}
	if isinstance(v, dict):
		return {"type": "object",
		        "properties": {k: infer(val) for k, val in v.items()}}
	return {"type": "string", "default": ""}


def merge_schema(a, b):
	"""合并两个推导结果：对象合并字段、数组合并元素，宁可多收不可漏。"""
	if a is None:
		return b
	if b is None:
		return a
	ta, tb = a.get("type"), b.get("type")
	if ta == "object" and tb == "object":
		props = dict(a.get("properties", {}))
		for k, v in b.get("properties", {}).items():
			props[k] = merge_schema(props.get(k), v)
		return {"type": "object", "title": a.get("title") or b.get("title") or "Item",
		        "properties": props}
	if ta == "array" and tb == "array":
		return {"type": "array", "items": merge_schema(a.get("items"), b.get("items"))}
	# 类型冲突：优先结构化的一方
	if ta in ("object", "array"):
		return a
	if tb in ("object", "array"):
		return b
	return a


def _item(s):
	"""上游 JsonArray 强制要求 items 带 title，缺了会 KeyError。"""
	if "title" not in s:
		s = dict(s)
		s["title"] = "Item"
	return s


def infer_list(items):
	"""数组元素并集：所有元素出现过的字段合并成一个 object 模板。"""
	if not items:
		return _item({"type": "string", "default": ""})
	if all(isinstance(x, dict) for x in items):
		merged = {}
		for x in items:
			for k, val in x.items():
				merged[k] = merge_schema(merged.get(k), infer(val))
		return _item({"type": "object", "title": "Item", "properties": merged})
	if any(isinstance(x, (dict, list)) for x in items):
		out = None
		for x in items:
			out = merge_schema(out, infer(x))
		return _item(out if out is not None else {"type": "string", "default": ""})
	return _item(infer(items[0]))


def make_schema():
	out = []
	for title, path in MODULES:
		if not os.path.isfile(path):
			print("  [SKIP] 缺少 %s" % path)
			continue
		cfg = load_json(path)
		props = {k: infer(v) for k, v in cfg.items()}
		# 编辑器用 `Class` 识别模块；真实文件里是小写 `class`
		props["Class"] = {"type": "string", "default": title}
		out.append({"title": title, "type": "object", "properties": props})
		print("  %-6s %3d 个顶层字段  ← %s" % (title, len(props), os.path.relpath(path, ROOT)))
	with io.open(SCHEMA_PROJECT, "w", encoding="utf-8", newline="\n") as f:
		json.dump(out, f, ensure_ascii=False, indent=2)
		f.write("\n")
	print("schema：%s" % os.path.relpath(SCHEMA_PROJECT, ROOT))
	return out


def flatten_schema_paths(schema, prefix=""):
	out = set()
	if "properties" in schema:
		for k, v in schema["properties"].items():
			p = "%s.%s" % (prefix, k)
			out.add(p)
			out |= flatten_schema_paths(v, p)
	elif schema.get("type") == "array":
		out |= flatten_schema_paths(schema.get("items", {}), prefix + "[]")
	return out


def check_coverage(schemas):
	"""每个 JSON 的字段路径必须全部出现在 schema 里（否则保存会丢）。"""
	by_title = {s["title"]: s for s in schemas}
	bad = 0
	for title, path in MODULES:
		if (title not in by_title) or (not os.path.isfile(path)):
			continue
		cfg = load_json(path)
		need = key_paths(cfg)
		have = flatten_schema_paths(by_title[title])
		missing = sorted(need - have)
		if missing:
			bad += 1
			print("  FAIL  %-6s 缺 %d 个字段：%s" % (title, len(missing), missing[:6]))
		else:
			print("  PASS  %-6s %d 个字段全覆盖" % (title, len(need)))
	return bad == 0


# ============================ [ 上游加载 ] ============================

def load_upstream():
	if EDITOR_DIR not in sys.path:
		sys.path.insert(0, EDITOR_DIR)
	spec = importlib.util.spec_from_file_location(
		"as_json_editor_main", os.path.join(EDITOR_DIR, "main.py"))
	mod = importlib.util.module_from_spec(spec)
	spec.loader.exec_module(mod)
	return mod


# ============================ [ 编辑器子类 ] ============================

def prepare_tmp():
	"""把真源复制到临时目录并注入 `Class`（不污染真源）。"""
	if os.path.isdir(TMP_DIR):
		for fn in os.listdir(TMP_DIR):
			if fn.endswith(".json"):
				os.remove(os.path.join(TMP_DIR, fn))
	os.makedirs(TMP_DIR, exist_ok=True)

	mapping = []
	for title, path in MODULES:
		if not os.path.isfile(path):
			continue
		cfg = dict(load_json(path))
		cfg["Class"] = title
		tmp = os.path.join(TMP_DIR, "%s.json" % title)
		with io.open(tmp, "w", encoding="utf-8", newline="\n") as f:
			json.dump(cfg, f, ensure_ascii=False, indent=2)
		mapping.append((title, tmp, path))
	return mapping


def build_editor_class(up):
	from PyQt5.QtWidgets import QMessageBox

	class ProjectEditor(up.JsonEditor):
		def __init__(self, args, mapping):
			self._mapping = mapping
			super(ProjectEditor, self).__init__(args)  # noqa: UP008
			for _title, tmp, _real in mapping:
				self.mLoad(tmp)

		def mLoad(self, jsonFile=None):
			"""覆盖上游：跳过 EcuC 自动登记（它写死了 PascalCase 的 Networks）。"""
			if not isinstance(jsonFile, str) or not os.path.isfile(jsonFile):
				return
			cfg = load_json(jsonFile)
			if isinstance(cfg, dict):
				self.cfgMap[cfg["Class"]] = jsonFile
				cfg = [cfg]
			titles = [x["title"] for x in self.schema]
			for m in cfg:
				if m.get("Class") in titles:
					self.reload(m["Class"], m)

		def mSave(self):
			changed, blocked = [], []
			for title, _tmp, real in self._mapping:
				mod = self.modules.get(title)
				if mod is None:
					continue
				cfg = mod.toJSON()
				cfg.pop("Class", None)
				orig = load_json(real)
				missing = key_paths(orig) - key_paths(cfg)
				if missing:
					blocked.append("%s：会丢 %s%s"
					               % (title, ", ".join(sorted(missing)[:5]),
					                  " …" if len(missing) > 5 else ""))
					continue
				dump_preserve(real, cfg)
				changed.append(title)

			if blocked:
				QMessageBox.critical(None, "保存被拒绝（会丢字段）",
				                     "以下模块未写入：\n\n" + "\n".join(blocked) +
				                     "\n\n处理：把这些字段补进 schema（config_editor.py 的 infer 会自动收录），或先在 JSON 里改名。")
			else:
				QMessageBox.information(None, "已保存",
				                        "已回写真源：%s\n\n下一步：File → Generate 走本仓库生成链。"
				                        % ("、".join(changed) if changed else "（无改动）"))

		def mGen(self):
			r = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "config.py"), "generate"],
			                   cwd=ROOT, capture_output=True, text=True)
			out = (r.stdout + r.stderr).strip()
			if r.returncode == 0:
				QMessageBox.information(None, "生成完成",
				                        "tools/config.py generate 成功。\n\n" + out[-1200:])
			else:
				QMessageBox.critical(None, "生成失败",
				                     "rc=%d\n\n%s" % (r.returncode, out[-1500:]))

	return ProjectEditor


# ============================ [ 入口 ] ============================

def ensure_schema():
	if not os.path.isfile(SCHEMA_PROJECT):
		print("未找到项目 schema，先推导：")
		return make_schema()
	return load_json(SCHEMA_PROJECT)


def cmd_self_test():
	"""无界面自检：加载 → toJSON → 字段树与真源一致（不写盘）。"""
	os.environ.setdefault("QT_QPA_PLATFORM", "offscreen")
	from PyQt5.QtWidgets import QApplication

	schemas = ensure_schema()
	if not check_coverage(schemas):
		return 1

	up = load_upstream()
	ProjectEditor = build_editor_class(up)
	mapping = prepare_tmp()
	app = QApplication(sys.argv)  # noqa: F841
	ed = ProjectEditor(argparse.Namespace(schema=SCHEMA_PROJECT, input=None), mapping)

	bad = 0
	for title, _tmp, real in mapping:
		mod = ed.modules.get(title)
		if mod is None:
			print("  FAIL  %-6s 未加载" % title)
			bad += 1
			continue
		cfg = mod.toJSON()
		cfg.pop("Class", None)
		miss = key_paths(load_json(real)) - key_paths(cfg)
		if miss:
			bad += 1
			print("  FAIL  %-6s 回写会丢：%s" % (title, sorted(miss)[:6]))
		else:
			print("  PASS  %-6s 加载/回写字段树一致" % title)
	print("-- self-test: %s" % ("PASS" if bad == 0 else "FAIL"))
	return 0 if bad == 0 else 1


def main():
	ap = argparse.ArgumentParser(description="本项目配置编辑器（上游 json.editor 的适配入口）")
	ap.add_argument("--make-schema", action="store_true", help="从现有 JSON 重新推导 schema.project.json")
	ap.add_argument("--check", action="store_true", help="只检查 schema 覆盖率（不启动 GUI）")
	ap.add_argument("--self-test", action="store_true", help="无界面加载/回写自检")
	args = ap.parse_args()

	if args.make_schema:
		make_schema()
		return 0
	if args.check:
		return 0 if check_coverage(ensure_schema()) else 1
	if args.self_test:
		return cmd_self_test()

	from PyQt5.QtGui import QFont
	from PyQt5.QtWidgets import QApplication

	ensure_schema()
	up = load_upstream()
	ProjectEditor = build_editor_class(up)
	mapping = prepare_tmp()

	qtApp = QApplication(sys.argv)
	qtApp.setFont(QFont("Consolas"))
	ed = ProjectEditor(argparse.Namespace(schema=SCHEMA_PROJECT, input=None), mapping)
	ed.show()
	return qtApp.exec_()


if __name__ == "__main__":
	sys.exit(main())
