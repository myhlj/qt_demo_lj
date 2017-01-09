#ifndef KEYDIALOG_H
#define KEYDIALOG_H

#include <QDialog>

namespace Ui {
class KeyDialog;
}

class KeyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyDialog(QWidget *parent = 0);
    ~KeyDialog();

private slots:
    void on_pushButton_keyboard_1_clicked();

    void on_pushButton_keyboard_2_clicked();

    void on_pushButton_keyboard_3_clicked();

    void on_pushButton_keyboard_4_clicked();

    void on_pushButton_keyboard_8_clicked();

    void on_pushButton_keyboard_7_clicked();

    void on_pushButton_keyboard_6_clicked();

    void on_pushButton_keyboard_5_clicked();

    void on_pushButton_keyboard_9_clicked();

    void on_pushButton_keyboard_10_clicked();

    void on_pushButton_keyboard_x_clicked();

    void on_pushButton_keyboard_resetting_clicked();

    void on_pushButton_keyboard_back_clicked();

    void on_pushButton_keyboard_ok_clicked();

private:
    Ui::KeyDialog *ui;
signals:
    void man_destory();
    void man_ok();
};

#endif // KEYDIALOG_H
