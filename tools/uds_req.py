#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    uds_req.py
@brief   发一条 UDS 请求并打印响应（可发完就走，不保持连接）

@details @section WHY 为什么需要单发工具

          `uds_flash.py` 是一条龙刷写，`m3_check.py` 是一整套回归 —— 都不适合
          "只发一条 `10 02` 然后撒手不管"这种验证。而 22.3 的 H4/H5 正是：

          | 用例 | 动作 |
          |------|------|
          | H4 | 发 `10 02` → App 写刷写标志并复位 → boot 进 UDS → **诊断仪不再连接** → 30 s 后自动回退正常启动 |
          | H5 | 同上，但 30 s 内开始刷写 → 不应超时 |

          H4 的关键是"发完就走"。本工具默认就是发完打印响应然后退出，
          不会像回归脚本那样持续轮询 —— 那个轮询会让 boot 认为"诊断仪还在"。

@note    只用标准帧 0x7E0/0x7E8、500 kbps，与 `Board.json` 的 CAN 配置一致。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-17 | binbina | 首版：单条 UDS 请求 + 可选等待 |
"""

import argparse
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import can  # noqa: E402

from isotp_lite import Isotp  # noqa: E402

REQ_ID = 0x7E0
RES_ID = 0x7E8


def main():
	ap = argparse.ArgumentParser(description="发一条 UDS 请求（默认发完即走）")
	ap.add_argument("--req", default="10 02", help="请求字节，空格分隔的十六进制，默认 10 02")
	ap.add_argument("--channel", type=int, default=0, help="Kvaser 通道号")
	ap.add_argument("--bitrate", type=int, default=500000)
	ap.add_argument("--timeout", type=float, default=2.0, help="等响应的秒数")
	ap.add_argument("--hold", type=float, default=0.0,
	                help="收到响应后继续保持连接 N 秒（H5 用；H4 保持 0 即'发完就走'）")
	ap.add_argument("--repeat-gap", type=float, default=0.0,
	                help="保持期间每隔 N 秒补发一次 3E 00（TesterPresent），默认不发")
	a = ap.parse_args()

	req = bytes(int(x, 16) for x in a.req.replace(",", " ").split())
	if not req:
		raise SystemExit("--req 为空")

	print("== UDS 单发 ==")
	print("请求 %s → 0x%03X（响应 0x%03X），通道 %d @ %d"
	      % (req.hex(" ").upper(), REQ_ID, RES_ID, a.channel, a.bitrate))

	bus = can.Bus(interface="kvaser", channel=a.channel, bitrate=a.bitrate)
	tp = Isotp(bus, REQ_ID, RES_ID)

	try:
		t0 = time.time()
		resp = tp.request(req, timeout=a.timeout)
		dt = (time.time() - t0) * 1000.0

		if resp is None:
			print("响应：**超时**（%.0f ms）" % dt)
			rc = 1
		else:
			print("响应：%s（%.0f ms）" % (resp.hex(" ").upper(), dt))
			rc = 0 if resp[0] != 0x7F else 2

		if a.hold > 0.0:
			print("保持连接 %.1f s（%s TesterPresent）..."
			      % (a.hold, ("每 %.1f s 发" % a.repeat_gap) if a.repeat_gap > 0 else "不发"))
			t_end = time.time() + a.hold
			while time.time() < t_end:
				if a.repeat_gap > 0.0:
					time.sleep(min(a.repeat_gap, max(0.0, t_end - time.time())))
					tp.request(b"\x3e\x00", timeout=0.3)
				else:
					time.sleep(0.05)
			print("保持结束，工具退出（此后 ECU 侧不会再收到诊断请求）")

		return rc
	finally:
		try:
			bus.shutdown()
		except Exception:
			pass


if __name__ == "__main__":
	sys.exit(main())
