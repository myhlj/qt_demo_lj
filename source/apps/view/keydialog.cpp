#include "keydialog.h"
#include "ui_keydialog.h"


KeyDialog::KeyDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),//去掉标题栏
    ui(new Ui::KeyDialog)
{
    ui->setupUi(this);
    ui->lineEdit_keyboard->setReadOnly(true);
    ui->lineEdit_keyboard->setMaxLength(18);
}

KeyDialog::~KeyDialog()
{
    delete ui;
}

void KeyDialog::on_pushButton_keyboard_1_clicked()
{
    QString sText = ui->lineEdit_keyboard->text();
    sText += ui->pushButton_keyboard_1->text();
    ui->lineEdit_keyboard->setText(sText);
}

void KeyDialog::on_pushButton_keyboard_2_clicked()
{
    QString sText = ui->lineEdit_keyboard->text();
    sText += ui->pushButton_keyboard_2->text();
    ui->lineEdit_keyboard->setText(sText);
}

void KeyDialog::on_pushButton_keyboard_3_clicked()
{
    QString sText = ui->lineEdit_keyboard->text();
    sText += ui->pushButton_keyboard_3->text();
    ui->lineEdit_keyboard->setText(sText);
}

void KeyDialog::on_pushButton_keyboard_4_clicked()
{
    QString sText = ui->lineEdit_keyboard->text();
    sText += ui->pushButton_keyboard_4->text();
    ui->lineEdit_keyboard->setText(sText);
}

void KeyDialog::on_pushButton_keyboard_8_clicked()
{
    QString sText = ui->lineEdit_keyboard->text();
    sText += ui->pushButton_keyboard_8->text();
    ui->lineEdit_keyboard->setText(sText);
}

void KeyDialog::on_pushButton_keyboard_7_clicked()
{
    QString sText = ui->lineEdit_keyboard->text();
    sText += ui->pushButton_keyboard_7->text();
    ui->lineEdit_keyboard->setText(sText);
}

void KeyDialog::on_pushButton_keyboard_6_clicked()
{
    QString sText = ui->lineEdit_keyboard->text();
    sText += ui->pushButton_keyboard_6->text();
    ui->lineEdit_keyboard->setText(sText);
}

void KeyDialog::on_pushButton_keyboard_5_clicked()
{
    QString sText = ui->lineEdit_keyboard->text();
    sText += ui->pushButton_keyboard_5->text();
    ui->lineEdit_keyboard->setText(sText);
}

void KeyDialog::on_pushButton_keyboard_9_clicked()
{
    QString sText = ui->lineEdit_keyboard->text();
    sText += ui->pushButton_keyboard_9->text();
    ui->lineEdit_keyboard->setText(sText);
}

void KeyDialog::on_pushButton_keyboard_10_clicked()
{
    QString sText = ui->lineEdit_keyboard->text();
    sText += ui->pushButton_keyboard_10->text();
    ui->lineEdit_keyboard->setText(sText);
}

void KeyDialog::on_pushButton_keyboard_x_clicked()
{
    QString sText = ui->lineEdit_keyboard->text();
    sText += ui->pushButton_keyboard_x->text();
    ui->lineEdit_keyboard->setText(sText);
}

void KeyDialog::on_pushButton_keyboard_resetting_clicked()
{
    ui->lineEdit_keyboard->clear();//置空
}

void KeyDialog::on_pushButton_keyboard_back_clicked()
{
    emit(man_destory());
    destroy();
}

void KeyDialog::on_pushButton_keyboard_ok_clicked()
{
    emit(man_ok());
    destroy();
}

bool KeyDialog::verify_idnumber(string a)
{
    if (a.length() != 18){
        return false;
    }
    int sum = (a[0] - '0') * 7 + (a[1] - '0') * 9 + (a[2] - '0') * 10
            + (a[3] - '0') * 5 + (a[4] - '0') * 8 + (a[5] - '0') * 4
            + (a[6] - '0') * 2 + (a[7] - '0') * 1 + (a[8] - '0') * 6
            + (a[9] - '0') * 3 + (a[10] - '0') * 7 + (a[11] - '0') * 9
            + (a[12] - '0') * 10 + (a[13] - '0') * 5 + (a[14] - '0') * 8
            + (a[15] - '0') * 4 + (a[16] - '0') * 2;
    int k = sum % 11;
    char lastNumber;
    if (k == 0){
        lastNumber = '1';
    }else if (k == 1){
        lastNumber = '0';
    }else if (k == 2){
        lastNumber = 'X';
    }else{
        lastNumber = '0'+12-k;
    }
    if(a[17] == lastNumber){
        return true;
    }else{
        return false;
    }
}
