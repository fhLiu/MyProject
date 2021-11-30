#include "RedisTimeline.h"

RedisTimeline::RedisTimeline(RedisUtil& util, std::string& user_id):re_command(""),
                                                                    re_key(""),
                                                                    util(util)
{

}

RedisTimeline::~RedisTimeline()
{
    
}


RedisResult RedisTimeline::CustomPush(std::string& user_id, std::string& message_id, std::string& time_mm)
{
    MakeCustomTimelineKey(user_id);
    MakePushCmd(user_id, time_mm, message_id);
    push(message_id, time_mm);
    return RedisResult::OK;
}

RedisResult RedisTimeline::PersonalPush(std::string& user_id, std::string& message_id, std::string& time_mm)
{
    MakePersonalTimelineKey(user_id);
    MakePushCmd(user_id, time_mm, message_id);
    push(message_id, time_mm);
    return RedisResult::OK;
}

RedisResult RedisTimeline::BroadCast(std::string& user_id, std::string& message_id)
{

    return RedisResult::OK;
}

RedisResult RedisTimeline::CustomPaging(std::string& user_id, int num, int count)
{
    MakeCustomTimelineKey(user_id);
    Paging(num, count);
    return RedisResult::OK;
}

RedisResult RedisTimeline::PersonalPaging(std::string& user_id, int num, int count)
{
    MakePersonalTimelineKey(user_id);
    Paging(num, count);
    return RedisResult::OK;
}

RedisResult RedisTimeline::push(std::string& message_id, std::string& time_m)
{
    if(RedisResult::OK != util.ExecCommand(re_command))
    {
        return RedisResult::ERROR;
    }

    return RedisResult::OK;
}

RedisResult RedisTimeline::Paging(int num, int count)
{
    int start_index = (num - 1) * count;
    int end_index = num * count - 1;
    MakePagingCmd(start_index, end_index);
    if (RedisResult::OK != util.ExecCommand(re_command))
    {
        return RedisResult::ERROR;
    }
    
    return RedisResult::OK;
}

void RedisTimeline::MakeCustomTimelineKey(std::string& user_id)
{
    re_key.assign("weibo::user::");
    re_key +=user_id;
    re_key += "::custom_timeline";
}

void RedisTimeline::MakePersonalTimelineKey(std::string& user_id)
{
    re_key.assign("weibo::user::");
    re_key += user_id;
    re_key += "::personal_timeline";
}

void RedisTimeline::MakePushCmd(std::string& user_id, std::string& time_m, std::string& message_id)
{
    re_command.assign("ZADD ");
    re_command += re_key;
    re_command += " ";
    re_command += time_m;
    re_command += " ";
    re_command += message_id;
}

void RedisTimeline::MakePagingCmd(int start_index, int end_index)
{
    re_command.assign("ZREVRANGE ");
    re_command += re_key;
    re_command += " ";
    re_command += std::to_string(start_index);
    re_command += " ";
    re_command += std::to_string(end_index);
}