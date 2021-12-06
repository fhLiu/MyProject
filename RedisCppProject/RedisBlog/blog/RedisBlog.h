#pragma once
#include <iostream>
#include "RedisUtil.h"
#include "gtest/gtest.h"
#include "hiredis/hiredis.h"

struct RedisBlog :UserId
{
    RedisBlog(std::string& user_id);
    ~RedisBlog();

    RedisResult CreateBlog(RedisUtil& util, UserInfo& user, std::string& content);

private:
    void MakeMessageKey(std::string& message_id);
    void MakeMessageCmd(RedisOperator type, UserInfo& user, std::string& message_id, std::string& content);

private:
    std::string re_command;
    std::string message_key;
};
