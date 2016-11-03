#include <iostream>
#include "tcpserver.h"
#include "options.h"
using namespace std;
#define PORT 9529

tcpserver::tcpserver(MainController *pMainCtr, QObject *parent) : QObject(parent)
  ,m_p_maincontorller(pMainCtr)
{
    options::get_instance();
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
    m_p_clientConnection = m_p_server->nextPendingConnection();
    connect(m_p_clientConnection, SIGNAL(readyRead()), this, SLOT(readClient()));
}

void tcpserver::readClient()
{
    QByteArray data = m_p_clientConnection->readAll();
    connect(m_p_clientConnection, SIGNAL(disconnected()), m_p_clientConnection, SLOT(deleteLater()));
    //m_p_clientConnection->write("hello disconnected");
    m_p_clientConnection->disconnectFromHost();
    //auto info = GetTransportInfo(data.constData());
    emit(ShowTransinfo(data));
}
