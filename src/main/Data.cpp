#include <iostream>
#include<functional>
#include "Data.h"
void Data::createData(std::string filename, int size) {
    looptimes = 1024 * 1024 * size / urlsize;//size的单位是M,urlsize的单位是B,所以需要1024*1024
    std::ofstream testdata(filename+"\\data.txt");
    Url *url=new Url();
    for(int i=1;i<=looptimes;i++){
        testdata<<url->GetUrl()<<std::endl;
    }
    testdata.close();
}