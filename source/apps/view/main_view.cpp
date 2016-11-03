#include "main_view.h"

#include <QUiLoader>
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QPainter>
#include <QFileDialog>
#include <QDirIterator>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include "IMainController.h"

MainView::MainView(QWidget *parent) :
    QWidget(parent)
{

}

MainView::~MainView()
{

}

void MainView::SetController(IMainController *controller)
{
    this->controller = controller;
}

void MainView::Init()
{
    QUiLoader loader;
    QString filePath = QString("%1/forms/mainwindow.ui").arg(QApplication::applicationDirPath());
    QFile file(filePath);
    if(!file.exists())
    {
        qDebug() << "ui file not exist";
        return;
    }

    file.open(QFile::ReadOnly);
    ui = loader.load(&file, this);
    file.close();

//    InitControls();

    QMetaObject::connectSlotsByName(this);
}

void MainView::ShowView()
{
//    ui->show();
    this->show();
}

void MainView::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::question(this, tr("Are you sure?"), tr("Are you sure?"), QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::No)
    {
        event->ignore();
    }
}

void MainView::ShowAcrossInfo(const QByteArray& data)
{

}
