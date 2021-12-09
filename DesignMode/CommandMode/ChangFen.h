#pragma once
#include <memory>
#include "BreakFast.h"
#include "ChangFenChef.h"

struct ChangFen : BreakFast
{
    ChangFen();
    void Cooking() override;
private:
    std::shared_ptr<ChangFenChef> sp;
};

