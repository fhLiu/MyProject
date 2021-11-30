#include "SimpleProducer.h"
#include <iostream>

SimpleProducer::SimpleProducer()
{
    std::cout<<"SimpleProducer..."<<std::endl;
}

SimpleProducer::~SimpleProducer()
{
    std::cout<<"~SimpleProducer..."<<std::endl;
}


void ProducerA::ProduceProduct()
{
    std::cout<<"ProducerA"<<std::endl;
}

void ProducerB::ProduceProduct()
{
    std::cout<<"ProducerB"<<std::endl;
}