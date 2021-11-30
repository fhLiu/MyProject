#include "RedisFans.h"


RedisFans::RedisFans(RedisUtil& util) : re_command(""),
                         re_key(""),
                         util(util)
{

}

RedisFans::~RedisFans()
{
    
}

RedisResult RedisFans::Follow(std::string& fans, std::string& target_id)
{
    //add fans to target's fans list
    MakeFansKey(target_id);
    MakeFollowCmd(fans);
    if ( RedisResult::OK != util.ExecCommand(re_command))
    {
        return RedisResult::ERROR;
    }
    util.FreeReply();

    //add target to fans's following list
    MakeFollowKey(fans);
    MakeFansCms(target_id);
    if (RedisResult::OK != util.ExecCommand(re_command))
    {
        return RedisResult::ERROR;
    }
    util.FreeReply();
    
    return RedisResult::OK;
}

bool RedisFans::IsFollow(std::string& fans, std::string& target_id)
{
    MakeFollowKey(fans);
    MakeFollowCmd(target_id);
    if (RedisResult::OK != util.ExecCommand(re_command))
    {
        return false;
    }
    return true;
}

bool RedisFans::IsFollowEachOther(std::string& fans, std::string& target_id)
{
    bool result = IsFollow(fans, target_id) && IsFollow(target_id, fans);
    return result;
}

std::vector<std::string>& RedisFans::GetAllFollows(std::string& user_id)
{
    MakeFollowKey(user_id);
    MakeFollowCmd(user_id);
    if (RedisResult::OK != util.ExecCommand(re_command))
    {
        return vec;
    }
    return vec;
}

std::vector<std::string>& RedisFans::GetAllFans(std::string& user_id)
{
    MakeFollowKey(user_id);
    MakeFollowCmd(user_id);
    if (RedisResult::OK != util.ExecCommand(re_command))
    {
        return vec;
    }
    return vec;
}

std::vector<std::string>& RedisFans::GetCommonFollows(std::string& user_id, std::string& target_id)
{
    MakeFollowKey(user_id);
    MakeFollowKey(target_id);
    if (RedisResult::OK != util.ExecCommand(re_command))
    {
        return vec;
    }
    return vec;
}

void RedisFans::MakeFollowKey(std::string& user_id)
{
    re_key.assign("weibo::user::");
    re_key += user_id;
    re_key += "::following";
}

void RedisFans::MakeFansKey(std::string& fans_id)
{
    re_key.assign("weibo::user::");
    re_key += fans_id;
    re_key += "::fans";
}

void RedisFans::MakeFollowCmd(std::string& fans_id)
{
    re_command.assign("SADD ");
    re_command += re_key;
    re_command += " ";
    re_command += fans_id;
}

void RedisFans::MakeFansCms(std::string& target_id)
{
    re_command.assign("SADD ");
    re_command += re_key;
    re_command += " ";
    re_command += target_id;
}

void RedisFans::Clear()
{
    vec.clear();
}