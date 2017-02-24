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
    QMessageBox msg_box(QMessageBox::Question, tr("Question"), tr("Are you sure?"));
    msg_box.setStandardButtons (QMessageBox::Ok | QMessageBox::Cancel);
    msg_box.setButtonText(QMessageBox::Ok, QString("确 定"));
    msg_box.setButtonText(QMessageBox::Cancel, QString("取 消"));
    if(msg_box.exec() == QMessageBox::Cancel)
    {
        event->ignore();
    }
}

void MainView::ShowAcrossInfo(const QByteArray& data)
{

}

void MainView::ShowSearchInfo(const IDCardInfo &info, int status, string errordes)
{

}
