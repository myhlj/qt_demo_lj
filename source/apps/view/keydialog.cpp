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
    QString cardno = ui->lineEdit_keyboard->text();

    emit(man_ok(cardno));
    destroy();
}
