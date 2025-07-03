#ifndef QNDIMANAGERCORE_H
#define QNDIMANAGERCORE_H

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include "qndimanagercore_global.h"

namespace QNK {
namespace Manager {
class QNDIMANAGERCORE_EXPORT QNdiManagerCore : public QObject
{
    Q_OBJECT

public:
    enum NdiGeneralType 
    {
        FindNdiSource,
        SwitchNdiSource,
        SwitchNdiStatus,
        NdiSourceData
    };
    Q_ENUM(NdiGeneralType)

    QNdiManagerCore();
    ~QNdiManagerCore();

private:
};
}

}


#endif // QNDIMANAGERCORE_H
