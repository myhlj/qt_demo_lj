#include "nocarddialog.h"
#include "ui_nocarddialog.h"
#include "options.h"
#include "common_data.h"
#include <QTimer>
#include <QDateTime>
#include "IMainController.h"

NoCardDialog::NoCardDialog(IMainController *controller,
                           const IDCardInfo& info,
                           int status,
                           const string errordes,
                           QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::NoCardDialog)
{
    m_controller = controller;
    m_cardinfo = info;
    m_status = status;
    m_errordes = errordes;
    ui->setupUi(this);
    init();
}

NoCardDialog::~NoCardDialog()
{
    delete ui;
}

void NoCardDialog::init()
{
    //初始化commbox
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
    ui->comboBox_chanel->setDisabled(true);
    ui->toolButton_exit->setDisabled(true);
    ui->toolButton_opengate->setDisabled(true);
    ui->toolButton_opengate_2->setDisabled(true);
    ui->toolButton_restart->setDisabled(true);
    ui->toolButton_shutdown->setDisabled(true);
    ui->toolButton_switch->setDisabled(true);

    switch(nCurrentChannelIndex){
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

    //timer
    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(recive_showtime()));
    timer->start(1000);
    //显示提示信息
    show_content();
    //显示身份证信息
    show_cardtextinfo();
    //显示身份证照片
    show_cardpic();
}

void NoCardDialog::on_pushButton_nocard_verifyno_clicked()
{
    if(m_status != STATUSSUCCED){
        return;
    }else{
        //发送到核验端检测
        int nCurrentChannelIndex = options::get_instance()->GetCurrentChannelIndex();
        switch(nCurrentChannelIndex){
        case GATEONE://通道一
            m_controller->SendCmd(GATEONE,LBTDMessage::MessType_HANDLEVERIFY,&m_cardinfo);
            break;
        case GATETWO://通道二
            m_controller->SendCmd(GATETWO,LBTDMessage::MessType_HANDLEVERIFY,&m_cardinfo);
            break;
        case GATEBOTH://双通道
            m_controller->SendCmd(GATEONE,LBTDMessage::MessType_HANDLEVERIFY,&m_cardinfo);
            break;
        }
        destroy();
        emit(nocarddialog_destory());
    }
}


void NoCardDialog::on_pushButton_nocard_deal_clicked()
{
     destroy();
     emit(nocarddialog_destory());
}

void NoCardDialog::recive_showtime()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss"); //设置显示格式
    ui->label_curtime->setText(strTime);
}

void NoCardDialog::show_cardtextinfo()
{
    ui->label_nocard_cardno->setText(m_cardinfo.textInfo.code);
    ui->label_nocard_address->setText(m_cardinfo.textInfo.address);
    ui->label_nocard_birthday->setText(m_cardinfo.textInfo.birthday);
    ui->label_nocard_name->setText(m_cardinfo.textInfo.name);
    ui->label_nocard_department->setText(m_cardinfo.textInfo.agency);
    ui->label_nocard_nation->setText(m_cardinfo.textInfo.folk);
    ui->label_nocard_sex->setText(m_cardinfo.textInfo.gender);
}

void NoCardDialog::show_content()
{
    if(m_status != STATUSSUCCED){
        ui->label_nocard_content->setStyleSheet("font-family:\"微软雅黑\";color: red;font-size: 24px;");
        ui->label_nocard_content->setText(m_errordes.c_str());
    }
}

void NoCardDialog::show_cardpic()
{
    QImage qTmp;
    bool bRet = qTmp.loadFromData(m_cardinfo.photo,m_cardinfo.photoLength);
    if(bRet){
        qTmp = qTmp.scaled(ui->label_nocard_pic1->width(),
                               ui->label_nocard_pic1->height(), Qt::KeepAspectRatio);
        ui->label_nocard_pic1->setPixmap(QPixmap::fromImage(qTmp.mirrored(false,false)));
    }
}
