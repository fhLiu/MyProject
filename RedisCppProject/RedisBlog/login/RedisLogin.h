#pragma once
#include "RedisUtil.h"
#include <memory>
#include <string>

struct RedisLogin
{
    RedisLogin();
    ~RedisLogin();

    RedisResult Registration(RedisUtil& util, std::string& email);
    std::string Login(RedisUtil& util,std::string& email);
    RedisResult UnRegistration(RedisUtil& util, std::string& email);
private:
    RedisResult IsExist(RedisUtil& util, std::string& email);
private:
    std::string  re_command;
};
