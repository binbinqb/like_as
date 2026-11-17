# 整机执行速度与 Flash 缓存

> **编写**：binbina ｜ **日期**：2026-11-17 ｜ **状态**：已定位并修复一处 3.2 倍降速

## 1 一句话结论

`FeeAc_Init()` 把 `CACHE_CTRL` 整个写成 0，连**全局缓存与 PFlash 预取**一起关掉，
导致整机（取指 + 常量表访问）慢到 **1/3.2**；只清 `FLS_EN` 一位即可满足 FEE 回读校验，
速度恢复。实测 245 KB 镜像 CRC：**267 ms → 81 ms**。

## 2 怎么发现的

起因是"给 Boot 选槽加耗时打点"，结果一路撞出三件事：

| 顺序 | 撞到的东西 | 关键证据 |
|---|---|---|
| 1 | Boot 里 DWT 计数器**冻结**，量出 0 µs | `DEMCR` 从 `0x01000000`（刚初始化）变成 `0x00000000`；10 万次自旋循环 `delta=0` |
| 2 | 同一段代码在 App 里 267 ms、在启动早期只有 84 ms | 同一二进制、同一镜像、两个时基一致 |
| 3 | `CACHE_CTRL` 在 `EcuM_StartupTwo()` 之后变成 0 | 四个测点读寄存器：`0x1C5 → 0x1C5 → 0x00000000 → 0x00000000` |

## 3 时基怎么选（踩过的两个坑）

| 坑 | 现象 | 结论 |
|---|---|---|
| Boot 里用 `PerfMon_Cycles()`（DWT） | 计数器冻结；唯一一次"能走"时读数还比真实值大一倍 | **Boot 里不要用 DWT**。谁清了 `DEMCR` 仍未查清（25.x 待办） |
| 关中断期间用 `Platform_NowMs()` | 量出 `0 ms`（245 KB 不可能） | `Platform_NowMs()` 由 SysTick **中断**推进，关中断时原地不动。关中断场景只能用 CYCCNT |

两个时基本身是可信的：

- `CYCCNT` 与 SysTick 交叉标定：200 ms 内 **23,919,953** 个周期 → **119,599,765 Hz ≈ 120 MHz**；
- 心跳间隔用**主机时间戳**复核：ECU 打印 `1000 ms/拍`，主机实测 `1.00 s/拍`。

## 4 实测数据（CVM0146-EVK，245 KB 镜像）

| 项目 | 数值 | 备注 |
|---|---|---|
| 整镜像 CRC，裸指针一次算 | **76 ms** | 改造前的写法 |
| 整镜像 CRC，256 B 分段（现在 Boot 用的） | **81 ms** | 离板可测的代价 = 5 ms |
| 整镜像 CRC，`CACHE_CTRL=0` 时 | **267 ms** | 修复前 |
| 关中断 / 开中断 | 81.1 / 81.4 ms | 差 0.3 ms → 中断不是瓶颈 |
| NvM 读取（`DFlash ... read`） | **34 → 25 ms** | 修复后的附带收益 |

> 上表 `267 ms` 与 `81 ms` 是同一份代码、同一个镜像、同一块板，唯一差别是
> `CACHE_CTRL` 的值。**不要**把"整机慢"归因于中断负载或时基不准 —— 都已经排除。

## 5 事故：`CACHE_CTRL` 被整写 0

### 5.1 现场

```
[dbg] after BootApp      crc=84236 us  cache=000001C5
[dbg] after FlashLoader  crc=84232 us  cache=000001C5
[dbg] after StartupTwo   crc=84251 us  cache=000001C5   ← 修复后
（修复前同一测点：  crc=267085 us  cache=00000000）
```

`EcuM_StartupTwo()` 里跑 `NvM_ReadAll` → `Fee_...` → `FeeAc_Init()`。

### 5.2 根因

```c
/* 修复前，FeeAc.c */
*((volatile uint32_t *)FEEAC_CACHE_CTRL_ADDR) = 0x00000000u;
```

注释写的理由是"本板复位后该寄存器全 0（缓存关）"——**这是错的**：
`sdk/drivers/cpu/startup/system_M014x.c` 的 `SystemInit()` 明确写了
`CACHE->CTRL = 0x1C7` 与 `SimReg_SetFlashPFlsPfbEn(SIM, 1)`。

`0x1C7` 的构成（`sdk/reg/cache_reg.h`）：

| 位 | 掩码 | 名称 | 整写 0 的后果 |
|---|---|---|---|
| 0 | `0x001` | `EN` | 全局缓存关 |
| 1 | `0x002` | `FLS_EN` | Flash 侧缓存关（**这一位才是 FEE 需要的**） |
| 2 | `0x004` | `PFB_EN` | PFlash 预取关 |
| 6/7 | `0x040`/`0x080` | `MCNT_EN`/`HCNT_EN` | 命中统计关 |
| 8 | `0x100` | `R0_MODE` | 区域 0 模式变 |

### 5.3 修法

只清 `FLS_EN`，其余保持 `SystemInit()` 设的值：

```c
uint32_t cacheCtrl = *(volatile uint32_t *)FEEAC_CACHE_CTRL_ADDR;
*(volatile uint32_t *)FEEAC_CACHE_CTRL_ADDR = cacheCtrl & ~FEEAC_CACHE_CTRL_FLS_EN;
```

### 5.4 验证

| 项 | 结果 |
|---|---|
| 四个测点的 `cache` | 全为 `0x1C5`（`0x1C7` 去掉 `FLS_EN`） |
| CRC 耗时 | 84 ms（不再随初始化阶段跳变） |
| 存储路径 | `nvm writeall` → `<+0, OK!`；`nvm dump` 四块 `st=0`，BOOTCNT/VIN 数值不变 |
| 心跳与时间基准 | 1.00 s/拍（未变） |

> `nvm writeall` 这一步不能省：`FLS_EN` 就是为"擦→写→**回读校验**"关的，
> 改错成不清它，会退化成 `FLS_STATE_READ_BACK_FAIL`——而且只在真写过之后才暴露。

## 6 怎么复现这组数

串口（UART2 / 115200）敲：

```
bootperf
```

输出三行（都是 CYCCNT 计时，关中断一组等价于 Boot 选槽时的环境）：

```
<+0, image 245616 B @ 0x00020000  (all times from CYCCNT)
     direct  irq-off : 76249 us  crc=10EB7F52
     chunked irq-off : 81105 us  crc=10EB7F52  same
     chunked irq-on  : 81387 us  crc=10EB7F52
```

`bootperf` 只在开发构建里存在；`build.bat --app=App --prod` 的镜像里
`grep -c bootperf` = **0**。

## 7 待办

| 编号 | 事项 | 为什么重要 |
|---|---|---|
| P1 | 查清 Boot 里谁把 `DEMCR` 清成 0 | 现在 Boot 无法自测耗时，只能靠 App 侧代测 |
| P2 | 查 `CACHE_CTRL.EN`（bit0）的准确语义（RM 30.3.2） | 现在靠"只清 FLS_EN"规避；若 EN 才是 Flash 缓存总闸，修法要跟着改 |
| P3 | 把"整机执行速度"做成可回归的判据 | 这次降速能活这么久，是因为**没有任何断言盯它** |
