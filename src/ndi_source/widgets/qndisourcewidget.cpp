#include "qndisourcewidget.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>

QT_BEGIN_NAMESPACE

class QNdiSourceWidget::Private
{
public:
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *infoButton;
    QLabel *statusLabel;
    bool isRunning = false;
    QString sourceName;
};

QNdiSourceWidget::QNdiSourceWidget(QWidget *parent)
    : QWidget(parent)
    , d(new Private)
{
    setWindowTitle("QNdiSource Widget");
    resize(300, 200);

    auto layout = new QVBoxLayout(this);
    
    d->statusLabel = new QLabel("NDI Source 状态: 未启动", this);
    layout->addWidget(d->statusLabel);
    
    d->startButton = new QPushButton("启动 NDI Source", this);
    layout->addWidget(d->startButton);
    
    d->stopButton = new QPushButton("停止 NDI Source", this);
    layout->addWidget(d->stopButton);
    
    d->infoButton = new QPushButton("显示信息", this);
    layout->addWidget(d->infoButton);
    
    connect(d->startButton, &QPushButton::clicked, this, &QNdiSourceWidget::startSource);
    connect(d->stopButton, &QPushButton::clicked, this, &QNdiSourceWidget::stopSource);
    connect(d->infoButton, &QPushButton::clicked, this, &QNdiSourceWidget::showInfo);
    
    d->stopButton->setEnabled(false);
}

QNdiSourceWidget::~QNdiSourceWidget()
{
    delete d;
}

void QNdiSourceWidget::startSource()
{
    if (!d->isRunning) {
        d->isRunning = true;
        d->statusLabel->setText("NDI Source 状态: 运行中");
        d->startButton->setEnabled(false);
        d->stopButton->setEnabled(true);
    }
}

void QNdiSourceWidget::stopSource()
{
    if (d->isRunning) {
        d->isRunning = false;
        d->statusLabel->setText("NDI Source 状态: 已停止");
        d->startButton->setEnabled(true);
        d->stopButton->setEnabled(false);
    }
}

void QNdiSourceWidget::showInfo()
{
    QMessageBox::information(this, "QNdiSource Widget 信息", 
        "这是 QNdiSource Widget 模块\n"
        "用于创建和管理 NDI 视频源\n"
        "可以发送视频流到 NDI 网络");
}

QString QNdiSourceWidget::sourceName() const
{
    return d->sourceName;
}

void QNdiSourceWidget::setSourceName(const QString &name)
{
    if (d->sourceName != name) {
        d->sourceName = name;
        emit sourceNameChanged();
    }
}

QT_END_NAMESPACE 