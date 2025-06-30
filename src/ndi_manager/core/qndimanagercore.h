#ifndef QNDIMANAGERCORE_H
#define QNDIMANAGERCORE_H

#include "qndimanagercore_global.h"
#include <QtCore/QObject>
#include <QtCore/QStringList>

QT_BEGIN_NAMESPACE

class QNDIMANAGERCORE_EXPORT QNdiManagerCore : public QObject
{
    Q_OBJECT

public:
    QNdiManagerCore();
    ~QNdiManagerCore();

    bool initialize();
    void shutdown();
    bool isInitialized() const;
    QString getVersion() const;
    QString getDescription() const;
    QStringList findSources();
    QStringList findReceivers();

private:
    class Private;
    Private *d;
};

QT_END_NAMESPACE

#endif // QNDIMANAGERCORE_H 