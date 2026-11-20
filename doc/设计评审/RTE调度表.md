# RTE 调度表（10.5 runnable 调度）

> **编写**：binbina ｜ **日期**：2026-11-20 ｜ **状态**：已实现，Host 9/9 + 静态回归 10/10
>
> **结论前置**：应用 runnable（BcmSig / BcmBiz / ComApp / AdcSampler / IoHwAb）
> 的**顺序与周期**从 `main.c` 的手写调用收进 `Board.json` 的 `rte.schedule`，
> 由生成器产 `Rte_Schedule.h`，新文件 `rte_sched.c` 的 `Rte_MainFunction()`
> 按表执行。**改调度不改代码**；分频机制支持 10 ms 整数倍周期。
> 本次是行为等价重构：执行顺序、周期、时序与收编前逐拍一致。

## 1 变更总览

| 文件 | 变更 |
|---|---|
| `Board.json` | `rte.schedule`：5 个 runnable 的顺序 + 周期（全 10 ms，与原 main.c 顺序一致） |
| `tools/generator/BcmRte.py` | 校验 S1~S4，生成 `Rte_Schedule.h`（原型 + 初始化列表宏） |
| `app/app/src/rte_sched.c` | **新增**：展开表 + 倒数计数分频 + `Rte_MainFunction()` |
| `app/app/src/rte_cfg.h` | `Rte_SchedFunc` / `Rte_SchedEntryType`（V0.3.0） |
| `app/app/src/rte.h` | 声明 `Rte_MainFunction()`（V0.4.0） |
| `app/app/src/main.c` | 5 个手写调用 → 1 个 `Rte_MainFunction()`（V2.9.0） |
| `tools/a1_sched_check.py` | `Rte_Schedule.h` 登记为第二个调度注册点；Host 测试目录豁免 |
| `tools/rte_sched_check.py` | **新增**：S 规则缺陷注入 + 变体配置编译运行（16 项断言） |
| `tools/host_build.py` + `test_sched.c` | 新增 `sched` 套件（真实配置驱动替身 runnable） |

## 2 设计决策

### 2.1 表放 Board.json 生成，机制放 rte_sched.c

| 要改什么 | 改哪里 | 谁保证 |
|---|---|---|
| runnable 顺序 / 周期 / 增删 | `Board.json` → 重新生成 | 生成规则 S1~S4 + 编译器（原型在生成头里） |
| 调度机制（计数、分频） | `rte_sched.c` | host `sched` 套件 |

与端口表（V0.2）同一模式：**只生成头**，表体在 app 层展开——生成 `.c` 会
被编进平台库，而平台库 include 路径里没有 app 头，会让平台层反向依赖应用层。

### 2.2 runnable 原型必须随表生成

第一版没生成原型，`rte_sched.c` 编译报"undeclared"。修法不是去 include
各组件头（那样每换一个项目都要手工补 include，"换项目只改 Board.json"
就不成立），而是生成器在 `Rte_Schedule.h` 里直接 `extern void FN(void);`。
**生成物自包含**是这条承诺的前提。

### 2.3 分频语义：执行后重装 reload-1

| reload | 计数器序列 | 行为 |
|---|---|---|
| 1 | 常驻 0 | 每拍执行 |
| 3 | 2→1→0 | 每 3 拍执行 |

首版写成"执行后装 reload"，reload=1 变成隔拍执行（host 用例
`s_cnt=[6,6,6,6,6]` 当场抓住）——这正是替身 runnable 用例的价值。

### 2.4 顺序即配置，跨周期依赖不允许

表内顺序 = **同一拍内的执行顺序**，两条硬依赖靠表序表达：

| 依赖 | 原因 |
|---|---|
| BcmSig 在 BcmBiz 之前 | 业务读的是本拍刚刷新的信号影子 |
| AdcSampler 在 IoHwAb 之前 | 先发布 ADC 样本，IoHwAb 再消费，反了晚一拍 |

周期不同的 runnable 不会每拍同拍执行，**靠"跨周期顺序"表达依赖必然偶发
失效**——多周期化之前必须重新评审这两条依赖（写进 Board.json 注释）。

### 2.5 EcuM_MainFunction / BootApp_MainFunction 不进表

它们是**框架状态机**（RUN/POST_RUN/SLEEP 迁移、A/B 刷写交接），不是业务
组件 runnable；进板级 JSON 语义错位。留在 `main.c`，紧跟
`Rte_MainFunction()` 之后——这个位置也是 10.5 的顺序决策（应用在 BSW
之后跑，端到端延迟少一拍）的一部分。

### 2.6 空表合法（S4）

schedule 段缺省 → 占一行 `{ 1u, NULL }`（零长度数组不可移植），
`Rte_MainFunction` 跳过 NULL。与端口空表的占位策略一致。

## 3 校验（S1~S4）

| # | 规则 | 为什么 |
|---|---|---|
| S1 | func 是合法 C 标识符 | 存在性由编译器查（原型在生成头里） |
| S2 | period_ms 是 10 的倍数且 ≥10 | 折算成基准拍数；reload=0 会被永久跳过 |
| S3 | 同一 func 不得出现两次 | 出现两次 = 该 runnable 每拍跑两次，**时间基准减半**（A1 事故的调度表版） |
| S4 | schedule 缺省/为空 → 空表占位 | 没有业务组件的项目也能生成 |

`tools/rte_sched_check.py`：1 组合法符号断言 + 5 组缺陷注入 + S4 +
变体编译运行（16 项断言），已纳入静态回归 `rte_sched`。

## 4 验证

| 项 | 结果 |
|---|---|
| Host 全套件 | **9/9**（新增 `sched`：顺序 == 配置序、10 拍各执行 10 次） |
| `rte_sched_check` | **16/16**（变体 10/20/30 ms → 6 拍执行 6/3/2 次；顺序跟随配置） |
| 静态回归 | **10/10**（`--static-only`，含 a4 生成幂等） |
| A1 调度唯一性 | PASS——应用 runnable 已登记为注册点，写回 main.c 直接调会被抓 |
| 编译 | App/AppB 零警告；`text 249648 → 249792`（**+144 B**：表 + 计数器 + 原型） |
| 上板回归 | 待跑（14 例；行为等价重构，预期全绿） |

## 5 缺陷注入证据（能证伪）

| 注入 | 被谁抓 |
|---|---|
| `rte.schedule` 里同一 func 写两次 | S3（"时间基准减半"） |
| `period_ms: 7` / `0` / 缺失 | S2（三条各自独立报错） |
| 变体周期 10/20/30 + 顺序重排，同一份 `rte_sched.c` 编译运行 | 分频次数 6/3/2 与顺序 B→C→A 全部符合新配置 |

## 6 没做的（明确留下）

| 项 | 原因 |
|---|---|
| 事件型 runnable / 触发端口 | 现有需求全是周期读写，没有触发语义 |
| 调度表耗时统计 | PerfMon 已量 BSW 拍耗时；runnable 级耗时等有实际需求再加 |
| 跨周期依赖静态检查 | 当前全 10 ms 无此场景；多周期化时先做依赖评审（见 2.4） |
