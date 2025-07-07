#ifndef QNDI_MANAGER_GLOBALCONTROLLER_H
#define QNDI_MANAGER_GLOBALCONTROLLER_H
#include "QNDI.Manager.Core.h"
#include "ndicpuworker.h"
#include "qndimanagercore_global.h"
#include <QThread>
#include <QVariant>


namespace QNK {
namespace Manager {
class QNDIMANAGERCORE_EXPORT NdiGlobalController : public QObject {
  Q_OBJECT
private:
  NdiGlobalController(QObject *parent = nullptr);

public:
  static NdiGlobalController *instance();
  ~NdiGlobalController();

public slots:
  void handleAnswer(const QNdiManagerCore::NdiGeneralType &type,
                    const QVariant &param, const bool &success,
                    const QString &message);

signals:
  void sendCommand(const QNdiManagerCore::NdiGeneralType &type,
                   const QVariant &param);
  void forwardAnswer(const QNdiManagerCore::NdiGeneralType &type,
                     const QVariant &param, const bool &success,
                     const QString &message);

private:
  NdiCpuWorker *m_workers{nullptr};
  QThread *m_thread{nullptr};
};
} // namespace Manager
} // namespace QNK
#define NdiGlobalCtrl NdiGlobalController::instance()
#endif // QNDI_MANAGER_GLOBALCONTROLLER_H
