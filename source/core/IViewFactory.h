#ifndef IVIEWFACTORY_H
#define IVIEWFACTORY_H

#include <string>

using namespace std;

class IMainView;

class IViewFactory
{
public:
    virtual IMainView* CreateMainView() = 0;
};

#endif
