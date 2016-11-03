#include "doublechannelwidget.h"
#include <QApplication>
#include <QFile>
#include <QLabel>
#include <QPixmap>
#include "ViewFactory.h"
#include "main_controller.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ViewFactory fct;
    MainController ctl(&fct);
    ctl.Execute();

    QString qss;
    QFile qssFile(":/qss/css.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        a.setStyleSheet(qss);
        qssFile.close();
    }

    return a.exec();
}
