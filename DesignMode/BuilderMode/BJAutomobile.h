#pragma once
#include "Builder.h"

struct BJAutomobile : Builder
{
    void BuildBody();
    void BuildTire();
    void BuildEngine();
    void BuildControlSystem();
    void BuildDisplaySystem();

    void ToString();
    ~BJAutomobile(){}
};
