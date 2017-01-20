#include "doublechannelwidget.h"
#include "ui_doublechannelwidget.h"

#include <QUiLoader>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>
#include <QDir>
#include <QDateTime>
#include <QTimer>
#include <iostream>
#include <QPainter>
#include "options.h"
#include "IMainController.h"
#include "THIDImageHelper.h"
#include "keydialog.h"
#include "common_data.h"



#define  MAXFILENUM 2100 //最多存储数据
#define  SHOWFILENUM 7 //界面显示一批7条数据

DoubleChannelWidget::DoubleChannelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoubleChannelWidget),
    m_bSwitched(true),//facemode
    m_nBatch(1),
    m_pMovie(NULL),
    m_across_num_chanel1(0),
    m_across_num_chanel2(0),
    m_across_warnnum_chanel1(0),
    m_across_warnnum_chanel2(0),
    m_warndialog(NULL)
{
    ui->setupUi(this);
    m_pMovie = new QMovie(":img/page/wait.gif");
}

DoubleChannelWidget::~DoubleChannelWidget()
{
    delete ui;
}

void DoubleChannelWidget::SetController(IMainController *controller)
{
    this->controller = controller;
}

void DoubleChannelWidget::Init()
{
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    connect(ui->label_pic1,SIGNAL(push_down(void)),
            this,SLOT(on_label_pic1_push_down(void)));
    connect(ui->label_pic2,SIGNAL(push_down(void)),
            this,SLOT(on_label_pic2_push_down(void)));
    connect(ui->label_pic3,SIGNAL(push_down(void)),
            this,SLOT(on_label_pic3_push_down(void)));
    connect(ui->label_pic4,SIGNAL(push_down(void)),
            this,SLOT(on_label_pic4_push_down(void)));
    connect(ui->label_pic5,SIGNAL(push_down(void)),
            this,SLOT(on_label_pic5_push_down(void)));
    connect(ui->label_pic6,SIGNAL(push_down(void)),
            this,SLOT(on_label_pic6_push_down(void)));
    connect(ui->label_pic7,SIGNAL(push_down(void)),
            this,SLOT(on_label_pic7_push_down(void)));

    InitComboxChanel();
    options* pOption = options::get_instance();
    int nIndex = pOption->GetCurrentChannelIndex();
    switch(nIndex){
        case GATEONE:
        ui->toolButton_opengate->setStyleSheet("border-image: url(:/img/page/btn-gate1.png);");
        ui->toolButton_opengate_2->hide();
        break;
        case GATETWO:
        ui->toolButton_opengate->setStyleSheet("border-image: url(:/img/page/btn-gate2.png);");
        ui->toolButton_opengate_2->hide();
        break;
        case GATEBOTH:
        ui->toolButton_opengate->setStyleSheet("border-image: url(:/img/page/btn-gate1.png);");
        ui->toolButton_opengate_2->show();
        break;
    }
    //布控人员
    ui->label_warn_alise_1->hide();
    //创建存储数据文件夹
    QString qs_path = QCoreApplication::applicationDirPath();
    qs_path += "/saveData";
    QDir dir;
    if(!dir.exists(qs_path)){
        dir.mkdir(qs_path);
    }
    //timer
    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(recive_showtime()));
    timer->start(1000);
    //加载上次过往的最后一批人员
    GetNewBatchData();
    ShowBottomPic();
    //label自动换行
    ui->label_idcardaddress->setWordWrap(true);
    ui->label_idcardaddress->setAlignment(Qt::AlignTop);
    ui->label_idcardaddress_2->setWordWrap(true);
    ui->label_idcardaddress_2->setAlignment(Qt::AlignTop);
}

void DoubleChannelWidget::recive_showtime()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss"); //设置显示格式
    ui->label_curtime->setText(strTime);
}

void DoubleChannelWidget::ShowView()
{
    this->show();
}

void DoubleChannelWidget::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::question(this, tr("Are you sure?"), tr("Are you sure?"), QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::No)
    {
        event->ignore();
    }
}

void DoubleChannelWidget::InitComboxChanel()
{
    options* pOptions = options::get_instance();
    int nCurrentChannelIndex = pOptions->GetCurrentChannelIndex();
    int nChannelNum = pOptions->GetChannelNumber();
    for(int i=0;i<nChannelNum;i++){
        QString temp;
        temp.sprintf("通道%d",i+1);
        ui->comboBox_chanel->addItem(temp);
    }
    ui->comboBox_chanel->addItem("双通道");
    if(nCurrentChannelIndex <= GATEBOTH && nCurrentChannelIndex >= GATEONE)
        ui->comboBox_chanel->setCurrentIndex(nCurrentChannelIndex - 1);
}


