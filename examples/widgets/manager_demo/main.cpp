#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include "qndimanagerwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("QNdiManager Widgets Demo");
    mainWindow.resize(500, 400);
    
    auto centralWidget = new QWidget(&mainWindow);
    mainWindow.setCentralWidget(centralWidget);
    
    auto layout = new QVBoxLayout(centralWidget);
    
    // 标题
    auto titleLabel = new QLabel("QNdiManager Widgets 演示程序", centralWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px;");
    layout->addWidget(titleLabel);
    
    // 说明
    auto descLabel = new QLabel("这是 NDI Manager 模块的独立演示程序\n用于管理和监控 NDI 网络", centralWidget);
    descLabel->setAlignment(Qt::AlignCenter);
    descLabel->setStyleSheet("color: gray; margin: 10px;");
    layout->addWidget(descLabel);
    
    // NDI Manager Widget
    auto managerWidget = new QNdiManagerWidget();
    layout->addWidget(managerWidget);
    
    mainWindow.show();
    
    return app.exec();
} 