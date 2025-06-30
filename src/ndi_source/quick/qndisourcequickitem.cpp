#include "qndisourcequickitem.h"
#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

class QNdiSourceQuickItem::Private
{
public:
    bool isRunning = false;
    QString status = "NDI Source 状态: 未启动";
    QString sourceName;
};

QNdiSourceQuickItem::QNdiSourceQuickItem(QQuickItem *parent)
    : QQuickItem(parent)
    , d(new Private)
{
}

QNdiSourceQuickItem::~QNdiSourceQuickItem()
{
    delete d;
}

void QNdiSourceQuickItem::startSource()
{
    if (!d->isRunning) {
        d->isRunning = true;
        d->status = "NDI Source 状态: 运行中";
        qDebug() << "QNdiSource Quick Item: 启动 NDI Source";
    }
}

void QNdiSourceQuickItem::stopSource()
{
    if (d->isRunning) {
        d->isRunning = false;
        d->status = "NDI Source 状态: 已停止";
        qDebug() << "QNdiSource Quick Item: 停止 NDI Source";
    }
}

void QNdiSourceQuickItem::showInfo()
{
    qDebug() << "QNdiSource Quick Item 信息:";
    qDebug() << "这是 QNdiSource Quick 模块";
    qDebug() << "用于在 QML 中创建和管理 NDI 视频源";
    qDebug() << "可以发送视频流到 NDI 网络";
}

QString QNdiSourceQuickItem::sourceName() const
{
    return d->sourceName;
}

void QNdiSourceQuickItem::setSourceName(const QString &name)
{
    if (d->sourceName != name) {
        d->sourceName = name;
        emit sourceNameChanged();
    }
}

QT_END_NAMESPACE 
