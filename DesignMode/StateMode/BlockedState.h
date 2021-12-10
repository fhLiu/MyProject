#pragma once
#include "ThreadState.h"
#include "ThreadContext.h"

struct BlockedState : ThreadState
{
    BlockedState();

    void Resume(ThreadContext& ctxt);
};
