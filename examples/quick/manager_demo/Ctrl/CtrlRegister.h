#ifndef CTRLREGISTER_H
#define CTRLREGISTER_H
#include <QQmlEngine>
#include <QQmlContext>
#include "NdiSourceInfoController.h"

namespace Ctrl {
inline void registerType(QQmlEngine *engine)
{
    QQmlContext *context = engine->rootContext();
    context->setContextProperty("ndiSourceInfoCtrl", NdiSourceInfoCtrl);
}
}

#endif // CTRLREGISTER_H
