#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <string>
#include <messagelbtd_generated.h>

/*
 * 发送给闸机命令,例如开门,关门,关机
*/
class client : public QObject
{
    Q_OBJECT
public:
    explicit client(QObject *parent = 0);
    ~client();
    //向闸机发送命令,当消息type设置门状态和比对状态或者曝光时，param值有意义
    bool SendCmd(int nChannelNum,LBTDMessage::MessType type,int param=0);
    std::string GetError();
private:
    bool Send(const std::string& sIP,int port,const char* data,int length);
private:
    QTcpSocket*      m_p_client;
    bool             m_b_isconnected;
    std::string      m_s_error;
signals:

public slots:
    void displayError(QAbstractSocket::SocketError);
    void readMessage();
    void connected();
    void disconnected();
};

#endif // CLIENT_H
