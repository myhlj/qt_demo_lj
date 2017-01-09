#include "ViewFactory.h"
#include "main_view.h"
#include "doublechannelwidget.h"

ViewFactory::ViewFactory()
{

}


ViewFactory::~ViewFactory()
{

}

IMainView* ViewFactory::CreateMainView()
{
    return new DoubleChannelWidget();
//    return new MainView();
}
