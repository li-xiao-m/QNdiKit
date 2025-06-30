#ifndef QNDIKITMANAGERQUICKVIEW_H
#define QNDIKITMANAGERQUICKVIEW_H

#include <QQuickWidget>

class QNDIKITMANAGER_EXPORT QNdiKitManagerQuickView : public QQuickWidget
{
    Q_OBJECT

public:
    explicit QNdiKitManagerQuickView(QWidget *parent = nullptr);
    ~QNdiKitManagerQuickView();
};

#endif // QNDIKITMANAGERQUICKVIEW_H 