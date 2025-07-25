# QNdiKit

[中文文档](docs/README_zh.md)

## Demo Video

![Demo Video](docs/tip1.gif)

*演示视频展示了QNdiKit的功能和使用效果*

**NDI SDK Download:** [https://ndi.video/for-developers/ndi-sdk/](https://ndi.video/for-developers/ndi-sdk/)

A modular Qt-based NDI framework for cross-platform (Windows, Linux, macOS) NDI source and manager development.

## Recommended Build Environment

| Platform   | OS                  | Compiler             | Qt Version  | NDI SDK Version | CMake Version |
|------------|---------------------|----------------------|-------------|-----------------|--------------|
| Windows    | Win10/11            | MSVC 2019/2022       | 5.15.x/6.x  | 6.0+            | 3.16+        |
| Linux      | Ubuntu 20.04+/CentOS 7+ | gcc 9+/clang 10+ | 5.15.x/6.x  | 6.0+            | 3.16+        |
| macOS      | 10.15+              | clang (Xcode 12+)    | 5.15.x/6.x  | 6.0+            | 3.16+        |

> **Recommendation:** Qt 5.15 and NDI SDK 6.0+ are preferred.

## Quick Build & Install

### One-Click Full Build (Recommended)
- **Windows:**
  ```bat
  build_all.bat --clean --prefix D:\your_install_dir
  ```
- **Linux/macOS:**
  ```sh
  ./build_all.sh --clean --prefix /your/install/dir
  ```

#### Common Parameters
| Parameter    | Description                          |
|--------------|--------------------------------------|
| --clean      | Clean all build dirs before building |
| --prefix DIR | Specify install path                 |
| --debug      | Build Debug version                  |
| --release    | Build Release version (default)      |
| --help       | Show all options                     |

### Single Module/Dev Build
- **Windows:**
  ```bat
  build.bat --clean --prefix D:\your_install_dir
  ```
- **Linux/macOS:**
  ```sh
  ./build.sh --clean --prefix /your/install/dir
  ```

### Install Built Artifacts
- **Windows:**
  ```bat
  install.bat --prefix D:\your_install_dir
  ```
- **Linux/macOS:**
  ```sh
  ./install.sh --prefix /your/install/dir
  ```

> **NDI SDK Path:** If not installed in the default location (Windows: C:/Program Files/NDI/NDI 6 SDK, Linux/macOS: /usr/local/ndi), use `-DNDI_SDK_ROOT=path` or set the `NDI_SDK_ROOT` environment variable.

## External Project Integration

1. **After installing QNdiKit, set the CMake variable:**
   ```cmake
   set(QNdiKit_DIR "/your/install/dir/complete/lib/cmake/QNdiKit")
   find_package(QNdiKit REQUIRED CONFIG)
   ```
2. **Link required modules:**
   ```cmake
   target_link_libraries(your_target
       QNdiKit::QNdiSourceCore
       QNdiKit::QNdiSourceWidgets
       QNdiKit::QNdiManagerCore
       QNdiKit::QNdiManagerWidgets
   )
   ```
3. **NDI dependency is handled automatically**
   - Just set QNdiKit_DIR, NDI::NDI target will be imported automatically.
   - If NDI SDK path is custom, set NDI_SDK_ROOT.

## Example External Project
See `examples/external_project_example/` for a minimal CMakeLists.txt usage example.

## Detailed Structure & Modules
See [docs/README_zh.md](docs/README_zh.md) for the Chinese version.

---

If you encounter issues, check environment variables, dependency paths, and script parameters, or refer to the Chinese documentation for more details.


---

## Project Progress

- Manager: NDI source discovery implemented
- Quick Manager: NDI source information display in QML/Quick supported

