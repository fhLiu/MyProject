#include "AbFactoryTwo.h"

AbFactoryTwo::AbFactoryTwo()
{

}

AbFactoryTwo::~AbFactoryTwo()
{
    
}

AbProducer *AbFactoryTwo::CreateProduct()
{
    return new AbProducerTwo();
}