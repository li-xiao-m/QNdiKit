# NDI Source Core 模块（必须构建）
add_subdirectory(core)

# NDI Source Widgets 模块
if(QNdiKit_BUILD_NDI_SOURCE_WIDGETS)
    add_subdirectory(widgets)
endif()

# NDI Source Quick 模块
if(QNdiKit_BUILD_NDI_SOURCE_QUICK)
    add_subdirectory(quick)
endif() 