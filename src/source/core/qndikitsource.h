#ifndef QNDIKITSOURCE_H
#define QNDIKITSOURCE_H

#include <QObject>
#include <QString>
#include "qndikitsource_global.h"

class QNDIKITSOURCE_EXPORT QNdiKitSource : public QObject
{
    Q_OBJECT

public:
    explicit QNdiKitSource(QObject *parent = nullptr);
    ~QNdiKitSource();

    void setName(const QString &name);
    QString name() const;

private:
    QString m_name;
};

#endif // QNDIKITSOURCE_H 