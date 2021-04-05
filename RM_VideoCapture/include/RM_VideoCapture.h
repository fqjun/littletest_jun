#pragma once

/*---工业相机中使用到opencv2.0的 IplImage 需要包含此头文件 ---*/
#include <CameraApi.h>
/*---工业相机中使用到opencv2.0的 cvReleaseImageHeader 需要包含此头文件 ---*/
#include <opencv2/imgproc/imgproc_c.h>
#include <iostream>
using namespace std;

#    define ISOPEN_INDUSTRY_CAPTURE 0
/**
    @brief: 是否使用工业相机
    @param: 0     使用工业相机
    @param: 1     使用普通USB相机
  */

#    define USB_CAPTURE_DEFULT 0
/**
    @brief: 相机的默认值
    @note: 使用普通USB相机时，Opencv的VideoCapture接口的值
  */

/* ------------------- 相机参数设置 ------------------- */
#define CAMERA_EXPOSURETIME 800      // 800 400大神符 1200
#define CAMERA_RESOLUTION_COLS 1280  // 1280 务必16的倍数！
#define CAMERA_RESOLUTION_ROWS 800   // 800 务必2的倍数！
#define CAMERA_RESOLUTION_COLS_FOV ((1280 - CAMERA_RESOLUTION_COLS) * 0.5)
#define CAMERA_RESOLUTION_ROWS_FOV ((1024 - CAMERA_RESOLUTION_ROWS) * 0.5)
#define CAMERA_BLUE_GAIN 123
#define CAMERA_GREEN_GAIN 123
#define CAMERA_RED_GAIN 103
#define CAMERA_GAMMA 119
#define CAMERA_CONTRAST 83
#define CAMERA_SATURATION 166
/**
  @brief: 设置相机的分辨率
  @param: CAMERA_EXPOSURETIME   相机曝光时间
  @param: COLS                  为图像的宽度
  @param: ROWS                  为图像的高度
  @param: FOV                   为图像对应左上角的偏移值
  @note: 这部分相机文档中是写反的　x轴　和　y轴
         偏移值计算为 *** (相机最大分辨率 - 当前设置分辨率)/2 ***
*/

#define CAMERA_CONFIG 1
/**
 * @brief: 设置相机参数模式选项
 * @param: 0 曝光
 * @param: 1 曝光 + 其他
 * @param: 2 动态调整 曝光
 * @param: 3 动态调整 曝光 + 其他
 * @note: 其他部分包括：对比度、饱和度、伽马值、颜色增益（R G B）
 *
 */
/* ------------------- 相机参数设置 ------------------- */

class RM_VideoCapture
{
    public:
    unsigned char *g_pRgbBuffer; //处理后数据缓存区

    int                     iCameraCounts = 1;
    int                     iStatus=-1;
    tSdkCameraDevInfo       tCameraEnumList;
    int                     hCamera;
    tSdkCameraCapbility     tCapability;      //设备描述信息
    tSdkFrameHead           sFrameInfo;
    BYTE*			        pbyBuffer;
    IplImage                *iplImage = nullptr;
    int                     channel=3;
    BOOL                    AEstate=FALSE;
    tSdkImageResolution     pImageResolution;       //相机分辨率信息

    bool                    iscamera0_open = false;
public:

    RM_VideoCapture(int cameramode);
    ~RM_VideoCapture();
    bool isindustryimgInput();
    void cameraReleasebuff();
    void cameraSet();

#if CAMERA_CONFIG != 0 
private:

    #if CAMERA_CONFIG > 1
    int exposuretime = CAMERA_EXPOSURETIME;
    #endif
    
    #if CAMERA_CONFIG == 1 || CAMERA_CONFIG == 3
    int b_gain = CAMERA_BLUE_GAIN;
    int g_gain = CAMERA_GREEN_GAIN;
    int r_gain = CAMERA_RED_GAIN;
    int gamma = CAMERA_GAMMA;
    int contrast = CAMERA_CONTRAST;
    int saturation = CAMERA_SATURATION;
    #endif 

#endif
};




