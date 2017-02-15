#ifndef WARNDIALOG_H
#define WARNDIALOG_H

#include <QDialog>
#include "data_generated.h"
#include <list>
using namespace MyTransportInfo;

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

namespace Ui {
class WarnDialog;
}

class IMainController;

class WarnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WarnDialog(int index,
                        const TransportInfo* info,
                        const QByteArray& data,
                        IMainController *controller,
                        QWidget *parent = 0);
    ~WarnDialog();
    void set_transport_info(const TransportInfo* info,const QByteArray& data);
private:
    Ui::WarnDialog *ui;
    int m_index;
    const TransportInfo* m_info;
    std::list<QByteArray> m_list_info;
    IMainController *controller;
private:
    void init();
    void show_cardinfo();
    void show_content();
    void show_gate();
    void show_ticketinfo();
    void hide_ticketinfo();
    void show_label_pic();
    void show_idcard_pic();
    void show_face_pic();
    void show_screen_pic();
    void show_switch_bg(const QString& path);

private slots:
    void recive_showtime();
    void on_pushButton_warn_opengate_clicked();
    void on_pushButton_warn_verifyno_clicked();
    void on_pushButton_warn_deal_clicked();

signals:
    void warndialog_destory();
};

#endif // WARNDIALOG_H
