# IoHwAb V2.0 架构基线（适配 like_as 现状）

> **编写**：binbina ｜ **日期**：2026-11-18 ｜ **状态**：架构基线，未实现
>
> **结论前置**：采用 V2.0 的**分层思想**（Core / Capability Adapter / Device Driver /
> Resource Manager / Generator），但**不照抄实现清单**。原因是三项仓库现状：
> ①RS2260 只需 GPIO（ABC/INH）+ ADC（COM），**不需要 I2C**；真正缺 I2C 的是
> PCA9555/TCA9539 一类扩展器；②没有 HSD/LSD/Relay 实物；
> ③当前板级可验证的 IO 只有 3 个 LED + 2 个 CAN STB。
> 因此 V1.0 只做**直连 IO + Host 可测**，把能力接口和生成器校验先钉死；
> MUX 与智能输出放到有硬件（或至少器件规格确认）之后。
>
> **V1.0.1 更正（2026-11-18）**：本文档初版把"I2C HAL"写成 RS2260 的前置任务，
> 是**判断错误** —— RS2260 由 A/B/C 选择引脚直接选通，COM 接 GPIO 或 ADC，
> 全程没有 I2C 事务。I2C HAL 只是 Expander 的前置。

## 1 与仓库现状的适配审查

| V2.0 要求 | 仓库现状 | 结论 / 动作 |
|---|---|---|
| IoHwAb 不碰 MCU 外设 | `infras/include` 有 `Dio.h` / `Adc.h` / `Pwm.h`；`DioAc/AdcAc/PwmAc` 是平台实现 | ✅ 直接按"能力适配器 → HAL"分层 |
| ADC 异步采样 | `AdcAc` 提供 `StartGroupConversion` / `IsGroupCompleted` / `ReadGroupRaw` | ✅ MUX 状态机可非阻塞实现，**不改 HAL** |
| RS2260 的 COM 走 GPIO/ADC | `Dio.h` 可直接驱动 A/B/C/INH；`Adc.h` 读 COM | ✅ **不需要 I2C**（V1.0.1 更正）：MUX 是纯引脚选通，V1.1 可直接开工 |
| PCA9555/TCA9539 | 无 I2C HAL；SDK 有 `i2c` 驱动但未封装；器件型号未定 | ⚠ **真正的 I2C 前置**：`infras/include/I2c.h` + `I2cAc.c` 先于 Expander，**不阻塞 RS2260** |
| HSD/LSD/Relay | 无驱动、无实物 | ⚠ 只做 Adapter 接口与 Host 模拟，标注"未实物验证" |
| `Board.json` 承载设备与绑定 | 已有 `pins[]`（9 条）、`dioChannels[]`（5 条）、`io` 段四表（din/ain/dout/pwm） | ✅ 在 `io` 段扩展，**不推翻现有 pins** |
| Host 可测 | `tools/host_build.py` 已有 mingw 编译/运行通路 | ✅ 直接加 `iohwab_test` 目标 |
| 生成器校验 | 02.8 门禁已有输入指纹机制 | ✅ 新生成器纳入同一门禁 |

## 2 分层与职责（相对 V2.0 的两处修正）

```
Application（Lighting / Wiper / DoorLock）
        ↓
RTE（端口）
        ↓
IoHwAb Core —— 逻辑通道、逻辑值、极性、消抖/滤波/新鲜度，不碰引脚
        ↓  Generated Binding（静态 const 表：逻辑 ID → 能力 ops + 物理通道 + 极性 + 时序参数）
Capability Adapter —— DigitalInput / AnalogInput / DigitalOutput / PwmOutput
        ↓
Device Driver / Resource Manager（MUX、Expander、HSD/LSD/Relay）
        ↓
MCU HAL（Dio / Adc / Pwm / I2c）
```

