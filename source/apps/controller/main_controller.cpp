#include "main_controller.h"

#include <string>

#include <QDir>
#include <QFile>
#include <QThread>
#include <QDebug>
#include <QApplication>
#include <QFileInfo>

#include "IViewFactory.h"
#include "IMainView.h"
#include "tcpserver.h"
#include "client.h"


MainController::MainController(IViewFactory *factory) :
    mViewFactory(factory),
    mMainView(NULL)
{
    mTcpServer = new tcpserver(this);
    mClient = new client();
}

MainController::~MainController()
{
    delete mTcpServer;
    delete mClient;
}

int MainController:: Execute()
{
    mMainView = mViewFactory->CreateMainView();
    mMainView->SetController(this);
    mMainView->Init();
    mMainView->ShowView();
    mTcpServer->Init();
    mClient->start();
    return 0;
}


void MainController::ShowInfo(const QByteArray data)
{
    //调用界面接口,显示信息
    mMainView->ShowAcrossInfo(data);
}

void MainController::SendCmd(int nChannelNum, LBTDMessage::MessType type,int paramL,string sParamR)
{
    return mClient->SendCmd(nChannelNum,type,sParamR,paramL);
}
