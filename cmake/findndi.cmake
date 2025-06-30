# FindNDI.cmake - 查找 NDI SDK
#
# 这个模块会尝试自动查找 NDI SDK 的安装路径
# 如果找不到，会提示用户手动设置 NDI_SDK_ROOT 变量
#
# 定义以下变量：
#   NDI_FOUND - 如果找到 NDI SDK 则为 TRUE
#   NDI_INCLUDE_DIRS - NDI SDK 头文件目录
#   NDI_LIBRARIES - NDI SDK 库文件
#   NDI_VERSION - NDI SDK 版本号

# 设置 NDI SDK 的默认搜索路径
set(NDI_SEARCH_PATHS
    "C:/Program Files/NDI/NDI 6 SDK"
    "C:/Program Files/NDI/NDI 5 SDK"
    "C:/Program Files/NDI/NDI 4 SDK"
    "C:/Program Files (x86)/NDI/NDI 6 SDK"
    "C:/Program Files (x86)/NDI/NDI 5 SDK"
    "C:/Program Files (x86)/NDI/NDI 4 SDK"
    "$ENV{PROGRAMFILES}/NDI/NDI 6 SDK"
    "$ENV{PROGRAMFILES}/NDI/NDI 5 SDK"
    "$ENV{PROGRAMFILES}/NDI/NDI 4 SDK"
    "$ENV{PROGRAMFILES_X86}/NDI/NDI 6 SDK"
    "$ENV{PROGRAMFILES_X86}/NDI/NDI 5 SDK"
    "$ENV{PROGRAMFILES_X86}/NDI/NDI 4 SDK"
    "/usr/local/ndi"
    "/opt/ndi"
)

# 优先使用 NDI_PATH
if(DEFINED NDI_PATH)
    if(NOT EXISTS "${NDI_PATH}")
        message(FATAL_ERROR "\n============================================\nNDI_PATH 路径不存在！\n============================================\n\n指定的 NDI_PATH 路径不存在：\n${NDI_PATH}\n\n请检查路径是否正确。\n============================================\n")
    endif()
    if(NOT EXISTS "${NDI_PATH}/include/Processing.NDI.Lib.h" AND 
       NOT EXISTS "${NDI_PATH}/Include/Processing.NDI.Lib.h")
        message(FATAL_ERROR "\n============================================\nNDI_PATH 路径无效！\n============================================\n\n指定的路径 ${NDI_PATH} 存在，但不包含 NDI SDK 文件。\n\n请确保该路径包含以下文件之一：\n- include/Processing.NDI.Lib.h\n- Include/Processing.NDI.Lib.h\n============================================\n")
    endif()
    set(NDI_SDK_ROOT_FOUND "${NDI_PATH}")
else()
    # 如果用户已经设置了 NDI_SDK_ROOT，优先使用并验证路径
    if(DEFINED NDI_SDK_ROOT)
        if(NOT EXISTS "${NDI_SDK_ROOT}")
            message(FATAL_ERROR "\n        ============================================\n        NDI SDK 路径不存在！\n        ============================================\n        \n        指定的 NDI_SDK_ROOT 路径不存在：\n        ${NDI_SDK_ROOT}\n        \n        请检查路径是否正确，或使用以下默认路径之一：\n        ${NDI_SEARCH_PATHS}\n        \n        或者重新运行 cmake 命令，不指定 NDI_SDK_ROOT 参数，\n        让系统自动查找默认安装路径。\n        ============================================\n        ")
        endif()
        # 验证指定路径是否包含 NDI SDK 文件
        if(NOT EXISTS "${NDI_SDK_ROOT}/include/Processing.NDI.Lib.h" AND 
           NOT EXISTS "${NDI_SDK_ROOT}/Include/Processing.NDI.Lib.h")
            message(FATAL_ERROR "\n        ============================================\n        NDI SDK 路径无效！\n        ============================================\n        \n        指定的路径 ${NDI_SDK_ROOT} 存在，但不包含 NDI SDK 文件。\n        \n        请确保该路径包含以下文件之一：\n        - include/Processing.NDI.Lib.h\n        - Include/Processing.NDI.Lib.h\n        \n        或者使用以下默认路径之一：\n        ${NDI_SEARCH_PATHS}\n        ============================================\n        ")
        endif()
        set(NDI_SDK_ROOT_FOUND "${NDI_SDK_ROOT}")
    else()
        # 用户未指定路径，搜索默认路径
        find_path(NDI_SDK_ROOT_FOUND
            NAMES
                "include/Processing.NDI.Lib.h"
                "include/Processing.NDI.Lib.h"
                "Include/Processing.NDI.Lib.h"
            PATHS ${NDI_SEARCH_PATHS}
            DOC "NDI SDK 根目录路径"
        )
    endif()
endif()

