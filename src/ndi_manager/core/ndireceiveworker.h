#ifndef NDIRECEIVEWORKER_H
#define NDIRECEIVEWORKER_H

#include "qchar.h"
#include "QNDI.Manager.Core.h"
#include "qndimanagercore_global.h"
#include <Processing.NDI.Lib.h>
#include <QObject>
#include <QVariant>

namespace QNK {
namespace Manager {
class QNDIMANAGERCORE_EXPORT NdiReceiveWorker : public QObject {
  Q_OBJECT
public:
  explicit NdiReceiveWorker(QObject *parent = nullptr);

public slots:
  void handle(const QNdiManagerCore::NdiGeneralType &type,
              const QVariant &param);

signals:
  void answer(const QNdiManagerCore::NdiGeneralType &type,
              const QVariant &param, const bool &success,
              const QString &message);

private:
  void handleSwitchNdiSource(const QNdiManagerCore::NdiGeneralType &type,
                             const QVariant &param);
  void handleSwitchNdiStatus(const QNdiManagerCore::NdiGeneralType &type,
                             const QVariant &param);
  void handleNdiSourceData(const QNdiManagerCore::NdiGeneralType &type,
                           const QVariant &param);
private:
  NDIlib_recv_instance_t m_pNDI_recv{nullptr};
  bool m_isPaused{false};
};
} // namespace Manager
} // namespace QNK

#endif // NDIRECEIVEWORKER_H
