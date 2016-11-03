#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QtNetwork>
#include "main_controller.h"
#include "data_generated.h"
using namespace MyTransportInfo;

class tcpserver : public QObject
{
    Q_OBJECT
public:
    explicit tcpserver(MainController* pMainCtr,QObject *parent = 0);
    ~tcpserver();
    bool Init();
private:
    QTcpServer          *m_p_server;
    QTcpSocket          *m_p_clientConnection;
    MainController      *m_p_maincontorller;
signals:
    void   ShowTransinfo(const QByteArray);
public slots:
    void   acceptConnection();
    void   readClient();
};

#endif // TCPSERVER_H
