# RTE 配置生成（V0.2）

> **编写**：binbina ｜ **日期**：2026-11-18 ｜ **状态**：已实现，Host 24/24
>
> **结论前置**：端口表不再手写在 `rte.h` 里，改由 `Board.json` 的 `rte.ports`
> 生成（`Rte_Ports.h`）；RTE 在 switch 之外新增 **U16（原始量）** 与
> **S32（定点物理量）** 两种端口，并把 DIN / AIN / DOUT 接进同一套端口模型。
> 换一个 BCM 项目只改配置，业务代码不动。

## 1 为什么是在既有 `rte.c` 上扩，而不是新起一层

仓库里已有一套 RTE（V0.1，11-17）：`switch` 端口 + 四态映射 + 单向校验，
设计是对的。本次做的是**把端口表从手写变成生成**、把类型从 1 种扩到 3 种，
所以改的是同一组文件：

| 文件 | 变更 |
|---|---|
| `app/app/src/rte.h` | 端口编号改为 `uint16`，由 `Rte_Ports.h` 提供；新增 `Rte_ReadU16` / `Rte_ReadS32` |
| `app/app/src/rte_cfg.h` | 表项由 `{dir, signalId}` 扩为 `{dir, kind, ref}`；新增 `RTE_KIND_*` |
| `app/app/src/rte_cfg.c` | 表体改为展开生成的 `RTE_PORT_CFG_LIST` |
| `app/app/src/rte.c` | 按 `kind` 分派：Com 2 态、DIN、AIN 原始/物理、DOUT |
| `tools/generator/BcmRte.py` | 新增：校验 E1~E6，生成 `Rte_Ports.h` |

> 期间我曾新建过一套 `bcm_rte.*`，发现与既有 RTE 重复后**整组删除**，
> 没有留下两套并行实现。

## 2 端口模型

```json
"rte": {
  "ports": [
    {"name": "PARK_BRAKE", "kind": "com_rx", "ref": "BCM_SIG_RX_PARK_BRAKE"},
    {"name": "BRAKE_LAMP", "kind": "com_tx", "ref": "BCM_SIG_BRAKE"},
    {"name": "DOOR_FL",    "kind": "io_din", "ref": "DOOR_FL"},
    {"name": "VBAT_MV",    "kind": "io_ain_phys", "ref": "VBAT_ADC"},
    {"name": "POT1_RAW",   "kind": "io_ain_raw",  "ref": "POT1_ADC"},
    {"name": "LED_R",      "kind": "io_dout", "ref": "LED_R"}
  ]
}
```

| kind | 方向 | 值类型 | ref 含义 | 后端 |
|---|---|---|---|---|
| `com_tx` | out | switch | `Bcm_SigIdType` | `BcmSig_TxSet` |
| `com_rx` | in | switch | `Bcm_SigRxIdType` | `BcmSig_RxRead` |
| `io_din` | in | switch | `IoHwAb_DinId` | `IoHwAb_DinRead` |
| `io_ain_raw` | in | U16 | `IoHwAb_AinId` | `IoHwAb_AinReadRaw` |
| `io_ain_phys` | in | S32 | `IoHwAb_AinId` | `IoHwAb_AinReadPhys` |
| `io_dout` | out | switch | `IoHwAb_DoutId` | `IoHwAb_DoutWrite` |

`dir` / `type` 可以不写（按 kind 推）；写了必须一致 —— 允许显式写是为了让
配置自解释，但写错要报错，不能"以写错的为准"。

## 3 状态映射

| 来源 | 映射 |
|---|---|
| `BCM_SIG_VALID` | `RTE_E_OK` |
| `BCM_SIG_TIMEOUT` | `RTE_E_MAX_AGE_EXCEEDED` |
| `BCM_SIG_INVALID` | `RTE_E_INVALID` |
| `BCM_SIG_NEVER_RECEIVED` | `RTE_E_NEVER_RECEIVED` |
| `IOHWAB_STATUS_VALID/STALE/ERROR/NEVER` | 同上四项一一对应 |

