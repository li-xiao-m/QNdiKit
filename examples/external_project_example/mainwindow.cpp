#include "mainwindow.h"
#include <QMessageBox>
#include <QApplication>

// 注意：这里我们只是演示，实际使用时需要包含 QNdiKit 头文件
// #include <QNdiKit/ndi_source_core.h>
// #include <QNdiKit/ndi_manager_core.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainLayout(nullptr)
    , m_ndiSourceGroup(nullptr)
    , m_ndiManagerGroup(nullptr)
{
    setupUI();
    setWindowTitle("QNdiKit 外部项目示例");
    resize(600, 400);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    
    m_mainLayout = new QVBoxLayout(m_centralWidget);
    
    // 添加标题
    QLabel *titleLabel = new QLabel("QNdiKit 外部项目使用示例", this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);
    
    // 添加说明
    QLabel *descLabel = new QLabel(
        "这个示例展示了如何在外部项目中使用 QNdiKit。\n"
        "请查看 CMakeLists.txt 了解如何配置 NDI SDK 路径。\0", this);
    descLabel->setAlignment(Qt::AlignCenter);
    descLabel->setWordWrap(true);
    m_mainLayout->addWidget(descLabel);
    
    // 创建 NDI Source 组
    createNdiSourceGroup();
    
    // 创建 NDI Manager 组
    createNdiManagerGroup();
    
    m_mainLayout->addStretch();
}

void MainWindow::createNdiSourceGroup()
{
    m_ndiSourceGroup = new QGroupBox("NDI Source 功能", this);
    QVBoxLayout *layout = new QVBoxLayout(m_ndiSourceGroup);
    
    QPushButton *testButton = new QPushButton("测试 NDI Source", this);
    connect(testButton, &QPushButton::clicked, this, &MainWindow::onTestNdiSource);
    layout->addWidget(testButton);
    
    m_mainLayout->addWidget(m_ndiSourceGroup);
}

void MainWindow::createNdiManagerGroup()
{
    m_ndiManagerGroup = new QGroupBox("NDI Manager 功能", this);
    QVBoxLayout *layout = new QVBoxLayout(m_ndiManagerGroup);
    
    QPushButton *testButton = new QPushButton("测试 NDI Manager", this);
    connect(testButton, &QPushButton::clicked, this, &MainWindow::onTestNdiManager);
    layout->addWidget(testButton);
    
    m_mainLayout->addWidget(m_ndiManagerGroup);
}

void MainWindow::onTestNdiSource()
{
    QMessageBox::information(this, "NDI Source 测试", 
        "NDI Source 功能测试\n\n"
        "在实际项目中，这里会调用 QNdiKit::NdiSourceCore 的功能。\n"
        "例如：\n"
        "- 创建 NDI 源\n"
        "- 设置源名称\n"
        "- 发送视频帧\n"
        "- 管理连接状态\0");
}

void MainWindow::onTestNdiManager()
{
    QMessageBox::information(this, "NDI Manager 测试", 
        "NDI Manager 功能测试\n\n"
        "在实际项目中，这里会调用 QNdiKit::NdiManagerCore 的功能。\n"
        "例如：\n"
        "- 查找网络中的 NDI 源\n"
        "- 连接到 NDI 源\n"
        "- 接收视频流\n"
        "- 管理多个连接");
} 
