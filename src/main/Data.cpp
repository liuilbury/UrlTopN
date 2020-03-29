#include <iostream>
#include<functional>
#include "Data.h"
void Data::createData(std::string filename, int size) {
    looptimes = 1024 * 1024 * size / urlsize;
    std::ofstream testdata(filename+"/data.txt");
    Url *url=new Url();
    for(int i=1;i<=looptimes;i++){
        testdata<<url->GetUrl()<<std::endl;
    }
    testdata.close();
}