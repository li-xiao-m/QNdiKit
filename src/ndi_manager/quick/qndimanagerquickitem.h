#ifndef QNDIMANAGERQUICKITEM_H
#define QNDIMANAGERQUICKITEM_H

#include "qndimanagerquick_global.h"
#include <QtQuick/QQuickItem>

QT_BEGIN_NAMESPACE

class QNDIMANAGERQUICK_EXPORT QNdiManagerQuickItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QStringList sources READ sources NOTIFY sourcesChanged)
    Q_PROPERTY(QStringList receivers READ receivers NOTIFY receiversChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)

public:
    explicit QNdiManagerQuickItem(QQuickItem *parent = nullptr);
    ~QNdiManagerQuickItem();

    QStringList sources() const;
    QStringList receivers() const;
    QString status() const;

public slots:
    void scanSources();
    void scanReceivers();
    void showInfo();

signals:
    void sourcesChanged();
    void receiversChanged();
    void statusChanged();

private:
    class Private;
    Private *d;
};

QT_END_NAMESPACE

#endif // QNDIMANAGERQUICKITEM_H 