**修正 1（V1.0.1 改判）：极性唯一归属在 Core，Adapter 只收发电气电平。**
V2.0 §5.5 只要求"不能两层同时取反"，没说谁做。初版把极性放在"生成绑定 + Adapter"，
实现时发现两处硬伤：①`activeLevel` 本来就在表项里，Core 做转换不需要任何额外信息；
②DOUT 与 DIN 必须对称 —— DIN 的"电气→逻辑"只能在 Core 做（Adapter 拿不到极性
配置项时不该自己发明），那么 DOUT 的"逻辑→电气"放 Adapter 就成了两套规则。
因此统一为：**Core 是唯一转换点**，`DoutOps.Write(ch, level)` 收到的是电气电平，
Adapter（含未来的 HSD/LSD/Relay）**禁止再按极性取反**。

**修正 2：能力接口按能力拆表，输入能力必须带样本序号**。
V2.0 已否掉"巨型 HwOps"，但 §5.3 的 `DoutOps` 只有 `Write`，无法支撑
本工程已有的"写后回读"与故障状态；输入侧则缺"这是不是新样本"的判据。
定为：

```c
/* 输出：level 是电气电平，极性由 Core 转换后传入 */
typedef struct {
    Std_ReturnType (*Write)(uint16 ch, boolean level);
    Std_ReturnType (*Read)(uint16 ch, boolean *level);    /* NULL = 不支持回读 */
} IoHwAb_DoutOpsType;

/* 输入：seq 只在新样本产生时 +1，Core 据此推进消抖/滤波 */
typedef struct {
    Std_ReturnType (*Read)(uint16 ch, boolean *level, uint16 *seq);
} IoHwAb_DinOpsType;
```

`Read == NULL` 时 `IoHwAb_DoutReadBack()` 返回 `E_NOT_OK`，**不得伪造正常值**
（与 V2.0 §9.2"不支持的能力不得返回伪造的正常值"一致）。
`ops == NULL`（该能力在本构建不适用）与"写失败"必须区分：前者不置故障位、
不计入 `SetAllSafe()` 的失败判定，否则目标板上的 Host 桩会让安全操作永远报错。

## 3 数据有效性（与现有 BcmSig 对齐）

```c
typedef enum {
    IOHWAB_STATUS_NEVER = 0,   /**< 尚无有效样本 */
    IOHWAB_STATUS_VALID,       /**< 样本有效 */
    IOHWAB_STATUS_STALE,       /**< 超时（时间戳过期） */
    IOHWAB_STATUS_ERROR        /**< 后端采样/通信失败 */
} IoHwAb_StatusType;
```

与 `BcmSig` 的四态（NEVER → TIMEOUT → INVALID → VALID 判定顺序）**语义同源**，
但命名不同：IoHwAb 的 `ERROR` 含"通信/采样失败"，`STALE` 是"值旧但曾经有效"。
RTE 端口应把两者都当"不可用"，不要只判 VALID。

## 4 对外 API（冻结，后续只增不改）

```c
Std_ReturnType IoHwAb_Init(void);        /* 首次初始化；运行期重复调用是空操作 */
Std_ReturnType IoHwAb_ReInit(void);      /* 显式重新初始化：清状态 + 回安全值 */
boolean        IoHwAb_IsInitialized(void);
void           IoHwAb_MainFunction(void);/* 10 ms：消抖、滤波、异步采样推进 */

Std_ReturnType IoHwAb_DinRead(IoHwAb_DinId id, boolean *value, IoHwAb_StatusType *status);
Std_ReturnType IoHwAb_AinReadRaw(IoHwAb_AinId id, uint16 *value, IoHwAb_StatusType *status);
Std_ReturnType IoHwAb_AinReadPhys(IoHwAb_AinId id, sint32 *value, IoHwAb_StatusType *status);

Std_ReturnType IoHwAb_DoutWrite(IoHwAb_DoutId id, boolean on);
Std_ReturnType IoHwAb_DoutReadBack(IoHwAb_DoutId id, boolean *on);
Std_ReturnType IoHwAb_DoutGetFault(IoHwAb_DoutId id, boolean *faulted);
Std_ReturnType IoHwAb_PwmSetDuty(IoHwAb_PwmId id, uint16 duty);  /* 0..10000 */
Std_ReturnType IoHwAb_SetAllSafe(void);
```

语义约定：

