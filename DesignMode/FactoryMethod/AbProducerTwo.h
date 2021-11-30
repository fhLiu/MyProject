#pragma once
#include "AbFactory.h"

struct AbProducerTwo:AbProducer
{
    AbProducerTwo();
    ~AbProducerTwo();

    void Show() override;
};
