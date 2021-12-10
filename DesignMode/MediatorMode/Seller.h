#pragma once
#include "Customer.h"

struct Seller : Customer
{
    Seller(std::string& name):Customer(name){}
    void Send(std::string&) override;
    void Receive(std::string& from, std::string& to) override;
};

