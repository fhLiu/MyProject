#pragma once
#include <iostream>

struct Color
{
    virtual std::string GetColor() = 0;
    virtual ~Color(){}
};
