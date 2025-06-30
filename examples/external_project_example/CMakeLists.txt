cmake_minimum_required(VERSION 3.16)

project(ExternalProjectExample VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 Qt
find_package(Qt6 QUIET COMPONENTS Core Widgets Quick)
if(Qt6_FOUND)
    set(QT_VERSION_MAJOR 6)
else()
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets Quick)
    set(QT_VERSION_MAJOR 5)
endif()

# 查找 QNdiKit
set(QNdiKit_DIR "D:/test/nditest/complete/lib/cmake/QNdiKit")
find_package(QNdiKit REQUIRED CONFIG)

# 创建可执行文件
add_executable(external_project_example
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

# 启用Qt元对象自动处理
set_target_properties(external_project_example PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
)

# 链接 QNdiKit 库
target_link_libraries(external_project_example
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Quick
    QNdiKit::QNdiSourceCore
    QNdiKit::QNdiSourceWidgets
    QNdiKit::QNdiManagerCore
    QNdiKit::QNdiManagerWidgets
)

# 安装
install(TARGETS external_project_example
    RUNTIME DESTINATION bin
)

if(MSVC)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()