| 约定 | 说明 |
|---|---|
| `E_OK` ≠ 数据有效 | 合法性看返回码，可用性看 `status`（V2.0 §4.3） |
| 越界 ID | 返回 `E_NOT_OK`，不读表、不 assert |
| 读接口不阻塞 | 值来自 `MainFunction` 维护的缓存 |
| `Init` 幂等（**运行期**） | **重复调用不改任何状态、不动输出**。需要重置语义时必须走 `IoHwAb_ReInit()`，且只允许在 EcuM/诊断复位等生命周期节点调用 —— V1.0.0 的 `Init` 每次都会把负载拉回安全值，车辆运行中重复调用等于关灯 |
| 样本新鲜度 | 输入 ops 返回 `seq`；`seq` 不变不推进消抖/滤波，超过 `staleTicks` 判 `STALE` |
| 物理量 | `sint32` 定点：`raw × factor / 1000 + offset`，**不用浮点**；中间量 `int64_t`，结果饱和到 `INT32_MIN..MAX` |
| 不适用 ≠ 失败 | `ops == NULL` 表示该能力在本构建不适用：写接口返回 `E_NOT_OK`，但不置故障位、不计入 `SetAllSafe()` 失败 |

## 5 配置模型（三段式，先同文件）

| 区域 | 内容 | V1.0 是否用 |
|---|---|---|
| `selectBuses[]` | ABC 引脚组 | 否（V1.1） |
| `devices[]` | 器件实例：`driver` / 参数 / 所属 selectBus | 否（V1.1，V1.0 只有 `direct` 伪器件） |
| `io.din/ain/dout/pwm[]` | 逻辑通道 → 设备/通道 + 行为参数 | 是 |

V1.0 的 `source` 允许两个值：`"direct"`（MCU 引脚）与 `"host"`（模拟）。
`source: direct` 时 `pin` 必须能在现有 `pins[]` 找到；`host` 时不校验引脚。

示例（V1.0 可生成的完整形态）：

```json
"io": {
  "din": [
    { "name": "DIN_SPARE0", "source": "host", "channel": 0,
      "activeLevel": "LOW", "debounceMs": 20 }
  ],
  "ain": [
    { "name": "VBAT", "source": "direct", "adcGroup": 0, "channel": 0,
      "factor": 33, "offset": 0, "filterShift": 3, "staleMs": 200 }
  ],
  "dout": [
    { "name": "LED_R", "source": "direct", "pin": "LED_R",
      "activeLevel": "LOW", "safeLevel": false }
  ],
  "pwm": [
    { "name": "DIM0", "source": "direct", "channel": 0,
      "freqHz": 100, "safeDuty": 0 }
  ]
}
```

## 6 生成器校验清单（每条对应一个可执行断言）

编号规则：`R<n>`，生成器必须在**任何**一条不满足时失败退出，不产半份配置。

| # | 规则 | 失败信息要点 |
|---|---|---|
| R1 | 逻辑通道名唯一（跨 din/ain/dout/pwm） | 打印重名与两处位置 |
| R2 | `source=direct` 的 `pin` 必须存在于 `pins[]` | 打印缺失的 pin 名 |
| R3 | `source=direct` 的 DIN 必须 `dir=IN`、DOUT 必须 `dir=OUT` | 打印实际 dir |
| R4 | `activeLevel` 只能是 `HIGH`/`LOW` | 打印非法值 |
| R5 | `debounceMs` 必须是 10 的整数倍且 ≥10 | V1.0 节拍是 10 ms |
| R6 | AIN 的 `adcGroup`/`channel` 必须在 Adc 配置内 | 打印可用范围 |
| R7 | PWM 的 `freqHz` 必须为正；`safeDuty ≤ 10000` | — |
| R8 | 同一物理资源不得被两个逻辑通道绑定（`pin` / `adc(ch,group)` / `pwm ch`） | 打印冲突双方 |
| R9 | `staleMs` 必须是 10 的整数倍且 ≥10（DIN/AIN 通用） | 打印非法值；V1.0.1 起生效 |
| R10 | 所有输出必须有 `safeLevel` / `safeDuty` | 缺省可用但要在日志提示 |