# 如果找不到 NDI SDK，显示错误信息
if(NOT NDI_SDK_ROOT_FOUND)
    message(FATAL_ERROR "
    ============================================
    NDI SDK 未找到！
    ============================================
    
    请执行以下操作之一：
    
    1. 安装 NDI SDK 到默认位置：
       C:\\Program Files\\NDI\\NDI 6 SDK
    
    2. 或者设置 NDI_SDK_ROOT 变量指向 NDI SDK 安装目录：
       cmake -DNDI_SDK_ROOT=\"C:/path/to/your/ndi/sdk\" ..
    
    3. 或者设置环境变量 NDI_SDK_ROOT
    
    搜索的路径包括：
    ${NDI_SEARCH_PATHS}
    ============================================
    ")
endif()

# 设置找到的 NDI SDK 根目录
set(NDI_SDK_ROOT "${NDI_SDK_ROOT_FOUND}")

# 查找头文件目录
find_path(NDI_INCLUDE_DIR
    NAMES
        "Processing.NDI.Lib.h"
        "Processing.NDI.Lib.h"
    PATHS
        "${NDI_SDK_ROOT}/include"
        "${NDI_SDK_ROOT}/Include"
        "${NDI_SDK_ROOT}"
    DOC "NDI SDK 头文件目录"
)

# 根据平台确定库文件路径和名称
if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        # 64位 Windows
        set(NDI_LIB_SEARCH_PATHS
            "${NDI_SDK_ROOT}/lib/x64"
            "${NDI_SDK_ROOT}/Lib/x64"
            "${NDI_SDK_ROOT}/lib"
            "${NDI_SDK_ROOT}/Lib"
        )
        set(NDI_LIB_NAME "Processing.NDI.Lib.x64")
    else()
        # 32位 Windows
        set(NDI_LIB_SEARCH_PATHS
            "${NDI_SDK_ROOT}/lib/x86"
            "${NDI_SDK_ROOT}/Lib/x86"
            "${NDI_SDK_ROOT}/lib"
            "${NDI_SDK_ROOT}/Lib"
        )
        set(NDI_LIB_NAME "Processing.NDI.Lib.x86")
    endif()
elseif(APPLE)
    set(NDI_LIB_SEARCH_PATHS
        "${NDI_SDK_ROOT}/lib/macOS"
        "${NDI_SDK_ROOT}/lib"
    )
    set(NDI_LIB_NAME "ndi")
elseif(UNIX)
    set(NDI_LIB_SEARCH_PATHS
        "${NDI_SDK_ROOT}/lib/linux"
        "${NDI_SDK_ROOT}/lib"
    )
    set(NDI_LIB_NAME "ndi")
endif()

# 查找库文件
find_library(NDI_LIBRARY
    NAMES ${NDI_LIB_NAME}
    PATHS ${NDI_LIB_SEARCH_PATHS}
    DOC "NDI SDK 库文件"
)

# 检查是否找到了所有必需的文件
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(NDI
    REQUIRED_VARS
        NDI_SDK_ROOT
        NDI_INCLUDE_DIR
        NDI_LIBRARY
    FAIL_MESSAGE "NDI SDK 未找到或配置不正确"
)

# 如果找到了 NDI SDK，设置输出变量
if(NDI_FOUND)
    set(NDI_INCLUDE_DIRS ${NDI_INCLUDE_DIR})
    set(NDI_LIBRARIES ${NDI_LIBRARY})
    
    # 尝试获取版本信息
    if(EXISTS "${NDI_SDK_ROOT}/version.txt")
        file(READ "${NDI_SDK_ROOT}/version.txt" NDI_VERSION_RAW)
        string(STRIP "${NDI_VERSION_RAW}" NDI_VERSION)
    else()
        set(NDI_VERSION "Unknown")
    endif()
    
    # 创建导入目标
    if(NOT TARGET NDI::NDI)
        add_library(NDI::NDI UNKNOWN IMPORTED)
        set_target_properties(NDI::NDI PROPERTIES
            IMPORTED_LOCATION "${NDI_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${NDI_INCLUDE_DIR}"
        )
        
        # 在 Windows 上添加运行时库路径
        if(WIN32)
            set_target_properties(NDI::NDI PROPERTIES
                IMPORTED_LOCATION_DEBUG "${NDI_LIBRARY}"
                IMPORTED_LOCATION_RELEASE "${NDI_LIBRARY}"
            )
        endif()
    endif()
    
    message(STATUS "找到 NDI SDK: ${NDI_SDK_ROOT}")
    message(STATUS "  - 版本: ${NDI_VERSION}")
    message(STATUS "  - 头文件: ${NDI_INCLUDE_DIR}")
    message(STATUS "  - 库文件: ${NDI_LIBRARY}")
endif()

# 标记为高级变量
mark_as_advanced(NDI_INCLUDE_DIR NDI_LIBRARY) 