#pragma once
#include <iostream>
#include "RedisUtil.h"


struct RedisTimeline
{
    RedisTimeline(RedisUtil& util, std::string& user_id);
    ~RedisTimeline();

    RedisResult CustomPush(std::string& user_id, std::string& message_id, std::string& time_m);
    RedisResult PersonalPush(std::string& user_id, std::string& message_id, std::string& time_m);
    RedisResult BroadCast(std::string& user_id, std::string& message_id);
    RedisResult CustomPaging(std::string& user_id, int num, int count);
    RedisResult PersonalPaging(std::string& user_id, int num, int count);

private:
    RedisResult push(std::string& message_id, std::string& time_m);
    RedisResult Paging(int num, int count);
    void MakeCustomTimelineKey(std::string& user_id);
    void MakePersonalTimelineKey(std::string& user_id);

    void MakePushCmd(std::string& user_id, std::string& time_m, std::string& message_id);
    void MakePagingCmd(int start_index, int end_index);

private:
    std::string re_command;
    std::string re_key;
    RedisUtil&  util;
};
