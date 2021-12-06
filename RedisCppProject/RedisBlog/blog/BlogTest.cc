#include "RedisBlog.h"
#include "RedisUtil.h"
#include "RedisLogin.h"
#include "gtest/gtest.h"
#include "hiredis/hiredis.h"

using namespace std;

struct RedisBlogsTest : public testing::Test
{
    void SetUp()override
    {

    }

    void TearDown()override
    {
        auto& instance = RedisGlobDataRepo::GetInstance();
        instance.ClearAll();
    }

private:


};


TEST_F(RedisBlogsTest, redis_blogs_blog_keys_create_successfull)
{
    std::string server_ip("127.0.0.1");
    UInt16      server_port(6637);
    std::string clear_cmd("FLUSHALL");
    std::string name("fgLiu");
    std::string email("119493xxxx@qq.com");
    std::string passwd("123456");
    RedisUtil util(server_ip, server_port);
    UserInfo user(name, email, 30);
    ASSERT_EQ(RedisResult::OK, util.ConnectRedis());
    RedisLogin login;
    EXPECT_EQ(login.Login(util, user, passwd), std::to_string(1000000000000));
    RedisBlog blog(login.GetUserId());
    std::string content("This is a test program, has many issue, you can change it if you find, please tell me the position, Thanks!!");
    EXPECT_EQ(blog.CreateBlog(util, user, content), RedisResult::OK);
}