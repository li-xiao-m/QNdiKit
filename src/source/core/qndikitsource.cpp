#include "qndikitsource.h"

QNdiKitSource::QNdiKitSource(QObject *parent)
    : QObject(parent)
{
}

QNdiKitSource::~QNdiKitSource()
{
}

void QNdiKitSource::setName(const QString &name)
{
    m_name = name;
}

QString QNdiKitSource::name() const
{
    return m_name;
} 