#include "qndikitmanagerwidget.h"
#include <QVBoxLayout>
#include <QLabel>

QNdiKitManagerWidget::QNdiKitManagerWidget(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    auto label = new QLabel("NDI Manager Widget", this);
    layout->addWidget(label);
}

QNdiKitManagerWidget::~QNdiKitManagerWidget()
{
} 