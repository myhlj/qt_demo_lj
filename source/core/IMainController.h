#ifndef IMAINCONTROLLER_H
#define IMAINCONTROLLER_H

#include <string>
#include "common_data.h"
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
     * sParamR-----------参数
     * paramL------------参数
    */
    virtual void SendCmd(int nChannelNum, LBTDMessage::MessType type,IDCardInfo* info=NULL,int paramL=0,string sParamR="") = 0;
    /*
     * 查询常口库
    */
    virtual void request_cardinfo(string cardno,string url) = 0;
};

#endif
