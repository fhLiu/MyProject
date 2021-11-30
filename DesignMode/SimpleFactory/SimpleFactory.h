#pragma once
#include "SimpleProducer.h"

struct SimpleFactory
{
    SimpleFactory();
    ~SimpleFactory();

    SimpleProducer* CreateProduct(PRODUCT_TYPE type);

private:
    SimpleProducer *product;
};
