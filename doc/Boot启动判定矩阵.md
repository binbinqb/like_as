# Boot 启动判定矩阵（22.3 复位恢复）

> **编写**：binbina ｜ **日期**：2026-11-17 ｜ **状态**：判定矩阵与 Host 用例已建立，**D1/D2/D3 已修**，待上板复核
>
> **判据来源**：`app/boot/src/boot_choice.c`（选槽）+ `app/platform/cvm0146/src/BootMeta.c`（状态机），
> 由 Host 用例**真编译被测代码**逐条执行：`test_boot_meta.c` 20 条、`test_boot_choice.c`
> 在开发/量产两种编法下各 9 条。不是读代码推断，也不是按理解重写的模型。

---

## 1 判定链路（代码位置）

```
上电
 ├─ BootMeta_Init()                 BootMeta.c:131   两槽各读主/备 meta，取 rollingCounter 大者
 ├─ [0] 刷写标志处理                main.c            reserved[0]==REQ_FLASH → 先清 0xFF → 进 UDS（30 s 空闲超时）
 ├─ [1~3] Boot_ChooseSlot()         boot_choice.c    选槽 → 校验 → 计数 / 回滚（见下）
 │     ├─ CheckImage(OK)            → 跳它
 │     ├─ 失败 + 开发模式            → DemoteToTesting（**保留计数**）→ 跳它
 │     ├─ 失败 + 量产模式            → 判 INVALID → 回滚另一槽
 │     └─ 另一槽也不行               → 开发看向量表兜底；量产直接等刷写
 └─ [4] Platform_JumpToApp(base)    main.c
```

> 选槽判定原先内联在 `main.c` 里。抽成 `boot_choice.c` 的原因：它要按**开发/量产**
> 两套策略分支，内联在 `main` 里就只能上板才能验证。抽出后同一份源码用
> `-DBOOT_MODE_PRODUCTION=0/1` 各编一次，两套策略都被真实执行过。

---

## 2 矩阵：现场 × 判据 × 实测

| # | 现场 | 判据（用户要求） | 修复前 | 修复后 | 结论 |
|---|---|---|---|---|---|
| 1 | 两槽全 0xFF | 不盲目跳转 | 无活动槽；meta 无效不降级 | 同左 | ✅ B1 |
| 2 | A=CONFIRMED、镜像完好 | 正常启动 | 选 A、校验通过 | 同左 | ✅ B2 |
| 3 | A 镜像 CRC 失败、meta 有效 | **不执行未验证镜像** | 降级后**照跳** | 量产：判 INVALID 回滚；开发：降级跳 | ✅ C2 |
| 4 | 同上，连续上电 | 达阈值停止重启 | 计数恒为 1，**永不回滚** | 第 4 次判 INVALID 回滚 | ✅ B4/C3 |
| 5 | A=TESTING、镜像完好、连续失败 | 3 次后判 INVALID | 第 4 次判 INVALID | 同左 | ✅ B5/C6 |
| 6 | A=INVALID、B=CONFIRMED 好 | 回滚 B | 选 B | 同左 | ✅ B6 |
| 7 | 两槽都 INVALID | 停留 UDS | 无活动槽 → 进 UDS | 同左 | ✅ B7/C5 |
| 8 | 主 meta 损坏、备 meta 好 | 主备择优 | 仍可用 | 同左 | ✅ B8 |
| 9 | CRC 正确但向量表 SP 越界 | 校验失败 | 拒绝 | 同左 | ✅ B9 |
| 10 | 刷写请求后诊断仪退出 | 超时恢复启动 | — | — | ⏸ 需上板（H4/H5） |

第 5 行是**对照组**：它证明"尝试计数 → INVALID → 回滚"这套机制本身是好的。
第 3/4 行修复前失败，说明问题在降级分支绕过计数，而不是机制缺失。

---

## 3 三个缺陷与修法

### D1 降级路径把尝试计数清零 → 永不回滚（已修）

`BootMeta_DemoteToTesting()` 原本 `meta.bootAttempts = 0`，而 boot 每次上电只要 CRC
不符就会再调一次，于是计数永远回到 1：

| 上电次数 | 修复前 降级后→PJ后 | 修复后 |
|---|---|---|
| 1 | 0 → 1 | 0 → 1 |
| 2 | **0 → 1** | 1 → 2 |
| 3 | 0 → 1 | 2 → 3 |
| 4 | 0 → 1 | 3 → 4 → **INVALID，回滚** |

**修法**：降级时保留 `bootAttempts`（`BootMeta.c`）。CONFIRMED 的计数本来就是 0，
不需要额外分支。