void DoubleChannelWidget::ShowAcrossInfo(const QByteArray& data)
{
    const TransportInfo* pInfo = GetTransportInfo(data.constData());
    if(pInfo == NULL){
        return;
    }
    //是否存储在内存供界面显示
    int nIndex = ui->comboBox_chanel->currentIndex();//当前界面选择index
    int nHandle = pInfo->header()->handle();
    switch(nIndex){
        case 0:{//通道1
            if(nHandle == GATEONE){
                ui->label_picchannel_3->setStyleSheet("border-image: url(:/img/page/btn-gate1.png);");
                SaveToVector(data);
                SaveData(data,pInfo);
            }
        }
        break;
        case 1:{//通道2
            if(nHandle == GATETWO){
                ui->label_picchannel_3->setStyleSheet("border-image: url(:/img/page/btn-gate2.png);");
                SaveToVector(data);
                SaveData(data,pInfo);
            }
        }
        break;
        case 2:{//双通道
            if(nHandle == GATEONE || nHandle == GATETWO){
                ui->label_picchannel->setStyleSheet("border-image: url(:/img/page/btn-gate1.png;");
                ui->label_picchannel_2->setStyleSheet("border-image: url(:/img/page/btn-gate2.png;");

                SaveToVector(data);
                SaveData(data,pInfo);
            }
        }
        break;
        default:
        return;
    }
    ShowCardInfo(pInfo,nIndex);
    ShowTicketInfo(pInfo,nIndex);
    ShowAcrossNum(pInfo,nIndex);
    ShowAcrossWarnNum(pInfo,nIndex);
    ShowBottomPic();
    //弹窗显示异常
    show_warndialog(nIndex,pInfo);
}

void DoubleChannelWidget::SaveToVector(const QByteArray &data)
{
    if(m_vector_data.size() > SHOWFILENUM){//界面显示7张图片
        m_vector_data.pop_back();
    }
    m_vector_data.push_front(data);
}

void DoubleChannelWidget::ShowCardInfo(const TransportInfo *pInfo, int index)
{
    switch(index){
        case 0:{//通道1
            if(pInfo->header()->handle() == GATEONE){
                ui->label_acrosstime_3->setText(pInfo->header()->capTime()->c_str());//采集时间
                ui->label_idcardname_3->setText(pInfo->idcardInfo()->name()->c_str());//名字
                ui->label_idcardaddress_3->setText(pInfo->idcardInfo()->address()->c_str());//地址
                ui->label_idcardbirthday_3->setText(pInfo->idcardInfo()->birthday()->c_str());//生日
                ui->label_idcarddepart_3->setText(pInfo->idcardInfo()->agency()->c_str());//机构
                ui->label_idcardnation_3->setText(pInfo->idcardInfo()->folk()->c_str());//民族
                ui->label_idcardnum_3->setText(pInfo->idcardInfo()->code()->c_str());//身份证号
                ui->label_idcardsex_3->setText(pInfo->idcardInfo()->gender()->c_str());//性别
                QString start(pInfo->idcardInfo()->expireStart()->c_str());
                QString end(pInfo->idcardInfo()->expireEnd()->c_str());
                ui->label_idcardusetime_3->setText(start + "-" + end);//有效期
            }
        }
        break;
        case 1:{
            if(pInfo->header()->handle() == GATETWO){
                ui->label_acrosstime_3->setText(pInfo->header()->capTime()->c_str());//采集时间
                ui->label_idcardname_3->setText(pInfo->idcardInfo()->name()->c_str());//名字
                ui->label_idcardaddress_3->setText(pInfo->idcardInfo()->address()->c_str());//地址
                ui->label_idcardbirthday_3->setText(pInfo->idcardInfo()->birthday()->c_str());//生日
                ui->label_idcarddepart_3->setText(pInfo->idcardInfo()->agency()->c_str());//机构
                ui->label_idcardnation_3->setText(pInfo->idcardInfo()->folk()->c_str());//民族
                ui->label_idcardnum_3->setText(pInfo->idcardInfo()->code()->c_str());//身份证号
                ui->label_idcardsex_3->setText(pInfo->idcardInfo()->gender()->c_str());//性别
                QString start(pInfo->idcardInfo()->expireStart()->c_str());
                QString end(pInfo->idcardInfo()->expireEnd()->c_str());
                ui->label_idcardusetime_3->setText(start + "-" + end);//有效期
            }
        }
        break;
        case 2://双通道
        if(pInfo->header()->handle() == GATEONE){//通道1
            ui->label_acrosstime->setText(pInfo->header()->capTime()->c_str());//采集时间
            ui->label_idcardname->setText(pInfo->idcardInfo()->name()->c_str());//名字
            ui->label_idcardaddress->setText(pInfo->idcardInfo()->address()->c_str());//地址
            ui->label_idcardbirthday->setText(pInfo->idcardInfo()->birthday()->c_str());//生日
            ui->label_idcarddepart->setText(pInfo->idcardInfo()->agency()->c_str());//机构
            ui->label_idcardnation->setText(pInfo->idcardInfo()->folk()->c_str());//民族
            ui->label_idcardnum->setText(pInfo->idcardInfo()->code()->c_str());//身份证号
            ui->label_idcardsex->setText(pInfo->idcardInfo()->gender()->c_str());//性别
            QString start(pInfo->idcardInfo()->expireStart()->c_str());
            QString end(pInfo->idcardInfo()->expireEnd()->c_str());
            ui->label_idcardusetime->setText(start + "-" + end);//有效期
        }else if(pInfo->header()->handle() == GATETWO){//通道2
            ui->label_acrosstime_2->setText(pInfo->header()->capTime()->c_str());//采集时间
            ui->label_idcardname_2->setText(pInfo->idcardInfo()->name()->c_str());//名字
            ui->label_idcardaddress_2->setText(pInfo->idcardInfo()->address()->c_str());//地址
            ui->label_idcardbirthday_2->setText(pInfo->idcardInfo()->birthday()->c_str());//生日
            ui->label_idcarddepart_2->setText(pInfo->idcardInfo()->agency()->c_str());//机构
            ui->label_idcardnation_2->setText(pInfo->idcardInfo()->folk()->c_str());//民族
            ui->label_idcardnum_2->setText(pInfo->idcardInfo()->code()->c_str());//身份证号
            ui->label_idcardsex_2->setText(pInfo->idcardInfo()->gender()->c_str());//性别
            QString start(pInfo->idcardInfo()->expireStart()->c_str());
            QString end(pInfo->idcardInfo()->expireEnd()->c_str());
            ui->label_idcardusetime_2->setText(start + "-" + end);//有效期
        }
        break;
    }

    ShowCardPic(pInfo,index);
}


