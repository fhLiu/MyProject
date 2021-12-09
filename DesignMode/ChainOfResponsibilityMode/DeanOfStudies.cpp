#include "DeanOfStudies.h"
#include <iostream>

bool DeanOfStudies::HandleRequset(int time_len, int& nums)
{
    bool result = true;
    nums += 1;
    if (time_len < 12)
    {
        std::cout<<"教务处长批准你"<<time_len<<"天假期"<<std::endl;
    }
    else{
        std::cout<<"假期天数找不到合适的审批人，请确认请假天数！！"<<std::endl;
        result = false;
    }

    return result;
}