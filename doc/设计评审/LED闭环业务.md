# LED 闭环业务（10.6）：第一条完整纵向切片

> **编写**：binbina ｜ **日期**：2026-11-20 ｜ **状态**：**上板 16/16、全回归 16/16**；Host 10/10（led_biz 12/12）
>
> **结论前置**：CAN1 收控制 → CanIf → PduR → Com → BcmSig → RTE → LED 状态机
> → RTE → IoHwAb → LED；LED 状态 → RTE → BcmSig → Com → PduR → CanIf → CAN0
> 每 100 ms 上报。整条链只改**配置 + 一个业务模块**，业务代码只认端口名。

## 1 链路与载体

```
CAN1 0x18FEF121 (CCVS, 100 ms)
  → CanIf → PduR → Com → BcmSig → RTE(LED_CTRL)
  → LedBiz 状态机 → RTE(LED_R) → IoHwAb → 板载 LED
  → RTE(LED_RUN_MODE/LED_OUT/LED_PHASE/FAULT_*) → BcmSig → Com → PduR → CanIf
  → CAN0 0x200 (100 ms)
```

| 方向 | 载体 | 说明 |
|---|---|---|
| 控制 | **复用** `CCVS.ParkingBrakeSwitch`（CAN1，100 ms，bit 2\|2） | 矩阵里已有的真实报文，0/1/2/3 语义天然匹配 |
| 状态 | `0x200`（CANTEST 测试报文，CAN0，100 ms）**新增 5 个信号** | 空位 bit 10–15，不动原有 `TX_COUNTER/TX_FLAG/TX_LEVEL` |

> **为什么不新起专用控制报文**：CAN1 的 34 条 RX 由 `can1.dbc` 注入，而 DBC 是
> 客户资料（`.gitignore` 排除）。新报文需要改注入脚本 + 多网络通道映射（生成器
> 目前按网络下标分配控制器号），代价远大于收益。第一版先用真实矩阵报文把
> **全链路**跑通；将来换成专用报文，只改 `Com.json` + `Board.json` 的 ref，
> **业务代码一行不动** —— 这正是 RTE 要证明的事。

## 2 行为契约

| 输入（LED_CTRL） | 动作 | 上报 |
|---|---|---|
| `ON`（raw 1） | 启动闪烁：亮相 500 ms → 灭相 500 ms 循环 | 模式=1，相位跟随 |
| `OFF`（raw 0） | 停止并熄灭 | 模式=0 |
| `ERROR/INVALID`（raw 2/3） | 不改输出；置"命令无效" | 故障位 cmd=1 |
| 500 ms 无**有效**命令 | 停止并熄灭 | 模式=0，故障位 timeout=1 |
| 上电至今无有效命令 | 熄灭 | 模式=3（尚未收到命令），**不算故障** |

要点：

1. **超时按“有效命令”计时，且分两条路径**：
   - **帧停发**：`Rte_Read` 返回 `MAX_AGE_EXCEEDED`（BcmSig 按 PDU 到达年龄判 500 ms）
     → 业务**立即**停止，不再等自己的计数；
   - **帧在、值无效**（raw 2/3）：PDU 是新鲜的，`Rte_Read` 仍返回 OK，
     业务用 10 ms 拍计数器累到 500 ms 再停。
   > 第一版两条路径叠加（先等 500 ms 新鲜窗口、再数 50 拍），实测帧停发要
   > **1 s** 才停，上板用例当场抓住；Host 已补“停发”用例钉死这条路径。
2. **闪烁非阻塞**：相位用拍计数翻转（50 拍 = 500 ms），没有 `DelayMs`。
3. **LED_OUT 只表示驱动成功提交**：板上没有灯电流/电压反馈，不能宣称"灯真的亮了"。
   Host 上 `LED_R` 是直连 DOUT（空桩），写必失败，因此 `LED_OUT` 恒为 0 ——
   这是诚实的语义，不是缺陷。

## 3 改动清单

| 文件 | 变更 |
|---|---|
| `Com.json` | 0x200 增加 `LedRunMode(10\|2)` / `LedOut(12\|1)` / `LedBlinkPhase(13\|1)` / `LedFaultTimeout(14\|1)` / `LedFaultCmd(15\|1)` |
| `bcm_sig.h` | TX 枚举 +5；RX 枚举 +`BCM_SIG_RX_LED_CMD` |
| `bcm_sig_cfg.c` | TX 表 +5 行；RX 表 +1 行（同一 Com 信号、同一 PDU，超时 500 ms） |
| `Board.json` | RTE 端口 +6（`LED_CTRL` + 5 个上报）；调度表 +`LedBiz_MainFunction`（10 ms） |
| `led_biz.c/.h` | **新增**：状态机（约 200 行，无抽象框架） |
| `main.c` | `LedBiz_Init()`（在 `BcmSig_Init` 之后） |
| `tools/host_build.py` | APP_SRCS +`led_biz.c`；新增 `led_biz` 套件 |
| `test_led_biz.c` | **新增**：11 项断言（默认/启动/时序/停止/无效/超时/恢复/上报语义） |
| `tools/rte_portmap_check.py` | 业务扫描与变体编译纳入 `led_biz.c`；变体保留 LED_R 端口改绑 `LED_G` |
| `tools/led_loop_check.py` | **新增**：上板验收（Kvaser 双通道） |
| `tools/regress_comm.py` | 新增 `led_loop`（hw 段） |

## 4 验证

| 项 | 结果 |
|---|---|
| 上板 `led_loop` | **16/16**（镜像探测、启动、闪烁 500 ms、停止、无效、超时、恢复、上报周期） |
| 全量回归 | **16/16**（静态 10 + 上板 6；`m19` 34 条 RX、`m3` 18 项诊断、`m10` 22 项均通过） |
| Host `led_biz` | **12/12**（含"帧完全停发"路径；启动、490/500/990/1000 ms 相位、停止、无效、超时、恢复） |
| Host 全套件 | **10/10**（新增 `led_biz`；`sched` 更新为 6 个 runnable） |
| 静态回归 | **10/10**（`rte_portmap` 13/13，含 LED 业务变体编译） |
| 编译 | App/AppB 零警告；`text 249792 → 250868`（+1076 B） |

上板脚本的判据：

| 用例 | 断言 |
|---|---|
| 启动 | 模式=1，1.6 s 内相位出现 0/1 |
| 闪烁时序 | 相邻相位跳变间隔 500 ms ±150 ms |
| 停止 | 模式=0、输出=0、相位=0 |
| 无效命令 | 故障位 cmd=1，不误报 timeout |
| 超时 | 停发 750 ms 后模式=0、输出=0、timeout=1 |
| 恢复 | 重新发有效命令：两个故障位清零、模式=1 |
| 上报周期 | 0x200 间隔 100 ms（80–130 ms） |

## 5 已知边界

| 项 | 说明 |
|---|---|
| 控制载体的语义 | CCVS 的手刹位原本用于 `BcmBiz`（驻车→制动灯）；`BcmBiz` 默认不接管输出，互不干扰。换成专用报文后此边界消失 |
| 无电气反馈 | `LED_OUT` 不能当"灯真的亮了"；将来加诊断回路要**新增**信号，不改其含义 |
| 无效命令期间的行为 | 保持当前输出（不立即熄灭），500 ms 后超时停 —— 与"其他值无效"的字面解释一致 |
| 上板脚本未实跑 | 依赖 Kvaser 与板子；布局已与 `Com.json` 手工对齐，改配置需同步 |
