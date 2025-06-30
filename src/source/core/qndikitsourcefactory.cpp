#include "qndikitsourcefactory.h"
#include "qndikitsource.h"

QNdiKitSourceFactory::QNdiKitSourceFactory(QObject *parent)
    : QObject(parent)
{
}

QNdiKitSourceFactory::~QNdiKitSourceFactory()
{
}

QNdiKitSource* QNdiKitSourceFactory::createSource(const QString &name, QObject *parent)
{
    auto source = new QNdiKitSource(parent);
    source->setName(name);
    return source;
} 