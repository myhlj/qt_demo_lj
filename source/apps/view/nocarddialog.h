#ifndef NOCARDDIALOG_H
#define NOCARDDIALOG_H

#include <QDialog>
#include <string>
#include "common_data.h"
#include "messagelbtd_generated.h"
using namespace LBTDMessage;
using namespace std;

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

namespace Ui {
class NoCardDialog;
}

class IMainController;
class NoCardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NoCardDialog(IMainController *controller,
                          const IDCardInfo& info,
                          int status,
                          const string errordes,
                          QWidget *parent = 0);
    ~NoCardDialog();
private slots:
    void on_pushButton_nocard_verifyno_clicked();
    void on_pushButton_nocard_deal_clicked();
    void recive_showtime();
signals:
    void nocarddialog_destory();
private:
    void init();
    void show_cardtextinfo();
    void show_content();
    void show_cardpic();
private:
    Ui::NoCardDialog *ui;
    IMainController *m_controller;
    int m_index;
    IDCardInfo       m_cardinfo;
    int m_status;
    string           m_errordes;
};

#endif // NOCARDDIALOG_H
