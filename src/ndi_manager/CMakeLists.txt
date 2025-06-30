# NDI Manager Core 模块（必须构建）
add_subdirectory(core)

# NDI Manager Widgets 模块
if(QNdiKit_BUILD_NDI_MANAGER_WIDGETS)
    add_subdirectory(widgets)
endif()

# NDI Manager Quick 模块
if(QNdiKit_BUILD_NDI_MANAGER_QUICK)
    add_subdirectory(quick)
endif() 