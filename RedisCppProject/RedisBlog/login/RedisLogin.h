#pragma once
#include "RedisUtil.h"
#include <memory>
#include <string>

struct UserInfo
{
    UserInfo(std::string& name, std::string& email, UInt8 age):name(name),
                                                            email(email),
                                                            age(age){}
    std::string name;
    std::string email;
    UInt8       age;
};


struct RedisLogin
{
    RedisLogin();
    ~RedisLogin();

    RedisResult Registration(RedisUtil& util, const UserInfo& user, const std::string& passwd);
    std::string Login(RedisUtil& util, const UserInfo& user, const std::string& passwd);
    RedisResult UnRegistration(RedisUtil& util, const UserInfo& user, const std::string& passwd);
private:
    RedisResult IsExist(RedisUtil& util);
    void MakeUserKey(UInt64 uid);
    void MakeUserKey(std::string& uid);
    void MakeEmail2UidKey();

    void MakeEmail2UidCmd(RedisOperator type,const UserInfo& user, UInt64 uid);
    void MakeUserInfoCmd(RedisOperator type,const UserInfo& user, UInt64 uid, const std::string& passwd);
private:
    std::string  re_command;
    std::string  user_key;
    std::string  email_2_uid_key;
};
