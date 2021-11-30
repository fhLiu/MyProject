#pragma once
#include "AbFactory.h"

struct AbProducerOne:AbProducer
{
    AbProducerOne();
    ~AbProducerOne();

    void Show() override;
};
