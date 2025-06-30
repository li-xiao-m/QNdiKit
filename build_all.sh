#!/bin/bash

set -e

echo "============================================"
echo "QNdiKit 全模块构建脚本 (Linux/macOS)"
echo "============================================"

# 检查是否在正确的目录
if [ ! -f "CMakeLists.txt" ]; then
    echo "错误: 请在 QNdiKit 根目录下运行此脚本"
    exit 1
fi

# 设置默认参数
BUILD_TYPE="Release"
BASE_INSTALL_DIR="/tmp/nditest"
CLEAN_BUILD=0
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
            BASE_INSTALL_DIR="$2"
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
            echo "  --clean      清理所有构建目录"
            echo "  --prefix DIR 指定基础安装路径 (默认: /tmp/nditest)"
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
echo "基础安装路径: $BASE_INSTALL_DIR"

# 清理构建目录
if [ $CLEAN_BUILD -eq 1 ]; then
    echo "清理所有构建目录..."
    for dir in build_*; do
        if [ -d "$dir" ]; then
            echo "清理 $dir..."
            rm -rf "$dir"
        fi
    done
    if [ -d "build" ]; then
        echo "清理 build..."
        rm -rf build
    fi
fi

echo ""
echo "============================================"
echo "开始构建所有模块组合"
echo "============================================"

# 1. Source Widgets 模块
echo ""
echo "[1/5] 构建 Source Widgets 模块..."
BUILD_DIR="build_source_widgets"
INSTALL_DIR="$BASE_INSTALL_DIR/source_widgets"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DQNdiKit_BUILD_NDI_SOURCE_WIDGETS=ON -DQNdiKit_BUILD_NDI_SOURCE_QUICK=OFF -DQNdiKit_BUILD_NDI_MANAGER_WIDGETS=OFF -DQNdiKit_BUILD_NDI_MANAGER_QUICK=OFF -DQNdiKit_BUILD_EXAMPLES=ON -DQNdiKit_INSTALL_PREFIX="$INSTALL_DIR"
if [ $? -ne 0 ]; then
    echo "配置失败！"
    exit 1
fi

cmake --build . --config $BUILD_TYPE --parallel $JOBS
if [ $? -ne 0 ]; then
    echo "构建失败！"
    exit 1
fi

cmake --install . --config $BUILD_TYPE
if [ $? -ne 0 ]; then
    echo "安装失败！"
    exit 1
fi

cd ..

# 2. Source Quick 模块
echo ""
echo "[2/5] 构建 Source Quick 模块..."
BUILD_DIR="build_source_quick"
INSTALL_DIR="$BASE_INSTALL_DIR/source_quick"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DQNdiKit_BUILD_NDI_SOURCE_WIDGETS=OFF -DQNdiKit_BUILD_NDI_SOURCE_QUICK=ON -DQNdiKit_BUILD_NDI_MANAGER_WIDGETS=OFF -DQNdiKit_BUILD_NDI_MANAGER_QUICK=OFF -DQNdiKit_BUILD_EXAMPLES=ON -DQNdiKit_INSTALL_PREFIX="$INSTALL_DIR"
if [ $? -ne 0 ]; then
    echo "配置失败！"
    exit 1
fi

cmake --build . --config $BUILD_TYPE --parallel $JOBS
if [ $? -ne 0 ]; then
    echo "构建失败！"
    exit 1
fi

cmake --install . --config $BUILD_TYPE
if [ $? -ne 0 ]; then
    echo "安装失败！"
    exit 1
fi

cd ..

# 3. Manager Widgets 模块
echo ""
echo "[3/5] 构建 Manager Widgets 模块..."
BUILD_DIR="build_manager_widgets"
INSTALL_DIR="$BASE_INSTALL_DIR/manager_widgets"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DQNdiKit_BUILD_NDI_SOURCE_WIDGETS=OFF -DQNdiKit_BUILD_NDI_SOURCE_QUICK=OFF -DQNdiKit_BUILD_NDI_MANAGER_WIDGETS=ON -DQNdiKit_BUILD_NDI_MANAGER_QUICK=OFF -DQNdiKit_BUILD_EXAMPLES=ON -DQNdiKit_INSTALL_PREFIX="$INSTALL_DIR"
if [ $? -ne 0 ]; then
    echo "配置失败！"
    exit 1
fi

cmake --build . --config $BUILD_TYPE --parallel $JOBS
if [ $? -ne 0 ]; then
    echo "构建失败！"
    exit 1
fi

cmake --install . --config $BUILD_TYPE
if [ $? -ne 0 ]; then
    echo "安装失败！"
    exit 1
fi

cd ..

# 4. Manager Quick 模块
echo ""
echo "[4/5] 构建 Manager Quick 模块..."
BUILD_DIR="build_manager_quick"
INSTALL_DIR="$BASE_INSTALL_DIR/manager_quick"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DQNdiKit_BUILD_NDI_SOURCE_WIDGETS=OFF -DQNdiKit_BUILD_NDI_SOURCE_QUICK=OFF -DQNdiKit_BUILD_NDI_MANAGER_WIDGETS=OFF -DQNdiKit_BUILD_NDI_MANAGER_QUICK=ON -DQNdiKit_BUILD_EXAMPLES=ON -DQNdiKit_INSTALL_PREFIX="$INSTALL_DIR"
if [ $? -ne 0 ]; then
    echo "配置失败！"
    exit 1
fi

cmake --build . --config $BUILD_TYPE --parallel $JOBS
if [ $? -ne 0 ]; then
    echo "构建失败！"
    exit 1
fi

cmake --install . --config $BUILD_TYPE
if [ $? -ne 0 ]; then
    echo "安装失败！"
    exit 1
fi

cd ..

# 5. 完整版本（所有模块）
echo ""
echo "[5/5] 构建完整版本（所有模块）..."
BUILD_DIR="build_complete"
INSTALL_DIR="$BASE_INSTALL_DIR/complete"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DQNdiKit_BUILD_NDI_SOURCE_WIDGETS=ON -DQNdiKit_BUILD_NDI_SOURCE_QUICK=ON -DQNdiKit_BUILD_NDI_MANAGER_WIDGETS=ON -DQNdiKit_BUILD_NDI_MANAGER_QUICK=ON -DQNdiKit_BUILD_EXAMPLES=ON -DQNdiKit_INSTALL_PREFIX="$INSTALL_DIR"
if [ $? -ne 0 ]; then
    echo "配置失败！"
    exit 1
fi

cmake --build . --config $BUILD_TYPE --parallel $JOBS
if [ $? -ne 0 ]; then
    echo "构建失败！"
    exit 1
fi

cmake --install . --config $BUILD_TYPE
if [ $? -ne 0 ]; then
    echo "安装失败！"
    exit 1
fi

cd ..

echo ""
echo "============================================"
echo "全模块构建完成！"
echo "============================================"
echo ""
echo "安装位置: $BASE_INSTALL_DIR"
echo ""
echo "各模块安装目录:"
echo "  - Source Widgets: $BASE_INSTALL_DIR/source_widgets"
echo "  - Source Quick:   $BASE_INSTALL_DIR/source_quick"
echo "  - Manager Widgets: $BASE_INSTALL_DIR/manager_widgets"
echo "  - Manager Quick:   $BASE_INSTALL_DIR/manager_quick"
echo "  - 完整版本:       $BASE_INSTALL_DIR/complete"
echo ""
echo "可执行文件:"
echo "  - QNdiSourceWidgetsDemo"
echo "  - QNdiSourceQuickDemo"
echo "  - QNdiManagerWidgetsDemo"
echo "  - QNdiManagerQuickDemo"
echo "" 