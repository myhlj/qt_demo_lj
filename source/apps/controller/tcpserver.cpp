#include <iostream>
#include "tcpserver.h"
#include "options.h"
using namespace std;
#define PORT 9529

tcpserver::tcpserver(QObject *parent) : QObject(parent)
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
    auto info = GetTransportInfo(data.constData());
    connect(m_p_clientConnection, SIGNAL(disconnected()), m_p_clientConnection, SLOT(deleteLater()));
    //m_p_clientConnection->write("hello disconnected");
    m_p_clientConnection->disconnectFromHost();
}
