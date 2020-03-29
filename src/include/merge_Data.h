#ifndef URLTOPN_MERGE_DATA_H
#define URLTOPN_MERGE_DATA_H
#include "Data.h"
#include <unordered_map>
class merge_Data :public Data{
public:
    int times=0;
    int N;
    std::vector<std::pair<std::string,int>>top[200];
    std::queue<int>unprocessed,processed;//两个队列，一个记录处理的，一个记录未处理的
    std::condition_variable repo_not_full;
    std::condition_variable repo_not_empty;
    std::mutex mtx;//互斥量
    std::mutex mtx_read;
    std::mutex mtx_write1;
    std::mutex mtx_write2;
    void mergeData_init();
    void mergeData_Top100_easy();
    void mergeData_read_AND_write();
    void mergeData_Top100_finish();
};
#endif