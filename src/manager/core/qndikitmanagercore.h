#ifndef QNDIKITMANAGERCORE_H
#define QNDIKITMANAGERCORE_H

#include <QObject>
#include "qndikitmanager_global.h"

class QNDIKITMANAGER_EXPORT QNdiKitManagerCore : public QObject
{
    Q_OBJECT

public:
    explicit QNdiKitManagerCore(QObject *parent = nullptr);
    ~QNdiKitManagerCore();
};

#endif // QNDIKITMANAGERCORE_H 