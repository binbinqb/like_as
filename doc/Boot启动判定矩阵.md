# Boot 启动判定矩阵（22.3 复位恢复）

> **编写**：binbina ｜ **日期**：2026-11-17 ｜ **状态**：判定矩阵与 Host 用例已建立，**两个缺陷待修**
>
> **判据来源**：`app/boot/src/main.c` 的判定链 + `app/platform/cvm0146/src/BootMeta.c` 的状态机，
> 由 `app/platform/host/test/test_boot_meta.c`（22 条断言）在 Host 上**真编译被测代码**逐条执行。
> 不是读代码推断，也不是按理解重写的模型。

---

## 1 判定链路（代码位置）

```
上电
 ├─ BootMeta_Init()                 BootMeta.c:131   两槽各读主/备 meta，取 rollingCounter 大者
 ├─ [0] 刷写标志处理                main.c:668       reserved[0]==REQ_FLASH → 先清 0xFF → 进 UDS（30 s 空闲超时）
 ├─ [1] slot = GetActiveSlot()      BootMeta.c:175   跳过 EMPTY / INVALID，取 counter 最大的槽
 ├─ [2] CheckImage(slot)            BootMeta.c:205   长度 → 向量表(SP/PC) → 整镜像 CRC32
 │     ├─ OK            → chosen = slot
 │     ├─ 失败但 meta 有效 → DemoteToTesting → chosen = slot   ← ⚠ 见 D1/D2
 │     └─ meta 无效      → 换另一个槽；另一个也失败则看向量表兜底  ← ⚠ 见 D3
 ├─ [3] PrepareJump(chosen)         BootMeta.c:293   TESTING 时 attempts+1，>3 判 INVALID 并返回失败
 │     └─ 失败 → 换另一个槽；另一个也坏 → 进 UDS
 └─ [4] Platform_JumpToApp(base)    main.c:772
```

---

## 2 矩阵：现场 × 期望 × 实测

`实测` 一列全部来自 Host 用例，行号即断言来源。

| # | 现场 | 期望（用户判据） | 实测 | 结论 |
|---|---|---|---|---|
| 1 | 两槽全 0xFF（未烧写） | 不盲目跳转 | 无活动槽；`meta 无效 → DemoteToTesting 返回失败` | ✅ 满足（B1） |
| 2 | A=CONFIRMED、镜像完好 | 正常启动 | 选 A、校验通过 | ✅ 满足（B2） |
| 3 | A 镜像 CRC 失败、meta 有效 | **不执行未经验证的镜像** | 降级成 TESTING 后**仍然跳转** | ❌ **不满足**（B3，D2） |
| 4 | 同上，连续上电 10 次 | 达阈值后停止重启 / 回滚 | 计数每轮被清回 1，**永不 INVALID** | ❌ **不满足**（B4，D1） |
| 5 | A=TESTING、镜像完好、连续启动失败 | 3 次后判 INVALID | 第 4 次判 INVALID、落盘、不再被选中 | ✅ 满足（B5） |
| 6 | A=INVALID、B=CONFIRMED 且镜像好 | 回滚 B | 选 B、校验通过 | ✅ 满足（B6） |
| 7 | 两槽都 INVALID | 停留 UDS | 无活动槽 → `main.c:748` 进 UDS | ✅ 满足（B7） |
| 8 | 主 meta 损坏、备 meta 好 | 主备择优 | 仍判定有效、镜像可校验 | ✅ 满足（B8） |
| 9 | CRC 正确但向量表 SP 越界 | 校验失败 | 拒绝 | ✅ 满足（B9） |
| 10 | 刷写请求后诊断仪退出 | 超时恢复启动 | — | ⏸ **未测**（需上板，30 s 空闲超时） |

> 第 5 行是**对照组**：它证明"尝试计数 → INVALID → 回滚"这套机制本身是好的。
> 第 4 行失败，说明降级路径绕过了它，而不是机制没实现。

---

## 3 三个缺陷

### D1 降级路径把尝试计数清零 → 永不回滚（严重）

