# like_as 项目长期约定

## 提交纪律（最高优先级，用户 2026-11-17 明确两次强调）

- **唯一推送目标**：`https://github.com/binbinqb/like_as`（`origin`，分支 `main`）
- **该仓库是 public**。任何一次提交前必须确认没有客户（OEM）资料进入索引。

### 禁止入库的目录 / 文件类型（涉密）

| 路径 | 内容 | 归属 |
|---|---|---|
| `doc/福田系统设计/` | 福田 L1 24V IDM 功能规范 PDF、系统框图、通信矩阵 xlsx、DiagData、诊断规范 | 福田（第三方资产） |
| `app/platform/cvm0146/src/config/dbc/*.dbc` | 由通信矩阵导出的 DBC | 同上 |
| `*.xlsx` / `*.pdf` 形式的客户规范 | — | 同上 |

`.gitignore:75` 已有 `/doc/福田系统设计/`，DBC 段也在忽略列表里。**不要删除这两条规则**。

### 每次提交前的三步硬检查

```sh
git ls-files | grep -c "福田系统设计"        # 必须为 0
git check-ignore -v "doc/福田系统设计/<任一文件>"  # 必须命中 .gitignore
git status --short                          # 不得出现上述路径
```

若历史上已误入（曾发生过，已用 filter-branch 从 44 个提交里摘除），
不要只 `git rm`：必须重写历史，否则旧提交仍可被拉取。

- 原始历史备份提交 `388f3f0` 只存在于本地 `.git`，**不得推送**。
- `build/` 已在 `.gitignore:10`；MSVC 的 `*.obj` 若落在仓库根目录要手工清掉。

## 工程约定（沿用）

- 分层：Application → cfg → chip → HAL 接口 → HAL 平台实现 → SDK
- 代码注释：中文 + Doxygen，`@author binbina`，不写版权/保密声明
- 验证优先：每个改动要有可复现脚本（`tools/*_check.py`）+ 上板证据
- 文档：结论前置、表格优先
