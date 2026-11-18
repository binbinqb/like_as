# IoHwAb V1.0 设计（DIN / AIN / DOUT）

> ⚠ **本文档已被 `doc/设计评审/IoHwAb-V2.0架构.md` 收敛**（2026-11-18）。
> 保留原因：它是 V2.0 的**实施切片**与设计过程记录。两处差异以 V2.0 为准：
> ①单一 `IoHwAb_HwOps` 改为按能力拆表；②读接口增加 `IoHwAb_StatusType`。
>
> **编写**：binbina ｜ **日期**：2026-11-18 ｜ **状态**：设计待确认，未写代码
>
> **结论前置**：V1.0 只做四件事——**逻辑通道表、消抖/滤波、Host 可跑的硬件后端、安全状态**。
> 真实开路/短路诊断、RS2260/TCA9539 扩展、HSD 电流反馈都留到 V1.1。
> 理由是当前板子上真正可用的 IO 只有 3 个 LED + 2 个 CAN STB：先把**契约和验证手段**立起来，
> 等硬件到位只加表项，不改代码结构。

## 1 范围

| 做 | 不做（V1.1 或更后） |
|---|---|
| 逻辑通道表（Board.json → 生成配置） | 开路/短路/过流的真实判定（器件相关） |
| DIN 消抖、AIN 一阶滤波与物理量换算 | RS2260 / TCA9539 扩展 IO |
| DOUT 极性、安全状态、读回 | HSD 电流反馈与 PWM 诊断 |
| Host 后端（内存模拟）+ 上板 LED 闭环 | RTE 端口自动生成 |
| `IoHwAb_MainFunction()` 10 ms 节拍 | 输出仲裁（多业务抢同一负载） |

**不在本层做业务决策**：门开了要不要亮灯，属于业务；门开输入是高电平还是低电平、
抖动多少、换算系数多少，属于本层。

## 2 分层与依赖

```
业务组件（Lighting / Wiper / DoorLock …）
        ↓ 只 include "iohwab.h"
IoHwAb（逻辑通道：ID + 表项 + 消抖/滤波 + 安全状态）
        ↓ 只通过 IoHwAb_HwOps 函数表
HAL：Dio_* / Adc_* / Pwm_*        ← 目标板实现（iohwab_hw_target.c）
     内存数组模拟                ← Host 实现（iohwab_hw_host.c）
```

- IoHwAb **不 include 任何 SDK 头**，与现有分层约定一致；
- 目标/Host 两种后端在**链接期**二选一，IoHwAb 源码零改动；
- `Board.json` 是唯一配置源，生成 `IoHwAb_Cfg.c/.h`。

## 3 通道模型

| 类 | 语义 | ID 前缀 | 底层 |
|---|---|---|---|
| DIN | 开关量输入（门/锁/开关） | `IOHWAB_DIN_*` | `Dio_ReadChannel` |
| AIN | 模拟输入（电压/温度） | `IOHWAB_AIN_*` | `Adc_ReadGroup` |
| DOUT | 开关型输出（HSD/LSD/Relay） | `IOHWAB_DOUT_*` | `Dio_WriteChannel` 或扩展 IO |
| PWM | 调光输出 | `IOHWAB_PWM_*` | `Pwm_SetDutyCycle` |

ID 由生成器按 `Board.json` 中数组顺序编号，从 0 连续；**应用只认枚举名，不认数字**。

## 4 接口（要点）

```c
/* 初始化：按表项写安全状态，初始化消抖/滤波上下文 */
void IoHwAb_Init(void);

/* 10 ms 周期：DIN 消抖、AIN 滤波、输出读回比对 */
void IoHwAb_MainFunction(void);

/* DIN：返回消抖后的电平；valid=false 表示尚未稳定（上电初期） */
IoHwAb_LevelType IoHwAb_DinRead(IoHwAb_DinId id, boolean *valid);

/* AIN：raw 与物理量两种读法；factor/offset 来自配置表 */
uint16_t IoHwAb_AinReadRaw(IoHwAb_AinId id);
sint32   IoHwAb_AinReadPhys(IoHwAb_AinId id);   /* (raw×factor)/1000 + offset，定点 */

/* DOUT：写逻辑值，内部按表项 activeLevel 取反；返回回读是否一致 */
Std_ReturnType IoHwAb_DoutWrite(IoHwAb_DoutId id, boolean on);
boolean        IoHwAb_DoutReadBack(IoHwAb_DoutId id);

/* PWM：占空比 0..IOHWAB_PWM_FULL（10000 = 100%），0 视为关断 */
Std_ReturnType IoHwAb_PwmSetDuty(IoHwAb_PwmId id, uint16_t duty);

/* 安全状态：所有输出回 safeLevel；上电与故障降级用 */
void IoHwAb_SetAllSafe(void);

/* 故障状态（V1.0 只有"未知/正常"两态，V1.1 扩展开路/短路/过流） */
IoHwAb_FaultType IoHwAb_GetFault(IoHwAb_DoutId id);
```

设计约束：

