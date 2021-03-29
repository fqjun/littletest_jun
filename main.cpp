#include <iostream>
#include<opencv4/opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat test;
    test = imread("~/workspace/gcurobot_wolf.jpeg");
    imshow("test",test);
    cout<<"hello world"<<endl;
    system("pause");
}