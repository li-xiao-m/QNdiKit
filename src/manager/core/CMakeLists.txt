# QNdiKit Manager Core Module
# NDI 管理器核心功能模块

set(MANAGER_CORE_SOURCES
    qndikitmanagercore.cpp
    qndikitmanager.cpp
    qndikitdiscovery.cpp
    qndikitconnection.cpp
)

set(MANAGER_CORE_HEADERS
    qndikitmanagercore.h
    qndikitmanager.h
    qndikitdiscovery.h
    qndikitconnection.h
    qndikitmanager_global.h
)

# 创建管理器核心库
if(QNdiKit_BUILD_STATIC)
    add_library(QNdiKitManagerCore STATIC ${MANAGER_CORE_SOURCES} ${MANAGER_CORE_HEADERS})
else()
    add_library(QNdiKitManagerCore SHARED ${MANAGER_CORE_SOURCES} ${MANAGER_CORE_HEADERS})
endif()

# 设置目标属性
set_target_properties(QNdiKitManagerCore PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME "QNdiKitManagerCore"
    DEFINE_SYMBOL QNDIKIT_MANAGER_CORE_LIBRARY
)

# 链接依赖库
target_link_libraries(QNdiKitManagerCore
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    NDI::NDI
)

# 包含目录
target_include_directories(QNdiKitManagerCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/QNdiKit/Manager>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# 启用 Qt 的 AUTOMOC
set_target_properties(QNdiKitManagerCore PROPERTIES
    AUTOMOC ON
    AUTOUIC OFF
    AUTORCC OFF
)

# 创建命名空间别名
add_library(QNdiKit::ManagerCore ALIAS QNdiKitManagerCore)

# 安装配置
if(QNdiKit_INSTALL)
    install(TARGETS QNdiKitManagerCore
        EXPORT QNdiKitTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    
    install(FILES ${MANAGER_CORE_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/QNdiKit/Manager
    )
endif() 