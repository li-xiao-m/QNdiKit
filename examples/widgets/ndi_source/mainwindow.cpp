#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    QLabel *label = new QLabel("NDI Source Demo", this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    
    QPushButton *btn = new QPushButton("点击测试", this);
    layout->addWidget(btn);
    connect(btn, &QPushButton::clicked, this, [](){
        QMessageBox::information(nullptr, "提示", "NDI 源功能待实现");
    });
}

MainWindow::~MainWindow()
{
} 