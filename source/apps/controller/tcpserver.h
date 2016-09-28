#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QtNetwork>
#include "data_generated.h"
using namespace MyTransportInfo;

class tcpserver : public QObject
{
    Q_OBJECT
public:
    explicit tcpserver(QObject *parent = 0);
    ~tcpserver();
    bool Init();
private:
    QTcpServer          *m_p_server;
    QTcpSocket          *m_p_clientConnection;
signals:

public slots:
    void   acceptConnection();
    void   readClient();
};

#endif // TCPSERVER_H
