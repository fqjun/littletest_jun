// #include "../setting/setting.hpp"
#include "RM_Link/include/RM_Link.h"
#include "setting/include/setting.hpp"
#include <memory>
int main()
{
    unique_ptr<RM_Link> run =make_unique<RM_Link>();
    run->run();

    Mat src = imread("/home/jun/workplace/test.png");
    imshow("src", src);
    cout << "sdlagsgasd" << endl;
    test();
    waitKey(0);
    return 0;
}