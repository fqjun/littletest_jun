#pragma once

#include <iostream>
#include <memory>
#include <opencv4/opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void test();
void test01();

class Array {
  public:
    int* getArray();
    void displayArray();

  private:
    int transform_arr[3];
};
