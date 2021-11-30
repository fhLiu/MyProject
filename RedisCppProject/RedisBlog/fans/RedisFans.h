#pragma once

#include <vector>
#include "RedisUtil.h"

struct RedisFans
{
    RedisFans(RedisUtil& util);
    ~RedisFans();

    RedisResult Follow(std::string& fans, std::string& target_id);
    bool IsFollow(std::string& fans, std::string& target_id);
    bool IsFollowEachOther(std::string& fans, std::string& target_id);
    std::vector<std::string>& GetAllFollows(std::string& user_id);
    std::vector<std::string>& GetAllFans(std::string& user_id);
    std::vector<std::string>& GetCommonFollows(std::string& user_id, std::string& target_id);

    void Clear();

private:
    void MakeFollowKey(std::string& user_id);
    void MakeFansKey(std::string& fans_id);
    void MakeFollowCmd(std::string& fans_id);
    void MakeFansCms(std::string& target_id);

private:
    std::string re_command;
    std::string re_key;
    RedisUtil& util;
    std::vector<std::string> vec;
};
