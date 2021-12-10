#include "NewState.h"
#include "RunnableState.h"

NewState::NewState():ThreadState("新建状态")
{
    std::cout<<"创建新的线程！"<<std::endl;
}

void NewState::Start(ThreadContext& ctxt)
{
    std::cout<<"开始启动线程！"<<std::endl;
    if (ctxt.GetState()->GetName() != "新建状态")
    {
        std::cerr<<"当前状态不处于新建状态，不能调用start方法，当前状态为："<<ctxt.GetState()->GetName()<<std::endl;
        return;
    }
    ctxt.SetState(new RunnableState());

    return;
}