#pragma once
#include "TripMode.h"

struct ByTrain : TripMode
{
    void GoOut() override;
};
