#pragma once
#include <iostream>

struct MemGirls
{
    MemGirls(std::string& name):name(name){}

    std::string& GetName();
    void SetName(std::string& name);

private:
    std::string name;
};
