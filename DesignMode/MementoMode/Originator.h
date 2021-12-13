#pragma once
#include "MemGirlStack.h"
#include "MemGirls.h"

struct Originator
{
    Originator(std::string& name);

    void SetAdmire(std::string& name);
    std::string& GetAdmire();
    MemGirls& CreateMementor();
    void RestoreMementor(MemGirls&);

private:
    std::string name;
    MemGirls girl;
};
