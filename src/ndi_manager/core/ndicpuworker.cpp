#include "ndicpuworker.h"
#include <QDebug>
#include <QTimer>

namespace QNK {
namespace Manager {
NdiCpuWorker::NdiCpuWorker(QObject *parent)
    : QObject{parent}
{
    this->initializeNDI();
    this->handle(QNdiManagerCore::FindNdiSource, QVariant());
}

NdiCpuWorker::~NdiCpuWorker()
{
    qDebug() << "NdiCpuWorker::~NdiCpuWorker";
    NDIlib_find_destroy(m_pNDI_find);
    NDIlib_destroy();
}

void NdiCpuWorker::handle(const QNdiManagerCore::NdiGeneralType &type, const QVariant &param)
{
    switch(type)
    {
        case QNdiManagerCore::NdiGeneralType::FindNdiSource:
            handleFindNdiSource(type, param);
            break;
        case QNdiManagerCore::NdiGeneralType::SwitchNdiSource:
            handleSwitchNdiSource(type, param);
            break;
        case QNdiManagerCore::NdiGeneralType::PauseNdiSource:
            handlePauseNdiSource(type, param);
            break;
        case QNdiManagerCore::NdiGeneralType::ResumeNdiSource:
            handleResumeNdiSource(type, param);
            break;
        default:
            break;
    }
}

void NdiCpuWorker::handleFindNdiSource(const QNdiManagerCore::NdiGeneralType &type, const QVariant &param)
{
    QVariantList sources;
    uint32_t no_sources = 0;
    const NDIlib_source_t *p_sources = nullptr;
    p_sources = NDIlib_find_get_current_sources(m_pNDI_find, &no_sources);
    for(uint32_t i = 0; i < no_sources; i++)
    {
        QVariantMap source;
        source["name"] = QString::fromUtf8(p_sources[i].p_ndi_name);
        source["url_address"] = QString::fromUtf8(p_sources[i].p_url_address);
        source["ip_address"] = QString::fromUtf8(p_sources[i].p_ip_address);
        sources.append(source);
    }
    qDebug() << "sources: " << sources;
    emit answer(type, sources, true, "NDIlib_find_get_current_sources success");
    QTimer::singleShot(3000, this, [=](){
        this->handle(QNdiManagerCore::FindNdiSource, QVariant());
    });
}

void NdiCpuWorker::handleSwitchNdiSource(const QNdiManagerCore::NdiGeneralType &type, const QVariant &param)
{
    emit answer(type, param, true, "switch all ndi sources");
}

void NdiCpuWorker::handlePauseNdiSource(const QNdiManagerCore::NdiGeneralType &type, const QVariant &param)
{
    emit answer(type, param, true, "pause all ndi sources");
}

void NdiCpuWorker::handleResumeNdiSource(const QNdiManagerCore::NdiGeneralType &type, const QVariant &param)
{
    emit answer(type, param, true, "resume all ndi sources");
}

void NdiCpuWorker::initializeNDI()
{
    if(!NDIlib_initialize())
    {
        qDebug() << "NDIlib_initialize failed";
        return;
    }
    m_pNDI_find = NDIlib_find_create_v2();
    if(!m_pNDI_find)
    {
        qDebug() << "NDIlib_find_create_v2 failed";
    }
}
}
}