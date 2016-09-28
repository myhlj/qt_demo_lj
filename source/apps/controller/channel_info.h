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
    bool            bchannelGateState;// true: ColseMode    false: OpenMode
    int             nExposionLevel;//曝光值：
    //int             nPassCount;//该通道通过人数
};

#endif // CHANNEL_INFO_H
