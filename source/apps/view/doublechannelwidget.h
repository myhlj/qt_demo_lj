#ifndef DOUBLECHANNELWIDGET_H
#define DOUBLECHANNELWIDGET_H

#include <QWidget>
#include <QVector>
#include "IMainView.h"


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

    // QWidget interface
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

private:
    Ui::DoubleChannelWidget *ui;
    IMainController *controller;
    bool            m_bSwitched;
    QVector<QByteArray> m_vector_data;
    enum blackResult{
        bingo = 1,
        notBlack,
        notCompare
    };
    int             m_nBatch;//记录当前批次
private:
    void InitComboxChanel();
    void SaveToVector(const QByteArray& data);//界面显示7张图片
    void ShowCardInfo(const TransportInfo *pInfo,int index);
    void ShowCardPic(const TransportInfo *pInfo,int index);
    void ShowTicketInfo(const TransportInfo *pInfo,int index);
    void ShowBottomPic();
    void ShowPic(BottomPicLabel* pLabel,const TransportInfo* pInfo);
    void LabelPicPushDownShow(BottomPicLabel* pLabel,const TransportInfo *pInfo);
    //接收一条数据都存储,存储文件格式为 日期时间_身份证号_通道
    bool SaveData(const QByteArray& data,const TransportInfo* pInfo);
    void GetPrevBatchData();//获取上一批数据,每批7条数据
    void GetNextBatchData();//获取下一批数据
    void GetNewBatchData();//获取最新的一批数据
};

#endif // DOUBLECHANNELWIDGET_H
