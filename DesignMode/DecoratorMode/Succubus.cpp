#include "Succubus.h"
#include <iostream>

Succubus::Succubus(Morrigan* cm):ChangerMorrigan(cm)
{}

void Succubus::SetChange()
{
    std::cout<<"变身女妖的巫妖王！！"<<std::endl;
}

void Succubus::Display()
{
    SetChange();
    ChangerMorrigan::Display();
}