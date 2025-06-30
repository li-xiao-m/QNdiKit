# FindQNdiKit.cmake - 查找 QNdiKit 库
#
# 这个模块用于查找已安装的 QNdiKit 库
#
# 定义以下变量：
#   QNdiKit_FOUND - 如果找到 QNdiKit 则为 TRUE
#   QNdiKit_INCLUDE_DIRS - QNdiKit 头文件目录
#   QNdiKit_LIBRARIES - QNdiKit 库文件
#   QNdiKit_VERSION - QNdiKit 版本号
#
# 定义以下目标：
#   QNdiKit::ndi_source_core - NDI 源核心模块
#   QNdiKit::ndi_source_widgets - NDI 源 Widgets 模块
#   QNdiKit::ndi_source_quick - NDI 源 Quick 模块
#   QNdiKit::ndi_manager_core - NDI 管理器核心模块
#   QNdiKit::ndi_manager_widgets - NDI 管理器 Widgets 模块
#   QNdiKit::ndi_manager_quick - NDI 管理器 Quick 模块

# 设置搜索路径
set(QNdiKit_SEARCH_PATHS
    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/QNdiKit"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/QNdiKit"
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/QNdiKit"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/QNdiKit"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/QNdiKit"
    "${CMAKE_CURRENT_SOURCE_DIR}/QNdiKit"
    "${CMAKE_CURRENT_BINARY_DIR}/QNdiKit"
    "${CMAKE_CURRENT_BINARY_DIR}/third_party/QNdiKit"
    "${CMAKE_CURRENT_BINARY_DIR}/external/QNdiKit"
    "${CMAKE_CURRENT_BINARY_DIR}/deps/QNdiKit"
    "${CMAKE_CURRENT_BINARY_DIR}/vendor/QNdiKit"
    "${CMAKE_CURRENT_BINARY_DIR}/libs/QNdiKit"
)

# 如果用户指定了 QNdiKit_DIR，添加到搜索路径
if(DEFINED QNdiKit_DIR)
    list(PREPEND QNdiKit_SEARCH_PATHS "${QNdiKit_DIR}")
endif()

# 如果用户指定了 QNdiKit_ROOT，添加到搜索路径
if(DEFINED QNdiKit_ROOT)
    list(PREPEND QNdiKit_SEARCH_PATHS "${QNdiKit_ROOT}")
endif()

# 尝试查找 QNdiKitConfig.cmake
find_package(QNdiKit QUIET CONFIG
    PATHS ${QNdiKit_SEARCH_PATHS}
    NO_DEFAULT_PATH
)

# 如果通过 CONFIG 模式找到了，直接返回
if(QNdiKit_FOUND)
    return()
endif()

# 尝试在系统安装路径中查找
find_package(QNdiKit QUIET CONFIG)

# 如果找到了，直接返回
if(QNdiKit_FOUND)
    return()
endif()

# 如果 CONFIG 模式失败，尝试 MODULE 模式
# 首先查找头文件
find_path(QNdiKit_INCLUDE_DIR
    NAMES
        "QNdiKit/ndi_source_core.h"
        "QNdiKit/ndi_manager_core.h"
    PATHS
        ${QNdiKit_SEARCH_PATHS}
        "/usr/local/include"
        "/usr/include"
        "C:/Program Files/QNdiKit/include"
        "C:/Program Files (x86)/QNdiKit/include"
    PATH_SUFFIXES
        "include"
        "include/QNdiKit"
    DOC "QNdiKit 头文件目录"
)

# 查找库文件
if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(QNdiKit_LIB_SEARCH_PATHS
            ${QNdiKit_SEARCH_PATHS}
            "C:/Program Files/QNdiKit/lib"
            "C:/Program Files (x86)/QNdiKit/lib"
        )
        set(QNdiKit_LIB_SUFFIXES "lib" "lib/x64" "lib/x86_64")
    else()
        set(QNdiKit_LIB_SEARCH_PATHS
            ${QNdiKit_SEARCH_PATHS}
            "C:/Program Files/QNdiKit/lib"
            "C:/Program Files (x86)/QNdiKit/lib"
        )
        set(QNdiKit_LIB_SUFFIXES "lib" "lib/x86" "lib/i386")
    endif()
elseif(APPLE)
    set(QNdiKit_LIB_SEARCH_PATHS
        ${QNdiKit_SEARCH_PATHS}
        "/usr/local/lib"
        "/opt/local/lib"
    )
    set(QNdiKit_LIB_SUFFIXES "lib" "lib/macOS")
elseif(UNIX)
    set(QNdiKit_LIB_SEARCH_PATHS
        ${QNdiKit_SEARCH_PATHS}
        "/usr/local/lib"
        "/usr/lib"
        "/opt/lib"
    )
    set(QNdiKit_LIB_SUFFIXES "lib" "lib/linux")
endif()

# 查找各个模块的库文件
set(QNdiKit_LIBRARIES_FOUND TRUE)

