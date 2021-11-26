#include "RedisBlog.h"



RedisBlog::RedisBlog()
{

}

RedisBlog::~RedisBlog()
{
    
}

RedisResult RedisBlog::CreateBlog(RedisUtil& util, UserInfo)
{

    return RedisResult::OK;
}

void RedisBlog::MakeMessageKey(std::string& message_id)
{
    message_key.assign("weibo::message::");
    message_key += message_id;
}

void RedisBlog::MakeMessageCmd(RedisOperator type, UserInfo& user)
{

}