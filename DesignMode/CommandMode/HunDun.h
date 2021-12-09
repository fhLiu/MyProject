#pragma once
#include <memory>
#include "BreakFast.h"
#include "HunDunChef.h"


struct HunDun : BreakFast
{
    HunDun();
    void Cooking() override;
private:
    std::shared_ptr<HunDunChef> sp;
};