> **R9 的沿革**：初版把 R9 写成"`source=host` 的通道不得出现在 Target 绑定表"。
> 实际做法是**一份配置服务 Target 与 Host**：host 通道在 Target 上是函数指针为 NULL
> 的桩，Core 据 `ops == NULL` 返回 `E_NOT_OK` 并在 `SetAllSafe()` 中跳过。
> 这比"生成两套表"更简单，也让"同一逻辑 ID 在两侧都存在"成为可测试的事实。
> 空出来的 R9 用于 `staleMs` 校验。

产物：`IoHwAb_Cfg.h`（ID 枚举 + 计数）、`IoHwAb_Cfg.c`（静态 const 表），
不含时间戳，连跑两次字节一致（进 02.8 门禁）。

## 7 Resource Manager（V1.1 设计，V1.0 不实现）

V2.0 §7 的模型成立，落到本工程只需把"等待 ADC"映射到现有三个函数：

```
SET_SELECT   : 写 ABC GPIO（一次，唯一写入者）
WAIT_SETTLE  : 10 ms 计数器递减
START_SAMPLE : AdcAc_StartGroupConversion(group)
WAIT_SAMPLE  : AdcAc_IsGroupCompleted(group) 轮询（每拍一次，不阻塞）
STORE_RESULT : AdcAc_ReadGroupRaw(group, buf) + 打时间戳
NEXT_CHANNEL : ABC++，回到 SET_SELECT
```

硬约束（与 V2.0 §7.5 一致，补两条本工程约束）：

1. 采样未完成**不得**切 ABC；
2. 一组 ABC 只有一个写入者；
3. 采样失败发布 `IOHWAB_STATUS_ERROR`，不发布旧值；
4. 每个样本带 `Platform_NowMs()` 时间戳（超过 `staleMs` 判 STALE）；
5. **`Adc_ReadGroup` 的现有实现会重新启动一次转换**，MUX 路径必须用
   `ReadGroupRaw`，避免"读一次又采一次"打乱 ABC 时序（实施时核对 `AdcAc.c`）。

## 8 实施分期（明确"能验证什么"）

| 期 | 内容 | 可验证 | 不可验证（缺硬件/规格） |
|---|---|---|---|
| **V1.0** | 能力接口 + Core + 直连 DIN/AIN/DOUT/PWM + 生成器 + Host 测试 | Host 16 组 / 39 条断言、生成器 R1~R10、上板 LED 与 CAN STB | 真实开关输入、真实模拟量、HSD/LSD |
| **V1.1** | RS2260 MUX（GPIO/ADC COM，**不需要 I2C**）→ I2C HAL + Expander | Host 模拟 ABC 时序、ADC 状态机；扩展器可用回环验证 | 真实 RS2260 时序（需板） |
| **V1.2** | HSD/LSD/Relay Adapter + 故障接口 | Host 故障注入；接口与 Dem 映射 | 开路/短路/过流的真实判定（需器件） |

**V1.1 的第一步是 RS2260 的 SelectBus 扫描状态机**，只用到现有 `Dio`/`Adc`，
不必等 I2C。`infras/include/I2c.h` + `I2cAc.c` 只服务于 PCA9555/TCA9539 一类
扩展器，应单列任务、不要塞进 RS2260 批次。

## 9 验收证据分级（避免"设计完成=功能完成"）

| 级别 | 证据 | 能证明 |
|---|---|---|
| A 静态 | 生成器两条规则注入失败、`IoHwAb.c` 不含引脚/SDK 头 | 边界没被绕过 |
| B Host | 16 组 / 39 条断言（消抖、极性、新鲜度、滤波、换算、饱和、四态、Init/ReInit、安全反馈、PWM、越界、不伪造） | 逻辑正确 |
| C 上板 | LED 亮灭、CAN STB 不受影响、m3 18/18 | 直连 IO 真实可用 |
| D 实物 | 示波器/电流探头/故障注入 | **V1.0 不声称达到** |

## 10 未决问题（实施前需要确认）

1. **RS2260 的 ABC 建立时间与 INH 时序**（决定扫描状态机的 `WAIT_SETTLE` 拍数）。
2. **HSD/LSD 具体型号**（V2.0 只写"HSD_MODEL_A"）——决定故障接口是否需要电流采样。
3. **AIN 的 `factor` 精度**：千分之一在 12 bit ADC 下约 0.03% 分辨率，是否够用。
4. 输出仲裁是否进 V1.2（当前结论：不进，业务层显式状态机优先）。

