#ifndef QNDISOURCEQUICKITEM_H
#define QNDISOURCEQUICKITEM_H

#include "qndisourcequick_global.h"
#include <QtQuick/QQuickItem>

QT_BEGIN_NAMESPACE

class QNDISOURCEQUICK_EXPORT QNdiSourceQuickItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString sourceName READ sourceName WRITE setSourceName NOTIFY sourceNameChanged)

public:
    explicit QNdiSourceQuickItem(QQuickItem *parent = nullptr);
    ~QNdiSourceQuickItem();

    QString sourceName() const;

public slots:
    void setSourceName(const QString &name);
    void startSource();
    void stopSource();
    void showInfo();

signals:
    void sourceNameChanged();

private:
    class Private;
    Private *d;
};

QT_END_NAMESPACE

#endif // QNDISOURCEQUICKITEM_H 