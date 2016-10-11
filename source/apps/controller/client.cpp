#include "client.h"
#include "options.h"
#include <iostream>
using namespace std;
using namespace LBTDMessage;
#define GATESPORT 9531

client::client(QObject *parent) : QObject(parent),
    m_b_isconnected(false)
{
    m_p_client = new QTcpSocket(this);

    connect(m_p_client,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(m_p_client,SIGNAL(connected()),this,SLOT(connected()));
    connect(m_p_client,SIGNAL(error(QAbstractSocket::SocketError)),
             this,SLOT(displayError(QAbstractSocket::SocketError)));
    connect(m_p_client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

client::~client()
{
    delete m_p_client;
}

bool client::Send(const string &sIP, int port, const char *data, int length)
{
    if(!m_b_isconnected){
        m_p_client->connectToHost(sIP.c_str(),port);
        if(m_p_client->waitForConnected()){
            if(length == m_p_client->write(data,length)){
                if(m_p_client->waitForBytesWritten()){
                    m_p_client->disconnectFromHost();
                    if (m_p_client->state() == QAbstractSocket::UnconnectedState ||
                              m_p_client->waitForDisconnected()){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void client::readMessage()
{

}

void client::connected()
{
    m_b_isconnected = true;
}

void client::disconnected()
{
    m_b_isconnected = false;
}

void client::displayError(QAbstractSocket::SocketError)
{
    m_s_error = m_p_client->errorString().toStdString();
    cout<<m_s_error<<endl;
}

bool client::SendCmd(int nChannelNum, MessType type, int param)
{
    //生成命令
    options* pOptions = options::get_instance();
    ChannelInfo info;
    if(pOptions->GetChannelInfo(nChannelNum,info)){
        flatbuffers::FlatBufferBuilder builder;
        auto message = CreateMessageLBTDDirect(builder,type,info.strchannelIP.c_str(),param);
        builder.Finish(message);
        uint8_t *buf = builder.GetBufferPointer();
        int size = builder.GetSize();
        return Send(info.strchannelIP,GATESPORT,(const char*)buf,size);
    }
    return false;
}

std::string client::GetError()
{
    return m_s_error;
}
