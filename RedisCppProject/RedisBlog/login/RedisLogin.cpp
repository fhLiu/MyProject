#include "RedisLogin.h"
#include "RedisGlobData.h"

using namespace std;

RedisLogin::RedisLogin()
{

}

RedisLogin::~RedisLogin()
{
    
}

RedisResult RedisLogin::Registration(RedisUtil& util, std::string& email)
{
    if (RedisResult::OK == IsExist(util, email))
    {
        cerr<<"the email has registration, please login with it..."<<endl;
        return RedisResult::ERROR;
    }
    auto& instance = RedisGlobDataRepo::GetInstance();
    auto user_id = instance.GenUserId();
    re_command.assign("HSET ");
    re_command += email;
    re_command += " ";
    re_command += std::to_string(user_id);
    if(RedisResult::OK != util.ExecCommand(re_command))
    {
        cerr<<"Registration failed...,exec command failed.."<<endl;
        return RedisResult::ERROR;
    }
    cout<<"Registration successful..."<<endl;
    return RedisResult::OK;
}

std::string RedisLogin::Login(RedisUtil& util, std::string& email)
{
    std::string emp("");
    do
    {
        if (RedisResult::OK != IsExist(util, email))
        {
            cerr<<"the email not registration, please registration with it..."<<endl;
            break;
        }

        re_command.assign("HGET ");
        re_command += email;
        if( RedisResult::OK !=util.ExecCommand(re_command))
        {
            break;
        }
        auto reply = util.GetReply();
        if(reply->type != REDIS_REPLY_STRING )
        {
            cerr<<"result type not string, type is : "<<reply->type<<endl;
            break;
        }
        emp.assign(reply->str, reply->len);

    } while (0);
    
    return emp;
}

RedisResult RedisLogin::UnRegistration(RedisUtil& util, std::string& email)
{

    return RedisResult::OK;
}

RedisResult RedisLogin::IsExist(RedisUtil& util, std::string& email)
{
    RedisResult result = RedisResult::OK;
    re_command.assign("HGET ");
    re_command += email;
    if(RedisResult::OK != util.ExecCommand(re_command))
    {
        return RedisResult::ERROR;
    }
    auto reply = util.GetReply();

    if (reply->type == REDIS_REPLY_NIL)
    {
        result = RedisResult::ERROR;
    }
    util.FreeReply();
    return RedisResult::OK;
}