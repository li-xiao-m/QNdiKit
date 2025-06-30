#include "findndisourceworker.h"
#include <QDebug>

namespace QNK {
namespace Manager {
FindNdiSourceWorker::FindNdiSourceWorker(QObject *parent)
    : QObject{parent}
{
    initializeNDI();
    this->handleFindNdiSource(QNK::Manager::QNdiManagerCore::FindNdiSource);
}

void FindNdiSourceWorker::handle(const QNK::Manager::QNdiManagerCore::NdiManagerType &type,
                                const QVariant &param)
{
    switch(type)
    {
        default:
            break;
    }
}

void FindNdiSourceWorker::initializeNDI()
{
    if(!NDIlib_initialize())
    {
        qDebug() << "NDIlib_initialize failed";
        return;
    }
    m_pNDI_find = NDIlib_find_create_v2();
    if(m_pNDI_find == nullptr)
    {
        qDebug() << "NDIlib_find_create_v2 failed";
        return;
    }
}

void FindNdiSourceWorker::handleFindNdiSource(const QNK::Manager::QNdiManagerCore::NdiManagerType &type, const QVariant &param)
{
    if(m_pNDI_find == nullptr)
    {
        emit answer(type, param, false, "NDIlib_find_create_v2 failed");
        return;
    }
    QVariantList sources;
    const NDIlib_source_t *p_sources = nullptr;
    uint32_t no_sources = 0;
    NDIlib_find_wait_for_sources(m_pNDI_find, 3000);
    p_sources = NDIlib_find_get_current_sources(m_pNDI_find, &no_sources);
    for(uint32_t i = 0; i < no_sources; i++)
    {
        sources.append(p_sources[i].p_ndi_name);
    }
    emit answer(type, sources, true, "NDIlib_find_get_current_sources success");
}
}
}