### D2 陈旧 meta 与镜像损坏不可区分（已修：用编译期开关区分策略，不再猜）

两者在 boot 看来完全一样（meta 结构有效 + CRC 不符），无法在运行时区分。
原实现选择"都当陈旧 metadata，降级照跳"，动机是避免 J-Link 重烧后的死锁；
但这个取舍对量产不成立。所以改成**编译期**开关：

| 构建 | `BOOT_ALLOW_STALE_META` | CRC 不符时 |
|---|---|---|
| `build.bat --app=Boot`（开发） | 1 | 降级 TESTING 后照跳，靠计数兜底 |
| `build.bat --app=Boot --prod`（量产） | 0 | 判 INVALID，回滚另一槽 |

### D3 向量表兜底是第二个"未验证镜像"入口（已修：同样受开关控制）

`Boot_LooksLikeImage()` 只看 SP/PC 两个字、不看 CRC。首次烧写需要它，量产不需要。
量产构建下 `BOOT_ALLOW_VECTOR_FALLBACK=0`：没有有效 meta 一律停 UDS（C4）。

### 为什么用编译期而不是运行时标志

运行时标志要存在 Flash / NvM 里，它本身就会被损坏或误写；而"这块板是不是量产件"
在编译时就是确定的。两个宏的默认值在 `boot_flash_map.h`（开发=0 即宽松）。

---

## 4 上板验证（需要 Kvaser + 目标板）

### 4.1 故障注入为什么不能用 UDS

| 服务 | 实际校验 | 后果 |
|---|---|---|
| `0x31` 擦除 | 只接受槽基址；拒绝活动槽 | 擦不到正在跑的那一槽 |
| `0x34` 下载 | 同上 | 写不到镜像中间某个字节 |
| `0x37` 收尾 | CRC 从 Flash **回读**算 | meta 永远与镜像自洽 |

最后一条是决定性的：经 UDS 刷进去的镜像，`meta.imageCrc` 必然是它自己的。
"meta 有效但镜像 CRC 不符"在 UDS 路径上**构造不出来** —— 这反过来证明刷写链路
本身自洽，D1/D2 不是刷写引入的。

### 4.2 已实现的注入钩子：`bootfault`

`app/app/src/cmd/bootfault_cmd.c`，**只在开发构建里存在**（`BOOT_MODE_PRODUCTION`
编译期剔除；量产镜像里连字符串都没有，实测 `grep -c bootfault` = 0）。

| 命令 | 做什么 | 不动镜像 |
|---|---|---|
| `bootfault meta-crc` | 活动槽 `meta.imageCrc ^= 0xFFFFFFFF` | ✅ 只改 meta |
| `bootfault meta-blank` | 擦掉两槽的 meta（模拟从未烧写） | ✅ |
| `bootfault testing N` | 活动槽置 TESTING 且 `bootAttempts=N` | ✅ 只改 meta |

只改 meta 是刻意的：最坏情况只是"启动判定走另一条分支"，不会让板子变砖
（镜像本身是好的，开发模式下照常启动）。**刻意不提供"改镜像字节"** —— 那会让
下一次启动必然跑飞，恢复只能靠 J-Link。

> **为什么必须有 `testing N`**：只用 `meta-crc` 验不到"计数累加 → 回滚"。
> CRC 改坏之后，App 只要还能起来，`BootApp_Init` 就会发现 `imageSize/imageCrc`
> 与 meta 不符并**重写 meta**（self-register）—— 计数随之清零。于是每轮上电都是
> "降级一次、修好一次"，永远累加不到阈值。`testing 3` 直接把"已失败 3 次"摆出来，
> 下一轮 `PrepareJump` 累加到 4 就判 INVALID 回滚，一轮看完。

### 4.3 上板用例

| 编号 | 注入 | 期望（修复后） |
|---|---|---|
| H1 | `bootfault meta-crc` + 复位 | 开发：日志出现 "boot anyway as TESTING"，板子照常启动 |
| H2 | `bootfault testing 3` + 复位 | 日志出现 "exceeded boot attempts, rollback to slot B"；B 无效则停 UDS |
| H3 | `bootfault meta-blank` + 复位 | 开发：向量表兜底启动；量产：停 UDS，`0x22` 读 VIN 可响应 |
| H3' | 刷量产 Boot 后 `meta-crc` + 复位 | 日志出现 "image rejected (production build)"，不跳坏镜像 |
| H4 | `10 03` 写刷写标志后复位，诊断仪不连接 | 30 s 后自动恢复启动 |
| H5 | H4 中 30 s 内开始刷写 | 不超时，正常刷完 |
| H6 | 刷写过程中断电 | 复位后旧槽仍可启动 |

