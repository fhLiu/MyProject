#pragma once
#include "ChangerMorrigan.h"

struct Succubus : ChangerMorrigan
{
    Succubus(Morrigan* cm);
    void SetChange();
    void Display() override;
};
