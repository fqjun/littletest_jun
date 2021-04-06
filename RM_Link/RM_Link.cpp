#include "include/RM_Link.h"

/**
 * @brief Construct a new rm link::rm link object
 * 选择输入源并初始化连接类
 *
 */
RM_Link::RM_Link()
    : industrialcapture(make_unique<RM_VideoCapture>(ISOPEN_INDUSTRY_CAPTURE)),
      capture(make_unique<VideoCapture>(USB_CAPTURE_DEFULT))
{
    // 初始化图像
    frame   = make_unique<Mat>();
    src_img = make_unique<Mat>();
}

/**
 * @brief Destroy the rm link::rm link object
 *
 */
RM_Link::~RM_Link()
{
    // TODO:清楚内存或其他内容
}

/**
 * @brief 总运行文件
 *
 */
void RM_Link::run()
{
    while (true) {
        if (industrialcapture->isindustryimgInput()) {
            *frame = cvarrToMat(industrialcapture->iplImage, true);
            cout<<"Industrial Camera"<<endl;
        }
        // else {
        //     *capture >> *frame;
        //     cout<<"Usb Camera"<<endl;
        // }

        if (frame->empty()) {
            cout << "图像为空" << endl;
            break;
        }

        this->frame->copyTo(*src_img);

        imshow("frame", *frame);
        // imshow("src_img", *src_img);

        // 释放相机内容（必须！）
        industrialcapture->cameraReleasebuff();

        // 按 q 退出程序
        if (waitKey(1) == 'q') {
            break;
        }
    }
}
