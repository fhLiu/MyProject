#pragma once
#include "AbFactory.h"
#include "AbProducerTwo.h"

struct AbFactoryTwo:AbFactory
{
    AbFactoryTwo();
    ~AbFactoryTwo();

    AbProducer *CreateProduct() override;
};
