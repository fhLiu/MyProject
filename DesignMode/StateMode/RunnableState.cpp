#include "RunnableState.h"
#include "RunningState.h"

RunnableState::RunnableState():ThreadState("就绪状态")
{
    std::cout<<"创建就绪状态"<<std::endl;
}

void RunnableState::GetCPU(ThreadContext& ctxt)
{
    std::cout<<"当前状态获取到CPU运行时间"<<std::endl;
    if (ctxt.GetState()->GetName() != "就绪状态")
    {
        std::cerr<<"当前状态不处于就绪状态，不能获取CPU运行时间，当前状态为："<<ctxt.GetState()->GetName()<<std::endl;
        return;
    }
    ctxt.SetState(new RunningState());
    return;
}