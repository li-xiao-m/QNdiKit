#include "ndivieweritem.h"
#include "ndigeneralcontroller.h"
#include <QGuiApplication>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>
#include <QSGTexture>


namespace QNK {
namespace Manager {
NdiViewerItem::NdiViewerItem(QQuickItem *parent)
    : QQuickItem(parent), m_thread(new QThread()),
      m_worker(new NdiReceiveWorker()) {
  connect(NdiGeneralCtrl, &NdiGeneralController::forwardAnswer, this,
          [=](const QNdiManagerCore::NdiGeneralType &type,
              const QVariant &param, bool isSuccess, const QString &message) {
            switch (type) {
            case QNdiManagerCore::NdiGeneralType::SwitchNdiSource:
            case QNdiManagerCore::NdiGeneralType::SwitchNdiStatus:
              this->sendCommand(type, param);
              break;
            default:
              break;
            }
          });

  connect(this, &NdiViewerItem::sendCommand, m_worker,
          &NdiReceiveWorker::handle);
  connect(m_worker, &NdiReceiveWorker::answer, this,
          &NdiViewerItem::handleAnswer);
  connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, this,
          [=]() {
            m_thread->quit();
            m_thread->wait();
            m_thread->deleteLater();
            m_worker->deleteLater();
          });

  m_worker->moveToThread(m_thread);
  m_thread->start();
  setFlag(ItemHasContents, true);
}

NdiViewerItem::~NdiViewerItem() {}

QSGNode *
NdiViewerItem::updatePaintNode(QSGNode *oldNode,
                               UpdatePaintNodeData *updatePaintNodeData) {
  if (!this->isVisible() || m_image.isNull()) {
    return nullptr; // 如果不可见或没图像，直接返回
  }

  QSGSimpleTextureNode *node = static_cast<QSGSimpleTextureNode *>(oldNode);
  if (!node) {
    node = new QSGSimpleTextureNode();
  }

  // 1. 每次更新时都根据当前图像创建一个新的纹理
  QSGTexture *texture = window()->createTextureFromImage(m_image);

  // 2. 把新纹理交给 node
  node->setTexture(texture);

  // 3. 关键：告诉 node 它拥有这个纹理的生命周期！
  node->setOwnsTexture(true);

  node->setRect(QRectF(0, 0, width(), height()));
  return node;
}

void NdiViewerItem::handleAnswer(const QNdiManagerCore::NdiGeneralType &type,
                                 const QVariant &param, bool isSuccess,
                                 const QString &message) {
  switch (type) {
  case QNdiManagerCore::NdiGeneralType::NdiSourceData:
    // 1. 获取新图像数据并存起来
    m_image = param.value<QImage>(); // 假设缩放等已在工作线程完成
    if (m_image.isNull()) {
      this->setVisible(false);
    } else {
      this->setVisible(true);
      // 2. 请求刷新，updatePaintNode 会被调用
      update();
    }
    break;
  default:
    break;
  }
  emit forwardAnswer(type, param, isSuccess, message);
}
} // namespace Manager
} // namespace QNK