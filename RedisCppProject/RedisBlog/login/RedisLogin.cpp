#include "RedisLogin.h"
#include "RedisGlobData.h"

using namespace std;

RedisLogin::RedisLogin():re_command(""),
                         user_key(""),
                         email_2_uid_key("")
{

}

RedisLogin::~RedisLogin()
{
    
}

RedisResult RedisLogin::Registration(RedisUtil& util, const UserInfo& user, const std::string& passwd)
{
    MakeEmail2UidCmd(RedisOperator::GET, user, 0);
    if (RedisResult::NIL != IsExist(util))
    {
        cerr<<"the email has registration, please login with it..."<<endl;
        return RedisResult::ERROR;
    }
    auto& instance = RedisGlobDataRepo::GetInstance();
    auto user_id = instance.GenUserId();
    //create email & user_id map
    MakeEmail2UidCmd(RedisOperator::SET, user, user_id);

    if(RedisResult::OK != util.ExecCommand(re_command))
    {
        cerr<<"Registration failed...,create email to uid key failed.."<<endl;
        return RedisResult::ERROR;
    }

    //create user_id and user_info map
    MakeUserInfoCmd(RedisOperator::SET, user, user_id, passwd);

    if(RedisResult::OK != util.ExecCommand(re_command))
    {
        cerr<<"Registration failed...,create user info failed.."<<endl;
        return RedisResult::ERROR;
    }
    cout<<"Registration successful..."<<endl;
    return RedisResult::OK;
}

std::string RedisLogin::Login(RedisUtil& util, const UserInfo& user, const std::string& passwd)
{
    std::string emp("");
    do
    {
        if (RedisResult::OK != IsExist(util))
        {
            cerr<<"the email not registration, please registration with it..."<<endl;
            break;
        }

        MakeEmail2UidCmd(RedisOperator::GET, user, 0);
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

RedisResult RedisLogin::UnRegistration(RedisUtil& util, const UserInfo& user, const std::string& passwd)
{

    return RedisResult::OK;
}

RedisResult RedisLogin::IsExist(RedisUtil& util)
{
    RedisResult result = RedisResult::OK;

    if(RedisResult::OK != util.ExecCommand(re_command))
    {
        return RedisResult::ERROR;
    }
    auto reply = util.GetReply();

    if (reply->type == REDIS_REPLY_NIL)
    {
        result = RedisResult::NIL;
    }
    util.FreeReply();
    return result;
}

void RedisLogin::MakeUserKey( UInt64 uid)
{
    user_key.assign("weibo::user::");
    user_key += std::to_string(uid);

}

void RedisLogin::MakeEmail2UidKey()
{
    email_2_uid_key.assign("weibo::email_to_uid");
}

void RedisLogin::MakeEmail2UidCmd(RedisOperator type,const UserInfo& user, UInt64 uid)
{
    MakeEmail2UidKey();
    if (type == RedisOperator::GET)
    {
        re_command.assign("HGET ");
    }
    else{
        re_command.assign("HSET ");
    }
    re_command += email_2_uid_key;
    re_command += " ";
    re_command += user.email;
    
    if (type == RedisOperator::SET)
    {
        re_command += " ";
        re_command += std::to_string(uid);
    }
}

void RedisLogin::MakeUserInfoCmd(RedisOperator type,const UserInfo& user, UInt64 uid, const std::string& passwd)
{
    MakeUserKey(uid);
    if (type == RedisOperator::GET)
    {
        re_command.assign("HMGET ");
        re_command +=  user_key;
        re_command += " id name email"

    }else{
        re_command.assign("HMSET ");
        re_command +=  user_key;
        re_command += " id ";
        re_command += std::to_string(uid);
        re_command += " name ";
        re_command += user.name;
        re_command += " email ";
        re_command += user.email;
        re_command += " password ";
        re_command += passwd;
        re_command += "";
    }
    

}