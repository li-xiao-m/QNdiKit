# QNdiKit

[English](../README.md)

**NDI SDK 下载：** [https://ndi.video/for-developers/ndi-sdk/](https://ndi.video/for-developers/ndi-sdk/)

一个基于 Qt 的模块化 NDI 框架，支持 Windows、Linux、macOS 跨平台高效开发 NDI 源和管理器应用。

## 推荐编译环境

| 平台    | 操作系统                | 编译器             | Qt版本      | NDI SDK版本 | CMake版本 |
|---------|-------------------------|--------------------|-------------|-------------|-----------|
| Windows | Win10/11                | MSVC 2019/2022     | 5.15.x/6.x  | 6.0+        | 3.16+     |
| Linux   | Ubuntu 20.04+/CentOS 7+ | gcc 9+/clang 10+   | 5.15.x/6.x  | 6.0+        | 3.16+     |
| macOS   | 10.15+                  | clang (Xcode 12+)  | 5.15.x/6.x  | 6.0+        | 3.16+     |

> **建议：** 推荐 Qt 5.15，NDI SDK 6.0 及以上。

## 快速编译与安装

### 一键全模块构建（推荐）
- **Windows**：
  ```bat
  build_all.bat --clean --prefix D:\your_install_dir
  ```
- **Linux/macOS**：
  ```sh
  ./build_all.sh --clean --prefix /your/install/dir
  ```

#### 常用参数
| 参数         | 说明                         |
|--------------|------------------------------|
| --clean      | 清理所有构建目录后重新构建   |
| --prefix DIR | 指定安装路径                 |
| --debug      | 构建 Debug 版本              |
| --release    | 构建 Release 版本（默认）    |
| --help       | 显示所有参数说明             |

### 单模块/开发调试
- **Windows**：
  ```bat
  build.bat --clean --prefix D:\your_install_dir
  ```
- **Linux/macOS**：
  ```sh
  ./build.sh --clean --prefix /your/install/dir
  ```

### 安装已构建产物
- **Windows**：
  ```bat
  install.bat --prefix D:\your_install_dir
  ```
- **Linux/macOS**：
  ```sh
  ./install.sh --prefix /your/install/dir
  ```

> **NDI SDK 路径**：如未安装在默认目录（Windows: C:/Program Files/NDI/NDI 6 SDK，Linux/macOS: /usr/local/ndi），可通过 `-DNDI_SDK_ROOT=路径` 或设置环境变量 `NDI_SDK_ROOT`。

## 外部项目集成

1. **安装 QNdiKit 后，设置 CMake 变量**
   ```cmake
   set(QNdiKit_DIR "/your/install/dir/complete/lib/cmake/QNdiKit")
   find_package(QNdiKit REQUIRED CONFIG)
   ```
2. **链接所需模块**
   ```cmake
   target_link_libraries(your_target
       QNdiKit::QNdiSourceCore
       QNdiKit::QNdiSourceWidgets
       QNdiKit::QNdiManagerCore
       QNdiKit::QNdiManagerWidgets
   )
   ```
3. **NDI 依赖自动处理**
   - 只需设置 QNdiKit_DIR，NDI::NDI 目标会自动导入，无需手动 find_package(NDI)。
   - 如 NDI SDK 路径特殊，设置 NDI_SDK_ROOT 即可。

## 示例外部项目
见 `examples/external_project_example/`，内含最小 CMakeLists.txt 用法范例。

## 详细结构与模块说明
详见本文件英文版或根目录 README.md。

---

如遇问题请先确认环境变量、依赖路径和脚本参数，或查阅英文文档获取详细模块与目录说明。

---

## 已完成工作

- 管理器：已实现NDI源查找功能
- Quick管理器：已支持在QML/Quick中显示NDI源信息 