#ifndef __THIDIMAGEHELPER_H_INCLUDE__
#define __THIDIMAGEHELPER_H_INCLUDE__

#ifndef WIN32
#define __stdcall
#else
#include<Windows.h>
#include<WinDef.h>
#endif

#include "THIDErrorDef.h"

#ifdef __cplusplus
extern "C"
{
#endif	//	__cplusplus

#ifndef __max
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#ifndef __min
#define __min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#ifndef _MAX_PATH
#define _MAX_PATH 1024
#endif

#ifndef __WIDTHBYTES__
#define WIDTHBYTES(bits) ((DWORD)(((bits)+31) & (~31)) / 8)
#endif

extern int InitFlag; // 畸变矫正初始化 全局标志

#define IMAGE_FORMAT_UNKNOWN -1 //add by jsa
#define IMAGE_FORMAT_BMP	  1
#define IMAGE_FORMAT_GIF	  2
#define IMAGE_FORMAT_JPG	  3
#define IMAGE_FORMAT_TIF	  6
#define IMAGE_FORMAT_JP2	  11

#ifndef _THIDNORMFACEGEOFORMAT
#define _THIDNORMFACEGEOFORMAT
typedef struct THIDNormFaceGeoFormat	// normalize face geometric format
{
	int nImgWidth;				// width of the normalize face
	float fHeightRatio;			// height to width ratio
	float fEyeYCoorRatio;		// Y coordinate of Eyes to width ratio
	float fFirstEyeXCoorRatio;	// X coordinate of first eye to width ratio
	float fSecondEyeXCoorRatio;	// X coordinate of second eye to width ratio

}THIDNormFaceGeoFormat;
#endif	//	_THIDNORMFACEGEOFORMAT

#define FACE_POSITION_NORMAL	0	// 人脸在原始图像中位置正常
#define FACE_POSITION_LEFT		1	// 人脸太靠近原始图像左边
#define FACE_POSITION_TOP		2	// 人脸太靠近原始图像上边
#define FACE_POSITION_RIGHT		3	// 人脸太靠近原始图像右边
#define FACE_POSITION_BOTTOM	4	// 人脸太靠近原始图像下边

typedef enum MirrorType
{
	Horizontal,			// 水平镜像
	Vertical,			// 垂直镜像
	Both				// 水平、垂直同时镜像
}MirrorType;

#ifndef _THIDEYEPOINT
#define _THIDEYEPOINT
typedef struct THIDEyePoint
{
        int xleft;			// 左眼在原始图像中的位置
        int yleft;
        int xright;			// 右眼在原始图像中的位置
        int yright;
        float confidence;		// 置信度, [50.0, 100.0]间的实数值
}THIDEyePoint;
#endif	//	_THIDEYEPOINT

#ifndef _THIDEYEPOINTF
#define _THIDEYEPOINTF
typedef struct THIDEyePointF	//描述眼睛信息
{
	float xleft;				// 左眼在原始图像中的x坐标
	float yleft;				// 左眼在原始图像中的y坐标
	float xright;				// 右眼在原始图像中的x坐标
	float yright;				// 右眼在原始图像中的y坐标
	float confidence;			// 眼睛定位的置信度, [50.0, 100.0]
}THIDEyePointF;
#endif	//	_THIDEYEPOINTF

#ifndef _THIDPOINT
#define _THIDPOINT
typedef struct THIDPoint
{
	int x;
	int y;
}THIDPoint;
#endif	//	_THIDPOINT

#ifndef _COLORREF_DEFINED
#define _COLORREF_DEFINED
typedef unsigned long COLORREF;
#endif // !_COLORREF_DEFINED

#ifndef RGB
#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L

#ifndef __GET_R_VALUE_MACRO__
#define __GET_R_VALUE_MACRO__
#define GetRValue(rgb)      ((unsigned char)(rgb))
#endif

#ifndef __GET_G_VALUE_MACRO__
#define __GET_G_VALUE_MACRO__
#define GetGValue(rgb)      ((unsigned char)(((unsigned short)(rgb)) >> 8))
#endif

#ifndef __GET_B_VALUE_MACRO__
#define __GET_B_VALUE_MACRO__
#define GetBValue(rgb)      ((unsigned char)((rgb)>>16))
#endif
#define RGB(r,g,b) ((COLORREF)(((unsigned char)(r)|((unsigned short)((unsigned char)(g))<<8))|(((unsigned long)(unsigned char)(b))<<16)))
#endif

#ifndef WIN32
#include <stdint.h>
#ifndef __DWORD_TYPE__
#define __DWORD_TYPE__
typedef unsigned int DWORD;
#endif

#ifndef __WORD_TYPE__
#define __WORD_TYPE__
typedef unsigned short WORD;
#endif

#ifndef __BYTE_TYPE__
#define __BYTE_TYPE__
typedef unsigned char BYTE;
#endif

#ifndef __STRUCT_TAG_RECT_TYPE__
#define __STRUCT_TAG_RECT_TYPE__
typedef struct tagRECT
{
        int left;
        int top;
        int right;
        int bottom;
} RECT;
#endif

#ifndef __STRUCT_TAG_BITMAPFILE_HEADER_TYPE__
#define __STRUCT_TAG_BITMAPFILE_HEADER_TYPE__
typedef struct tagBITMAPFILEHEADER 
{
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
} __attribute__ ((packed)) BITMAPFILEHEADER;
#endif

#ifndef __STRUCT_TAG_RGBQUAD_TYPE__
#define __STRUCT_TAG_RGBQUAD_TYPE__
typedef struct tagRGBQUAD {
	uint8_t rgbBlue;
	uint8_t rgbGreen;
	uint8_t rgbRed;
	uint8_t rgbReserved;
} RGBQUAD;
#endif

#ifndef __STRUCT_TAG_BITMAPINFOHEADER_TYPE__
#define __STRUCT_TAG_BITMAPINFOHEADER_TYPE__
typedef struct tagBITMAPINFOHEADER{
	uint32_t      biSize;
	int32_t       biWidth;
	int32_t       biHeight;
	uint16_t      biPlanes;
	uint16_t      biBitCount;
	uint32_t      biCompression;
	uint32_t      biSizeImage;
	int32_t       biXPelsPerMeter;
	int32_t       biYPelsPerMeter;
	uint32_t      biClrUsed;
	uint32_t      biClrImportant;
} BITMAPINFOHEADER;
#endif

#ifndef __STRUCT_TAG_BITMAPINFO_TYPE__
#define __STRUCT_TAG_BITMAPINFO_TYPE__
typedef struct tagBITMAPINFO {
	BITMAPINFOHEADER    bmiHeader;
	RGBQUAD             bmiColors[1];
} BITMAPINFO, *PBITMAPINFO;
#endif

#endif

/*********************************************************************************************************//*
 * @brief        :ImageHelper初始化
 * @input  param :mod 暂时未用
 * @output param :无
 * @retval       : 0成功，非0失败
 ************************************************************************************************************/
int __stdcall THIDFreeImageInit(int mod);

/*********************************************************************************************************//*
 * @brief        :ImageHelper 去初始化
 * @input  param :无
 * @output param :无
 * @retval       : 0成功，非0失败
 ************************************************************************************************************/
int __stdcall THIDFreeImageDeInit();

/*********************************************************************************************************//*
 * @brief        :THIDRawImageToJepgImage 将Raw 图像转换成jpeg格式的图像
 * @input  param :lpszPathName raw图像格式文件名 ； width, height ,pitch, bpp, 图像宽，高，pitch=channels*width ，位深
 *					red_mask, green_mask, blue_mask,topdown :暂时未用
 * @output param :SavedFileName 输出jpeg文件名
 * @retval       : 0成功，非0失败，(参见THIDErrorDef.h中的错误定义)
 ************************************************************************************************************/
int __stdcall THIDRawImageToJepgImage(const char * lpszPathName,
                                      int width,
                                      int height,
                                      int pitch,
                                      unsigned bpp,
                                      unsigned red_mask,
                                      unsigned green_mask,
                                      unsigned blue_mask,
                                      bool topdown,
                                      char *SavedFileName);

/*********************************************************************************************************//*
 * @brief        : THIDRawImageMemoryToJepgImage 从内存中Raw 数据保存成jpeg图像
 * @input  param :pRawData 图像裸数据 width图像宽 height 图像高 pitch=channels*width bpp 位深 red_mask,
 *                green_mask, blue_mask,topdown :暂时未用
 * @output param :SavedFileName 输出jpeg文件名
 * @retval       : 0成功，非0失败(参见THIDErrorDef.h中的错误定义)
 ************************************************************************************************************/
int __stdcall THIDRawImageMemoryToJepgImage(const unsigned char * pRawData,
                                            int width,
                                            int height,
                                            int pitch,
                                            unsigned bpp,
                                            unsigned red_mask,
                                            unsigned green_mask,
                                            unsigned blue_mask,
                                            bool topdown,
                                            char *SavedFileName);

/*********************************************************************************************************//*
 * @brief        : THIDGetJPEGImageParameters 获得jpeg图像的相关参数
 * @input  param : pSrcJPEGFile jpeg图片文件名(全路径)
 * @output param : width 宽 ,height 高, pitch= channels*width ,bpp 位深
 * @retval       : 0成功，非0失败(参见THIDErrorDef.h中的错误定义)
 ************************************************************************************************************/
int __stdcall THIDGetJPEGImageParameters(const char *pSrcJPEGFile,
                                         int *width,
                                         int *height,
                                         int *pitch,
                                         int *bpp);

/*********************************************************************************************************//*
 * @brief        : THIDJPEGImageToRaw 将jpeg图像转成Raw Data
 * @input  param : pSrcJPEGFile jpeg图片文件名(全路径)；pitch= channels*width ,bpp 位深
 * @output param : pDestData Raw数据
 * @retval       : 0成功，非0失败(参见THIDErrorDef.h中的错误定义)
 ************************************************************************************************************/
int __stdcall THIDJPEGImageToRaw(const char *pSrcJPEGFile,
                                 int pitch,
                                 int bpp,
                                 unsigned char *pDestData);

/****************************************************************************************************************//*
							jpeg 图像畸变矫正部分
*******************************************************************************************************************/

/*********************************************************************************************************//*
 * @brief        : THIDRadialDistortionCorrectionInit 畸变矫正初始化
 * @input  param : dSrcImgWidth 需要矫正的图片类型的宽，dSrcImgHeight需要矫正的图片类型的高
 * @output param : 无
 * @retval       : 0成功，非0失败(参见THIDErrorDef.h中的错误定义)
 ************************************************************************************************************/
int __stdcall THIDRadialDistortionCorrectionInit(int dSrcImgWidth,
                                                 int dSrcImgHeight);

/*********************************************************************************************************//*
 * @brief        : THIDRadialDistortionCorrectionDeInit 畸变矫反初始化
 * @input  param : 无
 * @output param : 无
 * @retval       : 0成功，非0失败(参见THIDErrorDef.h中的错误定义)
 ************************************************************************************************************/
int __stdcall THIDRadialDistortionCorrectionDeInit();

/*********************************************************************************************************//*
 * @brief        :THIDGetCorrectionImageSize 获得畸变矫正图像大小
 * @input  param :srcWidth 源文件的宽；srcHeight 源文件的高
 * @output param :dstWidth 矫正后文件宽；dstHeight 矫正后文件高
 * @retval       : 0成功，非0失败
 ************************************************************************************************************/
int __stdcall THIDGetCorrectionImageSize(int srcWidth,
                                         int srcHeight,
                                         int *dstWidth,
                                         int *dstHeight);

/*********************************************************************************************************//*
 * @brief        :THIDRadialDistortionCorrection 畸变矫正图像
 * @input  param :pbySrcImage  输入图像数据；dSrcImgWidth输入图像的矫正前的宽；dSrcImgHeight 输入图像的矫
 *                正前的高；lfRadius径向畸变半径；dImgChannel 图像通道数
 * @output param :plfDstImage 输出图像
 * @retval       : 0成功，非0失败
 ************************************************************************************************************/
int __stdcall THIDRadialDistortionCorrection(const unsigned char *pbySrcImage,// 输入图像
                                             int dSrcImgWidth,// 输入图像的宽
                                             int dSrcImgHeight,// 输入图像的高
                                             float lfRadius,// 径向畸变半径（lfRadius >= min(dSrcImgWidth, dSrcImgHeight)），半径越大，畸变程度越小，无理论上限
                                             unsigned char *plfDstImage,//  输出图像，长宽由THIDGetCorrectionImageSize得到，通道数目与输入图像相同（即可以处理灰度和彩色图像）
                                             int dImgChannel);// 图像通道数

/************************************************************************************************************
					CxImage version THIDImageHelper function use FreeImage achieve
 ************************************************************************************************************/
 
/*
 *	THIDDibImageToGrayImage: 将Dib格式的图像转换成raw格式的灰度图像
 *	Parameters:
 *		pbyInDibImage[in]: dib格式的图像
 *		pbyOutGrayImage[out]: raw格式的灰度图像，调用程序需要分配内存
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDDibImageToGrayImage(const unsigned char *pbyInDibImage,
                                      unsigned char *pbyOutGrayImage);

/*
 *	THIDDibToGray: convert dib image to raw format gray image
 *	Parameters:
 *		pBitsInfo[in]: Pointer to a BITMAPINFO structure that contains information about the DIB.
 *		pBits[in]: Pointer to the DIB bits, which are stored as an array of bytes.
 *		pbyOutGrayImage[out]: raw format gray image, caller must allocate memory.
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDDibToGray(const BITMAPINFO *pBitsInfo,
                            const unsigned char *pBits,
                            unsigned char *pbyOutGrayImage);

/*
 *	THIDGetDIBImageFromFile: 输入图像文件，解码得到dib格式的内存图像
 *	Parameters:
 *		strImagePathName[in]: 图像文件名
 *		ppbyOutDib[out]: dib格式的内存图像。函数内部分配内存，应用程序无需分配内存
 *				应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		nDibSize[out]: dib格式的内存图像的大小
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDGetDIBImageFromFile(const char *strImagePathName,
                                      unsigned char **ppbyOutDib,
                                      int *nDibSize);

int __stdcall THIDGetDIBImageFromFileW(const wchar_t *strImagePathName,
                                       unsigned char **ppbyOutDib,
                                       int *nDibSize);

/*
 *	THIDGetGrayImageFromFile: 输入图像文件，解码得到raw格式的灰度图像
 *	Parameters:
 *		strImagePathName[in]: 图像文件名
 *		ppbyOutGrayImage[out]: raw格式的灰度图像。函数内部分配内存，应用程序无需分配内存
 *	    		应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		nImgWidth[out]: 图像的宽度
 *		nImgHeight[out]: 图像的高度
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDGetGrayImageFromFile(const char *strImagePathName,
                                       unsigned char **ppbyOutGrayImage,
                                       int *nImgWidth, int *nImgHeight);

int __stdcall THIDGetGrayImageFromFileW(const wchar_t *strImagePathName,
                                        unsigned char **ppbyOutGrayImage,
                                        int *nImgWidth,
                                        int *nImgHeight);

/*
 *	THIDGetDIBImageFromBuffer: 从内存图像中解码得到dib格式的内存图像
 *	Parameters:
 *		pbyImageBuffer[in]: 内存图像数据
 *		nImageSize[in]: 内存图像占用的字节数
 *		nImageFormat[in]: 内存图像的格式
 *		ppbyOutDib[out]: 解码得到的dib格式的内存图像。函数内部分配内存，应用程序无需分配内存
 *				应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		nDibSize[out]: dib格式的内存图像的大小
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDGetDIBImageFromBuffer(const char *pbyImageBuffer,
                                        int nImageSize,
                                        int nImageFormat,
                                        unsigned char **ppbyOutDib,
                                        int *nDibSize);



/*
 *	THIDFreeMemory: 释放内存
 *	Parameters:
 *		pbyBuffer[in]: 传入调用THIDGetDIBImageFromFile、THIDGetGrayImageFromFile、
 *			THIDGetDIBImageFromBuffer、THIDGetGrayImageFromBuffer、THIDEncodeDIBToOtherFormat、
 *			THIDCropDibImage时得到的内存图像的指针
 */
void __stdcall THIDFreeMemory(unsigned char *pbyBuffer);

/*
 *	THIDGetGrayImageFromBuffer: 从内存图像中解码得到raw格式的灰度图像
 *	Parameters:
 *		pbyImageBuffer[in]: 内存图像数据
 *		nImageSize[in]: 内存图像占用的字节数
 *		nImageFormat[in]: 内存图像的格式
 *		ppbyOutGrayImage[out]: raw格式的灰度图像。函数内部分配内存，应用程序无需分配内存
 *				应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		nImgWidth[out]: 图像的宽度
 *		nImgHeight[out]: 图像的高度
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDGetGrayImageFromBuffer(const char *pbyImageBuffer,
                                         int nImageSize,
                                         int nImageFormat,
                                         unsigned char **ppbyOutGrayImage,
                                         int *nImgWidth,
                                         int *nImgHeight);

//THIDGetGrayImageFromBufferEx add by jsa @20160108

/*
 *	THIDGetGrayImageFromBufferEx: 从内存图像中解码得到raw格式的灰度图像
 *	Parameters:
 *		pbyImageBuffer[in]: 内存图像数据
 *		nImageSize[in]: 内存图像占用的字节数
 *		nImageFormat[in]: 内存图像的格式
 *		pbyGrayImage[out]: raw格式的灰度图像，需外部申请内存，大小为nSize，要求nSize>=nImgWidth*nImgHeight，若小于，返回内存错误
 *		nSize[in,out]:输入表示pbyGrayImage的大小，输出表示实际使用的大小即nImgWidth*nImgHeight
 *		nImgWidth[out]: 图像的宽度
 *		nImgHeight[out]: 图像的高度
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDGetGrayImageFromBufferEx(const char *pbyImageBuffer,
                                           int nImageSize,
                                           int nImageFormat,
                                           unsigned char *pbyGrayImage,
                                           int *nSize,
                                           int *nImgWidth,
                                           int *nImgHeight);

/*
 *	THIDEncodeDIBToOtherFormat: 将dib格式的内存图像编码成其他格式的图像
 *	Parameters:
 *		pbyInDib[in]: dib格式的内存图像
 *		nImageFormat[in]: 需要编码出的图像的格式
 *		ppbyOutBuffer[out]: 编码后的图像。函数内部分配内存，应用程序无需分配内存
 *				应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		nEncodeSize[out]: 编码后图像的大小
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDEncodeDIBToOtherFormat(const unsigned char *pbyInDib,
                                         int nImageFormat,
                                         unsigned char **ppbyOutBuffer,
                                         int *nEncodeSize);

/*
 *	THIDCropDibImage: 从dib格式的图像中切出指定大小的图像
 *	Parameters:
 *		pbyInDib[in]: dib格式的内存图像
 *		pCropRect[in]: 待剪切的图像区域
 *		ppbyCropDib[out]: 剪切出的dib格式的图像，应用程序无需分配内存
 *				应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		nDibSize[out]: 剪切出的dib格式图像的大小
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDCropDibImage(const unsigned char *pbyInDib,
                               const RECT *pCropRect,
                               unsigned char **ppbyCropDib,
                               int *nDibSize);

/* //add by jsa @20160324
 *	THIDCropDibImage: 从dib格式的图像中切出指定大小的图像
 *	Parameters:
 *		pbyInDib[in]: dib格式的内存图像
 *		pCropRect[in]: 待剪切的图像区域
 *		pbyCropDib[out]: 剪切出的dib格式的图像，若pbyCropDib输入NULL，则  *nDibSize 输出裁剪后图片需要的空间大小
 *		nDibSize[out]: 剪切出的dib格式图像的大小
                [in] :pbyCropDib 空间大小
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDCropDibImageOutAllocateMemory(const unsigned char *pbyInDib,
                                                const RECT *pCropRect,
                                                unsigned char *pbyCropDib,
                                                int *nDibSize);

/*
 *	THIDResizeImage: resize image
 *	Parameters:
 *		pSourceImage[in]: input image, it can be jpg, tif, bmp, or tiff image
 *		imageSize[in]: size of input image
 *		destWidth[in]: width of resized image
 *		destHeight[in]: height of resized image
 *		ppDestImage[out]: resized jpg image, the function allocate memory,
 *			when caller finished using the pointer, it must call THIDFreeMemory to free memory
 *		pDestSize[out]: size in bytes of resized image
 *		quality[in, opt]: compression quality, range from [0, 100]
 */
int __stdcall THIDResizeImage(const unsigned char *pSourceImage,
                              int imageSize,
                              int destWidth,
                              int destHeight,
                              unsigned char **ppDestImage,
                              int *pDestSize,
                              int quality = 70);

/**
 *	\brief 将RAW格式的灰度图像转换成dib位图
 *		\param[in] pGray RAW格式灰度图像
 *		\param[in] imageWidth 图像宽度
 *		\param[in] imageHeight 图像高度
 *		\param[out] ppDib dib位图，函数内部分配内存，应用程序无需分配内存
 *				应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		\param[out] pDibSize dib格式图像的大小
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDGrayToDib(const unsigned char *pGray,
                            int imageWidth,
                            int imageHeight,
                            unsigned char **ppDib,
                            int *pDibSize);

/**
 *	\brief 按指定角度旋转dib图像
 *		\param[in] pSourceDib 源dib图像
 *		\param[in] rotateAngle 旋转角度(单位: 度)，
 *				大于0表示逆时针旋转，小于0表示顺时针旋转
 *		\param[out] ppDestDib 旋转后的dib位图，函数内部分配内存，应用程序无需分配内存
 *				应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		\param[out] pDibSize dib格式图像的大小
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDRotateDib(const unsigned char *pSourceDib,
                            float angle,
                            unsigned char **ppDestDib,
                            int *pDibSize,
                            COLORREF colorPadding = RGB(255, 0, 0));

/**
 *	\brief 按指定角度旋转dib图像
 *		\param[in] pSourceDib 源dib图像
 *		\param[in] angle 旋转角度(单位: 度)，
 *				大于0表示逆时针旋转，小于0表示顺时针旋转
 *		\param[out] pDestDib 旋转后的dib位图，若pDestDib = NULL ,则 *pDibSize 输出旋转后需要内存空间大小
 *		\param[out] pDibSize dib格式图像的大小
 *            [in]  pDestDib 内存的大小
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDRotateDibOutAllocateMemory(const unsigned char *pSourceDib,
                                             float angle,
                                             unsigned char *pDestDib,
                                             int *pDibSize,
                                             COLORREF colorPadding = RGB(255, 0, 0) );

/**
 *	\brief 水平或垂直镜像图像
 *		\param[in] pSourceDib 源dib图像
 *		\param[in] flip 镜像类型
 *		\param[out] pDestDib 镜像后dib图像，调用程序需分配内存，内存与pSourceDib具有相同字节数
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDMirror(const unsigned char *pSourceDib,
                         MirrorType flip,
                         unsigned char *pDestDib);



/**
 *	\brief 放缩dib图像
 *		\param[in] pSourceDib 源dib图像
 *		\param[in] destWidth 放缩后图像宽度
 *		\param[in] destHeight 放缩后图像高度
 *		\param[out] ppDestDib 放缩后的dib位图，函数内部分配内存，应用程序无需分配内存
 *				应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		\param[out] pDibSize dib格式图像的大小
 *		\param[in, opt] keepAspectRatio 是否等比例放缩
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDResizeDib(const unsigned char *pSourceDib,
                            int destWidth,
                            int destHeight,
                            unsigned char **ppDestDib,
                            int *pDibSize,
                            bool keepAspectRatio = true);

/**
 *	\brief 放缩dib图像
 *		\param[in] pSourceDib 源dib图像
 *		\param[in] destWidth 放缩后图像宽度
 *		\param[in] destHeight 放缩后图像高度
 *		\param[out] pDestDib 放缩后的dib位图,若pDestDib = NULL,则 pDibSize 输出缩放后需要的内存空间大小
 *		\param[out] pDibSize dib格式图像的大小
			  [in]  pDestDib 分配内存的空间大小
 *		\param[in, opt] keepAspectRatio 是否等比例放缩
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDResizeDibOutAllocateMemory(const unsigned char *pSourceDib,
                                             int destWidth,
                                             int destHeight,
                                             unsigned char *pDestDib,
                                             int *pDibSize,
                                             bool keepAspectRatio = true);

/**
 *	\brief gamma变换
 *		\param[in, out] pDib dib图像
 *		\param[in] gamma系数 //gamma >0  =1.0 图像原样不变， >1 图像变浅，<1 图像变深
 *		\param[in] gammaG green分量gamma系数 //FreeImage 不支持此参数，输入值无效
 *		\param[in] gammaB blue分量gamma系数 //FreeImage 不支持此参数，输入值无效
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDGamma(unsigned char *pDib, float gamma, float gammaG, float gammaB);

/**
 *	\brief 得到规一化dib图像所占用的字节数
 *		\param[in] pFaceGeoFormat 规一化图像的几何信息
 *		\param[out] pDibSize 规一化dib图像占用的字节数
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDGetNormDibSize(const THIDNormFaceGeoFormat *pFaceGeoFormat,
                                 int *pDibSize);

/**
 *	\brief 输入dib格式的图像，输出规一化的dib格式图像
 *		\param[in] pDib dib格式的图像
 *		\param[in] pEyePoint 眼睛位置
 *		\param[in] pFaceGeoFormat 规一化图像的几何信息
 *		\param[out] pNormDib 输出规一化的图像，调用程序需分配内存，内存大小可通过THIDGetNormDibSize得到
 *		\param[out] nPosition 人脸在原始图像中的位置信息，用于表示人脸是否太靠近图像边缘
 *		\param[in, opt] colorPadding 归一化图像中某个像素若在原始图像中没有对应点，则采用该值填充
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDNormFace(const unsigned char *pDib,
                           const THIDEyePoint *pEyePoint,
                           const THIDNormFaceGeoFormat *pFaceGeoFormat,
                           unsigned char *pNormDib,
                           int *nPosition,
                           COLORREF colorPadding = RGB(255, 0, 0));

/*********************************************************************************************************//*
 * @brief        :THIDBrightContrast 对比度亮度调整
 * @input  param :pDib 图像数据；brightness 亮度百分值[-100,100];contrast 对比度百分值[-100,100];
 *                brightness [-100,100]范围，0代表无变化，小于0 变深，大于0变浅;
 *                contrast [-100,100]范围,0 代表无变化，小于0 对比度减小，大于0 对比度变大
 * @output param :pDib 调整后的DIB图像
 * @retval       : 0成功，非0失败
 ************************************************************************************************************/
int __stdcall THIDBrightContrast(unsigned char *pDib, int brightness, int contrast);

/**
 *	\brief 直方图均衡
 *		\param[in, out] pDib dib图像
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDHistEqu(unsigned char *pDib);

/*
 *	THIDYUV420PlanarToDib: 将YUV420 planar格式转换成dib格式
 *	Parameters:
 *		pYUV420[in]: 输入YUV420 planar格式图像
 *		imageWidth[in]: 图像宽度
 *		imageHeight[in]: 图像高度
 *		ppDib[out]: dib格式图像。函数内部分配内存，应用程序无需分配内存
 *				应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		dibSize[out]: dib格式图像的大小
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDYUV420PlanarToDib(const unsigned char *pYUV420,
                                    int imageWidth,
                                    int imageHeight,
                                    unsigned char **ppDib,
                                    int *dibSize);

/**
 *	\brief 将YUV422planar格式转换成dib格式
 *		\param[in]  pYUV422     输入YUV422planar格式图像
 *		\param[in]  imageWidth  图像宽度
 *		\param[in]  imageHeight 图像高度
 *		\param[out] ppDib       dib格式图像。函数内部分配内存，应用程序无需分配内存
 *				应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		\param[out] dibSize     dib格式图像的大小
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDYUV422PlanarToDib(const unsigned char *pYUV422,
                                    int imageWidth,
                                    int imageHeight,
                                    unsigned char **ppDib,
                                    int *dibSize);

/*
 *	THIDYV12PlanarToDib: 将YV12 planar格式转换成dib格式
 *	Parameters:
 *		pYV12[in]: 输入YV12 planar格式图像
 *		imageWidth[in]: 图像宽度
 *		imageHeight[in]: 图像高度
 *		ppDib[out]: dib格式图像。函数内部分配内存，应用程序无需分配内存
 *				应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		dibSize[out]: dib格式图像的大小
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDYV12PlanarToDib(const unsigned char *pYV12,
                                  int imageWidth,
                                  int imageHeight,
                                  unsigned char **ppDib,
                                  int *dibSize);

/**
 *	\brief 将YUV422Interleave格式转换成dib格式
 *		\param[in]  pYUV422     输入YUV422Interleave格式图像
 *		\param[in]  imageWidth  图像宽度
 *		\param[in]  imageHeight 图像高度
 *		\param[out] ppDib       dib格式图像。函数内部分配内存，应用程序无需分配内存
 *				应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		\param[out] dibSize     dib格式图像的大小
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDYUV422InterleaveToDib(const unsigned char *pYUV422,
                                        int imageWidth,
                                        int imageHeight,
                                        unsigned char **ppDib,
                                        int *dibSize);

/**
 *	\brief 将CbYCr422格式（即UYVY）转换成dib格式
 *		\param[in]  pCbYCr422   输入CbYCr422格式图像
 *		\param[in]  imageWidth  图像宽度
 *		\param[in]  imageHeight 图像高度
 *		\param[out] ppDib       dib格式图像。函数内部分配内存，应用程序无需分配内存
 *				应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		\param[out] dibSize     dib格式图像的大小
 *	\return int(参见THIDErrorDef.h中的错误定义)
 *  \note:CbYCr 为progressive packed格式
 */
int __stdcall THIDCbYCr422ToDib(const unsigned char *pCbYCr422,
                                int imageWidth,
                                int imageHeight,
                                unsigned char **ppDib,
                                int *dibSize);

/*
 *	THIDDibToYUV420Planar: 将24位真彩色dib位图转换成YUV420 planar格式
 *	Parameters:
 *		pDib[in]: 输入24位真彩色dib位图
 *		pYUV420[out]: 输出YUV420 planar格式，调用程序必须分配内存。内存大小
 *			为 imageWidth * imageHeight * 3 / 2
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDDibToYUV420Planar(const unsigned char *pDib, unsigned char *pYUV420);

/**
 *	\brief 将RAW格式的彩色图像转换成dib位图
 *		\param[in] pGray RAW格式彩色图像
 *		\param[in] imageWidth 图像宽度
 *		\param[in] imageHeight 图像高度
 *		\param[in] nChannel 图像通道数
 *		\param[out] ppDib dib位图，函数内部分配内存，应用程序无需分配内存
 *				应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		\param[out] pDibSize dib格式图像的大小
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDColorToDib(const unsigned char *pbyColor, int imageWidth, int imageHeight, int nChannel, unsigned char **ppDib, int *pDibSize);

/*
 *	THIDDibToColor: convert dib image to raw format BGR color image
 *	Parameters:
 *		pBitsInfo[in]: Pointer to a BITMAPINFO structure that contains information about the DIB. 
 *		pBits[in]: Pointer to the DIB bits, which are stored as an array of bytes.
 *		pbyOutGrayImage[out]: raw format BGR image, caller must allocate memory.
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDDibToColor(const BITMAPINFO *pBitsInfo, const unsigned char *pBits, unsigned char *pbyOutColorImage);

/*
 *	THIDDibImageToColorImage: 将Dib格式的图像转换成raw格式的BGR彩色图像
 *	Parameters:
 *		pbyInDibImage[in]: dib格式的图像
 *		pbyOutGrayImage[out]: raw格式的BGR彩色图像，调用程序需要分配内存
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDDibImageToColorImage(const unsigned char *pbyDibImage, unsigned char *pbyColorImage);

enum RotateType
{
	Rotate90 = 0,		// clockwise rotate 90 degree
	Rotate180,			// clockwise rotate 180 degree
	Rotate270			// clockwise rotate 270 degree
};

/**
 *	\brief Roate image by 90 degree, 180 degree or 270 degree
 *		\param[in] pDib input dib image, current only support 24 bits color image
 *		\param[out] pRotateDib rotated image, caller must allocate memory, if this
 *			parameter is NULL, the pBufferSize is filled with the memory size needed for rotated image
 *		\param[in, out] as input the size of pRotateDib, as output actual memory size needed by pRotateDib
 *	\return int ErrCode defined THIDErrorDef.h
 */
int __stdcall THIDRotate(const unsigned char *pDib, unsigned char *pRotateDib, int *pBufferSize, RotateType type = Rotate90);

/************************************************************************************************************
*									暂时未实现的函数														*
 ************************************************************************************************************/
 
/**
 *	\brief 在dib图像上画线
 *		\param[in, out] pDib dib图像
 *		\param[in] pt1 起始点
 *		\param[in] pt2 终止点
 *		\param[in] color 线条颜色
 *		\param[in, opt] thickness 线条宽度
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDLine(unsigned char *pDib, THIDPoint pt1, THIDPoint pt2,
					   COLORREF color, int thickness = 1);

/**
 *	\brief 在dib图像上画矩形
 *		\param[in, out] pDib dib图像
 *		\param[in] pt1 矩形左上角坐标
 *		\param[in] pt2 矩形右下角坐标
 *		\param[in] color 线条颜色
 *		\param[in, opt] thickness 线条宽度
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDRectangle(unsigned char *pDib, THIDPoint pt1, THIDPoint pt2,
							COLORREF color, int thickness = 1);

/**
 *	\brief 在dib图像上画圆
 *		\param[in, out] pDib dib图像
 *		\param[in] center 圆心坐标
 *		\param[in] radius 圆半径
 *		\param[in] color 线条颜色
 *		\param[in, opt] thickness 线条宽度
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDCircle(unsigned char *pDib, THIDPoint center, int radius,
						 COLORREF color, int thickness = 1);

/**
 *	\brief 在dib图像上画椭圆
 *		\param[in, out] pDib dib图像
 *		\param[in] center 椭圆中心坐标
 *		\param[in] axesX x方向主轴
 *		\param[in] axesY y方向主轴
 *		\param[in] angle x方向主轴与x轴的夹角，单位度
 *		\param[in] start_angle 椭圆弧开始角度，单位度
 *		\param[in] end_engle 椭圆弧结束角度，单位度
 *		\param[in] color 线条颜色
 *		\param[in, opt] thickness 线条宽度
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDEllipse(unsigned char *pDib, THIDPoint center, int axesX, int axesY,
						  float angle, float start_angle, float end_angle,
						  COLORREF color, int thickness = 1);

/**
 *	\brief 在dib图像上画多边形
 *		\param[in, out] pDib dib图像
 *		\param[in] pConvex 多边形顶点
 *		\param[in] numConvex 顶点数目
 *		\param[in] color 线条颜色
 *		\param[in, opt] thickness 线条宽度
 *	\return int(参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDPolygon(unsigned char *pDib, const THIDPoint *pConvex, int numConvex,
						  COLORREF color, int thickness = 1);

/**
 *	\brief 在dib图像上输出文本
 *		\param[in, out] pDib dib图像
 *		\param[in] origin 文本起始位置
 *		\param[in] szText 待输出的文本
 *		\param[in] color 字体颜色
 *		\param[in, opt] scale 字体大小比例
 *		\param[in, opt] thickness 文字线条宽度大小
 */
int __stdcall THIDPutText(unsigned char *pDib, const THIDPoint origin, const char *szText,
					  COLORREF color, float scale = 3.0f, int thickness = 1);


/////////////////////////////////////未实现的函数/////////////////////////////////////////////////////////////
#ifndef THIDNORMFACEGEOFORMATEX
#define THIDNORMFACEGEOFORMATEX
typedef struct THIDNormFaceGeoFormatEx
{
	int normWidth;		// width of normalized face image
	int normHeight;		// height of normalized face image	

	int faceWidthMin;	// minimum width of face area in normalized face image
	int faceWidthMax;	// maximum width of face area in normalized face image				

	//	int eyeYPosMin;		// minimum eye's y coordinate, 
	int eyeYPosMax;		// maximum eye's y coordinate
	int headTopYPosMin;	// minimum head top's y coordinate
	int headTopYPosMax;	// maximum head top's y coordinate	
	int rulerToMarginWidthMin;	// minimum width of ruler to margin
	int rulerToMarginWidthMax;	// maximum width of ruler to margin

	int resInDPI;		// resolution in DPI

	int reserved[6];
}THIDNormFaceGeoFormatEx;
#endif	//	THIDNORMFACEGEOFORMATEX
/*
 *	THIDNormalize: 输入dib格式的人脸图像，输出归一化图像
 *	Parameters:
 *		pbyDib[in]: dib格式的图像
 *		pFaceGeoFormatEx[in]: 归一化图像的几何信息
 *				2nd ID Card's geometric format: { 358, 441, 193, 221, 234, 7, 21, 0, 0, 350}
 *				front view of criminal suspect: {450, 600, 190, 210, 250, 45, 55, 65, 75, 300}
 *				profile view of criminal suspect: {450, 600, 265, 295, 250, 45, 55, 65, 75, 300}
 *		pFacePointInfo[in]: 人脸特征点坐标信息; (现程序内部只用到了眼睛位置)
 *		pbyNormDib[out]: 输出规一化的图像，调用程序需分配内存，内存大小为 (归一化图像宽度 * 归一化图像高度 * 3 + 10240) 字节
 *		colorPadding[in]: 归一化图像中某个像素若在原始图像中没有对应点，则采用该值填充
 */
int __stdcall THIDNormalize(const unsigned char *pbyDib, const THIDNormFaceGeoFormatEx *pFaceGeoFormatEx, 
	const THIDEyePoint *pEyePoint,  unsigned char *pbyNormDib, COLORREF colorPadding = RGB(255, 255, 255));


#ifdef WIN32 //放中文字符，linux下未实现
#ifndef _T
#ifdef WIN32
#define _T(x)       __T(x)
#define __T(x)      L ## x
#else
#define _T 
#endif
#endif


/**
 * \brief 在DIB位图上绘制文字
 * \param[in,out] pDib 要绘制文字的DIB位图数据指针
 * \param[in] origin 绘制原点
 * \param[in] szText 要绘制的内容
 * \param[in] color 绘制文字的颜色
 * \param[in] scale 绘制文字的高度
 * \param[in] thickness 绘制文字的粗细，取值~9
 * \param[in] fontName 绘制文字使用的字体
 * \return 
 */
// add by jsa 固定写死为宋体 @20151029
int __stdcall THIDPutTextExW(unsigned char *pDib, THIDPoint origin, const wchar_t *szText, 
                          COLORREF color, float scale = 30.0f,
                          int thickness = 1, const wchar_t * fontName = L"宋体");

int __stdcall THIDPutTextEx(unsigned char *pDib, THIDPoint origin, const char *szText, 
							COLORREF color, float scale = 30.0f,
							int thickness = 1, const char * fontName = "宋体");

#endif
/*
 *	THIDEncodeDIBToOtherFormat: 将dib格式的内存图像编码成其他格式的图像
 *	Parameters:
 *		pbyInDib[in]: dib格式的内存图像
 *		nImageFormat[in]: 需要编码出的图像的格式
 *		ppbyOutBuffer[out]: 编码后的图像。函数内部分配内存，应用程序无需分配内存
 *				应用程序在使用完该指针后需要调用 THIDFreeMemory 释放内存
 *		nEncodeSize[out]: 编码后图像的大小
  *		JpegQuality[in, opt]: JPEG图像的压缩率，范围（0,100]
 *	Return Value: int (参见THIDErrorDef.h中的错误定义)
 */
int __stdcall THIDEncodeDIBToOtherFormatEx(const unsigned char *pbyInDib, int nImageFormat, unsigned char **ppbyOutBuffer, int *nEncodeSize, int JpegQuality=85);


////////////////////////////////////////CxBio部分////////////////////////////////////////////////////////////////////////////////
#if 1

#define  __DLL_CXBIO_DLL_H_
#define __DLL_EXPORTING
typedef struct 
{
	unsigned int	inWidth;
	unsigned int	inHeight; 
	unsigned int    buf_size;
	float	        rate;       // only WSQ
	unsigned int    resolution;
	unsigned int	encType; 
	unsigned char*  inBuf;
} EncInParam;

typedef struct 
{
	unsigned int    width;
	unsigned int    height;
	unsigned int    buf_size;
	unsigned int    resolution;
	unsigned char*  buf;
} DecOutParam;

#ifdef __DLL_EXPORTING
#define DLL_EXPORTING_API __declspec(dllexport)
#else
#define DLL_IMPORTING_API __declspec(dllimport)
#endif


#define GETINFO_ERROR		1
#define GETINFO_SUCESS		0
#define GETINFO_ERRTYPE		(-1)


//	Const
#define CXBIO_FORMAT_UNKNOWN 0
#define CXBIO_FORMAT_WSQ 1
#define CXBIO_FORMAT_JPG 2
#define CXBIO_FORMAT_JPGL 3
#define CXBIO_FORMAT_JP2 4
#define CXBIO_FORMAT_JP2L 5
#define CXBIO_FORMAT_PNG 6
#define CXBIO_FORMAT_BMP 7
//	Error Code

// ok
#define CXBIO_ERROR_SUCCESS 0L
// invalid input buffer
#define CXBIO_INBUFF_ERROR  2L
// invalid type
#define CXBIO_TYPE_ERROR	3L
// encoding process error
#define CXBIO_ENCODING_ERROR 4L
// decoding process error
//#define CXBIO_DECODING_ERROR 5L
// compression rate error
#define CXBIO_COMPRESSIONRATE_ERROR 6L
// no gray-scale image.
#define CXBIO_IMAGE_FORMAT_ERROR 7L

#define MIN_HEADER_BMP		(24)
#define MIN_HEADER_WSQ		(592)
#define MIN_HEADER_JPG		(98)
#define MIN_HEADER_JPGL		(154)
#define MIN_HEADER_JP2		(56)
#define MIN_HEADER_JP2L		(56)
#define MIN_HEADER_PNG		(24)

#ifndef WIN32
	int  CxbioEncode (
		EncInParam*      inparam,
		unsigned char** outBuf ,
		unsigned int*   outLength
		);

	int  CxbioGetImageData (
		unsigned char* inBuf,
		unsigned int   inLength,
		unsigned int   inType,
		DecOutParam*   outResult
		);
	int  GetImageInfo(unsigned char *pHeadBuf, int nImageType,int *pWidth, int *pHeight);
	void   CxbioFree(void* ptr);
#else
	DLL_EXPORTING_API int __stdcall CxbioEncode (
		EncInParam*      inparam,
		unsigned char** outBuf ,
		unsigned int*   outLength
		);

	DLL_EXPORTING_API int __stdcall CxbioGetImageData (
		unsigned char* inBuf,
		unsigned int   inLength,
		unsigned int   inType,
		DecOutParam*   outResult
		);

	DLL_EXPORTING_API int __stdcall GetImageInfo(unsigned char *pHeadBuf, int nImageType,int *pWidth, int *pHeight);

	DLL_EXPORTING_API void  __stdcall CxbioFree(void* ptr);
#endif
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif	//	__cplusplus
#endif	//	__THIDIMAGEHELPER_H_INCLUDE__
