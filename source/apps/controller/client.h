#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <string>
#include <messagelbtd_generated.h>
#include <list>
#include <QThread>
#include <QMutex>
#include <QTcpSocket>
using namespace std;

/*
 * 发送给闸机命令,例如开门,关门,关机
*/
class client : public QThread
{
    Q_OBJECT
public:
    explicit client(QObject *parent = 0);
    ~client();
    //向闸机发送命令,当消息type设置门状态和比对状态或者曝光时，param值有意义
    void SendCmd(int nChannelNum,LBTDMessage::MessType type,string sParamR="",int paramL=0);
private:
    void run();
    bool Send(const std::string& sIP,int port,const char* data,int length,string& sError);
private:
    struct cmd_data{
        int                     nChannelNum;
        LBTDMessage::MessType   type;
        int                     paramL;
        string                  strParamR;
    };
    std::list<cmd_data> m_list_data;
    volatile bool       m_bStop;
    QMutex              m_qmutex;
    void SendBuffer(const cmd_data& data);
signals:

public slots:
    void displayError(QAbstractSocket::SocketError);
    void readMessage();
    void connected();
    void disconnected();
};

#endif // CLIENT_H