`BootMeta_DemoteToTesting()` 写回 meta 时 `bootAttempts = 0`：

```c
meta = info->meta;
meta.state        = BOOT_SLOT_TESTING;
meta.bootAttempts = 0u;        /* ← 每次上电都清零 */
```

而 `main.c:707-721` 的降级分支每次上电都会走一遍 `DemoteToTesting` → `PrepareJump`：

| 上电次数 | 降级后 attempts | PrepareJump 后 | 状态 |
|---|---|---|---|
| 1 | 0 | 1 | TESTING |
| 2 | **0（被清）** | 1 | TESTING |
| … | 0 | 1 | TESTING |
| 10 | 0 | 1 | TESTING |

`PrepareJump` 只在 `attempts > 3` 时判 INVALID，而计数永远回到 1。

**后果**：镜像 CRC 一直失败时，板子每次上电都跳到同一份坏镜像，**永不回滚到另一个槽**。
代码注释里写的"3 次后判 INVALID 并回滚"在这一分支上不成立。

> 这条比"可能跳到坏镜像"更严重：它把 A/B 结构最核心的保命能力（回滚）废掉了。

### D2 陈旧 meta 与镜像损坏不可区分

J-Link 重烧 app 后槽尾 meta 还是旧 CRC，与"Flash 位翻转导致镜像损坏"，在 boot 看来
**完全一样**（meta 结构有效 + 镜像 CRC 不符）。现有实现选择"都当陈旧 metadata，
降级照跳"，动机是避免"烧完能跑一次、一复位就 HALT"的死锁。

但这个取舍对量产不成立：量产不应存在"J-Link 重烧"这个场景，却要为它保留
"跳过未验证镜像"的通道。

### D3 向量表兜底是第二个"未验证镜像"入口

`main.c:729-731`（另一个槽也校验失败时）与 `main.c:738-741`（完全没有有效 meta 时）
都会用 `Boot_LooksLikeImage()` 只看 SP/PC 两个字，**不看 CRC** 就跳转。
首次烧写需要它，量产不需要。

---

## 4 修复方向（**尚未实施**，先评审）

原则：把"开发调试便利"和"量产安全"用编译期开关分开，而不是继续用运行时启发式猜。

| 项 | 做法 | 影响 |
|---|---|---|
| `BOOT_ALLOW_STALE_META` | debug 构建 =1（保留降级自注册）；release =0（CRC 失败直接判 INVALID 走回滚） | D1、D2 |
| `BOOT_ALLOW_VECTOR_FALLBACK` | debug =1；release =0（无有效 meta 一律进 UDS 等刷写） | D3 |
| 降级前不清计数 | `DemoteToTesting` 保留 `bootAttempts`（或只在 debug 下清零） | D1 |
| 修复后的判据 | B4 断言改成"第 4 次降级启动后判 INVALID 并回滚到 B" | 回归 |

**为什么用编译期开关而不是运行时标志**：运行时标志存在 Flash / NvM 里，本身就会
被损坏或误写；而"这块板是不是量产件"在编译时就是确定的。

---

## 5 上板验证计划（需要 Kvaser + 目标板）

### 5.1 先说结论：现有 UDS 服务**造不出**这些故障

这一条必须先查清，否则测试脚本写了也跑不通。查完的结果是**做不到**，原因在设计本身：

| 服务 | 实际校验 | 后果 |
|---|---|---|
| `0x31` 擦除 | `FlashLoader_MatchSlotBase()` 只接受**槽基址**（`FlashLoader.c:181`） | 不能擦任意地址 |
| `0x31` 擦除 | `FlashLoader_IsActiveSlot()` 拒绝擦**活动槽**（`:190`） | 不能擦正在跑的那一槽 |
| `0x31` 擦除 | 擦除长度上界 `BOOT_SLOT_IMAGE_MAX` = 槽大小 − meta 区 | **meta 不会被擦掉** |
| `0x34` 下载 | 同样只接受槽基址、拒绝活动槽（`:283`、`:291`） | 不能写镜像中间某个字节 |
| `0x37` 收尾 | CRC 是**写完之后从 Flash 回读算的**（`:307`） | meta 里的 CRC 必然与镜像一致 |

