#ifndef QNDI_MANAGER_CORE_H
#define QNDI_MANAGER_CORE_H

#include "qndimanagercore_global.h"
#include <QObject>

namespace QNK {
namespace Manager {
class QNDIMANAGERCORE_EXPORT QNdiManagerCore : public QObject
{
    Q_OBJECT
public:
    explicit QNdiManagerCore(QObject *parent = nullptr);
    ~QNdiManagerCore();

public:
    enum NdiGeneralType
    {
        FindNdiSource,
        SwitchNdiSource,
        SwitchNdiStatus,
        NdiSourceData
    };
    Q_ENUM(NdiGeneralType)

signals:
};
} // namespace Manager
} // namespace QNK
#endif // QNDI_MANAGER_CORE_H
