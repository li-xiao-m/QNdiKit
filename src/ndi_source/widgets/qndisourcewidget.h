#ifndef QNDISOURCEWIDGET_H
#define QNDISOURCEWIDGET_H

#include "qndisourcewidgets_global.h"
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class QNDISOURCEWIDGETS_EXPORT QNdiSourceWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString sourceName READ sourceName WRITE setSourceName NOTIFY sourceNameChanged)

public:
    explicit QNdiSourceWidget(QWidget *parent = nullptr);
    ~QNdiSourceWidget();

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

#endif // QNDISOURCEWIDGET_H 