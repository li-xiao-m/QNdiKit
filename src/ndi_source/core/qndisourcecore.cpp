#include "qndisourcecore.h"
#include <QtCore/QString>

QT_BEGIN_NAMESPACE

class QNdiSourceCore::Private
{
public:
    bool initialized = false;
    QString version = "1.0.0";
    QString description = "QNdiSource Core Module";
    QString name;
};

QNdiSourceCore::QNdiSourceCore(QObject *parent)
    : QObject(parent), d(new Private)
{
}

QNdiSourceCore::~QNdiSourceCore()
{
    shutdown();
    delete d;
}

bool QNdiSourceCore::initialize()
{
    if (d->initialized) {
        return true;
    }
    
    // 此处预留NDI初始化实现
    d->initialized = true;
    return true;
}

void QNdiSourceCore::shutdown()
{
    // 预留资源释放实现
}

bool QNdiSourceCore::isInitialized() const
{
    return d->initialized;
}

QString QNdiSourceCore::getVersion() const
{
    return d->version;
}

QString QNdiSourceCore::getDescription() const
{
    return d->description;
}

void QNdiSourceCore::setName(const QString &name)
{
    if (d->name != name) {
        d->name = name;
        emit nameChanged();
    }
}

QString QNdiSourceCore::name() const
{
    return d->name;
}

QStringList QNdiSourceCore::findSources()
{
    // 预留NDI源查找实现
    return QStringList();
}

QStringList QNdiSourceCore::findReceivers()
{
    // 预留NDI接收器查找实现
    return QStringList();
}

QNdiSourceCore* QNdiSourceCore::create()
{
    return new QNdiSourceCore();
}

QT_END_NAMESPACE 