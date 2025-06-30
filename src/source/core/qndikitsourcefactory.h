#ifndef QNDIKITSOURCEFACTORY_H
#define QNDIKITSOURCEFACTORY_H

#include <QObject>
#include <QString>
#include "qndikitsource_global.h"

class QNdiKitSource;

class QNDIKITSOURCE_EXPORT QNdiKitSourceFactory : public QObject
{
    Q_OBJECT

public:
    explicit QNdiKitSourceFactory(QObject *parent = nullptr);
    ~QNdiKitSourceFactory();

    QNdiKitSource* createSource(const QString &name, QObject *parent = nullptr);
};

#endif // QNDIKITSOURCEFACTORY_H 