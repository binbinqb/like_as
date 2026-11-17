import os
import sys

CWD = os.path.abspath('.')
sys.path.append('%s/tools' % (CWD))

from building import *

# ---------------------------------------------------------------------------
# --generate：只把配置同步到最新，然后退出，不解析 SConscript、不编译。
#
# 为什么必须在 SConscript() **之前**：不带 --app 时 BUILD_DIR 没有 app 子目录，
# 各 SConscript 的 variant_dir 会撞在一起，`@register_application` 第二次执行
# 就抛 "app App already registered"。放在这里相当于"先干活再建图"，
# 与 SCons 的依赖图完全解耦（生成链本来也是独立进程）。
#
# 返回值：0 已是最新 / 2 缺客户 DBC 但配置有改动 / 其他生成链失败。
# ---------------------------------------------------------------------------
if GetOption("generate_only"):
    sys.exit(ConfigSync(force=GetOption("gen")))

SConscript('SConscript', variant_dir=BUILD_DIR, duplicate=0)
