#pragma once
#include <opencv4/opencv2/opencv.hpp>
#include "../../RM_VideoCapture/include/RM_VideoCapture.h"
#include <memory>

using namespace std;
using namespace cv;

class RM_Link {
  public:
    RM_Link();
    ~RM_Link();

    // 总运行函数
    void run();

    // 获取控制信息
    void updateControlInformation(const unsigned char* arr);

  private:
    //各部分对象声明
    /* Basis长期启动 */
    /* 工业相机 */
    unique_ptr<RM_VideoCapture> industrialcapture;
    /* USB相机 */
    unique_ptr<VideoCapture> capture;

  private:
    /* Model TODO*/
    /* 自瞄 TODO*/
    /* 能量机关 TODO*/

  private:
    /* Tools */
// #if COUT_FPS == 1
    /* 计算帧率 */
// #endif
    /* 录制视频 TODO 添加开关*/
    /* 文件数据交换 TODO 添加开关*/

  private:
    //公共原图
    unique_ptr<Mat> frame;
    unique_ptr<Mat> src_img;

};
