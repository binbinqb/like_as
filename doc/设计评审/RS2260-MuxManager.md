# RS2260 MuxManager（V1.1 第一阶段）

> **编写**：binbina ｜ **日期**：2026-11-18 ｜ **状态**：核心已实现，Host 26/26；**无实物，未上板**
>
> **结论前置**：MuxManager 的状态机、配置生成与 IoHwAb 衔接已经完成，并用手工模拟的
> ABC/COM/ADC 时序在 Host 上验证了 11 组断言（26 条）。“转换期间不切 ABC”这条最关键的
> 约束现在是**可执行判据**，不再靠注释。缺的只有实物：ADC COM 的 HAL 绑定与真实建立时间。

## 1 为什么这件事不需要 I2C

上一轮已纠正：RS2260 由 **A/B/C 三根选择线** 选通，COM 接 GPIO 或 ADC。

| 连接 | 方向 | 用到 |
|---|---|---|
| MCU → A/B/C | 输出 | `Dio` |
| MCU → INH（可选） | 输出 | `Dio` |
| COM → MCU GPIO | 输入 | `Dio` |
| COM → MCU ADC | 输入 | `Adc` |

I2C 只属于 PCA9555/TCA9539 一类扩展器，与 RS2260 无关。

## 2 模型

```
SelectBus(ABC) ──┬── MuxDevice0 (COM → GPIO) ── DIN 采样
                 ├── MuxDevice1 (COM → ADC)  ── AIN 采样
                 └── MuxDevice2 (COM → GPIO)
```

- **SelectBus**：一组 A/B/C 引脚 + 建立时间 + ADC 超时 + 扫描掩码；
- **MuxDevice**：挂在哪条总线、COM 类型与通道、可选 INH、用到哪些 Y；
- **Y 通道**：ABC 的值直接等于 Y 索引（1-of-8），所以「ABC=n 时读到的就是 Y_n」。

多条总线共享同一个 ABC 值时**并行选通**：它们各有独立的 A/B/C 引脚，互不干扰，
这样两条总线的扫描不是一个等一个。

## 3 状态机

```
IDLE ──(有掩码)──► SET_SELECT ──settle>0──► WAIT_SETTLE
                        │                        │
                        └──settle=0──┐           │
                                     ▼           ▼
                                   START ◄───────┘
                                     │
                     ┌───────────────┴───────────────┐
                     │ 无 ADC 设备                    │ 有 ADC 设备
                     ▼                               ▼
                  ADVANCE ◄──── 完成/超时 ────── WAIT_SAMPLE
                     │
                     └──► 下一个 ABC（回绕则轮数 +1）
```

| 阶段 | 动作 | 失败处理 |
|---|---|---|
| SET_SELECT | 对每条需要该 ABC 的总线写 A/B/C | — |
| WAIT_SETTLE | 等待 `settleTicks` 拍 | — |
| START | GPIO：读 COM 并发布；ADC：启动转换 | 读/启动失败 → 本次不发布，`seq` 不变 |
| WAIT_SAMPLE | 查询转换完成；完成后取值发布 | 超时 → 计数 +1，丢弃本拍，继续扫描 |
| ADVANCE | 下一个有效 ABC | 掩码为空 → IDLE |

`Mux_MainFunction()` 单次调用最多推进 `MUX_STEPS_PER_TICK`（40）步，遇到等待立即返回；
一拍最多扫完一轮，避免纯 GPIO 场景空转。

## 4 与 IoHwAb 的契约

| 事项 | 归属 |
|---|---|
| 何时采样、ABC 怎么排、ADC 何时取值 | MuxManager |
| 逻辑电平、极性、消抖、滤波、四态 | IoHwAb Core |
| 通道号解释 | `IoHwAb_Mux*Ops` 胶水：`(dev << 8) | y` |

每次发布样本 `seq` +1。扫描慢或停摆时 `seq` 不再增长，IoHwAb 自然转 `STALE` ——
**不需要 Mux 自己上报超时**，这是 V1.0.1 引入样本序号的直接收益。

## 5 配置与生成（R11~R14）

