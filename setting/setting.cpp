#include"include/setting.hpp"
void test(){

    Mat frame = imread("/home/jun/workplace/test.png");
    unique_ptr<int> test1 = make_unique<int>(10);
    // cout<<"test1:"<<*test<<endl;
    cout<<"hello"<<endl;
    imshow("frame",frame);
    imshow("u1s1",frame);
}

