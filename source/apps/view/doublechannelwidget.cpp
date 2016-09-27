#include "doublechannelwidget.h"
#include "ui_doublechannelwidget.h"

#include <QUiLoader>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>

DoubleChannelWidget::DoubleChannelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoubleChannelWidget)
{
    ui->setupUi(this);
}

DoubleChannelWidget::~DoubleChannelWidget()
{
    delete ui;
}

void DoubleChannelWidget::SetController(IMainController *controller)
{
    this->controller = controller;
}

void DoubleChannelWidget::Init()
{

}

void DoubleChannelWidget::ShowView()
{
//    ui->show();
    this->show();
}

void DoubleChannelWidget::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::question(this, tr("Are you sure?"), tr("Are you sure?"), QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::No)
    {
        event->ignore();
    }
}
