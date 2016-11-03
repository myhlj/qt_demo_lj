#include "keydialog.h"
#include "ui_keydialog.h"

KeyDialog::KeyDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),//去掉标题栏
    ui(new Ui::KeyDialog)
{
    ui->setupUi(this);
}

KeyDialog::~KeyDialog()
{
    delete ui;
}
