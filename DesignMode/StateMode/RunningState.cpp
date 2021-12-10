#include "RunningState.h"
#include "BlockedState.h"
#include "DeadState.h"

RunningState::RunningState():ThreadState("运行状态")
{
    std::cout<<"创建运行状态，当前处于运行状态！"<<std::endl;
}

void RunningState::Suspend(ThreadContext& ctxt)
{
    std::cout<<"当前线程需要挂起，即将进入阻塞状态！"<<std::endl;
    if (ctxt.GetState()->GetName() != "运行状态")
    {
        std::cerr<<"当前状态不处于运行状态，不能挂起，当前状态为："<<ctxt.GetState()->GetName()<<std::endl;
        return;
    }
    ctxt.SetState(new BlockedState());
    return;
}

void RunningState::Stop(ThreadContext& ctxt)
{
    std::cout<<"当前线程需要结束，即将进入死亡状态！"<<std::endl;
    if (ctxt.GetState()->GetName() != "运行状态")
    {
        std::cerr<<"当前状态不处于运行状态，不能结束，当前状态为："<<ctxt.GetState()->GetName()<<std::endl;
        return;
    }
    ctxt.SetState(new DeadState());
    return;
}