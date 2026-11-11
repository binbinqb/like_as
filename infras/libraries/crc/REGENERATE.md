# CRC 表驱动实现的重生成命令

`src/crc*/crc*.c` 与 `.h` 由 pycrc 生成，**当前版本已经提交在库里，构建不需要 pycrc**。
只有要换多项式时才需要重跑下面这些命令（参数抄自 as-master 的 `gen()`）。

```sh
# 先取 pycrc
curl -LO https://pycrc.org/download/pycrc-0.10.0.zip
unzip pycrc-0.10.0.zip

# CRC8        @SWS_Crc_00031  poly 0x1D, init 0x00, xorout 0xFF
python pycrc-0.10.0/src/pycrc.py --model crc-8 --poly 0x1D --xor-in 0xFF --xor-out 0xFF \
    --reflect-in False --reflect-out False --algorithm table-driven \
    --generate h -o src/crc8/crc8.h
python pycrc-0.10.0/src/pycrc.py --model crc-8 --poly 0x1D --xor-in 0xFF --xor-out 0xFF \
    --reflect-in False --reflect-out False --algorithm table-driven \
    --generate c -o src/crc8/crc8.c

# CRC8H2F     @SWS_Crc_00043  poly 0x2F
python pycrc-0.10.0/src/pycrc.py --model crc-8 --poly 0x2F --xor-in 0xFF --xor-out 0xFF \
    --reflect-in False --reflect-out False --algorithm table-driven \
    --generate h -o src/crc8h2f/crc8h2f.h
python pycrc-0.10.0/src/pycrc.py --model crc-8 --poly 0x2F --xor-in 0xFF --xor-out 0xFF \
    --reflect-in False --reflect-out False --algorithm table-driven \
    --generate c -o src/crc8h2f/crc8h2f.c

# CRC16       @SWS_Crc_00019  poly 0x1021
python pycrc-0.10.0/src/pycrc.py --model crc-16 --poly 0x1021 --xor-in 0xFFFF --xor-out 0x0000 \
    --reflect-in False --reflect-out False --algorithm table-driven \
    --generate h -o src/crc16/crc16.h
python pycrc-0.10.0/src/pycrc.py --model crc-16 --poly 0x1021 --xor-in 0xFFFF --xor-out 0x0000 \
    --reflect-in False --reflect-out False --algorithm table-driven \
    --generate c -o src/crc16/crc16.c

# CRC32       @SWS_Crc_00020  poly 0x04C11DB7，反射
python pycrc-0.10.0/src/pycrc.py --model crc-32 --poly 0x04C11DB7 \
    --reflect-in True --reflect-out True --algorithm table-driven \
    --generate h -o src/crc32/crc32.h
python pycrc-0.10.0/src/pycrc.py --model crc-32 --poly 0x04C11DB7 \
    --reflect-in True --reflect-out True --algorithm table-driven \
    --generate c -o src/crc32/crc32.c

# CRC32P4     @SWS_Crc_00058  poly 0xF4ACFB13
python pycrc-0.10.0/src/pycrc.py --model crc-32 --poly 0xF4ACFB13 \
    --reflect-in True --reflect-out True --algorithm table-driven \
    --generate h -o src/crc32p4/crc32p4.h
python pycrc-0.10.0/src/pycrc.py --model crc-32 --poly 0xF4ACFB13 \
    --reflect-in True --reflect-out True --algorithm table-driven \
    --generate c -o src/crc32p4/crc32p4.c
```

**校验一致性**：`Crc_CalculateCRC32` 的 AUTOSAR 语义与 pycrc 的 `crc_update/crc_finalize` 有一处差异 ——
AUTOSAR 要求"非首次调用"时先对上次结果做 `finalize`。`src/Crc_32.c` 里已经处理，
重生成时**不要动 `Crc_32.c`**，只换 `crc32.c/h`。
