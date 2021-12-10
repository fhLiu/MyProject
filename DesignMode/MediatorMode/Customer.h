#pragma once
#include <memory>
#include <iostream>
#include "Medium.h"

struct Customer
{

    Customer(std::string& name):name(name){}
    void SetMedium(Medium* medium);
    std::string& GetName();
    virtual void Send(std::string&) = 0;
    virtual void Receive(std::string&) = 0;

    virtual ~Customer(){}

protected:
    std::shared_ptr<Medium> medium;
    std::string name;
};
