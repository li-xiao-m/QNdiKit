#include "ndireceiveworker.h"
#include "Processing.NDI.Recv.h"
#include "qdebug.h"
#include <QDebug>
#include <QImage>
#include <QTimer>
#include <QGuiApplication>

namespace QNK {
namespace Manager {
NdiReceiveWorker::NdiReceiveWorker(QObject *parent) : QObject{parent} {
  this->handle(QNdiManagerCore::NdiSourceData, QVariant());
}

void NdiReceiveWorker::handle(const QNdiManagerCore::NdiGeneralType &type,
                              const QVariant &param) {
  switch (type) {
  case QNdiManagerCore::NdiGeneralType::SwitchNdiSource:
    handleSwitchNdiSource(type, param);
    break;
  case QNdiManagerCore::NdiGeneralType::SwitchNdiStatus:
    handleSwitchNdiStatus(type, param);
    break;
  case QNdiManagerCore::NdiGeneralType::NdiSourceData:
    handleNdiSourceData(type, param);
    break;
  default:
    break;
  }
}

void NdiReceiveWorker::handleSwitchNdiSource(
    const QNdiManagerCore::NdiGeneralType &type, const QVariant &param) {
  if (!param.isValid() || param.isNull()) {
    emit answer(type, param, false, "Invalid parameter");
    return;
  }
  NDIlib_source_t target_source;
  std::string ndi_name = param.toMap()["source_name"].toString().toStdString();
  std::string url_address =
      param.toMap()["source_url"].toString().toStdString();
  qDebug() << "NdiReceiveWorker::handleSwitchNdiSource" << ndi_name.c_str()
           << url_address.c_str();
  target_source.p_ndi_name = ndi_name.c_str();
  target_source.p_url_address = url_address.c_str();
  if (m_pNDI_recv) {
    NDIlib_recv_destroy(m_pNDI_recv);
    m_pNDI_recv = nullptr;
  }
  // create a new NDI receiver
  NDIlib_recv_create_v3_t recv_create;
  memset(&recv_create, 0, sizeof(recv_create));
  recv_create.color_format = NDIlib_recv_color_format_BGRX_BGRA;
  recv_create.source_to_connect_to = target_source;
  m_pNDI_recv = NDIlib_recv_create_v3(&recv_create);
  if (!m_pNDI_recv) {
    emit answer(type, param, false, "Failed to create NDI receiver");
    return;
  }
  emit answer(type, param, true, "Success");
}

void NdiReceiveWorker::handleNdiSourceData(
    const QNdiManagerCore::NdiGeneralType &type, const QVariant &param) {
  do {
    if (this->m_isPaused) {
      break;
    }
    if (!m_pNDI_recv) {
      break;
    }
    // try to get the NDI source data
    NDIlib_video_frame_v2_t p_video_frame;
    NDIlib_recv_capture_v2(m_pNDI_recv, &p_video_frame, nullptr, nullptr, 1000);
    if (p_video_frame.p_data) {
      QImage frame(p_video_frame.p_data, p_video_frame.xres, p_video_frame.yres,
                   QImage::Format_ARGB32);
      emit answer(type, frame.copy(), true, "Success");
    } else {
      emit answer(type, QImage(), false, "Failed to get NDI source data");
    }
    NDIlib_recv_free_video_v2(m_pNDI_recv, &p_video_frame);
  } while (false);

  QTimer::singleShot(0, this, [=]() { this->handle(type, param); });
}

void NdiReceiveWorker::handleSwitchNdiStatus(
    const QNdiManagerCore::NdiGeneralType &type, const QVariant &param) {
  if (!param.isValid() || param.isNull()) {
    emit answer(type, param, false, "Invalid parameter");
    return;
  }
  this->m_isPaused = param.toBool();
  emit answer(type, param, true, "Success");
}

} // namespace Manager
} // namespace QNK
