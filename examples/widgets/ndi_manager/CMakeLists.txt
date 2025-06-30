# NDI Manager Demo

set(CMAKE_AUTOMOC ON)

add_executable(ndi_manager_demo
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

target_link_libraries(ndi_manager_demo
    QNdiKit::ManagerCore
    QNdiKit::ManagerWidgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)

# 设置包含目录
target_include_directories(ndi_manager_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 安装
if(QNdiKit_INSTALL)
    install(TARGETS ndi_manager_demo
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif() 