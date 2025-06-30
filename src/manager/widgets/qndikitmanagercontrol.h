#ifndef QNDIKITMANAGERCONTROL_H
#define QNDIKITMANAGERCONTROL_H

#include <QWidget>

class QNDIKITMANAGER_EXPORT QNdiKitManagerControl : public QWidget
{
    Q_OBJECT

public:
    explicit QNdiKitManagerControl(QWidget *parent = nullptr);
    ~QNdiKitManagerControl();
};

#endif // QNDIKITMANAGERCONTROL_H 