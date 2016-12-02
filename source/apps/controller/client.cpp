#include "client.h"
#include "options.h"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace LBTDMessage;
#define GATESPORT 88991

client::client(QObject *parent) : QThread(parent),m_bStop(false)
{

}

client::~client()
{
    m_bStop = true;
    wait();
}


void client::run()
{
    while(!m_bStop){
        m_qmutex.lock();
        if(m_list_data.empty()){
            m_qmutex.unlock();
            usleep(40 * 1000);
            continue;
        }
        cmd_data data = m_list_data.front();
        m_list_data.pop_front();
        m_qmutex.unlock();

        SendBuffer(data);
        usleep(40 * 1000);
    }
}

bool client::Send(const string &sIP, int port, const char *data, int length,string& sError)
{
    QTcpSocket* m_p_client = new QTcpSocket(NULL);

    m_p_client->connectToHost(sIP.c_str(),port);
    if(m_p_client->waitForConnected()){
        //先发一个固定的8位包长度
        char sLength[9] = {0};
        snprintf(sLength,9,"%08d",length);
        m_p_client->write(sLength,8);
        if(length == m_p_client->write(data,length)){
            if(m_p_client->waitForBytesWritten()){
                m_p_client->disconnectFromHost();
                if (m_p_client->state() == QAbstractSocket::UnconnectedState ||
                        m_p_client->waitForDisconnected()){
                    delete m_p_client;
                    return true;
                }else{
                    goto error;
                }
            }else{
                goto error;
            }
        }else{
            goto error;
        }
    }else{
        goto error;
    }
error:
    m_p_client->disconnectFromHost();
    //日志
    sError = m_p_client->errorString().toStdString();
    delete m_p_client;

    return false;
}

void client::readMessage()
{

}

void client::connected()
{
    //连接成功
}

void client::disconnected()
{
}

void client::displayError(QAbstractSocket::SocketError)
{

}

void client::SendCmd(int nChannelNum,LBTDMessage::MessType type,string sParamR,int paramL)
{
    cmd_data data;
    data.nChannelNum = nChannelNum;
    data.type = type;
    data.paramL = paramL;
    data.strParamR = sParamR;
    m_qmutex.lock();
    m_list_data.push_back(data);
    m_qmutex.unlock();
}

void client::SendBuffer(const cmd_data &data)
{
    //生成命令
    options* pOptions = options::get_instance();
    ChannelInfo info;
    if(pOptions->GetChannelInfo(data.nChannelNum,info)){
        flatbuffers::FlatBufferBuilder builder;
        auto message = CreateMessageLBTDDirect(builder,"HisignMess",data.type,data.paramL,data.strParamR.c_str());
        builder.Finish(message);
        uint8_t *buf = builder.GetBufferPointer();
        int size = builder.GetSize();
        string sError;
        if(!Send(info.strchannelIP,GATESPORT,(const char*)buf,size,sError)){
            cout<<sError<<endl;
        }
    }
}
