#pragma once
#include "Leader.h"

struct ClassAdviser : Leader
{
    bool HandleRequset(int time_len, int& nums) override;
};