1. **所有写接口返回 `Std_ReturnType`**，参数越界返回 `E_NOT_OK`（不 assert，量产不挂）；
2. **读接口不阻塞**：`Adc_ReadGroup` 在 `MainFunction` 里统一刷，读函数只取缓存；
3. **`IoHwAb_Init` 必须幂等**：Boot 跳转前后、诊断复位后都可能被调；
4. 通道数变化只影响生成文件，**API 签名不变**。

## 5 配置（`Board.json` 的 `io` 段扩展）

现有骨架：

```json
"io": { "hsd": [], "lsd": [], "hbridge": [], "expanders": [] }
```

V1.0 扩成四张表（示例取自本板真实资源）：

```json
"io": {
  "din": [
    { "name": "IGN_SW",  "pin": "IGN_SW",  "activeLevel": "HIGH",
      "debounceMs": 20, "safeDefault": "LOW" }
  ],
  "ain": [
    { "name": "VBAT",    "adcGroup": 0, "channel": 0,
      "factor": 33, "offset": 0, "filterShift": 3 }
  ],
  "dout": [
    { "name": "LED_R",   "pin": "LED_R",   "kind": "LSD",
      "activeLevel": "LOW", "safeLevel": false }
  ],
  "pwm": [
    { "name": "DIM_PTDO", "channel": 0, "activeLevel": "HIGH",
      "freqHz": 100, "safeDuty": 0 }
  ]
}
```

字段语义：

| 字段 | 含义 | 缺省 |
|---|---|---|
| `pin` | 引用 `Board.json` 的 `pins[].name`，引脚定义只写一处 | 必填 |
| `activeLevel` | 逻辑 true 对应的电平 | `HIGH` |
| `debounceMs` | DIN 稳定时间（按 10 ms 节拍折算拍数） | 20 |
| `safeLevel` / `safeDuty` | 安全状态 | false / 0 |
| `factor` / `offset` | 物理量 = raw × factor / 1000 + offset | 1000 / 0 |
| `filterShift` | 一阶滤波右移位数（0 = 不滤） | 0 |

## 6 生成链

新增 `tools/generator/IoHwAb.py`（与 Can/Com 同风格，纯函数、无时间戳）：

```
Board.json ──► IoHwAb.py ──► app/platform/cvm0146/src/config/IoHwAb/GEN/IoHwAb_Cfg.{c,h}
                                        │
                          手写 IoHwAb.c（逻辑，不含引脚）◄──┘
```

- 生成物只含**表**：`static const IoHwAb_DinCfgType IoHwAb_DinCfgs[]` + 枚举；
- `IoHwAb.c` 手写、与具体引脚无关，Host 也能编；
- 纳入 02.8 门禁：`Board.json` 与 `IoHwAb.py` 进 `gen_gate` 输入指纹。

## 7 Host 模拟与验证

`tools/host_build.py` 已能用 mingw 编译运行，直接复用：

| 用例 | 断言 |
|---|---|
| H1 DIN 消抖 | 抖动 3 拍不翻转；稳定 2 拍后翻转；`valid` 前 2 拍为 false |
| H2 DIN 极性 | `activeLevel=LOW` 时，引脚低 → 逻辑 true |
| H3 AIN 换算 | raw=2048、factor=33 → 67（定点）；滤波 8 拍收敛 |
| H4 DOUT 安全状态 | `Init` 后所有输出 = safeLevel；`SetAllSafe` 立即生效 |
| H5 DOUT 回读 | 模拟引脚被外部拉反 → `DoutReadBack` 与写入不一致可检出 |
| H6 PWM | duty 0/5000/10000 映射正确；超范围返回 E_NOT_OK |
| H7 越界 ID | 所有接口传非法 ID 返回 E_NOT_OK，不越界读表 |

上板闭环（当前硬件只有 LED）：`IoHwAb_DoutWrite(IOHWAB_DOUT_LED_R, 1)` → 板载红灯亮，
`0` → 灭；CAN STB 通道保持高电平（通信不受影响）。

## 8 与现有代码的关系

| 现有 | 影响 |
|---|---|
| `Board.json` / `pins[]` | 只**扩展** `io` 段，`pins` 不动 |
| `DioAc.c` / `AdcAc.c` / `PwmAc.c` | 不动；由 `iohwab_hw_target.c` 调用 |
| `BcmSig`（Com 信号绑定） | 不动；未来业务同时读 `BcmSig`（来自 CAN）与 `IoHwAb`（本地硬件） |
| `tools/host_build.py` | 加一个 `iohwab_test` 目标 |

## 9 待确认的两个决策

1. **AIN 换算用定点还是浮点**？建议 `sint32` 定点（`factor` 千分之一），
   与现有工程"不用浮点"的惯例一致；上层要物理量再除以 1000。
2. **V1.0 是否包含"输出仲裁"**？建议**不包含**：多业务抢同一负载（如室内灯被"门开"与
   "超时"两个逻辑同时控制）先在业务层用显式状态机解决，等出现第三处冲突再上仲裁层。

## 10 验收清单

- [ ] `IoHwAb.py` 生成两次字节一致（幂等），`gen_gate` 指纹覆盖
- [ ] Host 7 条用例全过（`python tools/host_build.py --run iohwab_test`）
- [ ] 上板 LED 亮/灭 + CAN STB 不受影响（m3 回归 18/18）
- [ ] `IoHwAb.c` 不含任何引脚号、不含 SDK 头
