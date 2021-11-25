#include "RedisLogin.h"
#include "gtest/gtest.h"
#include "hiredis/hiredis.h"
#include "RedisUtil.h"
#include "RedisGlobData.h"

using namespace std;

struct RedisLoginTest : public testing::Test
{
    void SetUp()override
    {

    }

    void TearDown()override
    {
        auto& instance = RedisGlobDataRepo::GetInstance();
        instance.ClearAll();
    }
    RedisLoginTest():server_ip("127.0.0.1"),
                     server_port(6379),
                     clear_cmd("FLUSHALL"),
                     name("fhLiu"),
                     email("119493xxxx@qq.com"),
                     passwd("123456")
    {
    }
protected:
    std::string server_ip;
    UInt16      server_port;
    std::string clear_cmd;
    std::string name;
    std::string email;
    std::string passwd;

};


TEST_F(RedisLoginTest, redis_blogs_login_registration_new_user_successfull)
{
    RedisUtil util(server_ip, server_port);
    UserInfo user(name, email, 30);
    ASSERT_EQ(RedisResult::OK, util.ConnectRedis());
    RedisLogin login;
    EXPECT_EQ(login.Registration(util, user, passwd), RedisResult::OK);
    // util.ExecCommand(clear_cmd);
}

TEST_F(RedisLoginTest, redis_blogs_login_login_successfull)
{
    RedisUtil util(server_ip, server_port);
    UserInfo user(name, email, 30);
    ASSERT_EQ(RedisResult::OK, util.ConnectRedis());
    RedisLogin login;
    EXPECT_EQ(login.Login(util, user, passwd), std::to_string(1000000000000));
    // util.ExecCommand(clear_cmd);
}

TEST_F(RedisLoginTest, redis_blogs_login_unregistration_successfull)
{
    RedisUtil util(server_ip, server_port);
    UserInfo user(name, email, 30);
    ASSERT_EQ(RedisResult::OK, util.ConnectRedis());
    RedisLogin login;
    EXPECT_EQ(login.UnRegistration(util, user, passwd), RedisResult::OK);
    // util.ExecCommand(clear_cmd);
}