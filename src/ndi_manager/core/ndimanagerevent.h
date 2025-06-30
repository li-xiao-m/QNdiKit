#ifndef NDIMANAGEREVENT_H
#define NDIMANAGEREVENT_H

#include <QEvent>
#include "qndimanagercore_global.h"

namespace QNK {
namespace Manager {
class QNDIMANAGERCORE_EXPORT NdiManagerEvent : public QEvent
{
public:
    // 头文件里声明
    static const QEvent::Type NdiManagerEventType;
    explicit NdiManagerEvent();

signals:
};
}
}

#endif // NDIMANAGEREVENT_H