void DoubleChannelWidget::ShowCardPic(const TransportInfo *pInfo, int index)
{
    const unsigned char *pbyOutBuffer = pInfo->idImage()->data();
    int nEncodeSize = pInfo->idImageSize();

    switch(index){
        case 0:{//单通道
            if(pInfo->header()->handle() == GATEONE){
                QImage qTmp;
                bool bRet = qTmp.loadFromData(pbyOutBuffer,nEncodeSize,"bmp");
                if(bRet){
                    qTmp = qTmp.scaled(ui->label_idcardpic_3->width(),
                                           ui->label_idcardpic_3->height(), Qt::KeepAspectRatio);
                    ui->label_idcardpic_3->setPixmap(QPixmap::fromImage(qTmp.mirrored(false,false)));
                }
                switch(pInfo->blackInfo()->blackResult()){//是否比中黑名单
                    case bingo:
                    ui->label_idcardpic_3->setStyleSheet("border: 2px solid red;");
                    ui->label_warn_alise_1->show();//布控人员
                    break;
                    case notMatch:
                    ui->label_idcardpic_3->setStyleSheet("border: 2px solid green;");
                    ui->label_warn_alise_1->hide();//布控人员
                    break;
                    case notCompare:
                    break;
                }
            }
        }
        break;
        case 1:{
            if(pInfo->header()->handle() == GATETWO){
                QImage qTmp;
                bool bRet = qTmp.loadFromData(pbyOutBuffer,nEncodeSize,"bmp");
                if(bRet){
                    qTmp = qTmp.scaled(ui->label_idcardpic_3->width(),
                                           ui->label_idcardpic_3->height(), Qt::KeepAspectRatio);
                    ui->label_idcardpic_3->setPixmap(QPixmap::fromImage(qTmp.mirrored(false,false)));
                }
                switch(pInfo->blackInfo()->blackResult()){//是否比中黑名单
                    case bingo:
                    ui->label_idcardpic_3->setStyleSheet("border: 2px solid red;");
                    ui->label_warn_alise_1->show();//布控人员
                    break;
                    case notMatch:
                    ui->label_idcardpic_3->setStyleSheet("border: 2px solid green;");
                    ui->label_warn_alise_1->hide();//布控人员
                    break;
                    case notCompare:
                    break;
                }
            }
        }
        break;
        case 2://双通道
        if(pInfo->header()->handle() == GATEONE){//通道1
            QImage qTmp;
            bool bRet = qTmp.loadFromData((const uchar*)pbyOutBuffer,nEncodeSize);
            if(bRet){
                qTmp = qTmp.scaled(ui->label_idcardpic->width(),
                                       ui->label_idcardpic->height(), Qt::KeepAspectRatio);
                ui->label_idcardpic->setPixmap(QPixmap::fromImage(qTmp.mirrored(true,false)));
            }
            switch(pInfo->blackInfo()->blackResult()){//是否比中黑名单
                case bingo:
                ui->label_idcardpic->setStyleSheet("border: 2px solid red;");
                break;
                case notMatch:
                ui->label_idcardpic->setStyleSheet("border: 2px solid green;");
                break;
                case notCompare:
                break;
            }
        }else if(pInfo->header()->handle() == GATETWO){
           QImage qTmp;
           bool bRet = qTmp.loadFromData((const uchar*)pbyOutBuffer,nEncodeSize);
           if(bRet){
               qTmp = qTmp.scaled(ui->label_idcardpic_2->width(),
                                  ui->label_idcardpic_2->height(), Qt::KeepAspectRatio);
               ui->label_idcardpic_2->setPixmap(QPixmap::fromImage(qTmp.mirrored(true,false)));
           }

           switch(pInfo->blackInfo()->blackResult()){//是否比中黑名单
                case bingo:
                ui->label_idcardpic_2->setStyleSheet("border: 2px solid red;");
                break;
                case notMatch:
                ui->label_idcardpic_2->setStyleSheet("border: 2px solid green;");
                break;
                case notCompare:
                break;
            }
        }
        break;
    }
}

