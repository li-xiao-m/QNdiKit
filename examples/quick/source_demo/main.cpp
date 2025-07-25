#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QtCore/QUrl>
#include <QtCore/QDir>
#include "qndisourcequickitem.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    QQmlApplicationEngine engine;
    
    // 注册C++类型到QML
    qmlRegisterType<QNdiSourceQuickItem>("QNdiKit", 1, 0, "NdiSourceItem");
    
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