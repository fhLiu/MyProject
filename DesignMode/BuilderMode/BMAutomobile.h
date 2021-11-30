#pragma once
#include "Builder.h"

struct BMAutomobile:Builder
{
    void BuildBody();
    void BuildTire();
    void BuildEngine();
    void BuildControlSystem();
    void BuildDisplaySystem();

    void ToString();
    ~BMAutomobile(){}
};
