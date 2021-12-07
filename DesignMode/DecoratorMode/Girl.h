#pragma once
#include "ChangerMorrigan.h"

struct Girl : ChangerMorrigan
{
    Girl(Morrigan* cm);
    void SetChange();
    void Display() override;
};
