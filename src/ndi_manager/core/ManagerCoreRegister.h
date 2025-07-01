#ifndef MANAGERCOREREGISTER_H
#define MANAGERCOREREGISTER_H
#include <QQmlEngine>
#include <QQmlContext>
#include "ndigeneralcontroller.h"
#include "qndimanagercore.h"

namespace QNK {
namespace Manager {
inline void registerType(QQmlEngine *engine)
{
    QQmlContext *context = engine->rootContext();
    context->setContextProperty("ndiGeneralCtrl", NdiGeneralCtrl);

    qRegisterMetaType<QNdiManagerCore::NdiGeneralType>("QNdiManagerCore::NdiGeneralType");
}
}
}

#endif // MANAGERCOREREGISTER_H