```json
"selectBuses": [
  { "name": "ABC0", "pins": ["MUX_A", "MUX_B", "MUX_C"],
    "settleMs": 20, "adcTimeoutMs": 30 }
],
"devices": [
  { "name": "MUX1", "selectBus": "ABC0", "comType": "GPIO", "comPin": "MUX1_COM",
    "inh": { "pin": "MUX1_INH", "activeLevel": "HIGH" } },
  { "name": "MUX2", "selectBus": "ABC0", "comType": "ADC",
    "adcGroup": 0, "channel": 3 }
],
"io": {
  "din": [ { "name": "DOOR_FL", "source": "mux", "device": "MUX1", "channel": 0 } ],
  "ain": [ { "name": "VBAT",    "source": "mux", "device": "MUX2", "channel": 3 } ]
}
```

| 规则 | 检查 |
|---|---|
| R11 | 总线名唯一；`pins` 恰好 3 根且都在 `dioChannels`；`settleMs` 为 0 或 10 的倍数 |
| R12 | 设备名唯一；`selectBus` 已定义；`comType` 只能是 GPIO/ADC；`comPin`/INH 引脚存在；ADC 组/通道在范围内 |
| R13 | `device` 已定义；COM 类型与 DIN/AIN 匹配；`channel` 在 0..7；同一设备通道不得重复引用 |
| R14 | 设备未被任何通道引用 → **提示**（不失败），掩码为 0，状态机跳过 |

产物：`Mux_Cfg.{h,c}`（总线/设备表 + 计数 + 枚举），与 `IoHwAb_Cfg.{h,c}` 同目录、
同一生成器，随 `Board.json` 变化由构建指纹触发。

> **为什么 R14 只提示不失败**：先画板后定信号是正常流程，设备暂时没人用不该阻塞构建；
> 但必须让人看见"这片会被白扫描"。

## 6 验证（无实物，全部 Host）

`tools/host_build.py` 新增 `mux` 用例，`mux.c` / `iohwab_mux.c` 与目标板**同一份源码**，
只把 HwOps 换成模拟实现。

| # | 断言 | 结果 |
|---|---|---|
| 1 | 未扫描前 `GetDin/GetAin` = `E_NOT_OK`（不拿 0 充数） | PASS |
| 2 | GPIO 读失败只影响本通道，同总线 ADC 正常 | PASS |
| 3 | settle=0 + ADC 立即就绪：一拍扫完一轮，ABC 0..3 各写一次 | PASS |
| 4 | `activeMask` 外的 ABC 4..7 从不扫描 | PASS |
| 5 | ADC 延迟 2 次查询：**转换期间 0 次切 ABC** | PASS |
| 6 | ADC 永不完成：超时计数增长、扫描继续、AIN 无样本、DIN 正常 | PASS |
| 7 | ADC 启动失败不计入超时 | PASS |
| 8 | 未启用 Y / 越界设备 / COM 类型不符 → `E_NOT_OK` | PASS |
| 9 | `IoHwAb_Mux*Ops` 拆包与 `Mux_Get*` 返回同序号、同值 | PASS |
| 10 | 一轮扫描后 `seq` 恰好 +1 | PASS |
| 11 | INH 未配置时不产生任何写操作 | PASS |

另外 `tools/mux_cfg_check.py`（新增，纳入静态回归）用合成配置验证 **R11~R14**：
1 组合法 + 8 组缺陷注入，24/24。原因是：当前 `Board.json` 的 `selectBuses`/`devices`
是空的，这些规则在真实构建里**一次都不会执行**，只能靠合成配置证明它们真的会失败。

整体：`host_build` 7/7 套件；通信回归 **12/12**（新增 `mux_cfg` 静态用例）；
App/AppB 编译零警，`text` 不变（无设备时 Mux 被 `--gc-sections` 丢弃，符合预期）。

## 7 明确的缺口（接实物前必须解决）

| 缺口 | 影响 | 前置 |
|---|---|---|
| **ADC COM 未接** | MUX 的模拟通道在板上不可用（显式 `E_NOT_OK`） | 与直连 AIN 同批：ADC 组表 + “取上次结果”的读取方式 |
| `settleMs` 是估的 | 太快会采到上一通道的残压 | RS2260 数据手册的建立/串扰参数 |
| INH 极性/时序未确认 | 可能使能不了或一直关断 | 器件手册；当前只做静态写一次 |
| 无实物 | 状态机只被模拟验证过 | 板子 + 器件 |

## 8 下一步

1. **接 ADC**：一并解决直连 AIN 与 MUX ADC COM（P2 项），Host 侧给 Adc 后端加“转换耗时”模拟；
2. 拿到 RS2260 手册后填 `settleMs` / `adcTimeoutMs` / INH 极性；
3. 实物到位：先用一根 Y 接已知电平，验证 ABC→Y 映射与建立时间，再逐通道接入。
