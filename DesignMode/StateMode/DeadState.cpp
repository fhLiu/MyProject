#include "DeadState.h"

DeadState::DeadState():ThreadState("死亡状态")
{
    std::cout<<"当前线程即将要灭亡了，任务已经完成了"<<std::endl;
}