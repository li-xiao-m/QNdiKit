# QNdiKit Manager QML Module
# NDI 管理器 QML 功能模块

set(MANAGER_QML_SOURCES
    qndikitmanagerquickitem.cpp
    qndikitmanagerquickview.cpp
    qndikitdiscoveryquickitem.cpp
)

set(MANAGER_QML_HEADERS
    qndikitmanagerquickitem.h
    qndikitmanagerquickview.h
    qndikitdiscoveryquickitem.h
)

# 创建管理器 QML 库
if(QNdiKit_BUILD_STATIC)
    add_library(QNdiKitManagerQml STATIC ${MANAGER_QML_SOURCES} ${MANAGER_QML_HEADERS})
else()
    add_library(QNdiKitManagerQml SHARED ${MANAGER_QML_SOURCES} ${MANAGER_QML_HEADERS})
endif()

# 设置目标属性
set_target_properties(QNdiKitManagerQml PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME "QNdiKitManagerQml"
    DEFINE_SYMBOL QNDIKIT_MANAGER_QML_LIBRARY
)

# 链接依赖库
target_link_libraries(QNdiKitManagerQml
    QNdiKit::ManagerCore
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    NDI::NDI
)

# 包含目录
target_include_directories(QNdiKitManagerQml
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/QNdiKit/Manager>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# 启用 Qt 的 AUTOMOC
set_target_properties(QNdiKitManagerQml PROPERTIES
    AUTOMOC ON
    AUTOUIC OFF
    AUTORCC OFF
)

# 创建命名空间别名
add_library(QNdiKit::ManagerQml ALIAS QNdiKitManagerQml)

# 安装配置
if(QNdiKit_INSTALL)
    install(TARGETS QNdiKitManagerQml
        EXPORT QNdiKitTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    
    install(FILES ${MANAGER_QML_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/QNdiKit/Manager
    )
endif() 