#ifndef __THIDERRORDEF_H_INCLUDE__
#define __THIDERRORDEF_H_INCLUDE__

#ifdef __cplusplus
extern "C"
{
#endif

#define		THID_ERR_NONE								0		//没有错误
#define		THID_ERR_NODOG								-1		//没有找到加密狗
#define		THID_ERR_DOGERROR							-2		//打开加密狗出错
#define		THID_ERR_READDOG							-3		//读取加密狗出错
#define		THID_ERR_INVALIDDOG							-4		//不是合法的加密狗
#define		THID_ERR_DOGUSERERROR						-5		//读取加密狗用户出错  
#define		THID_ERR_INVALIDUSER						-6		//不是合法的加密狗用户
#define		THID_ERR_MOUDLENOAUTHORITY					-7		//该模块没有授权
#define     THID_ERR_INVALIDMOUDLE						-8		//模块被损坏或不存在
#define     THID_ERR_DATABASEFULL						-9		//特征库已满，无法再入库
#define		THID_ERR_DOGTIMEOUT							-10		//授权已过期
#define		THID_ERR_EXCEEDMAXCHANNELALLOWED			-11		//超出最大允许通道数目

#define     THID_ERR_INVALIDCALL						-99		//非法调用，输入的参数不对
#define     THID_ERR_EXCEPTION							-100		//异常

#define		THID_ERR_GENERIC							1		//一般错误，没有专门的意思
#define		THID_ERR_MEMORYALLOC						2		//内存分配错误
#define		THID_ERR_DATACRC							3		//数据文件CRC校验错误
#define		THID_ERR_GETMODULEPATH						4		//无法得到dll所在路径
#define		THID_ERR_FILEIO								5		//文件I/O错误
#define		THID_ERR_MODENOTMATCH						6		//调用模式与初始化模式不匹配
#define		THID_ERR_INVALIDIMAGE						7		// 不是正确的图像
#define		THID_ERR_SDKNOTINIT							8		// SDK没有初始化
#define     THID_ERR_CANCELENROLL		                9		//取消本次捕获
#define		THID_ERR_USERIDNOTEXIST						10		// 该模板图像ID不存在
#define		THID_ERR_NOTIMPLEMENTATION					11		// 没有实现

#define 	THID_ERR_VERSION							24		// 版本不对
#define		THID_ERR_NOFACE								25		// 没有检测到人脸

#define		THID_ERR_WSASTARTUP							100		//网络启动错误
#define		THID_ERR_IPADDRESS							101		//IP地址错误
#define		THID_ERR_INVALIDSOCKET						102		//invalid socket
#define		THID_ERR_IOCTLSOCKET						103			// Socket控制错误
#define		THID_ERR_CONNECT							104				// socket连接错误
#define		THID_ERR_SELECT								105				// select函数出错
#define		THID_ERR_NETTIMEOUT							106			// 连接超时
#define		THID_ERR_SEND								107					// 发送错误
#define		THID_ERR_RECEIVE							108				// 接收错误
#define		THID_ERR_REMOTECLOSESOCKET					109		// 远程关闭了socket
#define		THID_ERR_UPDATEFIRMWARE						110			// 升级固件错误
#define		THID_ERR_NOCONNECT							111	// 没有建立网络连接

#define		THID_ERR_OPENSERIAL							200	// 打开串口错误
#define		THID_ERR_SETUPSERIAL						201	// 串口设置错误
#define		THID_ERR_WRITESERIAL						202	// 向串口发送数据错误
#define		THID_ERR_READSERIAL							203	// 从串口读数据错误

#define		THID_ERR_NOTINITVIDEO						300	// 没有待解码的视频文件
#define		THID_ERR_INITCODEC							301	// initialize codec error
#define		THID_ERR_CODEC								302	// codec error

#ifdef __cplusplus
}
#endif

#ifndef WIN32
	#ifndef __stdcall
		#define __stdcall
	#endif
	#ifndef NULL
		#define NULL 0
	#endif
#endif

#endif	//	__THIDERRORDEF_H_INCLUDE__
