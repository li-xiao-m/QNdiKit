#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include "qndisourcewidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("QNdiSource Widgets Demo");
    mainWindow.resize(400, 300);
    
    auto centralWidget = new QWidget(&mainWindow);
    mainWindow.setCentralWidget(centralWidget);
    
    auto layout = new QVBoxLayout(centralWidget);
    
    // 标题
    auto titleLabel = new QLabel("QNdiSource Widgets 演示程序", centralWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px;");
    layout->addWidget(titleLabel);
    
    // 说明
    auto descLabel = new QLabel("这是 NDI Source 模块的独立演示程序\n用于创建和管理 NDI 视频源", centralWidget);
    descLabel->setAlignment(Qt::AlignCenter);
    descLabel->setStyleSheet("color: gray; margin: 10px;");
    layout->addWidget(descLabel);
    
    // NDI Source Widget
    auto sourceWidget = new QNdiSourceWidget();
    layout->addWidget(sourceWidget);
    
    mainWindow.show();
    
    return app.exec();
} 