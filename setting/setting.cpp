#include "include/setting.hpp"
void test()
{
    Mat             frame = imread("/home/jun/workplace/test.png");
    unique_ptr<int> test1 = make_unique<int>(10);
    // cout<<"test1:"<<*test<<endl;
    cout << "hello" << endl;
    imshow("frame", frame);
    // imshow("u1s1",frame);
}

void setValue(int* _arr)
{
    for (size_t i = 0; i <= sizeof(_arr) / sizeof(_arr[0]); ++i) {
        _arr[i] = i;
        cout << "_arr[" << i << "] = " << _arr[i] << endl;
    }
}

void test01()
{
    unique_ptr<Array> test_arr = make_unique<Array>();
    setValue(test_arr->getArray());
    test_arr->displayArray();
}

int* Array::getArray()
{
    return this->transform_arr;
}

void Array::displayArray()
{
    for (size_t i = 0; i < sizeof(transform_arr) / sizeof(transform_arr[0]);
         ++i) {
        cout << "transform[" << i << "] =" << transform_arr[i] << endl;
    }
}