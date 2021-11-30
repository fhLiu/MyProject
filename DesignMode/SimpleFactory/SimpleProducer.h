#pragma once

enum struct PRODUCT_TYPE{
    TYPE_A, TYPE_B
};

struct SimpleProducer
{

    SimpleProducer();
    virtual ~SimpleProducer();

    virtual void ProduceProduct()=0;
};

struct ProducerA : SimpleProducer
{
    void ProduceProduct();
};

struct ProducerB : SimpleProducer
{
    void ProduceProduct();
};


