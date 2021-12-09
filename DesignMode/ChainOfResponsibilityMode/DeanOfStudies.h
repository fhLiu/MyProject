#pragma once
#include "Leader.h"

struct DeanOfStudies : Leader
{
    bool HandleRequset(int time_len, int& nums) override;
};
