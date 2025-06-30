#include "qndikitsourcewidget.h"
#include <QVBoxLayout>
#include <QLabel>

QNdiKitSourceWidget::QNdiKitSourceWidget(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    auto label = new QLabel("NDI Source Widget", this);
    layout->addWidget(label);
}

QNdiKitSourceWidget::~QNdiKitSourceWidget()
{
} 