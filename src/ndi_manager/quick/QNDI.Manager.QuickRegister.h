#ifndef QNDI_MANAGER_QUICKREGISTER_H
#define QNDI_MANAGER_QUICKREGISTER_H
#include <QQmlEngine>
#include "ndivieweritem.h"

namespace QNK {
namespace Manager {
inline void registerQuickType(QQmlEngine *engine)
{
    qmlRegisterType<NdiViewerItem>("QNK.Manager", 1, 0, "NdiViewerItem");
}
}
}
#endif // QNDI_MANAGER_QUICKREGISTER_H
