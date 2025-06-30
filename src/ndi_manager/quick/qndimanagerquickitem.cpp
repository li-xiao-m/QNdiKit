#include "qndimanagerquickitem.h"
#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

class QNdiManagerQuickItem::Private
{
public:
    QStringList sources;
    QStringList receivers;
    QString status = "NDI Manager 状态: 就绪";
};

QNdiManagerQuickItem::QNdiManagerQuickItem(QQuickItem *parent)
    : QQuickItem(parent)
    , d(new Private)
{
}

QNdiManagerQuickItem::~QNdiManagerQuickItem()
{
    delete d;
}

QStringList QNdiManagerQuickItem::sources() const
{
    return d->sources;
}

QStringList QNdiManagerQuickItem::receivers() const
{
    return d->receivers;
}

QString QNdiManagerQuickItem::status() const
{
    return d->status;
}

void QNdiManagerQuickItem::scanSources()
{
    QStringList newSources;
    newSources << "Camera 1" << "Camera 2" << "Screen Capture" << "Test Source";
    d->sources = newSources;
    d->status = "NDI Manager 状态: 已扫描到 " + QString::number(d->sources.size()) + " 个源";
    emit sourcesChanged();
    emit statusChanged();
    qDebug() << "QNdiManager Quick Item: 扫描到" << d->sources.size() << "个源";
}

void QNdiManagerQuickItem::scanReceivers()
{
    QStringList newReceivers;
    newReceivers << "Monitor 1" << "Monitor 2" << "Recording System";
    d->receivers = newReceivers;
    d->status = "NDI Manager 状态: 已扫描到 " + QString::number(d->receivers.size()) + " 个接收器";
    emit receiversChanged();
    emit statusChanged();
    qDebug() << "QNdiManager Quick Item: 扫描到" << d->receivers.size() << "个接收器";
}

void QNdiManagerQuickItem::showInfo()
{
    qDebug() << "QNdiManager Quick Item 信息:";
    qDebug() << "这是 QNdiManager Quick 模块";
    qDebug() << "用于在 QML 中管理和监控 NDI 网络";
    qDebug() << "可以扫描和发现 NDI 源和接收器";
}

QT_END_NAMESPACE 