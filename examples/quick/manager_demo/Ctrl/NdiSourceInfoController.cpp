#include "NdiSourceInfoController.h"
#include <QDebug>
#include "ndigeneralcontroller.h"

using namespace QNK::Manager;
NdiSourceInfoController::NdiSourceInfoController(QObject *parent)
    : QObject{parent}
    , m_model{new NdiSourceInfoModel(this)}
{
    connect(NdiGeneralCtrl, &NdiGeneralController::forwardAnswer, this, [=](const QNdiManagerCore::NdiGeneralType &type,
                                                                             const QVariant &param, 
                                                                             const bool &success, 
                                                                             const QString &message)
    {
        switch (type)
        {
        case QNdiManagerCore::NdiGeneralType::FindNdiSource:
            if (success)
            {
                model()->hotUpdate(param.toList());
            }
            break;
        default:
            break;
        }
    });
}

QVariantMap NdiSourceInfoController::getNdiSourceInfo(const int &index)
{
    return model()->getValue(index);
}

NdiSourceInfoController *NdiSourceInfoController::instance()
{
    static NdiSourceInfoController instance;
    return &instance;
}
