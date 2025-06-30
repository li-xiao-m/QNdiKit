#!/bin/bash

set -e

echo "============================================"
echo "QNdiKit 构建脚本 (Linux/macOS)"
echo "============================================"

# 检查是否在正确的目录
if [ ! -f "CMakeLists.txt" ]; then
    echo "错误: 请在 QNdiKit 根目录下运行此脚本"
    exit 1
fi

# 设置默认参数
BUILD_TYPE="Release"
CLEAN_BUILD=0
INSTALL_PREFIX=""
JOBS=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# 解析命令行参数
while [[ $# -gt 0 ]]; do
    case $1 in
        --debug)
            BUILD_TYPE="Debug"
            shift
            ;;
        --release)
            BUILD_TYPE="Release"
            shift
            ;;
        --clean)
            CLEAN_BUILD=1
            shift
            ;;
        --prefix)
            INSTALL_PREFIX="$2"
            shift 2
            ;;
        --jobs)
            JOBS="$2"
            shift 2
            ;;
        --help)
            echo "用法: $0 [选项]"
            echo "选项:"
            echo "  --debug      构建 Debug 版本"
            echo "  --release    构建 Release 版本 (默认)"
            echo "  --clean      清理构建目录"
            echo "  --prefix DIR 指定安装路径"
            echo "  --jobs N     指定并行编译任务数 (默认: $JOBS)"
            echo "  --help       显示此帮助信息"
            exit 0
            ;;
        *)
            echo "未知选项: $1"
            echo "使用 --help 查看帮助信息"
            exit 1
            ;;
    esac
done

echo "构建类型: $BUILD_TYPE"
echo "并行任务数: $JOBS"
if [ -n "$INSTALL_PREFIX" ]; then
    echo "安装路径: $INSTALL_PREFIX"
fi

# 清理构建目录
if [ $CLEAN_BUILD -eq 1 ]; then
    echo "清理构建目录..."
    if [ -d "build" ]; then
        rm -rf build
    fi
fi

# 创建构建目录
if [ ! -d "build" ]; then
    echo "创建构建目录..."
    mkdir build
fi

cd build

# 配置项目
echo "配置项目..."
CMAKE_ARGS="-DCMAKE_BUILD_TYPE=$BUILD_TYPE"
if [ -n "$INSTALL_PREFIX" ]; then
    CMAKE_ARGS="$CMAKE_ARGS -DQNdiKit_INSTALL_PREFIX=$INSTALL_PREFIX"
fi

cmake .. $CMAKE_ARGS

if [ $? -ne 0 ]; then
    echo "配置失败！"
    exit 1
fi

# 构建项目
echo "构建项目..."
cmake --build . --config $BUILD_TYPE --parallel $JOBS

if [ $? -ne 0 ]; then
    echo "构建失败！"
    exit 1
fi

echo "============================================"
echo "构建完成！"
echo "============================================"
echo ""
echo "构建的可执行文件位置:"
echo "  - QNdiSourceWidgetsDemo: build/examples/widgets/source_demo/QNdiSourceWidgetsDemo"
echo "  - QNdiManagerWidgetsDemo: build/examples/widgets/manager_demo/QNdiManagerWidgetsDemo"
echo "  - QNdiSourceQuickDemo: build/examples/quick/source_demo/QNdiSourceQuickDemo"
echo "  - QNdiManagerQuickDemo: build/examples/quick/manager_demo/QNdiManagerQuickDemo"
echo "" 