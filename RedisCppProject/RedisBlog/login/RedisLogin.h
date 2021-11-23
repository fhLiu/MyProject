#pragma once
#include "RedisUtil.h"

struct RedisLogin
{
    RedisLogin();
    ~RedisLogin();

    RedisResult Registration(std::string& email);
    RedisResult Login(std::string& email);
private:
    RedisResult IsExist();
};
