#ifndef QNDI_MANAGER_CORE_REGISTER_H
#define QNDI_MANAGER_CORE_REGISTER_H
#include <QQmlEngine>
#include <QQmlContext>
#include "QNDI.Manager.GlobalController.h"
#include "QNDI.Manager.Core.h"

namespace QNK {
namespace Manager {
inline void registerCoreType(QQmlEngine *engine)
{
    QQmlContext *context = engine->rootContext();
    context->setContextProperty("ndiGlobalCtrl", NdiGlobalCtrl);
    qRegisterMetaType<QNdiManagerCore::NdiGeneralType>("QNdiManagerCore::NdiGeneralType");
    qmlRegisterUncreatableType<QNdiManagerCore>("QNK.Manager", 1, 0, "QNkManagerCore", "QNkManagerCore is a singleton type");
}
}
}

#endif // QNDI_MANAGER_CORE_REGISTER_H
