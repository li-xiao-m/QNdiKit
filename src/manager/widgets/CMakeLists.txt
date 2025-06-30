# QNdiKit Manager Widgets Module
# NDI 管理器 Widgets 功能模块

set(MANAGER_WIDGETS_SOURCES
    qndikitmanagerwidget.cpp
    qndikitmanagercontrol.cpp
    qndikitdiscoverywidget.cpp
)

set(MANAGER_WIDGETS_HEADERS
    qndikitmanagerwidget.h
    qndikitmanagercontrol.h
    qndikitdiscoverywidget.h
)

# 创建管理器 Widgets 库
if(QNdiKit_BUILD_STATIC)
    add_library(QNdiKitManagerWidgets STATIC ${MANAGER_WIDGETS_SOURCES} ${MANAGER_WIDGETS_HEADERS})
else()
    add_library(QNdiKitManagerWidgets SHARED ${MANAGER_WIDGETS_SOURCES} ${MANAGER_WIDGETS_HEADERS})
endif()

# 设置目标属性
set_target_properties(QNdiKitManagerWidgets PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME "QNdiKitManagerWidgets"
    DEFINE_SYMBOL QNDIKIT_MANAGER_WIDGETS_LIBRARY
)

# 链接依赖库
target_link_libraries(QNdiKitManagerWidgets
    QNdiKit::ManagerCore
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    NDI::NDI
)

# 包含目录
target_include_directories(QNdiKitManagerWidgets
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/QNdiKit/Manager>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# 启用 Qt 的 AUTOMOC
set_target_properties(QNdiKitManagerWidgets PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC OFF
)

# 创建命名空间别名
add_library(QNdiKit::ManagerWidgets ALIAS QNdiKitManagerWidgets)

# 安装配置
if(QNdiKit_INSTALL)
    install(TARGETS QNdiKitManagerWidgets
        EXPORT QNdiKitTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    
    install(FILES ${MANAGER_WIDGETS_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/QNdiKit/Manager
    )
endif() 