# NDI Source Core
find_library(QNdiKit_NDI_SOURCE_CORE_LIBRARY
    NAMES
        "QNdiKit_ndi_source_core"
        "QNdiKit_ndi_source_core"
    PATHS ${QNdiKit_LIB_SEARCH_PATHS}
    PATH_SUFFIXES ${QNdiKit_LIB_SUFFIXES}
    DOC "QNdiKit NDI Source Core 库文件"
)

if(NOT QNdiKit_NDI_SOURCE_CORE_LIBRARY)
    set(QNdiKit_LIBRARIES_FOUND FALSE)
endif()

# NDI Source Widgets
find_library(QNdiKit_NDI_SOURCE_WIDGETS_LIBRARY
    NAMES
        "QNdiKit_ndi_source_widgets"
        "QNdiKit_ndi_source_widgets"
    PATHS ${QNdiKit_LIB_SEARCH_PATHS}
    PATH_SUFFIXES ${QNdiKit_LIB_SUFFIXES}
    DOC "QNdiKit NDI Source Widgets 库文件"
)

if(NOT QNdiKit_NDI_SOURCE_WIDGETS_LIBRARY)
    set(QNdiKit_LIBRARIES_FOUND FALSE)
endif()

# NDI Source Quick
find_library(QNdiKit_NDI_SOURCE_QUICK_LIBRARY
    NAMES
        "QNdiKit_ndi_source_quick"
        "QNdiKit_ndi_source_quick"
    PATHS ${QNdiKit_LIB_SEARCH_PATHS}
    PATH_SUFFIXES ${QNdiKit_LIB_SUFFIXES}
    DOC "QNdiKit NDI Source Quick 库文件"
)

if(NOT QNdiKit_NDI_SOURCE_QUICK_LIBRARY)
    set(QNdiKit_LIBRARIES_FOUND FALSE)
endif()

# NDI Manager Core
find_library(QNdiKit_NDI_MANAGER_CORE_LIBRARY
    NAMES
        "QNdiKit_ndi_manager_core"
        "QNdiKit_ndi_manager_core"
    PATHS ${QNdiKit_LIB_SEARCH_PATHS}
    PATH_SUFFIXES ${QNdiKit_LIB_SUFFIXES}
    DOC "QNdiKit NDI Manager Core 库文件"
)

if(NOT QNdiKit_NDI_MANAGER_CORE_LIBRARY)
    set(QNdiKit_LIBRARIES_FOUND FALSE)
endif()

# NDI Manager Widgets
find_library(QNdiKit_NDI_MANAGER_WIDGETS_LIBRARY
    NAMES
        "QNdiKit_ndi_manager_widgets"
        "QNdiKit_ndi_manager_widgets"
    PATHS ${QNdiKit_LIB_SEARCH_PATHS}
    PATH_SUFFIXES ${QNdiKit_LIB_SUFFIXES}
    DOC "QNdiKit NDI Manager Widgets 库文件"
)

if(NOT QNdiKit_NDI_MANAGER_WIDGETS_LIBRARY)
    set(QNdiKit_LIBRARIES_FOUND FALSE)
endif()

# NDI Manager Quick
find_library(QNdiKit_NDI_MANAGER_QUICK_LIBRARY
    NAMES
        "QNdiKit_ndi_manager_quick"
        "QNdiKit_ndi_manager_quick"
    PATHS ${QNdiKit_LIB_SEARCH_PATHS}
    PATH_SUFFIXES ${QNdiKit_LIB_SUFFIXES}
    DOC "QNdiKit NDI Manager Quick 库文件"
)

if(NOT QNdiKit_NDI_MANAGER_QUICK_LIBRARY)
    set(QNdiKit_LIBRARIES_FOUND FALSE)
endif()

# 检查是否找到了所有必需的文件
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QNdiKit
    REQUIRED_VARS
        QNdiKit_INCLUDE_DIR
        QNdiKit_LIBRARIES_FOUND
    FAIL_MESSAGE "QNdiKit 未找到或配置不正确"
)

