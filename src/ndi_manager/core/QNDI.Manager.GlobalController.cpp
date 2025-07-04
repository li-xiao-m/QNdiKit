#include "QNDI.Manager.GlobalController.h"
#include <QCoreApplication>
#include <QDebug>

namespace QNK {
namespace Manager {
NdiGlobalController::NdiGlobalController(QObject *parent)
    : QObject{parent}
    , m_workers{new NdiCpuWorker{}}
    , m_thread{new QThread{}}
{
    connect(this, &NdiGlobalController::sendCommand, m_workers, &NdiCpuWorker::handle);
    connect(m_workers, &NdiCpuWorker::answer, this, &NdiGlobalController::handleAnswer);
    connect(qApp, &QCoreApplication::aboutToQuit, this, [=](){
        qDebug() << "NdiGlobalController aboutToQuit";
        m_thread->quit();
        m_thread->wait();
        delete m_workers;
        delete m_thread;
    }); 
    m_workers->moveToThread(m_thread);
    m_thread->start();
}

NdiGlobalController *NdiGlobalController::instance()
{
    static NdiGlobalController instance;
    return &instance;
}

void NdiGlobalController::handleAnswer(const QNdiManagerCore::NdiGeneralType &type,
                                        const QVariant &param,
                                        const bool &success,
                                        const QString &message)
{
    emit forwardAnswer(type, param, success, message);
}
} // namespace Manager
} // namespace QNK
