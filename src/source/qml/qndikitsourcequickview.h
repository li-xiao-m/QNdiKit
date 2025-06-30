#ifndef QNDIKITSOURCEQUICKVIEW_H
#define QNDIKITSOURCEQUICKVIEW_H

#include <QQuickWidget>

class QNDIKITSOURCE_EXPORT QNdiKitSourceQuickView : public QQuickWidget
{
    Q_OBJECT

public:
    explicit QNdiKitSourceQuickView(QWidget *parent = nullptr);
    ~QNdiKitSourceQuickView();
};

#endif // QNDIKITSOURCEQUICKVIEW_H 