# 如果找到了 QNdiKit，设置输出变量和创建目标
if(QNdiKit_FOUND)
    set(QNdiKit_INCLUDE_DIRS ${QNdiKit_INCLUDE_DIR})
    set(QNdiKit_LIBRARIES
        ${QNdiKit_NDI_SOURCE_CORE_LIBRARY}
        ${QNdiKit_NDI_SOURCE_WIDGETS_LIBRARY}
        ${QNdiKit_NDI_SOURCE_QUICK_LIBRARY}
        ${QNdiKit_NDI_MANAGER_CORE_LIBRARY}
        ${QNdiKit_NDI_MANAGER_WIDGETS_LIBRARY}
        ${QNdiKit_NDI_MANAGER_QUICK_LIBRARY}
    )
    
    # 尝试获取版本信息
    if(EXISTS "${QNdiKit_INCLUDE_DIR}/QNdiKit/version.h")
        file(READ "${QNdiKit_INCLUDE_DIR}/QNdiKit/version.h" QNdiKit_VERSION_RAW)
        string(REGEX MATCH "QNDIKIT_VERSION \"([^\"]+)\"" QNdiKit_VERSION_MATCH "${QNdiKit_VERSION_RAW}")
        if(QNdiKit_VERSION_MATCH)
            set(QNdiKit_VERSION "${CMAKE_MATCH_1}")
        else()
            set(QNdiKit_VERSION "Unknown")
        endif()
    else()
        set(QNdiKit_VERSION "Unknown")
    endif()
    
    # 创建导入目标
    if(NOT TARGET QNdiKit::ndi_source_core AND QNdiKit_NDI_SOURCE_CORE_LIBRARY)
        add_library(QNdiKit::ndi_source_core UNKNOWN IMPORTED)
        set_target_properties(QNdiKit::ndi_source_core PROPERTIES
            IMPORTED_LOCATION "${QNdiKit_NDI_SOURCE_CORE_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${QNdiKit_INCLUDE_DIR}"
        )
    endif()
    
    if(NOT TARGET QNdiKit::ndi_source_widgets AND QNdiKit_NDI_SOURCE_WIDGETS_LIBRARY)
        add_library(QNdiKit::ndi_source_widgets UNKNOWN IMPORTED)
        set_target_properties(QNdiKit::ndi_source_widgets PROPERTIES
            IMPORTED_LOCATION "${QNdiKit_NDI_SOURCE_WIDGETS_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${QNdiKit_INCLUDE_DIR}"
        )
        if(TARGET QNdiKit::ndi_source_core)
            set_target_properties(QNdiKit::ndi_source_widgets PROPERTIES
                INTERFACE_LINK_LIBRARIES QNdiKit::ndi_source_core
            )
        endif()
    endif()
    
    if(NOT TARGET QNdiKit::ndi_source_quick AND QNdiKit_NDI_SOURCE_QUICK_LIBRARY)
        add_library(QNdiKit::ndi_source_quick UNKNOWN IMPORTED)
        set_target_properties(QNdiKit::ndi_source_quick PROPERTIES
            IMPORTED_LOCATION "${QNdiKit_NDI_SOURCE_QUICK_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${QNdiKit_INCLUDE_DIR}"
        )
        if(TARGET QNdiKit::ndi_source_core)
            set_target_properties(QNdiKit::ndi_source_quick PROPERTIES
                INTERFACE_LINK_LIBRARIES QNdiKit::ndi_source_core
            )
        endif()
    endif()
    
    if(NOT TARGET QNdiKit::ndi_manager_core AND QNdiKit_NDI_MANAGER_CORE_LIBRARY)
        add_library(QNdiKit::ndi_manager_core UNKNOWN IMPORTED)
        set_target_properties(QNdiKit::ndi_manager_core PROPERTIES
            IMPORTED_LOCATION "${QNdiKit_NDI_MANAGER_CORE_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${QNdiKit_INCLUDE_DIR}"
        )
    endif()
    
    if(NOT TARGET QNdiKit::ndi_manager_widgets AND QNdiKit_NDI_MANAGER_WIDGETS_LIBRARY)
        add_library(QNdiKit::ndi_manager_widgets UNKNOWN IMPORTED)
        set_target_properties(QNdiKit::ndi_manager_widgets PROPERTIES
            IMPORTED_LOCATION "${QNdiKit_NDI_MANAGER_WIDGETS_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${QNdiKit_INCLUDE_DIR}"
        )
        if(TARGET QNdiKit::ndi_manager_core)
            set_target_properties(QNdiKit::ndi_manager_widgets PROPERTIES
                INTERFACE_LINK_LIBRARIES QNdiKit::ndi_manager_core
            )
        endif()
    endif()
    
    if(NOT TARGET QNdiKit::ndi_manager_quick AND QNdiKit_NDI_MANAGER_QUICK_LIBRARY)
        add_library(QNdiKit::ndi_manager_quick UNKNOWN IMPORTED)
        set_target_properties(QNdiKit::ndi_manager_quick PROPERTIES
            IMPORTED_LOCATION "${QNdiKit_NDI_MANAGER_QUICK_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${QNdiKit_INCLUDE_DIR}"
        )
        if(TARGET QNdiKit::ndi_manager_core)
            set_target_properties(QNdiKit::ndi_manager_quick PROPERTIES
                INTERFACE_LINK_LIBRARIES QNdiKit::ndi_manager_core
            )
        endif()
    endif()
    
    message(STATUS "找到 QNdiKit: ${QNdiKit_INCLUDE_DIR}")
    message(STATUS "  - 版本: ${QNdiKit_VERSION}")
endif()

# 标记为高级变量
mark_as_advanced(
    QNdiKit_INCLUDE_DIR
    QNdiKit_NDI_SOURCE_CORE_LIBRARY
    QNdiKit_NDI_SOURCE_WIDGETS_LIBRARY
    QNdiKit_NDI_SOURCE_QUICK_LIBRARY
    QNdiKit_NDI_MANAGER_CORE_LIBRARY
    QNdiKit_NDI_MANAGER_WIDGETS_LIBRARY
    QNdiKit_NDI_MANAGER_QUICK_LIBRARY
) 