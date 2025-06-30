#include <QApplication>
#include <QMessageBox>
#include <QDir>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // 检查 QNdiKit 是否正确加载
    try {
        // 这里可以添加 QNdiKit 的初始化代码
        QMessageBox::information(nullptr, "QNdiKit 外部项目示例", 
            "QNdiKit 库已成功加载！\n\n"
            "这个示例展示了如何在外部项目中使用 QNdiKit。\n"
            "请查看 CMakeLists.txt 了解如何配置 NDI SDK 路径。\0");
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "错误", 
            QString("QNdiKit 初始化失败：%1").arg(e.what()));
        return 1;
    }
    
    MainWindow window;
    window.show();
    
    return app.exec();
} 
