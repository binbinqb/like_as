# tools/json.editor —— 上游收编说明

- **来源**：https://github.com/autoas/as 的 `tools/json.editor/`
- **收编版本**：commit `dfe6e07`（2026-11-20 拉取）
- **收编范围**：`main.py` / `json_editor.py` / `schema.json` / `plugin/*.py`，**原样未改**
- **许可证**：上游为 GPLv3 + 商业双许可（见上游 `LICENSE`）。本仓库已在
  使用同一来源的 `tools/generator`（文件头为 SSAS 版权），按既有口径处理：
  内部评估/学习可用；对外商用需遵守上游许可或联系 `parai@foxmail.com`。
- **为什么不改上游文件**：适配全部放在 `tools/config_editor.py` 里
  （子类化 `JsonEditor`，重写保存/生成），这样以后重新收编只需覆盖本目录，
  适配层不受影响。

## 上游默认入口（不推荐直接用）

```bash
cd tools/json.editor
python main.py            # 用上游 schema.json（PascalCase 方言）
```

上游 schema 与本仓库 JSON 的方言不同（`Networks` vs `networks`），直接用会
丢字段。**请用项目适配入口**：

```bash
python tools/config_editor.py            # 打开本项目配置
python tools/config_editor.py --check    # 只做 schema 覆盖率检查
python tools/config_editor.py --make-schema  # 重新生成项目 schema
```
