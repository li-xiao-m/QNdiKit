#!/bin/bash

set -e

echo "============================================"
echo "QNdiKit 安装脚本 (Linux/macOS)"
echo "============================================"

# 检查是否在正确的目录
if [ ! -f "CMakeLists.txt" ]; then
    echo "错误: 请在 QNdiKit 根目录下运行此脚本"
    exit 1
fi

# 检查构建目录是否存在
if [ ! -d "build" ]; then
    echo "错误: 构建目录不存在，请先运行 build.sh"
    exit 1
fi

# 设置默认参数
INSTALL_PREFIX=""
BUILD_TYPE="Release"

# 解析命令行参数
while [[ $# -gt 0 ]]; do
    case $1 in
        --prefix)
            INSTALL_PREFIX="$2"
            shift 2
            ;;
        --debug)
            BUILD_TYPE="Debug"
            shift
            ;;
        --release)
            BUILD_TYPE="Release"
            shift
            ;;
        --help)
            echo "用法: $0 [选项]"
            echo "选项:"
            echo "  --prefix DIR 指定安装路径 (默认: /usr/local)"
            echo "  --debug      安装 Debug 版本"
            echo "  --release    安装 Release 版本 (默认)"
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

echo "安装配置: $BUILD_TYPE"
if [ -n "$INSTALL_PREFIX" ]; then
    echo "安装路径: $INSTALL_PREFIX"
else
    echo "安装路径: /usr/local (默认)"
fi

cd build

# 安装项目
echo "安装项目..."
if [ -n "$INSTALL_PREFIX" ]; then
    cmake --install . --config $BUILD_TYPE --prefix "$INSTALL_PREFIX"
else
    cmake --install . --config $BUILD_TYPE
fi

if [ $? -ne 0 ]; then
    echo "安装失败！"
    exit 1
fi

echo "============================================"
echo "安装完成！"
echo "============================================"
echo ""
if [ -n "$INSTALL_PREFIX" ]; then
    echo "安装位置: $INSTALL_PREFIX"
else
    echo "安装位置: /usr/local"
fi
echo ""
echo "安装内容:"
echo "  - 可执行文件: bin/"
echo "  - 库文件: lib/"
echo "  - 头文件: include/QNdiKit/"
echo "  - CMake 配置: lib/cmake/QNdiKit/"
echo "  - pkg-config: lib/pkgconfig/"
echo "" 