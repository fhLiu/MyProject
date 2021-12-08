#pragma once
#include "StudyBorad.h"

struct JapanStudyAbroad : StudyAbroad
{
    void LookingForSchool() override;
    void ApplyForVisa() override;
    void ReadyGoAbroad() override;
};
