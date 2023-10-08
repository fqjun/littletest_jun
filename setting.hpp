// #pragma once

#ifndef _SETTING_HPP
#define _SETTING_HPP

#include <iostream>
#include <string>
#include <memory>
#include <opencv4/opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//数据结构体  
struct RuneParam
{
    int test_int;
    float test_float;
    double test_double;
    RuneParam()
    {
        test_float = 0.f;
        test_int = 0;
        test_double =0.0;
    }
};

class Settings {
  public:

    //构造函数
    Settings(const string& filename)
    {
        //显示参数文件是否读取正确
        FileStorage setting_fs(filename, FileStorage::READ);
        read(setting_fs);
        setting_fs.release();
        // cout<<"file:"<<file<<endl;
    }

    //读取数据
    void readData(const string& filename)
    {
        FileStorage read_fs(filename, FileStorage::READ);
        read(read_fs);
        read_fs.release();
    }

    //写入数据
    void writeData(string& filename) const
    {
        FileStorage write_fs(filename, FileStorage::WRITE);
        write(write_fs);
        write_fs.release();
    }

  private:
    void read(const FileStorage& fs)
    {
        //TODO:for debug image
        //TODO:for flag
        //TODO:for armor value 
        //TODO:for buff value
        fs["show_int"] >> this->rune->test_int;
        fs["show_float"] >>this->rune->test_float;
        fs["show_double"]>>this->rune->test_double;
    }

    void write(FileStorage& fs) const
    {
        fs << "show_int" << this->rune->test_int;
        //TODO:for debug image
        //TODO:for flag
        //TODO:for armor value 
        //TODO:for buff value
    }

    RuneParam *rune;
    string file;
};

#endif 