void DoubleChannelWidget::ShowTicketInfo(const TransportInfo *pInfo, int index)
{
    switch(index){
        case 0://单通道
        if(pInfo->header()->handle() == GATEONE){
            ui->label_station_start->setText(
                        pInfo->ticketInfo()->goStation() == NULL
                        ? "" : pInfo->ticketInfo()->goStation()->c_str());
            ui->label_station_end->setText(
                        pInfo->ticketInfo()->arriveStation() == NULL
                        ? "" : pInfo->ticketInfo()->arriveStation()->c_str());
            ui->label_ticket_num->setText(
                        pInfo->ticketInfo()->ticketNO() == NULL
                        ? "" : pInfo->ticketInfo()->ticketNO()->c_str());
            ui->label_ticket_date->setText(
                        pInfo->ticketInfo()->goTime() == NULL
                        ? "" : pInfo->ticketInfo()->goTime()->c_str());
            ui->label_ticket_index->setText(
                        pInfo->ticketInfo()->busNO() == NULL
                        ? "" : pInfo->ticketInfo()->busNO()->c_str());
        }
        break;
        case 1:
        if(pInfo->header()->handle() == GATETWO){
            ui->label_station_start->setText(
                        pInfo->ticketInfo()->goStation() == NULL
                        ? "" : pInfo->ticketInfo()->goStation()->c_str());
            ui->label_station_end->setText(
                        pInfo->ticketInfo()->arriveStation() == NULL
                        ? "" : pInfo->ticketInfo()->arriveStation()->c_str());
            ui->label_ticket_num->setText(
                        pInfo->ticketInfo()->ticketNO() == NULL
                        ? "" : pInfo->ticketInfo()->ticketNO()->c_str());
            ui->label_ticket_date->setText(
                        pInfo->ticketInfo()->goTime() == NULL
                        ? "" : pInfo->ticketInfo()->goTime()->c_str());
            ui->label_ticket_index->setText(
                        pInfo->ticketInfo()->busNO() == NULL
                        ? "" : pInfo->ticketInfo()->busNO()->c_str());
        }
        break;
        case 2://双通道
        if(pInfo->header()->handle() == GATEONE){//通道1
            ui->label_station_start_2->setText(
                        pInfo->ticketInfo()->goStation() == NULL
                        ? "" : pInfo->ticketInfo()->goStation()->c_str());
            ui->label_station_end_2->setText(
                        pInfo->ticketInfo()->arriveStation() == NULL
                        ? "" : pInfo->ticketInfo()->arriveStation()->c_str());
            ui->label_ticket_num_2->setText(
                        pInfo->ticketInfo()->ticketNO() == NULL
                        ? "" : pInfo->ticketInfo()->ticketNO()->c_str());
            ui->label_ticket_date_2->setText(
                        pInfo->ticketInfo()->goTime() == NULL
                        ? "" : pInfo->ticketInfo()->goTime()->c_str());
            ui->label_ticket_index_2->setText(
                        pInfo->ticketInfo()->busNO() == NULL
                        ? "" : pInfo->ticketInfo()->busNO()->c_str());
        }else if(pInfo->header()->handle() == GATETWO){//通道2
            ui->label_station_start_3->setText(
                        pInfo->ticketInfo()->goStation() == NULL
                        ? "" : pInfo->ticketInfo()->goStation()->c_str());
            ui->label_station_end_3->setText(
                        pInfo->ticketInfo()->arriveStation() == NULL
                        ? "" : pInfo->ticketInfo()->arriveStation()->c_str());
            ui->label_ticket_num_3->setText(
                        pInfo->ticketInfo()->ticketNO() == NULL
                        ? "" : pInfo->ticketInfo()->ticketNO()->c_str());
            ui->label_ticket_date_3->setText(
                        pInfo->ticketInfo()->goTime() == NULL
                        ? "" : pInfo->ticketInfo()->goTime()->c_str());
            ui->label_ticket_index_3->setText(
                        pInfo->ticketInfo()->busNO() == NULL
                        ? "" : pInfo->ticketInfo()->busNO()->c_str());
        }
        break;
    }
}


void DoubleChannelWidget::on_comboBox_chanel_currentIndexChanged(int index)
{
    options* pOption = options::get_instance();
    switch(index){
        case 0:
        ui->toolButton_opengate->setStyleSheet("border-image: url(:/img/page/btn-gate1.png);");
        ui->toolButton_opengate_2->hide();
        ui->label_picchannel_3->setStyleSheet("border-image: url(:/img/page/btn-gate1.png);");
        if(ui->stackedWidget->currentIndex() != 0)
            ui->stackedWidget->setCurrentIndex(0);
        pOption->SetCurrentChannelIndex(index + 1);
        break;
        case 1:
        ui->toolButton_opengate->setStyleSheet("border-image: url(:/img/page/btn-gate2.png);");
        ui->toolButton_opengate_2->hide();
        ui->label_picchannel_3->setStyleSheet("border-image: url(:/img/page/btn-gate2.png);");
        if(ui->stackedWidget->currentIndex() != 0)
            ui->stackedWidget->setCurrentIndex(0);
        pOption->SetCurrentChannelIndex(index + 1);
        break;
        case 2:
        ui->toolButton_opengate->setStyleSheet("border-image: url(:/img/page/btn-gate1.png);");
        ui->toolButton_opengate_2->show();
        if(ui->stackedWidget->currentIndex() != 1)
            ui->stackedWidget->setCurrentIndex(1);
        pOption->SetCurrentChannelIndex(index + 1);
        break;
    }
}