两条额外规则：

1. Com 的 `FAULT` / `UNKNOWN` 即使"值域合法"也判 `RTE_E_INVALID`
   —— 不能把"对方报故障"当成"灯灭了"；
2. `io_dout` 只接受 `ON` / `OFF`。`ERROR` / `INVALID` 返回 `E_NOT_OK`
   且**不驱动输出** —— 把故障当 OFF 会让负载安静地灭掉而仪表显示正常。

## 4 为什么运行期还要查类型和方向

端口号是整数，`Rte_ReadU16(RTE_PORT_PARK_BRAKE, ...)` 在编译期完全合法。
如果不查，就会把 Com 的 2 态值当原始量读出来 —— 数值"看起来正常"，错误
只能在上板后靠现象发现。所以：

- 类型不符 → `RTE_E_INVALID`
- 方向不符 → `RTE_E_INVALID` / `E_NOT_OK`（写输入端口、读输出端口）

这不是防御性编程，是让"接错端口"在**第一次调用**就暴露。

## 5 生成物为什么只出头文件

`Rte_Ports.h` 里只有：端口枚举、`RTE_PORT_NUM`、`RTE_PORT_CFG_LIST`（初始化列表）。
表体在 `app/app/src/rte_cfg.c` 里展开：

```c
const Rte_PortCfgType Rte_PortCfg[RTE_PORT_NUM] = RTE_PORT_CFG_LIST;
```

原因：若生成 `.c`，它会被编进**平台库**，而平台库的 include 路径里没有
`app/app/src/bcm_sig.h` —— 那会让平台层反向依赖应用层。头方案不引入这个
耦合，也没有额外的构建顺序依赖（生成 → 编译由 SCons 的头依赖自动跟踪）。

## 6 校验（E1~E6）

| # | 规则 |
|---|---|
| E1 | 端口名唯一且是合法 C 标识符 |
| E2 | `kind` 必须是六种之一 |
| E3 | 显式写的 `dir` / `type` 必须与 kind 一致 |
| E4 | `io_*` 的 `ref` 必须存在于 `io` 四表（按名字校验） |
| E5 | `com_*` 的 `ref` 必须是合法 C 标识符（存在性由编译器检查） |
| E6 | 同一 `(kind, ref)` 不得被两个端口绑定 |

`tools/rte_cfg_check.py` 用合成配置验证这 6 条（1 合法 + 7 组缺陷注入，
14 项断言），已纳入静态回归 —— 否则真实配置正确时这些规则永远不执行。

## 7 验证

| 项 | 结果 |
|---|---|
| Host `rte` 用例 | **24/24**（原 15 条 + IO 9 条） |
| `host_build` | **8/8 套件** |
| `rte_cfg` 规则自测 | **14/14** |
| 通信回归 | **13 例全过**（静态 8 + 上板 5） |
| 编译 | App/AppB 零警告；`text 249308 → 249648`（+340 B） |

新增的 9 条断言：DIN 未采样/消抖后 ON·OFF、AIN 物理量 ≈ -1000、
AIN 原始值 ≈ 30000（含滤波残差）、switch 端口读 S32 被拒、物理量端口读 U16 被拒、
输出端口读 S32 被拒、直连 LED 在 Host 上 `E_NOT_OK`。

## 8 没做的（明确留下）

| 项 | 原因 |
|---|---|
| **业务迁移** | `BcmBiz` 仍用 `Rte_Read_ParkBrake` / `Rte_Write_BrakeLamp`（宏保留，行为不变）。迁移应由 Lighting 组件一起做，不单独动业务 |
| runnable 调度表 | 当前 `BcmBiz_MainFunction()` 仍由 `main.c` 按拍调用；调度表属 10.5 |
| 事件型端口 / D-S 端口 | 现有需求都是周期读写，没有触发语义 |
| 端口读缓存 | 快照在 `BcmSig_MainFunction` 已做，RTE 再加一层只是把同一份数据存两遍（V0.1 已论证） |
