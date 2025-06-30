#ifndef QNDIKITSOURCECONTROL_H
#define QNDIKITSOURCECONTROL_H

#include <QWidget>

class QNDIKITSOURCE_EXPORT QNdiKitSourceControl : public QWidget
{
    Q_OBJECT

public:
    explicit QNdiKitSourceControl(QWidget *parent = nullptr);
    ~QNdiKitSourceControl();
};

#endif // QNDIKITSOURCECONTROL_H 