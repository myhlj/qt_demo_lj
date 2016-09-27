#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include <QObject>
#include <QString>

#include "IMainController.h"
#include "ViewModel.h"

class IViewFactory;
class IMainView;

class MainController : public QObject, public IMainController
{
    Q_OBJECT

public:
    MainController(IViewFactory *factory);
	~MainController();

public:
    // IMainController interface
    int Execute();

public:
    // IMainController interface


public slots:


private:


private:
    IViewFactory *mViewFactory;
    IMainView *mMainView;

};

#endif
