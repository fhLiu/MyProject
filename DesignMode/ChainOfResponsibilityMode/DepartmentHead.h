#pragma once
#include "Leader.h"

struct DepartmentHead : Leader
{
    bool HandleRequset(int time_len, int& nums) override;
};
