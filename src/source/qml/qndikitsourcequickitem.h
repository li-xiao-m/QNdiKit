#ifndef QNDIKITSOURCEQUICKITEM_H
#define QNDIKITSOURCEQUICKITEM_H

#include <QQuickItem>

class QNDIKITSOURCE_EXPORT QNdiKitSourceQuickItem : public QQuickItem
{
    Q_OBJECT

public:
    explicit QNdiKitSourceQuickItem(QQuickItem *parent = nullptr);
    ~QNdiKitSourceQuickItem();
};

#endif // QNDIKITSOURCEQUICKITEM_H 