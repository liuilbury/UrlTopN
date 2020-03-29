#ifndef URLTOPN_URL_H
#define URLTOPN_URL_H
#include <string>
#include <random>
#include <map>
class Url {
public:
    Url();
    const std::string ch = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";//url的组成字符
    std::random_device rd;
    std::string GetUrl();
private:
    std::string GetHead();
    std::string GetBody();
    std::string GetTail();
};
#endif