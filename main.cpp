#include "setting/setting.hpp"
// #include "setting.hpp"
int main()
{
    Mat src = imread("/home/jun/workplace/test.png");
    imshow("src",src);
    test();
    waitKey(0);
    return 0;
}