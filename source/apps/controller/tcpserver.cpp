#include <iostream>
#include "tcpserver.h"
#include "options.h"
using namespace std;
#define PORT 9529

tcpserver::tcpserver(MainController *pMainCtr, QObject *parent) : QObject(parent)
  ,m_p_maincontorller(pMainCtr)
{
}

tcpserver::~tcpserver()
{
    m_p_server->close();
    delete m_p_server;
}

bool tcpserver::Init()
{
    //连接和MainContorller的槽通信

    connect(this,SIGNAL(ShowTransinfo(const QByteArray)),
            m_p_maincontorller,SLOT(ShowInfo(const QByteArray)));

    m_p_server = new QTcpServer();
    if(m_p_server->listen(QHostAddress::Any,PORT)){
        connect(m_p_server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
        return true;
    }
    return false;
}

void tcpserver::acceptConnection()
{
     QTcpSocket *p_clientConnection = m_p_server->nextPendingConnection();
     readClient(p_clientConnection);
}

void tcpserver::readClient(QTcpSocket* pClient)
{
    QByteArray data;
    if(pClient->waitForReadyRead()){
        //先读大小,8位
        QByteArray length = pClient->read(8);
        QString sLength(length.data());
        int nLength = sLength.toInt();
        if(nLength <= 0){
            return;
        }

        //然后读数据
        char* pBuffer = new char[nLength];
        int nTotalLen = 0;
        while(true){
            if(pClient->waitForReadyRead()){
                int readLen = pClient->read(pBuffer,nLength);
                if(readLen == 0 || readLen == -1){//读取报错
                    cout<<"read failed:"<<nTotalLen<<endl;
                    return;
                }
                data.append(pBuffer,readLen);
                nTotalLen += readLen;
                if(nTotalLen == nLength)
                    break;
            }
        }
        connect(pClient, SIGNAL(disconnected()), pClient, SLOT(deleteLater()));
        pClient->disconnectFromHost();
    }
    emit(ShowTransinfo(data));
}
