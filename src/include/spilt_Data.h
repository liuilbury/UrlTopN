#ifndef URLTOPN_SPILT_DATA_H
#define URLTOPN_SPILT_DATA_H

#include "Data.h"

//spilt_Data的目的是拆分大文件，采用了单线程读多线程写的操作
class spilt_Data : public Data {
public:
    std::condition_variable repo_not_full;//队列不满条件变量
    std::condition_variable repo_not_empty;//队列不空条件变量
    std::mutex mtx;//读写操作的互斥量
    std::mutex mtx_read_queue;//写操作读取队列的互斥量
    std::mutex mtx_write_vector;//写操作写入vector的互斥量
    std::mutex mtx_write_file;//写操作写入文件的互斥量
    std::queue<std::string> q;//读线程放入数据，写线程读取数据的队列
    int hash_url_cnt[200];//某一个hash值的URL已经被储存的数量
    std::string spilt[200];//储存某一个hash值的url
    bool spilt_end = false;//是否已经读取完全部的URL
    void spiltData_init();//初始化hash_url_cnt与spilt
    void spiltData_read();//读操作
    void spiltData_write();//写操作
    void spiltData_end();//最后将spilt剩余的量全部写入文件
};

#endif