H4/H5 已由既有 `uds_flash.py` 覆盖过正常路径（`7F 19 11` → 36 s 回退），
H6 依赖程控电源（与 M22 任务 4 同一个 SKIP 原因）。

---

## 5 代码改动清单

| 文件 | 改动 |
|---|---|
| `boot_meta.h` | 新增 `BootMeta_CalcImageCrc()`；`DemoteToTesting` 文档改为"保留计数" |
| `BootMeta.c` | ① 整镜像 CRC 改走平台层分段读（原为裸指针）；② 降级不清零计数 |
| `boot_flash_map.h` | 新增 `BOOT_MODE_PRODUCTION` / `BOOT_ALLOW_STALE_META` / `BOOT_ALLOW_VECTOR_FALLBACK` |
| `boot_choice.h/.c` | **新增**：选槽判定，含开发/量产两套策略与 INVALID 落盘 |
| `boot/main.c` | 判定段改为调用 `Boot_ChooseSlot()`；删掉已移走的两个静态函数 |
| `boot/SConscript` | 加 `include` 路径；`--prod` → `BOOT_MODE_PRODUCTION=1` |
| `app/SConscript` | `--prod` 同样传给 app（供 `bootfault` 剔除） |
| `cmd/bootfault_cmd.c` | **新增**：仅开发构建的注入钩子 |
| `tools/host_build.py` | 支持 per-test 附加源/头目录/`-D`；新增 3 个 boot 套件 |

### 尺寸

| 镜像 | 改动前 | 开发构建 | 量产构建（`--prod`） |
|---|---|---|---|
| App | 241,084 | 242,184（+1,100，含 bootfault 命令） | **241,084**（与基线一致，命令被剔除） |
| AppB | 241,084 | 242,184 | — |
| Boot | 51,896 | 51,996（+100） | **51,896**（与基线一致） |

⚠ **Boot 需上板复核算槽耗时**：CRC 从"直读"改成 64 B 分段 `memcpy`，444 KB 上限
约 7000 次调用。逻辑等价已由 B2 证明（测试端一次性算 vs 固件端分段算必须相等），
但实际耗时只有上板能量。H1 会顺带验证。

---

## 7 上板实测记录（2026-11-17，CVM0146-EVK）

镜像：Boot `build Nov 17 2026 14:58:20`（开发版）、App `build Nov 17 2026 15:11:13`
（开发版，含 `bootfault`）。串口 UART2 / 115200。

### 7.1 H1 陈旧 meta → 降级照跳（通过）

```
CVM014x >>  bootfault meta-crc
<+0, slot A meta.imageCrc=0x222566B1 (was 0x222566B1); reset to observe
```

> ⚠ 这条输出里的 "was" 是**假的**：真旧值是 `0xDDDA994E`（下一段 boot 日志的
> `crc=DDDA994E` 可以反推）。`BootMeta_Write()` 会同步更新内部缓存，而打印 "was"
> 用的 `info->meta.imageCrc` 正指向那块缓存 —— 写完已经是新值了。
> 已改为在 Write **之前**存旧值；本记录保留原始输出，不做美化。

复位后：

```
slot A : 0x020000  CONFIRMED  rc=27  size=244576  crc=222566B1  v2.8.0
[boot] dbg slot A: sp=2000F000 pc=00020401 size=244576 crc=DDDA994E expect=222566B1
[boot] slot A check failed, boot anyway as TESTING (meta may be stale)   ← 判据
[boot] jump to slot A  base=0x020000  entry=0x020400
[app] slot A meta mismatch, self-register  size=244576 crc=DDDA994E      ← 自愈
```

**结论**：meta 有效但镜像 CRC 不符时，开发版不判死、降级后照跳；app 起来后把 meta
修回正确 CRC。**同时印证了上板用例的设计前提**：正因为 app 会自愈，靠连续复位
看累加是看不到的 —— 必须用 `testing N`（见 7.2）。


### 7.2 H2 计数累加 → INVALID → 回滚（通过，**D1 修复的决定性证据**）

```
CVM014x >>  bootfault testing 3
<+0, slot A TESTING attempts=3; reset -> next boot will be 4 (>3 => INVALID + rollback)
```

复位后：

```
slot A : 0x020000  TESTING    rc=28  size=244576  crc=DDDA994E  v2.8.0
[boot] dbg slot A: sp=2000F000 pc=00020401 size=244576 crc=DDDA994E expect=DDDA994E
[boot] slot A exceeded boot attempts, rollback to slot B      ← 判据（修复前永不出现）
[boot] no valid image in slot A or B, waiting for flash
[boot] entering UDS flash mode ...
```

