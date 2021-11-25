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
        return RedisResult::OK;
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
    std::string struid("");
    redisReply *reply = nullptr;
    do
    {
        MakeEmail2UidCmd(RedisOperator::GET, user, 0);
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
        reply = util.GetReply();
        if(reply->type != REDIS_REPLY_STRING )
        {
            cerr<<"result type not string, type is : "<<reply->type<<endl;
            break;
        }
        emp.assign(reply->str, reply->len);
        struid.assign(reply->str, reply->len);
        util.FreeReply();
        reply = nullptr;

        //check user info
        re_command.assign("HMGET ");
        re_command += "weibo::user::";
        re_command += emp;
        re_command += " password";
        struid = std::move(emp);
        if( RedisResult::OK !=util.ExecCommand(re_command))
        {
            break;
        }
        reply = util.GetReply();
        if (reply->type == REDIS_REPLY_NIL || reply->type != REDIS_REPLY_ARRAY)
        {
           cerr<<"resp type is "<<reply->type<<endl;
           break;
        }
        for(UInt8 index = 0; index < reply->elements; index++)
        {
            if(reply->element[index]->type == REDIS_REPLY_STRING)
            {
                emp.assign(reply->element[index]->str, reply->element[index]->len);
            }
        }

        if (passwd != emp)
        {
            cerr<<"user "<<user.name<<" passwd is error, please input again"<<endl;
            emp.clear();
            break;
        }
        emp = std::move(struid);
    } while (0);

    util.FreeReply();
    reply = nullptr;
    return emp;
}

RedisResult RedisLogin::UnRegistration(RedisUtil& util, const UserInfo& user, const std::string& passwd)
{
    std::string uid = Login(util, user, passwd);
    RedisResult result = RedisResult::OK;
    do
    {
        if(uid.empty())
        {
            cerr<<"Unregistration failed..."<<endl;
            result = RedisResult::OK;
            break;
        }

        //clear user info map
        re_command.assign("HDEL ");
        MakeUserKey(uid);
        re_command += user_key;
        re_command += " id name email password";
        if(RedisResult::ERROR == util.ExecCommand(re_command))
        {
            cerr<<"del user info map error..."<<uid<<endl;
            result = RedisResult::ERROR;
        }
        util.FreeReply();

        //clear email_to_uid
        MakeEmail2UidKey();
        re_command.assign("HDEL ");
        re_command += email_2_uid_key;
        re_command += " ";
        re_command += user.email;
        if(RedisResult::ERROR == util.ExecCommand(re_command))
        {
            cerr<<"del email to uid map error..."<<uid<<endl;
            result = RedisResult::ERROR;
        }
        util.FreeReply();

        //TODO clear blog comment timeline fans
    } while (0);
    

    return result;
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

void RedisLogin::MakeUserKey(std::string& uid)
{
    user_key.assign("weibo::user::");
    user_key += uid;
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
        re_command.assign("HSETNX ");
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
        re_command += " id name email";

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