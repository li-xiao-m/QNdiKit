# QNdiKit Manager Module
# NDI 管理器功能模块

# 核心管理器功能 - 必需
add_subdirectory(core)

# Widgets 管理器功能 - 可选
if(QNdiKit_BUILD_WIDGETS)
    add_subdirectory(widgets)
endif()

# QML 管理器功能 - 可选
if(QNdiKit_BUILD_QUICK)
    add_subdirectory(qml)
endif() 