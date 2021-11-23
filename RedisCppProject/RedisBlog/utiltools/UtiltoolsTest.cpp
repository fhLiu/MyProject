#include "RedisUtil.h"
#include "RedisGlobData.h"
#include "gtest/gtest.h"
#include "hiredis/hiredis.h"

using namespace std;

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
