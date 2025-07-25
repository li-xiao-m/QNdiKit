#ifndef NDIVIEWERITEM_H
#define NDIVIEWERITEM_H

#include "ndireceiveworker.h"
#include "QNDI.Manager.Core.h"
#include "qndimanagerquick_global.h"
#include <QImage>
#include <QQuickItem>
#include <QSGNode>
#include <QThread>
#include <QSGTexture>
#include <QImage>

namespace QNK {
namespace Manager {
class QNDIMANAGERQUICK_EXPORT NdiViewerItem : public QQuickItem {
  Q_OBJECT
public:
  explicit NdiViewerItem(QQuickItem *parent = nullptr);
  ~NdiViewerItem();

protected:
  QSGNode *updatePaintNode(QSGNode *oldNode,
                           UpdatePaintNodeData *updatePaintNodeData) override;

public slots:
  void handleAnswer(const QNdiManagerCore::NdiGeneralType &type,
                    const QVariant &param, bool isSuccess,
                    const QString &message);

signals:
  void sendCommand(const QNdiManagerCore::NdiGeneralType &type,
                   const QVariant &param);
  void forwardAnswer(const QNdiManagerCore::NdiGeneralType &type,
                     const QVariant &param, bool isSuccess,
                     const QString &message);

private:
  QThread *m_thread{nullptr};
  NdiReceiveWorker *m_worker{nullptr};
  QImage m_image;
};
} // namespace Manager
} // namespace QNK

#endif // NDIVIEWERITEM_H
