#include "RedisBlog.h"
#include "RedisGlobData.h"

using namespace std;

RedisBlog::RedisBlog(std::string& user_id):UserId(user_id)
{

}

RedisBlog::~RedisBlog()
{
    
}

RedisResult RedisBlog::CreateBlog(RedisUtil& util, UserInfo& user, std::string& content)
{
    auto& instance = RedisGlobDataRepo::GetInstance();
    std::string message_id = std::to_string(instance.GenBlogsId());
    MakeMessageKey(message_id);
    MakeMessageCmd(RedisOperator::SET, user, message_id, content);
    if(RedisResult::OK != util.ExecCommand(re_command))
    {
        cerr<<"create message failed, message_id is : "<<message_id<<endl;
        return RedisResult::ERROR;
    }
    return RedisResult::OK;
}

void RedisBlog::MakeMessageKey(std::string& message_id)
{
    message_key.assign("weibo::message::");
    message_key += message_id;
}

void RedisBlog::MakeMessageCmd(RedisOperator type, UserInfo& user, std::string& message_id, std::string& content)
{
    if(type == RedisOperator::SET)
    {
        re_command.assign("HMSET ");
    }
    else{
        re_command.assign("HGET ");
    }
    re_command += message_key;

    if (type == RedisOperator::SET)
    {
        re_command += " id:";
        re_command += message_id;
        re_command += "author:";
        re_command += GetUserId();
        re_command += "timer:";
        re_command += std::to_string(GetCurrentSysTimes());
        re_command += " content:";
        re_command += content;
    }
    else
    {
        re_command += " author";
    }
}