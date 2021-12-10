#pragma once
#include <memory>
#include "ThreadState.h"

struct ThreadContext
{
    ThreadContext();
    void SetState(ThreadState* state);
    ThreadState* GetState();
    void Start();
    void GetCPU();
    void Suspend();
    void Stop();
    void Resume();

private:
    std::shared_ptr<ThreadState> state;
};
