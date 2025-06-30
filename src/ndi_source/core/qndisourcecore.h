#ifndef QNDISOURCECORE_H
#define QNDISOURCECORE_H

#include "qndisourcecore_global.h"
#include <QtCore/QObject>
#include <QtCore/QStringList>

QT_BEGIN_NAMESPACE

class QNDISOURCE_EXPORT QNdiSourceCore : public QObject
{
    Q_OBJECT

public:
    explicit QNdiSourceCore(QObject *parent = nullptr);
    ~QNdiSourceCore();

    bool initialize();
    void shutdown();
    bool isInitialized() const;
    QString getVersion() const;
    QString getDescription() const;
    QStringList findSources();
    QStringList findReceivers();
    static QNdiSourceCore* create();

public slots:
    void setName(const QString &name);
    QString name() const;

signals:
    void nameChanged();

private:
    class Private;
    Private *d;
};

QT_END_NAMESPACE

#endif // QNDISOURCECORE_H 