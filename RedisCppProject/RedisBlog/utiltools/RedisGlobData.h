#include "BaseSingleton.h"
#include "RedisUtil.h"
#include <mutex>

RedisSingleton(RedisGlobDataRepo)
{

    friend BaseSingleton<RedisGlobDataRepo>;
    UInt64 GenUserId();
    UInt64 GenBlogsId();
    UInt64 GenCommentId();

private:
    RedisGlobDataRepo();

private:
    UInt64 user_id;
    UInt64 blog_id;
    UInt64 comment_id;
    std::mutex blog_mutex;
    std::mutex comment_mutex;
};
