#ifndef NDISOURCEINFOCONTROLLER_H
#define NDISOURCEINFOCONTROLLER_H

#include <QObject>
#include "../Model/NdiSourceInfoModel.h"

class NdiSourceInfoController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(NdiSourceInfoModel *model MEMBER m_model CONSTANT)
private:
    explicit NdiSourceInfoController(QObject *parent = nullptr);
    NdiSourceInfoModel* model() const{return m_model;};

public:
    static NdiSourceInfoController *instance();

signals:

private:
    NdiSourceInfoModel* m_model{nullptr};
};

#define NdiSourceInfoCtrl NdiSourceInfoController::instance()
#endif // NDISOURCEINFOCONTROLLER_H
