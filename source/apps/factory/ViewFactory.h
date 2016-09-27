#ifndef VIEWFACTORY_H
#define VIEWFACTORY_H

#include "IViewFactory.h"

class ViewFactory : public IViewFactory
{
public:
    ViewFactory();
    ~ViewFactory();


private:

    // IViewFactory interface
public:
    IMainView* CreateMainView();

};

#endif
