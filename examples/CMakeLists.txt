# Examples - 根据启用的模块自动编译对应的examples
if(QNdiKit_BUILD_EXAMPLES)
    # Source Widgets Example
    if(QNdiKit_BUILD_NDI_SOURCE_WIDGETS)
        add_subdirectory(widgets/source_demo)
    endif()
    
    # Source Quick Example
    if(QNdiKit_BUILD_NDI_SOURCE_QUICK)
        add_subdirectory(quick/source_demo)
    endif()
    
    # Manager Widgets Example
    if(QNdiKit_BUILD_NDI_MANAGER_WIDGETS)
        add_subdirectory(widgets/manager_demo)
    endif()
    
    # Manager Quick Example
    if(QNdiKit_BUILD_NDI_MANAGER_QUICK)
        add_subdirectory(quick/manager_demo)
    endif()
endif()
