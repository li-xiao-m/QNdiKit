@echo off
setlocal enabledelayedexpansion

echo ============================================
echo QNdiKit 安装脚本 (Windows)
echo ============================================

REM 检查是否在正确的目录
if not exist "CMakeLists.txt" (
    echo 错误: 请在 QNdiKit 根目录下运行此脚本
    pause
    exit /b 1
)

REM 检查构建目录是否存在
if not exist "build" (
    echo 错误: 构建目录不存在，请先运行 build.bat
    pause
    exit /b 1
)

REM 设置默认参数
set INSTALL_PREFIX=
set BUILD_CONFIG=Release

REM 解析命令行参数
:parse_args
if "%1"=="" goto :end_parse
if /i "%1"=="--prefix" (
    set INSTALL_PREFIX=%2
    shift
    shift
    goto :parse_args
)
if /i "%1"=="--debug" (
    set BUILD_CONFIG=Debug
    shift
    goto :parse_args
)
if /i "%1"=="--release" (
    set BUILD_CONFIG=Release
    shift
    goto :parse_args
)
if /i "%1"=="--help" (
    echo 用法: install.bat [选项]
    echo 选项:
    echo   --prefix DIR 指定安装路径 (默认: C:/Program Files/QNdiKit)
    echo   --debug     安装 Debug 版本
    echo   --release   安装 Release 版本 (默认)
    echo   --help      显示此帮助信息
    exit /b 0
)
shift
goto :parse_args
:end_parse

echo 安装配置: %BUILD_CONFIG%
if not "%INSTALL_PREFIX%"=="" (
    echo 安装路径: %INSTALL_PREFIX%
) else (
    echo 安装路径: C:/Program Files/QNdiKit (默认)
)

cd build

REM 安装项目
echo 安装项目...
if not "%INSTALL_PREFIX%"=="" (
    cmake --install . --config %BUILD_CONFIG% --prefix "%INSTALL_PREFIX%"
) else (
    cmake --install . --config %BUILD_CONFIG%
)

if %ERRORLEVEL% neq 0 (
    echo 安装失败！
    pause
    exit /b 1
)

echo ============================================
echo 安装完成！
echo ============================================
echo.
if not "%INSTALL_PREFIX%"=="" (
    echo 安装位置: %INSTALL_PREFIX%
) else (
    echo 安装位置: C:/Program Files/QNdiKit
)
echo.
echo 安装内容:
echo   - 可执行文件: bin/
echo   - 库文件: lib/
echo   - 头文件: include/QNdiKit/
echo   - CMake 配置: lib/cmake/QNdiKit/
echo   - pkg-config: lib/pkgconfig/
echo.

pause 