#pragma once

struct Motor
{
    virtual void Drive() = 0;

    virtual ~Motor(){}
};
