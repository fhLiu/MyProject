#include "RedisGlobData.h"

namespace {
    constexpr UInt64 USERID_INIT = 1000000000000;
    constexpr UInt64 BLOG_INIT = 1;
    constexpr UInt64 COMMEMT_INIT = 0;
}

RedisGlobDataRepo::RedisGlobDataRepo():user_id(USERID_INIT),
                                       blog_id(BLOG_INIT),
                                       comment_id(COMMEMT_INIT)
{

}

UInt64 RedisGlobDataRepo::GenUserId()
{
    return user_id++;
}

UInt64 RedisGlobDataRepo::GenBlogsId()
{
    std::lock_guard<std::mutex> lck(blog_mutex);

    return blog_id++;
}

UInt64 RedisGlobDataRepo::GenCommentId()
{
    std::lock_guard<std::mutex> lck(comment_mutex);
 
    return comment_id++;
}

void RedisGlobDataRepo::ClearAll()
{
    user_id = USERID_INIT;
    blog_id = BLOG_INIT;
    comment_id = COMMEMT_INIT;
}