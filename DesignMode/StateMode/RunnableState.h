#pragma once
#include "ThreadState.h"
#include "ThreadContext.h"

struct RunnableState : ThreadState
{
    RunnableState();
    void GetCPU(ThreadContext& ctxt);
};
