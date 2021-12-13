#include "MemGirlStack.h"

MemGirlStack::MemGirlStack():index(0)
{

}

bool MemGirlStack::Push(MemGirls& girl)
{
    if (index >=4)
    {
        std::cerr<<"相亲人数太多，想要更多，请升级会员等级！！"<<std::endl;
        return false;
    }
    
    history.push_back(girl);
    index++;
    return true;
}

MemGirls* MemGirlStack::Pop()
{
    if (index <= 0 )
    {
        std::cerr<<"不能再回撤了，已经到最开始的地方了！！"<<std::endl;
        return nullptr;
    }
    
    return &history[--index];
}