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
    MakeEmail2UidCmd("HGET ", user);
    if (RedisResult::OK == IsExist(util))
    {
        cerr<<"the email has registration, please login with it..."<<endl;
        return RedisResult::ERROR;
    }
    auto& instance = RedisGlobDataRepo::GetInstance();
    auto user_id = instance.GenUserId();
    //create email & user_id map
    MakeEmail2UidKey(user, user_id);
    cout<<re_command<<endl;
    if(RedisResult::OK != util.ExecCommand(re_command))
    {
        cerr<<"Registration failed...,create email to uid key failed.."<<endl;
        return RedisResult::ERROR;
    }

    //create user_id and user_info map
    MakeUserKey(user, user_id, passwd);
    cout<<re_command<<endl;
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

        re_command.assign("HGET ");
        re_command += user.email;
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
        result = RedisResult::ERROR;
    }
    util.FreeReply();
    return RedisResult::OK;
}

void RedisLogin::MakeUserKey(UInt64 uid)
{
    user_key.assign("weibo::user::");
    user_key += std::to_string(uid);

}

void RedisLogin::MakeEmail2UidKey(const UserInfo& user, UInt64 uid)
{
    email_2_uid_key.assign("weibo::email_to_uid");
}

void RedisLogin::MakeEmail2UidCmd(std::string type,const UserInfo& user, UInt64 uid)
{
    MakeEmail2UidKey();
    re_command.assign(type);
    re_command += email_2_uid_key;
    re_command += " ";
    re_command += user.email;
    re_command += " ";
    re_command += std::to_string(uid);
}

void RedisLogin::MakeUserInfoCmd(std::string type,const UserInfo& user, UInt64 uid, const std::string& passwd)
{
    MakeUserKey(uid);
    re_command.assign(type);
    re_command +=  user_key;
    re_command += " { id:";
    re_command += std::to_string(uid);
    re_command += ",name:";
    re_command += user.name;
    re_command += ",email:";
    re_command += user.email;
    re_command += ",password:";
    re_command += passwd;
    re_command += "}";
}