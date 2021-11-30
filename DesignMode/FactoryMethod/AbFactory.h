#pragma once

struct AbProducer;

struct AbFactory
{
    AbFactory();
    virtual ~AbFactory();
    virtual AbProducer *CreateProduct() = 0;
};


struct AbProducer
{
    AbProducer(){}
    virtual ~AbProducer(){}

    virtual void Show() = 0;
};
