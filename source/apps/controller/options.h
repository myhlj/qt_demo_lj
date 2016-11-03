/*
 * 配置文件类，读写写入配置文件
*/
#ifndef OPTIONS_H
#define OPTIONS_H
#include <QSettings>
#include <string.h>
#include <vector>
#include "channel_info.h"

class options
{
private:
    options();
public:
    static options* get_instance();
    ~options();
    //通道数目
    int GetChannelNumber()const{
        return m_nChannelNumber;
    }
    void SetChannelNumber(int number);
    //是否上传数据到别的平台
    bool GetDataTransFlag()const{
        return m_bDataTransFlag;
    }
    void SetDataTransFlag(bool bflag);
    //ip
    std::string GetDataTransIP()const{
        return m_strDataTransIP;
    }
    void SetDataTransIP(const std::string& sIp);
    //port
    void SetDataTransPort(int nport);
    int GetDataTransPort()const{
        return m_nDataTransPort;
    }
    //获取通道信息
    bool GetChannelInfo(int index,ChannelInfo& info);
    //当前通道配置(当前管理屏对应哪个通道)1--通道1 2--通道2 3--双通道(既显示通道一,又显示通道二)
    int GetCurrentChannelIndex()const{
        return m_nCurrentChannelIndex;
    }
    void SetCurrentChannelIndex(int nChannelIndex);
private:
    void ReadConfigIni();
private:
    int                         m_nChannelNumber;//通道数目
    std::vector<ChannelInfo>    m_vector_info;//通道信息
    QSettings*                  m_p_qsetting;//配置文件
    //数据上传SOCKET
    bool                        m_bDataTransFlag;//是否上传数据到别的平台
    std::string                 m_strDataTransIP;
    int                         m_nDataTransPort;
    int                         m_nCurrentChannelIndex;//当前通道配置(当前管理屏对应哪个通道)1--通道1 2--通道2 3--双通道(既显示通道一,又显示通道二)
};

#endif // options_H
