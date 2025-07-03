#ifndef QUICKVIEWREGISTER_H
#define QUICKVIEWREGISTER_H
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
#endif // QUICKVIEWREGISTER_H
