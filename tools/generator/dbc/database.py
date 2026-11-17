# -*- coding: utf-8 -*-
"""
@file    database.py
@brief   共享 DBC 数据库：一次解析 + 内容缓存 + 节点筛选（02.4）

@details @section DB_WHY 为什么不是"再包一层"
         Com / CanIf / PduR 三个 Generator 各自调 `get_messages(path)`，
         同一份 DBC 在一次联合生成里被解析三遍；节点筛选规则也分散在
         两个模块里（`msg["node"] == me`）。这里只做**三件具体的事**：

         | 事 | 实现 | 不做什么 |
         |----|------|----------|
         | 只解析一次 | 以文件内容 SHA256 + PARSER_VERSION 为键做进程内缓存 | 不做磁盘缓存、LRU、分布式缓存 |
         | 不被调用方改坏 | 每次返回 `deepcopy` | 不做只读视图/写时复制那套 |
         | 统一方向判定 | `classify()` 给出 TX / RX / 排除 | 不在解析阶段过滤（解析只管事实） |

         @section DB_WHY_COPY 为什么必须 deepcopy
         Generator 会就地改消息（例如 Com 把 `msg["id"]` 转成数字、往
         `msg` 上塞 `TxIpduCallout`）。如果缓存直接返回同一个 list，
         第二次调用拿到的就是"被上一个 Generator 改过"的数据 —— 表现
         为"生成顺序不同、产物不同"，而且极难复现。副本是这里唯一正确
         的选择，代价是一次深拷贝。

         @note @section DB_ECU 节点筛选：本项目的矩阵有个前提要说明
         规范规则是"发送方不是本节点、且至少一个信号接收方包含本节点"才
         算 RX。但当前客户矩阵里 **372 个信号的接收方全部是
         `Vector__XXX`**（未指定），严格按规则会把 34 条 RX 报文全部
         排除 —— 等于把整车输入清零。

         因此这里的规则是**三段式**：

         1. 发送方 == 本节点 → TX
         2. 存在显式接收方（非 `Vector__XXX`）：包含本节点 → RX，否则排除
         3. **没有**任何显式接收方（全是 `Vector__XXX`）→ 退回"非发送方即
            RX"，并在消息上标 `dirSpecified=False`，让调用方知道这是推断

         第 3 条不是"宽松"，是这份矩阵的既定含义：接收方一栏没填，不能
         当成"没人收"。等客户补全接收方后，规则 2 会自动接管，不需要改代码。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-17 | binbina | 首版：内容缓存、deepcopy 隔离、三段式节点筛选 |
"""

from copy import deepcopy
from hashlib import sha256
from pathlib import Path

__all__ = ["DbcDatabase", "classify", "BROADCAST_NODES"]

#: 缓存键里的解析器版本。改了 `dbc/__init__.py` 的解析/后处理语义就 +1，
#: 否则同一进程内的旧结果会被当新结果用（例如改字段名后仍拿到旧字段）。
#: 与 `dbc.PARSER_VERSION` 保持一致，由 `_version()` 读取。
PARSER_VERSION = 1

#: DBC 里表示"未指定接收方"的节点名。Vector 工具默认写这个。
BROADCAST_NODES = ("Vector__XXX", "Vector__XXX ")


def _version():
	"""取解析器版本（以 `dbc` 模块为准，避免两处各写一个数字）。"""
	from . import PARSER_VERSION as v
	return v


class DbcDatabase:
	"""进程内 DBC 缓存。

	用法：
	    db = DbcDatabase()
	    msgs = db.get_messages("can1.dbc")     # 副本，可随意修改
	    rx = classify(msgs, "BCM")

	同一进程里对**相同内容**重复调用只解析一次；不同路径、相同内容共享
	缓存（键是内容哈希，不是路径）。
	"""

	def __init__(self):
		self._cache = {}
		self.parses = 0   # 实际调用解析器的次数（测试用来证明"只解析一次"）
		self.hits = 0

	def get_messages(self, path):
		"""读文件 → 命中缓存则返回副本，未命中则解析并缓存。"""
		from . import parse_content

		content = Path(path).read_bytes()
		key = (sha256(content).hexdigest(), PARSER_VERSION, _version())

		if key in self._cache:
			self.hits += 1
			return deepcopy(self._cache[key])

		# 解析失败不写缓存：坏文件下次仍然会报错，而不是被"缓存成空列表"
		parsed = parse_content(content.decode("utf-8", errors="replace"), str(path))
		msgs = parsed["messages"]
		self.parses += 1
		self._cache[key] = msgs
		return deepcopy(msgs)

	def clear(self):
		"""清空缓存（测试用）。"""
		self._cache.clear()


def classify(messages, ecu):
	"""按本 ECU 给每条报文定方向，并剔除与本 ECU 无关的报文。

	返回**新的 list**，每项是消息的浅拷贝，额外带：

	| 字段 | 含义 |
	|------|------|
	| `dir` | `"TX"` / `"RX"` |
	| `dirSpecified` | True = 接收方明确写了；False = 靠"非发送方即接收"推断 |

	@param messages 解析结果（不会被修改）
	@param ecu      本节点名（来自项目配置，不写死 BCM）
	"""
	out = []
	for m in messages:
		recv = set()
		specified = False
		for s in m.get("signals", []):
			for n in s.get("node", []) or []:
				if n and n not in BROADCAST_NODES:
					specified = True
					recv.add(n)

		if m.get("node") == ecu:
			d = "TX"
			specified = True   # 发送方本身就是明确的
		elif specified:
			d = "RX" if ecu in recv else None
		else:
			d = "RX"           # 接收方一栏没填：不能当成"没人收"

		if d is None:
			continue

		m2 = dict(m)
		m2["dir"] = d
		m2["dirSpecified"] = specified
		out.append(m2)
	return out
