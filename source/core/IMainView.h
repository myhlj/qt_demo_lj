#ifndef IMAINVIEW_H
#define IMAINVIEW_H

#include <string>

#include "IView.h"
#include "ViewModel.h"
#include "data_generated.h"
using namespace MyTransportInfo;


class IMainController;

using namespace std;

class IMainView : public IView
{
public:
    virtual void SetController(IMainController *controller) = 0;
    virtual void ShowAcrossInfo(const QByteArray& data) = 0;
};

#endif
