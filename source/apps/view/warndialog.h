#ifndef WARNDIALOG_H
#define WARNDIALOG_H

#include <QDialog>
#include "data_generated.h"
using namespace MyTransportInfo;

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

namespace Ui {
class WarnDialog;
}

class WarnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WarnDialog(int index,const TransportInfo* info,QWidget *parent = 0);
    ~WarnDialog();
    void set_transport_info(const TransportInfo* info);
private:
    Ui::WarnDialog *ui;
    int m_index;
    const TransportInfo* m_info;
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
};

#endif // WARNDIALOG_H
