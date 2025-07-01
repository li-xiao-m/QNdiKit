add_executable(QNdiManagerQuickDemo main.cpp qml.qrc)
set_target_properties(QNdiManagerQuickDemo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out
)

# 查找必要的依赖包
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)
find_package(NDI REQUIRED)

target_link_libraries(QNdiManagerQuickDemo
    QNdiKit::ndi_manager_quick
    Qt${QT_VERSION_MAJOR}::Core
)

# 确保资源文件被正确处理
set_target_properties(QNdiManagerQuickDemo PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
)

if(QNdiKit_INSTALL)
    install(TARGETS QNdiManagerQuickDemo RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
    install(FILES main.qml DESTINATION ${CMAKE_INSTALL_DATADIR}/QNdiKit/examples/manager_quick)
endif() 