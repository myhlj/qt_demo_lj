#include "warndialog.h"
#include "ui_warndialog.h"
#include "options.h"
#include "common_data.h"
#include <QTimer>
#include <QDateTime>
#include "IMainController.h"
using namespace std;

#define BLACK_WARN_TEXT "黑名单异常"
#define TICKET_WARN_TEXT "票务异常"
#define NOTMATCH_WARN_TEXT "人员核验不匹配异常"

WarnDialog::WarnDialog(int index,
                       const TransportInfo *info,
                       const QByteArray& data,
                       IMainController *controller,
                       QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::WarnDialog)
{
    m_index = index;
    m_info = info;
    m_list_info.push_front(data);
    this->controller = controller;
    ui->setupUi(this);
    init();
}

WarnDialog::~WarnDialog()
{
    delete ui;
}

void WarnDialog::init()
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
    //显示信息
    show_content();
    //timer
    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(recive_showtime()));
    timer->start(1000);
}

void WarnDialog::recive_showtime()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss"); //设置显示格式
    ui->label_curtime->setText(strTime);
}

void WarnDialog::set_transport_info(const TransportInfo *info,const QByteArray& data)
{
    m_info = info;
    m_list_info.push_front(data);
    //显示信息
    show_content();
}

void WarnDialog::show_cardinfo()
{
    ui->label_warn_name->setText(m_info->idcardInfo()->name() == NULL
                                 ? "" : m_info->idcardInfo()->name()->c_str());
    ui->label_warn_address->setText(m_info->idcardInfo()->address() == NULL
                                    ? "" : m_info->idcardInfo()->address()->c_str());
    ui->label_warn_birthday->setText(m_info->idcardInfo()->birthday() == NULL
                                     ? "" : m_info->idcardInfo()->birthday()->c_str());
    ui->label_warn_cardno->setText(m_info->idcardInfo()->code() == NULL
                                   ? "" : m_info->idcardInfo()->code()->c_str());
    ui->label_warn_department->setText(m_info->idcardInfo()->agency() == NULL
                                       ? "" : m_info->idcardInfo()->agency()->c_str());
    ui->label_warn_sex->setText(m_info->idcardInfo()->gender() == NULL
                                ? "" : m_info->idcardInfo()->gender()->c_str());
    ui->label_warn_nation->setText(m_info->idcardInfo()->folk() == NULL
                                   ? "" : m_info->idcardInfo()->folk()->c_str());
    QString date_start = m_info->idcardInfo()->expireStart() == NULL
            ? "" : m_info->idcardInfo()->expireStart()->c_str();
    QString date_end = m_info->idcardInfo()->expireEnd() == NULL
            ? "" : m_info->idcardInfo()->expireEnd()->c_str();
    ui->label_warn_date->setText(date_start + "-" + date_end);
}

