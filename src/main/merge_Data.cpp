#include "merge_Data.h"
#include<algorithm>
#include<iostream>
bool cmp(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
    return a.second > b.second;
}

void merge_Data::mergeData_init() {
    for (int i = 0; i < 200; i++) {
        unprocessed.push(i);
        processed.push(i);
    }
}
int count = 0;
void merge_Data::mergeData_Top100_easy() {
    while (true) {
        if (unprocessed.empty())return;
        std::unique_lock<std::mutex> read(mtx_read);
        int t = unprocessed.front();
        unprocessed.pop();
        read.unlock();
        std::ifstream file("../../../data/spiltData/" + std::to_string(t) + ".txt");
        std::map<std::string, int> mpp;
        std::string query;
        while (getline(file, query)) {
            mpp[query]++;
        }
        file.close();
        std::vector<std::pair<std::string, int>> v{mpp.begin(), mpp.end()};
        int len = std::min((int)v.size(), N);
        mpp.clear();
        std::partial_sort(v.begin(), v.begin() + len, v.end(), cmp);
        for (int i = 0; i < len; i++) {
            top[t].push_back(v[i]);
        }
        v.clear();
        v.shrink_to_fit();
        count++;
        system("cls");
        std::cout <<"当前进度:" <<count / 2.0 <<"%"<<std::endl;
    }
}

void merge_Data::mergeData_read_AND_write() {
    while (true) {
        int f1 = processed.front();
        processed.pop();
        int f2 = processed.front();
        processed.pop();
        int cnt = 0, l = 0, r = 0, ml = top[f1].size(), mr = top[f2].size();
        std::vector<std::pair<std::string, int>> now;
        while (cnt < N) {
            if (l == ml && r == mr)break;
            if (l == ml) {
                now.push_back(top[f2][r]);
                r++;
                cnt++;
                continue;
            }
            if (r == mr) {
                now.push_back(top[f1][l]);
                l++;
                cnt++;
                continue;
            }
            if (top[f1][l].second >= top[f2][r].second) {
                now.push_back(top[f1][l]);
                l++;
                cnt++;
            }
            else if (top[f1][l].second < top[f2][r].second) {
                now.push_back(top[f2][r]);
                r++;
                cnt++;
            }
        }
        top[f1].clear();
        top[f1].shrink_to_fit();
        top[f2].clear();
        top[f2].shrink_to_fit();
        top[std::min(f1, f2)] = now;
        processed.push(std::min(f1, f2));
        times++;
        if (times == 199) {
            return;
        }
    }
}

void merge_Data::mergeData_Top100_finish() {
    std::ofstream file("../../../data/spiltData/ans.txt");
    for(auto i:top[0]){
        file<<i.first<<"  "<<i.second<<std::endl;
    }
    file.close();
}