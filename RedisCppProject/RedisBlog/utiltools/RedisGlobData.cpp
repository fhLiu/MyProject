#include "RedisGlobData.h"

RedisGlobDataRepo::RedisGlobDataRepo():user_id(1000000000000),
                                       blog_id(1),
                                       comment_id(0)
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