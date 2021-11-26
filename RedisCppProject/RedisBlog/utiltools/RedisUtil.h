#pragma once
#include <iostream>
#include <chrono>
#include "hiredis/hiredis.h"

using UInt64 = unsigned long long;
using SInt64 = signed long long;
using UInt32 = unsigned int;
using SInt32 = int;
using UInt16 = unsigned short;
using SInt16 = short;
using UInt8  = unsigned char;
using SInt8  = char;

enum struct RedisResult : UInt8
{OK, NIL, ERROR};

enum struct RedisOperator : UInt8
{GET, SET};

struct UserInfo
{
    UserInfo(std::string& name, std::string& email, UInt8 age):name(name),
                                                            email(email),
                                                            age(age){}
    std::string name;
    std::string email;
    UInt8       age;
};

struct RedisUtil
{
    RedisUtil(std::string& ip_addr, UInt16 port);
    ~RedisUtil();

    RedisResult ConnectRedis();
    RedisResult ExecCommand(const std::string& re_command);
    redisReply* GetReply()const;
    void FreeReply();
    void FreeCtxt();

private:
    std::string  server_ip;
    UInt16       port;
    redisContext   *ctxt;
    redisReply     *reply;
};

long long GetCurrentSysTimes();
