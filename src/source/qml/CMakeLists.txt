# QNdiKit Source QML Module
# NDI 源 QML 功能模块

set(SOURCE_QML_SOURCES
    qndikitsourcequickitem.cpp
    qndikitsourcequickview.cpp
    qndikitsourcequickmanager.cpp
)

set(SOURCE_QML_HEADERS
    qndikitsourcequickitem.h
    qndikitsourcequickview.h
    qndikitsourcequickmanager.h
)

# 创建源 QML 库
add_library(QNdiKitSourceQml SHARED dummy.cpp)

# 设置目标属性
set_target_properties(QNdiKitSourceQml PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME "QNdiKitSourceQml"
    DEFINE_SYMBOL QNDIKIT_SOURCE_QML_LIBRARY
    AUTOMOC ON
)

# 链接依赖库
target_link_libraries(QNdiKitSourceQml
    QNdiKit::SourceCore
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    NDI::NDI
)

# 包含目录
target_include_directories(QNdiKitSourceQml
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/QNdiKit/Source>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# 创建命名空间别名
add_library(QNdiKit::SourceQml ALIAS QNdiKitSourceQml)

# 安装配置
if(QNdiKit_INSTALL)
    install(TARGETS QNdiKitSourceQml
        EXPORT QNdiKitTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    
    install(FILES ${SOURCE_QML_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/QNdiKit/Source
    )
endif() 