#include "RedisLogin.h"
#include "gtest/gtest.h"
#include "hiredis/hiredis.h"
#include "RedisUtil.h"

using namespace std;

struct RedisLoginTest : public testing::Test
{
    void SetUp()override
    {

    }

    void TearDown()override
    {

    }
    RedisLoginTest():server_ip("127.0.0.1"),server_port(6379){}
protected:
    std::string server_ip;
    UInt16      server_port;
};


TEST_F(RedisLoginTest, redis_blogs_login_registration_new_user_successfull)
{
    std::string email("119493xxxx@qq.com");
    RedisUtil util(server_ip, server_port);
    RedisLogin login;
    EXPECT_EQ(login.Registration(util, email), RedisResult::OK);
}