@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

echo ============================================
echo QNdiKit 全模块构建脚本 (Windows)
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
set BASE_INSTALL_DIR=D:\test\nditest
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
    set BASE_INSTALL_DIR=%2
    shift
    shift
    goto :parse_args
)
if /i "%1"=="--help" (
    echo Usage: build_all.bat [options]
    echo Options:
    echo   --debug     Build Debug version
    echo   --release   Build Release version (default)
    echo   --clean     Clean all build directories
    echo   --prefix DIR Specify base install path (default: D:\test\nditest)
    echo   --help      Show this help message
    exit /b 0
)
shift
goto :parse_args
:end_parse

echo 构建类型: %BUILD_TYPE%
echo 基础安装路径: %BASE_INSTALL_DIR%

REM 清理构建目录
if %CLEAN_BUILD%==1 (
    echo 清理所有构建目录...
    for /d %%d in (build_*) do (
        if exist "%%d" (
            echo 清理 %%d...
            rmdir /s /q "%%d"
        )
    )
    if exist "build" (
        echo 清理 build...
        rmdir /s /q build
    )
)

echo.
echo ============================================
echo 开始构建所有模块组合
echo ============================================

REM 1. Source Widgets 模块
echo.
echo [1/5] 构建 Source Widgets 模块...
set BUILD_DIR=build_source_widgets
set INSTALL_DIR=%BASE_INSTALL_DIR%\source_widgets

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

cmake .. -G %GENERATOR% -A %ARCH% -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DQNdiKit_BUILD_NDI_SOURCE_WIDGETS=ON -DQNdiKit_BUILD_NDI_SOURCE_QUICK=OFF -DQNdiKit_BUILD_NDI_MANAGER_WIDGETS=OFF -DQNdiKit_BUILD_NDI_MANAGER_QUICK=OFF -DQNdiKit_BUILD_EXAMPLES=ON -DQNdiKit_INSTALL_PREFIX="%INSTALL_DIR%"
if %ERRORLEVEL% neq 0 (
    echo 配置失败！
    pause
    exit /b 1
)

cmake --build . --config %BUILD_CONFIG% --parallel
if %ERRORLEVEL% neq 0 (
    echo 构建失败！
    pause
    exit /b 1
)

cmake --install . --config %BUILD_CONFIG%
if %ERRORLEVEL% neq 0 (
    echo 安装失败！
    pause
    exit /b 1
)

cd ..

REM 2. Source Quick 模块
echo.
echo [2/5] 构建 Source Quick 模块...
set BUILD_DIR=build_source_quick
set INSTALL_DIR=%BASE_INSTALL_DIR%\source_quick

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

cmake .. -G %GENERATOR% -A %ARCH% -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DQNdiKit_BUILD_NDI_SOURCE_WIDGETS=OFF -DQNdiKit_BUILD_NDI_SOURCE_QUICK=ON -DQNdiKit_BUILD_NDI_MANAGER_WIDGETS=OFF -DQNdiKit_BUILD_NDI_MANAGER_QUICK=OFF -DQNdiKit_BUILD_EXAMPLES=ON -DQNdiKit_INSTALL_PREFIX="%INSTALL_DIR%"
if %ERRORLEVEL% neq 0 (
    echo 配置失败！
    pause
    exit /b 1
)

cmake --build . --config %BUILD_CONFIG% --parallel
if %ERRORLEVEL% neq 0 (
    echo 构建失败！
    pause
    exit /b 1
)

cmake --install . --config %BUILD_CONFIG%
if %ERRORLEVEL% neq 0 (
    echo 安装失败！
    pause
    exit /b 1
)

cd ..

REM 3. Manager Widgets 模块
echo.
echo [3/5] 构建 Manager Widgets 模块...
set BUILD_DIR=build_manager_widgets
set INSTALL_DIR=%BASE_INSTALL_DIR%\manager_widgets

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

