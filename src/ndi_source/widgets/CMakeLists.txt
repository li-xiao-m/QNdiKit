set(TARGET_NAME QNdiSourceWidgets)

# 收集源文件
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")

# 创建库
if(QNdiKit_BUILD_STATIC)
    add_library(${TARGET_NAME} STATIC ${SOURCES} ${HEADERS})
else()
    add_library(${TARGET_NAME} SHARED ${SOURCES} ${HEADERS})
endif()

# 设置目标属性
set_target_properties(${TARGET_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME "QNdiSourceWidgets"
    DEFINE_SYMBOL QNDISOURCEWIDGETS_EXPORTS
    AUTOMOC ON
)

# 链接依赖 - 只链接内部模块依赖
target_link_libraries(${TARGET_NAME}
    PUBLIC
        QNdiSourceCore
        NDI::NDI
        Qt${QT_VERSION_MAJOR}::Widgets
)

# 包含目录
target_include_directories(${TARGET_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../core>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/QNdiKit/ndi_source/core>
    )

add_library(QNdiKit::ndi_source_widgets ALIAS QNdiSourceWidgets)

# 安装
if(QNdiKit_INSTALL)
    install(TARGETS ${TARGET_NAME}
        EXPORT QNdiKitTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/QNdiKit/ndi_source/widgets)
endif() 