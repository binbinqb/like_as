# IoHwAb V1.0.1 收口：六项契约修正

> **编写**：binbina ｜ **日期**：2026-11-18 ｜ **状态**：已实现，Host 39/39
>
> **结论前置**：V1.0 的架构方向与分层不动，本轮只修**契约边界**——极性归属、
> 样本新鲜度、生命周期、换算边界、安全状态反馈，以及一处写错的依赖判断
> （RS2260 不需要 I2C）。六项全部落地为**可执行断言**，Host 用例由 19 条增至 39 条。

## 0 六项一览

| # | 项 | 性质 | 结论 |
|---|---|---|---|
| 1 | RS2260 依赖 I2C | 文档错误（我的判断失误） | 改为：RS2260 只需 Dio/Adc；I2C 仅是 Expander 前置 |
| 2 | 极性归属矛盾 | 契约自相矛盾 | 收敛到 **Core 唯一转换**，Adapter 只收发电气电平 |
| 3 | Init 运行期非幂等 | 运行期缺陷（会关灯） | `Init` 重复调用变空操作；新增 `ReInit` / `IsInitialized` |
| 4 | AIN 换算溢出 + 有符号右移 | 可移植性/UB 风险 | `int64_t` 中间量 + 饱和；右移显式朝零舍入 |
| 5 | 输入时间模型 | 扩展性缺陷（MUX 会重复消抖） | 输入 ops 带 `seq`，无新样本不推进、超时判 `STALE` |
| 6 | 安全操作无反馈 | 可观测性缺陷 | `SetAllSafe` 返回结果；新增 `DoutGetFault` |

## 1 P0-1 RS2260 不依赖 I2C（文档错误）

**原判断**（`IoHwAb-V2.0架构.md` 初版 §1 与 roadmap 任务）："没有 I2C HAL，
RS2260/PCA9555 类器件无法先行，V1.1 第 0 步先补 `I2c.h` / `I2cAc.c`。"

**事实**：RS2260 是**引脚选通的模拟多路开关**：

| 连接 | 方向 | 用到的 HAL |
|---|---|---|
| MCU GPIO → A/B/C | 输出 | `Dio` |
| MCU GPIO → INH（如存在） | 输出 | `Dio` |
| COM → MCU GPIO | 输入 | `Dio` |
| COM → MCU ADC | 输入 | `Adc` |

**全程没有 I2C 事务**。真正需要 I2C 的是 PCA9555/TCA9539 这类扩展器。

**修正**：

| 模块 | 前置 |
|---|---|
| RS2260（GPIO COM） | `Dio` + SelectBus 扫描 |
| RS2260（ADC COM） | `Dio` + `Adc` + SelectBus 扫描 |
| PCA9555 / TCA9539 | **I2C HAL** + 扩展器驱动（单列任务，不阻塞 RS2260） |

**影响**：V1.1 可以立刻开始 SelectBus 状态机，不必等 I2C；roadmap 里
"I2C HAL 是 RS2260 前置"的任务依赖已拆开。

## 2 P0-2 极性归属：收敛到 Core

**原矛盾**：`iohwab.h` 的归属表写"极性 = 生成绑定表 + ops 实现"，
而 `iohwab.c` 早在 Core 里调 `iohwab_ApplyPolarity()` —— **文档与代码各说一套**。

**判定**：以代码思路为准，**Core 是唯一转换点**，理由两条：

1. `activeLevel` 本来就在生成表项里，Core 做转换不需要额外信息；
2. DIN 与 DOUT 必须对称 —— 输入侧"电气→逻辑"只能在 Core 做（Adapter 拿不到
   极性配置时不该自己发明规则），那么输出侧"逻辑→电气"放 Adapter 就是两套规则。

**契约**：

```c
/* Adapter 收到的已经是电气电平；禁止再按 activeLevel 取反 */
Std_ReturnType (*Write)(uint16 channel, boolean level);
/* 输入 Adapter 返回电气电平，Core 负责去极性 */
Std_ReturnType (*Read)(uint16 channel, boolean *level, uint16 *seq);
```

**验证**：新增 `HOST_LOW` 通道（`activeLevel=LOW`，Host 后端）：
写逻辑 1 → `HostIo_GetDoutLevel()` 读到**电气 0**；回读仍还原为逻辑 1。
这条断言直接证明"Core 做转换、Adapter 只见电气电平"。

## 3 P0-3 Init 的运行期语义

