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
    RedisLoginTest():server_ip("127.0.0.1"),server_port(6379){}
protected:
    std::string server_ip;
    UInt16      server_port;
};


TEST_F(RedisLoginTest, redis_blogs_login_registration_new_user_successfull)
{
    std::string email("119493xxxx@qq.com");
    std::string name("fhLiu");
    std::string passwd("123456");
    UserInfo user(name, email, 30);
    RedisUtil util(server_ip, server_port);
    ASSERT_EQ(RedisResult::OK, util.ConnectRedis());
    RedisLogin login;
    EXPECT_EQ(login.Registration(util, user, passwd), RedisResult::OK);
}