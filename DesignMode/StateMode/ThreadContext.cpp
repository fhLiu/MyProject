#include "ThreadContext.h"
#include "NewState.h"
#include "RunningState.h"
#include "RunnableState.h"
#include "BlockedState.h"
#include "DeadState.h"

ThreadContext::ThreadContext():state(new NewState())
{

}

void ThreadContext::SetState(ThreadState* state)
{
    this->state.reset(state);
}

ThreadState* ThreadContext::GetState()
{
    return this->state.get();
}

void ThreadContext::Start()
{
    ((NewState*)state.get())->Start(*this);
}

void ThreadContext::GetCPU()
{
    ((RunnableState*)state.get())->GetCPU(*this);
}

void ThreadContext::Stop()
{
    ((RunningState*)state.get())->Stop(*this);
}

void ThreadContext::Resume()
{
    ((BlockedState*)state.get())->Resume(*this);
}

void ThreadContext::Suspend()
{
    ((RunningState*)state.get())->Suspend(*this);
}