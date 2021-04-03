#include "setting.hpp"

void test(int&) {}

int main()
{
    Mat test;
    test = imread("/home/jun/workplace/test.png");

    string test_str = "/home/jun/workplace/Github/littletest_jun/config.xml";

    cout << "test_str:" << test_str << endl;
    unique_ptr<Settings>settint = make_unique<Settings>(test_str);
    // Settings setting(test_str);

    int    input_test_int    = 0;
    float  input_test_float  = 0.f;
    double input_test_double = 0.0;

    while (true) {
        imshow("test", test);

        if (waitKey(1) == 's') {
            cout << "请输入int：";
            cin >> input_test_int;
        }
        if (waitKey(1) == 'a') {
            cout << "请输入float：";
            cin >> input_test_float;

        }
        if (waitKey(1) == 'd') {
            cout << "请输入double：";
            cin >> input_test_double;
            // setting.setInt(input_test);
            // setting.writeOnqce(test_str);
        }
        settint->readData(test_str);
        // setting.readData(test_str);

        if (waitKey(1) == 'q') {
            break;
        }
    }
    cout << "hello world" << endl;
}