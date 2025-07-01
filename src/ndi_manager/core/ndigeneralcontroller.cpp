#include "ndigeneralcontroller.h"
#include <QCoreApplication>
#include <QDebug>

namespace QNK {
namespace Manager {
NdiGeneralController::NdiGeneralController(QObject *parent)
    : QObject{parent}
    , m_workers{new NdiCpuWorker{}}
    , m_thread{new QThread{}}
{
    connect(this, &NdiGeneralController::sendCommand, m_workers, &NdiCpuWorker::handle);
    connect(m_workers, &NdiCpuWorker::answer, this, &NdiGeneralController::handleAnswer);
    connect(qApp, &QCoreApplication::aboutToQuit, this, [=](){
        qDebug() << "NdiGeneralController aboutToQuit";
        m_thread->quit();
        m_thread->wait();
        delete m_workers;
        delete m_thread;
    });
    m_workers->moveToThread(m_thread);
    m_thread->start();
}

NdiGeneralController *NdiGeneralController::instance()
{
    static NdiGeneralController instance;
    return &instance;
}

void NdiGeneralController::handleAnswer(const QNdiManagerCore::NdiGeneralType &type,
                                        const QVariant &param,
                                        const bool &success,
                                        const QString &message)
{
    emit forwardAnswer(type, param, success, message);
}

}
}