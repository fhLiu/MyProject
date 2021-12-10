#pragma once
#include "ThreadState.h"
#include "ThreadContext.h"

struct NewState : ThreadState
{
    NewState();

    void Start(ThreadContext& ctxt);
};
