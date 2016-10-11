#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include <QObject>
#include <QString>

#include "IMainController.h"
#include "ViewModel.h"
#include "data_generated.h"
using namespace MyTransportInfo;

class IViewFactory;
class IMainView;
class tcpserver;
class client;

class MainController : public QObject, public IMainController
{
    Q_OBJECT

public:
    MainController(IViewFactory *factory);
	~MainController();

public:
    // IMainController interface
    int Execute();
    bool SendCmd(int nChannelNum, LBTDMessage::MessType type, int param);
public:
    // IMainController interface


public slots:
    void ShowInfo(const TransportInfo* pInfo);

private:


private:
    IViewFactory *mViewFactory;
    IMainView *mMainView;
    tcpserver *mTcpServer;
    client    *mClient;
};

#endif
