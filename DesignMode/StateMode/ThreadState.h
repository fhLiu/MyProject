#pragma once
#include <iostream>

struct ThreadState
{
    ThreadState(std::string name):name(name){}
    std::string& GetName(){ return name; }
    virtual ~ThreadState(){}
protected:
    std::string name;
};
