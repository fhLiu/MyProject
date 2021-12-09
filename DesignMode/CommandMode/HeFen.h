#pragma once
#include <memory>
#include "BreakFast.h"
#include "HeFenChef.h"

struct HeFen : BreakFast
{
    HeFen();
    void Cooking() override;
private:
    std::shared_ptr<HeFenChef> sp;
};
