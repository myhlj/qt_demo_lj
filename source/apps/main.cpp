#include "doublechannelwidget.h"
#include <QApplication>
#include "ViewFactory.h"
#include "main_controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ViewFactory fct;
    MainController ctl(&fct);
    ctl.Execute();

    return a.exec();
}
