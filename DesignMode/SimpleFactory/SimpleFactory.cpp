#include "SimpleFactory.h"

SimpleFactory::SimpleFactory():product(nullptr)
{

}

SimpleFactory::~SimpleFactory()
{

}

SimpleProducer *SimpleFactory::CreateProduct(PRODUCT_TYPE type)
{
    switch (type)
    {
    case PRODUCT_TYPE::TYPE_A:
        product = new ProducerA();
        break;
    case PRODUCT_TYPE::TYPE_B:
        product = new ProducerB();
        break;
    default:
        break;
    }

    return product;
}