void DoubleChannelWidget::on_toolButton_switch_clicked()
{
    if(!m_bSwitched){
        ui->toolButton_switch->setStyleSheet("border-image: url(:/img/page/btn-verify.png)");
    }
    else{
        ui->toolButton_switch->setStyleSheet("border-image: url(:/img/page/btn-compare.png)");
    }
    m_bSwitched = !m_bSwitched;
    //设置闸机模式,切换模式
    int nIndex = ui->comboBox_chanel->currentIndex();
    switch(nIndex){
        case 0:
        controller->SendCmd(GATEONE,LBTDMessage::MessType_VERIFYMODE,m_bSwitched);
        break;
        case 1:
        controller->SendCmd(GATETWO,LBTDMessage::MessType_VERIFYMODE,m_bSwitched);
        break;
        case 2:
        controller->SendCmd(GATEONE,LBTDMessage::MessType_VERIFYMODE,m_bSwitched);
        controller->SendCmd(GATETWO,LBTDMessage::MessType_VERIFYMODE,m_bSwitched);
        break;
    }
}

void DoubleChannelWidget::on_toolButton_opengate_clicked()
{
    int nIndex = ui->comboBox_chanel->currentIndex();
    switch(nIndex){
        case 0:
        controller->SendCmd(GATEONE,LBTDMessage::MessType_OPENGATE);
        break;
        case 1:
        controller->SendCmd(GATETWO,LBTDMessage::MessType_OPENGATE);
        break;
        case 2:
        controller->SendCmd(GATEONE,LBTDMessage::MessType_OPENGATE);
        break;
    }
}

void DoubleChannelWidget::on_toolButton_opengate_2_clicked()
{
    controller->SendCmd(GATETWO,LBTDMessage::MessType_OPENGATE);
}

void DoubleChannelWidget::on_toolButton_shutdown_clicked()
{
    int nIndex = ui->comboBox_chanel->currentIndex();
    switch(nIndex){
        case 0:
        controller->SendCmd(GATEONE,LBTDMessage::MessType_CLOSETEMINAL);
        break;
        case 1:
        controller->SendCmd(GATETWO,LBTDMessage::MessType_CLOSETEMINAL);
        break;
        case 2:
        controller->SendCmd(GATEONE,LBTDMessage::MessType_CLOSETEMINAL);
        controller->SendCmd(GATETWO,LBTDMessage::MessType_CLOSETEMINAL);
        break;
    }
}

void DoubleChannelWidget::on_toolButton_restart_clicked()
{
    int nIndex = ui->comboBox_chanel->currentIndex();
    switch(nIndex){
        case 0:
        controller->SendCmd(GATEONE,LBTDMessage::MessType_RESTART);
        break;
        case 1:
        controller->SendCmd(GATETWO,LBTDMessage::MessType_RESTART);
        break;
        case 2:
        controller->SendCmd(GATEONE,LBTDMessage::MessType_RESTART);
        controller->SendCmd(GATETWO,LBTDMessage::MessType_RESTART);
        break;
    }
}

void DoubleChannelWidget::on_toolButton_exit_clicked()
{
    int nIndex = ui->comboBox_chanel->currentIndex();
    switch(nIndex){
        case 0:
        controller->SendCmd(GATEONE,LBTDMessage::MessType_EXIT);
        break;
        case 1:
        controller->SendCmd(GATETWO,LBTDMessage::MessType_EXIT);
        break;
        case 2:
        controller->SendCmd(GATEONE,LBTDMessage::MessType_EXIT);
        controller->SendCmd(GATETWO,LBTDMessage::MessType_EXIT);
        break;
    }
}

void DoubleChannelWidget::ShowBottomPic()
{
    const TransportInfo* pInfo = NULL;
    int size = m_vector_data.size();
    if(size > 0){
        pInfo = GetTransportInfo(m_vector_data[0].constData());
        ShowPic(ui->label_pic1,pInfo);
    }else{
        ClearPic(ui->label_pic1);
    }
    if(size > 1){
        pInfo = GetTransportInfo(m_vector_data[1].constData());
        ShowPic(ui->label_pic2,pInfo);
    }else{
        ClearPic(ui->label_pic2);
    }
    if(size > 2){
        pInfo = GetTransportInfo(m_vector_data[2].constData());
        ShowPic(ui->label_pic3,pInfo);
    }else{
        ClearPic(ui->label_pic3);
    }
    if(size > 3){
        pInfo = GetTransportInfo(m_vector_data[3].constData());
        ShowPic(ui->label_pic4,pInfo);
    }else{
        ClearPic(ui->label_pic4);
    }
    if(size > 4){
        pInfo = GetTransportInfo(m_vector_data[4].constData());
        ShowPic(ui->label_pic5,pInfo);
    }else{
        ClearPic(ui->label_pic5);
    }
    if(size > 5){
        pInfo = GetTransportInfo(m_vector_data[5].constData());
        ShowPic(ui->label_pic6,pInfo);
    }else{
        ClearPic(ui->label_pic6);
    }
    if(size > 6){
        pInfo = GetTransportInfo(m_vector_data[6].constData());
        ShowPic(ui->label_pic7,pInfo);
    }else{
        ClearPic(ui->label_pic7);
    }
}

