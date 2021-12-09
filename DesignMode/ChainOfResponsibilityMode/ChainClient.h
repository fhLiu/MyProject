#pragma once
#include <memory>
#include "DepartmentHead.h"
#include "ClassAdviser.h"
#include "Dean.h"
#include "DeanOfStudies.h"


bool LeaveApprovalProcess(int time_len, int& nums)
{
    Leader *sp1 = new ClassAdviser();
    Leader * sp2 = new DepartmentHead();
    Leader * sp3 = new Dean();
    Leader * sp4 = new DeanOfStudies();

    sp1->SetNext(sp2);
    sp2->SetNext(sp3);
    sp3->SetNext(sp4);

    //handle request...
    return sp1->HandleRequset(time_len, nums);
}