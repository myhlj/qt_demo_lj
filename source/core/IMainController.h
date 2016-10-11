#ifndef IMAINCONTROLLER_H
#define IMAINCONTROLLER_H

#include <string>
#include "messagelbtd_generated.h"
using namespace std;

class IMainController
{
public:
    virtual int Execute() = 0;
    /*
     * 发送命令到闸机接口
     * nChannelNum-------通道号
     * type--------------消息类型
     * param-------------参数类型
    */
    virtual bool SendCmd(int nChannelNum, LBTDMessage::MessType type, int param) = 0;
public:

};

#endif
