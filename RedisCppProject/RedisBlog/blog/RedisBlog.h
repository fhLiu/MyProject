#pragma once
#include <iostream>
#include "RedisUtil.h"
#include "gtest/gtest.h"
#include "hiredis/hiredis.h"

struct RedisBlog
{
    RedisBlog();
    ~RedisBlog();

    RedisResult CreateBlog(RedisUtil& util, UserInfo& user);

private:
    void MakeMessageKey(std::string& message_id);
    void MakeMessageCmd(RedisOperator type, UserInfo& user);

private:
    std::string re_command;
    std::string message_key;
};
