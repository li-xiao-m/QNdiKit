#ifndef QNDIKITMANAGER_H
#define QNDIKITMANAGER_H

#include <QObject>
#include "qndikitmanager_global.h"

class QNDIKITMANAGER_EXPORT QNdiKitManager : public QObject
{
    Q_OBJECT

public:
    explicit QNdiKitManager(QObject *parent = nullptr);
    ~QNdiKitManager();

    void startDiscovery();
    void stopDiscovery();
};

#endif // QNDIKITMANAGER_H 