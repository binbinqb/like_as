# VSCode 环境使用手册（GCC + SCons + J-Link）

> 结论前置：本工程在 VSCode 里只需记住三个动作——`Ctrl+Shift+B` 编译、`F5` 调试（自动编译+下载）、任务面板跑 CSpyBat 烧写。全链路已于 2026-11-18 实测通过（编译→GDB Server→FLM 下载→复位运行→串口心跳确认）。

## 1. 环境清单

| 项 | 值 | 说明 |
|---|---|---|
| VSCode | 1.146.0 | — |
| 工具链 | `C:\soft\gcc\10.3.1`（arm-none-eabi 10.3.1） | gdb 也在其 `bin\` 下 |
| 构建入口 | `build.bat`（唯一入口，勿另造） | 内部 `python -m SCons --cpl=CM4GCC`，Python 固定 3.12 |
| 构建产物 | `build/nt/CM4GCC/<App>/<App>.exe` / `.map` / `.s19` | **`.exe` 实为 ELF**（魔数 `7F 45 4C 46`），GDB 直接加载，无需改名 |
| J-Link | V9（S/N 602717758），驱动 7.56 | 授权含 FlashDL / GDB |
| 器件包 | `C:\Program Files\SEGGER\JLink\Devices\CVA_BLUE_WHALE\CVM01xx\` | `CVM0146_PFLASH.FLM` / `DFLASH.FLM` / `JLinkScript` |
| SVD | `H:\chip-doc\MCU\曦华科技-水木蓝鲸CVM014x\CVA_MCU_SDK_M01xx+++CDS\...\utilities\SVD\CVM014x.svd` | 已写进 launch.json，调试时可看外设寄存器 |
| 索引引擎 | **clangd（独占）** | cpptools 已卸载；靠根目录 `compile_commands.json` + `.clangd`（query-driver） |

VSCode 扩展（本工程相关）：`cortex-debug` 全家桶（含 peripheral-viewer / memory-view / rtos-views / debug-tracker）、`clangd`、`hexeditor`、`gnu-mapfiles`、`python`。串口日志另装 `ms-vscode.vscode-serial-monitor`（可选）。

## 2. 工程内配置文件

| 文件 | 内容 |
|---|---|
| `.vscode/tasks.json` | `build App`（默认 Ctrl+Shift+B）/ `build Boot` / `build AppB` / `gen compdb` / `flash App (CSpyBat)` / `flash Boot (CSpyBat)` |
| `.vscode/launch.json` | `J-Link: Debug App`（编译+下载+停 main）/ `J-Link: Debug Boot` / `J-Link: Attach (no download)` |
| `.clangd` | query-driver 指向 10.3.1 gcc，解决 `stdint.h not found` |
| `compile_commands.json` | `tools/gen_compdb.py` 生成，clangd 全工程索引数据源 |

> ⚠ `tasks.json` 的 `$gcc` problem matcher 是 VSCode 内置的，不依赖 cpptools，卸载后红线报错不受影响。

## 3. 操作手册

### 3.1 编译
- `Ctrl+Shift+B` = 编译 App；编译 Boot/AppB：菜单 **Terminal → Run Task…** 选对应任务
- 报错在底部 **PROBLEMS** 面板，点条目跳源码

### 3.2 烧写（两条路，用途不同）
| 路 | 操作 | 用途 |
|---|---|---|
| A：CSpyBat | Run Task → `flash App (CSpyBat)` | **正式烧写/验收**，与 Bcm_Frame 台架同路径（`tools/flash.py`） |
| B：GDB 下载 | F5 调试时自动发生 | 只服务于调试会话 |

### 3.3 调试
1. 源码行号左侧点红点打断点
2. `F5`（或左侧 Run and Debug → 顶部下拉选配置）
3. 常用键：F10 跳过 / F11 进入 / F5 继续 / Shift+F5 停止
4. 面板：
   - Ctrl+Shift+P → `Peripheral`：CVM014x 外设寄存器树（SVD）
   - Ctrl+Shift+P → `memory`：内存视图（可看 BootMeta 区）
5. **调试结束后 CPU 可能停在断点**——按工具条「重启」或复位，否则板子是停着的

### 3.4 串口日志
Serial Monitor 扩展 → COM2 / 115200。**与 `boot_accept.py` 互斥**（抢 COM2）。

### 3.5 `gen compdb` 何时跑
改了生成器脚本 / DBC / SConstruct / 新增删除源文件 / 编译宏之后跑一次。日常改 `.c/.h` 不用。

### 3.6 日常流
```
改代码 → Ctrl+Shift+B → 有错就修
        → 单步调试：打断点按 F5
        → 上板验收：Run Task → flash App (CSpyBat) → boot_accept.py
```

## 4. 纪律（违反会污染验收结果）

| # | 纪律 | 原因 |
|---|---|---|
| 1 | **调试 Boot 前先想 BootMeta**：单步过 `BootMeta_CheckImage` / 回滚逻辑时 bootAttempts 计数真实发生 | 验收前用 `bootfault meta-blank` 或重刷 App 归位 |
| 2 | **调试会话与 `boot_accept.py` 不许同时开** | 都抢 J-Link 探针（串口与 JTAG 不冲突） |
| 3 | **GDB 烧写不进验收链路** | 它不写 BootMeta，与 A/B 槽对账是两套账 |
| 4 | **构建只走 `build.bat`** | SCons 依赖图（gen.stamp）以它为准，另起入口会绕过 02.8 门禁 |

## 5. 实测记录（2026-11-18）

| 步骤 | 命令 | 结果 |
|---|---|---|
| 编译 | `build.bat --app=App` | ✅ text 243,904 + data 1,712 |
| GDB Server | `JLinkGDBServerCL -device CVM0146 -port 2331` | ✅ 正常起服务 |
| 下载 | gdb `-batch` + `load` | ✅ 245,616 B 经 PFLASH.FLM 写 0x20000，~20 MB/s |
| 复位运行 | `monitor reset` + `monitor go` | ✅ |
| 运行确认 | COM2 抓包 | ✅ 心跳 `alive #47`（复位后 47 s，时间吻合） |

## 6. 故障排查

| 症状 | 原因 | 处置 |
|---|---|---|
| `Cannot connect to J-Link` | 探针没插 / 被别的进程占用 | 查占用：调试会话、boot_accept、JLink.exe 别同时开 |
| `Error while loading flash algo ELF file` | 器件包缺失 | 确认 `JLink\Devices\CVA_BLUE_WHALE\` 存在 |
| gdb 报 `Remote doesn't know how to detach` | GDB Server 不支持远程 detach | 无害，批处理里用 `quit` 收尾 |
| clangd 报 `stdint.h not found` | query-driver 失效 | 检查 `.clangd` 的 `Compiler:` 路径；或重跑 `gen compdb` |
| 跳转/补全滞后 | compdb 过期 | Run Task → `gen compdb` |
| 调试下载后板子不动 | CPU 停在断点 | 工具条「重启」或复位 |

## 7. 关联

- 启动验收矩阵：[[Boot启动判定矩阵]]
- Flash 缓存性能事故：[[整机执行速度与Flash缓存]]
- 烧写脚本：`tools/flash.py`（CSpyBat 路径）；验收：`tools/boot_accept.py`
