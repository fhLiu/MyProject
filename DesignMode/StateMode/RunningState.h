#pragma once
#include "ThreadState.h"
#include "ThreadContext.h"

struct RunningState : ThreadState
{
    RunningState();
    void Suspend(ThreadContext& ctxt);
    void Stop(ThreadContext& ctxt);
};