void DoubleChannelWidget::on_label_pic1_push_down()
{
    if(m_vector_data.size() > 0){
        const TransportInfo* pInfo = GetTransportInfo(m_vector_data[0].constData());
        LabelPicPushDownShow(ui->label_pic1,pInfo);
    }
}

void DoubleChannelWidget::LabelPicPushDownShow(BottomPicLabel *pLabel, const TransportInfo *pInfo)
{
    int nIndex = ui->comboBox_chanel->currentIndex();//当前界面选择index
    switch(pInfo->blackInfo()->blackResult()){
    case bingo:
        break;
    case notMatch:
        switch(pInfo->header()->handle()){
            case GATEONE:
            //pLabel->setStyleSheet("border: 0px solid green;");
            //pLabel->setStyleSheet("border-image: url(:/img/page/facebox-aisle1-pushdown.png)");
            break;
            case GATETWO:
            //pLabel->setStyleSheet("border: 0px solid green;");
            //pLabel->setStyleSheet("border-image: url(:/img/page/facebox-aisle2-pushdown.png)");
            break;
        }
        break;
    case notCompare:
        break;
    }
    ShowCardInfo(pInfo,nIndex);
}

void DoubleChannelWidget::on_label_pic2_push_down()
{
    if(m_vector_data.size() > 1){
        const TransportInfo* pInfo = GetTransportInfo(m_vector_data[1].constData());
        LabelPicPushDownShow(ui->label_pic2,pInfo);
    }
}

void DoubleChannelWidget::on_label_pic3_push_down()
{
    if(m_vector_data.size() > 2){
        const TransportInfo* pInfo = GetTransportInfo(m_vector_data[2].constData());
        LabelPicPushDownShow(ui->label_pic3,pInfo);
    }
}

void DoubleChannelWidget::on_label_pic4_push_down()
{
    if(m_vector_data.size() > 3){
        const TransportInfo* pInfo = GetTransportInfo(m_vector_data[3].constData());
        LabelPicPushDownShow(ui->label_pic4,pInfo);
    }
}

void DoubleChannelWidget::on_label_pic5_push_down()
{
    if(m_vector_data.size() > 4){
        const TransportInfo* pInfo = GetTransportInfo(m_vector_data[4].constData());
        LabelPicPushDownShow(ui->label_pic5,pInfo);
    }
}

void DoubleChannelWidget::on_label_pic6_push_down()
{
    if(m_vector_data.size() > 5){
        const TransportInfo* pInfo = GetTransportInfo(m_vector_data[5].constData());
        LabelPicPushDownShow(ui->label_pic6,pInfo);
    }
}

void DoubleChannelWidget::on_label_pic7_push_down()
{
    if(m_vector_data.size() > 6){
        const TransportInfo* pInfo = GetTransportInfo(m_vector_data[6].constData());
        LabelPicPushDownShow(ui->label_pic7,pInfo);
    }
}


void DoubleChannelWidget::ShowPic(BottomPicLabel *pLabel, const TransportInfo *pInfo)
{
    //显示图片
    const unsigned char *pbyOutBuffer = pInfo->cropImage()->data();
    int nEncodeSize = pInfo->cropImageSize();

    QImage qTmp;
    bool bRet = qTmp.loadFromData((const uchar*)pbyOutBuffer,nEncodeSize,"jpg");
    if(bRet){
        QPixmap qPix;
        if(pInfo->blackInfo()->blackResult() == bingo){//比中黑名单
            switch(pInfo->header()->handle()){
            case GATEONE:
                qPix.load(":/img/page/facebox-alarm-aisle1.png");
                break;
            case GATETWO:
                qPix.load(":/img/page/facebox-alarm-aisle2.png");
                break;
            }
        }else if(pInfo->blackInfo()->blackResult() == notMatch){//未比中
            switch(pInfo->header()->handle()){
            case GATEONE:
                qPix.load(":/img/page/facebox-aisle1.png");
                break;
            case GATETWO:
                qPix.load(":/img/page/facebox-aisle2.png");
                break;
            }
        }else if(pInfo->blackInfo()->blackResult() == notCompare){//未必对
            switch(pInfo->header()->handle()){
            case GATEONE:
                qPix.load(":/img/page/facebox-alarm-aisle1.png");
                break;
            case GATETWO:
                qPix.load(":/img/page/facebox-alarm-aisle2.png");
                break;
            }
        }
        pLabel->setStyleSheet("border: 0px solid green;");
        qTmp = qTmp.scaled(pLabel->width(), pLabel->height());
        qTmp = qTmp.mirrored(true,false);
        QPainter painter(&qTmp);
        painter.drawPixmap(0,0,pLabel->width(),pLabel->height(),qPix);
        pLabel->setPixmap(QPixmap::fromImage(qTmp));
    }else{
        if(pInfo->blackInfo()->blackResult() == bingo){//比中黑名单
            switch(pInfo->header()->handle()){
            case GATEONE:
                qTmp.load(":/img/page/facebox-alarm-aisle1.png");
                break;
            case GATETWO:
                qTmp.load(":/img/page/facebox-alarm-aisle2.png");
                break;
            }
        }else if(pInfo->blackInfo()->blackResult() == notMatch){//未比中
            switch(pInfo->header()->handle()){
            case GATEONE:
                qTmp.load(":/img/page/facebox-aisle1.png");
                break;
            case GATETWO:
                qTmp.load(":/img/page/facebox-aisle2.png");
                break;
            }
        }else if(pInfo->blackInfo()->blackResult() == notCompare){//未必对
            switch(pInfo->header()->handle()){
            case GATEONE:
                qTmp.load(":/img/page/facebox-alarm-aisle1.png");
                break;
            case GATETWO:
                qTmp.load(":/img/page/facebox-alarm-aisle2.png");
                break;
            }
        }
        pLabel->setStyleSheet("border: 0px solid green;");
        pLabel->setPixmap(QPixmap::fromImage(qTmp));
    }
}

