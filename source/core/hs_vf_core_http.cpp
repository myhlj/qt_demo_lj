#include <QUrl>
#include <QDebug>
#include "hs_vf_core_http.h"


hs_vf_core_http::hs_vf_core_http(QObject* /*parent*/) : m_network_manager(NULL)
  ,m_reply_timeout(NULL)
{

}

hs_vf_core_http::~hs_vf_core_http()
{

}


bool hs_vf_core_http::init(const string& url)
{
    QUrl qurl(QString::fromStdString(url));
    if(!qurl.isValid()){
        return false;
    }

    m_url = url;
    m_network_manager = new QNetworkAccessManager;
    connect(m_network_manager, SIGNAL(finished(QNetworkReply*))
            , this, SLOT(reply_finished(QNetworkReply*)));

    m_reply_timeout = new MyReplyTimeout(this);
    connect(m_reply_timeout,SIGNAL(timeout()),this,SLOT(reply_timeouted()));

    return true;
}

void hs_vf_core_http::uninit()
{
    if(m_network_manager)
    {
        delete m_network_manager;
        m_network_manager = NULL;
    }
    if(m_reply_timeout)
    {
        delete m_reply_timeout;
        m_reply_timeout = NULL;
    }
}

void hs_vf_core_http::reply_finished(QNetworkReply *reply)
{
    QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    int status = statusCodeV.toInt();
    qDebug() << status;
    if (reply->error() == QNetworkReply::NoError){
        m_reply_timeout->stop_timer();
        QByteArray bytes = reply->readAll();
        QString back = QString::fromUtf8(bytes);
        qDebug() << back;
        emit validate_complete(back,reply->error());
    }else{
       qDebug()<< "replyFinished:  "<< reply->error() << " "<<reply->errorString();
       if(reply->error() == QNetworkReply::OperationCanceledError){
           //因为超时所以操作被取消
           emit validate_complete("",QNetworkReply::TimeoutError);
       }else{
           m_reply_timeout->stop_timer();
           emit validate_complete("",reply->error());
       }
    }
    reply->deleteLater();
}

void hs_vf_core_http::reply_timeouted()
{
    qDebug() << "http get/post timeout";
}

void hs_vf_core_http::post(const QByteArray &bytes,int timeout_sec)
{
    QUrl url(QString::fromStdString(m_url));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QVariant("application/json"));

    QNetworkReply* reply = m_network_manager->post(request, bytes);
    //设置超时时间
    m_reply_timeout->stop_timer();
    m_reply_timeout->start_timer(reply,1000 * timeout_sec);
}
