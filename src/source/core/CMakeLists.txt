# QNdiKit Source Core Module
# NDI 源核心功能模块

set(SOURCE_CORE_SOURCES
    qndikitsourcecore.cpp
    qndikitsource.cpp
    qndikitsourcefactory.cpp
)

set(SOURCE_CORE_HEADERS
    qndikitsourcecore.h
    qndikitsource.h
    qndikitsourcefactory.h
    qndikitsource_global.h
)

# 创建源核心库
add_library(QNdiKitSourceCore SHARED dummy.cpp)

# 设置目标属性
set_target_properties(QNdiKitSourceCore PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME "QNdiKitSourceCore"
    DEFINE_SYMBOL QNDIKIT_SOURCE_CORE_LIBRARY
    AUTOMOC ON
)

# 链接依赖库
target_link_libraries(QNdiKitSourceCore
    Qt${QT_VERSION_MAJOR}::Core
    NDI::NDI
)

# 包含目录
target_include_directories(QNdiKitSourceCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/QNdiKit/Source>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# 创建命名空间别名
add_library(QNdiKit::SourceCore ALIAS QNdiKitSourceCore)

# 安装配置
if(QNdiKit_INSTALL)
    install(TARGETS QNdiKitSourceCore
        EXPORT QNdiKitTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    
    install(FILES ${SOURCE_CORE_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/QNdiKit/Source
    )
endif() 