最后一条尤其关键：`0x37` 的 `meta.imageCrc = Crc_CalculateCRC32((const uint8_t *)s_dl.base, ...)`
——CRC 取自 Flash 现状，所以**经 UDS 刷进去的镜像，meta 永远自洽**。
"meta 有效但镜像 CRC 不符"这个状态，UDS 路径从构造上就到不了。

> 这其实是好消息：说明刷写链路本身是自洽的，D1/D2 不是刷写引入的，
> 而是"外部改写"（J-Link / 位翻转）才可能遇到的状态。但它也意味着
> 这两个缺陷**无法用现有诊断服务复现**。

### 5.2 故障注入的两条可行路径

| 方案 | 做法 | 代价 |
|---|---|---|
| **A. J-Link 直写**（可脚本化） | `JLinkExe` + 脚本：`w4 <addr> <value>` 改 meta 或改镜像一个字节，然后复位 | 需要 J-Link 与命令行工具；属于"外部改写"，与真实故障同构 |
| **B. app 内加调试命令**（推荐） | shell 加 `bootfault <slot> <kind>`，仅 **debug 构建**编译：`kind` = `meta-crc` / `img-byte` / `meta-blank` | 要改 app 代码；但可串口触发、可进自动化脚本，release 不含此代码 |

方案 B 更契合本项目已有的验证方式（`m3_check` / `a9_biz_check` 都是串口 + Kvaser 脚本）。
建议与 D1 的修复一起做：**先加钩子 → 复现缺陷 → 改 boot → 用同一脚本回归**。

### 5.3 上板用例（方案 B 就绪后）

| 编号 | 注入 | 期望（修复后） |
|---|---|---|
| H1 | `bootfault A img-byte`（A 为活动槽，改镜像 1 字节） | 复位后不跳 A |
| H2 | H1 基础上连续复位 4 次 | 第 4 次判 A=INVALID 并回滚 B，不再尝试 A |
| H3 | `bootfault A meta-blank`（抹掉两槽 meta） | 停在 UDS；`0x22` 读 VIN 可响应 |
| H4 | `10 03` 让 app 写刷写标志后复位，诊断仪不连接 | 30 s 后自动恢复启动 |
| H5 | H4 中在 30 s 内开始刷写 | 不超时，正常刷完 |
| H6 | 刷写过程中断电（槽内镜像不完整） | 复位后旧槽仍可启动 |

⚠ H1~H3 都需要**活动槽**上出现坏镜像，而 `0x31/0x34` 明确拒绝活动槽——
这正是必须用 A/B 方案之一的原因，不是遗漏。

---

## 6 本次已改的代码（唯一一处）

`BootMeta.c` 的整镜像 CRC 原先用裸指针：`Crc_CalculateCRC32((const uint8_t *)base, ...)`。
板上 Flash 内存映射能跑，但它和同一函数里的向量表读取（走 `Platform_FlashRead()`）
是**两条不同的取数路径**，而且导致这个函数在 Host 上完全没法测。

改为 `BootMeta_ImageCrc()`：按 64 B 分段经 `Platform_FlashRead()` 取数，用 AUTOSAR 的
分段 CRC 约定累算。行为等价由 B2 证明（测试端一次性算、固件端分段算，结果必须一致）。

| 镜像 | 改动前 | 改动后 | 说明 |
|---|---|---|---|
| Boot | 51,896 | **51,968**（+72 B） | 新增分段循环 |
| App | 241,084 | 241,084 | `CheckImage` 只有 boot 调，被 `--gc-sections` 回收 |
| AppB | 241,084 | 241,084 | 同上 |

⚠ **需上板复核**：boot 选槽时的 CRC 计算从"直读"变成"分段 memcpy"，逻辑等价但
启动耗时略增（444 KB 上限约 7000 次调用，实测毫秒级）。H3 那一步会顺带验证。
