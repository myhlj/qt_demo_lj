#ifndef DOUBLECHANNELWIDGET_H
#define DOUBLECHANNELWIDGET_H

#include <QWidget>
#include <QVector>
#include <QMovie>
#include "IMainView.h"
#include "warndialog.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

class BottomPicLabel;

namespace Ui {
class DoubleChannelWidget;
}

class DoubleChannelWidget : public QWidget, public IMainView
{
    Q_OBJECT

public:
    explicit DoubleChannelWidget(QWidget *parent = 0);
    ~DoubleChannelWidget();

    // IMainView interface
    void SetController(IMainController *controller);
    void Init();
    void ShowView();
    void ShowAcrossInfo(const QByteArray& data);
protected:
    void closeEvent(QCloseEvent *);

private slots:

    void on_comboBox_chanel_currentIndexChanged(int index);

    void on_toolButton_switch_clicked();

    void on_toolButton_opengate_clicked();

    void on_toolButton_opengate_2_clicked();

    void on_toolButton_shutdown_clicked();

    void on_toolButton_restart_clicked();

    void on_toolButton_exit_clicked();

    void on_label_pic1_push_down();
    void on_label_pic2_push_down();
    void on_label_pic3_push_down();
    void on_label_pic4_push_down();
    void on_label_pic5_push_down();
    void on_label_pic6_push_down();
    void on_label_pic7_push_down();

    void on_toolButton_next_clicked();

    void on_toolButton_prev_clicked();

    void on_toolButton_search_clicked();

    void on_toolButton_search_2_clicked();

    void keyboardDestoryed();
    void keyboardOnOk();
    void recive_showtime();
private:
    Ui::DoubleChannelWidget *ui;
    IMainController *controller;
    bool            m_bSwitched;
    QVector<QByteArray> m_vector_data;
    int             m_nBatch;//记录当前批次
    QMovie*         m_pMovie;//播放gif
    int             m_across_num_chanel1;//通道一当天通过人数
    int             m_across_warnnum_chanel1;//通道一当天报警人数
    int             m_across_num_chanel2;
    int             m_across_warnnum_chanel2;
    WarnDialog*     m_warndialog;
private:
    void InitComboxChanel();
    void SaveToVector(const QByteArray& data);
    void ShowCardInfo(const TransportInfo *pInfo,int index);
    void ShowCardPic(const TransportInfo *pInfo,int index);
    void ShowTicketInfo(const TransportInfo *pInfo,int index);
    void ShowAcrossNum(const TransportInfo *info,int index);
    void ShowAcrossWarnNum(const TransportInfo *info,int index);
    void ShowBottomPic();
    void ShowPic(BottomPicLabel* pLabel,const TransportInfo* pInfo);
    void ClearPic(BottomPicLabel* pLabel);
    void LabelPicPushDownShow(BottomPicLabel* pLabel,const TransportInfo *pInfo);
    bool SaveData(const QByteArray& data,const TransportInfo* pInfo);
    void GetPrevBatchData();
    void GetNextBatchData();
    void GetNewBatchData();
    void write_acrossnum_to_file();
    void show_warndialog(int index,const TransportInfo* info);
};

#endif // DOUBLECHANNELWIDGET_H