void DoubleChannelWidget::ClearPic(BottomPicLabel *pLabel)
{
    QImage qTmp;
    if(qTmp.load(":/img/page/facebox.png")){
        pLabel->setPixmap(QPixmap::fromImage(qTmp));
    }
}

void DoubleChannelWidget::on_toolButton_next_clicked()
{
    GetNextBatchData();
    ShowBottomPic();
}

void DoubleChannelWidget::on_toolButton_prev_clicked()
{
    GetPrevBatchData();
    ShowBottomPic();
}

bool DoubleChannelWidget::SaveData(const QByteArray &data, const TransportInfo *pInfo)
{
    QDateTime time = QDateTime::currentDateTime();
    QString qs_path = QCoreApplication::applicationDirPath();
    qs_path += "/saveData";
    QDir dir(qs_path);
    if(dir.count() >= MAXFILENUM){//本地最多存储数据
        //删除最先创建的一批数据
        dir.setFilter(QDir::Files | QDir::NoSymLinks);
        dir.setSorting(QDir::Time | QDir::Reversed);
        const QFileInfoList list = dir.entryInfoList();
        QFileInfoList::const_iterator itera = list.begin();

        for(int i = 0;(itera != list.end() && i < SHOWFILENUM);++itera,i++){
            dir.remove(itera->fileName());
        }
    }

    QString strCurTime = time.toString("yyyymmdd-hhmmsszzz");
    QString strHandle;
    strHandle.sprintf("%d",pInfo->header()->handle());
    QString strFileName = qs_path + "/" + strCurTime + "_" + pInfo->idcardInfo()->code()->c_str()
            + "_" + strHandle;
    QFile file(strFileName);
    if(file.open(QIODevice::WriteOnly)){
        file.write(data);
        file.close();
        return true;
    }
    return false;
}

void DoubleChannelWidget::GetPrevBatchData()
{
    if(m_nBatch > 1){
        m_vector_data.clear();
        QString qs_path = QCoreApplication::applicationDirPath();
        qs_path += "/saveData";
        QDir dir(qs_path);
        m_nBatch--;
        dir.setFilter(QDir::Files | QDir::NoSymLinks);
        dir.setSorting(QDir::Time);
        const QFileInfoList list = dir.entryInfoList();
        QFileInfoList::const_iterator itera = list.begin();
        int nEnd = (m_nBatch - 1) * SHOWFILENUM > 0 ? (m_nBatch - 1) * SHOWFILENUM : 0;
        itera += nEnd;
        for(int i=0;(itera != list.end()) && (i < SHOWFILENUM);++itera,i++){
            QString filename = qs_path + "/" + itera->fileName();
            QFile file(filename);
            if(file.open(QIODevice::ReadOnly)){
                m_vector_data.push_back(file.readAll());
                file.close();
            }
        }
    }
}

void DoubleChannelWidget::GetNextBatchData()
{
    if(m_nBatch * SHOWFILENUM < MAXFILENUM){
        QString qs_path = QCoreApplication::applicationDirPath();
        qs_path += "/saveData";
        QDir dir(qs_path);
        dir.setFilter(QDir::Files | QDir::NoSymLinks);
        dir.setSorting(QDir::Time);
        const QFileInfoList list = dir.entryInfoList();
        QFileInfoList::const_iterator itera = list.begin();
        if(m_nBatch * SHOWFILENUM >= dir.count()){
            return;//没有下一页了.
        }
        m_vector_data.clear();
        int nEnd = m_nBatch * SHOWFILENUM;
        m_nBatch++;
        itera += nEnd;
        for(int i=0;(itera != list.end()) && (i < SHOWFILENUM);++itera,i++){
            QString filename = qs_path + "/" + itera->fileName();
            QFile file(filename);
            if(file.open(QIODevice::ReadOnly)){
                m_vector_data.push_back(file.readAll());
                file.close();
            }
        }
    }
}

