#ifndef QNDIKITSOURCECORE_H
#define QNDIKITSOURCECORE_H

#include <QObject>
#include "qndikitsource_global.h"

class QNDIKITSOURCE_EXPORT QNdiKitSourceCore : public QObject
{
    Q_OBJECT

public:
    explicit QNdiKitSourceCore(QObject *parent = nullptr);
    ~QNdiKitSourceCore();
};

#endif // QNDIKITSOURCECORE_H 