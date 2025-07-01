#ifndef NDIGENERALCONTROLLER_H
#define NDIGENERALCONTROLLER_H

#include <QThread>
#include <QVariant>
#include "qndimanagercore.h"
#include "ndicpuworker.h"
#include "qndimanagercore_global.h"

namespace QNK
{
    namespace Manager
    {
        class QNDIMANAGERCORE_EXPORT NdiGeneralController : public QObject
        {
            Q_OBJECT
        private:
            explicit NdiGeneralController(QObject *parent = nullptr);

        public:
            static NdiGeneralController *instance();

        public slots:
            void handleAnswer(const QNdiManagerCore::NdiGeneralType &type,
                              const QVariant &param,
                              const bool &success,
                              const QString &message);

        signals:
            void sendCommand(const QNdiManagerCore::NdiGeneralType &type,
                             const QVariant &param);
            void forwardAnswer(const QNdiManagerCore::NdiGeneralType &type,
                               const QVariant &param,
                               const bool &success,
                               const QString &message);

        private:
            NdiCpuWorker* m_workers{nullptr};
            QThread* m_thread{nullptr};
        };
    }
}

#define NdiGeneralCtrl QNK::Manager::NdiGeneralController::instance()
#endif // NDIGENERALCONTROLLER_H
