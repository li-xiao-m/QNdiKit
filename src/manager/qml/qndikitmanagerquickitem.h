#ifndef QNDIKITMANAGERQUICKITEM_H
#define QNDIKITMANAGERQUICKITEM_H

#include <QQuickItem>

class QNDIKITMANAGER_EXPORT QNdiKitManagerQuickItem : public QQuickItem
{
    Q_OBJECT

public:
    explicit QNdiKitManagerQuickItem(QQuickItem *parent = nullptr);
    ~QNdiKitManagerQuickItem();
};

#endif // QNDIKITMANAGERQUICKITEM_H