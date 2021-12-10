#include "BlockedState.h"
#include "RunnableState.h"

BlockedState::BlockedState():ThreadState("阻塞状态")
{

}

void BlockedState::Resume(ThreadContext& ctxt)
{
    std::cout<<"Resume 当前阻塞的 Thread!!"<<std::endl;
    if (ctxt.GetState()->GetName() != "阻塞状态")
    {
        std::cerr<<"当前状态不是阻塞状态，不能resume，当前状态为："<<ctxt.GetState()->GetName()<<std::endl;
        return;
    }
    ctxt.SetState(new RunnableState());
    return;
}