# QNdiKit Source Module
# NDI 源功能模块

# 核心源功能 - 必需
add_subdirectory(core)

# Widgets 源功能 - 可选
if(QNdiKit_BUILD_WIDGETS)
    add_subdirectory(widgets)
endif()

# QML 源功能 - 可选
if(QNdiKit_BUILD_QUICK)
    add_subdirectory(qml)
endif() 