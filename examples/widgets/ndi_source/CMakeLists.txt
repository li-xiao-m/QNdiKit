# NDI Source Demo

set(CMAKE_AUTOMOC ON)

add_executable(ndi_source_demo
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

set_target_properties(ndi_source_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out
)

target_link_libraries(ndi_source_demo
    QNdiKit::SourceCore
    QNdiKit::SourceWidgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)

# 设置包含目录
target_include_directories(ndi_source_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 安装
if(QNdiKit_INSTALL)
    install(TARGETS ndi_source_demo
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif() 