void WarnDialog::show_content()
{
    if(m_info->blackInfo()->blackResult() == bingo){//最先判断黑名单
        hide_ticketinfo();//隐藏票务
        ui->pushButton_warn_verifyno->hide();//隐藏认证不同
        ui->pushButton_warn_deal->show();
        ui->pushButton_warn_opengate->hide();
        ui->label_warn_content->setText(BLACK_WARN_TEXT);
        show_label_pic();
        show_switch_bg(":/img/warndialog/bg/bg1.png");
        ui->label_warn_pic1->setStyleSheet("border: 3px solid red");
        ui->label_warn_pic2->setStyleSheet("border: 3px solid red");
        ui->label_warn_pic3->setStyleSheet("border: 3px solid red");
    }else if(m_info->ticketInfo()->ticketResult() == notMatch){//票务
        show_ticketinfo();//显示票务
        ui->pushButton_warn_verifyno->hide();//隐藏认证不同
        ui->pushButton_warn_deal->show();
        ui->pushButton_warn_opengate->hide();
        ui->label_warn_content->setText(TICKET_WARN_TEXT);
        show_label_pic();
        show_switch_bg(":/img/warndialog/bg/bg3.png");
        ui->label_warn_pic1->setStyleSheet("border: 3px solid yellow");
        ui->label_warn_pic2->setStyleSheet("border: 3px solid yellow");
        ui->label_warn_pic3->setStyleSheet("border: 3px solid yellow");
    }else if(m_info->verifyResult() == notMatch){
        hide_ticketinfo();//隐藏票务
        ui->pushButton_warn_verifyno->show();//显示人证不同
        ui->pushButton_warn_deal->hide();
        ui->pushButton_warn_opengate->show();
        ui->label_warn_content->setText(NOTMATCH_WARN_TEXT);
        show_label_pic();
        show_switch_bg(":/img/warndialog/bg/bg2.png");
        ui->label_warn_pic1->setStyleSheet("border: 3px solid #2aa1d3");
        ui->label_warn_pic2->setStyleSheet("border: 3px solid #2aa1d3");
        ui->label_warn_pic3->setStyleSheet("border: 3px solid #2aa1d3");
    }
    show_cardinfo();
    show_gate();
}

void WarnDialog::show_gate()
{
    switch(m_info->header()->handle()){
    case GATEONE:
        ui->label_warn_gate->setStyleSheet("border-image: url(:/img/warndialog/warn_gate1.png);");
        break;
    case GATETWO:
        ui->label_warn_gate->setStyleSheet("border-image: url(:/img/warndialog/warn_gate2.png);");
        break;
    }
}

void WarnDialog::show_ticketinfo()
{
    ui->label_warn_ticket_start->setText(m_info->ticketInfo()->goStation() == NULL
                                         ? "" : m_info->ticketInfo()->goStation()->c_str());
    ui->label_warn_ticket_start->show();
    ui->label_warn_ticket_end->setText(m_info->ticketInfo()->arriveStation() == NULL
                                       ? "" : m_info->ticketInfo()->arriveStation()->c_str());
    ui->label_warn_ticket_end->show();
    ui->label_warn_ticket_num->setText(m_info->ticketInfo()->ticketNO() == NULL
                                       ? "" : m_info->ticketInfo()->ticketNO()->c_str());
    ui->label_warn_ticket_num->show();
    ui->label_warn_ticket_date->setText(m_info->ticketInfo()->goTime() == NULL
                                        ? "" : m_info->ticketInfo()->goTime()->c_str());
    ui->label_warn_ticket_date->show();
    ui->label_warn_ticket_people->setText(m_info->ticketInfo()->stationName() == NULL
                                          ? "" : m_info->ticketInfo()->stationName()->c_str());
    ui->label_warn_ticket_people->show();
    ui->label_warn_ticket_stationnum->setText(m_info->ticketInfo()->stationNO() == NULL
                                              ? "" : m_info->ticketInfo()->stationNO()->c_str());
    ui->label_warn_ticket_stationnum->show();

    ui->label_warn_static9->show();
    ui->label_warn_static10->show();
    ui->label_warn_static11->show();
    ui->label_warn_static12->show();
    ui->label_warn_static13->show();
}

void WarnDialog::hide_ticketinfo()
{
    ui->label_warn_ticket_start->hide();
    ui->label_warn_ticket_end->hide();
    ui->label_warn_ticket_num->hide();
    ui->label_warn_ticket_date->hide();
    ui->label_warn_ticket_people->hide();
    ui->label_warn_ticket_stationnum->hide();

    ui->label_warn_static9->hide();
    ui->label_warn_static10->hide();
    ui->label_warn_static11->hide();
    ui->label_warn_static12->hide();
    ui->label_warn_static13->hide();
}

void WarnDialog::show_label_pic()
{
    show_idcard_pic();
    show_face_pic();
    show_screen_pic();
}

