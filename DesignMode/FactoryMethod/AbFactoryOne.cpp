#include "AbFactoryOne.h"

AbFactoryOne::AbFactoryOne()
{

}

AbFactoryOne::~AbFactoryOne()
{}

AbProducer *AbFactoryOne::CreateProduct()
{
    return new AbProducerOne();
}