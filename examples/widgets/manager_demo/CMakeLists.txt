add_executable(QNdiManagerWidgetsDemo main.cpp)
set_target_properties(QNdiManagerWidgetsDemo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out
)

# 查找必要的依赖包
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(NDI REQUIRED)

target_link_libraries(QNdiManagerWidgetsDemo
    QNdiKit::ndi_manager_widgets
    Qt${QT_VERSION_MAJOR}::Core
)

if(QNdiKit_INSTALL)
    install(TARGETS QNdiManagerWidgetsDemo RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif() 