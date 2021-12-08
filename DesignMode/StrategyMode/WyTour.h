#pragma once
#include <memory>
#include "ByTrain.h"
#include "ByCar.h"
#include "BySelfDrive.h"


struct WyTour
{
    WyTour():sp(nullptr){}
    void SetTripMode(TripMode* mode);
    TripMode* GetTripMode();
    void GoOut();

private:
    std::shared_ptr<TripMode> sp;
};
