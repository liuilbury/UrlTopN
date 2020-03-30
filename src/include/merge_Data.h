#ifndef URLTOPN_MERGE_DATA_H
#define URLTOPN_MERGE_DATA_H
#include "Data.h"
#include <unordered_map>
class merge_Data :public Data{
public:
    int times=0;//合并次数
    int N;//TopN的N
    std::vector<std::pair<std::string,int>>top[200];
    std::queue<int>unprocessed,processed;//两个队列，一个记录处理的，一个记录未处理的
    std::mutex mtx_read;//读取锁
    void mergeData_init();//初始化
    void mergeData_Top100_easy();//计算出小文件的TopN
    void mergeData_read_AND_write();//合并小文件
    void mergeData_Top100_finish();//输出答案
};
#endif