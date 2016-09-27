#ifndef IMAINVIEW_H
#define IMAINVIEW_H

#include <string>

#include "IView.h"
#include "ViewModel.h"

class IMainController;

using namespace std;

class IMainView : public IView
{
public:
    virtual void SetController(IMainController *controller) = 0;

};

#endif
