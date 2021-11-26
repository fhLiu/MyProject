#include "RedisUtil.h"

using namespace std;


RedisUtil::RedisUtil(std::string& ip_addr, UInt16 port):
                                server_ip(ip_addr), port(port),
                                ctxt(nullptr), reply(nullptr)
{

}

RedisUtil::~RedisUtil()
{
    FreeReply();
    FreeCtxt();
}

RedisResult RedisUtil::ConnectRedis()
{
    ctxt = redisConnect(server_ip.c_str(), port);
    if (ctxt == nullptr || ctxt->err != 0)
    {
        cerr<<"redis connected failed, cause is : "<<ctxt->errstr<<endl;
        return RedisResult::ERROR;
    }
    
    cout<<"Redis connected successful..."<<endl;
    return RedisResult::OK;
}

RedisResult RedisUtil::ExecCommand(const std::string& re_command)
{
    cout<<"exec command is : "<<re_command<<endl;
    reply = (redisReply*)redisCommand(ctxt, re_command.c_str());
    if (reply == nullptr || reply->type == REDIS_REPLY_ERROR)
    {
        cerr<<"exec command failed...";
        if (reply != nullptr)
        {
            cerr<<", cause is : "<<reply->str<<endl;
        }else{
            cerr<<endl;
        }
        return RedisResult::ERROR;
    }
    if (reply->type == REDIS_REPLY_NIL)
    {
        cout<<"not data..."<<endl;
    }

    return RedisResult::OK;
}

redisReply* RedisUtil::GetReply()const
{
    return reply;
}

void RedisUtil::FreeReply()
{
    if(reply)
    {
        freeReplyObject(reply);
        reply = nullptr;
    }
}

void RedisUtil::FreeCtxt()
{
    if (ctxt)
    {
        redisFree(ctxt);
        ctxt = nullptr;
    }
}

long long GetCurrentSysTimes()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}