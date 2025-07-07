#include "ndivieweritem.h"
#include "QNDI.Manager.GlobalController.h"
#include "qglobal.h"
#include <QGuiApplication>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>
#include <QSGTexture>

namespace QNK {
namespace Manager {
NdiViewerItem::NdiViewerItem(QQuickItem *parent)
    : QQuickItem(parent), m_thread(new QThread()),
      m_worker(new NdiReceiveWorker()) {
  connect(NdiGlobalCtrl, &NdiGlobalController::forwardAnswer, this,
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
  connect(qApp, &QCoreApplication::aboutToQuit, this,
          [=]() {
            m_thread->quit();
            m_thread->wait();
            delete m_worker;
            delete m_thread;
            m_thread = nullptr;
            m_worker = nullptr;
          });

  m_worker->moveToThread(m_thread);
  m_thread->start();
  setFlag(ItemHasContents, true);
}

NdiViewerItem::~NdiViewerItem() {
  if (m_thread) {
    m_thread->quit();
    m_thread->wait();
    delete m_worker;
    delete m_thread;
    m_thread = nullptr;
    m_worker = nullptr;
  }
}

QSGNode *
NdiViewerItem::updatePaintNode(QSGNode *oldNode,
                               UpdatePaintNodeData *updatePaintNodeData) {
  QSGSimpleTextureNode *node = dynamic_cast<QSGSimpleTextureNode *>(oldNode);

  if (!node) {
    node = new QSGSimpleTextureNode();
  }

  // Calculate the texture area based on the fill mode
  QRect node_rect = boundingRect().toRect();
  const double image_ratio = m_image.width() / (double)m_image.height();
  const double rect_ratio = node_rect.width() / (double)node_rect.height();
  // If image_ratio > rect_ratio, the image is too narrow for the rect
  // Adjust height based on width, otherwise adjust width based on height
  if (image_ratio > rect_ratio) {
    const int new_height = node_rect.width() / image_ratio;
    node_rect.setY(node_rect.y() + (node_rect.height() - new_height) / 2);
    node_rect.setHeight(new_height);
  } else {
    const int new_width = image_ratio * node_rect.height();
    node_rect.setX(node_rect.x() + (node_rect.width() - new_width) / 2);
    node_rect.setWidth(new_width);
  }

  QSGTexture *texture = window()->createTextureFromImage(m_image);
  texture->setFiltering(QSGTexture::Linear);
  texture->setMipmapFiltering(QSGTexture::Linear);
  node->setTexture(texture);
  node->setOwnsTexture(true);
  node->setRect(node_rect);
  node->markDirty(QSGNode::DirtyGeometry);
  node->markDirty(QSGNode::DirtyMaterial);

  return node;
}

void NdiViewerItem::handleAnswer(const QNdiManagerCore::NdiGeneralType &type,
                                 const QVariant &param, bool isSuccess,
                                 const QString &message) {
  switch (type) {
  case QNdiManagerCore::NdiGeneralType::NdiSourceData:
    // 1. Obtain new image data and store it
    if (param.value<QImage>().isNull()) {
      return;
    }
    m_image = param.value<QImage>();
    this->setVisible(true);
    this->update();
    break;
  default:
    break;
  }
  emit forwardAnswer(type, param, isSuccess, message);
}
} // namespace Manager
} // namespace QNK