## 11 与 V1.0 旧设计的关系

`doc/设计评审/IoHwAb-V1.0设计.md` 是本文档的**实施切片**，其中两处已被本版收敛：

| 旧 V1.0 设计 | V2.0 基线 |
|---|---|
| 单一 `IoHwAb_HwOps` 函数表 | 按能力拆成 `DoutOps` / `DinOps` / `AinOps` / `PwmOps` |
| `IoHwAb_DinRead(id, boolean *valid)` | `IoHwAb_DinRead(id, boolean*, IoHwAb_StatusType*)` |

以本文档为准；旧文档保留作为设计过程记录。

## 12 V1.0 实施状态（2026-11-18）

### 12.1 已落地

| 文件 | 作用 |
|---|---|
| `infras/include/iohwab.h` | 公共契约：四类 ID、四态、四个能力 ops、API、配置表类型 |
| `tools/generator/IoHwAb.py` | 从 Board.json `io` 段生成通道枚举/计数/表；校验 R1~R8、R10 |
| `app/app/src/iohwab.c` | Core：消抖、滤波、定点换算、极性、安全状态（Target/Host 同一份） |
| `app/platform/cvm0146/src/IoHwAbAc.c` | 目标能力：Dio / Pwm；Host 通道为空桩（NULL 指针） |
| `app/platform/host/test/test_iohwab.c` + `iohwab_host_ops.c` | Host 用例与内存后端 |
| `app/app/src/cmd/io_cmd.c` | `io status/safe/led r|g|b on|off`，上板自检入口 |
| `app/app/src/main.c` | `IoHwAb_Init()`（安全状态）+ 10 ms `IoHwAb_MainFunction()` |

### 12.2 验证结果

| 级别 | 结果 |
|---|---|
| A 静态 | `app/app/src/iohwab.c` 不含任何引脚号与 SDK 头；生成器校验失败即终止 |
| B Host | **39/39 断言（16 组）**，`host_build` 6/6 套件通过（V1.0.1 后） |
| C 上板 | `io status`：Init 后 dout=0；`io led r on` → 1；`off` → 0；通信回归 11/11 |
| D 实物 | **未做**：LED 是否真的亮需人眼确认；无 HSD/LSD/示波器 |

### 12.3 实施中发现的两个真实约束

1. **`PinsDrv_ReadPin()` 读的是 PDIR（输入数据）**，纯输出引脚的输入通路未使能时恒为 0。
   因此目标侧回读用**输出锁存影子**，只能证明"写通路已执行"，不能证明引脚电平。
   Host 后端的回读是真实内存值，Host 用例不受影响。
2. **Host 通道在板上必须返回 `E_NOT_OK`**：`io status` 里 `din[0] status=3(ERROR)`
   是**正确行为**，不是故障 —— 它证明"不支持的能力没有伪造正常值"。

### 12.4 V1.1 的第一件事

**RS2260 的 SelectBus 扫描状态机**（A/B/C 选通 + COM 读 GPIO/ADC），只用现有
`Dio`/`Adc`，**不需要 I2C**。I2C HAL 只服务 PCA9555/TCA9539，单列任务。

### 12.5 V1.0.1 收口（2026-11-18，六项契约修正）

见 `doc/设计评审/IoHwAb-V1.0.1收口.md`。摘要：

| 项 | 修正 |
|---|---|
| P0 依赖 | RS2260 不需要 I2C，I2C 只是 Expander 前置 |
| P0 极性 | 唯一归属 Core，Adapter 只收发电气电平 |
| P0 初始化 | `Init` 运行期空操作；新增 `ReInit` 与 `IsInitialized` |
| P1 换算 | `int64_t` 中间量 + 饱和；右移改为显式朝零舍入 |
| P1 新鲜度 | 输入 ops 带 `seq`，无新样本不推进消抖/滤波 |
| P1 安全反馈 | `SetAllSafe` 返回结果；新增 `DoutGetFault`，区分"不适用"与"失败" |

