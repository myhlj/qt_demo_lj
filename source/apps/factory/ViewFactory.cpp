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
    // TODO:根据配置返回不同通道界面
    return new DoubleChannelWidget();
//    return new MainView();
}
