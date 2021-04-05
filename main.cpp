// #include "../setting/setting.hpp"
#include "RM_VideoCapture/include/RM_VideoCapture.h"
#include "setting/include/setting.hpp"
#include <memory>
// #include "setting.hpp"
using namespace std;
int main()
{
    // unique_ptr<RM_VideoCapture> industrialcapture =
    //     make_unique<RM_VideoCapture>(ISOPEN_INDUSTRY_CAPTURE);
    // unique_ptr<Mat> frame = make_unique<Mat>();
RM_VideoCapture industrialcapture(ISOPEN_INDUSTRY_CAPTURE);
Mat frame;
    while (true) {
        if (industrialcapture.isindustryimgInput()) {
            frame = cvarrToMat(industrialcapture.iplImage, true);
        }
        else {
            cout << "图像为空" << endl;
            break;
        }

        if (frame.empty()) {
            cout << "图像为空" << endl;
            break;
        }
        imshow("frame", frame);
        industrialcapture.cameraReleasebuff();

        if (waitKey(1) == 'q') {
            break;
        }
    }

    Mat src = imread("/home/jun/workplace/test.png");
    imshow("src", src);
    cout << "sdlagsgasd" << endl;
    test();
    waitKey(0);
    return 0;
}