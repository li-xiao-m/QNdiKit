#include "qndimanagerwidget.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class QNdiManagerWidget::Private
{
public:
    QPushButton *scanSourcesButton;
    QPushButton *scanReceiversButton;
    QPushButton *infoButton;
    QListWidget *sourcesList;
    QListWidget *receiversList;
    QLabel *statusLabel;
};

QNdiManagerWidget::QNdiManagerWidget(QWidget *parent)
    : QWidget(parent)
    , d(new Private)
{
    setWindowTitle("QNdiManager Widget");
    resize(400, 300);

    auto layout = new QVBoxLayout(this);
    
    d->statusLabel = new QLabel("NDI Manager 状态: 就绪", this);
    layout->addWidget(d->statusLabel);
    
    d->scanSourcesButton = new QPushButton("扫描 NDI 源", this);
    layout->addWidget(d->scanSourcesButton);
    
    d->sourcesList = new QListWidget(this);
    d->sourcesList->setMaximumHeight(100);
    layout->addWidget(d->sourcesList);
    
    d->scanReceiversButton = new QPushButton("扫描 NDI 接收器", this);
    layout->addWidget(d->scanReceiversButton);
    
    d->receiversList = new QListWidget(this);
    d->receiversList->setMaximumHeight(100);
    layout->addWidget(d->receiversList);
    
    d->infoButton = new QPushButton("显示信息", this);
    layout->addWidget(d->infoButton);
    
    connect(d->scanSourcesButton, &QPushButton::clicked, this, &QNdiManagerWidget::scanSources);
    connect(d->scanReceiversButton, &QPushButton::clicked, this, &QNdiManagerWidget::scanReceivers);
    connect(d->infoButton, &QPushButton::clicked, this, &QNdiManagerWidget::showInfo);
}

QNdiManagerWidget::~QNdiManagerWidget()
{
    delete d;
}

void QNdiManagerWidget::scanSources()
{
    d->sourcesList->clear();
    QStringList sources = {"Camera 1", "Camera 2", "Screen Capture", "Test Source"};
    d->sourcesList->addItems(sources);
    d->statusLabel->setText("NDI Manager 状态: 已扫描到 " + QString::number(sources.size()) + " 个源");
}

void QNdiManagerWidget::scanReceivers()
{
    d->receiversList->clear();
    QStringList receivers = {"Monitor 1", "Monitor 2", "Recording System"};
    d->receiversList->addItems(receivers);
    d->statusLabel->setText("NDI Manager 状态: 已扫描到 " + QString::number(receivers.size()) + " 个接收器");
}

void QNdiManagerWidget::showInfo()
{
    QMessageBox::information(this, "QNdiManager Widget 信息", 
        "这是 QNdiManager Widget 模块\n"
        "用于管理和监控 NDI 网络\n"
        "可以扫描和发现 NDI 源和接收器");
}

QStringList QNdiManagerWidget::sources() const
{
    QStringList result;
    for (int i = 0; i < d->sourcesList->count(); ++i) {
        result << d->sourcesList->item(i)->text();
    }
    return result;
}

QStringList QNdiManagerWidget::receivers() const
{
    QStringList result;
    for (int i = 0; i < d->receiversList->count(); ++i) {
        result << d->receiversList->item(i)->text();
    }
    return result;
}

QT_END_NAMESPACE 