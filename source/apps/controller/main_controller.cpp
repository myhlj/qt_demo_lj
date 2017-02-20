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
#include "options.h"


MainController::MainController(IViewFactory *factory) :
    mViewFactory(factory),
    mMainView(NULL)
{
    mTcpServer = new tcpserver(this);
    mClient = new client();
    mHttpClient = new hs_vf_core_http();
}

MainController::~MainController()
{
    delete mTcpServer;
    delete mClient;
    mHttpClient->uninit();
    delete mHttpClient;
}

int MainController:: Execute()
{
    mMainView = mViewFactory->CreateMainView();
    mMainView->SetController(this);
    mMainView->Init();
    mMainView->ShowView();
    mTcpServer->Init();
    mClient->start();
    mHttpClient->init();
    connect(mHttpClient,SIGNAL(request_complete(QByteArray,QNetworkReply::NetworkError,string)),
            this,SLOT(recv_request(QByteArray,QNetworkReply::NetworkError,string)));
    return 0;
}


void MainController::ShowInfo(const QByteArray data)
{
    //调用界面接口,显示信息
    mMainView->ShowAcrossInfo(data);
}

void MainController::SendCmd(int nChannelNum, LBTDMessage::MessType type,IDCardInfo* info,int paramL,string sParamR)
{
    return mClient->SendCmd(nChannelNum,type,info,sParamR,paramL);
}


void MainController::request_cardinfo(string cardno, string url)
{
    if(!verify_idnumber(cardno)){
        IDCardInfo info;
        mMainView->ShowSearchInfo(info,STATUSCARDNOERROR,"身份证号码格式错误");
        return;
    }
    QByteArray bytes = ProducePopulationJson::get_population_json(cardno);
    mHttpClient->post(url,bytes,options::get_instance()->GetPoplationTimeout());
}

void MainController::recv_request(QByteArray bytes, QNetworkReply::NetworkError error,string errordes)
{
    IDCardInfo info;
    if(error == QNetworkReply::NoError){
        ProducePopulationJson json;
        string descript;
        int status = json.analy_request_json(bytes,info,descript);
        //界面显示
        mMainView->ShowSearchInfo(info,status,descript);
    }else{
        mMainView->ShowSearchInfo(info,STATUSSOCKETERROR,errordes);
    }
}

bool MainController::verify_idnumber(string a)
{
    if (a.length() != 18){
        return false;
    }
    int sum = (a[0] - '0') * 7 + (a[1] - '0') * 9 + (a[2] - '0') * 10
            + (a[3] - '0') * 5 + (a[4] - '0') * 8 + (a[5] - '0') * 4
            + (a[6] - '0') * 2 + (a[7] - '0') * 1 + (a[8] - '0') * 6
            + (a[9] - '0') * 3 + (a[10] - '0') * 7 + (a[11] - '0') * 9
            + (a[12] - '0') * 10 + (a[13] - '0') * 5 + (a[14] - '0') * 8
            + (a[15] - '0') * 4 + (a[16] - '0') * 2;
    int k = sum % 11;
    char lastNumber;
    if (k == 0){
        lastNumber = '1';
    }else if (k == 1){
        lastNumber = '0';
    }else if (k == 2){
        lastNumber = 'X';
    }else{
        lastNumber = '0'+12-k;
    }
    if(a[17] == lastNumber){
        return true;
    }else{
        return false;
    }
}
