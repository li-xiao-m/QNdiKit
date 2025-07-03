set(TARGET_NAME QNdiManagerCore)

# 收集源文件
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")

# 创建库
if(QNdiKit_BUILD_STATIC)
    add_library(${TARGET_NAME} STATIC ${SOURCES} ${HEADERS})
else()
    find_package(Qt5 REQUIRED COMPONENTS Core)

    add_library(${TARGET_NAME} SHARED ${SOURCES} ${HEADERS})

target_link_libraries(QNdiManagerCore PRIVATE 
    Qt${QT_VERSION_MAJOR}::Core 
    Qt${QT_VERSION_MAJOR}::Gui 
    Qt${QT_VERSION_MAJOR}::Quick)
endif()

set_target_properties(${TARGET_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tmp
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out
)

# 设置目标属性
set_target_properties(${TARGET_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME "QNdiManagerCore"
    DEFINE_SYMBOL QNDIMANAGERCORE_EXPORTS
    AUTOMOC ON 
)

# 链接依赖 - 只链接必要的依赖
target_link_libraries(${TARGET_NAME} 
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Qml
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Quick
        NDI::NDI
)

# 包含目录
target_include_directories(${TARGET_NAME} 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_library(QNdiKit::ndi_manager_core ALIAS QNdiManagerCore)

# 安装
if(QNdiKit_INSTALL)
    install(TARGETS ${TARGET_NAME}
        EXPORT QNdiKitTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/QNdiKit/ndi_manager/core)
endif() 
