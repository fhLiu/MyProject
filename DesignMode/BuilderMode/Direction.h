#pragma once

#include <memory>
#include "BJAutomobile.h"
#include "BMAutomobile.h"


struct Direction
{
    Direction(Builder* ptr);

    void Reset(Builder* ptr);
    void CreateAutomobile();

private:
    std::shared_ptr<Builder> m_ptr;
};
