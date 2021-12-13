#include "Originator.h"

namespace{
    std::string empty("");
}

Originator::Originator(std::string& name):name(name),girl(empty)
{

}

void Originator::SetAdmire(std::string& name)
{
    this->name = name;
}

std::string& Originator::GetAdmire()
{
    return name;
}

MemGirls& Originator::CreateMementor()
{
    girl.SetName(name);
    return girl;
}

void Originator::RestoreMementor(MemGirls& girl)
{
    name = girl.GetName();
}