#include "Url.h"
#include <random>
Url::Url() {}
std::string Url::GetUrl() {
    return Url::GetHead()+Url::GetBody()+Url::GetTail();
}
std::string Url::GetHead() {
    unsigned int t=rd()%2;
    if(t)return "Http://";
    else return "Https://";
}
std::string Url::GetBody() {
    unsigned int start=rd()%50;
    unsigned int len=rd()%2+11;
    return ch.substr(start,len);
}
std::string Url::GetTail() {
    return ".com/problem_pid="+std::to_string(rd()%100);
}