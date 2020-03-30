#ifndef URLTOPN_URL_H
#define URLTOPN_URL_H

#include <string>
#include <random>
#include <map>

//URL的用处是生成一个URL类，通过调用GetURL()将返回一个URL字符串
class Url {
public:
    Url();

    const std::string ch = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";//url的组成字符
    std::random_device rd;//随机数生成器
    std::string GetUrl();//创建一个新的URL
private:
    std::string GetHead();//得到URL的头部
    std::string GetBody();//得到URL的中部
    std::string GetTail();//得到URL的尾部
};

#endif