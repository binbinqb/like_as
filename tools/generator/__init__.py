# SSAS - Simple Smart Automotive Software
# Copyright (C) 2021 Parai Wang <parai@foxmail.com>

import os
import json
import pickle
import hashlib

from .NvM import Gen as NvMGen
from .RoD import Gen as RoDGen
from .Dem import Gen as DemGen
from .Com import Gen as ComGen
from .Net import Gen as NetGen
from .Factory import Gen as FactoryGen
from .MemCluster import Gen as MCGen
from .PduR import Gen as PduRGen
from .CanTp import Gen as CanTpGen
from .LinTp import Gen as LinTpGen
from .CanIf import Gen as CanIfGen
from .CanNm import Gen as CanNmGen
from .OsekNm import Gen as OsekNmGen
from .Nm import Gen as NmGen
from .CanSM import Gen as CanSMGen
from .ComM import Gen as ComMGen
from .Rte import Gen as RteGen
from .protoc import Gen as ProtocGen
from .Os import Gen as OsGen
from .Dcm import Gen as DcmGen
from .Trace import Gen as TraceGen
from .Xcp import Gen as XcpGen
from .LinIf import Gen as LinIfGen
from .J1939Tp import Gen as J1939TpGen
from .Csm import Gen as CsmGen
from .SecOC import Gen as SecOCGen
from .E2E import Gen as E2EGen
from .TLS import Gen as TLSGen
from .Mirror import Gen as MirrorGen
from .BL import Gen as BLGen
from .Shell import Gen as ShellGen
from .Board import Gen as BoardGen

def DummyGen(cfg):
    pass


__GEN__ = {
    "NvM": NvMGen,
    "RoD": RoDGen,
    "Dem": DemGen,
    "Com": ComGen,
    "Net": NetGen,
    "Factory": FactoryGen,
    "MemCluster": MCGen,
    "PduR": PduRGen,
    "CanTp": CanTpGen,
    "LinTp": LinTpGen,
    "CanIf": CanIfGen,
    "Rte": RteGen,
    "protoc": ProtocGen,
    "OS": OsGen,
    "Dcm": DcmGen,
    "Trace": TraceGen,
    "EcuC": DummyGen,
    "Xcp": XcpGen,
    "LinIf": LinIfGen,
    "J1939Tp": J1939TpGen,
    "CanNm": CanNmGen,
    "OsekNm": OsekNmGen,
    "Nm": NmGen,
    "CanSM": CanSMGen,
    "ComM": ComMGen,
    "Csm": CsmGen,
    "SecOC": SecOCGen,
    "E2E": E2EGen,
    "TLS": TLSGen,
    "Mirror": MirrorGen,
    "BL": BLGen,
    "Shell": ShellGen,
    "Board": BoardGen,
}

RootDir = os.path.abspath(os.path.dirname(__file__) + "/../..")

# 生成器源码摘要的进程级缓存（见 _gen_src_digest）
_GEN_SRC_DIGEST = None


def GetGen(cfg):
    if cfg.endswith(".json"):
        with open(cfg) as f:
            con = json.load(f)
            if "class" in con:
                cls = con["class"]
                if cls in __GEN__:
                    return cls, __GEN__[cls]
                else:
                    raise Exception("class %s is not supported" % (cls))
            else:
                raise
    else:
        raise


def _gen_src_digest():
    """生成器自身源码（`tools/generator/**.py`）的摘要，进程内只算一次。

    @note 跳过 `parsetab.py`：那是 PLY 解析 DBC 时**自动生成**的表缓存
          （`.gitignore` 里），内容随首次解析产生，不属于"生成器源码"。
          把它算进来会让"第一次生成"和"第二次生成"的哈希不同，
          平白多跑一轮。
    """
    global _GEN_SRC_DIGEST
    if _GEN_SRC_DIGEST is not None:
        return _GEN_SRC_DIGEST
    md5 = hashlib.md5()
    base = os.path.dirname(os.path.abspath(__file__))
    for cur, dirs, files in os.walk(base):
        dirs[:] = sorted(d for d in dirs if d != "__pycache__")
        for fn in sorted(files):
            if not fn.endswith(".py") or fn == "parsetab.py":
                continue
            p = os.path.join(cur, fn)
            md5.update(os.path.relpath(p, base).replace(os.sep, "/").encode("utf-8"))
            with open(p, "rb") as f:
                md5.update(f.read())
    _GEN_SRC_DIGEST = md5.hexdigest()
    return _GEN_SRC_DIGEST


def CalcHash(js):
    L = [js]
    with open(js) as f:
        cfg = json.load(f)
        for cls in ["Com", "CanIf", "PduR"]:
            if cfg.get("class", None) == cls:
                for n in cfg.get("networks", []):
                    for x in ["dbc", "ldf"]:
                        path = n.get(x, None)
                        if path != None:
                            if not os.path.isfile(path):
                                path = os.path.join(os.path.dirname(js), path)
                            L.append(path)
        for cls, key in [("Dcm", "excel"), ("Rte", "py"), ("protoc", "entry")]:
            if cfg.get("class", None) == cls:
                path = cfg.get(key, None)
                if path != None:
                    if not os.path.isfile(path):
                        path = os.path.join(os.path.dirname(js), path)
                        L.append(path)
    md5 = hashlib.md5()
    for f in L:
        md5.update(open(f, "rb").read())
    # 生成器自身的源码也必须进缓存键。
    #
    # 原先只哈希 JSON + DBC，于是"改了生成器、JSON 没动"时 `Generate()`
    # 判定"没变化"，直接返回上次结果 —— 改了却不生效，且没有任何提示。
    # 实测踩到：给 `Com.py` 插一行注释输出，连跑两遍产物一个字节都没变。
    # （`a4_gen_check` 的 C1 幂等判据抓不到这种"稳定地不更新"。）
    md5.update(_gen_src_digest().encode("ascii"))
    new_hash = md5.hexdigest()
    return new_hash


def Generate(cfgs, force=False):
    source = {}
    db = {}
    dbpath = "%s/.gendb.pkl" % (RootDir)
    if os.path.isfile(dbpath):
        try:
            with open(dbpath, "rb") as f:
                db = pickle.load(f)
        except Exception:
            # 缓存坏了不算错误：当没有缓存处理，最坏结果是多生成一次。
            # 为什么会坏：App / AppB 两个构建并发时同时 dump 同一个文件，
            # 旧实现直接 pickle.dump 到目标文件，后写的那次可能只写了一半。
            db = {}
    if type(cfgs) is str:
        cfgs = [cfgs]
    for cfg in cfgs:
        cls, gen = GetGen(cfg)
        if cfg in db:
            old_hash, src = db[cfg]
        else:
            old_hash, src = None, []
        new_hash = CalcHash(cfg)
        if new_hash != old_hash or force:
            src = gen(cfg)
        if src != None:
            if type(src) is list:
                if cls not in source:
                    source[cls] = src
                else:
                    source[os.path.basename(cfg)[:-5]] = src
            else:
                source.update(src)
        db[cfg] = new_hash, src
    # 原子落盘（02.8）：先写**进程私有**的临时文件再 os.replace。
    # 并发构建时读到的要么是旧的完整内容，要么是新的完整内容，不会是半个；
    # 临时名带 pid 是因为两个进程同时写同名 tmp 一样会互相覆盖。
    tmppath = "%s.%d.tmp" % (dbpath, os.getpid())
    with open(tmppath, "wb") as f:
        pickle.dump(db, f)
    os.replace(tmppath, dbpath)
    return source
