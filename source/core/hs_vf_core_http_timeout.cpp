#include "hs_vf_core_http_timeout.h"

MyReplyTimeout::MyReplyTimeout(QObject */*pParent*/) :
    m_network_reply(NULL)
{
    m_timer = new QTimer();
}

MyReplyTimeout::~MyReplyTimeout()
{
    stop_timer();
    if(m_timer)
    {
        delete m_timer;
        m_timer = NULL;
    }
}

void MyReplyTimeout::on_timeouted()
{
    // 处理超时
    if (m_network_reply->isRunning())
    {
        m_network_reply->abort();
        m_network_reply->deleteLater();
        emit timeout();
    }
}

void MyReplyTimeout::start_timer(QNetworkReply *reply,const int timeout)
{
    Q_ASSERT(reply);
    m_network_reply = reply;
    if (reply && reply->isRunning())
    {
        // 启动单次定时器
        connect(m_timer, SIGNAL(timeout()), this, SLOT(on_timeouted()));
        m_timer->setSingleShot(true);
        m_timer->start(timeout);
    }
}

void MyReplyTimeout::stop_timer()
{
    if(m_timer->isActive())
    {
        m_timer->stop();
    }
}
