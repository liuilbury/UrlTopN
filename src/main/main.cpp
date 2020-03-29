#include <iostream>
#include<thread>
#include "spilt_Data.h"
#include "merge_Data.h"
int n, size;
std::string filename;

void GetInfo() {
    std::cout << "请输入文件地址" << std::endl;
    std::cin >> filename;
    std::cout << "请输入文件大小" << std::endl;
    std::cin >> size;
}

void Create() {
    GetInfo();
    Data().createData(filename, size);
    std::cout << "生成文件到:"+filename+"/data.txt" << std::endl;
}

void SpiltFile() {
    spilt_Data data;
    data.spiltData_init();
    data.filename = filename;
    data.looptimes = 1024 * 1024 * size / data.urlsize;
    std::cout << "拆分文件中..." << std::endl;
    //单线程读多线程写
    std::thread read(&spilt_Data::spiltData_read, &data);
    std::thread write1(&spilt_Data::spiltData_write, &data);
    std::thread write2(&spilt_Data::spiltData_write, &data);
    std::thread write3(&spilt_Data::spiltData_write, &data);
    std::thread write4(&spilt_Data::spiltData_write, &data);
    read.join();
    write1.join();
    write2.join();
    write3.join();
    write4.join();
    std::cout << "拆分文件完成" << std::endl;
    //最后的剩余url进行写入
    std::thread End(&spilt_Data::spiltData_end, &data);
    End.join();
}

void MergeFile(int n) {
    merge_Data data;
    data.N=n;
    data.mergeData_init();
    std::cout << "解析文件中" << std::endl;
    std::thread read1(&merge_Data::mergeData_Top100_easy, &data);
    std::thread read2(&merge_Data::mergeData_Top100_easy, &data);
    std::thread read3(&merge_Data::mergeData_Top100_easy, &data);
    read1.join();
    read2.join();
    read3.join();
    std::cout << "解析文件完成" << std::endl;
    data.mergeData_read_AND_write();
    std::cout << "合并完成" << std::endl;
    data.mergeData_Top100_finish();
    std::cout << "解析文件完成" << std::endl;
    for (int i = 0; i < data.N; i++) {
        std::cout << data.top[0][i].first <<"   count:"<< data.top[0][i].second<<std::endl;
    }
}
void run() {
    GetInfo();
    std::cout << "请输入需要前多少个URL" << std::endl;
    int n;
    std::cin >> n;
    SpiltFile();
    MergeFile(n);
}
int main(int argc, char *argv[]) {
    std::cout << "1.创建一个URL大文件" << std::endl;
    std::cout << "2.求出现次数TopN的url" << std::endl;
    std::cout << "3.退出" << std::endl;
    std::cin >> n;
    if (n == 1) {
        Create();
    }
    else if (n == 2) {
        run();
    }
    return 0;
}