cmake .. -G %GENERATOR% -A %ARCH% -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DQNdiKit_BUILD_NDI_SOURCE_WIDGETS=OFF -DQNdiKit_BUILD_NDI_SOURCE_QUICK=OFF -DQNdiKit_BUILD_NDI_MANAGER_WIDGETS=ON -DQNdiKit_BUILD_NDI_MANAGER_QUICK=OFF -DQNdiKit_BUILD_EXAMPLES=ON -DQNdiKit_INSTALL_PREFIX="%INSTALL_DIR%"
if %ERRORLEVEL% neq 0 (
    echo 配置失败！
    pause
    exit /b 1
)

cmake --build . --config %BUILD_CONFIG% --parallel
if %ERRORLEVEL% neq 0 (
    echo 构建失败！
    pause
    exit /b 1
)

cmake --install . --config %BUILD_CONFIG%
if %ERRORLEVEL% neq 0 (
    echo 安装失败！
    pause
    exit /b 1
)

cd ..

REM 4. Manager Quick 模块
echo.
echo [4/5] 构建 Manager Quick 模块...
set BUILD_DIR=build_manager_quick
set INSTALL_DIR=%BASE_INSTALL_DIR%\manager_quick

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

cmake .. -G %GENERATOR% -A %ARCH% -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DQNdiKit_BUILD_NDI_SOURCE_WIDGETS=OFF -DQNdiKit_BUILD_NDI_SOURCE_QUICK=OFF -DQNdiKit_BUILD_NDI_MANAGER_WIDGETS=OFF -DQNdiKit_BUILD_NDI_MANAGER_QUICK=ON -DQNdiKit_BUILD_EXAMPLES=ON -DQNdiKit_INSTALL_PREFIX="%INSTALL_DIR%"
if %ERRORLEVEL% neq 0 (
    echo 配置失败！
    pause
    exit /b 1
)

cmake --build . --config %BUILD_CONFIG% --parallel
if %ERRORLEVEL% neq 0 (
    echo 构建失败！
    pause
    exit /b 1
)

cmake --install . --config %BUILD_CONFIG%
if %ERRORLEVEL% neq 0 (
    echo 安装失败！
    pause
    exit /b 1
)

cd ..

REM 5. 完整版本（所有模块）
echo.
echo [5/5] 构建完整版本（所有模块）...
set BUILD_DIR=build_complete
set INSTALL_DIR=%BASE_INSTALL_DIR%\complete

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

cmake .. -G %GENERATOR% -A %ARCH% -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DQNdiKit_BUILD_NDI_SOURCE_WIDGETS=ON -DQNdiKit_BUILD_NDI_SOURCE_QUICK=ON -DQNdiKit_BUILD_NDI_MANAGER_WIDGETS=ON -DQNdiKit_BUILD_NDI_MANAGER_QUICK=ON -DQNdiKit_BUILD_EXAMPLES=ON -DQNdiKit_INSTALL_PREFIX="%INSTALL_DIR%"
if %ERRORLEVEL% neq 0 (
    echo 配置失败！
    pause
    exit /b 1
)

cmake --build . --config %BUILD_CONFIG% --parallel
if %ERRORLEVEL% neq 0 (
    echo 构建失败！
    pause
    exit /b 1
)

cmake --install . --config %BUILD_CONFIG%
if %ERRORLEVEL% neq 0 (
    echo 安装失败！
    pause
    exit /b 1
)

cd ..

echo.
echo ============================================
echo 全模块构建完成！
echo ============================================
echo.
echo 安装位置: %BASE_INSTALL_DIR%
echo.
echo 各模块安装目录:
echo   - Source Widgets: %BASE_INSTALL_DIR%\source_widgets
echo   - Source Quick:   %BASE_INSTALL_DIR%\source_quick
echo   - Manager Widgets: %BASE_INSTALL_DIR%\manager_widgets
echo   - Manager Quick:   %BASE_INSTALL_DIR%\manager_quick
echo   - 完整版本:       %BASE_INSTALL_DIR%\complete
echo.
echo 可执行文件:
echo   - QNdiSourceWidgetsDemo.exe
echo   - QNdiSourceQuickDemo.exe
echo   - QNdiManagerWidgetsDemo.exe
echo   - QNdiManagerQuickDemo.exe
echo.

pause 