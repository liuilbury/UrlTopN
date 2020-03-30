#ifndef URLTOPN_DATA_H
#define URLTOPN_DATA_H

#include<fstream>
#include "Url.h"
#include<queue>
#include<mutex>
#include<thread>
#include<string>
#include <condition_variable>
#include <iostream>

//Data类的用处是创建一个新的URL文件
//使用createData函数并给予文件地址和大小可以在指定地址生成指定大小的data.txt文件
//且作为spilt_Data和merge_Data的父类，为它们提供原始文件的位置及需要分成多少份或需要合并多少份
class Data {
public:
    std::string filename;//文件地址
    const int urlsize = 40;  //认为一条url近似40B大小
    long long looptimes;//looptimes=filesize/urlsize.意味着一共有多少条URL

    void createData(std::string filename, int size);//生成文件
};

#endif