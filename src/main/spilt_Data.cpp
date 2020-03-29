#include "spilt_Data.h"
void spilt_Data::spiltData_init() {
    for (int i = 0; i < 200; i++) {
        hash_url_cnt[i] = 0;
        spilt[i] = "";
    }
}
void spilt_Data::spiltData_read() {
    std::ifstream in(filename);
    std::string query;
    while (true) {
        if (getline(in, query)) {
            std::unique_lock<std::mutex> lock(mtx);
            if (q.size() == looptimes / 200/200) {
                repo_not_full.wait(lock);
            }
            q.push(query);
            repo_not_empty.notify_all();
            //std::cout <<"read:"<<std::this_thread::get_id()<<"    "<< q.size()-1<<"---"<<q.size() << std::endl;
            lock.unlock();
        }
        else {
            spiltend = true;
            return;
        }
    }
}
void spilt_Data::spiltData_write() {
    while (true) {
        std::unique_lock<std::mutex> lock_read(mtx_read);
        std::unique_lock<std::mutex> lock(mtx);
        if (q.empty()) {
            if (spiltend) {
                lock_read.unlock();
                lock.unlock();
                break;
            }
            repo_not_empty.wait(lock);
        }
        std::string query = q.front();
        q.pop();
        repo_not_full.notify_all();
        //std::cout <<"write:"<<std::this_thread::get_id()<<"   "<< q.size() + 1 << "---" << q.size() << std::endl;
        lock.unlock();
        lock_read.unlock();
        std::hash<std::string> ss;
        int ha_sh = ss(query) % 200;
        std::unique_lock<std::mutex> lock_write1(mtx_write1);
        spilt[ha_sh] = spilt[ha_sh] + query + "\n";
        hash_url_cnt[ha_sh]++;
        if (hash_url_cnt[ha_sh] != looptimes / 200 / 200) {
            lock_write1.unlock();
        }
        else {
            std::string outstring = spilt[ha_sh];
            spilt[ha_sh] = "";
            hash_url_cnt[ha_sh] = 0;
            lock_write1.unlock();
            std::unique_lock<std::mutex> lock_write2(mtx_write2);
            std::ofstream out("../../../data/spiltData/" + std::to_string(ha_sh) + ".txt", std::ios::app);
            
            out << outstring;
            out.close();
            lock_write2.unlock();
        }
    }
}
void spilt_Data::spiltData_end() {
    for (int i = 0; i < 200; i++) {
        if (spilt[i].size() == 0)
            continue;
        std::ofstream out("../../../data/spiltData/" + std::to_string(i) + ".txt", std::ios::app);
        out << spilt[i] << std::endl;
        spilt[i] = "";
        out.close();
    }
}