void DoubleChannelWidget::GetNewBatchData()
{
    m_nBatch = 1;
    QString qs_path = QCoreApplication::applicationDirPath();
    qs_path += "/saveData";
    QDir dir(qs_path);

    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setSorting(QDir::Time);
    const QFileInfoList list = dir.entryInfoList();
    QFileInfoList::const_iterator itera = list.begin();

    for(int i=0;(itera != list.end()) && (i < SHOWFILENUM);++itera,i++){
        QString filename = qs_path + "/" + itera->fileName();
        QFile file(filename);
        if(file.open(QIODevice::ReadOnly)){
            m_vector_data.push_back(file.readAll());
            file.close();
        }
    }
}

void DoubleChannelWidget::on_toolButton_search_clicked()
{
    KeyDialog* pKeyDialog = new KeyDialog(this);
    pKeyDialog->setAttribute(Qt::WA_TranslucentBackground);//背景透明
    pKeyDialog->setModal(true);//modal
    ui->stackedWidget->setCurrentIndex(2);//背景
    connect(pKeyDialog,SIGNAL(man_ok()),this,SLOT(keyboardOnOk()));
    connect(pKeyDialog,SIGNAL(man_destory()),this,SLOT(keyboardDestoryed()));
    pKeyDialog->show();
}

void DoubleChannelWidget::on_toolButton_search_2_clicked()
{
    KeyDialog* pKeyDialog = new KeyDialog(this);
    pKeyDialog->setAttribute(Qt::WA_TranslucentBackground);
    pKeyDialog->setModal(true);
    ui->stackedWidget->setCurrentIndex(2);
    connect(pKeyDialog,SIGNAL(man_ok()),this,SLOT(keyboardOnOk()));
    connect(pKeyDialog,SIGNAL(man_destory()),this,SLOT(keyboardDestoryed()));
    pKeyDialog->show();
}

void DoubleChannelWidget::keyboardDestoryed()
{
    switch(ui->comboBox_chanel->currentIndex()){
    case 0:
    case 1:
        ui->stackedWidget->setCurrentIndex(0);
        break;
    case 2:
        ui->stackedWidget->setCurrentIndex(1);
        break;
    }
}

void DoubleChannelWidget::keyboardOnOk()
{
    //查询
    ui->stackedWidget->setCurrentIndex(3);
    ui->label_gif->setMovie(m_pMovie);
    m_pMovie->start();
}

void DoubleChannelWidget::ShowAcrossNum(const TransportInfo *info,int index)
{
    switch(index){
        case 0:{//通道1
            if(info->header()->handle() == GATEONE){
                m_across_num_chanel1++;
                ui->label_acrossnum_3->setText(QString::number(m_across_num_chanel1));
            }
        }
        break;
        case 1:{
            if(info->header()->handle() == GATETWO){
                m_across_num_chanel2++;
                ui->label_acrossnum_3->setText(QString::number(m_across_num_chanel2));
            }
        }
        break;
        case 2://双通道
        if(info->header()->handle() == GATEONE){//通道1
            m_across_num_chanel1++;
            ui->label_acrossnum->setText(QString::number(m_across_num_chanel1));
        }else if(info->header()->handle() == GATETWO){//通道2
            m_across_num_chanel2++;
            ui->label_acrossnum_2->setText(QString::number(m_across_num_chanel2));
        }
        break;
    }
}

void DoubleChannelWidget::ShowAcrossWarnNum(const TransportInfo *info, int index)
{
    switch(index){
        case 0:{//通道1
            if(info->header()->handle() == GATEONE){
                if(info->blackInfo()->blackResult() == bingo){
                    m_across_warnnum_chanel1++;
                    ui->label_warnnum_3->setText(QString::number(m_across_warnnum_chanel1));
                }
            }
        }
        break;
        case 1:{
            if(info->header()->handle() == GATETWO){
                if(info->blackInfo()->blackResult() == bingo){
                    m_across_warnnum_chanel2++;
                    ui->label_warnnum_3->setText(QString::number(m_across_warnnum_chanel2));
                }
            }
        }
        break;
        case 2://双通道
        if(info->header()->handle() == GATEONE){//通道1
            if(info->blackInfo()->blackResult() == bingo){
                m_across_warnnum_chanel1++;
                ui->label_warnnum->setText(QString::number(m_across_warnnum_chanel1));
            }
        }else if(info->header()->handle() == GATETWO){//通道2
            if(info->blackInfo()->blackResult() == bingo){
                m_across_warnnum_chanel2++;
                ui->label_warnnum_2->setText(QString::number(m_across_warnnum_chanel2));
            }
        }
        break;
    }
}

void DoubleChannelWidget::write_acrossnum_to_file()
{

}

void DoubleChannelWidget::show_warndialog(int index,const TransportInfo *info)
{
    if(m_warndialog == NULL){
        m_warndialog = new WarnDialog(index,info,this);
        m_warndialog->setAttribute(Qt::WA_TranslucentBackground);//背景透明
        m_warndialog->setModal(true);
        m_warndialog->show();
    }else{
        m_warndialog->set_transport_info(info);
    }
}
