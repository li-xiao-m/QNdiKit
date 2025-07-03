#ifndef MANAGERCOREREGISTER_H
#define MANAGERCOREREGISTER_H
#include <QQmlEngine>
#include <QQmlContext>
#include "ndigeneralcontroller.h"
#include "qndimanagercore.h"

namespace QNK {
namespace Manager {
inline void registerCoreType(QQmlEngine *engine)
{
    QQmlContext *context = engine->rootContext();
    context->setContextProperty("ndiGeneralCtrl", NdiGeneralCtrl);
    qRegisterMetaType<QNdiManagerCore::NdiGeneralType>("QNdiManagerCore::NdiGeneralType");
    qmlRegisterUncreatableType<QNdiManagerCore>("QNK.Manager", 1, 0, "QNkManagerCore", "QNkManagerCore is a singleton type");
}
}
}

#endif // MANAGERCOREREGISTER_H
