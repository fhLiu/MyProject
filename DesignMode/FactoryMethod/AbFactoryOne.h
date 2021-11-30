#pragma once
#include "AbFactory.h"
#include "AbProducerOne.h"

struct AbFactoryOne:AbFactory
{
    AbFactoryOne();
    ~AbFactoryOne();

    AbProducer *CreateProduct() override;
};
