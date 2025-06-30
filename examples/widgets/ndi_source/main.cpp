#include <QApplication>
#include <QMainWindow>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    MainWindow window;
    window.setWindowTitle("QNdiKit - NDI Source Demo");
    window.resize(800, 600);
    window.show();
    
    return app.exec();
} 