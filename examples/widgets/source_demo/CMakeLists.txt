add_executable(QNdiSourceWidgetsDemo main.cpp)

# 查找必要的依赖包
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(NDI REQUIRED)

target_link_libraries(QNdiSourceWidgetsDemo
    QNdiKit::ndi_source_widgets
    Qt${QT_VERSION_MAJOR}::Core
)

if(QNdiKit_INSTALL)
    install(TARGETS QNdiSourceWidgetsDemo RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif() 
