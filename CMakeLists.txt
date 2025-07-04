cmake_minimum_required(VERSION 3.16)

project(QNdiKit VERSION 0.1 LANGUAGES CXX)

# 安装路径配置
if(DEFINED QNdiKit_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "${QNdiKit_INSTALL_PREFIX}")
elseif(NOT DEFINED CMAKE_INSTALL_PREFIX)
    if(WIN32)
        set(CMAKE_INSTALL_PREFIX "D:/Program Files/QNdiKit")
    else()
        set(CMAKE_INSTALL_PREFIX "/usr/local") 
    endif() 
endif() 
  
if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release")
endif() 
 
if(LINUX AND NOT CMAKE_CROSSCOMPILING)
    set(CMAKE_INSTALL_RPATH "$ORIGIN") 
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH OFF)
endif()
 
set(CMAKE_POSITION_INDEPENDENT_CODE ON)  
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_C_VISIBILITY_PRESET "hidden")
set(CMAKE_CXX_VISIBILITY_PRESET "hidden")

option(QNdiKit_BUILD_STATIC "Build static libraries" OFF)
option(QNdiKit_BUILD_EXAMPLES "Build examples" ON)
option(QNdiKit_INSTALL "Install library" ON)

# NDI Source 模块选项
option(QNdiKit_BUILD_NDI_SOURCE_WIDGETS "Build ndi source widgets" ON)
option(QNdiKit_BUILD_NDI_SOURCE_QUICK "Build ndi source quick" ON)

# NDI Manager 模块选项
option(QNdiKit_BUILD_NDI_MANAGER_WIDGETS "Build ndi manager widgets" ON)
option(QNdiKit_BUILD_NDI_MANAGER_QUICK "Build ndi manager quick" ON)

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /manifest:no")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /manifest:no")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /manifest:no")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
    if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
        set(CMAKE_DEBUG_POSTFIX "d")
    endif()
elseif(MINGW)
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

if(QNdiKit_INSTALL)
    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers) 
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(NDI REQUIRED)

# Qt查找，支持Qt5和Qt6
find_package(Qt6 QUIET COMPONENTS Core Widgets Quick)
if(Qt6_FOUND)
    set(QT_VERSION_MAJOR 6)
else()
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets Quick)
    set(QT_VERSION_MAJOR 5)
endif()

add_subdirectory(src)
add_subdirectory(examples)

if(QNdiKit_INSTALL)
    install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindQNdiKit.cmake"
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/findndi.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QNdiKit
    )
    install(EXPORT QNdiKitTargets
        FILE QNdiKitTargets.cmake
        NAMESPACE QNdiKit::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QNdiKit
    )
    configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/QNdiKitConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/QNdiKitConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QNdiKit
        PATH_VARS CMAKE_INSTALL_INCLUDEDIR
    )
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/QNdiKitConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/QNdiKitConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/QNdiKitConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QNdiKit
    )
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/QNdiKit.pc.in"
        "${CMAKE_CURRENT_BINARY_DIR}/QNdiKit.pc"
        @ONLY
    )
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/QNdiKit.pc"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
    )
endif()

set_target_properties(${TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tmp  # .lib/.exp 输出到 tmp
)
