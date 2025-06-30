#ifndef QNDIKITDISCOVERY_H
#define QNDIKITDISCOVERY_H

#include <QObject>
#include "qndikitmanager_global.h"

class QNDIKITMANAGER_EXPORT QNdiKitDiscovery : public QObject
{
    Q_OBJECT

public:
    explicit QNdiKitDiscovery(QObject *parent = nullptr);
    ~QNdiKitDiscovery();
};

#endif // QNDIKITDISCOVERY_H 