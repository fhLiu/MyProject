#pragma once
#include "Leader.h"

struct Dean : Leader
{
    bool HandleRequset(int time_len, int& nums) override;
};
