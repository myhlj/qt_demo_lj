#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include <QObject>
#include <QString>

#include "IMainController.h"
#include "ViewModel.h"
#include "data_generated.h"
#include "hs_vf_core_http.h"
#include "producepopulationjson.h"
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
    void SendCmd(int nChannelNum, LBTDMessage::MessType type,IDCardInfo* info=NULL,int paramL=0,string sParamR="");
    void request_cardinfo(string cardno,string url);
public:
    // IMainController interface
public slots:
    void ShowInfo(const QByteArray data);
private slots:
    void recv_request(QByteArray bytes,QNetworkReply::NetworkError error,string errordes="");
private:
    bool verify_idnumber(string a);
private:
    IViewFactory *mViewFactory;
    IMainView *mMainView;
    tcpserver *mTcpServer;
    client    *mClient;
    hs_vf_core_http* mHttpClient;
};

#endif
