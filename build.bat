@echo off
rem ============================================================================
rem  H:/as build entry (GCC + SCons, same tools/building.py as as-master)
rem
rem  Usage:
rem    build.bat                 build Demo
rem    build.bat --app=Demo      build the given application
rem    build.bat --lib=Can       build a single library
rem
rem  NOTE: keep this file pure ASCII. A UTF-8 .bat with Chinese comments is
rem        decoded as GBK by cmd.exe, which garbles the text AND breaks the
rem        parentheses of if/else blocks (symptom: "'t' is not recognized as
rem        an internal or external command").
rem
rem  Why the interpreter is pinned:
rem    SCons is installed in Python 3.12. The `python` on PATH may be 3.13
rem    without scons, which fails with "No module named SCons".
rem
rem  Why ARMGCC is pinned:
rem    building.py downloads gcc-arm-none-eabi by default. 10.3-2021.10 is
rem    already installed (same version AS uses), so point at it and avoid the
rem    download. C:\soft\gcc\10.3.1 is a junction to "10 2021.10" (no spaces).
rem ============================================================================
setlocal

if "%PYTHON%"=="" set "PYTHON=C:\Users\qingb\AppData\Local\Programs\Python\Python312\python.exe"
if "%ARMGCC%"=="" set "ARMGCC=C:\soft\gcc\10.3.1"
if "%ARMGCC_VERSION%"=="" set "ARMGCC_VERSION=10.3.1"

rem ar/objcopy/size are invoked by bare name (building.py does not prefix them
rem with ARMGCC), so the toolchain bin dir must be on PATH. Without this the
rem build only fails at the very end: "ar rc ... No such file or directory".
set "PATH=%ARMGCC%\bin;%PATH%"

if not exist "%PYTHON%" (
    echo [ERROR] Python not found: %PYTHON%
    echo         Set PYTHON to an interpreter that has scons installed.
    exit /b 2
)

if "%~1"=="" (
    set "ARGS=--app=App"
) else (
    set "ARGS=%*"
)

"%PYTHON%" -m SCons --cpl=CM4GCC %ARGS%
exit /b %ERRORLEVEL%
