#pragma once

struct TripMode
{
    virtual void GoOut() = 0;
    virtual ~TripMode(){}
};
