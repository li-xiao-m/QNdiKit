@echo off
setlocal enabledelayedexpansion

echo ============================================
echo QNdiKit 构建脚本 (Windows)
echo ============================================

REM 检查是否在正确的目录
if not exist "CMakeLists.txt" (
    echo 错误: 请在 QNdiKit 根目录下运行此脚本
    pause
    exit /b 1
)

REM 设置默认参数
set BUILD_TYPE=Release
set BUILD_CONFIG=Release
set GENERATOR="Visual Studio 17 2022"
set ARCH=x64
set INSTALL_PREFIX=
set CLEAN_BUILD=0

REM 解析命令行参数
:parse_args
if "%1"=="" goto :end_parse
if /i "%1"=="--debug" (
    set BUILD_TYPE=Debug
    set BUILD_CONFIG=Debug
    shift
    goto :parse_args
)
if /i "%1"=="--release" (
    set BUILD_TYPE=Release
    set BUILD_CONFIG=Release
    shift
    goto :parse_args
)
if /i "%1"=="--clean" (
    set CLEAN_BUILD=1
    shift
    goto :parse_args
)
if /i "%1"=="--prefix" (
    set INSTALL_PREFIX=%2
    shift
    shift
    goto :parse_args
)
if /i "%1"=="--help" (
    echo 用法: build.bat [选项]
    echo 选项:
    echo   --debug     构建 Debug 版本
    echo   --release   构建 Release 版本 (默认)
    echo   --clean     清理构建目录
    echo   --prefix DIR 指定安装路径
    echo   --help      显示此帮助信息
    exit /b 0
)
shift
goto :parse_args
:end_parse

echo 构建类型: %BUILD_TYPE%
echo 构建配置: %BUILD_CONFIG%
if not "%INSTALL_PREFIX%"=="" (
    echo 安装路径: %INSTALL_PREFIX%
)

REM 清理构建目录
if %CLEAN_BUILD%==1 (
    echo 清理构建目录...
    if exist "build" (
        rmdir /s /q build
    )
)

REM 创建构建目录
if not exist "build" (
    echo 创建构建目录...
    mkdir build
)

cd build

REM 配置项目
echo 配置项目...
set CMAKE_ARGS=-G %GENERATOR% -A %ARCH% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
if not "%INSTALL_PREFIX%"=="" (
    set CMAKE_ARGS=%CMAKE_ARGS% -DQNdiKit_INSTALL_PREFIX="%INSTALL_PREFIX%"
)

cmake .. %CMAKE_ARGS%

if %ERRORLEVEL% neq 0 (
    echo 配置失败！
    pause
    exit /b 1
)

REM 构建项目
echo 构建项目...
cmake --build . --config %BUILD_CONFIG% --parallel

if %ERRORLEVEL% neq 0 (
    echo 构建失败！
    pause
    exit /b 1
)

echo ============================================
echo 构建完成！
echo ============================================
echo.
echo 构建的可执行文件位置:
echo   - QNdiSourceWidgetsDemo: build\examples\widgets\source_demo\%BUILD_CONFIG%\QNdiSourceWidgetsDemo.exe
echo   - QNdiManagerWidgetsDemo: build\examples\widgets\manager_demo\%BUILD_CONFIG%\QNdiManagerWidgetsDemo.exe
echo   - QNdiSourceQuickDemo: build\examples\quick\source_demo\%BUILD_CONFIG%\QNdiSourceQuickDemo.exe
echo   - QNdiManagerQuickDemo: build\examples\quick\manager_demo\%BUILD_CONFIG%\QNdiManagerQuickDemo.exe
echo.

pause 