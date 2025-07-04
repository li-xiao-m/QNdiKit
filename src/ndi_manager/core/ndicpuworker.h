#ifndef NDICPUWORKER_H
#define NDICPUWORKER_H

#include "QNDI.Manager.Core.h"
#include "qndimanagercore_global.h"
#include <Processing.NDI.Lib.h>
#include <QObject>
#include <QVariant>


namespace QNK {
namespace Manager {
class QNDIMANAGERCORE_EXPORT NdiCpuWorker : public QObject {
  Q_OBJECT
public:
  explicit NdiCpuWorker(QObject *parent = nullptr);
  ~NdiCpuWorker();

public slots:
  void handle(const QNdiManagerCore::NdiGeneralType &type,
              const QVariant &param);

signals:
  void answer(const QNdiManagerCore::NdiGeneralType &type,
              const QVariant &param, const bool &success,
              const QString &message);

private:
  void handleFindNdiSource(const QNdiManagerCore::NdiGeneralType &type,
                           const QVariant &param);
  void handleSwitchNdiSource(const QNdiManagerCore::NdiGeneralType &type,
                             const QVariant &param);
  void handleSwitchNdiStatus(const QNdiManagerCore::NdiGeneralType &type,
                             const QVariant &param);

private:
  void initializeNDI();

private:
  NDIlib_find_instance_t m_pNDI_find{nullptr};
};

} // namespace Manager
} // namespace QNK

#endif // NDICPUWORKER_H
