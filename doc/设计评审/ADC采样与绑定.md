# 直连 ADC 采样与绑定（V1.1 第二阶段）

> **编写**：binbina ｜ **日期**：2026-11-18 ｜ **状态**：已实现，**上板实测通过**（板载 POT1 / VBAT）
>
> **结论前置**：直连 AIN 从"永远 `E_NOT_OK`"变成真实可用，并且**在现有开发板上验证过** ——
> 板载电位计与 VBAT 分压就是真实模拟源。MUX 的 ADC COM 走同一套 HAL，但**没有 RS2260 实物，未验证**。

## 1 为什么要加一层 AdcSampler

`Adc_ReadGroup()` 的行为是：状态必须是 `ADC_COMPLETED`，否则返回 `E_NOT_OK`。
若每次读都"启动 + 忙等 + 读"，等于把 10 ms 节拍交给一个微秒级外设，而且
**一次转换只能服务一个读者**（第二个人再启动会把第一个人的结果冲掉）。

按 V2.0 的分工："异步输入设备自己负责采样与时间调度，IoHwAb 只消费样本"。
所以新增 `AdcSampler`：

```
第 N 拍    Start(group)                     → pending
第 N+1 拍  Completed? 是 → Read 整组 + 每槽位 seq++ ；否 → 等/超时
```

- 每个组**只有一个驱动者**：直连 AIN → `AdcSampler`；MUX ADC COM → `MuxManager`；
- 生成器 **R15** 拒绝"同一组既接直连 AIN 又接 MUX"的配置。

> 这一条不是洁癖：两个人同时操作同一组时，读到的都是"合理的电压值"，
> 从数据上**看不出错误**，只会在某些时刻莫名跳动。必须在配置期拦住。

## 2 顺带修掉一个潜伏缺陷：channel 没带组号

`IoHwAb_AinCfgType` 有 `group` 和 `channel` 两个字段，但 `IoHwAb_MainFunction()`
调 `ops->ReadRaw(cfg->channel, ...)` 时**没把 group 传下去** ——
也就是说非 0 组的通道会去读 0 组的槽位。

现在统一编码：`channel = (group << 8) | slot`，生成器负责拼、Adapter 负责拆。
`group` 字段保留用于表内可读性。

| 来源 | 编码 |
|---|---|
| 直连 AIN | `(adcGroup << 8) | slot` |
| MUX 的 AIN | `(device << 8) | Y` |
| Host 模拟 | 原样（通道号即数组下标） |

两套编码都放在高位，互不冲突（组/设备都不会超过 255）。

## 3 接口与实现

| 文件 | 作用 |
|---|---|
| `infras/include/adc_sampler.h` | 组配置、`AdcSampler_HwOps`（Start/Completed/Read）、`AdcSampler_GetRaw` |
| `app/app/src/adc_sampler.c` | 核心：按组轮转、完成发布、超时丢弃（Target/Host 同一份） |
| `app/platform/cvm0146/src/AdcSamplerAc.c` | Adc HAL 绑定 + 组表（通道数用 `Adc_Cfg.h` 的宏） |
| `app/platform/cvm0146/src/IoHwAbAc.c` | `iohwabac_AinReadRaw` → 拆 `(group,slot)` → `AdcSampler_GetRaw` |
| `app/app/src/main.c` | `AdcSampler_Init()` + 10 ms `AdcSampler_MainFunction()`（在 IoHwAb 之前） |
| `app/app/src/cmd/io_cmd.c` | `io status` 增加 5 路 AIN 的原始值与 status |

`Adc_Cfg.h` 新增 `ADC_CFG_GROUP0_CHANNELS` / `GROUP1_CHANNELS` 两个宏：
文件作用域的静态表不能用 `const` 数组初始化，宏是唯一能让
"Adc_Cfg.c 的定义"与"采样器组表"共用同一个数字的办法。

## 4 验证

### 4.1 Host（`host_build` 新增 `adc_sampler` 用例，8/8 套件）

| # | 断言 | 结果 |
|---|---|---|
| 1 | 未采样 `GetRaw` = `E_NOT_OK` | PASS |
| 2 | 第 1 拍只启动、第 2 拍才发布（不抢跑） | PASS |
| 3 | 双通道组一次转换发布两个槽位 | PASS |
| 4 | 两拍后 `seq` 恰好 +1 | PASS |
| 5 | 转换延迟 2 次查询期间不发布 | PASS |
| 6 | 组 0 永不完成 → 超时计数增长、不发布、**组 1 不受影响** | PASS |
| 7 | 读失败 → `seq` 不变（上层转 STALE） | PASS |
| 8 | 启动失败不计入超时 | PASS |
| 9 | 越界组/槽位被拒 | PASS |

### 4.2 上板（真实模拟源，**这是本轮最强的一条证据**）

```
io
  ain[2]  = 1923 (status=1)     ← POT1_ADC（ADC0_SE12，槽位 0）
  ain[3]  = 2255 (status=1)     ← VBAT_ADC（ADC0_SE13，槽位 1）
  ain[0]  = n/a (status=3)      ← Host 通道在板上不可用（正确）
  ain[1]  = n/a (status=3)
  ain[4]  = n/a (status=3)

adc 0
  g0: 1923(1549mV) 2257(1818mV)
adc 1
  g1: 2243(1807mV)
```

两条**独立路径**互相印证：

- `io` 走 `AdcSampler → IoHwAb（滤波 shift=2）`；
- `adc 0` 走 shell 的一次性 `Adc_StartGroupConversion + Adc_ReadGroup`。

POT1 两路完全一致（1923），VBAT 差 2 个计数 —— 正是 IoHwAb 一阶滤波的滞后量，
不是采样错误。`status=1`（VALID）也证明 `seq` 在持续更新（否则会转 STALE）。

### 4.3 回归

通信回归 **12/12**、`mux_cfg` **26/26**（新增 R15 与直连编码断言）、
App/AppB 零警告；`text 247948 → 249308`（+1360 B），`bss +200 B`（采样缓冲与序号）。

## 5 明确没做 / 没验证

| 项 | 状态 |
|---|---|
| **MUX 的 ADC COM** | 代码已接 `Adc HAL`（Start→`Adc_StartGroupConversion`，Ready→`Adc_GetGroupStatus`，Read→`Adc_ReadGroup`+取槽位），但**没有 RS2260 实物，从未执行过这条路径** |
| RS2260 的 `settleMs` | 仍是估值，需要器件手册 |
| 模拟开关 Ron 对采样时间的影响 | `Adc_Cfg.c` 的 `samplingTime=20` 是给低阻电位器定的，接 MUX 后**必须重扫收敛点**（该文件注释已写明） |
| ADC 校准/参考电压误差 | 未做；当前按 VDDA=3300 mV 换算，实测值与万用表未比对 |

## 6 下一步

1. 实物到位：先用一根 Y 接已知电压，验证 ABC→Y 映射、`settleMs` 与采样时间；
2. 若 OEM 要求，再补 ADC 校准与参考电压实测（会改变 `factor`）；
3. PCA9555/TCA9539 仍需先做 I2C HAL —— 与 ADC 无关。
