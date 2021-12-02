#pragma once
#include "Color.h"
#include <memory>

struct Bag
{
    void SetColor(Color *color)
    {
        p_color.reset(color);
    }

    virtual std::string GetName() = 0;

protected:
    std::shared_ptr<Color> p_color;
};
