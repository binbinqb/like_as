# AS / CVM0146

按 [`as-master`](file://H:/优秀开源项目/as-master)（[autoas/as](https://github.com/autoas/as)）的
**工程组织方式**，把 AS 的 AUTOSAR BSW 移植到 CVM0146（Cortex-M4F，1 MB PFlash / 128 KB DFlash）。

> **用途：评估/学习原型。** AS 是 GPLv3 + 商业双许可；本目录只作技术验证，
> 不进入产品。若要产品化，需购买商业许可或按结构重写。

## 当前状态：M0 ~ M14 完成

| 里程碑 | 内容 | 状态 |
|---|---|---|
| **M0** | GCC 启动 + 时钟 + UART2 控制台 + SysTick 时基 + printf | ✅ 已上板，26 项验收 |
| **M1** | Port/Dio/Can AC + `Can_Cfg` → Kvaser 双通道收发 | ✅ 已上板，10 项验收 |
| **M2** | CanIf 接入 + 邮箱表外置 + 29 位扩展帧 + TX 确认 | ✅ 已上板 |
| **M2b** | **CAN1**（PTC6/PTC7 = `ALT3`，PTE13 = STB）+ PGN 掩码 + 控制面命令 | ✅ 已上板，`m2_check.py` **40 项全过** |
| **M3** | **PduR + CanTp + Dcm** 最小集（0x7E0/0x7E8） | ✅ 已上板，`m3_check.py` **17 项全过** |
| **M4** | **存储栈**：厂商 NvM+FEE 引擎 + AUTOSAR 外观，跑片内 DFlash | ✅ 已上板，`m4_check.py` **23 项全过**（含 GC 压测） |
| **M5** | **故障诊断**：CAN bus-off 检测 + 故障快照持久化到 DTC 块 | ✅ 已上板，`m5_check.py` **25 项全过** |
| **M6** | **诊断服务**：Dem + Dcm 0x19 读故障码 / 0x14 清故障码 | ✅ 已上板，`m6_check.py` **23 项全过** |
| **M7** | **写能力**：Dcm 0x2E 写 DID（VIN 落 NvM）+ 0x27 安全访问（恒通过） | ✅ 已上板，`m7_check.py` **16 项全过** |
| **M8** | **多扩展帧接收** + 软件定时器：CanNm / Com 的前置条件 | ✅ 已上板，`m8_check.py` **11 项全过** |
| **M9** | **网络管理**：CanNm + Nm + ComM 状态镜像（0x500，200 ms） | ✅ 已上板，`m9_check.py` **26 项全过** |
| **M10** | **信号层**：Com（0x200 发 / 0x201 收，100 ms），位打包/大小端/信号超时/分组启停 | ✅ 已上板，`m10_check.py` **22 项全过** |
| **M11** | **状态管理**：EcuM 三阶段初始化 + BSW 调度表 + ComM/CanSM 标准通信链路 | ✅ 已上板，`m11_check.py` **18 项全过** |
| **M12** | **睡眠/唤醒框架**：唤醒源识别 + EcuM 唤醒接口 + STOP 模式手动睡眠（`!z`） | ✅ 已上板，`m12_check.py` **15 项全过** |
| **M13** | **A/B 分区 UDS bootloader**：双镜像 + 槽尾 meta + 刷非活动槽 | ✅ 已上板，双向升级验过 |
| **M14** | **通信矩阵承载能力**：20 条构造报文 / 段掩码邮箱 / 硬件+软件双层过滤压测 | ✅ 已上板，`m14_check.py` 4 组全过 |
| **M15** | **ADC 模块**（as-master 无此模块，按三段式补）：ADC0+ADC1 双单元、多通道、PDB+TRGMUX 软触发 | ✅ 已上板，`!j` 三路读数稳定 |
| **M18** | **PWM 模块**（as-master 无此模块，按三段式补）：PwmLite 4 路输出、0%/100% 静态电平、同实例同频约束 | ✅ 已上板，**寄存器读数**验证 |
| **M19** | **CAN1 真实通信矩阵**：34 条 RX 按 PF 分组（7 个邮箱）+ 6 条 TX + 生成器注入 | ✅ 已上板，3400 帧 0 丢帧 |
| M16 | 端口唤醒（PTE4）+ DeepSleep/Standby + 电流实测 | 待做 |
| — | **IO 扩展链（I2C/TCA9539、RS2260 MUX）暂停**，等实际板子 | 待做 |

> **M2 的关键变化**：应用层不再看见 CAN ID，也不再看见通道号。`main.c` 只说"发 TxPdu 2"，
> 报文 ID / 邮箱号 / 扩展位 / 挂在哪一路，全在 `CanIf_Cfg.c` 与 `Can_Cfg.c` 两张表里。
> 改报文、把报文从 CAN0 挪到 CAN1，应用代码一行不用动。

### M2 验收（Kvaser ch0=CAN0, ch1=CAN1，两路 @500 kbps）

```bat
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools/m2_check.py
```

> 前置：Kvaser `ch0 → CAN0`、`ch1 → CAN1`，两路都要 500 kbps，
> **且两路都要接 120 Ω 终端电阻**（板上 `JP3/JP5` 给 CAN0、`JP6/JP9` 给 CAN1）。
> 少接终端电阻的症状是 ACK 错误、一帧都收不到，而软件侧看不出任何异常。

| 组 | 内容 |
|---|---|
| 横幅 | `bring-up (M2)`、`CAN0 + CAN1, 500 kbps` |
| CAN0 TX 标准帧 | 3 s 内 ≥4 帧 `0x123`、DLC=8、标准帧、8 字节逐帧递增 |
| CAN0 TX 扩展帧 | ≥2 帧 `0x18FF0002`、**29 位**、后 7 字节恒 `A5`、首字节递增 |
| CAN0 RX 标准帧 | 发 `0x321` → `[can] rx #n pdu=0 (CAN0 0x321) dlc=8 data=de ad ...` |
| CAN0 RX 扩展帧 | 发 `0x18FF0001` → `pdu=1 (CAN0 0x18FF0001(ext))` |
| CAN1 TX | ≥2 帧 `0x124`、DLC=8、后 7 字节恒 `C3`、首字节递增 |
| CAN1 RX | 发 `0x322` → `pdu=2 (CAN1 0x322)` |
| **RX 掩码（PGN）** | 发 `0x18FF01AB` → `pdu=3`（掩码 `0x1FFFFF00` 忽略源地址）；发 `0x18FF0200` → **不投递** |
| **未配置帧** | 发 `0x7FF` → 不投递，且板子不崩 |
| **短帧** | 发 DLC=4 → 打印 `dlc=4` + 4 字节 |
| **控制面** | `!o`/`!n` 切 PDU 模式、`!s`/`!g` 切控制器模式、`!t`/`!r` 切收发器模式；每步都回读状态并验证总线上有无 `0x123` |
| TX 确认 | 心跳行 `txok` 递增（两路的邮箱中断都在调 `CanIf_TxConfirmation()`） |
| 心跳 | ≥2 条（证明 CanIf 初始化没卡住主循环） |

实测：**40 项，通过 40，失败 0**。M0 回归仍 26 项全过（`!` 命令不破坏回显）。

> `txok` 这一项是最容易悄悄断的：中断里漏处理 TX 分支，发送**照样成功**，
> 但 confirmation 永远不来 —— 接 CanTp 后表现为"分段发送永久卡在第一帧"。
>
> ⚠ **`txok` 只有在总线上有另一个节点 ACK 时才会增长**。只插 J-Link 不接 Kvaser
> （或 Kvaser 没开）时，控制器会因 ACK 错误无限重发，`txok` 一直是 0 ——
> 这是正常现象，不是固件问题。

### 两层 CAN 过滤：硬件在 CanIf 之前（实测踩过）

M2 加"一条过滤项匹配一组报文"时踩了一次，值得记下来：

```
0x18FF01AB ──▶ 硬件邮箱过滤 ──▶ CanIf 软件掩码 ──▶ 应用
              individualMask     rxPdu.canid/mask
              不匹配就**根本不进 CPU**，中断都不置
```

第一次只改了 `CanIf_Cfg.c` 的掩码，硬件邮箱还是 `0x322` 全掩码 ——
结果 `0x18FF01AB` 压根没到 CPU，CanIf 的掩码再正确也没机会执行，
测试报 `pdu=3 未命中`。**修法是两层同时放行，且硬件掩码要比软件宽**：

| 层 | 配置 | 作用 |
|---|---|---|
| 硬件（`Can_Cfg.c`） | `canid=0x18FF0000` + `individualMask=0x1FFF0000` | 把整个 `0x18FFxxxx` 段收进来 |
| 软件（`CanIf_Cfg.c`） | `canid=0x18FF0100` + `mask=0x1FFFFF00` | 再按 PGN 精确到 `0x18FF01xx`，忽略源地址 |

硬件若和软件一样窄，软件过滤既测不到、也不生效。
`individualMask` 语义：**1 = 必须匹配，0 = 不关心**（FlexCAN 标准）。

> 另有一个静默陷阱：CanIf 表里的 `canid` 必须**本身就在掩码范围内**
> （`canid & mask == canid`）。写 `canid=0x18FF0100` 却配 `mask=0x1FFF0000`，
> 等式 `0x18FF0000 != 0x18FF0100` 永不成立，症状只是"这条报文收不到"，不报任何错。

### 引脚与 MUX 的出处（别猜）

| 信号 | 引脚 | MUX | 出处 |
|---|---|---|---|
| CAN0_RX / TX | PTE4 / PTE5 | `ALT5` | 已由 M1 上板验证 |
| CAN0_STB | PTC1 | `ALT1`（GPIO） | 开发板手册表 8，1=STANDBY / 0=ACTIVE |
| **CAN1_RX / TX** | **PTC6 / PTC7** | **`ALT3`** | 开发板手册表 8 + PinMux 表 `cvm0146` |
| **CAN1_STB** | **PTE13** | `ALT1`（GPIO） | 同上 |

PinMux 表的用法：手册第 4 章说明引脚复用见附件 `CVM014x_PinMux_V2.5.xlsx`。
列顺序是 `DEFAULT / ALT0 / ALT1 / ALT2 / ALT3 / ALT4 / ALT5 / ALT6 / ALT7`，
其中 **ALT1 恒为 GPIO**（`PINSDRV_MUX_AS_GPIO = 1`），可与驱动枚举对齐校验。

> 这张表用 PTE4 校准过：它的 `CAN0_RX` 落在 ALT5，与 M1 实测一致，
> 由此确认列偏移没读错 —— 否则 PTC6/PTC7 会被误判成别的 ALT。

### M4 验收（存储栈，纯串口，不需要 Kvaser）

```bat
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools/m4_check.py
```

| 组 | 内容 |
|---|---|
| 横幅 | `nvm   : DFlash 2x12 KB, 4 blocks, boot #N (init x ms, read y ms)` |
| 块表 | `!d` 四个块，长度 8 / 32 / 17 / 64 |
| 掉电保持 | 连复位两次，启动计数每次 +1（`boot #5 → #6 → #7`） |
| ROM 默认值 | `VIN` 未写过 → 读到 `CVM0146M4NVM00001` |
| 延迟落盘 | `!w` 改 RAM → 标脏 → `WriteAll` → 复位后 `CONFIG[1]` 仍在 |
| DET | `!x` 非法块 id → `[det] mod=20 api=0x0b err=0x0a` |
| **GC** | `!p` 连写 400 次（≈22 KB，写满 12 KB 扇区 1~2 次），<10 s，复位后数据不丢 |
| 主循环 | 心跳照常（存储没把 loop 卡死） |

> **GC 这一项必须单列。** FEE 是日志式存储，平时只往活动扇区尾部追加；
> 写满后要走"搬备份扇区 → 擦活动扇区 → 翻活动扇区"这条路径，正常使用中
> 几天都走不到一次。它的错误表现是"跑几周之后数据全没"。
> 本工程就是在这条路径上抓到一个真实缺陷，见下。

### M4 落地的四个坑

| # | 现象 | 根因 |
|---|---|---|
| 1 | 存储整块哑掉，`NvM_GetStatus()` 返回 `MEMIF_UNINIT`，前 200 多次写却全部正常 | **`Fee_Cache` 开小了**。厂商 demo 用 64 字节，但 GC 搬块会用它放**一整块**数据（`fee.c:776/799`），DTC 块 72 字节越界 8 字节，正好冲掉紧邻的 `NvM_Initialized` |
| 2 | `NvM_ReadAll()` 永久超时；`fee=IDLE`、`jr=PENDING`、块=PENDING，三个"正常值"凑成死锁 | **`Fee_Runtime.job` 指向了 `Fee_SysJob`**。`Fee_GetUserJob()` 会把用户作业整个拷进 `runtime->job`，于是把 READ 操作码写进了系统作业槽，`Fee_GetSysJob()` 从此永远为真、又因为 op≠GC 什么都不做，用户作业再也取不到 |
| 3 | 初始化卡 5 s 以上 | `FlashDrv_Read1sSection()` 每次是一条 **FTFC 命令**（内部读整 1 KB）。按 8 字节 phrase 逐片调用把 1 条命令拆成 128 条，24 KB 扫描变成三千多条命令 |
| 4 | 配了 `immediate=false` 的块"写完就没了" | 厂商引擎的 `immediate=false` **只写 RAM**，与 AUTOSAR 的 `NvM_WriteBlock` 语义冲突 |

> 前两个都是"不报任何错、只表现为不工作"的类型，靠读代码看不出来，
> 是靠 `!p` 连写 400 次 + 超时现场快照（`memif/fee/nvm/rjob/jr/jobs/w` 六个值）
> 才定位到的。这也是为什么验收脚本必须包含 GC 压测。

### M4 的架构选择：厂商引擎 + AUTOSAR 外观

```
应用 / Dcm / Dem        只认 NvM_BlockIdType（0..3）
        │
   NvM_*()              ← 本工程写，AUTOSAR 标准接口（infras/memory/NvM/NvM.c）
        │
   NvM_Port*()          ← 本工程写，零厂商类型 / 零 AUTOSAR 类型（NvM_Port.h）
        │
   Nvm_* / Fee_*        ← 厂商原样（infras/memory/vendor），一行未改
        │
   FeeAc_FlsMethod      ← 5 个函数指针，落到 CVM0146 的 DFlash
```

**为什么中间必须隔一层 `NvM_Port`：** AUTOSAR 的 `NvM.h` 与厂商的 `nvm_types.h`
都定义了 `NVM_REQ_*`（前者是宏，后者是枚举成员）。同一个 `.c` 同时 include 会出事：
先 include AUTOSAR 则宏污染枚举定义、编译不过；先 include 厂商则宏把后续所有
`NVM_REQ_OK` 展开成 0，**不报错但比较永远错**。所以边界上放一层"两边类型都不出现"
的接口，参数只有 `uint16_t` / `uint8_t` / `bool`。

**依赖取舍**（as-master 那套 storage 需要 4 个额外依赖，本工程只要 1 个）：

| 依赖 | 要不要 | 理由 |
|---|---|---|
| `Det` | **要** | AUTOSAR 要求参数错误有落点。加了 30 行实现后，`NvM_ReadBlock(非法id)` 能从"只返回 E_NOT_OK"变成 `[det] mod=20 api=0x0b err=0x0a` |
| `sys/queue.h` | 不要 | 只用 as-master 的 NvM 才需要 STAILQ；厂商引擎自带数组队列 |
| `Crc` | 不要 | 厂商 NvM/FEE 自带 CRC8 表，且**必须同源**（见 `FeeAc_CalcCrc8` 注释）。as-master 的 NvM 配 `NVM_CRC8` 其实不校验（只支持 CRC16），引它反而丢完整性保护 |
| `MemIf` | 不要实现 | 只有 DFlash 一个存储设备，多设备分发没意义。`MemIf.h` 只提供 `MemIf_StatusType` 这个类型，不需要 `.c` |

**为 0x27 / Dem 留的路已经通了**（`m4_check.py` 里有对应用例）：

- `NvM_WriteBlock(id, NULL)` = "写该块自己的 RAM 映像"，Dcm 的
  `NvM_WriteBlock(SecurityNvMBlkId, NULL)` 就是这种用法；
- `NvM_GetBlockDataPtrAndLength(id, &p, &len)` 让 Dem 直接改 RAM 再统一落盘，少一次拷贝；
- 脏块掩码 + `NvM_SetRamBlockStatus` + `NvM_WriteAll` 实现"批量落盘只写改过的块"
  （厂商引擎的 `WriteAll` 是**全写**，会白白磨损扇区）。

真开 0x27 时要做的事只有三件：加一个 `NVM_CFG_ID_SECURITY` 块、
把 `Dcm_NvmSecurityAccess_Ram` 指向该块的 RAM 映像、填 `Dcm_Cfg` 的 `SecurityNvMBlkId`。

### M5 验收（故障诊断，纯串口，不需要 Kvaser）

```bat
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools\m5_check.py
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools\m5_check.py --with-can
```

| 组 | 内容 |
|---|---|
| 检测就绪 | `!e` 读回 `BOFFMSK=1`、`ERRMSK=0`（bus-off 中断开、错误中断不开） |
| 故障注入 | `!i` → `!b` 出现 `C00100 ch=0 cnt=1 err=0x04 flt=2` |
| 累加 | 再注入一次，同一条记录 `cnt=2`，**不占新槽位** |
| 掉电保持 | 复位后记录仍在，`cnt` 与 `firstBoot` 都不变 |
| 清除 | `!B` → 空；再复位仍为空（清除也落盘） |
| 不破坏原有功能 | 心跳照走、`0x123` 照发（`--with-can` 用 Kvaser 验） |

### M5 的三个硬事实

**① 单节点实验室造不出 bus-off，这是协议决定的**

直觉上"对端不应答"应该能触发 bus-off，实测不行：

| 尝试 | 结果 |
|---|---|
| 断开 Kvaser（无节点应答），跑 60 s | `TEC` 涨到 **128** 后一动不动 |
| Kvaser 250 kbps 错速（有终端、不解码） | `TEC=136`，`REC=7`，仍不 bus-off |
| Kvaser 连发 **16939 帧**同 ID 不同数据去撞 | `TEC` 只到 **1~7** |

原因写在 ISO 11898-1 §7.1.3：**error passive 状态（TEC≥128）下，ACK 错误不再累加 TEC**。
这是协议防止"孤立节点把自己锁死"的设计。想越过 128 只能靠位错误/格式错误，
需要两个节点精确同步发送 —— 实验室做不到。

所以本工程分两层验：
- **硬件触发条件**用 `!e` 验（`BOFFMSK=1` + `ERRMSK=0`）；
- **记录链路**用 `!i` 故障注入验（分配槽位、累加、落盘、掉电保持全是本工程的代码）。

> 真要做物理 bus-off，把 CAN_H 对地短接几秒（持续显性位 → 位错误）。
> 需要动硬件，不适合进自动脚本。

**② `SetControllerMode(STOPPED → STARTED)` 会弄死控制器 —— 所以恢复不靠它**

这是本次最意外的发现。原本按 README 早先的计划做"bus-off 兜底重启"，
实测重启之后控制器**不再发送任何帧**：

| 读数 | 重启前 | 重启后 |
|---|---|---|
| `ESR1.IDLE` | 0 | **1**（总线空闲得可疑） |
| `TEC/REC` | 128 / 0 | 0 / 0 |
| `CanIf_Transmit()` | `E_OK` | 仍然 `E_OK` |
| Kvaser 收到帧数 | 8 帧 / 2 s | **0 帧 / 3 s** |
| `obj->waitFailed` | 0 | 0（**不是超时退出**） |

也就是说：一次 bus-off 触发软件重启，会把"本来能自己好的控制器"变成"永久哑掉"。
**这比不恢复严重得多**，所以最终实现里去掉这条路径。

FlexCAN 的 `CTRL1.BOFFREC = 0`（厂商 `SetBusOffRecEnable(true)` 写的正是 0 ——
注意 FlexCAN 里 **0 才是自动恢复使能**，1 是禁止）保证硬件在 128×11 个隐性位后
自己回到 error-active，软件不需要介入。真要做硬恢复，可靠手段是整机
`NVIC_SystemReset()`（EcuM 级），而不是运行期重新 Configure 外设 —— 留给 M6。

**③ SDK 又两个"漏初始化"的字段**

`FlexCanDrv_GetDefaultCfg()` 没有初始化 `warningIntEnable` 和 `selected3bitSampling`。
前者关系到 `CANx_ORed` 中断（三个源的或），不显式写 false 就会拿到栈垃圾，
一旦 NVIC 打开就是不可预期的中断风暴；后者决定 `CTRL1.SMP`（单点/三点采样），
两次 Configure 会得到不同值（实测 `0x052CA087` → `0x052CA00F`）。
本工程在 `CanAc_Init()` 里把 `warningIntEnable` 显式补成 `false`。

### M6 验收（0x19 / 0x14，需要 Kvaser）

```bat
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools\m6_check.py
```

| 组 | 内容 |
|---|---|
| 空表 | `19 02 FF` → `59 02 8F`；`19 01 FF` → `59 01 8F 01 00 00`；`19 0A` → `59 0A 8F` |
| 注入后 | `19 02 FF` → `59 02 8F C0 01 00 8F`（U0001 / 状态 0x8F） |
| 状态过滤 | `19 02 01`（查 TF）读得到；`19 02 10`（查 TNCSLC）读不到 |
| 清除 | `14 FF FF FF` → `54`（中间有 NRC 0x78） |
| 一致性 | 串口 `!b` 条数 == `19 01` 数量（同一个 Dem 后端） |
| 掉电保持 | 复位后 `19 02 FF` 仍读到 |
| 回归 | `10 03` / `22 F1 90`（多帧）/ `3E 00` 全部正常 |

### M6 的三个设计决定

**① 没有引入 as-master 那 2070 行 Dem，而是写了一个 Dem API 子集**

as-master 的 `Dem.c` 是完整实现（去抖 / 老化 / 冻结帧），但它**不提供 `Dem_Cfg.c`**
—— 那份配置要使用者自己写，涉及事件表、DTC 表、内存目的地、去抖参数、
每个事件一个 NvM 块 id。本工程只有一个故障源，配出来的表 90% 是空转。

代价对比：

| | 完整 Dem | 本实现 |
|---|---|---|
| 代码量 | 2070 行 + 几百行配置 | 约 480 行（含注释） |
| 新增 NvM 块 | 每个事件一个 | 复用 M5 的 DTC 块 |
| 去抖 / 老化 | ✅ | ❌ |
| 0x19 的 0x01/0x02/0x0A | ✅ | ✅ |
| 0x19 的快照 / 扩展数据 | ✅ | ❌ |
| 接口 | AUTOSAR | **完全一致** |

关键在于最后一行：`Dcm_Dsp.c` 里那 400 行现成的 0x19/0x14 **一行没改**就能驱动它。
将来要升级，替换 `infras/diagnostic/Dem/Dem.c` 即可，调用方不动。

**② M5 的 `fault_log` 下沉成了 Dem，不是并排放着**

M5 时故障表放在 `app/app/src/fault_log.c`。接 Dcm 时发现分层错了：
`infras` 的 Dem 不能反过来依赖 `app` 的模块。

所以整体下沉到 `infras/diagnostic/Dem/Dem.c`，接口换成 `Dem_SetEventStatus()`。
好处不只是"分层干净"—— 应用现在只认 `Dem_CFG_EVENT_*` 事件号，
**不知道 DTC 码、不知道表在哪、不知道有几个槽**。换存储布局应用不用改。

**③ 0x14 会先回 NRC 0x78，脚本必须处理**

`Dcm_DspClearDTC` 在 `USE_NVM` 下返回 `DCM_E_RESPONSE_PENDING`，
要等 NvM 把 DTC 块写完才给最终 `54`。测试脚本不吞掉 `7F 14 78` 的话，
下一条命令会读到上一条的尾巴 —— 现象是"命令串位"，比不响应还难查。

为此把 M3 里手写的 ISO-TP 抽成了 `tools/isotp_lite.py`（M3 / M6 共用），
并在 `request()` 里内置 pending 处理。

### M8 验收（多扩展帧接收，需要 Kvaser）

```bat
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools\m8_check.py
```

| 组 | 内容 |
|---|---|
| 多邮箱并行 | 4 个不同 PGN 的 29 位帧 → 分别落 PDU 6/7/8/9 |
| 掩码分组 | 同 PGN（0xFF01）两个源地址（0x00 / 0xAB）→ 都进 PDU 5 |
| 负例过滤 | `0x18FF0200` 收不到（证明是真过滤，不是全放行） |
| 标准帧回归 | `0x321` 仍走 PDU 0 |
| 诊断回归 | `10 03` 仍正常（新邮箱没抢诊断邮箱） |

### M8 的核心结论：那个"RX 不支持扩展帧"的阻塞根本不存在

之前记过一条结论：「Foton 的 49 条报文都是 29 位扩展帧，而 RX mailbox 只支持标准帧」，
把它列成了 CanNm / Com / J1939Tp 的前置硬阻塞。**这次实测推翻了**：

| 怀疑点 | 实测 |
|---|---|
| IDE 位没置 | `FlexCanDrv_SetMsgId()`（`flexcan_drv.c:164`）对 `isExt` 分支**正确**置了 `CS.IDE \| CS.SRR` |
| 29 位 ID 被截断 | `MESSAGE_BUFFER_ID_EXT_ID_MASK = 0x1FFFFFFF`、shift = 0，写的是完整 29 位 |
| 邮箱数量不够 | `canRamNum=3` × 512 B ÷ 16 = **96 个**（CAN0），CAN1 是 64 个 |

M2 时其实就验过一条扩展帧（`0x18FF0001`），只是没人往"多条并行"这个方向再推一步。
本次加 5 个邮箱后 6 条全通，说明能力一直在，**是判断错了，不是芯片不行**。

### M8 踩的坑：加报文把表序搞乱了

加 4 个 J1939 报文时，我把 `0x18FF0001` 留在原位（排在 `0x18FExxxx` **之前**），
结果 **它自己**收不到了，而新加的四条全正常 —— 看起来像"老功能被新配置破坏"。

根因是 `CanIf_RxDispatch()`（`CanIf.c:104`）用**二分查找**：

```c
m = l + ((h - l) >> 1);
if (var->canid == (canid & var->mask))  rxPdu = var;      /* 命中 */
else if (var->canid > canid)            h = m - 1u;
else                                    l = m + 1u;
```

乱序时 `var->canid > canid` 这个判断会把本该搜索的那一半砍掉。**它不报错、不告警，
只是某条报文静默消失。**

两条硬约束：

1. **全表按 `canid` 严格升序**；
2. **掩码项必须排在所有精确项之后** —— 掩码项代表一个 ID 区间，
   夹在中间会让二分的区间收缩方向判错。

为此加了 `CanIfCfg_CheckRxOrder()`：初始化时遍历两张表验一遍，
不通过就在串口打 `[warn] CanIf RX 过滤表顺序非法`。
**只告警不阻断** —— 报文收不到已经够烦，不该连诊断都进不去。

### M8 附带的：软件定时器（CanNm 的前置）

as-master 的 `system/timer/std_timer.c` 是 **PC 实现**（`timeGetTime()` / `gettimeofday()`），
MCU 上编译不过。拆成两层：

```
infras/system/timer/std_timer.c    定时器逻辑（含溢出处理），原样保留
        ↓ 调用 Std_GetTime()
app/platform/cvm0146/src/StdTimerAc.c    SysTick 毫秒 → 微秒
```

**溢出处理必须保留**：`std_time_t` 是 32 位微秒，**71.6 分钟回绕一次**。
直接 `if (now >= deadline)` 会在回绕那一下得到巨大误判，
表现为"定时器要么立刻超时、要么永不超时"。AS 用 `NO_OVERFLOW` / `OVERFLOW`
两种状态区分，这段逻辑一行没改。

启动时加了一个 50 ms 自检（`TimerSelfTest()`），验的是**时间源**而不是逻辑：

```
  timer : 50 ms 超时 -> 实测 50 ms (ok)
```

时基要是搞错（单位 ms 当 us、或返回 0），CanNm 会疯狂发 NM 报文、永远不睡，
而现象只在 CAN 上表现为"报文太密"，很难反推到时基。

### M7 验收（0x27 / 0x2E，需要 Kvaser）

```bat
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools\m7_check.py
```

| 组 | 内容 |
|---|---|
| 0x27 会话限制 | 默认会话 `27 01` → NRC 0x7E；`10 03` 后可请求 |
| 0x27 握手 | `27 01` → `67 01 11 22 33 44`；`27 02` + **任意** key → `67 02` |
| 0x27 已解锁 | 再请求种子 → `67 01 00 00 00 00`（ISO 14229：无需再发 key） |
| 解锁不影响他服务 | `22` / `19` 在解锁前后都可用 |
| 0x2E 写入 | `2E F1 90` + 17 字节 → `6E F1 90`，写完立刻读得到 |
| 0x2E 拒绝 | 长度错 → 0x13；零件号 → 0x31；不存在的 DID → 0x31 |
| 收尾 | VIN 写回出厂默认，避免污染 M3 的断言 |

### M7 的三个坑

**① `securityMask` 是"允许的等级集合"，不是"最低要求"**

最初填 `0x01`（以为"1 = 只允许未解锁"，等价于不限制）。结果：

```
27 01 → 67 01 11 22 33 44     (种子正常)
27 02 → 67 02                 (解锁成功)
22 F1 90 → 7F 22 33           (!!! 所有服务全被拒)
```

因为 `Dcm_Dsl.c:135` 是**按位与命中**判断的：

```c
if (0u != (sesSecAccess->securityMask & (1u << context->currentLevel))) r = E_OK;
else *nrc = DCM_E_SECUTITY_ACCESS_DENIED;      /* 0x33 */
```

解锁后 `currentLevel = 1`，`0x01 & 0x02 = 0` → 被拒。正确值是 **`0x03`（bit0 LOCKED | bit1 L1）**。
将来真要"必须解锁才能写 VIN"，把那一项改成 `0x02` 即可 —— 那时 locked 下拿到 0x33 正是想要的。

**② VIN 有两个数据源，0x2E 一做就露馅**

原来 `Dcm_Cfg.c` 里有个 `static const uint8_t Dcm_Vin[17] = "CVM0146M3TEST0001"`，
而 NvM 里还有一个 VIN 块（默认 `CVM0146M4NVM00001`）。两份数据不一致：

- 0x2E 只能写进一个 RAM 副本，掉电就没；
- 0x22 读的是常量，写多少都读不到新值；
- 最糟的是"看代码"和"看 `!d`"各自都显示正常。

现在 VIN 只有**一个数据源**：NvM 的 VIN 块。0x22 读它、0x2E 写它。

**连带影响**：M3 验收的 VIN 断言从 `CVM0146M3TEST0001` 改成 `CVM0146M4NVM00001`；
M3 里那条"用 0x2E 造长请求"的用例改成写 F187（不可写），
否则每跑一次回归就把 VIN 写成 17 个 X —— 这个坑实际踩到了，改完才恢复。

**③ NvM 对同一块的重复写会丢弃，但 `NvM_WriteBlock()` 仍返回成功**

这是最隐蔽的一个。连续两次 `2E F1 90` 且间隔很短时：

```
2E F1 90 + "AAAA..."  → 6E F1 90    读回 AAAA...   ✅
2E F1 90 + "BBBB..."  → 6E F1 90    读回 AAAA...   ❌
```

响应是正响应、`NvM_WriteBlock()` 返回 `E_OK`（请求入队成功），但厂商引擎对
**同一块**的重复写请求在作业未完成时会丢弃它。

修法：`Dcm_WriteVin()` 里先查 `NvM_GetStatus() != MEMIF_IDLE`，
忙就返回 `conditionsNotCorrect`(0x22) —— **如实报错，不假装成功**。
测试仪收到 0x22 会重试（真车诊断仪对 DID 写入本来就要重试）。

同时 `isotp_lite.py` 加了 `flush_rx()`：连续请求之间清掉残留响应帧，
否则会读到上一条的尾巴（"命令串位"）。

### M9 验收（网络管理，需要 Kvaser）

```bat
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools\m9_check.py
```

| 组 | 内容 |
|---|---|
| 初始状态 | `!m` → `comm=NO_COM_NO_PENDING cannm=BUS_SLEEP mode=BUS_SLEEP`，总线上无 0x500 |
| 主动请求 | `!a` → `REPEAT_MESSAGE` → 800 ms 后 `NORMAL_OPERATION` |
| 周期 | 平均 **200 ms**，抖动 `min=199 max=201`（9 个间隔） |
| 报文格式 | 标准帧 8 字节，`byte0=0x42`(NID)，`byte1` 在 RepeatMessage 期是 **0x11**、NormalOperation 期是 **0x10** |
| 释放即停发 | `!R` 后 1 s 内 **0 帧**，状态落 `READY_SLEEP` |
| 睡眠序列 | `READY_SLEEP` → 2.6 s → `PREPARE_BUS_SLEEP` → 2.0 s → `BUS_SLEEP` |
| **被别的节点留住** | ReadSleep 期间对端每 200 ms 发 NM，本节点**不睡**；对端停发后才进 PREPARE |
| 被动启动 | `!A` 从 `BUS_SLEEP` 拉起，CBV=**0x00**（不冒充"我叫醒的"），800 ms 后自动回 `READY_SLEEP` |
| 不破坏原有功能 | 心跳 0x123 照发、`10 03` 仍正常 |

### M9 的三层结构与"可被唤醒"到底做到哪一步

```
应用（main.c）        只调 Nm_NetworkRequest / Release / PassiveStartUp
      │
   Nm（208 行）        按 busType 分发到 CanNm
      │
  ComM（128 行，桩）   状态镜像 + 弱符号日志 → 串口
      │
  CanNm（1183 行）     状态机 / 定时器 / CBV 维护
      │
  CanIf → 邮箱 11(TX) / 12(RX)，0x500
```

| 唤醒源 | 状态 |
|---|---|
| 本节点应用请求（`!a`） | ✅ 已通 |
| 总线上别的节点在发（`NmTimeout` 不断被重启） | ✅ 已通 |
| 收发器检测总线活动 → EcuM → `Nm_PassiveStartUp` | ⚠️ **手动验通（`!A`）**，EcuM 未接 |
| 真正把 MCU 从低功耗模式叫醒 | ❌ 属 EcuM + 平台低功耗，M10 |

**所以这一版不能说"整车能唤醒 BCM"**，只能说 NM 侧链路是通的。
最后一行不是 CanNm 的职责 —— CanNm 在 `BUS_SLEEP` 只响应
`CANNM_PASSIVE_STARTUP_REQUEST_MASK`，而置这一位的正是 EcuM。

### M9 踩的四个坑

**① `Nm.c` 里 ComM 通知由 `#ifdef USE_COMM` 包着，不是 `USE_NM`**

这四处（`Nm.c:139/149/159/169`）控制 `ComM_Nm_*` 是否被调用。只定义 `USE_NM`
的后果是：NM 状态机照跑、报文照发，但 `!m` 永远显示 `comm=NO_COM` ——
排查时极易误判成"ComM 没工作"。

`USE_COMM` 这个名字容易被读成"有 Com 信号层"，但全仓只有这 4 处用它，
所以定义它是安全的（已在 `Nm/SConscript` 里注明）。

**② CanNm ↔ Nm 是双向引用，不能用库依赖排序**

`CanNm` 调 `Nm_*` 上报，`Nm` 调 `CanNm_*` 分发。本工程链接命令**不带
`--start-group`**，静态库单次扫描无论怎么排都会有一边解析不到。

做法与 as-master 一致：两个库都不声明对方为 `LIBS`，都进最终链接行，
靠链接器全局符号解析。`Nm` → `ComM` 是单向，正常声明。

**③ PduR 的 `PduHandleId` 必须填 0，不是 CanIf 的 PDU 号**

`CanNm_RxIndication(RxPduId, ...)` 和 `CanNm_TxConfirmation(TxPduId, ...)`
把第一个参数当**通道下标**用（`CanNm.c:810/851`：`&ChannelContexts[RxPduId]`）。
而 PduR 会把 `DestPduRef->PduHandleId` / `SrcPduRef->PduHandleId` 原样传下去。
C 语言看不出这个错配，填 10 就是越界读 —— 已在 `PduR_Cfg.h` 里标 `@warning`。

**④ 验收脚本的计时基线比固件更容易错**

首发 24/26，两个失败**全是脚本问题**：

| 现象 | 真因 |
|---|---|
| "REPEAT_MESSAGE 请求位没置" | 捕获窗口跨过了 800 ms 边界，混进了 NormalOperation 的帧（CBV=0x10）。固件是对的 |
| "PREPARE 耗时 1.3 s，不是 2 s" | 计时起点取在"打完 note 之后"，而 `nm_state()` 一次串口往返 ~0.2 s，上面两条 note 把起点推后了 0.9 s |

修法：**先抓帧、再查状态**；计时从"最后一帧对端报文"算起。
凡是"抓一段时间的总线"与"读一次串口状态"混在一条用例里，就必须先想清楚
哪个动作有延迟、哪个动作是瞬时。

### M10 验收（信号层，需要 Kvaser）

```bat
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools\m10_check.py
```

| 组 | 内容 |
|---|---|
| 周期 | 0x200 每 **100 ms** 一帧（平均 100.1 ms，抖动 99~101） |
| 字节对齐打包 | `byte0`（TX_COUNTER）每帧 **+1**（模 256） |
| **非字节对齐单 bit** | `TX_FLAG` 起始位 9 → `byte1` 恒为 **0x02** |
| **跨字节不占满** | `TX_LEVEL=0xABC`、12 位 → `byte2=0xBC`、`byte3=0x0A`（高 4 位必须为 0） |
| 未用字节 | `byte4~7` 恒 0 |
| 接收解包 | 注入 0x201 → `!v` 读到的 cnt/temp 与注入值一致 |
| **Motorola 大端** | `byte2=0x01 byte3=0x23` → **291**（不是 0x2301） |
| **信号超时** | 对端停发 1 s 后 `RX_COUNTER`→**0xEE**、`RX_TEMP`→**0**（0.9 s 触发） |
| 分组启停 | `!y` 停 → **0 帧**；再 `!y` → 恢复 10 帧/秒 |
| 不破坏原有功能 | 心跳 0x123、NM 0x500、诊断 `10 03` 都正常 |

### M10 刻意没做的一件事：不接业务信号

**灯光 / 门锁 / 雨刮的位布局来自整车通信矩阵，现在没有。** 硬编一套假布局，
将来矩阵一到全部要改，而且改的时候没人知道哪些是"当时编的"。

所以这一版只验证 Com 的**机制**，用三个边界信号把最容易错的地方钉死：

| 信号 | 起始位 | 宽度 | 它专门验什么 |
|---|---|---|---|
| `TX_COUNTER` | 0 | 8 | 字节对齐的基本打包 |
| `TX_FLAG` | **9** | **1** | 非字节对齐的单 bit（落 byte1 的 bit1） |
| `TX_LEVEL` | 16 | **12** | 跨字节但**不占满**（byte2 全部 + byte3 低 4 位） |

接真实信号时**只改 `Com_Cfg.c` 这张表**：加条目、指到对应字节偏移、
填 `BitPosition`/`BitSize`。`Com.c` 一行不动，应用层用的是
`Com_SendSignal(COM_SIG_xxx)`，信号号从配置头来。

### M10 的三个坑

**① 大端信号的 `BitPosition` 是 7，不是 0**

实测：填 0 时总线上 `01 23` 读回来是 **0x9180** —— 正好左移 7 位；
`0xFFFF` 读回来是 `0xFF80`，同一个位移规律。

根因在 `Std_BitGetBigEndian()`（`std_bit.c:33`）：

```c
uint16_t lsbIndex = ((bitPos ^ 0x7u) + bitSize - 1u) ^ 7u;
uint8_t bitsRead  = (8 * nBytes) - (7u - (bitPos & 0x07u));
```

它把 `bitPos` 当作**从字节 LSB 数起的位序号**，而大端信号的起点是
"该字节的最高位"，序号是 **7**。所以大端信号要用
`BitPosition = 7 - (起始位在字节内的偏移)`；小端不受影响，仍是 `起始位 & 7`。

**这个错误不报任何警**，读出来的值还落在合法范围内（温度 25 ℃ 会变成 8961 ℃）。

**② TX/RX 不能共用一个 ID**

最初图省事让 0x200 既发又收，结果**接收测试没法做**：板子每 100 ms 也在发
0x200，Kvaser 一注入就撞车（同 ID 同优先级），抓到的帧内容互相污染、
错误计数上涨。拆成 0x200 发 / 0x201 收之后才对。

真实总线里一个 ID 只有一个发送者 —— 同 ID 本来就不该出现在量产设计里。

**③ M10 的周期流量暴露了一个潜伏很久的 SDK 缺陷**

接上 Com 之后，M2 的"停止/启动控制器"用例开始失败：

```
!s (STOPPED)  → 0x123 = 0,  0x200 = 0     ✅ 符合预期
!g (STARTED)  → 0x123 = 0,  0x200 = 0     ❌ 控制器永久静默
```

而**把 Com 分组停掉**（`!y`）再走同样的 `!s → !g`，就能正常恢复。
也就是说：**控制器停止期间只要有一次 `Can_Write`，它就再也起不来了。**

寄存器对比定位到根因：

| | CTRL1 |
|---|---|
| 第一次 Configure | `0x052CA007` |
| 第二次 Configure | `0x052CA00F` ← **bit3(SMP) 翻转** |

`SMP = 3 点采样`，而位时序是按 1 点采样算的，采样点偏移到收不到 ACK，
`TEC` 一直是 0、`ESR1.IDLE` 置位，报文一帧都出不去，**所有 API 却都返回成功**。

源头是 `FlexCanDrv_GetDefaultCfg()`（`flexcan_drv.c:389`）**漏了
`selected3bitSampling` 字段**，`cfg` 是栈变量，第二次调用拿到的是上一次的残留值。

修法不是补那一个字段，而是**在取默认值前先 `memset(&cfg, 0, sizeof(cfg))`**：

```c
(void)memset(&cfg, 0, sizeof(cfg));
FlexCanDrv_GetDefaultCfg(&cfg);
```

这样将来 SDK 再漏别的字段，也只会落在"0"这个确定值上，而不是随机栈内容。
修完 `!s → !g` 完全可逆，`CTRL1` 前后都是 `0x052CA007`。

> 这个坑 M5 时其实**擦肩而过**：当时发现 `STOPPED → STARTED` 会把控制器弄哑，
> 结论是"软件重启不可靠，别用"，于是把 `!k` 删了，却没查到根因。
> 这次是 Com 的周期流量把它从"偶发"变成"必现"才逼出来的。
> **教训：把"这条路不能走"当成结论，比"找到了为什么"要危险得多。**

### M11 验收（EcuM + 标准通信链路，需要 Kvaser）

```bat
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools\m11_check.py
```

| 组 | 内容 |
|---|---|
| 启动 | 横幅 + `[ecum] RUN`；NVM 横幅证明 `DriverInitTwo` 跑过；无 PCC/Configure 超时 |
| 状态 | `!q` → RUN(2)；`!m` → `comm=FULL_COM_NETWORK_REQUESTED` + `cannm=NORMAL_OPERATION` |
| **自动通信** | **没有任何手工 `Init`**，`0x123` / `0x500` / `0x200` 全都在发 |
| 诊断回归 | `10 03` 正常（链路切换没踩坏 CanTp/Dcm） |
| 控制器可逆 | `!s` 停 → 信号 0 帧；`!g` 恢复 → 10 帧/秒（这就是 CanSM 做 bus-off 恢复走的同一路径） |
| POST_RUN | `!u` → mode=3，2.5 s 内 NM **0 帧** |
| 回 RUN | `!U` → mode=2，NM 与信号报文都恢复 |

### M11 做成了什么：初始化顺序从代码变成表

之前 `main.c` 里是 9 行手写的 `Xxx_Init(NULL)` 加一个启动控制器的循环，
每加一个模块都要回来改一次，顺序靠注释约定、编译器管不了。现在：

```c
// EcuM_Cfg.c —— 加模块 = 加一行
static const EcuM_DriverInitItemType EcuM_DriverInitListZero[] = {
    { (EcuM_DriverInitFncType)Port_Init, NULL },
    { (EcuM_DriverInitFncType)Can_Init,  NULL },
};
```

三个阶段按 AUTOSAR 划分：

| 阶段 | 放什么 | 本工程的映射 |
|---|---|---|
| **Zero** | 只依赖寄存器、不依赖任何 BSW | `Port_Init`、`Can_Init` |
| **One** | 需要能被上层调用的模块 | `CanIf` → `PduR` → `CanTp` → `Dcm` → `NvM_Init` → `Nm` → `CanNm` → `Com` → `ComM` → `CanSM` |
| **Two** | 要"世界安静下来"才能做的 | `NvM_ReadAll` + 启动计数 + `Dem_Init` |

`EcuM_BswService()` 同理，10 ms 节拍按表顺序跑
`CanSM → ComM → Com → CanNm → Nm → CanTp → Dcm → NvM → Dem`。

进 RUN 走的是标准三层，应用只碰 ComM 一个接口：

```
EcuM_AL_EnterRUN()
      ↓
ComM_RequestComMode(USER_APP, FULL) + ComM_CommunicationAllowed(TRUE)
      ↓  ComM 每 10 ms 仲裁
CanSM_RequestComMode(FULL)              Nm_NetworkRequest()
      ↓                                        ↓
控制器 STARTED + 收发器 NORMAL            CanNm 发 0x500
      ↓
ComM_Nm_NetworkMode() → Com_IpduGroupStart() → 0x200 开始发
```

### M11 的两个致命坑（都是"整机静默"级）

**① 厂商驱动的所有硬件等待都没有超时出口**

`FlexCanDrv_WaitExpired()`（`flexcan_drv.c:238`）是驱动里**唯一**的超时出口，
而它依赖 `obj->waitExpired` —— 厂商 `FlexCanDrv_Init()` 明确把它置 0，
**全仓没有任何地方赋值**。于是每一个 `while (硬件握手位)` 都是无限循环。

症状：接上 CanSM 后启动第一拍就卡死，**串口一行都不再输出、心跳停止**，
只有调试器能看到 PC 停在 `FlexCanDrv_EnableCanOperationClk`。

修法：在 AC 层实现 `CanAc_WaitExpired()` 并给每个通道一份独立预算，
每次调驱动前 `CanAc_WaitBegin()` 重置 —— 把"整机死"降级成"一次模式切换失败"。

**② 本平台的 FlexCAN 不能做低功耗往返 —— 而这正是 `CAN_CS_SLEEP` 会做的事**

CanSM 进 NOCOM 是四步（`CanSM.c:55~90`）：

```
CanIf_SetControllerMode(STOPPED)
CanIf_SetControllerMode(SLEEP)     ← 平台侧原本写 MCR[MDIS]=1，模块断电
CanIf_SetTrcvMode(NORMAL)
CanIf_SetTrcvMode(STANDBY)
```

一旦写下去，**再也回不来**。实测证据（CAN0，`0x40038000`）：

| 观测 | 结果 |
|---|---|
| `MCR` | 恒为 `0xD890000F`（`MDIS=1 / LPMACK=1 / NOTRDY=1`） |
| 调试器 `w4` 清 `MDIS` | **读回不变**，写不进去 |
| `PCC.CK_EN0` / `CK_EN1` | CAN0 两位都是 1（时钟开着） |
| `PCC.SW_RST0` / `LOCK` | 都是 0（没复位、没加锁） |
| 同一份代码的 CAN1 | 正常 —— 因为它只 `Configure` 过一次、没睡过 |

后果是滚雪球：CanSM 第一步请求 STOPPED，而"断电的模块进不了 freeze"
→ `FRZACK` 永不置位 → 请求失败 → CanSM 卡在 `PRE_NOCOM` 重试
→ 永远到不了 FULLCOM → 通道一次都启动不起来。

三处修正：

1. **`CanAc_SetSleepMode` 不再写 `MDIS`**，与 STOPPED 一样只做 freeze + halt。
   AUTOSAR 对 `CAN_CS_SLEEP` 的要求是"不通信"，不是"关外设时钟"；
   真正的省电在收发器 STB（已由 CanSM 驱动）和整机 `Mcu_SetMode`（M12）。
2. **`CanAc_DeInit` 在 `LPMACK=1` 时直接返回 `E_OK`** ——
   复位后 `MDIS` 本来就是 1，此时模块必然不可能通信，正好满足 STOPPED 语义。
   不这样处理，CanSM 的第一步就死锁。
3. **平台层显式打开 PCC 的两个时钟位**（`CK_EN0` 工作时钟 + `CK_EN1` 配置时钟），
   且在**任何**驱动调用之前。厂商只在 `Configure()` 开头开一次，
   于是"先 SLEEP 后 CONFIGURE"这条路径必然踩空。

另外把 `Configure` 收敛成**每通道只做一次**（`s_configured`）：
之后的 `STARTED` 只清 freeze/halt，O(1) 且没有低功耗往返。
这既符合 AUTOSAR 的语义（配置在 `Can_Init` 阶段完成），
也顺带让 M10 那个"SMP 位翻转"问题再也不会被触发。

### M11 还发现：as-master 的 ComM 也缺实现

`ComM_EcuM_WakeUpIndication()` 在 `ComM.h:105` 只有声明，**全仓无定义**，
链接期才报错。所以 `!A` 改为调用同一条链路的后半段
`ComM_Nm_NetworkStartIndication()` —— 它做的事完全一样
（`ComM.c:612` 置 `COMM_NM_FLAG_NETWORK_START`，下一拍走 passive startup）。

M12 接上收发器唤醒中断时，正确做法是在 EcuM 的 wakeup 处理里补一个
`ComM_EcuM_WakeUpIndication()`（一行转调），而不是在应用层继续调 Nm 侧入口。

### M11 的验收口径（必须说清楚）

`m11_check.py` 里的"控制器可逆（`!s`/`!g`）"验的是 **bus-off 恢复所走的同一条路径**，
**不是**"真的 bus-off 之后自己回来"。原因见「M5 的三个硬事实」①：
单节点实验室在 error passive 下 ACK 错误不再累加 TEC，造不出 bus-off。
真要做物理 bus-off，把 CAN_H 对地短接几秒即可 —— 那要动硬件，不进自动脚本。

### M12 验收（睡眠/唤醒，纯串口）

```bat
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools\m12_check.py
```

| 组 | 内容 |
|---|---|
| 唤醒源识别 | 冷启动横幅 `wake : NONE (255)  [cold boot]`（读 PMC 真实标志，不是软件猜） |
| EcuM 接口 | `!z` 里 `wakeup sources = 0x0100 (CAN0)`，走标准 `EcuM_EnableWakeupSources()` |
| **真的睡过** | `!z` → `tick +1 (约 100 ms)`：节拍临时放大到 100 ms，CPU 确实停在 WFI 里 |
| 不睡死 | 100 ms 兜底一定返回，返回后心跳继续、EcuM 仍在 RUN |
| 唤醒链路 | `EcuM_CheckWakeup` 被调用，且**如实报 `hw=NONE`**（tick 唤醒不是 CAN 唤醒），不走 ComM 唤醒分支 |

### M12 补了什么，以及为什么没做"真低功耗"

三件事：

1. **唤醒源可见**：启动横幅打一行 `wake : <源> (<编码>)`。实车没有调试器，
   这一行是排查"为什么自己醒了 / 为什么没睡"的第一手证据。
2. **补上 as-master 的第二个缺口**：`ComM_EcuM_WakeUpIndication()` 只有声明没有实现
   （`ComM.c` 里加了一行转调 `ComM_Nm_NetworkStartIndication`，走同一个 flag）。
3. **EcuM 三个唤醒接口**：`EcuM_EnableWakeupSources` / `EcuM_CheckWakeup` /
   `EcuM_EndCheckWakeup`。其中 `CheckWakeup` 只信**硬件标志**
   （`PowerDrv_GetWakeupSource()`），不信传进来的位图 ——
   位图是软件希望的，标志才是事实，两者不一致正是最该打日志的场景。

**没做真低功耗，是刻意的**，原因是硬件条件还不具备：

| 唤醒源 | 现状 |
|---|---|
| 收发器 WAKE 引脚 | ❌ 硬件没接（`Can_Cfg` 只有 STB） |
| CAN0 RX（PTE4）端口唤醒 | ❌ 没配。要做得在睡前把 PTE4 从 ALT5 切成 GPIO 边沿中断，醒来再切回 |
| `SysTick` | ✅ 一直在跑，是唯一的兜底 |

`!z` 因此走的是 Cortex-M **Sleep**（`SCB->SCR` 清 SLEEPDEEP + `WFI`），
**外设时钟没关、电流不会明显下降**。它的价值是把"WFI 通路 + 唤醒源读取"
这两件事验证到位：

```
!z → tick +1 (约 100 ms), 唤醒源=NONE(255)
   → CheckWakeup req=0x0100 hw=NONE
```

`tick +1` 是关键证据：如果 CPU 在空转，`Platform_NowMs()` 会前进上百个 tick；
只前进 1 个，说明它确实停在那里等中断。

> **"能睡"和"省电"必须分开说。** 把两者混为一谈是这类项目最常见的自欺。
> 真正测电流必须等 M13 把端口唤醒做出来、停掉 SysTick 之后。

### M12 的设计取舍：`EcuM_AL_EnterSLEEP()` 为什么不直接 WFI

`EcuM_MainFunction()` 走到 SLEEP 时，`EcuM_AL_EnterPOST_RUN()` 早已跑过，
它只是**发起**了撤通信请求。之后 ComM → Nm → CanNm 还要走
`ReadySleep`(2 s) → `PrepareBusSleep`(2 s)，CanSM 才把控制器停掉。
这时候立刻 WFI 会有三个问题：

1. 总线上可能还有报文没发完，睡下去就截断了；
2. 真正的"可以睡了"条件是 `ComM_GetState() == NO_COM_NO_PENDING_REQUEST`，
   那是 2~5 s 之后的事；
3. 本平台 CAN 模块的低功耗态不可逆（见「M11 的两个致命坑」②），
   必须确认它已经停稳才能动电源。

所以 `EcuM_AL_EnterSLEEP()` 只记录状态 + 打日志，
**真正的 WFI 由应用在确认总线已静之后主动调用**（`!z`，或将来更上层的电源策略）。

### M3 验收（UDS on CAN，0x7E0 → 0x7E8）

```bat
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools/m3_check.py
```

| 组 | 内容 |
|---|---|
| 0x10 | `10 03` → `50 03 00 32 01 F4`；串口 `[dcm] session 1 -> 3` |
| 0x22 多帧 | `22 F1 90` → `62 F1 90` + 17 字节 VIN（响应 20 字节，走 FF+CF） |
| 0x22 单帧 | `22 F1 87` → `62 F1 87` + 11 字节零件号 |
| 0x3E | `3E 00` → `7E 00` |
| NRC | 未知 DID → `7F 22 31`；未实现服务 → `7F 31 11` |
| RX 多帧 | 20 字节长请求（FF+CF 上行）→ 得到 `7F 2E 11`，证明重组正常 |
| S3 | 静默 6.5 s → `[dcm] session 3 -> 1 (S3 timeout)` |

实测：**17 项，通过 17，失败 0**。M2 回归 40/40，M0 回归 26/26。

> 测试脚本**没有用 `can-isotp`**：`isotp.CanStack` 在这块 Kvaser 上实测收不到响应帧
> （板子确实回了 0x7E8，库的 `process()` 就是不返回数据）。改成手写 70 行 ISO-TP
> （SF / FF / CF / FC），每一帧显式可控，反而更好定位问题。

### M3 落地的三个坑（都是实测撞出来的）

**① `GetSesChgPermissionFnc` 不能传 NULL。**
`Dcm_Dsp.c:373` 是 `sesCtrlConfig->GetSesChgPermissionFnc(...)`，**没有判空**。
传 NULL 后第一条 `10 03` 就跳到地址 0，CFSR 报 `INVSTATE` 进 HardFault。
症状极具迷惑性：启动横幅、printf 自检全正常，只有发诊断请求时整块板子静默 ——
看着像"CAN 收不到"，实际是诊断栈崩了。

**② `XXX_MainFunction()` 必须按固定周期调用，不能扔进自由循环。**
`CanTp` / `Dcm` 的定时器是"每调用一次减一 tick"（`CanTpSignalAlarm`），
而 N_Bs/N_Cr/S3 是把毫秒按 `*_MAIN_FUNCTION_PERIOD` 折算成 tick 的。
主循环每秒跑几万次 → 100 tick 的 N_Bs 在几百微秒内耗尽 → **单帧全通、多帧一律失败**。
本工程用 `BSW_PERIOD_MS`（10 ms）统一调度：
```c
if ((Platform_NowMs() - nextBsw) >= BSW_PERIOD_MS) {
    nextBsw = Platform_NowMs();
    CanTp_MainFunction();
    Dcm_MainFunction();
}
```

**③ 多帧发送必须开 `CANTP_USE_TX_CONFIRMATION`。**
`CanTp_SendCF()` 发完一帧把状态置 `WAIT_CF_TX_COMPLETED`，之后只有两条路能推进：

| 编译选项 | 推进者 | 代价 |
|---|---|---|
| **定义本宏**（本工程） | `CanTp_TxConfirmation()` ← CanIf 的发送完成回调 | 需要 PduR 路径 `PDUR_CANTP_TX_CONFIRM` 把确认接回 CanTp |
| 不定义 | `CanTp_MainFunction_Fast()` 无条件推进 | 需要 1 ms 周期任务，且**绕过 STmin** |

不开又没接 Fast 任务的症状：FF 发得出去、**第一帧 CF 也发得出去，然后没下文**。

### 一条 ISO-TP 诊断链路要过 4 条 PduR 路径

这是最容易搞错的地方 —— **TP 型报文要过两次 PduR**：

```
N-PDU（单帧）                        SDU（重组后的整条请求）
0x7E0 → CanIf → PduR → CanTp   →   PduR → Dcm
          path 2                    path 0
```

| pathId | 方向 | Src | Dest | 用到的回调 |
|---|---|---|---|---|
| 0 | SDU 上行 | CanTp | Dcm | `TpRxIndication` / `StartOfReception` / `CopyRxData` |
| 1 | SDU 下行 | Dcm | CanTp | `Transmit` / `CopyTxData` / `TxConfirmation` |
| 2 | N-PDU 上行 | CanIf | CanTp | `RxIndication` |
| 3 | N-PDU 发送确认 | **CanTp** | CanIf | `TxConfirmation` |

两个必须记住的约束：

- **path 0 必须是 0**：`Dcm_StartOfReception(id,...)` 里 `DET_VALIDATE(id < numOfChls)`，
  Dcm 把 RX pathId 当通道索引用。
- **path 3 的 Src 是 CanTp 而不是 CanIf**：`PduR_TxConfirmation()` 把结果交给
  `SrcPduRef->api->TxConfirmation` —— **确认永远往上游走**。写成 Src=CanIf 会得到空指针调用。


### M1 验收（历史，被 M2 覆盖）

```bat
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools/m1_check.py
```

| 组 | 内容 |
|---|---|
| 横幅 | `bring-up (M1)`、CAN 配置行 |
| TX | 3 s 内 ≥4 帧 `0x123`、DLC=8、标准帧、**数据逐帧 +1** |
| RX | Kvaser 发 `0x321` → 板子打印 `[can] rx #1 id=0x321 data=de ad be ef 01 02 03 04` |
| 心跳 | ≥2 条（证明 CAN 初始化没卡住主循环） |

实测：`10 项，通过 10，失败 0`。M0 回归仍 `26 项，通过 26`。

实测通道对应：**Kvaser ch0 = 板子 CAN0**，ch1 = CAN1（M1 未初始化，收到 0 帧）。

M0 有两条独立的证据链。**第一条不需要串口**，只用 J-Link 读 RAM/寄存器：

| 判据 | 实测 |
|---|---|
| 固件入口 | `Entry = 0x401`，向量表在 0x0（栈顶 0x2000F000 / Reset 0x401） |
| 内核时钟 | PLL 120 MHz（`s_ms` 1 s 涨 1000） |
| UART2 | `CR1=0x0D`（UE/TE/RE）、`BRR=0x8A`、`TDR` 最后写入 `0x0A`、`ISR=0xD0` |
| 主循环 | PC 采样落在 `main` / `UartDrv_GetRxCounter`，非卡死 |

**第二条是串口上的自动验收**（板载 CH343 → PC 的 COM2）：

```bat
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools/m0_check.py
```

它会先开串口再复位（顺序反了会丢掉启动横幅），然后核对 26 项：

| 组 | 项数 | 内容 |
|---|---|---|
| 启动横幅 | 3 | 版本、`PLL 120 MHz`、`UART2 115200 8N1` |
| printf 自检 | 17 | 宽度/左右对齐/补零/`#` 前缀/正负号/精度/`INT32_MIN`/字符串截断/`%%` |
| 心跳 | 3 | ≥2 条、周期 1000 ms（±30）、序号连续 |
| 回显 | 3 | 短串、16 字符、52 字符长串 |

实测：`26 项，通过 26，失败 0`，退出码 0。

## M13 验收：A/B 分区 UDS bootloader

**这一轮做的是 bootloader，不是低功耗**（低功耗按用户要求往后放）。

### 分区布局（`boot_flash_map.h` 是唯一权威）

```
0x00000000  ┌──────────────────────┐
            │ Boot          64 KB  │  选槽 / 校验 / 跳转 / 回滚（不含刷写）
0x00010000  ├──────────────────────┤
            │ Slot A       448 KB  │  尾部 4 KB = meta（主备各 1 个扇区）
0x00080000  ├──────────────────────┤
            │ Slot B       448 KB  │  尾部 4 KB = meta
0x000F0000  ├──────────────────────┤
            │ 预留          64 KB  │  标定 / 参数 / 扩展
0x00100000  └──────────────────────┘
```

单槽可用镜像 **444 KB**（448 − 4）。当前镜像 155.8 KB，余量 2.8 倍。

### 四个关键设计

| 设计 | 为什么 | 不这么做会怎样 |
|------|--------|----------------|
| **双镜像**（App / AppB 各链接一次） | Cortex-M4 无 MMU，绝对地址链接时定死 | A 的镜像刷进 B 槽，第一次解引用全局变量就跳飞 |
| **活动槽 = rollingCounter 大者**，无独立标志位 | 计数值只有一次写操作，天然原子 | 标志位要"先清旧再置新"，中间掉电就两个都活动/都不是 |
| **meta 放槽尾**（主备各一份，先备后主） | 镜像被整体擦除时 meta 同槽一起没，不可能"镜像没了 meta 还说有效" | 独立 meta 区需要额外同步，且 A/B 不对称 |
| **只刷非活动槽** | 正在跑的那份永远不被碰 | 刷一半掉电，两个槽都废，只能拆壳接调试器 |

### 上电流程（boot 侧，`app/boot/src/main.c`）

```
Platform_Init()        时钟 + 串口（精简驱动：clock/flash/power/reset/pins/uart）
BootMeta_Init()        读两槽 meta（主备择优：取 rollingCounter 大的那份）
GetActiveSlot()        排除 metaValid=0 / EMPTY / INVALID，取计数最大者
CheckImage(slot)       长度 + 向量表(SP/PC) + CRC32
  ├─ 通过 → 跳
  ├─ meta 完好但镜像不符 → **降级 TESTING 后仍跳**（见坑 ⑦）
  └─ meta 也没有 → 换另一槽；都不行 → HALT 并打印救援命令
PrepareJump(slot)      TESTING 时尝试次数 +1，超 3 次判 INVALID（回滚触发点）
JumpToApp(base)        停 SysTick → 关清 NVIC → VTOR → 换 MSP → 跳
```

app 起来后 `BootApp_Init()` 对账槽地址、必要时自注册；`BootApp_Confirm()`
在 **CAN 起来之后**才把 meta 置 CONFIRMED —— 放在 main 开头的话，
"时钟对了但总线起不来"的镜像也会被判成功，回滚就白做了。

### 刷写链路（app 侧）

| UDS | 作用 | 关键点 |
|-----|------|--------|
| `31 01 FF00 <addr4> <size4>` | 擦除非活动槽 | **分片**：每主循环周期擦 1 个扇区、返回 `0x78`，Dcm 的 `Dcm_Pending` 会自动重入 |
| `31 01 FF01 <addr4> <size4> <crc4>` | 校验镜像 | 同步完成（150 KB CRC ≈ 6 ms） |
| `34 00 44 <addr4> <size4>` | 请求下载 | 地址必须**正好等于**槽基址；块长报 120（8 的倍数） |
| `36 <seq> <data>` | 写一块 | 地址必须严格连续；不足 8 字节的尾巴跨块暂存 |
| `37` | 结束 | 补 0xFF 写尾巴 → **从 Flash 读回来**算 CRC → 写 meta（TESTING，rc+1） |
| `11 01` | 复位 | `AIRCR.SYSRESETREQ`，延时 500 ms 让 `51 01` 先发出去 |

工具：`tools/uds_flash.py --elf <AppB.exe> [--verify]`，实测 **6.8 KB/s**，
155.8 KB 用 23 秒，擦除 0.5 秒。

### 实测记录（双向都验过）

```
# 从 A 刷 B
slot A : CONFIRMED  rc=9   size=159560  crc=0F2F97AA
slot B : CONFIRMED  rc=10  size=159564  crc=F7513B8F
[boot] active slot : B (rolling counter)
[boot] jump to slot B  base=0x080000  entry=0x080400
[app]  slot : B  (link 0x00080000)
[app]  slot B meta ok  state=2  rc=10

# 从 B 刷 A（反向）
verify    : OK
[boot] jump to slot A  base=0x010000
[app]  slot : A  (link 0x00010000)
```

### M13 踩的七个坑

| # | 现象 | 根因 | 修法 |
|---|------|------|------|
| ① | `missing binary operator before token "("` | `#if (sizeof(X) % 8)` —— 预处理阶段 `sizeof` 未求值 | 改 `_Static_assert` |
| ② | boot 一上电就 HardFault，`BFAR=0x44` | 精简版 `Mcu_Init` 漏了 `PinsDrv_Init`，`Uart2_Init` 配引脚时端口基址是 NULL | 补 5 个 `PinsDrv_Init` |
| ③ | boot 报"镜像 CRC 失败"，但调试打印里 CRC 明明一致 | `CheckImage` 要求 `imageSize % 8 == 0`，而实际值 154804 **% 8 = 4** | 只要求 4 字节对齐（CRC 覆盖任意长度都成立） |
| ④ | 刷写到第 18 块（偏移 2040）必挂 NRC 0x72 | `FlashDrv_Read1sSection()` **拒绝跨扇区**，判空预检按 1 KB 切段时跨了 2 KB 边界 | 切段时同时按扇区边界夹 |
| ⑤ | 多帧请求发出去、FC 也回来了、然后没响应 | `isotp_lite._send_long()` 忽略 FC 的 **BlockSize**，把 17 个 CF 全推出去，ECU 收满 8 帧就等下一个 FC | 按 BS 分段等 FC，并按 STmin 延时 |
| ⑥ | `31 01 FF01` 明明校验成功，工具报 MISMATCH | 响应是 `71 01 FF 01 <status>`，状态在 `r[4]`，工具读的 `r[3]`（RID 低字节） | 改读 `r[4]`，并检查长度 |
| ⑦ | J-Link 重烧 app 后"能跑一次、一复位就 HALT" | 槽尾 meta 还记着旧镜像 CRC → boot 校验失败不跳 → 唯一能修 meta 的 app 没机会启动 | `BootMeta_DemoteToTesting()`：meta 完好但镜像不符时降级 TESTING 仍跳一次，起不来由 attempts 自动回滚 |

> 坑 ④ 和 ⑦ 的共同点：**失败发生在"看起来最不可能"的地方**。
> ④ 的 CRC 是对的、镜像也是对的，挂在一个从不报错的预检上；
> ⑦ 的 meta 是好的、镜像也是好的，挂在两者"版本对不上"。

### 构建与烧写（A/B 之后变了）

```sh
build.bat --app=Boot                          # boot（54 KB / 64 KB）
build.bat --app=App                           # slot A 镜像
build.bat --app=AppB                          # slot B 镜像

python tools/flash.py --boot --run            # 首次部署：boot + App 一起烧
python tools/flash.py --elf <App|AppB> --force --run   # 开发迭代：烧完保证它会跑
python tools/uds_flash.py --elf build/nt/CM4GCC/AppB/AppB.exe --verify   # 升级到 B 槽
```

**boot 只占 54 KB**：`Mcu_Init()` 会把 20 多个外设驱动全拉进镜像（56 KB），
boot 走精简版 `Platform_McuInitMinimal()`，只初始化 clock/flash/power/reset/pins/uart。

#### 为什么开发迭代必须加 `--force`

J-Link/CSpyBat 只写镜像、**不动槽尾 meta**。于是"刚烧进去的新镜像"和
"meta 里记的旧 rollingCounter"对不上 —— boot 仍去启动计数更大的那个槽，
新固件永远没机会跑。**症状是"烧写成功、串口输出还是老版本"**，
极容易误判成编译没生效（M14 排查时就先怀疑过固件没烧进去）。

`--force` 的做法：从 ELF 的 `.interrupts` 段判断镜像链接在哪个槽，
然后把**另一个槽**的 meta 区（主 + 备，共 2 个 4 KB 内的扇区）整段写 0，
让 boot 认为它没有有效元数据。只影响另一个槽，正在跑的那份不动。

> **踩过的坑：`objcopy -I binary` 造出来的 ELF 没有程序头（PHDR）。**
> CSpyBat 只按程序头下载，于是它什么都不烧、`rc` 还返回 0。
> 第一次实现就是这么"报告清零成功"，回读却一个字没变。
> 现在改用 `arm-none-eabi-ld` + 链接脚本（并加 `-z max-page-size=0x1000`，
> 否则默认 64 KB 页对齐会把 LOAD 段撑成 64 KB，连带擦掉大半个预留区），
> 并且**强制 J-Link 回读校验** —— 不复信退出码。


### 已知缺口（bootloader 方向）

- meta 里的**版本号是 0**（`FlashLoader_TransferExit` 没从镜像里解析）—— 需要 `0x2E` 写 DID 或从镜像头约定字段读
- **boot 自身不支持刷写**（按约定只做启动管理）。两槽都坏时只能 J-Link 救
- `0x27 CompareKey()` 仍恒通过，量产前必须换真算法
- 刷写期间**没有 3E 保活**，靠 P2/P2* 的 0x78 维持；超过 5 秒无响应的工具会被 S3 踢回默认会话

## 目录

```
H:/as/
  SConstruct / SConscript      与 as-master 逐字同构（遍历子目录 + Building()）
  build.bat                    构建入口（纯 ASCII，见坑 7）
  app/
    SConscript                 遍历 */
    app/                       主应用（--app=App / --app=AppB，同一份源码两个链接变体）
      SConscript               两个 Application 子类只差 LD 与 APP_SLOT_INDEX
      src/main.c               横幅 + printf 自检 + 心跳 + 回显 + 全部 `!` 命令
      src/EcuM_Cfg.c            M11：三张初始化表 + 10 ms BSW 调度表
      src/ecum_callout.c       M11：全部 `EcuM_AL_*` 集成代码（进 RUN 走 ComM）
      src/boot_app.c/h         M13：槽地址对账 + 首次自注册 + 启动确认
    boot/                      M13：boot 工程（--app=Boot，链接 0x0，54 KB）
      SConscript               只链平台库，不链任何 BSW 模块
      src/main.c               选槽 → 校验 → 跳转；镜像全坏时 HALT 并打印救援命令
    platform/
      SConscript               遍历 */
      cvm0146/
        SConscript              LibraryCvm0146：SDK + 启动 + AC + cfgs 表
        include/                平台对外头文件（应用层只认这里）
        src/
          platform_cvm0146.c    时钟 + 控制台 + SysTick
          platform_priv.h       内部共享（McuType、端口映射），不对外
          PortAc.c              PortAc_PinInit → PinsDrv
          DioAc.c               DioAc_Read/WriteChannel → PinsDrv
          CanAc.c               CanAc_* + **Can_Write** + 邮箱中断（收发都在这）
          AdcAc.c               M15：ADC0/ADC1 + PDB0/PDB1 + TRGMUX（**唯一碰 ADC 寄存器的地方**）
          FlashAc.c             M13：PFlash 单扇区擦 / phrase 写 / 判空（**关中断 + 回读校验**）
          BootMeta.c            M13：meta 主备读写 + 活动槽判定 + 镜像 CRC 校验
          FlashLoader.c         M13：0x31/0x34/0x36/0x37 回调（分片擦、对齐写、meta 落盘）
          config/
            Port_Cfg.c/h        引脚 MUX/方向/初始电平（唯一配 MUX 的地方）
            Adc_Cfg.c/h         M15：组/通道表（hwUnit + hwChannel + 采样时间 + 参考电压）
            Dio_Cfg.c/h         通道号 → 端口/引脚
            Can_Cfg.c/h         通道参数（波特率/STB/hwInstanceId）**+ 邮箱表 + HTH 表**
                                M14：15 个邮箱按**段**分组（20+ 条报文，49 条也够用）
            CanIf_Cfg.c/h       RX 过滤表 + TX PDU 表 + 控制器上下文
                                M14：23 条 RX 表项，严格升序 + 区间不重叠
            CanTp_Cfg.c/h       ISO-TP 通道（0x7E0/0x7E8、N_Bs/N_Cr、STmin、BS）
            PduR_Cfg.c/h        4 条路由路径（N-PDU 与 SDU 各一对）
            Dcm_Cfg.c/h         服务表 + DID 表 + 会话/计时 + **刷写例程表**
                                （0x10/0x22/0x2E/0x27/0x31/0x34/0x36/0x37/0x11）
            Can_HwCfg.h         邮箱/HTH 的中性类型与报文 ID（平台私有）
                                **标准帧硬件掩码必须 << 18**（见 M14 头号坑）
        sdk/                    厂商 SDK 原样（6 MB，只读）
          drivers/ reg/ mcu.c mcu.h CVM014x_features.h
          linker/               CVM0146_flash.ld（原始）
                                CVM0146_boot.ld  0x00000000 / 64 KB
                                CVM0146_app_a.ld 0x00010000 / 448 KB
                                CVM0146_app_b.ld 0x00080000 / 448 KB
  infras/                       AUTOSAR BSW/MCAL（与 as-master 同构）
    SConscript                  $INFRAS 注册 + 遍历子目录
    include/                    82 个公共头（Std_Types / Can / Dio / Port / Det / CanIf ...）
    mcal/
      SConscript                遍历 */
      Can/                      AS 原样 Can.c（198 行，只状态机）+ Can_Priv.h
      Adc/                      M15：Adc.c（薄转发）+ Adc_Priv.h（配置结构 + AdcAc_* 边界）
                                **as-master 没有这个模块**，按它的三段式补
      Dio/                      AS 原样 Dio.c（38 行）
      Port/                     AS 原样 Port.c（33 行）
    communication/
      SConscript                遍历 */
      CanIf/                    AS 原样 CanIf.c（600 行，软件 ID 过滤 + 分发）
      PduR/                     AS 原样 PduR.c + CanIf/CanTp/Dcm 三个 shim（只取用到的）
      CanTp/                    AS 原样 CanTp.c（ISOTP 分段/重组）
      Com/                      M10：AS 原样 Com.c（1135 行，信号打包/解包/周期）
      ComM/                    M11：AS 原样 ComM.c（688 行，通信管理器）
      CanSM/                   M11：AS 原样 CanSM.c（703 行，控制器/bus-off 状态机）
      CanNm/                    M9：AS 原样 CanNm.c（1183 行，NM 状态机）
      Nm/                       M9：AS 原样 Nm.c（208 行，按 busType 分发）
    libraries/
      SConscript                遍历 */
      mempool/                  AS 原样（CanIf 的包池依赖，即使池为 0 也要头文件）
      crc/                      M13：as-master 原样（CRC8/16/32/32P4，pycrc 表驱动）
      stdbit/                   M10：AS 原样 std_bit.c（Com 的位流读写，32 位）
                                只拷 32 位版，std_bit64.c 本工程用不到
    diagnostic/
      SConscript                遍历 */
      Dcm/                      AS 原样 Dcm.c/Dsl/Dsd/Dsp
                                （0x10/0x14/0x19/0x22/0x27/0x2E/0x3E）
      Dem/                      本工程写的 Dem（简化实现，接口与 AUTOSAR 一致）
        Dem.c                   DTC 状态表 + 0x19/0x14 的后端（零拷贝，直写 NvM 块 RAM）
    memory/                     M4：存储栈
      SConscript                $MEMORY / $MEMORY_VENDOR 注册 + 遍历 */
      vendor/                   厂商 NvM + FEE 引擎，**原样不改**（升级=整目录覆盖）
        fee/                    fee.c / fee_initialization.c
        nvm/                    nvm.c / nvm_block.c / nvm_queue.c / nvm_statemachine.c
      NvM/                      本工程写的 AUTOSAR 外观
        NvM.c                   NvM_Init/ReadBlock/WriteBlock/ReadAll/WriteAll/MainFunction
        NvM_Port.h              外观与引擎之间的**唯一**通道（零厂商类型、零 AUTOSAR 类型）
    system/                     M4：Det / M8：timer / M11：EcuM
      Det/Det.c                 参数错误落点（弱符号 Det_Log 由应用覆盖打串口）
      timer/std_timer.c         软件定时器（逻辑原样，时间源由平台提供）
      EcuM/                     M11：AS 原样 EcuM.c（115 行标准状态机）
        EcuM.c                  Init / StartupTwo / RequestRUN / MainFunction
        EcuM_Priv.h             配置结构（三张初始化表 + 两张主函数表）
  doc/
    AUTOSAR 学习文档/            知识库（Obsidian）
  refs/vendor/                  厂商参考资料（562 MB，**不参与构建**，可随时删除）
  tools/
    building.py                 与 as-master 同一份构建框架（仅改 CM4 multilib 目录名）
    flash.py                    CSpyBat 烧写 + J-Link 复位运行
    m0_check.py                 M0 串口自动验收（26 项，退出码即结论）
    m1_check.py                 M1 CAN 收发验收（10 项，需 Kvaser）—— 已被 M2 覆盖，保留作历史
    m2_check.py                 M2 验收（40 项：双通道收发 + 掩码 + 控制面）
    m3_check.py                 M3 验收（17 项：UDS 0x10/0x22/0x3E + NRC + 多帧）
    m4_check.py                 M4 验收（23 项：块表/掉电保持/ROM默认/延迟落盘/DET/GC压测）
    m5_check.py                 M5 验收（25 项：BOFFMSK/故障注入/累加/掉电保持/清除/不破坏收发）
    m6_check.py                 M6 验收（23 项：0x19 三个子功能/状态过滤/0x14 清除/一致性/回归）
    m7_check.py                 M7 验收（16 项：0x27 握手/会话限制/0x2E 写入与拒绝/NvM 落盘）
    m8_check.py                 M8 验收（11 项：多扩展帧并行/掩码分组/负例过滤/回归）
    m9_check.py                 M9 验收（26 项：NM 周期/CBV/睡眠序列/被唤醒/被动启动/回归）
    m10_check.py                M10 验收（22 项：位打包/大小端/信号超时/分组启停/回归）
    m11_check.py                M11 验收（18 项：三阶段启动/ComM→CanSM 链路/RUN↔POST_RUN）
    m12_check.py                M12 验收（15 项：唤醒源上报/CheckWakeup 如实报告/STOP 睡眠/不睡死）
    m14_check.py                M14 压测（逐条 5/5 + 满线 9200 帧 + 按邮箱/按 PDU 双计数比对）
    uds_flash.py                M13：UDS 刷写上位机（31/34/36/37 流程 + 校验）
    isotp_lite.py               手写 ISO-TP（M3/M6/M13 共用，内置 NRC 0x78 pending、按 BS 等 FC）
    gen_compdb.py               生成 compile_commands.json（给 IDE 做全工程索引）
  build/nt/CM4GCC/App/          产物：App.exe（ELF）+ App.s19 + App.map
  compile_commands.json         IDE 索引数据库（gen_compdb.py 生成，可删）
  .vscode/ .clangd              编辑器配置：compile_commands 已接好
```

## 与 as-master 的组织对照

| 职责 | as-master | 本仓库 |
|---|---|---|
| 构建框架 | `SConstruct` + `SConscript` + `tools/building.py` | **同构**，`SConstruct` 逐字相同 |
| BSW/MCAL | `infras/{include,mcal,communication,diagnostic,memory,system,libraries}` | 同名同层级 |
| 平台层 | `app/platform/<mcu>/`（`src/` 放 AC，`src/config/` 放 `*_Cfg.c`） | `app/platform/cvm0146/`，同布局 |
| 应用 | `app/app/`（`--app=App`） | `app/app/`（`--app=App`） |
| 厂商 SDK | 不在主仓（由芯片厂商提供） | `app/platform/cvm0146/sdk/`（本仓库自带，便于复现） |
| 参考资料 | `doc/` | `doc/` + `refs/vendor/`（后者不进构建） |

**每层的 `SConscript` 只做"遍历子目录"**，新增平台或模块只要建目录 + 写一个
`@register_library` 即可，不需要维护任何列表：

```python
# app/SConscript、app/platform/SConscript、infras/mcal/SConscript 都是这两行
for sc in Glob("*/SConscript"):
    SConscript(sc)
```

**模块裁剪靠 `cfgs` 字典**（`app/platform/cvm0146/SConscript`）：写一行就编进配置并加
`USE_<NAME>` 宏，不写就不链接。这是 AS "可裁剪" 的实现方式。

> 变更记录：原规划的 `project/{demo,app,boot}`（一个目录一个项目）已按 as-master
> 改为 `app/{app,bootloader,examples}` —— 应用与 bootloader 是**同一套构建体系下的不同 target**
> （`--app=App` / `--app=Boot`），不是并列的独立工程。

## 构建与烧写

```bat
build.bat                                         :: 默认 --app=App
build.bat --app=App --verbose
build.bat --cpl=?                                 :: 列出可用工具链

"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools/flash.py --run
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools/m0_check.py
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools/m1_check.py
```

`build.bat` 会把 `%ARMGCC%\bin` 加进 PATH：`ar`/`objcopy`/`size` 是裸命令名调用的。

工具链：`arm-none-eabi-gcc 10.3.1`（`C:\soft\gcc\10.3.1` → 指向 `10 2021.10` 的目录联接）。
`build.bat` 已设 `PYTHON` / `ARMGCC` / `ARMGCC_VERSION`：
SCons 装在 Python 3.12（PATH 上的 `python` 可能是没有 scons 的 3.13）。

## 九个坑（都是这次实测踩出来的）

1. **`startup.c` 的 IAR 版本不能用于 GCC**：它用 `__section_begin()`。必须用 CDS 的
   `startup_M014x_gcc.S` + `CVM0146_flash.ld`，因为 GCC 分支依赖
   `__DATA_ROM/__BSS_START/...` 这些链接脚本符号。
2. **ECC RAM 初始化只在 `START_FROM_FLASH` 分支里**：复位后先整片写零。漏了这个
   宏，读未初始化 SRAM 会报 ECC 错，症状是"随机 HardFault"，极难查。
3. **平台层的路径要用 `GetCurrentDir()`**：`SConscript` 在 `variant_dir` 下执行，
   `Dir("include")` 会被映射成 `build/nt/.../include`（不存在）。`GetCurrentDir()` 走
   `rfile()`，拿的是源码目录绝对路径。
4. **`Glob()` 必须写在模块级别，不能写在 `config()` 里**：`config()` 执行时 cwd 已是
   `variant_dir`，那里没有源码副本（`duplicate=0`），Glob 返回空 →
   链接时报 `undefined reference to main`。
5. **`-Map` 不能直接传给 gcc**，要写 `-Wl,-Map,<path>`。
6. **J-Link 不能直接 `loadfile`**：安装目录缺 `Devices/CVA_BLUE_WHALE/`，内置
   CVM0146 的 FLM 落空。走 IAR `CSpyBat --download_only`（IAR 自带 FLM+DDF），
   再用 J-Link `r`+`g` 复位运行 —— 即 `tools/flash.py`。
7. **`.bat` 里不能写中文**：UTF-8 的 bat 被 cmd 按 GBK 解码 → 乱码 + `if (...)` 括号被破坏，
   症状是 `'t' 不是内部或外部命令`。全用 ASCII。
8. **格式化输出不解析宽度会"让日志撒谎"**：首版 `Platform_Printf` 没处理 `%6u`，
   原样输出且**没消耗对应参数**，紧跟的 `%u` 取到错位的值，打印成 `alive #138000`
   （正确 `#138`）。程序不崩、只是数字全错。所以：① 修饰符必须解析并消费参数；
   ② 不支持的转换符要显式报错并终止（`%10s` 那种会把整数当指针解引用 → HardFault）；
   ③ 格式化层必须有上板可见的自检用例。
9. **`ar` 不在 PATH 上，Windows 才会遇到**：`building.py` 只设了 `CC`/`AS`，
   而 SCons 的 `ar` tool 默认 `$AR = "ar"`；Linux 工具链有裸 `ar`，Windows 只有
   `arm-none-eabi-ar.exe`。已在 `CreateCompiler` 里补 `AR`/`RANLIB`，
   `build.bat` 也把工具链 `bin` 加进 PATH。
   **这个错只在"构建库"（要打 `.a`）时出现，只构建应用是碰不到的** ——
   所以 M0 一路正常，到 M1 加静态库才炸。

## 关于 AS 的 Can 驱动，两个反直觉的点

复刻前必须知道，否则会以为"代码不全"：

1. **`Can_Write` 在整个 `infras` 里没有实现**，只有 `Can.h` 的声明和 `CanIf.c` 的调用。
   `Can.c` 只有 198 行，全是状态机 + DET 校验。TX/RX 必须由平台的 AC 层补上 ——
   本仓库补在 `src/CanAc.c`。
2. **`CanIf_SetTrcvMode` / `CanIf_GetTrcvMode` 定义在 `Can.c` 里**，不在 `CanIf.c`。
   这是 AS 的一处分层倒置（MCAL 里出现了名字带 CanIf 的函数），
   但它行为是对的（就是控 STB 引脚），照着用即可；M2 接 CanIf 时注意别重复定义。

## 读代码导航：`*Ac_*` 这类"看不见的实现"

这是 AC 分层最让人不适应的地方，先把它说透。

**现象**：在 `infras/mcal/Port/Port.c` 里对 `PortAc_PinInit()` 按 F12，只跳到
`Port_Priv.h` 的声明；`infras/mcal/Port/` 目录里"缺一段实现"，像代码不全。

**原因**：它不是编译期 include 进来的，是**链接期绑定**。

| 时间点 | 发生了什么 | 怎么验证 |
|---|---|---|
| 编译 `Port.c` | 只看到声明，生成 `call` + 一个待填地址 | `arm-none-eabi-nm Port.o` → `U PortAc_PinInit` |
| 编译 `PortAc.c` | 定义该函数，并调用厂商 `PinsDrv_*` | `nm PortAc.o` → `T PortAc_PinInit`、`U PinsDrv_*` |
| 链接 | ld 拿 `U` 找 `T`，把地址填进 `call` | 重定位 `R_ARM_ABS32 PortAc_PinInit` |
| 运行 | `Port_Init` 的 `call` 跳到 `0x19a4` | 实测 MUX 寄存器被写成 `0x500`（ALT5） |

**结论：debug 不是问题。** 符号在最终 ELF 里，函数名下断点能命中：

```
$ arm-none-eabi-gdb  →  break PortAc_PinInit
Breakpoint 1 at 0x19b0: file app\platform\cvm0146\src\PortAc.c, line 40.
（J-Link 硬件断点实测 PC = 0x000019B0，正好停在函数体第一行）
```

栈回溯、局部变量、单步全部正常。**只是 IDE 的"跳转"不友好**，因为语义上确实是两个文件。

### 三个层次的对策

**① 命名约定（零成本，解决 80%）**
看到 `XxxAc_` 就去 `app/platform/<芯片>/src/XxxAc.c`。表里一一对应：

| 接口 | 实现位置 |
|---|---|
| `PortAc_PinInit` | `app/platform/cvm0146/src/PortAc.c` |
| `DioAc_Read/WriteChannel` | `app/platform/cvm0146/src/DioAc.c` |
| `CanAc_GlobalInit/Init/DeInit/SetSleepMode/SetupPinMode/WritePin` | `app/platform/cvm0146/src/CanAc.c` |
| **`Can_Write`**（AUTOSAR 标准接口，AS 未实现） | `app/platform/cvm0146/src/CanAc.c` |
| 各模块 `*_Cfg.c` 配置表 | `app/platform/cvm0146/src/config/` |

三个 `*_Priv.h` 里的声明处已加注释直接指向实现文件（本地新增注释，不改 AS 代码）。

**② 全工程索引（解决跳转与查引用）**

```bat
"%LOCALAPPDATA%\Programs\Python\Python312\python.exe" tools/gen_compdb.py
```

生成 `compile_commands.json`（53 个编译单元，含每文件的 `-D`/`-I`），已配好：
- `.vscode/c_cpp_properties.json` → 已装的 **cpptools 直接可用**，无需装新东西；
- `.clangd` → 若装了 clangd，更准（自动向 arm-gcc 查询系统头路径）。

用它按 **Find all references**（不是 F12）来找 `PortAc_PinInit`：
会同时列出 `Port_Priv.h` 的声明、`Port.c` 的调用点、`PortAc.c` 的定义。

> ⚠ `gen_compdb.py` 内部会"清理 → dry-run → 重建"三步：`scons -n` 在工程
> up-to-date 时一条命令都不打印，不清理就拿不到编译命令。全程约 1 分钟。

**③ 架构层面：这个成本值不值**

诚实说：**AC 层的收益与"是否真的会换 MCU"成正比。**

| 情况 | AC 层的价值 |
|---|---|
| 只做 CVM014x 一颗芯片、不改平台 | 收益接近 0，纯阅读负担 |
| 将来要移植到 S32K / TC3xx / RH850 | 收益巨大：`CanIf`/`CanTp`/`Dcm` 一行不改，只重写 `*Ac.c` |

既然这个工程是对标 AUTOSAR、按 AS 复刻的，**建议保留 AC 层**，用上面 ①② 抵消成本，
而不是拉平层次。真要拉平，代价是 `infras` 直接 include 厂商头，
M2 之后的 CanTp/Dcm 全部被绑死在这颗芯片上，那时候再拆代价更高。

## 已知缺口（待办，按优先级）

| # | 缺口 | 影响 | 计划 |
|---|---|---|---|
| **1** | ~~Bus-off 检测与恢复完全没有~~ → **M5 已解决检测与记录**；恢复完全依赖硬件 `BOFFREC=0` 自动恢复 | 检测、计数、现场快照、故障码落盘全部就绪。**软件重启控制器实测有害**（见「M5 的三个硬事实」②），故不做 | 真需要硬恢复时走 `NVIC_SystemReset()`（M6 的 EcuM） |
| 2 | `CanIf_MainFunction` / `_Fast` 未调用 | 包池为 0 时基本空转，当前无影响 | 打开包池时一并接 |
| 3 | `CANIF_RX_PACKET_POOL_SIZE > 0` 的"中断入池 + 主循环分发"未启用 | `Std_EnterCritical/ExitCritical` 目前被 `--gc-sections` 回收 | 报文变多、中断变重时再开 |
| 4 | ~~突发负载下的丢帧率未测~~ → **M14 已测**：9200 帧背靠背（2.3 s 满线）**0 丢帧**，ISR 每帧一次、无积压 | 500 kbps 满总线时不丢帧；瓶颈是总线本身，不是软件 | 若要再压，得换 CAN FD 或降低帧负载 |

### 缺口 1 的最终结论（M5 已完成，与原计划不同）

原计划写的四步是：开 `busoffIntEnable` → 加 `CANx_ORed_Handler` → 在
`CanIf_ControllerBusOff()` 里做 `STOPPED → 延时 → STARTED` → Kvaser 侧断 ACK 验收。

实际做完之后，**前两步照做，后两步推翻了**：

| 原计划 | 实际 |
|---|---|
| 开 `busoffIntEnable` + `errorIntEnable` | 只开 bus-off。`errorIntEnable` 每错一帧触发一次，干扰大的总线上会吃满 CPU，而错误类型在 bus-off 那一刻的快照里已经拿得到 |
| 加 `CANx_ORed_Handler` | ✅ 照做，并且**三个源都清**（`BOFFINT/TWRNINT/RWRNINT`），否则中断反复重入 |
| 恢复用 `STOPPED → STARTED` | ❌ **推翻**。实测重启后控制器永久不再发帧（`IDLE=1`、`TEC=0`、`Transmit` 仍返回 `E_OK`）。详见「M5 的三个硬事实」② |
| Kvaser 断 ACK 制造 bus-off | ❌ **不可行**。error passive 下 ACK 错误不累加 TEC，TEC 卡在 128。详见「M5 的三个硬事实」① |

现在实际做的是：**检测 + 计数 + 现场快照 + 故障码落盘 + 恢复告警**，
恢复交给硬件的 `BOFFREC`。这条结论有实测支撑，比原计划的推测可靠。

## M14 验收：通信矩阵承载能力

**这一轮做的不是"把 Foton 的 49 条报文抄进表里"，而是把承载它们的架构压到极限。**

理由：架构瓶颈（邮箱分组、掩码、软件过滤、中断压力、丢帧）**与具体 PGN 无关**。
用 20 条覆盖了各种边界特征的构造报文压测，等价于压测 49 条真实报文；
真实 DBC 到手后剩下的事只是填三张表。

### 报文集：20 条报文 / 23 个用例

| 类 | 用例 | 压的是什么 |
|---|---|---|
| 标准帧段 | `0x0A0~0x0A2`（10 ms）、`0x100~0x102`、`0x110` | 区间掩码合并、高频中断 |
| J1939 `0x18FFxx` | PGN FF00/FF01/FF02/FF03/FF05/FF06 | 段掩码、多 PGN 共用一个邮箱 |
| **同 PGN 多源地址** | PGN FF04 的 SA=01/02/05 | **一条表项收一组 SA**（真实矩阵里最常见） |
| J1939 `0x18FExx` | PGN FEA1/FEB1/FEC1/FEE0/FEF1 | 第二个段邮箱 |
| 边界 | 段内最大 PGN `0x18FFFF00` | 二分查找右边界 |
| 回归 | `0x321`（标准）、`0x7E0`（诊断） | 历史里程碑不被破坏 |

### 邮箱分配：15 个邮箱承载 20+ 条报文

| mb | 方向 | 覆盖范围 |
|----|------|----------|
| 0 / 3 / 4 / 11 / 13 | TX | 心跳 0x123、扩展帧、诊断响应、NM、Com |
| 1 | RX | `0x321`（精确） |
| **2** | RX | **`0x18FF0000` + 掩码 `0x1FFF0000`** → PGN 0xFF00~0xFFFF 全部 |
| **6** | RX | **`0x18FE0000` + 掩码 `0x1FFF0000`** → PGN 0xFE00~0xFEFF 全部 |
| 7 / 8 / 9 | RX | `0x0A0~0x0A7` / `0x100~0x107` / `0x110` |
| 5 / 12 / 14 | RX | 诊断请求、NM 0x500、Com 0x201 |

**49 条真实报文用这套结构也只要 6 个接收邮箱** —— 这就是"按段分组"而不是
"一条报文一个邮箱"的意义。

### 三层：硬件宽 → 软件窄 → 应用

```
硬件邮箱（段掩码，粗）     CanIf 过滤表（PGN 精确，细）      应用
mb2 收 0x18FFxxxx 全部  →  0x18FF0100 + 0x1FFFFF00  →  PDU 5（灯光）
                           0x18FF0200 + 0x1FFFFF00  →  PDU 16（门锁）
                           0x18FF0700（表里没有）     →  丢弃
```

**硬件不放行的帧连中断都不会有，软件层配得再对也没用**；反过来，
硬件放行但软件没配的帧（如 `0x18FF0700`）会被 CanIf 丢掉 —— 这一条是
`m8_check.py` 的负例，验的正是软件过滤层。

### 实测结果（`m14_check.py`，4 组判据全过）

```
轮 1：23 条用例逐条 5 帧 → 每条都是 mb 计数 5/5 且 PDU 计数 5/5
轮 2：9200 帧背靠背注入（2.3 s 满线，标准 3200 / 扩展 6000）
      接收 9200    丢失 0 帧（0.00%）
      邮箱中断 9212 次，每次平均 1.00 帧
      按邮箱分布 6 项、按 PDU 分布 17 项 —— 全部精确相等
```

> **"perISR ≈ 1.0" 是健康指标，不是问题指标。** 它表示每帧触发一次中断、
> ISR 在下一帧到达前就处理完了。只有 > 1.5 才说明帧在邮箱里排队、中断被推迟。

### 这一轮最重要的坑：掩码少了 18 位移位

**现象**：把标准帧段配到 mb7/8/9 后，mb8/mb9 一条都收不到，连带 mb12/mb14
（NM 0x500、Com 0x201）也哑了。而 mb1（0x321）完全正常。

**误判**：读到 `MCR[MAXMB]=96` 却只有 mb0~mb7 有计数，于是判断成
"这颗芯片只实现了 8 个邮箱"，还据此把整个邮箱表压到 0~7。

**推翻误判的证据**：更早的一版表里，mb15 配一模一样的掩码时**它自己是好的**
（只有它后面的 mb16/17 收不到）。mb15 可用 → "只有 8 个邮箱"不成立。

**根因**：`MESSAGE_BUFFER_ID_STD_ID_SHIFT = 18` —— FlexCAN 把 11 位标准 ID
存在 ID 字的 **bit[28:18]**，而 `FlexCanReg_SetRxIndividualMask()` 就一句
`obj->RXIMR[num] = mask;`，**原样写入、不移位**。传进去的 `0x7F8` 落在
bit[10:3]，而 ID 域那几位**恒为 0**：

```
硬件比对： (来帧ID & 0x7F8) == (邮箱ID & 0x7F8)
        →   0 == 0                    ← 恒成立 = 全收邮箱
```

FlexCAN 把一帧投给**编号最小的匹配邮箱**，所以 mb7 变成全收邮箱后，
排在它后面的所有标准帧都被它截走，**没有任何报错、没有任何异常标志**。

**修法**：硬件掩码左移 18 位（`0x7F8 << 18 = 0x1FE00000`），
软件层（`CanIf_Cfg.c`）仍用 11 位原值 —— **同一个语义、两个不同的数值**，
这是本工程唯一一处"硬件值 ≠ 软件值"的配置。

### 另外四个坑

| # | 现象 | 根因 | 修法 |
|---|------|------|------|
| ② | 段内最大用例一直 FAIL | 原来用 29 位极值 `0x1FFFFF00`，它 bit[28:16]=`0x1FFFF`，**不满足**硬件段掩码要求的 `0x18FF0`，压根进不了邮箱 | 改用段内最大 PGN `0x18FFFF00` |
| ③ | 压测刚跑就崩在 `send()` | Kvaser 溢出抛 `CANLIBOperationError`，它继承 `CanlibError(Exception)`，**不是** `can.CanError`；只捕 CanError 时重试形同不存在 | 单独捕获 CanlibError |
| ④ | 判据报 "ISR 效率 FAIL 1.00" | 判据写成 `per_isr >= 1.0`，方向反了 —— 1.00 在丢帧为 0 时是**最好**的状态 | 改 `<= 1.5` |
| ⑤ | M8 负例开始 FAIL、其余全过 | 负例用 `0x18FF0200`，而 M14 把 PGN FF02（门锁）正式接进表了，它**应该**收到 | 负例改 `0x18FF0700`（硬件放行、软件表没有） |

> 还有一个排查时踩的坑：**M9 脚本收尾会把 ECU 留在 `NO_COM`（总线睡眠）**，
> 紧接着跑 M8 会 10 项全 FAIL、连 `10 03` 都不应答 —— 那不是配置坏了，
> 是控制器已经停了。跑任何后续脚本前先复位。

### 命令与脚本

| 命令 | 作用 |
|------|------|
| `!k` | 打印接收计数：按通道总/ISR、**按邮箱**、**按 PDU（软件过滤后）** |
| `!K` | 清零上述全部计数 |
| `python tools/m14_check.py [--per-msg N] [--skip-round1]` | 压测（默认 100 → 2300 帧；`--per-msg 400` → 9200 帧） |

**为什么要按邮箱 + 按 PDU 两套计数**：只验一套时三类错全都看不出来 ——

| 现象 | 含义 |
|------|------|
| 邮箱涨、PDU 不涨 | CanIf 过滤表把帧丢了（canid/mask/顺序错） |
| 邮箱涨、PDU 涨在**别的项** | 过滤表区间重叠，被前一项截走 |
| 两套都涨但数值不等 | 同一条被多个邮箱投递（重复配置） |

## M15 验收：ADC 模块（as-master 没有这个模块，按它的三段式补）

### 先说清"1:1 移植"的边界

核对 as-master 的 MCAL，只有 **六个模块**：

| as-master | 本工程 |
|---|---|
| `Can` `Dio` `Port` | ✅ 已移植（AS 原样 + CVM0146 的 AC） |
| `Eep` `Fls` | ❌ 未移植（用厂商 FEE/NvM 引擎替代，M4 已定版） |
| `Lin` | ❌ 本项目不用 LIN |
| **`Adc`** / **`I2c`** | **as-master 里根本没有** |

所以"1:1"能做到的是**结构 1:1、命名 1:1**，接口必须按 AUTOSAR 标准补
（`SWS_ADCDriver` / `SWS_I2CDriver` 手册就在 `doc/` 里）。
这次补的是 ADC；I2C 因实际板子未到，暂停。

### 三段式结构（与 Port/Dio 逐字同构）

```
infras/include/Adc.h             标准 API / 类型 / 错误码（0x0A~0x1C 核对了原文）
infras/mcal/Adc/Adc_Priv.h       配置结构 + AdcAc_* 边界   ← 分层分界线
infras/mcal/Adc/Adc.c            DET 校验 + 查表 + 转发，**零寄存器**
app/platform/cvm0146/src/AdcAc.c ADC0/ADC1 + PDB0/PDB1 + TRGMUX
app/platform/cvm0146/src/config/Adc_Cfg.{c,h}
```

判断分层有没有破的硬标准：**`Adc.c` 里不出现 `ADC0` / `SC1` / `PDB` 任何一个词**。

`Adc_Init` 已归位到 `EcuM_Cfg.c` 的 `DriverInitListZero`（Port → Can → Adc），
它是表里**唯一带 config 参数**的项 —— 标准 `Adc_Init()` 要配置指针，
而 Port/Can 都是从自己的 `Xxx_Cfg.c` 取全局实例。

### 实测（`!j`，连读三次一致）

```
[adc] g0: 1921(1548mV) 2252(1814mV)   ← ADC0：POT1(ch12) + VBAT(ch13)，双通道
[adc] g1: 2241(1805mV)                ← ADC1：POT2(ch2)，单通道
```

一次 `TrgMuxDrv_GenSWTrigger()` 同时触发 PDB0 和 PDB1，两个 ADC 各自扫完自己的组。

| 信号源 | 引脚 | 通道 | 出处 |
|---|---|---|---|
| AN_POT_1 | PTC14 | ADC0_SE12 | 《CVM0146 开发板快速入门》表 2（p7） |
| AN_POT_2 | PTD2 | ADC1_SE2 | 同上 |
| I_AN_VBAT | PTC15 | ADC0_SE13 | 同上，分压比 0.23 |

> 附带结论：**ADC 引脚复位默认就是模拟功能，不需要在 `Port_Cfg.c` 里配**。
> 官方 `adc_pdb_trigger` 例程同样一行引脚配置都没有。

### 六个坑，全是"不报错只不工作"

| # | 现象 | 根因 | 修法 |
|---|------|------|------|
| ① | `!j` 永远 `timeout, status=1 (BUSY)` | **ADC0/PDB0 的时钟 `Mcu_Init()` 里不开**。`AdcDrv_Configure()` 写寄存器返回成功，但模块根本没跑 | `ClockDrv_ConfigureClock(CLOCKDRV_ADCn, PLL, div=4)` + `CLOCKDRV_PDBn` 开 gating |
| ② | 开了时钟仍 timeout | **软件触发必须经 TRGMUX**。单独 `PdbDrv_SwtrigCmd()` 不走 —— `trgInSel` 未选通时 SWTRIG 不启动计数 | `TrgMuxDrv_Configure({SIM_SW_TRIG → PDBn_TRG_IN})` + `TrgMuxDrv_GenSWTrigger()` |
| ③ | 配置读回全对，PDB 就是不动 | `PdbDrv_Configure()` **不调** `PdbDrv_LoadCmd()`，配置只在缓冲区，要置 `LDOK` 才加载 | Configure 后显式 `PdbDrv_LoadCmd()` |
| ④ | 读数在 554~677 之间乱跳 | 通道号填的是 PTA0（悬空），不是电位器 | 按表 2 填 `ADC0_SE12`。悬空漂、接上稳，是最直观的判据 |
| ⑤ | 一直 BUSY，但单通道曾经是好的 | **槽位必须在 `AdcDrv_Configure()` 里一次定死**。使能后再用 `AdcDrv_ConfigureChn()` 改**不保证生效** | 把槽位写进 `chnCfg[]`，运行期只触发不改通道 |
| ⑥ | **单通道组正常、双通道组 timeout** | 多通道要 PDB 预触发**背靠背**：`preTrgCfg.mode[0][1..n-1] = PDBDRV_PRETRG_BB_MODE`。只配 `mode[0][0]` 时一次触发只转第一个通道 | 按通道数补齐 BB_MODE |

> ⑥ 最值钱：它的表现是"ADC1 单通道好好的、ADC0 双通道死的"，
> 极易被误判成"多通道不可用"或"ADC0 坏了"。实际上 ADC0 一点问题没有。

### 两个概念别混：槽位 ≠ 通道

| 概念 | 含义 | 谁决定 |
|---|---|---|
| **槽位** | SC1A/SC1B… 的序号，决定**结果进哪个 Rn** | 组内通道的**顺序** |
| **通道** | ADCH 域，决定**采样哪个引脚** | 配置表 `hwChannel` |

`AdcDrv_ConfigureChn(obj, chn, state)` 里 `chn` 是槽位、`state` 才是 ADCH。
搞反了读到的是"另一个槽位上一次的值"，而不是报错。

### 能力边界

| 能力 | 状态 |
|---|---|
| ADC0 / ADC1 双单元 | ✅ 一个 `GenSWTrigger` 同时触发两个 PDB |
| 单组多通道（一次触发扫全组） | ✅ 槽位 = 组内序号 |
| 组内跨单元 | ❌ Init 阶段显式拒绝 |
| **一个单元多个组** | ❌ 显式拒绝（槽位重叠，后配的覆盖先配的） |

> 最后一条对 MUX 有直接影响：**两个 RS2260 的 COM 都接 ADC0 时，不能做成两个组**，
> 得合成一个组（组内多通道），或者一个接 ADC0、一个接 ADC1。
> 这个约束现在就在代码里挡着，不会到跑起来才发现。

### 已知缺口

- **采样时间没有标定**：`samplingTime = 20` 对开发板的电位器（低阻）够用，
  实测抖动只有 ±1 LSB；但接 RS2260（Ron ≈ 105 Ω + 分压网络）后源阻抗变高，
  **必须重新扫一遍找收敛点**
- `VDDA` 是否为 3.3 V 未验证：`VBAT` 读数 1814 mV，按分压比 0.23 反推 `VIN ≈ 7.9 V`，
  与实际供电是否吻合待确认。把电位器拧到两端，读数应压到 `0` / `4095`

## M18 验收：PWM 模块（as-master 没有，按它的三段式补）

### 为什么必须先补它

BCM 看着是"开关量控制器"，实际有**明确的 PWM 需求**：

| 负载 | 频率 | 依据 |
|------|------|------|
| 顶灯渐亮/渐灭 | **100 Hz**，占空比 20%→90%，2.5 s ±0.1 s | 功能规范 `IL001`/`IL002` 明文 |
| 鼓风机调速（PWM + RC 模拟 0~12 V） | 20 kHz 量级 | 框图 `Blower_Analog_Out`，纹波要小 |
| 水泵 PWM | 2 Hz ~ 2 kHz（推荐 200 Hz） | 框图注 |
| 三通比例阀 | 由阀厂给定 | 框图注 |

`IL001` 的时序要求是"2.5 秒内线性从 20% 升到 90%"，精度 ±0.1 s（4%）——
这必须靠定时改占空比实现，没有 PWM 模块就只能干瞪眼。

### 三段式结构（与 Adc 逐字同构）

```
infras/include/Pwm.h             标准 API（SWS_PWM R25-11，错误码 0x10~0x19 核对了原文）
infras/mcal/Pwm/Pwm_Priv.h       配置结构 + PwmAc_* 边界
infras/mcal/Pwm/Pwm.c            DET 校验 + 查表转发，**零寄存器**
app/platform/cvm0146/src/PwmAc.c PwmLite0~4 + 引脚复用 + 波形计算
app/platform/cvm0146/src/config/Pwm_Cfg.{c,h}
```

硬标准：**`Pwm.c` 里不出现 `PWMLITE` / `pwmLiteDrv` / `PINSDRV` 任何一个词**。

### 实测（寄存器读数，不是"看着像"）

```
[pwm] mod0 period=600000 (100Hz, timer=60000000Hz)
[pwm] ch0 -> PTD0   100Hz  duty=0/32768
[pwm] ch1 -> PTD1   100Hz  duty=16384/32768
[pwm] ch2 -> PTE15  100Hz  duty=8192/32768
[pwm] ch3 -> PTE16  100Hz  duty=24576/32768
[pwm] init done: 4 of 4 channels active
```

用 J-Link 直接读 `PWMLITE0`（基址 `0x40058000`）确认配置进了硬件：

```
40058000: CTRL=1  PRD=0x000927C0(=600000)  STOP=0  SYNC=0
40058010: CH0.CTRL=5  THR0=1  THR1=0x927C1
40058020: CH1.CTRL=6  THR0=1  THR1=0x493E1(=300001)
```

| 项 | 期望 | 实测 | 判断 |
|----|------|------|------|
| `PRD` | 60 MHz / 100 Hz = 600000 | 600000 | ✅ |
| `CH0.CTRL` | `0b0101`（两阈值都 LOW → 恒低，对应 0%） | 5 | ✅ |
| `CH1.CTRL` | `0b0110`（HIGH→LOW，正极性调制） | 6 | ✅ |
| `CH1.THR1` | 600000 × 50% = 300000 | 300001 | ✅（SDK 内部 +1） |

> **为什么用寄存器而不是看波形**：开发板上 `PTD0/PTE15/PTE16` 接 RGB 灯，
> `!l` 的演示肉眼能看到颜色变化，但"灯亮了"不等于"频率对、占空比精确"。
> 寄存器读数能同时验证**周期、阈值、behavior 编码**三件事，而且可重复。

### 五个坑

| # | 现象 | 根因 | 修法 |
|---|------|------|------|
| ① | 100 Hz 变成 5896 Hz，无报错 | `period = 600000` **远超 uint16**。用 16 位会截成 `600000 & 0xFFFF = 10176` | `Pwm_PeriodType` 用 **uint32** |
| ② | 引脚配了但没有波形 | **`Mcu_Init()` 不开 PwmLite 时钟门控**，只存了寄存器指针 | 显式 `ClockDrv_ConfigureClock(CLOCKDRV_PWMLITEn)`（与 ADC 同一个坑） |
| ③ | 配 PWM 之后 **CAN 不通了** | `PWM4~7` 与 `PTE10/PTE11`（CAN3）、`PTE4/PTE5`（CAN0）复用。配成 ALT6 就把 CAN 引脚改掉了 | `s_padMap` 里标 `usable=0`，`Init` 时**拒绝**并打印 |
| ④ | 引脚复用值不对 | `pin_mux.xlsx` 的 ALT 列编号**容易数错一位**（我按表算出 ALT5，例程是 ALT6） | **以官方例程为准**，并在注释里写明理由 |
| ⑤ | 生产构建里"同实例频率冲突"检查消失了 | 把检查塞进了 `DET_VALIDATE`，而 `DET_CFG_ENABLE == 0` 时它是**空宏** | 崩溃/静默错误类的检查必须独立于 DET 开关 |

① 最值钱：它的症状是"频率不对"而不是"不工作"，不用示波器根本发现不了，
而且会把排查方向引向"分频系数算错了"。

### 硬件约束：同实例必须同频

`PwmLite` 的周期是**模块级**的（`PwmLiteDrv_ModuleConfig()` 只有一个 `period`），
不是通道级。同一个实例里配两个不同频率，硬件做不到 —— 后配的覆盖先配的，
两个通道都变成后一个频率。

`Pwm_Init()` 里 `Pwm_CheckPeriodConsistency()` 直接拒绝这种配置。
所以本工程的 4 个通道都在 PwmLite0、都是 100 Hz，只在占空比上区分。

真实项目里不同频率要**分到不同实例**：

| 负载 | 实例 | 频率 |
|------|------|------|
| 顶灯 | PwmLite0 | 100 Hz |
| 鼓风机 | PwmLite1 | 20 kHz |
| 水泵 | PwmLite2 | 200 Hz |

### 命令

| 命令 | 作用 |
|------|------|
| `!l` | 演示：全灭 → ch0 渐亮 → 绿渐亮 → 蓝渐亮 → RGB 50% → 复位（约 4.4 s，RGB 灯肉眼可见） |
| `!L` | 恢复配置表初值（ch0=0% ch1=50% ch2=25% ch3=75%） |

### 能力边界

| 能力 | 状态 |
|---|---|
| 单路独立 PWM 输出 | ✅ 8 个物理引脚（PAD0~7），其中 **PAD0~3 可用**（PAD4~7 与 CAN 冲突） |
| 运行期改占空比 | ✅ 周期末生效，无尖峰 |
| 运行期改周期 | ✅ 但**同实例所有通道一起变**（硬件限制） |
| 0% / 100% 静态电平 | ✅ 走独立分支，不产生尖峰 |
| 边沿中断通知 | ❌ 空实现（BCM 无此需求） |
| 互补输出 / 死区 | ❌ **本模块不做** —— 风门电机全桥要靠 `Mft` 的 PWM 模式 |

> **风门电机的全桥驱动不在本模块范围**。框图里 3 个风门电机（模式/冷暖/内外循环）
> 都是"两个半桥组成全桥"，需要互补 + 死区，那是 `Mft` 的能力。
> 参考例程 `examples/CVM0146/driver_examples/mft_pwm_3ph_full_bridge`。

## M19 验收：CAN1 接入 Foton 真实通信矩阵

### 先纠正一条我自己的错判

M17 结束时我写过：

> 生成的 40 条 PDU **hoh 全是 0**……AS 模型是「一个 hoh 一个硬件接收对象」，
> 但 **FlexCAN 一个邮箱只有一个掩码**，34 条不同 PGN 配 hoh=0 收不了。
> 方案：加 `hohGroups`，写 `gen_hoh.py` 按 `id & mask` 分配 hoh。

**这个判断是错的，`hohGroups` 那套方案根本不需要。**

查 `CanIf.c` 才发现：`hoh` 只在**发送**路径用（`Can_Write(txPdu->hoh, ...)`）。
接收路径 `CanIf_RxDispatch()` 只用 `canid` 和 `mask` 做二分查找，**完全不看 hoh**：

```c
/* CanIf.c:104 附近 —— 二分查找只用 canid / mask */
canid = Mailbox->CanId & CAN_CANID_MASK;
while ((NULL == rxPdu) && (l <= h)) {
    m = l + ((h - l) >> 1);
    var = &config->rxPdus[m];
    if (var->canid == (canid & var->mask)) { rxPdu = var; }
    ...
}
```

所以 RX 的 `hoh` 是**死字段**，填 0 不影响任何行为。
真正管 RX 分组的只有两处：`Can_Cfg.c` 的邮箱表（硬件）和 `CanIf_Cfg.c` 的过滤表（软件）。

> 这条教训值得单独记：**"某个字段看起来该起作用"和"它真的起作用"是两件事**。
> 上一轮我没查调用点就下了结论，白设计了一套方案。

### CAN0 / CAN1 的分工

接入真实矩阵会把历史回归全部打破（PDU 编号、canid 全变），所以按通道分开：

| 通道 | 角色 | 内容 |
|---|---|---|
| **CAN0** | 开发测试通道 | M1~M14 的构造报文、诊断 0x7E0/0x7E8、NM 0x500、Com 0x200/0x201 —— **一行没动** |
| **CAN1** | 实车整车网 | 34 条 RX（按 PF 分 7 组）+ 6 条 TX + 保留 0x124/0x322 作对照物 |

这样 261 项历史回归**全部继续有效**，同时真实矩阵可以独立验证。

### 34 条 RX → 7 个邮箱（按 PF 分组）

矩阵里 34 条报文的 **PGN 全不相同**（PS 字节各异），一条一个邮箱要 34 个。
按 **PF（bit23:16）** 分组只要 7 个：

| mb | PF | 覆盖 | 条数 |
|----|----|------|------|
| 8 | 0xEB | TP.DT（传输协议数据） | 1 |
| 9 | 0xEC | TP.CM（传输协议连接管理） | 1 |
| 10 | 0xEE | ACL | 1 |
| 11 | 0xF0 | EEC1/EEC3/ERC1/ERC3/EBC1/ETC2/CRASH | 6 |
| 12 | 0xFD | EOI/DLCC1/EBC5 | 3 |
| 13 | 0xFE | CCVS/CCVS1/VDC1/AMB/TCO1/DM1_TPMS/TIRE_COND/ETC5 | 8 |
| 14 | 0xFF | ESCL1/ESCLM/PEPS1/PEPS2/ID1~3/DW/EEC3/ECC2/VCU4/ESCL_NM | 14 |

软件层（CanIf）再用 `0x1FFFFFFF` **精确匹配**整条 29 位 ID ——
矩阵里同 PGN 不同 SA（如 0xFEF1 有 SA=0x00 和 0x21）是**两条独立报文**，所以不能屏蔽 SA。

### 掩码必须屏蔽优先级：`0x00FF0000` 而不是 `0x1FFF0000`

这是本轮最隐蔽的一条。矩阵里同一条报文的优先级从 3 到 6 都有：

```
0x0CF00400  P=3   EEC1
0x0CFDCC21  P=3   BCM_OEL（我们要发的）
0x18FEF100  P=6   CCVS1
0x98FFB04D  P=6   ESCL1
```

`0x1FFF0000` 保留 bit28:26（优先级），P 不一致的帧**会被硬件直接丢掉**，
而且**没有任何报错** —— 症状是"某些 PGN 收得到、某些收不到"。

改用 `0x00FF0000`（只匹配 EDP+PF，屏蔽 P/R/DP）：

```
来帧 0x0CF00400 & 0x00FF0000 = 0x00F00000
邮箱 0x18F00000 & 0x00FF0000 = 0x00F00000   → 命中 ✓
```

顺带对 DP=1 的 PGN（`0x1xxxxx`）也免疫 —— 硬件宽、软件窄。

### 实测（`m19_check.py`）

```
逐条注入 5 帧 × 34 条：
  EEC1_ELECTRONIC_ENGINE_CONTROLLER_1   PF=0xF0 mb11 pdu23  tx=5  rx=5/5   ok
  ESCL1                                 PF=0xFF mb14 pdu26  tx=5  rx=5/5   ok
  ...
  TP_CM                                 PF=0xEC mb9  pdu55  tx=5  rx=5/5   ok
PASS 34 / 34   （邮箱计数与 PDU 计数全部精确相等）

加压 100 帧 × 34 条 = 3400 帧：PASS 34 / 34，0 丢帧
```

TX 侧（Kvaser 在 CAN1 上收）：

```
!M   tx 0x18FE4021 LCSF  tag=0xA1  ok
     tx 0x18FF0C21 CTRL  tag=0xA2  ok
     tx 0x0CFDCC21 OEL   tag=0xA3  ok
     tx 0x18FDCD21 OWW   tag=0xA4  ok
     tx 0x18FE4E21 DOOR  tag=0xA5  ok
     tx 0x18FECA21 DM1   tag=0xA6  ok
     6 / 6 sent

Kvaser 收到：6/6，首字节 tag 全部匹配
```

### 生成器怎么用：注入而不是整体替换

`CanIf_Cfg.c` 里有两类内容：

| 部分 | 来源 | 变动频率 |
|---|---|---|
| CAN0（M1~M14 的测试/诊断/NM/Com） | 手写，261 项回归依赖 | 几乎不变 |
| CAN1（34 条真实矩阵） | 通信矩阵 | 每次矩阵更新 |

整体替换要把 CAN0 的 23 条也拖进 JSON —— 等于给已完成的验证付二次成本，
而且 PDU 编号一变，M2/M8/M14 三个脚本的期望值全要改。

所以 `tools/sync_canif.py` 做**标记注入**：

```sh
python tools/sync_canif.py            # 跑生成器 + 注入
python tools/sync_canif.py --dry-run  # 只看不写
```

脚本干三件手工容易做错的事：

1. **编号偏移**：CAN0 已占 0~22，CAN1 从 **23** 开始，`PduIdType` 全局唯一
2. **hoh 回填**：生成器给的恒为 0，按 PF 段回填成真实邮箱号（不然读代码的人会以为"34 条共用 mb0"）
3. **格式**：生成器输出 `0xcf00400`（小写无前导零）+ 2 空格缩进，转成 `0x0CF00400u` + Tab

### 三个坑

| # | 现象 | 根因 | 修法 |
|---|------|------|------|
| ① | 34 条一条都收不到 | 沿用 CAN0 的 `0x1FFF0000` 掩码，**带优先级**；矩阵里 P 从 3 到 6 都有 | 改 `0x00FF0000` |
| ② | mb1 计数在涨，但 PDU 计数是 0 | CAN1 过滤表被整表换成 34 条真实报文，**0x322 不在里面了** | 硬件收到 ≠ 软件收到；M2 用例改成真实报文 |
| ③ | M14 压测全 FAIL、连 mb 计数都是 0 | **M8 脚本跑完把 CAN0 留在 OFFLINE/STOPPED**，不是配置坏 | 跑后续脚本前先复位 |

② 是这轮唯一"看起来像 bug 其实是设计"的一条：它正好证明了分层 ——
**硬件放行由邮箱掩码决定，软件放行由 CanIf 表决定，两层各自独立**。

### 命令

| 命令 | 作用 |
|---|---|
| `!M` | 发一轮 CAN1 真实矩阵的 6 条报文（首字节 0xA1~0xA6，便于 Kvaser 侧区分） |
| `!k` | 接收计数：按通道总/ISR、按邮箱、按 PDU |

### 能力边界

| 能力 | 状态 |
|---|---|
| CAN1 收 34 条真实报文 | ✅ 3400 帧 0 丢帧 |
| CAN1 发 6 条真实报文 | ✅ Kvaser 全部收到，tag 匹配 |
| **TP_CM / TP_DT 走信号层** | ❌ **当前当普通 PDU 交给 App 打印**。J1939 多帧传输要等 `J1939Tp` 移植后改 `up` |
| 34 条接 Com（信号级） | ❌ 下一步：`Com.json` 加 CAN1 网络，372 个信号自动生成 |
| SA 可变（地址声明） | ❌ 当前精确匹配具体 SA。实车若走动态地址声明需要改回 `0x1FFFFF00` |

> **TP 报文这一条要特别说明**：`0x9CEBFF21`(PF=0xEB) 和 `0x9CECFF21`(PF=0xEC)
> 是 J1939 的传输协议，不该被当成信号 PDU。现在硬件收（mb8/mb9）、
> CanIf 投给 App 仅打印，**等 `J1939Tp` 移植后改成投给它**。

## 下一步：真低功耗（M16）

**bootloader 已在 M13 完成**（见上一章）。低功耗按用户要求往后放，框架在 M12 已经通了，但**还没省电**。
真正落地要做的四步：

| 步 | 内容 | 风险 |
|---|---|---|
| ① | **PTE4（CAN0_RX）端口唤醒**：睡前从 ALT5 切成 GPIO 输入 + 双边沿中断，醒来切回 | 中。切错会导致收不到报文 |
| ② | 停 `SysTick`，改由 **LPTMR/LPIT** 定时兜底 + 端口唤醒 | **高**。配错会睡死，只能断电恢复 |
| ③ | `PowerDrv_SetPowerMode(STANDBY_WITH_CPU_RETENTION)` 替代 STOP | 高。需要确认 RAM 保持与外设重初始化 |
| ④ | 电流实测（睡眠前 / 睡眠中 / 唤醒后） | 低。只有这一步做完，才能说"低功耗做完了" |

> **顺序不能跳。** 必须先有可靠的唤醒源（①），才敢停 tick（②）；
> 必须先确认醒得回来，才敢进 Standby（③）。反过来做就是赌板子不会睡死。

**还欠的技术债**（都在 README 里标了 `@warning`）：

- `CAN_USE_CTRL_AC_GLOBAL` 未定义 → `CanAc_GlobalInit` 是死代码
- `Com_SendSignal` 无 shadow buffer（8 字节 / 10 ms / 单字节写在 M4 上原子，
  加 16/32 位信号时要重新评估，AUTOSAR 的正解是**排他区**不是双缓冲）
- CAN 侧包池（「已知缺口」第 2~3 条）—— 第 4 条丢帧率已由 M14 实测为 0，
  即当前"不开包池"的选择在满负载下也成立；等报文多到中断里做不完运算时再评估

> M3 已完成，`m3_check.py` 17 项全过；接线细节见上面「一条 ISO-TP 诊断链路要过 4 条 PduR 路径」。

> M2b（CAN1）已完成，不再单列。做法记录在下面这张表里，加第三路（CAN2：PTE24/PTE25/PTE23）
> 时照抄即可。

### 加一路 CAN 要改五个地方（M2b 实测清单）

| # | 文件 | 改什么 |
|---|---|---|
| 1 | `Port_Cfg.h/.c` | 引脚表 `PORT_CFG_NUM_PINS` +2/3，加 RX/TX（MUX 值查 PinMux 表）与 STB（GPIO=ALT1） |
| 2 | `Dio_Cfg.h/.c` | `DIO_CHANNEL_CANx_STB`，`DIO_CFG_NUM_CHANNELS` +1 |
| 3 | `Can_Cfg.h/.c` | `CAN_CFG_NUM_CHANNELS` +1、通道结构体数组 +1、`Can_HwIns2ChlMap` +1、邮箱表 +1 张、`CanHw_MsgTables` +1 行、HTH 表 +1 行 |
| 4 | `CanAc.c` | `CANx_ORed_0_15_MB_Handler` + `IrqDrv_EnableIrq(CANx_ORed_0_15_MB_IRQn)` |
| 5 | `CanIf_Cfg.h/.c` | `CANIF_CHL_CANx`、`CANIF_RX_*`/`CANIF_TX_*` 编号（TX 必须 0..N-1 连续）、`CanIf_RxPdus_CANx[]`、`CanIf_TxPdus[]` +1、`CanIf_CtrlConfigs[]` +1 |

**应用层不用改** —— 这是这套分层唯一值得炫耀的地方：
`main.c` 里只是多了一个 `CANIF_TX_CANx` 枚举值，逻辑没变。
（本次因为要"每个通道发不同内容"才动了 `main.c`，否则连它都不用碰。）

## M2 落地的三个非显然点

这三条都是这次实际撞出来的，写下来省下一次排查：

1. **中间层缺 `SConscript` 会静默跳过整棵子树**。`infras/communication/` 建了目录
   却没写 `SConscript`，`Glob("*/SConscript")` 就匹配不到，`CanIf` 类根本没注册；
   症状不是"编译失败"，而是链接期 `cannot find -lCanIf` ——
   库被当成**外部库**去找，而不是当成自己的模块。
2. **`CanIf_RxIndication` 不在 `CanIf.h` 里，在 `CanIf_Can.h`**。前者是"CanIf 提供给
   上层的 API"，后者是"Can 提供给 CanIf 的上行接口"。写错头文件得到的是
   `implicit declaration`（返回 int、参数按默认提升），ARM 上调用约定与 `void` 不同，
   属于真实隐患而非纯风格问题。
3. **`CanIf_SetPduMode(ONLINE)` 是发送的开关**。`CanIf_Init()` 把 `PduMode` 置
   `CANIF_OFFLINE`，`CanIf_Transmit()` 里 `if (CANIF_ONLINE == context->PduMode)`
   不成立就直接返回 `E_NOT_OK`。漏了这一句的症状是"初始化全成功，一帧都发不出去"。


## M-Shell：命令行解释器引入（Bcm_Frame `sh` → 本项目）

目标：把命令从 `main.c` 的巨型单字符 switch 里拆出来，做成**按模块独立编译**的
`xxx_cmd.c`，并给上位机一个统一的串口交互层。

### 结构

```
infras/shell/            sh 中间件（4,054 行，Bcm_Frame 原样移植 + 三处适配）
  sh_port.h              替代 Bcm_Frame 的 hal_comm.h（只保留 3 个状态码 + 错误结构）
  sh_compat.c            hal_error_count/assert_count/get_last 的弱默认实现
app/app/src/sh_app.c     UART2 绑定 + `!x` 旧命令兼容桥
app/app/src/cmd/         应用侧命令文件（board_cmd.c 为样板）
infras/libraries/lwrb/   TX/RX 环形缓冲（sh_io.c 与平台 RX 中断共用）
tools/shell.py           上位机标准客户端（提示符切帧 / 自动找口 / ANSI 清洗）
```

命令注册用**链接器段**：`SH_EXPORT_CMD` 把描述符放进 `hal_sh_cmd` 段，
`sh_task` 遍历 `__start_hal_sh_cmd..__stop_hal_sh_cmd`。不参与编译的模块
自然没有命令，`help` 里看不到、编译链接都不报错 —— 这就是"不用就不编译"。

### 五条实测踩出来的坑

1. **GCC 下段会被 `--gc-sections` 回收，且 orphan 放置会撞 m_interrupts**。
   首次链接报 `section 'hal_sh_cmd' will not fit in region 'm_interrupts'`。
   解决：在 `CVM0146_app_a/b.ld` 的 `.text` 里显式 `KEEP(*(hal_sh_cmd))`，
   并**手写** `__start_/__stop_hal_sh_cmd` 两个符号（收进 .text 后 ld 不再自动生成）。
2. **轮询式 `Platform_GetChar` 会丢字节**。主循环里 NvM 擦除/突发接收占用几毫秒，
   期间到 UART 的字节直接丢；症状是"连续发 `*IDN?\n`，板上只收到 `*IDN`，
   命令不执行也不报错"。改为 `UART2_RxTx_Handler` 中断 + 512 字节 lwrb 环。
3. **多个输出者会互相插进同一行**（心跳 `alive #N` 插在命令输出中间）。
   改为控制台汇：`Platform_Puts/Platform_Printf` 逐字符交给 `sh_putch` 入 TX 环；
   `Platform_PutChar` 保持**原始直写**，它是 shell 排空环的通道，再过滤会递归。
4. **旧验收脚本发的是不带回车的 `!k`**，而 shell 按行分发（需回车）。
   `sh_app.c` 加兼容桥：读到 `!` 吞掉、把紧随一个字符交给旧 `CmdExec`。
   ⇒ 旧脚本零改动，新命令并行可用；迁完后桥与 `CmdExec` 一起删。
5. **`__weak` 是 IAR/ARMCC 语法**，GCC 报 `expected ';' before 'int'`；
   改 `__attribute__((weak))`。

### 验收记录（2026-11-12）

| 项 | 结果 |
|---|---|
| `help` | 列出 13 条内建 + 1 条应用命令（`board`） |
| `board` / `*IDN?` / `*SYST?` / `echo a b` | 正常，输出带 `<+0,` SCPI 应答头 |
| 整行快速发送（模拟脚本） | 不丢字节 |
| 旧命令 `!k`（不带回车）连发 | 正常，走兼容桥 |
| 回归 M2 | 39/39 |
| 回归 M19 | 34/34 |
| 镜像体积 | App 200,684 B（+17 KB）· Boot 56,640 B（+1.8 KB，64K 区仍余 8.8K） |

### 命令迁移进度（2026-11-12 第二批）

| 模块 | 新命令 | 旧入口 | 状态 |
|---|---|---|---|
| ADC（M15） | `adc [group]` | `!j` 已删 | ✅ 已迁移并验证 |
| PWM（M18） | `pwm [reset \| <ch> <pct>]` | `!l/!L` 已删 | ✅ 已迁移并验证 |
| EcuM（M11/M12） | `ecum [run\|postrun\|sleep]` | `!u/!U/!q/!z` 保留（转调 cmd 实现） | ✅ 逻辑已迁移，M11 18/18、M12 15/15 |
| NM（M9） | `nm [req\|rel\|passive]` | `!a/!R/!A/!m` 保留（转调 cmd 实现） | ✅ 逻辑已迁移，M9 26/26 |
| 存储（M4） | `nvm [dump\|writeall\|touch\|stress\|illegal]` | `!d/!c/!w/!x/!p` 保留（转调） | ✅ 逻辑迁入 `storage_app.c`，M4 23/23 |
| Com（M10） | `com [sig\|group]` | `!v/!y` 保留（转调） | ✅ 信号层整体迁入 `com_app.c`，M10 22/22 |
| CAN 控制/计数（M2/M14/M19） | `can [pdu\|ctrl\|trcv\|counters\|regs\|burst\|matrix]` | `!o…!M` 保留（转调 `CanTest_CmdExec`） | ✅ 整块迁入 `can_test.c`，M2 39/39、M14 全过、M19 34/34 |
| DTC（M5） | `dtc [dump\|clear\|inject]` | `!b/!B/!i` 保留（同路径） | ✅ 复用 `CanTest_CmdExec`，M5 24/24 |

**main.c 从 2215 行降到 435 行**（命令、CAN 测试、存储、信号层全部迁出）。

| 文件 | 行数 | 职责 |
|---|---|---|
| `main.c` | 435 | 启动序列 + 主循环调度 + Det 钩子 |
| `can_test.c` | 884 | CAN 周期发送/接收统计/总线故障/旧命令分发 |
| `storage_app.c` | 390 | 存储初始化（EcuM 表）+ 验收实现 |
| `com_app.c` | 174 | 信号层状态 + ComApp_Tick |
| `cmd/*.c` | 900 | 8 个命令文件（adc/board/can/com/dtc/ecum/nm/nvm/pwm） |

迁移方式：逻辑搬进 `cmd/xxx_cmd.c`，旧 `!x` 分支改为调用 `cmd_api.h` 里声明的包装函数
（脚本零改动）；脚本切到新命令后再删旧分支。

### JSON 配置化（2026-11-12 第三批）

`config/Shell/Shell.json` → `tools/generator/Shell.py` → `GEN/Shell_Cfg.h`：

| 字段 | 作用 |
|---|---|
| `boardName` / `version` | `*IDN?` 与横幅 |
| `prompt` / `defaultMode` | 提示符、上电模式（manual/auto） |
| `lineMax` / `maxArgs` / `txRing` / `printBuf` / `historyDepth` / `ctxPool` | 容量（`sh_cfg.h` 里每项都有 `#ifndef` 守卫，生成值优先） |
| **`disabledCmds`** | 不参与编译的命令名（如 `["pwm"]`） |

`disabledCmds` 的实现：app SConscript 读 JSON → 追加 `-DSH_DISABLE_CMD_<NAME>`，
命令文件整体 `#if !defined(...)` —— 关掉的命令**零 flash 残留**，`help` 里自然消失。
实测：`["pwm"]` 时 `pwm` 返回 `<-1, cmd not exist`、`help` 不列出；改回 `[]` 恢复。

⚠️ **不要用生成头定义这个开关**：SCons 在 variant_dir 下对生成头的依赖追踪不可靠
（实测改 JSON 不触发重编，需要手删 `.o`）；`CPPDEFINES` 变化一定会重编。

JSON 编辑器：`schema.json` 已增加 `Shell` 条目（15 个模块），`Shell.json` 通过
schema 校验，可直接在编辑器里改参数与命令开关。

### 兼容桥已删除（2026-11-12 第四批）

- 11 个验收脚本统一加 `CMD_MAP` + `xlate()`：旧 `!x` 字符串翻译成新命令并补换行，
  调用点零改动；`!k` 现在直接回 `<-1, cmd not exist`
- `sh_app.c` 的 `!` 拦截、`App_LegacyCmdExec`、`CanTest_CmdExec` 全部删除
- DTC 清/注入拆成 `Fault_ClearDtc()` / `Fault_InjectBusOff()`（与 UDS 同路径）
- M0 回显断言修正：shell 行编辑会插 ANSI 重绘序列，比对前先剥掉

全量回归：M0 26/26、M2 39/39、M4 23/23、M5 24/24、M6 23/23、M9 26/26、
M10 22/22、M11 18/18、M12 15/15、M14 全过、M19 34/34。

## M20 板级抽象层（第一步：板级身份/资源表）

`config/Board/Board.json` → `tools/generator/Board.py` → `GEN/Board_Cfg.h/.c`：
板名、MCU、内核时钟、控制台、CAN 实例数与速率、ADC 组数、PWM 频率/通道数，
外加 `io`（HSD/LSD/H 桥/扩展芯片，板子定型后填）。

`board` 命令实测输出：

```
<+0, board=CVM0146-EVK (CVM0146FMLQ) slot=A build=Nov 12 2026 13:10:23
     core=120MHz console=UART2/115200 can=2 pwm=4ch@100Hz adcGroups=2 shell=sh-1.0.0
```

**实车板到来时**：新建一份 Board.json（改值即可），驱动与命令零改动。
JSON 编辑器 `schema.json` 已加 `Board` 条目（共 16 个模块）。

⚠️ **不走 cfgs 字典**：那个循环假定 key 是"库名"，没有 `Board` 库 → 会变成 `-lBoard`。
Board 的生成物直接编进平台库，`$Board_Cfg` 单独注册 include 路径。

### 引脚表也进了 Board.json（第二步）

`Board.json` 新增 `pins[]`（9 个引脚）与 `dioChannels[]`（5 路），生成器产出两个宏：

```c
#define BOARD_PINS_TABLE   PORT_PIN_DEF(CAN, UNUSED, LOW, PORT_PORT_E, 4u, 5u), ...
#define BOARD_DIO_CHANNELS { (uint8_t)PORT_PORT_C, 1u }, ...
```

`Port_Cfg.c` / `Dio_Cfg.c` 的表体改为引用这两个宏 —— **结构、头文件、构建方式全不动**，
但引脚定义只有一个真源（JSON）。数量由 `PORT_CFG_NUM_PINS` / `DIO_CFG_NUM_CHANNELS`
在编译期对上。

⚠️ 生成宏里的 **逗号** 与 **LF 换行** 都是坑：CRLF 会让 `\` 续行失效；漏逗号报
"expected '}' before '{'"。

## D1 第一步：分区改 128 / 448 / 448 / 0（已上板）

**尺寸预算**（实测 App 侧目标模块 text）：
Dcm 10022 + CanTp 5348 + PduR 2444 + CanIf 1106 = 18,920 B，
加配置表与 CanAc 约 22 KB；boot 现有 56,644 B + 22 KB ≈ 79 KB > 64 KB 上限。

新布局（`boot_flash_map.h` + 三份 .ld + `flash.py` 同步）：

```
0x00000000  Boot     128 KB
0x00020000  Slot A   448 KB（尾部 4 KB meta）
0x00090000  Slot B   448 KB（尾部 4 KB meta）
0x00100000  结束（无预留区）
```

验收：`--boot` 同烧后 boot 正常跳转（s19 首记录 `0002 0000`）、`board` 报 slot A、
M2 39/39。**注意**：旧固件的 meta 全部失效（槽基址变了），两侧都要重烧。


## D1 第二步前置：boot 集成 NvM 栈（已上板）

决策：boot 也带存储栈。直接用途是**编程会话下诊断仪读 VIN**（`22 F1 90`）——
app 不在时只有 boot 能回答；顺带每次启动都做一次 DFlash 自检。

### 尺寸（实测）

| 项 | text |
|---|---|
| boot（原） | 56,644 |
| **boot（含 NvM 栈）** | **83,016** |
| 增量 | **+26,372**（NvM 2,680 + Fee 1,186 + FeeAc 1,074 + 厂商引擎其余） |

128 KB 区还剩 **48 KB**，够 D1 第二步的 CanIf+CanTp+PduR+Dcm（实测 18,920 B）。

### 上板输出

```
  slot A : 0x020000  CONFIRMED  rc=2    size=202548  crc=A259F1D1  v2.8.0
  slot B : 0x090000  EMPTY      (no meta)
[boot] nvm: DFlash ok, bootCnt = 601
[boot] nvm: VIN = CVM0146M4NVM00001
[boot] active slot : A (rolling counter)
```

`bootCnt` 与 app 侧的启动计数连续、VIN 完整 17 字节 —— 证明 boot 与 app
读写的是同一块 DFlash、同一份块表。

### 四个坑（都只有上板才暴露）

1. **`self.LIBS` 加库名不够，必须真的调用**。第一次只在 boot 的 SConscript 里
   加了 `NvM/MemEngine/Det`，编译链接全过、尺寸纹丝不动（56,636）——
   因为没有任何代码引用 `NvM_Init`，静态库里被引用的目标文件才进镜像，
   `--gc-sections` 把整条链当垃圾回收了。
2. **`NvM_Init` 之后必须等 idle，且单块 `ReadBlock` 会拿到 `NOT_OK`**。
   `NvM_MapBlockState()` 把 `NVM_PORT_BLK_UNINIT`（从未读写过）映射成
   `NVM_REQ_NOT_OK`。所以 boot 也要走 `NvM_ReadAll()`，与 app 的启动路径一致；
   只读一个块时块状态还是 UNINIT，看起来像"boot 读不了 DFlash"。
3. **目标缓冲必须用 `NVM_CFG_BYTES()` 对齐后的大小**。引擎读路径最后一步是
   `memcpy(userBuff, cpyBuff, readJob->datasize)`（`nvm_statemachine.c:117`），
   而 `datasize` 是 FEE 块长对齐后的值：BOOTCNT 8 字节 → `NVM_CFG_BYTES(8)=16`，
   VIN 17 → 24。给 8/17 字节的栈数组会被多写 8/7 字节 —— 第一版就是这么写的，
   栈上恰好有余量才没崩，属于"看起来能跑"的未定义行为。
4. **块内容是小端**。`Storage_GetU32` 是 `p[0] | p[1]<<8 | ...`，按大端解析
   会把 `bootCnt=601` 读成 `1426194432`。

### 串口抓 boot 输出的技巧

`flash.py --boot --run` 之后 boot 只跑几十毫秒就跳 app，用 `subprocess.run` +
`serial.read()` 会整段错过（等它返回时 boot 早跑完了）。正确做法是
`Popen` 异步启动 JLink，同时用 `ser.in_waiting` 轮询而不是 `read(timeout)`：

```python
p = subprocess.Popen([JLINK, "-CommanderScript", script], ...)
while time.time() - t0 < 5.0:
    n = ser.in_waiting
    if n:
        buf += ser.read(n)
    time.sleep(0.005)
```


## D1 第二步：刷写协议栈进 boot（架构完成，CAN 收发待排查）

### 已完成

| 项 | 状态 |
|---|---|
| boot 专用 cfg | `app/boot/config/`：CanIf（1RX+1TX）/ CanTp / PduR（4 条路径）/ Dcm（7 个服务） |
| 协议栈链接 | Can / Dio / Port / CanIf / CanTp / PduR / Dcm + NvM / MemEngine / Det |
| 平台层 | `Platform_McuInitMinimal` 增加 flexCAN 驱动句柄；keep 列表加 CanAc/PortAc/DioAc/FlashLoader |
| UDS 模式 | 无镜像时进 `Boot_UdsLoop()`（10 ms 节拍跑 CanTp/Dcm），不再死等 J-Link |
| DET 可见性 | `boot_stubs.c` 提供 `Det_Log`，否则 `Det.c` 的空实现把所有参数错误吞掉 |

### 验证结果

- ✅ boot 带完整协议栈正常启动、正常跳 app（M2 39/39 未受影响）
- ✅ `BOOT_FORCE_UDS=1` 时 boot 停在 UDS 模式，串口打印就绪横幅
- ✅ boot 与 app 共用同一份 `Can_Cfg.c` / `NvM_Cfg.c`（配置不漂移）
- ❌ **CAN 收发未通**：Kvaser 发 `10 02` 到 0x7E0，boot 无响应、无 DET、无 CanIf 回调
  → 帧在 **CanAc 邮箱中断层**就丢了，没进 `CanIf_RxIndication`

寄存器快照（UDS 模式打印）：

```
[canreg] ch0 mcr=00830060 ctrl1=052ca007 ecr=00000000 esr1=00040080
[canreg]  waitFailed=0
[canreg]  TEC=0 REC=0 FLTCONF=0 BOFFINT=0 BOFFMSK=1 ERRMSK=0
```

`MCR` bit28（HALT）=0、bit31（MDIS）=0 → 控制器已使能；ECR=0 → 无任何收发活动。
说明**邮箱中断没触发**，而不是总线错误。

### 已修复：STB 拉低漏了 `CanIf_SetTrcvMode`

`Can_SetControllerMode(STARTED)` **只启动控制器，不管收发器**。STB 拉低在
`CanIf_SetTrcvMode(ch, NORMAL)` 里（`Can.c:126`），app 由 **CanSM** 调，
boot 没有 CanSM 所以漏了 —— 收发器一直停在 Standby，总线上什么都收不到。

已在 `Boot_UdsInit` 补上（顺序：STARTED → SetTrcvMode(NORMAL) → SetPduMode(ONLINE)）。

### 逐项排除记录（都有寄存器证据）

| 假设 | 实测 | 结论 |
|---|---|---|
| mb5 没开中断 | `IMASK1 = 0x000053FF`，bit5=1 | ❌ 排除 |
| NVIC 没使能 | `ISER3` 的 bit7（IRQ103）= ON | ❌ 排除 |
| STB 还在待机 | `GPIOC PDOR = 0` → PC1 输出低 | ❌ 排除 |
| CAN 引脚 MUX 错 | `PE4/PE5 PCR = 0x500` → MUX=5 | ❌ 排除 |
| 控制器没启动 | `MCR=0x00830060`（MDIS=0/HALT=0）、`CTRL1=0x052CA007` | ❌ 排除 |

**且 MCR / CTRL1 / IMASK1 与 app 运行时逐位相同**（唯一差异是 ECR：
app 有 TX 错误累积因为它在发心跳，boot 从不发帧）。

### 当前剩余疑点

`ECR = 0` + `IFLAG1 = 0` —— 控制器**完全没看到总线活动**，而 app 在同一块板上
工作正常。软件侧能查的都已排除，下一步要靠硬件观测：

1. **让 boot 主动发一帧**（最简单的二分）：在 `Boot_UdsLoop` 前调
   `Can_Write(3, ...)` 发 0x7E8，Kvaser 若能收到 → TX 通路 OK、问题在 RX；
   收不到 → 收发器/引脚/供电
2. **示波器看 PE5（CAN0_TX）** 在 boot 里有无波形 —— 直接区分"控制器没发"
   还是"收发器没转"
3. 对比 app 运行时 PC1 的 PCR 值（app 是否配了 boot 没有的位，如 DSE/ODE）
4. 检查 CAN0 收发器供电（VDDA/待机电路的 EN 引脚是否还有第三根控制线）

### ⚠ 尺寸告警

**boot = 128,392 B / 130,048 B（ld 的 m_text 上限），只剩 1.6 KB。**

必须优化，否则加任何东西就链接失败。方向：
- 给 boot 单独加 `-Os`（app 不动）
- 或把 boot 区从 128 KB 扩到 160 KB（槽 448 → 432 KB，app 当前 202 KB 仍够）

### 尚未完成（下一步）

1. **D1 第二步**：boot 内接 CanIf+CanTp+PduR+Dcm（boot 专用 cfg：只留 UDS 与刷写服务），
   app 侧关掉 0x34/36/37，实测"app 不在也能刷"。
2. **M22**：CAN1 的 34 RX / 6 TX 迁入 Com/PduR JSON。
3. 模块级 `cmd/` 目录约定。
