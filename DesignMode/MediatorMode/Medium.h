#pragma once
#include <iostream>
#include <memory>
#include "Customer.h"

struct  Customer;

struct Medium
{
    virtual void Register(std::shared_ptr<Customer>) = 0;
    virtual void Relay(std::string from, std::string to) = 0;
    virtual ~Medium(){}
};