**原缺陷**：`IoHwAb_Init()` 每次都清消抖/滤波上下文并执行 `SetAllSafe()`。
"重复调用结果相同"只说明**结果幂等**，掩盖了**副作用**：车辆运行中若有代码
（或诊断流程）重复调用，正在点亮的灯光会被拉回安全值。

**修正**：

| API | 语义 |
|---|---|
| `Std_ReturnType IoHwAb_Init(void)` | **首次**才执行；已初始化则立即返回 `E_OK`，不改状态、不动输出 |
| `Std_ReturnType IoHwAb_ReInit(void)` | 显式重新初始化：清状态 + 回安全值；只允许 EcuM/诊断复位调用 |
| `boolean IoHwAb_IsInitialized(void)` | 生命周期状态查询（`io status` 已打印） |

**验证**：写 `HOST0=1` → 再次 `Init()` → 电气仍为 1、DIN 状态仍 `VALID`；
`ReInit()` 后输出回 0、DIN 回 `NEVER`。

## 4 P1-1 AIN 换算与滤波的数值边界

**原缺陷**：`*value = ((sint32)raw * factor) / 1000 + offset;`
`raw ≤ 65535`、`factor` 为 `sint32`，乘积可达 1.4e14，**远超 sint32**（有符号溢出是 UB）。
另外 `(raw - filt) >> shift` 在负差值上是**实现定义行为**（算术/逻辑右移因编译器而异）。

**修正**：

```c
int64_t phys = ((int64_t)raw * (int64_t)factor) / 1000 + (int64_t)offset;
*value = iohwab_SatS32(phys);          /* 饱和到 INT32_MIN..INT32_MAX */

static sint32 iohwab_Shr(sint32 v, uint8 shift)   /* 朝零舍入，可移植 */
{
    if (v >= 0) { return (sint32)(v >> shift); }
    return (sint32)(-((-v) >> shift));
}
```

**语义选择**：溢出**饱和**而不是返回错误 —— 物理量换算的语义是"限幅到量程"，
返回错误反而会让上层丢弃一个仍然有意义的极值。需要区分截断时用原始值判断。

> **MISRA 偏离说明（有意）**：MISRA C:2012 Dir 4.6 建议避免 `long long`。
> 本处必须使用 `int64_t`：32 位内核上无法用 `sint32` 完成 `65535 × 2^31` 量级的
> 中间乘积，任何"拆项"写法在极端参数下仍会溢出。偏离范围限定在
> `IoHwAb_AinReadPhys()` 的单个表达式内，结果立即饱和回 `sint32`，不扩散到接口。

**验证**：`AIN_OVF`（`factor=1e8`）：`65535×1e8 = 6.5e12`（乘积已溢出 sint32），
`/1000` 后 6.5e9 仍超 `INT32_MAX` → 断言等于 `INT32_MAX`。
负差值收敛：`2048 → 512` 30 拍后落在 500..600。

## 5 P1-2 样本新鲜度（V1.1 的前置）

**原缺陷**：`MainFunction()` 每 10 ms 无条件把读到的值当作新样本。
直连 GPIO/ADC 没问题，但 RS2260（ABC 扫描）、I2C 扩展器（批量读）**不可能**
每 10 ms 都有新数据。后果：

- DIN 拿同一个旧样本反复"确认"，消抖失去意义；
- AIN 反复对同一个值滤波（数值不动，但状态一直被刷新成 `VALID`）；
- 超时检测永远不触发 —— **总线已经死了，上层看到的还是 VALID**。

**修正**：输入能力返回样本序号 `seq`：

```c
Std_ReturnType (*Read)(uint16 channel, boolean *level, uint16 *seq);
Std_ReturnType (*ReadRaw)(uint16 channel, uint16 *raw, uint16 *seq);
```

Core 规则：

| `seq` | 动作 |
|---|---|
| 变化 | 推进消抖/滤波，`sameSeqTicks` 清零 |
| 不变 | **不推进**，`sameSeqTicks++`；≥ `staleTicks` 且曾提交过有效值 → `STALE` |
| 读取失败 | 直接 `ERROR`（优先于超时判断） |

配置新增 `din.staleMs`（默认 500 ms），生成器 R9 校验（10 的整数倍、≥10）。

**后端实现约定**：

