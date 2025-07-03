#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QtCore/QUrl>
#include <QtCore/QDir>
#include "managercoreregister.h"
#include "quickviewregister.h"
#include "Ctrl/CtrlRegister.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    QQmlApplicationEngine engine;
    QNK::Manager::registerCoreType(&engine);
    QNK::Manager::registerQuickType(&engine);
    Ctrl::registerType(&engine);
    
    // 加载主QML文件
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    
    engine.load(url);
    
    if (engine.rootObjects().isEmpty()) {
        qWarning() << "Failed to load QML file:" << url;
        return -1;
    }
    
    return app.exec();
} 