**结论**：计数从 3 累加到 4、超过 3 次上限、A 判 INVALID、回滚被触发。
`slot B : EMPTY (no meta)` 所以回滚目标不可用，按设计停在 UDS 等刷写（不是死机）。

这条在**修复前必然失败**：旧代码 `DemoteToTesting` 每次把 `bootAttempts` 清零，
计数永远是 1，日志里永远不会出现 `exceeded boot attempts`。

### 7.3 H4 刷写请求后不连接 → 30 s 自动回退（通过）

`tools/boot_accept.py` 自动跑（J-Link 复位 + UDS 单发 + 独占串口抓取）：

```
[dcm] session 1 -> 2 (requested)
[app] programming session -> will reboot into bootloader
=== boot 横幅（App 已自行复位）===
[boot] flash requested by app (10 02 programming session)
[boot] entering UDS flash mode ...
（★ 此后 30.0 s 内没有任何诊断请求）
[boot] no tester, leaving flash mode
[boot] resume normal boot after idle timeout
[boot] jump to slot A  base=0x020000  entry=0x020400
```

**结论**：交棒与超时回退都对，实测空闲计时 **30.0 s** 命中。

> 之前手动验证时这条一直"验不出来"，原因是**人手会顺手再连一次工具**——
> 那条 `10 02` 本身就是诊断请求，会把空闲计时重置。这也是把复位与等待
> 自动化的直接动机。

### 7.4 H3 无 meta（开发版兜底）/ H3' 量产拒绝坏镜像（均通过）

H3（`bootfault meta-blank` + 开发版 Boot）：

```
[boot] no valid meta, fallback to vector table probe
[boot] jump to slot A  base=0x020000  entry=0x020400
```

H3'（`bootfault meta-crc` + `--app=Boot --prod` 刷入量产 Boot）：

```
slot A : 0x020000  CONFIRMED  rc=2  size=244584  crc=63C75C3B  v2.8.0
[boot] dbg slot A: ... crc=9C38A3C4 expect=63C75C3B      ← 镜像好、meta 被改坏
[boot] slot A image rejected (production build)          ← 判据：不执行未验证镜像
[boot] slot A unusable, try slot B
[boot] vector fallback disabled (production build)       ← 量产不做向量表兜底
[boot] no valid image in slot A or B, waiting for flash
```

**结论**：量产构建在 CRC 不符时**不跳**，把该槽判死后试图换槽；无有效 meta 时
也不再看向量表，直接停在 UDS。与验证 1（开发版降级照跳）形成对照。

> `63C75C3B ^ 0xFFFFFFFF = 9C38A3C4` —— 与 `meta-crc` 的取反实现一致。

### 7.5 一个待修的元数据问题（25.x 候选）

UDS 刷写后 meta 的版本号变成 `v0.0.0`：

```
刷写前：slot A : ... CONFIRMED  rc=3  size=244584  crc=9C38A3C4  v2.8.0
刷写后：slot A : ... TESTING    rc=1  size=244584  crc=9C38A3C4  v0.0.0
```

原因：`0x37` 写 meta 时字段是 `memset` 后逐个赋值的，**没有版本字段**；而 App
的 self-register 只在 `imageSize/imageCrc` 不符时才触发 —— UDS 刷进去的镜像
两者本来就一致，所以永远不会补写版本。

影响：仅可追溯性（版本不参与任何启动决策）。修法二选一：`0x37` 从镜像里读版本，
或 App 每次启动顺带对账版本。**未实施。**

### 7.6 选槽耗时（已量，2026-11-17）

Boot 里**不能**用 DWT 自测（`DEMCR` 在 NVM 初始化后会被清成 0，计数器冻结），
所以耗时改在 App 侧用 CYCCNT 量，等价环境是"关中断"那一组：

| 项 | 245 KB 镜像耗时 |
|---|---|
| 整镜像 CRC（256 B 分段，Boot 选槽走的就是这条） | **81 ms** |
| 裸指针一次算（改造前的写法） | 76 ms |
| 修复 `CACHE_CTRL` 之前 | 267 ms |

也就是说：**选槽这一步约 81 ms，是 Boot 里最重的一段**。完整数据、
测量方法与那次 3.2 倍降速的事故记录见 `doc/整机执行速度与Flash缓存.md`。
复现命令：串口敲 `bootperf`（仅开发构建）。

### 7.7 仍未上板

| 用例 | 状态 |
|---|---|
| 选槽耗时 | 日志无时间戳，未测（要测需在 `dbg slot` 前后加 `Platform_NowMs()`） |
| 擦写中断电 | 属 M22 任务 4，SKIP（缺程控电源） |