- GPIO：每次读取都是即时电平 → 逐次 +1；
- ADC：**只有转换真正完成**才 +1，且必须用"取上次结果"的接口
  （不能用会重新触发转换的 `Adc_ReadGroup()`，否则打乱 MUX 的 ABC 时序）；
- Host：默认逐次 +1；`HostIo_SetDinFrozen/SetAinFrozen` 冻结 seq 用于测试。

## 6 P1-3 安全状态的错误反馈

**原缺陷**：`void IoHwAb_SetAllSafe(void)` 内部 `(void)iohwab_DoutApply(...)`，
把每路返回值丢掉。将来 HSD/LSD 经 SPI/I2C 下发，失败是常态而非异常，
上层无法知道哪些负载**没有**进入安全状态。

**修正**：

```c
Std_ReturnType IoHwAb_SetAllSafe(void);                    /* 任一路真实失败 → E_NOT_OK */
Std_ReturnType IoHwAb_DoutGetFault(IoHwAb_DoutId id, boolean *faulted);
```

实现细节：**不提前返回** —— 一路失败不能阻止其余负载进安全状态；
逐路故障位独立记录。

**实现中新发现的语义问题（已定）**：`ops == NULL` 表示"该能力在本构建不适用"
（Target 上的 Host 桩 / Host 上的 GPIO 桩）。如果把这种情况算作失败，
目标板上 `io safe` 会**永远报错**（因为配置里有两个 host 直连通道），
真实故障反而被淹没。因此：

| 情况 | 返回 | 故障位 | 计入 SetAllSafe 失败 |
|---|---|---|---|
| `ops == NULL`（本构建不适用） | `E_NOT_OK` | 保持 FALSE | 否 |
| Adapter 存在但写失败 | `E_NOT_OK` | TRUE | 是 |

**验证**：注入 `HOST0` 写失败 → `DoutWrite` = `E_NOT_OK`、`GetFault(HOST0)` = TRUE、
`SetAllSafe` = `E_NOT_OK`、未失败的 `HOST_LOW` 仍为 FALSE；
解除注入 → `SetAllSafe` = `E_OK`、输出回安全值。

## 7 接口变更清单（对使用方不兼容）

| 项 | V1.0.0 | V1.0.1 |
|---|---|---|
| `IoHwAb_Init` | `void` | `Std_ReturnType`，运行期空操作 |
| `IoHwAb_SetAllSafe` | `void` | `Std_ReturnType` |
| `IoHwAb_DinOpsType.Read` | `(ch, level*)` | `(ch, level*, seq*)` |
| `IoHwAb_AinOpsType.ReadRaw` | `(ch, raw*)` | `(ch, raw*, seq*)` |
| `IoHwAb_DinCfgType` | 5 字段 | 6 字段（新增 `staleTicks`） |
| 新增 | — | `IoHwAb_ReInit` / `IoHwAb_IsInitialized` / `IoHwAb_DoutGetFault` |

调用方只有 `main.c`（已改为检查 `Init` 返回值并打印）与 `io_cmd.c`（`io safe`
已按返回值报错）。Adapter 侧：`IoHwAbAc.c` 增加 DIN 的 seq 计数，
ADC 仍为显式 `E_NOT_OK`（直连 AIN 未实现，**不伪装**）。

## 8 验收证据

| 级别 | 证据 |
|---|---|
| A 静态 | `iohwab.c` 无引脚号/无 SDK 头；生成器 R1~R10 校验；`a4_gen_check` / `hardcode_check` / `check-pdu` |
| B Host | **39/39 断言（16 组）**，`host_build` 6/6 套件 |
| C 上板 | `io status` 新增 `init=` 与故障位显示；通信回归 11/11 |
| D 实物 | **仍未做**：LED 亮灭需人眼确认；无 HSD/LSD/示波器 |

## 9 不在本轮（明确留下）

| 项 | 原因 |
|---|---|
| 直连 ADC 实装 | 需要真实模拟通道与 ADC 组表（P2） |
| RS2260 SelectBus Host 模拟 | V1.1 主体，本轮只把契约准备好 |
| HSD/LSD 诊断能力（`GetFault/GetCurrent`） | 无器件型号，V1.2 |
| 输出仲裁 | 当前无第三处冲突，业务层状态机优先 |

## 10 一句话总结

V1.0 证明了"分层 + 静态绑定 + Host 同源测试"这条路可行；
V1.0.1 把**契约**补齐到能承载 MUX 和智能驱动的程度。
下一步做 RS2260 时，Core 不需要再改一行。
