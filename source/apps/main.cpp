#include "doublechannelwidget.h"
#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QLabel>
#include <QPixmap>
#include "ViewFactory.h"
#include "main_controller.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString qss;
    QFile qssFile(":/qss/css.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        a.setStyleSheet(qss);
        qssFile.close();
    }

    QTranslator trans;
    bool success = trans.load(":/i18n/zh-CN.qm");
    if(success)
    {
        a.installTranslator(&trans);
    }

    ViewFactory fct;
    MainController ctl(&fct);
    ctl.Execute();

    return a.exec();
}
