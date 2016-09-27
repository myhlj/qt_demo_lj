#ifndef DOUBLECHANNELWIDGET_H
#define DOUBLECHANNELWIDGET_H

#include <QWidget>
#include "IMainView.h"

namespace Ui {
class DoubleChannelWidget;
}

class DoubleChannelWidget : public QWidget, public IMainView
{
    Q_OBJECT

public:
    explicit DoubleChannelWidget(QWidget *parent = 0);
    ~DoubleChannelWidget();

    // IMainView interface
    void SetController(IMainController *controller);
    void Init();
    void ShowView();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::DoubleChannelWidget *ui;
    IMainController *controller;
};

#endif // DOUBLECHANNELWIDGET_H
