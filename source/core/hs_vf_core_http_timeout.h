#ifndef HS_VF_CORE_HTTP_TIMEOUT_H
#define HS_VF_CORE_HTTP_TIMEOUT_H

#include <QObject>
#include <QNetworkReply>
#include <QTimer>

class MyReplyTimeout : public QObject
{
    Q_OBJECT
public:
    MyReplyTimeout(QObject *pParent);
    ~MyReplyTimeout();
public:
    void start_timer(QNetworkReply *reply,const int timeout);
    void stop_timer();

signals:
    void timeout();  // 超时信号
public slots:
    void on_timeouted();

private:
    QNetworkReply* m_network_reply;
    QTimer*        m_timer;
};

#endif // HS_VF_CORE_HTTP_TIMEOUT_H
