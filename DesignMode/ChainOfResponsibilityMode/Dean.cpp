#include "Dean.h"
#include <iostream>

bool Dean::HandleRequset(int time_len, int& nums)
{
    bool result = true;
    nums += 1;
    if (time_len > 9)
    {
        if (GetNext() != nullptr)
        {
            result = GetNext()->HandleRequset(time_len, nums);
        }else{
            std::cout<<"假期天数找不到合适的审批人，请确认请假天数！！"<<std::endl;
            result = false;
        }
        
    }
    else{
        std::cout<<"院长批准你"<<time_len<<"天假期"<<std::endl;
    }

    return result;
}