#pragma once
#include "TripMode.h"

struct BySelfDrive : TripMode
{
    void GoOut() override;
};
