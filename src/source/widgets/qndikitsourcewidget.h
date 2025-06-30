#ifndef QNDIKITSOURCEWIDGET_H
#define QNDIKITSOURCEWIDGET_H

#include <QWidget>

class QNDIKITSOURCE_EXPORT QNdiKitSourceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QNdiKitSourceWidget(QWidget *parent = nullptr);
    ~QNdiKitSourceWidget();
};

#endif // QNDIKITSOURCEWIDGET_H 