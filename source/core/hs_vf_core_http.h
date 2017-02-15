#ifndef HS_VF_CORE_HTTP_H
#define HS_VF_CORE_HTTP_H

#include <QObject>
#include <string>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtNetwork>
#include "hs_vf_core_http_timeout.h"
using namespace std;

class hs_vf_core_http : public QObject
{
    Q_OBJECT
public:
    explicit hs_vf_core_http(QObject *parent = 0);
    ~hs_vf_core_http();

    bool init(const string& url);
    void uninit();
    void  post(const QByteArray& bytes,int timeout_sec);
public slots:
    void reply_finished(QNetworkReply * reply);
    void reply_timeouted();
signals:
    void validate_complete(QByteArray back,QNetworkReply::NetworkError error);
private:
    QNetworkAccessManager* m_network_manager;
    MyReplyTimeout*        m_reply_timeout;
    string                 m_url;
};

#endif // HS_VF_CORE_HTTP_H
