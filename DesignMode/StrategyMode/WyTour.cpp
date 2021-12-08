#include "WyTour.h"

void WyTour::SetTripMode(TripMode* mode)
{
    sp.reset(mode);
}

TripMode* WyTour::GetTripMode()
{
    return sp.get();
}

void WyTour::GoOut()
{
    if(sp)
        sp->GoOut();
}