void WarnDialog::show_idcard_pic()
{
    //身份证图片
    QImage qTmp;
    bool bRet = qTmp.loadFromData(m_info->idImage()->data(),m_info->idImageSize(),"bmp");
    if(bRet){
        qTmp = qTmp.scaled(ui->label_warn_pic1->width(),
                               ui->label_warn_pic1->height(), Qt::KeepAspectRatio);
        ui->label_warn_pic1->setPixmap(QPixmap::fromImage(qTmp.mirrored(false,false)));
    }else{

    }
}

void WarnDialog::show_face_pic()
{
    //人脸图
    QImage qTmp;
    bool bRet = qTmp.loadFromData(m_info->cropImage()->data(),m_info->cropImageSize(),"jpg");
    if(bRet){
        qTmp = qTmp.scaled(ui->label_warn_pic2->width(),
                               ui->label_warn_pic2->height(), Qt::KeepAspectRatio);
        ui->label_warn_pic2->setPixmap(QPixmap::fromImage(qTmp.mirrored(false,false)));
    }else{

    }
}

void WarnDialog::show_screen_pic()
{
    //场景图
    QImage qTmp;
    bool bRet = qTmp.loadFromData(m_info->srcImage()->data(),m_info->scrImageSize(),"jpg");
    if(bRet){
        qTmp = qTmp.scaled(ui->label_warn_pic3->width(),
                               ui->label_warn_pic3->height(), Qt::KeepAspectRatio);
        ui->label_warn_pic3->setPixmap(QPixmap::fromImage(qTmp.mirrored(false,false)));
    }else{

    }
}

void WarnDialog::show_switch_bg(const QString& path)
{
    QPalette palette;
    ui->widget_page_switch->setAutoFillBackground(true);
    QImage image;
    if(image.load(path))
    {
        image = image.scaled(ui->widget_page_switch->width(),
                             ui->widget_page_switch->height());
        palette.setBrush(QPalette::Window, QBrush(image));
        ui->widget_page_switch->setPalette(palette);
    }
}

void WarnDialog::on_pushButton_warn_opengate_clicked()
{
    //先pop当前的数据
    QByteArray current_data = m_list_info.front();
    m_list_info.pop_front();
    //显示上一条数据
    if(m_list_info.size() > 0){
        current_data = m_list_info.front();
        const TransportInfo* pInfo = GetTransportInfo(current_data.constData());
        if(pInfo == NULL){
            return;
        }
        m_info = pInfo;
        show_content();
        //发送开门消息
        this->controller->SendCmd(m_info->header()->handle(),
                                  LBTDMessage::MessType_OPENGATE);
    }else{
        const TransportInfo* pInfo = GetTransportInfo(current_data.constData());
        if(pInfo == NULL){
            return;
        }
        m_info = pInfo;
        //发送开门消息
        this->controller->SendCmd(m_info->header()->handle(),
                                  LBTDMessage::MessType_OPENGATE);
        emit(warndialog_destory());
        //销毁本窗口
        destroy();

    }
}

void WarnDialog::on_pushButton_warn_verifyno_clicked()
{
    //先pop当前的数据
    m_list_info.pop_front();
    //显示上一条数据
    if(m_list_info.size() > 0){
        QByteArray data = m_list_info.front();
        const TransportInfo* pInfo = GetTransportInfo(data.constData());
        if(pInfo == NULL){
            return;
        }
        m_info = pInfo;
        show_content();
    }else{
        //销毁本窗口
        destroy();
        emit(warndialog_destory());
    }
}

void WarnDialog::on_pushButton_warn_deal_clicked()
{
    //先pop当前的数据
    m_list_info.pop_front();
    //显示上一条数据
    if(m_list_info.size() > 0){
        QByteArray data = m_list_info.front();
        const TransportInfo* pInfo = GetTransportInfo(data.constData());
        if(pInfo == NULL){
            return;
        }
        m_info = pInfo;
        show_content();
    }else{
        //销毁本窗口
        destroy();
        emit(warndialog_destory());
    }
}
