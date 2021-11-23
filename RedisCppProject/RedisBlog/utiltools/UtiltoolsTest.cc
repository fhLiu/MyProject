#include "RedisUtil.h"
#include "RedisGlobData.h"
#include <thread>
#include <mutex>
#include "gtest/gtest.h"
#include "hiredis/hiredis.h"

using namespace std;
constexpr UInt8 MAX_THREAD_NUMS = 200;

struct RedisUtiltoolsTest : public testing::Test
{
    void SetUp()override
    {
        ctxt = redisConnect("127.0.0.1", 6379);
    }

    void TearDown()override
    {
        if (reply)
        {
           freeReplyObject(reply);
           reply = nullptr;
        }
        
        if (ctxt)
        {
            redisFree(ctxt);
            ctxt = nullptr;
        }
        
    }
    RedisUtiltoolsTest():ctxt(nullptr), 
                         reply(nullptr),
                         rediscommand("")
    {

    }
protected:
    redisContext   *ctxt;
    redisReply     *reply;
    std::string     rediscommand;
};


TEST_F(RedisUtiltoolsTest, redis_global_repo_is_safety)
{
    EXPECT_NE(ctxt, nullptr);
}

TEST_F(RedisUtiltoolsTest, redis_global_repo_is_unique)
{
    auto& instance = RedisGlobDataRepo::GetInstance();
    auto user_id = instance.GenUserId();
    auto first_blog_id = instance.GenBlogsId();
    auto first_comment_id = instance.GenCommentId();
    UInt64 valid_first_user_id = 1000000000000;
    UInt64 valid_first_blog_id = 1;
    UInt64 valid_first_comment_id = 0;
    EXPECT_EQ(user_id, valid_first_user_id);
    EXPECT_EQ(first_blog_id, valid_first_blog_id);
    EXPECT_EQ(first_comment_id, valid_first_comment_id);

    user_id = instance.GenUserId();
    EXPECT_EQ(user_id, valid_first_user_id+1);
    EXPECT_NE(user_id, valid_first_user_id+2);
}

void TestMutilThreadSafety()
{
    auto& instance = RedisGlobDataRepo::GetInstance();
    instance.GenCommentId();
}

TEST_F(RedisUtiltoolsTest, redis_global_repo_is_unique_when_mutil_thread_scene)
{
    
    std::thread tharr[MAX_THREAD_NUMS];

    for (UInt8 i = 0; i < MAX_THREAD_NUMS; i++)
    {
        tharr[i] = std::move(std::thread(TestMutilThreadSafety));
    }

    for (UInt8 i = 0; i < MAX_THREAD_NUMS; i++)
    {
        tharr[i].join();
    }
    auto& instance = RedisGlobDataRepo::GetInstance();
    UInt64 last_id = MAX_THREAD_NUMS + 1;
    EXPECT_EQ(instance.GenCommentId(), last_id);
    
}
