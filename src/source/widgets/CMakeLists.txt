# QNdiKit Source Widgets Module
# NDI 源 Widgets 功能模块

set(SOURCE_WIDGETS_SOURCES
    qndikitsourcewidget.cpp
    qndikitsourceviewer.cpp
    qndikitsourcecontrol.cpp
)

set(SOURCE_WIDGETS_HEADERS
    qndikitsourcewidget.h
    qndikitsourceviewer.h
    qndikitsourcecontrol.h
)

# 创建源 Widgets 库
add_library(QNdiKitSourceWidgets SHARED dummy.cpp)

# 设置目标属性
set_target_properties(QNdiKitSourceWidgets PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME "QNdiKitSourceWidgets"
    DEFINE_SYMBOL QNDIKIT_SOURCE_WIDGETS_LIBRARY
    AUTOMOC ON
)

# 链接依赖库
target_link_libraries(QNdiKitSourceWidgets
    QNdiKit::SourceCore
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    NDI::NDI
)

# 包含目录
target_include_directories(QNdiKitSourceWidgets
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/QNdiKit/Source>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# 创建命名空间别名
add_library(QNdiKit::SourceWidgets ALIAS QNdiKitSourceWidgets)

# 安装配置
if(QNdiKit_INSTALL)
    install(TARGETS QNdiKitSourceWidgets
        EXPORT QNdiKitTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    
    install(FILES ${SOURCE_WIDGETS_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/QNdiKit/Source
    )
endif() 