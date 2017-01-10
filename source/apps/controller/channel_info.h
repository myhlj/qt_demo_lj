#ifndef CHANNEL_INFO_H
#define CHANNEL_INFO_H
//通道信息
struct ChannelInfo{
    ChannelInfo():strchannelIP("")
        ,bchannelVerifyMode(true)
        ,bchannelGateState(true)
        //,nPassCont(0)
        ,nExposionLevel(0){
    }
    std::string     strchannelIP;
    bool            bchannelVerifyMode;// true: faceMode     false : CardMode
    bool            bchannelGateState;// true: OpenMode(常开)    false: CloseMode(常关)
    int             nExposionLevel;//曝光值：
};

#endif // CHANNEL_INFO_H
