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


MainController::MainController(IViewFactory *factory) :
    mViewFactory(factory),
    mMainView(NULL)
{
    mTcpServer = new tcpserver();
}

MainController::~MainController()
{

}

int MainController:: Execute()
{
    mMainView = mViewFactory->CreateMainView();
    mMainView->SetController(this);
    mMainView->Init();
    mMainView->ShowView();
    mTcpServer->Init();
    return 0;
}
