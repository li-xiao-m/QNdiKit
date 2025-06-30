#include "qndimanagercore.h"
#include <QtCore/QString>
#include <QtCore/QStringList>

QT_BEGIN_NAMESPACE

class QNdiManagerCore::Private
{
public:
    bool initialized = false;
    QString version = "1.0.0";
    QString description = "QNdiManager Core Module";
    QStringList sources;
    QStringList receivers;
};

QNdiManagerCore::QNdiManagerCore()
    : d(new Private)
{
}

QNdiManagerCore::~QNdiManagerCore()
{
    shutdown();
    delete d;
}

bool QNdiManagerCore::initialize()
{
    if (d->initialized) {
        return true;
    }
    
    // 此处预留NDI管理器初始化实现
    d->initialized = true;
    return true;
}

void QNdiManagerCore::shutdown()
{
    if (!d->initialized) {
        return;
    }
    
    // 此处预留NDI管理器清理实现
    d->initialized = false;
}

bool QNdiManagerCore::isInitialized() const
{
    return d->initialized;
}

QString QNdiManagerCore::getVersion() const
{
    return d->version;
}

QString QNdiManagerCore::getDescription() const
{
    return d->description;
}

QStringList QNdiManagerCore::findSources()
{
    QStringList newSources;
    newSources << "Camera 1" << "Camera 2" << "Screen Capture" << "Test Source";
    d->sources = newSources;
    return d->sources;
}

QStringList QNdiManagerCore::findReceivers()
{
    QStringList newReceivers;
    newReceivers << "Monitor 1" << "Monitor 2" << "Recording System";
    d->receivers = newReceivers;
    return d->receivers;
}

QT_END_NAMESPACE 