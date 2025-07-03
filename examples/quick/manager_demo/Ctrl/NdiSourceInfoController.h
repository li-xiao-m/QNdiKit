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

public:
    static NdiSourceInfoController *instance();
    Q_INVOKABLE QVariantMap getNdiSourceInfo(const int &index);
    NdiSourceInfoModel* model() const{return m_model;};

signals:

private:
    NdiSourceInfoModel* m_model{nullptr};
};

#define NdiSourceInfoCtrl NdiSourceInfoController::instance()
#endif // NDISOURCEINFOCONTROLLER_H
