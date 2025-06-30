# NDI Source 模块
if(QNdiKit_BUILD_NDI_SOURCE_WIDGETS OR QNdiKit_BUILD_NDI_SOURCE_QUICK)
    add_subdirectory(ndi_source)
endif()

# NDI Manager 模块
if(QNdiKit_BUILD_NDI_MANAGER_WIDGETS OR QNdiKit_BUILD_NDI_MANAGER_QUICK)
    add_subdirectory(ndi_manager)
endif()
