#include "spilt_Data.h"

void spilt_Data::spiltData_init() {//初始化
    for (int i = 0; i < 200; i++) {
        hash_url_cnt[i] = 0;
        spilt[i] = "";
    }
}

void spilt_Data::spiltData_read() {
    std::ifstream in(filename);//打开文件
    std::string query;
    while (true) {
        if (getline(in, query)) {//读取一行
            std::unique_lock<std::mutex> lock(mtx);//想要操作队列时加锁
            if (q.size() == looptimes / 200 / 200) {
                repo_not_full.wait(lock);//队列满时释放锁，被唤醒时获得锁
            }
            q.push(query);
            repo_not_empty.notify_one();//唤醒所有因空阻塞的线程
            lock.unlock();//解锁
        } else {
            spilt_end = true;
            return;
        }
    }
}

void spilt_Data::spiltData_write() {
    while (true) {
        std::unique_lock<std::mutex> lock_read_queue(mtx_read_queue);//写线程锁
        std::unique_lock<std::mutex> lock(mtx);//想要读取队列时加锁
        if (q.empty()) {
            if (spilt_end) {//如果结束标识为true且队列为空，则退出
                lock_read_queue.unlock();
                lock.unlock();
                break;
            }
            repo_not_empty.wait(lock);//队列空时释放锁，被唤醒时获得锁
        }
        std::string query = q.front();
        q.pop();
        repo_not_full.notify_one(); //唤醒所有因空阻塞的线程
        lock.unlock();
        lock_read_queue.unlock();
        std::hash<std::string> ss;
        int ha_sh = ss(query) % 200;
        std::unique_lock<std::mutex> lock_write_vector(mtx_write_vector);//写线程在使用vector的时候不被干扰
        spilt[ha_sh] = spilt[ha_sh] + query + "\n";//字符串拼接
        hash_url_cnt[ha_sh]++;
        if (hash_url_cnt[ha_sh] != looptimes / 200 / 200) {//当hash_url_cnt[ha_sh]里的数量为looptimes/200/200时，进行写操作
            lock_write_vector.unlock();
        } else {
            std::string outstring = spilt[ha_sh];
            spilt[ha_sh] = "";
            hash_url_cnt[ha_sh] = 0;
            lock_write_vector.unlock();
            std::unique_lock<std::mutex> lock_write_file(mtx_write_file);//写线程在使用文件的时候不被干扰
            std::ofstream out("../../../data/spiltData/" + std::to_string(ha_sh) + ".txt", std::ios::app);
            out << outstring;
            out.close();
            lock_write_file.unlock();
        }
    }
}

void spilt_Data::spiltData_end() {//写线程全部退出后，spilt里还有剩余URL需要处理
    for (int i = 0; i < 200; i++) {
        if (spilt[i].size() == 0)
            continue;
        std::ofstream out("../../../data/spiltData/" + std::to_string(i) + ".txt", std::ios::app);
        out << spilt[i];
        spilt[i] = "";
        out.close();
    }
}