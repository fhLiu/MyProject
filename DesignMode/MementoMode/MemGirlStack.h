#pragma once
#include <vector>
#include <iostream>
#include "MemGirls.h"

struct MemGirlStack
{
    MemGirlStack();
    bool Push(MemGirls& girl);
    MemGirls* Pop();

private:
    int index;
    std::vector<MemGirls> history;
};
