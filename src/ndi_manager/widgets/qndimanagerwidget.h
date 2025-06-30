#ifndef QNDIMANAGERWIDGET_H
#define QNDIMANAGERWIDGET_H

#include "qndimanagerwidgets_global.h"
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class QNDIMANAGERWIDGETS_EXPORT QNdiManagerWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QStringList sources READ sources NOTIFY sourcesChanged)
    Q_PROPERTY(QStringList receivers READ receivers NOTIFY receiversChanged)

public:
    explicit QNdiManagerWidget(QWidget *parent = nullptr);
    ~QNdiManagerWidget();

    QStringList sources() const;
    QStringList receivers() const;

public slots:
    void scanSources();
    void scanReceivers();
    void showInfo();

signals:
    void sourcesChanged();
    void receiversChanged();

private:
    class Private;
    Private *d;
};

QT_END_NAMESPACE

#endif // QNDIMANAGERWIDGET_H 