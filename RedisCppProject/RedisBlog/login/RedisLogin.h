#pragma once
#include "RedisUtil.h"
#include <memory>
#include <string>


struct RedisLogin
{
    RedisLogin();
    ~RedisLogin();

    RedisResult Registration(RedisUtil& util, const UserInfo& user, const std::string& passwd);
    std::string Login(RedisUtil& util, const UserInfo& user, const std::string& passwd);
    RedisResult UnRegistration(RedisUtil& util, const UserInfo& user, const std::string& passwd);
    std::string& GetUserId();
private:
    RedisResult IsExist(RedisUtil& util);
    void MakeUserKey();
    void MakeEmail2UidKey();

    void MakeEmail2UidCmd(RedisOperator type,const UserInfo& user);
    void MakeUserInfoCmd(RedisOperator type,const UserInfo& user, const std::string& passwd);
private:
    std::string  re_command;
    std::string  user_key;
    std::string  email_2_uid_key;
    std::string  user_id;
};
