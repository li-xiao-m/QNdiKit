#include "ndivieweritem.h"
#include "ndigeneralcontroller.h"
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

NdiViewerItem::~NdiViewerItem() {
  if (m_texture) {
    delete m_texture;
    m_texture = nullptr;
  }
}

QSGNode *
NdiViewerItem::updatePaintNode(QSGNode *oldNode,
                               UpdatePaintNodeData *updatePaintNodeData) {
  if (!m_texture) {
    return oldNode;
  }

  QSGSimpleTextureNode *node = static_cast<QSGSimpleTextureNode *>(oldNode);
  if (!node) {
    node = new QSGSimpleTextureNode();
  }

  node->setTexture(m_texture);
  node->setOwnsTexture(false);

  // 更新节点显示的尺寸
  qreal texture_width = m_texture->textureSize().width();
  qreal texture_height = m_texture->textureSize().height();
  qreal ratio = texture_width / texture_height; 
  if(ratio > 1) {
    texture_width = this->width();
    texture_height = texture_width / ratio;
  } else {
    texture_height = this->height();
    texture_width = texture_height * ratio;
  }
  node->setRect(QRectF(
      (this->width() - texture_width) / 2.0,
      (this->height() - texture_height) / 2.0,
      texture_width,
      texture_height));

  return node;
}

void NdiViewerItem::handleAnswer(const QNdiManagerCore::NdiGeneralType &type,
                                 const QVariant &param, bool isSuccess,
                                 const QString &message) {
  switch (type) {
  case QNdiManagerCore::NdiGeneralType::NdiSourceData:
    // 1. 获取新图像数据并存起来
    if (param.value<QImage>().isNull()) {
      return;
    }
    this->setVisible(true);
    if (m_texture) {
      m_texture->deleteLater();
      m_texture = nullptr;
    }
    m_texture = window()->createTextureFromImage(param.value<QImage>());
    m_texture->setFiltering(QSGTexture::Linear);
    this->update();
    break;
  default:
    break;
  }
  emit forwardAnswer(type, param, isSuccess, message);
}
} // namespace Manager
} // namespace QNK