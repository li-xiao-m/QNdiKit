#ifndef QNDIKITMANAGERWIDGET_H
#define QNDIKITMANAGERWIDGET_H

#include <QWidget>

class QNDIKITMANAGER_EXPORT QNdiKitManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QNdiKitManagerWidget(QWidget *parent = nullptr);
    ~QNdiKitManagerWidget();
};

#endif // QNDIKITMANAGERWIDGET_H 