#include "Data.h"
class spilt_Data :public Data {
public:
    std::condition_variable repo_not_full;
    std::condition_variable repo_not_empty;
    std::mutex mtx;//读写操作的互斥量
    std::mutex mtx_read;//写操作读取队列的
    std::mutex mtx_write1;
    std::mutex mtx_write2;
    std::queue<std::string>q;
    int hash_url_cnt[200];
    std::string spilt[200];
    bool spiltend = false;
    void spiltData_init();
    void spiltData_write();
    void spiltData_read();
    void spiltData_end();
};